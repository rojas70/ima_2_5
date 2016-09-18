// HomingController.cpp : Implementation of CHomingController
#include "stdafx.h"
#include "IMA2_ArmTools.h"
#include "HomingController.h"
#define NUM_AXES 6
#define MAX_PRESSURE 4000
#define MIN_PRESSURE 0
/////////////////////////////////////////////////////////////////////////////////////////////////
// CHomingController
// 
// The arm is moved through its entire joint range to find the encoder zero locations. 
// The pressure values for the motion sequence are computed by the Homer mechanism. 
// Each time the mechanism is invoked, it outputs the next pressure in the sequence. 
// When the Homer mechanism has completed its sequence (in IMA 1.0 the component 
// dispatches the agent event (-2,-2) to causes the state machine to transition to State 1.)
/////////////////////////////////////////////////////////////////////////////////////////////////


STDMETHODIMP CHomingController::get_HomingSteps(float *pVal)
{
	// TODO: Add your implementation code here
	if (pVal != NULL)
		*pVal = 4.0f*m_dHomingSteps;

	return S_OK;
}

STDMETHODIMP CHomingController::put_HomingSteps(float newVal)
{
	// TODO: Add your implementation code here
	if (newVal > 0)
		m_dHomingSteps = newVal/4.0f;
	return S_OK;
}


STDMETHODIMP CHomingController::get_OutputMinIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal != NULL)
		*pVal=m_sOutputMinIndex;

	return S_OK;
}

STDMETHODIMP CHomingController::put_OutputMinIndex(short newVal)
{
	// TODO: Add your implementation code here
	if (newVal >= 0 && newVal < NUM_AXES)
		m_sOutputMinIndex = newVal;

	return S_OK;
}

STDMETHODIMP CHomingController::get_OutputMaxIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal != NULL)
		*pVal=m_sOutputMaxIndex;

	return S_OK;
}

STDMETHODIMP CHomingController::put_OutputMaxIndex(short newVal)
{
	// TODO: Add your implementation code here
	if (newVal >= 0 && newVal < NUM_AXES)
		m_sOutputMaxIndex = newVal;
	return S_OK;
}

STDMETHODIMP CHomingController::get_OutputMin(double *pVal)
{
	// TODO: Add your implementation code here

	if (pVal != NULL)
		*pVal = m_pOutputMin[m_sOutputMinIndex];
	return S_OK;
}

STDMETHODIMP CHomingController::put_OutputMin(double newVal)
{
	// TODO: Add your implementation code here
	if (m_sOutputMinIndex < NUM_AXES)
		m_pOutputMin[m_sOutputMinIndex] = newVal;
	return S_OK;
}

STDMETHODIMP CHomingController::get_OutputMax(double *pVal)
{
	// TODO: Add your implementation code here
	if (m_sOutputMaxIndex >= 0 && m_sOutputMaxIndex < NUM_AXES)
		*pVal = m_pOutputMax[m_sOutputMaxIndex];
	return S_OK;
}

STDMETHODIMP CHomingController::put_OutputMax(double newVal)
{
	// TODO: Add your implementation code here
	if (m_sOutputMaxIndex < NUM_AXES)
		m_pOutputMax[m_sOutputMaxIndex] = newVal;
	return S_OK;
}

STDMETHODIMP CHomingController::Initial()
{
	// TODO: Add your implementation code here
	m_CurrentStep	= 0;	// Reset the homing steps
	m_BaseStep		= 0;

	return S_OK;
}

STDMETHODIMP CHomingController::get_LeftArm(short *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_LeftArm;
	return S_OK;
}

STDMETHODIMP CHomingController::put_LeftArm(short newVal)
{
	// TODO: Add your implementation code here
	m_LeftArm = newVal;

	// This value could be used to change the sequence for the homing controller for the left arm.
	// This has not been done yet, but one can see the homing sequence seen in the right arm for 
	// the left arm as well.

	// Juan Rojas. Feb 06
	return S_OK;
}


STDMETHODIMP CHomingController::OnConstruct() {

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

	// Deallocate storage
	SysFreeString(BindInf.Name);
	SysFreeString(BindInf.Path);
	SafeArrayDestroy(BindInf.PIDs);
	SafeArrayDestroy(BindInf.IIDs);
	
	return S_OK;
}

STDMETHODIMP CHomingController::OnDestruct() {	return S_OK; }

//////////////////////////////
// Load values of saved data
//////////////////////////////
STDMETHODIMP CHomingController::Load(VARIANT Data) {
	
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

		// Decrement the pointer reference count from our member variable. 
		VariantClear(&m_VBPropertyBag);
		
		// Release
		pIPB->Release();

	return S_OK;

}

STDMETHODIMP CHomingController::Save(VARIANT * pData)
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

