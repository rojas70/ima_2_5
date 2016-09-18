// PTSmoothPursuit.cpp : Implementation of CPTSmoothPursuit
#include "stdafx.h"
#include "IMA2_PTVisionLib.h"
#include "PTSmoothPursuit.h"
#include "O:\components\msvbvm60.tlh" // property bag dll

/////////////////////////////////////////////////////////////////////////////
// CPTSmoothPursuit


STDMETHODIMP CPTSmoothPursuit::get_LowPassFilterConstant(double *pVal)
{
	// TODO: Add your implementation code here
	if(m_sLowPassFilterConstantIndex >= 0 && m_sLowPassFilterConstantIndex < 4)
		 *pVal = m_dLowPassFilterConstant[m_sLowPassFilterConstantIndex];
	return S_OK;
}

STDMETHODIMP CPTSmoothPursuit::put_LowPassFilterConstant(double newVal)
{
	// TODO: Add your implementation code here
	if(m_sLowPassFilterConstantIndex >= 0 && m_sLowPassFilterConstantIndex < 4)
		 m_dLowPassFilterConstant[m_sLowPassFilterConstantIndex] = newVal;
	return S_OK;
}

STDMETHODIMP CPTSmoothPursuit::get_SchemaWeights(double *pVal)
{
	// TODO: Add your implementation code here
	if(m_sSchemaWeightsIndex >= 0 && m_sSchemaWeightsIndex < 4)
		*pVal = SchemaWeights[m_sSchemaWeightsIndex];
	return S_OK;
}

STDMETHODIMP CPTSmoothPursuit::put_SchemaWeights(double newVal)
{
	// TODO: Add your implementation code here
	if(m_sSchemaWeightsIndex >=0 && m_sSchemaWeightsIndex < 4)
		SchemaWeights[m_sSchemaWeightsIndex] = newVal;
	return S_OK;
}

// Smooth pursuit to updated location
STDMETHODIMP CPTSmoothPursuit::GetUpdate(SAFEARRAY* Value, short Method)
{
	// TODO: Add your implementation code here
	GetTargetLocation();
	DoPursuit((double*)Value->pvData, Method);
	return S_OK;
}

void CPTSmoothPursuit::Add2VelVector(long VectorNumber, long Length, double *Value, double y_Offset)
{
	SAFEARRAY *mysa;
	m_Bindings->get_Pointers(SysAllocString(L"TargetVelVector"),&m_pIUnkTargetVelVector);

	// Link to the Dynamic Vector Interface
	IDynamicVector* pLink = NULL;

	if( m_pIUnkTargetVelVector != NULL )
	{
		m_pIUnkTargetVelVector->QueryInterface(IID_IDynamicVector,(void **)&pLink);

		if( pLink != NULL )
		{
			int i;
			/*** shift the whole array to the right = Length ***/ 
			for(i=m_sSamplingLength-1;i>=Length;i--)
			{
				m_dVelVector[VectorNumber][i]  = m_dVelVector[VectorNumber][i-Length];
			}			
			/*** add new value to the array ***/ 
			for(i=0;i<Length;i++)
			{
				m_dVelVector[VectorNumber][i] = Value[i]+y_Offset;
			}
			mysa=SafeArrayCreateVector(VT_R8,0,m_sSamplingLength);
			memcpy(mysa->pvData,m_dVelVector[VectorNumber],sizeof(double)*m_sSamplingLength);
			pLink->SetVector(VectorNumber, mysa);
			SafeArrayDestroy(mysa);
			pLink->Release();
		}
		else
		{
			::MessageBox(NULL,"Could not create IDynamicVector interface (binding \"TargetVelVector\")","Error",MB_OK);
		}
	}
	else
	{
		::MessageBox(NULL,"Cound not find component associated with binding \"TargetVelVector\"","Error",MB_OK);
	}
}



