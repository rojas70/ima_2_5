#include "stdafx.h"
#include <windows.h>
#include <windef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <stdarg.h>	
#include "time.h"
#include <IOSTREAM>
#include "winmotenc.h"

using namespace std;

/////////////////////////////////////////////////////////////////////

// Initialize input and output valve buffers for the left and right valves
double LeftValvesOutputs[12]	={0};
double RightValvesOutputs[12]	={0};
double LeftValvesInputs[12]		={0};
double RightValvesInputs[12]	={0};

// Function declarations
void initializecards();
void initializeleftvalves();		// Slowly inflate all muscles to their bias pressure of 2bars (2 volts).
void closevalves();

int main()
{
	// Initialize cards and left valves
	int count=0,numb=0;
	float v0=1.0,v1=1.0;
	double buffervoltage1=0.0,buffervoltage2=0.0,buffervoltage3=0.0,buffervoltage4=0.0,buffervoltage5=0.0,buffervoltage6=0.0, buffervoltage7=0.0, buffervoltage8=0.0;

	initializecards();
	initializeleftvalves();

	// Precise Sampling Time Initialization		
	LARGE_INTEGER	start_ticks;
	LARGE_INTEGER	end_ticks;
	LARGE_INTEGER	ticksPerSecond;
	LARGE_INTEGER	tick;
	LARGE_INTEGER	cputime;

	// QueryPerformance calls
	if (!QueryPerformanceFrequency(&ticksPerSecond))
	if (!QueryPerformanceCounter(&tick) ) 
		printf("\n\nCan't run. The counter not installed.\n\n");
	Sleep(3000);

	// Set buffer voltages to 2 volts for all 8 arrays.
	buffervoltage1 = 2;buffervoltage2 = 2;
	buffervoltage3 = 2;buffervoltage5 = 2;
	buffervoltage4 = 2;buffervoltage6 = 2;
	buffervoltage7 = 2,buffervoltage8 = 2;

	// Choose board 0
	vitalSelectBoard(0);

	// Begin the control loop. 
	while(count<10)
	{
		// Give value to tick_counter at beginning of operation. 
		QueryPerformanceCounter(&start_ticks);

		// Update the voltage output refrences
		vitalDacWrite( 0, buffervoltage1 );

		// Read the pressures
		// Read Encoders

		// Find error
		// Calculate the new voltage output reference
	
		//...Controller will be here....
		


		// Analog-outputs check the voltages to see if they are greater than 3V. 
		// If so, we must truncate the value at 3V.

		// Each of the stages to increase the servo-valve voltage is found next. 
		if (count>0 && count<50)
		{
			//buffervoltage1+=0.02;buffervoltage2-=0.02;buffervoltage3+=0.02;buffervoltage4-=0.02;
			
			
			// Change in a pair-wise fashion the voltage value of the bicep muslces. 
			// Contract biceps
			buffervoltage5-=0.02;
			buffervoltage6+=0.02;
			buffervoltage7+=0.02;
			buffervoltage8-=0.02;
	
			// Write this stream of voltage values to all servo-valves
		    vitalDacWrite( 0, buffervoltage1 );
			vitalDacWrite( 1, buffervoltage2 );
			vitalDacWrite( 2, buffervoltage3 );
			vitalDacWrite( 3, buffervoltage4 );
			vitalDacWrite( 4, buffervoltage5 );
			vitalDacWrite( 5, buffervoltage6 );
			vitalDacWrite( 6, buffervoltage7 );
			vitalDacWrite( 7, buffervoltage8 );
		}

		if (count>50 && count<150)
		{
			// Shoulders
			// Contract shoulders
			buffervoltage1-=0.02;
			buffervoltage2+=0.02;

			buffervoltage3-=0.02;
			buffervoltage4+=0.02;

			// Biceps
			// Deflate
			buffervoltage5+=0.01;
			buffervoltage6-=0.01;

			buffervoltage7-=0.01;
			buffervoltage8+=0.01;

			// Write the voltage buffer values to the servo-valves
		    vitalDacWrite( 0, buffervoltage1 );
			vitalDacWrite( 1, buffervoltage2 );
			vitalDacWrite( 2, buffervoltage3 );
			vitalDacWrite( 3, buffervoltage4 );
			vitalDacWrite( 4, buffervoltage5 );
			vitalDacWrite( 5, buffervoltage6 );
			vitalDacWrite( 6, buffervoltage7 );
			vitalDacWrite( 7, buffervoltage8 );
		}


		if (count>150 && count<250)
		{
			// Shoulder
			// Deflate
			buffervoltage1+=0.02;
			buffervoltage2-=0.02;
			
			buffervoltage3+=0.02;
			buffervoltage4-=0.02;

			// Biceps
			// Contract
			buffervoltage5-=0.01;
			buffervoltage6+=0.01;

			buffervoltage7+=0.01;
			buffervoltage8-=0.01;

			// Write to the servo-valves
		    vitalDacWrite( 0, buffervoltage1 );
			vitalDacWrite( 1, buffervoltage2 );
			vitalDacWrite( 2, buffervoltage3 );
			vitalDacWrite( 3, buffervoltage4 );
			vitalDacWrite( 4, buffervoltage5 );
			vitalDacWrite( 5, buffervoltage6 );
			vitalDacWrite( 6, buffervoltage7 );
			vitalDacWrite( 7, buffervoltage8 );
		}

		if (count>250 && count<300)
		{

			// Shoulder
			// Defltate
			buffervoltage5+=0.02;
			buffervoltage6-=0.02;

			buffervoltage7-=0.02;
			buffervoltage8+=0.02;

			// Write to servo-valves
			vitalDacWrite( 4, buffervoltage5 );
			vitalDacWrite( 5, buffervoltage6 );
			vitalDacWrite( 6, buffervoltage7 );
			vitalDacWrite( 7, buffervoltage8 );
		}

		// Rest between stages
		if (count == 50 || count == 100 ||count == 150 || count == 200 || count == 250)
				Sleep(500);

	

		// Give value of tick_counter to end ticks   
		QueryPerformanceCounter(&end_ticks); 

		// Compute total time elapsed: (end_ticks - start_ticks) / ticks_per_second
		printf("Total time elapsed:%f\n",(float)(end_ticks.QuadPart-start_ticks.QuadPart)/ticksPerSecond.QuadPart*1000);
		
		// If less than 20 seconds, 
		while(((float)(end_ticks.QuadPart-start_ticks.QuadPart)/ticksPerSecond.QuadPart*1000) < (float) 20)
		QueryPerformanceCounter(&end_ticks); cputime.QuadPart = end_ticks.QuadPart- start_ticks.QuadPart;	

		count++;
	}
	
	QueryPerformanceCounter(&end_ticks); printf("total:%f\n",(float)(end_ticks.QuadPart-start_ticks.QuadPart)/ticksPerSecond.QuadPart*1000);

	closevalves();
	Sleep(1000);

	//clean up on exit
	vitalQuit();

	// wait for 1 seconds

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

// Definition of local functions

void initializecards()
{
	int numb =0;
	//Initializing the Cards
	if( numb=vitalInit() )
		printf("%d board(s) detected\n",numb);
	else
		printf( "Error initializing WinMotenc library\n" );
}


void initializeleftvalves()
{
	// Initialize variables
	double buffervoltage=0.1;
	int i=0,j=0,k=0;

	for(i=0;i<20;i++) // 20x100 ms = 2 seconds. The time it takes to inflate the muscle to its bias value. 
	{
		// Select board 0
		vitalSelectBoard(0);

		// Write to each of the 8 channels of board 0. 
		for(j=0;j<8;j++) 
			vitalDacWrite( j, buffervoltage );

		// Switch to board 1 to write to the remaining 4 channels.
		vitalSelectBoard(1);
		for(j=0;j<4;j++) // giving reference to first 4 channel of board 1
			vitalDacWrite( j, buffervoltage );

		// Increase the voltage. There are a total of 20 steps. It goes from 0.1 milivots to 2 volts. 
		buffervoltage += 0.1; 
		Sleep(100);														// Wait 100 ms at each step
	}

	// Set the output valve buffer pressure to 2.0 bar for each of the 12 valves. 
	for(k = 0; k < 12; k++)
			LeftValvesOutputs[k] = 2.0;
}

void closevalves()
{
	int i=0,j=0,k=0;

	for(i=0;i<20;i++) // The idea is to deflate the muscles in 30 steps, each one decreases the voltage by 0.1Volts.
	{
		// Decrease the voltage buffer value by 0.1 volts for all 12 channel values. 
		for(k=0;k<12;k++)
			LeftValvesOutputs[k]-=0.1;

		// Choose Board 0
		vitalSelectBoard(0);

		// Write to first 8 servo-valves the decreased voltage value
		for(j=0;j<8;j++) 
			vitalDacWrite( j, LeftValvesOutputs[j] );

		// Choose Board 1
		vitalSelectBoard(1);

		// Write to the next 8 channels, the decreased servo-valve voltage value. 
		for(j=0;j<8;j++) 
			vitalDacWrite( j, LeftValvesOutputs[j+8] );

		// Choose last board
		vitalSelectBoard(2);

		// Write to the last 8 channels, 0 volts. 
		for(j=0;j<8;j++) 
			vitalDacWrite( j, 0 );

		Sleep(150); // Wait 100 ms at each step
	}
}




