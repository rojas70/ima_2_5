#ifndef _NeuralNetworkWholeSystemFunctions_h
#define _NeuralNetworkWholeSystemFunctions_h

#include <windows.h>
#include <windef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <stdarg.h>	
#include <TIME.H>
#include<IOSTREAM>
#include <winbase.h>

#include"Headers\3dsLoadFunctions.h"
#include"Headers\GLWindowFunctions.h"

#include"Headers\driver.h"
#include"Headers\MotorFunctions.h"
#include"Headers\AnalogInputFunctions.h"
#include"Headers\AnalogOutputFunctions.h"
#include"Headers\TrainANNET.h"
#include"Headers\TrainUpperLink.h"
#include"Headers\TrainDoubleLink.h"
#include"Headers\TrainPONNET.h"

#define PI 3.141592653589

extern long lCounter[6];
extern WORD wSwitch[6],wEmgc;
extern clock_t startTime,stopTime,clTime;
extern float AO[4];
extern float fMotorVoltage[3];
extern float AverageAnalogInputs[12];

void CreateSimultionFile();
void ErrorLowMemberShipFunction(float*,float*,float*,float*,float *output);
void ErrorMediumMemberShipFunction(float*,float*,float*,float*,float *output);
void ErrorHighMemberShipFunction(float*,float*,float*,float*,float *output);
void ErrorVeryHighMemberShipFunction(float*,float*,float*,float *output);
void ErrorVeryLowMemberShipFunction(float*,float*,float*,float *output);
void InferenceRule1Function(float*,float *output);
void InferenceRule2Function(float*,float *output);
void InferenceRule3Function(float*,float *output);
void InferenceRule4Function(float*,float *output);
void InferenceRule5Function(float*,float *output);
void AlphaHighDefuzzificationFunction(float*,float*,float*,float *output1,float *output2);
void AlphaMediumDefuzzificationFunction(float*,float*,float*,float *output1,float *output2);
void AlphaLowDefuzzificationFunction(float*,float*,float*,float *output1,float *output2);
void AlphaVeryLowDefuzzificationFunction(float*,float*,float*,float *output1,float *output2);
void AlphaVeryHighDefuzzificationFunction(float*,float*,float*,float *output1,float *output2);

void _stdcall Timer_ISR_Function(EP_LIOINT *pstINTSource)
{
	//if (pstINTSource->TIMER)//  whether trigger signal from timer or not
	//	nTimerCount++;
		printf("erdem timer : %d  %d",nTimerCount,pstINTSource->TIMER);
}

