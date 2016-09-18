// SESInterface.h : Declaration of the CSESInterface

#ifndef __SESINTERFACE_H_
#define __SESINTERFACE_H_

#include "resource.h"       // main symbols

#include "O:\Base Classes\ComponentImpl.h"
#include "O:\Components\msvbvm60.tlh" // property bag dll


/////////////////////////////////////////////////////////////////////////////
// CSESInterface
class ATL_NO_VTABLE CSESInterface : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSESInterface, &CLSID_SESInterface>,
	public IDispatchImpl<ISESInterface, &IID_ISESInterface, &LIBID_IMA2_SESINTERFACELib>,
	public CComponentImpl 
{
public:
	CSESInterface()
	{

		m_DBname			= SysAllocString(L"dbses_isac");

	}

DECLARE_REGISTRY_RESOURCEID(IDR_SESINTERFACE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSESInterface)
	COM_INTERFACE_ENTRY(ISESInterface)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()

// ISESInterface
public:
	STDMETHOD(Post)();
	STDMETHOD(ResetSES)();
	STDMETHOD(get_DatabaseName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_DatabaseName)(/*[in]*/ BSTR newVal);

	virtual STDMETHODIMP Load(VARIANT Data);
	virtual STDMETHODIMP Save(VARIANT *pData);

private:

	STDMETHOD(OnConstruct)(void);	// Set bindings
	STDMETHOD(OnDestruct)(void);	// Delete them

	SESManager			sesMan;		//sesManager

	BSTR				m_DBname;	//Database name



};

#endif //__SESINTERFACE_H_
