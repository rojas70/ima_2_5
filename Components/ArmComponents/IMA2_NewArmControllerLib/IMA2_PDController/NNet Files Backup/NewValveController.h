	// NewValveController.h : Declaration of the CNewValveController

#ifndef __NEWVALVECONTROLLER_H_
#define __NEWVALVECONTROLLER_H_

#include "resource.h"       						// main symbols
#include "O:\Base Classes\ComponentImpl.h"			// Component Lib file
#include "O:\Components\msvbvm60.tlh"				// property bag dll
#include "O:\Include\IMA2_BasicComponentsLib.h"		// Vector Signal 
#include "O:\Include\IMA2_MatlabStateMachineLib.h"		// Vector Signal 
#include "O:\Include\Winmotenc\winmotenc.h"


// Included Header Files
#include "Headers\commport.h"
#include "Headers\winmotenc.h"

//#include "Headers\NNMuscleClass.h"

//Definitions
#define NUM_AXES		6							
#define NUMBER_OF_STEPS 50		// Number of steps to run the P-controller. Might not be needed, since we can call this ALWAYS in IMA.

// What arm are we using
#define RIGHT_ARM		0
#define LEFT_ARM		1	

// Neural Net Motion: Fwd / Bwd
#define FORWARD			1
#define BACKWARD	   -1

// MATH
#define PI			3.14159265
#define RADS2DEGREE	360/(2*PI)
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

		m_bstrError = SysAllocString(L"This component controlls valves and has PID or NN Controller");

		for (int i=0; i<NUM_AXES; i++)
		{
			// Voltage
			m_fIncrementalVoltage[i]		= 0.0;				// in voltage
			m_dAngles[i]					=   0;				// Joint Angle values
			m_dErrorOutput[i]				=   0;
			m_dEncoders[i]					=   0;				// Encoder values
			m_fDesiredAngles[i]				= 0.0;
			m_fDesiredTrajectory[i]			=   0;
			m_fpreviousAngles[i]			= 0.0;

		}

		for (int j=0; j<NUM_AXES*2; j++)
		{
			// Control Variables
			m_dInitialValveOutputs[j]		= 0.0;
			m_dValveOutputs[j]				=   0;				// in voltage
		}
		// Angles
		m_dLeftPValue[0]			= m_dRightPValue[0] = 0.0009;
		m_dLeftPValue[1]			= m_dRightPValue[1] = 0.0013;
		m_dLeftPValue[2]			= m_dRightPValue[2] = 0.0015;
		m_dLeftPValue[4]			= m_dRightPValue[4] = 0.0015;

		// For index 3, the values are opposite
		m_dLeftPValue [3]			=  0.003;
		m_dRightPValue[3]			= -0.003;

		m_dLeftPValue [5]			=  0.0030;
		m_dRightPValue[5]			=  0.0015;


		// Indeces
		m_sLeftPValueIndex			= 0;
		m_sRightPValueIndex			= 0;

		
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


		// Step variables (milliseconds)
		m_sSampleTime				= 60;

		// Set CNNMuscles Class pointer to NULL
		// Must do for both side arms.
		// Assigning Right NN Class pointers
/*		RightNNMusclesAngle0F = NULL;	RightNNMusclesAngle0B = NULL;
		RightNNMusclesAngle1F = NULL;	RightNNMusclesAngle1B = NULL;
		RightNNMusclesAngle2F = NULL;	RightNNMusclesAngle2B = NULL;
		RightNNMusclesAngle3F = NULL;	RightNNMusclesAngle3B = NULL;
		RightNNMusclesAngle4F = NULL;	RightNNMusclesAngle4B = NULL;
		RightNNMusclesAngle5F = NULL;	RightNNMusclesAngle5B = NULL;

		// Assigning Left NN Class Pointers
		LeftNNMusclesAngle0F = NULL;	LeftNNMusclesAngle0B = NULL;
		LeftNNMusclesAngle1F = NULL;	LeftNNMusclesAngle1B = NULL;
		LeftNNMusclesAngle2F = NULL;	LeftNNMusclesAngle2B = NULL;
		LeftNNMusclesAngle3F = NULL;	LeftNNMusclesAngle3B = NULL;
		LeftNNMusclesAngle4F = NULL;	LeftNNMusclesAngle4B = NULL;
		LeftNNMusclesAngle5F = NULL;	LeftNNMusclesAngle5B = NULL;
*/
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
	void ReadPressure();
	STDMETHOD(get_P_RightValueIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_P_RightValueIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_P_LeftValueIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_P_LeftValueIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_P_RightValue)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_P_RightValue)(/*[in]*/ double newVal);
	STDMETHOD(get_P_LeftValue)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_P_LeftValue)(/*[in]*/ double newVal);
	STDMETHOD(get_LogicalAnglesIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_LogicalAnglesIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_LogicalAngles)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_LogicalAngles)(/*[in]*/ double newVal);
	STDMETHOD(get_ValveOutputs)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_ValveOutputs)(/*[in]*/ double newVal);
	STDMETHOD(get_ValveOutputsIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_ValveOutputsIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_WhatArm)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(put_WhatArm)(/*[in]*/ BOOL newVal);
	STDMETHOD(get_ErrorMessage)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ErrorMessage)(/*[in]*/ BSTR newVal);

	STDMETHOD(DoHomingRoutine)();
	STDMETHOD(Close)();
	STDMETHOD(PIDController)();
