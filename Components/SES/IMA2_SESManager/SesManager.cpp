// SesManager.cpp : Implementation of CSesManager
#include "stdafx.h"
#include "IMA2_SESManager.h"
#include <afx.h>
#include "SesManager.h"
#include <fstream>

/////////////////////////////////////////////////////////////////////////////
// CSesManager

STDMETHODIMP CSesManager::OnConstruct()
{

// OnConstruct is called when the component is created. In addition to putting in
// whatever initialization code you need, If you are going to connect to another
// component anywhere in your code, you need to set up bindings. If you are not
// connecting to another component you can delete this code down to the "Final
// Component Initialization, where you should put your own start-up code (allocate
// memory, initialize variables, etc.)
//
// The following code will create one binding. Change "DescriptiveName" to some
// appropriate string. This string will be visible as the name of the binding from
// DAD. It is *not* the name of the component you will bind to. The name of the
// specific component on the other end of the binding is determined at runtime (in DAD).
//
// To make more than one binding, simply copy the code between **START** and **FINISH**
// 
// There is an option when creating a binding to limit that binding to a specific type
// (This is not properly implemented through DAD as of 12/10/2005. If you choose this option,
// you can get, for example, only vector signals, but not any kind of component with a
// vector signal interface.) See the description below on how to achieve this.
//
// If you wish to allow only one component to connect to this binding, make the BindType
// BT_Default. If you wish to allow several components, make the BindType BT_Collection.

		HRESULT hRes=S_OK;

		int numiids;
		long x[1];
		IMA2_BindingInfo Binding;

		//**START**
		numiids=1;

		//1. Head Angles
		Binding.Name		= SysAllocString(L"PTActualAngles");			// Assign name to object
		Binding.BindType	= BT_Default;									// Condition to accept one connection
		Binding.Path		= SysAllocString(L"");							// This must be the path of our component
		Binding.PIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);	// Create and empty string array
		Binding.IIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);	// Create and empty string array
		m_ConfigureBindings->Add(&Binding);									// Set up the clients bindings array.

		// 2. SES Pan LOC
		Binding.Name		= SysAllocString(L"SESPan");				// Assign name to object
		m_ConfigureBindings->Add(&Binding);	// Set up the clients bindings array.					
		
		// 3. SES Tilt LOC
		Binding.Name		= SysAllocString(L"SESTilt");				// Assign name to object
		m_ConfigureBindings->Add(&Binding);	// Set up the clients bindings array.	

		//4.  Names Queue
		Binding.Name		= SysAllocString(L"Names");				// Assign name to object
		m_ConfigureBindings->Add(&Binding);	// Set up the clients bindings array.					


		//5.  Types Queue
		Binding.Name		= SysAllocString(L"Types");				// Assign name to object
		m_ConfigureBindings->Add(&Binding);	// Set up the clients bindings array.					


		//If you wish to specify that a particular binding references only one
		//kind of component (e.g. VectorSignal), uncomment the code below,
		//and change the strings to the proper PID and IID. PIDs can be found
		//by creating a new component in DAD and looking at the PID in the
		//"Create New" dialog or in the list of properties on the bottom-right
		//of the main window. (Leave off the .1 at the end of the listed PID.)

		//x[0]=0; //specifies first element
		//SafeArrayPutElement(BindInf.PIDs, x, 
		//				(void *)SysAllocString(L"IMA2_BasicComponentsLib.VectorSignal"));
		//SafeArrayPutElement(BindInf.IIDs, x, (void *)SysAllocString(L"IVectorSignal"));

		//If you wish to allow more than one type of component, set "numiids" 
		//to the proper count (instead of 1) in the uncommented code above. Then, for each component,
		//copy the code above, increment x[0] and set the PID and IID strings
		//correctly.
		//NOTE: Be sure that, if you are setting up another binding after this,
		//numiids is set back to 1. (This should happen automatically if you 
		//followed the instructions and copied everything from "Start" to "Finish")

				

		// Free Binding Info
		SysFreeString(Binding.Name);
		SysFreeString(Binding.Path);
		SafeArrayDestroy(Binding.PIDs);
		SafeArrayDestroy(Binding.IIDs);
		//**FINISH**

//////////////////////////////////////
//	Final Component Initialization  //
//////////////////////////////////////
//Put code here that must happen so that the component's
//interface functions can run correctly

	return hRes;
}

STDMETHODIMP CSesManager::OnDestruct()
{
	//////////////////
	// Cleanup Code //
	//////////////////
	//Put code here that undoes/deallocates any leftover variables

	return S_OK;
}

