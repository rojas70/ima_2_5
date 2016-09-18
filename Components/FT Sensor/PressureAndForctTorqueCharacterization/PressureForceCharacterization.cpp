// PressureForceCharacterization.cpp : Implementation of CPressureForceCharacterization
#include "stdafx.h"
#include "PressureAndForctTorqueCharacterization.h"
#include "PressureForceCharacterization.h"
#include <time.h>

#define NUM_AXES 6
/////////////////////////////////////////////////////////////////////////////////////////////////
//                        CPressureForceCharacterization
// 
// The goal of the program is to create an easy-to-understand series of functions
// that will allow us to change the pressure of any joint, in single instances, or
// series of instances, and be able to record the values for pressure, force, and torque.
/////////////////////////////////////////////////////////////////////////////////////////////////


STDMETHODIMP CPressureForceCharacterization::OnConstruct() {

// TODO: Bindings. Personalize the binding of your component. 

	int numiids;
	IMA2_BindingInfo	BindInf;
	numiids=1;

	// 1. OutputPressureVector
	BindInf.Name		= SysAllocString(L"OutputPressureVector");			// Assign name to object
	BindInf.BindType	= BT_Collection;									// Condition to accept multiple targets
	BindInf.Path		= SysAllocString(L"");								// This must be the path of our component
	BindInf.PIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);		// Create and empty string array
	BindInf.IIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);		// Create and empty string array
	m_ConfigureBindings->Add(&BindInf);										// Set up the clients bindings array.	

	// 2. StateMachine - This is in order to send to the state machine a Signal String.
	// This string will replace the former AgentDispatchEvent() call
	BindInf.Name		= SysAllocString(L"StateMachine");					
	m_ConfigureBindings->Add(&BindInf);

	// 3. FTSensorCom - Connect to the FTSensor component to access functions to retrieve data
	BindInf.Name		= SysAllocString(L"FTSensorCom");
	m_ConfigureBindings->Add(&BindInf);

	// 4. SampleIndPressure - Connect to this component to actually move the joints
	BindInf.Name		= SysAllocString(L"SampIndPressure");
	m_ConfigureBindings->Add(&BindInf);

	// Deallocate storage
	SysFreeString(BindInf.Name);
	SysFreeString(BindInf.Path);
	SafeArrayDestroy(BindInf.PIDs);
	SafeArrayDestroy(BindInf.IIDs);
	
	return S_OK;
}

STDMETHODIMP CPressureForceCharacterization::OnDestruct() 
{	
	CloseFile();
	return S_OK; 
}

//////////////////////////////
// Load values of saved data
//////////////////////////////
STDMETHODIMP CPressureForceCharacterization::Load(VARIANT Data) {
	
	// Variables
	BSTR					ItemName = NULL;// The string holding the name of the item to write into the property bag.
	_PropertyBagWrapper*	pIPB;			// COM Interface Pointer to the PropertyBag _Wrapper_ Class
	HRESULT					hRes;			// The HRESULT value we get back from COM calls.
	variant_t				*ItemValue;

	// (1) Create the property bag wrapper class
	// (2) Have the class point to the interface 
	hRes = CoCreateInstance(CLSID_PropertyBagWrapper, NULL, CLSCTX_INPROC_SERVER, IID__PropertyBagWrapper, (LPVOID*)&pIPB);

		if (pIPB == NULL)	
			return !S_OK;

		// Get the pointer to the real VB property bag (the VB object (defined in msvbvm60.dll (aka VBRUN)) that our wrapper class created)
		// hRes = pIPB->GetPropertyBag(&m_VBPropertyBag);
		
		// Pass Data to PropertyBag
		hRes = pIPB->SetPropertyBag(&Data);


		// Constants for angle input conversions

		// m_dHomingSteps
		ItemName	= SysAllocString(L"HomingSteps");	// Define strings
		ItemValue	= new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName,ItemValue);		// 2nd argument is return value (look retval for help)
		m_dHomingSteps	= (float)*ItemValue;
		// Deallocate
		SysFreeString(ItemName);
		// Delete our variants
		delete ItemValue;

		// Variable m_NumAxes
		ItemName	= SysAllocString(L"NumAxes");	// Define strings
		ItemValue			= new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		m_NumAxes	= (long)*ItemValue;
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_pOutputMax
		// Define strings
		ItemName	= SysAllocString(L"OutputMax");
		ItemValue			= new variant_t;
		// Read Data from the property bag
		pIPB->GetArrayFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(m_pOutputMax, ItemValue->parray->pvData, sizeof(double)*NUM_AXES);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_pOutputMin
		// Define strings
		ItemName	= SysAllocString(L"OutputMin");
		ItemValue			= new variant_t;
		// Read Data from the property bag
		pIPB->GetArrayFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(m_pOutputMin, ItemValue->parray->pvData, sizeof(double)*NUM_AXES);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_LeftArm
		// Define strings
		ItemName	= SysAllocString(L"LeftArm");
		ItemValue			= new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		put_LeftArm((short)*ItemValue);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// m_bstrInputFile
		ItemName	= SysAllocString(L"FileName");
		ItemValue	= new variant_t;
		pIPB->GetFromPropertyBag(&ItemName,ItemValue);	//2nd argument is return value (look retval for help)
		SysReAllocString(&m_bstrInputFile,ItemValue->bstrVal);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Decrement the pointer reference count from our member variable. 
		VariantClear(&m_VBPropertyBag);
		
		// Release
		pIPB->Release();

	return S_OK;

}

