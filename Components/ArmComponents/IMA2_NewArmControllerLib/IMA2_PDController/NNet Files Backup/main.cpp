#include "Headers\stdafx.h"
#include <windows.h>
#include <windef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <stdarg.h>
#include <math.h>
#include <IOSTREAM>
#include <sstream>
#include "Headers\winmotenc.h"
#include "Headers\Control.h"
#include "Headers\NNMuscleClass.h"
#include "Headers\MahirKinematics.h"
#include "Headers\PID.h"
#include "Headers\commport.h"
#include "Headers\GripControl.h"

using namespace std;

#define npoints		5			// trajectory points
#define NUM_AXES	6							
#define NUMBER_OF_STEPS 50		// Number of steps to run the P-controller. Might not be needed, since we can call this ALWAYS in IMA.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Function Declarations
// Perform Left and Right Homing Position
void LeftNeuralNetController();
void RightNeuralNetController();

// Initialize P-controllers
void LeftPID();
void RightPID();

// Function used by Erdem to get desired points from camera's.
void GetPoints(int *,int *);

// Variable Declarations

// Valves
double	m_dInitialleftValvesOutputs[12];				// around the home position
double	m_dleftValvesOutputs[12]			= {0};				// in voltage
double	m_dleftValvesInputs[12]				= {0};				// in voltage

double	m_dInitialrightValvesOutputs[12];
double	m_drightValvesOutputs[12]			= {0};
double	m_drightValvesInputs[12]			= {0};

// Angles
double	m_dleftAngles[6]					= {0};				// Joint Angle values
float	m_fDesiredLeftAngle[6]				= {0.0};
float	m_fprevThetasL[6]					= {0.0};

double	m_drightAngles[6]					= {0};
float	m_fDesiredRightAngle[6]				= {0.0};
float	m_fprevThetasR[6]					= {0.0};

double m_dAngleError[NUM_AXES]				= {0.0};

// Encoders
long	m_dleftEncoders[6]					= {0};				// Encoder values
long	m_drightEncoders[6]					= {0};

// Trajectories
float	m_fDesiredLeftTrajectory[npoints][6] = {0};
float	m_fDesiredRightTrajectory[npoints][6]= {0};

// PID
double	*m_dLP_Output						= NULL;
double	*m_dRP_Output						= NULL;

double m_dLeftPValue[6]						= {0.00045, 0.00065, 0.00075,  0.0015, 0.00075, 0.0015 };
double m_dRightPValue[6]					= {0.00045, 0.00065, 0.00075, -0.0015, 0.00075, 0.0015 };

// Error
double m_dLeftAngleError[NUM_AXES]			= {0};
double m_dRightAngleError[NUM_AXES]			= {0};

// Step variables (milliseconds)
short	m_sTotalStep						= 50;
short	m_sSampleTime						= 60;

/*************************************************************************
* Object Creation
* The next statetements create NNMuscles type objects for both the right 
* and left arms, for both the forward and backward motions, and for each
* of the Joint Angles
*************************************************************************/
// Left Muscles
CNNMuscles LeftNNMusclesAngle0F(1,0,1);CNNMuscles LeftNNMusclesAngle0B(1,0,-1);
CNNMuscles LeftNNMusclesAngle1F(1,1,1);CNNMuscles LeftNNMusclesAngle1B(1,1,-1);
CNNMuscles LeftNNMusclesAngle2F(1,2,1);CNNMuscles LeftNNMusclesAngle2B(1,2,-1);
CNNMuscles LeftNNMusclesAngle3F(1,3,1);CNNMuscles LeftNNMusclesAngle3B(1,3,-1);
CNNMuscles LeftNNMusclesAngle4F(1,4,1);CNNMuscles LeftNNMusclesAngle4B(1,4,-1);
CNNMuscles LeftNNMusclesAngle5F(1,5,1);CNNMuscles LeftNNMusclesAngle5B(1,5,-1);

