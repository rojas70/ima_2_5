// Testing123.cpp : Implementation of CTesting123
#include "stdafx.h"
#include "TestComp.h"
#include "Testing123.h"

/////////////////////////////////////////////////////////////////////////////
// CTesting123

STDMETHODIMP CTesting123::OnConstruct()
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

		Binding.Name		= SysAllocString(L"Test");			// Assign name to object
		Binding.BindType	= BT_Default;									// Condition to accept one connection
		Binding.Path		= SysAllocString(L"");							// This must be the path of our component
		Binding.PIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);	// Create and empty string array
		Binding.IIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);	// The thrid parameter is the number of elements in the array
																			// Be careful not to use sizeof() commonly used in memcpy

		//If you wish to specify that a particular binding references only one
		//kind of component (e.g. VectorSignal), uncomment the code below,
		//and change the strings to the proper PID and IID. PIDs can be found
		//by creating a new component in DAD and looking at the PID in the
		//"Create New" dialog or in the list of properties on the bottom-right
		//of the main window. (Leave off the .1 at the end of the listed PID.)

		//x[0]=0; //specifies first element
		//SafeArrayPutElement(BindInf.PIDs,x,(void *)SysAllocString(L"IMA2_BasicComponentsLib.VectorSignal"));
		//SafeArrayPutElement(BindInf.IIDs,x,(void *)SysAllocString(L"IVectorSignal"));

		//If you wish to allow more than one type of component, set "numiids" 
		//to the proper count (instead of 1) in the uncommented code above. Then, for each component,
		//copy the code above, increment x[0] and set the PID and IID strings
		//correctly.
		//NOTE: Be sure that, if you are setting up another binding after this,
		//numiids is set back to 1. (This should happen automatically if you 
		//followed the instructions and copied everything from "Start" to "Finish")

		m_ConfigureBindings->Add(&Binding);								// Set up the clients bindings array.
				

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

STDMETHODIMP CTesting123::OnDestruct()
{
	//////////////////
	// Cleanup Code //
	//////////////////
	//Put code here that undoes/deallocates any leftover variables

	return S_OK;
}

STDMETHODIMP CTesting123::Save(VARIANT *pData)
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
	// A CString can be converted to a BSTR using the member function AllocSysString (see CString 
	// documentation). If you get a weird exception, try using "new variant_t(variable);" (That is,
	// don't use a VarType.)
	//
	// If you want to save an array, you have to assign a SAFEARRAY to the Variant. (Do NOT just
	// use a pointer, it will save just one value). replace the line starting "ItemValue =" with the following 
	// code (substituting your pointer for "variable", the array length for "numelem", int/float/double, etc. 
	// for "Type", and using the VarType of one element of the array--BSTR arrays are not allowed.):
	//
	//	ItemValue = new variant_t;
	//	ItemValue->vt=VT_ARRAY|VarType;
	//	ItemValue->parray=SafeArrayCreateVector(VarType,0,numelem);
	//	memcpy(ItemValue->parray->pvData,variable,numelem*sizeof(Type));
	//
	// Also, add the line SafeArrayDestroy(ItemValue->parray); before "delete ItemValue"
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

	double dArr[5]={0.0,1.3,4.9,8,32.7};
	float fArr[4]={2.2f,4.6f,3.2f,7.7f};
	int iArr[5]={2,5,7,19,45};
	short sArr[6]={4,7,2,7,9,34};
	float f=6.0f;

	// Create Class with CoCreateInstance (definition can be found in MSDN).
	// Create the property bag wrapper class, put pointer to the Interface in pIPB
	hRes = CoCreateInstance(CLSID_PropertyBagWrapper, NULL, CLSCTX_INPROC_SERVER, IID__PropertyBagWrapper, (LPVOID*)&pIPB);

	if (pIPB == NULL)	
		return !S_OK;

	//**START**
		ItemName = SysAllocString(L"FloatTest");
		ItemValue = new variant_t(f);
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		SysFreeString(ItemName);
		delete ItemValue;
	//**FINISH**
	//**START**
		// Create string names for items to be saved
		ItemName = SysAllocString(L"DoubleArray");
		// Store the data and the type of data into a variant_t type
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_R8;
		ItemValue->parray=SafeArrayCreateVector(VT_R8,0,5);
	    memcpy(ItemValue->parray->pvData,dArr,5*sizeof(double));
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Delete our variants
		delete ItemValue;
	//**FINISH**

	//**START**
		// Create string names for items to be saved
		ItemName = SysAllocString(L"FloatArray");
		// Store the data and the type of data into a variant_t type
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_R4;
		ItemValue->parray=SafeArrayCreateVector(VT_R4,0,4);
	    memcpy(ItemValue->parray->pvData,fArr,4*sizeof(float));
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Delete our variants
		delete ItemValue;
	//**FINISH**

	//**START**
		// Create string names for items to be saved
		ItemName = SysAllocString(L"IntArray");
		// Store the data and the type of data into a variant_t type
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_I4;
		ItemValue->parray=SafeArrayCreateVector(VT_I4,0,5);
	    memcpy(ItemValue->parray->pvData,iArr,5*sizeof(int));
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Delete our variants
		delete ItemValue;
	//**FINISH**

	//**START**
		// Create string names for items to be saved
		ItemName = SysAllocString(L"ShortArray");
		// Store the data and the type of data into a variant_t type
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_I2;
		ItemValue->parray=SafeArrayCreateVector(VT_I2,0,6);
	    memcpy(ItemValue->parray->pvData,sArr,6*sizeof(short));
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
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

