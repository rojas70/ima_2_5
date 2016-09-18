// StepFilter.cpp : Implementation of CStepFilter
#include "stdafx.h"
#include "IMA2_ArmTools.h"
#include "StepFilter.h"
#include "O:\Include\IMA2_BasicComponentsLib.h"

/////////////////////////////////////////////////////////////////////////////
// CStepFilter
/*//////////////////////////////////////////////////////////////////////////////////////////////
	IIR (Infinite Impulse Response) Filter with parameters Alpha[joint].
	This filter is considered a first-order IIR low-pass digital filter.
	It cuts of high frequency signals.
		
	Alpha is the weight of the old joint angle, 1-Alpha is the 
	weight of the desired joint angle 
		
	Input - Desired Logical Angles
	Output - Filtered Desired Logical Angles
	FilteredDesiredJointAngle = Alpha*OldFilteredDesiredAngle + (1-Alpha)*DesiredJointAngle
//////////////////////////////////////////////////////////////////////////////////////////////*/



STDMETHODIMP CStepFilter::get_AlphaIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if (m_sAlphaIndex > -1 && m_sAlphaIndex < NUM_AXES)
		*pVal = m_sAlphaIndex;
	return S_OK;
}

STDMETHODIMP CStepFilter::put_AlphaIndex(short newVal)
{
	// TODO: Add your implementation code here
	if (m_sAlphaIndex > -1 && m_sAlphaIndex < NUM_AXES)
		m_sAlphaIndex = newVal;
	return S_OK;
}


STDMETHODIMP CStepFilter::get_alpha(double * pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_pdAlpha[m_sAlphaIndex];
	
	return S_OK;
}

STDMETHODIMP CStepFilter::put_alpha(double newVal)
{
	// TODO: Add your implementation code here
	m_pdAlpha[m_sAlphaIndex] = newVal;
	
	return S_OK;
}


/*//////////////////////////////////////////////////////////////////////////////////////////////
	IIR (Infinite Impulse Response) Filter with parameters Alpha[joint].
	This filter is considered a first-order IIR low-pass digital filter.
		
	Alpha is the weight of the old joint angle, 1-Alpha is the 
	weight of the desired joint angle 
		
	Input - Desired Logical Angles
	Output - Filtered Desired Logical Angles
	FilteredDesiredJointAngle = Alpha*OldFilteredDesiredAngle + (1-Alpha)*DesiredJointAngle
//////////////////////////////////////////////////////////////////////////////////////////////*/
STDMETHODIMP CStepFilter::FilterDesiredAngles()
{
	// TODO: Implement the operations that this component supports.
	int i;
	double FilteredDesiredJointAngle[NUM_AXES],DesiredJointAngle[NUM_AXES],OldFilteredDesiredAngle[NUM_AXES];
	SAFEARRAY *mysa;
 
	IVectorSignal *pIVSOut=NULL;
	IVectorSignal *pIVSIn=NULL;

	// Get pointer to object and interface 
	m_Bindings->get_Pointers(SysAllocString(L"DesiredLogicalAngles"), &m_pIUnkVectorIn);				// DesiredLogicalAngles
	m_Bindings->get_Pointers(SysAllocString(L"FilteredDesiredLogicalAngles"), &m_pIUnkVectorOut);		// FilteredDesiredLogicalAngles

	if(m_pIUnkVectorOut != NULL && m_pIUnkVectorIn != NULL)
	{
		m_pIUnkVectorIn->QueryInterface(IID_IVectorSignal,(void **)&pIVSIn);
		m_pIUnkVectorOut->QueryInterface(IID_IVectorSignal,(void **)&pIVSOut);

		if(pIVSIn != NULL && pIVSOut != NULL)
		{
			mysa = SafeArrayCreateVector(VT_R8,0,NUM_AXES);
			pIVSIn->GetCurrentVector(mysa);
			memcpy(DesiredJointAngle, mysa->pvData, sizeof(double)*NUM_AXES);
			
			pIVSOut->GetCurrentVector(mysa);
			memcpy(OldFilteredDesiredAngle, mysa->pvData, sizeof(double)*NUM_AXES);


			// The following equations works as an averaging equation.
			// If alpha = 1, the previous copy of the data is used.
			// If alpha = 0, the actual copy of the data is used.
			// If alpha = 0.5 an average of both groups of data is used.
			// So on.
			for(i=0;i<NUM_AXES;i++)
				FilteredDesiredJointAngle[i] = m_pdAlpha[i]*OldFilteredDesiredAngle[i] + (1-m_pdAlpha[i])*DesiredJointAngle[i];
			
			memcpy(mysa->pvData, FilteredDesiredJointAngle, sizeof(double)*NUM_AXES);
			pIVSOut->SetCurrentVector(mysa);

			// Destroy SafeArray
			SafeArrayDestroy(mysa);

			pIVSIn->Release();
			pIVSOut->Release();
		}
	}
	else
	{
		if (pIVSIn != NULL)
			pIVSIn->Release();

		if (pIVSOut != NULL)
			pIVSOut->Release();
		
		ATLTRACE(_T("CSampIndPressure::Sample Failure!"));
		return S_OK;					// Fail/end.
	}
	return S_OK;
}