STDMETHODIMP CSesManager::Save(VARIANT *pData)
{
	//This method is called by DAD when a component is saved. Items that should be saved are the
	//ones that are important to the setup of the code, or user options that should hold over
	//from one use of an agent to another. (Example: size of data, filenames, etc.) Since each
	//time a component is loaded, it is expected to behave the same way, run-time arguments should
	//probably not be saved, but any member variable on the interface that can be set by a user
	//probably should be saved. If you have no variables that should be saved, comment out or delete
	//the code in Save and Load (except for "return S_OK").

	// For each variable to be saved, make a copy of the code between **START** and **FINISH**
	// (and paste them so that they all appear before the call to GetPropertyBag). Change the
	// term "DescriptiveName" to something descriptive of the item you are saving, and make
	// sure not to reuse names. In the next line of code, change "variable" to the variable
	// you are saving and VarType to the VarType of that value. Valid types and VarTypes are:
	// (Note: These are limited by VB/OLE compatibility, not by the list of things that Variants can be.)
	// int:		VT_I4
	// float:	VT_R4
	// double:	VT_R8
	// BSTR:	VT_BSTR
	// char:	VT_BYTE
	// All strings (char*) should be converted to BSTR (see BSTR documentation).
	// A CString can be converted to a BSTR using the member function AllocSysString 
	// (see CString documentation)
	//
	// If you want to save an array, you have to assign a SAFEARRAY to the Variant. (Do NOT just
	// use a pointer, it will save just one value). replace the line starting "ItemValue =" with the following 
	// code (substituting your pointer for "variable", the array length for "numelem", int/float/double, etc. 
	// for "Type", and using the VarType of one element of the array--BSTR arrays are not allowed.):
	//
	//	ItemValue = new variant_t;
	//	ItemValue->vt=VT_ARRAY|VarType;
	//	ItemValue->parray=SafeArrayCreateVector(VarType,0,numelem);
	//  memcpy(ItemValue->parray->pvData,variable,numelem*sizeof(Type));
	//
	// Also, add the line SafeArrayDestroy(ItemValue->parray); before "delete ItemValue"
	// Because of the nature of a SafeArray, you do not have to explicitly save the length of the array.
	// However, due to the nature of property bags, you must call the array version of the Add function:
	//
	//  hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
	//
	// (See Load comments for how to extract arrays from the propertybag).

	// Variables
	BSTR					ItemName = NULL;	// the name of the item to write into the property bag.
	variant_t*			ItemValue;
	HRESULT		hRes;									// The HRESULT value we get back from COM calls.
	_PropertyBagWrapper*	pIPB;				// COM Interface Pointer to the PropertyBag _Wrapper_ Class


	// Create Class with CoCreateInstance (definition can be found in MSDN).
	// Create the property bag wrapper class, put pointer to the Interface in pIPB
	hRes = CoCreateInstance(CLSID_PropertyBagWrapper, NULL, CLSCTX_INPROC_SERVER, 
									IID__PropertyBagWrapper, (LPVOID*)&pIPB);

	if (pIPB == NULL)	
		return !S_OK;

	//**START**
		//TESSELLATION FREQUENCY
		// Create string names for items to be saved
		ItemName = SysAllocString(L"Tessellation");
		// Store the data and the type of data into a variant_t type
 		ItemValue = new variant_t(m_lTessFreq,VT_I4);
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Delete our variants
		delete ItemValue;

		//DATABASE NAME
		// Create string names for items to be saved
		ItemName = SysAllocString(L"DBName");
		ItemValue = new variant_t(m_DBname);		// Variant stores variable as a BSTR 
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Delete our variants
		delete ItemValue;

		//SES PAN
/*		// Create string names for items to be saved
		ItemName = SysAllocString(L"RetrieveAtPan");
		ItemValue = new variant_t(m_dSESPan , VT_R8);		
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Delete our variants
		delete ItemValue;

		//SES TILT
		// Create string names for items to be saved
		ItemName = SysAllocString(L"RetrieveAtTilt");
		ItemValue = new variant_t(m_dSESTilt , VT_R8);		
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Delete our variants
		delete ItemValue;
*/
	

	//**FINISH**

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

STDMETHODIMP CSesManager::Load(VARIANT Data)
{
	// This function will load in all the data you just saved in the Save function.

	// For each variable to be loaded, make a copy of the code between **START** and **FINISH**
	// (and paste them so that they all appear before the call to VariantClear). Change the
	// term "DescriptiveName" to the name you gave this item in Save.
	// On the line beginning "variable = ", change "variable" to the variable that you saved
	// the value from, and change "Type" to the type of that variable (use "long" for "int")
	// A CString can be directly set to a BSTR, but in order to get a char* back, you have to 
	// use strcpy (I think).
	//
	// If you made an array, you have to load it back in now.
	// Just like in the save function, you must call the array version of the Get function:
	//
	//  pIPB->GetArrayFromPropertyBag(&ItemName, ItemValue);
	//
	// If your variable is dynamically allocated, make sure to delete and reallocate it:
	//
	//  if(variable!=NULL)
	//		delete variable;
	//  variable=new Type[ItemValue->parray->rgsabound->cElements];	
	//
	// Then just copy the values from the parray (replace the "variable =" line with this):
	//
	//  memcpy(variable, ItemValue->parray->pvData, 
	//  						ItemValue->parray->rgsabound->cElements*sizeof(Type));
	//
	// Note that this means you do not have to separately save the length of the array, although if
	// you have a variable that keeps track of the array length you should also set it at this point:
	//
	//  numelem=ItemValue->parray->rgsabound->cElements;
	//
	// Also, to avoid a memory leak, add "SafeArrayDestroy(ItemValue->parray)" before "delete ItemValue".

	BSTR					ItemName = NULL;	// the name of the item to write into the property bag.
	variant_t*			ItemValue;
	HRESULT		hRes;									// The HRESULT value we get back from COM calls.
	_PropertyBagWrapper*	pIPB;				// COM Interface Pointer to the PropertyBag _Wrapper_ Class

	// (1) Create the property bag wrapper class
	// (2) Have the class point to the interface 
	hRes = CoCreateInstance(CLSID_PropertyBagWrapper, NULL, CLSCTX_INPROC_SERVER, 
							IID__PropertyBagWrapper, (LPVOID*)&pIPB);

	if (pIPB == NULL)	
		return !S_OK;

	// Pass Data to PropertyBag
	hRes = pIPB->SetPropertyBag(&Data);

	//**START**
		//TESSELLATION FREQUENCY
		// Define strings
		ItemName = SysAllocString(L"Tessellation");
		ItemValue=new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName, ItemValue);  //2nd argument is return value
		m_lTessFreq = (long)* ItemValue;
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		//DATABASE NAME
		// Define strings
		ItemName = SysAllocString(L"DBName");
		ItemValue=new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName, ItemValue);  //2nd argument is return value (look retval for help)
		SysReAllocString(&m_DBname,ItemValue->bstrVal);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