void CPTSmoothPursuit::ReadTargetVelocity()
{
	GetTargetLocation();
	/*** x velocity in left target ***/
	m_dTargetVel[0] = m_dLowPassFilterConstant[0]*m_dTargetVel[0]+
					  (1.0f-m_dLowPassFilterConstant[0])*(LeftTarget[0]-m_dPreviousSamplingTargetLocation[0]);
	/*** y velocity in left target ***/
	m_dTargetVel[1] = m_dLowPassFilterConstant[1]*m_dTargetVel[1]+
		              (1.0f-m_dLowPassFilterConstant[1])*(LeftTarget[1]-m_dPreviousSamplingTargetLocation[1]);
	/*** x velocity in right target ***/
	m_dTargetVel[2] = m_dLowPassFilterConstant[2]*m_dTargetVel[2]+
		              (1.0f-m_dLowPassFilterConstant[2])*(RightTarget[0]-m_dPreviousSamplingTargetLocation[2]);
	/*** y velocity in right target ***/
	m_dTargetVel[3] = m_dLowPassFilterConstant[3]*m_dTargetVel[3]+
					  (1.0f-m_dLowPassFilterConstant[3])*(RightTarget[1]-m_dPreviousSamplingTargetLocation[3]);

	m_dPreviousSamplingTargetLocation[0] = LeftTarget[0];
	m_dPreviousSamplingTargetLocation[1] = LeftTarget[1];
	m_dPreviousSamplingTargetLocation[2] = RightTarget[0];
	m_dPreviousSamplingTargetLocation[3] = RightTarget[1];

	Add2VelVector(0, 1, m_dTargetVel,   70);
	Add2VelVector(1, 1, m_dTargetVel+1, 70);
	Add2VelVector(2, 1, m_dTargetVel+2, 70);
	Add2VelVector(3, 1, m_dTargetVel+3, 70);
}

double CPTSmoothPursuit::LowPassMotor()
{
	return 0.0f;
}

void CPTSmoothPursuit::AddToVector(long VectorNumber, long Length, double *Value, double y_Offset)
{
	SAFEARRAY* mysa;

	m_Bindings->get_Pointers(SysAllocString(L"MotorVector"),&m_pIUnkMotorVector);
	
	IDynamicVector* pLink = NULL;

	if( m_pIUnkMotorVector != NULL )
	{
		m_pIUnkMotorVector->QueryInterface(IID_IDynamicVector,(void **)&pLink);

		if( pLink != NULL )
		{
			int i;
			/*** shift the whole array to the right = Length ***/ 
			for(i=m_sSamplingLength-1;i>=Length;i--)
			{
				m_dVector[VectorNumber][i]  = m_dVector[VectorNumber][i-Length];
			}			
			/*** add new value to the array ***/ 
			for(i=0;i<Length;i++)
			{
				m_dVector[VectorNumber][i] = Value[i]+y_Offset;
			}
			mysa=SafeArrayCreateVector(VT_R8,0,m_sSamplingLength);
			memcpy(mysa->pvData,m_dVector[VectorNumber],sizeof(double)*m_sSamplingLength);
			pLink->SetVector(VectorNumber, mysa);
			SafeArrayDestroy(mysa);
			pLink->Release();
		}
		else
		{
			::MessageBox(NULL,"Could not create IDynamicVector interface (binding \"MotorVector\")","Error",MB_OK);
		}
	}
	else
	{
		::MessageBox(NULL,"Cound not find component associated with binding \"MotorVector\"","Error",MB_OK);
	}
}


/*
void CPTSmoothPursuit::SampleCameraHeadAngles()
{

	m_Bindings->get_Pointers(SysAllocString(L"MotionLink"),&m_pIUnkMotorControllerLink);

	IMotionLink*	pLink	= NULL;
	double time;

	if( m_pIUnkMotorControllerLink != NULL )
	{
		m_pIUnkMotorControllerLink->QueryInterface(IID_IMotionLink,(void **)&pLink);

		if( pLink != NULL )
		{
			// get real motors angles
			pLink->GetPositionVector( 4, m_dSampleAngles, &time ); 

			pLink->Release();
		}
	}
}
*/
void CPTSmoothPursuit::RecordMotorValue()
{
	AddToVector(1, 1, m_dSampleAngles , 90);
}


