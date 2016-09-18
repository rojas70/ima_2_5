//
//

// CFTSensor implementation
// Wrapper class for ATI Intelligent Multi-axis force/torque sensor
// see manual for more details

#include "stdafx.h"
#include "FTSensor.h"
#include "commport.h"
#include "stdio.h"
#include <assert.h>

#define SZLen 2000

// Constructor 1
CFTSensor::CFTSensor(){

	int i;

	// initialize some values
	for(i=0;i<6;i++) {

		m_pfCurrentFT[i]=0.0f;
		m_pfCurrentFrame[i]=0.0f;

		m_pfMaxFT[i]=-9999.0f;	// see the manual under Sensor Peaks
		m_pfMinFT[i]=9999.0f;	// see previous comment
	}

	m_bPeaksEnabled=FALSE;
	m_nAveLen=0;

	m_nSampleWaitTime=50;
	m_bThread=FALSE;
	m_bTerminateSensorThread=FALSE;
	m_hSensorThread=NULL;

	m_pPort=new CCommPort("\\COM1", 38400);
}

CFTSensor::CFTSensor(char * sCommName, BOOL bInit, BOOL bThread, int nWait){

	int i;
	ATLTRACE("************* Creating Sensor Object\n");

	// initialize some values
	for(i=0;i<6;i++) {

		m_pfCurrentFT[i]=0.0f;
		m_pfCurrentFrame[i]=0.0f;

		m_pfMaxFT[i]=-9999.0f;	// see the manual under Sensor Peaks
		m_pfMinFT[i]=9999.0f;	// see previous comment

	}

	m_bPeaksEnabled=FALSE;
	m_nAveLen=0;

	m_nSampleWaitTime=nWait;
	m_bTerminateSensorThread=FALSE;

	ATLTRACE("**************** Creating commport object\n");

	m_pPort=new CCommPort(sCommName, 38400);

	if(bInit) InitSensor();

	m_bThreaded=bThread;

	
}

CFTSensor::CFTSensor(char * sCommName, double pfFrame[6], BOOL bInit, BOOL bThread, int nWait){

	int i;

	// initialize some values
	for(i=0;i<6;i++) {

		m_pfCurrentFT[i]=0.0f;
		m_pfCurrentFrame[i]=pfFrame[i];

		m_pfMaxFT[i]=-9999.0f;	// see the manual under Sensor Peaks
		m_pfMinFT[i]=9999.0f;	// see previous comment

	}

	m_bPeaksEnabled=FALSE;
	m_nAveLen=0;

	m_nSampleWaitTime=nWait;
	m_bTerminateSensorThread=FALSE;

	m_pPort=new CCommPort(sCommName, 38400);

	if(bInit) InitSensor();

	m_bThreaded=bThread;

}

CFTSensor::~CFTSensor(){
	// Signal other document threads to exit now...
	m_bTerminateSensorThread = TRUE;

	if(m_pPort!=NULL) delete m_pPort;
}

/////////////////////////////////////////////////////////////////
// This function creates a customized axis frame. 
// Mainly, one provides the translation for the force axes,
// and the rotation for the torque axes. Look at p. 46 of the 
// manual for more information.
// Inputs:	pfFrame[0] = Translation in X
//			pfFrame[1] = Translation in Y
//			pfFrame[2] = Translation in Z
//			pfFrame[3] = Rotation in X
//			pfFrame[4] = Rotation in Y
//			pfFrame[5] = Rotation in Z
/////////////////////////////////////////////////////////////////
void CFTSensor::SetFrame(double pfFrame[6]){	

	char szCmd[100], szRet[SZLen];
	int i;
	// Customize frame 0 
	// First select tool frame 0, the default frame
	sprintf(szCmd,"TF 0\r");	// write string to parameter
	SendCommand(szCmd,szRet);

	// construct the new frame
	// TC d,s,x,y,z,u,b,o
	sprintf(
		szCmd,
		"TC 1, GenerateFrame1, %d, %d, %d, %d, %d, %d \r",
		(int)pfFrame[0],(int)pfFrame[1],(int)pfFrame[2],
		(int)pfFrame[3],(int)pfFrame[4],(int)pfFrame[5]);

	SendCommand(szCmd,szRet);

	// switch to new frame
	// TF 1
	sprintf(szCmd,"TF 1\r");	
	SendCommand(szCmd,szRet);

	//copy frame data to member variables
	for(i=0;i<6;i++)
		m_pfCurrentFrame[i]=pfFrame[i];
}

void CFTSensor::GetFrame(double pfFrame[6]){	//x,y,z,?,?,?

	int i;

	for(i=0;i<6;i++)
		pfFrame[i]=m_pfCurrentFrame[i];

}

void CFTSensor::GetFT(double pfFT[6]){			//Fx,Fy,Fz,Tx,Ty,Tz,

	int i;

	if(!m_bThread) SampleFT(m_pfCurrentFT);

	for(i=0;i<6;i++)
		pfFT[i]=m_pfCurrentFT[i];

}

BOOL CFTSensor::GetFTPeaks(double pfFTMax[6],double pfFTMin[6]){	//returns status of peak enabling
	int i;

	if(!m_bThread) SampleFTPeaks(m_pfMaxFT,m_pfMinFT);

	for(i=0;i<6;i++) {
		pfFTMax[i]=m_pfMaxFT[i];
		pfFTMin[i]=m_pfMinFT[i];
	}

	return m_bPeaksEnabled;

}

