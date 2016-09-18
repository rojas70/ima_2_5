// TrajectoryPlayer.cpp : Implementation of CTrajectoryPlayer
#include "stdafx.h"
#include "IMA2_TrajectoryLib.h"
#include "TrajectoryPlayer.h"

/////////////////////////////////////////////////////////////////////////////
// CTrajectoryPlayer
// 
// This class reads data from a txt file that then should be sent to an input
// VS (either XYZRPY or Joint-Angle information) in the Arm Agents.
// 
// The txt file normally has two sets of data. The first one is found in the 
// first column of the file and represents the time instance of a particular 
// step in a trajectory. The rest of the columns represent the cartesian or angle
// data. 
//
// The data in the text file is commonly produced by the Trajectory Generator
// Class. 
/////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Set loop variables to their initial values and secure opening of file
//////////////////////////////////////////////////////////////////////////



STDMETHODIMP CTrajectoryPlayer::OnConstruct() {

// TODO: Bindings. Personalize the binding of your component. 

	int numiids;
	IMA2_BindingInfo BindInf;
	numiids=1;

	// 1. Output VS
	BindInf.Name		= SysAllocString(L"OutputVS");						// Assign name to object
	BindInf.BindType	= BT_Collection;									// Condition to accept multiple targets
	BindInf.Path		= SysAllocString(L"");								// This must be the path of our component
	BindInf.PIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);		// Create and empty string array
	BindInf.IIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);		// Create and empty string array
	m_ConfigureBindings->Add(&BindInf);										// Set up the clients bindings array.	

	// 2. State Machine
	BindInf.Name		= SysAllocString(L"StateMachine");
	m_ConfigureBindings->Add(&BindInf);

	// Deallocate storage
	SysFreeString(BindInf.Name);
	SysFreeString(BindInf.Path);
	SafeArrayDestroy(BindInf.PIDs);
	SafeArrayDestroy(BindInf.IIDs);
	
	return S_OK;
}

STDMETHODIMP CTrajectoryPlayer::OnDestruct() {	return S_OK; }

