	// NewValveController.h : Declaration of the CNewValveController

#ifndef __NEWVALVECONTROLLER_H_
#define __NEWVALVECONTROLLER_H_

#include "resource.h"       						// main symbols
#include "math.h"
#include "O:\Base Classes\ComponentImpl.h"			// Component Lib file
#include "O:\Components\msvbvm60.tlh"				// property bag dll
#include "O:\Include\IMA2_BasicComponentsLib.h"		// Vector Signal 
#include "O:\Include\IMA2_MatlabStateMachineLib.h"		// Vector Signal 
#include "O:\Include\Winmotenc\winmotenc.h"

// Included Header Files
#include "Headers\commport.h"
#include "Headers\winmotenc.h"

// Definitions
#define NUM_AXES		6							

// What arm are we using
#define RIGHT_ARM		0
#define LEFT_ARM		1	

// MATH
#define PI			4*atan(1.0)
#define RADS2DEGREE	360/(2*PI)

// Voltage/Pressure relationship
#define OUTPUTVOLTAGE_2_INPUTVOLTAGE 2.5/1000	// Conversion ratio from output voltage to input voltage.
/////////////////////////////////////////////////////////////////////////////
// CNewValveController
class ATL_NO_VTABLE CNewValveController : 
	public CComObjectRootEx<CComSingleThreadModel>,	
	public CComCoClass<CNewValveController, &CLSID_NewValveController>,
	public IDispatchImpl<INewValveController, &IID_INewValveController, &LIBID_IMA2_NNET_N_PCONTROLLERLib>,
	public CComponentImpl 
{
public:
	CNewValveController()
	{
		// Flag to indicate if we have connected with the cards
		m_bConnected				= FALSE;

		// What arm variable
		m_bWhatArm					=	RIGHT_ARM;		// This is the default and can be changed in the DAD interface.

		m_bstrError = SysAllocString(L"This component moves the arm to the desired angles in degrees.");

		for (int i=0; i<NUM_AXES; i++)
		{
			// Arrays
			m_dAngles[i]					=   0;				// Joint Angle values
			m_dErrorOutput[i]				=   1;				// Value 0 is used as a condition to stop loop
			m_dEncoders[i]					=   0;				// Encoder values
			m_dDesiredAngles[i]				= 0.0;
			m_dPhysicalAngle[i]				= 0.0;
		}

		for (int j=0; j<NUM_AXES*2; j++)
		{
			// Voltage arrays
			m_dInitialValveOutputs[j]		= 0.0;
			m_dValveOutputs[j]				=   0;				// in voltage
		}
		// Angles
		m_dPGain[0]	= 0.0009;
		m_dPGain[1] = 0.0013;
		m_dPGain[2] = 0.0015;		
		m_dPGain[3] = 0.0003;
		m_dPGain[4] = 0.0015;
		m_dPGain[5] = 0.0003;
	
		// Encoder
		m_dEncoderGain[0]			= -5092.0;
		m_dEncoderGain[1]			=  5092.0;
		m_dEncoderGain[2]			=  4244.0;
		m_dEncoderGain[3]			= -4244.0;
		m_dEncoderGain[4]			=   636.6;
		m_dEncoderGain[5]			=  -636.6;

		// Indeces
		m_sValveOutputsIndex		= 0;
		m_sEncodersIndex			= 0;
		m_sAnglesIndex				= 0;
		m_sPGainIndex				= 0;
		m_sChannel					= 0;

		// Step variables 
		m_sNumOfSteps				= 50;		// iterations

		// Infalation/deflation rates
		m_sInflationRate				= 35;
		m_sDeflationRate				= 500;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_NEWVALVECONTROLLER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CNewValveController)
	COM_INTERFACE_ENTRY(INewValveController)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()
// INewValveController
public:
	STDMETHOD(gripper_CloseGripper)();
	STDMETHOD(gripper_OpenGripper)();
	STDMETHOD(get_rate_DeflationRate)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_rate_DeflationRate)(/*[in]*/ short newVal);
	STDMETHOD(get_rate_InflationRate)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_rate_InflationRate)(/*[in]*/ short newVal);
	STDMETHOD(get_NumOfSteps)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_NumOfSteps)(/*[in]*/ short newVal);
	STDMETHOD(get_gain_PGainValueIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_gain_PGainValueIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_gain_PGainValue)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_gain_PGainValue)(/*[in]*/ double newVal);
	STDMETHOD(get_JointAnglesIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_JointAnglesIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_JointAngles)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_JointAngles)(/*[in]*/ double newVal);
	STDMETHOD(get_ValveOutputs)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_ValveOutputs)(/*[in]*/ double newVal);
	STDMETHOD(get_ValveOutputsIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_ValveOutputsIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_WhatArm)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_WhatArm)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_ErrorMessage)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ErrorMessage)(/*[in]*/ BSTR newVal);

	// Interface Mthods
	STDMETHOD(DoHomingRoutine)();		// Initialize arms and get them to the home position
	STDMETHOD(Move)();					// Call the P-controller to move to desired location	
	STDMETHOD(Close)();					// Releases pressure from muscles and closes cards

	// Private routines
	// Initialization
	void InitializeCards();	
	int  InitializeValves();
	
	// Gains
	void SetGains();

	// Encoder
	void ReadEncoders();
	void ResetEncoders();
	int DesiredHomeValues();
	int  ReadJointAngles();		// Reads angles for arms	
	
	// Voltages
	void ReadVoltages();
	void ResetVoltages();
	void SetHomePositionVoltages();
	int  SetArmVoltages(double bufferVoltages[]);
	int  GoToHomePosition();		// Can be called before closing to avoid any accidents

