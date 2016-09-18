// SES.cpp : Implementation of CSES
#include "stdafx.h"
#include "IMA2_SESLib.h"
#include "SES.h"
#include <fstream>

/////////////////////////////////////////////////////////////////////////////
// CSES
STDMETHODIMP CSES::OnConstruct()
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
//		long x[1];
		IMA2_BindingInfo Binding;

		//**START**
		numiids=1;

		// 1. Input Image
		Binding.Name		= SysAllocString(L"InputImage");				// Assign name to object
		Binding.BindType	= BT_Default;									// Condition to accept one connection
		Binding.Path		= SysAllocString(L"");							// This must be the path of our component
		Binding.PIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);	// Create and empty string array
		Binding.IIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);	// Create and empty string array
		m_ConfigureBindings->Add(&Binding);								// Set up the clients bindings array.
			
		// 2. Head Angles
		Binding.Name		= SysAllocString(L"PTActualAngles");				// Assign name to object
		m_ConfigureBindings->Add(&Binding);								// Set up the clients bindings array.

		// 3. Salient Information
		Binding.Name		= SysAllocString(L"SalientInfo");				// Assign name to object
		m_ConfigureBindings->Add(&Binding);	// Set up the clients bindings array.


		// 4. SalientHeadAngles
		Binding.Name		= SysAllocString(L"SalientHeadAngles");				// Assign name to object
		m_ConfigureBindings->Add(&Binding);	// Set up the clients bindings array.
		
		// Free Binding Info
		SysFreeString(Binding.Name);
		SysFreeString(Binding.Path);
		SafeArrayDestroy(Binding.PIDs);
		SafeArrayDestroy(Binding.IIDs);
		//**FINISH**

	return hRes;
}

STDMETHODIMP CSES::OnDestruct() { return S_OK;}

STDMETHODIMP CSES::Save(VARIANT *pData)
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
	// A CString can be converted to a BSTR using the member function AllocSysString (see CString documentation)
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
	// Note: "delete ItemValue" will take care of destroying the safearray (do *not* call SafeArrayDestroy).
	// Because of the nature of a SafeArray, you do not have to explicitly save the length of the array.
	// However, due to the nature of property bags, you must call the array version of the Add function:
	//
	//  hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
	//
	// (See Load comments for how to extract arrays from the propertybag).

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



	//**START**
		//FG processing with Levels or not
		// Create string names for items to be saved
		ItemName = SysAllocString(L"Levels");
		// Store the data and the type of data into a variant_t type
 		ItemValue = new variant_t(m_sLevels,VT_I2);
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Delete our variants
		delete ItemValue;


		//Not needed right now
		//Number of Attn Locs to return for individual Image when doing FG processing
		// Create string names for items to be saved
		ItemName = SysAllocString(L"NumAttnLocs");
		// Store the data and the type of data into a variant_t type
 		ItemValue = new variant_t(m_lNumLocs,VT_I4);
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Delete our variants
		delete ItemValue;


		//Name of DB to use
		// Create string names for items to be saved
		ItemName = SysAllocString(L"DBName");
		ItemValue = new variant_t(m_DBname);		// Variant stores variable as a BSTR 
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Delete our variants
		delete ItemValue;

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

STDMETHODIMP CSES::Load(VARIANT Data)
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
	//  memcpy(variable,ItemValue->parray->pvData,ItemValue->parray->rgsabound->cElements*sizeof(Type));
	//
	// Note that this means you do not have to separately save the length of the array, although if
	// you have a variable that keeps track of the array length you should also set it at this point:
	//
	//  numelem=ItemValue->parray->rgsabound->cElements;
	//

	BSTR					ItemName = NULL;// The string holding the name of the item to write into the property bag.
	variant_t*				ItemValue;
	HRESULT					hRes;			// The HRESULT value we get back from COM calls.
	_PropertyBagWrapper*	pIPB;			// COM Interface Pointer to the PropertyBag _Wrapper_ Class

	// (1) Create the property bag wrapper class
	// (2) Have the class point to the interface 
	hRes = CoCreateInstance(CLSID_PropertyBagWrapper, NULL, CLSCTX_INPROC_SERVER, IID__PropertyBagWrapper, (LPVOID*)&pIPB);

	if (pIPB == NULL)	
		return !S_OK;

	// Pass Data to PropertyBag
	hRes = pIPB->SetPropertyBag(&Data);


	//**START**
		// Define strings
		ItemName = SysAllocString(L"Levels");
		ItemValue=new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName, ItemValue);  //2nd argument is return value (look retval for help)
		m_sLevels = (short)* ItemValue;
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Define strings
		ItemName = SysAllocString(L"NumAttnLocs");
		ItemValue=new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName, ItemValue);  //2nd argument is return value (look retval for help)
		m_lNumLocs = (long)* ItemValue;
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;
		
		//DB name
		// Define strings
		ItemName = SysAllocString(L"DBName");
		ItemValue=new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName, ItemValue);  //2nd argument is return value (look retval for help)
		SysReAllocString(&m_DBname,ItemValue->bstrVal);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;
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