// Right Muscles
CNNMuscles RightNNMusclesAngle0F(0,0,1);CNNMuscles RightNNMusclesAngle0B(0,0,-1);
CNNMuscles RightNNMusclesAngle1F(0,1,1);CNNMuscles RightNNMusclesAngle1B(0,1,-1);
CNNMuscles RightNNMusclesAngle2F(0,2,1);CNNMuscles RightNNMusclesAngle2B(0,2,-1);
CNNMuscles RightNNMusclesAngle3F(0,3,1);CNNMuscles RightNNMusclesAngle3B(0,3,-1);
CNNMuscles RightNNMusclesAngle4F(0,4,1);CNNMuscles RightNNMusclesAngle4B(0,4,-1);
CNNMuscles RightNNMusclesAngle5F(0,5,1);CNNMuscles RightNNMusclesAngle5B(0,5,-1);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Main function
void main()
{
	// Flags. Activate computations.
	bool m_bWhatArm = 0;			// 0 = Right, 1 = Left
	int count=1,i;

	/*** Allocate Neural Network files. ***/
	// Associate Files to left/right arms, forward and backward motions, for each joint angle. 

	// Left Arm Objects
	if (m_bWhatArm == 1)
	{
		LeftNNMusclesAngle0F.Allocator();LeftNNMusclesAngle0B.Allocator();
		LeftNNMusclesAngle1F.Allocator();LeftNNMusclesAngle1B.Allocator();
		LeftNNMusclesAngle2F.Allocator();LeftNNMusclesAngle2B.Allocator();
		LeftNNMusclesAngle3F.Allocator();LeftNNMusclesAngle3B.Allocator();
		LeftNNMusclesAngle4F.Allocator();LeftNNMusclesAngle4B.Allocator();
		LeftNNMusclesAngle5F.Allocator();LeftNNMusclesAngle5B.Allocator();
	}
	else		// Right Arm Objects
	{	
		RightNNMusclesAngle0F.Allocator();RightNNMusclesAngle0B.Allocator();
		RightNNMusclesAngle1F.Allocator();RightNNMusclesAngle1B.Allocator();
		RightNNMusclesAngle2F.Allocator();RightNNMusclesAngle2B.Allocator();
		RightNNMusclesAngle3F.Allocator();RightNNMusclesAngle3B.Allocator();
		RightNNMusclesAngle4F.Allocator();RightNNMusclesAngle4B.Allocator();
		RightNNMusclesAngle5F.Allocator();RightNNMusclesAngle5B.Allocator();
	}

	/*** Initialization Calls ***/
	// Initialize Cards.
	InitializeCards();

	// Initialize Valves = Homing Routines
	if (m_bWhatArm == 1)
		InitializeLeftValves();
	else
		InitializeRightValves();	
	Sleep(500);

	// Reset Encoders
	// This is a crucial step. It is used so that the ENCODERS are reset every time before we use the arm.
	// When power is given to an encoder, it marks the current position as it's ZERO position. 
	// We have to try to find a way to have a consistent starting position. We do this after moving the
	// arms to the home position.
	// Resetting encoders at the beginning however, does not guarantee an exact home position. 
	// But this is what we are working with at this time.
	if (m_bWhatArm == 1)  
	{
		ResetLeftEncoders();
		ReadLeftEncoders();
		leftLogicalAngles();
	}
	else 
	{
		ResetRightEncoders();
		ReadRightEncoders();
		rightLogicalAngles();
	}



	// Control Loop

	// Assign theta's to previous Angles
	if (m_bWhatArm == 1)
		for(i=1;i<=6;i++)
			m_fprevThetasL[i] = m_dleftAngles[i];
	else
		for(i=1;i<=6;i++)
			m_fprevThetasR[i] = m_drightAngles[i];

	// Get Desired Angles
	// IVectorSignal *pIVSDesAng;
	// Get pointer to m_pIUnkDesiredAngles 
	/* m_Bindings->get_Pointers(SysAllocString(L"DesiredAngles"),&m_pIUnkDesiredAngles);
	if(m_pIUnkDesiredAngles == NULL)	return E_POINTER;
	m_pIUnkDesiredAngles->QueryInterface(IID_IVectorSignal,(void**)&pIVSDesAng);
	if (pIVSDesAng != NULL)
	{
		mysa = SafeArrayCreateVector(VT_R8,0,m_Axes);
		pIVSDesAng->GetCurrentVector(mysa);		// Current sample
		memcpy(m_fDesiredLeftAngle,mysa->pvData,sizeof(double)*m_Axes); 
*/
	//m_fDesiredLeftAngle[j];			// Used for P-control computation
	//m_fDesiredRightAngle[j];
	
	// Call NN/P Controller
	// Left
	if (m_bWhatArm == 1)
	{
		LeftNeuralNetController();
		LeftPID();
		Sleep(500);
	}
	// Right
	else
	{
		RightNeuralNetController();
		RightPID(); 
		Sleep(500);
	} 

				
	// Closing the Controls
	CloseValves();
	Sleep(500);
	vitalQuit();
	Sleep(500);
}

