//////////////////////////////////////////////////////////////////////
// ComponentImpl.h: Inheritable implementation of the IMA2 IComponent interface.
//
// Last Modified: Robert Olivares / Juan Rojas (9/26/04, before that 8/28/01)
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPONENTIMPL_H__1688ECC9_E093_4852_A1D0_949A3F0B4573__INCLUDED_)
#define AFX_COMPONENTIMPL_H__1688ECC9_E093_4852_A1D0_949A3F0B4573__INCLUDED_
#pragma once

#import "O:\Include\Ima2.tlb"					raw_interfaces_only, raw_native_types, no_namespace, named_guids 

// TODO Bindings
// Allow us to access the property bag wrapper class
typedef int _PropertyBagPtr;		// HACK to define PropertyBags in C++
#import		"O:\Include\IMA2_PropertyBags.dll"	raw_interfaces_only, raw_native_types, no_namespace, named_guids	
#include	"O:\components\msvbvm60.tlh" 

// ************************************************************************************
// Used to generate the TLI nd TLH files which must have PropertyBag code removed to work (gut the  _Functions::VT2PB and _Functions::LoadPB functions in the IMA2_Helper.tli file)
// #import "C:\IMA2\System\Framework\IMA2_Helper.dll" no_namespace // this statment is copied from MSDN help file

// Contains definitions for things, but must have above two functions gutted to work
#include	"O:\components\ima2_helper.tlh"
// ************************************************************************************




class CComponentImpl : public IComponent
{
	// ************************************************************************************************************
	// Public member variables
	// ************************************************************************************************************
	public:

		/*
		These are included in the struct definition of IMA2_DistributingInfo

		BSTR					m_Path;			// The full path and name of this component.
		BSTR					m_Machine;		// The machine that this component was created.
		BSTR					m_PID;			// The ProgID of this component.
		long					m_Process;		// The Process ID of this component.
		long					m_Thread;		// The Thread ID of this component.
		*/

		IMA2_DistributingInfo	m_Info;					// Contains all the information the distributing layer needs to function
		ILocator *				m_Locator;				// The pointer for the locator where this component is registered.
		IBindings *				m_Bindings;				// The pointer for the our bindings collection.
		IConfigureBindings *	m_ConfigureBindings;	// The interface that allows us to configure the bindings collection.
		VARIANT					m_VBPropertyBag;		// Contains the pointer to the VB PropertyBag we obtain from our IMA2 Property Bag Wrapper class. (return this from IComponent::Save())
		int						m_lDataSize;			// Contains the size of the data saved in an IMA25 object

	public:

	// ************************************************************************************************************
	// Constructor & Destructor
	// ************************************************************************************************************
		// Constructor
		CComponentImpl::CComponentImpl()	
		{ 
			m_Info.IsContainer	= false;	// Default is false; DERIVED container classes should change this to TRUE.
			m_Info.Name			= NULL;
			m_Info.Path			= NULL;
			m_Info.Machine		= NULL;
			m_Info.PID			= NULL;
			m_Info.Process		= 0;
			m_Info.Thread		= 0;
			
			m_Locator			= NULL;
			m_Bindings			= NULL;
			m_ConfigureBindings = NULL;

			
			// Initialize the variant that will hold our propertybag pointer.
			VariantInit(&m_VBPropertyBag);	// standard method in VBRUN (msvbvm60.dll)
			
			// Initialize the size of the data for an object
			m_lDataSize = 0;
		}

		// Destructor
		CComponentImpl::~CComponentImpl()	
		{
			// If our IComponent.Destruct() function hasn't been called, call it now.
			if (m_Info.Path != NULL) Destruct();		
		}

	// ************************************************************************************************************
	// Overrideable events for derived classes
	// ************************************************************************************************************

		// Called after the component has been constructed and its Locator, Name, PID, and Machine fields filled.
		virtual STDMETHODIMP OnConstruct(void)	{return S_OK;}

		// Called right before the component has been destructed and its Locator, Name, PID, and Machine fields released.
		virtual STDMETHODIMP OnDestruct(void)	{return S_OK;}

	// ************************************************************************************************************
	// Basic IMA2 component implementation of IComponent::Construct() and IComponent::Destruct(). 
	//
	// These two functions should *not* be overridden. Instead, it is reccommended that the 
	// OnActivate and OnDeactivate events be overridden for customization.
	// ************************************************************************************************************

