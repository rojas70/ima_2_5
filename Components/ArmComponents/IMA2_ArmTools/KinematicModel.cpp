// KinematicModel.cpp : Implementation of CKinematicModel
#include "stdafx.h"
#include "IMA2_ArmTools.h"
#include "KinematicModel.h"
#include "O:\Components\ArmComponents\KinematicsClass\SAKinematics.h"
//#include "schmath.h"
#include <math.h>
/////////////////////////////////////////////////////////////////////////////
// CKinematicModel

/*************************************************/
/* WhatArm()
/* Select what arm is being used. 
/* Correct inputs are "Right" == 0 or "Left" ==1
/*************************************************/
STDMETHODIMP CKinematicModel::get_WhatArm(BSTR * pVal)
{
	if (m_LeftArm == 0)
		*pVal = SysAllocString(L"Right");

	else if (m_LeftArm == 1)
		*pVal = SysAllocString(L"Left");

	else
		*pVal = SysAllocString(L"Please type: right or left");
	
	return S_OK;
}

STDMETHODIMP CKinematicModel::put_WhatArm(BSTR newVal)
{
	// Macro necessary for string manipulation
	USES_CONVERSION;

	// make lower case letters before comparing
	if(strcmp(strlwr(OLE2T(newVal)),"left")==0)
		m_LeftArm = 1;
	else if(strcmp(strlwr(OLE2T(newVal)),"right")==0)
		m_LeftArm = 0;
	else
		m_LeftArm = -1;

	
	/*** Change Kinematic Parameters ***/
	
	// For LEFT ARM
	if (m_LeftArm == 1) 
	{
		/** Transformations **/
		// Ajust the values to reflect the left side
		m_pdEndEffXform[0]	=  LEFT_HAND_X;	
		m_pdEndEffXform[1]	=  LEFT_HAND_Y;	
		m_pdEndEffXform[2]	=  LEFT_HAND_Z;	
	
		// Values to translate point from left shoulder to the origin of ISAC
		m_pdBaseXform[0]	=  LEFT_BASE_X;		
		m_pdBaseXform[1]	=  LEFT_BASE_Y;		
		m_pdBaseXform[2]	=  LEFT_BASE_Z;		
												
		/** DH Parameters **/ 
		m_dA2		=  LEFT_A2;
		m_dA3		=      0.0;
		m_dD3		=  LEFT_D3;			
		m_dD4		=  LEFT_D4;
	}

	// For RIGHT ARM
	else if(m_LeftArm == 0)
	{
		/** Transformation **/ 
		// Re-assign RightArm its original values for the y-coord
		m_pdEndEffXform[0]	=  RIGHT_HAND_X;	
		m_pdEndEffXform[1]	=  RIGHT_HAND_Y;	
		m_pdEndEffXform[2]	=  RIGHT_HAND_Z;		

		m_pdBaseXform[0]	=  RIGHT_BASE_X;		
		m_pdBaseXform[1]	=  RIGHT_BASE_Y;		
		m_pdBaseXform[2]	=  RIGHT_BASE_Z;			
		
		/** DH Parameters **/
		m_dA2		=  RIGHT_A2;
		m_dA3		=       0.0;
		m_dD3		=  RIGHT_D3;			
		m_dD4		=  RIGHT_D4;
	}

	else 
		return !S_OK;

	return S_OK;
}


STDMETHODIMP CKinematicModel::get_param_A2(double * pVal)
{
	if(pVal == NULL) return !S_OK;

	*pVal = m_dA2;
	return S_OK;
}

STDMETHODIMP CKinematicModel::put_param_A2(double newVal)
{

	m_dA2 = newVal;
	return S_OK;
}

STDMETHODIMP CKinematicModel::get_param_A3(double * pVal)
{
	if(pVal == NULL) return !S_OK;

	*pVal = m_dA3;
	return S_OK;
}

STDMETHODIMP CKinematicModel::put_param_A3(double newVal)
{
	m_dA3 = newVal;

	return S_OK;
}

STDMETHODIMP CKinematicModel::get_param_D3(double * pVal)
{
	if(pVal == NULL) return !S_OK;
	*pVal = m_dD3;

	return S_OK;
}

STDMETHODIMP CKinematicModel::put_param_D3(double newVal)
{
	m_dD3 = newVal;

	return S_OK;
}

