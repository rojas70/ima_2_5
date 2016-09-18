/////////////////////////////////////////////////////////////////////
// EyeMotionCenter.h : Declaration of the CEyeMotionCenter
// This program utilizes incoming vector data from VisualInputRep
// which contains the centroid of a segmented blob, to compute
// saccadic eye motions or smooth pursuits, or both. The latter
// is called by using CEyeMotionCenter::DoProportionalTracking()
// The Saccade class was inapropriately named. It should have been
// CPTSaccade. The PT represents ISACs current camera type: Pan-Tilt
/////////////////////////////////////////////////////////////////////

#ifndef __EYEMOTIONCENTER_H_
#define __EYEMOTIONCENTER_H_

#include "resource.h"       // main symbols
#include "stdio.h"
#include "math.h"

#include "O:\Base Classes\ComponentImpl.h"
#include "O:\Components\HeadComponents\IMA2_PTVisionLib\IMA2_PTVisionLib.h"

/*** for Neural network component ***/
#include "I:\Include\NeuralNetworkComponents.h"
/*** interface to VisualInputRepresentation ***/
#include "VisualInputRepresentation.h"
/*** interface to Saccade ****/
#include "Saccade.h"
/*** interface to SmoothPursuit ****/
#include "PTSmoothPursuit.h"
/*** interface to PTHeadControl ****/
#include "O:\Components\HeadComponents\IMA2_PTHeadLib\IMA2_PTHeadLib.h"

/////////////////////////////////////////////////////////////////////////////
// CEyeMotionCenter
class ATL_NO_VTABLE CEyeMotionCenter : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEyeMotionCenter, &CLSID_EyeMotionCenter>,
	public IDispatchImpl<IEyeMotionCenter, &IID_IEyeMotionCenter, &LIBID_IMA2_PTVISIONLIBLib>,
	public CComponentImpl
{
public:
	CEyeMotionCenter():
	
		// Set up macros. Value in parenthesis belongs to Upper Caps Term.
    	NUM_AXES(6),									// LPan, RPan, LTilt, RTilt, Avg Pan, Avg Tilt

		// DP Pan
  		MOTOR_RANGE_ANGLES_PAN		(318.0f),			// Pan-Angle range in degrees
		MOTOR_RANGE_PULSES_PAN_LEFT (6184.0),			// Pulses in left servo's range
		MOTOR_RANGE_PULSES_PAN_RIGHT(6178.0),			// Pulses in right servo's range
		PULSE_TO_ANG_PAN_LEFT		((double) (MOTOR_RANGE_ANGLES_PAN/MOTOR_RANGE_PULSES_PAN_LEFT)),
		PULSE_TO_ANG_PAN_RIGHT		((double) (MOTOR_RANGE_ANGLES_PAN/MOTOR_RANGE_PULSES_PAN_RIGHT)),

    	// DP Tilt
		MOTOR_RANGE_ANGLES_TILT		(106.0f),			// Tilt-Angle range	in degrees
		MOTOR_RANGE_PULSES_TILT		(2061.0f),			// Pulses in servo's range
		PULSE_TO_ANG_TILT((double) (MOTOR_RANGE_ANGLES_TILT/MOTOR_RANGE_PULSES_TILT))
	{
		// Variables and Flags
		i		= 0;
		
		alpha	= 0.5;									// Used to average current and previous motor angle positions		// 
		bLimitTilt							= FALSE;	// Flag to indicate whether to increase the limits for the tilt angles of the cameras
		m_bAssembly							= TRUE;		// Flag to indicate whether Juan is using this component for the assembly project.

		// Initialize array
		for(i=0;i<4;i++) 
		{
			 m_dSaccadeUpdateAngles[i]			= 0.0;
			 m_dVergenceUpdateAngles[i]			= 0.0;
			 m_dUpdateAngles[i]					= 0.0;
			 m_dMotorAngles[i]					= 0.0;
			 m_dSampleAngles[i]					= 0.0;
			 m_dAverageMotorAngles[i]			= 0.0;
			 m_dMotorPulses[i]					= 0.0;
		}

		// Starting camera angles for Juan's experiments
		m_dPreviousMotorAngles[0]			= -10.0;
		m_dPreviousMotorAngles[1]			= -30.0;
		m_dPreviousMotorAngles[2]			=  10.0;
		m_dPreviousMotorAngles[3]			= -30.0;

		// These are the maximum limits we want to impose on our camera angles. 
		// Physical limits are: -90 <= Pan <= 90; -80 <= Tilt <= 50
		// The values selected below will keep the cameras within the workspace
		m_dTargetThreshold[0]				= -90.0;	// Min Pan-Angle
		m_dTargetThreshold[1]				=  90.0;	// Max Pan-Angle
		m_dTargetThreshold[2]				= -80.0;	// Min Tilt-Angle
		m_dTargetThreshold[3]				=  50.0;	// Max Tilt-Angle

		m_dVergenceUpdateAngles[0] = m_dVergenceUpdateAngles[1] = 0.0f;

		// Threshold parameter to move or not move the cameras
		m_dDeadZone[0] = m_dDeadZone[1]		= 1.0;		// Represents the distance/norm from center of image to center of segmented blob
		m_dTargetDistanceFromCenter[0]		= 0.0;		// Norm for left camera
		m_dTargetDistanceFromCenter[1]		= 0.0;		// Norm for right camera

		// Initialize indeces for IMA 2.5
		m_lDeadZoneIndex					= 0;
		m_lPTTargetThresholdIndex			= 0;
		m_dCameraSpeedFactor				= 0.35;		/* default value */ 		
		
		// IComponent Pointers
		m_pIUnkSmoothPursuit				= NULL;
		m_pIUnkSaccade						= NULL;
		m_pIUnkVisualInputRep				= NULL;
		m_pIUnkMotorControllerLink			= NULL;
		m_pIUnkBPHead						= NULL;
		m_pIUnkMotorOutput					= NULL;
		m_pIUnkMotorInput					= NULL;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_EYEMOTIONCENTER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEyeMotionCenter)
	COM_INTERFACE_ENTRY(IEyeMotionCenter)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()


public:
// IEyeMotionCenter

	// Main Callable Interface Functions	
	STDMETHOD(Initialize)();
	STDMETHOD(DoProportionalTracking)();
	STDMETHOD(HeadSample)();
	STDMETHOD(WriteMotorPositions)();

	// Interface Properties	
	STDMETHOD(get_CameraSpeedFactor)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_CameraSpeedFactor)(/*[in]*/ double newVal);
	STDMETHOD(get_DeadZone)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_DeadZone)(/*[in]*/ double newVal);
	STDMETHOD(get_DeadZoneIndex)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_DeadZoneIndex)(/*[in]*/ long newVal);
	STDMETHOD(get_PTTargetThreshold)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_PTTargetThreshold)(/*[in]*/ double newVal);
	STDMETHOD(get_PTTargetThresholdIndex)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_PTTargetThresholdIndex)(/*[in]*/ long newVal);

	void PerformSaccade(double *Input, double *Output);
	void MoveCatch(double *Value);
	void AcquireTarget();
	void GetTargetLocation();
	void Add2DisparityVector();  //09/05/03

	BOOL ExceedMotorRange(double* Val);
	BOOL AnglesAboveThreshold();
	BOOL PerformSaccade(long CameraID);

	// Variables
	// Indeces
	int i;
	long m_lDeadZoneIndex;
	long m_lPTTargetThresholdIndex;
	BOOL	m_bAssembly;					// Flag to indicate if this is for the AssemblyDemo
	BOOL	bLimitTilt;						// Flag to indicate whether or not to extend the tilt limits on the cameras
	double	m_dTargetDistanceFromCenter[2]; /* left and right */
	double	m_dDeadZone[2];					/* left and right deadzone */
	double	m_dLeftTargetLocation[2];
	double	m_dRightTargetLocation[2];

	double	m_dTargetThreshold[4];			/* for checking if camera head reach the target */
	double	m_dDisparity[2];				/* disparity vector, Li Sun 09/05/03 */
	double  m_dCameraSpeedFactor;			/* Factor that determines the size of the camera step - affects the speed of the cameras*/

	// Camera Angles
	double	alpha;							/* Gain used in averaging motor angles */
	double	m_dPreviousMotorAngles[4];		/* Used for averaging of motor angles in MoveCatch()*/
	double	m_dAverageMotorAngles[4];		/* Used for averaging of motor angles in MoveCatch()*/
	double	m_dUpdateAngles[4];				/* (left pan, left tilt, right pan, right tilt) */
	double	m_dSampleAngles[4];				/* (left pan, left tilt, right pan, right tilt, overall pan and average tilt and verge) */
	double	m_dMotorAngles[4];				/* (left pan, left tilt, right pan, right tilt) */
	double	m_dMotorPulses[4];				/* Motor pulses */
	double	m_dVergenceUpdateAngles[4];		/* (left pan, left tilt, right pan, right tilt) */
	double	m_dSaccadeUpdateAngles[4];		/* (left,tilt) and (right,tilt) */

