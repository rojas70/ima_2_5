// TextQueue.cpp : Implementation of CTextQueue
#include "stdafx.h"
#include "IMA2_TextQueueLib.h"
#include "TextQueue.h"

/////////////////////////////////////////////////////////////////////////////
// CTextQueue
/////////////////////////////////////////////////////////////////////

/*
TextQueue Documentation
Overview
The TextQueue Component is a representation that holds text string data to be shared or passed between components. The 

Properties
DataPersistent
Description: long:This property is a flag that will allow data to be saved with the agent if set to nonzero.

AgentEventID
Description: long: Specifies Agent Event to be triggered when the data is updated

AgentEventType
Description: long: Specifies the type of the AgentEvent to be fired

UpdateAgentEventFlag
Description: long: If flag is true(1), an agent event is thrown when the text is updated.

CurrentIndex
Description: long: The current value of the text pointer index.

CurrentText
Description: BSTR: Property that holds the current text string.

QueueLength
Description: long: The number of strings in the queue.

Methods
SetText
Description: Sets text at a particular index, index. Use this if you need to access particular indices.

Parameters: 

long index 
BSTR text 

GetText
Description: Retrieves text at a particular index. Use this if you need to access particular indices.
Parameters: 
long index 
BSTR *text 
double *pdTime 

SetCurrentText
Description: Sets text at the current index. The index does not change. If text is in the current index, that text is written over.
Parameters: 
BSTR text 

GetCurrentText
Description: Retrieves current text. Note, the index is not updated.
Parameters: 
double* pdTime 
BSTR *text 

FireAgentEvent
Description: 
Parameters: 
long Type 
long ID 

UpdateData
Description: 
Parameters: 
long lbUpdPrx 

Test1
Description: 
Parameters: 
long a 
long b 
*/


/////////////////////////////////////////////////////////////////////
// The OnConstruct Function sets all the bindings for the component
/////////////////////////////////////////////////////////////////////
STDMETHODIMP CTextQueue::OnConstruct() {

// TODO: Bindings. Personalize the binding of your component. 

	int numiids;
	IMA2_BindingInfo BindInf;
	numiids=1;

	// 1. State Machine
	BindInf.Name		= SysAllocString(L"State Machine");				// Assign name to object
	BindInf.BindType	= BT_Collection;									// Condition to accept multiple targets
	BindInf.Path		= SysAllocString(L"");								// This must be the path of our component
	BindInf.PIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);		// Create and empty string array
	BindInf.IIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);		// Create and empty string array
	m_ConfigureBindings->Add(&BindInf);										// Set up the clients bindings array.	
	
	// Deallocate storage
	SysFreeString(BindInf.Name);
	SysFreeString(BindInf.Path);
	SafeArrayDestroy(BindInf.PIDs);
	SafeArrayDestroy(BindInf.IIDs);
	
	return S_OK;
}

STDMETHODIMP CTextQueue::OnDestruct() {	return S_OK; }

//////////////////////////////
// Load values of saved data
//////////////////////////////
STDMETHODIMP CTextQueue::Load(VARIANT Data) {
	
	// Variables
	int i;
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

		// Variable m_lQueueLength
		// Define strings
		ItemName	= SysAllocString(L"QueueLength");
		ItemValue			= new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		m_lQueueLength		= (long)*ItemValue;
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_lThrowEvent
		// Define strings
		ItemName	= SysAllocString(L"ThrowEvent");
		ItemValue			= new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		m_lThrowEvent		= (long)*ItemValue;
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// m_lSaveData
		ItemName	= SysAllocString(L"SaveData");
		ItemValue			= new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		m_lSaveData			= (long)*ItemValue;
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_textData
		if(m_lSaveData == 1)
		{
			for(i=0;i<MAX_Q_LEN;i++)
			{
				ItemName	= SysAllocString(L"TextData[i]");
				ItemValue	= new variant_t;
				pIPB->GetFromPropertyBag(&ItemName,ItemValue);	//2nd argument is return value (look retval for help)
				SysReAllocString(&m_textData[i],ItemValue->bstrVal);//parray?
			}
			// Deallocate
			SysFreeString(ItemName);
			delete ItemValue;
		}

		// Decrement the pointer reference count from our member variable. 
		VariantClear(&m_VBPropertyBag);
		
		// Release
		pIPB->Release();

	return S_OK;

}

