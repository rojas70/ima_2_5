#ifndef _Control_h
#define _Control_h

#include "stdafx.h"
#include <windows.h>
#include <windef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <IOSTREAM>
#include "winmotenc.h"

// Left
extern double	m_dInitialleftValvesOutputs[12];
extern double	m_dleftValvesOutputs[12];
extern double	m_dleftValvesInputs[12];
extern double	m_dleftAngles[6];
extern long		m_dleftEncoders[6];

// Right
extern double	m_drightValvesOutputs[12];
extern double	m_dInitialrightValvesOutputs[12];
extern double	m_drightValvesInputs[12];
extern long		m_drightEncoders[6];
extern double	m_drightAngles[6];

#define PI			3.14159265
#define RADS2DEGREE	360/(2*PI)
#define NUM_AXES	6
/*********************************************************************
* InitializeAllValves()
*
* The values for these muscles were calculated by inspection
* in order for the arm to go to the HOME position. 
*
* These values were the easiest way to get the arm to go to 
* a somewhat stable position each time.
* 
* However, after using the muscles for some time, the properties
* of the muscles change and the home position will not be the same.
*********************************************************************/
void InitializeAllValves()
{
	// Initialize local variables
	double bufferVoltage = 0.1;
	int i=0,j=0,k=0;

	// Left Arm
	m_dleftValvesOutputs[0]		= 2.3;		// Rotation for shoulder
	m_dleftValvesOutputs[1]		= 1.7;

	m_dleftValvesOutputs[2]		= 2.0;		// Vertical Lift for shoulder
	m_dleftValvesOutputs[3]		= 2.0;

	m_dleftValvesOutputs[4]		= 0.0;		// Bicep
	m_dleftValvesOutputs[5]		= 2.2;
	m_dleftValvesOutputs[6]		= 2.4;
	m_dleftValvesOutputs[7]		= 0.0;

	m_dleftValvesOutputs[8]		= 2.3;		// Forearm
	m_dleftValvesOutputs[9]		= 1.7;
	m_dleftValvesOutputs[10]	= 1.7;
	m_dleftValvesOutputs[11]	= 2.3;

	// Right Arm
	m_drightValvesOutputs[0]	=2.1;		// Rotation for shoulder
	m_drightValvesOutputs[1]	=1.9;

	m_drightValvesOutputs[2]	=2.2;		// Vertical Lift for shoulder
	m_drightValvesOutputs[3]	=1.8;
	
	m_drightValvesOutputs[4]	=0.0;		// Bicep
	m_drightValvesOutputs[5]	=2.2;
	m_drightValvesOutputs[6]	=2.1;
	m_drightValvesOutputs[7]	=0.0;

	m_drightValvesOutputs[8]	=2.0;		// Forearm
	m_drightValvesOutputs[9]	=2.0;
	m_drightValvesOutputs[10]	=2.0;
	m_drightValvesOutputs[11]	=2.0;

	// The following set of steps, 25x100 ms = 2.5 sec, allows the muscles to fully inflate.
	// Write voltages to the valves and increase those voltages with each iteration.
	for(i=0;i<25;i++) 
	{
		vitalSelectBoard(0);
		if(bufferVoltage <= m_dleftValvesOutputs[1] + 0.05)
				vitalDacWrite(1, bufferVoltage);
		if(bufferVoltage <= m_dleftValvesOutputs[2] + 0.05)
				vitalDacWrite(2, bufferVoltage);

		// Increase the buffer voltage gently to allow for smooth inflation. 
		bufferVoltage +=0.1; 
		Sleep(100);								// Wait 100 ms at each step.


		vitalSelectBoard(1);
		if(bufferVoltage <= m_drightValvesOutputs[0] + 0.05)
				vitalDacWrite(4, bufferVoltage);
		if(bufferVoltage <= m_drightValvesOutputs[2] + 0.05)
				vitalDacWrite(6, bufferVoltage);
		bufferVoltage +=0.1; // Increasing the ref voltage slowly not to harm 
		Sleep(100); // Wait 100 ms at each step		
	}
	Sleep(200);
	bufferVoltage =0.1;
	for(i=0;i<25;i++) // 25x100 ms = 2.5 sec makes the muscles blow up
	{	
		vitalSelectBoard(0);
		for(j=0;j<8;j++) // giving reference to each channel of board 0
		{	
			if(j==0)
				if(bufferVoltage <= m_dleftValvesOutputs[j] + 0.05){
					vitalDacWrite(j, bufferVoltage);}
			//if (j==1)
			//	if(bufferVoltage <= m_dleftValvesOutputs[j] + 0.05){
			//		vitalDacWrite(j, bufferVoltage);}
			//if (j==2)
			//	if(bufferVoltage <= m_dleftValvesOutputs[j] + 0.05){
			//		vitalDacWrite(j, bufferVoltage);}
			if (j==3)
				if(bufferVoltage <= m_dleftValvesOutputs[j] + 0.05){
					vitalDacWrite(j, bufferVoltage);}
			if (j==4)
				if(bufferVoltage <= m_dleftValvesOutputs[j] + 0.05){
					vitalDacWrite(j, bufferVoltage);}
			if (j==5)
				if(bufferVoltage <= m_dleftValvesOutputs[j] + 0.05){
					vitalDacWrite(j, bufferVoltage);}
			if (j==6)
				if(bufferVoltage <= m_dleftValvesOutputs[j] + 0.05){
					vitalDacWrite(j, bufferVoltage);}
			if (j==7)
				if(bufferVoltage <= m_dleftValvesOutputs[j] + 0.05){
					vitalDacWrite(j, bufferVoltage);}
		}
		vitalSelectBoard(1);
		for(j=8;j<12;j++) // giving reference to each channel of board 0
		{	
			if (j==8)
				if(bufferVoltage <= m_dleftValvesOutputs[j] + 0.05){
					vitalDacWrite(j-8, bufferVoltage);}
			if (j==9)
				if(bufferVoltage <= m_dleftValvesOutputs[j] + 0.05){
					vitalDacWrite(j-8, bufferVoltage);}
			if (j==10)
				if(bufferVoltage <= m_dleftValvesOutputs[j] + 0.05){
					vitalDacWrite(j-8, bufferVoltage);}
			if (j==11)
				if(bufferVoltage <= m_dleftValvesOutputs[j] + 0.05){
					vitalDacWrite(j-8, bufferVoltage);}
		}
		// Right Arm
		vitalSelectBoard(1);
		for(j=0;j<4;j++) // giving reference to each channel of board 0
		{	
			//if (j==0)
			//	if(bufferVoltage <= m_drightValvesOutputs[j] + 0.05){
			//		vitalDacWrite(j+4, bufferVoltage);}
			if (j==1)
				if(bufferVoltage <= m_drightValvesOutputs[j] + 0.05){
					vitalDacWrite(j+4, bufferVoltage);}
			//if (j==2)
			//	if(bufferVoltage <= m_drightValvesOutputs[j] + 0.05){
			//		vitalDacWrite(j+4, bufferVoltage);}
			if (j==3)
				if(bufferVoltage <= m_drightValvesOutputs[j] + 0.05){
					vitalDacWrite(j+4, bufferVoltage);}
		}
		vitalSelectBoard(2);
		for(j=4;j<12;j++) // giving reference to each channel of board 0
		{	
			if(j==4)
				if(bufferVoltage <= m_drightValvesOutputs[j] + 0.05){
					vitalDacWrite(j-4, bufferVoltage);}
			if (j==5)
				if(bufferVoltage <= m_drightValvesOutputs[j] + 0.05){
					vitalDacWrite(j-4, bufferVoltage);}
			if (j==6)
				if(bufferVoltage <= m_drightValvesOutputs[j] + 0.05){
					vitalDacWrite(j-4, bufferVoltage);}
			if (j==7)
				if(bufferVoltage <= m_drightValvesOutputs[j] + 0.05){
					vitalDacWrite(j-4, bufferVoltage);}
			if (j==8)
				if(bufferVoltage <= m_drightValvesOutputs[j] + 0.05){
					vitalDacWrite(j-4, bufferVoltage);}
			if (j==9)
				if(bufferVoltage <= m_drightValvesOutputs[j] + 0.05){
					vitalDacWrite(j-4, bufferVoltage);}
			if (j==10)
				if(bufferVoltage <= m_drightValvesOutputs[j] + 0.05){
					vitalDacWrite(j-4, bufferVoltage);}
			if (j==11)
				if(bufferVoltage <= m_drightValvesOutputs[j] + 0.05){
					vitalDacWrite(j-4, bufferVoltage);}
		}
		bufferVoltage +=0.1; // Increasing the ref voltage slowly not to harm 
		Sleep(100); // Wait 100 ms at each step		
	}

	for(int s=0;s<12;s++)
	{
		m_dInitialleftValvesOutputs[s] = m_dleftValvesOutputs[s];
		m_dInitialrightValvesOutputs[s] = m_drightValvesOutputs[s];
	}

	//m_bstrError = SysAllocString(L"Initializing Both Arm!!\n");
}

