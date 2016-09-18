// Kinematics.cpp: implementation of the Kinematics class.
//
//////////////////////////////////////////////////////////////////////

//MODIFICATIONS BY SEAN BEGLEY 03/12/2008
//	- fixed bug with m_pdBaseXform[1] not having a seperate value for the Left & Right Arm
//	- moved the setting of pdPos[0-3] from Kinematics::Kinematics (in Kinematics.cpp) to Inverse Kinematics
//		to fix a bug

#include "stdafx.h"
#include "Kinematics.h"
#define	PI	3.14159265
#define NUM_AXES	6
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Kinematics::Kinematics(short LeftHanded, short EndEffector)
{
	unsigned int i,j;
	
	m_lNumAxes	= 6;
	m_LeftArm	= 0;											// Arm and hand flag
	m_sRightHand= 1;
	m_pdEndEffXform[0]=m_pdEndEffXform[1]=m_pdEndEffXform[2]=0;	// Initialize variables

	// Default Model Parameters for the current arms.
	// 6 Degree's of Freedom (DOF) Arm's

	/* DH Params for Right Arm

		i | alpha i-1 | ai-1 | di | thetai
		----------------------------------
		0 |    0      |   0  |  0 | theta0
		1 |  -90      |   0  |  0 | theta1
		2 |    0      |  a2  | d3 | theta2
		3 |  -90      |   0  | d4 | theta3
		4 |   90      |   0  |  0 | theta4
		5 |  -90      |   0  |  0 | theta5
		
	// Alpha's are described in ::GetAxisT(UINT,double)	*/
	// m_dD3 Parameter. Horizontal distance: 20 cm from the center of the eyes to the shoulder base.


	// Check to see if we are working with the Left Arm
	if (LeftHanded == 1)
		m_dD3 = 200.0;				// Left Arm Parameter
	else
		m_dD3 = -200.0;				// Right Arm Parameter. 

	/**** Standard Arm Parameters ***/		
	m_dA2 = 330.0;					// Vertical distance from the shoulder to the elbow
	m_dA3 = 0.0;					// No Puma Offset on this arm (Vertical distance from the elbow to the wrist).
	m_dD4 = 290.0;					// Distance from the elbow to the wrist. Same for both arms. 

	
	// End-Effector

	// Check to see if we are using end-effector
	if (EndEffector == 1)
	{
		// RIGHT HAND
		if (LeftHanded == 0) 
		{
			// End Effector Transformation
			m_pdEndEffXform[0]	= -180.0;	// x-coord: used to translate the x-coord to reflect the added distance of the hand 
			m_pdEndEffXform[1]	= - 50.0;	// y-coord: used to translate the y-coord to reflect the added distance of the hand (horizontally)
		}

		// LEFT HAND
		else 
		{
			m_pdEndEffXform[0]	=  -180;	// x-coord: used to translate the x-coord to reflect the added distance of the hand 
			m_pdEndEffXform[1]	=    50;		// y-coord: used to translate the y-coord to reflect the added distance of the hand (horizontally)// No discplacement. 			
		}
	}
	
	if (LeftHanded == 0)
	{
		m_pdBaseXform[1]	= -265.0;		// y-coord (horizontally).		Orig value =  -265.0. Updated Nov 2006.
	}
	else
	{
		m_pdBaseXform[1]	= 230.0;		// y-coord (horizontally).		Orig value =  -265.0. Updated Nov 2006.
	}

	// Same for the rest of these parameters
	m_pdEndEffXform[2]	=    0.0;		 
	m_pdEndEffXform[3]	=    0.0;		
	m_pdEndEffXform[4]	=    0.0;		
	m_pdEndEffXform[5]	=    PI;		

	// Shoulder base to mid-eye transformation for Right Arm.
	// Values are changed in .cpp file if LeftArm is selected
	m_pdBaseXform[0]	= -42.0;		// x-coord (into the robot).	Orig value =  -60.0. Updated Nov 2006.
	m_pdBaseXform[2]	= -330.0;		// z-coord (vertically).		Orig value =  -275.0. Updated Nov 2006.
										// z-coord is determined to be -295 from the shoulder midpoint to the mid-point of cameras. But his value empirically is much more effective.
										// You can try to change it as you test the arm on-line if the z-dist. is not accurate.
	m_pdBaseXform[3]	= 0.0;		
	m_pdBaseXform[4]	= 0.0;		
	m_pdBaseXform[5]	= 0.0;		

	for(i=0;i<NUM_AXES;i++) 
	{
		m_pdAxisMax[i]	= 100.0;	// For ForwardKinematics make sure to change index[0] for both to +/-500 in DAD
		m_pdAxisMin[i]	=-100.0;
	}
	
	// Default Joint Angles, Theta's
	// "Capital L" Home Position
	Ang[0] = 0.0;			// 0	radians
	Ang[1] = PI / 2.0;		// 1.57 radians
	Ang[2] = -PI;			// -3.142 radians
	Ang[3] = 0.0;			// 0 radians 
	if (LeftHanded == 1)
		Ang[4] = PI / 2.0;
	else					// Wrist positions are different for the two arms.
		Ang[4] = - PI / 2.0;
	Ang[5] = 0.0;			// 0 radians

	// Establish upper and lower limits
	for (j = 0; j < 6; j++)
	{
		LowLimit[j] = -250.0;
		UpLimit[j] = 250.0;
		AngStat[j] = ANGLE_OK;		// Angle status
	}

	// Initialize B2W (base-to-wrist) from angles
	ForwardKinematics();

	// Initialize W2E (wrist-to-effector) and W2EInverse and Identity matrices.
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4 ;j++)
		{
			// Create a diagonal identity matrix
			if (i==j)	
				{
				 W2E[i+4*j]	= 1.0;
				 W2EI[i+4*j]= 1.0;
				}
			else
			   { 
				W2E[i+4*j]  = 0.0;
				W2EI[i+4*j] = 0.0;
			   }
		}

	// Initialize B2E. 
	// B2E is equal to B2W because W2E is I
	// B2E = B2W * W2E = B2W * I = B2W
	for (i = 0; i < 16; i++)
		B2E[i] = B2W[i];	
}

