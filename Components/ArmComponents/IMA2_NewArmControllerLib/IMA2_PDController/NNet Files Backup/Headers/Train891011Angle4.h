// Train.h: interface for the CTrain class.
//
//////////////////////////////////////////////////////////////////////
#ifndef _Train891011Angle4_h
#define _Train891011Angle4_h

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <malloc.h>
#include <time.h>

class CNNMuscles891011Angle4    
{
public:
	CNNMuscles891011Angle4(int m, int leftright);
	virtual ~CNNMuscles891011Angle4();
	void Allocator(void); // 
	void Input(void); // 
	void ProcessUpperLink(float *input,float *output); // 
	void Process();
	void WeightsWrite(void); // 
	void IsExist(void);
	int forwardvalue;
	int leftorrightarm;

private:
	int i, j, k, t, n;
	long epochs;
	int nNeuron;
	int nInput;

	FILE *TrainData,*weights,*hata;

	float wpresent_th[2];//random
	float wpast_th[2];//random
	float wfuture_th[2];//random
	float y_in[2];
	float delta[2];
	float deltaw_th[2];

	int m;
	double alfa;//0.001;////0.00001;////0.001 ;//learning rate
	float mm;
	float *T1; 
	float y1;
	float a;

	float **inputx;
	float *z_in;
	float *z;
	float *delta_in;
	float *delta_hidden;
	float *deltav_th;
	float **deltav;
	float **deltaw;
	float **wpresent;
	float **wpast;
	float **wfuture;
	float *vpresent_th;
	float *vpast_th;
	float **vpresent;
	float **vpast;
	float **vfuture;
	float *vfuture_th;

};

#endif 