STDMETHODIMP CKinematicModel::get_param_D4(double * pVal)
{
	if(pVal == NULL) return !S_OK;
	*pVal = m_dD4;

	return S_OK;
}

STDMETHODIMP CKinematicModel::put_param_D4(double newVal)
{
	m_dD4 = newVal;

	return S_OK;
}

STDMETHODIMP CKinematicModel::get_AxisMaxIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal != NULL)
		*pVal=m_sAxisMaxIndex;
	return S_OK;
}

STDMETHODIMP CKinematicModel::put_AxisMaxIndex(short newVal)
{
	// TODO: Add your implementation code here
	if (newVal >= 0 && newVal < NUM_AXES)
		m_sAxisMaxIndex = newVal;

	return S_OK;
}

STDMETHODIMP CKinematicModel::get_AxisMax(double * pVal)
{
	if(pVal == NULL) return !S_OK;

	if(m_sAxisMaxIndex > m_lNumAxes || m_sAxisMaxIndex <0) return E_INVALIDARG;

	*pVal = m_pdAxisMax[m_sAxisMaxIndex];
	return S_OK;
}

STDMETHODIMP CKinematicModel::put_AxisMax(double newVal)
{
	if(m_sAxisMaxIndex > m_lNumAxes || m_sAxisMaxIndex <0) return E_INVALIDARG;
	m_pdAxisMax[m_sAxisMaxIndex] = newVal;

	return S_OK;
}

STDMETHODIMP CKinematicModel::get_AxisMinIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal != NULL)
		*pVal=m_sAxisMinIndex;

	return S_OK;
}

STDMETHODIMP CKinematicModel::put_AxisMinIndex(short newVal)
{
	// TODO: Add your implementation code here
	if (newVal >= 0 && newVal < NUM_AXES)
		m_sAxisMinIndex = newVal;
	return S_OK;
}

STDMETHODIMP CKinematicModel::get_AxisMin(double * pVal)
{
	if(pVal == NULL) return !S_OK;
	if(m_sAxisMinIndex > m_lNumAxes || m_sAxisMinIndex <0) return E_INVALIDARG;

	*pVal = m_pdAxisMin[m_sAxisMinIndex];
	return S_OK;
}

STDMETHODIMP CKinematicModel::put_AxisMin(double newVal)
{
	if(m_sAxisMinIndex > m_lNumAxes || m_sAxisMinIndex <0) return E_INVALIDARG;
	m_pdAxisMin[m_sAxisMinIndex] = newVal;

	return S_OK;
}

STDMETHODIMP CKinematicModel::get_transform_EndEffXformIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal != NULL)
		*pVal=m_sEndEffXformIndex;

	return S_OK;
}

STDMETHODIMP CKinematicModel::put_transform_EndEffXformIndex(short newVal)
{
	// TODO: Add your implementation code here
	if (newVal >= 0 && newVal < NUM_AXES)
		m_sEndEffXformIndex = newVal;

	return S_OK;
}

STDMETHODIMP CKinematicModel::get_transform_EndEffXform(double * pVal)
{
	// TODO: Add your implementation code here

	if(pVal == NULL) return !S_OK;
	if(m_sEndEffXformIndex > m_lNumAxes || m_sEndEffXformIndex < 0) return E_INVALIDARG;

	*pVal = m_pdEndEffXform[m_sEndEffXformIndex];
	return S_OK;
}

STDMETHODIMP CKinematicModel::put_transform_EndEffXform(double newVal)
{
	double M[16];
	// TODO: Add your implementation code here
	if(m_sEndEffXformIndex > m_lNumAxes || m_sEndEffXformIndex <0) return E_INVALIDARG;

	m_pdEndEffXform[m_sEndEffXformIndex] = newVal;
	m_pKMArm->SetRPYMatrix(m_pdEndEffXform,M);			// Build W2E Transformation (Wrist-to-EndEffector)
	m_pKMArm->SetW2ETransform(M);						// Set W2E Transformation

	return S_OK;
}

STDMETHODIMP CKinematicModel::get_transform_BaseXformIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal != NULL)
		*pVal=m_sBaseXformIndex;

	return S_OK;
}

STDMETHODIMP CKinematicModel::put_transform_BaseXformIndex(short newVal)
{
	// TODO: Add your implementation code here
	if (newVal >= 0 && newVal < NUM_AXES)
		m_sBaseXformIndex = newVal;

	return S_OK;
}

