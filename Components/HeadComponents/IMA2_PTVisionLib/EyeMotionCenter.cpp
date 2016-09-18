// EyeMotionCenter.cpp : Implementation of CEyeMotionCenter
#include "stdafx.h"
#include "IMA2_PTVisionLib.h"
#include "EyeMotionCenter.h"

#define TILT_MAX_LIMIT  15
#define PIXEL_WIDTH		320
#define PIXEL_HEIGHT	240

/////////////////////////////////////////////////////////////////////////////
// CEyeMotionCenter


STDMETHODIMP CEyeMotionCenter::get_DeadZoneIndex(long *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_lDeadZoneIndex;
	return S_OK;
}

STDMETHODIMP CEyeMotionCenter::put_DeadZoneIndex(long newVal)
{
	// TODO: Add your implementation code here
	m_lDeadZoneIndex = newVal;
	return S_OK;
}

STDMETHODIMP CEyeMotionCenter::get_PTTargetThresholdIndex(long *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_lPTTargetThresholdIndex;
	return S_OK;
}

STDMETHODIMP CEyeMotionCenter::put_PTTargetThresholdIndex(long newVal)
{
	// TODO: Add your implementation code here
	m_lPTTargetThresholdIndex = newVal;
	return S_OK;
}

STDMETHODIMP CEyeMotionCenter::get_DeadZone(double * pVal)
{
	// TODO: Add your implementation code here
	if(m_lDeadZoneIndex >= 0 && m_lDeadZoneIndex < 2)
	 *pVal = m_dDeadZone[m_lDeadZoneIndex];
	return S_OK;
}

STDMETHODIMP CEyeMotionCenter::put_DeadZone(double newVal)
{
	// TODO: Add your implementation code here
	if(m_lDeadZoneIndex >= 0 && m_lDeadZoneIndex < 2)
	 m_dDeadZone[m_lDeadZoneIndex] = newVal;
	return S_OK;
}

STDMETHODIMP CEyeMotionCenter::get_PTTargetThreshold(double * pVal)
{
	// TODO: Add your implementation code here
	if(m_lPTTargetThresholdIndex >= 0 && m_lPTTargetThresholdIndex < 4)
		*pVal=m_dTargetThreshold[m_lPTTargetThresholdIndex]; 
	return S_OK;
}

STDMETHODIMP CEyeMotionCenter::put_PTTargetThreshold(double newVal)
{
	// TODO: Add your implementation code here
	if(m_lPTTargetThresholdIndex >= 0 && m_lPTTargetThresholdIndex < 4)
		m_dTargetThreshold[m_lPTTargetThresholdIndex] = newVal;
	return S_OK;
}

//////////////////////////////////
// Interface callable Functions //
//////////////////////////////////
STDMETHODIMP CEyeMotionCenter::HeadSample()
{
	// Local Variables
	SAFEARRAY* mysa;
	IPTCatch*	pLink	= NULL;

	// Get pointer to object and interface
	m_Bindings->get_Pointers(SysAllocString(L"HeadControl"),&m_pIUnkBPHead);
	if( m_pIUnkBPHead != NULL )
	{
		m_pIUnkBPHead->QueryInterface(IID_IPTCatch,(void **)&pLink);
		if( pLink != NULL ) 
		{
			// Get actual motor angles (LP,LT,RP,RT,OP,AVGT)
			mysa=SafeArrayCreateVector(VT_R8,0,4);
			pLink->SampleHead( mysa ); 
			memcpy(m_dSampleAngles,mysa->pvData,sizeof(double)*4);
			SafeArrayDestroy(mysa);	//crashes right here
		
			// Release I/F
			pLink->Release();
		}
		else
		{
			::MessageBox(NULL,"Could not create IPTCatch interface (binding \"HeadControl\")","Error",MB_OK);
		}
	}
	else
	{
		::MessageBox(NULL,"Cound not find component associated with binding \"HeadControl\"","Error",MB_OK);
	}
	return S_OK;
}