STDMETHODIMP CPressureForceCharacterization::Save(VARIANT * pData)
{
	// Variables
	BSTR					ItemName = NULL;// The string holding the name of the item to write into the property bag.
	variant_t*				ItemValue;
	HRESULT					hRes;			// The HRESULT value we get back from COM calls.
	_PropertyBagWrapper*	pIPB;			// COM Interface Pointer to the PropertyBag _Wrapper_ Class

	// Create Class with CoCreateInstance (definition can be found in MSDN).
	// Create the property bag wrapper class, put pointer to the Interface in pIPB
	hRes = CoCreateInstance(CLSID_PropertyBagWrapper, NULL, CLSCTX_INPROC_SERVER, IID__PropertyBagWrapper, (LPVOID*)&pIPB);

	if (pIPB == NULL)	
		return !S_OK;

	// m_dHomingSteps
	ItemName = SysAllocString(L"HomingSteps");
	// Store the data and the type of data into a variant_t type
	ItemValue = new variant_t(m_dHomingSteps);//, VT_R4);
	// Add an item to the property bag via the wrapper class.
	hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
	// Free the strings memory location
	SysFreeString(ItemName);
	// Delete our variants
	delete ItemValue;

	// m_NumAxes
	ItemName = SysAllocString(L"NumAxes");
	// Store the data and the type of data into a variant_t type
	ItemValue = new variant_t(m_NumAxes, VT_I4);
	// Add an item to the property bag via the wrapper class.
	hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
	// Free the strings memory location
	SysFreeString(ItemName);
	// Delete our variants
	delete ItemValue;

	// m_pOutputMax
	ItemName = SysAllocString(L"OutputMax");
	// Store the data and the type of data into a variant_t type
	ItemValue=new variant_t;
	ItemValue->vt=VT_R8|VT_ARRAY;
	// Store the data and the type of data into a variant_t type
	ItemValue->parray=SafeArrayCreateVector(VT_R8,0,NUM_AXES);
	memcpy(ItemValue->parray->pvData,m_pOutputMax,NUM_AXES*sizeof(double));
	// Add an item to the property bag via the wrapper class.
	hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
	// Free the strings memory location
	SysFreeString(ItemName);
	// Delete our variants
	delete ItemValue;

	// m_pOutputMin
	ItemName = SysAllocString(L"OutputMin");
	// Store the data and the type of data into a variant_t type
	ItemValue = new variant_t;
	ItemValue->vt=VT_ARRAY|VT_R8;
	ItemValue->parray=SafeArrayCreateVector(VT_R8,0,NUM_AXES);
	memcpy(ItemValue->parray->pvData,m_pOutputMin,NUM_AXES*sizeof(double));
	// Add an item to the property bag via the wrapper class.
	hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
	// Free the strings memory location
	SysFreeString(ItemName);
	// Delete our variants
	delete ItemValue;

	// m_LeftArm
	ItemName = SysAllocString(L"LeftArm");
	// Store the data and the type of data into a variant_t type
	ItemValue = new variant_t(m_LeftArm, VT_I2);
	// Add an item to the property bag via the wrapper class.
	hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
	// Free the strings memory location
	SysFreeString(ItemName);
	// Delete our variants
	delete ItemValue;

	// m_bstrInputFile
	ItemName = SysAllocString(L"FileName");
	ItemValue = new variant_t(m_bstrInputFile);		// Variant stores variable as a BSTR 
	hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
	// Deallocate
	SysFreeString(ItemName);
	delete ItemValue;


		// Get the pointer to the real VB property bag (the VB object (defined in msvbvm60.dll (aka VBRUN)) that our wrapper class created)
	hRes = pIPB->GetPropertyBag(&m_VBPropertyBag);
		
	// Copy the value VB gave to us into the return value of this function (which will be returned to whatever's calling our save function)
	VariantCopy(pData, &m_VBPropertyBag);

	// Decrement the pointer reference count from our member variable. 
	VariantClear(&m_VBPropertyBag);

	// Release
	pIPB->Release();

	return S_OK;
}



