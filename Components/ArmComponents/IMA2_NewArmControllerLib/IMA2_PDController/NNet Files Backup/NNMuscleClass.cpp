// Train.cpp: implementation of the CTrain class.
//
//////////////////////////////////////////////////////////////////////

//#include "Headers\NNMuscleClass.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <malloc.h>
#include <time.h>

#define PI 3.141592653589
#define Rate 8

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNNMuscles::CNNMuscles(int leftrightarmvalue, int anglenumbervalue, int forwardbackwardvalue)
{
	leftrightarm	= leftrightarmvalue;				// if leftrightarmvalue		= 1 --> LEFT arm
	anglenumber		= anglenumbervalue;					// if anglevalue			= 0 --> angle0 & =1 --> Angle1 ...5
	forwardbackward = forwardbackwardvalue;				// if forwardbackwardvalue	= 1 --> FORWARD
}

CNNMuscles::~CNNMuscles()
{
	
	delete vfuture_th;
	delete vpast_th;
	delete vpresent_th;
	delete z;
	delete z_in;

	for(j=0;j<nNeuron;j++)
	{
		free(*(wpresent+j));
		free(*(wpast+j));
		free(*(wfuture+j));
		free(*(deltaw+j));
	}
	free(wpresent);
	free(wpast);
	free(wfuture);
	free(deltaw);

	for(i=0;i<nInput;i++)
	{
		free(*(vpresent+i));
		free(*(vpast+i));
		free(*(vfuture+i));
		free(*(deltav+i));
	}
	free(vpresent);
	free(vpast);
	free(vfuture);
	free(deltav);

	for(t=0;t<m;t++)
	free(*(inputx+t));
	free(inputx);
}

