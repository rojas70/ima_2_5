// PanTiltUnit.cpp : Implementation of CPanTiltUnit
#include "stdafx.h"
#include "IMA2_PanTiltLaser.h"
#include "PanTiltUnit.h"

/////////////////////////////////////////////////////////////////////////////
// CPanTiltUnit


STDMETHODIMP CPanTiltUnit::OnConstruct()
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
		//Scan Range Input

		// The first element is degrees to move,
		// The second element is the maximum degree value for the range.
		// The third element is the minimum degree value for the range.

		numiids=1;

		Binding.Name		= SysAllocString(L"ScanRangeInput");			// Assign name to object
		Binding.BindType	= BT_Default;									// Condition to accept one connection
		Binding.Path		= SysAllocString(L"");							// This must be the path of our component
		Binding.PIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);	// Create and empty string array
		Binding.IIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);	// Create and empty string array
		m_ConfigureBindings->Add(&Binding);									// Set up the clients bindings array.

		// I'll add the state machine in later

		//Binding.Name = SysAllocString(L"StateMachine");
		//m_ConfigureBindings->Add(&Binding);


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

STDMETHODIMP CPanTiltUnit::OnDestruct()
{
	//////////////////
	// Cleanup Code //
	//////////////////
	//Put code here that undoes/deallocates any leftover variables

	return S_OK;
}

STDMETHODIMP CPanTiltUnit::Save(VARIANT *pData)
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

/*	//**START**
		// Create string names for items to be saved
		ItemName = SysAllocString(L"DescriptiveName");
		// Store the data and the type of data into a variant_t type
 		ItemValue = new variant_t(variable,VarType);
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Delete our variants
		delete ItemValue;
*/	//**FINISH**

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

 STDMETHODIMP CPanTiltUnit::Load(VARIANT Data)
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

/*	//**START**
		// Define strings
		ItemName = SysAllocString(L"DescriptiveName");
		ItemValue=new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName, ItemValue);  //2nd argument is return value
		variable = (Type)* ItemValue;
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;
*/	//**FINISH**
		
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

/*------------------------------------------------------------------------------

	Method Name:			InitLaser()

	Purpose:		This function runs the initialization code for the laser pan-tilt unit.

	Written by:            Joe Hall
	Created from code by:  Chris Garber
	Date:                  5/25/05

-------------------------------------------------------------------------------*/

STDMETHODIMP CPanTiltUnit::InitLaser()
{
	// TODO: Add your implementation code here

	if(!lv.Initlaser())
	{
		cout << "Failed to initialize COM port!" << endl;
		return S_OK;
	}
	else



	return S_OK;
}

/*------------------------------------------------------------------------------

	Method Name:			HomeLaser()

	Purpose:		This function sends the PTU to the home position.

	Written by:            Joe Hall
	Created from code by:  Chris Garber
	Date:                  5/25/05

-------------------------------------------------------------------------------*/

STDMETHODIMP CPanTiltUnit::HomeLaser()
{
	// TODO: Add your implementation code here

	lv.Homelaser();
	Sleep(2000); // Sleep is necessary to allow the laser to move and 
	             // get there in time.
	return S_OK;
}

/*------------------------------------------------------------------------------

	Method Name:			ResetLaser()

	Purpose:		This function resets the pan-tilt unit for the laser.

	Written by:            Joe Hall
	Created from code by:  Chris Garber
	Date:                  5/25/05

-------------------------------------------------------------------------------*/

STDMETHODIMP CPanTiltUnit::ResetLaser()
{
	// TODO: Add your implementation code here

	lv.Resetlaser();
	Sleep(2000); // Sleep is necessary to allow the laser to move and 
	             // get there in time.

	return S_OK;
}

/*------------------------------------------------------------------------------

	Method Name:			Scan()

	Purpose:		This function performs the actual scan. The scan is defined by
					the degrees2move, max position, and min position of the pan-tilt
					unit for the laser.

	Written by:            Joe Hall
	Created from code by:  Chris Garber
	Date:                  5/25/05

-------------------------------------------------------------------------------*/

STDMETHODIMP CPanTiltUnit::Scan()
{
	// TODO: Add your implementation code here

	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	IVectorSignal   *pIVSScan = NULL;
	SAFEARRAY*      mysaScan;
	double			scaninput[3];

	m_Bindings->get_Pointers(SysAllocString(L"ScanRangeInput"),&IUnkScanRangeInput);

	if(IUnkScanRangeInput != NULL)
	{
		IUnkScanRangeInput->QueryInterface(IID_IVectorSignal,(void**)&pIVSScan);

		if(pIVSScan != NULL)
		{

			//Get Scan Input 
			mysaScan=SafeArrayCreateVector(VT_R8,0,3);
			pIVSScan->GetCurrentVector( mysaScan );
			memcpy(scaninput,mysaScan->pvData,sizeof(double)*3);  //memcpy(destination, source, size of bytes)
			//now want to send it to interface
			SafeArrayDestroy(mysaScan);

			// Deallocate pointers
			pIVSScan->Release();
			pIVSScan = NULL;

		}
	}

    // I will need to read from the vector signal at this point and get 
	// deg2move, max and min

	degree = (int)scaninput[0];
	maxup = (int)scaninput[1];    // get the information from scaninput
	maxdown = (int)scaninput[2];

	//degree = 5;
	//maxup = 0;       // These values are the default values
	//maxdown = -45;   // This was used for testing

	if(degree > 0) 
		numberofscans=((maxup - maxdown)/degree -1); // get the number of scans
	else
		numberofscans=0; // this is to prevent div/0.

	lv.Movelaser(maxup); // move the laser to the maxup position to begin scans


	for(int i=0;i<numberofscans;++i)
	{
		if(dir == 1)
			degreedir = degree;   // begin scanning
		else
			degreedir= degree * -1;
		lv.Movelaser(degreedir);
	
		Sleep(200);
	}

	Sleep(2000);


	return S_OK;
}
