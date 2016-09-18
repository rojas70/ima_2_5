// Train.h: interface for the CTrain class.
//
//////////////////////////////////////////////////////////////////////
#ifndef _NNMuscleClass_h
#define _NNMuscleClass_h

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <malloc.h>
#include <time.h>

class CNNMuscles  
{
public:
	CNNMuscles(int leftrightarm, int anglenumber, int forwardbackward);
	virtual ~CNNMuscles();
	void Allocator(void); // 
	void Input(void); // 
	void Process(float *input,float *output); // 
	void Process();
	void WeightsWrite(void); // 
	void IsExist(void);

	int forwardbackward;
	int leftrightarm;
	int anglenumber;

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
