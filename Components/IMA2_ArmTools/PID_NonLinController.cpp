// PID_NonLinController.cpp : Implementation of CPID_NonLinController
#include "stdafx.h"
#include "math.h"
#include "IMA2_ArmTools.h"
#include "PID_NonLinController.h"

/////////////////////////////////////////////////////////////////////////////
// CPID_NonLinController

/////////////////////////////////////////////////////////////////////
// The OnConstruct Function sets all the bindings for the component
/////////////////////////////////////////////////////////////////////
STDMETHODIMP CPID_NonLinController::OnConstruct() {

// TODO: Bindings. Personalize the binding of your component. 

	int numiids;
	IMA2_BindingInfo BindInf;
	numiids=1;

	// 1. PhysicalAngles
	BindInf.Name		= SysAllocString(L"PhysicalAngles");				// Assign name to object
	BindInf.BindType	= BT_Collection;									// Condition to accept multiple targets
	BindInf.Path		= SysAllocString(L"");								// This must be the path of our component
	BindInf.PIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);		// Create and empty string array
	BindInf.IIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);		// Create and empty string array
	m_ConfigureBindings->Add(&BindInf);										// Set up the clients bindings array.	

	// 2. DesiredPhysicalAngles
	BindInf.Name		= SysAllocString(L"DesiredPhysicalAngles");					
	m_ConfigureBindings->Add(&BindInf);

	// 3. BiasedPressure
	BindInf.Name		= SysAllocString(L"PressureBiasVector");					
	m_ConfigureBindings->Add(&BindInf);

	// 4. Pressures
	BindInf.Name		= SysAllocString(L"Pressures");					
	m_ConfigureBindings->Add(&BindInf);
	
	// Deallocate storage
	SysFreeString(BindInf.Name);
	SysFreeString(BindInf.Path);
	SafeArrayDestroy(BindInf.PIDs);
	SafeArrayDestroy(BindInf.IIDs);
	
	return S_OK;
}

STDMETHODIMP CPID_NonLinController::OnDestruct() {	return S_OK; }