void NeuralTrainTrajectoryALLSystem()
{
	CTrainDD NeuralControlDD;NeuralControlDD.Allocator();
	CTrainUP NeuralControlUP;NeuralControlUP.Allocator();
	CTrainANNET Rubbertuator1(1);Rubbertuator1.Allocator();
	CTrainANNET Rubbertuator2(2);Rubbertuator2.Allocator();
	CTrainANNET Rubbertuator3(3);Rubbertuator3.Allocator();
	CTrainANNET Rubbertuator4(4);Rubbertuator4.Allocator();
	float sillyAdress1,sillyAdress2,sillyAdress3,sillyAdress4,sillyAdress5,sillyAdress6,sillyAdress7,sillyAdress8;

	FILE *EncoderValues,*FilteredPressureValues,*ReadTrajectoryFile,*DesiredPressureTrajectory;
	if((EncoderValues = fopen(".\\NeuralFiles\\ALLTrainDataEncoders.txt","w")) == NULL)
		printf("Dosya Acýlmadý EncoderValues\n");
	if((FilteredPressureValues = fopen(".\\NeuralFiles\\ALLTrainFilteredPressureValues.txt","w")) == NULL)
		printf("Dosya Acýlmadý FilteredPressureValues\n");
	if((ReadTrajectoryFile = fopen(".\\NeuralFiles\\SinVelocityTrajectoryDesired.txt","r")) == NULL)
		printf("Dosya Acýlmadý SinVelocityTrajectoryDesired\n");
	if((DesiredPressureTrajectory = fopen(".\\NeuralFiles\\ALLDesiredPressureTrajectory.txt","w")) == NULL)
		printf("Dosya Acýlmadý DesiredPressureTrajectory\n");

	// 20 ms icin Initialize		
	LARGE_INTEGER ticksPerSecond,start_ticks, end_ticks, cputime,tick;
	if (!QueryPerformanceFrequency(&ticksPerSecond))
	if (!QueryPerformanceCounter(&tick) ) printf("no go counter not installed");

	int iStepTime = 20;int i = 0;float fStep = 0.02;int lDataNumber=1100 ;
	int iCountAll=0,iCount=0;
	float Pressure1[3000],Pressure2[3000],Pressure3[3000],Pressure4[3000];
	long lEncodersValues1[3000],lEncodersValues2[3000],lEncodersValues3[3000],lEncodersValues4[3000],lEncodersValues5[3000];
	float DesiredVelocityLink1[3000],DesiredVelocityLink2[3000],DesiredVelocityLink3[3000];
	float DesiredPressure1[3000]={0},DesiredPressure2[3000]={0},DesiredPressure3[3000]={0},DesiredPressure4[3000]={0};
	float DesiredDotPressure1[3000]={0},DesiredDotPressure2[3000]={0},DesiredDotPressure3[3000]={0},DesiredDotPressure4[3000]={0};
	float ActualPressures1[3000]={0},ActualPressures2[3000]={0},ActualPressures3[3000]={0},ActualPressures4[3000]={0};
	float InitalPressure1,InitalPressure2,InitalPressure3,InitalPressure4;
	int prescount = 0;

	//printf("STARTED ett!!!\n");
	// Allocation of Muscles and Motor Classes

	GoHome();GoHomeMuscle();
	//AO[0]=5.0;AO[1]=5.6;AO[2]=5.6;AO[3]=5.0;SetAnalogOutput(AO);
	//Motor1.MotorServoOn();Motor2.MotorServoOn();Motor3.MotorServoOn();

	Sleep(1500);
	GetAnalogInputs(AverageAnalogInputs);
	InitalPressure1 = AverageAnalogInputs[0];
	InitalPressure2 = AverageAnalogInputs[1];
	InitalPressure3 = AverageAnalogInputs[2];
	InitalPressure4 = AverageAnalogInputs[3];

	// Trajectory Genereation for Motors
	while(!feof(ReadTrajectoryFile))
	{
		fscanf(ReadTrajectoryFile,"%f		%f		%f\n",&DesiredVelocityLink1[iCountAll],&DesiredVelocityLink2[iCountAll],&DesiredVelocityLink3[iCountAll]);	
		iCountAll++;
	}
	
	// Trajectory Genereation for Rubbertuator
	DesiredPressure1[0]= InitalPressure1;DesiredPressure2[0]= InitalPressure2;DesiredPressure3[0]= InitalPressure3;DesiredPressure4[0]= InitalPressure4;
	
	for( i = 1; i<=iCountAll*2/4; i++)
	{
		DesiredPressure1[i] = InitalPressure1+0.05*sin(PI/35*((float)i))+0.5*sin(PI/80*((float)i));
		DesiredDotPressure1[i] = (DesiredPressure1[i]-DesiredPressure1[i-1])/20;
		DesiredPressure4[i] = InitalPressure4-(0.05*sin(PI/35*((float)i)))+0.5*sin(PI/80*((float)i));
		DesiredDotPressure4[i] = (DesiredPressure4[i]-DesiredPressure4[i-1])/20;

		DesiredPressure2[i] = InitalPressure2-(0.05*sin(PI/35*((float)i)))-0.5*sin(PI/80*((float)i));
		DesiredDotPressure2[i] = (DesiredPressure2[i]-DesiredPressure2[i-1])/20;
		DesiredPressure3[i] = InitalPressure3+0.05*sin(PI/35*((float)i))-0.5*sin(PI/80*((float)i));;
		DesiredDotPressure3[i] = (DesiredPressure3[i]-DesiredPressure3[i-1])/20;		
	}

	for( i = i; i>iCountAll*2/4 && i<=iCountAll; i++)
	{
		DesiredPressure1[i] = InitalPressure1+0.6*sin(PI/100*((float)i));
		DesiredDotPressure1[i] = (DesiredPressure1[i]-DesiredPressure1[i-1])/20;
		DesiredPressure4[i] = InitalPressure4+0.6*sin(PI/100*((float)i));
		DesiredDotPressure4[i] = (DesiredPressure4[i]-DesiredPressure4[i-1])/20;

		DesiredPressure2[i] = InitalPressure2-0.6*sin(PI/100*((float)i));
		DesiredDotPressure2[i] = (DesiredPressure2[i]-DesiredPressure2[i-1])/20;
		DesiredPressure3[i] = InitalPressure3-0.6*sin(PI/100*((float)i));;
		DesiredDotPressure3[i] = (DesiredPressure3[i]-DesiredPressure3[i-1])/20;		
	}

	// Begining of The Train Trajectory
	// Dikkat buradaki Deltapressure olayýný dzeltmedim cunku gerek yok PONNET pressure ve digerlerine bakýyor ANNET etkilemiyor
	
	while(CheckEmergency() && SwitchReadMotionStop() && iCount<iCountAll-2)
	{
		QueryPerformanceCounter(&start_ticks);
	
		sillyAdress1 = DesiredPressure1[iCount+1]-DesiredPressure1[iCount];
		sillyAdress2 = DesiredPressure1[iCount+2]-DesiredPressure1[iCount];
		sillyAdress3 = DesiredPressure1[iCount+1]-DesiredPressure1[iCount];
		sillyAdress4 = DesiredPressure1[iCount+2]-DesiredPressure1[iCount];
		sillyAdress5 = DesiredPressure1[iCount+1]-DesiredPressure1[iCount];
		sillyAdress6 = DesiredPressure1[iCount+2]-DesiredPressure1[iCount];
		sillyAdress7 = DesiredPressure1[iCount+1]-DesiredPressure1[iCount];
		sillyAdress8 = DesiredPressure1[iCount+2]-DesiredPressure1[iCount];

		Rubbertuator1.ProcessANNET(&DesiredPressure1[iCount],&DesiredPressure1[iCount+1],&DesiredPressure1[iCount+2],&sillyAdress1,&sillyAdress2,&DesiredDotPressure1[iCount],&AO[0]);
		Rubbertuator2.ProcessANNET(&DesiredPressure2[iCount],&DesiredPressure2[iCount+1],&DesiredPressure2[iCount+2],&sillyAdress3,&sillyAdress4,&DesiredDotPressure2[iCount],&AO[1]);
		Rubbertuator3.ProcessANNET(&DesiredPressure3[iCount],&DesiredPressure3[iCount+1],&DesiredPressure3[iCount+2],&sillyAdress5,&sillyAdress6,&DesiredDotPressure3[iCount],&AO[2]);
		Rubbertuator4.ProcessANNET(&DesiredPressure4[iCount],&DesiredPressure4[iCount+1],&DesiredPressure4[iCount+2],&sillyAdress7,&sillyAdress8,&DesiredDotPressure4[iCount],&AO[3]);

		SetAnalogOutput(AO);
		GetAnalogInputs(AverageAnalogInputs);
		ActualPressures1[iCount]=AverageAnalogInputs[0];ActualPressures2[iCount]=AverageAnalogInputs[1];
		ActualPressures3[iCount]=AverageAnalogInputs[2];ActualPressures4[iCount]=AverageAnalogInputs[3];
	
		NeuralControlDD.ProcessDoubleLinkOutput(&DesiredVelocityLink2[iCount],&DesiredVelocityLink3[iCount],&fMotorVoltage[1],&fMotorVoltage[2]);
		NeuralControlUP.ProcessUpperLink(&DesiredVelocityLink1[iCount],&fMotorVoltage[0]);	
		Motor1.SetMotorSpeed(fMotorVoltage[0]);Motor2.SetMotorSpeed(fMotorVoltage[1]);Motor3.SetMotorSpeed(fMotorVoltage[2]);
		CounterRead();
		lEncodersValues1[iCount] =lCounter[0]; lEncodersValues2[iCount] = lCounter[1];lEncodersValues3[iCount] = lCounter[2];
		lEncodersValues4[iCount] = lCounter[3];lEncodersValues5[iCount] = lCounter[4];
		
		iCount++;

		// Sleep 20 ms.   
		QueryPerformanceCounter(&end_ticks); //printf("kalan:%f\n",(float)(end_ticks.QuadPart-start_ticks.QuadPart)/ticksPerSecond.QuadPart*1000);
		while(((float)(end_ticks.QuadPart-start_ticks.QuadPart)/ticksPerSecond.QuadPart*1000) < (float)20)
		QueryPerformanceCounter(&end_ticks); cputime.QuadPart = end_ticks.QuadPart- start_ticks.QuadPart;	
	}
	
	// Writing Outputs TO the Files
	for( i = 0; i<iCountAll-3 ; i++)
	{
		fprintf(FilteredPressureValues,"%f		%f		%f		%f\n",ActualPressures1[i],ActualPressures2[i],ActualPressures3[i],ActualPressures4[i]);
		fprintf(DesiredPressureTrajectory,"%f		%f		%f		%f\n",DesiredPressure1[i],DesiredPressure2[i],DesiredPressure3[i],DesiredPressure4[i]);
		fprintf(EncoderValues,"%d		%d		%d		%d		%d\n",lEncodersValues1[i],lEncodersValues2[i],lEncodersValues3[i],lEncodersValues4[i],lEncodersValues5[i]);
	}	

	Motor1.MotorServoOff();Motor2.MotorServoOff();Motor3.MotorServoOff();
	AO[0]=0.0;AO[1]=0.0;AO[2]=0.0;AO[3]=0.0;SetAnalogOutput(AO);Sleep(1000);
	
	fclose(EncoderValues);fclose(FilteredPressureValues);fclose(ReadTrajectoryFile);fclose(DesiredPressureTrajectory);

	//printf("STOPPED!!!\n");
	
}

