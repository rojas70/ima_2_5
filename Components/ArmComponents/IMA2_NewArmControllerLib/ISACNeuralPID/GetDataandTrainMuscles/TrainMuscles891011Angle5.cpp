// Train.cpp: implementation of the CTrain class.
//
//////////////////////////////////////////////////////////////////////

#include "../Headers\Train891011Angle5.h"
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

CNNMuscles891011Angle5::CNNMuscles891011Angle5(int m, int leftright)
{
	forwardvalue = m;
	leftorrightarm = leftright;
}

CNNMuscles891011Angle5::~CNNMuscles891011Angle5()
{
	fclose(TrainData);
	fclose(weights)   ;
	fclose(hata)     ;
	
	delete vfuture_th;
	delete vpast_th;
	delete vpresent_th;
	delete T1; 
	delete z;
	delete z_in;
	delete deltav_th;
	delete delta_hidden;
	delete delta_in;

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

void CNNMuscles891011Angle5::Allocator(void)
{
	using namespace std;
	nInput = 1;// sadece voltaj   nInput = 13;
	y1 = 0;

	cout << "Please enter the number of neurons: " << endl;
	cin >> nNeuron;

	cout << "Please enter learning rate: " << endl;
	cin >> alfa;

	cout << "Please enter momentum constant: " << endl;
	cin >> mm;

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

 
   for( k = 0;k<1;k++ )
   {
	    wpresent_th[k]=0.01*(rand()%100);
		wpast_th[k]=0.01*(rand()%100);
		wfuture_th[k]=0.01*(rand()%100);
   }
   for(j=0;j<nNeuron;j++)
   {
	   for(k=0;k<1;k++)
	   {
	   	wpresent[j][k]=0.01*(rand()%100);
		wpast[j][k]=0.01*(rand()%100);
		wfuture[j][k]=0.01*(rand()%100);
	   }
   }
   for( j= 0;j<nNeuron;j++ )
   {
	    vpresent_th[j]=0.01*(rand()%100);
		vpast_th[j]=0.01*(rand()%100);
		vfuture_th[j]=0.01*(rand()%100);
   }
   for(i=0;i<(nInput);i++)
   {
	   for (j=0;j<nNeuron;j++)
	   {
		   vpresent[i][j]=0.01*(rand()%100);
		   vpast[i][j]   =0.01*(rand()%100);
		   vfuture[i][j] =0.01*(rand()%100);
	   }
	}
	printf("Enter data number \n");
	scanf("%d",&m);

	inputx = (float**)malloc(m*sizeof(float*));
	for(i=0;i<m;i++)
		*(inputx+i) = (float*)malloc(nInput*sizeof(float));

	T1    = (float*)malloc(sizeof (float)*m);
	
	printf("Enter how many epochs you want to use in the training = \n");
	scanf("%d",&epochs);
}

void CNNMuscles891011Angle5::IsExist(void)
{
	if (leftorrightarm) //Left Arm
		{
			if ( forwardvalue ==1 )
			{
				if ((weights=fopen("..\\NNWeights\\LeftNNmuscle891011Angle5FWeights.txt","w"))==NULL)		
					printf("Can't Open File LeftNNmuscle891011Angle5FWeights.txt\n");
					
				if( (TrainData=fopen( "..\\TrainFiles\\LeftNeuralDataForward891011Angle5.txt", "r" )) == NULL )
					printf( "Can't Open File LeftNeuralDataForward891011Angle5.txt\n" );

				if ((hata=fopen("..\\NNWeights\\LeftNNmuscle891011Angle5FWeightsErrors.txt","w"))==NULL)		
					printf("Can't Open File LeftNNmuscle891011Angle5FWeightsErrors.txt\n");

			}else 
			{
				if ((weights=fopen("..\\NNWeights\\LeftNNmuscle891011Angle5BWeights.txt","w"))==NULL)		
					printf("Can't Open File LeftNNmuscle891011Angle4BWeights.txt\n");
					
				if( (TrainData=fopen( "..\\TrainFiles\\LeftNeuralDataBackward891011Angle5.txt", "r" )) == NULL )
					printf( "Can't Open File LeftNeuralDataBackward891011Angle5.txt\n" );

				if ((hata=fopen("..\\NNWeights\\LeftNNmuscle891011Angle5BWeightsErrors.txt","w"))==NULL)		
					printf("Can't Open File LeftNNmuscle891011Angle5BWeightsErrors.txt\n");
			}
		}
		
		if (!leftorrightarm) //Right Arm
		{
			if ( forwardvalue ==1 )
			{
				if ((weights=fopen("..\\NNWeights\\RightNNmuscle891011Angle5FWeights.txt","w"))==NULL)		
					printf("Can't Open File RightNNmuscle891011Angle5FWeights.txt\n");
					
				if( (TrainData=fopen( "..\\TrainFiles\\RightNeuralDataForward891011Angle5.txt", "r" )) == NULL )
					printf( "Can't Open File RightNeuralDataForward891011Angle5.txt\n" );

				if ((hata=fopen("..\\NNWeights\\RightNNmuscle891011Angle5FWeightsErrors.txt","w"))==NULL)		
					printf("Can't Open File RightNNmuscle891011Angle5FWeightsErrors.txt\n");

			}else 
			{
				if ((weights=fopen("..\\NNWeights\\RightNNmuscle891011Angle5BWeights.txt","w"))==NULL)		
					printf("Can't Open File RightNNmuscle891011Angle5BWeights.txt\n");
					
				if( (TrainData=fopen( "..\\TrainFiles\\RightNeuralDataBackward891011Angle5.txt", "r" )) == NULL )
					printf( "Can't Open File RightNeuralDataBackward891011Angle5.txt\n" );

				if ((hata=fopen("..\\NNWeights\\RightNNmuscle891011Angle5BWeightsErrors.txt","w"))==NULL)		
					printf("Can't Open File RightNNmuscle891011Angle5BWeightsErrors.txt\n");
			}
		}
}

void CNNMuscles891011Angle5::Input(void)
{
	for (t=0;t<(m);t++)
		for (i=0;i<nInput;i++)
			inputx[t][i]  =0;		

	for(t=0;t<m;t++)	
		fscanf(TrainData,"%f %f\n",&T1[t],&inputx[t][0]);
	
	// Here Normalizing the Angles.changes between -70 & +70 to 0-1 
	for(t=0;t<m;t++)
		inputx[t][0] = (inputx[t][0] +70)/ 140;

}

void CNNMuscles891011Angle5::Process(void)
{
	clock_t cTimePass;clock();long iRemainingTime;
	cTimePass = clock();

	for(n=0;n<epochs;n++)		// How many times will we train this?
	{
		// How much time left?
		if ( n == 100 )
		{
			iRemainingTime =(long) (clock() - cTimePass) * ( epochs - 100 ) / 1000 / 100 ;
			printf("Time Remaining (approx.) : %d seconds.\n",iRemainingTime);
		}

		for(t=0;t<m;t++)
		{
			y_in[0] = wfuture_th[0];
			for(j=0;j<nNeuron;j++)
			{
				z_in[j] = vfuture_th[j];
				for(i=0;i<nInput;i++)
				{

					z_in[j] += inputx[t][i] * vfuture[i][j];
				}
				z[j]= 2/(1+exp(-2*z_in[j]))-1;// activation function: tansig   n = 2/(1+exp(-2*n))-1
			//	z[j] = 1/(1+exp(-(z_in[j])));
				y_in[0] += z[j] * wfuture[j][0];
			}
		
			y1=y_in[0];
	
			delta[0]=(T1[t]-y1);
	
			for(j=0;j<nNeuron;j++)
			{
				deltaw[j][0] = alfa*delta[0]*z[j];
			}
	
			deltaw_th[0]=alfa*delta[0];
	
			for(j=0;j<nNeuron;j++)
				delta_in[j] = delta[0]*wfuture[j][0]; //+ delta[1]*wfuture[j][1]	;	

			for(j=0;j<nNeuron;j++)
			{
				//activation func:tansig

				delta_hidden[j]=delta_in[j]*(4*exp(-2*z_in[j]))/((1+exp(-2*z_in[j]))*(1+exp(-2*z_in[j])));
				deltav_th[j] = alfa * delta_hidden[j];
			}

			for (j=0;j<nNeuron;j++)
				for(i=0;i<nInput;i++)
					deltav[i][j] = alfa*(inputx[t][i])*(delta_hidden[j]);
	
			for (k=0;k<1;k++)
			{
				for (j=0;j<nNeuron;j++)
				{
					wfuture[j][k] = wpresent[j][k]+deltaw[j][k]+mm*(wpresent[j][k]-wpast[j][k]);
					wpast[j][k]	= wpresent[j][k];
					wpresent[j][k] = wfuture[j][k];
				}
				
				wfuture_th[k] = wpresent_th[k]+deltaw_th[k]+mm*(wpresent_th[k]-wpast_th[k]);
				wpast_th[k]	= wpresent_th[k];
				wpresent_th[k] = wfuture_th[k];
			}

			for(j=0;j<nNeuron;j++)
			{
				for(i=0;i<nInput;i++)
				{
					vfuture[i][j] = vpresent[i][j] + deltav[i][j] + mm*(vpresent[i][j]-vpast[i][j]);
					vpast[i][j] = vpresent[i][j];
					vpresent[i][j] = vfuture[i][j];
				}
				vfuture_th[j] = vpresent_th[j] + deltav_th[j] + mm*(vpresent_th[j]-vpast_th[j]);
				vpast_th[j] = vpresent_th[j];
				vpresent_th[j] = vfuture_th[j];
			}
		}	
	}
	for(t=0;t<m;t++) // m yerine 1 yazýyoruz , m data sayýsý
	{
		y_in[0] = wfuture_th[0];
		for(j=0;j<nNeuron;j++)
		{
			z_in[j] = vfuture_th[j];
			for(i=0;i<1;i++)	// nInput yerine 1 yazýyoruz , nInput data sayýsý
			{
				z_in[j] += inputx[t][i] * vfuture[i][j];
			}
			z[j]= 2/(1+exp(-2*z_in[j]))-1;// activation function: tansig   n = 2/(1+exp(-2*n))-1
			y_in[0] += z[j] * wfuture[j][0];
		}	
		a=T1[t]-y_in[0];
		fprintf(hata,"%f\n",a);
	}		
}

void CNNMuscles891011Angle5::WeightsWrite(void)
{
	fprintf(weights,"%d\n",nNeuron);
	fprintf(weights,"%f\n",alfa);
	fprintf(weights,"%f\n",mm);
	fprintf(weights,"%d\n",m);
	fprintf(weights,"%d\n",epochs);
	fprintf(weights,"%d\n",nInput);

	for (k=0;k<1;k++)
	{
		for (j=0;j<nNeuron;j++)
			fprintf(weights,"%f\n",wfuture[j][k]);
		fprintf(weights,"%f\n",wfuture_th[k]);
	}
	
	for(j=0;j<nNeuron;j++)
	{
		for(i=0;i<nInput;i++)
			fprintf(weights,"%f\n",vfuture[i][j]);
	}

	for(j=0;j<nNeuron;j++)
		fprintf(weights,"%f\n",vfuture_th[j]);
}

