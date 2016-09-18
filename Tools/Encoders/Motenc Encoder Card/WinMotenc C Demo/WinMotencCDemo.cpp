// WinMotencCDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "winmotenc.h"

double AdcMilliVolts[4];

int main(int argc, char* argv[])
{

	printf("Initializing MOTENC Board\n");
	
	if( !vitalInit() )
	{
		printf( "Error initializing WinMotenc library\n" );
		return 0;
	}

	//##### Analog Outputs #####

	// Write analog output voltage 3.5volts on channel 0
	printf("Output 3.5 volts on channel 0\n");
	vitalDacWrite( 0, 3.5 );

	// wait for 0.5 seconds
	Sleep( 500 );

	// write zero volts
	printf("Output 0 volts on channel 0\n");
	vitalDacWrite( 0, 0 );

	AdcMilliVolts[0] = 0;
	AdcMilliVolts[1] = 0;
	AdcMilliVolts[2] = 0;
	AdcMilliVolts[3] = 0;

	//##### Analog Inputs #####
	//Read Channel 0..3 on J5
	vitalReadAnalogInputs( 0, AdcMilliVolts );
	printf( "ADC milli volts Ch 0..3 on J5 = %4.2f, %4.2f, %4.2f, %4.2f\n", 
											AdcMilliVolts[0],
											AdcMilliVolts[1],
											AdcMilliVolts[2],
											AdcMilliVolts[3] );

	//Read Channel 4..7 on J8
	vitalReadAnalogInputs( 1, AdcMilliVolts );
	printf( "ADC milli volts Ch 4..7 on J8 = %4.2f, %4.2f, %4.2f, %4.2f\n", 
											AdcMilliVolts[0],
											AdcMilliVolts[1],
											AdcMilliVolts[2],
											AdcMilliVolts[3] );

	//clean up on exit
	vitalQuit();

	return 0;
}