//////////////////////////////
// Load values of saved data
//////////////////////////////
STDMETHODIMP CPID_NonLinController::Load(VARIANT Data) {
	
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

		// Variable m_pKp
		// Define strings
		ItemName	= SysAllocString(L"Kp");
		ItemValue			= new variant_t;
		// Read Data from the property bag
		pIPB->GetArrayFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(m_pKp, ItemValue->parray->pvData,MAX_AXES*sizeof(bool));
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_pKi
		ItemName	= SysAllocString(L"Ki");
		ItemValue			= new variant_t;
		pIPB->GetArrayFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(m_pKi, ItemValue->parray->pvData,MAX_AXES*sizeof(double));
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_pKd
		ItemName	= SysAllocString(L"Kd");
		ItemValue			= new variant_t;
		pIPB->GetArrayFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(m_pKd, ItemValue->parray->pvData,MAX_AXES*sizeof(double));
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_pMaxClamp
		ItemName	= SysAllocString(L"MaxClamp");
		ItemValue			= new variant_t;
		pIPB->GetArrayFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(m_pMaxClamp, ItemValue->parray->pvData,MAX_AXES*sizeof(double));
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_pMinClamp
		ItemName	= SysAllocString(L"MinClamp");
		ItemValue			= new variant_t;
		pIPB->GetArrayFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(m_pMinClamp, ItemValue->parray->pvData,MAX_AXES*sizeof(double));
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_pBiasedPressure
		ItemName		= SysAllocString(L"BiasedPressure");
		ItemValue				= new variant_t;
		pIPB->GetArrayFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(m_pBiasedPressure, ItemValue->parray->pvData,MAX_AXES*sizeof(double));		
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_pControl_Law
		ItemName		= SysAllocString(L"Control_Law");
		ItemValue				= new variant_t;
		pIPB->GetArrayFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(m_pControl_Law, ItemValue->parray->pvData,MAX_AXES*sizeof(short));		
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_A0
		ItemName		= SysAllocString(L"A0");
		ItemValue				= new variant_t;
		pIPB->GetArrayFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(m_A0, ItemValue->parray->pvData,MAX_AXES*sizeof(double));		
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_A1
		ItemName		= SysAllocString(L"A1");
		ItemValue				= new variant_t;
		pIPB->GetArrayFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(m_A1, ItemValue->parray->pvData,MAX_AXES*sizeof(double));		
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_A2
		ItemName		= SysAllocString(L"A2");
		ItemValue				= new variant_t;
		pIPB->GetArrayFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(m_A2, ItemValue->parray->pvData,MAX_AXES*sizeof(double));		
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_A3
		ItemName		= SysAllocString(L"A3");
		ItemValue				= new variant_t;
		pIPB->GetArrayFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(m_A3, ItemValue->parray->pvData,MAX_AXES*sizeof(double));		
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_A4
		ItemName		= SysAllocString(L"A4");
		ItemValue				= new variant_t;
		pIPB->GetArrayFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(m_A4, ItemValue->parray->pvData,MAX_AXES*sizeof(double));		
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_pAlpha
		ItemName		= SysAllocString(L"Alpha");
		ItemValue				= new variant_t;
		pIPB->GetArrayFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(m_pAlpha, ItemValue->parray->pvData,MAX_AXES*sizeof(double));		
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;
		// Decrement the pointer reference count from our member variable. 
		VariantClear(&m_VBPropertyBag);

		// Variable m_bInvertPressure
		ItemName		= SysAllocString(L"InvertPressure");
		ItemValue				= new variant_t;
		pIPB->GetArrayFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(m_bInvertPressure, ItemValue->parray->pvData,MAX_AXES*sizeof(bool));		
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

//////////////////////
// Saved properties
//////////////////////
STDMETHODIMP CPID_NonLinController::Save(VARIANT *pData) {
	
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
		
		// Variable m_pKd
		// Create string names for items to be saved
		ItemName = SysAllocString(L"Kd");
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_R8;
		ItemValue->parray=SafeArrayCreateVector(VT_R8,0,MAX_AXES);
		memcpy(ItemValue->parray->pvData,m_pKd,MAX_AXES*sizeof(double));
		hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_pKp
		// Create string names for items to be saved
		ItemName = SysAllocString(L"Kp");
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_R8;
		ItemValue->parray=SafeArrayCreateVector(VT_R8,0,MAX_AXES);
		memcpy(ItemValue->parray->pvData,m_pKp,MAX_AXES*sizeof(double));
		hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_pKi
		ItemName = SysAllocString(L"Ki");
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_R8;
		ItemValue->parray=SafeArrayCreateVector(VT_R8,0,MAX_AXES);
		memcpy(ItemValue->parray->pvData,m_pKi,MAX_AXES*sizeof(double));
		hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_pMaxClamp
		ItemName = SysAllocString(L"MaxClamp");
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_R8;
		ItemValue->parray=SafeArrayCreateVector(VT_R8,0,MAX_AXES);
		memcpy(ItemValue->parray->pvData,m_pMaxClamp,MAX_AXES*sizeof(double));
		hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
		// Deallocate
		SysFreeString(ItemName);
		// Delete ItemValue
		delete ItemValue;

		// Variable m_pMinClamp
		ItemName = SysAllocString(L"MinClamp");
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_R8;
		ItemValue->parray=SafeArrayCreateVector(VT_R8,0,MAX_AXES);
		memcpy(ItemValue->parray->pvData,m_pMinClamp,MAX_AXES*sizeof(double));
		hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
		// Deallocate
		SysFreeString(ItemName);
		// Delete ItemValue
		delete ItemValue;


		// Variable m_pBiasedPressure
		ItemName = SysAllocString(L"BiasedPressure");
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_R8;
		ItemValue->parray=SafeArrayCreateVector(VT_R8,0,MAX_AXES);
		memcpy(ItemValue->parray->pvData,m_pBiasedPressure,MAX_AXES*sizeof(double));
		hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
		// Deallocate
		SysFreeString(ItemName);
		// Delete ItemValue
		delete ItemValue;


		// Variable m_pControl_Law
		ItemName = SysAllocString(L"Control_Law");
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_I2;
		ItemValue->parray=SafeArrayCreateVector(VT_I2,0,MAX_AXES);
		memcpy(ItemValue->parray->pvData,m_pControl_Law,MAX_AXES*sizeof(short));
		hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
		// Deallocate
		SysFreeString(ItemName);
		// Delete ItemValue
		delete ItemValue;

		// Variable m_A0
		ItemName = SysAllocString(L"A0");
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_R8;
		ItemValue->parray=SafeArrayCreateVector(VT_R8,0,MAX_AXES);
		memcpy(ItemValue->parray->pvData,m_A0,MAX_AXES*sizeof(double));
		hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
		// Deallocate
		SysFreeString(ItemName);
		// Delete ItemValue
		delete ItemValue;

		// Variable m_A1
		ItemName = SysAllocString(L"A1");
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_R8;
		ItemValue->parray=SafeArrayCreateVector(VT_R8,0,MAX_AXES);
		memcpy(ItemValue->parray->pvData,m_A1,MAX_AXES*sizeof(double));
		hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
		// Deallocate
		SysFreeString(ItemName);
		// Delete ItemValue
		delete ItemValue;

		// Variable m_A2
		ItemName = SysAllocString(L"A2");
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_R8;
		ItemValue->parray=SafeArrayCreateVector(VT_R8,0,MAX_AXES);
		memcpy(ItemValue->parray->pvData,m_A2,MAX_AXES*sizeof(double));
		hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
		// Deallocate
		SysFreeString(ItemName);
		// Delete ItemValue
		delete ItemValue;

		// Variable m_A3
		ItemName = SysAllocString(L"A3");
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_R8;
		ItemValue->parray=SafeArrayCreateVector(VT_R8,0,MAX_AXES);
		memcpy(ItemValue->parray->pvData,m_A3,MAX_AXES*sizeof(double));
		hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
		// Deallocate
		SysFreeString(ItemName);
		// Delete ItemValue
		delete ItemValue;

		// Variable m_A4
		ItemName = SysAllocString(L"A4");
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_R8;
		ItemValue->parray=SafeArrayCreateVector(VT_R8,0,MAX_AXES);
		memcpy(ItemValue->parray->pvData,m_A4,MAX_AXES*sizeof(double));
		hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_pAlpha[]
		ItemName = SysAllocString(L"Alpha");
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_R8;
		ItemValue->parray=SafeArrayCreateVector(VT_R8,0,MAX_AXES);
		memcpy(ItemValue->parray->pvData,m_pAlpha,MAX_AXES*sizeof(double));
		hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_bInvertPressure[]
		ItemName = SysAllocString(L"InvertPressure");
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_I2;
		ItemValue->parray=SafeArrayCreateVector(VT_I2,0,MAX_AXES);
		memcpy(ItemValue->parray->pvData,m_bInvertPressure,MAX_AXES*sizeof(short));
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
// Set initial pressure Bias
/////////////////////////////////////////////////

STDMETHODIMP CPID_NonLinController::Initial()
{
	// TODO: Add your implementation code here

	long Index;
	SAFEARRAY *mysa;

	IVectorSignal *pIVSPressBias = NULL;			// Vector signal for Pressure Bias

	// Fill state with zeros
	for (Index = 0; Index < MAX_AXES; Index++)
		 m_pIntegrator[Index] = 0.0;				// Controller state variables

	// Get object and interface pointer
	m_Bindings->get_Pointers(SysAllocString(L"PressureBiasVector"),&m_pIUnkBiasedPressureState);
	if (m_pIUnkBiasedPressureState == NULL) return E_POINTER;
		m_pIUnkBiasedPressureState->QueryInterface(IID_IVectorSignal,(void**)&pIVSPressBias);

	if (pIVSPressBias != NULL)
	{
		// Pass a SafeArray
		mysa = SafeArrayCreateVector(VT_R8,0,m_Axes);
		memcpy(mysa->pvData,m_pBiasedPressure,sizeof(double)*m_Axes);
		pIVSPressBias->SetCurrentVector(mysa); 	
		pIVSPressBias->Release();
		// Destroy SafeArray
		SafeArrayDestroy(mysa);
		pIVSPressBias = NULL;
	}
	else	// We don't have all the right connections so release and signal error.
	{
		if (pIVSPressBias != NULL)
			pIVSPressBias->Release();

		return E_FAIL;
	}

	return S_OK;
}

STDMETHODIMP CPID_NonLinController::get_InvertPressure(BOOL *pVal)
{
	// TODO: Add your implementation code here
	if (pVal == NULL)
		return E_POINTER;

	if (m_sInvertPressureIndex < MAX_AXES)
	{
			*pVal = m_bInvertPressure[m_sInvertPressureIndex];
	}
	else
		return E_INVALIDARG;

	return S_OK;
}

STDMETHODIMP CPID_NonLinController::put_InvertPressure(BOOL newVal)
{
	
	// TODO: Add your implementation code here
	if (m_sInvertPressureIndex < MAX_AXES)
	{
		m_bInvertPressure[m_sInvertPressureIndex] = newVal;
	}
	else
		return E_INVALIDARG;

	return S_OK;
}

STDMETHODIMP CPID_NonLinController::get_A0(double *pVal)
{
	// TODO: Add your implementation code here
	if (m_sA0Index < m_Axes)
	{
		if (pVal == NULL)
			return E_POINTER;

		*pVal = m_A0[m_sA0Index];

		return S_OK;
	}
	else 
	 return E_INVALIDARG;
}

STDMETHODIMP CPID_NonLinController::put_A0(double newVal)
{
	// TODO: Add your implementation code here
	if (m_sA0Index < m_Axes)
	{
		m_A0[m_sA0Index] = newVal;

		return S_OK;
	}
	else
		return E_INVALIDARG;
}

STDMETHODIMP CPID_NonLinController::get_A1(double *pVal)
{
	// TODO: Add your implementation code here
	if (m_sA1Index < m_Axes)
	{
		if (pVal == NULL)
			return E_POINTER;

		*pVal = m_A1[m_sA1Index];

		return S_OK;
	}
	else 
	 return E_INVALIDARG;
}

STDMETHODIMP CPID_NonLinController::put_A1(double newVal)
{
	// TODO: Add your implementation code here
	if (m_sA1Index < m_Axes)
	{
		m_A1[m_sA1Index] = newVal;

		return S_OK;
	}
	else
		return E_INVALIDARG;
}

STDMETHODIMP CPID_NonLinController::get_A2(double *pVal)
{
	// TODO: Add your implementation code here
	if (m_sA2Index < m_Axes)
	{
		if (pVal == NULL)
			return E_POINTER;

		*pVal = m_A2[m_sA2Index];

		return S_OK;
	}
	else 
	 return E_INVALIDARG;
}

STDMETHODIMP CPID_NonLinController::put_A2(double newVal)
{
	if (m_sA2Index < m_Axes)
	{
		m_A2[m_sA2Index] = newVal;

		return S_OK;
	}
	else
		return E_INVALIDARG;
}

STDMETHODIMP CPID_NonLinController::get_A3(double *pVal)
{
	// TODO: Add your implementation code here
	if (m_sA3Index < m_Axes)
	{
		if (pVal == NULL)
			return E_POINTER;

		*pVal = m_A3[m_sA3Index];

		return S_OK;
	}
	else 
	 return E_INVALIDARG;
}

STDMETHODIMP CPID_NonLinController::put_A3(double newVal)
{
	// TODO: Add your implementation code here
	if (m_sA3Index < m_Axes)
	{
		m_A3[m_sA3Index] = newVal;

		return S_OK;
	}
	else
		return E_INVALIDARG;
}

STDMETHODIMP CPID_NonLinController::get_A4(double *pVal)
{
	// TODO: Add your implementation code here
	if (m_sA4Index < m_Axes)
	{
		if (pVal == NULL)
			return E_POINTER;

		*pVal = m_A4[m_sA4Index];

		return S_OK;
	}
	else 
	 return E_INVALIDARG;
}

STDMETHODIMP CPID_NonLinController::put_A4(double newVal)
{
	// TODO: Add your implementation code here
	if (m_sA4Index < m_Axes)
	{
		m_A4[m_sA4Index] = newVal;

		return S_OK;
	}
	else
		return E_INVALIDARG;
}

STDMETHODIMP CPID_NonLinController::get_MinClamp(double *pVal)
{
	// TODO: Add your implementation code here
	if (m_sMinClampIndex < m_Axes)
	{
		if (pVal == NULL)
			return E_POINTER;

		*pVal = m_pMinClamp[m_sMinClampIndex];

		return S_OK;
	}
	else 
	 return E_INVALIDARG;
}

STDMETHODIMP CPID_NonLinController::put_MinClamp(double newVal)
{
	// TODO: Add your implementation code here
	if (m_sMinClampIndex < m_Axes)
	{
		m_pMinClamp[m_sMinClampIndex] = newVal;

		return S_OK;
	}
	else
		return E_INVALIDARG;
}

STDMETHODIMP CPID_NonLinController::get_MaxClamp(double *pVal)
{
	// TODO: Add your implementation code here
	if (m_sMaxClampIndex < m_Axes)
	{
		if (pVal == NULL)
			return E_POINTER;

		*pVal = m_pMaxClamp[m_sMaxClampIndex];

		return S_OK;
	}
	else 
	 return E_INVALIDARG;
}

STDMETHODIMP CPID_NonLinController::put_MaxClamp(double newVal)
{
	// TODO: Add your implementation code here
	if (m_sMaxClampIndex < m_Axes)
	{
		m_pMaxClamp[m_sMaxClampIndex] = newVal;

		return S_OK;
	}
	else
		return E_INVALIDARG;
}

STDMETHODIMP CPID_NonLinController::get_Kp(double *pVal)
{
	// TODO: Add your implementation code here
	if (m_sKpIndex < m_Axes)
	{
		if (pVal == NULL)
			return E_POINTER;

		*pVal = m_pKp[m_sKpIndex];

		return S_OK;
	}
	else 
	 return E_INVALIDARG;
}

STDMETHODIMP CPID_NonLinController::put_Kp(double newVal)
{
	// TODO: Add your implementation code here
	if (m_sKpIndex < m_Axes)
	{
		m_pKp[m_sKpIndex] = newVal;

		return S_OK;
	}
	else
		return E_INVALIDARG;
}

STDMETHODIMP CPID_NonLinController::get_Ki(double *pVal)
{
	// TODO: Add your implementation code here
	if (m_sKiIndex < m_Axes)
	{
		if (pVal == NULL)
			return E_POINTER;

		*pVal = m_pKi[m_sKiIndex];

		return S_OK;
	}
	else 
	 return E_INVALIDARG;
}

STDMETHODIMP CPID_NonLinController::put_Ki(double newVal)
{
	// TODO: Add your implementation code here
	if (m_sKiIndex < m_Axes)
	{
		m_pKi[m_sKiIndex] = newVal;

		return S_OK;
	}
	else
		return E_INVALIDARG;
}

STDMETHODIMP CPID_NonLinController::get_Kd(double *pVal)
{
	// TODO: Add your implementation code here
	if (m_sKdIndex < m_Axes)
	{
		if (pVal == NULL)
			return E_POINTER;

		*pVal = m_pKd[m_sKdIndex];

		return S_OK;
	}
	else 
	 return E_INVALIDARG;
}

STDMETHODIMP CPID_NonLinController::put_Kd(double newVal)
{
	// TODO: Add your implementation code here
	if (m_sKdIndex < m_Axes)
	{
		m_pKd[m_sKdIndex] = newVal;

		return S_OK;
	}
	else
		return E_INVALIDARG;
}

STDMETHODIMP CPID_NonLinController::get_Control_Law(int *pVal)
{
	// TODO: Add your implementation code here
	if (m_sControl_LawIndex < m_Axes)
	{
		if (pVal == NULL)
			return E_POINTER;

		*pVal = m_pControl_Law[m_sControl_LawIndex];

		return S_OK;
	}
	else 
	 return E_INVALIDARG;
}

STDMETHODIMP CPID_NonLinController::put_Control_Law(int newVal)
{
	// TODO: Add your implementation code here
	if (m_sControl_LawIndex < m_Axes)
	{
		m_pControl_Law[m_sControl_LawIndex] = newVal;

		return S_OK;
	}
	else
		return E_INVALIDARG;
}

STDMETHODIMP CPID_NonLinController::get_BiasedPressure(double *pVal)
{
	// TODO: Add your implementation code here
	if (m_sBiasedPressureIndex < m_Axes)
	{
		if (pVal == NULL)
			return E_POINTER;

		*pVal = m_pBiasedPressure[m_sBiasedPressureIndex];

		return S_OK;
	}
	else 
	 return E_INVALIDARG;
}

STDMETHODIMP CPID_NonLinController::put_BiasedPressure(double newVal)
{
	// TODO: Add your implementation code here
	if (m_sBiasedPressureIndex < m_Axes)
	{
		m_pBiasedPressure[m_sBiasedPressureIndex] = newVal;

		return S_OK;
	}
	else
		return E_INVALIDARG;
}


STDMETHODIMP CPID_NonLinController::get_InvertPressureIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal == NULL)
		return E_POINTER;

	*pVal = m_sInvertPressureIndex;
	
	return S_OK;
}

