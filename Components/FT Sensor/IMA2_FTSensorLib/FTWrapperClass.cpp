// FTWrapperClass.cpp: implementation of the CFTWrapperClass class.
//
// Wrapper class for ATI Intelligent Multi-axis force/torque sensor
// See manual for more details: O:\Documentation\System Description\Force-Torque Sensor\Force Torque Controller Manual Omega.pdf
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FTWrapperClass.h"
#include "stdio.h"
#include <assert.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CFTWrapperClass::CFTWrapperClass()
{
	int i;

	for(i=0;i<NUM_AXES;i++)
	{
		m_pfCurrentFT[i]	=    0.0f;
		m_pfCurrentFrame[i]	=    0.0f;

		m_pfMaxFT[i]		=-9999.0f;		// see the manual under Sensor Peaks
		m_pfMinFT[i]		= 9999.0f;		// see previous comment
	}

	m_bPeaksEnabled			= FALSE;
	m_bThread				= FALSE;
	m_bTerminateSensorThread= FALSE;

	m_nAverageMovingLength	= 0;
	m_nSampleWaitTime		= 50;

	m_hSensorThread			= NULL;
	m_pPort					= NULL;

	//pfFT					= new double[NUM_AXES];
}

// Contains thread
CFTWrapperClass::CFTWrapperClass(char * sCommName, BOOL bInit, BOOL bThread, int nWait)
{
	int i;
	ATLTRACE("************* Creating Sensor Object************\n");

	for(i=0;i<NUM_AXES;i++) 
	{
		m_pfCurrentFT[i]		=   0.0f;
		m_pfCurrentFrame[i]		=   0.0f;

		m_pfMaxFT[i]			=-9999.0f;	// see the manual under Sensor Peaks
		m_pfMinFT[i]			= 9999.0f;	// see previous comment
	}

	m_bPeaksEnabled				= FALSE;
	m_bTerminateSensorThread	= FALSE;

	m_nAverageMovingLength		= 0;
	m_nSampleWaitTime			= nWait;

	ATLTRACE("********** Creating commport object**********\n");
	m_pPort						= new CCommPort(sCommName, 38400);

	if(bInit) 
		InitSensor();

	m_bThreaded					= bThread;
}

// Includes pfFrame info.
CFTWrapperClass::CFTWrapperClass(char * sCommName, double pfFrame[NUM_AXES], BOOL bInit, BOOL bThread, int nWait)
{
	int i;

	for(i=0;i<NUM_AXES;i++) 
	{
		m_pfCurrentFT[i]			= 0.0f;
		m_pfCurrentFrame[i]			= pfFrame[i];

		m_pfMaxFT[i]				=-9999.0f;	// see the manual under Sensor Peaks
		m_pfMinFT[i]				= 9999.0f;	// see previous comment
	}

	m_bPeaksEnabled					= FALSE;
	m_bTerminateSensorThread		= FALSE;
	
	m_nAverageMovingLength			= 0;
	m_nSampleWaitTime				= nWait;	// Defined in the declaration in the .h file

	ATLTRACE("********** Creating commport object**********\n");
	m_pPort							= new CCommPort(sCommName, 38400);

	if(bInit) 
		InitSensor();

	m_bThreaded						= bThread;
}


CFTWrapperClass::~CFTWrapperClass()
{
	// Signal other document threads to exit now...
	m_bTerminateSensorThread = TRUE;

	if(m_pPort!=NULL) 
		delete m_pPort;
}