void InitializeLeftValves()
{
	//m_bstrError = SysAllocString(L"Initializing Left Arm!!\n");
	double bufferVoltage=0.1;
	int i=0,j=0,k=0;

	m_dleftValvesOutputs[0]=2.3;
	m_dleftValvesOutputs[1]=1.7;
	m_dleftValvesOutputs[2]=2.0;
	m_dleftValvesOutputs[3]=2.0;
	m_dleftValvesOutputs[4] =0.0;
	m_dleftValvesOutputs[5] =2.2;
	m_dleftValvesOutputs[6] =2.4;
	m_dleftValvesOutputs[7] =0.0;
	m_dleftValvesOutputs[8]  =2.3;
	m_dleftValvesOutputs[9]  =1.7;
	m_dleftValvesOutputs[10] =1.7;
	m_dleftValvesOutputs[11] =2.3;

	for(i=0;i<25;i++) // 25x100 ms = 2.5 sec makes the muscles blow up
	{
		vitalSelectBoard(0);
		if(bufferVoltage <= m_dleftValvesOutputs[1] + 0.05)
				vitalDacWrite(1, bufferVoltage);
		if(bufferVoltage <= m_dleftValvesOutputs[2] + 0.05)
				vitalDacWrite(2, bufferVoltage);
		bufferVoltage +=0.1; // Increasing the ref voltage slowly not to harm 
		Sleep(100); // Wait 100 ms at each step		
	}
	Sleep(200);
	bufferVoltage=0.1;

	for(i=0;i<25;i++) // 25x100 ms = 2.5 sec makes the muscles blow up
	{	
		vitalSelectBoard(0);
		for(j=0;j<8;j++) // giving reference to each channel of board 0
		{	
			if(j==0)
				if(bufferVoltage <= m_dleftValvesOutputs[j] + 0.05){
					vitalDacWrite(j, bufferVoltage);}
			//if (j==1)
			//	if(bufferVoltage <= m_dleftValvesOutputs[j] + 0.05){
			//		vitalDacWrite(j, bufferVoltage);}
			//if (j==2)
			//	if(bufferVoltage <= m_dleftValvesOutputs[j] + 0.05){
			//		vitalDacWrite(j, bufferVoltage);}
			if (j==3)
				if(bufferVoltage <= m_dleftValvesOutputs[j] + 0.05){
					vitalDacWrite(j, bufferVoltage);}
			if (j==4)
				if(bufferVoltage <= m_dleftValvesOutputs[j] + 0.05){
					vitalDacWrite(j, bufferVoltage);}
			if (j==5)
				if(bufferVoltage <= m_dleftValvesOutputs[j] + 0.05){
					vitalDacWrite(j, bufferVoltage);}
			if (j==6)
				if(bufferVoltage <= m_dleftValvesOutputs[j] + 0.05){
					vitalDacWrite(j, bufferVoltage);}
			if (j==7)
				if(bufferVoltage <= m_dleftValvesOutputs[j] + 0.05){
					vitalDacWrite(j, bufferVoltage);}
		}
		vitalSelectBoard(1);
		for(j=8;j<12;j++) // giving reference to each channel of board 0
		{	
			if (j==8)
				if(bufferVoltage <= m_dleftValvesOutputs[j] + 0.05){
					vitalDacWrite(j-8, bufferVoltage);}
			if (j==9)
				if(bufferVoltage <= m_dleftValvesOutputs[j] + 0.05){
					vitalDacWrite(j-8, bufferVoltage);}
			if (j==10)
				if(bufferVoltage <= m_dleftValvesOutputs[j] + 0.05){
					vitalDacWrite(j-8, bufferVoltage);}
			if (j==11)
				if(bufferVoltage <= m_dleftValvesOutputs[j] + 0.05){
					vitalDacWrite(j-8, bufferVoltage);}
		}
		bufferVoltage +=0.1; // Increasing the ref voltage slowly not to harm 
		Sleep(100); // Wait 100 ms at each step		
	}
	for(int s=0;s<12;s++)
		m_dInitialleftValvesOutputs[s] = m_dleftValvesOutputs[s];

	vitalSelectBoard(0);
}