/*****************************************************************************************************************************************/


void LeftPID()
{
	// PID Output variables
	int count = 20;

	while(count<NUMBER_OF_STEPS)
	{
		// Read Encoders and compute logical angles. 
		ReadLeftEncoders();leftLogicalAngles();

		//for (int i=0; i<NUM_AXES; i++)
		*m_dLP_Output/*[i]*/ = leftPID(/*&m_fDesiredLeftAngle[i]*/);
		
		// As each joint works through opposing muscles, one 
		// muscle inflates and the other deflates.
		// Physical inspection is necessary to understand the order.
		m_dleftValvesOutputs[0] = m_dleftValvesOutputs[0]-m_dLP_Output[0];
		m_dleftValvesOutputs[1] = m_dleftValvesOutputs[1]+m_dLP_Output[0];
			
		m_dleftValvesOutputs[2] = m_dleftValvesOutputs[2]+m_dLP_Output[1];
		m_dleftValvesOutputs[3] = m_dleftValvesOutputs[3]-m_dLP_Output[1];

		// Bicep vertical motion
		m_dleftValvesOutputs[4] = m_dleftValvesOutputs[4]+m_dLP_Output[2];
		m_dleftValvesOutputs[5] = m_dleftValvesOutputs[5]-m_dLP_Output[2];
		m_dleftValvesOutputs[6] = m_dleftValvesOutputs[6]-m_dLP_Output[2];
		m_dleftValvesOutputs[7] = m_dleftValvesOutputs[7]+m_dLP_Output[2];

		// Bicep rotational motion
		m_dleftValvesOutputs[4] = m_dleftValvesOutputs[4]+m_dLP_Output[3];
		m_dleftValvesOutputs[5] = m_dleftValvesOutputs[5]+m_dLP_Output[3];
		m_dleftValvesOutputs[6] = m_dleftValvesOutputs[6]-m_dLP_Output[3];
		m_dleftValvesOutputs[7] = m_dleftValvesOutputs[7]-m_dLP_Output[3];

		// Forearm vertical motion
		m_dleftValvesOutputs[8] = m_dleftValvesOutputs[8]+m_dLP_Output[4];
		m_dleftValvesOutputs[9] = m_dleftValvesOutputs[9]-m_dLP_Output[4];
		m_dleftValvesOutputs[10] = m_dleftValvesOutputs[10]+m_dLP_Output[4];
		m_dleftValvesOutputs[11] = m_dleftValvesOutputs[11]-m_dLP_Output[4];

		// Forearm rotational motion
		m_dleftValvesOutputs[8] = m_dleftValvesOutputs[8]-m_dLP_Output[5];
		m_dleftValvesOutputs[9] = m_dleftValvesOutputs[9]-m_dLP_Output[5];
		m_dleftValvesOutputs[10] = m_dleftValvesOutputs[10]+m_dLP_Output[5];
		m_dleftValvesOutputs[11] = m_dleftValvesOutputs[11]+m_dLP_Output[5];

		// Write values to hardware
		SetLeftArmPressures();

		Sleep(20);
		count++;
	}
}