/*		//sespan
		// Define strings
		ItemName = SysAllocString(L"RetrieveAtPan");
		ItemValue=new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName, ItemValue);  //2nd argument is return value
		m_dSESPan = (double)* ItemValue;
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;


		//sesTilt
		// Define strings
		ItemName = SysAllocString(L"RetrieveAtTilt");
		ItemValue=new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName, ItemValue);  //2nd argument is return value
		m_dSESTilt = (double)* ItemValue;
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;
*/
	//**FINISH**
		
	// Decrement the pointer reference count from our member variable. 
	VariantClear(&m_VBPropertyBag);
		
	// Release
	pIPB->Release();

	// If there is stuff that must be reinitialized due to the load, do it here. (For example,
	// VectorSignal stores an array length, so the array must be reallocated after loading in
	// the correct length from file.) Load happens after "OnConstruct", but only gets called
	// for components that are being loaded from file, so you might have to have the same
	// "Final Initialization" code in both places.
	
	return S_OK;
}




STDMETHODIMP CSesManager::get_DatabaseName(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pVal = SysAllocString(m_DBname);
	ATLTRACE("get_DatabaseName: getting database name. \n");
	return S_OK;
	
}

STDMETHODIMP CSesManager::put_DatabaseName(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	char * name;
	// TODO: Add your implementation code here
	SysReAllocString(&m_DBname,newVal);
	ATLTRACE("put_DatabaseName: setting database name. \n");
	
	//get BSTR back to char
	name = (char*)malloc(_bstr_t(m_DBname).length());
	strcpy(name,(char*)_bstr_t(m_DBname));
	
	//Disconnect and Reconnect
	Disconnect();
	Connect(name, "localhost", "user");

	return S_OK;
}


STDMETHODIMP CSesManager::ResetSES()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	bool bRetVal;
	
	bRetVal = DumpAllData();
	if(bRetVal)
		ATLTRACE("Task Complete \n");
	else
		ATLTRACE("DumpAllData operation was unsuccessful \n");

	return S_OK;
}


STDMETHODIMP CSesManager::PostSESInfo()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	ITextQueue*		pTQNames = NULL;		
	ITextQueue*		pTQTypes = NULL;		
	IVectorSignal*	pIVSData = NULL;
	
//	double*			pdTime = NULL;
//	double			pdAngleData[4];
	
	BSTR			bstrNames = NULL;
	BSTR			bstrTypes = NULL;

	long			lNumNames;
	long			lNumTypes;

	char			cpName[20];
	char			cpType[20];

	SAFEARRAY		*mysa;

	USES_CONVERSION;

	//use information from camera to know which to post

	//bindings
	m_Bindings->get_Pointers(SysAllocString(L"PTActualAngles"),&m_pIUnkDataVS);
	m_Bindings->get_Pointers(SysAllocString(L"Types"),&m_pIUnkTypesTQ);
	m_Bindings->get_Pointers(SysAllocString(L"Names"),&m_pIUnkNamesTQ);



	if(m_pIUnkDataVS != NULL && m_pIUnkNamesTQ != NULL && m_pIUnkTypesTQ != NULL)
	{
		m_pIUnkDataVS->QueryInterface(IID_IVectorSignal,(void **)&pIVSData);
		m_pIUnkNamesTQ->QueryInterface(IID_ITextQueue,(void **)&pTQNames);
		m_pIUnkTypesTQ->QueryInterface(IID_ITextQueue,(void **)&pTQTypes);

		if(pIVSData != NULL && pTQNames != NULL && pTQTypes != NULL)
		{
			// can only post one piece of data at a time
			//grab current vector and post at that location (current head angles)
			mysa=SafeArrayCreateVector(VT_R8,0,6);
			pIVSData->GetCurrentVector( mysa );  //can also say "GetVector" w/ an index...
			memcpy(m_pdHeadAngles,mysa->pvData,sizeof(double)*6);
			SafeArrayDestroy(mysa);

			pTQNames->GetCurrentText(&bstrNames);
			pTQTypes->GetCurrentText(&bstrTypes);

			strcpy(cpName, OLE2T(bstrNames));
			strcpy(cpType, OLE2T(bstrTypes));
			LPSTR	lpname = OLE2A(bstrNames);
			//only using left pan & tilt to post for now
			//posting order: left pan, left tilt, name, type, identifier
			if(!Post(m_pdHeadAngles[0], m_pdHeadAngles[1], cpName, cpType, cpIdentifier))
			{
				// post message saying data was not posted
				ATLTRACE("ERROR: Data was not posted to SES \n");
			}
		
			
			pIVSData->Release();
			pIVSData = NULL;
			pTQNames->Release();
			pTQNames = NULL;
			pTQTypes->Release();
			pTQTypes = NULL;

		}
	}

	return S_OK;
}

STDMETHODIMP CSesManager::RetrieveFromSES()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	ITextQueue*		pTQNames = NULL;
	ITextQueue*		pTQTypes = NULL;
	IVectorSignal*	pIVSData  = NULL;
	IVectorSignal*	pIVSData2  = NULL;
	BSTR			bstrNames = NULL;
	BSTR			bstrTypes  = NULL;
	SAFEARRAY		*mysa;

	char			retrievedIdentifier[50];	//used by retrieveAtAngles
	char			retrievedTime[50];			//used by retrieveAtAngles
	
	char			cpName[40];
	char			cpType[40];
	char*			cpTemp;

