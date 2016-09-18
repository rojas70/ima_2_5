// PanTiltUnit.h : Declaration of the CPanTiltUnit

#ifndef __PANTILTUNIT_H_
#define __PANTILTUNIT_H_

#include "resource.h"       // main symbols
//#include "commport.h"       // Communicating with pan-tilt unit
#include "laser.h"
#include "O:\Base Classes\ComponentImpl.h"   // Added by Joe
#include "O:\Components\msvbvm60.tlh" // property bag dll
#include "O:\Include\IMA2_BasicComponentsLib.h" // Vector Signals
//#include "O:\Include\IMA2_MatlabStateMachineLib.h" // Matlab State Machine

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 


/////////////////////////////////////////////////////////////////////////////
// CPanTiltUnit
class ATL_NO_VTABLE CPanTiltUnit : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPanTiltUnit, &CLSID_PanTiltUnit>,
	public IDispatchImpl<IPanTiltUnit, &IID_IPanTiltUnit, &LIBID_IMA2_PANTILTLASERLib>,
	public CComponentImpl // added by Joe
{
public:
	CPanTiltUnit()
	{
		IUnkScanRangeInput = NULL; // this will hold degrees2move, max, and min
		degree = 0;
		maxup = 0;
		maxdown = 0;
		numberofscans=0;
		dir = 0;
		degreedir = 0;

	}

DECLARE_REGISTRY_RESOURCEID(IDR_PANTILTUNIT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPanTiltUnit)
	COM_INTERFACE_ENTRY(IPanTiltUnit)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()

// IPanTiltUnit
public:
	STDMETHOD(Scan)();
	STDMETHOD(ResetLaser)();
	STDMETHOD(HomeLaser)();
	STDMETHOD(InitLaser)();

	virtual STDMETHODIMP Load(VARIANT Data);
	virtual STDMETHODIMP Save(VARIANT *pData);

	IComponent *IUnkScanRangeInput;


private:

	STDMETHOD(OnConstruct)(void); // Set bindings
	STDMETHOD(OnDestruct)(void); // Delete bindings

	laser lv;    // laser variables declared
	double degree;
	int maxup;
	int maxdown;
	int numberofscans;
	int dir;
	double degreedir;

};

#endif //__PANTILTUNIT_H_
