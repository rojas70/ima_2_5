// SES.h : Declaration of the CSES

#ifndef __SES_H_
#define __SES_H_

#include "resource.h"							  // main symbols
#include "O:\Base Classes\ComponentImpl.h"
#include "O:\Components\msvbvm60.tlh"			// property bag dll
#include "O:\Include\IMA2_BasicComponentsLib.h" // Vector Signal
#include "O:\Include\IMA2_ImageRepLib.h"		//Image Representation
//#include "CreateNewSES.h"
#include "SESManager.h"
#include "FGate.h"
#include <iostream>
#include "CImg.h"
  using namespace cimg_library;

//class CFGate;
//class CSESManager;

/////////////////////////////////////////////////////////////////////////////
// CSES
class ATL_NO_VTABLE CSES : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSES, &CLSID_SES>,
	public IDispatchImpl<ISES, &IID_ISES, &LIBID_IMA2_SESLIBLib>,
	public CComponentImpl 
{
public:
	CSES()
	{
 		m_sLevels			= 0;   //0 for 1 level only, 1 for all levels
		imgInd				= 0;
		m_lNumLocs			= 12;
		m_pdPanTiltAngles	= NULL;
		m_DBname			= SysAllocString(L"dbses_kat");

		m_pdPanTiltAngles	= new double[6];
		for (int i=0;i<6;i++)
			m_pdPanTiltAngles[i]=0.0;	//am I using this?


	}

DECLARE_REGISTRY_RESOURCEID(IDR_SES)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSES)
	COM_INTERFACE_ENTRY(ISES)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()

// ISES
public:
	STDMETHOD(test)();
	void(RunFGate)(BSTR image_name, int iNodeID, int iNumPts);
	STDMETHOD(ResetSES)();
	STDMETHOD(get_DatabaseName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_DatabaseName)(/*[in]*/ BSTR newVal);
	STDMETHOD(ProcessImage)();
	STDMETHOD(get_NumAttnLocations)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_NumAttnLocations)(/*[in]*/ long newVal);
	STDMETHOD(get_FeatureGateLevels)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_FeatureGateLevels)(/*[in]*/ short newVal);
	STDMETHOD(CalculateSalience)();

	virtual STDMETHODIMP Load(VARIANT Data);
	virtual STDMETHODIMP Save(VARIANT *pData);

private:

	STDMETHOD(OnConstruct)(void);	// Set bindings
	STDMETHOD(OnDestruct)(void);	// Delete them
	double* m_pdPanTiltAngles;

	FGate myFGate;
	SESManager sesMan;

	short m_sLevels;
	long  m_lNumLocs;
	int imgInd;

	BSTR				m_DBname;
	BYTE*				InputImage;	
};

#endif //__SES_H_
