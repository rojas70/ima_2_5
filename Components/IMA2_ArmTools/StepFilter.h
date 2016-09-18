// StepFilter.h : Declaration of the CStepFilter

#ifndef __STEPFILTER_H_
#define __STEPFILTER_H_

#include "resource.h"       // main symbols
#include "O:\Base Classes\ComponentImpl.h"
#include "O:\Components\msvbvm60.tlh"				// property bag dll
#include "O:\Include\IMA2_BasicComponentsLib.h"		// Vector Signal 
#define NUM_AXES 6 
/////////////////////////////////////////////////////////////////////////////
// CStepFilter
class ATL_NO_VTABLE CStepFilter : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStepFilter, &CLSID_StepFilter>,
	public IDispatchImpl<IStepFilter, &IID_IStepFilter, &LIBID_IMA2_ARMTOOLSLib>,
	public CComponentImpl 
{
public:
	CStepFilter()
	{
		for(int i=0;i<NUM_AXES;i++)
			m_pdAlpha[i]=0.75;

		m_sAlphaIndex = m_sAngleSpeedIndex = 0;

		// TODO: Setup component links
		m_pIUnkVectorIn= NULL;
		m_pIUnkVectorOut= NULL;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_STEPFILTER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStepFilter)
	COM_INTERFACE_ENTRY(IStepFilter)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()

// IStepFilter

	short m_sAlphaIndex;
	short m_sAngleSpeedIndex;

	double m_pdAlpha[NUM_AXES];
	
	IComponent * m_pIUnkVectorIn;
	IComponent * m_pIUnkVectorOut;

public:
	STDMETHOD(FilterDesiredAngles)();
	STDMETHOD(get_AlphaIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_AlphaIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_alpha)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_alpha)(/*[in]*/ double newVal);

private:
	STDMETHOD(OnConstruct)(void);
	STDMETHOD(OnDestruct)(void);

	// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT pData);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component

};

#endif //__STEPFILTER_H_
