// Example.cpp : Implementation of CExample
#include "stdafx.h"
#include "ExampleComp.h"
#include "Example.h"

/////////////////////////////////////////////////////////////////////////////
// CExample

// The following file was put together by Christina Campbell on 9/21/05,
// to help people creating a component for the first time.
// Copy the functions OnConstruct, OnDestruct, Load, and Save into
// your own C++ code, change "CExample" to the name of your own class
// for all of them, and then carefully read the instructions to
// customize the code.
//
// The first function, ConncectingToComponent, contains template code
// for how to call the functions of a component to which this component
// has a binding. Do not copy the entire function. Instead, you should
// clip out the code inside, paste it at all the places in your code
// you want to connect to a component, and alter it to your specific
// needs based on the comments in the function.
//
// Finally, any functions that you are going to put on the interface have
// a very limited number of things that can be arguments:
// VARIANT, int, short, double, float, and SAFEARRAY. You can make any
// argument be a pointer to one of these types, but in order to actally
// pass an array in or out, you have to use a SAFEARRAY. You must specify
// the SAFEARRAY type in the .idl file. (e.g. SAFEARRAY(double)) It should
// probably be a SAFEARRAY* in your .h file (and .cpp file), though.
// You can get to the data in an incoming SAFEARRAY by setting a local
// variable (typecast to the appropriate type to the member pvData:
//
//   double* locdata;
//   locdata=(double*)mysafearray->pvData;
//
// If you want to keep the data beyond the function, however, you should
// copy out the elements (or use memcpy as described in Load and Save on
// how to deal with arrays).
//
// In order to put a function on the Interface, click the ClassView tab of
// the workspace window, right click on the interface name (e.g. IVectorSignal)
// and choose "Add Method...". All Methods will have the HRESULT return type, so
// all output variables must be by reference.
//
// To make an interface variable, choose "Add Property...". If you want to
// make it so that a user can read, but not change, a property value, deselect
// the option of making a "put" function in the Add Property dialog box.
//
// Any questions should be directed to Juan Rojas or Christina Campbell
// I can be contacted at christina.l.campbell@vanderbilt.edu

STDMETHODIMP CExample::ConnectingToComponent()
{
	// This is not actually a function, but an example of how to connect
	// to a component that you made a binding to (see OnConstruct for 
	// how to make a binding.)
	// In order to actually connect to a component-specific interface
	// (e.g IVectorSignal), you must #include the .h file belonging to
	// that interface (common .h files are available in O:\Include),
	// and added to the project its companion _i.c file. You should 
	// also make sure that all _i.c files have been set to NOT include
	// precompiled headers. Go to the Project Menu, click on settings, 
	// choose the C/C++ tab, and select the PreCompiled Headers category. 
	// To connect to a component, simply copy the following code anywhere
	// (in any function) you want to connect to a component, replace
	// "InternalName" with the name of the binding you want, as specified
	// in OnConstruct, replace "IVectorSignal" with the interface name of
	// the interface you want, and "IID_IVectorSignal" with its IID (which
	// usually just means replacing the IVectorSignal part with the name
	// of the interface you want). You'll probably also want to rename IVS,
	// since that is an abbreviation of IVectorSignal :)
	// IMPORTANT:
	// You have to run this code *every* time you want to connect to another
	// component. There is no guarantee that Comp or IVS will be valid the
	// next time you want them (even if you eliminate the "Release" line
	// in this code). It's much safer to just go through the whole 
	// process each time.

	IComponent *Comp	= NULL;
	IVectorSignal *IVS	= NULL;		// Used to connect to the interface of a component later on.

	m_Bindings->get_Pointers(SysAllocString(L"InternalName"),&Comp);	// Connect to the component

	if (Comp!=NULL)			// Added to ensure failure detection, it ensures that there is a connection to the component
		Comp->QueryInterface(IID_IVectorSignal,(void **)&IVS);			// Connect to the interface

	if ( IVS != NULL )
	{
		//Your Code here! 
		//You can directly call any function of the interface you have connected to. 
		//For example: IVS->GetCurrentVector(mydata);

		IVS->Release();
		IVS=NULL;
	}
	return S_OK;
}

STDMETHODIMP CExample::OnConstruct()
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

		Binding.Name		= SysAllocString(L"DescriptiveName");			// Assign name to object
		Binding.BindType	= BT_Default;									// Condition to accept one connection
		Binding.Path		= SysAllocString(L"");							// This must be the path of our component
		Binding.PIDs		= SafeArrayCreateVector(VT_BSTR, 0, 1);			// Create an empty string array
		Binding.IIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);	// Create an empty string array

		x[0]=0; //specifies first element
		SafeArrayPutElement(Binding.IIDs,x,(void *)SysAllocString(L"InterfaceName"));

		//It is *strongly* recommended that you use the two lines above to limit the
		//type of component allowed in the bind to one that has the type of interface
		//you are using. For example, if you were binding to a vectorsignal, as in the
		//ConnectingToComponent function above, you would replace "InterfaceName" with
		//"IVectorSignal".

		//It is possible to allow more than one kind of interface in the restriction, by
		//changing "numiids" to the number of allowed interfaces, then copying the above two
		//lines, incrementing x[0], and changing InterfaceName to the appropriate string.
		//However, this is not recommended unless you actually want to allow both interfaces
		//on this one binding, and are calling QueryInterface for both interfaces.

		//As of February 2006, restricting Binding by PID is unavailable.
		

		m_ConfigureBindings->Add(&Binding);								// Set up the clients bindings array.
				

		// Free Binding Info
		SysFreeString(Binding.Name);
		SysFreeString(Binding.Path);
		SafeArrayDestroy(Binding.PIDs);
		SafeArrayDestroy(Binding.IIDs);
		//**FINISH**

	return hRes;
}

STDMETHODIMP CExample::OnDestruct()
{
	//////////////////
	// Cleanup Code //
	//////////////////
	//Put code here that undoes/deallocates any leftover variables

	return S_OK;
}

STDMETHODIMP CExample::Save(VARIANT *pData)
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
		// Create string names for items to be saved
		ItemName = SysAllocString(L"DescriptiveName");
		// Store the data and the type of data into a variant_t type
 		ItemValue = new variant_t(variable,/*VarType*/VT_I4);
		// Add an item to the property bag via the wrapper class.
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

STDMETHODIMP CExample::Load(VARIANT Data)
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
		ItemName = SysAllocString(L"DescriptiveName");
		ItemValue=new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName, ItemValue);  //2nd argument is return value (look retval for help)
		variable = (/*Type*/)* ItemValue;
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