STDMETHODIMP CKinematicModel::get_transform_BaseXform(double * pVal)
{

	if(m_sBaseXformIndex < 0 || m_sBaseXformIndex > m_lNumAxes) return E_INVALIDARG;
	*pVal = m_pdBaseXform[m_sBaseXformIndex];

	return S_OK;
}

STDMETHODIMP CKinematicModel::put_transform_BaseXform(double newVal)
{
	m_pdBaseXform[m_sBaseXformIndex] = newVal;

	return S_OK;
}


/////////////////////////////////////////////////////////////////////
// The OnConstruct Function sets all the bindings for the component
/////////////////////////////////////////////////////////////////////
STDMETHODIMP CKinematicModel::OnConstruct() {

// TODO: Bindings. Personalize the binding of your component. 

	int numiids;
	IMA2_BindingInfo BindInf;
	numiids=1;
	long x[1];
	x[0]=0;

	// 1. InputVector - either XYZ or Angles
	BindInf.Name		= SysAllocString(L"InputVector");					// Assign name to object
	BindInf.BindType	= BT_Collection;									// Condition to accept multiple targets
	BindInf.Path		= SysAllocString(L"");								// This must be the path of our component
	BindInf.PIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);		// Create and empty string array
	BindInf.IIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);		// Create and empty string array
	SafeArrayPutElement(BindInf.IIDs,x,(void *)SysAllocString(L"IVectorSignal"));
	m_ConfigureBindings->Add(&BindInf);										// Set up the clients bindings array.	


	// 2. OutputVector - either XYZ or Angles
	BindInf.Name		= SysAllocString(L"OutputVector");					
	SafeArrayPutElement(BindInf.IIDs,x,(void *)SysAllocString(L"IVectorSignal"));
	m_ConfigureBindings->Add(&BindInf);
	
	// Deallocate storage
	SysFreeString(BindInf.Name);
	SysFreeString(BindInf.Path);
	SafeArrayDestroy(BindInf.PIDs);
	SafeArrayDestroy(BindInf.IIDs);
	
	return S_OK;
}

STDMETHODIMP CKinematicModel::OnDestruct() {	return S_OK; }

//////////////////////////////
// Load values of saved data
//////////////////////////////
STDMETHODIMP CKinematicModel::Load(VARIANT Data) {
	
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

		// Variable m_dA2
		ItemName	= SysAllocString(L"A2");
		ItemValue			= new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		m_dA2 = double(*ItemValue);		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_dA3
		ItemName	= SysAllocString(L"A3");
		ItemValue			= new variant_t;
		pIPB->GetFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		// Assign to variable
		m_dA3 = double(*ItemValue);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_dD3
		ItemName	= SysAllocString(L"D3");
		ItemValue			= new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		m_dD3 = double(*ItemValue);		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_dD4
		ItemName	= SysAllocString(L"D4");
		ItemValue			= new variant_t;
		pIPB->GetFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		m_dD4 = double(*ItemValue);		// Deallocate
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_lNumAxes
		ItemName	= SysAllocString(L"NumAxes");
		ItemValue			= new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		m_lNumAxes = (long)*ItemValue;		
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_pdEndEffXform
		/*
		ItemName	= SysAllocString(L"EndEffXform");
		ItemValue			= new variant_t;
		// Read Data from the property bag
		pIPB->GetArrayFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(m_pdEndEffXform, ItemValue->parray->pvData,NUM_AXES*sizeof(double));
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;
		*/

		// Variable m_pdAxisMax
		ItemName	= SysAllocString(L"AxisMax");
		ItemValue			= new variant_t;
		// Read Data from the property bag
		pIPB->GetArrayFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(m_pdAxisMax, ItemValue->parray->pvData,NUM_AXES*sizeof(double));
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_pdAxisMin
		ItemName	= SysAllocString(L"AxisMin");
		ItemValue			= new variant_t;
		// Read Data from the property bag
		pIPB->GetArrayFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(m_pdAxisMin, ItemValue->parray->pvData,NUM_AXES*sizeof(double));
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_pdBaseXform
		ItemName	= SysAllocString(L"BaseXform");
		ItemValue			= new variant_t;
		// Read Data from the property bag
		pIPB->GetArrayFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(m_pdBaseXform, ItemValue->parray->pvData,NUM_AXES*sizeof(double));
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_LeftArm
		// Define strings
		ItemName	= SysAllocString(L"LeftArm");
		ItemValue	= new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		m_LeftArm = (short)*ItemValue;
		//put_WhatArm((short)*ItemValue);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		/********************************************************/
		// Adjust parameters related to the hand
		// If right hand is used
		/*if (m_sRightHand == 1) {
			m_pdEndEffXform[0]	= RIGHT_HAND_X;	
			m_pdEndEffXform[1]	= RIGHT_HAND_Y;	
		}
		// If no hand is used (default)
		else {
			m_pdEndEffXform[0]	= LEFT_HAND_X;	
			m_pdEndEffXform[1]	= LEFT_HAND_Y;	
		}*/
		/********************************************************/

		// Decrement the pointer reference count from our member variable. 
		VariantClear(&m_VBPropertyBag);
		
		// Release
		pIPB->Release();

	return S_OK;

}