/***************************************************************/
/* SetFrame(double frame_coordinates[6])
/* Function called by: CFTSensorCom::Initialization();
/*
/* 1) Sets the frame to TF0, which is the standard frame.
/* 2) Creates the newly designed frame.
/* 3) Selects the newly created frame.
/* 4) Create a local copy
/***************************************************************/
void CFTWrapperClass::SetFrame(double pfFrame[NUM_AXES]){	

	char szCmd[100], szRet[SZLen];
	int i;

	// 1) Set current frame to 0 (origin)
	// TF 0. (For more info look at p. 44 in manual)
	sprintf(szCmd,"TF 0\r");	// Save string in szCmd	
	SendCommand(szCmd,szRet);

	// 2) Construct the new frame. Look at p. 46
	// (TC d,s, X,Y,Z, R,P,Y)
	//  TC: command for construction of tool frame
	//   d: parameter to specify tool frame
	//   s: string s, is a one-to-six character name assigned to tool frame
	// xyz: translation distances along each of the axes
	// RPY: represent 1/10 of a degree for rotation about X-, Y- and Z-axis respectively
	// ie: TC 1,ISAC,0,0,0,-90,0,-90

	// Copy command to szCmd
	sprintf(
		szCmd,
		"TC 1, f1, %d, %d, %d, %d, %d, %d \r",						
		(int)pfFrame[0],(int)pfFrame[1],(int)pfFrame[2],
		(int)pfFrame[3],(int)pfFrame[4],(int)pfFrame[5]
		);
	// Send Command
	SendCommand(szCmd,szRet);

	// 3) Switch to new frame
	// Sometime systems gets stuck, so call TF 1, TF 0, TF 1.
	// TF 1
	sprintf(szCmd,"TF 1\r");	
	SendCommand(szCmd,szRet);
	// TF 0
	sprintf(szCmd,"TF 0\r");	
	SendCommand(szCmd,szRet);	
	// TF 1
	sprintf(szCmd,"TF 1\r");	
	SendCommand(szCmd,szRet);


	// 4) Copy frame data to the private member variable
	for(i=0;i<NUM_AXES;i++)
		m_pfCurrentFrame[i]=pfFrame[i];
}


void CFTWrapperClass::GetFrame(double pfFrame[NUM_AXES]){	// Fx,Fy,Fz,Tx,Ty,Tz,
	int i;

	for(i=0;i<NUM_AXES;i++)
		pfFrame[i]=m_pfCurrentFrame[i];
}

void CFTWrapperClass::GetFT(double pfFT[NUM_AXES]){			// Fx,Fy,Fz,Tx,Ty,Tz,

	int i;

	if(!m_bThread) SampleFT(m_pfCurrentFT);

	for(i=0;i<NUM_AXES;i++)
		pfFT[i]=m_pfCurrentFT[i];

}

BOOL CFTWrapperClass::GetFTPeaks(double pfFTMax[NUM_AXES],double pfFTMin[NUM_AXES]){	// Returns status of peak enabling
	int i;

	if(!m_bThread) SampleFTPeaks(m_pfMaxFT,m_pfMinFT);

	for(i=0;i<NUM_AXES;i++) {
		pfFTMax[i]=m_pfMaxFT[i];
		pfFTMin[i]=m_pfMinFT[i];
	}

	return m_bPeaksEnabled;

}

/***********************************************************************************************
Page 36
The F/T Controller has the capability of storing three different bias (zero) readings.
Biasing is useful for eliminating the effects of gravity (tool weight) or other forces acting
on the end-effector. When a sensor bias is performed, the Controller will read the forces
and torques currently acting on the sensor and use these readings as a reference for future
readings. Future readings will have this reference subtracted from them before they are
transmitted. 

Note:
When biasing, ensure the force and torque readings are steady-state. Biasing while
the transducer is vibrating, accelerating, or decelerating can provide a poor
reference for your application.

- SB Sensor Bias
Performs a sensor bias. Bias readings are stored in a LIFO (last-in-first-out) buffer. If an
SB command is issued, the present bias reading (if any) is stored in the buffer. If an SU
(Sensor Unbias) command is then issued, the previous bias reading is removed from the
buffer and used as the current bias reading. Up to three levels of bias readings may be
stored in this manner.
If an SB command is issued when the bias buffer is full, the bias replaces the most recent
bias. This leaves the first two biases undisturbed.
**************************************************************************************************/
void CFTWrapperClass::BiasSensor(BOOL bBias){				// True for biasing; false for unbiasing

	char szCmd[100], szRet[SZLen];

	if(bBias) 
	{
		sprintf(szCmd,"SB\r");
		SendCommand(szCmd,szRet);
	}

	else 
	{
		// Unbias sensor. Returns to last bias reading.
		sprintf(szCmd,"SU\r");
		SendCommand(szCmd,szRet);
	}
}