/******************************************************************************************************
/* DoProportionalTracking()
/* This function uses the centroid values computed by the ColorSegmenter.
/* The Centroid values are transmitted to this function through the VisualInputRep component.
/*
/* The method works as follows:
/* 1) Get the centroid values.
/* 2) Compute an error measure: 
/*    The distance of the center of the segmented blob, compared to that of the center of the image.
/* 3) Compute the equivalent number of PT steps to move:
/*    The pixel error is sent to a Neural Network that computes the equivalent motion in the Pan-Tilt system.
/* 4) Add the updated motor angles to the current angles.
/* 5) Compute the average of current and previous angles to reduce the effects of noise and random motion
/* 6) Send new positions to PT system to move the cameras.
******************************************************************************************************/
STDMETHODIMP CEyeMotionCenter::DoProportionalTracking()
{
	bLimitTilt = TRUE;
	double delta_l[2],delta_r[2];
	double m_dMotorUpdate[4];

	// 2) and 3) 
	// Find the distance from the center of the segmented blob to the center of the image in pixels.
	AcquireTarget();
	
	// Perform saccades if object is outside deadzone. Serves to provide stability
	if(m_dTargetDistanceFromCenter[0]>m_dDeadZone[0] || m_dTargetDistanceFromCenter[1]>m_dDeadZone[1])
	{
		// 3) Convert from difference in pixels to motor angle updates using a NN, 
		PerformSaccade(m_dLeftTargetLocation, delta_l);	
		PerformSaccade(m_dRightTargetLocation, delta_r);	

		// Compute the MotorUpdate angles.
		// CameraSpeedFactor is a gain that visually affects the speed of the camera
		// Left
		m_dMotorUpdate[0] = m_dCameraSpeedFactor * delta_l[0];  
		m_dMotorUpdate[1] = m_dCameraSpeedFactor * delta_l[1];
		
		// Right
		m_dMotorUpdate[2] = m_dCameraSpeedFactor * delta_r[0];
		m_dMotorUpdate[3] = m_dCameraSpeedFactor * delta_r[1];

		// 4) Add angle updates to current motor angles.
		m_dUpdateAngles[0] = m_dSampleAngles[0]+m_dMotorUpdate[0];	// The sample angles are obtained by calling HeadSample()
		m_dUpdateAngles[1] = m_dSampleAngles[1]+m_dMotorUpdate[1];
		m_dUpdateAngles[2] = m_dSampleAngles[2]+m_dMotorUpdate[2];
		m_dUpdateAngles[3] = m_dSampleAngles[3]+m_dMotorUpdate[3];

		// 5) Average motor angles
		for(i=0; i<4; i++)
		{
			m_dAverageMotorAngles[i] = (1-alpha)*(m_dUpdateAngles[i]) + alpha*m_dPreviousMotorAngles[i];
			m_dPreviousMotorAngles[i] = m_dAverageMotorAngles[i];
		}
		
		// 6) Send the averaged angles to the Pan-Tilt system
		MoveCatch(m_dAverageMotorAngles);
	}

	// If the centroid reading was zero, and the TargetDistanceFromCenter is also zero, then we need to update the average motor angles.
	else
		for(i=0;i<4;i++)
			m_dAverageMotorAngles[i] = m_dSampleAngles[i];
		

	return S_OK;
}

STDMETHODIMP CEyeMotionCenter::WriteMotorPositions()
{
	SAFEARRAY *mysa;
	IVectorSignal*	pLink	= NULL;

	// Get object and interface's pointer
	m_Bindings->get_Pointers(SysAllocString(L"ActualAngles"),&m_pIUnkMotorOutput);
	if( m_pIUnkMotorOutput != NULL )
	{
		m_pIUnkMotorOutput->QueryInterface(IID_IVectorSignal,(void **)&pLink);

		if( pLink != NULL )
		{
			mysa=SafeArrayCreateVector(VT_R8,0,4);
			memcpy(mysa->pvData,m_dAverageMotorAngles,sizeof(double)*4);
			pLink->SetCurrentVector( mysa );						// set vector signal
			SafeArrayDestroy(mysa);
			// Release I/F
			pLink->Release();
		}
		else
		{
			::MessageBox(NULL,"Could not create IVectorSignal interface (binding \"ActualAngles\")","Error",MB_OK);
		}
	}

	else
	{
		MessageBox(NULL,"Cound not find component associated with binding \"ActualAngles\"","Error",MB_OK);
	}

	return S_OK;
}

