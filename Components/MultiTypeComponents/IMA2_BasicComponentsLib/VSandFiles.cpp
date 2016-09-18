// VSandFiles.cpp : Implementation of CVSandFiles
#include "stdafx.h"
#include "IMA2_BasicComponentsLib.h"
#include "VSandFiles.h"

/////////////////////////////////////////////////////////////////////////////
// CVSandFiles

STDMETHODIMP CVSandFiles::OnConstruct() {

// TODO: Bindings. Personalize the binding of your component. 

	int numiids;
	IMA2_BindingInfo BindInf;
	numiids=1;

	// 1. VectorSignal to Write to.
	BindInf.Name		= SysAllocString(L"ConnectingVS");					// Assign name to object
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

STDMETHODIMP CVSandFiles::OnDestruct() 
{	
	CloseFile();
	return S_OK; 
}

///////////////////////////////////////////////////////////////////
// Frist pass the pointer of the variable DATA to the PropertyBag
// Then retrive items from the PropertyBag by name
///////////////////////////////////////////////////////////////////
STDMETHODIMP CVSandFiles::Load(VARIANT Data) 
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
		
		// Pass Data from file to PropertyBag
		hRes = pIPB->SetPropertyBag(&Data);

		// Retrieve Data from PropertyBag
		// Variable 1
		ItemName	= SysAllocString(L"NumAxes");
		Var			= new variant_t;
		pIPB->GetFromPropertyBag(&ItemName,Var);	//2nd argument is return value (look retval for help)
		m_lNumAxes	= (long)*Var;
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Variable 2
		ItemName	= SysAllocString(L"FileName");
		Var			= new variant_t;
		pIPB->GetFromPropertyBag(&ItemName,Var);	//2nd argument is return value (look retval for help)
		SysReAllocString(&m_bstrFileName,Var->bstrVal);
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Decrement the pointer reference count from our member variable. 
		VariantClear(&m_VBPropertyBag);
		
		// Release
		pIPB->Release();


	return S_OK;
}


