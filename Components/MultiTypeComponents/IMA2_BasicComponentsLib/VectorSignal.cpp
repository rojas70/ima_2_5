// VectorSignal.cpp : Implementation of CVectorSignal
#include "stdafx.h"
#include "IMA2_BasicComponentsLib.h"
#include "VectorSignal.h"

/////////////////////////////////////////////////////////////////////////////
// CVectorSignal
//
// The most important data component in the IMA 2.5 architecture!
//
// Data structure that looks as:
//
//					Vector						Vector 
//					  Len		........		  Len				
//					   1						   20
// Signal Length	1	
//		.
//		.
//		.
// Signal Length	10			........		   20
//
// 
// You can identify the position of data, by the (Row Vector, Index) position. 
// The parameters Signal Lenth, and Vector Length can be modified at run time
// but are initialized to value of 10 and 20 respectively.
// 
// There are four main interface methods:
// 1) GetVector			- gets the complete data set: i.e. 10x20
// 2) SetVector			- sets the complete data set
// 3) GetCurrentVector	- get the row vector indicated
// 4) SetCurrentVector	- sets the row vector indicated
////////////////////////////////////////////////////////////////////////////


STDMETHODIMP CVectorSignal::get_Index(long *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_lIndex;
	return S_OK;
}

STDMETHODIMP CVectorSignal::put_Index(long newVal)
{
	// TODO: Add your implementation code here
	m_lIndex = newVal;
	return S_OK;
}

STDMETHODIMP CVectorSignal::get_IndexValue(double *pVal)
{
	// TODO: Add your implementation code here
	if (pVal == NULL)	return E_POINTER;

	if (m_lIndex < m_lVectorLength)	
		*pVal = m_vecData[m_lRowVector][m_lIndex];

	return S_OK;
}

STDMETHODIMP CVectorSignal::put_IndexValue(double newVal)
{
	// TODO: Add your implementation code here
	if (m_lIndex < m_lVectorLength)	
		m_vecData[m_lRowVector][m_lIndex] = newVal;

	return S_OK;
}

STDMETHODIMP CVectorSignal::get_RowVector(long *pVal)
{
	// TODO: Add your implementation code here
	if (pVal == NULL)		
		return E_POINTER;
	
	*pVal = m_lRowVector;

	return S_OK;
}

STDMETHODIMP CVectorSignal::put_RowVector(long newVal)
{
	// TODO: Add your implementation code here
	m_lRowVector = newVal;
	return S_OK;
}

STDMETHODIMP CVectorSignal::get_SignalLength(long *pVal)
{
	// TODO: Add your implementation code here
	if (pVal != NULL)
		*pVal = m_lSignalLength;

	return S_OK;
}

STDMETHODIMP CVectorSignal::put_SignalLength(long newVal)
{
	// TODO: Add your implementation code here
	HRESULT hres;
	long oldsiglen=m_lSignalLength;

	// Call Lock();
	// The Lock method blocks other clients from modifying the variables stored in the Application object, 
	// ensuring that only one client at a time can alter or access the Application variables.
	Lock();
	m_lSignalLength=newVal;

	// Data is reallocated to service the change in size of the data set
	hres=ReallocateData(oldsiglen, m_lVectorLength);
	Unlock();
	return hres;
}

STDMETHODIMP CVectorSignal::get_VectorLength(long *pVal)
{
	// TODO: Add your implementation code here
	if (pVal != NULL)
	{
		 *pVal = m_lVectorLength;	 
		 ATLTRACE("m_lVectorLength = %d\n", m_lVectorLength);
		 return S_OK;
	}
	
	else
		return E_FAIL;
	
	return S_OK;
}

STDMETHODIMP CVectorSignal::put_VectorLength(long newVal)
{
	// TODO: Add your implementation code here
	HRESULT hres;
	long oldveclen=m_lVectorLength;

	// Call Lock();
	// The Lock method blocks other clients from modifying the variables stored in the Application object, 
	// ensuring that only one client at a time can alter or access the Application variables.
	Lock();
	m_lVectorLength=newVal;

	// Data is reallocated to service the change in size of the data set
	hres=ReallocateData(m_lSignalLength,oldveclen);
	Unlock();
	return hres;
}