/**************************************************************************************************
Page 36.
(SP b) Sensor Peaks

b=1: 
Enable collection of force/torque maximum and minimum values.

b=0: 
Disable collection of force/torque maximum and minimum values; default.
When enabled maximum and minimum F/T values are collected until reset or the
command is disabled. The maximum and minimum values collected are kept in a buffer
until they are cleared by the SC command or a system reset occurs. Use the QP command
to read the values stored in this buffer. You can examine this buffer with SP enabled or
disabled.
**************************************************************************************************/
void CFTWrapperClass::EnablePeaks(BOOL bPeak){			//true for enabling, false for diabling

	char szCmd[100], szRet[SZLen];

	if(bPeak) {
		// collect peak info
		sprintf(szCmd,"SP 1\r\n");
		SendCommand(szCmd,szRet);
	}
	else {
		// don't collect peak info
		sprintf(szCmd,"SP 0\r");
		SendCommand(szCmd,szRet);
	}

	m_bPeaksEnabled=bPeak;
}

/**************************************************************************************************
Page 37.
SC Sensor peaks Cleared
Loads -9999 in the maximum values and 9999 in the minimum values. This command is
executed on system reset. If the sensor peak monitoring is enabled and the SC command is
issued, then the buffer will be cleared and new minimum and maximum values will be
collected (issuing the SC command does not disable peak monitoring).
I.e. before you call this command you more than likely will want to disable peak monitoring  SP 0
**************************************************************************************************/
BOOL CFTWrapperClass::ClearPeaks(){					//returns status of peak enabling

	char szCmd[100], szRet[SZLen];

	// clear peak info
	sprintf(szCmd,"SC\r");
	SendCommand(szCmd,szRet);

	return m_bPeaksEnabled;
}

/**************************************************************************************************
Page 38.
(SA d) Sensor Averaging
Performs a moving average of the last d samples of sensor data. This can be useful to
reduce the effects of mechanical vibrations and inertia. The parameter d must be 0, 2, 4, 8,
16, 32, 64, or 128. A value of 0 disables the averaging function.
**************************************************************************************************/
BOOL CFTWrapperClass::SetAverageLength(int nLen){				//nLen must be element of {0,2,4,8,16}, returns old value;

	char szCmd[100], szRet[SZLen];

	// If nLen is not equal to any of the allowed values, then return error.
	if(nLen!=0 && nLen!=2 && nLen!=4 && nLen!=8 && nLen!=16 && nLen!=32 && nLen!=64 && nLen!=128)
		return FALSE;

	sprintf(szCmd,"SA %d\r",nLen);
	SendCommand(szCmd,szRet);

	return TRUE;
}

// Returns length of moving average
int CFTWrapperClass::GetAverageLength(){return m_nAverageMovingLength; }

///////////////////////////////////////////////////////////////
// Sample the FT sensor for data on Fx, Fy, Fz, Tx, Ty, Tz
///////////////////////////////////////////////////////////////
int CFTWrapperClass::SampleFT(double* pfFT){		// queries sensor

	char	szCmd[1000], szRet[2000], a[10];
	int		i,pnFD[7];

	// QR - Query data Record
	// Request output of one record of data in the preselected type and mode.
	sprintf(szCmd,"QR\r\n");	// Stores the 2nd argument in the string array.
	ATLTRACE("\t \t ************* Just Before Send Command ************* \n");
	SendCommand(szCmd,szRet);	// Looking for data readings in szRet

	// Read out the information
	if( sscanf( 
			szRet,																							// Store data using commas as delimeters
			"%s %d, %d, %d, %d, %d, %d, %d",																// The first value is trash returned in hyperterminal, disregard
			a, /*****/&pnFD[6]/*****/, &pnFD[0], &pnFD[1], &pnFD[2], &pnFD[3], &pnFD[4], &pnFD[5]) != 8)	// string reads the commands; ints read FTdata 
	{
		MessageBox(NULL, "Did not read data appropriately", "SampleFT Error", MB_OK);	
	}
	
	for (i=0;i<NUM_AXES;i++)
		pfFT[i] = pnFD[i];

	return 0;
}