STDMETHODIMP CTesting123::Load(VARIANT Data)
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
	// If you are not dynamically allocating the array, you might want to check that cElements is
	// the right size. (This will only be a problem if you specified the save size wrong or there's
	// something wrong with our property bag interface code. Let us know if you catch something we
	// didn't!) Then just copy the values from the parray (replace the "variable =" line with this):
	//
	//	memcpy(variable,ItemValue->parray->pvData,ItemValue->parray->rgsabound->cElements*sizeof(Type));
	//
	// Note that this means you do not have to separately save the length of the array, although if
	// you have a variable that keeps track of the array length you should also set it at this point:
	//
	//  numelem=ItemValue->parray->rgsabound->cElements;
	//
	// Also, to avoid a memory leak, add "SafeArrayDestroy(ItemValue->parray)" before "delete ItemValue".

	BSTR					ItemName = NULL;// The string holding the name of the item to write into the property bag.
	variant_t*				ItemValue;
	HRESULT					hRes;			// The HRESULT value we get back from COM calls.
	_PropertyBagWrapper*	pIPB;			// COM Interface Pointer to the PropertyBag _Wrapper_ Class

	double dArr[5];
	float fArr[4];
	int iArr[5];
	short sArr[6];

	// (1) Create the property bag wrapper class
	// (2) Have the class point to the interface 
	hRes = CoCreateInstance(CLSID_PropertyBagWrapper, NULL, CLSCTX_INPROC_SERVER, IID__PropertyBagWrapper, (LPVOID*)&pIPB);

	if (pIPB == NULL)	
		return hRes;

	// Pass Data to PropertyBag
	hRes = pIPB->SetPropertyBag(&Data);


	//**START**
		// Define strings
		ItemName = SysAllocString(L"DoubleArray");
		ItemValue=new variant_t;
		// Read Data from the property bag
		hRes=pIPB->GetArrayFromPropertyBag(&ItemName, ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(dArr,ItemValue->parray->pvData,ItemValue->parray->rgsabound->cElements*sizeof(double));
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;
	//**FINISH**
	//**START**
		// Define strings
		ItemName = SysAllocString(L"FloatArray");
		ItemValue=new variant_t;
		// Read Data from the property bag
		pIPB->GetArrayFromPropertyBag(&ItemName, ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(fArr,ItemValue->parray->pvData,ItemValue->parray->rgsabound->cElements*sizeof(float));
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;
	//**FINISH**
	//**START**
		// Define strings
		ItemName = SysAllocString(L"IntArray");
		ItemValue=new variant_t;
		// Read Data from the property bag
		pIPB->GetArrayFromPropertyBag(&ItemName, ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(iArr,ItemValue->parray->pvData,ItemValue->parray->rgsabound->cElements*sizeof(int));
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;
	//**FINISH**
	//**START**
		// Define strings
		ItemName = SysAllocString(L"ShortArray");
		ItemValue=new variant_t;
		// Read Data from the property bag
		pIPB->GetArrayFromPropertyBag(&ItemName, ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(sArr,ItemValue->parray->pvData,ItemValue->parray->rgsabound->cElements*sizeof(short));
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



STDMETHODIMP CTesting123::SendDouble(SAFEARRAY *Data)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	double *dd;
	dd=new double[Data->rgsabound->cElements];

	for(int i=0;i<Data->rgsabound->cElements;i++)
		dd[i]=i*1.1;

	memcpy(Data->pvData,dd,sizeof(double)*Data->rgsabound->cElements);

	return S_OK;
}