void CFTSensor::BiasSensor(BOOL bBias){				//true for biasing; false for unbiasing

	char szCmd[100], szRet[SZLen];

	if(bBias) {

		// bias sensor
		sprintf(szCmd,"SB\r");
		SendCommand(szCmd,szRet);

	}
	else {

		// unbias sensor (returns to last bias reading)
		sprintf(szCmd,"SU\r");
		SendCommand(szCmd,szRet);

	}
}

void CFTSensor::EnablePeaks(BOOL bPeak){			//true for enabling, false for diabling

	char szCmd[100], szRet[SZLen];

	if(bPeak) {

		// collect peak info
		sprintf(szCmd,"SP 1\r");
		SendCommand(szCmd,szRet);

	}
	else {

		// don't collect peak info
		sprintf(szCmd,"SP 0\r");
		SendCommand(szCmd,szRet);

	}


	m_bPeaksEnabled=bPeak;
}

BOOL CFTSensor::ClearPeaks(){					//returns status of peak enabling

	char szCmd[100], szRet[SZLen];

	// clear peak info
	sprintf(szCmd,"SC\r");
	SendCommand(szCmd,szRet);

	return m_bPeaksEnabled;


}

BOOL CFTSensor::SetAveLen(int nLen){				//nLen must be element of {0,2,4,8,16}, returns old value;

	char szCmd[100], szRet[SZLen];

	if(nLen!=0 && nLen!=2 && nLen!=4 && nLen!=8 && nLen!=16)
		return FALSE;

	sprintf(szCmd,"SA %d\r",nLen);
	SendCommand(szCmd,szRet);

	return TRUE;
}

int CFTSensor::GetAveLen(){					//returns length of moving average

	return m_nAveLen;
}

int CFTSensor::SampleFT(double pfFT[6]){		// queries sensor

	char szCmd[1000], szRet[2000];
	char a,b,c,d,e;
	int error, i;
	int pnFD[6];

	error = 0;

	sprintf(szCmd,"QR\r");
	ATLTRACE("\t \t ************* Just Before Send Command ************* \n");
	
	SendCommand(szCmd,szRet);
	sscanf( szRet, "%c%c%c%c%c,   %d,   %d,   %d,   %d,   %d,   %d",
		&a,&b,&c,&d,&e,&pnFD[0],&pnFD[1],&pnFD[2],&pnFD[3],&pnFD[4],&pnFD[5]);
		
	for(i=0;i<6;i++)
		pfFT[i]=(double)pnFD[i];


	return error;
}

void CFTSensor::SampleFTPeaks(double pfMaxFT[6], double pfMinFT[6]){		// queries sensor
	char szCmd[1000], szRet[2000];

	sprintf(szCmd,"QP\r");
	SendCommand(szCmd,szRet);

	sscanf( szRet, "%f, %f, %f, %f, %f, %f, %f, %f, %f, %f ,%f, %f", 
		&pfMaxFT[0],&pfMaxFT[1],&pfMaxFT[2],&pfMaxFT[3],&pfMaxFT[4],&pfMaxFT[5],
		&pfMinFT[0],&pfMinFT[1],&pfMinFT[2],&pfMinFT[3],&pfMinFT[4],&pfMinFT[5]);	

}

// The sensor echoes characters as they are sent.  I am assuming they will be buffered.
// So my plan is to write the whole Cmd string, then read the return buffer until an 
// '>' (the prompt) is encountered, stripping out "Acks"

BOOL CFTSensor::SendCommand(char * szCmd, char * szRet){	// for talking to sensor

	char cData;
	int i=0;
	int count=0;
	bool eflag = true;


	// send Cmd string
	m_pPort->WriteComm(szCmd, sizeof(szCmd));

//	do {
//		
//		m_pPort->ReadComm(&cData,1);
//		count++;
//		if(cData!=6) 
//			szRet[i++] = cData;	//DANGER!  szRet better have enough room
//		assert( count < 1200 );
//
//	} while(cData!='>');
	// read until sensor prompt received


	ATLTRACE("\t \t ************* Cdata Start \n");
//	while(eflag)
//	{
//		if(cData != '>')
//			eflag = true;
//		else 
//			eflag = false;
	while(cData!='>')
	{
		m_pPort->ReadComm(&cData,1);
	//	ATLTRACE("\t \t ************* Cdata Start Complete %d \n",count);
		count++;
		if(cData!=6) 
			szRet[i++] = cData;	//DANGER!  szRet better have enough room
	//	Sleep(0);  // small pause to let the system catch up
		
		 if( count == 71 )
		 {
			 assert( count < 67 );
			 break;
		 }

		assert( count < 71 );
		assert( i < 71 );

	}

	ATLTRACE("\t \t ************* Cdata Complete %d \n",count);
	szRet[i]=0;

	return TRUE;
	
}

void CFTSensor::InitSensor() {
	char szCmd[20], szRet[SZLen];

	// warm reset
	szCmd[0]=23;		//ctrl-W
	SendCommand(szCmd,szRet);

	// Actually, should do this later, when arm is still
	// set bias
//	BiasSensor(TRUE);
	
	// set frame
	SetFrame(m_pfCurrentFrame);

	// set average
	SetAveLen(m_nAveLen);

	// set peak collection
	EnablePeaks(m_bPeaksEnabled);

}