void InitializeRightValves()
{
	//m_bstrError = SysAllocString(L"Initializing Right Arm!!\n");
	double bufferVoltage=0.1;
	int i=0,j=0,k=0;

	m_drightValvesOutputs[0]=2.1;//2.2
	m_drightValvesOutputs[1]=1.9;//1.8
	m_drightValvesOutputs[2]=2.2;
	m_drightValvesOutputs[3]=1.8;
	m_drightValvesOutputs[4] =0.0;
	m_drightValvesOutputs[5] =2.2;//2.1
	m_drightValvesOutputs[6] =2.1;//1.9
	m_drightValvesOutputs[7] =0.0;
	m_drightValvesOutputs[8]  =2.0;
	m_drightValvesOutputs[9]  =2.0;
	m_drightValvesOutputs[10] =2.0;
	m_drightValvesOutputs[11] =2.0;

	for(i=0;i<25;i++) // 25x100 ms = 2.5 sec makes the muscles blow up
	{
		vitalSelectBoard(1);
		if(bufferVoltage <= m_drightValvesOutputs[0] + 0.05)
				vitalDacWrite(4, bufferVoltage);
		if(bufferVoltage <= m_drightValvesOutputs[2] + 0.05)
				vitalDacWrite(6, bufferVoltage);
		bufferVoltage +=0.1; // Increasing the ref voltage slowly not to harm 
		Sleep(100); // Wait 100 ms at each step		
	}
	Sleep(200);
	bufferVoltage=0.1;	
	for(i=0;i<25;i++) // 25x100 ms = 2.5 sec makes the muscles blow up
	{	
		vitalSelectBoard(1);
		for(j=0;j<4;j++) // giving reference to each channel of board 0
		{	
			//if (j==0)
			//	if(bufferVoltage <= m_drightValvesOutputs[j] + 0.05){
			//		vitalDacWrite(j+4, bufferVoltage);}
			if (j==1)
				if(bufferVoltage <= m_drightValvesOutputs[j] + 0.05){
					vitalDacWrite(j+4, bufferVoltage);}
			//if (j==2)
			//	if(bufferVoltage <= m_drightValvesOutputs[j] + 0.05){
			//		vitalDacWrite(j+4, bufferVoltage);}
			if (j==3)
				if(bufferVoltage <= m_drightValvesOutputs[j] + 0.05){
					vitalDacWrite(j+4, bufferVoltage);}
		}
		vitalSelectBoard(2);
		for(j=4;j<12;j++) // giving reference to each channel of board 0
		{	
			if(j==4)
				if(bufferVoltage <= m_drightValvesOutputs[j] + 0.05){
					vitalDacWrite(j-4, bufferVoltage);}
			if (j==5)
				if(bufferVoltage <= m_drightValvesOutputs[j] + 0.05){
					vitalDacWrite(j-4, bufferVoltage);}
			if (j==6)
				if(bufferVoltage <= m_drightValvesOutputs[j] + 0.05){
					vitalDacWrite(j-4, bufferVoltage);}
			if (j==7)
				if(bufferVoltage <= m_drightValvesOutputs[j] + 0.05){
					vitalDacWrite(j-4, bufferVoltage);}
			if (j==8)
				if(bufferVoltage <= m_drightValvesOutputs[j] + 0.05){
					vitalDacWrite(j-4, bufferVoltage);}
			if (j==9)
				if(bufferVoltage <= m_drightValvesOutputs[j] + 0.05){
					vitalDacWrite(j-4, bufferVoltage);}
			if (j==10)
				if(bufferVoltage <= m_drightValvesOutputs[j] + 0.05){
					vitalDacWrite(j-4, bufferVoltage);}
			if (j==11)
				if(bufferVoltage <= m_drightValvesOutputs[j] + 0.05){
					vitalDacWrite(j-4, bufferVoltage);}
		}

		bufferVoltage +=0.1; // Increasing the ref voltage slowly not to harm 
		Sleep(100); // Wait 100 ms at each step		
	}
	for(int s=0;s<12;s++)
		m_dInitialrightValvesOutputs[s] = m_drightValvesOutputs[s];

	vitalSelectBoard(1);
}
/****************************************************
* SetLeftArmPressures()
*
* Function writes pressure values by talking to the
* Motenc cards. Calls vitalDacWrite().
*
* We have to write 12 valve values. The first eight
* channels are on board 0, and the next 4 on board 1.
****************************************************/

