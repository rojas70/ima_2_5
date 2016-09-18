// CopyVS.h : Declaration of the CCopyVS

#ifndef __COPYVS_H_
#define __COPYVS_H_

#include "resource.h"       // main symbols
#include "O:\Base Classes\ComponentImpl.h"
#include "O:\Components\MultiTypeComponents\IMA2_BasicComponentsLib\IMA2_BasicComponentsLib.h"		//VectorSignal functionality

#define MAX_VECTORS 10
#define MAX_LEN 20

/////////////////////////////////////////////////////////////////////////////
// CCopyVS
class ATL_NO_VTABLE CCopyVS : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCopyVS, &CLSID_CopyVS>,
	public IDispatchImpl<ICopyVS, &IID_ICopyVS, &LIBID_IMA2_COPYREPSLIBLib>,
	public CComponentImpl
{
public:
	CCopyVS() 
	{
		// Input/Output row vectors
		m_sInputRowVector	= 0;
		m_sOutputRowVector	= 0;

		m_pIUnkIn	= NULL;
		m_pIUnkOut	= NULL;
	}


DECLARE_REGISTRY_RESOURCEID(IDR_COPYVS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCopyVS)
	COM_INTERFACE_ENTRY(ICopyVS)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()

// Input/Output RowVector
	short	m_sInputRowVector;
	short	m_sOutputRowVector;

// ICopyVS
	IComponent *	m_pIUnkIn;
	IComponent *	m_pIUnkOut;

// Create one entry for each binding that this component will support.
	IMA2_BindingInfo		m_BindingInput;			// BindingInfo to link to input  VS
	IMA2_BindingInfo		m_BindingOutput;		// BindingInfo to link to output VS


// Internal constuctor/destructor
	STDMETHOD(OnConstruct)(void);
	STDMETHOD(OnDestruct)(void);

public:
	STDMETHOD(CopyCurrentVector)();
	STDMETHOD(get_OutputRowVector)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_OutputRowVector)(/*[in]*/ short newVal);
	STDMETHOD(get_InputRowVector)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_InputRowVector)(/*[in]*/ short newVal);
	STDMETHOD(CopyRowVector)();
	STDMETHOD(CopyVectorSignal)(/*ULONG operation, ULONG flags*/);
private:

	// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT pData);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component

};

#endif //__COPYVS_H_