void CPTSmoothPursuit::SetupMotorVector()
{
	m_Bindings->get_Pointers(SysAllocString(L"MotorVector"),&m_pIUnkMotorVector);
	m_Bindings->get_Pointers(SysAllocString(L"TargetVelVector"),&m_pIUnkTargetVelVector);

	IDynamicVector* pLink = NULL;

	if( m_pIUnkMotorVector != NULL )
	{
		m_pIUnkMotorVector->QueryInterface(IID_IDynamicVector,(void **)&pLink);

		if( pLink != NULL )
		{
			/*** set number of vector to 4 (left and right pan-tilt units) **/
			pLink->put_NumVectors(8); 
			pLink->put_VectorLength(m_sSamplingLength);
			pLink->Release();
		}
		else
		{
			::MessageBox(NULL,"Could not create IDynamicVector interface (binding \"MotorVector\")","Error",MB_OK);
		}
	}

	if( m_pIUnkTargetVelVector != NULL )
	{
		m_pIUnkTargetVelVector->QueryInterface(IID_IDynamicVector,(void **)&pLink);

		if( pLink != NULL )
		{
			/*** set number of vector to 4 (left and right pan-tilt units) **/
			pLink->put_NumVectors(4); 
			pLink->put_VectorLength(m_sSamplingLength);
			pLink->Release();
		}
		else
		{
			::MessageBox(NULL,"Could not create IDynamicVector interface (binding \"TargetVelVector\")","Error",MB_OK);
		}
	}

}

void CPTSmoothPursuit::DoPursuit(double *Value, short Method)
{
	double x_dist, y_dist;

	ReadTargetVelocity(); //it seems 'ReadTargetVelocity' is useless for new PTHead (09/08/03)

	switch(Method)
	{
	case 0: /**** PID control ****/
			// HACK
			x_dist = 160.0f - (LeftTarget[0]+RightTarget[0])/2;
			y_dist = 120.0f - (LeftTarget[1]+RightTarget[1])/2;
			/*** update camera ***/
////			Value[0] = 0.0f; // no verge movement
////			Value[1] = 0.0f; // no verge movement
			Value[0] = (x_dist)*SchemaWeights[0];			/** left Pan   **/
			Value[1] = -(y_dist)*SchemaWeights[1];			/** left Tilt  **/
			Value[2] = (x_dist)*SchemaWeights[2];			/** right Pan   **/
			Value[3] = -(y_dist)*SchemaWeights[3];			/** right Tilt  **/
			/*** shall we add smoother motors? ***/
			/*** yes : leave this break uncomment ***/
			/*** no  : comment it out ***/
			break;
	case 1: /**** Lowpass Motor Control ***/
			m_dBuffAngles[0] = Value[0];
			m_dBuffAngles[1] = Value[1];
			m_dBuffAngles[2] = Value[2];
			m_dBuffAngles[3] = Value[3];
			Value[0] = m_dLowPassFilterConstant[0]*m_dPreviousUpdate[0]+
					   (1-m_dLowPassFilterConstant[0])*m_dBuffAngles[0];
			Value[1] = m_dLowPassFilterConstant[1]*m_dPreviousUpdate[1]+
					   (1-m_dLowPassFilterConstant[1])*m_dBuffAngles[1];
			Value[2] = m_dLowPassFilterConstant[2]*m_dPreviousUpdate[2]+
					   (1-m_dLowPassFilterConstant[2])*m_dBuffAngles[2];
			Value[3] = m_dLowPassFilterConstant[3]*m_dPreviousUpdate[3]+
					   (1-m_dLowPassFilterConstant[3])*m_dBuffAngles[3];
			m_dPreviousUpdate[0] = Value[0];
			m_dPreviousUpdate[1] = Value[1];
			m_dPreviousUpdate[2] = Value[2];
			m_dPreviousUpdate[3] = Value[3];

// in order to save time, I cacel the following processes  09/08/03
/*			AddToVector(0, 1, m_dBuffAngles,   70);
			AddToVector(1, 1, m_dBuffAngles+1, 70);
			AddToVector(2, 1, m_dBuffAngles+2, 70);
			AddToVector(3, 1, m_dBuffAngles+3, 70);
			AddToVector(4, 1, m_dPreviousUpdate, 70);
			AddToVector(5, 1, m_dPreviousUpdate+1, 70);
			AddToVector(6, 1, m_dPreviousUpdate+2, 70);
			AddToVector(7, 1, m_dPreviousUpdate+3, 70);
*/			break;
	}
}