//////////////////////
// Saved properties
//////////////////////
STDMETHODIMP CKinematicModel::Save(VARIANT *pData) {
	
	// Variables
	BSTR					ItemName = NULL;// The string holding the name of the item to write into the property bag.
	variant_t				*ItemValue;
	_PropertyBagWrapper		*pIPB;			// COM Interface Pointer to the PropertyBag _Wrapper_ Class
	HRESULT					hRes;			// The HRESULT value we get back from COM calls.

	ItemValue = new variant_t;
	// (1) Create the property bag wrapper class
	// (2) Have the class point to the interface 
	hRes = CoCreateInstance(CLSID_PropertyBagWrapper, NULL, CLSCTX_INPROC_SERVER, IID__PropertyBagWrapper, (LPVOID*)&pIPB);

		if (pIPB == NULL)	
			return !S_OK;
		
		// Variable m_dA2
		// Create string names for items to be saved
		ItemName = SysAllocString(L"A2");
		// Store the data and the type of data into a variant_t type
 		ItemValue = new variant_t(m_dA2,VT_R8);
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_dA3
		// Create string names for items to be saved
		ItemName = SysAllocString(L"A3");
		// Store the data and the type of data into a variant_t type
 		ItemValue = new variant_t(m_dA3,VT_R8);
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_dD3
		// Create string names for items to be saved
		ItemName = SysAllocString(L"D3");
		// Store the data and the type of data into a variant_t type
 		ItemValue = new variant_t(m_dD3,VT_R8);
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_dD4
		// Create string names for items to be saved
		ItemName = SysAllocString(L"D4");
		// Store the data and the type of data into a variant_t type
 		ItemValue = new variant_t(m_dD4,VT_R8);
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_lNumAxes
		// Create string names for items to be saved
		ItemName = SysAllocString(L"NumAxes");
		// Store the data and the type of data into a variant_t type
 		ItemValue = new variant_t(m_lNumAxes,VT_I4);
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_pdBaseXform
		// Create string names for items to be saved
		ItemName = SysAllocString(L"BaseXform");
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_R8;
		ItemValue->parray=SafeArrayCreateVector(VT_R8,0,NUM_AXES);
		memcpy(ItemValue->parray->pvData,m_pdBaseXform,NUM_AXES*sizeof(double));
		hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		/*
		// Variable m_pdEndEffXform
		// Create string names for items to be saved
		ItemName = SysAllocString(L"EndEffXform");
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_R8;
		ItemValue->parray=SafeArrayCreateVector(VT_R8,0,NUM_AXES);
		memcpy(ItemValue->parray->pvData,m_pdEndEffXform,NUM_AXES*sizeof(double));
		hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;
		*/
		// Variable m_pdAxisMax
		// Create string names for items to be saved
		ItemName = SysAllocString(L"AxisMax");
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_R8;
		ItemValue->parray=SafeArrayCreateVector(VT_R8,0,NUM_AXES);
		memcpy(ItemValue->parray->pvData,m_pdAxisMax,NUM_AXES*sizeof(double));
		hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_pdAxisMin
		// Create string names for items to be saved
		ItemName = SysAllocString(L"AxisMin");
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_R8;
		ItemValue->parray=SafeArrayCreateVector(VT_R8,0,NUM_AXES);
		memcpy(ItemValue->parray->pvData,m_pdAxisMin,NUM_AXES*sizeof(double));
		hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
		// Deallocate
		SysFreeString(ItemName);
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

		// m_sRightHand
		ItemName = SysAllocString(L"RightHand");
		// Store the data and the type of data into a variant_t type
 		ItemValue = new variant_t(m_sRightHand, VT_I2);
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Destroy ItemValue
		delete ItemValue;

		// Returns a pointer to the PropertyBag as a VARIANT
		hRes = pIPB->GetPropertyBag(&m_VBPropertyBag);
		
		// Copy the contents of the property bag to the pData VARIANT
		VariantCopy(pData, &m_VBPropertyBag);

		// Decrement the pointer reference count from our member variable. 
		VariantClear(&m_VBPropertyBag);

		// Release
		pIPB->Release();

	return S_OK;
}