///////////////////////////
//        Get / Put Methods
///////////////////////////
STDMETHODIMP CPressureForceCharacterization::get_HomingSteps(float *pVal)
{
	// TODO: Add your implementation code here
	if (pVal != NULL)
		*pVal = 4.0f*m_dHomingSteps;

	return S_OK;
}

STDMETHODIMP CPressureForceCharacterization::put_HomingSteps(float newVal)
{
	// TODO: Add your implementation code here
	if (newVal > 0)
		m_dHomingSteps = newVal/4.0f;
	return S_OK;
}


STDMETHODIMP CPressureForceCharacterization::get_OutputMinIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal != NULL)
		*pVal=m_sOutputMinIndex;

	return S_OK;
}

STDMETHODIMP CPressureForceCharacterization::put_OutputMinIndex(short newVal)
{
	// TODO: Add your implementation code here
	if (newVal >= 0 && newVal < NUM_AXES)
		m_sOutputMinIndex = newVal;

	return S_OK;
}

STDMETHODIMP CPressureForceCharacterization::get_OutputMaxIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal != NULL)
		*pVal=m_sOutputMaxIndex;

	return S_OK;
}

STDMETHODIMP CPressureForceCharacterization::put_OutputMaxIndex(short newVal)
{
	// TODO: Add your implementation code here
	if (newVal >= 0 && newVal < NUM_AXES)
		m_sOutputMaxIndex = newVal;
	return S_OK;
}

STDMETHODIMP CPressureForceCharacterization::get_OutputMin(double *pVal)
{
	// TODO: Add your implementation code here

	if (pVal != NULL)
		*pVal = m_pOutputMin[m_sOutputMinIndex];
	return S_OK;
}

STDMETHODIMP CPressureForceCharacterization::put_OutputMin(double newVal)
{
	// TODO: Add your implementation code here
	if (m_sOutputMinIndex < NUM_AXES)
		m_pOutputMin[m_sOutputMinIndex] = newVal;
	return S_OK;
}

STDMETHODIMP CPressureForceCharacterization::get_OutputMax(double *pVal)
{
	// TODO: Add your implementation code here
	if (m_sOutputMaxIndex >= 0 && m_sOutputMaxIndex < NUM_AXES)
		*pVal = m_pOutputMax[m_sOutputMaxIndex];
	return S_OK;
}

STDMETHODIMP CPressureForceCharacterization::put_OutputMax(double newVal)
{
	// TODO: Add your implementation code here
	if (m_sOutputMaxIndex < NUM_AXES)
		m_pOutputMax[m_sOutputMaxIndex] = newVal;
	return S_OK;
}

STDMETHODIMP CPressureForceCharacterization::Initialize()
{
	// TODO: Add your implementation code here
	m_CurrentStep			=   0;	// Reset the homing steps
	m_BaseStep				=   0;
	m_sWhatJointIsIt   		=   0;
	m_sNoOfSteps			=   0;
	m_dChangeinPressure		= 0.0;

	CloseFile();
	OpenFile();

	return S_OK;
}

STDMETHODIMP CPressureForceCharacterization::get_LeftArm(short *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_LeftArm;
	return S_OK;
}

STDMETHODIMP CPressureForceCharacterization::put_LeftArm(short newVal)
{
	// TODO: Add your implementation code here
	m_LeftArm = newVal;

	// This value could be used to change the sequence for the homing controller for the left arm.
	// This has not been done yet, but one can see the homing sequence seen in the right arm for 
	// the left arm as well.

	// Juan Rojas. Feb 06
	return S_OK;
}


STDMETHODIMP CPressureForceCharacterization::get_PressureForRubbertuatorPair1(double *pVal)
{
	// TODO: Add your implementation code here
	if (*pVal != NULL)
			*pVal = m_pdOriginalPressure[0];			
	return S_OK;
}

STDMETHODIMP CPressureForceCharacterization::put_PressureForRubbertuatorPair1(double newVal)
{
	// TODO: Add your implementation code here
	if( (newVal<m_pOutputMin[0]) && (newVal>m_pOutputMax[0]) )
		m_pdOriginalPressure[0]	= newVal;
	return S_OK;
}