void SetLeftArmPressures()
{
	int channel=0;
	
	// Select Board 0.
	vitalSelectBoard(0);

	// Write values and check for negative or too great of a pressure.
	for(channel=0;channel<8;channel++) // giving reference to each channel of board 0
	{
		if (m_dleftValvesOutputs[channel] < 0.0 )
		{			
			//m_bstrError = SysAllocString(L"negative pressure!\n");
			m_dleftValvesOutputs[channel] = 0.0;
		}
		if (m_dleftValvesOutputs[channel] > 3.6 )
		{
			m_dleftValvesOutputs[channel] = 3.6;
			//m_bstrError = SysAllocString(L"Too Maiac Pressure!!\n");
		}
		vitalDacWrite( channel, m_dleftValvesOutputs[channel] );
	}
	vitalSelectBoard(1);
	for(channel=0;channel<4;channel++) // giving reference to first 4 channel of board 1
	{
		if (m_dleftValvesOutputs[channel+8] < 0.0 ){
			//m_bstrError = SysAllocString(L"negative pressure!\n");
			m_dleftValvesOutputs[channel+8] = 0.0;
		}
		if (m_dleftValvesOutputs[channel+8] > 3.6 )
		{
			m_dleftValvesOutputs[channel+8] = 3.6;
			//m_bstrError = SysAllocString(L"Too Maiac Pressure!!\n");
		}

		vitalDacWrite( channel, m_dleftValvesOutputs[channel+8] );
	}
}

