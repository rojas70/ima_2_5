/********************* NOTE: THIS VERSION OF THE PROGRAM APPLIES ONLY TO AQUATEEN AND HP3JC *******************************/
/********************* THERE IS A LOCAL AND MODIFIED VERSION OF THE CONTROL BASIS FOR ISAC & OCTAVIA **********************/
/********************* THAT VERSION IS LOCATED IN THE C:\IMA2\COMPONENTS FOLDER OF OCTAVIA ********************************/
/********************* MATLAB IKs ORIGINATED THAT DIFFERENCE. THEY CAN BE MADE THE SAME AND USE ONLY ONE VERSOIN **********/
/********************* OCTAVIA DOES NOT HAVE LATEST VERSION OF MATLAB... RUNS W2K *****************************************/
// ControlBasis.h : Declaration of the CControlBasis

#ifndef __CONTROLBASIS_H_
#define __CONTROLBASIS_H_

#include "resource.h"       						// main symbols
#include "math.h"
#include <cmath>
#include "O:\Base Classes\ComponentImpl.h"			// Component Lib file
#include "O:\Components\msvbvm60.tlh"				// property bag dll
#include "O:\Include\IMA2_BasicComponentsLib.h"		// Vector Signal
#include "O:\Include\Motoman\IMA2_MotomanLib.h"		// For motoman
#include "O:\Include\IMA2_MatlabStateMachineLib.h"	// For StateMachine

#include "engine.h"									// Necessary to run matlab funcitons (used in the computation of inverse kinematics)

// Project Definitions
const double PI = 4.0*atan(1.0);

#define NUM_AXES			6
#define NUMBER_OF_CYCLES	1

// Robots
#define ISAC_ROBOT			0
#define HP3JC_ROBOT			1

// Dominant and Subordinate Controllers
#define DOMINANT						 0			// Flag to be used to know if controller is dominant.
#define SUBORDINATE						 1			// Flag to be used to know if controller is subordinate.

#define DOMINANT_POSITION_CONTROLLER	10			// Declares that this controller is the dominant one in this program.
#define SUBORDINATE_POSITION_CONTROLLER	11			// Declares that this controllers is the subordinate one in this program.

#define	DOMINANT_FORCE_CONTROLLER		20			// We can only have upto 2 controllers.
#define	SUBORDINATE_FORCE_CONTROLLER	21			// There will always be one dominant, and there may be a subordinate one as well.

#define DOMINANT_MOMENT_CONTROLLER		30
#define SUBORDINATE_MOMENT_CONTROLLER	31

#define DOMINANT_IKIN_CONTROLLER		40			// Added Sept 2008 to generate a more stable controller than jacobian position control.
#define SUBORDINATE_IKIN_CONTROLLER		41

#define DOMINANT_CARTESIAN_CONTROLLER	 50			// Added Jan 2009 to generate a more stable controller than jacobian position control.
#define SUBORDINATE_CARTESIAN_CONTROLLER 51 
		

#define NOT_ACTIVE						99

// Function return values
#define SUCCESS							 0
#define FAILURE							-1

// Tool number and name definitions
#define EMPTY		0							// No tool is used
#define BARRET		1							// Barrett Hand is defined as tool number 0 in the NX100
#define ASSEMBLY	2							// Assembly tool is used = barret + truss

// Force Controller Reference Values for approach
#define Des_Fx_Approach  20		// 40		(40,2) leads to a faster insertion.
#define Des_Fy_Approach   0.0	//			(20,1) leads to a slower insertion.
#define Des_Fz_Approach	  1		// 2		Other values are possible. Got to test empirically.