STDMETHODIMP CPressureForceCharacterization::get_PressureForRubbertuatorPair2(double *pVal)
{
	// TODO: Add your implementation code here
	if (*pVal != NULL)
			*pVal = m_pdOriginalPressure[1];
	return S_OK;
}

STDMETHODIMP CPressureForceCharacterization::put_PressureForRubbertuatorPair2(double newVal)
{
	// TODO: Add your implementation code here
	if( (newVal<m_pOutputMin[1]) && (newVal>m_pOutputMax[1]) )
		m_pdOriginalPressure[1]	= newVal;

	return S_OK;
}

STDMETHODIMP CPressureForceCharacterization::get_PressureForRubbertuatorPair3(double *pVal)
{
	// TODO: Add your implementation code here
	if (*pVal != NULL)
			*pVal = m_pdOriginalPressure[2];			
	return S_OK;
}

STDMETHODIMP CPressureForceCharacterization::put_PressureForRubbertuatorPair3(double newVal)
{
	// TODO: Add your implementation code here
	if( (newVal<m_pOutputMin[2]) && (newVal>m_pOutputMax[2]) )
		m_pdOriginalPressure[2]	= newVal;

	return S_OK;
}

STDMETHODIMP CPressureForceCharacterization::get_PressureForRubbertuatorPair4(double *pVal)
{
	// TODO: Add your implementation code here
	if (*pVal != NULL)
			*pVal = m_pdOriginalPressure[3];		
	return S_OK;
}

STDMETHODIMP CPressureForceCharacterization::put_PressureForRubbertuatorPair4(double newVal)
{
	// TODO: Add your implementation code here
	if( (newVal<m_pOutputMin[3]) && (newVal>m_pOutputMax[3]) )
		m_pdOriginalPressure[3]	= newVal;

	return S_OK;
}

STDMETHODIMP CPressureForceCharacterization::get_PressureForRubbertuatorPair5(double *pVal)
{
	// TODO: Add your implementation code here
	if (*pVal != NULL)
			*pVal = m_pdOriginalPressure[4];		
	return S_OK;
}

STDMETHODIMP CPressureForceCharacterization::put_PressureForRubbertuatorPair5(double newVal)
{
	// TODO: Add your implementation code here
	if( (newVal<m_pOutputMin[4]) && (newVal>m_pOutputMax[4]) )
		m_pdOriginalPressure[4]	= newVal;

	return S_OK;
}

STDMETHODIMP CPressureForceCharacterization::get_PressureForRubbertuatorPair6(double *pVal)
{
	// TODO: Add your implementation code here
	if (*pVal != NULL)
			*pVal = m_pdOriginalPressure[5];		
	return S_OK;
}

STDMETHODIMP CPressureForceCharacterization::put_PressureForRubbertuatorPair6(double newVal)
{
	// TODO: Add your implementation code here
	if( (newVal<m_pOutputMin[5]) && (newVal>m_pOutputMax[5]) )
		m_pdOriginalPressure[5] = newVal;

	return S_OK;
}

STDMETHODIMP CPressureForceCharacterization::get_FileName(BSTR *pVal)
{
	// TODO: Add your implementation code here
	*pVal = SysAllocString(m_bstrInputFile);
	ATLTRACE("get_FileName: FileName name is m_bstrInputFile\n");

	return S_OK;
}