STDMETHODIMP CPID_NonLinController::put_InvertPressureIndex(short newVal)
{
	// TODO: Add your implementation code here
	m_sInvertPressureIndex = newVal;

	return S_OK;
}

STDMETHODIMP CPID_NonLinController::get_A0Index(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal == NULL)
		return E_POINTER;

	*pVal = m_sA0Index;

	return S_OK;
}

STDMETHODIMP CPID_NonLinController::put_A0Index(short newVal)
{
	// TODO: Add your implementation code here
	m_sA0Index = newVal;
	return S_OK;
}

STDMETHODIMP CPID_NonLinController::get_A1Index(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal == NULL)
		return E_POINTER;

	*pVal = m_sA1Index;

	return S_OK;
}

STDMETHODIMP CPID_NonLinController::put_A1Index(short newVal)
{
	// TODO: Add your implementation code here
	m_sA1Index = newVal;

	return S_OK;
}

STDMETHODIMP CPID_NonLinController::get_A2Index(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal == NULL)
		return E_POINTER;

	*pVal = m_sA2Index;

	return S_OK;
}

STDMETHODIMP CPID_NonLinController::put_A2Index(short newVal)
{
	// TODO: Add your implementation code here
	m_sA2Index = newVal;

	return S_OK;
}

STDMETHODIMP CPID_NonLinController::get_A3Index(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal == NULL)
		return E_POINTER;

	*pVal = m_sA3Index;

	return S_OK;
}