///////////////////////////////////////////////////////////////////
// Frist pass the pointer of the variable DATA to the PropertyBag
// Then retrive items from the PropertyBag by name
///////////////////////////////////////////////////////////////////
STDMETHODIMP CTrajectoryPlayer::Load(VARIANT Data) 
{
	
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

		// Pass Data from file to PropertyBag
		hRes = pIPB->SetPropertyBag(&Data);

		// Variable 1
		ItemName	= SysAllocString(L"FileName");
		ItemValue	= new variant_t;
		pIPB->GetFromPropertyBag(&ItemName,ItemValue);	//2nd argument is return value (look retval for help)
		SysReAllocString(&m_bstrInputFile,ItemValue->bstrVal);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable 2
		ItemName	= SysAllocString(L"NumAxes");
		ItemValue	= new variant_t; 
		pIPB->GetFromPropertyBag(&ItemName, ItemValue);	//2nd argument is return value (look retval for help)
		m_lNumAxes	= (long)*ItemValue;
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

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
STDMETHODIMP CTrajectoryPlayer::Save(VARIANT * pData)
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

		// Variable 1
		ItemName = SysAllocString(L"FileName");
		ItemValue = new variant_t(m_bstrInputFile);		// Variant stores variable as a BSTR 
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable 2
		ItemName = SysAllocString(L"NumAxes");
		// Store the data and the type of data into a variant_t type
 		ItemValue = new variant_t(m_lNumAxes,VT_I4);
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

////////////////////////////
// Interface Methods
////////////////////////////
STDMETHODIMP CTrajectoryPlayer::get_NumAxes(long *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_lNumAxes;

	return S_OK;
}

STDMETHODIMP CTrajectoryPlayer::put_NumAxes(long newVal)
{
	// TODO: Add your implementation code here
	if (newVal >= 0)
		m_lNumAxes = newVal;

	return S_OK;
}

STDMETHODIMP CTrajectoryPlayer::get_FileName(BSTR *pVal)
{
	// TODO: Add your implementation code here
	*pVal = SysAllocString(m_bstrInputFile);
	ATLTRACE("get_FileName: FileName name is m_bstrInputFile\n");

	return S_OK;
}

STDMETHODIMP CTrajectoryPlayer::put_FileName(BSTR newVal)
{
	// TODO: Add your implementation code here
	SysReAllocString(&m_bstrInputFile,newVal);
	ATLTRACE("put_FileNameName\n");

	return S_OK;
}

STDMETHODIMP CTrajectoryPlayer::Initialize()
{
	// TODO: Add your implementation code here
	m_bDone			= FALSE;
	m_lLoopCounter	= 0;
	CloseFile();
	OpenFile();
	return S_OK;
}

void CTrajectoryPlayer::OpenFile()
{
	USES_CONVERSION;		// Necessary to convert from BSTR to LPWSTR
	_bstr_t	bstrTemp;

	// Open the text file
	m_fp  = fopen(OLE2T(m_bstrInputFile), "r+t");
	
	// This first statement extracts the time variable in the file
	// A later fscanf will then extract the position variables
	if(m_fp == NULL ) 
		MessageBox(NULL, "Please add a file for the trajectory to play!", "Your forgot to insert the file location :)", MB_OK);
}

void CTrajectoryPlayer::CloseFile()
{
	if(m_fp!=NULL)
	{
		fclose(m_fp );
		m_fp=NULL;
	}
}

//////////////////////////////////////////////////////////////////
// Function: Write to a VS all the points in the traj file 
// 
// Check to see if NextTrajPoint is equal to 0
// If so, Set the VectorSignal with the position information
//////////////////////////////////////////////////////////////////
STDMETHODIMP CTrajectoryPlayer::OutputTrajectory()
{
	// TODO: Add your implementation code here
	int i;
	short nFileStat = ~EOF;
	short nCount	= 0;

	SAFEARRAY		*mysa;
	IStateMachine	*pISM			= NULL;
	IVectorSignal	*pIVSReadFile	= NULL;

	// Read the file
	if(m_fp==NULL) return MessageBox(NULL,"Could not read file", "Error in CTrajectoryPlayer::GetLocation()",MB_OK);

	// Read the file 
	while(nFileStat!= EOF)
	{

		// Read the next alloted time step in the file and store in NextTrajPoint
		nFileStat = fscanf(m_fp ,"%lf\t",&m_dNextTrajPoint);
		ATLTRACE("\n");

		// XYZRPY or JointAngles position
		for(i=0;i<m_lNumAxes;i++)
		{
			// Read the number of elements XYZRPY or Joint Angles
			nFileStat = fscanf(m_fp ,"%lf",&(m_dLastCmd[i]));	// Read out the actual values
			ATLTRACE("%lf ",m_dLastCmd[i]);
		}

		// Get pointer to VS object and interface
		m_Bindings->get_Pointers(SysAllocString(L"OutputVS"),&m_pIUnkOut);

		if(m_pIUnkOut==NULL) return E_POINTER;
		m_pIUnkOut->QueryInterface(IID_IVectorSignal,(void**)&pIVSReadFile);
		if(pIVSReadFile==NULL) return E_POINTER;

		// Set Vector signal with location that is read from fscanf
		mysa = SafeArrayCreateVector(VT_R8,0,m_lNumAxes);
		memcpy(mysa->pvData,m_dLastCmd,sizeof(double)*m_lNumAxes);
		pIVSReadFile->SetCurrentVector(mysa);
		Sleep(50);
		// Destroy SafeArray
		SafeArrayDestroy(mysa);
	}

	CloseFile();
	OpenFile();

	// Tell State Machine to go to next state
	// Pass a BSTR to the StateMachine "Signal" call.
	// By comparing strings the SM will know to move to the next state.

	m_Bindings->get_Pointers(SysAllocString(L"StateMachine"), &m_pIUnkStateMachine);
	if (m_pIUnkStateMachine != NULL)
		m_pIUnkStateMachine->QueryInterface(IID_IStateMachine,(void **)&pISM);
	if (pISM != NULL)
		pISM->Signal(SysAllocString(L"Compute next trajectory"));
	pISM->Release();


	// Release Interface Pointer
	pIVSReadFile->Release();

	return S_OK;
}