//	char**			pcpRetTypes = NULL;
//	char**			pcpRetNames = NULL;
//	double*			pdRetPans = NULL;
//	double*			pdRetTilts = NULL;
	double*			phiTheta;
	double			SESLoc[2];
	double			temp[1] = {0};

	int				iNumRecs= -1;
	int				i;

	USES_CONVERSION;

	m_Bindings->get_Pointers(SysAllocString(L"SESPan"),&m_pIUnkDataVS);
	m_Bindings->get_Pointers(SysAllocString(L"SESTilt"),&m_pIUnkDataVS2);
	m_Bindings->get_Pointers(SysAllocString(L"Types"),&m_pIUnkTypesTQ);
	m_Bindings->get_Pointers(SysAllocString(L"Names"),&m_pIUnkNamesTQ);

	
	if(m_pIUnkDataVS != NULL && m_pIUnkDataVS2 != NULL && m_pIUnkNamesTQ != NULL && m_pIUnkTypesTQ != NULL)
	{
		m_pIUnkDataVS->QueryInterface(IID_IVectorSignal,(void **)&pIVSData);
		m_pIUnkDataVS2->QueryInterface(IID_IVectorSignal,(void **)&pIVSData2);
		m_pIUnkNamesTQ->QueryInterface(IID_ITextQueue,(void **)&pTQNames);
		m_pIUnkTypesTQ->QueryInterface(IID_ITextQueue,(void **)&pTQTypes);

		if(pTQNames != NULL && pTQTypes != NULL && pIVSData != NULL && pIVSData2 != NULL)
		{
			
			//check if name is there, if so Retrieve by Name
			pTQNames->GetCurrentText(&bstrNames);	//check name
			strcpy(cpName, OLE2T(bstrNames));
			pTQTypes->GetCurrentText(&bstrTypes);	//check type
			strcpy(cpType, OLE2T(bstrTypes));
			if(stricmp(cpName, "")!=0)
			{
				//retrieve by name (10 records returned max--records ordered by most recent posting)
				iNumRecs = RetrieveByName(cpName);
				if(iNumRecs > 0)
				{
					if (iNumRecs > 10)
						iNumRecs = 10;

					for(i=0; i<iNumRecs; i++)
					{
					
						cpTemp = pcpRetTypes[i];
						pTQTypes->SetText((long)i, T2OLE(cpTemp));
						
						//set pan
						temp[0] = pdRetPans[i];
						mysa=SafeArrayCreateVector(VT_R8,0,1);
						memcpy(mysa->pvData, temp,sizeof(double)*1);
						pIVSData->SetVector(i, mysa );  //can also say "GetVector" w/ an index...
						SafeArrayDestroy(mysa);	
						//set tilt
						temp[0] = pdRetTilts[i];
						mysa=SafeArrayCreateVector(VT_R8,0,1);
						memcpy(mysa->pvData, temp ,sizeof(double)*1);
						pIVSData2->SetVector(i, mysa );
						SafeArrayDestroy(mysa);
					}

				}
			}
			else if(stricmp(cpType, "")!=0)
			{
				//retrieve by type (10 records returned max--records ordered by most recent posting)
				iNumRecs = RetrieveByType(cpType);
				if(iNumRecs > 0)
				{
					if (iNumRecs > 10)
						iNumRecs = 10;
					for(i=0; i<iNumRecs; i++)
					{
						cpTemp = pcpRetNames[i];
						pTQNames->SetText((long)i, T2OLE(cpTemp));

						//set pan
						temp[0] = pdRetPans[i];
						mysa=SafeArrayCreateVector(VT_R8,0,1);
						memcpy(mysa->pvData, temp,sizeof(double)*1);
						pIVSData->SetVector(i, mysa );  //can also say "GetVector" w/ an index...
						SafeArrayDestroy(mysa);	
						//set tilt
						temp[0] = pdRetTilts[i];
						mysa=SafeArrayCreateVector(VT_R8,0,1);
						memcpy(mysa->pvData, temp,sizeof(double)*1);
						pIVSData2->SetVector(i, mysa );
						SafeArrayDestroy(mysa);
					}

				}
			}

		
			else	
			{
				//retrieve by location	
				//get location from SESPan and SESTilt vectors (if they weren't set, default is 0,0)
				mysa=SafeArrayCreateVector(VT_R8,0,1);
				pIVSData->GetCurrentVector( mysa );
				memcpy(temp, mysa->pvData,sizeof(double)*1);
				SafeArrayDestroy(mysa);				
				SESLoc[0] = temp[0];

				mysa=SafeArrayCreateVector(VT_R8,0,1);
				pIVSData2->GetCurrentVector( mysa );
				memcpy(temp,mysa->pvData,sizeof(double)*1);
				SafeArrayDestroy(mysa);
				SESLoc[1] = temp[0];

				//convert to phi/theta
				phiTheta = ConvertToPhiTheta(SESLoc[0], SESLoc[1]);

				//Retrieve - retrieves the closest posting (only 1)
				//cpRetNames = new char[1];
				//cpRetTypes = new char[1];
				RetrieveAtAngles(phiTheta[0], phiTheta[1], retrievedIdentifier,retrievedTime);

				//put name and type into bins
				cpTemp = pcpRetNames[0];
				pTQNames->SetText((long)0,T2OLE(cpTemp));
				cpTemp = pcpRetTypes[0];
				pTQTypes->SetText((long)0,T2OLE(cpTemp));
							
			}
			

			pIVSData->Release();
			pIVSData = NULL;
			pIVSData2->Release();
			pIVSData2 = NULL;
			pTQTypes->Release();
			pTQTypes = NULL;
			pTQNames->Release();
			pTQNames = NULL;
		}
	}
		
	return S_OK;
}