STDMETHODIMP CPID_NonLinController::put_A3Index(short newVal)
{
	// TODO: Add your implementation code here
	m_sA3Index = newVal;

	return S_OK;
}

STDMETHODIMP CPID_NonLinController::get_A4Index(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal == NULL)
		return E_POINTER;

	*pVal = m_sA4Index;

	return S_OK;
}

STDMETHODIMP CPID_NonLinController::put_A4Index(short newVal)
{
	// TODO: Add your implementation code here
	m_sA4Index = newVal;

	return S_OK;
}

STDMETHODIMP CPID_NonLinController::get_MinClampIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal == NULL)
		return E_POINTER;

	*pVal = m_sMinClampIndex;

	return S_OK;
}

STDMETHODIMP CPID_NonLinController::put_MinClampIndex(short newVal)
{
	// TODO: Add your implementation code here
	m_sMinClampIndex = newVal;

	return S_OK;
}

STDMETHODIMP CPID_NonLinController::get_MaxClampIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal == NULL)
		return E_POINTER;

	*pVal = m_sMaxClampIndex;

	return S_OK;
}

STDMETHODIMP CPID_NonLinController::put_MaxClampIndex(short newVal)
{
	// TODO: Add your implementation code here
	m_sMaxClampIndex = newVal;

	return S_OK;
}

