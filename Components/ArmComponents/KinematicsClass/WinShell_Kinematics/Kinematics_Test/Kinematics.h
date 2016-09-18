//   Kinematics.h
//	This file is the header file for the softarm kinematics library.
//	This library is based on the derivation of the Puma 560 kinematics in
//	Craig's Robotics Text, but departs in several places to simplify the solutions
//	for softarm robots and improve robustness.
//
//	The input and output for this kinematic model is based on the angle-axis
//	representation of orientation, but support for other orientation setups
//	is also included. The angle-axis representation makes special use of the
//	matrix structure to reduce the chance of a singularity in calculations and
//	should be the most robust representaion.
//
//
//	XYZAA is a representation of arm WRIST point position in the base frame of the arm:
//	XYZAA[0-2]	= the XYZ position of the arm in the base frame.
//  XYZAA[3-5]	= the "pointing vector" for the arm in the base frame.
//	XYZAA[6]	= the "rotation about" the pointing vector of the arm.
//
//  Key to simplification: (gives perfect inversion even in "sigular" cases)
//	For the SoftArm XYZAA[0-2] is basically determined by parameters and Ang[0-2]
//	XYZAA[3-5] are determined by Ang[3-4]
//	XYZAA[6] = Ang[5]
//
// Tools and additional transformations can be applied to generate a "wrist point" based
// on other desired points. 
//
// Conventions: Angles are stored in radians, all distances are measured in millimeters.
//

#if !defined(AFX_KINEMATICS_H__24246A86_724F_48F2_8598_2E436CEFCF0C__INCLUDED_)
#define AFX_KINEMATICS_H__24246A86_724F_48F2_8598_2E436CEFCF0C__INCLUDED_

#include <math.h>

#ifndef   PI
#define	  PI	3.14159265359
#endif

#define	  R2D	(180.0 / PI)
#define	  D2R	(PI / 180.0)

#define NUM_AXES 6

// Bitmask positions for joint error flags
#define	JOINT_0_ERR	0x0001
#define JOINT_1_ERR 0x0002
#define JOINT_2_ERR 0x0004
#define JOINT_3_ERR 0x0008
#define JOINT_4_ERR 0x0010
#define JOINT_5_ERR 0x0020
#define ANY_JOINT_ERR -998	/*0x003f*/
#define SCALE_ERR -999		/*0x0040*/
#define KINEMATICS_OK 0x0000

#define FALSE 0


// Defines for angle status:
#define ANGLE_OK	0
#define ANGLE_ABOVE	1
#define ANGLE_BELOW	2

class Kinematics  
{
	public:

		Kinematics(short LeftHanded = 0, short EndEffector = 1);// Left Handed Version or Right Handed Version

		int GetW2EI(double oM[16]);

		int GetW2ETransform(double M[16]);
		int SetW2ETransform(double M[16]);

		int	GetXYZAA(double XYZAA[7]);		// Angle Axis outputs.
		int SetXYZAA(double XYZAA[7]);		// Angle Axis inputs.

		int	GetXYZRPY(double XYZRPY[6]);	// Wrist angle(Roll, Pitch, Yaw) + position outputs (XYZ).
		int SetXYZRPY(double XYZRPY[6]);	// Wrist angle(Roll, Pitch, Yaw) + position inputs  (XYZ).

		int GetXYZRPYMat(double M[16],double XYZRPY[6]); // Compute angle + position outputs (XYZRPY params) from 4x4 matrix

		int	GetAngles(double oAng[6]);		// Angle outputs.
		int	SetAngles(double iAng[6]);		// Angle inputs.

		int	GetT(double oMatrix[16]);		// Transform outputs.
		int GetB2E(double oMatrix[16]);		// Base-to-effector transformation matrix
		int GetAxisT(unsigned int i, double oMatrix[16]);	// Individual Link Transform Out.
		int	SetT(double iMatrix[16]);		// Transform inputs.

		int	SetParameters(double iD3,double iD4, double iA2, double iA3);
		int	GetParameters(double &oD3,double &oD4,double &oA2,double &oA3);

		int	GetJacobian(double oMatrix[16]); // Fwd Jacobian

		int SetRPYMatrix(double RPY[6], double oM[16]);

		// Implementation functions for transformation math (assumes homogeneous transforms)
		int InverseTransform(double M1[16]);
		int PostMult(double M1[16],double M2[16]);
		int PreMult(double M1[16],double M2[16]);

		// KINEMATICS ********

		// Sets B2W based on Angles
		int ForwardKinematics();

		// Sets Ang based on B2W
		int InverseKinematics();

		double	Ang[6];			// State Variables: X,Y,Z,Roll,Pitch,Yaw
		int		AngStat[6];		// Angle status.

		double	B2W[16];		// Base-to-Wrist transformation matrix.
		double  W2E[16];		// Wrist-to-Effector transformation matrix.
		double  W2EI[16];		// Wrist-to-Effector Inverse transformation matrix:
		double	B2E[16];		// Base-to-Effector transformation matrix.

		double LowLimit[6];		// Angle Limits in the Model.
		double UpLimit[6];

		// Kinematic model parameters

		double	m_dA2;
		double	m_dA3;
		double	m_dD3;
		double	m_dD4;

//		Kinematics	*m_pKMArm;
		
		short	m_LeftArm;						// Flag to indicate if the left or the right arm is in use
		short m_sEndEffector;					// Indicates if we are using an end-effector

		long	m_lNumAxes;
		double	m_pdEndEffXform[NUM_AXES];		// Transformation from the last joint to either the middle of the palm or middle of the fingers
		double	m_pdBaseXform[NUM_AXES];		// Transformation from the Shoulder to the origin of ISAC

		double	m_pdAxisMax[NUM_AXES];
		double	m_pdAxisMin[NUM_AXES];

		// Using hand?
		short m_sRightHand;				// Are we using the right hand, true/false

		// Array indeces for IMA 2.5
		/*short m_sBaseXformIndex;
		short m_sEndEffXformIndex;
		short m_sAxisMinIndex;
		short m_sAxisMaxIndex;*/

		virtual ~Kinematics();

};

#endif // !defined(AFX_KINEMATICS_H__24246A86_724F_48F2_8598_2E436CEFCF0C__INCLUDED_)