void ALLOUTPUT()
{
	CTrainDD NeuralControlDD;NeuralControlDD.Allocator();
	CTrainUP NeuralControlUP;NeuralControlUP.Allocator();
	CTrainANNET Muscle1ANNET(1);Muscle1ANNET.Allocator();
	CTrainANNET Muscle2ANNET(2);Muscle2ANNET.Allocator();
	CTrainANNET Muscle3ANNET(3);Muscle3ANNET.Allocator();
	CTrainANNET Muscle4ANNET(4);Muscle4ANNET.Allocator();
	CTrainPONNET Muscle1PONNET(1);Muscle1PONNET.Allocator();Muscle1PONNET.CreateWeightMatrix();
	CTrainPONNET Muscle2PONNET(2);Muscle2PONNET.Allocator();Muscle2PONNET.CreateWeightMatrix();
	CTrainPONNET Muscle3PONNET(3);Muscle3PONNET.Allocator();Muscle3PONNET.CreateWeightMatrix();
	CTrainPONNET Muscle4PONNET(4);Muscle4PONNET.Allocator();Muscle4PONNET.CreateWeightMatrix();

	float sillyAdress1,sillyAdress2,sillyAdress3,sillyAdress4,sillyAdress5,sillyAdress6,sillyAdress7,sillyAdress8;
	int iStepTime=20,i=0,iCountAll=0,iCount=1,TotalWeigtsCount=0,j=0,partindex=0;
	float WeightsforRubs[3000][15]={0};
	float RubsPacket[15]={0},Pd1=0.0,Pd2=0.0,Pd3=0.0,Pd4=0.0,fStep = 0.02;;
	float DesiredVelocityLink1[3000],DesiredVelocityLink2[3000],DesiredVelocityLink3[3000];
	float DesiredPressure1[3000]={0},DesiredPressure2[3000]={0},DesiredPressure3[3000]={0},DesiredPressure4[3000]={0};
	float DesiredDotPressure1[3000]={0},DesiredDotPressure2[3000]={0},DesiredDotPressure3[3000]={0},DesiredDotPressure4[3000]={0};
	float ActualPressures1[3000]={0},ActualPressures2[3000]={0},ActualPressures3[3000]={0},ActualPressures4[3000]={0};
	long lEncodersValues1[3000],lEncodersValues2[3000],lEncodersValues3[3000],lEncodersValues4[3000],lEncodersValues5[3000];
	float LogVoltages[3000][4];
	float RealEncoderValue4,RealEncoderValue5,DeltaP,TotalError=0,ErrorP=0,ErrorPrevious=0;
	float KP,KI,KD;

	FILE *EncoderValues,*PressureValues,*ReadTrajectoryMotorsVelocities,*ReadTrajectoryRubsWeights,*LogTime,*LogANNET;
	if((EncoderValues = fopen(".\\NeuralFiles\\ALLTrajectoryActualEncoders.txt","w")) == NULL)
		printf("Dosya Acýlmadý EncoderValues\n");
	if((PressureValues = fopen(".\\NeuralFiles\\ALLTrajectoryActualPressureValues.txt","w")) == NULL)
		printf("Dosya Acýlmadý FilteredPressureValues\n");
	if((ReadTrajectoryMotorsVelocities = fopen(".\\NeuralFiles\\SinVelocityTrajectoryDesired.txt","r")) == NULL)
		printf("Dosya Acýlmadý SinVelocityTrajectoryDesired\n");
	if((ReadTrajectoryRubsWeights = fopen(".\\NeuralFiles\\SinTrajectoryALLWeights.txt","r")) == NULL)
		printf("Dosya Acýlmadý DesiredPressureTrajectory\n");
	if((LogTime = fopen(".\\NeuralFiles\\LogTimeALL.txt","w")) == NULL)
		printf("Dosya Acýlmadý LogTime\n");
	if((LogANNET = fopen(".\\NeuralFiles\\LogALLANNETPressures.txt","w")) == NULL)
		printf("Dosya Acýlmadý LogTime\n");

	// 20 ms icin Initialize		
	LARGE_INTEGER ticksPerSecond,start_ticks, end_ticks, cputime,tick;
	if (!QueryPerformanceFrequency(&ticksPerSecond))
	if (!QueryPerformanceCounter(&tick) ) printf("no go counter not installed");

	Sleep(100);//printf("STARTED!!!\n");

	//GoHome();GoHomeMuscle();
	
	while(!feof(ReadTrajectoryMotorsVelocities))
	{
		fscanf(ReadTrajectoryMotorsVelocities,"%f		%f		%f\n",&DesiredVelocityLink1[iCountAll],&DesiredVelocityLink2[iCountAll],&DesiredVelocityLink3[iCountAll]);	
		iCountAll++;
	}
	while(!feof(ReadTrajectoryRubsWeights))
	{
		fscanf(ReadTrajectoryRubsWeights ,"%f  %f  %f  %f  %f	%f	%f	%f	%f	%f	%f	%f	%f	%f\n",&WeightsforRubs[TotalWeigtsCount][0],&WeightsforRubs[TotalWeigtsCount][1],&WeightsforRubs[TotalWeigtsCount][2],&WeightsforRubs[TotalWeigtsCount][3],&WeightsforRubs[TotalWeigtsCount][4],&WeightsforRubs[TotalWeigtsCount][5],&WeightsforRubs[TotalWeigtsCount][6],&WeightsforRubs[TotalWeigtsCount][7],&WeightsforRubs[TotalWeigtsCount][8],&WeightsforRubs[TotalWeigtsCount][9],&WeightsforRubs[TotalWeigtsCount][10],&WeightsforRubs[TotalWeigtsCount][11],&WeightsforRubs[TotalWeigtsCount][12],&WeightsforRubs[TotalWeigtsCount][13]);
		TotalWeigtsCount++;
	}

	// Processden once ANNET icin Pressurelarý ve Pressuredotlar lazým onu buluyorum
	for( j=1;j<TotalWeigtsCount-2;j++) // Aslýnda burada tüm datalar olacak j yerine TotalWeigtsCount-1
	{
		if ( (WeightsforRubs[j-1][0] < WeightsforRubs[j][0]) ) // Getting Ready the Direction For the Ssytem
			RubsPacket[14] = 1.0;
		if ( (WeightsforRubs[j-1][0] > WeightsforRubs[j][0]) )
			RubsPacket[14] = 0.0;
		if ( (WeightsforRubs[j-1][0] == WeightsforRubs[j][0]) )
			RubsPacket[14] = RubsPacket[14] ;

		for(i=0;i<14;i++)  // Getting Ready the Direction For the Ssytem
			RubsPacket[i] = WeightsforRubs[j-1][i];

		Muscle1PONNET.ProcessPONNET(RubsPacket,&DesiredPressure1[j-1],&partindex);
		Muscle2PONNET.ProcessPONNET(RubsPacket,&DesiredPressure2[j-1],&partindex);
		Muscle3PONNET.ProcessPONNET(RubsPacket,&DesiredPressure3[j-1],&partindex);
		Muscle4PONNET.ProcessPONNET(RubsPacket,&DesiredPressure4[j-1],&partindex);
	}
	
	for( j=0;j<TotalWeigtsCount-2;j++) 
	{
		// ANNET Inputs FOr the First Muscle
		DesiredDotPressure1[j] = (DesiredPressure1[j+1]-DesiredPressure1[j])/20;
		DesiredDotPressure2[j] = (DesiredPressure2[j+1]-DesiredPressure2[j])/20;
		DesiredDotPressure3[j] = (DesiredPressure3[j+1]-DesiredPressure3[j])/20;
		DesiredDotPressure4[j] = (DesiredPressure4[j+1]-DesiredPressure4[j])/20;
	}
	
	while(CheckEmergency() && SwitchReadMotionStop() && iCount<TotalWeigtsCount-3)
	{

		QueryPerformanceCounter(&start_ticks);

		sillyAdress1 = DesiredPressure1[iCount+1]-DesiredPressure1[iCount];
		sillyAdress2 = DesiredPressure1[iCount+2]-DesiredPressure1[iCount];
		sillyAdress3 = DesiredPressure1[iCount+1]-DesiredPressure1[iCount];
		sillyAdress4 = DesiredPressure1[iCount+2]-DesiredPressure1[iCount];
		sillyAdress5 = DesiredPressure1[iCount+1]-DesiredPressure1[iCount];
		sillyAdress6 = DesiredPressure1[iCount+2]-DesiredPressure1[iCount];
		sillyAdress7 = DesiredPressure1[iCount+1]-DesiredPressure1[iCount];
		sillyAdress8 = DesiredPressure1[iCount+2]-DesiredPressure1[iCount];

		Muscle1ANNET.ProcessANNET(&DesiredPressure1[iCount],&DesiredPressure1[iCount+1],&DesiredPressure1[iCount+2],&sillyAdress1,&sillyAdress2,&DesiredDotPressure1[iCount],&AO[0]);
		Muscle2ANNET.ProcessANNET(&DesiredPressure2[iCount],&DesiredPressure2[iCount+1],&DesiredPressure2[iCount+2],&sillyAdress3,&sillyAdress4,&DesiredDotPressure2[iCount],&AO[1]);
		Muscle3ANNET.ProcessANNET(&DesiredPressure3[iCount],&DesiredPressure3[iCount+1],&DesiredPressure3[iCount+2],&sillyAdress5,&sillyAdress6,&DesiredDotPressure3[iCount],&AO[2]);
		Muscle4ANNET.ProcessANNET(&DesiredPressure4[iCount],&DesiredPressure4[iCount+1],&DesiredPressure4[iCount+2],&sillyAdress7,&sillyAdress8,&DesiredDotPressure4[iCount],&AO[3]);

		for(int z=0 ;z<4;z++)
			LogVoltages[iCount][z] = AO[z];

		SetAnalogOutput(AO);GetAnalogInputs(AverageAnalogInputs);
		ActualPressures1[iCount]=AverageAnalogInputs[0];ActualPressures2[iCount]=AverageAnalogInputs[1];
		ActualPressures3[iCount]=AverageAnalogInputs[2];ActualPressures4[iCount]=AverageAnalogInputs[3];

		NeuralControlDD.ProcessDoubleLinkOutput(&DesiredVelocityLink2[iCount],&DesiredVelocityLink3[iCount],&fMotorVoltage[1],&fMotorVoltage[2]);
		NeuralControlUP.ProcessUpperLink(&DesiredVelocityLink1[iCount],&fMotorVoltage[0]);	
		Motor1.SetMotorSpeed(fMotorVoltage[0]);Motor2.SetMotorSpeed(fMotorVoltage[1]);Motor3.SetMotorSpeed(fMotorVoltage[2]);
		CounterRead();
		lEncodersValues1[iCount] =lCounter[0]; lEncodersValues2[iCount] = lCounter[1];lEncodersValues3[iCount] = lCounter[2];
		lEncodersValues4[iCount] = lCounter[3];lEncodersValues5[iCount] = lCounter[4];

		iCount++;myGlutDisplay();
				
		// Sleep 20 ms.   
		QueryPerformanceCounter(&end_ticks); //printf("%f\n",(float)(end_ticks.QuadPart-start_ticks.QuadPart)/ticksPerSecond.QuadPart*1000);
		while(((float)(end_ticks.QuadPart-start_ticks.QuadPart)/ticksPerSecond.QuadPart*1000) < (float)20)
			QueryPerformanceCounter(&end_ticks); cputime.QuadPart = end_ticks.QuadPart- start_ticks.QuadPart;		
	}

	// Writing Outputs TO the Files
	for( i = 1; i<TotalWeigtsCount-3 ; i++)
	{
		fprintf(PressureValues,"%d	%f		%f		%f		%f\n",i,ActualPressures1[i],ActualPressures2[i],ActualPressures3[i],ActualPressures4[i]);
		fprintf(EncoderValues,"%d	%d		%d		%d		%d		%d\n",lEncodersValues1[i],lEncodersValues2[i],lEncodersValues3[i],lEncodersValues4[i],lEncodersValues5[i],i);
		fprintf(LogANNET,"%d	%f	%f	%f	%f	%f	%f	%f	%f %f	%f	%f	%f	%d	%d	%d	%d  %d\n",i,DesiredPressure1[i],DesiredPressure2[i],DesiredPressure3[i],DesiredPressure4[i],ActualPressures1[i],ActualPressures2[i],ActualPressures3[i],ActualPressures4[i],LogVoltages[i][0],LogVoltages[i][1],LogVoltages[i][2],LogVoltages[i][3],lEncodersValues1[i],lEncodersValues2[i],lEncodersValues3[i],lEncodersValues4[i],lEncodersValues5[i]);		
	}	

	Motor1.MotorServoOff();Motor2.MotorServoOff();Motor3.MotorServoOff();
	AO[0]=0.0;AO[1]=0.0;AO[2]=0.0;AO[3]=0.0;SetAnalogOutput(AO);Sleep(1000);
	
	fclose(EncoderValues);fclose(PressureValues);fclose(ReadTrajectoryMotorsVelocities);fclose(ReadTrajectoryRubsWeights );
	fclose(LogTime);fclose(LogANNET);

	//printf("STOPPED!!!\n");
}

