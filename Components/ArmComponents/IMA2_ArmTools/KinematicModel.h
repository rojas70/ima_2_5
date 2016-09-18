// KinematicModel.h : Declaration of the CKinematicModel

#ifndef __KINEMATICMODEL_H_
#define __KINEMATICMODEL_H_

#define NUM_AXES	6

#include "resource.h"       // main symbols
#include "O:\Base Classes\ComponentImpl.h"
#include "O:\Components\msvbvm60.tlh"				// property bag dll
#include "O:\Include\IMA2_BasicComponentsLib.h"		// Vector Signal 

#ifndef PI
#define	PI	3.14159265
#endif
#ifndef PI2
#define PI2 6.2831853
#endif

/******* KINEMATIC AND TRANSFORM DEFINITIONS *******/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//** Old definitions for ISAC HANDS **/
//#define	OLD_RIGHT_HAND_X	-130.00					// Is used to set the origin in the middle of the hand
//#define	OLD_LEFT_HAND_X		-130.00					// Is used to set the origin in the middle of the hand
//
//#define OLD_RIGHT_HAND_Y		-50.00					// No displacement
//#define OLD_LEFT_HAND_Y		 -50.00					// Translates the origin to the left of the hand by 5 cm.
//
//
//** New method and updated definitions **/
// If end-effectors change for right and left hands please update here and it will change in the rest of the program.
//
// Current definitions involve: ATI FT Sensor + Stand alone plate.
//				   X-direction: 33.0        + 31.75 (1/8 inch) = 364.75
//				   Y-direction:	0
//
#define	RIGHT_HAND_X	 180.0		//was 33.3			
#define RIGHT_HAND_Y	  0.0
#define RIGHT_HAND_Z	  0.0

#define	LEFT_HAND_X		 33.3	
#define LEFT_HAND_Y		  0.0
#define LEFT_HAND_Z		  0.0
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** BASE TRANSFORMATION **/
// These are transformation that displace the origin of the arm (shoulder of isac) to the origin of the eyes. 
// The translation for the right-Y and left-Y are slightly different for the arms. The BASE_Y values are different
// because the center point for the eyes is not half-way between both arms. It is slightly closer to the left-arm, 
// thus this number being smaller.
// 
// This notion is based on a static point for the robot. 
// 
// Given the nature of our cameras, they move when detecting objects of interest, effectively changing the center
// point for the robot. This should be accounted for in the base transform. 
// 
// This can be easily down by including the transformation computed in the O:\Components\HeadComponents\IMA2_3DPositionLib program.
// Documentation for that transform can be found at: O:\Documentation\Component Description\Head\Head Change\Compute3DPosition.doc
//
// The values for that transformation can be appended unto a VS from the head, and copied and added in this compoent. 
// Yet to be implemented.
// 
// Juan Rojas. Jan 2009.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define RIGHT_BASE_X	- 42.0
#define RIGHT_BASE_Y	-265.0
#define RIGHT_BASE_Z	-360.0		// -330.0 Old value. 

#define LEFT_BASE_X		- 42.0
#define LEFT_BASE_Y		 230.0
#define LEFT_BASE_Z		-360.0	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** DH PARAMETERS **/
// These are the kinematic parameters for both the right and left arms
#define RIGHT_A2	 320.0	// 330.0 is old value. I think 320 is more precise. 
#define RIGHT_A3	   0.0
#define RIGHT_D3	-200.0	
#define RIGHT_D4	 334.0	// 290.0	is old value. 334 is measured from the joint to the edge of the circular metalic plate that holds the FT sensor.
							// The End Effector transform starts from that edge.
#define LEFT_A2		 320.0	// Changes to these parameters were made on Jan. 2009
#define LEFT_A3	       0.0
#define LEFT_D3		 200.0	
#define LEFT_D4		 334.0	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CSAKinematics;
/////////////////////////////////////////////////////////////////////////////
// CKinematicModel
/////////////////////////////////////////////////////////////////////////////
class ATL_NO_VTABLE CKinematicModel : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CKinematicModel, &CLSID_KinematicModel>,
	public IDispatchImpl<IKinematicModel, &IID_IKinematicModel, &LIBID_IMA2_ARMTOOLSLib>,
	public CComponentImpl 