void CNNMuscles::Allocator(void)
{

	using namespace std;

	nInput  = 1;
	nNeuron = 50;

	int		sillybuffer1;
	float	sillybuffer2;

	FILE *weights;
	
	// Left Arm Files
	if (leftrightarm ==1 && anglenumber == 0 && forwardbackward == 1)
		if((weights = fopen(".\\NNWeights\\LeftNNmuscle01FWeights.txt","r")) == NULL)
			//printf("Can't Open File LeftNNmuscle01FWeights.txt\n");
	if (leftrightarm ==1 && anglenumber == 0 && forwardbackward == -1)
		if((weights = fopen(".\\NNWeights\\LeftNNmuscle01BWeights.txt","r")) == NULL)
			//printf("Can't Open File LeftNNmuscle01FWeights.txt\n");
	
	if (leftrightarm ==1 && anglenumber == 1 && forwardbackward == 1)
		if((weights = fopen(".\\NNWeights\\LeftNNmuscle23FWeights.txt","r")) == NULL)
			//printf("Can't Open File LeftNNmuscle23FWeights.txt\n");
	if (leftrightarm ==1 && anglenumber == 1 && forwardbackward == -1)
		if((weights = fopen(".\\NNWeights\\LeftNNmuscle23BWeights.txt","r")) == NULL)
			//printf("Can't Open File LeftNNmuscle23BWeights.txt\n");

	if (leftrightarm ==1 && anglenumber == 2 && forwardbackward == 1)
		if((weights = fopen(".\\NNWeights\\LeftNNmuscle4567Angle2FWeights.txt","r")) == NULL)
			//printf("Can't Open File LeftNNmuscle4567Angle2FWeights.txt\n");
	if (leftrightarm ==1 && anglenumber == 2 && forwardbackward == -1)
		if((weights = fopen(".\\NNWeights\\LeftNNmuscle4567Angle2BWeights.txt","r")) == NULL)
			//printf("Can't Open File LeftNNmuscle4567Angle2BWeights.txt\n");

	if (leftrightarm ==1 && anglenumber == 3 && forwardbackward == 1)
		if((weights = fopen(".\\NNWeights\\LeftNNmuscle4567Angle3FWeights.txt","r")) == NULL)
			//printf("Can't Open File LeftNNmuscle4567Angle3FWeights.txt\n");
	if (leftrightarm ==1 && anglenumber == 3 && forwardbackward == -1)
		if((weights = fopen(".\\NNWeights\\LeftNNmuscle4567Angle3BWeights.txt","r")) == NULL)
			//printf("Can't Open File LeftNNmuscle4567Angle3BWeights.txt\n");

	if (leftrightarm ==1 && anglenumber == 4 && forwardbackward == 1)
		if((weights = fopen(".\\NNWeights\\LeftNNmuscle891011Angle4FWeights.txt","r")) == NULL)
			//printf("Can't Open File LeftNNmuscle891011Angle4FWeights.txt\n");
	if (leftrightarm ==1 && anglenumber == 4 && forwardbackward == -1)
		if((weights = fopen(".\\NNWeights\\LeftNNmuscle891011Angle4BWeights.txt","r")) == NULL)
			//printf("Can't Open File LeftNNmuscle891011Angle4BWeights.txt\n");

	if (leftrightarm ==1 && anglenumber == 5 && forwardbackward == 1)
		if((weights = fopen(".\\NNWeights\\LeftNNmuscle891011Angle5FWeights.txt","r")) == NULL)
			//printf("Can't Open File LeftNNmuscle891011Angle4FWeights.txt\n");
	if (leftrightarm ==1 && anglenumber == 5 && forwardbackward == -1)
		if((weights = fopen(".\\NNWeights\\LeftNNmuscle891011Angle5BWeights.txt","r")) == NULL)
			//printf("Can't Open File LeftNNmuscle891011Angle5BWeights.txt\n");
	
	// Right Arm Files
	if (leftrightarm ==0 && anglenumber == 0 && forwardbackward == 1)
		if((weights = fopen(".\\NNWeights\\RightNNmuscle01FWeights.txt","r")) == NULL)
			//printf("Can't Open File RightNNmuscle01FWeights.txt\n");
	if (leftrightarm ==0 && anglenumber == 0 && forwardbackward == -1)
		if((weights = fopen(".\\NNWeights\\RightNNmuscle01BWeights.txt","r")) == NULL)
			//printf("Can't Open File RightNNmuscle01FWeights.txt\n");
	
	if (leftrightarm ==0 && anglenumber == 1 && forwardbackward == 1)
		if((weights = fopen(".\\NNWeights\\RightNNmuscle23FWeights.txt","r")) == NULL)
			//printf("Can't Open File RightNNmuscle23FWeights.txt\n");
	if (leftrightarm ==0 && anglenumber == 1 && forwardbackward == -1)
		if((weights = fopen(".\\NNWeights\\RightNNmuscle23BWeights.txt","r")) == NULL)
			//printf("Can't Open File RightNNmuscle23BWeights.txt\n");

	if (leftrightarm ==0 && anglenumber == 2 && forwardbackward == 1)
		if((weights = fopen(".\\NNWeights\\RightNNmuscle4567Angle2FWeights.txt","r")) == NULL)
			//printf("Can't Open File RightNNmuscle4567Angle2FWeights.txt\n");
	if (leftrightarm ==0 && anglenumber == 2 && forwardbackward == -1)
		if((weights = fopen(".\\NNWeights\\RightNNmuscle4567Angle2BWeights.txt","r")) == NULL)
			//printf("Can't Open File RightNNmuscle4567Angle2BWeights.txt\n");

	if (leftrightarm ==0 && anglenumber == 3 && forwardbackward == 1)
		if((weights = fopen(".\\NNWeights\\RightNNmuscle4567Angle3FWeights.txt","r")) == NULL)
			//printf("Can't Open File RightNNmuscle4567Angle3FWeights.txt\n");
	if (leftrightarm ==0 && anglenumber == 3 && forwardbackward == -1)
		if((weights = fopen(".\\NNWeights\\RightNNmuscle4567Angle3BWeights.txt","r")) == NULL)
			//printf("Can't Open File RightNNmuscle4567Angle3BWeights.txt\n");

	if (leftrightarm ==0 && anglenumber == 4 && forwardbackward == 1)
		if((weights = fopen(".\\NNWeights\\RightNNmuscle891011Angle4FWeights.txt","r")) == NULL)
			//printf("Can't Open File RightNNmuscle891011Angle4FWeights.txt\n");
	if (leftrightarm ==0 && anglenumber == 4 && forwardbackward == -1)
		if((weights = fopen(".\\NNWeights\\RightNNmuscle891011Angle4BWeights.txt","r")) == NULL)
			//printf("Can't Open File RightNNmuscle891011Angle4BWeights.txt\n");

	if (leftrightarm ==0 && anglenumber == 5 && forwardbackward == 1)
		if((weights = fopen(".\\NNWeights\\RightNNmuscle891011Angle5FWeights.txt","r")) == NULL)
			//printf("Can't Open File RightNNmuscle891011Angle4FWeights.txt\n");
	if (leftrightarm ==0 && anglenumber == 5 && forwardbackward == -1)
		if((weights = fopen(".\\NNWeights\\RightNNmuscle891011Angle5BWeights.txt","r")) == NULL)
			//printf("Can't Open File RightNNmuscle891011Angle5BWeights.txt\n");

	fscanf(weights,"%d\n",&nNeuron); 
	fscanf(weights,"%f\n",&sillybuffer2);
	fscanf(weights,"%f\n",&sillybuffer2);
	fscanf(weights,"%d\n",&sillybuffer1);
	fscanf(weights,"%d\n",&sillybuffer1);
	fscanf(weights,"%d\n",&nInput);

	srand( (unsigned)time( NULL ) );

	//1*10
	z_in = (float*)malloc(nNeuron*sizeof(float));

	//1*10
	z = (float*)malloc(nNeuron*sizeof(float));

	//1*10
	delta_in = (float*)malloc(nNeuron*sizeof(float));

	//1*10
	delta_hidden = (float*)malloc(nNeuron*sizeof(float));

	//1*10
	deltav_th = (float*)malloc(nNeuron*sizeof(float));

	// 14*10
	deltav = (float**)malloc(nInput*sizeof(float*));
	for(i=0;i<nInput;i++)
		*(deltav+i) = (float*)malloc(nNeuron*sizeof(float));

	//10*2
	deltaw = (float**)malloc(nNeuron*sizeof(float*));
	for(i=0;i<nNeuron;i++)
		*(deltaw+i) = (float*)malloc(2*sizeof(float));

	//random 10*2
	wpresent = (float**)malloc(nNeuron*sizeof(float*));
	for(i=0;i<nNeuron;i++)
		*(wpresent+i) = (float*)malloc(2*sizeof(float));

	//random 10*2
	wpast = (float**)malloc(nNeuron*sizeof(float*));
	for(i=0;i<nNeuron;i++)
		*(wpast+i) = (float*)malloc(2*sizeof(float));

	//random 10*2
	wfuture = (float**)malloc(nNeuron*sizeof(float*));
	for(i=0;i<nNeuron;i++)
		*(wfuture+i) = (float*)malloc(2*sizeof(float));

	//random 1*10
	vpresent_th = (float*)malloc(nNeuron*sizeof(float));

	//random 1*10
	vpast_th = (float*)malloc(nNeuron*sizeof(float));

	//random 1*10
	vfuture_th = (float*)malloc(nNeuron*sizeof(float));

	//random 14*10
	vpresent = (float**)malloc(nInput*sizeof(float*));
	for(i=0;i<nInput;i++)
		*(vpresent+i) = (float*)malloc(nNeuron*sizeof(float));

	//random 14*10
	vpast = (float**)malloc(nInput*sizeof(float*));
	for(i=0;i<nInput;i++)
		*(vpast+i) = (float*)malloc(nNeuron*sizeof(float));

	//random 14*10
	vfuture = (float**)malloc(nInput*sizeof(float*));
	for(i=0;i<nInput;i++)
		*(vfuture+i) = (float*)malloc(nNeuron*sizeof(float));

	m=1;
	//***********************READING WEIGHTS NINPUTS AND NEURONS***************************

	for (k=0;k<1;k++)
	{
		for (j=0;j<nNeuron;j++)
			fscanf(weights,"%f\n",&wfuture[j][k]);
		fscanf(weights,"%f\n",&wfuture_th[k]); 
	}

	for(j=0;j<nNeuron;j++)
	{
		for(i=0;i<nInput;i++)
			fscanf(weights,"%f\n",&vfuture[i][j]);
	}

	for(j=0;j<nNeuron;j++)
		fscanf(weights,"%f\n",&vfuture_th[j]);

	//***************END OF READING********************************************

	inputx = (float**)malloc(m*sizeof(float*));
	for(i=0;i<m;i++)
		*(inputx+i) = (float*)malloc(nInput*sizeof(float));

	fclose(weights);
}

