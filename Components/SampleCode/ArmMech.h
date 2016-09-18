// ArmMech.h : Declaration of the CArmMech

#ifndef __ARMMECH_H_
#define __ARMMECH_H_

#include "resource.h"       // main symbols
#include "O:\Base Classes\ComponentImpl.h"
#include "O:\Components\msvbvm60.tlh"

/////////////////////////////////////////////////////////////////////////////
// CArmMech
class ATL_NO_VTABLE CArmMech : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CArmMech, &CLSID_ArmMech>,
	public IDispatchImpl<IArmMech, &IID_IArmMech, &LIBID_IMA2_ARMCOMPONENTLib>,
	public CComponentImpl
{
public:
	CArmMech()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ARMMECH)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CArmMech)
	COM_INTERFACE_ENTRY(IArmMech)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()

// IArmMech
public:
	STDMETHOD(DoNothing2)(SAFEARRAY hello, int sit);
	STDMETHOD(DoNothing)(SAFEARRAY* hello);
	STDMETHOD(RunArm)();

	// Create one entry for each binding that this component will support.
	IMA2_BindingInfo		m_BindingVectorSignal;		// BindingInfo for the VS binding

// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT Data);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component

private:

	STDMETHOD(OnConstruct)(void);	// Set bindings
	STDMETHOD(OnDestruct)(void);	// Delete them
};

#endif //__ARMMECH_H_
