// Kinematics_Test.cpp : Defines the entry point for the console application.
//

//MODIFICATIONS BY SEAN BEGLEY 03/12/2008
//	- fixed bug with abs at the end of InverseKinematics.  abs works only for ints so anything > -1 and < 1 will
//		return 0... replaced with fabs which is designed for floating point #s
//	- moved the setting of pdPos[0-3] from Kinematics::Kinematics (in Kinematics.cpp) to Inverse Kinematics
//		to fix a bug

#include "Kinematics.h"
#include <iostream>
using namespace std;

#define NUM_AXES 6
#define	R2D	(180.0 / PI)
//------------------------------------------
// Function headers
void InverseKinematics(double*, double*, short, short);		// Desired XYZ, Actual Joint Angles, Arm, End-effector?

//------------------------------------------


int main()
{
	printf("\nThis executable contains the forward and inverse kinematics of ISAC.\n");
	printf("\nInput the desired XYZ coordinates to get the 6 joint angles for the right/left arm.\n");
	
	// Assign local variables

	// Arm and EndEffector
	short m_sLeftArm		= 0;
	short m_sEndEffector	= 0;

	// Position and Angles for Kinematics
	double pdAngles[NUM_AXES];				// size before was [NUM_AXES+1]
	double pdPos[6];
	
	for (int i=0; i<6; i++)
		pdPos[i]=0.0;

	// Get input for arm 
	printf("\nWhich arm would you like to test? \nFor Right Arm enter 0, for Left Arm enter 1: ");
	cin >> m_sLeftArm;

	// Get input for end-effector from user
	printf("\nWill you consider the end effector? \nPlease enter 0 or 1: ");
	cin >> m_sEndEffector;

	// Get XYZ values
	printf("\nPlease input the position values in cartesian coords: x, y, and z\n");
	cout << "\nX: ";
	cin >> pdPos[0];
	cout << "Y: ";
	cin >> pdPos[1];
	cout << "Z: ";
	cin >> pdPos[2];

	// Base to eyes transform: m_pdBaseXform
	// Tranform: Subtract the base-tranform from the center of the eyes to get the coords at the base of the shoulder

	//pdPos[0]-=	- 42.0;
	//pdPos[1]-=	-265.0;
	//pdPos[2]-=	-330.0;	

	// Call the inverse kinematic function for the selected arm
	// Right Arm
	if(m_sLeftArm == 0)
	{
		InverseKinematics(pdPos, pdAngles, m_sLeftArm, m_sEndEffector);
		printf("\n\nAngles for the Right arm: \n");
	}

	else
	{
		InverseKinematics(pdPos, pdAngles, m_sLeftArm, m_sEndEffector);
		printf("\n\nAngles for the Left arm\n\n");
	}
		cout.setf(0,ios::floatfield);
		cout.precision(5);
		cout << "Theta 1: " << pdAngles[0] /** R2D*/ << endl;
		cout << "Theta 2: " << pdAngles[1] /** R2D*/ << endl;
		cout << "Theta 3: " << pdAngles[2] /** R2D*/ << endl;
		cout << "Theta 4: " << pdAngles[3] /** R2D*/ << endl;
		cout << "Theta 5: " << pdAngles[4] /** R2D*/ << endl;
		cout << "Theta 6: " << pdAngles[5] /** R2D*/ << endl;

	cin.ignore(256,'\n');
	cout << "\nPress enter to EXIT..." << endl;
	cin.get();

	return 0;
}

void InverseKinematics(double * pdPos, double * pdAngles, short m_sLeftArm, short m_sEndEffector)
{
	int i;
	double		M[16];
	Kinematics	*m_pKMArm;

	//for (i=0;i<16;i++)
	//	M[i]=0.0;

	// Create Arm Class
	m_pKMArm = new Kinematics(m_sLeftArm, m_sEndEffector);							
	//m_pKMArm->m_sRightHand = m_sLeftArm;							// Tells which side end-effector information we will use

	// Tranform: Subtract the base-tranform from the center of the eyes to get the coords at the base of the shoulder
	pdPos[0]-=m_pKMArm->m_pdBaseXform[0];
	pdPos[1]-=m_pKMArm->m_pdBaseXform[1];
	pdPos[2]-=m_pKMArm->m_pdBaseXform[2];
	
	// Initialization calls necessary to get parameters right
	m_pKMArm->SetRPYMatrix(m_pKMArm->m_pdEndEffXform,M);			// Build W2E Transformation
	m_pKMArm->SetW2ETransform(M);

	// Call that actually computes the inverse kinematics and returns the angles
	// Give it the XYZ to compute the new position
	m_pKMArm->SetXYZRPY(pdPos);		
	// Get the angles of the new position
	m_pKMArm->GetAngles(pdAngles);	

	for (i=0;i<6;i++)
		if(fabs(pdAngles[i]) < 0.0001)
			pdAngles[i] = 0.0000;
}