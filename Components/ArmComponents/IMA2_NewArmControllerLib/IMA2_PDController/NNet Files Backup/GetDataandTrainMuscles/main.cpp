#include "../Headers\stdafx.h"
#include <windows.h>
#include <windef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <stdarg.h>
#include <math.h>
#include <IOSTREAM>
#include "../Headers\Control.h"
#include "../Headers\Train01.h"
#include "../Headers\Train23.h"
#include "../Headers\Train4567Angle2.h"
#include "../Headers\Train4567Angle3.h"
#include "../Headers\Train891011Angle4.h"
#include "../Headers\Train891011Angle5.h"
#include "../Headers\SampleAndTrainAll.h"

using namespace std;

double leftValvesOutputs[12]={0};
double leftValvesInputs[12]={0};
double InitialleftValvesOutputs[12];
long leftEncoders[6]={0};
double leftAngles[6]={0};

double rightValvesOutputs[12]={0};
double rightValvesInputs[12]={0};
double rightleftValvesOutputs[12];
double InitialrightValvesOutputs[12];
long rightEncoders[6]={0};
double rightAngles[6]={0};

double incrementalVoltage = 0.0, incrementalVoltage1 = 0.0;

void  main()
{
	InitializeCards(); //InitializeLeftValves();
	InitializeAllValves();
	Sleep(3000);
	//ResetRightEncoders();ResetLeftEncoders();
	//while(!kbhit()) {ReadRightEncoders();RealRightAngles();Sleep(50);}
	CloseValves();Sleep(500);
	vitalQuit();Sleep(100);
	//InitializeCards();CloseRightGripper();Sleep(3500);OpenRightGripper();vitalQuit();Sleep(100);

	// SampleForNeuralTrain01Angle0(arm) means taking sample for training 0 & 1 muscles for angle 0. If
	// arm is 0 --> right and if arm =1 --> left arm
	//SampleForNeuralTrain01Angle0(0);
	//SampleForNeuralTrain23Angle1(0);
	//SampleForNeuralTrain4567Angle2(0);
	//SampleForNeuralTrain4567Angle3(0);
	//SampleForNeuralTrain891011Angle4(0);
	//SampleForNeuralTrain891011Angle5(0);

	//Train01(-1,1); // (backward(-1)/forward(1),leftright(1 for left, right=0)) , data number 135 for F (163 for right arm) & 163 for B (135 for right arm),normalized between -65 & +25 to 0-1
	//Train23(-1,1); // -1 corresponds to backward 1 corresponds to fwd, data number for F 267 and for B 261, normalized between 58 & 130 to 0-1
	//Train4567Angle2(1,-1); // -1 corresponds to backward 1 corresponds to fwd, data number 208, normalized between -145 & -210 to 0-1.
	//Train4567Angle3(-1,0); // -1 corresponds to backward 1 corresponds to fwd, data number 108, normalized between -40 & 30 to 0-1.
	// 20 neurons + 50000 epoch --> sqrt(mse))= 0.0282 & 10 neurons + 100000 epoch (sqrt(mse)) = 0.0290 for forward 
	// & 10 neurons + 250000 epoch (sqrt(mse)) = 0.0220 for forward
	
	//Train891011Angle4(-1,0); // -1 corresponds to backward 1 corresponds to fwd, data number 198, normalized between -40 & 40 to 0-1.
	//Train891011Angle5(1,0); // -1 corresponds to backward 1 corresponds to fwd, data number 199 for F 198  for B, normalized between -70 & 70 to 0-1.

	Beep(200,100);

}