void RightPID()
{
	// PID Output variables
	int count = 20;
	while(count<NUMBER_OF_STEPS)
	{
		ReadRightEncoders();rightLogicalAngles();

		for (int i=0; i<NUM_AXES; i++)
			*m_dRP_Output = rightPID(/*&m_fDesiredRightAngle[i]*/);
		
		m_drightValvesOutputs[0] = m_drightValvesOutputs[0]-m_dRP_Output[0];
		m_drightValvesOutputs[1] = m_drightValvesOutputs[1]+m_dRP_Output[0];
			
		m_drightValvesOutputs[2] = m_drightValvesOutputs[2]+m_dRP_Output[1];
		m_drightValvesOutputs[3] = m_drightValvesOutputs[3]-m_dRP_Output[1];

		m_drightValvesOutputs[4] = m_drightValvesOutputs[4]+m_dRP_Output[2];
		m_drightValvesOutputs[5] = m_drightValvesOutputs[5]-m_dRP_Output[2];
		m_drightValvesOutputs[6] = m_drightValvesOutputs[6]-m_dRP_Output[2];
		m_drightValvesOutputs[7] = m_drightValvesOutputs[7]+m_dRP_Output[2];

		m_drightValvesOutputs[4] = m_drightValvesOutputs[4]+m_dRP_Output[3];
		m_drightValvesOutputs[5] = m_drightValvesOutputs[5]+m_dRP_Output[3];
		m_drightValvesOutputs[6] = m_drightValvesOutputs[6]-m_dRP_Output[3];
		m_drightValvesOutputs[7] = m_drightValvesOutputs[7]-m_dRP_Output[3];

		m_drightValvesOutputs[8] = m_drightValvesOutputs[8]+m_dRP_Output[4];
		m_drightValvesOutputs[9] = m_drightValvesOutputs[9]-m_dRP_Output[4];
		m_drightValvesOutputs[10] = m_drightValvesOutputs[10]+m_dRP_Output[4];
		m_drightValvesOutputs[11] = m_drightValvesOutputs[11]-m_dRP_Output[4];

		m_drightValvesOutputs[8] = m_drightValvesOutputs[8]-m_dRP_Output[5];
		m_drightValvesOutputs[9] = m_drightValvesOutputs[9]-m_dRP_Output[5];
		m_drightValvesOutputs[10] = m_drightValvesOutputs[10]+m_dRP_Output[5];
		m_drightValvesOutputs[11] = m_drightValvesOutputs[11]+m_dRP_Output[5];

		SetRightArmPressures();Sleep(20);count++;
	}
}