void SetRightArmPressures()
{
	int channel=0;

	vitalSelectBoard(1);
	for(channel=4;channel<8;channel++) // giving reference to each channel of board 0
	{
		if (m_drightValvesOutputs[channel-4] < 0.0 ){
			//m_bstrError = SysAllocString(L"negative pressure!\n");
			m_drightValvesOutputs[channel-4] = 0.0;
		}
		if (m_drightValvesOutputs[channel-4] > 3.6 )
		{
			m_drightValvesOutputs[channel-4] = 3.6;
			//m_bstrError = SysAllocString(L"Too Maiac Pressure!!\n");
		}
		vitalDacWrite( channel, m_drightValvesOutputs[channel-4] );
	}
	vitalSelectBoard(2);
	for(channel=0;channel<8;channel++) // giving reference to first 4 channel of board 1
	{
		if (m_drightValvesOutputs[channel+4] < 0.0 ){
			//m_bstrError = SysAllocString(L"negative pressure!\n");
			m_drightValvesOutputs[channel+4] = 0.0;
		}
		if (m_drightValvesOutputs[channel+4] > 3.6 )
		{
			m_drightValvesOutputs[channel+4] = 3.6;
			//m_bstrError = SysAllocString(L"Too Maiac Pressure!!\n");
		}
		if ( channel!=0 && channel!=3) // Not using the triceps
			vitalDacWrite( channel, m_drightValvesOutputs[channel+4] );
	}
}