/*****************************************************************
/* ForwardKinematics()
/* Compute an XYZRPY coordinate given joint angle positions
/* Input:	Joint Angles (Logical Angles for ISAC)
/* Output:	Cartesian Coordinates
/* 
/* This function performs five operations:
/* 1) Get joint angles in degrees from IMA Interface
/* 2) Call the forward kinematics computation to create the 16 element homogeneous transform matrix
/* 3) Save the XYZRPY values to a local six-element vector
/* 4) Include the "ShoulderBase-to-Eyes" transform for ISAC
/* 5) Output the values (milimetres, degrees) to the vector signal on the IMA interface
/*****************************************************************/
STDMETHODIMP CKinematicModel::kin_ForwardKinematics()
{
	// Local variables	
	HRESULT hRes;
	double pdPos[16];
	double pdAngles[NUM_AXES];			// size before was [NUM_AXES+1]	
	SAFEARRAY *mysa;
	
	IVectorSignal *pIVSIn  = NULL;
	IVectorSignal *pIVSOut = NULL;

	// If this class has not been initialized do so.
	if(m_bInitialized == 0)
		hRes = Initialize();

	// Get pointers for components and interfaces
	m_Bindings->get_Pointers(SysAllocString(L"InputVector"),&m_pIUnkIn);		// Joint Angles
	m_Bindings->get_Pointers(SysAllocString(L"OutputVector"),&m_pIUnkOut);		// Cartesian Position

	if(m_pIUnkIn == NULL && m_pIUnkOut == NULL)	return !S_OK;

	m_pIUnkIn->QueryInterface(IID_IVectorSignal,(void **)&pIVSIn);
	m_pIUnkOut->QueryInterface(IID_IVectorSignal,(void **)&pIVSOut);

	// (1) Get arm angles
	mysa = SafeArrayCreateVector(VT_R8,0,NUM_AXES);
	pIVSIn->GetCurrentVector(mysa);
	memcpy(pdAngles,mysa->pvData,(NUM_AXES)*sizeof(double));
	SafeArrayDestroy(mysa);

	// (2) Call the Forward Kinematics Method. Saves result in B2W array, including the 
	// wrist-to-end-effector transform.
	m_pKMArm->SetAngles(pdAngles);

	// (3) Copy X,Y,Z, and R,P,Y values from matrix into pdPos.
	m_pKMArm->GetXYZRPY(pdPos);

	// (4) Add the Eyes-to-ShouldBase transform.
	// Given that all measurements on ISAC are done from the middle of his eyes, we need to include a 
	// transform from the very base of the shoulder to the middle of the eyes.
	// This frame origin coincides with the frame used for ISAC's cameras.
	pdPos[0]+=m_pdBaseXform[0]; // check the value of the BaseXform seems it's = 0
	pdPos[1]+=m_pdBaseXform[1];
	pdPos[2]+=m_pdBaseXform[2];

	// (5) Send out the cartesian position
	mysa = SafeArrayCreateVector(VT_R8,0,16);
	memcpy(mysa->pvData,pdPos,sizeof(double)*16);
	pIVSOut->SetCurrentVector(mysa);
	// Destroy SafeArray
	SafeArrayDestroy(mysa);

	pIVSOut->Release();
	pIVSIn->Release();


	return S_OK;
}

