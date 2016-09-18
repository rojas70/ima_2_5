// trialobj.h : Declaration of the Ctrialobj

#ifndef __TRIALOBJ_H_
#define __TRIALOBJ_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// Ctrialobj
class ATL_NO_VTABLE Ctrialobj : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<Ctrialobj, &CLSID_trialobj>,
	public IDispatchImpl<Itrialobj, &IID_Itrialobj, &LIBID_TRIALLib>
{
public:
	Ctrialobj()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TRIALOBJ)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(Ctrialobj)
	COM_INTERFACE_ENTRY(Itrialobj)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// Itrialobj
public:
};

#endif //__TRIALOBJ_H_