void ALLOUTPUTFUZZYGA()
{
	CTrainDD NeuralControlDD;NeuralControlDD.Allocator();
	CTrainUP NeuralControlUP;NeuralControlUP.Allocator();
	CTrainANNET Muscle1ANNET(1);Muscle1ANNET.Allocator();
	CTrainANNET Muscle2ANNET(2);Muscle2ANNET.Allocator();
	CTrainANNET Muscle3ANNET(3);Muscle3ANNET.Allocator();
	CTrainANNET Muscle4ANNET(4);Muscle4ANNET.Allocator();
	CTrainPONNET Muscle1PONNET(1);Muscle1PONNET.Allocator();Muscle1PONNET.CreateWeightMatrix();
	CTrainPONNET Muscle2PONNET(2);Muscle2PONNET.Allocator();Muscle2PONNET.CreateWeightMatrix();
	CTrainPONNET Muscle3PONNET(3);Muscle3PONNET.Allocator();Muscle3PONNET.CreateWeightMatrix();
	CTrainPONNET Muscle4PONNET(4);Muscle4PONNET.Allocator();Muscle4PONNET.CreateWeightMatrix();

	float sillyAdress1,sillyAdress2,sillyAdress3,sillyAdress4,sillyAdress5,sillyAdress6,sillyAdress7,sillyAdress8;
	int iStepTime=20,i=0,iCountAll=0,iCount=1,TotalWeigtsCount=0,j=0,partindex=0;
	float WeightsforRubs[3000][15]={0};
	float RubsPacket[15]={0},Pd1=0.0,Pd2=0.0,Pd3=0.0,Pd4=0.0,fStep = 0.02;;
	float DesiredVelocityLink1[3000],DesiredVelocityLink2[3000],DesiredVelocityLink3[3000];
	float DesiredPressure1[3000]={0},DesiredPressure2[3000]={0},DesiredPressure3[3000]={0},DesiredPressure4[3000]={0};
	float DesiredDotPressure1[3000]={0},DesiredDotPressure2[3000]={0},DesiredDotPressure3[3000]={0},DesiredDotPressure4[3000]={0};
	float ActualPressures1[3000]={0},ActualPressures2[3000]={0},ActualPressures3[3000]={0},ActualPressures4[3000]={0};
	long lEncodersValues1[3000],lEncodersValues2[3000],lEncodersValues3[3000],lEncodersValues4[3000],lEncodersValues5[3000];
	float LogVoltages[3000][4];
	float output1=0.0,output2=0.0,output3=0.0,output4=0.0;

	float DirectionVector[3000]={0};
	float NormalizedAngle=0.0,Emax = (float) 0.0182,Emin = (float)0.0098,Eavg=0.0,Error=0.0,Eavgup=0.0,Eavglow=0.0; 
	float centerofmass1=0.0,centerofmass2=0.0,centerofmass3=0.0,centerofmass4=0.0,centerofmass5=0.0 ,area1 = 0.0,area2 = 0.0,area3 = 0.0,area4 = 0.0,area5 = 0.0 ;
	float Fuzzyerrorlow=0.0,Fuzzyerrormedium=0.0,Fuzzyerrorhigh=0.0,Fuzzyerrorveryhigh=0.0,Fuzzyerrorverylow=0.0,alpha_high_R1=0.0,alpha_medium_R2=0.0,alpha_low_R3=0.0,Alpha=0.0,alpha_verylow_R4=0.0,alpha_veryhigh_R5=0.0;
	float kf[10] = {0.1489  ,  0.6020   , 0.2659 ,   0.0067   , 0.5735   , 0.5266  ,  0.6143   , 0.1722 ,0.8195  , 0.5964};

	float OutsideValue1=0.0,OutsideValue2=0.0,OutsideValue3=0.0,OutsideValue4=0.0;
	float OutputBuffer1=0.0,OutputBuffer2=0.0,OutputBuffer3=0.0,OutputBuffer4=0.0;


	FILE *EncoderValues,*PressureValues,*ReadTrajectoryMotorsVelocities,*ReadTrajectoryRubsWeights,*LogTime,*LogANNET;
	if((EncoderValues = fopen(".\\NeuralFiles\\ALLTrajectoryActualEncoders.txt","w")) == NULL)
		printf("Dosya Acýlmadý EncoderValues\n");
	if((PressureValues = fopen(".\\NeuralFiles\\ALLTrajectoryActualPressureValues.txt","w")) == NULL)
		printf("Dosya Acýlmadý FilteredPressureValues\n");
	if((ReadTrajectoryMotorsVelocities = fopen(".\\NeuralFiles\\SinVelocityTrajectoryDesired.txt","r")) == NULL)
		printf("Dosya Acýlmadý SinVelocityTrajectoryDesired\n");
	if((ReadTrajectoryRubsWeights = fopen(".\\NeuralFiles\\SinTrajectoryALLWeights.txt","r")) == NULL)
		printf("Dosya Acýlmadý DesiredPressureTrajectory\n");
	if((LogTime = fopen(".\\NeuralFiles\\LogTimeALL.txt","w")) == NULL)
		printf("Dosya Acýlmadý LogTime\n");
	if((LogANNET = fopen(".\\NeuralFiles\\LogALLANNETPressures.txt","w")) == NULL)
		printf("Dosya Acýlmadý LogTime\n");

	// 20 ms icin Initialize		
	LARGE_INTEGER ticksPerSecond,start_ticks, end_ticks, cputime,tick;
	if (!QueryPerformanceFrequency(&ticksPerSecond))
	if (!QueryPerformanceCounter(&tick) ) printf("no go counter not installed");

	Sleep(100);//printf("STARTED!!!\n");

	//GoHome();GoHomeMuscle();
	//AO[0]=5.0;AO[1]=5.6;AO[2]=5.6;AO[3]=5.0;SetAnalogOutput(AO);
	//Motor1.MotorServoOn();Motor2.MotorServoOn();Motor3.MotorServoOn();

	while(!feof(ReadTrajectoryMotorsVelocities))
	{
		fscanf(ReadTrajectoryMotorsVelocities,"%f		%f		%f\n",&DesiredVelocityLink1[iCountAll],&DesiredVelocityLink2[iCountAll],&DesiredVelocityLink3[iCountAll]);	
		iCountAll++;
	}
	while(!feof(ReadTrajectoryRubsWeights))
	{
		fscanf(ReadTrajectoryRubsWeights ,"%f  %f  %f  %f  %f	%f	%f	%f	%f	%f	%f	%f	%f	%f\n",&WeightsforRubs[TotalWeigtsCount][0],&WeightsforRubs[TotalWeigtsCount][1],&WeightsforRubs[TotalWeigtsCount][2],&WeightsforRubs[TotalWeigtsCount][3],&WeightsforRubs[TotalWeigtsCount][4],&WeightsforRubs[TotalWeigtsCount][5],&WeightsforRubs[TotalWeigtsCount][6],&WeightsforRubs[TotalWeigtsCount][7],&WeightsforRubs[TotalWeigtsCount][8],&WeightsforRubs[TotalWeigtsCount][9],&WeightsforRubs[TotalWeigtsCount][10],&WeightsforRubs[TotalWeigtsCount][11],&WeightsforRubs[TotalWeigtsCount][12],&WeightsforRubs[TotalWeigtsCount][13]);
		TotalWeigtsCount++;
	}

	// Processden once ANNET icin Pressurelarý ve Pressuredotlar lazým onu buluyorum
		// Creat The Direction Vector
	for( j=1;j<TotalWeigtsCount;j++) // Aslýnda burada tüm datalar olacak j yerine TotalWeigtsCount-1
	{
		if ( (WeightsforRubs[j-1][0] < WeightsforRubs[j][0])) // Getting Ready the Direction For the Ssytem
			DirectionVector[j]=1.0;
		if ( (WeightsforRubs[j-1][0] > WeightsforRubs[j][0]))
			DirectionVector[j]=0.0;
		if ( (WeightsforRubs[j-1][0] == WeightsforRubs[j][0]))
			DirectionVector[j]=DirectionVector[j-1];
	}DirectionVector[0]=DirectionVector[1];
	
	// Process Start Here
	for( j=1;j<TotalWeigtsCount-2;j++) // Aslýnda burada tüm datalar olacak j yerine TotalWeigtsCount-1
	{
		// Fuzzy Begins
		// Decide Which NN will be used.Ex(4.2/4)
		NormalizedAngle = WeightsforRubs[j][0] -(floor(WeightsforRubs[j][0]/4))*4;

		for(i=0;i<14;i++)  // Getting Ready The Weights For The System
			RubsPacket[i] = WeightsforRubs[j][i];
		
		if (NormalizedAngle<=2)		// Bir oncekini Al j-1 icin
		{				
			RubsPacket[14] = DirectionVector[j];// Direction Bir sonraki
			partindex = -1;
		}
		if (NormalizedAngle>2)		// Bir sonrakini Al j+1 icin
		{				
			RubsPacket[14] = DirectionVector[j]; // Direction Bir sonraki
			partindex = +1; // Bir sonrakine bakmak icin
		}
		Muscle1PONNET.ProcessPONNET(RubsPacket,&output1,&partindex);
		Muscle2PONNET.ProcessPONNET(RubsPacket,&output2,&partindex);
		Muscle3PONNET.ProcessPONNET(RubsPacket,&output3,&partindex);
		Muscle4PONNET.ProcessPONNET(RubsPacket,&output4,&partindex);
		OutsideValue1 = output1;OutsideValue2 = output2;OutsideValue3 = output3;OutsideValue4 = output4;
	
		// O andaki degeri
		RubsPacket[14] = DirectionVector[j];partindex = 0;
		Muscle1PONNET.ProcessPONNET(RubsPacket,&output1,&partindex);
		Muscle2PONNET.ProcessPONNET(RubsPacket,&output2,&partindex);
		Muscle3PONNET.ProcessPONNET(RubsPacket,&output3,&partindex);
		Muscle4PONNET.ProcessPONNET(RubsPacket,&output4,&partindex);
		OutputBuffer1 = output1;OutputBuffer2 = output2;OutputBuffer3 = output3;OutputBuffer4 = output4;

		// Elimizde output ve OutsideValue1 var alpha ile convex combination yapýlacak
		// Error Function
		Error = 0.0017353*NormalizedAngle*NormalizedAngle +  -0.0062396 * NormalizedAngle + 0.015369;
		Eavg = (Emax + Emin) /2;Eavglow=(Eavg+Emin)/2;Eavgup = (Eavg+Emax)/2;
		
		// Fuzzifiction Start
		ErrorLowMemberShipFunction(&Error,&Emin,&Eavg,&Eavglow,&Fuzzyerrorlow);
		ErrorMediumMemberShipFunction(&Error,&Eavglow,&Eavgup,&Eavg,&Fuzzyerrormedium);
		ErrorHighMemberShipFunction(&Error,&Eavg,&Emax,&Eavgup,&Fuzzyerrorhigh);
		ErrorVeryHighMemberShipFunction(&Error,&Eavgup,&Emax,&Fuzzyerrorveryhigh);
		ErrorVeryLowMemberShipFunction(&Error,&Eavglow,&Eavg,&Fuzzyerrorverylow);

		// Rules
		InferenceRule1Function(&Fuzzyerrorlow,&alpha_high_R1);
		InferenceRule2Function(&Fuzzyerrormedium,&alpha_medium_R2);
		InferenceRule3Function(&Fuzzyerrorhigh,&alpha_low_R3);
		InferenceRule4Function(&Fuzzyerrorveryhigh,&alpha_verylow_R4);
		InferenceRule5Function(&Fuzzyerrorverylow,&alpha_veryhigh_R5);

		//Defuzzification
		AlphaVeryLowDefuzzificationFunction(&alpha_verylow_R4,&kf[0],&kf[1],&centerofmass4,&area4);	
		AlphaLowDefuzzificationFunction(&alpha_low_R3,&kf[2],&kf[3],&centerofmass3,&area3);	
		AlphaMediumDefuzzificationFunction(&alpha_medium_R2,&kf[4],&kf[5],&centerofmass2,&area2);
		AlphaHighDefuzzificationFunction(&alpha_high_R1,&kf[6],&kf[7],&centerofmass1,&area1);
		AlphaVeryHighDefuzzificationFunction(&alpha_veryhigh_R5,&kf[8],&kf[9],&centerofmass5,&area5);

		// Convex combination
		Alpha = (centerofmass1*area1 + centerofmass2*area2 +centerofmass3*area3+centerofmass4*area4+centerofmass5*area5)/(area1+area2+area3+area4+area5);
		if(DirectionVector[j-1] = 0.0)
		{
			DesiredPressure1[j-1] = output1 * Alpha + (1-Alpha) * OutsideValue1;
			DesiredPressure2[j-1] = output2 * Alpha + (1-Alpha) * OutsideValue2;
			DesiredPressure3[j-1] = output3 * Alpha + (1-Alpha) * OutsideValue3;
			DesiredPressure4[j-1] = output4 * Alpha + (1-Alpha) * OutsideValue4;
		}
		if(DirectionVector[j-1] = 1.0)
		{
			DesiredPressure1[j-1] = output1 * Alpha + (1-Alpha) * OutsideValue1;
			DesiredPressure2[j-1] = output2 * Alpha + (1-Alpha) * OutsideValue2;
			DesiredPressure3[j-1] = output3 * Alpha + (1-Alpha) * OutsideValue3;
			DesiredPressure4[j-1] = output4 * Alpha + (1-Alpha) * OutsideValue4;
		}	
	}
	
	for( j=0;j<TotalWeigtsCount-2;j++) 
	{
		// ANNET Inputs FOr the First Muscle
		DesiredDotPressure1[j] = (DesiredPressure1[j+1]-DesiredPressure1[j])/20;
		DesiredDotPressure2[j] = (DesiredPressure2[j+1]-DesiredPressure2[j])/20;
		DesiredDotPressure3[j] = (DesiredPressure3[j+1]-DesiredPressure3[j])/20;
		DesiredDotPressure4[j] = (DesiredPressure4[j+1]-DesiredPressure4[j])/20;
	}
	
	while(CheckEmergency() && SwitchReadMotionStop() && iCount<TotalWeigtsCount-3)
	{

		QueryPerformanceCounter(&start_ticks);

		sillyAdress1 = DesiredPressure1[iCount+1]-DesiredPressure1[iCount];
		sillyAdress2 = DesiredPressure1[iCount+2]-DesiredPressure1[iCount];
		sillyAdress3 = DesiredPressure1[iCount+1]-DesiredPressure1[iCount];
		sillyAdress4 = DesiredPressure1[iCount+2]-DesiredPressure1[iCount];
		sillyAdress5 = DesiredPressure1[iCount+1]-DesiredPressure1[iCount];
		sillyAdress6 = DesiredPressure1[iCount+2]-DesiredPressure1[iCount];
		sillyAdress7 = DesiredPressure1[iCount+1]-DesiredPressure1[iCount];
		sillyAdress8 = DesiredPressure1[iCount+2]-DesiredPressure1[iCount];

		Muscle1ANNET.ProcessANNET(&DesiredPressure1[iCount],&DesiredPressure1[iCount+1],&DesiredPressure1[iCount+2],&sillyAdress1,&sillyAdress2,&DesiredDotPressure1[iCount],&AO[0]);
		Muscle2ANNET.ProcessANNET(&DesiredPressure2[iCount],&DesiredPressure2[iCount+1],&DesiredPressure2[iCount+2],&sillyAdress3,&sillyAdress4,&DesiredDotPressure2[iCount],&AO[1]);
		Muscle3ANNET.ProcessANNET(&DesiredPressure3[iCount],&DesiredPressure3[iCount+1],&DesiredPressure3[iCount+2],&sillyAdress5,&sillyAdress6,&DesiredDotPressure3[iCount],&AO[2]);
		Muscle4ANNET.ProcessANNET(&DesiredPressure4[iCount],&DesiredPressure4[iCount+1],&DesiredPressure4[iCount+2],&sillyAdress7,&sillyAdress8,&DesiredDotPressure4[iCount],&AO[3]);

		for(int z=0 ;z<4;z++)
			LogVoltages[iCount][z] = AO[z];

		SetAnalogOutput(AO);GetAnalogInputs(AverageAnalogInputs);
		ActualPressures1[iCount]=AverageAnalogInputs[0];ActualPressures2[iCount]=AverageAnalogInputs[1];
		ActualPressures3[iCount]=AverageAnalogInputs[2];ActualPressures4[iCount]=AverageAnalogInputs[3];

		NeuralControlDD.ProcessDoubleLinkOutput(&DesiredVelocityLink2[iCount],&DesiredVelocityLink3[iCount],&fMotorVoltage[1],&fMotorVoltage[2]);
		NeuralControlUP.ProcessUpperLink(&DesiredVelocityLink1[iCount],&fMotorVoltage[0]);	
		Motor1.SetMotorSpeed(fMotorVoltage[0]);Motor2.SetMotorSpeed(fMotorVoltage[1]);Motor3.SetMotorSpeed(fMotorVoltage[2]);
		CounterRead();
		lEncodersValues1[iCount] =lCounter[0]; lEncodersValues2[iCount] = lCounter[1];lEncodersValues3[iCount] = lCounter[2];
		lEncodersValues4[iCount] = lCounter[3];lEncodersValues5[iCount] = lCounter[4];

		iCount++;myGlutDisplay();
				
		// Sleep 20 ms.   
		QueryPerformanceCounter(&end_ticks); //printf("%f\n",(float)(end_ticks.QuadPart-start_ticks.QuadPart)/ticksPerSecond.QuadPart*1000);
		while(((float)(end_ticks.QuadPart-start_ticks.QuadPart)/ticksPerSecond.QuadPart*1000) < (float)20)
			QueryPerformanceCounter(&end_ticks); cputime.QuadPart = end_ticks.QuadPart- start_ticks.QuadPart;		
	}

	// Writing Outputs TO the Files
	for( i = 1; i<TotalWeigtsCount-3 ; i++)
	{
		fprintf(PressureValues,"%d	%f		%f		%f		%f\n",i,ActualPressures1[i],ActualPressures2[i],ActualPressures3[i],ActualPressures4[i]);
		fprintf(EncoderValues,"%d	%d		%d		%d		%d		%d\n",lEncodersValues1[i],lEncodersValues2[i],lEncodersValues3[i],lEncodersValues4[i],lEncodersValues5[i],i);
		fprintf(LogANNET,"%d	%f	%f	%f	%f	%f	%f	%f	%f %f	%f	%f	%f	%d	%d	%d	%d  %d\n",i,DesiredPressure1[i],DesiredPressure2[i],DesiredPressure3[i],DesiredPressure4[i],ActualPressures1[i],ActualPressures2[i],ActualPressures3[i],ActualPressures4[i],LogVoltages[i][0],LogVoltages[i][1],LogVoltages[i][2],LogVoltages[i][3],lEncodersValues1[i],lEncodersValues2[i],lEncodersValues3[i],lEncodersValues4[i],lEncodersValues5[i]);		
	}	

	Motor1.MotorServoOff();Motor2.MotorServoOff();Motor3.MotorServoOff();
	AO[0]=0.0;AO[1]=0.0;AO[2]=0.0;AO[3]=0.0;SetAnalogOutput(AO);Sleep(1000);
	
	fclose(EncoderValues);fclose(PressureValues);fclose(ReadTrajectoryMotorsVelocities);fclose(ReadTrajectoryRubsWeights );
	fclose(LogTime);fclose(LogANNET);

	//printf("STOPPED!!!\n");
}