STDMETHODIMP CSES::CalculateSalience()
{
	// TODO: Add your implementation code here
	SAFEARRAY* mysaNode;
	SAFEARRAY* mysaAngles;
	IComponent *IUnkMostSalient	= NULL;
	IComponent *IUnkSalientAngles = NULL;
	IVectorSignal *pIVSnodeID	=NULL;		// for nodeID and activation
	IVectorSignal *pIVSangles = NULL;	//for headangles
	double salientTempArray[4];
	double salientIDArray[2];
	double salientHeadArray[4];

	//bindings
	m_Bindings->get_Pointers(SysAllocString(L"SalientInfo"),&IUnkMostSalient);
	m_Bindings->get_Pointers(SysAllocString(L"SalientHeadAngles"),&IUnkSalientAngles);

	if(IUnkMostSalient != NULL && IUnkSalientAngles !=NULL)	
	{
		IUnkMostSalient->QueryInterface(IID_IVectorSignal,(void**)&pIVSnodeID);
		IUnkSalientAngles->QueryInterface(IID_IVectorSignal,(void**)&pIVSangles);

		if(pIVSnodeID != NULL && pIVSangles != NULL)	
		{
	
			//Calculate FOA location
			sesMan.ReturnFOA(salientTempArray);
			//get nodeID and activation
			salientIDArray[0] = salientTempArray[0];
			salientIDArray[1] = salientTempArray[1];
			//get Head Angles
			salientHeadArray[0] = salientTempArray[2];
			salientHeadArray[1] = salientTempArray[3];
			salientHeadArray[2] = salientHeadArray[3] = 0;  //not using right camera yet
			
			//Write this information to a VectorSignal to be used by aaHeadCommand and to be displayed
			//on DAD..can that be the same one?
			//node info
			mysaNode=SafeArrayCreateVector(VT_R8,0,2);
			memcpy(mysaNode->pvData,salientIDArray,sizeof(double)*2);  //memcpy(destination, source, sizeof bytes)
			//now want to send it to interface like this?
			pIVSnodeID->SetCurrentVector( mysaNode );
			SafeArrayDestroy(mysaNode);
			//headangles info
			mysaAngles=SafeArrayCreateVector(VT_R8,0,4);
			memcpy(mysaAngles->pvData,salientHeadArray,sizeof(double)*4);  //memcpy(destination, source, sizeof bytes)
			//now want to send it to interface like this?
			pIVSangles->SetCurrentVector( mysaAngles );
			SafeArrayDestroy(mysaAngles);

			// Deallocate pointers
			pIVSnodeID->Release();
			pIVSnodeID = NULL;
			pIVSangles->Release();
			pIVSangles = NULL;
			
		}
	}

	return S_OK;	
}