//Retrieve by Type
int CSesManager::RetrieveByType(char* Type)
{
	Query		qyRetrieve = m_connSES->query();
	Result		resRecs;
	int			num_tags;
	int			i = 0;
	int			j;
	char*		temp;
	Row			row;
	Result::iterator	a;

	qyRetrieve << "SELECT tblSES.name, tblSES.pan, tblSES.tilt FROM tblSES WHERE tblSES.type = '" << Type << "';";
	resRecs = qyRetrieve.store();

	num_tags = resRecs.size();
		
	if(num_tags != 0)
	{
//		pcpRetNames = new char*	[num_tags];
		
//		for(j=0; j<num_tags; j++)
//		{
//			pcpRetNames[j] = new char [40];
//		}
		
		
		for(a=resRecs.begin(); a != resRecs.end(); a++)
		{
			row = *a;
			temp = (char*)row[0].data();
			strcpy((char*)pcpRetNames[i], temp);
			pdRetPans[i]			= row[1];
			pdRetTilts[i]			= row[2];
			
			i++;
		}
	
		return (num_tags);   
	}
	return (0);  

}


//Retrieve by Name
int CSesManager::RetrieveByName(char* Name)
{
	Query qySES			= m_connSES->query();
	Result				resRecs;
	Row					row;
	Result::iterator	a;

	int			num_tags;
	int			i = 0;
	int			j;

	char*		temp;


	qySES << "SELECT type, pan, tilt FROM tblSES WHERE name = '" << Name << "' order by timestamp DESC;";
	resRecs = qySES.store();

	num_tags = resRecs.size();
		
	if(num_tags != 0)
	{
	//	pcpRetTypes = new char*	[num_tags];
	//	for(j=0; j<num_tags; j++)
	//	{
	//		pcpRetTypes[j] = new char [40];
	//	}

			
		for(a=resRecs.begin(); a != resRecs.end(); a++)
		{
			row = *a;
			temp = (char*)row[0].data();
		
			strcpy((char*)pcpRetTypes[i],temp);
		//	strcpy(tempType, temp);
			pdRetPans[i]			= row[1];
			pdRetTilts[i]			= row[2];
			i++;
		}
		//  must return values in VS, TQ
		return (num_tags);   
	}
	return (0);  
}



// RetrieveAtAngles returns all main information about an object at the specified location
// Returns TRUE if data is found
// Returns FALSE if data is not found
// If >1 data records found, returns data closest to specified point, not most recent data
bool CSesManager::RetrieveAtAngles(float Phi, float Theta, char* Identifier, char* Time)
{
	Query qySES = m_connSES->query();
	Result		resSES;
	
	Result::iterator	R;
	Row					rwSES;

	CString		cstrSQL;

	bool	records_found = false;

	char*	cpTemp;
	char	cpI[5];
	char	cpJ[5];
	char	keepI[5];
	char	keepJ[5];

	int*	Indices;
	int		indexI,indexJ;
	int		max_i = 0;
	int		max_j = 0;
	int		tempI,tempJ;
	int		valI, valJ;

	int		x, y;
	int		iNumRecs = 0;
	int		iNumFields = 0;


	float	min_dist, dist;


	// search for first record that is closest to location
	// First, change angles into indices
	Indices = AnglesToIndices(Phi, Theta);
	indexI = Indices[0];
	indexJ = Indices[1];

	// Second, change indices to strings
	_itoa(indexI, cpI, 10);
	_itoa(indexJ, cpJ, 10);

	// first find max vals of indices 
	// this may not work very well at poles (i = 0, i = max)
	qySES << "SELECT MAX(i_index) AS i_index FROM tblNodes WHERE j_index = " << cpJ << ";";
	resSES = qySES.store();
	rwSES = *resSES.begin();
	max_i = rwSES[0];
	qySES << "SELECT MAX(j_index) AS j_index FROM tblNodes WHERE i_index = " << cpI << ";";
	resSES = qySES.store();
	rwSES = *resSES.begin();
	max_j = rwSES[0];

	// initialize min distance
	min_dist = 1000;

	// go through neighborhood of 5 - can set this during run time if you want
	for(x=-5; x<=5; x++)
	{
		// check indices to make sure they aren't negative or over the max value
		if((indexI + x) < 0)
			tempI = max_i + (indexI + x) + 1;
		else if ((indexI + x) > max_i)
			tempI = indexI + x - max_i - 1;
		else
			tempI = indexI + x;
		// change short to char*
		_itoa(tempI, cpI, 10);
		for(y=-5; y<= 5; y++)
		{
			// check indices to make sure they aren't negative or over the max value
			if((indexJ + y) < 0)
				tempJ = max_j + (indexJ + y) + 1;
			else if ((indexJ + y) > max_j)
				tempJ = indexJ + y - max_j - 1;
			else
				tempJ = indexJ + y;
			// change short to char*
			_itoa(tempJ, cpJ, 10);
			// select records
			qySES << "SELECT tblSES.name, tblSES.type, tblSES.identifier, tblSES.timestamp, tblNodes.i_index, tblNodes.j_index FROM tblSES INNER JOIN tblNodes on tblSES.ID = tblNodes.ID WHERE tblNodes.i_index = " << cpI << " and tblNodes.j_index = " << cpJ << ";";
			resSES = qySES.store();
			iNumRecs = resSES.size();
			if (iNumRecs > 0)
			{
				// keep record that is closest to actual location
				for(R = resSES.begin(); R < resSES.end(); R++)
				{
					rwSES = *R;
					valI = rwSES[4];
					valJ = rwSES[5];
					dist = (float)pow((pow(valI-tempI, 2) + pow(valJ-tempJ, 2)), 0.5);
					if (dist < min_dist)
					{
						min_dist = dist;
						// keep these records
						cpTemp = (char*) rwSES[0].data();
						strcpy((char*)pcpRetNames[0], cpTemp);
					//	cpTemp = (char*) rwSES[3].data();
//						strcpy(Time, cpTemp);
						cpTemp = (char*) rwSES[2].data();
						strcpy(Identifier, cpTemp);
						cpTemp = (char*) rwSES[1].data();
						strcpy((char*)pcpRetTypes[0], cpTemp);
						// keep i and j
						_itoa(valI, keepI, 10);	
						_itoa(valJ, keepJ, 10);

					}
				}
			}
		}
	}

	if (min_dist == 1000.0)
	{
		// no records were returned
		strcpy((char*)pcpRetNames[0], "No records found in area");
		return false;
	}
	else
		return true;

}