//	IUnknown* m_pIUnkVergence;
	IComponent* m_pIUnkSmoothPursuit;
	IComponent* m_pIUnkSaccade;
	IComponent* m_pIUnkVisualInputRep;
	IComponent* m_pIUnkMotorControllerLink; /* talk to camera head */
	IComponent* m_pIUnkBPHead;				/* for all motors (left, right, pan, and tilt) */
	IComponent* m_pIUnkMotorOutput;			/* now is for display motor sample */
	IComponent* m_pIUnkMotorInput;			/* now is for display motor commands */
	IComponent* m_pIUnkDisparityVector;		/* now is for display disparity from PTVergence 09/05/03 */

	// DP Pan
	const double MOTOR_RANGE_ANGLES_PAN;	    // pan angle range	
	const double MOTOR_RANGE_PULSES_PAN_LEFT;	// left pulses in servo's range
	const double PULSE_TO_ANG_PAN_LEFT;
	const double MOTOR_RANGE_PULSES_PAN_RIGHT;	// right pulses in servo's range
	const double PULSE_TO_ANG_PAN_RIGHT;

	// DP Tilt
	const double MOTOR_RANGE_ANGLES_TILT;		// tilt angle range	
	const double MOTOR_RANGE_PULSES_TILT;		// pulses in servo's range
	const double PULSE_TO_ANG_TILT;

	const long	 NUM_AXES;						// how many axes does this pantilt have?
private:
	// Internal constuctor/destructor
	STDMETHOD(OnConstruct)(void);
	STDMETHOD(OnDestruct)(void);

	// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT pData);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component
													// This would be equivalent to returning a virtual HRESULT
													// STDMETHOD returns a virtual HRESULT
};

#endif //__EYEMOTIONCENTER_H_