{
public:
	CKinematicModel()
	{
		int i;

		// Boolean Flag
		m_bInitialized	= 0;

		// Number of Axes for Robot
		m_lNumAxes	= NUM_AXES;

		// What Arm
		m_LeftArm	= 0;				// Arm and hand flag
		m_sRightHand= 1;

		// CSAKinematics Pointer. Constructor is allocated in the .cpp file
		m_pKMArm	= NULL;

		/** Assign Tranform parameters. Uses #define values **/
		// RIGHT HAND
		if (m_sRightHand == 1) 
		{
			/** Transformations **/
			// End Effector Transformation
			m_pdEndEffXform[0]	= RIGHT_HAND_X;	// Look at the #definition's to update numbers there.
			m_pdEndEffXform[1]	= RIGHT_HAND_Y;	

			// Base Tranformation
			// Shoulder base to mid-eye transformation for Right Arm.
			// Values are changed in .cpp file if LeftArm is selected
			m_pdBaseXform[0]	= RIGHT_BASE_X;		// x-coord (into the robot).	Orig value =  -60.0. Updated Nov 2006.
			m_pdBaseXform[1]	= RIGHT_BASE_Y;		// y-coord (horizontally).		Orig value =  -265.0. Updated Nov 2006.
			m_pdBaseXform[2]	= RIGHT_BASE_Z;		// z-coord (vertically).		Orig value =  -275.0. Updated Nov 2006.
													// ** z-coord is determined to be -295 from the shoulder midpoint to the mid-point of cameras. But this value empirically is much more effective.
													// You can try to change it as you test the arm on-line if the z-dist. is not accurate.
			/** DH Parameters **/
			m_dA2		=  RIGHT_A2;
			m_dA3		=  RIGHT_A3;
			m_dD3		=  RIGHT_D3;			
			m_dD4		=  RIGHT_D4;	
		}

		// LEFT HAND
		else 
		{
			/** Transformations **/
			// End Effector Transformation
			m_pdEndEffXform[0]	=  LEFT_HAND_X;	
			m_pdEndEffXform[1]	=  LEFT_HAND_Y;	

			// Base Transformation
			m_pdBaseXform[0]	= LEFT_BASE_X;		
			m_pdBaseXform[1]	= LEFT_BASE_Y;		
			m_pdBaseXform[2]	= LEFT_BASE_Z;

			/** DH Parameters **/
			m_dA2		=  LEFT_A2;
			m_dA3		=  LEFT_A3;
			m_dD3		=  LEFT_D3;			
			m_dD4		=  LEFT_D4;

		}

		// The rest of the transformation parameters are the same for both arms.
		m_pdEndEffXform[2]	=    0.0;		 
		m_pdEndEffXform[3]	=    0.0;			// Roll
		m_pdEndEffXform[4]	=    PI/2;			// Pitch. Necessary to align axes!
		m_pdEndEffXform[5]	=    0.0;			// Yaw

		m_pdBaseXform[3]	= 0.0;		
		m_pdBaseXform[4]	= 0.0;		
		m_pdBaseXform[5]	= 0.0;		

		/** Axes Limits **/ 
		for(i=0;i<NUM_AXES;i++) 
		{
			m_pdAxisMax[i]	= 100.0;	// For ForwardKinematics make sure to change index[0] for both to +/-500 in DAD
			m_pdAxisMin[i]	=-100.0;
		}

		// IComponent variables
		m_pIUnkIn		= NULL;
		m_pIUnkOut		= NULL;
		m_pIUnkCmd		= NULL;

		// Array indeces
		m_sEndEffXformIndex=m_sBaseXformIndex=m_sAxisMinIndex=m_sAxisMaxIndex=0;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_KINEMATICMODEL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CKinematicModel)
	COM_INTERFACE_ENTRY(IKinematicModel)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()

// IKinematicModel
public:
	STDMETHOD(Initialize)();
	STDMETHOD(kin_InverseKinematics)();
	STDMETHOD(kin_ForwardKinematics)();

	STDMETHOD(get_AxisMinIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_AxisMinIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_AxisMaxIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_AxisMaxIndex)(/*[in]*/ short newVal);	
	STDMETHOD(get_AxisMin)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_AxisMin)(/*[in]*/ double newVal);
	STDMETHOD(get_AxisMax)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_AxisMax)(/*[in]*/ double newVal);

	STDMETHOD(get_transform_BaseXformIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_transform_BaseXformIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_transform_BaseXform)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_transform_BaseXform)(/*[in]*/ double newVal);
	STDMETHOD(get_transform_EndEffXformIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_transform_EndEffXformIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_transform_EndEffXform)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_transform_EndEffXform)(/*[in]*/ double newVal);

	STDMETHOD(get_param_D4)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_param_D4)(/*[in]*/ double newVal);
	STDMETHOD(get_param_D3)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_param_D3)(/*[in]*/ double newVal);
	STDMETHOD(get_param_A3)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_param_A3)(/*[in]*/ double newVal);
	STDMETHOD(get_param_A2)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_param_A2)(/*[in]*/ double newVal);

	STDMETHOD(get_WhatArm)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_WhatArm)(/*[in]*/ BSTR newVal);

private:

	// IMA Component Links
	IComponent *m_pIUnkIn;
	IComponent *m_pIUnkOut;
	IComponent *m_pIUnkCmd;
	IComponent *m_pIUnkMotion;
	
	// Boolean Flag
	bool m_bInitialized;				// Flag to indicate if function has been initialized.

	// Kinematics Class Pointer
	CSAKinematics	*m_pKMArm;

	// DH Parameters
	double	m_dA2;
	double	m_dA3;
	double	m_dD3;
	double	m_dD4;
	
	// What Arm is being used
	short	m_LeftArm;				// Flag to indicate LeftArm is in use
	// Not used anymore
	short m_sRightHand;						// Are we using the right hand, true/false

	long	m_lNumAxes;

	// Transform vectors
	double	m_pdEndEffXform[NUM_AXES];		// Transformation from the last joint to either the middle of the palm or middle of the fingers
	double	m_pdBaseXform[NUM_AXES];		// Transformation from the Shoulder to the origin of ISAC

	// Axis limits
	double	m_pdAxisMax[NUM_AXES];
	double	m_pdAxisMin[NUM_AXES];

	// Array indeces for IMA 2.5
	short m_sBaseXformIndex;
	short m_sEndEffXformIndex;
	short m_sAxisMinIndex;
	short m_sAxisMaxIndex;

private:
	// Internal constuctor/destructor
	STDMETHOD(OnConstruct)(void);
	STDMETHOD(OnDestruct)(void);

	// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT pData);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component
};

#endif //__KINEMATICMODEL_H_