BOOL CEyeMotionCenter::PerformSaccade(long CameraID)
{
	// Get component/object's pointer
	m_Bindings->get_Pointers(SysAllocString(L"PTSaccade"),&m_pIUnkSaccade);
	
	// Get objects interface pointer
	ISaccade* pLink = NULL;

	if( m_pIUnkSaccade != NULL )
	{
		m_pIUnkSaccade->QueryInterface(IID_ISaccade,(void **)&pLink);

		if( pLink != NULL )
		{
			switch(CameraID)
			{
			/*** get saccade update angles for left pan-tilt unit **/
			case 0:
				pLink->GetUpdate(0, m_dSaccadeUpdateAngles); 
				break;
			/*** get saccade update angles for right pan-tilt unit **/
			case 1:
				pLink->GetUpdate(1, m_dSaccadeUpdateAngles+2); 
				break;
			}

			// DEBUG
			pLink->Release();
			return TRUE;
		}
		else
		{
			::MessageBox(NULL,"Could not create ISaccade interface (binding \"PTSaccade\")","Error",MB_OK);
			return FALSE;
		}
	}
	else
	{
		::MessageBox(NULL,"Cound not find component associated with binding \"PTSaccade\"","Error",MB_OK);
		return FALSE;
	}
}

////////////////////////////
// Do saccadic motions.
// Calls CSaccade method.
////////////////////////////
void CEyeMotionCenter::PerformSaccade(double * Input, double * Output)
{
	// Get component/object's pointer
	m_Bindings->get_Pointers(SysAllocString(L"PTSaccade"),&m_pIUnkSaccade);
	
	// Get objects interface pointer
	ISaccade* pLink = NULL;

	if( m_pIUnkSaccade != NULL )
	{
		m_pIUnkSaccade->QueryInterface(IID_ISaccade,(void **)&pLink);

		if( pLink != NULL )
		{
			pLink->SaccadeFunction(Input, Output); 
			pLink->Release();
		}
		else
		{
			::MessageBox(NULL,"Could not create ISaccade interface (binding \"PTSaccade\")","Error",MB_OK);
		}
	}
	else
	{
		::MessageBox(NULL,"Cound not find component associated with binding \"PTSaccade\"","Error",MB_OK);
	}
	
}

//////////////////////////////////////////////////////////////////
// Call PTControl methods to move the head to the computed angle
//////////////////////////////////////////////////////////////////
void CEyeMotionCenter::MoveCatch(double * Value)
{
	// Local Variables
	SAFEARRAY* mysa;
	IPTCatch*	pLink = NULL;

	// Check to make sure that the desired angles do not exceed the range of the Pan-Tilt system
	ExceedMotorRange(Value);

	// Get component/object's pointer
	m_Bindings->get_Pointers(SysAllocString(L"HeadControl"),&m_pIUnkBPHead);
	if( m_pIUnkBPHead != NULL )
	{
		m_pIUnkBPHead->QueryInterface(IID_IPTCatch,(void **)&pLink);
		if( pLink != NULL )
		{
			
			// Convert motor angles to motor pulses
			m_dMotorPulses[0] = Value[0] / PULSE_TO_ANG_PAN_LEFT;	
			m_dMotorPulses[2] = Value[2] / PULSE_TO_ANG_PAN_RIGHT;
			m_dMotorPulses[1] = Value[1] / PULSE_TO_ANG_TILT;
			m_dMotorPulses[3] = Value[3] / PULSE_TO_ANG_TILT;

			// This section came before converting the tilt angles and then would limit the tilt pulses
			/*if(bLimitTilt == TRUE)
			{
				if(m_dMotorPulses[1] > TILT_MAX_LIMIT)
				{
					m_dMotorPulses[1] = TILT_MAX_LIMIT;
					bLimitTilt = FALSE;
				}

				if(m_dMotorPulses[3] > TILT_MAX_LIMIT)
				{
					m_dMotorPulses[3] = TILT_MAX_LIMIT;
					bLimitTilt = FALSE;
				}
			}*/


			// Pass the motor pulses to CommandHeadAbsolute
			mysa=SafeArrayCreateVector(VT_R8,0,4);
			memcpy(mysa->pvData,m_dMotorPulses,sizeof(double)*4);
			pLink->CommandHeadAbsolute( mysa ); 
			SafeArrayDestroy(mysa);

			// Release I/F
			pLink->Release();
			
		}
		else
		{
			::MessageBox(NULL,"Could not create IPTCatch interface (binding \"HeadControl\")","Error",MB_OK);
		}
	}
	else
	{
		::MessageBox(NULL,"Cound not find component associated with binding \"HeadControl\"","Error",MB_OK);
	}

}