STDMETHODIMP CPID_NonLinController::get_KpIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal == NULL)
		return E_POINTER;

	*pVal = m_sKpIndex;

	return S_OK;
}

STDMETHODIMP CPID_NonLinController::put_KpIndex(short newVal)
{
	// TODO: Add your implementation code here
	m_sKpIndex = newVal;

	return S_OK;
}

STDMETHODIMP CPID_NonLinController::get_KiIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal == NULL)
		return E_POINTER;

	*pVal = m_sKiIndex;

	return S_OK;
}

STDMETHODIMP CPID_NonLinController::put_KiIndex(short newVal)
{
	// TODO: Add your implementation code here
	m_sKiIndex = newVal;

	return S_OK;
}

STDMETHODIMP CPID_NonLinController::get_KdIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal == NULL)
		return E_POINTER;

	*pVal = m_sKdIndex;

	return S_OK;
}

STDMETHODIMP CPID_NonLinController::put_KdIndex(short newVal)
{
	// TODO: Add your implementation code here
	m_sKdIndex = newVal;

	return S_OK;
}

STDMETHODIMP CPID_NonLinController::get_Control_LawIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal == NULL)
		return E_POINTER;

	*pVal = m_sControl_LawIndex;

	return S_OK;
}

STDMETHODIMP CPID_NonLinController::put_Control_LawIndex(short newVal)
{
	// TODO: Add your implementation code here
	m_sControl_LawIndex = newVal;

	return S_OK;
}

STDMETHODIMP CPID_NonLinController::get_BiasedPressureIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal == NULL)
		return E_POINTER;

	*pVal = m_sBiasedPressureIndex;

	return S_OK;
}

STDMETHODIMP CPID_NonLinController::put_BiasedPressureIndex(short newVal)
{
	// TODO: Add your implementation code here
	m_sBiasedPressureIndex = newVal;

	return S_OK;
}

STDMETHODIMP CPID_NonLinController::get_AlphaIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal == NULL)
		return E_POINTER;

	*pVal = m_sAlphaIndex;

	return S_OK;
}

STDMETHODIMP CPID_NonLinController::put_AlphaIndex(short newVal)
{
	// TODO: Add your implementation code here
	m_sAlphaIndex = newVal;

	return S_OK;
}

STDMETHODIMP CPID_NonLinController::get_LeftArm(short *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_LeftArm;
	return S_OK;
}