STDMETHODIMP CSES::ProcessImage()
{
	//This function:
	//Connects to Image,
	//Runs FeatureGate Processing
	//Posts all information in appropriate tables

	// TODO: Add your implementation code here
	//Figure out image filename
	int						iNodeID;
	char					cData[50];
	char					filename[150] = "myImage";
	BSTR					nameStr = NULL;
	int						row = 240;
	int						col = 320;
	char dirName[100] = "C:\\Images\\";  


	imgInd++;
	itoa(imgInd, cData, 10);
	strcat(filename, cData); 
	strcat(filename, ".bmp");

	strcat(dirName, filename);

	//Get head angles
	SAFEARRAY *mysa;
	IComponent *IUnkHeadAngles	= NULL;
	IVectorSignal *pIVS	= NULL;		// Used to write data from the new head 

	m_Bindings->get_Pointers(SysAllocString(L"PTActualAngles"),&IUnkHeadAngles);

	if (IUnkHeadAngles!=NULL)			// Added to ensure failure detection
		IUnkHeadAngles->QueryInterface(IID_IVectorSignal,(void **)&pIVS);

	if ( pIVS != NULL )
	{
		//Your Code here! 
		//You can directly call any function of the interface.
		//For example: IVS->GetCurrentVector(mydata);
		mysa=SafeArrayCreateVector(VT_R8,0,6);
		pIVS->GetCurrentVector( mysa );
		memcpy(m_pdPanTiltAngles,mysa->pvData,sizeof(double)*6);
		SafeArrayDestroy(mysa);

		pIVS->Release();
		pIVS=NULL;
	}


	// Get input image
	IComponent* m_pIUnkImgIn = NULL;
	IImageRep*	pImgIn = NULL;
	long	lIn;				// Trick variable

	// Get pointer to ImageIn Representation
	m_Bindings->get_Pointers(SysAllocString(L"InputImage"),&m_pIUnkImgIn);
	if(m_pIUnkImgIn!=NULL)
	{
		// Get pointer to the interface of that representation
		m_pIUnkImgIn->QueryInterface(IID_IImageRep,(void **)&pImgIn);
		if( pImgIn != NULL)			// Successful query?
		{
			// Get Image Buffers
			pImgIn->Data( 0, &lIn );	// Place data in lIn
			InputImage = (BYTE*) lIn;	// Cast it and save it
		
		//	MessageBox(NULL, "in 2", "in 2", MB_OK);
			//Need to SAVE IMAGE TO FILE HERE
			CImg<unsigned char> inImg(col,row,1,3,0);
			
			for(int y=0; y<row; y++)
			{
				for(int x=0; x<col; x++)
				{
					inImg(x,y,0,2) = InputImage[(y*col*3)+(x*3)];		//blue
					inImg(x,y,0,1) = InputImage[(y*col*3)+(x*3)+1];		//green
					inImg(x,y,0,0) = InputImage[(y*col*3)+(x*3)+2];		//red
			
				}
			}
		//	MessageBox(NULL, "in 3", "in 3", MB_OK);
			inImg.save(dirName);
		//	MessageBox(NULL, "in 4", "in 4", MB_OK);
			//ofstream outImg(dirName);  //?
			//for(int i=0;i<320*240*3;i++)
			//	outImg << InputImage[i];
			//outImg.close();
		}
		// Deallocate dynamic memory
		pImgIn->Release();	
	}




	
	//post Image on SES
	iNodeID = sesMan.PostImg(cData, "fovea", "imgsegment", m_pdPanTiltAngles[0], m_pdPanTiltAngles[1], filename);
	
	//process image

	// Define strings
	USES_CONVERSION;
	nameStr = SysAllocString(T2OLE(filename));
	//HOW TO PUT FILENAME IN nameStr?

	RunFGate(nameStr, iNodeID, m_lNumLocs);
	SysFreeString(nameStr);


	return S_OK;
}

STDMETHODIMP CSES::ResetSES()
{
	// TODO: Add your implementation code here
	bool bRetVal;
	
	bRetVal = sesMan.DumpAllData();
	imgInd = 0;
	if(bRetVal)
		ATLTRACE("Task Complete \n");
	else
		ATLTRACE("DumpAllData operation was unsuccessful \n");

	return S_OK;
}

void CSES::RunFGate(BSTR image_name, int iNodeID, int iNumPts)
{
	// TODO: Add your implementation code here
	CImg<double>* ciSalientPts;
	bool bRetVal;
	char * fname;
		
	//get BSTR back to char
	fname = (char*)malloc(_bstr_t(image_name).length());
	strcpy(fname,(char*)_bstr_t(image_name));

	//process image
	ciSalientPts = myFGate.featureGate(fname, iNumPts, m_sLevels);
	
	//post attentional points on SES in appropriate table
	bRetVal = sesMan.PostAttnPts(ciSalientPts, iNodeID);
	
	delete ciSalientPts;

}

STDMETHODIMP CSES::test()
{
	// TODO: Add your implementation code here

	return S_OK;
}


STDMETHODIMP CSES::get_FeatureGateLevels(short *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_sLevels;
	return S_OK;
}

STDMETHODIMP CSES::put_FeatureGateLevels(short newVal)
{
	// TODO: Add your implementation code here
	m_sLevels = newVal;
	return S_OK;
}


STDMETHODIMP CSES::get_NumAttnLocations(long *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_lNumLocs;
	return S_OK;
}

STDMETHODIMP CSES::put_NumAttnLocations(long newVal)
{
	// TODO: Add your implementation code here
	m_lNumLocs = newVal;
	return S_OK;
}


STDMETHODIMP CSES::get_DatabaseName(BSTR *pVal)
{
	// TODO: Add your implementation code here
	*pVal = SysAllocString(m_DBname);
	ATLTRACE("get_DatabaseName: getting database name. \n");
	return S_OK;
}

STDMETHODIMP CSES::put_DatabaseName(BSTR newVal)
{
	// TODO: Add your implementation code here
	SysReAllocString(&m_DBname,newVal);
	ATLTRACE("put_DatabaseName: setting database name. \n");
	return S_OK;
}