///////////////////////////////////////////////////////////////////////////
// Get angular location of target and find how far it is from the center
///////////////////////////////////////////////////////////////////////////
void CEyeMotionCenter::AcquireTarget()
{
		/** compute the distance of the target from the center of the image **/	
		double buff1,buff2;

		// Get the Pixel Location of the centroid of the object of interest
		GetTargetLocation();

		// LEFT CAMERA
		// Find the distance between current pixel location and the center of the image for the left camera
		// Assumes a 320x240 image
		if(m_dLeftTargetLocation[0]>0 || m_dLeftTargetLocation[1]>0)
		{
			// Find distance from center for the ImageWidth
			buff1 = (m_dLeftTargetLocation[0]-160);	// Used below to find dist. from center
			// Square the result
			buff1*=buff1;

			// Find distance from center for the ImageHeight
			buff2 = (120-m_dLeftTargetLocation[1]);
			// Square result
			buff2*=buff2;

			// Find the norm of centroid of blob to center of imate
			m_dTargetDistanceFromCenter[0] = sqrt(buff1+buff2);
		}

		else
			m_dTargetDistanceFromCenter[0] = 0;

		// RIGHT CAMERA
		// Find the distance between current pixel location and the center of the image for the right camera
		if(m_dRightTargetLocation[0]>0 || m_dRightTargetLocation[1]>0)
		{
			// Find distance from center for the ImageWidth
			buff1 = (m_dRightTargetLocation[0]-160);
			// Square the result
			buff1*=buff1;

			// Find distance from center for the ImageHeight
			buff2 = (120-m_dRightTargetLocation[1]);
			// Square the result
			buff2*=buff2;

			// Find the norm
			m_dTargetDistanceFromCenter[1] = sqrt(buff1+buff2);
		}

		else
			m_dTargetDistanceFromCenter[1] = 0;

}

/****************************************************************************************************
/* GetTargetLocation()
/* Function:
/* Retreives the relative position of the segmented blob coming from the Segmented Image.
/* I.e. If the blob is at the center of the screen, you will get a target location of (0.5, 0.5).
/* 
/* Calls the function IID_IVisualInputRepresentation::GetTargetLocation(CameraID, pixelLocation, Length)
/* Where,
/*		 CameraId:		left or right camera,
/*		 pixelLocation:	is the variable that stores the relative position of the center of the segmented blob relative to the center of the image
/*		 Length:        is the number of variables (rows, cols)
/*
/* We then transform that relative position into pixel position by multiplying by the pixel
/* height and pixel width (assume 320 x 240).
/* 
/* We retrive this date for both cameras for both pan and tilt.
****************************************************************************************************/
void CEyeMotionCenter::GetTargetLocation()
{
	// Local variables
	IVisualInputRepresentation* pLink = NULL;

	// Get the object's and interface pointer of VisualInputRep
	m_Bindings->get_Pointers(SysAllocString(L"VisualInputRep"),&m_pIUnkVisualInputRep);
	if( m_pIUnkVisualInputRep != NULL )
	{
		m_pIUnkVisualInputRep->QueryInterface(IID_IVisualInputRepresentation,(void **)&pLink);
		if( pLink != NULL )
		{
			// Get the centroid value from the VisualInputRep for the left camera and then the right camera
			pLink->GetTargetLocation(0, m_dLeftTargetLocation, 2);		// Left
			pLink->GetTargetLocation(1, m_dRightTargetLocation,2);		// Right

			// Compute the pixel equivalent for the centroid value
			// Left
			m_dLeftTargetLocation[0]*=PIXEL_WIDTH;						// 320 pixels
			m_dLeftTargetLocation[1]*=PIXEL_HEIGHT;						// 240 pixels			
			// Right
			m_dRightTargetLocation[0]*=PIXEL_WIDTH;
			m_dRightTargetLocation[1]*=PIXEL_HEIGHT;

			// Release object pointer
			pLink->Release();
		}
		else
		{
			::MessageBox(NULL,"Could not create IVisualInputRepresentation interface (binding \"VisualInputRep\")","Error",MB_OK);
		}
	}
	else
	{
		::MessageBox(NULL,"Cound not find component associated with binding \"VisualInputRep\"","Error",MB_OK);
	}
}
/*
void CEyeMotionCenter::ClearUpdateAngles()
{
	for(int i=0;i<4;i++)
		m_dUpdateAngles[i] = 0.0f;
}
*/

