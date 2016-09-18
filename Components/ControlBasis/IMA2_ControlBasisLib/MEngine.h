// MEngine.h : Declaration of the CMEngine

#ifndef __MENGINE_H_
#define __MENGINE_H_

#include "resource.h"       					// main symbols
#include "O:\Base Classes\ComponentImpl.h"		// Component Lib file
#include "O:\Components\msvbvm60.tlh"			// property bag dll
// If you have bindings with other components, include their header file here.
// # Define's go here.
/////////////////////////////////////////////////////////////////////////////
// CMEngine
class ATL_NO_VTABLE CMEngine : 
	public CComObjectRootEx<CComSingleThreadModel>,	
	public CComCoClass<CMEngine, &CLSID_MEngine>,
	public IDispatchImpl<IMEngine, &IID_IMEngine, &LIBID_MATLAB_TESTLib>,
	public CComponentImpl 
{
public:
	CMEngine()
	{
		// TODO: Initialize all variables in constructor
	
	}


DECLARE_REGISTRY_RESOURCEID(IDR_MENGINE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMEngine)
	COM_INTERFACE_ENTRY(IMEngine)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()
// IMEngine
// This is where all your interface methods will appear and be displayed on DAD
public:
	STDMETHOD(get_Prompt)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Prompt)(/*[in]*/ BSTR newVal);
	STDMETHOD(Test)();

	//void mexFunction(int, mxArray*,int, mxArray*);

private:

	BSTR	m_bstrPrompt;

// Binding methods
STDMETHOD(OnConstruct)(void);	// Set bindings
STDMETHOD(OnDestruct)(void);	// Delete them
// Override of IMA base components
virtual STDMETHODIMP Load(VARIANT pData);
virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component
// Include IMA Component Bindings of type IComponent *

};

#endif //__MENGINE_H_