/*
STDMETHODIMP CSesManager::get_Name(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	
	// TODO: Add your implementation code here
	*pVal = SysAllocString(m_Name);
	ATLTRACE("get_Name: getting name. \n");

	return S_OK;
}

STDMETHODIMP CSesManager::put_Name(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	
	// TODO: Add your implementation code here
	SysReAllocString(&m_Name,newVal);
	ATLTRACE("put_Name: setting name. \n");
	
	return S_OK;
}

STDMETHODIMP CSesManager::get_Type(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	
	// TODO: Add your implementation code here
	*pVal = SysAllocString(m_Type);
	ATLTRACE("get_Type: getting type. \n");

	return S_OK;
}

STDMETHODIMP CSesManager::put_Type(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	SysReAllocString(&m_Type,newVal);
	ATLTRACE("put_Type: setting type. \n");

	return S_OK;
}
*/
STDMETHODIMP CSesManager::get_Tessellation(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()) //?

	// TODO: Add your implementation code here
	*pVal = m_lTessFreq;
	ATLTRACE("get_Tessellation: getting tessellation frequency. \n");

	return S_OK;
}

STDMETHODIMP CSesManager::put_Tessellation(long newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	m_lTessFreq = newVal;
	ATLTRACE("put_Tessellation: setting tessellation frequency. \n");

	return S_OK;
}


//***NON INTERFACE FUNCTIONS***

//Lets you specify the Database you want to connect to
void CSesManager::Connect(char* dbNameTemp, char* ServerTemp, char* UsernameTemp)
{
	
	dbName = dbNameTemp;
	m_connSES = new Connection(dbName, ServerTemp, UsernameTemp);

}

//Kills the db connection
void CSesManager::Disconnect()
{
	delete m_connSES;
}

//Dump All data from tables tblses, tblactivation, tblattention
bool CSesManager::DumpAllData()
{
	
	Query	qySES = m_connSES->query();
	Result	rsSES;
	Result::iterator R;
	Row		rwSES;
	char	*cpSQL = new char[255];
	char*	cpTemp = new char[255];
	int		flag[3];
	flag[0] = flag[1] = flag[2] = 0;
	int iNumRecs = 0;

	cout << "hi" << endl;
	try{
	strcpy (cpSQL, "Show tables from ");
	strcat (cpSQL, dbName);
	cout << cpSQL <<endl;

	qySES << cpSQL;

	rsSES = qySES.store();
	}
	catch(BadQuery er)
	{
		cerr << er.error<<endl;
	}
	for (R = rsSES.begin(); R < rsSES.end(); R++)
	{
		
		rwSES = *R;
		cpTemp = (char*) rwSES[0].data();
		
		// check to see if these tables exist, if so, delete contents
		if(!_stricmp(cpTemp, "tblses"))
			flag[0] = 1;
		
		else if(!_stricmp(cpTemp, "tblactivation"))
			flag[1] = 1;
		
		else if(!_stricmp(cpTemp, "tblattention"))
			flag[2] = 1;
	}
	qySES.reset();

	if(flag[2] == 1)
	{
		try{
			strcpy(cpTemp,"DELETE FROM tblattention;");
			//cout << cpTemp << endl;
			qySES << cpTemp;
			rsSES = qySES.store();
			qySES.reset();
		}
		catch(BadQuery er)
		{
		//	cerr <<"ERROR: " << er.error << endl;

		}
		//make sure it was deleted:
		strcpy(cpTemp, "SELECT * FROM tblattention;");
		qySES << cpTemp;
		rsSES = qySES.store();
		qySES.reset();
		if(rsSES.size() == 0)
		{
			//	cout << "delete tblattention: SUCCESS" <<endl;
		}
		else
			return false;
	}
	if(flag[0] == 1)
	{
		try{
			strcpy(cpTemp, "DELETE FROM tblSES;");
			qySES << cpTemp;
			rsSES = qySES.store();
			qySES.reset();
			//cout << cpTemp << endl;
		}
		catch(BadQuery er)
		{
		//	cerr <<"ERROR: " << er.error << endl;
		}
		//make sure it was deleted:
		strcpy(cpTemp, "SELECT * FROM tblses;");
		qySES << cpTemp;
		rsSES = qySES.store();
		qySES.reset();
		if(rsSES.size() == 0)
		{
			//cout << "delete tblSES: SUCCESS" <<endl;
		}
		else
			return false;
	}
	if(flag[1] == 1)
	{
		try{
			strcpy(cpTemp, "DELETE FROM tblactivation;");
			qySES << cpTemp;
			rsSES = qySES.store();
			qySES.reset();
			//cout << cpTemp << endl;
		}
		catch(BadQuery er)
		{
		//	cerr <<"ERROR: " << er.error << endl;
		}
		//make sure it was deleted:
		strcpy(cpTemp, "SELECT * FROM tblactivation;");
		qySES << cpTemp;
		rsSES = qySES.store();
		qySES.reset();
		if(rsSES.size() == 0)
		{
		//	cout << "delete tblactivation: SUCCESS" <<endl;
		}
		else
			return false;
	}

	cpTemp = NULL;
	cpSQL = NULL;

	return true;

}