/***************************************************
* Process(input, output)
*
* Input	 = DesiredThetaAngle[i]
* Output = Corresponding Voltage[i]
*
* Uses results from the trained nerual net to assign
* the corresponding voltage to the desired position.
*
* Angles are normalized to fit neural net structure.
***************************************************/
void CNNMuscles::Process(float *input,float *output)
{
	inputx[0][0] = *input;

	// Left Arm
	if (leftrightarm == 1 && anglenumber == 0)
		// Normalize angles for forward motion. Convert range of -65deg:+25deg to 0:1.
		inputx[0][0] = (inputx[0][0] + 65) / 90;

	// Right Arm
	if (leftrightarm ==0 && anglenumber == 0)
		// Normalize angles for forward motion. Convert range of -25deg:+55deg to 0:1.
		inputx[0][0] = (inputx[0][0] + 25) / 80;

	if (anglenumber == 1 )
		// Normalizing the input 40-125 to 0-1
		inputx[0][0] = (inputx[0][0] - 40) / 85;

	if (anglenumber == 2)
		// Normalizing the input -215 & -130 to 0-1
		inputx[0][0] = (inputx[0][0] + 215) / 75;

	if (anglenumber == 3)
		// Normalizing the input -40 & 30 to 0-1
		inputx[0][0] = (inputx[0][0] + 40) / 70;

	if (anglenumber == 4)
		// Normalizing the input -40 && 40 to 0-1
		inputx[0][0] = (inputx[0][0] +40) / 80;

	if (anglenumber == 5)
		// Normalizing the input -70 & 70 to 0-1
		inputx[0][0] = (inputx[0][0] +70)/ 140;
	
	for(t=0;t<1;t++) // m =1 m is the data number
	{
		y_in[0] = wfuture_th[0];

		for(j=0;j<nNeuron;j++)
		{
			z_in[j] = vfuture_th[j];

			for(i=0;i<1;i++)	// nInput yerine 1 yazýyoruz , nInput data sayýsý
				z_in[j] += inputx[t][i] * vfuture[i][j];

				// Compute the following activation function, tansig:   n = 2/(1+exp(-2*n))-1
				z[j]= 2/(1+exp(-2*z_in[j]))-1;
				y_in[0] += z[j] * wfuture[j][0];
		}
			// Returns voltage associated with joint angle
			*output = y_in[0];
	}					
}