BOOL CEyeMotionCenter::ExceedMotorRange(double *Val)
{
	if(Val[0] < m_dTargetThreshold[0])
		Val[0] = m_dTargetThreshold[0];
	else if(Val[0] > m_dTargetThreshold[1])
		Val[0] = m_dTargetThreshold[1];

	if(Val[1] < m_dTargetThreshold[2])
		Val[1] = m_dTargetThreshold[2];
	else if(Val[1] > m_dTargetThreshold[3])
		Val[1] = m_dTargetThreshold[3];
	
	if(Val[2] < m_dTargetThreshold[0])
		Val[2] = m_dTargetThreshold[0];
	else if(Val[2] > m_dTargetThreshold[1])
		Val[2] = m_dTargetThreshold[1];

	if(Val[3] < m_dTargetThreshold[2])
		Val[3] = m_dTargetThreshold[2];
	else if(Val[3] > m_dTargetThreshold[3])
		Val[3] = m_dTargetThreshold[3];

	return TRUE;
}

/*
BOOL CEyeMotionCenter::AnglesAboveThreshold()
{
	if(m_dUpdateAngles[0] > 44.00)
		m_dUpdateAngles[0] = 44.00;
	if(m_dUpdateAngles[0] < -44.00)
		m_dUpdateAngles[0] = -44.00;

	if(m_dUpdateAngles[1] > 44.00)
		m_dUpdateAngles[1] = 44.00;
	if(m_dUpdateAngles[1] < -44.00)
		m_dUpdateAngles[1] = -44.00;

	if(m_dUpdateAngles[2] > 44.00)
		m_dUpdateAngles[2] = 44.00;
	if(m_dUpdateAngles[2] < -44.00)
		m_dUpdateAngles[2] = -44.00;

	if(m_dUpdateAngles[3] > 44.00)
		m_dUpdateAngles[3] = 44.00;
//KH	if(m_dUpdateAngles[3] < -44.00)
//KH		m_dUpdateAngles[3] = -44.00;
	if(m_dUpdateAngles[3] < -50.00)
		m_dUpdateAngles[3] = -50.00;

	return FALSE;
}
*/
/////////////////////////////////////////////////////////////////////
// The OnConstruct Function sets all the bindings for the component
/////////////////////////////////////////////////////////////////////
STDMETHODIMP CEyeMotionCenter::OnConstruct() {

// TODO: Bindings. Personalize the binding of your component. 

	IMA2_BindingInfo	m_Binding;
	int numiids=1;
	long x[1];
	x[0]=0;

	// DisparityVector - Retrieves DisparityVector
/*	m_Binding.Name		= SysAllocString(L"DisparityVector");						// Assign name to object
	m_Binding.BindType	= BT_Default;											// Condition to accept a single binding
	m_Binding.Path		= SysAllocString(L"");									// This is the path of the component you are connecting to
	m_Binding.PIDs		= SafeArrayCreateVector(VT_BSTR, 0, 1);					// Create an empty string array
	m_Binding.IIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);			// Create an empty string array
	SafeArrayPutElement(m_Binding.IIDs,x,(void *)SysAllocString(L"IVectorSignal"));
	m_ConfigureBindings->Add(&m_Binding);										// Set up the clients bindings array.	
		// Free Binding Info
		SysFreeString(m_Binding.Name);
		SysFreeString(m_Binding.Path);
		SafeArrayDestroy(m_Binding.PIDs);
		SafeArrayDestroy(m_Binding.IIDs);
*/
/*
	// MotorInput
	m_Binding.Name		= SysAllocString(LDesiredAngles);					
	m_Binding.BindType	= BT_Default;											// Condition to accept a single binding
	m_Binding.Path		= SysAllocString(L"");									// This is the path of the component you are connecting to
	m_Binding.PIDs		= SafeArrayCreateVector(VT_BSTR, 0, 1);					// Create an empty string array
	m_Binding.IIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);			// Create an empty string array
	SafeArrayPutElement(m_Binding.IIDs,x,(void *)SysAllocString(L"IVectorSignal"));
	m_ConfigureBindings->Add(&m_Binding);										// Set up the clients bindings array.	
		// Free Binding Info
		SysFreeString(m_Binding.Name);
		SysFreeString(m_Binding.Path);
		SafeArrayDestroy(m_Binding.PIDs);
		SafeArrayDestroy(m_Binding.IIDs);
*/	
	// MotorOutput
	m_Binding.Name		= SysAllocString(L"ActualAngles");					
	m_Binding.BindType	= BT_Default;											// Condition to accept a single binding
	m_Binding.Path		= SysAllocString(L"");									// This is the path of the component you are connecting to
	m_Binding.PIDs		= SafeArrayCreateVector(VT_BSTR, 0, 1);					// Create an empty string array
	m_Binding.IIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);			// Create an empty string array
	SafeArrayPutElement(m_Binding.IIDs,x,(void *)SysAllocString(L"IVectorSignal"));
	m_ConfigureBindings->Add(&m_Binding);										// Set up the clients bindings array.	
		// Free Binding Info
		SysFreeString(m_Binding.Name);
		SysFreeString(m_Binding.Path);
		SafeArrayDestroy(m_Binding.PIDs);
		SafeArrayDestroy(m_Binding.IIDs);
	
	// PTControl
	m_Binding.Name		= SysAllocString(L"HeadControl");					
	m_Binding.BindType	= BT_Default;											// Condition to accept a single binding
	m_Binding.Path		= SysAllocString(L"");									// This is the path of the component you are connecting to
	m_Binding.PIDs		= SafeArrayCreateVector(VT_BSTR, 0, 1);					// Create an empty string array
	m_Binding.IIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);			// Create an empty string array
	SafeArrayPutElement(m_Binding.IIDs,x,(void *)SysAllocString(L"IPTCatch"));
	m_ConfigureBindings->Add(&m_Binding);										// Set up the clients bindings array.	
		// Free Binding Info
		SysFreeString(m_Binding.Name);
		SysFreeString(m_Binding.Path);
		SafeArrayDestroy(m_Binding.PIDs);
		SafeArrayDestroy(m_Binding.IIDs);

	// Saccade
	m_Binding.Name		= SysAllocString(L"PTSaccade");					
	m_Binding.BindType	= BT_Default;											// Condition to accept a single binding
	m_Binding.Path		= SysAllocString(L"");									// This is the path of the component you are connecting to
	m_Binding.PIDs		= SafeArrayCreateVector(VT_BSTR, 0, 1);					// Create an empty string array
	m_Binding.IIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);			// Create an empty string array
	SafeArrayPutElement(m_Binding.IIDs,x,(void *)SysAllocString(L"ISaccade"));
	m_ConfigureBindings->Add(&m_Binding);										// Set up the clients bindings array.	
		// Free Binding Info
		SysFreeString(m_Binding.Name);
		SysFreeString(m_Binding.Path);
		SafeArrayDestroy(m_Binding.PIDs);
		SafeArrayDestroy(m_Binding.IIDs);

	// SmoothPursuit