private:
	// Flags
	bool	m_bConnected;										// Useful so that if we want to disconnect we make sure we are connected
	bool	m_bWhatArm;											// Tells what arm is being selected.
	
	// Error Message Display Variable
	BSTR	m_bstrError;										// Used to print error results to DAD interface to help user. 

	// Voltage Buffers
	double	m_dInitialValveOutputs[NUM_AXES*2];					// around the home position
	double	m_dValveOutputs[NUM_AXES*2];						// in voltage
	short	m_sValveOutputsIndex;								// Index is used in DAD interface
	short	m_sChannel;											// Stores what channel in Motenc Cards is being accessed

	// Encoders
	long	m_dEncoders[NUM_AXES];								// Encoder values
	short	m_sEncodersIndex;
	double	m_dEncoderGain[NUM_AXES];
	double	m_dPhysicalAngle[NUM_AXES];							// Not joint angles. Angles generated by the unique physical structure of ISAC. These values are then used to compute the Joint Angles.

	// Controller
	short	m_sAnglesIndex;										// For DAD interface
	double	m_dAngles[NUM_AXES];								// Joint Angle values
	double	m_dDesiredAngles[NUM_AXES];							// Desired Angles
	short	m_sNumOfSteps;										// Number of steps or iterations to run the P-controller

	double  m_dErrorOutput[NUM_AXES];							// Holds the angle error between desired angles and actual angles.

	double	m_dPGain[NUM_AXES];
	short	m_sPGainIndex;

	// Infaltion rates	
	short m_sInflationRate;									// Determines how fast to fill air pressure. The bigger the number the slower the process.
	short m_sDeflationRate;									// It's an inversely proportional relationship. 

	// For an ATL template, the pointer must be defined as part of the class
	// The constructor should have the pointer set to NULL
	// The CPP file is the one where 'new' is used to allocate sufficient memory for the class.
	// Otherwise the Class object will be out of scope.

	// Include IMA Component Bindings of type IComponent *
	IComponent *m_pIUnkDesiredAngles;
	IComponent *m_pIUnkCurrentAngles;
//	IComponent *m_pIUnkValveVoltages;

	// Binding methods
	STDMETHOD(OnConstruct)(void);	// Set bindings
	STDMETHOD(OnDestruct)(void);	// Delete them

	// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT pData);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component
};
#endif //__NNCONTROLLER_H_