STDMETHODIMP CVectorSignal::GetCurrentVector(SAFEARRAY* data)
{
	// TODO: Add your implementation code here
	long i;
	long lDataLength;
	double *locdata;
	if (data == NULL)
		return E_POINTER;
	
	lDataLength=data->rgsabound->cElements;

	// Assign locdata the pointer address of the SAFEARRAY
	locdata=(double*)data->pvData;

	// Store Vector data in elements of locdata
	if (m_vecData != NULL) {

		Lock();
		if (lDataLength <= m_lVectorLength)	{

//			memcpy(data,m_vecData[m_lRowVector],sizeof(double)*lDataLength);
			for (i = 0; i < lDataLength; i++)
			{
				locdata[i]=m_vecData[m_lRowVector][i];
			}
			
		}

		Unlock();
		return S_OK;	
	}

	// Default condition:	
	else {
		for (i = 0; i < lDataLength; i++)
			locdata[i] =7.7;

		return E_FAIL;
	}

	return S_OK;
}


STDMETHODIMP CVectorSignal::GetVector(long index, SAFEARRAY* data)
{
	// TODO: Add your implementation code here
	long i;
	long lDataLength;
	double* locdata;

	Lock();
	index = ((m_lRowVector + m_lSignalLength) - index) % m_lSignalLength;
	locdata=(double*)data->pvData;
	lDataLength=data->rgsabound->cElements;
	
	if (m_vecData != NULL)
	{
		if ((index < m_lSignalLength)&&(lDataLength <= m_lVectorLength))	{

			for (i = 0; i < lDataLength; i++)
				locdata[i]=m_vecData[index][i];
		}

		Unlock();

		return S_OK;
	}

	Unlock();

	// Default conditions:
	if (lDataLength <= m_lVectorLength)
	{
		for (i = 0; i < lDataLength; i++)
			locdata[i] =7.8;
	}

	return E_FAIL;
}

STDMETHODIMP CVectorSignal::SetCurrentVector(SAFEARRAY* data)
{
	// TODO: Add your implementation code here
	long i;
	long lDataLength;
	double* locdata;

	if ((m_vecData != NULL))	{

		lDataLength=data->rgsabound->cElements;
		locdata=(double*)data->pvData;
		if (lDataLength <= m_lVectorLength)
		{
			Lock();

			m_lRowVector++;
			m_lRowVector %= m_lSignalLength;				// Circular buffer			
		 
			for (i = 0; i < lDataLength; i++)
				m_vecData[m_lRowVector][i]= locdata[i];

			Unlock();
		}
		else		
			return E_INVALIDARG;

		return S_OK;
	}	
	
	return E_FAIL;
}

STDMETHODIMP CVectorSignal::SetVector(long index, SAFEARRAY* data)
{
	// TODO: Add your implementation code here
	long i;
	long lDataLength;
	double *locdata;

	if (index > m_lSignalLength)		// It doesn't go back that far...
		return E_FAIL;

	index = ((m_lRowVector + m_lSignalLength) - index) % m_lSignalLength;

	locdata=(double*)data->pvData;
	lDataLength=data->rgsabound->cElements;
	if ((m_vecData != NULL))
	{
		Lock();

		if ((index < m_lSignalLength)&&(lDataLength <= m_lVectorLength))	{
			for (i = 0; i < lDataLength; i++)
				m_vecData[index][i]= locdata[i];
		}

		Unlock();

		return S_OK;
	}

	return E_FAIL;
}


STDMETHODIMP CVectorSignal::OnConstruct()
{


//////////////////////////////////////
//	Final Component Initzialization //
//////////////////////////////////////

	HRESULT hRes;
	Lock();
	hRes=ReallocateData(0,0);
	Unlock();

	return hRes;
}

STDMETHODIMP CVectorSignal::OnDestruct()
{
	long oldsiglen=m_lSignalLength;
	long oldveclen=m_lVectorLength;
	m_lVectorLength=0;
	m_lSignalLength=0;
	ReallocateData(oldsiglen,oldveclen);

	return S_OK;
};