/*	m_Binding.Name		= SysAllocString(L"PTSmoothPursuit");					
	m_Binding.BindType	= BT_Default;											// Condition to accept a single binding
	m_Binding.Path		= SysAllocString(L"");									// This is the path of the component you are connecting to
	m_Binding.PIDs		= SafeArrayCreateVector(VT_BSTR, 0, 1);					// Create an empty string array
	m_Binding.IIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);			// Create an empty string array
	SafeArrayPutElement(m_Binding.IIDs,x,(void *)SysAllocString(L"IPTSmoothPursuit"));
	m_ConfigureBindings->Add(&m_Binding);										// Set up the clients bindings array.	
		// Free Binding Info
		SysFreeString(m_Binding.Name);
		SysFreeString(m_Binding.Path);
		SafeArrayDestroy(m_Binding.PIDs);
		SafeArrayDestroy(m_Binding.IIDs);
*/
	// VisualInputRep
	m_Binding.Name		= SysAllocString(L"VisualInputRep");					
	m_Binding.BindType	= BT_Default;											// Condition to accept a single binding
	m_Binding.Path		= SysAllocString(L"");									// This is the path of the component you are connecting to
	m_Binding.PIDs		= SafeArrayCreateVector(VT_BSTR, 0, 1);					// Create an empty string array
	m_Binding.IIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);			// Create an empty string array
	SafeArrayPutElement(m_Binding.IIDs,x,(void *)SysAllocString(L"IVisualInputRepresentation"));
	m_ConfigureBindings->Add(&m_Binding);										// Set up the clients bindings array.	
		// Free Binding Info
		SysFreeString(m_Binding.Name);
		SysFreeString(m_Binding.Path);
		SafeArrayDestroy(m_Binding.PIDs);
		SafeArrayDestroy(m_Binding.IIDs);

	return S_OK;
}

STDMETHODIMP CEyeMotionCenter::OnDestruct() {	return S_OK; }

