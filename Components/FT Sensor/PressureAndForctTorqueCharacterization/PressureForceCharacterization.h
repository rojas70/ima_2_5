// PressureForceCharacterization.h : Declaration of the CPressureForceCharacterization

#ifndef __PRESSUREFORCECHARACTERIZATION_H_
#define __PRESSUREFORCECHARACTERIZATION_H_

#include "resource.h"								// main symbols
#include "O:\Components\msvbvm60.tlh"				// property bag dll
#include "O:\Base Classes\ComponentImpl.h"
#include "O:\Include\IMA2_BasicComponentsLib.h"		// Vector Signal 
#include "O:\Include\IMA2_MatlabStateMachineLib.h"	// Matlab State Machine
#include "O:\Include\IMA2_FTSensorLib.h"			// FTSensor
#include "O:\Include\IMA2_ArmTools.h"				// SampleIndPressure

#define NUM_AXES 6
#define NUM_OF_STEPS 100
/////////////////////////////////////////////////////////////////////////////
// CPressureForceCharacterization
class ATL_NO_VTABLE CPressureForceCharacterization : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPressureForceCharacterization, &CLSID_PressureForceCharacterization>,
	public IDispatchImpl<IPressureForceCharacterization, &IID_IPressureForceCharacterization, &LIBID_PRESSUREANDFORCTTORQUECHARACTERIZATIONLib>,
	public CComponentImpl 
{
public:
	CPressureForceCharacterization()
	{
		int index;

		// Left arm
		m_LeftArm				=    0;
			
		// Steps
		m_CurrentStep			=    0;
		m_BaseStep				=    0;

		// Pressure
		m_sWhatJointIsIt   		=    0;
		m_sNoOfSteps			=    0;
		m_dChangeinPressure		=  0.0;

		m_dHomingSteps			= 50.0;			
		m_NumAxes				= NUM_AXES;			

		m_bstrInputFile			= SysAllocString(L"");
		m_pdOriginalPressure	= NULL;
		m_fp					= NULL;	

		// Initialize Bindings
		m_pIUnkPressure			= NULL;
		m_pIUnkFTSensor			= NULL;
		m_pIUnkSampleIndPressure= NULL;

		m_pdOriginalPressure	= new double[NUM_AXES];	// A total of 6 pairs of rubertuators

		for (index=0; index<NUM_AXES; index++)
			m_pdOriginalPressure[index] = 2000.0;

		m_pdOriginalPressure[0] = 1000.0;				// First joint has a lower value

		for (index=0; index<NUM_AXES; index++)
		{
			m_pOutputMax[index] = 4000.0;				// Reasonable default range as set in AgentBuilder for RightArm Agent
			m_pOutputMin[index] =    0.0;
			m_pFTBuffer[index]  =    0.0;				// Force Torque buffer
		}

		m_pOutputMax[0]			= 1200.0;				// As set in agent builder 1/13/2006

		// Indeces
		m_sOutputMaxIndex = m_sOutputMinIndex = 0;

	}

DECLARE_REGISTRY_RESOURCEID(IDR_PRESSUREFORCECHARACTERIZATION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPressureForceCharacterization)
	COM_INTERFACE_ENTRY(IPressureForceCharacterization)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()

// IPressureForceCharacterization
public:
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
	STDMETHOD(get_FileName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_FileName)(/*[in]*/ BSTR newVal);


	STDMETHOD(get_PressureForRubbertuatorPair6)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_PressureForRubbertuatorPair6)(/*[in]*/ double newVal);
	STDMETHOD(get_PressureForRubbertuatorPair5)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_PressureForRubbertuatorPair5)(/*[in]*/ double newVal);
	STDMETHOD(get_PressureForRubbertuatorPair4)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_PressureForRubbertuatorPair4)(/*[in]*/ double newVal);
	STDMETHOD(get_PressureForRubbertuatorPair3)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_PressureForRubbertuatorPair3)(/*[in]*/ double newVal);
	STDMETHOD(get_PressureForRubbertuatorPair2)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_PressureForRubbertuatorPair2)(/*[in]*/ double newVal);
	STDMETHOD(get_PressureForRubbertuatorPair1)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_PressureForRubbertuatorPair1)(/*[in]*/ double newVal);

	// Interface Method
	STDMETHOD(Initialize)();
	STDMETHOD(VerticalPush1)();
	STDMETHOD(StartCharacerizationProcess)();
	STDMETHOD(ChangePressure)(short whatjoint, double basepressure, double pressurechange, short numberofsteps);
	STDMETHOD(WriteDataToFile)();
	STDMETHOD(GoToHomePosition)();

	// Internal Methods
	void(ChangePressureX)(short whatjoint, double basepressure, double pressurechange, short numberofsteps);
	void(WriteDataToFileX)();
	void OpenFile();
	void CloseFile();

	// Variables

	// For number of iterations to change pressure
	ULONG	m_CurrentStep;
	ULONG	m_BaseStep;
	float	m_dHomingSteps;

	// Paramters to determine the change in pressure
	short	m_sWhatJointIsIt;
	short	m_sNoOfSteps;
	double	m_dChangeinPressure;
	double *m_pdOriginalPressure;					// We will assume 6 pressures, each pair of values for each joint should be equal

	// General
	long	m_NumAxes;
	short	m_LeftArm;

	// Pressure Max and Min Values for each axis
	short	m_sOutputMaxIndex;			// Indeces for arrays
	short	m_sOutputMinIndex;
	double	m_pOutputMax[NUM_AXES];
	double	m_pOutputMin[NUM_AXES];

	// Force Torque data array
	double	m_pFTBuffer[NUM_AXES];			// Buffer to hold FT values Fx Fy Fz Tx Ty Tz


	// IMA Component Bindings
	IComponent *m_pIUnkPressure;			// pressure data
	IComponent *m_pIUnkFTSensor;			// FT data
	IComponent *m_pIUnkSampleIndPressure;	// SampleIndPressure

private:
	// Internal constuctor/destructor
	STDMETHOD(OnConstruct)(void);
	STDMETHOD(OnDestruct)(void);

	// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT pData);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component
													// This would be equivalent to returning a virtual HRESULT													// STDMETHOD returns a virtual HRESULT

	// File variables
	FILE *		m_fp;								// File handle
	BSTR		m_bstrInputFile;					// String container

};

#endif //__PRESSUREFORCECHARACTERIZATION_H_