//////////////////////////////////////////////////////////////////////////////////////////////
// Save ItemNames in Strings, and values in VARIANTS and then pass them to the PropertyBag
// Then, copy the contents of the PropertyBag into pData to be stored to file.
//////////////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CVSandFiles::Save(VARIANT * pData)
{
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
		ItemName = SysAllocString(L"NumAxes");
		Var = new variant_t(m_lNumAxes, VT_I4);
		hRes = pIPB->AddToPropertyBag(&ItemName, Var);
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Variable 2
		ItemName = SysAllocString(L"FileName");
		Var = new variant_t(m_bstrFileName);		// Variant stores variable as a BSTR 
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

//////////////////////////////////////////////////
// Initialize()
//
// Secures the correct opening of the file
// Should be the first function to be called. 
// Replaces FinalComponentInit() in IMA 1.0
//////////////////////////////////////////////////
STDMETHODIMP CVSandFiles::Initialize()
{
	// TODO: Add your implementation code here
	CloseFile();
	OpenFile();
	InitFile(FALSE);	// Create File
	ATLTRACE("%lf ",m_dTemp);
	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////////
// Input:	Text File
// Output:	Binding to a VS
// Function:This function will copy the number of values in each line determined 
//			by the variable m_lNumAxes.
//			Due to the way scanf works two different considerations can be seen:
//			1) The fist value of Data: m_dData[0] is read so as to not lose it when we 
//			   scanf at the end of each line to check for EOF.
//			2) The if statement is there to jump out of the while loop once the last	
//			   fscanf is done, and nFileStat changes to EOF
////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CVSandFiles::Write2VS()
{
	// TODO: Add your implementation code here
	USES_CONVERSION;
	_bstr_t	bstrTemp;	
	
	int i;
	SAFEARRAY		*mysa;							// Create automtaion type to be used with VS Interface calls	
	IVectorSignal	*pIVSOut;						// Type to connect to VS Interface


	// Get pointer to object and interface
	m_Bindings->get_Pointers(SysAllocString(L"ConnectingVS"),&m_pIUnkOut);
	if(m_pIUnkOut==NULL) return E_POINTER;
	m_pIUnkOut->QueryInterface(IID_IVectorSignal,(void**)&pIVSOut);
	if(pIVSOut==NULL) return E_POINTER;	

	// Open the text file: "r" = read; and "t" = open in text (translated) mode look in MSDN
	m_fp  = fopen(OLE2T(m_bstrFileName), "r+t");
	if(m_fp == NULL) 
	{
		ATLTRACE(_T("No File associated with this component"));
		return !S_OK;
	}

	// Read the file for as many NUMBER OF AXES (not lines) as there may be: i.e. XYZRPY or JointAngles 1-6
	while((nFileStat!= EOF) && (nFileStat = fscanf(m_fp ,"%lf\t",&(m_dData[0])) ) )
	{
		if(nFileStat!= EOF)
		{
				// XYZRPY or JointAngles:
				for(i=1;i<m_lNumAxes;i++)
				{
					// Read the number of elements XYZRPY or Joint Angles
					nFileStat = fscanf(m_fp ,"%lf\t",&(m_dData[i]));
					ATLTRACE("%lf ",m_dData[i]);
				}

				// Set data to Vector Signal
				mysa = SafeArrayCreateVector(VT_R8,0,m_lNumAxes);
				memcpy(mysa->pvData,m_dData,sizeof(double)*m_lNumAxes);
				pIVSOut->SetCurrentVector(mysa);
				SafeArrayDestroy(mysa);

				// New line for debug purposes
				ATLTRACE("\n");
		}
	}
	
	
	// Close the file
	CloseFile();
	OpenFile();
	nFileStat = 0;	// Reset File status

	// Relase interface connection
	pIVSOut->Release();

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
// Input:	VS values
// Output:	Text file
// Function:The function copies the values located in the VS up to size
//			m_lNumAxes to the file.
/////////////////////////////////////////////////////////////////////////
STDMETHODIMP CVSandFiles::Write2File()
{
	// TODO: Add your implementation code here
	double pdData[20];					
	
	SAFEARRAY		*mysa;							// Create automtaion type to be used with VS Interface calls	
	IVectorSignal	*pIVSOut;						// Type to connect to VS Interface

	// Get pointers to object and interface
	m_Bindings->get_Pointers(SysAllocString(L"ConnectingVS"),&m_pIUnkOut);
	if(m_pIUnkOut==NULL) return E_POINTER;
	m_pIUnkOut->QueryInterface(IID_IVectorSignal,(void**)&pIVSOut);
	if(pIVSOut==NULL) return E_POINTER;	

	// Get VS Values
	mysa = SafeArrayCreateVector(VT_R8,0,m_lNumAxes);
	pIVSOut->GetCurrentVector(mysa);
	memcpy(pdData,mysa->pvData,sizeof(double)*m_lNumAxes);
	SafeArrayDestroy(mysa);

	// Write to file with the following function
	WriteDoubles(m_lNumAxes,pdData);

	pIVSOut->Release();

	return S_OK;
}


////////////////////
// Open File()
////////////////////
void CVSandFiles::OpenFile()
{
	// Local variable
	USES_CONVERSION;
	_bstr_t	bstrTemp;

	// Open a text file
	// "r" = read
	// "t" = open in text (translated) mode look in MSDN
	m_fp  = fopen(OLE2T(m_bstrFileName), "r+t");
}

////////////////////
// Close File()
////////////////////
void CVSandFiles::CloseFile()
{
	if(m_fp!=NULL)
	{
		fclose(m_fp);
		m_fp=NULL;
	}
}

// Write Doubles to a file
void CVSandFiles::WriteDoubles(long len, double * pdData)
{
	// Local variables
	USES_CONVERSION;	// for converting BSTR to char *
	char szTemp[200];
	char pcNewline[2] = {0x0d, 0x0a};
	char szMark[2] = "#";
	
	int i;

	CComBSTR bstrTemp;
	DWORD dwNBytesWritten;
	DWORD dwStrSize = 0;	

	// Write each element to string, tab delineated
	for(i=0;i<len;i++)
		dwStrSize += sprintf((szTemp+dwStrSize),"%f\t",pdData[i]);

	WriteFile( 
	/* Handle to file to write to						*/	m_hDataFile, 
	/* Pointer to data to write to file					*/	szTemp,  
	/* Number of bytes to write							*/	dwStrSize -1,
	/* Pointer to number of bytes written				*/	&dwNBytesWritten,  
	/* Pointer to structure needed for overlapped I/O	*/	NULL
	);

	// Write newline
	WriteFile( 
	/* Handle to file to write to						*/	m_hDataFile, 
	/* Pointer to data to write to file					*/	pcNewline,  
	/* Number of bytes to write							*/	2,
	/* Pointer to number of bytes written				*/	&dwNBytesWritten,  
	/* Pointer to structure needed for overlapped I/O	*/	NULL
	);
}

////////////////////////////
// Interface Methods
////////////////////////////
STDMETHODIMP CVSandFiles::get_FileName(BSTR *pVal)
{
	// TODO: Add your implementation code here
	*pVal = SysAllocString(m_bstrFileName);
	ATLTRACE("get_FileName: FileName name is m_bstrFileName\n");

	return S_OK;
}

STDMETHODIMP CVSandFiles::put_FileName(BSTR newVal)
{
	// TODO: Add your implementation code here
	SysReAllocString(&m_bstrFileName,newVal);
	InitFile(FALSE);
	ATLTRACE("put_FileNameName\n");
	return S_OK;
}

STDMETHODIMP CVSandFiles::get_NumAxes(long *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_lNumAxes;
	return S_OK;
}

STDMETHODIMP CVSandFiles::put_NumAxes(long newVal)
{
	// TODO: Add your implementation code here
	if (newVal >= 0)
		m_lNumAxes = newVal;
	return S_OK;
}

//////////////////////////////////////////////////////////
// Call to create a file that is readable and writeable
// Stores data in HANDLE m_hDataFile
//////////////////////////////////////////////////////////
void CVSandFiles::InitFile(bool bOverwrite)
{
	USES_CONVERSION;						// for converting BSTR to char *

	char * szTemp			= NULL;
	DWORD dwStrSize			= 0;
	DWORD dwNBytesWritten	= 0;
	CComBSTR bstrTemp;

	// Call to create a readable/writeable file in the directory path indicated in DAD
	m_hDataFile = CreateFile( 
		/* Pointer to name of the file					*/	OLE2T(m_bstrFileName), 
		/* Access (read-write) mode						*/	GENERIC_WRITE, 
		/* Share mode									*/	FILE_SHARE_READ|FILE_SHARE_WRITE,  
		/* Pointer to security attributes				*/	NULL, 
		/* How to create								*/	(bOverwrite)?(CREATE_ALWAYS):(OPEN_ALWAYS) , 
		/* File attributes								*/	FILE_ATTRIBUTE_NORMAL, 
		/* Handle to file with attributes to copy		*/	NULL 
	);
    
	// Write String
	WriteFile( 
	/* Handle to file to write to						*/	m_hDataFile,		// Done above
	/* Pointer to data to write to file					*/	szTemp,				// EMPTY
	/* Number of bytes to write							*/	dwStrSize -1,
	/* Pointer to number of bytes written				*/	&dwNBytesWritten,  
	/* Pointer to structure needed for overlapped I/O	*/	NULL
	);
}