/**********************************************************************
* CloseValves()
* 
**********************************************************************/
void CloseValves()
{
	double bufferVoltage=0.1;
	int i=0,j=0,k=0;

	//m_bstrError = SysAllocString(L"Closing Valves!!\n");

	for(i=0;i<36;i++) // 36x100 ms = 3.6 seconds allows the muscles to deflate.
	{		
		// Left Arm
		vitalSelectBoard(0);
		for(j=0;j<8;j++) // giving reference to each channel of board 0
		{
			if( m_dleftValvesOutputs[j]-bufferVoltage >0 )
				vitalDacWrite( j, m_dleftValvesOutputs[j]-bufferVoltage);
		}
		vitalSelectBoard(1);
		for(j=0;j<4;j++) // giving reference to first 4 channel of board 1
		{
			if( m_dleftValvesOutputs[j+8]-bufferVoltage >0 )
				vitalDacWrite( j, m_dleftValvesOutputs[j+8]-bufferVoltage);	
		}


		// For the Right Arm
		for(j=4;j<8;j++) // giving reference to first 4 channel of board 1
		{
			if( m_drightValvesOutputs[j-4]-bufferVoltage >0 )
				vitalDacWrite( j, m_drightValvesOutputs[j-4]-bufferVoltage );
		}
		vitalSelectBoard(2);
		for(j=0;j<8;j++) // giving reference to first 4 channel of board 1
		{
			if( m_drightValvesOutputs[j+4]-bufferVoltage >0 )
				vitalDacWrite( j, m_drightValvesOutputs[j+4]-bufferVoltage );
		}
		Sleep(200); // Wait 100 ms at each step
		bufferVoltage += 0.1;
	}
}

/****************************************************
* ReadLeftEncoders()
*
* Function OUTPUTS encoder values by talking to the
* Motenc cards. Calls vitalEncoderRead().
*
* Each card contains 4 enconder connections.
* The Left encoders are: all 4 channels in board 1, and
* the first 2 channels in board 2.
****************************************************/
void ReadLeftEncoders()
{
	// Select Board(0) and first 4 channels
	vitalSelectBoard(0);
	for(int channel=0;channel<4;channel++)
		vitalEncoderRead(channel, &m_dleftEncoders[channel]);

	// Switch to Board(1) and first 2 channels
	vitalSelectBoard(1);
	for(channel=0;channel<2;channel++)
		vitalEncoderRead(channel, &m_dleftEncoders[channel+4]);		// Input to index 4 and 5.

	// The encoders at positions 2 and 5, need to have negative values to reflect that particular angle. 
	m_dleftEncoders[2]*=-1;
	m_dleftEncoders[5]*=-1;				

	//ATLTRACE(_T("Enc1: %d Enc2: %d Enc3: %d Enc4: %d Enc5: %d Enc6: %d\n",m_dleftEncoders[0],m_dleftEncoders[1],m_dleftEncoders[2],m_dleftEncoders[3],m_dleftEncoders[4],m_dleftEncoders[5]));
}