		virtual STDMETHODIMP Construct (BSTR Path, BSTR PID, ILocator ** AL)
		{
			USES_CONVERSION;									// Needed any time an String Conversion MACRO like OLE is used.
			char	cn[]	= "                            ";	// Computer name buffer
			ULONG	cns		= sizeof(cn);						// Actual computer name size
						
			// Check to make sure we haven't been constructed before.
			if (m_Info.Path != NULL) return(E_FAIL);

			// Check to make sure we're not being incorrectly constructed.
			if ((Path == NULL) || (PID == NULL)) return(E_FAIL);

			// Retrieve this computer's name (buffer, size)
			GetComputerName(cn, &cns);

			// Copy our Bstrings and fill in other information
			m_Info.Path			= SysAllocString(Path);
			m_Info.PID			= SysAllocString(PID);
			m_Info.Machine		= SysAllocString(T2OLE(cn));
			m_Info.Process		= GetCurrentProcessId();
			m_Info.Thread 		= GetCurrentThreadId();
			m_Info.IsContainer	= false;

			// Retrieve our component's name from its path
			m_Info.Name			= NameFromPath(Path);
			BSTR	Owner	= SysAllocString(m_Info.Path);		// Assign Path


			// ********Get a pointer to the event service to publish our activation/deactivation.
			// ********m_ES = CreateObject("IMA2_EventService.EventService");	(wants class/server name)

			// Get our lovely Locator.
			m_Locator	= *AL;
			m_Locator->AddRef();

			// Code added on 11/26/04
			// After mending some code, the rest of the VB IComponent Construct is completed below.			

			// Do BINDINGS
			//////////////////////////////////////////////////////////////////////////////	
			// Declare the Interface Pointer for your Visual Basic object. Here,
			// pFunctions is the Smart pointer wrapper class representing the
			// Default interface of the Visual Basic object.
			// Functions is the class that contains the GetBindingsObject() used below
			//////////////////////////////////////////////////////////////////////////////

			// Object to hold the Bindings Object and Configure Bindings
			_Functions * pIFunctions;
			IBindingsPtr	pIBP;

			// Use SMART POINTERS to reach the Functions interface that is part of Helper.dll
			//_COM_SMARTPTR_TYPEDEF(_Functions, __uuidof(_Functions));

			 // Create Instance of pFunctions
		     HRESULT hres=CoCreateInstance(__uuidof(Functions), NULL, CLSCTX_INPROC_SERVER, __uuidof(_Functions), (LPVOID*)&pIFunctions);

			 // Create the bindings object
			 if (pIFunctions == NULL)	
				 return !S_OK;

			 pIBP = pIFunctions->GetBindingsObject();

			 m_Bindings = (struct IBindings *)pIBP;
			 m_Bindings->AddRef();

			// Construct the bindings collection
			hres=pIBP->get_Settings(&m_ConfigureBindings);
			
			// Construct our bindings collection.
			hres=m_ConfigureBindings->Construct(Owner, AL);

			// Fire off the "event" to derived classes.
			OnConstruct();

			return S_OK;
		}

		/*
		virtual STDMETHODIMP CreateBindingsObject(void)
		{
			...
		}
		*/

		virtual STDMETHODIMP Destruct ()
		{
			HRESULT hres;
			
			// We aren't constructed or have already been destructed.
			if (m_Info.Path == NULL) return(E_FAIL);

			// Pass on the message to derived classes.
			hres = OnDestruct();
			
			// Free our internal memory stores
			SysFreeString(m_Info.Name);
			SysFreeString(m_Info.Path);
			SysFreeString(m_Info.PID);
			SysFreeString(m_Info.Machine);

			// Eliminate the bindings collection if we have one.
			if (m_Bindings != NULL) 
			{
				m_ConfigureBindings->Destruct();
				m_ConfigureBindings->Release();
				m_Bindings->Release();				// Gives unhandled exception
			}

			m_Locator->Release();
			return hres;
		}

	// ************************************************************************************************************
	// Basic Distributed Programming Functions
	// ************************************************************************************************************

		virtual STDMETHODIMP get_Distributing (struct IMA2_DistributingInfo * pInfo)
		{
			// Create a copy of our data to return.
		
			(*pInfo).Name			= SysAllocString(m_Info.Name);
			(*pInfo).Path			= SysAllocString(m_Info.Path);
			(*pInfo).PID 			= SysAllocString(m_Info.PID);
			(*pInfo).Machine		= SysAllocString(m_Info.Machine);
			(*pInfo).IsContainer	= m_Info.IsContainer;
			(*pInfo).Process		= m_Info.Process;
			(*pInfo).Thread			= m_Info.Thread;

			return S_OK;
		}

	// ************************************************************************************************************
	// Binding Functions
	// ************************************************************************************************************

		virtual STDMETHODIMP get_Bindings(IBindings ** pRetVal)
		{
			if (m_Bindings != NULL) m_Bindings->AddRef();
			*pRetVal = m_Bindings;
			return S_OK;
		}