//	STDMETHOD(NeuralNetController)();
	STDMETHOD(GoToHomePosition)();
	STDMETHOD(SetArmVoltages)();
	STDMETHOD(ReadLogicalAngles)();
	STDMETHOD(InitializeValves)();
//	STDMETHOD(AllocateNeuralNet)();

	void ReadEncoders();
	void PID();
	void ResetEncoders();
	void InitializeCards();


private:
	// Connected to the valves?
	bool	m_bConnected;										// Useful so that if we want to disconnect we make sure we are connected

	// Arm
	bool	m_bWhatArm;											// Tells what arm is being selected.
	
	// Error Message Display Variable
	BSTR	m_bstrError;										// Used to print error results to DAD interface to help user. 

	// Nerual Net Files
	float	m_fIncrementalVoltage[NUM_AXES];					// Used to store voltages in Neural Net. 

	// Control
	double	m_dInitialValveOutputs[NUM_AXES*2];					// around the home position
	double	m_dValveOutputs[NUM_AXES*2];						// in voltage
	short	m_sValveOutputsIndex;								// Index is used in DAD interface

	long	m_dEncoders[NUM_AXES];								// Encoder values
	short	m_sEncodersIndex;
	double	m_dEncoderGain[NUM_AXES];

	// PID
	double	m_dAngles[NUM_AXES];								// Joint Angle values
	short	m_sAnglesIndex;										// For DAD interface

	double  m_dErrorOutput[NUM_AXES];							// Holds the angle error between desired angles and actual angles.

	// PID
	double	m_dLeftPValue[NUM_AXES];
	short	m_sLeftPValueIndex;

	double	m_dRightPValue[NUM_AXES];
	short	m_sRightPValueIndex;

	float	m_fDesiredAngles[NUM_AXES];							// Desired Angles
	float	m_fDesiredTrajectory[NUM_AXES];						// Desired Trajectories
	float	m_fpreviousAngles[NUM_AXES];						// Previous Angle's

	short	m_sSampleTime;										// Step variables (milliseconds)

	// For an ATL template, the pointer must be defined as part of the class
	// The constructor should have the pointer set to NULL
	// The CPP file is the one where 'new' is used to allocate sufficient memory for the class.
	// Otherwise the Class object will be out of scope.

	// Assigning Right NN Class pointers
/*	CNNMuscles *RightNNMusclesAngle0F;	CNNMuscles *RightNNMusclesAngle0B;
	CNNMuscles *RightNNMusclesAngle1F;	CNNMuscles *RightNNMusclesAngle1B;
	CNNMuscles *RightNNMusclesAngle2F;	CNNMuscles *RightNNMusclesAngle2B;
	CNNMuscles *RightNNMusclesAngle3F;	CNNMuscles *RightNNMusclesAngle3B;
	CNNMuscles *RightNNMusclesAngle4F;	CNNMuscles *RightNNMusclesAngle4B;
	CNNMuscles *RightNNMusclesAngle5F;	CNNMuscles *RightNNMusclesAngle5B;

	// Assigning Left NN Class Pointers
	CNNMuscles *LeftNNMusclesAngle0F;	CNNMuscles *LeftNNMusclesAngle0B;
	CNNMuscles *LeftNNMusclesAngle1F;	CNNMuscles *LeftNNMusclesAngle1B;
	CNNMuscles *LeftNNMusclesAngle2F;	CNNMuscles *LeftNNMusclesAngle2B;
	CNNMuscles *LeftNNMusclesAngle3F;	CNNMuscles *LeftNNMusclesAngle3B;
	CNNMuscles *LeftNNMusclesAngle4F;	CNNMuscles *LeftNNMusclesAngle4B;
	CNNMuscles *LeftNNMusclesAngle5F;	CNNMuscles *LeftNNMusclesAngle5B;	
*/

	// Include IMA Component Bindings of type IComponent *
	IComponent *m_pIUnkDesiredAngles;
	IComponent *m_pIUnkCurrentAngles;
	IComponent *m_pIUnkValveVoltages;


	// Binding methods
	STDMETHOD(OnConstruct)(void);	// Set bindings
	STDMETHOD(OnDestruct)(void);	// Delete them

	// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT pData);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component

};

#endif //__NNCONTROLLER_H_