//////////////////////////////
// Load values of saved data
//////////////////////////////
STDMETHODIMP CEyeMotionCenter::Load(VARIANT Data) {
	
	// Variables
	BSTR					ItemName = NULL;// The string holding the name of the item to write into the property bag.
	_PropertyBagWrapper*	pIPB;			// COM Interface Pointer to the PropertyBag _Wrapper_ Class
	HRESULT					hRes;			// The HRESULT value we get back from COM calls.
	variant_t				*Var;

	// (1) Create the property bag wrapper class
	// (2) Have the class point to the interface 
	hRes = CoCreateInstance(CLSID_PropertyBagWrapper, NULL, CLSCTX_INPROC_SERVER, IID__PropertyBagWrapper, (LPVOID*)&pIPB);

		if (pIPB == NULL)	
			return !S_OK;

		// Get the pointer to the real VB property bag (the VB object (defined in msvbvm60.dll (aka VBRUN)) that our wrapper class created)
		// hRes = pIPB->GetPropertyBag(&m_VBPropertyBag);
		
		// Pass Data to PropertyBag
		hRes = pIPB->SetPropertyBag(&Data);

		// Variable 1
		// Define strings
		ItemName	= SysAllocString(L"DeadZone-Left");
		Var			= new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName,Var);  //2nd argument is return value (look retval for help)
		m_dDeadZone[0]			= (double)*Var;
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Variable 2
		ItemName	= SysAllocString(L"DeadZone-Right");
		Var			= new variant_t;
		pIPB->GetFromPropertyBag(&ItemName,Var);  //2nd argument is return value (look retval for help)
		m_dDeadZone[1]			= (double)*Var;
				// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Variable 3
		ItemName	= SysAllocString(L"TargetThreshold-0");
		Var			= new variant_t;
		pIPB->GetFromPropertyBag(&ItemName,Var);  //2nd argument is return value (look retval for help)
		m_dTargetThreshold[0]		= (double)*Var;
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Variable 4
		ItemName	= SysAllocString(L"TargetThreshold-1");
		Var			= new variant_t;
		pIPB->GetFromPropertyBag(&ItemName,Var);  //2nd argument is return value (look retval for help)
		m_dTargetThreshold[1]		= (double)*Var;
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Variable 5
		ItemName	= SysAllocString(L"TargetThreshold-2");
		Var			= new variant_t;
		pIPB->GetFromPropertyBag(&ItemName,Var);  //2nd argument is return value (look retval for help)
		m_dTargetThreshold[2]		= (double)*Var;
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Variable 6
		ItemName	= SysAllocString(L"TargetThreshold-3");
		Var			= new variant_t;
		pIPB->GetFromPropertyBag(&ItemName,Var);  //2nd argument is return value (look retval for help)
		m_dTargetThreshold[3]		= (double)*Var;
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Variable 7
		ItemName	= SysAllocString(L"CameraSpeedFactor");
		Var			= new variant_t;
		pIPB->GetFromPropertyBag(&ItemName,Var);  //2nd argument is return value (look retval for help)
		m_dCameraSpeedFactor		= (double)*Var;
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Decrement the pointer reference count from our member variable. 
		VariantClear(&m_VBPropertyBag);
		
		// Release
		pIPB->Release();

	return S_OK;

}