///////////////////////////////////////////////////////////////
// Sample the FT peaks for data on Fx, Fy, Fz, Tx, Ty, Tz
///////////////////////////////////////////////////////////////
void CFTWrapperClass::SampleFTPeaks(double pfMaxFT[NUM_AXES], double pfMinFT[NUM_AXES]){		// queries sensor
	
	char	szCmd[1000], szRet[2000];
	char	echo[10], strmin[10], strmax[10];
	int		i,pnFTPeaks[NUM_AXES*2];

	// QP Query Peaks
	// Request output of maximum and minimum values of resolved force/torque data collected
	// from SP command. The maximum values are preloaded with -9999 and the minimum
	// values are preloaded with 9999. These preloaded values will be seen if the SP command
	// was never enabled, after a hardware or software reset or after the SC command was
	// issued. The QP command will not affect the collection of the maximum or minimum
	// values while the SP command is enabled.	sprintf(szCmd,"QP\r");
	sprintf(szCmd,"QP\r\n");
	SendCommand(szCmd,szRet);

	sscanf( 
		szRet,																							/* stored data */
		"%s %s %d, %d, %d, %d, %d, %d %s %d, %d, %d, %d ,%d, %d",										/* min and its six values */
		echo,																							/* echo */
		strmin, &pnFTPeaks[0],&pnFTPeaks[1],&pnFTPeaks[2],&pnFTPeaks[3],&pnFTPeaks[4],&pnFTPeaks[5],	/* max and its six values */
		strmax, &pnFTPeaks[6],&pnFTPeaks[7],&pnFTPeaks[8],&pnFTPeaks[9],&pnFTPeaks[10],&pnFTPeaks[11]);	

	for(i=0;i<NUM_AXES;i++)
	{
		pfMinFT[i]=pnFTPeaks[i];
		pfMaxFT[i]=pnFTPeaks[i+NUM_AXES];
	}
}

/****************************************************************************************/
/* SendCommand( Command as String, Length)
/* 
/* Most basic and important function. Used by all other calls to send commands & receive response.
/* Input:	szCmd (arbitrary command)
/* Output:	szRet (system response)
/*
/* Sends commands as in a terminal.
/* The sensor echoes characters as they are sent.  I am assuming they will be buffered.
/* Write the full command string and then,
/* Read the return buffer until an ">" (the prompt) appears.
/* The system routinely returns "<ACK>", if command was successful or prints an error message.
/****************************************************************************************/
BOOL CFTWrapperClass::SendCommand(/*[in]*/char * szCmd, /*[in]*/char * szRet)
{	
	// Local variables
	char	cData;			// Will hold terminal response
	int		i		= 0;
	int		count	= 0;

	// 1) Send input command string and its size.
	m_pPort->WriteComm(szCmd, strlen(szCmd));

	// 2) Print message to dump to help with debugging
	ATLTRACE("\t \t ************* Cdata Start *************\n");

	// 3) Read the buffer response into cData. 
	// Read 1 byte at-a-time.
	// Continue to read so as long as a carriage return is not seen.
	while(cData !='>')		// This char is represented by decimal value 62.
	{
		// Read one byte of data and store it in cData
		DWORD bytesread = m_pPort->ReadComm(&cData,1);
		
		if(cData!=6)			// supposed to be 6...
			szRet[i++] = cData;	// 6 is the number that represents <ACK> ASCII Command. 
								// The screen will display a spade symbol twice.
								// I.e. pg. 28 of FT Manual. 
								// This is the characteristic return of characters from the FT sensor.
								// Store each byte of data into szRet.
		count++;

		// Stop the program if a carrot character does not show up.
		// There is a bad connection.
/*
		 if( count == 71 )		// upper case G
		 {
			 assert( count < 67 );	// Is activated if false and stops the program
			 break;
		 }

		assert( count < 71 );
		assert( i < 71 );
*/	
	}

	ATLTRACE("\t \t ************* Cdata Complete %d *************\n",count);
	szRet[i]=0;

	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// Intialize the sizes of the command and answer to 20 chars and 2000
///////////////////////////////////////////////////////////////////////
void CFTWrapperClass::InitSensor() {
	
	char szCmd[20], szRet[SZLen];				

	// Warm reset: issued when ctrl-W is pressed.
	// Equivalent to:
	szCmd[0] = 23;		
	SendCommand(szCmd,szRet);

	// Actually, should do this later, when arm is still
	// set bias
//	BiasSensor(TRUE);
	
	// Set the current frame
	SetFrame(m_pfCurrentFrame);

	// Set the average moving length average
	SetAverageLength(m_nAverageMovingLength);

	// Set peak collection
	EnablePeaks(m_bPeaksEnabled);

}

/******************************************************
/* Sets the reading of force-torque data to pounds.
******************************************************/
int CFTWrapperClass::SetForceFormat()
{
	char	szCmd[1000], szRet[2000];
	int		retVal;
	// CD R
	// Setup communication for Resolved force/torque data output (Default).
	sprintf(szCmd,"CD R\r\n");
	retVal = SendCommand(szCmd,szRet);

	return retVal;

}
