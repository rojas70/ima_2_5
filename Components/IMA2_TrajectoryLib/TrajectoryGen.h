// TrajectoryGen.h : Declaration of the CTrajectoryGen

#ifndef __TRAJECTORYGEN_H_
#define __TRAJECTORYGEN_H_

#include "resource.h"						// main symbols
#include "O:\Base Classes\ComponentImpl.h"
#include "O:\Components\msvbvm60.tlh"		// property bag dll
#include "O:\Include\IMA2_BasicComponentsLib.h"
#include "O:\Include\IMA2_MatlabStateMachineLib.h"
#include "O:\Include\IMA2_ColorSegmenterLib.h"

#define MAX_PTS 6
#define MAX_STOPS 20		// Potential number of intermediate points in a trajectory
//////////////////////////////////////////////////////////////////////////////////////
// CTrajectoryGen
class ATL_NO_VTABLE CTrajectoryGen : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTrajectoryGen, &CLSID_TrajectoryGen>,
	public IDispatchImpl<ITrajectoryGen, &IID_ITrajectoryGen, &LIBID_IMA2_TRAJECTORYLIBLib>,
	public CComponentImpl 
{
public:
	CTrajectoryGen()
	{
		
		m_pIUnkPoints			= NULL;
		m_pIUnkStateMachine		= NULL;
		m_pIUnkLeftCS			= NULL;
		m_pIUnkRightCS			= NULL;

		for (int i=0;i<MAX_STOPS;i++) {	// Initialize number of steps equally for each 
			m_lNumSteps[i]		= 20;	// independent variable (XYZRPY or JointAngles[1-6])
			m_dTravelPeriod[i]	= 1.0;	/*** In the previous version it was m_lNumSteps[MAX_STOPS]  ***/
		}						

		m_lNumberTrajectoryPoints= 1;		
		m_lNumElements			 = 6;
		m_dStartTime			 = 0.0;

		m_sTravelPeriodIndex	 = 0;
		m_sNumStepsIndex		 = 0;

		m_dSegmentedPixelThreshold= 100;	// 900 ~ For a medium-sized object close to ISAC

		// File Name
		m_bstrOutputFile = SysAllocString(L"");
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TRAJECTORYGEN)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTrajectoryGen)
	COM_INTERFACE_ENTRY(ITrajectoryGen)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()

// ITrajectoryGen
public:
	STDMETHOD(get_SegmentedPixelThreshold)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_SegmentedPixelThreshold)(/*[in]*/ double newVal);
	STDMETHOD(CheckForObject)();
	STDMETHOD(GenerateTrajectory)();
	STDMETHOD(get_OutputFile)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_OutputFile)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_StartTime)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_StartTime)(/*[in]*/ double newVal);
	STDMETHOD(get_NumberTrajectoryPoints)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_NumberTrajectoryPoints)(/*[in]*/ long newVal);
	STDMETHOD(get_TravelPeriod)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_TravelPeriod)(/*[in]*/ double newVal);
	STDMETHOD(get_NumSteps)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_NumSteps)(/*[in]*/ long newVal);
	STDMETHOD(get_NumElements)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_NumElements)(/*[in]*/ long newVal);
	STDMETHOD(get_NumStepsIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_NumStepsIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_TravelPeriodIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_TravelPeriodIndex)(/*[in]*/ short newVal);

// %%INTERFACE: ITrajectoryGen



protected:
	void OpenFile();
	void CloseFile();
	
	long		m_lNumberTrajectoryPoints;				// Number of moves in between MAX_STOPS (or ViaPoints)
	long		m_lNumElements;				// Num Elements normally stands for: XYZRPY, or 6 joint angles
	long		m_lNumSteps[MAX_STOPS];		// Number of stops or intermediate trajectory points

	double		m_dStartTime;
	double		m_dTravelPeriod[MAX_STOPS];

	double		m_dSegmentedPixelThreshold;	// Number of pixels needed in order to generate a trajectory

	BSTR		m_bstrOutputFile;
	FILE *		m_fp;

private:
		// Binding methods
	STDMETHOD(OnConstruct)(void);	// Set bindings
	STDMETHOD(OnDestruct)(void);	// Delete them

	// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT pData);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component

	
	short m_sTravelPeriodIndex;
	short m_sNumStepsIndex;

	// IMA Component Bindings
	IComponent *m_pIUnkPoints;
	IComponent *m_pIUnkStateMachine;
	IComponent *m_pIUnkLeftCS;
	IComponent *m_pIUnkRightCS;
	
};

#endif //__TRAJECTORYGEN_H_
