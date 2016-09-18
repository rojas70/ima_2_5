// HomingController.h : Declaration of the CHomingController

#ifndef __HOMINGCONTROLLER_H_
#define __HOMINGCONTROLLER_H_

#include "resource.h"								// main symbols
#include "O:\Base Classes\ComponentImpl.h"
#include "O:\Components\msvbvm60.tlh"				// property bag dll
#include "O:\Include\IMA2_BasicComponentsLib.h"		// Vector Signal 
#include "O:\Include\IMA2_MatlabStateMachineLib.h"			// Matlab State Machine

#define NUM_AXES 6
/////////////////////////////////////////////////////////////////////////////
// CHomingController
class ATL_NO_VTABLE CHomingController : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CHomingController, &CLSID_HomingController>,
	public IDispatchImpl<IHomingController, &IID_IHomingController, &LIBID_IMA2_ARMTOOLSLib>,
	public CComponentImpl 

{
public:
	CHomingController()
	{
		// Steps
		m_CurrentStep		=   0;
		m_BaseStep			=   0;
		m_delta_pressure	= 100;				// Next three used for MoveThroughDexterousWorkspace()
		m_stage				=   0;				// i.e. by default start at stage 1 in the arm routine
		m_counter			=   0;				// It actually holds the value for the pressure level
		y_axis_counter		=	0;				// It measures the number of times we will move the arm through the y-axis

		m_NumAxes			= NUM_AXES;			// Useful default
		m_dHomingSteps		= 50.0;				// Useless default

		// Left arm
		m_LeftArm			= 0;
			
		for (int index=0; index<NUM_AXES; index++)
		{
			m_pOutputMax[index] = 2000.0;		// Reasonable default range as set in AgentBuilder for RightArm Agent
			m_pOutputMin[index] =-2000.0;
		}

		m_pOutputMax[0] = 1200.0;				// As set in agent builder 1/13/2006

		// Indeces
		m_sOutputMaxIndex = m_sOutputMinIndex = 0;

		// Initialize Bindings
		m_pIUnkInput		= NULL;
		m_pIUnkOutput		= NULL;
		m_pIUnkStateMachine = NULL;

	}

DECLARE_REGISTRY_RESOURCEID(IDR_HOMINGCONTROLLER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CHomingController)
	COM_INTERFACE_ENTRY(IHomingController)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()

// IHomingController
public:
	STDMETHOD(MoveRightArmUpperQuadrant)();
	STDMETHOD(MoveThroughDexterousWorkspace)();
	// Interface Method
	STDMETHOD(Initial)();
	STDMETHOD(ComputeHomingPressures)();

	// Interface Properties
	STDMETHOD(get_OutputMax)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_OutputMax)(/*[in]*/ double newVal);
	STDMETHOD(get_OutputMin)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_OutputMin)(/*[in]*/ double newVal);
	STDMETHOD(get_OutputMaxIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_OutputMaxIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_OutputMinIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_OutputMinIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_HomingSteps)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_HomingSteps)(/*[in]*/ float newVal);
	STDMETHOD(get_LeftArm)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_LeftArm)(/*[in]*/ short newVal);

	// Variables
	ULONG	m_CurrentStep;
	ULONG	m_BaseStep;
	int		m_delta_pressure;						// Used in ::MoveThroughDexterousWorkspace()
	int		m_stage;								// same
	int		m_counter;
	int		y_axis_counter;							

	long	m_NumAxes;
	float	m_dHomingSteps;

	short	m_LeftArm;
	short	m_sOutputMaxIndex;						// Indeces for arrays
	short	m_sOutputMinIndex;

	double	m_pOutputMax[NUM_AXES];
	double	m_pOutputMin[NUM_AXES];

	// IMA Component Bindings
	IComponent *m_pIUnkInput;						// Vector signal inputs and outputs
	IComponent *m_pIUnkOutput;
	IComponent *m_pIUnkStateMachine;				// StateMachine Connection
private:
	// Internal constuctor/destructor
	STDMETHOD(OnConstruct)(void);
	STDMETHOD(OnDestruct)(void);

	// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT pData);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component
};

#endif //__HOMINGCONTROLLER_H_