#define Des_Fx_Insert  20		// 40		These worked well with the moment + force controller
#define Des_Fy_Insert   0.0		
#define Des_Fz_Insert   1		// 2	
/////////////////////////////////////////////////////////////////////////////
// CControlBasis
class ATL_NO_VTABLE CControlBasis : 
	public CComObjectRootEx<CComSingleThreadModel>,		
	public CComCoClass<CControlBasis, &CLSID_ControlBasis>,
	public IDispatchImpl<IControlBasis, &IID_IControlBasis, &LIBID_IMA2_CONTROLBASISLIBLib>,
	public CComponentImpl 
{
public:
	CControlBasis()
	{
		int i,j;

		// Alpha: Low-pass frequency filter gain
		alpha					= 0.85;

		// Flags
		m_iRetVal				= 0;								// Return Value variable
		m_bHomePositionFlag		= true;							// Home angles flag
		m_bWrite2File			= false;						// Write to files flag
		m_sMatEngine			= 0;							// Matlab engine flag
		bCartesianFlag			= 0;							// Cartesian flag used in GetDominantVectorData() or GetSubordinateVectorData()

		// Error message
		m_bstrError = SysAllocString(L"Review variables on the interface to ensure your program is set properly");

		// Robot selection
		m_bstrWhatRobot = SysAllocString(L"HP3JC");				// Set HP3JC as the default location
		m_sWhatRobot	= HP3JC_ROBOT;							// Used pre-header definition.

		// Controllers
		m_sNumControllers		= 1;							// Set the default to 1. 
		m_sWhichIsDomController = DOMINANT_POSITION_CONTROLLER;	// Set's the position controller as the dominant controller;
		m_sWhichIsSubController	= NOT_ACTIVE;					// Says that there is no active subordiante controller

		// Gains
		// The values of these gains will change depending on the robot selected in: put_WhatRobot();
		m_dPositionGain[0] = 0.0000425;		m_dIKinGain[0] = 0.1;	m_dForceGain[0] = 0.001; 		m_dMomentGain[0] = 0; 			m_dCartesianGain[0] = 1;
		m_dPositionGain[1] = 0.0002;		m_dIKinGain[1] = 0.1;	m_dForceGain[1] = 0.002;		m_dMomentGain[1] = 0; 			m_dCartesianGain[0] = 1;
		m_dPositionGain[2] = 0.0002;		m_dIKinGain[2] = 0.1;	m_dForceGain[2] = 0.002;		m_dMomentGain[2] = 0; 			m_dCartesianGain[0] = 1;
		m_dPositionGain[3] = 0.00056;		m_dIKinGain[3] = 0.1;	m_dForceGain[3] = 0;			m_dMomentGain[3] =   0.200; 	m_dCartesianGain[0] = 1;
		m_dPositionGain[4] = 0.00056;		m_dIKinGain[4] = 0.1;	m_dForceGain[4] = 0;			m_dMomentGain[4] =   0.200; 	m_dCartesianGain[0] = 1;
		m_dPositionGain[5] = 0.00056;		m_dIKinGain[5] = 0.1;	m_dForceGain[5] = 0;			m_dMomentGain[5] =   0.200; 	m_dCartesianGain[0] = 1;

		// Controller Vectors
		for(i = 0; i<NUM_AXES; i++)
		{
			// Dominant Controllers
			m_dDomCont_DesInput[i] = m_dDomCont_ActualInput[i] = m_dDomCont_Error[i] = m_dDomCont_Output[i] = m_dPreviousControllerOutput[i] = m_dAveragedOutput[i] = 0.0;

			// Subordinate Controllers
			m_dSubCont_DesInput[i] = m_dSubCont_ActualInput[i] = m_dSubCont_Error[i] = m_dSubCont_Output[i] = 0.0;

			// Other Matrices
			m_dNullSpaceProjectionOutput[i] = 0.0;
			m_dCompositeControllerOutput[i] = 0.0;
			m_dDesired_Joint_Angles[i]		= 0.0;

			// Cartesian matrices
			d_AverageOutputCart[i]			= 0.0;
			d_PreviousCartOutput[i]			= 0.0;
			m_dDesiredXYZRPY[i]				= 0.0;
			m_dActualCartesian[i]			= 0.0;
			m_dFTReferenceValue[i]			= 0.0;
		}

		// Reference Value Index
		m_sFTReferenceValueIndex = 0;

		// Null Space Projected Vector
		for(i=0;i<NUM_AXES;i++)
		{
			for(j=0;j<NUM_AXES;j++)	
			{
				// Initialize the identity matrix, with a diagonal of 1's
				if(i==j)
					eye[i][j] = 1.0;
				else
					eye[i][j] = 0.0;
			
				// Zero the null_space projection matrix
				m_dNullSpaceProjectionMatrix[i][j] = 0.0;
			}
		}

		// Indeces

		// Gains
		m_sPositionGainIndex		= 0;
		m_sForceGainIndex			= 0;
		m_sMomentGainIndex			= 0;
		m_sIKinGainIndex			= 0;

		// Dominant Controllers
		m_sDomCont_DesInputIndex = m_sDomCont_ActualInputIndex = m_sDomCont_OutputIndex = 0;

		// Subordinate Controllers
		m_sSubCont_DesInputIndex = m_sSubCont_ActualInputIndex = m_sSubCont_OutputIndex = 0;

		// Jacobian
		// Angles
		for (i = 0; i<NUM_AXES; i++)
			Angle[i] = 0.0;

		// File
		stream = NULL;

		// Timing Variables
		ticksPerSecond.QuadPart	= 0;
		start_ticks.QuadPart	= 0;
		end_ticks.QuadPart		= 0;
		sample_time				= 0.0;

		// CumulativeError
		CumulativeError = 0;


		// Matlab Variables
		m_MatXYZRPY			= NULL;
		m_MatJointAngles	= NULL;

		// Tool types
		m_MatToolType		= NULL;
		m_dToolType			= new double;
		*m_dToolType		= BARRET;
	}

	~CControlBasis()
	{
		SysFreeString(m_bstrError);
		SysFreeString(m_bstrWhatRobot);

		delete m_dToolType;

		// Close Matlab engine and clear memory
		if(m_sMatEngine == 1)
		{
			engEvalString(ep, "close;");			// Close engine
			mxDestroyArray(m_MatXYZRPY);			// Clear memory of matlab variables
			mxDestroyArray(m_MatJointAngles);	
			mxDestroyArray(m_MatToolType);	
		}
	}


DECLARE_REGISTRY_RESOURCEID(IDR_CONTROLBASIS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CControlBasis)
	COM_INTERFACE_ENTRY(IControlBasis)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()

// IControlBasis
// This is where all your interface methods will appear and be displayed on DAD
public:
	void Reset();
	// Interface method
	STDMETHOD(Initialize)();
	STDMETHOD(ComputeControlBasis)();
	STDMETHOD(Close)();

	// Interface properties
	STDMETHOD(get_ref_DesFT_ReferenceValueIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_ref_DesFT_ReferenceValueIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_ref_DesFT_ReferenceValue)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_ref_DesFT_ReferenceValue)(/*[in]*/ double newVal);

	STDMETHOD(get_ToolType)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ToolType)(/*[in]*/ BSTR newVal);

	STDMETHOD(get_AveragingWeight_JointAngles)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_AveragingWeight_JointAngles)(/*[in]*/ double newVal);

	STDMETHOD(get_gain_MomentGainIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_gain_MomentGainIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_gain_ForceGainIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_gain_ForceGainIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_gain_PositionGainIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_gain_PositionGainIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_gain_IKinGainIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_gain_IKinGainIndex)(/*[in]*/ short newVal);

	STDMETHOD(get_cont_NumControllers)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_cont_NumControllers)(/*[in]*/ short newVal);

	STDMETHOD(get_cont_SubContType)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_cont_SubContType)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_cont_DomContType)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_cont_DomContType)(/*[in]*/ BSTR newVal);

	STDMETHOD(get_sub_OutputVectorIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_sub_OutputVectorIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_sub_DesiredVectorIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_sub_DesiredVectorIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_sub_ActualVectorIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_sub_ActualVectorIndex)(/*[in]*/ short newVal);

	STDMETHOD(get_sub_OutputVector)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_sub_OutputVector)(/*[in]*/ double newVal);
	STDMETHOD(get_sub_ActualVector)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_sub_ActualVector)(/*[in]*/ double newVal);
	STDMETHOD(get_sub_DesiredVector)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_sub_DesiredVector)(/*[in]*/ double newVal);

	STDMETHOD(get_dom_OutputVectorIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_dom_OutputVectorIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_dom_ActualVectorIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_dom_ActualVectorIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_dom_DesiredVectorIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_dom_DesiredVectorIndex)(/*[in]*/ short newVal);

	STDMETHOD(get_dom_OutputVector)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_dom_OutputVector)(/*[in]*/ double newVal);
	STDMETHOD(get_dom_ActualVector)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_dom_ActualVector)(/*[in]*/ double newVal);
	STDMETHOD(get_dom_DesiredVector)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_dom_DesiredVector)(/*[in]*/ double newVal);

	STDMETHOD(get_gain_IKinGain)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_gain_IKinGain)(/*[in]*/ double newVal);
	STDMETHOD(get_gain_MomentGain)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_gain_MomentGain)(/*[in]*/ double newVal);
	STDMETHOD(get_gain_ForceGain)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_gain_ForceGain)(/*[in]*/ double newVal);
	STDMETHOD(get_gain_PositionGain)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_gain_PositionGain)(/*[in]*/ double newVal);

	STDMETHOD(get_WhatRobot)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_WhatRobot)(/*[in]*/ BSTR newVal);

	STDMETHOD(get_ErrorMessage)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ErrorMessage)(/*[in]*/ BSTR newVal);

	// Local functions
	int  ComputeControllerOutput(bool);
	void JacobianProduct(short TypeOfController, double * TempBuffer);
	void SetGains();
	void ProjectToNullSpace();
	void Write2File(char * title, double time, double * data , char * textfile); // Writes vector and time data to file
	void WriteJointAngleHomePosition();																			// Write joint angle home positions.
	int  ComputeInverseKinematics(double XYZRPY[6]);															// Computes inverse kinematics.
	void RPY_2_R06(double[6], double[16]);																		// Computes the 3x3 rotation matrix of the homogeneous transformation. Necessary to derive the inverse kinematics.
	void ComputePPos(double[16]);																				// Extracts/computes the position of the wrist given end-effector coordinates. Necessary to derive the inverse kinematics.
	void CheckError();																							// Checks error to see if it is proper to transition from first controller to second controller

	HRESULT ComputeJacobian(short TypeOfController);
	HRESULT GetSubordinateVectorData();
	HRESULT GetDominantVectorData();