/****************************************************
* ReadRightEncoders()
*
* Function OUTPUTS encoder values by talking to the
* Motenc cards. 
*
* Each card contains 4 enconder connections.
* The Right encoders are: last 2 channels in board 1, and
* the all 4 channels in board 2.
****************************************************/
void ReadRightEncoders()
{
	// Select Board(1) and select last two channels.
	vitalSelectBoard(1);
	
	//!!!First two encoders are flipped!!! (The readings show that)
	vitalEncoderRead(2, &m_drightEncoders[1]);
	vitalEncoderRead(3, &m_drightEncoders[0]);

	// Switch to board 2 and read from all 4 channels.
	vitalSelectBoard(2);
	for(int channel=0; channel<4; channel++)
		vitalEncoderRead(channel, &m_drightEncoders[channel+2]);	// Input into index items: 2-5.

	// The encoders at positions 2 and 5, need to have negative values to reflect that particular angle. 
	m_drightEncoders[1]*=-1;
	m_drightEncoders[2]*=-1;

	//ATLTRACE(_T("Enc1: %d Enc2: %d Enc3: %d Enc4: %d Enc5: %d Enc6: %d\n",m_drightEncoders[0],m_drightEncoders[1],m_drightEncoders[2],m_drightEncoders[3],m_drightEncoders[4],m_drightEncoders[5]));
}

void ResetLeftEncoders()
{
	vitalSelectBoard(0);
	for(int channel=0;channel<4;channel++)
		vitalResetCounter(channel);
	vitalSelectBoard(1);
	for(channel=0;channel<2;channel++)
		vitalResetCounter(channel);
}