STDMETHODIMP CPID_NonLinController::put_LeftArm(short newVal)
{
	// TODO: Add your implementation code here
	m_LeftArm = newVal;

	// RETURN LEFT ARM VALUES
	if (m_LeftArm == 1) 
	{

	// These values existed in IMA 1.0. Have never been used. But are noted in case someone
	// in the future, might want to look at arm behavior with these values. 
	/*	m_pKp[0] =  500.0;	
		m_pKp[1] =  500.0;
		m_pKp[2] = 1000.0;
		m_pKp[3] = 1000.0;
		m_pKp[4] = 1500.0;
		m_pKp[5] = 1500.0;

		m_pKi[0] =  20.0;	
		m_pKi[1] =  50.0;
		m_pKi[2] =  70.0;
		m_pKi[3] =  70.0;
		m_pKi[4] = 250.0;
		m_pKi[5] = 250.0;

		m_pKd[0] =  2.0;
		m_pKd[1] =  1.0;
		m_pKd[2] =  1.0;
		m_pKd[3] =  1.0;
		m_pKd[4] = 90.0;
		m_pKd[5] = 90.0;	
*/
	}
	
	// RETURN RIGHT ARM VALUES
	else if (m_LeftArm == 0) 	
	{
		
		// If other values are used for the left arm, use these for the right arm. 
/*		// Original Right arm PID Values
		m_pKp[0] = 500.0;	
		m_pKp[1] = 850.0;
		m_pKp[2] = 850.0;
		m_pKp[3] = 850.0;
		m_pKp[4] = 900.0;
		m_pKp[5] = 900.0;

		m_pKi[0] = 15.0;	
		m_pKi[1] = 90.0;
		m_pKi[2] = 150.0;
		m_pKi[3] = 150.0;
		m_pKi[4] = 150.0;
		m_pKi[5] = 150.0;

		m_pKd[0] = 1.0;
		m_pKd[1] = 1.0;
		m_pKd[2] = 1.0;
		m_pKd[3] = 1.0;
		m_pKd[4] = 1.0;
		m_pKd[5] = 1.0;	
*/
	}
	
	else 
		return !S_OK;

	return S_OK;
}
///////////////////////////////////////////////////////////////////////////////////////////
// Inputs:	Desired Physcial Angles
//			Physical Angles
// Outputs:	Pressures (6)
//
// Function:By using a PID Controller and a Non-linear controller the pressuers 
//			of the arm are computed and passed on to the SampleIndPressure
//			component via a VectorSignal so the values are passed onto the hardware.
//			Note that each pair of pressure values should add up to 4000 which is the max
//			pressure value
///////////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CPID_NonLinController::PID_NonLin_6Press()
{
	// Variables
	long Index;
	SAFEARRAY* mysa;
	double derror, dvel, vel		= 0.0;
	double error,sign, dTempNonLin	= 0.0;

	double In[MAX_AXES];					// data buffer for Physical Angles
	double Des[MAX_AXES];					// data buffer for Desired Physical Angles
	double Out[MAX_AXES];					// data buffer for Pressure Output
	double TempPID[MAX_AXES];
	double PIn[MAX_AXES],PDes[MAX_AXES];    // data buffers for previous Phys Angles and Des Phys Angles


	for(Index=0; Index<MAX_AXES; Index++)
		In[Index]=Des[Index]=Out[Index]=TempPID[Index]=PIn[Index]=PDes[Index]=0.0;

	IVectorSignal *pIVSIn		= NULL;		// Vector signal for Physical Angles			(input)
	IVectorSignal *pIVSDes		= NULL;		// Vector signal for Desired Physical Angles	(input)
	IVectorSignal *pIVSOut		= NULL;		// Vector signal for Pressure Output			(output)
	IVectorSignal *pIVSPressBias= NULL;		// Vector signal for Pressure Bias
	

	// Get pointer to m_pIUnkInputState 
	m_Bindings->get_Pointers(SysAllocString(L"PhysicalAngles"),&m_pIUnkInputState);
	if(m_pIUnkInputState == NULL)	return E_POINTER;
	m_pIUnkInputState->QueryInterface(IID_IVectorSignal,(void**)&pIVSIn);

	// Get pointer to m_pIUnkOutput 
	m_Bindings->get_Pointers(SysAllocString(L"Pressures"),&m_pIUnkOutput);
	if(m_pIUnkOutput == NULL)	return E_POINTER;
	m_pIUnkOutput->QueryInterface(IID_IVectorSignal,(void**)&pIVSOut);

	// Get pointer to m_pIUnkDesiredState 
	m_Bindings->get_Pointers(SysAllocString(L"DesiredPhysicalAngles"),&m_pIUnkDesiredState);
	if(m_pIUnkDesiredState == NULL)	return E_POINTER;
	m_pIUnkDesiredState->QueryInterface(IID_IVectorSignal,(void**)&pIVSDes);

	// Get pointer to m_pIUnkBiasedPressureState 
	m_Bindings->get_Pointers(SysAllocString(L"PressureBiasVector"),&m_pIUnkBiasedPressureState);
	if(m_pIUnkBiasedPressureState == NULL)	return E_POINTER;
	m_pIUnkBiasedPressureState->QueryInterface(IID_IVectorSignal,(void**)&pIVSPressBias);


	if ((pIVSIn != NULL) && (pIVSOut != NULL) && (pIVSDes != NULL) && (pIVSPressBias != NULL))
	{
		ATLTRACE(_T("CPID Controller: All Bindings OK"));
		
		// Get the input data we need -- current and previous samples from
		// state and desired values through SAFEARRAYS.

		// Physical Angles
		mysa = SafeArrayCreateVector(VT_R8,0,m_Axes);
		pIVSIn->GetCurrentVector(mysa);		// Current sample
		memcpy(In,mysa->pvData,sizeof(double)*m_Axes); 
		pIVSIn->GetVector(1,mysa);			// Previous sample
		memcpy(PIn,mysa->pvData,sizeof(double)*m_Axes);

		// Desired Physical Angles
		pIVSDes->GetCurrentVector(mysa);		// Current sample
		memcpy(Des,mysa->pvData,sizeof(double)*m_Axes); 
		pIVSDes->GetVector(1,mysa);			// Previous sample
		memcpy(PDes,mysa->pvData,sizeof(double)*m_Axes);

		// Pressure Bias
		pIVSPressBias->GetCurrentVector(mysa);							// Read pressure bias to member variable
		memcpy(m_pBiasedPressure,mysa->pvData,sizeof(double)*m_Axes); 
		pIVSPressBias->SetCurrentVector(mysa);							// Not necessary to do this in IMA 2.5

		// Compute PID controller output

		// For each joint:
		for (Index = 0; Index < m_Axes ; Index++)
		{
			// Look at the actual error
			error = Des[Index] - In[Index];
	
			// Simplistic velocity calculations: could add filters later.
			vel = (In[Index] - PIn[Index]);
			dvel = (Des[Index] - PDes[Index]);
			derror = dvel - vel;	

			// Use current error in integrator but don't update integrator, yet.
			// NEW:
			TempPID[Index] = m_pKp[Index] * error  +
							 m_pKd[Index] * derror +
							 m_pKi[Index] * (m_pIntegrator[Index] + error);


			//  ************************************************
			//  This is the NONLINEAR CONTROLLER right here!!!!!
			//  ************************************************
			dTempNonLin= m_A0[Index] + (m_A1[Index]*Des[Index])
									 + (m_A2[Index]*(pow(Des[Index],2)))
									 + (m_A3[Index]*(pow(Des[Index],3)));


			TempPID[Index] += dTempNonLin;
			// Set the sign of change...
			if (error > 0.0f)
				sign = 1.0f;
			else
				sign = -1.0f;
	

			// Control integrator accumulation:
			// Smart PID clamp to make sure we head in the right direction.
			// Only integrate if total output is not clamped and we push away
			// from a clamped state.

			if (TempPID[Index] > m_pMaxClamp[Index])
			{
				//reduce integrator if error is neg and output is above MaxClamp
				if (error < 0.0f)
						m_pIntegrator[Index] += error;  
			
			}
			else if (TempPID[Index] < m_pMinClamp[Index])
			{
				//increase integrator if error is pos and output is below MinClamp
				if (error > 0.0f)
					m_pIntegrator[Index] += error;
			}
			else	
				m_pIntegrator[Index] += error;	// Normal integration
			 
			// Assign controller Outputs
			// NEW:
			Out[Index] = TempPID[Index];			

		}	// END FOR
	

			// Set the output data we computed: (send the 6 pressures to the agent)
			memcpy(mysa->pvData,Out,sizeof(double)*(m_Axes));
 			pIVSOut->SetCurrentVector(mysa); 
			// Destroy SafeArray
			SafeArrayDestroy(mysa);

			pIVSIn->Release();
			pIVSOut->Release();		// We're done with this pass through PID
			pIVSDes->Release();
			pIVSPressBias->Release();

			return S_OK;
	}	// END IF

	else 
	{
		ATLTRACE(_T("CPID Controller: Mechanism Bad connections."));
		if (pIVSIn != NULL)
			pIVSIn->Release();

		if (pIVSOut != NULL)
			pIVSOut->Release();

		if (pIVSDes != NULL)
			pIVSDes->Release();

		if (pIVSPressBias != NULL)
			pIVSPressBias->Release();

		return E_FAIL;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
// Inputs:	Desired Physcial Angles
//			Physical Angles
// Outputs:	Pressures (12)
//
// Function:By using a PID Controller and a Non-linear controller the pressures 
//			of the arm are computed and passed on to the SampleIndPressure
//			component via a VectorSignal so the values are passed onto the hardware.
//			Note that each pair of pressure values should add up to 4000 which is the max
//			pressure value
///////////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CPID_NonLinController::PID_NonLin_12Press()
{
	// TODO: Add your implementation code here
	// Variables
	long Index;
	SAFEARRAY* mysa;
	double derror, dvel, vel		= 0.0;
	double error,sign, dTempNonLin	= 0.0;

	double In[MAX_AXES];						// data buffer for Physical Angles
	double Des[MAX_AXES];						// data buffer for Desired Physical Angles
	double Out2[2*MAX_AXES+10];					// data buffer for Pressure Output
	double TempPID[MAX_AXES];
	double PIn[MAX_AXES],PDes[MAX_AXES];		// data buffers for previous Phys Angles and Des Phys Angles


	for(Index=0; Index<MAX_AXES; Index++)
		In[Index]=Des[Index]=TempPID[Index]=PIn[Index]=PDes[Index]=0.0;

	for(Index = 0; Index < (2*MAX_AXES+10); Index++)
		Out2[Index] = 0.0f;


	IVectorSignal *pIVSIn		= NULL;		// Vector signal for Physical Angles			(input)
	IVectorSignal *pIVSDes		= NULL;		// Vector signal for Desired Physical Angles	(input)
	IVectorSignal *pIVSOut		= NULL;		// Vector signal for Pressure Output			(output)
	IVectorSignal *pIVSPressBias= NULL;		// Vector signal for Pressure Bias
	

	// Get pointer to m_pIUnkInputState: Physical Angles
	m_Bindings->get_Pointers(SysAllocString(L"PhysicalAngles"),&m_pIUnkInputState);
	if(m_pIUnkInputState == NULL)	return E_POINTER;
	m_pIUnkInputState->QueryInterface(IID_IVectorSignal,(void**)&pIVSIn);

	// Get pointer to m_pIUnkOutput: Pressures
	m_Bindings->get_Pointers(SysAllocString(L"Pressures"),&m_pIUnkOutput);
	if(m_pIUnkOutput == NULL)	return E_POINTER;
	m_pIUnkOutput->QueryInterface(IID_IVectorSignal,(void**)&pIVSOut);

	// Get pointer to m_pIUnkDesiredState: Desired Physical Angles
	m_Bindings->get_Pointers(SysAllocString(L"DesiredPhysicalAngles"),&m_pIUnkDesiredState);
	if(m_pIUnkDesiredState == NULL)	return E_POINTER;
	m_pIUnkDesiredState->QueryInterface(IID_IVectorSignal,(void**)&pIVSDes);

	// Get pointer to m_pIUnkBiasedPressureState 
	m_Bindings->get_Pointers(SysAllocString(L"PressureBiasVector"),&m_pIUnkBiasedPressureState);
	if(m_pIUnkBiasedPressureState == NULL)	return E_POINTER;
	m_pIUnkBiasedPressureState->QueryInterface(IID_IVectorSignal,(void**)&pIVSPressBias);


	if ((pIVSIn != NULL) && (pIVSOut != NULL) && (pIVSDes != NULL) && (pIVSPressBias != NULL))
	{
		ATLTRACE(_T("CPID Controller: All Bindings OK"));
		
		// Get the input data we need -- current and previous samples from
		// state and desired values through SAFEARRAYS.

		// Physical Angles
		mysa = SafeArrayCreateVector(VT_R8,0,m_Axes);
		pIVSIn->GetCurrentVector(mysa);		// Current sample
		memcpy(In,mysa->pvData,sizeof(double)*m_Axes); 
		pIVSIn->GetVector(1,mysa);			// Previous sample
		memcpy(PIn,mysa->pvData,sizeof(double)*m_Axes);

		// Desired Physical Angles
		pIVSDes->GetCurrentVector(mysa);	// Current sample
		memcpy(Des,mysa->pvData,sizeof(double)*m_Axes); 
		pIVSDes->GetVector(1,mysa);			// Previous sample
		memcpy(PDes,mysa->pvData,sizeof(double)*m_Axes);

		// Pressure Bias
		pIVSPressBias->GetCurrentVector(mysa);							// Read pressure bias to member variable
		memcpy(m_pBiasedPressure,mysa->pvData,sizeof(double)*m_Axes); 
		pIVSPressBias->SetCurrentVector(mysa);							// Not necessary to do this in IMA 2.5
		// Destroy SafeArray
		SafeArrayDestroy(mysa);

		// Compute PID controller output
		// For each joint:
		for (Index = 0; Index < m_Axes ; Index++)
		{
			// e = Desired Theta - Actual Theta
			error	= Des[Index] - In[Index];
	
			// Velocity calculation used to find error_dot further down (Simplistic velocity calculations: could add filters later).
			vel		= (In[Index] - PIn[Index]);		// The difference between the current and previous physical angle input (theta)
			dvel	= (Des[Index] - PDes[Index]);	// The difference between the desired current and desired previous physical angle input (theta)

			// edot = DesiredTheta_dot-Theta_dot = (DesiredTheta-PreviousDesiredTheta) - (Theta-PreviousTheta)
			derror	= dvel - vel;				

			// Use current error in integrator but don't update integrator, yet.
			// NEW:
			TempPID[Index] = m_pKp[Index] * error  +							// Proportional:	Defines the output to be reached depending upon the input set-point value.
							 m_pKd[Index] * derror +							// Differential:	Sets the rate at which the arm responds to a set-point input.
							 m_pKi[Index] * (m_pIntegrator[Index] + error);		// Integral:		Attempts to drive the output to zero steady-state error.
	

			//  ************************************************
			//  This is the NONLINEAR CONTROLLER right here!!!!!
			//  ************************************************
			dTempNonLin= m_A0[Index] + (m_A1[Index]*Des[Index])
									 + (m_A2[Index]*(pow(Des[Index],2)))
									 + (m_A3[Index]*(pow(Des[Index],3)));


			TempPID[Index] += dTempNonLin;
			// Set the sign of change...
			if (error > 0.0f)
				sign = 1.0f;
			else
				sign = -1.0f;
	
			//////////////////////////////////////////////////////////////////////////////////////////
			// Control Integrator Accumulation:
			// Smart PID clamp to make sure we head in the right direction.
			// Only integrate if total output is NOT clamped and we push away from a clamped state.
			//////////////////////////////////////////////////////////////////////////////////////////

			// If PID Pressure is greater than the maximum possible pressure, then
			if (TempPID[Index] > m_pMaxClamp[Index])
			{
				// Reduce the integrator If: (1) error is neg AND (2) output is above MaxClamp
				if (error < 0.0f)
						m_pIntegrator[Index] += error;  
			
			}
			else if (TempPID[Index] < m_pMinClamp[Index])
			{
				// Increase integrator If: (1) error is pos And, (2) output is below MinClamp
				if (error > 0.0f)
					m_pIntegrator[Index] += error;
			}
			else	
				m_pIntegrator[Index] += error;	// Normal integration
			 
			// Assign controller Outputs
			
				// The if/else statements refer to the direction in which the arm is moving. 
				// This logic configuration was decided based at the beginning based on trials
				// in order for the arm to move adequately.
			
				// The even and odd joints need to move in different directions.
				// Reflecting the agonist/antagonist concept of the arm.
				if (m_bInvertPressure[Index] == TRUE) 
				{
					Out2[2*Index]   = m_pBiasedPressure[Index]  + TempPID[Index];	// Even-Agonist
					Out2[2*Index+1] = m_pBiasedPressure[Index]  - TempPID[Index];	// Odd -Antagonist
				}
				else
				{
					Out2[2*Index]   = m_pBiasedPressure[Index]  - TempPID[Index];
					Out2[2*Index+1] = m_pBiasedPressure[Index]  + TempPID[Index];
				}
			
				
			// Clamping Algorithm
			// Select the pressure in Out2 as long as it is less than 4000psi (max pressure for each rubbertuator)
 			Out2[2*Index]   = max(0.0,min(Out2[2*Index]  ,4000.0));
			Out2[2*Index+1] = max(0.0,min(Out2[2*Index+1],4000.0));
			
		}	// END FOR

			// Set the output data we computed: (send the 12 pressures to the agent)
			mysa = SafeArrayCreateVector(VT_R8,0,2*m_Axes);
			memcpy(mysa->pvData,Out2,sizeof(double)*(2*m_Axes));
 			pIVSOut->SetCurrentVector(mysa); 
			// Destroy SafeArray
			SafeArrayDestroy(mysa);

			pIVSIn->Release();
			pIVSOut->Release();		// We're done with this pass through PID
			pIVSDes->Release();
			pIVSPressBias->Release();
			return S_OK;
	
	}// END IF

	else	// We don't have all the right connections so release and signal error.
	{
		ATLTRACE(_T("CPID Controller: Mechanism Bad connections."));
		if (pIVSIn != NULL)
			pIVSIn->Release();

		if (pIVSOut != NULL)
			pIVSOut->Release();

		if (pIVSDes != NULL)
			pIVSDes->Release();

		if (pIVSPressBias != NULL)
			pIVSPressBias->Release();

		return E_FAIL;
	}	
}


STDMETHODIMP CPID_NonLinController::Read_CurrentPressure()
{
	// TODO: Add your implementation code here
	SAFEARRAY* mysa;
	IVectorSignal *pIVSOut	= NULL;		// Vector signal for Pressure Output

	// Get pointer to the Pressure Vector Signal and to its interface
	m_Bindings->get_Pointers(SysAllocString(L"Pressures"),&m_pIUnkOutput);
	if(m_pIUnkOutput == NULL)	return E_POINTER;
	m_pIUnkOutput->QueryInterface(IID_IVectorSignal,(void**)&pIVSOut);

	if(pIVSOut != NULL)
	{
		// Get the Pressure values
		mysa=SafeArrayCreateVector(VT_R8,0,2*m_Axes);
		pIVSOut->GetCurrentVector(mysa); 
		memcpy(m_pCurrentPressures, mysa->pvData,sizeof(double)*2*m_Axes);

		// Destroy SafeArray
		SafeArrayDestroy(mysa);		    

		pIVSOut->Release();
		return S_OK;
	}

	else
	{
		ATLTRACE(_T("CPID Controller: Mechanism Bad connections."));

		if (pIVSOut != NULL)
			pIVSOut->Release();
	
		return E_FAIL;
	}
}