Kinematics::~Kinematics(){}

//-------------------------------------------------------------------------------------------------------------------


int	Kinematics::GetXYZAA(double XYZAA[7])
{
	double Tmp;

	// Position Vector. See p. 25 of O:\Components\ArmComponents\KinematicsClass\PumaFamilyDerivation.pdf 
	XYZAA[0] = B2E[12];	// X
	XYZAA[1] = B2E[13];	// Y
	XYZAA[2] = B2E[14];	// Z

	// Rotational Angle r11, r22, r33
	Tmp = (B2W[0] + B2W[5] + B2W[10] - 1.0) / 2.0;
	if (fabs(Tmp)  > 0.999)	// Basically zero rotation or 180 rotation...
	{
		XYZAA[6] = 0.0;
	}
	else
		XYZAA[6] = acos(Tmp);

	if (XYZAA[6] != 0.0)
	{
		Tmp = 2.0 * sin(XYZAA[6]);
		// Orientation Vector	- Meaningless with small angles.
		XYZAA[3] = (B2E[6] - B2E[9]) / Tmp;
		XYZAA[4] = (B2E[8] - B2E[2]) / Tmp;
		XYZAA[5] = (B2E[1] - B2E[4]) / Tmp;
	}
	else
	{
		XYZAA[3] = 0.0;
		XYZAA[4] = 0.0;
		XYZAA[5] = 0.0;
	}
		

	return KINEMATICS_OK;
}


////////////////////////////////
// Set the Angle Axis inputs.
////////////////////////////////
int Kinematics::SetXYZAA(double XYZAA[7]) // Uses Inv Kinematics & Fwd Kinematics
{
	double TMat[16];			// Transform matrix
	double ct,st,vt;
	double Tmp;
	int i;

	// Insurance for Angle-Axis:
	Tmp = 0.0;
	for (i = 3; i < 6; i++)
		Tmp += XYZAA[i]*XYZAA[i];

	if (Tmp < 0.0001) return 0;		// Too close to a zero vector so angles don't change.
	// Actually it becomes undefined, so for consistnecy I assume angles are not changed in this case.

	// Normalize this axis vector (in case it's not normal).
	Tmp = sqrt(Tmp);
	if (Tmp != 1.0)
	{
		for (i = 3; i < 6; i++)
			XYZAA[i] = XYZAA[i] / Tmp;
	}

	// Build Angle Axis Matrix in TMat...
	ct = cos(XYZAA[6]);					// Roll Angle
	st = sin(XYZAA[6]);
	vt = 1.0 - ct;

	// First Column
	TMat[0] = XYZAA[3]*XYZAA[3]*vt + ct;
	TMat[1] = XYZAA[3]*XYZAA[4]*vt + XYZAA[5]*st;
	TMat[2] = XYZAA[3]*XYZAA[5]*vt - XYZAA[4]*st;
	TMat[3] = 0.0;

	// Second Column
	TMat[4] = XYZAA[3]*XYZAA[4]*vt - XYZAA[5]*st;
	TMat[5] = XYZAA[4]*XYZAA[4]*vt + ct;
	TMat[6] = XYZAA[4]*XYZAA[5]*vt + XYZAA[3]*st;
	TMat[7] = 0.0;


	//Third Column
	TMat[8] = XYZAA[3]*XYZAA[5]*vt + XYZAA[4]*st;
	TMat[9] = XYZAA[4]*XYZAA[5]*vt - XYZAA[3]*st;
	TMat[10] = XYZAA[5]*XYZAA[5]*vt + ct;
	TMat[11] = 0.0;

	// Translation Parameters
	TMat[12] = XYZAA[0];
	TMat[13] = XYZAA[1];
	TMat[14] = XYZAA[2];
	TMat[15] = 1.0;


	return SetT(TMat);						// Inverse kinematics based on new goal transformation.
}