void ResetRightEncoders()
{
	vitalSelectBoard(1);
	for(int channel=2;channel<4;channel++)
		vitalResetCounter(channel);
	vitalSelectBoard(2);
	for(channel=0;channel<4;channel++)
		vitalResetCounter(channel);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// leftLogicalAngles()
// This routine transforms encoder values to degrees, and then adjusts them to fit the DH paramters 
// for a PUMA model.
////////////////////////////////////////////////////////////////////////////////////////////////////
void leftLogicalAngles()
{
	// Encoder Gain - values have not changed from IMA 1.0

	double m_dEncoderGain[NUM_AXES];
	m_dEncoderGain[0]	= -5092.0;
	m_dEncoderGain[1]	=  5092.0;
	m_dEncoderGain[2]	=  4244.0;
	m_dEncoderGain[3]	= -4244.0;
	m_dEncoderGain[4]	=   636.6;
	m_dEncoderGain[5]	=  -636.6;

	// DesiredAngle  =       EncoderPosition / Encoder Resolution 
	m_dleftAngles[0] =		   ( (double)  m_dleftEncoders[0] / m_dEncoderGain[0] * RADS2DEGREE );
	m_dleftAngles[1] =		   ( (double) -m_dleftEncoders[1] / m_dEncoderGain[1] * RADS2DEGREE ) + 90;
	m_dleftAngles[2] =  (0.5 * ( (double)  m_dleftEncoders[3] / m_dEncoderGain[2] - (double) m_dleftEncoders[2] / m_dEncoderGain[2] ) * RADS2DEGREE ) -180;
	m_dleftAngles[3] =   0.5 * ( (double) -m_dleftEncoders[3] / m_dEncoderGain[3] - (double) m_dleftEncoders[2] / m_dEncoderGain[2] ) * RADS2DEGREE;
	m_dleftAngles[4] =   0.5 * ( (double) -m_dleftEncoders[4] / m_dEncoderGain[4] - (double) m_dleftEncoders[5] / m_dEncoderGain[5] ) * RADS2DEGREE;
	m_dleftAngles[5] =		   ( (double)  m_dleftEncoders[4] / m_dEncoderGain[5] + (double) m_dleftEncoders[5] / m_dEncoderGain[5] ) * RADS2DEGREE;

	//ATLTRACE(_T("ang0: %.2f ang1: %.2f ang2: %.2f ang3: %.2f ang4: %.2f ang5: %.2f\n",m_dleftAngles[0],m_dleftAngles[1],m_dleftAngles[2],m_dleftAngles[3],m_dleftAngles[4],m_dleftAngles[5]));
}

void rightLogicalAngles()
{
	double m_dEncoderGain[NUM_AXES];
	m_dEncoderGain[0]	= -5092.0;
	m_dEncoderGain[1]	=  5092.0;
	m_dEncoderGain[2]	=  4244.0;
	m_dEncoderGain[3]	= -4244.0;
	m_dEncoderGain[4]	=   636.6;
	m_dEncoderGain[5]	=  -636.6;

	m_drightAngles[0] =   (double)  m_drightEncoders[0] / m_dEncoderGain[0]		* RADS2DEGREE;
	m_drightAngles[1] =   (double) -m_drightEncoders[1] /  m_dEncoderGain[0]		* RADS2DEGREE + 90;
	m_drightAngles[2] =  ((double) -m_drightEncoders[3] / -4244.0	/2	* RADS2DEGREE + (double) m_drightEncoders[2] / 4244	/2	* RADS2DEGREE) -180 ;
	m_drightAngles[3] =  ((double) -m_drightEncoders[3] / -4244.0		* RADS2DEGREE - (double) m_drightEncoders[2] / 4244		* RADS2DEGREE ) ;
	m_drightAngles[5] =  ((double) -m_drightEncoders[4] /   636.6	/2	* RADS2DEGREE - (double) m_drightEncoders[5] /  636.6 /2	* RADS2DEGREE);
	// Opposite of Left Arm 4-5 changed and 4 multiplied by -1
	m_drightAngles[4]=  ((double) m_drightEncoders[4]	/ - 636.6		* RADS2DEGREE + (double) m_drightEncoders[5] /  636.6		* RADS2DEGREE);

	//ATLTRACE(_T("ang0: %.2f ang1: %.2f ang2: %.2f ang3: %.2f ang4: %.2f ang5: %.2f\n",m_drightAngles[0],m_drightAngles[1],m_drightAngles[2],m_drightAngles[3],m_drightAngles[4],m_drightAngles[5]));
}

void ReadLeftPressure()
{
	double leftPressures[4]={0};

	//Filtering
	for(int i=0;i<5;i++)
	{
		if( i == 0 ){
			vitalSelectBoard(0);
			vitalReadAnalogInputs( 0, leftPressures);
			for(int channel=0; channel<4;channel++)
				m_dleftValvesInputs[channel]= leftPressures[channel];

			vitalReadAnalogInputs( 1, leftPressures);
			for(channel=4;channel<8;channel++)
				m_dleftValvesInputs[channel]= leftPressures[channel-4];

			vitalSelectBoard(1);
			vitalReadAnalogInputs( 0, leftPressures);
			for(channel=8;channel<12;channel++)
				m_dleftValvesInputs[channel]= leftPressures[channel-8];

			Sleep(1);
		}else{
			vitalSelectBoard(0);
			vitalReadAnalogInputs( 0, leftPressures);
			for(int channel=0; channel<4;channel++)
				m_dleftValvesInputs[channel]+= leftPressures[channel];

			vitalReadAnalogInputs( 1, leftPressures);
			for(channel=4;channel<8;channel++)
				m_dleftValvesInputs[channel]+= leftPressures[channel-4];

			vitalSelectBoard(1);
			vitalReadAnalogInputs( 0, leftPressures);
			for(channel=8;channel<12;channel++)
				m_dleftValvesInputs[channel]+= leftPressures[channel-8];

			Sleep(1);
		}
	}

	for(i=0;i<12;i++)
		m_dleftValvesInputs[i]/=5;

	// there is a problem with the 10th muscle
	m_dleftValvesInputs[9]-=100;

	vitalSelectBoard(0);

}

void InitializeCards()
{
	//m_bstrError = SysAllocString(L"Initializing Cards!!\n");
	int numb =0;
	//Initializing the Cards
	if( numb=vitalInit() )
		numb=0;//dummy to then decomment mbstr
		//m_bstrError = SysAllocString(L"%d board(s) detected\n",numb);
	else
		numb=0;
		//m_bstrError = SysAllocString(L "Error initializing WinMotenc library\n" );
}


#endif