void ErrorVeryLowMemberShipFunction(float*Error,float *LowerBound,float *MediumBound,float *Fuzzynumber)
{
	if  (*Error >= *MediumBound)
		*Fuzzynumber = 0 ;
	if ( *Error <= *LowerBound)
        *Fuzzynumber = +1;
	if ( (*Error < *MediumBound) && ( *Error > *LowerBound)) 
        *Fuzzynumber = (*MediumBound-*Error)/(*MediumBound-*LowerBound);
}
void ErrorLowMemberShipFunction(float *Error,float *LowerBound,float *UpperBound,float *MediumBound,float *Fuzzynumber)
{
	if  (*Error <= *LowerBound)
		*Fuzzynumber = 0 ;
	if (*Error >=*UpperBound)
		*Fuzzynumber = 0;
	if ((*Error > *LowerBound) && (*Error < *MediumBound))
        *Fuzzynumber = (*Error -*LowerBound)/(*MediumBound-*LowerBound) ;
	if ((*Error > *MediumBound) && (*Error < *UpperBound))
		*Fuzzynumber = (*UpperBound -*Error)/(*UpperBound-*MediumBound) ;
}

void ErrorMediumMemberShipFunction(float *Error,float *LowerBound,float *UpperBound,float *MediumBound,float *Fuzzynumber)
{
	if  (*Error <= *LowerBound)
		*Fuzzynumber = 0 ;
	if (*Error >=*UpperBound)
		*Fuzzynumber = 0;
	if ((*Error > *LowerBound) && (*Error < *MediumBound))
        *Fuzzynumber = (*Error -*LowerBound)/(*MediumBound-*LowerBound) ;
	if ((*Error > *MediumBound) && (*Error < *UpperBound))
		*Fuzzynumber = (*UpperBound -*Error)/(*UpperBound-*MediumBound) ;
}
void ErrorHighMemberShipFunction(float *Error,float *LowerBound,float *UpperBound,float *MediumBound,float *Fuzzynumber)
{
	if  (*Error <= *LowerBound)
		*Fuzzynumber = 0 ;
	if (*Error >=*UpperBound)
		*Fuzzynumber = 0;
	if ((*Error > *LowerBound) && (*Error < *MediumBound))
        *Fuzzynumber = (*Error -*LowerBound)/(*MediumBound-*LowerBound) ;
	if ((*Error > *MediumBound) && (*Error < *UpperBound))
		*Fuzzynumber = (*UpperBound -*Error)/(*UpperBound-*MediumBound) ;
}