STDMETHODIMP CPressureForceCharacterization::put_FileName(BSTR newVal)
{
	// TODO: Add your implementation code here
	SysReAllocString(&m_bstrInputFile,newVal);
	ATLTRACE("put_FileNameName\n");

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
// The arm is moved through its entire joint range to find the encoder zero locations. 
// The pressure values for the motion sequence are computed by the Homer mechanism. 
// Each time the mechanism is invoked, it outputs the next pressure in the sequence. 
// In Ima 1.0, the call was designed to call AgentDispatchEvent(-2,-2) to causes the 
// state machine to transition to State 1.)
/////////////////////////////////////////////////////////////////////////
STDMETHODIMP CPressureForceCharacterization::StartCharacerizationProcess()
{/*	
	// Variables
	SAFEARRAY *mysa;
	long Index,VIndex = 0;
	double Value[NUM_AXES];

	// Bindings
	IVectorSignal *pIVS	= NULL;
	IStateMachine *pISM = NULL;

	// Get object and interface pointers
	m_Bindings->get_Pointers(SysAllocString(L"OutputPressureVector"), &m_pIUnkPressure);
	if (m_pIUnkPressure != NULL)
	{
		m_pIUnkPressure->QueryInterface(IID_IVectorSignal,(void **)&pIVS);
		if (pIVS != NULL)
		{
			/******************************************************************************/
			// Run BASE (joint 0) and Joints 1-5 through first quarter of trajectory range
			// Increase counter for base:	m_BaseStep++
			// Increase counter for joints: m_CurrentStep++
			// Total trajectory = 4*m_dHomingSteps
			//
			// The different portions of code below normalize the output pressure
			// based on what part of the trajectory is being considered for the BASE and 
			// for the Joints 1-5 based out of OutputMax and OutputMin
			// These pressures are then sent to the Pressure Vector Signal which are used by the
			// SampIndPressure.HW_IO functions to apply to the ServoValves.
			// Juan Rojas. Nov 2005. 
			/******************************************************************************/

			// Use the following code for the right arm. The left arm chanages the order slightly.

	// MOVE UP AND RIGHT TOWARDS THE BACK
/*				if(m_CurrentStep < m_dHomingSteps && m_BaseStep < m_dHomingSteps)
				{
					// Get output pressure vector
					mysa = SafeArrayCreateVector(VT_R8,0,m_NumAxes);
					pIVS->GetCurrentVector(mysa);
					memcpy(Value, mysa->pvData, sizeof(double)*m_NumAxes);

					for (Index = 0; Index < m_NumAxes; Index++)
						Value[Index] = m_pOutputMin[Index] * ((double) m_CurrentStep  / (double) m_dHomingSteps);		// m_pOutputMin=-2000	

					// Set the output pressure vector
 					memcpy(mysa->pvData,Value,sizeof(double)*m_NumAxes);
					// We use a harcoded index 0 to try to replicate behavior in IMA 1
					pIVS->SetVector(0,mysa);
					// Destroy SafeArray
					SafeArrayDestroy(mysa);
					m_CurrentStep++;
					m_BaseStep++;
				}
				
				// First compute the base value (3 choices) and then the rest of the joints
				/***********************************************************/
				// Run BASE through full range: arm rotates from right to left
				// Value[0] - Increment BASE counter
				/***********************************************************/
/*				else if(m_CurrentStep == m_dHomingSteps && m_BaseStep < 2*m_dHomingSteps)
				{
					mysa = SafeArrayCreateVector(VT_R8,0,m_NumAxes);
					pIVS->GetCurrentVector(mysa);
					memcpy(Value, mysa->pvData, sizeof(double)*m_NumAxes);

					Value[0] = m_pOutputMin[0] * 
						((double) 2*m_dHomingSteps - (double) m_BaseStep ) / (double) m_dHomingSteps;

	//ROTATE IN AROUND THE BASE 90 DEGREES	
					memcpy(mysa->pvData,Value,sizeof(double)*m_NumAxes);
					pIVS->SetVector(0,mysa);
					// Destroy SafeArray
					SafeArrayDestroy(mysa);
					m_BaseStep++;
				}
				/***********************************************************/
				// Run BASE - Value[0] - through 3/4 of trajectory range 
				// Increment BASE counter
				/***********************************************************/
/*				else if(m_CurrentStep == m_dHomingSteps && m_BaseStep < 3*m_dHomingSteps)
				{
					mysa = SafeArrayCreateVector(VT_R8,0,m_NumAxes);
					pIVS->GetCurrentVector(mysa);
					memcpy(Value, mysa->pvData, sizeof(double)*m_NumAxes);
					
					Value[0] = m_pOutputMax[0] * 
						(double)  (m_BaseStep - 2*m_dHomingSteps) / (double) m_dHomingSteps;

	//CONTINUE TO ROTATE SOME 45 DEGREES	
					memcpy(mysa->pvData,Value,sizeof(double)*m_NumAxes);
					pIVS->SetVector(0,mysa);
					// Destroy SafeArray
					SafeArrayDestroy(mysa);
					m_BaseStep++;
				}
				/***********************************************************/
				// Run BASE - Value[0] - through full trajectory range 
				// Increment BASE counter
				/***********************************************************/
/*				else if(m_CurrentStep == m_dHomingSteps && m_BaseStep < 4*m_dHomingSteps)
				{
					mysa = SafeArrayCreateVector(VT_R8,0,m_NumAxes);
					pIVS->GetCurrentVector(mysa);
					memcpy(Value, mysa->pvData, sizeof(double)*m_NumAxes);
					
					Value[0] = m_pOutputMax[0] * 
						(double)  (4*m_dHomingSteps - m_BaseStep ) / (double) m_dHomingSteps;

	//ROTATE BACK SAME DISTANCE MOVED IN PREVIOUS STEP	
					memcpy(mysa->pvData,Value,sizeof(double)*m_NumAxes);
					pIVS->SetVector(0,mysa);
					// Destroy SafeArray
					SafeArrayDestroy(mysa);
					m_BaseStep++;
				}
				
				/*****************************************************/
				// Finish joints 1-5 through half of the trajectory
				// Increment Joint counter
				/*****************************************************/
/*				else if(m_CurrentStep < 2*m_dHomingSteps && m_BaseStep == 4*m_dHomingSteps)
				{
					mysa = SafeArrayCreateVector(VT_R8,0,m_NumAxes);
					pIVS->GetCurrentVector(mysa);
					memcpy(Value, mysa->pvData, sizeof(double)*m_NumAxes);

					for (Index = 1; Index < m_NumAxes; Index++)
					{
						Value[Index] = m_pOutputMin[Index] * 
							((double) 2*m_dHomingSteps - (double) m_CurrentStep ) / (double) m_dHomingSteps;
					}
	//LOWER'S THE ARM, WITH ARM STRAIGHT AND IN HOME POSITION	
					memcpy(mysa->pvData,Value,sizeof(double)*m_NumAxes);
					pIVS->SetVector(0,mysa);
					// Destroy SafeArray
					SafeArrayDestroy(mysa);
					m_CurrentStep++;

				}
				/*****************************************************/
				// Finish joints 1-5 through 3/4 of trajectory
				// Increment Joint counter
				/*****************************************************/
/*				else if(m_CurrentStep < 3*m_dHomingSteps && m_BaseStep == 4*m_dHomingSteps)
				{
					mysa = SafeArrayCreateVector(VT_R8,0,m_NumAxes);
					pIVS->GetCurrentVector(mysa);
					memcpy(Value, mysa->pvData, sizeof(double)*m_NumAxes);

					for (Index = 1; Index < m_NumAxes; Index++)
					{
						Value[Index] = m_pOutputMax[Index] * 
						(double)  (m_CurrentStep - 2*m_dHomingSteps) / (double) m_dHomingSteps;
					}

	//MOVE THE ARM BACK A LITTLE BIT	
					memcpy(mysa->pvData,Value,sizeof(double)*m_NumAxes);
					pIVS->SetVector(0,mysa);
					// Destroy SafeArray
					SafeArrayDestroy(mysa);
					m_CurrentStep++;

				}
				else if(m_CurrentStep < 4*m_dHomingSteps && m_BaseStep == 4*m_dHomingSteps)
				{
					mysa = SafeArrayCreateVector(VT_R8,0,m_NumAxes);
					pIVS->GetCurrentVector(mysa);
					memcpy(Value, mysa->pvData, sizeof(double)*m_NumAxes);

					for (Index = 1; Index < m_NumAxes; Index++)
					{
						Value[Index] = m_pOutputMax[Index] * 
						(double)  (4*m_dHomingSteps - m_CurrentStep ) / (double) m_dHomingSteps;
					}
	//RETURN HOME	
					memcpy(mysa->pvData,Value,sizeof(double)*m_NumAxes);
					pIVS->SetVector(0,mysa);
					// Destroy SafeArray
					SafeArrayDestroy(mysa);
					m_CurrentStep++;
				}
				else	// Done with homing mechanism
				{
					pIVS->Release();
					m_CurrentStep = 0;
					ATLTRACE(_T("CPressureForceCharacterization::TakeMeHome() Done\n"));
					
					// Tell the state machine to which this component binds to go to next state
					// Pass a string of type BSTR to the StateMachine::Signal("") call.
					// By comparing strings the SM will know to move to the next state.
					m_Bindings->get_Pointers(SysAllocString(L"StateMachine"), &m_pIUnkStateMachine);
					if (m_pIUnkStateMachine != NULL)
						m_pIUnkStateMachine->QueryInterface(IID_IStateMachine,(void **)&pISM);
					if (pISM != NULL)
						pISM->Signal(SysAllocString(L"Go to next state"));
					pISM->Release();

					return 1;	// Tell activity to call someone else next time.

				}
			
//			}			// End of Right Arm if-else statements


			pIVS->Release();
		}

	}
*/
 return 0; 
}


//////////////////////
// Open a text file
//////////////////////
void CPressureForceCharacterization::OpenFile()
{
	USES_CONVERSION;		// Necessary to convert from BSTR to LPWSTR

	// Open the text file
	m_fp  = fopen(OLE2T(m_bstrInputFile), "r+t");
	
	if(m_fp == NULL ) 
		MessageBox(NULL, "OpenFile() Error. Please add a file for to record data!", "You forgot to insert the file location :)", MB_OK);
}

//////////////////////
// Close the text file
//////////////////////
void CPressureForceCharacterization::CloseFile()
{
	if(m_fp!=NULL)
	{
		fclose(m_fp );
		m_fp=NULL;
	}
}

////////////////////////////////////////////////
// Interface method that calls private method
////////////////////////////////////////////////
STDMETHODIMP CPressureForceCharacterization::ChangePressure(short whatjoint, double basepressure, double pressurechange, short numberofsteps) 
{
	ChangePressureX(whatjoint, basepressure, pressurechange, numberofsteps);
	return S_OK;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void ChangePressure(short whatjoint, double basepressure, double pressurechange, short numberofsteps) 
//  
// For each joint(pair of rubbertuators):						WhatJoint;
// What is the original pressure:								basePressure;
// By how much do want to change this pressure in each step:	pressurechange;
// How many steps do you want to take:							numberofsteps;
//
// This function is of most general use. It can be used to change pressure one time or a series of time. 
// Separate functions calls (each containing only one change in pressure) can be called to control the change in pressure over time.
// We can call this function (or series of calls) and then have a ForceTorque call afterwards to do the appropriate read.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CPressureForceCharacterization::ChangePressureX(short whatjoint, double basepressure, double pressurechange, short numberofsteps) 
{
	int					counter	= 0;
	SAFEARRAY			*mysa;
	IVectorSignal		*pIVS	= NULL;
	ISampIndPressure	*pISIP	= NULL;

	// Connect to binding and interface to post the pressure values
	m_Bindings->get_Pointers(SysAllocString(L"OutputPressureVector"), &m_pIUnkPressure);
	m_Bindings->get_Pointers(SysAllocString(L"SampleIndPressure"), &m_pIUnkSampleIndPressure);
	if (m_pIUnkPressure != NULL && m_pIUnkSampleIndPressure != NULL)
	{
		m_pIUnkPressure->QueryInterface(IID_IVectorSignal,(void **)&pIVS);
		m_pIUnkSampleIndPressure->QueryInterface(IID_ISampIndPressure,(void **)&pISIP);
			if(pIVS != NULL)
			{
				// Make sure no bogus data is entered for the joint, and that the base pressure is always within functional limits
				if (whatjoint >= 0 && whatjoint < NUM_AXES)
				{
					// If the joint is within legal parameters then go ahead and change the pressure for that joint
					if (basepressure >= m_pOutputMin[whatjoint] && basepressure <= m_pOutputMax[whatjoint])
					{
						if (counter < numberofsteps)
						{
							// Set the internal variable to the basepressure value
							m_pdOriginalPressure[whatjoint]		= basepressure;
							//m_pdOriginalPressure[whatjoint+1]	= basepressure;				// If you consider working with 12 pressures vs. 6

							// Change the pressure iteratively
							// In order to ensure that the pressure will be changed for each joint iteratively
							// you must loop back through the incremental statement. A for loop cannot be used, 
							// the alternative is to use a counter that increases until it reaches the limiting variable: number of steps

							basepressure = basepressure + pressurechange;
							counter++;

							// Add basepressure value to Vector Signal
							mysa = SafeArrayCreateVector(VT_R8,0,NUM_AXES);
							memcpy(mysa->pvData,m_pdOriginalPressure,sizeof(double)*NUM_AXES);
							pIVS->SetCurrentVector(mysa);

							// Call the Sampler to move the arm
							pISIP->HW_IO_6();
						}

						else
							MessageBox(NULL, "CPressureForceCharacterization::Counter is greater than the number of steps","Counter Out-of-bound", MB_OK);
					}

					else
						MessageBox(NULL, "CPressureForceCharacterization::ChangePressureX - the base pressure is out of bounds", "Pressure Out-of-bound",MB_OK);
				}

				else
					MessageBox(NULL, "CPressureForceCharacterization::ChangePressureX - Joint input is out of bounds","Joint Out-of-bound", MB_OK);

				pIVS->Release();
				pISIP->Release();
				SafeArrayDestroy(mysa);

			}			

			else
				if (pIVS != NULL && pISIP != NULL)
				{
					pIVS->Release();
					pISIP->Release();
					ATLTRACE(_T("CPressureForceCharacterization::ChangePressureX failed!"));
				}

	}
}


////////////////////////////////////////////////
// Interface method that calls private method
////////////////////////////////////////////////
STDMETHODIMP CPressureForceCharacterization::WriteDataToFile()
{
	WriteDataToFileX();
	return S_OK;
}

////////////////////////////////////////////////////////////////////////////
// WriteDataToFile()
//
// This experiment will write to file the values for the six joint pressures,
// and the torque and force values in the three cartesian axes. 
// The file will has the following header info:
//
// Name of Experiment: 	
// Date of Experiment:						
//
// And then will contain the values for each step in the pressure sequence
// P0 P1 P2 P3 P4 P5 P6 Fx Fy Fz Tx Ty Tz		
////////////////////////////////////////////////////////////////////////////
void CPressureForceCharacterization::WriteDataToFileX()
{
	int				i = 0;
	SAFEARRAY		*mysa;
	IVectorSignal	*pIVS	= NULL;

	// Get object and interface pointers for FTData
	m_Bindings->get_Pointers(SysAllocString(L"FTSensorCom"), &m_pIUnkFTSensor);
	if (m_pIUnkFTSensor != NULL)
	{
		m_pIUnkFTSensor->QueryInterface(IID_IVectorSignal,(void **)&pIVS);
		if (pIVS != NULL)
		{
			// Get FT values from Vector Signal
			mysa = SafeArrayCreateVector(VT_R8,0,NUM_AXES);
			pIVS->GetCurrentVector(mysa);
			memcpy(m_pFTBuffer,mysa->pvData,sizeof(double)*NUM_AXES);
			SafeArrayDestroy(mysa);

			// Write the six joint pressures to file
			for(i=0;i<NUM_AXES;i++)	
				fprintf(m_fp,"%.2f\t%.2f\t", m_pdOriginalPressure[i], m_pFTBuffer[i+1]);		// Print Joints P0 - Joints P6, Fx Fy Fz Tx Ty Tz
			fprintf(m_fp,"%\n");																// print newline
			
			pIVS->Release();		
		}

		else
			if (pIVS != NULL)
			{
				pIVS->Release();
				ATLTRACE(_T("CPressureForceCharacterization::WriteDataToFileX failed!"));
			}
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Test 1: straight motion
//
// The goal of this test is to move the arm in a straight motion as if pushing, starting from the home position. 
// The motion of pushing straight is obtained by incrementing the pressure in joints 2 and 3 iteratively. 
// The motion stops when the arm is in a straight position. The arm will end up tilted downwards by the end of the motion. 
// i.e.
// For this test, the pressure in both joints will be incremented in jumps of 10 units a total of 100 times. 
// Hence if the base pressure is 2000, the final pressure will be 3000.
// 
// When running in DAD, the following components will be needed: FTSensorCom, PressureForceCharacterization, PressureVS, ForceTorqueVS, Sampler, StateMachine
// Initialize the FTSensorCom, and the PressureForceCharacterization
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CPressureForceCharacterization::VerticalPush1()
{
	// Bindings
	IVectorSignal *pIVS	= NULL;
	IFTSensorCom  *pIFT = NULL;

	// Get object and interface pointers
	m_Bindings->get_Pointers(SysAllocString(L"OutputPressureVector"), &m_pIUnkPressure);
	m_Bindings->get_Pointers(SysAllocString(L"FTSensorCom"),		  &m_pIUnkFTSensor);
	if (m_pIUnkPressure != NULL && m_pIUnkFTSensor != NULL)
	{
		m_pIUnkPressure->QueryInterface(IID_IVectorSignal,(void **)&pIVS);
		m_pIUnkFTSensor->QueryInterface(IID_IFTSensorCom,(void **)&pIFT);

		if (pIVS != NULL && pIFT != NULL)
		{
			// Have 100 separate steps in which the pressure is incremented by 10
			for (int i=0; i<NUM_OF_STEPS; i++) 
			{
				// Change pressure and then write values to file
				ChangePressureX(2, 2000, 10, 1);		// Change pressure for joint 2 first
				ChangePressureX(3, 2000, 10, 1);		// Change pressure for joint 3 second
				pIFT->SampleFTData();					// Get FTData

				// Write Pressure, Force and Torque to file for all joints
				WriteDataToFileX();
			}

			pIVS->Release();
			pIFT->Release();

		}

		else
			if (pIVS != NULL && pIFT != NULL)
			{
				pIVS->Release();
				pIFT->Release();
				ATLTRACE(_T("CPressureForceCharacterization::VerticalPush1 failed!"));
				return S_OK;
			}
	}

	return S_OK;
}






// This function applies takes the arm to the home position
STDMETHODIMP CPressureForceCharacterization::GoToHomePosition()
{
	// TODO: Add your implementation code here

	return S_OK;
}