INT CSesManager::Post(double dPan, double dTilt, char* name, char* type, char* identifier)
{
	Query	qySES = m_connSES->query();
	CString	cstrSQL;
	Result				resSES;
	char*	cpSQL;
	char	cpID[5];
	char	pan[20];
	char	tilt[20];

	int*	ipIndices;			//i,j indices
	int		iIndexID = 0;		//nodeID
	int		temp;
	int		iSESRecs = 0;

	double	phi,theta;
	bool	blnUpdate = false;	//Update vs Post Flag

	//Convert from pan/tilt to phi/theta
	theta = 90 - dTilt;

	if((dPan >= 0)&&(dPan <= 180))
		phi = dPan;
	else
		phi = dPan + 360;

	
	//First must determine which node is closest
	//Find nodeID from phi/theta
	// all angles will map to a pair of indices or an index ID
	ipIndices = AnglesToIndices(phi, theta);
	temp = ipIndices[0];
	temp = ipIndices[1];
	iIndexID = ipIndices[2];

	// convert nodeID to char* for use in SQL statement
	_itoa(iIndexID, cpID, 10);
	sprintf(tilt, "%G", dTilt);
	sprintf(pan, "%G", dPan);


	// find out if any records in tblSES to see if update or new post
	// select any records that match the name
	qySES << "SELECT * FROM tblses WHERE name = '" << name << "'";
	resSES = qySES.store();
	iSESRecs = resSES.size();
	if(iSESRecs>0)
	{
		ATLTRACE("Selected from tblses, found %d matching records\n", iSESRecs);
		blnUpdate = true;
	}


	if(blnUpdate)
	{
		// update record in SES (and other tables)
		cstrSQL.Insert(0, "'");
		cstrSQL.Insert(0, type);
		cstrSQL.Insert(0, "' AND type = '");
		cstrSQL.Insert(0, name);
		cstrSQL.Insert(0, ", timestamp = NOW() WHERE name = '");
		cstrSQL.Insert(0, tilt);
		cstrSQL.Insert(0, ", tilt = ");
		cstrSQL.Insert(0, pan);
		cstrSQL.Insert(0, ", pan = ");
		cstrSQL.Insert(0, cpID);
		cstrSQL.Insert(0, "UPDATE tblSES SET ID = ");
		cpSQL = cstrSQL.GetBuffer(1);
		qySES.exec(cpSQL);
		cstrSQL.ReleaseBuffer();
		cstrSQL.Empty();
		cpSQL = NULL;
	}
	else
	{
		//post at that node
		cstrSQL.Insert(0, "')");
		cstrSQL.Insert(0, tilt);
		cstrSQL.Insert(0, "', '");
		cstrSQL.Insert(0, pan);
		cstrSQL.Insert(0, ", '");
		cstrSQL.Insert(0, " NOW()");
		cstrSQL.Insert(0, "', ");
		cstrSQL.Insert(0, identifier);
		cstrSQL.Insert(0, "', '");
		cstrSQL.Insert(0, type);
		cstrSQL.Insert(0, "', '");
		cstrSQL.Insert(0, name);
		cstrSQL.Insert(0, ", '");
		cstrSQL.Insert(0, cpID);
		cstrSQL.Insert(0, "INSERT INTO tblSES (ID, name, type, identifier, timestamp, pan, tilt) VALUES (");
		cpSQL = cstrSQL.GetBuffer(1);
		qySES.exec(cpSQL);

		//	ATLTRACE("Inserted new record\n");
		cstrSQL.ReleaseBuffer();
		cstrSQL.Empty();
		cpSQL = NULL;
		qySES.reset();
		
	}

	return iIndexID;
	
}


/*
//Post method for ISAC.  Posts a full image at node location.  saves filename information of img
int SESManager::PostImg(char *Name, char *Type, char *Identifier, double Pan, double Tilt, char *Image_Name)
{
	// MySQL query object
	Query qySES = m_connSES->query();
	
	CString	cstrSQL;
	char*	cpSQL;
	char	cpID[5];
	char	pan[6];
	char	tilt[6];

	int*	ipIndices;			//i,j indices
	int		iIndexID = 0;		//nodeID
	int		temp;
	int		iSESRecs = 0;

	double	phi,theta;


	//find closest node
	
	//Convert from pan/tilt to phi/theta
	theta = 90 - Tilt;

	if((Pan >= 0)&&(Pan <= 180))
		phi = Pan;
	else
		phi = Pan + 360;
	
	//cout << "Phi: " << phi << " Theta: " << theta << endl;

	//Find nodeID from phi/theta
	// all angles will map to a pair of indices or an index ID
	ipIndices = AnglesToIndices(phi, theta);
	temp = ipIndices[0];
	temp = ipIndices[1];
	iIndexID = ipIndices[2];
	
	//cout << "nodeID " << iIndexID << endl;

	// convert nodeID to char* for use in SQL statement
	_itoa(iIndexID, cpID, 10);
	sprintf(pan, "%G", Pan);
	sprintf(tilt, "%G", Tilt);

	//cout << cpID << " " << pan << " " << tilt << endl;

	//post at that node
	cstrSQL.Insert(0, "')");
	cstrSQL.Insert(0, Image_Name);
	cstrSQL.Insert(0, "', '");
	cstrSQL.Insert(0, tilt);
	cstrSQL.Insert(0, "', '");
	cstrSQL.Insert(0, pan);
	cstrSQL.Insert(0, ", '");
	cstrSQL.Insert(0, " NOW()");
	cstrSQL.Insert(0, "', ");
	cstrSQL.Insert(0, Identifier);
	cstrSQL.Insert(0, "', '");
	cstrSQL.Insert(0, Type);
	cstrSQL.Insert(0, "', '");
	cstrSQL.Insert(0, Name);
	cstrSQL.Insert(0, ", '");
	cstrSQL.Insert(0, cpID);
	cstrSQL.Insert(0, "INSERT INTO tblSES (ID, name, type, identifier, timestamp, pan, tilt, image_name) VALUES (");
	cpSQL = cstrSQL.GetBuffer(1);
	qySES.exec(cpSQL);

//	TRACE0("Inserted new record\n");
	cstrSQL.ReleaseBuffer();
	cstrSQL.Empty();
	cpSQL = NULL;
	qySES.reset();

return iIndexID;
	
}
*/