//////////////////////////////////////////////////////////////////////////////////////
// The arm is moved through its entire joint range to find the encoder zero locations. 
// To learn more about encoders and zero locations go to: O:\System\Tools\Encoder
//
// The pressure values for the motion sequence are computed by the Homer mechanism. 
// Each time the mechanism is invoked, it outputs the next pressure in the sequence.
// 
// 2007:
// A new set of servo valves has been installed and safety requires us to limit the 
// range motion of the first joint in both arms. Instead of incrementing the pressure to
// 4000 psi, we will only do it to 3000psi. 
//
// Note: Steps were taken to ensure that the zero location of the encoder is still reached.
// !!!!!! 2008: Since new valves were installed, air leakage was detected from old valves.
//		        triceps were disabled and so the homing routine will not work as originally 
//				programmed!!!!!!! The IMA2_NNet_PID program shows a new homing routine.
//
// In Ima 1.0, the call was designed to call AgentDispatchEvent(-2,-2) to causes the 
// state machine to O transition to State 1.)
///////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CHomingController::ComputeHomingPressures()
{	
	// Variables
	SAFEARRAY *mysa;
	long Index,VIndex = 0;
	double Value[NUM_AXES];

	// Bindings
	IVectorSignal *pIVS	= NULL;
	IStateMachine *pISM = NULL;

	// Get object and interface pointers
	m_Bindings->get_Pointers(SysAllocString(L"OutputPressureVector"), &m_pIUnkOutput);
	if (m_pIUnkOutput != NULL)
	{
		m_pIUnkOutput->QueryInterface(IID_IVectorSignal,(void **)&pIVS);
		if (pIVS != NULL)
		{
			/******************************************************************************/
			// Run BASE (joint 0) and Joints 1-5 through first quarter of trajectory range
			// Increase counter for base:	m_BaseStep++
			// Increase counter for joints: m_CurrentStep++
			// Total trajectory =			4*m_dHomingSteps
			//
			// The different portions of code below normalize the output pressure
			// based on what part of the trajectory is being considered for the BASE and 
			// for the Joints 1-5 based out of OutputMax and OutputMin
			// These pressures are then sent to the Pressure Vector Signal which are used by the
			// SampIndPressure.HW_IO functions to apply to the ServoValves.
			// Juan Rojas. Nov 2005. 
			/******************************************************************************/

			// This sort of counter is useful to: (1) Distinguish each of the different sections of the arm motion
			// without having to revisit them when the function is called again, and (2) it allows us to use them
			// to change the pressure at the same time.
			if(m_CurrentStep < m_dHomingSteps && m_BaseStep < m_dHomingSteps)		// Homing steps is IMA value: 200 divided by 4 = 50 in general
				{
					// Get output pressure vector
					mysa = SafeArrayCreateVector(VT_R8,0,m_NumAxes);
					pIVS->GetCurrentVector(mysa);
					memcpy(Value, mysa->pvData, sizeof(double)*m_NumAxes);			// Retrieve the current value of the pressure, to be modified later

					for (Index = 0; Index < m_NumAxes; Index++)
						Value[Index] = m_pOutputMin[Index] * (double) m_CurrentStep  / (double) m_dHomingSteps;		// Value ranges from 0 to -2000. I.e. -2000 * n/50


	// MOVE UP AND RIGHT TOWARDS THE BACK	
					// Set the output pressure vector
 					memcpy(mysa->pvData,Value,sizeof(double)*m_NumAxes);
					// We use a harcoded index 0 to try to replicate behavior in IMA 1 to set the pressure
					pIVS->SetVector(0,mysa);										// Update the pressure VS
					// Destroy SafeArray
					SafeArrayDestroy(mysa);

					// Increment the step
					m_CurrentStep++;
					m_BaseStep++;
				}
				
				// First compute the base value (3 choices) and then the rest of the joints
				/**********************************************************************************************************************/
				// Run BASE through full range: arm rotates from right to left
				// Value[0] - Increment BASE counter
				/**********************************************************************************************************************/
				else if(m_CurrentStep == m_dHomingSteps && m_BaseStep < 2*m_dHomingSteps)  // IF CurrentStep=200 AND BaseStep goes 200-400
				{
					mysa = SafeArrayCreateVector(VT_R8,0,m_NumAxes);
					pIVS->GetCurrentVector(mysa);
					memcpy(Value, mysa->pvData, sizeof(double)*m_NumAxes);

					Value[0] = m_pOutputMin[0] * 
						((double) 2*m_dHomingSteps - (double) m_BaseStep ) / (double) m_dHomingSteps;			// Value ranges from -2000 to 0

	//ROTATE IN AROUND THE BASE 90 DEGREES	
					memcpy(mysa->pvData,Value,sizeof(double)*m_NumAxes);
					pIVS->SetVector(0,mysa);
					// Destroy SafeArray
					SafeArrayDestroy(mysa);
					m_BaseStep++;
				}
				/**********************************************************************************************************************/
				// Run BASE - Value[0] - through 3/4 of trajectory range 
				// Increment BASE counter
				/**********************************************************************************************************************/
				else if(m_CurrentStep == m_dHomingSteps && m_BaseStep < 3*m_dHomingSteps)
				{
					mysa = SafeArrayCreateVector(VT_R8,0,m_NumAxes);
					pIVS->GetCurrentVector(mysa);
					memcpy(Value, mysa->pvData, sizeof(double)*m_NumAxes);
					
					Value[0] = m_pOutputMax[0] * 
						(double)  (m_BaseStep - 2*m_dHomingSteps) / (double) m_dHomingSteps;				// Values range from 0 to 2000

	//CONTINUE TO ROTATE SOME 45 DEGREES	
					memcpy(mysa->pvData,Value,sizeof(double)*m_NumAxes);
					pIVS->SetVector(0,mysa);
					// Destroy SafeArray
					SafeArrayDestroy(mysa);
					m_BaseStep++;
				}
				/**********************************************************************************************************************/
				// Run BASE - Value[0] - through full trajectory range 
				// Increment BASE counter
				/**********************************************************************************************************************/
				else if(m_CurrentStep == m_dHomingSteps && m_BaseStep < 4*m_dHomingSteps)
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
				
				/****************************************************************************************************************/
				// Finish joints 1-5 through half of the trajectory
				// Increment Joint counter
				/****************************************************************************************************************/
				else if(m_CurrentStep < 2*m_dHomingSteps && m_BaseStep == 4*m_dHomingSteps)
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
				/****************************************************************************************************************/
				// Finish joints 1-5 through 3/4 of trajectory
				// Increment Joint counter
				/****************************************************************************************************************/
				else if(m_CurrentStep < 3*m_dHomingSteps && m_BaseStep == 4*m_dHomingSteps)
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
					/************************************************************************************************************************/
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
					ATLTRACE(_T("CHomingController::TakeMeHome() Done\n"));
					
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

 return 0; 
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Input: 
// Output: Pressures
//
// Function: The goal of this function is to move the arm throughout its dexterous workspace.
// The dexterous workspace is typically described as the workspace in which the tool or end-effector
// can reach appropriately. 
//
// We will move the arm by reaching maximum positions at some joints.
// This function is used in the RightArm Agent and in conjuction with Forward Kinematics and a 
// VS2File component to write the cartesian coordinates to a file for later analysis.
// Look at RightArm agent found under O:\Agents\TestAgents\Characterization of the RightArm Workspace\RightArm.cmp
////////////////////////////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CHomingController::MoveThroughDexterousWorkspace()
{
	// Variables
	double			PressureOutput[2*NUM_AXES];
	SAFEARRAY		*mysa;
	IVectorSignal	*pIPressure	= NULL;
	IStateMachine	*pISM		= NULL;

	// Get object and interface pointers to the Pressure VS and to the State Machine
	m_Bindings->get_Pointers(SysAllocString(L"OutputPressureVector"), &m_pIUnkOutput);
	m_Bindings->get_Pointers(SysAllocString(L"StateMachine"), &m_pIUnkStateMachine);						

	if (m_pIUnkOutput != NULL && m_pIUnkStateMachine != NULL)
	{
		m_pIUnkOutput->QueryInterface(IID_IVectorSignal,(void **)&pIPressure);			// Pressure VS
		m_pIUnkStateMachine->QueryInterface(IID_IStateMachine,(void **)&pISM);			// State Machine VS
		if (pIPressure != NULL)
		{
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// RightArm Motion: Complete Definition of its workspace based on maximum and minimum physical limitations
			// The arm motion that will examine the limitations is composed of 4 stages. These 4 stages can be applied at
			// different y points (horizontal points) to get a mapping of the whole space.
			// Stage 1: The arm is moved back as far as possible and the bicep is curled.
			// Stage 2: The arm is moved forward and up as far as possible.
			// Stage 3: The arm is extended 
			// Stage 4: The arm is moved down and back as far as possible.
			// Stage 5: The arm is curled to get to the original position.
			// We will do this at three points: at negative Y, at zero Y and at positive Y.
			// 
			// To get the routine ready we proceed as follows:
			// (0) Rotate the arm back:	Pressures [0,1] - this will move the shoulder towards the back
			// (1) Inflate the forearm:	Pressures [8,11]- this is to hold the end-effector in position
			// (2) Rotate the shoulder:	Pressures [2,3] - the shoulder is rotated back as far as possible
			// (3) Curl the bicep:		Pressures [5,6] - arm will be pushed back and curled at this point
			/****  The first four steps are required before recording the kinematics. ****/
			// (4) Rotate the shoulder: Pressures [2,3] - rotate the shoulder forward to the max
			// (5) Extend the arm:		Pressures [4,7] - achieve an extended arm, inflate triceps and deflate biceps
			// (6) Rotate the shoulder: Pressures [2,3] - rotate the shoulder backwards to the max
			// (7) Curl the biceps:		Pressures [5,6[ - curl the biceps back to the original position
			/****  5 stages completed.
			// Do again with y now at origin, and then again with a positive y.*/
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// Stage 0: Rotate base towards the back. Pressures[0-1]	
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if(m_stage == 0)																// First if, in a series of if, else if, else statements
			{
				// Get output pressure vector
				mysa = SafeArrayCreateVector(VT_R8,0,2*NUM_AXES);
				pIPressure->GetCurrentVector(mysa);
				memcpy(PressureOutput, mysa->pvData, sizeof(double)*2*NUM_AXES);			// Retrieve the current value of the pressure, to be modified later

				// The rate of inflation determined here was done empirically and reflects an angle of approx. 45deg with the x-axis (coming out of ISAC)
				PressureOutput[0] = PressureOutput[0] + m_delta_pressure; 
				PressureOutput[1] = PressureOutput[1] + m_delta_pressure/2; 
				m_counter = (int)PressureOutput[0];											// Will act as a flag, so that when it is eqaul to MAX_PRESSURE we can move on

				// Set the output pressure vector
 				memcpy(mysa->pvData,PressureOutput,sizeof(double)*2*NUM_AXES);
				// Set the Pressure VectorSignal with the update value
				pIPressure->SetVector(0,mysa);
				// Destroy SafeArray
				SafeArrayDestroy(mysa);

				// Check to change flag when stage is completed
				if (m_counter == MAX_PRESSURE)
					m_stage = 1;
			}
			
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// Stage 1. Inflate the forearm to keep the end effector in the right position.
			// Pressure[8,11]=0, Pressure[9,10]=4000
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if(m_stage == 1)																
			{
				// Get output pressure vector
				mysa = SafeArrayCreateVector(VT_R8,0,2*NUM_AXES);
				pIPressure->GetCurrentVector(mysa);
				memcpy(PressureOutput, mysa->pvData, sizeof(double)*2*NUM_AXES);			

				PressureOutput[9]  = PressureOutput[9]  + m_delta_pressure; 
				PressureOutput[10] = PressureOutput[10] + m_delta_pressure; 
				m_counter = (int)PressureOutput[10];										

				// Set the output pressure vector
 				memcpy(mysa->pvData,PressureOutput,sizeof(double)*2*NUM_AXES);
				// Set the Pressure VectorSignal with the update value
				pIPressure->SetVector(0,mysa);
				// Destroy SafeArray
				SafeArrayDestroy(mysa);

				// Check to change flag when stage is completed
				if (m_counter == MAX_PRESSURE)
					m_stage = 2;
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// Stage 2: Rotate the shoulder to the back. Pressures [2,3]
			// Inflate Pressure[2] to the max
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if(m_stage == 2)															
			{
				// Get output pressure vector
				mysa = SafeArrayCreateVector(VT_R8,0,2*NUM_AXES);
				pIPressure->GetCurrentVector(mysa);
				memcpy(PressureOutput, mysa->pvData, sizeof(double)*2*NUM_AXES);		

				PressureOutput[2]  = PressureOutput[2] + m_delta_pressure;
				m_counter = (int)PressureOutput[2];

				// Set the output pressure vector
 				memcpy(mysa->pvData,PressureOutput,sizeof(double)*2*NUM_AXES);
				// Set the Pressure VectorSignal with the update value
				pIPressure->SetVector(0,mysa);
				// Destroy SafeArray
				SafeArrayDestroy(mysa);

				// Check to change flag when stage is completed
				if (m_counter == MAX_PRESSURE)							
					m_stage = 3;
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// Stage 3: Curl the bicep Pressures[5,6].
			// Inflate the bicep muscles to achieve a limit on how far back the tool can go.
			// This finalizes getting the initialization routine, and from here we will start writing the cartesian coordinates of the 
			// wrist.
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if(m_stage == 3)										
			{

				// Get output pressure vector
				mysa = SafeArrayCreateVector(VT_R8,0,2*NUM_AXES);
				pIPressure->GetCurrentVector(mysa);
				memcpy(PressureOutput, mysa->pvData, sizeof(double)*2*NUM_AXES);			

				PressureOutput[5]  = PressureOutput[5] + m_delta_pressure;
				PressureOutput[6]  = PressureOutput[6] + m_delta_pressure;
				m_counter = (int)PressureOutput[6];

				// Set the output pressure vector
 				memcpy(mysa->pvData,PressureOutput,sizeof(double)*2*NUM_AXES);
				// Set the Pressure VectorSignal with the update value
				pIPressure->SetVector(0,mysa);
				// Destroy SafeArray
				SafeArrayDestroy(mysa);

				// Check to change flag when stage is completed
				if (m_counter == MAX_PRESSURE)	
				{
					m_stage = 4;
					// Send a signal to the state machine to move to the "Next" state
					if (pISM != NULL)
						pISM->Signal(SysAllocString(L"Next"));
					pISM->Release();
				}
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// Stage 4: Rotate the shoulder up as far as possible. Pressure[3]
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if(m_stage == 4)										
			{

				// Get output pressure vector
				mysa = SafeArrayCreateVector(VT_R8,0,2*NUM_AXES);
				pIPressure->GetCurrentVector(mysa);
				memcpy(PressureOutput, mysa->pvData, sizeof(double)*2*NUM_AXES);		

				PressureOutput[3] = PressureOutput[3] + m_delta_pressure;
				PressureOutput[2] = PressureOutput[2] - m_delta_pressure;			
				m_counter = (int)PressureOutput[3];

				// Set the output pressure vector
 				memcpy(mysa->pvData,PressureOutput,sizeof(double)*2*NUM_AXES);
				// Set the Pressure VectorSignal with the update value
				pIPressure->SetVector(0,mysa);
				// Destroy SafeArray
				SafeArrayDestroy(mysa);

				// Check to change flag when stage is completed
				if (m_counter == MAX_PRESSURE)							
					m_stage = 5;
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////			
			// Stage 5: Extend the arm. Pressures[4-7]
			// Increase pressures[4,7] (triceps) to 1000, and decrease 5,6 to zero (biceps).
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if(m_stage == 5)										
			{
				// Get output pressure vector
				mysa = SafeArrayCreateVector(VT_R8,0,2*NUM_AXES);
				pIPressure->GetCurrentVector(mysa);
				memcpy(PressureOutput, mysa->pvData, sizeof(double)*2*NUM_AXES);			

				PressureOutput[4]  = PressureOutput[4] + m_delta_pressure/4;		// Extend triceps up to 1bar
				PressureOutput[7]  = PressureOutput[7] + m_delta_pressure/4; 
				PressureOutput[5]  = PressureOutput[5] - m_delta_pressure;			// Deflate biceps to 0bar
				PressureOutput[6]  = PressureOutput[6] - m_delta_pressure; 
				m_counter = (int)PressureOutput[6];									// Use as flag, when it reaches 0.

				// Set the output pressure vector
 				memcpy(mysa->pvData,PressureOutput,sizeof(double)*2*NUM_AXES);
				// Set the Pressure VectorSignal with the update value
				pIPressure->SetVector(0,mysa);
				// Destroy SafeArray
				SafeArrayDestroy(mysa);

				// Check to change flag when stage is completed
				if (m_counter == MIN_PRESSURE)							
					m_stage = 6;
			}
			
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// Stage 6: Rotate shoulder down and back as far as possible. Pressures[2,3]	
			// We want to increment Pressure[2] to the max, and reduce Pressure[3] to zero
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if(m_stage == 6)										
			{
				// Get output pressure vector
				mysa = SafeArrayCreateVector(VT_R8,0,2*NUM_AXES);
				pIPressure->GetCurrentVector(mysa);
				memcpy(PressureOutput, mysa->pvData, sizeof(double)*2*NUM_AXES);			

				// Deflate pressure 3 and increment 2.
				PressureOutput[3]  = PressureOutput[3] - m_delta_pressure;
				PressureOutput[2]  = PressureOutput[2] + m_delta_pressure;
				m_counter = (int)PressureOutput[2];

				// Set the output pressure vector
 				memcpy(mysa->pvData,PressureOutput,sizeof(double)*2*NUM_AXES);
				// Set the Pressure VectorSignal with the update value
				pIPressure->SetVector(0,mysa);
				// Destroy SafeArray
				SafeArrayDestroy(mysa);

				// Check to change flag when stage is completed
				if (m_counter == MAX_PRESSURE)							
					m_stage = 7;
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// Stage 7: Curl the bicep. Pressures[4-7]	
			// Return to curl posiiton
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if(m_stage == 7)										
			{
				// Get output pressure vector
				mysa = SafeArrayCreateVector(VT_R8,0,2*NUM_AXES);
				pIPressure->GetCurrentVector(mysa);
				memcpy(PressureOutput, mysa->pvData, sizeof(double)*2*NUM_AXES);			

				PressureOutput[5]  = PressureOutput[5] + m_delta_pressure;			// Curl the bicep
				PressureOutput[6]  = PressureOutput[6] + m_delta_pressure; 
				PressureOutput[4]  = PressureOutput[4] - m_delta_pressure/4;		// Decrease pressure in tricep
				PressureOutput[7]  = PressureOutput[7] - m_delta_pressure/4; 
				m_counter = (int)PressureOutput[6];

				// Set the output pressure vector
 				memcpy(mysa->pvData,PressureOutput,sizeof(double)*2*NUM_AXES);
				// Set the Pressure VectorSignal with the update value
				pIPressure->SetVector(0,mysa);
				// Destroy SafeArray
				SafeArrayDestroy(mysa);

				// Check to change flag when stage is completed
				if (m_counter == MAX_PRESSURE)				
					m_stage = 4;

				// This section could have been organized better, but we are going to rotate the base at this point.
				// We will rotate half-way to the other end, and then finally till the max of the other side.

				// This statement is only used when we have gone through two passes of the if statement below. 
				// This statement is necessary  to reset the pressure in the arms, once the final stage has been reached.
				if (y_axis_counter == 4 && m_counter == MAX_PRESSURE)
					m_stage = 8;


				if (m_counter == MAX_PRESSURE && y_axis_counter < 4)
				{
					PressureOutput[0] = PressureOutput[0] - 1000;		// Assuming 4 passes (i.e. 4k-3k-2k-1k-0)
					PressureOutput[1] = PressureOutput[1] +  500;		// Assuming 4 passes (i.e. 2k-2.5k-3k-3.5k-4k)
					// Update the pressure vector
					mysa = SafeArrayCreateVector(VT_R8,0,2*NUM_AXES);
	 				memcpy(mysa->pvData,PressureOutput,sizeof(double)*2*NUM_AXES);
					pIPressure->SetVector(0,mysa);
					SafeArrayDestroy(mysa);	
					// Update the counter
					y_axis_counter++;									// Initialize it at 0.
				}

			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// Stage 8: Reset all the pressures
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (m_stage == 8)
			{
				for(int i = 0; i < 2*NUM_AXES; i++)
					PressureOutput[i] = 0.0;

				// Create the SafeArray
				mysa = SafeArrayCreateVector(VT_R8,0,2*NUM_AXES);
				// Set the output pressure vector
 				memcpy(mysa->pvData,PressureOutput,sizeof(double)*2*NUM_AXES);
				// Set the Pressure VectorSignal with the update value
				pIPressure->SetVector(0,mysa);
				// Destroy SafeArray
				SafeArrayDestroy(mysa);

				// Disacciate with any stage
				m_stage = -1;

				// Send a signal to the state machine to Stop
				if (pISM != NULL)
					pISM->Signal(SysAllocString(L"Stop"));
				pISM->Release();

				// Send note to the debug dump
				ATLTRACE(_T("\nMoveArmThroughWorkSpace(): Routine ended effectively"));
			}
			
			else												// None of the conditions were met. There is something wrong!
			{
				// Send note to the debug dump
				ATLTRACE(_T("\nMoveArmThroughWorkSpace(): None of the conditions were met. Something went wrong!"));
				return !S_OK;
			}

		}														// Finish the connection to the object's interface
		
		else
			if (pIPressure != NULL && pISM != NULL)
			{
				pIPressure->Release();
				pISM->Release();
			}
	}

	return S_OK;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Input: 
// Output: Pressures
//
// Function: The goal of this function is to move the arm throughout its dexterous workspace.
// The dexterous workspace is typically described as the workspace in which the tool or end-effector
// can reach appropriately. 
//
// We will move the arm by reaching maximum positions at some joints.
// This function is used in the RightArm Agent and in conjuction with Forward Kinematics and a 
// VS2File component to write the cartesian coordinates to a file for later analysis.
// Look at RightArm agent found under O:\Agents\TestAgents\Characterization of the RightArm Workspace\RightArm.cmp

STDMETHODIMP CHomingController::MoveRightArmUpperQuadrant()
{
	// Variables
	double			PressureOutput[2*NUM_AXES];
	SAFEARRAY		*mysa;
	IVectorSignal	*pIPressure	= NULL;
	IStateMachine	*pISM		= NULL;

	// Get object and interface pointers to the Pressure VS and to the State Machine
	m_Bindings->get_Pointers(SysAllocString(L"OutputPressureVector"), &m_pIUnkOutput);
	m_Bindings->get_Pointers(SysAllocString(L"StateMachine"), &m_pIUnkStateMachine);						

	if (m_pIUnkOutput != NULL && m_pIUnkStateMachine != NULL)
	{
		m_pIUnkOutput->QueryInterface(IID_IVectorSignal,(void **)&pIPressure);			// Pressure VS
		m_pIUnkStateMachine->QueryInterface(IID_IStateMachine,(void **)&pISM);			// State Machine VS
		if (pIPressure != NULL)
		{
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// RightArm Motion: Upper Quadrant
			// Total Number of Stages: 9
			// The arm will rotate around back, extended, shoulder will rotate, bicep contracted, and shoulder rotated again, bicep extended.
			/****  Initialization Steps - to get the arm in position before recording kinematics ****/
			// (0) Rotate the base    : Pressures[0,1]  - this will move the shoulder towards the back
			// (1) Inflate the forearm: Pressures[8-11]	- this is to hold the end-effector in position
			// (2) Inflate the triceps: Pressures[4-7]	- harden the triceps to ensure arm extension
			// (3) Lift arm:			Pressuers[2-3]	- raise the arm to the max
			/****  The first four steps are required before recording the kinematics. ****/
			// (4) Rotate shoulder:		Pressures[0-1]	- rotate shoulder towards the inside
			// (5) Curl bicep:			Pressures[4-7]	- curl biceps in order to study upper limit for workspace
			// (6) Rotate shoulder:		Pressures[0-1]	- return shoulder to the origin
			// (7) Extend bicep:		Pressures[4-7]	- return to the extended arm positionto finish the quadrant
			// (8) Reset all pressures
			//*********************************
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// Stage 0: Rotate base towards the back. Pressures[0-1]	
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if(m_stage == 0)																// First if, in a series of if, else if, else statements
			{
				// Get output pressure vector
				mysa = SafeArrayCreateVector(VT_R8,0,2*NUM_AXES);
				pIPressure->GetCurrentVector(mysa);
				memcpy(PressureOutput, mysa->pvData, sizeof(double)*2*NUM_AXES);			// Retrieve the current value of the pressure, to be modified later

				// The rate of inflation determined here was done empirically and reflects an angle of approx. 45deg with the x-axis (coming out of ISAC)
				PressureOutput[0] = PressureOutput[0] + m_delta_pressure; 
				PressureOutput[1] = PressureOutput[1] + m_delta_pressure/2; 
				m_counter = (int)PressureOutput[0];											// Will act as a flag, so that when it is eqaul to MAX_PRESSURE we can move on

				// Set the output pressure vector
 				memcpy(mysa->pvData,PressureOutput,sizeof(double)*2*NUM_AXES);
				// Set the Pressure VectorSignal with the update value
				pIPressure->SetVector(0,mysa);
				// Destroy SafeArray
				SafeArrayDestroy(mysa);

				// Check to change flag when stage is completed
				if (m_counter == MAX_PRESSURE)
					m_stage = 1;
			}
			
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// Stage 1. Inflate the forearm to keep the end effector in the right position.
			// Pressure[8,11]=0, Pressure[9,10]=4000
			// Inflate in increments of 100
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if(m_stage == 1)																
			{
				// Get output pressure vector
				mysa = SafeArrayCreateVector(VT_R8,0,2*NUM_AXES);
				pIPressure->GetCurrentVector(mysa);
				memcpy(PressureOutput, mysa->pvData, sizeof(double)*2*NUM_AXES);			

				PressureOutput[9]  = PressureOutput[9]  + m_delta_pressure; 
				PressureOutput[10] = PressureOutput[10] + m_delta_pressure; 
				m_counter = (int)PressureOutput[10];										

				// Set the output pressure vector
 				memcpy(mysa->pvData,PressureOutput,sizeof(double)*2*NUM_AXES);
				// Set the Pressure VectorSignal with the update value
				pIPressure->SetVector(0,mysa);
				// Destroy SafeArray
				SafeArrayDestroy(mysa);

				// Check to change flag when stage is completed
				if (m_counter == MAX_PRESSURE)
					m_stage = 2;
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// Stage 2: Inflate triceps to 1000. Pressures[4,7]. 
			// Inflating to 1 bar is enough to achieve arm extension for the larger tricep muscles on the right arm.
			// PressureOutput[9,10] stay at MAX capacity
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if(m_stage == 2)															
			{
				// Get output pressure vector
				mysa = SafeArrayCreateVector(VT_R8,0,2*NUM_AXES);
				pIPressure->GetCurrentVector(mysa);
				memcpy(PressureOutput, mysa->pvData, sizeof(double)*2*NUM_AXES);			

				PressureOutput[4]  = PressureOutput[4] + m_delta_pressure;
				PressureOutput[7]  = PressureOutput[7] + m_delta_pressure;
				m_counter = (int)PressureOutput[7];

				// Set the output pressure vector
 				memcpy(mysa->pvData,PressureOutput,sizeof(double)*2*NUM_AXES);
				// Set the Pressure VectorSignal with the update value
				pIPressure->SetVector(0,mysa);
				// Destroy SafeArray
				SafeArrayDestroy(mysa);

				// Check to change flag when stage is completed
				if (m_counter == MAX_PRESSURE / 4)							// We are just looking to inflate to 1bar
					m_stage = 3;
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// Stage 3: Lift arm. Pressure[3]	
			// We will raise the shoulder to the max
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if(m_stage == 3)										
			{
				// Get output pressure vector
				mysa = SafeArrayCreateVector(VT_R8,0,2*NUM_AXES);
				pIPressure->GetCurrentVector(mysa);
				memcpy(PressureOutput, mysa->pvData, sizeof(double)*2*NUM_AXES);		

				PressureOutput[3]  = PressureOutput[3] + m_delta_pressure;
				m_counter = (int)PressureOutput[3];

				// Set the output pressure vector
 				memcpy(mysa->pvData,PressureOutput,sizeof(double)*2*NUM_AXES);
				// Set the Pressure VectorSignal with the update value
				pIPressure->SetVector(0,mysa);
				// Destroy SafeArray
				SafeArrayDestroy(mysa);

				// Check to change flag when stage is completed
				if (m_counter == MAX_PRESSURE)	
				{
					m_stage = 4;
					// Send a signal to the state machine to move to the "Next" state
					if (pISM != NULL)
						pISM->Signal(SysAllocString(L"Next"));
					pISM->Release();
				}
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// Stage 4: Rotate shoulder. Pressures[1]	
			// Rotate shoulder towards the inside to the max.
			// We have ignored the rotation of the arm in the opposite direction (towards the back of the robot) b/c 
			// we don't think the vision will ever have to look back there.
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if(m_stage == 4)										
			{
				// Get output pressure vector
				mysa = SafeArrayCreateVector(VT_R8,0,2*NUM_AXES);
				pIPressure->GetCurrentVector(mysa);
				memcpy(PressureOutput, mysa->pvData, sizeof(double)*2*NUM_AXES);

				PressureOutput[0] = PressureOutput[0] - m_delta_pressure;		// Deflate the back muscle
				PressureOutput[1] = PressureOutput[1] + m_delta_pressure/2;		// Inflate the pending half of the muscle (look at stage 0)
				m_counter = (int)PressureOutput[1];

				// Set the output pressure vector
 				memcpy(mysa->pvData,PressureOutput,sizeof(double)*2*NUM_AXES);
				// Set the Pressure VectorSignal with the update value
				pIPressure->SetVector(0,mysa);
				// Destroy SafeArray
				SafeArrayDestroy(mysa);

				// Check to change flag when stage is completed
				if (m_counter == MAX_PRESSURE)							
					m_stage = 5;
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////			
			// Stage 5: Curl bicep. Pressures[5,6]	(Biceps should be able to curl in spite having the triceps inflated to 1bar)
			// Curl biceps to the max in order to study upper limit for workspace
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if(m_stage == 5)										
			{
				// Get output pressure vector
				mysa = SafeArrayCreateVector(VT_R8,0,2*NUM_AXES);
				pIPressure->GetCurrentVector(mysa);
				memcpy(PressureOutput, mysa->pvData, sizeof(double)*2*NUM_AXES);			

				PressureOutput[5]  = PressureOutput[5] + m_delta_pressure;
				PressureOutput[6]  = PressureOutput[6] + m_delta_pressure; 
				m_counter = (int)PressureOutput[6];

				// Set the output pressure vector
 				memcpy(mysa->pvData,PressureOutput,sizeof(double)*2*NUM_AXES);
				// Set the Pressure VectorSignal with the update value
				pIPressure->SetVector(0,mysa);
				// Destroy SafeArray
				SafeArrayDestroy(mysa);

				// Check to change flag when stage is completed
				if (m_counter == MAX_PRESSURE)							
					m_stage = 6;
			}
			
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// Stage 6:Rotate shoulder. Pressures[0-1]	
			// Return shoulder to the origin
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if(m_stage == 6)										
			{
				// Get output pressure vector
				mysa = SafeArrayCreateVector(VT_R8,0,2*NUM_AXES);
				pIPressure->GetCurrentVector(mysa);
				memcpy(PressureOutput, mysa->pvData, sizeof(double)*2*NUM_AXES);			

				// Deflate index 1 (half-way see stage 0) to move to the origin, but also inflate the other muscle to rotate around the back
				PressureOutput[1]  = PressureOutput[1] - m_delta_pressure/2;
				PressureOutput[0]  = PressureOutput[0] + m_delta_pressure;
				m_counter = (int)PressureOutput[0];

				// Set the output pressure vector
 				memcpy(mysa->pvData,PressureOutput,sizeof(double)*2*NUM_AXES);
				// Set the Pressure VectorSignal with the update value
				pIPressure->SetVector(0,mysa);
				// Destroy SafeArray
				SafeArrayDestroy(mysa);

				// Check to change flag when stage is completed
				if (m_counter == MAX_PRESSURE)							
					m_stage = 7;
			}
			
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// Stage 7: Extend bicep. Pressures[4-7]	
			// Return to the extended arm position to finish the quadrant
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if(m_stage == 7)										
			{
				// Get output pressure vector
				mysa = SafeArrayCreateVector(VT_R8,0,2*NUM_AXES);
				pIPressure->GetCurrentVector(mysa);
				memcpy(PressureOutput, mysa->pvData, sizeof(double)*2*NUM_AXES);			

				PressureOutput[5]  = PressureOutput[5] - m_delta_pressure;
				PressureOutput[6]  = PressureOutput[6] - m_delta_pressure; 
				m_counter = (int)PressureOutput[6];

				// Set the output pressure vector
 				memcpy(mysa->pvData,PressureOutput,sizeof(double)*2*NUM_AXES);
				// Set the Pressure VectorSignal with the update value
				pIPressure->SetVector(0,mysa);
				// Destroy SafeArray
				SafeArrayDestroy(mysa);

				// Check to change flag when stage is completed
				if (m_counter == MIN_PRESSURE)				
				{
					m_stage = 8;								// Exit

					// Tell the state machine to move to the next state in order to stop recording XYZ coordinates
					if (pISM != NULL)
						pISM->Signal(SysAllocString(L"Last"));
					pISM->Release();
				}

			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// Stage 8: Reset all the pressures
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (m_stage == 8)
			{
				for(int i = 0; i < 2*NUM_AXES; i++)
					PressureOutput[i] = 0.0;

				// Create the SafeArray
				mysa = SafeArrayCreateVector(VT_R8,0,2*NUM_AXES);
				// Set the output pressure vector
 				memcpy(mysa->pvData,PressureOutput,sizeof(double)*2*NUM_AXES);
				// Set the Pressure VectorSignal with the update value
				pIPressure->SetVector(0,mysa);
				// Destroy SafeArray
				SafeArrayDestroy(mysa);

				// Disacciate with any stage
				m_stage = -1;

				// Send note to the debug dump
				ATLTRACE(_T("\nMoveArmThroughWorkSpace(): Routine ended effectively"));
			}
			
			else												// None of the conditions were met. There is something wrong!
			{
				// Send note to the debug dump
				ATLTRACE(_T("\nMoveArmThroughWorkSpace(): None of the conditions were met. Something went wrong!"));
				return !S_OK;
			}

		}														// Finish the connection to the object's interface
		
		else
			if (pIPressure != NULL && pISM != NULL)
			{
				pIPressure->Release();
				pISM->Release();
			}
	}

	return S_OK;
}
