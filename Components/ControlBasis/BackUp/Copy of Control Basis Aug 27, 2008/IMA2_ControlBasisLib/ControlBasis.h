// ControlBasis.h : Declaration of the CControlBasis

#ifndef __CONTROLBASIS_H_
#define __CONTROLBASIS_H_

#include "resource.h"       					// main symbols
#include "math.h"
#include "O:\Base Classes\ComponentImpl.h"		// Component Lib file
#include "O:\Components\msvbvm60.tlh"			// property bag dll
#include "O:\Include\IMA2_BasicComponentsLib.h"		// Vector Signal


// Project Definitions
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

#define NOT_ACTIVE						99
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
		alpha					= 0.5;

		// Home Angles flag 
		m_bHomePositionFlag		= true;

		// Error message
		m_bstrError = SysAllocString(L"Review variables on the interface to ensure your program is set properly");

		// Robot selection
		m_bstrWhatRobot = SysAllocString(L"HP3JC");				// Set HP3JC as the default location
		m_sWhatRobot	= HP3JC_ROBOT;							// Used pre-header definition.

		// Controllers
		m_sNumControllers		= 1;							// Set the default to 1. 
		m_sWhichIsDomController = DOMINANT_POSITION_CONTROLLER;	// Set's the position controller as the dominant controller;
		m_sWhichIsSubController	= NOT_ACTIVE;					// Says that there is no active subordiante controller
//		m_bPositionController	= 1;							// Set the default to Position controller as active.
//		m_bForceController		= 0;
//		m_bMomentController		= 0;

		// Gains
		// The values of these gains will change depending on the robot selected in: put_WhatRobot();
		m_dPositionGain[0] = 0.2;		m_dForceGain[0] = 0.05; m_dMomentGain[0] = 0.05; 	
		m_dPositionGain[1] = 0.2;		m_dForceGain[1] = 0.05; m_dMomentGain[1] = 0.05; 
		m_dPositionGain[2] = 0.2;		m_dForceGain[2] = 0.05; m_dMomentGain[2] = 0.05; 
		m_dPositionGain[3] = 0.2;		m_dForceGain[3] = 0.05; m_dMomentGain[3] = 2.00; 
		m_dPositionGain[4] = 0.2;		m_dForceGain[4] = 0.05; m_dMomentGain[4] = 2.00; 
		m_dPositionGain[5] = 0.2;		m_dForceGain[5] = 0.05; m_dMomentGain[5] =-2.00; // There seems to be a sign-error between force/moment controller.

		// Controller Vectors
		for(i = 0; i<NUM_AXES; i++)
		{
			// Dominant Controllers
			m_dDomCont_DesInput[i] = m_dDomCont_ActualInput[i] = m_dDomCont_Error[i] = m_dDomCont_Output[i] = m_dPreviousControllerOutput[i] = m_dAveragedOutput[i] = 0.0;

			// Subordinate Controllers
			m_dSubCont_DesInput[i] = m_dSubCont_ActualInput[i] = m_dSubCont_Error[i] = m_dSubCont_Output[i] = 0.0;

			m_dNullSpaceProjectionOutput[i] = 0.0;
			m_dCompositeControllerOutput[i] = 0.0;
		}

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
	}

	~CControlBasis()
	{
		SysFreeString(m_bstrError);
		SysFreeString(m_bstrWhatRobot);
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
	// Interface method
	STDMETHOD(Initialize)();
	STDMETHOD(ComputeControlBasis)();

	// Interface properties
	STDMETHOD(get_AveragingWeight_JointAngles)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_AveragingWeight_JointAngles)(/*[in]*/ double newVal);
	STDMETHOD(get_gain_MomentGainIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_gain_MomentGainIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_gain_ForceGainIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_gain_ForceGainIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_gain_PositionGainIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_gain_PositionGainIndex)(/*[in]*/ short newVal);

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
	void ComputeControllerOutput(bool);
	void JacobianProduct(short TypeOfController, double * TempBuffer);
	void SetGains();
	void ProjectToNullSpace();
	void Write2File(char *, double *, char *);
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
//	bool	m_bPositionController;		// Flag to indicate that position controller is in use (useful when determining dominant and subordinate controllers and jacobian).
//	bool	m_bForceController;			// Flag to indicate that force controller is in use.
//	bool	m_bMomentController;		// Flag to indicate that moment controller is in use.

	// Gains									// There will be different values for ISAC or HP3JC.
	double	alpha;								// Averaging filter parameter
	double	m_dPositionGain[NUM_AXES];			// Holds position-gain value.
	double	m_dForceGain[NUM_AXES];				// Holds only force (not moment) gain value
	double	m_dMomentGain[NUM_AXES];			// Holds moment gain value.
	double	m_dInverseTorqueGain[NUM_AXES];		// Holds inverse torque gain value (used in force controller). For more see Platt's dissertation.

	// Controller Vectors
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

	// Indeces									// Used in DAD's Interface

	// Gains
	short	m_sPositionGainIndex;				// Holds index for position gain.
	short	m_sForceGainIndex;					// Holds index for force gain.
	short	m_sMomentGainIndex;					// Holds index for moment gain.

	// Dominant Controller
	short	m_sDomCont_DesInputIndex;			// Is the index for the dominant's controller desired input vector.
	short	m_sDomCont_ActualInputIndex;		// Is the index for the dominant's controller desired input vector.
	short	m_sDomCont_OutputIndex;				// Is the index for the dominant's controller desired input vector.

	// Subordinate Controller
	short	m_sSubCont_DesInputIndex;			// Is the index for the subordinate's controller desired input vector.
	short	m_sSubCont_ActualInputIndex;		// Is the index for the subordinate's controller desired input vector.
	short	m_sSubCont_OutputIndex;				// Is the index for the subordinate's controller desired input vector.

	// Bindings
	// Dominant Controller
	IComponent*	m_pIUnkDomCont_DesInput;		// Holds pointer to object for the dominant's controller desired input.
	IComponent*	m_pIUnkDomCont_ActualInput;		// Holds pointer to object for the dominant's controller actual input.
	IComponent*	m_pIUnkDomCont_Output;			// Holds pointer to object for the dominant's controller output.

	// Subordinate Controller
	IComponent*	m_pIUnkSubCont_DesInput;		// Holds pointer to object for the subordinate's controller desired input.
	IComponent*	m_pIUnkSubCont_ActualInput;		// Holds pointer to object for the subordinate's controller actual input.
	IComponent*	m_pIUnkSubCont_Output;			// Holds pointer to object for the subordinate's controller output.

	// Angles
	IComponent* m_pIUnkAngle;					// Holds pointer to object for the current Joint Angles.

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

	bool	m_bHomePositionFlag;			// Flag used to load home positions on first call.
	void	WriteJointAngleHomePosition();	// Write joint angle home positions.

	// Binding methods
	STDMETHOD(OnConstruct)(void);	// Set bindings
	STDMETHOD(OnDestruct)(void);	// Delete them

	// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT pData);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component

};

#endif //__CONTROLBASIS_H_