/////////////////////////////////////////////////////////////////////////
// Returns position vector and orientation in terms of roll, pitch, yaw
/////////////////////////////////////////////////////////////////////////
int	Kinematics::GetXYZRPY(double XYZRPY[6])
{
	return GetXYZRPYMat(B2E,XYZRPY);
}


///////////////////////////////////////////////////////////
// Converts a homogeneous transform matrix into xyz, rpy
///////////////////////////////////////////////////////////
int Kinematics::GetXYZRPYMat(double M[16],double XYZRPY[6])
{
	double cb;

	// Position Vector:
	 XYZRPY[0] = M[12];	// X
	 XYZRPY[1] = M[13];	// Y
	 XYZRPY[2] = M[14];	// Z

	 // Orientation Angle Solution:
	 // Solve for Roll, Pitch, Yaw. See Robot Simulation by Dr. Cook page A-12,13

	 XYZRPY[4] = atan2(-M[2],sqrt(M[0]*M[0] + M[1]*M[1]));	// Beta = atan2(-r31, sqrt(r11^2 + r21^2))

	 cb = cos(XYZRPY[4]);									


	 // Take care of degenerate case: i.i if Beta = +/- 90 degrees
	 // See Robot Simulation by Dr. Cook page A-14
	 if (fabs(cb) > 0.0001)	// Almost 90 degrees for B angle then assume 90 degrees 
	 {
		XYZRPY[5] = atan2(M[1]/cb, M[0]/cb);
		XYZRPY[3] = atan2(M[6]/cb, M[10]/cb);
	 }
	 else // Degenerate case.
	 {
		XYZRPY[5] = 0.0;
		XYZRPY[3] = atan2(M[4], M[5]);
	 }

	 return KINEMATICS_OK;
}


int	Kinematics::SetXYZRPY(double XYZRPY[6])
{
	// Compute the Base-Wrist Transform
	SetRPYMatrix(XYZRPY, B2E);								// Set destination transformation to B2E
	// Call the inverse kinematics function after the transform is computed 
	SetT(B2E);												// At this point the B2E is really a B2W and will be transformed in the next call
	PostMult(B2W,W2EI);				// Invert the wrist to effector transformation.

	return InverseKinematics();		// find joint angles according to new B2W
}

////////////////////////////////////////////////////////////////////////////////
// Input:  Position Matrix XYZRPY
// Output: Homogenous Transformation (In the main part of the inv. kin = B2E)
// Create a XYZ Euler Angle Transformation Matrix and append position at the end
////////////////////////////////////////////////////////////////////////////////
int Kinematics::SetRPYMatrix(double RPY[6], double oM[16])
{
	double ca,cb,cg;		// Cosine Saves
	double sa,sb,sg;		// Sine Saves

	// Precompute Trig Functions to save on evaluations
	ca = cos(RPY[5]); sa = sin(RPY[5]);
	cb = cos(RPY[4]); sb = sin(RPY[4]);
	cg = cos(RPY[3]); sg = sin(RPY[3]);

	// Inverse solution for roll-pitch-yaw angle set
	// 
	// Rz(alpha)Ry(Beta)Rx(gamma) = 
	//	 | ca -sa 0 || cB  0 sB || 1  0 0  |		| r11 r12 r13  Px|
	//	 | sa ca  0 || 0   1  0 || 0 cy -sy| = oM = | r21 r22 r23  Py|	// See Robot Simulation by Dr. Cook page A-12
	//	 | 0   0  1 ||-sB  0 cB || 0 sy cy |		| r31 r32 r33  Pz|
	//												|   0   0   0   1|
	
					  
	// First Column
	oM[0] = ca*cb;					// r11
	oM[1] = sa*cb;					// r21
	oM[2] = -sb;					// r31
	oM[3] = 0.0;					// r41

	// Second Column
	oM[4] = ca*sb*sg - sa*cg;		// r12
	oM[5] =	sa*sb*sg + ca*cg;		// r22
	oM[6] =	cb*sg;					// r32
	oM[7] = 0.0;					// r42
	
	// Third Column
	oM[8] = ca*sb*cg + sa*sg;		// r13
	oM[9] = sa*sb*cg - ca*sg;		// r23
	oM[10] = cb*cg;					// r33
	oM[11] = 0.0;					// r43

	// Fourth Column -  position vector.
	oM[12] = RPY[0];				// X	
	oM[13] = RPY[1];				// Y
	oM[14] = RPY[2];				// Z
	oM[15] = 1.0;

	return 0;
}


