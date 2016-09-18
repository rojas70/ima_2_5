// SAKinematics.cpp
//	This file is the implementation of the softarm kinematics class.
//
// Robert Todd Pack
// Fall 1996
// 
// Last Update
// Juan Rojas
// Spring 2009

#include	"O:\Components\ArmComponents\IMA2_ArmTools\StdAfx.h"
#include	"SAKinematics.h"

// #define
#define NUM_AXES 6
/////////////////////////////////////////////////////////////////////////////////

// Constructor
CSAKinematics::CSAKinematics(short LeftHanded)
{
	unsigned int i,j = 0;

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
		
	// Alpha's are described in ::GetAxisT(UINT,double)
	*/

	// Assign Kinematic Parameters based on whether we are working with the Right or Left Arm.

	/** DH PARAMETERS **/
	// Left Arm
	if (LeftHanded == 1)
	{		
		A2 = LEFT_A2;	// Link length for the Bicep.
		A3 = LEFT_A3;	// Height difference between joint in shoulder and joint in elbow. 
		D3 = LEFT_D3;	// Link Offset between shoulder and elbow.
		D4 = LEFT_D4;	// Link length of forearm
	}
	// Right Arm
	if(LeftHanded == 0)
	{
		A2 = RIGHT_A2;
		A3 = RIGHT_A3;
		D3 = RIGHT_D3;
		D4 = RIGHT_D4;
	}	

	/** THETAs -- Joint Angles**/
	// These angles are designed to have ISAC's arm form a _| shape. (radians)
	Ang[0] = THETA0;		// 0	degrees
	Ang[1] = THETA1;		// 90	degrees
	Ang[2] = THETA2;		//-180	degrees
	Ang[3] = THETA3;		// 0	degrees
	Ang[4] = THETA4;		// 90	degrees
	Ang[5] = THETA5;		// 180	degrees

	/** LIMITS **/
	// Establish upper and lower limits in radians
	for (j=0;j<6;j++)
	{
		LowLimit[j] = -250.0;
		UpLimit[j] = 250.0;
		AngStat[j] = ANGLE_OK;		// Angle status
	}

	/*****************************************************************************/
	// Initialize B2W (base-to-wrist) from angles
	// First go through, the FKin matrix without any transforms should look like:
	/*
	/* T0_6 = 
	/* | 0   0   1   334 |
	/* | 0  -1   0  -200 |
	/* | 1   0   0  -320 |
	/* | 0   0   0     1 |
	/*
	/* These numbers reflect adequately the direction of the wrist at ISAC's home position.
	/*****************************************************************************/
	ForwardKinematics();

	// Initialize W2E (wrist-to-effector) and W2EInverse and Identity matrices.
	// Creates a diagonal identity matrix.
	for (i=0;i<4; i++)	
		for (j=0;j<4;j++)
		{
			// Create a diagonal of 1's.
			if (i==j)	
			{
				 W2E[i+4*j]	= 1.0;
				 W2EI[i+4*j]= 1.0;
			}

			// Zero out offsets
			else
			{ 
				W2E[i+4*j]  = 0.0;
				W2EI[i+4*j] = 0.0;
			}
		}

	// Initialize B2E. 
	// B2E is equal to B2W because W2E is I
	// B2E = B2W * W2E = B2W * I = B2W
	// B2W was created in the Initialization Routine
	for (i = 0; i < 16; i++)
		B2E[i] = B2W[i];	

}


CSAKinematics::~CSAKinematics() {}