STDMETHODIMP CStepFilter::OnConstruct() {

// TODO: Bindings. Personalize the binding of your component. 

	int numiids;
	IMA2_BindingInfo BindInf;
	numiids=1;

	// 1. AngleSpeed
	BindInf.Name		= SysAllocString(L"DesiredLogicalAngles");			// Assign name to object
	BindInf.BindType	= BT_Collection;									// Condition to accept multiple targets
	BindInf.Path		= SysAllocString(L"");								// This must be the path of our component
	BindInf.PIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);		// Create and empty string array
	BindInf.IIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);		// Create and empty string array
	m_ConfigureBindings->Add(&BindInf);									// Set up the clients bindings array.	

	// 2. Alpha
	BindInf.Name		= SysAllocString(L"FilteredDesiredLogicalAngles");					
	m_ConfigureBindings->Add(&BindInf);
	
	// Deallocate storage
	SysFreeString(BindInf.Name);
	SysFreeString(BindInf.Path);
	SafeArrayDestroy(BindInf.PIDs);
	SafeArrayDestroy(BindInf.IIDs);
	
	return S_OK;
}

STDMETHODIMP CStepFilter::OnDestruct() {	return S_OK; }

//////////////////////////////
// Load values of saved data
//////////////////////////////
STDMETHODIMP CStepFilter::Load(VARIANT Data) 
{
	
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

		// Variable m_pdAlpha
		// Define strings
		ItemName	= SysAllocString(L"Alpha");
		Var			= new variant_t;
		// Read Data from the property bag
		pIPB->GetArrayFromPropertyBag(&ItemName,Var);  //2nd argument is return value (look retval for help)
		memcpy(m_pdAlpha, Var->parray->pvData, sizeof(double)*NUM_AXES);
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Decrement the pointer reference count from our member variable. 
		VariantClear(&m_VBPropertyBag);
		
		// Release
		pIPB->Release();

	return S_OK;
}

STDMETHODIMP CStepFilter::Save(VARIANT * pData)
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

	// m_pdAlpha
	ItemName = SysAllocString(L"Alpha");
	// Store the data and the type of data into a variant_t type
	ItemValue = new variant_t;
	ItemValue->vt = VT_ARRAY|VT_R8;
	ItemValue->parray=SafeArrayCreateVector(VT_R8,0,NUM_AXES);
	memcpy(ItemValue->parray->pvData,m_pdAlpha,NUM_AXES*sizeof(double));
	// Add an item to the property bag via the wrapper class.
	hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
	// Free the strings memory location
	SysFreeString(ItemName);
	// Destroy SafeArray
//	SafeArrayDestroy(ItemValue->parray);
	// Delete ItemValue
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


