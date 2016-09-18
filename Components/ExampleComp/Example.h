// Example.h : Declaration of the CExample

#ifndef __EXAMPLE_H_
#define __EXAMPLE_H_

#include "resource.h"       // main symbols
#include "O:\Base Classes\ComponentImpl.h"
#include "O:\Components\msvbvm60.tlh" // property bag dll
#include "O:\Include\IMA2_BasicComponentsLib.h"

/////////////////////////////////////////////////////////////////////////////
// CExample
class ATL_NO_VTABLE CExample : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CExample, &CLSID_Example>,
	public IDispatchImpl<IExample, &IID_IExample, &LIBID_EXAMPLECOMPLib>,
	public CComponentImpl
{
public:
	CExample()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_EXAMPLE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CExample)
	COM_INTERFACE_ENTRY(IExample)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()

// IExample
public:
	STDMETHOD(ConnectingToComponent)();	//This is what it looks like when
										//you add a method to the interface

	virtual STDMETHODIMP Load(VARIANT Data);
	virtual STDMETHODIMP Save(VARIANT *pData);

private:

	STDMETHOD(OnConstruct)(void);	// Set bindings
	STDMETHOD(OnDestruct)(void);	// Delete them

	double variable;

};

#endif //__EXAMPLE_H_