	// ************************************************************************************************************
	// Persistence functions
	// ************************************************************************************************************

		// Template to Load Data for classes
		virtual STDMETHODIMP Load (VARIANT Data)
		{
			// Variables
			BSTR					ItemName1 = NULL;	// Holds the name of a given item to be writen into a PropertyBag
			_PropertyBagWrapper*	pIPB;			// COM Interface Pointer to the PropertyBag _Wrapper_ Class
			HRESULT					hRes;			// The HRESULT value we get back from COM calls.

			// (1) Create the property bag wrapper class
			// (2) Have the class point to the interface 
			hRes = CoCreateInstance(CLSID_PropertyBagWrapper, NULL, CLSCTX_INPROC_SERVER, IID__PropertyBagWrapper, (LPVOID*)&pIPB);
			{
				if (pIPB == NULL)	
					return !S_OK;
				
				// Pass Data to PropertyBag
				hRes = pIPB->SetPropertyBag(&Data);

				// Define strings
				ItemName1 = SysAllocString(L"VectorValueX");	// Assign to Item1 the name of your variable

				// Read Data from the property bag
				//hRes = pIPB->GetFromPropertyBag(&ItemName1);
			}
				// Decrement the pointer reference count from our member variable. 
				VariantClear(&m_VBPropertyBag);
				
				// Release
				pIPB->Release();

			return S_OK;
		}

	////////////////////////////////////////////////////////////////////////////////////////////
	// The SAVE Method makes use of property bags. Originally we wanted to import
	// the msvbvm60.dll which contains this function call. However, the dll does 
	// not have an export declaration in it and thus can't be imported.
	// To get around it, an IMA2_PropertyBags.dll was created. It returns a pointer
	// that points to the PropertyBag of the respective component.
	// To access this PropertyBag from C++ we have to create a wrapper class that contains
	// a pointer to the PropertyBag found in Visual Basic.
	// That is what this function does.
	//
	// Last Changed: Roberto Olivares 9/26/04
	////////////////////////////////////////////////////////////////////////////////////////////
		virtual STDMETHODIMP Save (VARIANT * pVal)
		{
			// Variables
			BSTR					ItemName = NULL;// The string holding the name of the item to write into the property bag.
			VARIANT					ItemValue;

			HRESULT					hRes;			// The HRESULT value we get back from COM calls.
			_PropertyBagWrapper*	pIPB;			// COM Interface Pointer to the PropertyBag _Wrapper_ Class


			// Create Class with CoCreateInstance (definition can be found in MSDN).
			// Create the property bag wrapper class, put pointer to the Interface in pIPB
			hRes = CoCreateInstance(CLSID_PropertyBagWrapper, NULL, CLSCTX_INPROC_SERVER, IID__PropertyBagWrapper, (LPVOID*)&pIPB);
	
			{
				
				ItemName = SysAllocString(L"VectorValueX");		// Allocate the string and cast it with L to a 2 byte char (look up ANSI and Unicode strings)
				VariantInit(&ItemValue);						// Initialize our variant (does not free existing one)

				// Add an item to the property bag via the wrapper class.
				hRes = pIPB->AddToPropertyBag(&ItemName, &ItemValue);

				// Release the string
				SysFreeString(ItemName);

			}

			// Get the pointer to the real VB property bag (the VB object (defined in msvbvm60.dll (aka VBRUN)) that our wrapper class created)
			hRes = pIPB->GetPropertyBag(&m_VBPropertyBag);
			
			// Copy the value VB gave to us into the return value of this function (which will be returned to whatever's calling our save function)
			VariantCopy(pVal, &m_VBPropertyBag);

			// Decrement the pointer reference count from our member variable. 
			VariantClear(&m_VBPropertyBag);

			// Release
			pIPB->Release();

			return S_OK;
		}

		virtual STDMETHODIMP DataSize (LONG * pVal)
		{
			*pVal = m_lDataSize;
			return S_OK;
		}


	// ************************************************************************************************************
	// Non-IComponent utility functions for simplifying things. Callable from inheriting class.
	// ************************************************************************************************************

	protected:

		// Returns whether or not a COM object is an IMA2 container as well.
		bool IsContainer(IUnknown *pObj)
		{
			IUnknown *pCI = NULL;

			// Check for NULL pointer.
			if (pObj == NULL) return false;

			// Obtain a pointer to IContainer interface if possible, then release on success.
			pObj->QueryInterface(IID_IContainer, (void **)&pCI);
			if (pCI != NULL) 
			{
				pCI->Release();
				return true;
			}
			else
			{
				return false;
			}
		}