void ErrorVeryHighMemberShipFunction(float*Error,float *MediumBound,float *UpperBound,float *Fuzzynumber)
{
	if  (*Error >= *UpperBound)
		*Fuzzynumber = 1 ;
	if (*Error <= *MediumBound)
        *Fuzzynumber = 0;
	if ((*Error < *UpperBound) && (*Error > *MediumBound) )
        *Fuzzynumber =( *Error -*MediumBound)/( *UpperBound-*MediumBound);
}

void InferenceRule1Function(float *FuzzyError,float *alphavalue)
{
	*alphavalue = *FuzzyError;	
}
void InferenceRule2Function(float *FuzzyError,float *alphavalue)
{
	*alphavalue = *FuzzyError;	
}
void InferenceRule3Function(float *FuzzyError,float *alphavalue)
{
	*alphavalue = *FuzzyError;	
}
void InferenceRule4Function(float *FuzzyError,float *alphavalue)
{
	*alphavalue = *FuzzyError;	
}
void InferenceRule5Function(float *FuzzyError,float *alphavalue)
{
	*alphavalue = *FuzzyError;	
}
void AlphaLowDefuzzificationFunction(float *alpha,float *MediumBound,float *Mu,float *centerofmass,float *area)
{
	float UpperBound,LowerBound;
	UpperBound = *MediumBound+*Mu;LowerBound = *MediumBound - *Mu;
	*centerofmass=*MediumBound;*area = *alpha * (*Mu)  * (2-*Mu);
}
void AlphaMediumDefuzzificationFunction(float *alpha,float *MediumBound,float *Mu,float *centerofmass,float *area)
{
	float UpperBound,LowerBound;
	UpperBound = *MediumBound+*Mu;LowerBound = *MediumBound - *Mu;
	*centerofmass=*MediumBound;*area = *alpha * (*Mu)  * (2-*Mu);
}
void AlphaHighDefuzzificationFunction(float *alpha,float *MediumBound,float *Mu,float *centerofmass,float *area)
{
	float UpperBound,LowerBound;
	UpperBound = *MediumBound+*Mu;LowerBound = *MediumBound - *Mu;
	*centerofmass=*MediumBound;*area = *alpha * (*Mu)  * (2-*Mu);
}
void AlphaVeryHighDefuzzificationFunction(float *alpha,float *MediumBound,float *Mu,float *centerofmass,float *area)
{
	float UpperBound,LowerBound;
	UpperBound = *MediumBound+*Mu;LowerBound = *MediumBound - *Mu;
	*centerofmass=*MediumBound;*area = *alpha * (*Mu)  * (2-*Mu);
}
void AlphaVeryLowDefuzzificationFunction(float *alpha,float *MediumBound,float *Mu,float *centerofmass,float *area)
{
	float UpperBound,LowerBound;
	UpperBound = *MediumBound+*Mu;LowerBound = *MediumBound - *Mu;
	*centerofmass=*MediumBound;*area = *alpha * (*Mu)  * (2-*Mu);
}

#endif 