/********************************************************************************************************************
/* Compute Joing Angles (Desired Logical Angles) given Desired XYZRPY position.
/* Input:	DesiredXYZPosition (mm, degrees)
/* Output:	DesiredLogicalAngles (degrees)
/* Note: It is important for the developper to make sure that the input vector is receiving the DesiredXYZPos BINDING
/* (It could easily be mistaken for another variable like DesiredLogicalAngles).	
/*
/* This method performs 5 functions:
/* 1) Gets desired XYZRPY positions,
/* 2) Subtracts the "ShoulderBase-to-Eyes" transform from the Cartesian positions and converts degrees to radians
/* 3) Compute the 16 element homogeneous transform from the XYZRPY vector
/* 4) Compute the inverse kinematics
/* 5) Output the robot joint angles in degrees
/********************************************************************************************************************/
STDMETHODIMP CKinematicModel::kin_InverseKinematics()
{
	// Local variables
	HRESULT hRes;
	double pdPos[16];
	double pdAngles[NUM_AXES];			// size before was [NUM_AXES+1]
	SAFEARRAY *mysa;

	IVectorSignal *pIVSIn  = NULL;
	IVectorSignal *pIVSOut = NULL;

	// If this class has not been initialized do so.
	if(m_bInitialized == 0)
		hRes = Initialize();

	// Get pointers for components and interfaces
	m_Bindings->get_Pointers(SysAllocString(L"InputVector"),&m_pIUnkIn);			// DesiredXYZPos
	m_Bindings->get_Pointers(SysAllocString(L"OutputVector"),&m_pIUnkOut);			// DesLogAngles

	if(m_pIUnkIn == NULL && m_pIUnkOut == NULL)	return !S_OK;

	m_pIUnkIn->QueryInterface(IID_IVectorSignal,(void **)&pIVSIn);
	m_pIUnkOut->QueryInterface(IID_IVectorSignal,(void **)&pIVSOut);

	if(pIVSIn == NULL && pIVSOut == NULL) return !S_OK;

	// 1) Get the DesiredXYZRPY Position
	mysa = SafeArrayCreateVector(VT_R8,0,16);
	pIVSIn->GetCurrentVector(mysa);
	memcpy(pdPos,mysa->pvData,sizeof(double)*16);
	SafeArrayDestroy(mysa);

	/**** WORKSPACE LIMITS CHECKED ****/
	// Before we compute the inverse kinematics we will check to see if the input XYZ coordinates
	// are withing the dexterous workspace of the Right and Left arm. 
	//
	// The mathematics to estimate the workspace were done through matlab. M-files, figs, .mats can be found at:
	// O:\Agents\Test Agents\Characterization of the RightArm Workspace\ (mostly under Sphere Fitting).
	// The results provide four shperes in order to describe the workspace: upper-front/back, lower-front/back
	// as can be seen from the figures. 
	//
	// Hence, in order to see if an XYZ coord is in the workspace, the point must be within the radious of the 
	// upper/lower-front spheres, and outside the upper/lower-back spheres. 
	// 
	// The equations are derived from an approximation of the sphere variables Cx,Cy,Cz,R through the least-squares method
	// lsqnonlin method in matlab:
	// uf = sqrt((pdPos[0]--33.80)^2+(pdPos[1]--253.83)^2+(pdPos[2]--731.40)^2) < 838.79 
	// lf = sqrt((pdPos[0]--28.63)^2+(pdPos[1]--259.95)^2+(pdPos[2]--270.92)^2) < 735.55
	//
	// ub = sqrt((pdPos[0]--55.77)^2+(pdPos[1]--270.24)^2+(pdPos[2]--283.45)^2) > 382.65 
	// lb = sqrt((pdPos[0]--94.17)^2+(pdPos[1]--248.36)^2+(pdPos[2]--639.46)^2) > 357.53
	
	// Right Arm
	if (m_LeftArm == 0)	
	{
	//	if ( !(
	//		sqrt( (int)(pdPos[0]+33.80)^2 + (int)(pdPos[1]+253.83)^2 + (int)(pdPos[2]+731.40)^2   ) < 850/*838.79*/  &&
	//		sqrt( (int)(pdPos[0]+28.63)^2 + (int)(pdPos[1]+259.95)^2 + (int)(pdPos[2]+270.92)^2   ) < 750/*735.55*/  &&
	//		sqrt( (int)(pdPos[0]+55.77)^2 + (int)(pdPos[1]+270.24)^2 + (int)(pdPos[2]+283.45)^2   ) > 390/*382.65*/  &&
	//		sqrt( (int)(pdPos[0]+94.17)^2 + (int)(pdPos[1]+248.36)^2 + (int)(pdPos[2]+639.46)^2   ) > 357.53  
	//		) )
	//	{

			// If the DesiredXYZ coordinate is outside the workspace, we want to keep the same values in pdPos[] as before. 
			// Hence, leave the data member without change and exit the function. 
			// The arm loop should process the same result it did for the previous iterations.
	//		MessageBox( NULL, "Sorry, the Arm cannot reach location %1f\t%1f\t%1f\t,&pdPos[0],&pdPos[1],&pdPos[2]", "Arm Reached its limit", MB_OK );

			// Send out the previous iteration set of angles to the (Desisred Logical Angles) Vector Signal
		/*	mysa = SafeArrayCreateVector(VT_R8,0,NUM_AXES);
			memcpy(mysa->pvData,pdAngles,sizeof(double)*NUM_AXES);
			pIVSOut->SetCurrentVector(mysa); 
			SafeArrayDestroy(mysa);

			// Release the interface connections and return S_OK in order to move on through the rest of the function calls
			pIVSOut->Release();
			pIVSIn->Release();
			return S_OK;*/
	//	}
	}


	// Left Arm
	if (m_LeftArm == 1)
	{
//		pdPos[0]-=m_pdBaseXform[0];
//		pdPos[1]-=m_pdBaseXform[1];
//		pdPos[2]-=m_pdBaseXform[2];
	}

	// 2) Tranform: Subtract the base-tranform from the center of the eyes to get the coords at the base of the shoulder
	pdPos[0]-=m_pdBaseXform[0];	// X
	pdPos[1]-=m_pdBaseXform[1];	// Y
	pdPos[2]-=m_pdBaseXform[2];	// Z

	// Convert RPY from degrees to radians
	pdPos[3] = pdPos[3] * D2R;
	pdPos[4] = pdPos[4] * D2R;
	pdPos[5] = pdPos[5] * D2R;

	// 3) We pass the XYZRPY vector through pdPos.
	//    Then a 16 element homogeneous matrix is computed.
	//    Finally, the IK are computed.
	m_pKMArm->SetXYZRPY(pdPos);		

	// 4) Retrieve the computed IK angles (in degrees) into our local copy.
	m_pKMArm->GetAngles(pdAngles);	

	// 5) Output computed joint angles to the (Desisred Logical Angles) Vector Signal
	mysa = SafeArrayCreateVector(VT_R8,0,NUM_AXES);
	memcpy(mysa->pvData,pdAngles,sizeof(double)*NUM_AXES);
	pIVSOut->SetCurrentVector(mysa); 
	SafeArrayDestroy(mysa);
		
	// Release bindings
	pIVSOut->Release();
	pIVSIn->Release();

	return S_OK;

}