private:
	// GUI Message 
	BSTR	m_bstrError;				// Is used to hold string data that is published on the interface to tell user on the latest status of program.

	// Robots
	BSTR	m_bstrWhatRobot;			// Holds selection of robot type: ISAC or HP3JC. Affects Jacobian values.
	short	m_sWhatRobot;				// Flag to indicate which robot is selected.

	// Controllers
	short	m_sNumControllers;			// Holds numbers of controllers running in object. Could have 1 or 2 (dominant and subordinate).
	short	m_sWhichIsDomController;	// Holds flag to indicate which controller is dominant (see the #defines).
	short	m_sWhichIsSubController;	// Holds flag to indicate which controller is subordinate (see the #defines).

	// Gains									// There will be different values for ISAC or HP3JC.
	double	alpha;								// Averaging filter parameter
	double	m_dPositionGain[NUM_AXES];			// Holds position-gain value.
	double	m_dIKinGain[NUM_AXES];				// Holds gains for inverse kinematic gain variable.
	double	m_dForceGain[NUM_AXES];				// Holds only force (not moment) gain value
	double	m_dMomentGain[NUM_AXES];			// Holds moment gain value.
	double	m_dInverseTorqueGain[NUM_AXES];		// Holds inverse torque gain value (used in force controller). For more see Platt's dissertation.
	double	m_dCartesianGain[NUM_AXES];			// Holds gains for cartesian controller. Jan 09.

	/********** Controller Vectors **********/
	// Dominant Controller
	double	m_dDomCont_DesInput[NUM_AXES];		// Holds 'Dominant's controller' desired input (could be position/force/moment).
	double	m_dDomCont_ActualInput[NUM_AXES];	// Holds 'Dominant's controller' actual input.
	double	m_dDomCont_Error[NUM_AXES];			// Holds the error (the difference between the desired and the actual input). This vector does not show on DADs interface.
	double	m_dDomCont_Output[NUM_AXES];		// Holds the output of the controller (this is the updated desired position of the joints).
	double	m_dPreviousControllerOutput[NUM_AXES];// Holds a history (previous reading) of the output of the controller
	double	m_dAveragedOutput[NUM_AXES];// Holds the averaged output that is finally passed to the Vector Signal.
	
	// Subordinate Controller
	double	m_dSubCont_DesInput[NUM_AXES];		// Holds 'Subordinate's controller' desired input (could be position/force/moment).
	double	m_dSubCont_ActualInput[NUM_AXES];	// Holds 'Subordinate's controller' actual input.
	double	m_dSubCont_Error[NUM_AXES];			// Holds the error (the difference between the desired and the actual input). This vector does not show on DADs interface.
	double	m_dSubCont_Output[NUM_AXES];		// Holds the output of the controller (this is the updated desired position of the joints).

	// Null space projection
	double eye[NUM_AXES][NUM_AXES];								// Identity matrix (6x6)
	double m_dNullSpaceProjectionOutput[NUM_AXES];				// Holds result where the subordinate controller output is projected to the null space of the dominant controller (6x1 matrix).
	double m_dNullSpaceProjectionMatrix[NUM_AXES][NUM_AXES];	// Holds the actual projection matrix (6x6)
	double m_dCompositeControllerOutput[NUM_AXES];				// Holds the combined output of the subordinate and dominant controller.

	// Cartesian Controller Buffers
	double d_AverageOutputCart[NUM_AXES];						// Holds average values for the cartesian output
	double d_PreviousCartOutput[NUM_AXES];						// Holds history values for the cartesian output
	double m_dDesiredXYZRPY[NUM_AXES];							// Used to save desired xyzrpy coordinate data for the cartesian controller
	double m_dActualCartesian[NUM_AXES];
	bool   bCartesianFlag;										// Flag used in the conversion of desired incremental data to desired XYZ data

	// Inverse Kinematics Matrix
	double	m_dDesired_Joint_Angles[NUM_AXES];					// Holds the computed desired joint angles

	/********** Indeces	**********/								// Used in DAD's Interface

	// Gains
	short	m_sPositionGainIndex;				// Holds index for position gain.
	short	m_sForceGainIndex;					// Holds index for force gain.
	short	m_sMomentGainIndex;					// Holds index for moment gain.
	short	m_sIKinGainIndex;					// Holds index for inverse kinematic position gain.

	// Dominant Controller
	short	m_sDomCont_DesInputIndex;			// Is the index for the dominant's controller desired input vector.
	short	m_sDomCont_ActualInputIndex;		// Is the index for the dominant's controller desired input vector.
	short	m_sDomCont_OutputIndex;				// Is the index for the dominant's controller desired input vector.

	// Subordinate Controller
	short	m_sSubCont_DesInputIndex;			// Is the index for the subordinate's controller desired input vector.
	short	m_sSubCont_ActualInputIndex;		// Is the index for the subordinate's controller desired input vector.
	short	m_sSubCont_OutputIndex;				// Is the index for the subordinate's controller desired input vector.

	/********** Matlab Engine **********/		// Used to compute the inverse kinematics of the HP3JC
	Engine   *ep;								// Matlab Engine Variable		
	mxArray  *m_MatXYZRPY;						// Matlab type variables. They are arrays. Needed to pass variables in and out of engine. 
	mxArray	 *m_MatJointAngles;

	// Tool type
	mxArray *m_MatToolType;						// Will store the typo of tool type used. This changes the value of d6 in the DH Parameters and Inv Kins'.
	double	*m_dToolType;						// Flag to determine what tool type we have: EMPTY, BARRET, ASSEMBLY

	/********** Bindings **********/
	// Dominant Controller
	IComponent*	m_pIUnkDomCont_DesInput;		// Holds pointer to object for the dominant's controller desired input.
	IComponent*	m_pIUnkDomCont_ActualInput;		// Holds pointer to object for the dominant's controller actual input.
	IComponent*	m_pIUnkDomCont_Output;			// Holds pointer to object for the dominant's controller output.

	// Subordinate Controller
	IComponent*	m_pIUnkSubCont_DesInput;		// Holds pointer to object for the subordinate's controller desired input.
	IComponent*	m_pIUnkSubCont_ActualInput;		// Holds pointer to object for the subordinate's controller actual input.
	IComponent*	m_pIUnkSubCont_Output;			// Holds pointer to object for the subordinate's controller output.

	// Positions: Angles and Cartesian
	IComponent* m_pIUnkAngle;					// Holds pointer to object for the current Joint Angles.
	IComponent* m_pIUnkCartesian;

	// State Machine
	IComponent* m_pIUnkStateMachine;

	// HP3JC
	IComponent* m_pIUnkHP3JC;

	// Cumulative Error
	IComponent* m_pIUnkCumError;

	/********** Timing Variables **********/	// Timing variables. Need <windows.h>
	LARGE_INTEGER ticksPerSecond;				// CPU frequency, counts per second. In essence number of ticks per second. Method: QueryPerformanceFrequency(&ticksPerSecond) must be called to get value.
	LARGE_INTEGER start_ticks;					// Retrives starting value of counter
	LARGE_INTEGER end_ticks;					// Retrives ending value of counter
	double		  sample_time;					// Variable to compute cpu time

	/********** Cumulative Error **********/
	double CumulativeError;						// Error used to estimated time for transition between controller

	/********** FT Reference values **********/
	double m_dFTReferenceValue[NUM_AXES];		// Holds values for force and moment reference values
	short  m_sFTReferenceValueIndex;			// Index for this array


	// Jacobian.								// NOTE: The values that will go inside represent the TRANSFORM!!!!!!!!
	double Angle[NUM_AXES];						// Holds Angles used in Jacobian.
	double J11,J12,J13,J14,J15,J16;
	double J21,J22,J23,J24,J25,J26;
	double J31,J32,J33,J34,J35,J36;
	double J41,J42,J43,J44,J45,J46;
	double J51,J52,J53,J54,J55,J56;
	double J61,J62,J63,J64,J65,J66;

	// Writing to files
	FILE *stream;							// Stream to write to files.

	// Flag
	bool	m_bHomePositionFlag;			// Flag used to load home positions on first call.
	bool	m_bWrite2File;					// Flag to indicate whether or not to write to file.
	int		m_iRetVal;						// Variable to hold functions return values.
	short	m_sMatEngine;					// Flag used to determine if we connected to matlab engine

	// Binding methods
	STDMETHOD(OnConstruct)(void);	// Set bindings
	STDMETHOD(OnDestruct)(void);	// Delete them

	// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT pData);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component

};

#endif //__CONTROLBASIS_H_