STDMETHODIMP CVectorSignal::Load(VARIANT Data) {


	// Variables
	BSTR					ItemName = NULL;// The string holding the name of the item to write into the property bag.
	_PropertyBagWrapper*	pIPB;			// COM Interface Pointer to the PropertyBag _Wrapper_ Class
	HRESULT					hRes;			// The HRESULT value we get back from COM calls.
	variant_t				*Var;

	long oldsiglen, oldveclen;

	oldsiglen=m_lSignalLength;
	oldveclen=m_lVectorLength;

	// (1) Create an object of the Propertybag wrapper class and place the address of the output variable (that receives the interface pointer) in pIPB
	// (2) Have the class point to the interface 
	hRes = CoCreateInstance(CLSID_PropertyBagWrapper, NULL, CLSCTX_INPROC_SERVER, IID__PropertyBagWrapper, (LPVOID*)&pIPB);

		if (pIPB == NULL)	
			return !S_OK;

		// Get the pointer to the real VB property bag (the VB object (defined in msvbvm60.dll (aka VBRUN)) that our wrapper class created)
		//hRes = pIPB->GetPropertyBag(&m_VBPropertyBag);
		
		// Pass Data to PropertyBag
		hRes = pIPB->SetPropertyBag(&Data);

		//Lock to avoid process issues while changing the vector and signal lengths
		Lock();

		// Load 1st item
		// Define strings
		ItemName = SysAllocString(L"SignalLength");
		Var = new variant_t;
		// Read Data from the property bag
		hRes=pIPB->GetFromPropertyBag(&ItemName,Var);  //2nd argument is return value (look retval for help)
		m_lSignalLength=(long)*Var;
		SysFreeString(ItemName);
		delete Var;
		

		// Load 2nd item
		ItemName = SysAllocString(L"VectorLength");		
		Var = new variant_t;
		// Read Data from the property bag
		hRes=pIPB->GetFromPropertyBag(&ItemName,Var);  //2nd argument is return value (look retval for help)
		m_lVectorLength=(long)*Var;
		SysFreeString(ItemName);
		delete Var;


		// Decrement the pointer reference count from our member variable. 
		VariantClear(&m_VBPropertyBag);
		
		// Release
		pIPB->Release();
		

//////////////////////////////////////
//	Final Component Initzialization //
//////////////////////////////////////

	if(oldsiglen!=m_lSignalLength || oldveclen!=m_lVectorLength)
		hRes=ReallocateData(oldsiglen,oldveclen);

	Unlock();

	//ATLTRACE(_T("CVectorSignal:Vector Space Allocated"));

	return hRes;
}

////////////////////////////////////////////////////////////////////////
// Called by the framework to serialize the component to binary sotrage 
// in a file.
//
// Pass it a data pointer to a Variant that contains an automation type
// or an array of automation types
//
// The data is saved to a PropertyBag (in VB) via a _PropertyBagWrapper Class in C++
// 
// PropertyBags have not been successfully defined in C++, hence the need of the wrapper class. 
// The dll containing the definitions for the PropertyBag does not have a export stdcall and thus can't be used.
//
// Juan Rojas, Feb. 5, 2005
////////////////////////////////////////////////////////////////////////
STDMETHODIMP CVectorSignal::Save(VARIANT *pData) {

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
		
		// Create string names for items to be saved
		ItemName = SysAllocString(L"SignalLength");
		// Store the data and the type of data into a variant_t type
 		Var = new variant_t(m_lSignalLength,VT_I4);
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, Var);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Delete our variants
		delete Var;

		// Create string names for items to be saved
		ItemName = SysAllocString(L"VectorLength");
		// Store the data and the type of data into a variant_t type
		Var = new variant_t(m_lVectorLength,VT_I4);				
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, Var);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Delete our variants
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