/*	AnglesToIndices converts SES angle values to index values
	A short array is returned with the matching i, j indices and an ID
	Does this by selecting a range of angles w/in 20 degrees of desired angles,
	finding the angle pair w/ the smallest distance from the desired angle
	pair and retreiving the indices that match that node*/
int* CSesManager::AnglesToIndices(float AnglePhi, float AngleTheta)
{

	// MySQL Query object
	Query		qyIndices = m_connSES->query();
	// MySQL Result object
	Result		resNodes;
	
	// holds
	char	str1[20];
	char	str2[20];
	char	str3[20];
	char	str4[20];
	
	// hold either "AND" or "OR" for SQL query for retrieving phi and theta
	char*	cpPhiWhere;
	char*	cpThetaWhere;

	float*	fpPhis;
	float*	fpThetas;
	float	fPhiDist, fThetaDist, fDist;
	float	fMinDist = 100;

	int*	ipI_s;
	int*	ipJ_s;
	int*	ipID_s;
	int		ipIndices[3];
	short	sNumRecs;
	short	sKeep = -1;

	cpPhiWhere = "AND";
	cpThetaWhere = "AND";

	// must set the string to match the data
	// if theta is less than 20 degrees, will need to check thetas <=360
	// so will use an OR in SQL query
	if(AngleTheta < 20.0)
	{
		sprintf(str1, "%e", (AngleTheta + 360 - 20));
		cpThetaWhere = "OR";
	}
	else
		sprintf(str1, "%e", (AngleTheta - 20.0));
	// if theta is >340 degrees, will need to check thetas <=20
	// so will use an OR in SQL query
	if(AngleTheta >= 340)
	{
		sprintf(str2, "%e", (AngleTheta - 360 + 20.0));	
		cpThetaWhere = "OR";
	}
	else
		sprintf(str2, "%e", (AngleTheta + 20.0));
	// if phi is less than 20 degrees, will need to check phis <=360
	// so will use an OR in SQL query
	if(AnglePhi < 20.0)
	{
		sprintf(str3, "%e", (AnglePhi + 360 - 20.0));
		cpPhiWhere = "OR";
	}
	else
		sprintf(str3, "%e", (AnglePhi - 20.0));
	// if phi is >340 degrees, will need to check phis <=20
	// so will use an OR in SQL query
	if(AnglePhi >= 340)
	{
		sprintf(str4, "%e", (AnglePhi - 360 + 20.0));
		cpPhiWhere = "OR";
	}
	else
		sprintf(str4, "%e", (AnglePhi + 20.0));
		
	// insert query to select angles w/in a specific range of phi, theta
	qyIndices << "SELECT ID, i_index, j_index, phi, theta FROM tblNodes WHERE ((" << str3 << " <= phi " << cpPhiWhere << " phi <= " << str4
		<< ") AND (theta <= " << str2 << cpThetaWhere << " theta >= " << str1 << "));";

	// store results
	resNodes = qyIndices.store();
	// get result size
	sNumRecs = resNodes.size();
	// initialize arrays holding query results
	ipID_s	 = new int	[sNumRecs];
	ipI_s    = new int [sNumRecs];
	ipJ_s    = new int [sNumRecs];
	fpPhis	 = new float [sNumRecs];
	fpThetas = new float [sNumRecs];

	// assign iterator to go through result array
	Result::iterator a;
	Row		row;
	int		i = 0;
	// iterate through results
	for(a=resNodes.begin(); a != resNodes.end(); a++)
	{
		// point row to iterator
		row = *a;
		// get values for record being held in row
		ipID_s[i] = row[0];
		ipI_s[i] = row[1];
		ipJ_s[i] = row[2];
		fpPhis[i] = row[3];
		fpThetas[i] = row[4];
		i++;
	}

	// get distances b/tw original angles and result angles
	for(i=0; i<sNumRecs; i++)
	{
		fPhiDist = AnglePhi - fpPhis[i];
		fThetaDist = AngleTheta - fpThetas[i];
		fDist = (float)pow((pow(fPhiDist, 2) + pow(fThetaDist, 2)), 0.5);
		if (fDist < fMinDist)
		{
			// if distance is smallest, keep it
			fMinDist = fDist;
			sKeep = i;
		}
	}

	// get indices that match smallest distance angle pair
	ipIndices[0] = ipI_s[sKeep];
	ipIndices[1] = ipJ_s[sKeep];
	ipIndices[2] = ipID_s[sKeep];

	delete [] ipID_s;
	delete [] ipI_s; 
	delete [] ipJ_s;
	delete [] fpPhis;
	delete [] fpThetas;

	// return indices that match the closest phi,theta angle pair
	return &ipIndices[0];
}


//Converts a pan/tilt angle into a phi/theta angle
double* CSesManager::ConvertToPhiTheta(double dPan, double dTilt)
{
	double phiTheta[2];
	
	//Convert theta
	phiTheta[1] = 90 - dTilt;
	
	//convert phi
	if((dPan >= 0)&&(dPan <= 180))
		phiTheta[0] = dPan;
	else
		phiTheta[0] = dPan + 360;


	return &phiTheta[0];
}

//Converts a phi/theta angle into a pan/tilt angle
double* CSesManager::ConvertToPanTilt(double dPhi, double dTheta)
{
	double panTilt[2];

	//Convert tilt
	panTilt[1] = 90 - dTheta;

	//Convert pan
	if((dPhi >= 0)&&(dPhi <= 180))
		panTilt[0] = dPhi;
	else
		panTilt[0] = dPhi - 360;

	return &panTilt[0];

}
