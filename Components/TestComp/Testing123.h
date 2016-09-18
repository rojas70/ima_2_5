// Testing123.h : Declaration of the CTesting123

#ifndef __TESTING123_H_
#define __TESTING123_H_

#include "resource.h"       // main symbols
#include "O:\Base Classes\ComponentImpl.h"
#include "O:\Components\msvbvm60.tlh" // property bag dll

/////////////////////////////////////////////////////////////////////////////
// CTesting123
class ATL_NO_VTABLE CTesting123 : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTesting123, &CLSID_Testing123>,
	public IDispatchImpl<ITesting123, &IID_ITesting123, &LIBID_TESTCOMPLib>,
	public CComponentImpl
{
public:
	CTesting123()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TESTING123)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTesting123)
	COM_INTERFACE_ENTRY(ITesting123)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()

// ITesting123
public:
	STDMETHOD(SendDouble)(/*[out,retval]*/ SAFEARRAY *Data);
	virtual STDMETHODIMP Load(VARIANT Data);
	virtual STDMETHODIMP Save(VARIANT *pData);

private:

	STDMETHOD(OnConstruct)(void);	// Set bindings
	STDMETHOD(OnDestruct)(void);	// Delete them

	
};

#endif //__TESTING123_H_