void CPTSmoothPursuit::GetTargetLocation()
{
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
			LeftTarget[0]*=320;
			LeftTarget[1]*=240;

			/*** get target location from right camera **/    
			pLink->GetTargetLocation(1,RightTarget,9); 
			// HACK by Anthony
			RightTarget[0]*=320;
			RightTarget[1]*=240;

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


// The OnConstruct Function sets all the bindings for the component, and \
// also replaces FinalComponentInitialization
STDMETHODIMP CPTSmoothPursuit::OnConstruct() {

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

	// TargetVelVector - Retrieves TargetVelVector component
	m_Binding.Name		= SysAllocString(L"TargetVelVector");					
	m_Binding.BindType	= BT_Default;											// Condition to accept a single binding
	m_Binding.Path		= SysAllocString(L"");									// This is the path of the component you are connecting to
	m_Binding.PIDs		= SafeArrayCreateVector(VT_BSTR, 0, 1);					// Create an empty string array
	m_Binding.IIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);			// Create an empty string array
	SafeArrayPutElement(m_Binding.IIDs,x,(void *)SysAllocString(L"IDynamicVector"));
	m_ConfigureBindings->Add(&m_Binding);										// Set up the clients bindings array.	
		// Free Binding Info
		SysFreeString(m_Binding.Name);
		SysFreeString(m_Binding.Path);
		SafeArrayDestroy(m_Binding.PIDs);
		SafeArrayDestroy(m_Binding.IIDs);

	m_Binding.Name		= SysAllocString(L"MotorVector");
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
	
	return S_OK;
}

STDMETHODIMP CPTSmoothPursuit::OnDestruct() { return S_OK; }

STDMETHODIMP CPTSmoothPursuit::Load(VARIANT Data) {

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
		//hRes = pIPB->GetPropertyBag(&m_VBPropertyBag);
		
		// Pass Data to PropertyBag
		hRes = pIPB->SetPropertyBag(&Data);

		// Variable 1
		// Define strings
		ItemName	= SysAllocString(L"SchemaWeights");
		Var			= new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName,Var);  //2nd argument is return value (look retval for help)
		*SchemaWeights = *Var;
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// variable 2
		ItemName	= SysAllocString(L"LowPassFilterConstant");
		Var			= new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName,Var);  //2nd argument is return value (look retval for help)
		*m_dLowPassFilterConstant = *Var;
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Decrement the pointer reference count from our member variable. 
		VariantClear(&m_VBPropertyBag);
		
		// Release
		pIPB->Release();
	
		//////////////////////////////////
		// Final Component Initialization
		//////////////////////////////////
		
		SetupMotorVector();
	return S_OK;

}

STDMETHODIMP CPTSmoothPursuit::Save(VARIANT *pData) {
	
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
		ItemName = SysAllocString(L"SchemaWeights");
		// Store the data and the type of data into a variant_t type
 		Var = new variant_t;
		Var->vt=VT_R8|VT_BYREF;
		Var->pdblVal=SchemaWeights;
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, Var);
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Variable 2
		// Create string names for items to be saved
		ItemName = SysAllocString(L"LowPassFilterConstant");
		// Store the data and the type of data into a variant_t type
 		Var = new variant_t;
		Var->vt=VT_R8|VT_BYREF;
		Var->pdblVal=m_dLowPassFilterConstant;

		// Add an item to the property bag via the wrapper class.
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