////////////////////////////////
// Get the Angle Axis outputs.
////////////////////////////////
int	CSAKinematics::GetXYZAA(double XYZAA[7])
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
int CSAKinematics::SetXYZAA(double XYZAA[7]) // Uses Inv Kinematics & Fwd Kinematics
{
	double TMat[16];			// Transform matrix
	double ct,st,vt;
	double Tmp;
	int i;

	// Insurance for Angle-Axis:
	Tmp = 0.0;
	for (i = 3; i < 6; i++)
		Tmp += XYZAA[i]*XYZAA[i];

	if (Tmp < 0.0001) return FALSE;		// Too close to a zero vector so angles don't change.
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

/*******************************************************************************
/* GetXYZRPY(16 Element Homogeneous Transform Matrix, 6 element XYZRPY vector)
/* 
/* This function is called by CKinematicModel::ForwardKinematics()
/* This function calls GetXYZRPYMat() and returns a six element vector.
/*******************************************************************************/
int	CSAKinematics::GetXYZRPY(double XYZRPY[6])
{
	return GetXYZRPYMat(B2E,XYZRPY);
}


/**************************************************************************************
/* GetXYZRPYMat(Homogeneous Tranform Matrix, 6 element Cartesian Vector)
/* 
/* This function is called by: CKinematicModel::ForwardKinematics()
/* At this point the forward kinematics have been computed, including a Base-to-wrist Transform.
/* 
/* The purpose of this function is to:
/* (1) Compute the RPY values from the 3x3 roation matrix
/* in the homogenous transform, and to copy the cartesian coordinates from the 3x1 vector 
/* in the homogeneous tranform, and
/*
/* (2) To convert RPY values from radians to degrees, to be used
/* with ISAC's new servo valve controller in IMA.
/**************************************************************************************/
int CSAKinematics::GetXYZRPYMat(double M[16],double XYZRPY[6])
{
	// Local variables
	int		 i;	
	double  cb;			// Cosine beta.

	// Copy X, Y, and Z, from the homogeneous matrix to the Cartesian vector.
	 XYZRPY[0] = M[12];		// X
	 XYZRPY[1] = M[13];		// Y
	 XYZRPY[2] = M[14];		// Z

	 // Compute the roll, pitch, and yaw angles from 3x3 rotation matrix.
	 // For more, see Robot Simulation by Dr. Cook page A-12,13; or any kinematics text.

	 // Pitch
	 XYZRPY[4] = atan2(-M[2],sqrt(M[0]*M[0] + M[1]*M[1]));	// Beta = atan2(-r31, sqrt(r11^2 + r21^2))

	 // Compute the cosine of the pitch, beta.
	 cb = cos(XYZRPY[4]);									

	 // Roll and Yaw
	 // Singularity
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

	 // Convert values back to degrees
	 for(i=3; i<NUM_AXES;i++)
		XYZRPY[i] = XYZRPY[i]*R2D;

	 return KINEMATICS_OK;
}

/******************************************************************
/* SetXYZRPY(XYZRPY)
/* 
/* This function is called from CKinematicModel::InverseKinematics()
/* and is the first in a series of calls. 
/* 
/* 1) Computes the 16 element homogeneous transform
/* 2) Create a local copy of a Base-to-End Effector transform
/* 3) Use a post multiply to get a Base-to-Wrist transform
/* 4) Call the inverse kinematics and store the result in Ang[] in degrees
/******************************************************************/
int	CSAKinematics::SetXYZRPY(/*[in]*/double XYZRPY[6])
{
	// Computes the 16 element homogenesou transform, including the 3x3 rotation matrix and the 3x1 position vector
	SetRPYMatrix(/*[in]*/XYZRPY, /*[out]*/B2E);		

	// 1) Calls inverse kinematics for the first time. Stores results in private member variable Ang[].
	// 2) Also creates/sets a B2E transform. (Really want B2W)
	SetT(B2E);						// At this point the B2E == B2W

	// Obtain Base-to-wrist transform by subtrating the effects of the end-effector
	PostMult(B2W,W2EI);				// Invert the wrist to effector transformation, ie the transform is a end-effector-to-wrist

	// Now call inverse kinematics.
	return InverseKinematics();		// find joint angles according to new B2W
}

/*******************************************************************
* SetRPYMatrix()
*
* In deriving the inverse kinematics, we need to obtain the values
* for the rotation matrix R06. This is our goal. To generate these
* values we convert given RPY values into the Rotation matrix.
* 
* Takes command vector in the form of: X Y Z  Rot X Rot Y  Rot Z
* Where the rotations are about the fixed base frame axes.
*******************************************************************/
int CSAKinematics::SetRPYMatrix(/*[in]*/double RPY[6], /*[out]*/double oM[16])
{
	double ca,cb,cg;		// Cosine arguments
	double sa,sb,sg;		// Sine arguments

	// Precompute Trig Functions to save on evaluations
	ca = cos(RPY[5]); sa = sin(RPY[5]);
	cb = cos(RPY[4]); sb = sin(RPY[4]);
	cg = cos(RPY[3]); sg = sin(RPY[3]);

	/* The following procedure is standard in converting roll-pitch-yaw angles into a 3x3 rotation matrix.
	 * You can look at Equation 2.38 of the Robot Modeling and Control by Spong et al book.
	 * Do a roll about x, a pitch about y, and a yaw about z.
	 * Since the rotations take place about a fixed frame, R is defined as follows:
	 * 
	 *   R = Rz(alpha)Ry(Beta)Rx(gamma) = 
	 *	 | ca -sa 0 || cB  0 sB || 1  0 0  |		| r11 r12 r13  Px|
	 *	 | sa ca  0 || 0   1  0 || 0 cy -sy| = oM = | r21 r22 r23  Py|	// See Robot Simulation by Dr. Cook page A-12
	 *   | 0   0  1 ||-sB  0 cB || 0 sy cy |		| r31 r32 r33  Pz|
	 * 												|   0   0   0   1|
	 */

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

/*****************************************************************************
/* GetAngles(output joint angles) -- IK
/* 
/* This function is called from CKinematicModel::InverseKinematics()
/* The previous function called before this one was: CSAKinematics::SetXYZRPY(XYZRPY);
/*
/* Retrieves the computed inverse kinematic joint angles.
/****************************************************************************/
int	CSAKinematics::GetAngles(/*[out]*/ double oAng[6])
{
	int i;

	for (i = 0; i < 6 ; i++)
		oAng[i] = Ang[i];

	return KINEMATICS_OK;
}

/****************************************************************************
/* SetAngles(Ang[6])  -- FK
/* 
/* This function is called by CKinematicModel::ForwardKinematics()
/* This function also calls CSAKinematics::ForwardKinematics()
/*
/* This function performs four routines:
/* 1) Set six elements of the joint angles to private member variable Ang[].
/* 2) Call the forward kinematics function.
/* 3) Save the results in the B2E matrix.
/* 4) Compute the wrist to end-effector transform.
****************************************************************************/
int	CSAKinematics::SetAngles(double iAng[6])
{
	// Local variables
	int i,j;

	for (i = 0; i < 6 ; i++)
	{
		// Check angle limits for all joints
		if (iAng[i] > UpLimit[i])
			AngStat[i] = ANGLE_ABOVE;
		else if (iAng[i] < LowLimit[i])
			AngStat[i] = ANGLE_BELOW;
		else 
			AngStat[i] = ANGLE_OK;

		// Set angles
		Ang[i] = iAng[i];
	}

	// Call method to compute forward kinematics.
	// Result is a homogeneous transform -> 16 element matrix.
	// It containts a 3x3 rotation matrix and a 3x1 translation matrix. 
	i =  ForwardKinematics();		// Saves result in local matrix B2W

	// Copies the saved results in the Base-to-End-Effector variable.
	for (j = 0; j < 16; j++)
		B2E[j] = B2W[j];			

	// If using a gripper, update the B2E matrix by including the transform from the wrist to the end-effector.
	PostMult(B2E,W2E);				

	return i;

}

////////////////////////////////
// Get Base-to-effector matrix
// Copy B2E to 4x4 matrix
/////////////////////////////////
int CSAKinematics::GetB2E(double oMatrix[16])
{
	int i;
	for (i = 0; i< 16;i++)
	 oMatrix[i] = B2E[i];

	return KINEMATICS_OK;

}


int	CSAKinematics::GetT(double oMatrix[16])	// Uses Fwd Kinematics
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
int CSAKinematics::GetAxisT(unsigned int i, double oMatrix[16])
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
				TA = A2;
				TD = D3;
				break;
			// Joint 4
			case 3:
				TL = - PI/2.0;		// - 90 degrees
				TA = A3;
				TD = D4;
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
int	CSAKinematics::GetJacobian(double oMatrix[16])
{
	return FALSE;
}

/**********************************************************************************************/
// SetT(/*[in]*/Homogeneous Transform Matrix)
/*
/* This function is called from: CSAKinematics::SetXYZRPY()
/* The function previously called before this one is: CSAKinematics::SetXYZRPYMatrix()
/*
/* This functions performs two tasks:
/* 1) Calls the CSAKinematicModel::InverseKinematics() method and stores the results in
/* 2) Computed a Base-to-Wrist transform:
/* Set up the Base-to-End Effector Matrix, then post-multiply by the Wrist-to-Effector Matrix
/**********************************************************************************************/
int	CSAKinematics::SetT(/*[in]*/double iMatrix[16])
{ 
	int i;
	int ret;

	// Copy values from matrix that only contains the data for the 3x3 rotation matrix.
	for (i = 0; i < 16; i++)
		B2W[i] = iMatrix[i];

	// Call inverse kinematics.
	// The InverseKinematics call operates on the B2W matrix.
	ret = InverseKinematics();


	// Set up the Base-to-Effector Matrix
	// First get the Base-to-Wrist Matrix, then post-multiply by the Wrist-to-Effector Matrix
	// To get the Base-to-Effector Matrix
	for (i = 0; i < 16; i++)
		B2E[i] = B2W[i];			// Copy in the new B2W

	PostMult(B2E,W2E);				// Add in the W2E transformation.

	return ret;
}

/////////////////////////
// Set the DH parameters
/////////////////////////
int	CSAKinematics::SetParameters(double iD3,double iD4, double iA2, double iA3)
{
	D3 = iD3;
	D4 = iD4;
	A2 = iA2;
	A3 = iA3;

	return ForwardKinematics();	// Recompute the transform based on new parameters
}


///////////////////////////
// Get the DH parameters
///////////////////////////
int	CSAKinematics::GetParameters(double &oD3,double &oD4,double &oA2,double &oA3)
{
	oD3 = D3;
	oD4 = D4;
	oA2 = A2;
	oA3 = A3;

	return KINEMATICS_OK;
}

/***********************************************************************************************************
/* CSAKinematics::ForwardKinematics()
/* Works in sync with the following methods: 
/* CKinematicModel::SetAngles()
/* CKinematicModel::ForwardKinematics()
/*
/* The following routines conspire to keep the angle-vector Ang[] and the base to wrist
/* transformation matrix B2W in SYNC and consistent at ALL times. Any routine changing
/* angles should call ForwardKinematics AND any routine changing the transform matrix oMatrix[]
/* should call InverseKinematics.
/*
/* This routine computes the complete B2W transform matrix from the current joint angles (in degrees).
/* Should be called whenever the joint angles are changed to keep the state consistent.
/*
/* The forward kinematic equations were copied from a standard text following the Puma derivation. 
/* Hence they were not derived. Although we noted Alpha angles in the constructors they are not used.
/*
/* See p. 25(bottom part) of O:\Components\ArmComponents\KinematicsClass\PumaFamilyDerivation.pdf
/* file in SAKinematics folder for the equations used below
/**************************************************************************************************************/
int CSAKinematics::ForwardKinematics()
{
	// Local variables
	double c[6];		// Cosine
	double s[6];		// Sine
	double s23,c23;		// (Theta2 + Theta3)
	double Tmp;			// Temps
	double Tmp1;	
	int i;

	// Precompute the trig functions to save time: 
	// (a) Convert from degrees to radians, and 
	// (b) save in c[] and s[] forms
	for (i = 0; i < 6; i++)
	{
		c[i] = cos(Ang[i]*D2R);
		s[i] = sin(Ang[i]*D2R);
	}	

	s23 = sin(Ang[1]*D2R + Ang[2]*D2R);										// Notice that s23 is elements 1 and 2 of Ang
	c23 = cos(Ang[1]*D2R + Ang[2]*D2R);
	

	// Position term - Fourth Column
	// Common term used to calculate both Px and Py. Look at p. 25 of Puma documentation.
	Tmp = (A2 * c[1] + A3 * c23 - D4 * s23);						

	B2W[12] = c[0] * Tmp - D3 * s[0];								// Px
	B2W[13] = s[0] * Tmp + D3 * c[0];								// Py
	B2W[14] = -A3 * s23 - A2 * s[1] - D4 * c23;						// Pz
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
// Look at slide 53 to look at the Inverse Kinematics analytical solution.
// O:\Components\ArmComponents\KinematicsClass\Docuemantation\Inverse Kinematics - MechE 498 - O Malley.pdf
// Pages 35-54
//////////////////////////////////////////////////////////////////////////////////////////////////
int CSAKinematics::InverseKinematics()
{
	 int i;
	 double AngTmp[6]; 
	 double	Tmp,K,T23,Tmp2;
	 double Px2,Py2,Pz2;
	 double c1,s1,c23,s23,c4,s4,c5,s5;

	 // Speedup to remove redundant computations for Px^2, Py^2, Pz^2
	 Px2 = B2W[12]*B2W[12];	
	 Py2 = B2W[13]*B2W[13];
	 Pz2 = B2W[14]*B2W[14];

	 // Minimal sanity check
	 if ((Px2 + Py2) < (D3*D3)) 
	 {
		 // Beep (200,1000);
		 return SCALE_ERR;
	 }


	// Base Angle
	 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	 Tmp = sqrt(Px2 + Py2 - (D3*D3));										// Pick Negative - Left Handed?

	 /**** Theta 1 ****/
	 AngTmp[0] = atan2(B2W[13],B2W[12]) - atan2(D3,Tmp);					// p. 43 of Inverse Kinematics.pdf
	 /**** Theta 1 ****/
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	 // Elbow Angle
	 K = (Px2 + Py2 + Pz2 - A2*A2 - A3*A3 - D3*D3 - D4*D4) / (2.0 * A2);	// p. 46. (The slide is wrong in that is shows A4^2, it is in fact D4^2 as shown in this equation)	
	 if ((A3*A3 + D4*D4) < (K*K))
	 {
	//	 Beep (500,100);
	//	 Beep (500,100);
		 return SCALE_ERR;
	 }

	 Tmp = -sqrt(A3*A3 + D4*D4 - K*K);										// Pick Negative angle -> Elbow Down
	  
	 /**** Theta 3 ****/
	 AngTmp[2] = atan2(A3,D4) - atan2(K,Tmp);
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
	 // The equation for temp in the slide is wrong. This can be verified if compared with Craig's book.
	 // In the first bracket, the cosing should be a function of theta3 not theta2. Theta2 is not defined and
	 // cannot be used!
	 Tmp = (-A3 -A2*cos(AngTmp[2]))*B2W[14] -								
		 (cos(AngTmp[0])*B2W[12] +sin(AngTmp[0])*B2W[13])* (D4 - A2 * sin(AngTmp[2]));
	 Tmp2 = (A2 * sin(AngTmp[2]) - D4)*B2W[14] - 
		 (-A3 - A2*cos(AngTmp[2]))*(cos(AngTmp[0])*B2W[12] + sin(AngTmp[0])*B2W[13]);
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
	 // Wrist angles
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

	// Convert angles from radians to degrees
	for(i=0; i<NUM_AXES;i++)
		Ang[i] = Ang[i] * R2D;


	return KINEMATICS_OK;;

}


/////////////////////////////////////////////////////
// Post multiplies matrix M1 by M2 /w result in M1.
/////////////////////////////////////////////////////
int CSAKinematics::PostMult(/*[in],[out]*/double M1[16], /*[in]*/double M2[16])
{
	// Local variables
	double Mtmp[16];		// Temp Matrix
	double Tmp;
	unsigned int i,j,k;

	// Traverse the matrices performing the appropriate row-col multiplications
	for(i=0;i<4;i++)	//Row
	{
		for(j=0;j<4;j++)	//Col
		{
			Tmp = 0.0;

			for (k=0;k<4;k++)
				Tmp += M1[i + 4*k] * M2[4*j + k];

			Mtmp[i + j*4] = Tmp;
		}
	}

	for (i = 0; i < 16; i++)	//Row	
		M1[i] = Mtmp[i];

	return 0;
}


/////////////////////////////////////////////////////
// Post multiplies matrix M1 by M2 /w result in M2.
/////////////////////////////////////////////////////
int CSAKinematics::PreMult(double M1[16],double M2[16])
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
int CSAKinematics::InverseTransform(double M1[16])
{	
	double Tmp,TTmp[3];

	/* Transpose the rotation sub-matrix

     	| x 1 2   3 |
	    | 4 x 6   7 |
	    | 8 9 x   11|
		|           |
		| . . . .   |

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

	// Multiply the translation vector (x,y,z) by the new transposed rotation sub-matirx
	//					x			   y			  z
	TTmp[0] = M1[0]*M1[12] + M1[4]*M1[13] + M1[8]*M1[14];
	TTmp[1] = M1[1]*M1[12] + M1[5]*M1[13] + M1[9]*M1[14];
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
int CSAKinematics::SetW2ETransform(double M[16])
{
	unsigned int i;

	// Set both forward and inverse transforms to M
	for (i = 0; i < 16; i++)
	{
		W2E[i] = M[i];				// Forward Transform Matrix
		W2EI[i] = M[i];				// Inverse Transform Matrix
	}

	// Create the inverted matrix.
	i = InverseTransform(W2EI);

	// Setup the position matrices from this change

	// Set up B2E according to the new W2E
	for (i = 0; i < 16; i++)
		B2E[i] = B2W[i];			// Copy in the B2W

	PostMult(B2E,W2E);				// Add in the W2E transformation.

	return i;
}

/////////////////////////////////////
// Get Wrist-to-Effector 
/////////////////////////////////////
int CSAKinematics::GetW2ETransform(double M[16])
{
	unsigned int i;

	for (i = 0; i < 16; i++)
		M[i] = W2E[i];

	return 0;
}

/////////////////////////////////////
// Get Wrist-to-Effector Inverse
/////////////////////////////////////
int CSAKinematics::GetW2EI(double oM[16])
{
	unsigned int i;

	for (i = 0; i < 16; i++)
		oM[i] = W2EI[i];

	return 0;
}

/*
int CSAKinematics::HelpMateInverseKM()
{
 double AngTmp[6]; 
 double	Tmp,K,T23,Tmp2;
 double Px2,Py2,Pz2;
 double c1,s1,c3,s3,c23,s23,c4,s4;
 int i,ret;

 Px2 = B2W[12]*B2W[12];	// Speedup to remove redundant computations
 Py2 = B2W[13]*B2W[13];
 Pz2 = B2W[14]*B2W[14];

 // Minimal sanity check
 if ((Px2 + Py2) < (D3*D3)) 
 {
//	 Beep (200,1000);
	 return SCALE_ERR;
 }


// Base Angle
 Tmp = sqrt(Px2 + Py2 - (D3*D3));							// Pick Neg - Left Handed?
 AngTmp[0] = atan2(B2W[13],B2W[12]) - atan2(D3,Tmp);


 // Elbow Angle
 K = (Px2 + Py2 + Pz2 - A2*A2 - A3*A3 - D3*D3 - D4*D4) / (2.0 * A2);
 if ((A3*A3 + D4*D4) < (K*K))
 {
//	 Beep (500,100);
//	 Beep (500,100);
	 return SCALE_ERR;
 }

 Tmp = -sqrt(A3*A3 + D4*D4 - K*K);						// Pick Neg - Elbow Down

 AngTmp[2] = atan2(A3,D4) - atan2(K,Tmp);

 if (AngTmp[2] > (PI/2.0))									// Fix reflected solutions
	 AngTmp[2] = -2.0*PI + AngTmp[2];

 // Precompute
 c1 = cos(AngTmp[0]);
 s1	= sin(AngTmp[0]);
 c3 = cos(AngTmp[2]);
 s3	= sin(AngTmp[2]);

 // Shoulder Angle
 Tmp = (-A3 -A2*c3)*B2W[14] - (c1*B2W[12] +s1*B2W[13])* (D4 - A2 * s3);
 Tmp2 = (A2*s3 - D4)*B2W[14] - (-A3 - A2*c3)*(c1*B2W[12] + s1*B2W[13]);
 T23 = atan2(Tmp,Tmp2);

 // Precompute
 c23 = cos(T23);
 s23 = sin(T23);

 AngTmp[1] = T23 - AngTmp[2];

 if (AngTmp[1] < (-PI/2.0))							// Fixup reflected solutions.
	 AngTmp[1] = 2.0*PI + AngTmp[1];


 // Wrist Roll Angle
 Tmp = c23*(c1*B2W[8] + B2W[9]*s1)-s23*B2W[10];
 Tmp2= c1*B2W[9] - B2W[8]*s1;

 AngTmp[3] = atan2(Tmp,Tmp2);

// Check for flips
 if (AngTmp[3] > (PI/2.0))
	 AngTmp[3] = PI - AngTmp[3];
 if (AngTmp[3] < (-PI/2.0))
	 AngTmp[3] = PI + AngTmp[3];

 s4 = sin(AngTmp[3]);
 c4 = cos(AngTmp[3]);


 // Wrist Pitch Angle
 Tmp = -s23*(c1*B2W[0] + s1*B2W[1])-c23*B2W[2];
 Tmp2 = (c1*c23*c4+s1*s4)*B2W[0]+(c23*c4*s1-c1*s4)*B2W[1]-c4*s23*B2W[2];
 AngTmp[4] = atan2(Tmp,Tmp2);

 AngTmp[5] = 0.0;

 // Assign to state variables
 ret = KINEMATICS_OK;
 for (i = 0; i < 6; i++)
 {
	if ((AngTmp[i] > UpLimit[i])||(AngTmp[i] < LowLimit[i])) 
	{
//	 Beep (900,1000);
		ret |= (0x0001 << i);				// Set joint range limit flags
	}

	Ang[i] = AngTmp[i];
}

/*
 Ang[0]=B2W[2];
 Ang[1]=B2W[4];
 Ang[2]=B2W[9];
 Ang[3]=B2W[12];
 Ang[4]=B2W[13];
 Ang[5]=B2W[14];
*/
// Xuan----
//	ForwardKinematics();

//	return ret;
// --------

// return ForwardKinematics();
//}