/////////////////////////////////////////////////////////////////////////////////////////
// Reallocate data is there is a size change in the Vector Signal.
// Three scenarios:
// (1) No size change	- if not change, break out without changing size
// (2) Smaller			- if smaller delete data allocations great than desired size
// (3) Greater			- copy stored data, and reallocated to desired size
/////////////////////////////////////////////////////////////////////////////////////////
HRESULT CVectorSignal::ReallocateData(long oldsiglen,long oldveclen)
{
	int i, index, spindex;
	double **savedata;

	// Default case when it is originally created
	if(m_lSignalLength==0 || m_lVectorLength==0)
		return S_OK;

	// (1) If no change in size, break out
	if(m_lSignalLength==oldsiglen && m_lVectorLength==oldveclen)
		return S_OK;

	// Create a copy of store data for later use.
	savedata=m_vecData;	

	// Allocate memory pointer to a double of size signal length
	if(oldsiglen!=m_lSignalLength)
		m_vecData = new double* [m_lSignalLength];

	// Allocate data of size vectorlength for each signal
	// Initializing value to zero
	if (m_vecData != NULL)
	{
		for (index=0; index < m_lSignalLength; index++)
		{
			m_vecData[index] = new double[m_lVectorLength];

			if (m_vecData[index] != NULL)	{

				for (spindex = 0; spindex < m_lVectorLength; spindex++)
					m_vecData[index][spindex] = 0.0;
			}		
		}			
	}				
	else
	{
		m_vecData=savedata;
		return E_POINTER;
	}

	// Copy the still-valid data
	for(index=0;index<min(m_lSignalLength,oldsiglen);index++)
		for(spindex=0;spindex<min(m_lVectorLength,oldveclen);spindex++)
			m_vecData[index][spindex]=savedata[index][spindex];


	//delete the old m_VecData
	if (savedata != NULL)	
	{
		// Delete the rows
		for (i=0; i<oldsiglen; i++)
			delete [] savedata[i];

		// Delete the pointer itself
		delete [] savedata;
	}

	return S_OK;
}

/////////////////////////////////////////////////////////
// Used to update information in Manager Book
/////////////////////////////////////////////////////////
STDMETHODIMP CVectorSignal::UpdateManager(BSTR Interface, VARIANT *Data)
{
	USES_CONVERSION;
	VARIANT *arrayptr;
	SAFEARRAYBOUND arrbound[2];
	long idx[2];
	int i,j;

	Lock();
	if(strcmp(OLE2T(Interface),"IVectorSignal")==0)
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
		arrayptr[0].lVal=m_lVectorLength;		// Vector Length

		// Set type of next element
		arrayptr[1].vt=VT_I4;
		// Set long value 
		arrayptr[1].lVal=m_lSignalLength;		// Signal Length

		// Set type of next element
		arrayptr[2].vt=VT_I4;
		// Set value of long
		arrayptr[2].lVal=m_lRowVector;			// Row Vector

		// Set type of next element as double array
		arrayptr[3].vt=VT_ARRAY|VT_R8;
		
		
		// Set parameters for array-boundaries to then create a Vector for arrayptr
		arrbound[0].cElements=m_lSignalLength;
		arrbound[0].lLbound=0;
		arrbound[1].cElements=m_lVectorLength;
		arrbound[1].lLbound=0;

		// Create vector of dimensions arrabound
		arrayptr[3].parray=SafeArrayCreate(VT_R8,2,arrbound);

		for(i=0;i<m_lSignalLength;i++)
		{
			for(j=0;j<m_lVectorLength;j++)
			{
				idx[0]=i;
				idx[1]=j;
				SafeArrayPutElement(arrayptr[3].parray,idx,&(m_vecData[i][j]));
			}
		}
	}

	Unlock();
	return S_OK;
}


STDMETHODIMP CVectorSignal::TestSetup(long Index)
{
	// TODO: Add your implementation code here
	short i;

	// Sets vector values to known quantities based on index
	
	if (Index == 0)	{
		if (m_vecData != NULL)
			if (m_vecData[m_lRowVector] != NULL)					
				for (i = 0; i < m_lVectorLength; i++)
					m_vecData[m_lRowVector][i] = (double) i;
			

	}


	else if (Index == 1)	{
		if (m_vecData != NULL)
			if (m_vecData[m_lRowVector] != NULL)					
				for (i = 0; i < m_lVectorLength; i++)
					m_vecData[m_lRowVector][i] = (double) 1.5 * i;
			
	}

	return S_OK;
}