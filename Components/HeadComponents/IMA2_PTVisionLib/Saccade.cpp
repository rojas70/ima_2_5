///////////////////////////////////////////
// Should have been named PTSaccade
///////////////////////////////////////////

// Saccade.cpp : Implementation of CSaccade
#include "stdafx.h"
#include "IMA2_PTVisionLib.h"
#include "Saccade.h"
#include "O:\components\msvbvm60.tlh" // property bag dll

#define PIXEL_WIDTH 320
#define PIXEL_HEIGHT 240
/////////////////////////////////////////////////////////////////////////////
// CSaccade

STDMETHODIMP CSaccade::aaSaccade() {
	GetTargetLocation();
	DoSaccade(0);
	DoSaccade(1);

	return S_OK;
}

void CSaccade::GetTargetLocation()
{
    // Bind to the component
    m_Bindings->get_Pointers(SysAllocString(L"VisualInputRep"),&m_pIUnkVisualInputRep);

	IVisualInputRepresentation* pLink = NULL;

	if( m_pIUnkVisualInputRep != NULL )
	{
		m_pIUnkVisualInputRep->QueryInterface(IID_IVisualInputRepresentation,(void **)&pLink);

		if( pLink != NULL )
		{
			/*** get target location from left camera **/
			pLink->GetTargetLocation(0,LeftTarget,9);			
			// HACK by Anthony
			LeftTarget[0]*=PIXEL_WIDTH;
			LeftTarget[1]*=PIXEL_HEIGHT;

			/*** get target location from right camera **/
			pLink->GetTargetLocation(1,RightTarget,9); 
			// HACK by Anthony
			RightTarget[0]*=PIXEL_WIDTH;
			RightTarget[1]*=PIXEL_HEIGHT;
			// DEBUG
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

void CSaccade::SetTargetLocation()
{
    // Bind to the component
    m_Bindings->get_Pointers(SysAllocString(L"VisualInputRep"),&m_pIUnkVisualInputRep);

	IVisualInputRepresentation* pLink = NULL;

	if( m_pIUnkVisualInputRep != NULL )
	{
		m_pIUnkVisualInputRep->QueryInterface(IID_IVisualInputRepresentation,(void **)&pLink);

		if( pLink != NULL )
		{
			/*** get target location from left camera **/
			pLink->SetTargetLocation(0,LeftTarget,9); 
			/*** get target location from right camera **/
			pLink->SetTargetLocation(0,RightTarget,9); 
			// DEBUG
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

void CSaccade::ClearTargetVariables()
{
	for(int i=0;i<9;i++)
		LeftTarget[i] = RightTarget[i] = 0.0f;
}

void CSaccade::ClearTargetLocation()
{
	ClearTargetVariables();
	SetTargetLocation();
}

STDMETHODIMP CSaccade::GetUpdate(long CameraID, double * Value)
{
	// TODO: Add your implementation code here
	GetTargetLocation();
	DoSaccade(CameraID, Value);	
	return S_OK;
}

void CSaccade::ComputeAngles(double x,double y, double* updateAngles)
{
	float input[2];
	float output[2];

// HACK
//	input[0] = ((float)x-160.0f)/160.0f;
	input[0] = (160.0f-(float)x)/160.0f;
	input[1] = (120.0f-(float)y)/120.0f;
//	input[1] = ((float)y-120)/120.0f;
	if(	m_bNeuralNetReady)
	{

		net.SimulateFeedForward(input, output);	
//		updateAngles[0] = (double)output[0]*45.0f;					// updated pan angle
//		updateAngles[1] = (double)output[1]*45.0f;					// updated tilt angle
		updateAngles[0] = (double)output[0]*550*PULSE_TO_ANG_PAN;	// updated pan angle
		updateAngles[1] = (double)output[1]*360*PULSE_TO_ANG_TILT;  // updated tilt angle
	}
	else
		updateAngles[0] = updateAngles[1] = 0.0f;
}

void CSaccade::DoSaccade(long CameraID, double* Value)
{
	double leftBuff[2],rightBuff[2];
	leftBuff[0]=leftBuff[1]=rightBuff[0]=rightBuff[1]=0.0f;

	switch(CameraID)
	{
	case 0:	/*** do left camera ***/
		if(LeftTarget[0]>0 && LeftTarget[1]>0)
		{
			ComputeAngles(LeftTarget[0],LeftTarget[1],leftBuff);
			UpdateAngles[0] = *(Value)   = leftBuff[0];	/** new left angle **/
			UpdateAngles[1] = *(Value+1) = leftBuff[1];
		}
		else
		{
			UpdateAngles[0] = *(Value)   = 0;	/** new left angle **/
			UpdateAngles[1] = *(Value+1) = 0;
		}
		break;
	case 1:
		if(RightTarget[0]>0 && RightTarget[1]>0)
		{
			ComputeAngles(RightTarget[0],RightTarget[1], rightBuff);		
			UpdateAngles[2] = *(Value)   = rightBuff[0]; /** new right angle **/
			UpdateAngles[3] = *(Value+1) = rightBuff[1];
		}
		else
		{
			UpdateAngles[0] = *(Value)   = 0;	/** new left angle **/
			UpdateAngles[1] = *(Value+1) = 0;
		}
		break;
	}
}

void CSaccade::DoSaccade(long CameraID)
{
	double leftBuff[2],rightBuff[2];
	leftBuff[0]=leftBuff[1]=rightBuff[0]=rightBuff[1]=0.0f;

	switch(CameraID)
	{
	case 0:	/*** do left camera ***/
		if(LeftTarget[0]>0 && LeftTarget[1]>0)
		{
			ComputeAngles(LeftTarget[0],LeftTarget[1],leftBuff);
			UpdateAngles[0] = leftBuff[0];	/** new left angle **/
			UpdateAngles[1] = leftBuff[1];
		}
		else
		{
			UpdateAngles[0] = 0;	/** new left angle **/
			UpdateAngles[1] = 0;
		}
		break;
	case 1:
		if(RightTarget[0]>0 && RightTarget[1]>0)
		{
			ComputeAngles(RightTarget[0],RightTarget[1], rightBuff);		
			UpdateAngles[2] = rightBuff[0]; /** new right angle **/
			UpdateAngles[3] = rightBuff[1];
		}
		else
		{
			UpdateAngles[0] = 0;	/** new left angle **/
			UpdateAngles[1] = 0;
		}

		break;
	}
}


BOOL CSaccade::InitializeNeuralNet()
{
	TCHAR *str1,*str2,*str3,*str4;
	USES_CONVERSION;

	// TODO: Add your implementation code here
	str1 = OLE2T((BSTR)m_sNeuralNetFileName[0]);
	str2 = OLE2T((BSTR)m_sNeuralNetFileName[1]);
	str3 = OLE2T((BSTR)m_sNeuralNetFileName[2]);
	str4 = OLE2T((BSTR)m_sNeuralNetFileName[3]);

	ATLTRACE("Opening files %s\n%s\n%s\n%s\n",str1,str2,str3,str4);

	// Initialize Neural Net and check for failure
	if(!net.InitializeWeights(str1,10,2,str2,2,10,str3,str4))
	{
		m_bNeuralNetReady=FALSE;
		::MessageBox(NULL,"Can't initialize Neural Network Module!","Error",MB_ICONERROR);
		return E_FAIL;
	}
	else
	{
		m_bNeuralNetReady=TRUE;
		ATLTRACE("Initialize Neural Net Module OK!\n");
	}
	return S_OK;
}

STDMETHODIMP CSaccade::SaccadeFunction(double * ImagePosition, double * MotorOutput)
{
	// TODO: Add your implementation code here
	if(ImagePosition[0]>0 && ImagePosition[1]>0)
		{
			ComputeAngles(ImagePosition[0],ImagePosition[1],MotorOutput);
		}
		else
		{
			MotorOutput[0] = 0;
			MotorOutput[1] = 0;
		}
	return S_OK;
}


// The OnConstruct Function sets all the bindings for the component, and \
// also replaces FinalComponentInitialization
STDMETHODIMP CSaccade::OnConstruct() {

// TODO: Bindings. Personalize the binding of your component. 

	IMA2_BindingInfo	m_Binding;
	int numiids=1;
	long x[1];
	x[0]=0;

	// VisualInputRep - Retrieves VisualInputRep component
	m_Binding.Name		= SysAllocString(L"VisualInputRep");					// Assign name to object
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
	

// Final Component Initialization equivalent:

	/*****************************
	 load weight and bias files
	 for neural net module
	 ****************************/
	InitializeNeuralNet();


	return S_OK;
}

STDMETHODIMP CSaccade::OnDestruct() { return S_OK; }

STDMETHODIMP CSaccade::Load(VARIANT Data) { return S_OK; }

STDMETHODIMP CSaccade::Save(VARIANT *pData) { return S_OK; }