//////////////////////
// Saved properties
//////////////////////
STDMETHODIMP CEyeMotionCenter::Save(VARIANT *pData) {
	
	// Variables
	BSTR					ItemName = NULL;// The string holding the name of the item to write into the property bag.
	variant_t				*Var;
	_PropertyBagWrapper		*pIPB;			// COM Interface Pointer to the PropertyBag _Wrapper_ Class
	HRESULT					hRes;			// The HRESULT value we get back from COM calls.

	// (1) Create the property bag wrapper class
	// (2) Have the class point to the interface 
	hRes = CoCreateInstance(CLSID_PropertyBagWrapper, NULL, CLSCTX_INPROC_SERVER, IID__PropertyBagWrapper, (LPVOID*)&pIPB);

		if (pIPB == NULL)	
			return !S_OK;
		
		// Variable 1
		// Create string names for items to be saved
		ItemName = SysAllocString(L"DeadZone-Left");
		// Store the data and the type of data into a variant_t type
		Var = new variant_t(m_dDeadZone[0], VT_R8);		// Casting to long, b/c BOOL (which is an int) is not accepted by the variant_t functions
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, Var);
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Variable 2
		ItemName = SysAllocString(L"DeadZone-Right");
		Var = new variant_t(m_dDeadZone[1], VT_R8);
		hRes = pIPB->AddToPropertyBag(&ItemName, Var);
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Variable 3
		ItemName = SysAllocString(L"TargetThreshold-0");
		Var = new variant_t(m_dTargetThreshold[0], VT_R8);
		hRes = pIPB->AddToPropertyBag(&ItemName, Var);
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Variable 4
		ItemName = SysAllocString(L"TargetThreshold-1");
		Var = new variant_t(m_dTargetThreshold[1], VT_R8);
		hRes = pIPB->AddToPropertyBag(&ItemName, Var);
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Variable 5
		ItemName = SysAllocString(L"TargetThreshold-2");
		Var = new variant_t(m_dTargetThreshold[2], VT_R8);
		hRes = pIPB->AddToPropertyBag(&ItemName, Var);
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Variable 6
		ItemName = SysAllocString(L"TargetThreshold-3");
		Var = new variant_t(m_dTargetThreshold[3], VT_R8);
		hRes = pIPB->AddToPropertyBag(&ItemName, Var);
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Variable 7
		ItemName = SysAllocString(L"CameraSpeedFactor");
		Var = new variant_t(m_dCameraSpeedFactor, VT_R8);
		hRes = pIPB->AddToPropertyBag(&ItemName, Var);
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Returns a pointer to the PropertyBag as a VARIANT
		hRes = pIPB->GetPropertyBag(&m_VBPropertyBag);
		
		// Copy the contents of the property bag to the pData VARIANT
		VariantCopy(pData, &m_VBPropertyBag);

		// Save the size of the data 
		m_lDataSize = pData->parray->rgsabound[0].cElements;		

		// Decrement the pointer reference count from our member variable. 
		VariantClear(&m_VBPropertyBag);

		// Release
		pIPB->Release();

	return S_OK;
}

/////////////////////////////////////////////////
// Equivalent to Final Component Initzialization 
// Move head to position indicated by PTDesiredAngles
// Often it is the home position. Serves to reset the
// CameraHead position.
/////////////////////////////////////////////////
STDMETHODIMP CEyeMotionCenter::Initialize()
{
	// Local variables
	int i;

	// These variables are initialized here again for ocassions in which the component has been started and then 
	// a different goal is set and the component is re-started.
	for(i=0;i<4;i++)
	{
		 m_dSampleAngles[i]			= 0.0;
		 m_dUpdateAngles[i]			= 0.0;
		 m_dSaccadeUpdateAngles[i]	= 0.0;
		 m_dMotorAngles[i]			= 0.0;
		 m_dAverageMotorAngles[i]	= 0.0;
	}

	if(m_bAssembly == TRUE)
	{
		// Starting positions for 
		double AssemblyDemoStartingPositionAngles[4] = {-15,-40,15,-40};

		// Adjust threshold angles
		m_dTargetThreshold[0]				= -45.0;	// Min Pan-Angle
		m_dTargetThreshold[1]				=  45.0;	// Max Pan-Angle
		m_dTargetThreshold[2]				= -80.0;	// Min Tilt-Angle
		m_dTargetThreshold[3]				= -10.0;	// Max Tilt-Angle

		// Assign PreviousMotorAngles to AssemblyDemoStartingPositions[]
		m_dPreviousMotorAngles[0]			= AssemblyDemoStartingPositionAngles[0];
		m_dPreviousMotorAngles[1]			= AssemblyDemoStartingPositionAngles[1];
		m_dPreviousMotorAngles[2]			= AssemblyDemoStartingPositionAngles[2];
		m_dPreviousMotorAngles[3]			= AssemblyDemoStartingPositionAngles[3];

		MoveCatch(AssemblyDemoStartingPositionAngles);
	}

	else
		MoveCatch(m_dUpdateAngles);					// Move the PT system to the home position

	return S_OK;
}

STDMETHODIMP CEyeMotionCenter::get_CameraSpeedFactor(double *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_dCameraSpeedFactor;
	return S_OK;
}

STDMETHODIMP CEyeMotionCenter::put_CameraSpeedFactor(double newVal)
{
	// TODO: Add your implementation code here
	if(newVal >= 0 && newVal <= 1.0)
		m_dCameraSpeedFactor = newVal;
	return S_OK;
}