int	Kinematics::GetAngles(double oAng[6])
{
	int i;

	for (i = 0; i < 6 ; i++)
		oAng[i] = Ang[i];

	return KINEMATICS_OK;
}


int	Kinematics::SetAngles(double iAng[6])
{
	int i,j;

	for (i = 0; i < 6 ; i++)
	{
		if (iAng[i] > UpLimit[i])
			AngStat[i] = ANGLE_ABOVE;
		else if (iAng[i] < LowLimit[i])
			AngStat[i] = ANGLE_BELOW;
		else 
			AngStat[i] = ANGLE_OK;

		Ang[i] = iAng[i];
	}

	i =  ForwardKinematics();		// Sets up B2W properly from angles.

	for (j = 0; j < 16; j++)
		B2E[j] = B2W[j];			// Set B2E to B2W

	PostMult(B2E,W2E);				// Add in gripper transformation.

	return i;

}

////////////////////////////////
// Get Base-to-effector matrix
// Copy B2E to 4x4 matrix
/////////////////////////////////
int Kinematics::GetB2E(double oMatrix[16])
{
	int i;
	for (i = 0; i< 16;i++)
	 oMatrix[i] = B2E[i];

	return KINEMATICS_OK;

}


int	Kinematics::GetT(double oMatrix[16])	// Uses Fwd Kinematics
{
	int i;
	for (i = 0; i< 16;i++)
		oMatrix[i] = B2W[i];

	return KINEMATICS_OK;
}


///////////////////////////////////////////////////////////////////
// Will calculate Forward Kinematics - obtain transformation matrix
// Look at Appendix A, Section 2.0 of Robot Simulation by Dr. Cook
// or its equivalent in Dr. Craigs book
///////////////////////////////////////////////////////////////////
int Kinematics::GetAxisT(unsigned int i, double oMatrix[16])
{
// Temp DH parameters representing: a, d, Theta,Alpha
 double TA,TD,TT,TL;	


	if (i < 6)
	{
	// Setup Temps based on Axis
		TT = Ang[i];	// theta
		TA = 0.0;		// a
		TL = 0.0;		// alpha
		TD = 0.0;		// d

	/**** SET the DH Params ****/
	// Look at p. 25 of the pdf in the O:\Components\ArmComponents\KinematicsClass folder
	// We are filling the DH Table for the different joints
		switch (i)
		{
			// Joint 1
			case 0:				
				break;
			// Joint 2
			case 1:
				TL = - PI/2.0;		// -90 degrees
				break;
			// Joint 3
			case 2:
				TA = m_dA2;
				TD = m_dD3;
				break;
			// Joint 4
			case 3:
				TL = - PI/2.0;		// - 90 degrees
				TA = m_dA3;
				TD = m_dD4;
				break;
			// Joint 5
			case 4:
				TL = PI/2.0;		// 90 degrees
				break;
			// Joint 6
			case 5:
				TL = - PI/2.0;		// -90 degrees
				break;
			default:
				break;
		}

		/*** Fill a DH-matrix based on temps ***/
		double cT, sT;		// Cosine and Sine save evaluations:
		double cA, sA;	

		// Fill matrix based on DH-parameters
		// Look at p. 25 in the pdf in the SAKinematics folder
		// Evaluate these only once.
		cT = cos(TT);

		sT = sin(TT);
		cA = cos(TL);		// Alpha of previous DHP frame
		sA = sin(TL);

		// Look at equation A.41 in Robot Simulation by Dr. Cook
		// Overall Transformation Matrix
		//				
		//				| cT	-sT		 0		 a		|
		//	(i-1)Ti =	| stcA	cTcA	-sA		-sA*d	|
		//				| sTsA	cTsA	 cA		cA*d	|
		//				|	0	 0		 0		 1		|

		// Column 1
		oMatrix[0] = cT;
		oMatrix[1] = sT*cA;
		oMatrix[2] = sT*sA;
		oMatrix[3] = 0.0;

		// Column 2
		oMatrix[4] = -sT;
		oMatrix[5] = cT*cA;
		oMatrix[6] = cT*sA;
		oMatrix[7] = 0.0;

		// Column 3
		oMatrix[8] = 0.0;
		oMatrix[9] = - sA;
		oMatrix[10] = cA;
		oMatrix[11] = 0.0;

		// Column 4
		oMatrix[12] = TA;
		oMatrix[13] = - sA * TD;
		oMatrix[14] = cA * TD;
		oMatrix[15] = 1.0;

		return KINEMATICS_OK;
	}
	else
		return FALSE;
}


