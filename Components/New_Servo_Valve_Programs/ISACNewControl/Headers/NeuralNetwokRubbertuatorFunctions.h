#ifndef _NeuralNetwokRubbertuatorFunctions_h
#define _NeuralNetwokRubbertuatorFunctions_h

#include <windows.h>
#include <windef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <stdarg.h>	
#include <TIME.H>
#include<IOSTREAM>

#include"Headers\3dsLoadFunctions.h"
#include"Headers\GLWindowFunctions.h"

#include"Headers\driver.h"
#include"Headers\MotorFunctions.h"
#include"Headers\AnalogInputFunctions.h"
#include"Headers\AnalogOutputFunctions.h"
#include"Headers\TrainANNET.h"
#include "../Headers\TrainDoubleLink.h"

#define PI 3.141592653589

extern long lCounter[6];
extern WORD wSwitch[6],wEmgc;
extern clock_t startTime,stopTime,clTime;
extern float AO[4];
extern float fMotorVoltage[3];
extern float AverageAnalogInputs[12];

void NeuralTrainTrajectoryRubbertuators()
{
	FILE *ActualPressureVoltagesANNET1,*ActualPressureVoltagesANNET2,*ActualPressureVoltagesANNET3,*ActualPressureVoltagesANNET4;

	int lDataNumber=1300,iStepTime = 20, i = 0,iMuscleCount = 0,j=0;
	float fStep = 0.02,initialPressure[4]={0.0};

	float Pressures[5000][4]={0},VoltageOutputs[5000][4],PressureDots[5000][4]={0};

	// 20 ms icin Initialize		
	LARGE_INTEGER ticksPerSecond,start_ticks, end_ticks, cputime,tick;
	if (!QueryPerformanceFrequency(&ticksPerSecond))
	if (!QueryPerformanceCounter(&tick) ) printf("no go counter not installed");

	if((ActualPressureVoltagesANNET1 = fopen(".\\NeuralFiles\\TrainPressureVoltageANNET1.txt","w")) == NULL)
		printf("Dosya Acýlmadý\n");

	if((ActualPressureVoltagesANNET2 = fopen(".\\NeuralFiles\\TrainPressureVoltageANNET2.txt","w")) == NULL)
		printf("Dosya Acýlmadý\n");

	if((ActualPressureVoltagesANNET3 = fopen(".\\NeuralFiles\\TrainPressureVoltageANNET3.txt","w")) == NULL)
		printf("Dosya Acýlmadý\n");

	if((ActualPressureVoltagesANNET4 = fopen(".\\NeuralFiles\\TrainPressureVoltageANNET4.txt","w")) == NULL)
		printf("Dosya Acýlmadý\n");

	AO[0] = 5.0 ;AO[1] = 5.6 ;AO[2] = 5.6 ;AO[3] = 5.0 ;SetAnalogOutput(AO);

	initialPressure[0] = AO[0];initialPressure[1] = AO[1];initialPressure[2] = AO[2];initialPressure[3] = AO[3];
	
	Sleep(1000);

	for(j= 0;j<4;j++)  // FOR ALL Muscles
	{
		printf("Muscle NO :%d\n",j);
		i=0;AO[0] = 5.0 ;AO[1] = 5.6 ;AO[2] = 5.6 ;AO[3] = 5.0 ;SetAnalogOutput(AO);
		Sleep(1000);

		while (i<lDataNumber && CheckEmergency() && SwitchReadMotionStop() )
		{	
			QueryPerformanceCounter(&start_ticks);
				
			if(i<=100) 
				AO[j] += fStep ;
			if(i>100 && i<=400) 
				AO[j] -= fStep/3 ;
			if(i>400 && i<=600) 
				AO[j]=initialPressure[j]+sin(PI/200*((float)i-400));
			if(i>600 && i<=800) 
				if(i%10 == 1)
					AO[j] += 0.1;
			if(i>800 && i<=1000) 
				if(i%10 == 1)
					AO[j] -= 0.1;
			if(i>1000 && i<=1100) 
				AO[j] += fStep ;
			if(i>1100 && i<=1300) 
				AO[j] -= fStep ;
		

			//AO[j] = initialPressure[j]+2.2*sin(PI/100*i);

			SetAnalogOutput(AO);
			VoltageOutputs[i][j] = AO[j];

			GetAnalogInputs(AverageAnalogInputs);
			Pressures[i][j] = AverageAnalogInputs[j];
	
			i++;

			// Sleep 20 ms.   
			QueryPerformanceCounter(&end_ticks); printf("%f\n",(float)(end_ticks.QuadPart-start_ticks.QuadPart)/ticksPerSecond.QuadPart*1000);
			while(((float)(end_ticks.QuadPart-start_ticks.QuadPart)/ticksPerSecond.QuadPart*1000) < (float)20)
				QueryPerformanceCounter(&end_ticks); cputime.QuadPart = end_ticks.QuadPart- start_ticks.QuadPart;	
		}
	}
	for(j= 0;j<4;j++)  // FOR ALL Muscles
	{
		for(i = 0 ;i<lDataNumber-1 ; i++)
		{					
			PressureDots[i][j] = (Pressures[i+1][j] - Pressures[i][j])/20.0;
			if ( j==0 )
				fprintf(ActualPressureVoltagesANNET1,"%f  %f  %f\n",VoltageOutputs[i][j],Pressures[i+1][j],PressureDots[i][j]);
			if ( j==1 )
				fprintf(ActualPressureVoltagesANNET2,"%f  %f  %f\n",VoltageOutputs[i][j],Pressures[i+1][j],PressureDots[i][j]);
			if ( j==2 )
				fprintf(ActualPressureVoltagesANNET3,"%f  %f  %f\n",VoltageOutputs[i][j],Pressures[i+1][j],PressureDots[i][j]);
			if ( j==3 )
				fprintf(ActualPressureVoltagesANNET4,"%f  %f  %f\n",VoltageOutputs[i][j],Pressures[i+1][j],PressureDots[i][j]);
		}		
	}
	fclose(ActualPressureVoltagesANNET1);fclose(ActualPressureVoltagesANNET2);fclose(ActualPressureVoltagesANNET3);fclose(ActualPressureVoltagesANNET4);
	printf("Bitti\n");
}
		
#endif 