void LeftNeuralNetController()
{
	// Declare Incremental Voltage variables for local function
	float incrementalVoltage0 = 0.0;
	float incrementalVoltage1 = 0.0;
	float incrementalVoltage2 = 0.0;
	float incrementalVoltage3 = 0.0;
	float incrementalVoltage4 = 0.0;
	float incrementalVoltage5 = 0.0;

	// Declare segmented Trajectory Path (in angles) variables
	double SegmentPathL0=0,SegmentPathL1=0,SegmentPathL2=0,SegmentPathL3=0,SegmentPathL4=0,SegmentPathL5=0;
	int count=1;

	/*** Precise Sampling Time Initialization ***/
	
	// Declare timing variables
	LARGE_INTEGER ticksPerSecond, start_ticks, end_ticks, cputime, tick;

	// Timer functions (windows.h). 
	// Checking to see if Timer calls do work. (Tow of them are tested: (a) get computer frequency and (b) current-tick value.
	if (!QueryPerformanceFrequency(&ticksPerSecond))							// This commands outputs the computer's 'counter-frequency'. I.e. how many ticks in one second.
		if (!QueryPerformanceCounter(&tick) )									// This command outputs the 
			// ATLTRACE(_T("There is a problem reading timing information from this machine");

	// We may want to take out the segmented path stuff out for IMA.

	// Create the segmented path: Difference between desired/current over total number of steps.
	SegmentPathL0 = (m_fDesiredLeftAngle[0] - m_fprevThetasL[0])/ m_sTotalStep	;
	SegmentPathL1 = (m_fDesiredLeftAngle[1] - m_fprevThetasL[1])/ m_sTotalStep	;
	SegmentPathL2 = (m_fDesiredLeftAngle[2] - m_fprevThetasL[2])/ m_sTotalStep	;
	SegmentPathL3 = (m_fDesiredLeftAngle[3] - m_fprevThetasL[3])/ m_sTotalStep	;
	SegmentPathL4 = (m_fDesiredLeftAngle[4] - m_fprevThetasL[4])/ m_sTotalStep	;
	SegmentPathL5 = (m_fDesiredLeftAngle[5] - m_fprevThetasL[5])/ m_sTotalStep	;

	/*** Generate the Homing Routine ***/
	// Run this loop iteratively for as many times as SegmentedPath was partitioned.
	// Check if for each iteration execution took less than the sampling time of 60msec.
	while(count<=m_sTotalStep)
	{
		QueryPerformanceCounter(&start_ticks);

		// Computing the correct stage of the homing trajectory. 
		// Each time count increases, we move to the next stage of the planned trajectory.
		m_fDesiredLeftAngle[0] = m_fprevThetasL[0] + count * SegmentPathL0;
		m_fDesiredLeftAngle[1] = m_fprevThetasL[1] + count * SegmentPathL1;
		m_fDesiredLeftAngle[2] = m_fprevThetasL[2] + count * SegmentPathL2;
		m_fDesiredLeftAngle[3] = m_fprevThetasL[3] + count * SegmentPathL3;
		m_fDesiredLeftAngle[4] = m_fprevThetasL[4] + count * SegmentPathL4;
		m_fDesiredLeftAngle[5] = m_fprevThetasL[5] + count * SegmentPathL5;
		
		// For the following calls we have to examine whether we are moving forward
		// or backward in order to call the appropriate Neural Network file.
		// The .Process() call returns the approrpriate voltage for the the desired angle. 
		
		/*** Angle 0, Joint 1 ***/
		if( m_fprevThetasL[0] > m_fDesiredLeftAngle[0] )
			LeftNNMusclesAngle0B.Process(&m_fDesiredLeftAngle[0],&incrementalVoltage0);

		else if( m_fprevThetasL[0] < m_fDesiredLeftAngle[0] )
			LeftNNMusclesAngle0F.Process(&m_fDesiredLeftAngle[0],&incrementalVoltage0);

		// Write valve outputs (for both valve 0 and 1).
		m_dleftValvesOutputs[0] = m_dInitialleftValvesOutputs[0] - incrementalVoltage0;
		m_dleftValvesOutputs[1] = m_dInitialleftValvesOutputs[1] + incrementalVoltage0;
		

		/*** Angle 1, Joint 2 ***/
		if( m_fprevThetasL[1] < m_fDesiredLeftAngle[1] )
			LeftNNMusclesAngle1F.Process(&m_fDesiredLeftAngle[1],&incrementalVoltage1);

		else if( m_fprevThetasL[1] > m_fDesiredLeftAngle[1] )
			LeftNNMusclesAngle1B.Process(&m_fDesiredLeftAngle[1],&incrementalVoltage1);

		m_dleftValvesOutputs[2] = m_dInitialleftValvesOutputs[2]+incrementalVoltage1;
		m_dleftValvesOutputs[3] = m_dInitialleftValvesOutputs[3]-incrementalVoltage1;

		/*** Angle 2, Joint 3&4 ***/
		if( m_fprevThetasL[2] > m_fDesiredLeftAngle[2] )
				LeftNNMusclesAngle2B.Process(&m_fDesiredLeftAngle[2],&incrementalVoltage2);
		else if( m_fprevThetasL[2] < m_fDesiredLeftAngle[2] )
				LeftNNMusclesAngle2F.Process(&m_fDesiredLeftAngle[2],&incrementalVoltage2);
		
		/*** Angle 3, Joint 3&4 ***/
		if( m_fprevThetasL[3] > m_fDesiredLeftAngle[3] )
				LeftNNMusclesAngle3B.Process(&m_fDesiredLeftAngle[3],&incrementalVoltage3);

		else if( m_fprevThetasL[3] < m_fDesiredLeftAngle[3] )
				LeftNNMusclesAngle3F.Process(&m_fDesiredLeftAngle[3],&incrementalVoltage3);

		m_dleftValvesOutputs[4] = m_dInitialleftValvesOutputs[4] + incrementalVoltage2 - incrementalVoltage3;
		m_dleftValvesOutputs[5] = m_dInitialleftValvesOutputs[5] - incrementalVoltage2 - incrementalVoltage3;			
		m_dleftValvesOutputs[6] = m_dInitialleftValvesOutputs[6] - incrementalVoltage2 + incrementalVoltage3;
		m_dleftValvesOutputs[7] = m_dInitialleftValvesOutputs[7] + incrementalVoltage2 + incrementalVoltage3;

		/*** Angle 4, Joint 5&6 ***/
		if( m_fprevThetasL[4] >  m_fDesiredLeftAngle[4] )
			LeftNNMusclesAngle4B.Process(& m_fDesiredLeftAngle[4],&incrementalVoltage4);
		else if( m_fprevThetasL[4] <  m_fDesiredLeftAngle[4] )
			LeftNNMusclesAngle4F.Process(& m_fDesiredLeftAngle[4],&incrementalVoltage4);

		/*** Angle 5, Joint 5&6 ***/
		if( m_fprevThetasL[5] > m_fDesiredLeftAngle[5] )
			LeftNNMusclesAngle5B.Process(&m_fDesiredLeftAngle[5],&incrementalVoltage5);
		else if( m_fprevThetasL[5] < m_fDesiredLeftAngle[5] )
			LeftNNMusclesAngle5F.Process(&m_fDesiredLeftAngle[5],&incrementalVoltage5);

		m_dleftValvesOutputs[8] = m_dInitialleftValvesOutputs[8] - incrementalVoltage4 - incrementalVoltage5 ;
		m_dleftValvesOutputs[9] = m_dInitialleftValvesOutputs[9] + incrementalVoltage4 + incrementalVoltage5;
		m_dleftValvesOutputs[10]= m_dInitialleftValvesOutputs[10] - incrementalVoltage4 + incrementalVoltage5;
		m_dleftValvesOutputs[11]= m_dInitialleftValvesOutputs[11] + incrementalVoltage4 - incrementalVoltage5;

		/*** Write pressures (voltages) to the Hardware. ***/
		SetLeftArmPressures();

		QueryPerformanceCounter(&end_ticks); 

		while(  ((float)(end_ticks.QuadPart - start_ticks.QuadPart)/ticksPerSecond.QuadPart*1000 ) < (float)m_sSampleTime )
			QueryPerformanceCounter(&end_ticks); cputime.QuadPart = end_ticks.QuadPart- start_ticks.QuadPart;	

		// Increase counter
		count++;
	}

	Sleep(200);

	// Read the encoder position and then computer the Logical Angles
	ReadLeftEncoders();
	leftLogicalAngles();

	// Assigning the Previous Angles
	for(int i=0;i<6;i++)
		m_fprevThetasL[i] = m_dleftAngles[i];
}