		// Locates and copies just the name from a path string of the form "\\Locator\Parent\Child".
		// The result string will contain "child" and must be deallocated by the caller.
		BSTR NameFromPath(BSTR Path)
		{
			#define uint unsigned int

			uint	i;
			uint	NameLen;
			uint	PathLen		= SysStringLen(Path);
			uint	NameStart	= 0;
			BSTR	Result		= NULL;

			// Check for no path.
			if (PathLen == 0) return NULL;

			// Search path string backwards for last slash character (#92)
			for (i = PathLen - 1; i > 0; i--)
				if (Path[i] == 92) { NameStart = i + 1; break; }

			// Allocate space for our name string
			NameLen = PathLen - NameStart;
			Result	= SysAllocStringLen(NULL, NameLen);

			// Copy just the name over to our result string
			for (i = NameStart; i < PathLen; i++)
				Result[i - NameStart] = Path[i];

			return Result;
		}

		// Initializes the bindings collection for this object.
		STDMETHODIMP InitializeBindings()
		{
			HRESULT		hres;
			CLSID		BCID;
			BSTR		Owner	= SysAllocString(m_Info.Path);
			ILocator *	AL		= m_Locator;

			if (m_Bindings != NULL) return E_FAIL;

			m_Locator->AddRef();
				
			// Need to get its CLSID, create the object, get configuration interface, and construct it.
			#pragma warning(disable: 4530)
			try 
			{
				hres = CLSIDFromProgID(L"IMA2_Bindings.Bindings", &BCID);
				hres = CoCreateInstance(BCID, NULL, CLSCTX_SERVER, IID_IBindings, (void **)&m_Bindings);
				hres = m_Bindings->QueryInterface(IID_IConfigureBindings, (void **)&m_ConfigureBindings);
				hres = m_ConfigureBindings->Construct(Owner, &AL);
			}
			catch (...)
			{
				return hres;
			}

			return hres;
		}

		// Adds a simple binding to the bindings list.
		STDMETHODIMP AddSimpleBinding(OLECHAR * Name)
		{
			IMA2_BindingInfo		BindInfo;
			HRESULT					hres;

			// If the bindings collection doesn't exist...
			if (m_Bindings == NULL) 
			{
				hres = InitializeBindings();		// Create one.
				if (hres != 0) return hres;			// Something happened, so return the error.
			}

			// Set up the binding information structure.
			BindInfo.IIDs		= NULL;
			BindInfo.PIDs		= NULL;
			BindInfo.Path		= NULL;
			BindInfo.BindType	= BT_Default;
			BindInfo.Name		= SysAllocString(Name);

			// Call the bindings object to add us to its list.
			hres = m_ConfigureBindings->Add(&BindInfo);
			
			// Clean up
			SysFreeString(BindInfo.Name);
			return hres;
		}

		// Retrieves a pointer to a specified interface on the given binding, NULL if not bound.
		void * GetBinding(UCHAR * Name, REFIID riid)
		{

			HRESULT		hres;
			IUnknown *	pIUnk;
			void *		retval;

			hres = m_Bindings->get_Pointers((unsigned short*)Name, (IComponent **)&pIUnk);
			if (hres != S_OK) return NULL;

			hres = pIUnk->QueryInterface(riid, &retval);
			if (hres != S_OK) return NULL;

			return retval;
		}

		STDMETHODIMP ValidatePointers(int NumPointers, void * Ptr1, ...)
		{
			va_list			vl;
			IUnknown **		Ptrs = NULL;
			int				NullCount = 0;
			int				i = 0;

			if (NumPointers <= 0) return E_FAIL;

			Ptrs = (IUnknown **)malloc(NumPointers * sizeof(IUnknown *));

			Ptrs[0] = (IUnknown *)Ptr1;
			if (Ptrs[0] == NULL) NullCount++;

			va_start( vl, Ptr1 );

			// Step through the list and count invalid pointers.
			for(i = 1; i >= NumPointers - 1; i++ )
			{
				Ptrs[i] = va_arg( vl, IUnknown *);
				if (Ptrs[i] == NULL) NullCount++;
				// Attempt to TRY/CATCH and AddRef/Release pair here to confirm functional pointer.
			}

			va_end( vl );

			// If any invalid pointers were found, go through the list and release the valid ones.
			if (NullCount > 0)
			{
				for(i = 0; i >= NumPointers - 1; i++ )
					if (Ptrs[i] != NULL) (IUnknown *)Ptrs[i]->Release();
				return E_FAIL;
			}

			return S_OK;
		}

};

#endif // !defined(AFX_COMPONENTIMPL_H__1688ECC9_E093_4852_A1D0_949A3F0B4573__INCLUDED_)
