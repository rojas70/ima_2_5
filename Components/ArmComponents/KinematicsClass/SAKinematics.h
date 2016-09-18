// SAKinematics.h
//	This file is the header file for the softarm kinematics library.
//	This library is based on the derivation of the Puma 560 kinematics in
//	Craig's Robotics Text, but departs in several places to simplify the solutions
//	for softarm robots and improve robustness.
//
//  Robert Todd Pack
//  Fall 1996
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

#ifndef	_SAKINEMATICS_
#define _SAKINEMATICS_

#include <math.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Matrix and Vector Dimensions
#define NUM_AXES	 6	// Size of vectors
#define MATRIX_SZ	16	// Size of matrices
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Radian Definitions
#ifndef PI
#define	PI	3.14159265359
#endif

#define	  R2D	(180.0 / PI)
#define	  D2R	(PI / 180.0)
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Defines for angle status:
#define ANGLE_OK	0
#define ANGLE_ABOVE	1
#define ANGLE_BELOW	2
#define	JOINT_ERROR(x,y) (x&y)
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** DH PARAMETERS **/
/** Must match those in KinematicModel.h **/ 
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** THETA ANGLES AT HOME POSITION **/
// Angles are in radians
#define THETA0    0.0;		//  0 radians
#define THETA1   90.0		//  PI / 2.0 radians
#define THETA2 -180.0;		// -PI radians
#define THETA3    0.0;		//  0 radians
#define THETA4    0.0;		//  PI/2 radians
#define THETA5    0.0;		//  PI radians
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


class CSAKinematics
{
	public:
	int GetW2EI(double oM[16]);
	int GetW2ETransform(double M[16]);
	int SetW2ETransform(double M[16]);

		CSAKinematics(short LeftHanded = 0);// Left Handed Version or Right Handed Version
		~CSAKinematics();

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

	private:

		// Sets B2W based on Ang
		int ForwardKinematics();

		// Sets Ang based on B2W
		int InverseKinematics();


		// Private member variables
		int		AngStat[NUM_AXES];		// Angle status.	
		double	Ang[NUM_AXES];			// State Variables: X,Y,Z,Roll,Pitch,Yaw
		double	LowLimit[NUM_AXES];		// Angle Limits in the Model.
		double	UpLimit[NUM_AXES];

		double	B2W[MATRIX_SZ];			// Base-to-Wrist transformation matrix.
		double  W2E[MATRIX_SZ];			// Wrist-to-Effector transformation matrix.
		double  W2EI[MATRIX_SZ];		// Wrist-to-Effector Inverse transformation matrix:
		double	B2E[MATRIX_SZ];			// Base-to-Effector transformation matrix.

		double	D3,D4;			// DH Parameters.
		double	A2,A3;

	public:

	// Implementation functions for transformation math (assumes homogeneous transforms)
	int InverseTransform(double M1[16]);
	int PostMult(/*[in],[out]*/double M1[16],/*[in]*/double M2[16]);
	int PreMult(/*[in],[out]*/double M1[16],/*[in]*/double M2[16]);

};

#endif