/********************************************************************************************************************/
/* Initialization()
/*
/* This routine is in charge of doing the following:
/* 1) Call the Constructor of CSAKinematics. The constructor does:
/*    a) Call Forward Kinematics. It creates the initial 4x4 matrix containing
/*       the 3x3 rotation matrix and the 3x1 translation vector. 
/*		 This matrix does not account for the end-effector. 
/*		 The result is stored in the element B2W, which stands for Base-to-End Effector. 
/*	  b) The call to the constructor also creates other matrices: B2W, B2E, W2E, and W2EI.
/* 2) The next two calls are coupled and work together. The first call sets the stage for the second.
/*	  The SetRPYMatrix() is used by SetW2ETransform() to append the Wrist-to-End Effector transform to
/*    the B2W matrix. To do so, the W2ETransofrm uses the matrix elements generated by SetRPYMatrix().
/*    The original designer of this code used this method to facilitate the creation of the final Forward Kinematics.
/**********************************************************************************************************************/
STDMETHODIMP CKinematicModel::Initialize()
{
	double M[16];

	if(m_bInitialized == 0)
	{
	
		// 1) Compute FKins and Transform Matrices
		m_pKMArm = new CSAKinematics(m_LeftArm);

		// 2) Use end effector data in next two calls to include end-effector info in Forward Kins.
		m_pKMArm->SetRPYMatrix(/*[in]*/m_pdEndEffXform, /*[out]*/M);			// Create a structure to be used by next call.
		m_pKMArm->SetW2ETransform(M);											// Create Base-to-Wrist Homogeneous Transform.

		// Change Flag
		m_bInitialized = 1;
	}

	return S_OK;
}