void RightNeuralNetController()
{
	// Declare Incremental Voltage variables for local function
	float incrementalVoltage0 = 0.0;
	float incrementalVoltage1 = 0.0;
	float incrementalVoltage2 = 0.0;
	float incrementalVoltage3 = 0.0;
	float incrementalVoltage4 = 0.0;
	float incrementalVoltage5 = 0.0;

	// Declare segmented Trajectory Path (in angles) variables
	double SegmentPathR0=0,SegmentPathR1=0,SegmentPathR2=0,SegmentPathR3=0,SegmentPathR4=0,SegmentPathR5=0;
	int count=1;

	/*** Precise Sampling Time Initialization ***/
	
	// Declare timing variables
	LARGE_INTEGER ticksPerSecond, start_ticks, end_ticks, cputime, tick;

	// Timer functions (windows.h). 
	// Checking to see if Timer calls do work. (Tow of them are tested: (a) get computer frequency and (b) current-tick value.
	if (!QueryPerformanceFrequency(&ticksPerSecond))							// This commands outputs the computer's 'counter-frequency'. I.e. how many ticks in one second.
		if (!QueryPerformanceCounter(&tick) )									// This command outputs the 
			// ATLTRACE(_T("There is a problem reading timing information from this machine");
	
	// Create the segmented path: Difference between desired/current over total number of steps.
	SegmentPathR0 = (m_fDesiredRightAngle[0] - m_fprevThetasR[0])/ m_sTotalStep	;
	SegmentPathR1 = (m_fDesiredRightAngle[1] - m_fprevThetasR[1])/ m_sTotalStep	;
	SegmentPathR2 = (m_fDesiredRightAngle[2] - m_fprevThetasR[2])/ m_sTotalStep	;
	SegmentPathR3 = (m_fDesiredRightAngle[3] - m_fprevThetasR[3])/ m_sTotalStep	;
	SegmentPathR4 = (m_fDesiredRightAngle[4] - m_fprevThetasR[4])/ m_sTotalStep	;
	SegmentPathR5 = (m_fDesiredRightAngle[5] - m_fprevThetasR[5])/ m_sTotalStep	;

	/*** Generate the Homing Routine ***/
	// Run this loop iteratively for as many times as SegmentedPath was partitioned.
	// Check if for each iteration execution took less than the sampling time of 60msec. 
	while(count<=m_sTotalStep)
	{
		QueryPerformanceCounter(&start_ticks);
		
		// Computing the correct stage of the homing trajectory. 
		// Each time count increases, we move to the next stage of the planned trajectory.		
		m_fDesiredRightAngle[0] = m_fprevThetasR[0] + count * SegmentPathR0;
		m_fDesiredRightAngle[1] = m_fprevThetasR[1] + count * SegmentPathR1;
		m_fDesiredRightAngle[2] = m_fprevThetasR[2] + count * SegmentPathR2;
		m_fDesiredRightAngle[3] = m_fprevThetasR[3] + count * SegmentPathR3;
		m_fDesiredRightAngle[4] = m_fprevThetasR[4] + count * SegmentPathR4;
		m_fDesiredRightAngle[5] = m_fprevThetasR[5] + count * SegmentPathR5;

		// For the following calls we have to examine whether we are moving forward
		// or backward in order to call the appropriate Neural Network file.
		// The .Process() call returns the approrpriate voltage for the the desired angle. 

		/*** Angle 0, Joint 1 ***/
		if( m_fprevThetasR[0] > m_fDesiredRightAngle[0] )
			RightNNMusclesAngle0B.Process(&m_fDesiredRightAngle[0],&incrementalVoltage0);

		else if( m_fprevThetasR[0] < m_fDesiredRightAngle[0])
			RightNNMusclesAngle0F.Process(&m_fDesiredRightAngle[0],&incrementalVoltage0);

		// Write output voltage (valves 0 and 1).
		m_drightValvesOutputs[0] = m_dInitialrightValvesOutputs[0] - incrementalVoltage0;
		m_drightValvesOutputs[1] = m_dInitialrightValvesOutputs[1] + incrementalVoltage0;

		/*** Angle 1, Joint 2 ***/
		if( m_fprevThetasR[1] < m_fDesiredRightAngle[1] )
			RightNNMusclesAngle1F.Process(&m_fDesiredRightAngle[1],&incrementalVoltage1);

		else if( m_fprevThetasR[1] > m_fDesiredRightAngle[1])
			RightNNMusclesAngle1B.Process(&m_fDesiredRightAngle[1],&incrementalVoltage1);

		m_drightValvesOutputs[2] = m_dInitialrightValvesOutputs[2]+incrementalVoltage1;
		m_drightValvesOutputs[3] = m_dInitialrightValvesOutputs[3]-incrementalVoltage1;


		/*** Angle 2, Joint 3&4 ***/
		if( m_fprevThetasR[2] > m_fDesiredRightAngle[2] )
			RightNNMusclesAngle2B.Process(&m_fDesiredRightAngle[2],&incrementalVoltage2);

		else if( m_fprevThetasR[2] < m_fDesiredRightAngle[2] )
			RightNNMusclesAngle2F.Process(&m_fDesiredRightAngle[2],&incrementalVoltage2);
		
		
		/*** Angle 3, Joint 3&4 ***/
		if( m_fprevThetasR[3] > m_fDesiredRightAngle[3])
			RightNNMusclesAngle3B.Process(&m_fDesiredRightAngle[3],&incrementalVoltage3);
		else if( m_fprevThetasR[3] < m_fDesiredRightAngle[3])
			RightNNMusclesAngle3F.Process(&m_fDesiredRightAngle[3],&incrementalVoltage3);

		m_drightValvesOutputs[4] = m_dInitialrightValvesOutputs[4] + incrementalVoltage2 - incrementalVoltage3;
		m_drightValvesOutputs[5] = m_dInitialrightValvesOutputs[5] - incrementalVoltage2 - incrementalVoltage3;			
		m_drightValvesOutputs[6] = m_dInitialrightValvesOutputs[6] - incrementalVoltage2 + incrementalVoltage3;
		m_drightValvesOutputs[7] = m_dInitialrightValvesOutputs[7] + incrementalVoltage2 + incrementalVoltage3;

		
		/*** Angle 4, Joint 5&6 ***/
		if( m_fprevThetasR[4] > m_fDesiredRightAngle[4] )
			RightNNMusclesAngle4B.Process(&m_fDesiredRightAngle[4],&incrementalVoltage4);
		else if( m_fprevThetasR[4] < m_fDesiredRightAngle[4] )
			RightNNMusclesAngle4F.Process(&m_fDesiredRightAngle[4],&incrementalVoltage4);
		
		
		/*** Angle 5, Joint 5&6 ***/
		if( m_fprevThetasR[5] > m_fDesiredRightAngle[5] )
			RightNNMusclesAngle5B.Process(&m_fDesiredRightAngle[5],&incrementalVoltage5);
		else if( m_fprevThetasR[5] < m_fDesiredRightAngle[5] )
			RightNNMusclesAngle5F.Process(&m_fDesiredRightAngle[5],&incrementalVoltage5);

		m_drightValvesOutputs[8] = m_dInitialrightValvesOutputs[8] - incrementalVoltage4 - incrementalVoltage5 ;
		m_drightValvesOutputs[9] = m_dInitialrightValvesOutputs[9] + incrementalVoltage4 + incrementalVoltage5;
		m_drightValvesOutputs[10]= m_dInitialrightValvesOutputs[10] - incrementalVoltage4 + incrementalVoltage5;
		m_drightValvesOutputs[11]= m_dInitialrightValvesOutputs[11] + incrementalVoltage4 - incrementalVoltage5;

		/*** Write pressures (voltages) to the Hardware. ***/
		SetRightArmPressures();

		QueryPerformanceCounter(&end_ticks); 

		while(((float)(end_ticks.QuadPart-start_ticks.QuadPart)/ticksPerSecond.QuadPart*1000) < (float) m_sSampleTime)
			QueryPerformanceCounter(&end_ticks); cputime.QuadPart = end_ticks.QuadPart- start_ticks.QuadPart;	

		// Increase counter
		count++;
	}
	
	Sleep(200);

	// Read the encoder position and then computer the Logical Angles
	ReadRightEncoders();
	rightLogicalAngles();

	// Assigning the Previous Angles
	for(int i=0;i<6;i++)
		m_fprevThetasR[i] = m_drightAngles[i];
}
