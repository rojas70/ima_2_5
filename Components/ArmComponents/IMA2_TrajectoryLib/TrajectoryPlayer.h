// TrajectoryPlayer.h : Declaration of the CTrajectoryPlayer

#ifndef __TrajectoryPlayer_H_
#define __TrajectoryPlayer_H_

#include "resource.h"						 // main symbols
#include "O:\Base Classes\ComponentImpl.h"
#include "O:\Components\msvbvm60.tlh"		// property bag dll
#include "O:\Include\IMA2_BasicComponentsLib.h"
#include "O:\Include\IMA2_MatlabStateMachineLib.h"

#define AXIS_MAX 10
/////////////////////////////////////////////////////////////////////////////
// CTrajectoryPlayer
class ATL_NO_VTABLE CTrajectoryPlayer : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTrajectoryPlayer, &CLSID_TrajectoryPlayer>,
	public IDispatchImpl<ITrajectoryPlayer, &IID_ITrajectoryPlayer, &LIBID_IMA2_TRAJECTORYLIBLib>,
	public CComponentImpl 
{
public:
	CTrajectoryPlayer()
	{
		int i;

		m_lVersion			= 1;
		m_lNumAxes			= 3;
		m_lLoop				= 0;
		m_lLoopCounter		= 0;
		m_bDone				= FALSE;

		m_dLastRealTime		= 0.0;
		m_dNextTrajPoint	= 0.0;
		m_dTrajTime			= 0.0;
		m_dLastTrajTime		= 0.0;
		m_dTimeScale		= 1.0;

		for(i=0;i<AXIS_MAX;i++)
		{
			m_plAxisMask[i] = 1;
			//m_pdArbValue[i] = 1;
			m_dLastCmd[i]	= 0.0;
			m_pdOrgPos[i]	= 0.0;
		}

		m_dLastTrajPoint[0] = 450.0;
		m_dLastTrajPoint[1] = -250.0;
		m_dLastTrajPoint[2] = -600.0;
		m_dLastTrajPoint[3] = 0.0;
		m_dLastTrajPoint[4] = 0.0;
		m_dLastTrajPoint[5] = 0.0;

		m_fp				= NULL;	
		m_pIUnkOut			= NULL;
		m_pIUnkStateMachine	= NULL;
		m_bstrInputFile		= SysAllocString(L"");

		//m_lReplayMode=REPLAY_MODE_ABS | REPLAY_MODE_TIME;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TRAJECTORYPLAYER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTrajectoryPlayer)
	COM_INTERFACE_ENTRY(ITrajectoryPlayer)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()

// ITrajectoryPlayer
public:
	STDMETHOD(get_FileName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_FileName)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_NumAxes)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_NumAxes)(/*[in]*/ long newVal);
	STDMETHOD(Initialize)();
	STDMETHOD(OutputTrajectory)();

private:
	// Local private functions
	void CloseFile();
	void OpenFile();
	
	// Member variables
	BOOL		m_bDone;

	long		m_lVersion;
	long		m_lNumAxes;

	long		m_lLoop;
	long		m_lLoopCounter;

	BSTR		m_bstrInputFile;

	long		m_plAxisMask[AXIS_MAX];
	double		m_dTimeScale;

	double		m_dTrajTime;
	double		m_dLastTrajTime;
	double		m_dLastRealTime;

	double		m_dNextTrajPoint;
	double		m_dLastTrajPoint[AXIS_MAX];

	double		m_pdOrgPos[AXIS_MAX];
	double		m_dLastCmd[AXIS_MAX+2];

	FILE *		m_fp;

	IComponent *m_pIUnkOut;

	// Private IMA functions
	// Binding methods
	STDMETHOD(OnConstruct)(void);	// Set bindings
	STDMETHOD(OnDestruct)(void);	// Delete them

	// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT pData);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component

	IComponent	*m_pIUnkStateMachine;

};

#endif //__TrajectoryPlayer_H_
