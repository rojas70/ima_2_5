// CopyVS.cpp : Implementation of CCopyVS
#include "stdafx.h"
#include "IMA2_CopyRepsLib.h"
#include "CopyVS.h"

/////////////////////////////////////////////////////////////////////////////
// CCopyVS

///////////////////////////////////////////////////////////////////
// Load data from file through data saved to the PropertyBag in VB
///////////////////////////////////////////////////////////////////
STDMETHODIMP CCopyVS::Load(VARIANT Data) {
	
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

		// Variable m_sInputRowVector
		// Define strings
		ItemName		= SysAllocString(L"InputRowVector");
		ItemValue		= new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		m_sInputRowVector= (short)*ItemValue;
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_sOutputRowVector
		// Define strings
		ItemName		= SysAllocString(L"OutputRowVector");
		ItemValue		= new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		m_sOutputRowVector= (short)*ItemValue;
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Decrement the pointer reference count from our member variable. 
		VariantClear(&m_VBPropertyBag);
		
		// Release
		pIPB->Release();
		
return S_OK;
}


////////////////////////////////////////////////////////////////////////
// Called by the framework to serialize the component to binary sotrage 
// in a file.
////////////////////////////////////////////////////////////////////////
STDMETHODIMP CCopyVS::Save(VARIANT *pData) {

	// Variables
	BSTR					ItemName = NULL;// The string holding the name of the item to write into the property bag.
	variant_t				*ItemValue;
	_PropertyBagWrapper		*pIPB;			// COM Interface Pointer to the PropertyBag _Wrapper_ Class
	HRESULT					hRes;			// The HRESULT value we get back from COM calls.

	// (1) Create the property bag wrapper class
	// (2) Have the class point to the interface 
	hRes = CoCreateInstance(CLSID_PropertyBagWrapper, NULL, CLSCTX_INPROC_SERVER, IID__PropertyBagWrapper, (LPVOID*)&pIPB);

		if (pIPB == NULL)	
			return !S_OK;
		
		// m_sInputRowVector
		// Create string names for items to be saved
		ItemName = SysAllocString(L"InputRowVector");
		// Store the data and the type of data into a variant_t type
 		ItemValue = new variant_t(m_sInputRowVector,VT_I2);
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Delete our variants
		delete ItemValue;

		// m_sOutputRowVector
		ItemName = SysAllocString(L"OutputRowVector");
		// Store the data and the type of data into a variant_t type
		ItemValue = new variant_t(m_sOutputRowVector, VT_I2);
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
STDMETHODIMP CCopyVS::CopyVectorSignal(/*ULONG operation, ULONG flags*/)
{
	// TODO: Add your implementation code here
	int		i;
	long	lInLen=0,lOutLen=0;
	long	lQueueLen;
	SAFEARRAY* mysa;
	IVectorSignal *pIVSIn, *pIVSOut;

// Temporary variable to test the component while we fix DAD. Juan Rojas 3/30/05
/* Mechanism works by copying vector in input component link at index operation to vector in output component link VS at index
flags.  These component links hold up to 10 vectors each.*/

/* Adding mechanism that will copy entire vector signal (all QueueLength of them) from the 
VS pointed at by input link at 0 and write it to output link at 0. */

	// Retrieve pointer of Input VS
	m_Bindings->get_Pointers(SysAllocString(L"InputVS"),&m_pIUnkIn);
	m_Bindings->get_Pointers(SysAllocString(L"OutputVS"),&m_pIUnkOut);

	if(	m_pIUnkIn==NULL ||	m_pIUnkOut==NULL)
		return E_POINTER;

	m_pIUnkIn->QueryInterface(IID_IVectorSignal,(void**)&pIVSIn);
	m_pIUnkOut->QueryInterface(IID_IVectorSignal,(void**)&pIVSOut);
	//CComQIPtr< IVectorSignal, &IID_IVectorSignal > pIVSIn(m_pIUnkIn);
	//CComQIPtr< IVectorSignal, &IID_IVectorSignal > pIVSOut(m_pIUnkOut);

	if(pIVSIn == NULL || pIVSOut == NULL)
		return -1;

	pIVSIn->get_VectorLength(&lInLen);
	pIVSOut->get_VectorLength(&lOutLen);
	
	pIVSIn->get_SignalLength(&lQueueLen);
	pIVSOut->put_SignalLength(lQueueLen);
	
	if (lInLen > lOutLen)
		pIVSOut->put_VectorLength(lInLen);

	mysa=SafeArrayCreateVector(VT_R8,0,lInLen);
	for(i=0; i<lQueueLen; i++)
	{
		pIVSIn->GetVector(i, mysa);
		pIVSOut->SetVector(i, mysa);
	}
	SafeArrayDestroy(mysa);

	pIVSOut->put_Index(0);

	return S_OK;
}


STDMETHODIMP CCopyVS::CopyRowVector()
{
	long	lInLen=0,lOutLen=0;
	long	lQueueLen;
	SAFEARRAY* mysa;
	IVectorSignal *pIVSIn, *pIVSOut;

	// Retrieve pointer of Input VS
	m_Bindings->get_Pointers(SysAllocString(L"InputVS"),&m_pIUnkIn);
	m_Bindings->get_Pointers(SysAllocString(L"OutputVS"),&m_pIUnkOut);

	if(	m_pIUnkIn==NULL ||	m_pIUnkOut==NULL)
		return E_POINTER;

	m_pIUnkIn->QueryInterface(IID_IVectorSignal,(void**)&pIVSIn);
	m_pIUnkOut->QueryInterface(IID_IVectorSignal,(void**)&pIVSOut);

	if(pIVSIn == NULL || pIVSOut == NULL)
		return -1;

	pIVSIn->get_VectorLength(&lInLen);
	pIVSOut->get_VectorLength(&lOutLen);
	
	pIVSIn->get_SignalLength(&lQueueLen);
	pIVSOut->put_SignalLength(lQueueLen);
	
	if (lInLen > lOutLen)
		pIVSOut->put_VectorLength(lInLen);

	mysa=SafeArrayCreateVector(VT_R8,0,lInLen);
	pIVSIn->GetVector(m_sInputRowVector, mysa);
	pIVSOut->SetVector(m_sOutputRowVector, mysa);
	SafeArrayDestroy(mysa);

	return S_OK;
}

//*****************************************************************************************
// Do all bindings
//
//	Author: Juan Rojas
//	Date:  August 2004
//*****************************************************************************************
STDMETHODIMP CCopyVS::OnConstruct()
{
// TODO: Bindings. Personalize the binding of your component. 

// Input Binding
	SAFEARRAYBOUND		SafeArrayBoundIn[1];									// We're making a one-dimensional SafeArray
	long x[1];


	SafeArrayBoundIn[0].lLbound	= 0;											// Our SafeArray starts at index 0
	SafeArrayBoundIn[0].cElements = 1;											// It's empty, doesn't have any elements yet.

	m_BindingInput.Name		= SysAllocString(L"InputVS");						// Assign name to object
	m_BindingInput.BindType	= BT_Default;										// Condition to accept a single binding
	m_BindingInput.Path		= SysAllocString(L"");								// This is the path of the component you are connecting to
	m_BindingInput.PIDs		= SafeArrayCreate(VT_BSTR, 1, SafeArrayBoundIn);	// Create and empty string array
	m_BindingInput.IIDs		= SafeArrayCreate(VT_BSTR, 1, SafeArrayBoundIn);	// Create and empty string array
	x[0]=0; //specifies first element
	SafeArrayPutElement(m_BindingInput.PIDs,x,(void *)SysAllocString(L"IMA2_BasicComponentsLib.VectorSignal"));
	SafeArrayPutElement(m_BindingInput.IIDs,x,(void *)SysAllocString(L"IVectorSignal"));

	m_ConfigureBindings->Add(&m_BindingInput);									// Set up the clients bindings array.	

// Output Binding 
	SAFEARRAYBOUND		SafeArrayBoundOut[1];									// We're making a one-dimensional SafeArray

	SafeArrayBoundOut[0].lLbound	= 0;										// Our SafeArray starts at index 0
	SafeArrayBoundOut[0].cElements = 1;											// It's empty, doesn't have any elements yet.

	m_BindingOutput.Name		= SysAllocString(L"OutputVS");					// Assign name to object
	m_BindingOutput.BindType	= BT_Default;									// Condition to accept a single binding
	m_BindingOutput.Path		= SysAllocString(L"");							// This is the path of the component you are connecting to
	m_BindingOutput.PIDs		= SafeArrayCreate(VT_BSTR, 1, SafeArrayBoundOut);// Create and empty string array
	m_BindingOutput.IIDs		= SafeArrayCreate(VT_BSTR, 1, SafeArrayBoundOut);// Create and empty string array
	SafeArrayPutElement(m_BindingOutput.PIDs,x,(void *)SysAllocString(L"IMA2_BasicComponentsLib.VectorSignal"));
	SafeArrayPutElement(m_BindingOutput.IIDs,x,(void *)SysAllocString(L"IVectorSignal"));

	m_ConfigureBindings->Add(&m_BindingOutput);									// Set up the clients bindings array.

	return S_OK;
}

STDMETHODIMP CCopyVS::OnDestruct()
{
	SysFreeString(m_BindingOutput.Name);
	SysFreeString(m_BindingOutput.Path);
	SafeArrayDestroy(m_BindingOutput.PIDs);
	SafeArrayDestroy(m_BindingOutput.IIDs);

	SysFreeString(m_BindingInput.Name);
	SysFreeString(m_BindingInput.Path);
	SafeArrayDestroy(m_BindingInput.PIDs);
	SafeArrayDestroy(m_BindingInput.IIDs);

	return S_OK;
}

STDMETHODIMP CCopyVS::get_InputRowVector(short *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_sInputRowVector;
	return S_OK;
}

STDMETHODIMP CCopyVS::put_InputRowVector(short newVal)
{
	// TODO: Add your implementation code here
	if (newVal >= 0)
		m_sInputRowVector = newVal;
	return S_OK;
}

STDMETHODIMP CCopyVS::get_OutputRowVector(short *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_sOutputRowVector;

	return S_OK;
}

STDMETHODIMP CCopyVS::put_OutputRowVector(short newVal)
{
	// TODO: Add your implementation code here
	if (newVal >= 0)
		m_sOutputRowVector = newVal;

	return S_OK;
}

STDMETHODIMP CCopyVS::CopyCurrentVector()
{
	// TODO: Add your implementation code here
	long	lInLen=0,lOutLen=0;
	long	lQueueLen;
	SAFEARRAY* mysa;
	IVectorSignal *pIVSIn, *pIVSOut;

	// Retrieve pointer of Input VS
	m_Bindings->get_Pointers(SysAllocString(L"InputVS"),&m_pIUnkIn);
	m_Bindings->get_Pointers(SysAllocString(L"OutputVS"),&m_pIUnkOut);

	if(	m_pIUnkIn==NULL ||	m_pIUnkOut==NULL)
		return E_POINTER;

	m_pIUnkIn->QueryInterface(IID_IVectorSignal,(void**)&pIVSIn);
	m_pIUnkOut->QueryInterface(IID_IVectorSignal,(void**)&pIVSOut);

	if(pIVSIn == NULL || pIVSOut == NULL)
		return -1;

	pIVSIn->get_VectorLength(&lInLen);
	pIVSOut->get_VectorLength(&lOutLen);
	
	pIVSIn->get_SignalLength(&lQueueLen);
	pIVSOut->put_SignalLength(lQueueLen);
	
	if (lInLen > lOutLen)
		pIVSOut->put_VectorLength(lInLen);

	mysa=SafeArrayCreateVector(VT_R8,0,lInLen);
	pIVSIn->GetCurrentVector(mysa);
	pIVSOut->SetCurrentVector(mysa);
	SafeArrayDestroy(mysa);

	return S_OK;
}