// Forward Jacobian
// not implemented for now
int	Kinematics::GetJacobian(double oMatrix[16])
{
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////////////////////
// Set the (B2W) base-to-wrist matrix: 6-T-0 
//
// Set up the Base-to-Effector Matrix
// First get the Base-to-Wrist Matrix, then post-multiply by the Wrist-to-Effector Matrix
// To get the Base-to-Effector Martrix
// Look at p. 36 of 
//////////////////////////////////////////////////////////////////////////////////////////
int	Kinematics::SetT(double iMatrix[16])
{ 
	int i;
	int ret;

	for (i = 0; i < 16; i++)
		B2W[i] = iMatrix[i];

	// Set up B2W so compute angles from this transformation.
		ret = InverseKinematics();


	// Set up the Base-to-Effector Matrix
	// First get the Base-to-Wrist Matrix, then post-multiply by the Wrist-to-Effector Matrix
	// To get the Base-to-Effector Martrix
	for (i = 0; i < 16; i++)
		B2E[i] = B2W[i];			// Copy in the new B2W

	PostMult(B2E,W2E);				// Add in the W2E transformation.

	return ret;
}

/////////////////////////
// Set the DH parameters
/////////////////////////
int	Kinematics::SetParameters(double iD3,double iD4, double iA2, double iA3)
{
	m_dD3 = iD3;
	m_dD4 = iD4;
	m_dA2 = iA2;
	m_dA3 = iA3;

	return ForwardKinematics();	// Recompute the transform based on new parameters
}


///////////////////////////
// Get the DH parameters
///////////////////////////
int	Kinematics::GetParameters(double &oD3,double &oD4,double &oA2,double &oA3)
{
	oD3 = m_dD3;
	oD4 = m_dD4;
	oA2 = m_dA2;
	oA3 = m_dA3;

	return KINEMATICS_OK;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Kinematics::ForwardKinematics()
// The following routines conspire to keep the angle-vector Ang[] and the base to wrist
// transformation matrix B2W in SYNC and consistent at ALL times. Any routine changing
// Angles should call ForwardKinematics AND any routine changing the transform matrix oMatrix[]
// should call InverseKinematics.
//
//
// This routine computes the complete B2W transform matrix from the current joint angles.
// Should be called whenever the joint angles are changed to keep the state consistent.
//
// See p. 25(bottom part) of O:\Components\ArmComponents\KinematicsClass\PumaFamilyDerivation.pdf
//  file in SAKinematics folder for the equations used below
////////////////////////////////////////////////////////////////////////////////////////////////////
int Kinematics::ForwardKinematics()
{
	double c[6];
	double s[6];
	double s23,c23;
	double Tmp	= 0.0;
	double Tmp1 = 0.0;
	int i = 0;

	// Precompute the trig functions to save time
	for (i = 0; i < 6; i++)
	{
		c[i] = cos(Ang[i]);
		s[i] = sin(Ang[i]);
	}	
	s23 = sin(Ang[1] + Ang[2]);										// Notice that s23 is elements 1 and 2 of Ang
	c23 = cos(Ang[1] + Ang[2]);
	

	// Position term - Fourth Column
	// Common term used to calculate both Px and Py. Look at p. 25 of Puma documentation.
	Tmp = (m_dA2 * c[1] + m_dA3 * c23 - m_dD4 * s23);						

	B2W[12] = c[0] * Tmp - m_dD3 * s[0];								// Px
	B2W[13] = s[0] * Tmp + m_dD3 * c[0];								// Py
	B2W[14] = -m_dA3 * s23 - m_dA2 * s[1] - m_dD4 * c23;						// Pz
	B2W[15] = 1.0;

	// Orientation Sub-Matrix First Column
	Tmp		= c23*(c[3]*c[4]*c[5] - s[3]*s[5]) - s23*s[4]*c[5];		// Save Time
	Tmp1	= s[3]*c[4]*c[5] + c[3]*s[5];

	B2W[0]	= c[0]*Tmp + s[0]*Tmp1;									// r11
	B2W[1]	= s[0]*Tmp - c[0]*Tmp1;									// r21
	B2W[2]	= -s23*(c[3]*c[4]*c[5] - s[3]*s[5]) - c23*s[4]*c[5];	// r31
	B2W[3]	= 0.0;													// r41

	// Orientation Sub-Matrix Second Col
	Tmp		= c23*(-c[3]*c[4]*s[5] - s[3]*c[5]) + s23*s[4]*s[5];	// Save Time
	Tmp1	= c[3]*c[5] - s[3]*c[4]*s[5];

	B2W[4]	= c[0]*Tmp + s[0]*Tmp1;									// r12
	B2W[5]	= s[0]*Tmp - c[0]*Tmp1;									// r22
	B2W[6]	= -s23*(-c[3]*c[4]*s[5] - s[3]*c[5]) + c23*s[4]*s[5];	// r32
	B2W[7]	= 0.0;													// r34

	// Orientation Sub-Matrix Third Col
	Tmp		= (c23*c[3]*s[4] + s23*c[4]);							// Save Time

	B2W[8]	= -c[0]*Tmp - s[0]*s[3]*s[4];							// r13
	B2W[9]	= -s[0]*Tmp + c[0]*s[3]*s[4];							// r23
	B2W[10] = s23 * c[3] * s[4] - c23*c[4];							// r33
	B2W[11] = 0.0;													// r43

 return KINEMATICS_OK;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// This routine computes (if possible) the Ang vector based on the current B2W transform
// matrix. Should be called whenever the matrix is changed to keep internal state consistent.
// I.e. Compute the values of Theta 1-6 based on the cartesian positions XYZ
//
// Look at slide 33 to look at the Inverse Kinematics analytical solution.
// O:\Components\ArmComponents\KinematicsClass\Inverse Kinematics - MechE 498 - O Malley.pdf
// Pages 35-54
//////////////////////////////////////////////////////////////////////////////////////////////////
int Kinematics::InverseKinematics()
{
	 int i;
	 double AngTmp[6]; 
	 double	Tmp,K,T23,Tmp2;
	 double Px2,Py2,Pz2;
	 double c1,s1,c23,s23,c4,s4,c5,s5;

	 // I thought it would be appropriate to initialize this variable, but when i do it throws off
	 // the output values. Perhaps the programs was originally tweaked to work when these values 
	 // are not initialized. 
	 // The value with which this is created, produces different values for the cos and sin...
	 // Initialize AngTem
	 // for(i=0;i<6;i++) AngTmp[i]=0.0;

	 // Speedup to remove redundant computations for Px^2, Py^2, Pz^2
	 Px2 = B2W[12]*B2W[12];	
	 Py2 = B2W[13]*B2W[13];
	 Pz2 = B2W[14]*B2W[14];

	 // Minimal sanity check
	 if ((Px2 + Py2) < (m_dD3*m_dD3)) 
	 {
		 // Beep (200,1000);
		 return SCALE_ERR;
	 }


	// Base Angle
	 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	 Tmp = sqrt(Px2 + Py2 - (m_dD3*m_dD3));										// Pick Negative - Left Handed?

	 /**** Theta 1 ****/
	 AngTmp[0] = atan2(B2W[13],B2W[12]) - atan2(m_dD3,Tmp);					// p. 43 of Inverse Kinematics.pdf
	 /**** Theta 1 ****/
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	 // Elbow Angle
	 K = (Px2 + Py2 + Pz2 - m_dA2*m_dA2 - m_dA3*m_dA3 - m_dD3*m_dD3 - m_dD4*m_dD4) / (2.0 * m_dA2);	// p. 46. (The slide is wrong in that is shows A4^2, it is in fact D4^2 as shown in this equation)	
	 if ((m_dA3*m_dA3 + m_dD4*m_dD4) < (K*K))
	 {
	//	 Beep (500,100);
	//	 Beep (500,100);
		 return SCALE_ERR;
	 }

	 Tmp = -sqrt(m_dA3*m_dA3 + m_dD4*m_dD4 - K*K);										// Pick Negative angle -> Elbow Down
	  
	 /**** Theta 3 ****/
	 AngTmp[2] = atan2(m_dA3,m_dD4) - atan2(K,Tmp);
	 /**** Theta 3 ****/

	 // If angle is > 90 degrees down (more than a full arm extension)
	 // Do a bicep curl
	 if (AngTmp[2] > (PI/2.0))												// Fix reflected solutions
		 AngTmp[2] = -2.0*PI + AngTmp[2];
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	 // Precompute
	 c1 = cos(AngTmp[0]);
	 s1	= sin(AngTmp[0]);

	 // Shoulder Angle. page 48 of Inverse Kinematics.pdf
	 Tmp = (-m_dA3 -m_dA2*cos(AngTmp[1]))*B2W[14] -								// Error!!! Fixed on Nov. 7, 2006. Juan Rojas. seems like there is an error here. According to the .pdf it should be (-A3 -A2*cos(AngTmp[**1**])). Changed from [2] to [1]
		 (cos(AngTmp[0])*B2W[12] +sin(AngTmp[0])*B2W[13])* (m_dD4 - m_dA2 * sin(AngTmp[2]));
	 Tmp2 = (m_dA2 * sin(AngTmp[2]) - m_dD4)*B2W[14] - 
		 (-m_dA3 - m_dA2*cos(AngTmp[2]))*(cos(AngTmp[0])*B2W[12] + sin(AngTmp[0])*B2W[13]);
	 T23 = atan2(Tmp,Tmp2);													// Theta2,3. p. 48

	 // Precompute
	 c23 = cos(T23);
	 s23 = sin(T23);

	 /**** Theta 2 ****/
	 AngTmp[1] = T23 - AngTmp[2];											// p. 49. I.e. (Theta2 + Theta3) - Theta3
	 /**** Theta 2 ****/

	 if (AngTmp[1] < (-PI/2.0))		// Warning - this should be under 0					// Fixup reflected solutions.
		 AngTmp[1] = 2.0*PI + AngTmp[1];

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	 // These only depend on the Angle Axis Vector XYZAA[3-5]
	 // Wrist Roll Angle
	 Tmp = -B2W[8]*s1 + B2W[9]*c1;
	 Tmp2= -B2W[8]*c1*c23 - 
			B2W[9]*s1*c23 + B2W[10]*s23;

	 // Roll Singularity. Test to check for singularity. For more look at p. 50 for an explanation on this singularity
	 // If true, keep current value
	 if ((fabs(Tmp) < 0.001) && (fabs(Tmp2) < 0.001))	
		 /**** Theta 4 ****/
		AngTmp[3] = Ang[3];	// Keep Current Value
	 else
		AngTmp[3] = atan2(Tmp,Tmp2);			// p. 50
		 /**** Theta 4 ****/

	// Check for flips, per page 53
	 if (AngTmp[3] > (PI/2.0))
		 AngTmp[3] = PI - AngTmp[3];
	 if (AngTmp[3] < (-PI/2.0))
		 AngTmp[3] = PI + AngTmp[3];

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	 // Precompute
	 c4 = cos(AngTmp[3]);
	 s4 = sin(AngTmp[3]);

	 // Wrist Pitch Angle																	// p. 51
	 Tmp = -(B2W[8]*(c1*c23*c4 + s1*s4) + B2W[9]*(s1*c23*c4 - c1*s4) - B2W[10]*(s23*c4));	// The negative sign here is correct. It was missed in the soln of the notes in the Inverse Kinematics pdf
	 Tmp2 = B2W[8]*(-c1*s23) + B2W[9]*(-s1*s23) + B2W[10]*(-c23);
	 
	 /*** Theta 5 ****/
	 AngTmp[4] = atan2(Tmp,Tmp2);
	 /**** Theta 5 ****/
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	 // Precompute
	 c5 = cos(AngTmp[4]);
	 s5 = sin(AngTmp[4]);


	// Wrist twist angle
	 Tmp = -B2W[0]*(c1*c23*s4 - s1*c4) - B2W[1]*(s1*c23*s4 + c1*c4) + B2W[2]*(s23*s4);	// p. 52
	 Tmp2 = B2W[0]*((c1*c23*c4 + s1*s4)*c5 - c1*s23*s5) + 
		B2W[1]*((s1*c23*c4 - c1*s4)*c5 - s1*s23*s5) - B2W[2]*(s23*c4*c5 + c23*s5);

	 /**** Theta 6 ****/
	 AngTmp[5] = atan2(Tmp,Tmp2);
	 /**** Theta 6 ****/

	// Check for flips, per pg. 53
	 if (AngTmp[5] > (PI/2.0))
		 AngTmp[5] = PI - AngTmp[5];
	 if (AngTmp[5] < (-PI/2.0))
		 AngTmp[5] = PI + AngTmp[5];

	 // Assign to state variables
	
	for (i = 0; i < 6; i++)
	{
/*
		if ((AngTmp[i] > (UpLimit[i]*(PI/180)))||(AngTmp[i] < (LowLimit[i]*(PI/180)))) 
	 {
	//	 Beep (900,1000);
			ret |= (0x0001 << i);				// Set joint range limit flags
	 }

*/
		Ang[i] = AngTmp[i];
	}


	return KINEMATICS_OK;;

}


/////////////////////////////////////////////////////
// Post multiplies matrix M1 by M2 /w result in M1.
/////////////////////////////////////////////////////
int Kinematics::PostMult(double M1[16],double M2[16])
{
	double Mtmp[16];		// Temp Matrix
	double Tmp;
	unsigned int i,j,k;

	for (i = 0; i < 4; i++)	//Row
	for (j = 0; j < 4; j++)	//Col
	{
		Tmp = 0.0;
		for (k = 0; k < 4; k++)
			Tmp += M1[i + 4*k] * M2[4*j + k];

		Mtmp[i + j*4] = Tmp;
	}

	for (i = 0; i < 16; i++)	//Row	
		M1[i] = Mtmp[i];

	return 0;
}


/////////////////////////////////////////////////////
// Post multiplies matrix M1 by M2 /w result in M2.
/////////////////////////////////////////////////////
int Kinematics::PreMult(double M1[16],double M2[16])
{
	double Mtmp[16];		// Temp Matrix
	double Tmp;
	unsigned int i,j,k;

	for (i = 0; i < 4; i++)	//Row
	for (j = 0; j < 4; j++)	//Col
	{
		Tmp = 0.0;
		for (k = 0; k < 4; k++)
			Tmp += M1[i + 4*k] * M2[4*j + k];

		Mtmp[i + j*4] = Tmp;
	}

	for (i = 0; i < 16; i++)	//Row	
		M2[i] = Mtmp[i];

	return 0;
}

/////////////////////////////////////////////////////////////////////
// This assumes that the transform is a Homogeneous Transform Matrix
/////////////////////////////////////////////////////////////////////
int Kinematics::InverseTransform(double M1[16])
{	
	double Tmp,TTmp[3];

	/* Transpose the rotation sub-matrix

     	| x 4 8 . |
	    | 1 x 9 . |
	    | 2 6 x . |
		| . . . . |

	*/
	Tmp = M1[1];
	M1[1] = M1[4];
	M1[4] = Tmp;

	Tmp = M1[2];
	M1[2] = M1[8];
	M1[8] = Tmp;

	Tmp = M1[6];
	M1[6] = M1[9];
	M1[9] = Tmp;

	// Rotation matrix is now transposed and ready to multiply by the translation to get the
	// new translation.

	// Express the position in terms of the elements of the rotation matrix
	// Multiply the translation vector (x,y,z) by the new transposed rotation sub-matirx
	//					x			   y			  z
	TTmp[0] = M1[0]*M1[12] + M1[4]*M1[13] + M1[8]*M1[14];
	TTmp[1] = M1[1]*M1[12] + M1[5]*M1[13] + M1[9]*M1[14];		// Look at p. A-11, eqtn A.26 in Cook's Book
	TTmp[2] = M1[2]*M1[12] + M1[6]*M1[13] + M1[10]*M1[14];

	// Reverse rotated translation vector
	M1[12] = -TTmp[0];
	M1[13] = -TTmp[1];
	M1[14] = -TTmp[2];
	

	// Make sure it's a homogeneous matrix.
	// |0|
	// |0|
	// |0|
	// |1|
	M1[3] = M1[7] = M1[11] = 0.0;
	M1[15] = 1.0;

	return 0;
}

////////////////////////////////////
// Compute wrist-to-effector matrix
////////////////////////////////////
int Kinematics::SetW2ETransform(double M[16])
{
	unsigned int i;

	// Set both forward and inverse transforms to M
	for (i = 0; i < 16; i++)
	{
		W2E[i] = M[i];				// Forward Transform Matrix
		W2EI[i] = M[i];				// Inverse Transform Matrix
	}

	// Invert the W2EI Matrix
	i = InverseTransform(W2EI);

	// Setup the position matrices from this change

	// Compute the Base-to-EndEffector by multiplying the Base-Wrist x Wrist-EndEffector
	// Temporary step. Set B2E as B2W
	for (i = 0; i < 16; i++)
		B2E[i] = B2W[i];			
	// Compute B2E
	PostMult(B2E,W2E);				

	return i;
}

/////////////////////////////////////
// Get Wrist-to-Effector 
/////////////////////////////////////
int Kinematics::GetW2ETransform(double M[16])
{
	unsigned int i;

	for (i = 0; i < 16; i++)
		M[i] = W2E[i];

	return 0;
}

/////////////////////////////////////
// Get Wrist-to-Effector Inverse
/////////////////////////////////////
int Kinematics::GetW2EI(double oM[16])
{
	unsigned int i;

	for (i = 0; i < 16; i++)
		oM[i] = W2EI[i];

	return 0;
}