//////////////////////
// Saved properties
//////////////////////
STDMETHODIMP CTextQueue::Save(VARIANT *pData) {
	
	// Variables
	int i;
	BSTR					ItemName = NULL;// The string holding the name of the item to write into the property bag.
	variant_t				*ItemValue;
	_PropertyBagWrapper		*pIPB;			// COM Interface Pointer to the PropertyBag _Wrapper_ Class
	HRESULT					hRes;			// The HRESULT value we get back from COM calls.

	// (1) Create the property bag wrapper class
	// (2) Have the class point to the interface 
	hRes = CoCreateInstance(CLSID_PropertyBagWrapper, NULL, CLSCTX_INPROC_SERVER, IID__PropertyBagWrapper, (LPVOID*)&pIPB);

		if (pIPB == NULL)	
			return !S_OK;
		
		// m_lQueueLength
		ItemName = SysAllocString(L"QueueLength");
		// Store the data and the type of data into a variant_t type
		ItemValue = new variant_t(m_lQueueLength, VT_I4);
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Delete our variants
		delete ItemValue;

		// m_lThrowEvent
		ItemName = SysAllocString(L"ThrowEvent");
		// Store the data and the type of data into a variant_t type
		ItemValue = new variant_t(m_lThrowEvent, VT_I4);
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Delete our variants
		delete ItemValue;

		// m_lSaveData
		ItemName = SysAllocString(L"SaveData");
		// Store the data and the type of data into a variant_t type
		ItemValue = new variant_t(m_lSaveData, VT_I4);
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Delete our variants
		delete ItemValue;

	// If we want to save the text info
	if(m_lSaveData == 1)
	{
		// m_TextData
		for (i=0;i<MAX_Q_LEN;i++)
		{
			ItemName = SysAllocString(L"TextData[i]");
			// Store the data and the type of data into a variant_t type
 			ItemValue = new variant_t((BSTR)m_textData[i]);						
			//ItemValue->parray=SafeArrayCreateVector(VT_BSTR,0,MAX_Q_LEN);
			memcpy(ItemValue->parray,m_textData[i],sizeof(BSTR));
			// Add an item to the property bag via the wrapper class.
			hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		}
		// Free the strings memory location
		SysFreeString(ItemName);
		// Destroy ItemValue
		delete ItemValue;	
	}
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

STDMETHODIMP CTextQueue::get_StringIndex(long *pVal)
{
	// TODO: Add your implementation code here
	if (pVal != NULL)
		*pVal = m_lStringIndex;
	return S_OK;
}

STDMETHODIMP CTextQueue::put_StringIndex(long newVal)
{
	// TODO: Add your implementation code here
	if (newVal>= 0)
		m_lStringIndex = newVal;

	return S_OK;
}

STDMETHODIMP CTextQueue::get_CurrentText(BSTR *pVal)
{
	// TODO: Add your implementation code here
	*pVal = SysAllocString(m_textData[m_lStringIndex]);
	ATLTRACE("Got text\n");

	return S_OK;
}

STDMETHODIMP CTextQueue::put_CurrentText(BSTR newVal)
{
	// TODO: Add your implementation code here
	SysReAllocString(&m_textData[m_lStringIndex],newVal);
	ATLTRACE("Put text\n");

	return S_OK;
}

STDMETHODIMP CTextQueue::get_QueueLength(long *pVal)
{
	// TODO: Add your implementation code here
	if (pVal != NULL)
		*pVal = m_lQueueLength;
	return S_OK;
}

STDMETHODIMP CTextQueue::put_QueueLength(long newVal)
{
	// TODO: Add your implementation code here
	// Can't take a size of 0
	if(newVal <= 0)
		newVal = 1;

	// Use the remainder to assign length
	m_lQueueLength = newVal % MAX_Q_LEN;

	// If remainder is 0, use MAX_Q_LEN
	if (m_lQueueLength==0)
		m_lQueueLength = MAX_Q_LEN;

	return S_OK;
}

STDMETHODIMP CTextQueue::get_ThrowEvent(long *pVal)
{
	// TODO: Add your implementation code here
	if(pVal != NULL)
		*pVal = m_lThrowEvent;
	return S_OK;
}

STDMETHODIMP CTextQueue::put_ThrowEvent(long newVal)
{
	// TODO: Add your implementation code here
	if((newVal == 0) || (newVal == 1))
		m_lThrowEvent = newVal;
	return S_OK;
}

STDMETHODIMP CTextQueue::get_SaveData(long *pVal)
{
	// TODO: Add your implementation code here
	if (pVal != NULL)
		*pVal = m_lSaveData;
	return S_OK;
}

STDMETHODIMP CTextQueue::put_SaveData(long newVal)
{
	// TODO: Add your implementation code here
	if((newVal == 0) || (newVal == 1))
		m_lSaveData = newVal;

	return S_OK;
}


STDMETHODIMP CTextQueue::GetText(long index, BSTR *text)
{
	// TODO: Add your implementation code here

	// Local Variables
	long lTemp;
	USES_CONVERSION;

	// Lock the data
	Lock();


	if (m_lStringIndex == 0 && m_lSaveData == 0)
		lTemp= m_lQueueLength;
	else if (m_lStringIndex == 0 && m_lSaveData == 1)
		lTemp = m_lStringIndex + 1;
	else
		lTemp = m_lStringIndex - 1;

	if (index != 0 && index != m_lQueueLength)
		index = (index + m_lQueueLength) % m_lQueueLength;

	if (m_textData != NULL)
	{
//		ATLTRACE("CTextQueue::GetText--returning Q[%d] = %s\n",index,m_textData[index]);
		SysReAllocString(&(*text),m_textData[index]);
		Unlock();
		return S_OK;
	}

	Unlock();

	ATLTRACE(_T("Had No Data!!!\n"));
	return S_OK;
}

STDMETHODIMP CTextQueue::SetText(long index, BSTR text)
{
	// TODO: Add your implementation code here
	USES_CONVERSION;

	if (index != 0 && index != m_lQueueLength)
		index = (index + m_lQueueLength) % m_lQueueLength;

	
	if (m_textData != NULL)
	{

		Lock();
		if (index < m_lQueueLength)
			m_textData[index] = SysAllocString(text);

		Unlock();

		return S_OK;
	}	
	
	return E_FAIL;
}

STDMETHODIMP CTextQueue::GetCurrentText(BSTR *text)
{
	// TODO: Add your implementation code here
	USES_CONVERSION;

	ATLTRACE("CTextQueue::GetCurrentText: %s", OLE2T(m_textData[m_lStringIndex]));
	if (m_textData[m_lStringIndex] != NULL)
	{
		Lock();
		SysReAllocString(&(*text),m_textData[m_lStringIndex]);

		Unlock();
		return S_OK;
	}
	else
		return E_FAIL;


	ATLTRACE(_T("Had No Data!!!\n"));
}

STDMETHODIMP CTextQueue::SetCurrentText(BSTR text)
{
	// TODO: Add your implementation code here
	USES_CONVERSION;

	if (m_textData != NULL)
	{
		Lock();

		m_lStringIndex++;		
		m_lStringIndex %= m_lQueueLength;
		
		if(m_textData[m_lStringIndex]!=NULL)
			m_textData[m_lStringIndex] = SysAllocString(text);
		
		
		Unlock();

		return S_OK;
	}	

	return E_FAIL;
}

STDMETHODIMP CTextQueue::UpdateManager(BSTR Interface, VARIANT *Data)
{
	// TODO: Add your implementation code here
	USES_CONVERSION;
	int i;
	long index[1];
	VARIANT *arrayptr;

	Lock();
	
	// If we have an ITextQueue interface
	if(strcmp(OLE2T(Interface),"ITextQueue")==0)
	{
		// Set type to an array of type VARIANT
		Data->vt=VT_ARRAY|VT_VARIANT;

		// Create a vector of type VARIANT and size 4
		Data->parray=SafeArrayCreateVector(VT_VARIANT,0,4);

		// Pass SafeArrayVector to arrayptr.
		arrayptr=(VARIANT*)Data->parray->pvData;
		
		// Set type
		arrayptr[0].vt=VT_I4;
		// Set value for long
		arrayptr[0].lVal=m_lQueueLength;		// Queue Length

		// Set type of next element as double array
		arrayptr[1].vt=VT_ARRAY|VT_BSTR;
		
		// Create vector 
		arrayptr[1].parray=SafeArrayCreateVector(VT_BSTR,2,m_lQueueLength);

		for(i=0;i<m_lQueueLength;i++)
		{
			index[0] = i;
			SafeArrayPutElement(arrayptr[1].parray,index,&(m_textData[i]));
		}
	}

	Unlock();
	return S_OK;
}





