#ifndef _MahirKinematics_h
#define _MahirKinematics_h


#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <iostream>
#include <float.h>

#define PI 3.14159265

///*extern*/ double *alpha,*a,*d,*theta;
double *alpha = new double[6];
double *a = new double[6];
double *d = new double[6];
double *theta = new double[6];
/*extern*/ double **rotation;
///*extern*/ double **limitsOfThetas;
double limitsOfThetas[6][2];

/*extern*/ double **T01;
/*extern*/ double **T12;
/*extern*/ double **T23;
/*extern*/ double **T34;
/*extern*/ double **T45;
/*extern*/ double **T56;

/*extern*/ double **T02;
/*extern*/ double **T03;
/*extern*/ double **T04;
/*extern*/ double **T05;
/*extern*/ double **T06;

///*extern*/ double *j1Pos;
///*extern*/ double *j2Pos;
///*extern*/ double *j3Pos;
///*extern*/ double *j4Pos;
///*extern*/ double *j5Pos;
///*extern*/ double *j6Pos;
///*extern*/ double *endEffPos;
double *j1Pos = new double[3];
double *j2Pos = new double[3];
double *j3Pos = new double[3];
double *j4Pos = new double[3];
double *j5Pos = new double[3];
double *j6Pos = new double[3];
double *endEffPos = new double[3];


/*extern*/ double lengthOfEndEff;

void initializeParameters(){

	lengthOfEndEff = 270;

	//limitsOfThetas = (double**)malloc(6*sizeof(double*));
	//for( int i = 0; i < 6; i++)
	//	limitsOfThetas[i] = (double*)malloc(2*sizeof(double));
		
	limitsOfThetas[0][0] = -60*PI/180.0;
	limitsOfThetas[0][1] = 35*PI/180.0;

	limitsOfThetas[1][0] = 40*PI/180.0;
	limitsOfThetas[1][1] = 125*PI/180.0;

	limitsOfThetas[2][0] = -210*PI/180.0;
	limitsOfThetas[2][1] = -100*PI/180.0;

	limitsOfThetas[3][0] = -16*PI/180.0;
	limitsOfThetas[3][1] = 19*PI/180.0;

	limitsOfThetas[4][0] = -60*PI/180.0;
	limitsOfThetas[4][1] = 60*PI/180.0;

	limitsOfThetas[5][0] = -70*PI/180.0;
	limitsOfThetas[5][1] = 70*PI/180.0;


	//alpha = (double*)malloc(6*sizeof(double));
	//a = (double*)malloc(6*sizeof(double));
	//d = (double*)malloc(6*sizeof(double));
	//theta = (double*)malloc(6*sizeof(double));

	
	alpha[0] = 0;
	alpha[1] = -PI/2;
	alpha[2] = 0;
	alpha[3] = -PI/2;
	alpha[4] = PI/2;
	alpha[5] = -PI/2;

	a[0] = 0;
	a[1] = 0;
	a[2] = 330;
	a[3] = 0;
	a[4] = 0;
	a[5] = 0;

	d[0] = 0;
	d[1] = 0;
	d[2] = 200;
	d[3] = 290;
	d[4] = 0;
	d[5] = 0;
	
}

double** matrixMultiply( double **R1, double **R2 ){
	//double **result;
	//result = (double**)malloc(3*sizeof(double*));
	double **result = new double *[3];

	for( int i = 0; i < 3; i++){
		//result[i] = (double*)malloc(3*sizeof(double));
		result[i] = new double[3];
		for( int j = 0; j < 3; j++ ){
			result[i][j] = R1[i][0]*R2[0][j] + R1[i][1]*R2[1][j] + R1[i][2]*R2[2][j];
		}
	}
	
	return result;
}



double distanceOfThetas(double *thetas, double *prevThetas){
	double result = 0.0;
	
	for( int i = 0; i < 6; i++ )
		result += (thetas[i]-prevThetas[i])*(thetas[i]-prevThetas[i]);

	return sqrt(result);
}

int checkForLimitations(double *thetas){
	//return 0; //For testing kinematics
	if( limitsOfThetas[0][0] > thetas[0] || limitsOfThetas[0][1] < thetas[0] )
		return 1;
	
	if( limitsOfThetas[1][0] > thetas[1] || limitsOfThetas[1][1] < thetas[1] )
		return 1;
	
	if( limitsOfThetas[2][0] > thetas[2] || limitsOfThetas[2][1] < thetas[2] )
		return 1;
	
	if( limitsOfThetas[3][0] > thetas[3] || limitsOfThetas[3][1] < thetas[3] )
		return 1;
	
	if( limitsOfThetas[4][0] > thetas[4] || limitsOfThetas[4][1] < thetas[4] )
		return 1;
	if( limitsOfThetas[5][0] > thetas[5] || limitsOfThetas[5][1] < thetas[5] )
		return 1;

	return 0;
}


double** createRotationMatrixInitialToEnd(double alpha, double beta, double gamma){
	//Here euler angles will be used for simplification
	double **result;
	double **result1 = new double*[3];
	double **result2 = new double*[3];
	double **result3 = new double*[3];
	
	//printf("\naplha = %lf\n", beta);
	//result1 = (double**)malloc(3*sizeof(double*));
	for( int i = 0; i < 3; i++)
		result1[i] = new double[3];
	//	result1[i] = (double*)malloc(3*sizeof(double));

	//result2 = (double**)malloc(3*sizeof(double*));
	for( i = 0; i < 3; i++)
		result2[i] = new double[3];
	//	result2[i] = (double*)malloc(3*sizeof(double));

	//result3 = (double**)malloc(3*sizeof(double*));
	for( i = 0; i < 3; i++)
		result3[i] = new double[3];
	//	result3[i] = (double*)malloc(3*sizeof(double));
	
	
	
	result1[0][0] = 1;
	result1[0][1] = 0;
	result1[0][2] = 0;
	
	result1[1][0] = 0;
	result1[1][1] = cos(alpha);
	result1[1][2] = -sin(alpha);
	
	result1[2][0] = 0;
	result1[2][1] = sin(alpha);
	result1[2][2] = cos(alpha);

	
	result2[0][0] = cos(beta);
	result2[0][1] = 0;
	result2[0][2] = -sin(beta);
	
	result2[1][0] = 0;
	result2[1][1] = 1;
	result2[1][2] = 0;
	
	result2[2][0] = sin(beta);
	result2[2][1] = 0;
	result2[2][2] = cos(beta);

	
	result3[0][0] = cos(gamma);
	result3[0][1] = -sin(gamma);
	result3[0][2] = 0;
	
	result3[1][0] = sin(gamma);
	result3[1][1] = cos(gamma);
	result3[1][2] = 0;
	
	result3[2][0] = 0;
	result3[2][1] = 0;
	result3[2][2] = 1;
	
	result = matrixMultiply(result1,result2);
	result = matrixMultiply(result,result3);

	/*
	for(i = 0; i < 3; i++)
	{
		free(result1[i]);
		free(result2[i]);
		free(result3[i]);
	}
	*/
	delete result1;
	delete result2;
	delete result3;

	
	return result;

}

double** createRotationMatrixBaseToInitial(double gamma, double beta, double alpha){
	//double **result;
	//printf("\naplha = %lf\n", beta);
	//result = (double**)malloc(3*sizeof(double*));
	double ** result = new double*[3];
	for( int i = 0; i < 3; i++)
		result[i] = new double[3];
	//	result[i] = (double*)malloc(3*sizeof(double));

	result[0][0] = cos(alpha)*cos(beta);
	result[0][1] = cos(alpha)*sin(beta)*sin(gamma)-sin(alpha)*cos(gamma);
	result[0][2] = cos(alpha)*sin(beta)*cos(gamma)+sin(alpha)*sin(gamma);
	

	result[1][0] = sin(alpha)*cos(beta);
	result[1][1] = sin(alpha)*sin(beta)*sin(gamma)+cos(alpha)*cos(gamma);
	result[1][2] = sin(alpha)*sin(beta)*cos(gamma)-cos(alpha)*sin(gamma);
	

	result[2][0] = -sin(beta);
	result[2][1] = cos(beta)*sin(gamma);
	result[2][2] = cos(beta)*cos(gamma);
	

	return result;

}


double* inverseKinematics(double *desPos, double gamma, double beta, double alpha, double *prevThetas, int *solutionexist)
{
	
	*solutionexist = 1;
	initializeParameters();


	double **dummyM1, **dummyM2;
	//Initally 90 degrees angle ( theta[4] = 90 )
	dummyM1 = createRotationMatrixBaseToInitial(PI,-PI/2,0);
	dummyM2 = createRotationMatrixInitialToEnd(gamma,beta,alpha);

	rotation = matrixMultiply(dummyM1,dummyM2);

	for( int m = 0; m < 3; m++ ){
		//printf("\n");
		for( int l = 0; l < 3; l++ ){
			//printf("%lf ",rotation[m][l]);
		}
	}
	//printf("adasfsdgdfgdfhfgh\n");

	double endEffectorVect[3]; 
	
	endEffectorVect[0] = rotation[0][2];
	endEffectorVect[1] = rotation[1][2];
	endEffectorVect[2] = rotation[2][2];
	//printf(" \nendEffectorVect[0] = %lf",endEffectorVect[0]);
	//Desired position modified (it is changed to wrist position)
	//Approaching the goal with alpha, beta, gamma angles are guaaranteed
	//Minus direction		

	//for( int l = 0; l < 3; l++ )
			//printf("desPos[%d] =  %lf \n", l, desPos[l]);
      
	double prevTheta3 = prevThetas[3]; //This should be known for singularity check!!!

	//All theta possibilities
	double theta01, theta02;
	double theta21, theta22;
	double theta11, theta12, theta13, theta14;
	double theta31, theta32, theta33, theta34, theta35, theta36, theta37, theta38;
	double theta41, theta42, theta43, theta44, theta45, theta46, theta47, theta48;
	double theta51, theta52, theta53, theta54, theta55, theta56, theta57, theta58;
	
	//Desired wrist x,y,z
	double px = desPos[0] - (endEffectorVect[0]*lengthOfEndEff);
	double py = desPos[1] - (endEffectorVect[1]*lengthOfEndEff);
	double pz = desPos[2] - (endEffectorVect[2]*lengthOfEndEff);	
	double dummyAngle;
	double dummy1, dummy2;	
	
	//For checking nearest solution and joint limits thing
	int pairs[8];
	double distance[8];

	
	theta01 = atan2(py,px)-atan2(d[2],sqrt(px*px+py*py-d[2]*d[2]));	
	theta02 = atan2(py,px)-atan2(d[2],-sqrt(px*px+py*py-d[2]*d[2]));
	

	double K = (px*px+py*py+pz*pz-a[2]*a[2]-a[3]*a[3]-d[2]*d[2]-d[3]*d[3])/(2*a[2]);

	theta21 = atan2(a[3],d[3])-atan2(K,sqrt(a[3]*a[3]+d[3]*d[3]-K*K));	
	theta22 = atan2(a[3],d[3])-atan2(K,-sqrt(a[3]*a[3]+d[3]*d[3]-K*K));
	theta[0] = theta01; 
	theta[2] = theta21;
	dummy1 = ( -a[3]-a[2]*cos(theta[2]) )*pz - ( cos(theta[0])*px+sin(theta[0])*py )
		*( d[3]-a[2]*sin(theta[2]) );
	dummy2 = ( a[2]*sin(theta[2])-d[3] )*pz
		- ( -a[3]-a[2]*cos(theta[2]) )*( cos(theta[0])*px + sin(theta[0])*py );
	dummyAngle = atan2( dummy1, dummy2 );
	
	
	theta11 = dummyAngle - theta[2];
	

	theta[0] = theta01; 
	theta[2] = theta22;
	dummy1 = ( -a[3]-a[2]*cos(theta[2]) )*pz - ( cos(theta[0])*px+sin(theta[0])*py )
		*( d[3]-a[2]*sin(theta[2]) );
	dummy2 = ( a[2]*sin(theta[2])-d[3] )*pz
		- ( -a[3]-a[2]*cos(theta[2]) )*( cos(theta[0])*px + sin(theta[0])*py );
	dummyAngle = atan2( dummy1, dummy2 );
	theta12 = dummyAngle - theta[2];
	theta[0] = theta02; 
	theta[2] = theta21;
	dummy1 = ( -a[3]-a[2]*cos(theta[2]) )*pz - ( cos(theta[0])*px+sin(theta[0])*py )
		*( d[3]-a[2]*sin(theta[2]) );
	dummy2 = ( a[2]*sin(theta[2])-d[3] )*pz
		- ( -a[3]-a[2]*cos(theta[2]) )*( cos(theta[0])*px + sin(theta[0])*py );
	dummyAngle = atan2( dummy1, dummy2 );
	theta13 = dummyAngle - theta[2];
	

	theta[0] = theta02; 
	theta[2] = theta22;
	dummy1 = ( -a[3]-a[2]*cos(theta[2]) )*pz - ( cos(theta[0])*px+sin(theta[0])*py )
		*( d[3]-a[2]*sin(theta[2]) );
	dummy2 = ( a[2]*sin(theta[2])-d[3] )*pz
		- ( -a[3]-a[2]*cos(theta[2]) )*( cos(theta[0])*px + sin(theta[0])*py );
	dummyAngle = atan2( dummy1, dummy2 );
	theta14 = dummyAngle - theta[2];
	

	//So we have theta01, theta11, theta21 (pair 0)
	//So we have theta01, theta12, theta22 (pair 1)
	//So we have theta02, theta13, theta21 (pair 2)
	//So we have theta02, theta14, theta22 (pair 3)
	//pairs

	//If s5 != 0 we can solve theta3 as below
	theta[0] = theta01;
	theta[1] = theta11;
	theta[2] = theta21;	

	dummy1 = -rotation[0][2]*sin(theta[0])+rotation[1][2]*cos(theta[0]);	
	dummy2 = -rotation[0][2]*cos(theta[0])*cos(theta[1]+theta[2])-rotation[1][2]*sin(theta[0])*cos(theta[1]+theta[2])+rotation[2][2]*sin(theta[1]+theta[2]);
	//if else is for singularity check
	if((fabs(dummy1) < 0.001) && (fabs(dummy2) < 0.001))
		theta31 = prevTheta3;
	else
		theta31 = atan2(dummy1,dummy2);
	

	theta[0] = theta01;
	theta[1] = theta12;
	theta[2] = theta22;	

	dummy1 = -rotation[0][2]*sin(theta[0])+rotation[1][2]*cos(theta[0]);	
	dummy2 = -rotation[0][2]*cos(theta[0])*cos(theta[1]+theta[2])-rotation[1][2]*sin(theta[0])*cos(theta[1]+theta[2])+rotation[2][2]*sin(theta[1]+theta[2]);
	
	if((fabs(dummy1) < 0.001) && (fabs(dummy2) < 0.001))
		theta32 = prevTheta3;
	else
		theta32 = atan2(dummy1,dummy2);	
	
	theta[0] = theta02;
	theta[1] = theta13;
	theta[2] = theta21;	

	dummy1 = -rotation[0][2]*sin(theta[0])+rotation[1][2]*cos(theta[0]);
	dummy2 = -rotation[0][2]*cos(theta[0])*cos(theta[1]+theta[2])-rotation[1][2]*sin(theta[0])*cos(theta[1]+theta[2])+rotation[2][2]*sin(theta[1]+theta[2]);
	
	if((fabs(dummy1) < 0.001) && (fabs(dummy2) < 0.001))
		theta33 = prevTheta3;
	else
		theta33 = atan2(dummy1,dummy2);	

	theta[0] = theta02;
	theta[1] = theta14;
	theta[2] = theta22;	

	dummy1 = -rotation[0][2]*sin(theta[0])+rotation[1][2]*cos(theta[0]);
	dummy2 = -rotation[0][2]*cos(theta[0])*cos(theta[1]+theta[2])-rotation[1][2]*sin(theta[0])*cos(theta[1]+theta[2])+rotation[2][2]*sin(theta[1]+theta[2]);
	theta34 = atan2(dummy1,dummy2);
	if((fabs(dummy1) < 0.001) && (fabs(dummy2) < 0.001))
		theta34 = prevTheta3;
	else
		theta34 = atan2(dummy1,dummy2);
	
	
	//So we have theta01, theta11, theta21, theta31 (pair 0)
	//So we have theta01, theta12, theta22, theta32 (pair 1)
	//So we have theta02, theta13, theta21, theta33 (pair 2)
	//So we have theta02, theta14, theta22, theta34 (pair 3)
	//pairs
	theta[0] = theta01;
	theta[1] = theta11;
	theta[2] = theta21;
	theta[3] = theta31;
	dummy1 = -1*( rotation[0][2]*( cos(theta[0])*cos(theta[1]+theta[2])*cos(theta[3]) + sin(theta[0])*sin(theta[3]) ) 
		+ rotation[1][2]*( sin(theta[0])*cos(theta[1]+theta[2])*cos(theta[3]) - cos(theta[0])*sin(theta[3]) ) 
		- rotation[2][2]*( sin(theta[1]+theta[2]))*cos(theta[3])  );

	dummy2 = rotation[0][2]*( -cos(theta[0])*sin(theta[1]+theta[2]) ) 
		+ rotation[1][2]*( -sin(theta[0])*sin(theta[1]+theta[2]) ) 
		+ rotation[2][2]*( -cos(theta[1]+theta[2]) );

	theta41 = atan2(dummy1,dummy2);
	theta[0] = theta01;
	theta[1] = theta12;
	theta[2] = theta22;
	theta[3] = theta32;
	dummy1 = -1*( rotation[0][2]*( cos(theta[0])*cos(theta[1]+theta[2])*cos(theta[3]) + sin(theta[0])*sin(theta[3]) ) 
		+ rotation[1][2]*( sin(theta[0])*cos(theta[1]+theta[2])*cos(theta[3]) - cos(theta[0])*sin(theta[3]) ) 
		- rotation[2][2]*( sin(theta[1]+theta[2]))*cos(theta[3])  );

	dummy2 = rotation[0][2]*( -cos(theta[0])*sin(theta[1]+theta[2]) ) 
		+ rotation[1][2]*( -sin(theta[0])*sin(theta[1]+theta[2]) ) 
		+ rotation[2][2]*( -cos(theta[1]+theta[2]) );

	theta42 = atan2(dummy1,dummy2);
	

	theta[0] = theta02;
	theta[1] = theta13;
	theta[2] = theta21;
	theta[3] = theta33;
	dummy1 = -1*( rotation[0][2]*( cos(theta[0])*cos(theta[1]+theta[2])*cos(theta[3]) + sin(theta[0])*sin(theta[3]) ) 
		+ rotation[1][2]*( sin(theta[0])*cos(theta[1]+theta[2])*cos(theta[3]) - cos(theta[0])*sin(theta[3]) ) 
		- rotation[2][2]*( sin(theta[1]+theta[2]))*cos(theta[3])  );

	dummy2 = rotation[0][2]*( -cos(theta[0])*sin(theta[1]+theta[2]) ) 
		+ rotation[1][2]*( -sin(theta[0])*sin(theta[1]+theta[2]) ) 
		+ rotation[2][2]*( -cos(theta[1]+theta[2]) );

	theta43 = atan2(dummy1,dummy2);
	

	theta[0] = theta02;
	theta[1] = theta14;
	theta[2] = theta22;
	theta[3] = theta34;
	dummy1 = -1*( rotation[0][2]*( cos(theta[0])*cos(theta[1]+theta[2])*cos(theta[3]) + sin(theta[0])*sin(theta[3]) ) 
		+ rotation[1][2]*( sin(theta[0])*cos(theta[1]+theta[2])*cos(theta[3]) - cos(theta[0])*sin(theta[3]) ) 
		- rotation[2][2]*( sin(theta[1]+theta[2]))*cos(theta[3])  );

	dummy2 = rotation[0][2]*( -cos(theta[0])*sin(theta[1]+theta[2]) ) 
		+ rotation[1][2]*( -sin(theta[0])*sin(theta[1]+theta[2]) ) 
		+ rotation[2][2]*( -cos(theta[1]+theta[2]) );

	theta44 = atan2(dummy1,dummy2);
	

	//So we have theta01, theta11, theta21, theta31, theta41 (pair 0)
	//So we have theta01, theta12, theta22, theta32, theta42 (pair 1)
	//So we have theta02, theta13, theta21, theta33, theta43 (pair 2)
	//So we have theta02, theta14, theta22, theta34, theta44 (pair 3)
	//pairs	
	
	theta[0] = theta01;
	theta[1] = theta11;
	theta[2] = theta21;
	theta[3] = theta31;
	theta[4] = theta41;
	dummy1 = -rotation[0][0]*( cos(theta[0])*cos(theta[1]+theta[2])*sin(theta[3]) - sin(theta[0])*cos(theta[3]) )
		-rotation[1][0]*( sin(theta[0])*cos(theta[1]+theta[2])*sin(theta[3]) + cos(theta[0])*cos(theta[3]) ) 
		+rotation[2][0]*( sin(theta[1]+theta[2])*sin(theta[3]) );

	dummy2 = rotation[0][0]*( ( cos(theta[0])*cos(theta[1]+theta[2])*cos(theta[3]) + sin(theta[0])*sin(theta[3]) )*cos(theta[4]) - cos(theta[0])*sin(theta[1]+theta[2])*sin(theta[4]) )
		+ rotation[1][0]*( ( sin(theta[0])*cos(theta[1]+theta[2])*cos(theta[3]) - cos(theta[0])*sin(theta[3]) )*cos(theta[4]) - sin(theta[0])*sin(theta[1]+theta[2])*sin(theta[4]) )
		-rotation[2][0]*( sin(theta[1]+theta[2])*cos(theta[3])*cos(theta[4]) + cos(theta[1]+theta[2])*sin(theta[4]) );
	theta51 = atan2(dummy1,dummy2);

	theta[0] = theta01;
	theta[1] = theta12;
	theta[2] = theta22;
	theta[3] = theta32;
	theta[4] = theta42;
	dummy1 = -rotation[0][0]*( cos(theta[0])*cos(theta[1]+theta[2])*sin(theta[3]) - sin(theta[0])*cos(theta[3]) )
		-rotation[1][0]*( sin(theta[0])*cos(theta[1]+theta[2])*sin(theta[3]) + cos(theta[0])*cos(theta[3]) ) 
		+rotation[2][0]*( sin(theta[1]+theta[2])*sin(theta[3]) );

	dummy2 = rotation[0][0]*( ( cos(theta[0])*cos(theta[1]+theta[2])*cos(theta[3]) + sin(theta[0])*sin(theta[3]) )*cos(theta[4]) - cos(theta[0])*sin(theta[1]+theta[2])*sin(theta[4]) )
		+ rotation[1][0]*( ( sin(theta[0])*cos(theta[1]+theta[2])*cos(theta[3]) - cos(theta[0])*sin(theta[3]) )*cos(theta[4]) - sin(theta[0])*sin(theta[1]+theta[2])*sin(theta[4]) )
		-rotation[2][0]*( sin(theta[1]+theta[2])*cos(theta[3])*cos(theta[4]) + cos(theta[1]+theta[2])*sin(theta[4]) );
	theta52 = atan2(dummy1,dummy2);

	theta[0] = theta02;
	theta[1] = theta13;
	theta[2] = theta21;
	theta[3] = theta33;
	theta[4] = theta43;
	dummy1 = -rotation[0][0]*( cos(theta[0])*cos(theta[1]+theta[2])*sin(theta[3]) - sin(theta[0])*cos(theta[3]) )
		-rotation[1][0]*( sin(theta[0])*cos(theta[1]+theta[2])*sin(theta[3]) + cos(theta[0])*cos(theta[3]) ) 
		+rotation[2][0]*( sin(theta[1]+theta[2])*sin(theta[3]) );

	dummy2 = rotation[0][0]*( ( cos(theta[0])*cos(theta[1]+theta[2])*cos(theta[3]) + sin(theta[0])*sin(theta[3]) )*cos(theta[4]) - cos(theta[0])*sin(theta[1]+theta[2])*sin(theta[4]) )
		+ rotation[1][0]*( ( sin(theta[0])*cos(theta[1]+theta[2])*cos(theta[3]) - cos(theta[0])*sin(theta[3]) )*cos(theta[4]) - sin(theta[0])*sin(theta[1]+theta[2])*sin(theta[4]) )
		-rotation[2][0]*( sin(theta[1]+theta[2])*cos(theta[3])*cos(theta[4]) + cos(theta[1]+theta[2])*sin(theta[4]) );
	theta53 = atan2(dummy1,dummy2);

	theta[0] = theta02;
	theta[1] = theta14;
	theta[2] = theta22;
	theta[3] = theta34;
	theta[4] = theta44;
	dummy1 = -rotation[0][0]*( cos(theta[0])*cos(theta[1]+theta[2])*sin(theta[3]) - sin(theta[0])*cos(theta[3]) )
		-rotation[1][0]*( sin(theta[0])*cos(theta[1]+theta[2])*sin(theta[3]) + cos(theta[0])*cos(theta[3]) ) 
		+rotation[2][0]*( sin(theta[1]+theta[2])*sin(theta[3]) );

	dummy2 = rotation[0][0]*( ( cos(theta[0])*cos(theta[1]+theta[2])*cos(theta[3]) + sin(theta[0])*sin(theta[3]) )*cos(theta[4]) - cos(theta[0])*sin(theta[1]+theta[2])*sin(theta[4]) )
		+ rotation[1][0]*( ( sin(theta[0])*cos(theta[1]+theta[2])*cos(theta[3]) - cos(theta[0])*sin(theta[3]) )*cos(theta[4]) - sin(theta[0])*sin(theta[1]+theta[2])*sin(theta[4]) )
		-rotation[2][0]*( sin(theta[1]+theta[2])*cos(theta[3])*cos(theta[4]) + cos(theta[1]+theta[2])*sin(theta[4]) );
	theta54 = atan2(dummy1,dummy2);

	//So we have theta01, theta11, theta21, theta31, theta41, theta51 (pair 0)
	//So we have theta01, theta12, theta22, theta32, theta42, theta52 (pair 1)
	//So we have theta02, theta13, theta21, theta33, theta43, theta53 (pair 2)
	//So we have theta02, theta14, theta22, theta34, theta44, theta54 (pair 3)
	//pairs

	//There is also flipping the wrist thing! (page 121 Craig)
	//We don't need to singularity check here, since we've allready done it before (look previous lines)
	theta35 = theta31 + PI;
	theta45 = -theta41;
	theta55 = theta51 + PI;

	theta36 = theta32 + PI;
	theta46 = -theta42;
	theta56 = theta52 + PI;

	theta37 = theta33 + PI;
	theta47 = -theta43;
	theta57 = theta53 + PI;

	theta38 = theta34 + PI;
	theta48 = -theta44;
	theta58 = theta54 + PI;

	//So we have theta01, theta11, theta21, theta31, theta41, theta51 (pair 0)
	//So we have theta01, theta12, theta22, theta32, theta42, theta52 (pair 1)
	//So we have theta02, theta13, theta21, theta33, theta43, theta53 (pair 2)
	//So we have theta02, theta14, theta22, theta34, theta44, theta54 (pair 3)
	//So we have theta01, theta11, theta21, theta35, theta45, theta55 (pair 4)
	//So we have theta01, theta12, theta22, theta36, theta46, theta56 (pair 5)
	//So we have theta02, theta13, theta21, theta37, theta47, theta57 (pair 6)
	//So we have theta02, theta14, theta22, theta38, theta48, theta58 (pair 7)
	//pairs
	theta[0] = theta01;theta[1] = theta11;theta[2] = theta21;theta[3] = theta31;
	theta[4] = theta41;theta[5] = theta51;

	int check = 0;
	for( int i = 0; i < 6; i++ ){
		if( _isnan(theta[i]) == 0 ){
			while( theta[i] >= PI )
				theta[i] -= 2*PI;
			while( theta[i] < -PI )
				theta[i] += 2*PI;
			if( i == 2 && theta[i] > -100*PI/180 )
				theta[i] -= 2*PI;
			//printf("%lf ", theta[i]*180/PI );
		}else{
			check = 1;
			break;
		}
	}//printf("\n");

	if( check == 0 ){
		pairs[0] = checkForLimitations(theta);
		distance[0] = distanceOfThetas(theta, prevThetas);
	}else{
		pairs[0] = 1;
		distance[0] = 100000;
	}

	
	/////////////////////////////////////////////
	theta[0] = theta01;theta[1] = theta12;theta[2] = theta22;theta[3] = theta32;
	theta[4] = theta42;theta[5] = theta52;

	check = 0;
	for( i = 0; i < 6; i++ ){
		if( _isnan(theta[i]) == 0 ){
			while( theta[i] >= PI )
				theta[i] -= 2*PI;
			while( theta[i] < -PI )
				theta[i] += 2*PI;
			if( i == 2 && theta[i] > -100*PI/180 )
				theta[i] -= 2*PI;
			//printf("%lf ", theta[i]*180/PI );
		}else{
			check = 1;
			break;
		}
	}//printf("\n");

	if( check == 0 ){
		pairs[1] = checkForLimitations(theta);
		distance[1] = distanceOfThetas(theta, prevThetas);
	}else{
		pairs[1] = 1;
		distance[1] = 100000;
	}

    /////////////////////////////////////////////
	theta[0] = theta02;theta[1] = theta13;theta[2] = theta21;theta[3] = theta33;
	theta[4] = theta43;theta[5] = theta53;
	
	check = 0;
	for( i = 0; i < 6; i++ ){
		if( _isnan(theta[i]) == 0 ){
			while( theta[i] >= PI )
				theta[i] -= 2*PI;
			while( theta[i] < -PI )
				theta[i] += 2*PI;
			if( i == 2 && theta[i] > -100*PI/180 )
				theta[i] -= 2*PI;
			//printf("%lf ", theta[i]*180/PI );
		}else{
			check = 1;
			break;
		}
	}//printf("\n");

	if( check == 0 ){
		pairs[2] = checkForLimitations(theta);
		distance[2] = distanceOfThetas(theta, prevThetas);
	}else{
		pairs[2] = 1;
		distance[2] = 100000;
	}

	/////////////////////////////////////////////
	theta[0] = theta02;theta[1] = theta14;theta[2] = theta22;theta[3] = theta33;
	theta[4] = theta44;theta[5] = theta54;

	check = 0;
	for( i = 0; i < 6; i++ ){
		if( _isnan(theta[i]) == 0 ){
			while( theta[i] >= PI )
				theta[i] -= 2*PI;
			while( theta[i] < -PI )
				theta[i] += 2*PI;
			if( i == 2 && theta[i] > -100*PI/180 )
				theta[i] -= 2*PI;
			//printf("%lf ", theta[i]*180/PI );
		}else{
			check = 1;
			break;
		}
	}//printf("\n");

	if( check == 0 ){
		pairs[3] = checkForLimitations(theta);
		distance[3] = distanceOfThetas(theta, prevThetas);
	}else{
		pairs[3] = 1;
		distance[3] = 100000;
	}

	/////////////////////////////////////////////
	theta[0] = theta01;theta[1] = theta11;theta[2] = theta21;theta[3] = theta35;
	theta[4] = theta45;theta[5] = theta55;

	check = 0;
	for( i = 0; i < 6; i++ ){
		if( _isnan(theta[i]) == 0 ){
			while( theta[i] >= PI )
				theta[i] -= 2*PI;
			while( theta[i] < -PI )
				theta[i] += 2*PI;
			if( i == 2 && theta[i] > -100*PI/180 )
				theta[i] -= 2*PI;
			//printf("%lf ", theta[i]*180/PI );
		}else{
			check = 1;
			break;
		}

	}//printf("\n");

	if( check == 0 ){
		pairs[4] = checkForLimitations(theta);
		distance[4] = distanceOfThetas(theta, prevThetas);
	}else{
		pairs[4] = 1;
		distance[4] = 100000;
	}

	
	/////////////////////////////////////////////
	theta[0] = theta01;theta[1] = theta12;theta[2] = theta22;theta[3] = theta36;
	theta[4] = theta46;theta[5] = theta56;

	check = 0;
	for( i = 0; i < 6; i++ ){
		if( _isnan(theta[i]) == 0 ){
			while( theta[i] >= PI )
				theta[i] -= 2*PI;
			while( theta[i] < -PI )
				theta[i] += 2*PI;
			if( i == 2 && theta[i] > -100*PI/180 )
				theta[i] -= 2*PI;
			//printf("%lf ", theta[i]*180/PI );
		}else{
			check = 1;
			break;
		}
	}//printf("\n");

	if( check == 0 ){
		pairs[5] = checkForLimitations(theta);
		distance[5] = distanceOfThetas(theta, prevThetas);
	}else{
		pairs[5] = 1;
		distance[5] = 100000;
	}

	/////////////////////////////////////////////	
	theta[0] = theta02;theta[1] = theta13;theta[2] = theta21;theta[3] = theta37;
	theta[4] = theta47;theta[5] = theta57;

	check = 0;
	for( i = 0; i < 6; i++ ){
		if( _isnan(theta[i]) == 0 ){
			while( theta[i] >= PI )
				theta[i] -= 2*PI;
			while( theta[i] < -PI )
				theta[i] += 2*PI;
			if( i == 2 && theta[i] > -100*PI/180 )
				theta[i] -= 2*PI;
			//printf("%lf ", theta[i]*180/PI );
		}else{
			check = 1;
			break;
		}
	}//printf("\n");

	if( check == 0 ){
		pairs[6] = checkForLimitations(theta);
		distance[6] = distanceOfThetas(theta, prevThetas);
	}else{
		pairs[6] = 1;
		distance[6] = 100000;
	}

	/////////////////////////////////////////////
	theta[0] = theta02;theta[1] = theta14;theta[2] = theta22;theta[3] = theta38;
	theta[4] = theta48;theta[5] = theta58;

	check = 0;
	for( i = 0; i < 6; i++ ){
		if( _isnan(theta[i]) == 0 ){
			while( theta[i] >= PI )
				theta[i] -= 2*PI;
			while( theta[i] < -PI )
				theta[i] += 2*PI;
			if( i == 2 && theta[i] > -100*PI/180 )
				theta[i] -= 2*PI;
			//printf("%lf ", theta[i]*180/PI );
		}else{
			check = 1;
			break;
		}
	}//printf("\n");
	
	if( check == 0 ){
		pairs[7] = checkForLimitations(theta);
		distance[7] = distanceOfThetas(theta, prevThetas);
	}else{
		pairs[7] = 1;
		distance[7] = 100000;
	}

	/////////////////////////////////////////////	
	double nearest = 10000;
	double nearNo = -1;
	for( i = 0; i < 8; i++ ){
		if( pairs[i] == 0 && distance[i] < nearest ){
			nearNo = i;
			nearest = distance[i];
		}
	}
	if( nearest == 10000 ){
		//printf("\n!!!!Not reachable!!!!\n ");
		*solutionexist = 0;
		//for( i = 0; i < 6; i++ )		
			//printf("\nTheta[%d] = %lf\n",i, prevThetas[i]*180/PI );
		return prevThetas;
	}

	if( nearNo == 0 ){
		theta[0] = theta01;theta[1] = theta11;theta[2] = theta21;theta[3] = theta31;
		theta[4] = theta41;theta[5] = theta51;
	}
	if( nearNo == 1 ){
		theta[0] = theta01;theta[1] = theta12;theta[2] = theta22;theta[3] = theta32;
		theta[4] = theta42;theta[5] = theta52;
	}
	if( nearNo == 2 ){
		theta[0] = theta02;theta[1] = theta13;theta[2] = theta21;theta[3] = theta33;
		theta[4] = theta43;theta[5] = theta53;
	}
	if( nearNo == 3 ){
		theta[0] = theta02;theta[1] = theta14;theta[2] = theta22;theta[3] = theta33;
		theta[4] = theta44;theta[5] = theta54;
	}
	if( nearNo == 4 ){
		theta[0] = theta01;theta[1] = theta11;theta[2] = theta21;theta[3] = theta35;
		theta[4] = theta45;theta[5] = theta55;
	}
	if( nearNo == 5 ){
		theta[0] = theta01;theta[1] = theta12;theta[2] = theta22;theta[3] = theta36;
		theta[4] = theta46;theta[5] = theta56;
	}
	if( nearNo == 6 ){
		theta[0] = theta02;theta[1] = theta13;theta[2] = theta21;theta[3] = theta37;
		theta[4] = theta47;theta[5] = theta57;
	}
	if( nearNo == 7 ){
		theta[0] = theta02;theta[1] = theta14;theta[2] = theta22;theta[3] = theta38;
		theta[4] = theta48;theta[5] = theta58;
	}

	for( i = 0; i < 6; i++ ){
		while( theta[i] >= PI )
			theta[i] -= 2*PI;
		while( theta[i] < -PI )
			theta[i] += 2*PI;
		if( i == 2 && theta[i] > -100*PI/180 )
			theta[i] -= 2*PI;
		//printf("\nTheta[%d] = %lf\n",i, theta[i]*180/PI );
	}
	
	
	//printf("\n~~~~ SOLUTION FOUND ~~~~\n ");

	return theta;
}

double** transformMatrixMultiply( double **T1, double **T2 ){
	//double **result;
	//result = (double**)malloc(4*sizeof(double*));
	//double result[4][4];
	double **result = new double*[4];

	for( int i = 0; i < 3; i++){
		//result[i] = (double*)malloc(4*sizeof(double));
		result[i] = new double[4];
		for( int j = 0; j < 3; j++ ){
			result[i][j] = T1[i][0]*T2[0][j] + T1[i][1]*T2[1][j] + T1[i][2]*T2[2][j] + T1[i][3]*T2[3][j] ;
		}
	}
	
	return result;
}


void createTransformMatrices(double *theta){	
	
	//T01 = (double**)malloc(4*sizeof(double*));
	//for( int i = 0; i < 4; i++)
	//	T01[i] = (double*)malloc(4*sizeof(double));

	T01[0][0] = cos(theta[0]);
	T01[0][1] = -sin(theta[0]);
	T01[0][2] = 0;
	T01[0][3] = a[0];

	T01[1][0] = sin(theta[0])*cos(alpha[0]);
	T01[1][1] = cos(theta[0])*cos(alpha[0]);
	T01[1][2] = -sin(alpha[0]);
	T01[1][3] = -sin(alpha[0])*d[0];

	T01[2][0] = sin(theta[0])*sin(alpha[0]);
	T01[2][1] = cos(theta[0])*sin(alpha[0]);
	T01[2][2] = cos(alpha[0]);
	T01[2][3] = cos(alpha[0])*d[0];

	T01[3][0] = 0;
	T01[3][1] = 0;
	T01[3][2] = 0;
	T01[3][3] = 1;	
	
	//T12 = (double**)malloc(4*sizeof(double*));
	//for( i = 0; i < 4; i++)
	//	T12[i] = (double*)malloc(4*sizeof(double));

	T12[0][0] = cos(theta[1]);
	T12[0][1] = -sin(theta[1]);
	T12[0][2] = 0;
	T12[0][3] = a[1];

	T12[1][0] = sin(theta[1])*cos(alpha[1]);
	T12[1][1] = cos(theta[1])*cos(alpha[1]);
	T12[1][2] = -sin(alpha[1]);
	T12[1][3] = -sin(alpha[1])*d[1];

	T12[2][0] = sin(theta[1])*sin(alpha[1]);
	T12[2][1] = cos(theta[1])*sin(alpha[1]);
	T12[2][2] = cos(alpha[1]);
	T12[2][3] = cos(alpha[1])*d[1];

	T12[3][0] = 0;
	T12[3][1] = 0;
	T12[3][2] = 0;
	T12[3][3] = 1;
	
	//T23 = (double**)malloc(4*sizeof(double*));
	//for( i = 0; i < 4; i++)
	//	T23[i] = (double*)malloc(4*sizeof(double));

	T23[0][0] = cos(theta[2]);
	T23[0][1] = -sin(theta[2]);
	T23[0][2] = 0;
	T23[0][3] = a[2];

	T23[1][0] = sin(theta[2])*cos(alpha[2]);
	T23[1][1] = cos(theta[2])*cos(alpha[2]);
	T23[1][2] = -sin(alpha[2]);
	T23[1][3] = -sin(alpha[2])*d[2];

	T23[2][0] = sin(theta[2])*sin(alpha[2]);
	T23[2][1] = cos(theta[2])*sin(alpha[2]);
	T23[2][2] = cos(alpha[2]);
	T23[2][3] = cos(alpha[2])*d[2];

	T23[3][0] = 0;
	T23[3][1] = 0;
	T23[3][2] = 0;
	T23[3][3] = 1;

	//T34 = (double**)malloc(4*sizeof(double*));
	//for( i = 0; i < 4; i++)
	//	T34[i] = (double*)malloc(4*sizeof(double));

	T34[0][0] = cos(theta[3]);
	T34[0][1] = -sin(theta[3]);
	T34[0][2] = 0;
	T34[0][3] = a[3];

	T34[1][0] = sin(theta[3])*cos(alpha[3]);
	T34[1][1] = cos(theta[3])*cos(alpha[3]);
	T34[1][2] = -sin(alpha[3]);
	T34[1][3] = -sin(alpha[3])*d[3];

	T34[2][0] = sin(theta[3])*sin(alpha[3]);
	T34[2][1] = cos(theta[3])*sin(alpha[3]);
	T34[2][2] = cos(alpha[3]);
	T34[2][3] = cos(alpha[3])*d[3];

	T34[3][0] = 0;
	T34[3][1] = 0;
	T34[3][2] = 0;
	T34[3][3] = 1;

	//T45 = (double**)malloc(4*sizeof(double*));
	//for( i = 0; i < 4; i++)
	//	T45[i] = (double*)malloc(4*sizeof(double));

	T45[0][0] = cos(theta[4]);
	T45[0][1] = -sin(theta[4]);
	T45[0][2] = 0;
	T45[0][3] = a[4];

	T45[1][0] = sin(theta[4])*cos(alpha[4]);
	T45[1][1] = cos(theta[4])*cos(alpha[4]);
	T45[1][2] = -sin(alpha[4]);
	T45[1][3] = -sin(alpha[4])*d[4];

	T45[2][0] = sin(theta[4])*sin(alpha[4]);
	T45[2][1] = cos(theta[4])*sin(alpha[4]);
	T45[2][2] = cos(alpha[4]);
	T45[2][3] = cos(alpha[4])*d[4];

	T45[3][0] = 0;
	T45[3][1] = 0;
	T45[3][2] = 0;
	T45[3][3] = 1;

	//T56 = (double**)malloc(4*sizeof(double*));
	//for( i = 0; i < 4; i++)
	//	T56[i] = (double*)malloc(4*sizeof(double));

	T56[0][0] = cos(theta[5]);
	T56[0][1] = -sin(theta[5]);
	T56[0][2] = 0;
	T56[0][3] = a[5];

	T56[1][0] = sin(theta[5])*cos(alpha[5]);
	T56[1][1] = cos(theta[5])*cos(alpha[5]);
	T56[1][2] = -sin(alpha[5]);
	T56[1][3] = -sin(alpha[5])*d[5];

	T56[2][0] = sin(theta[5])*sin(alpha[5]);
	T56[2][1] = cos(theta[5])*sin(alpha[5]);
	T56[2][2] = cos(alpha[5]);
	T56[2][3] = cos(alpha[5])*d[5];

	T56[3][0] = 0;
	T56[3][1] = 0;
	T56[3][2] = 0;
	T56[3][3] = 1;
}


void forwardKinematics( double *thetas){
	//Attention call this function after inverseKinematics since variables have to be initialized
	//If you call initialize parameters function here, it will consume so much memory because of malloc
	createTransformMatrices(thetas);
	T02 = transformMatrixMultiply(T01, T12);
	T03 = transformMatrixMultiply(T02, T23);
	T04 = transformMatrixMultiply(T03, T34);
	T05 = transformMatrixMultiply(T04, T45);
	T06 = transformMatrixMultiply(T05, T56);

	//j1Pos = (double*)malloc(3*sizeof(double));
	j1Pos[0] = T01[3][0];
	j1Pos[1] = T01[3][1];
	j1Pos[2] = T01[3][2];

	//j2Pos = (double*)malloc(3*sizeof(double));
	j2Pos[0] = T02[3][0];
	j2Pos[1] = T02[3][1];
	j2Pos[2] = T02[3][2];

	//j3Pos = (double*)malloc(3*sizeof(double));
	j3Pos[0] = T03[3][0];
	j3Pos[1] = T03[3][1];
	j3Pos[2] = T03[3][2];

	//j4Pos = (double*)malloc(3*sizeof(double));
	j4Pos[0] = T04[3][0];
	j4Pos[1] = T04[3][1];
	j4Pos[2] = T04[3][2];

	//j5Pos = (double*)malloc(3*sizeof(double));
	j5Pos[0] = T05[3][0];
	j5Pos[1] = T05[3][1];
	j5Pos[2] = T05[3][2];

	//j6Pos = (double*)malloc(3*sizeof(double));
	j6Pos[0] = T06[3][0];
	j6Pos[1] = T06[3][1];
	j6Pos[2] = T06[3][2];

	//endEffPos = (double*)malloc(3*sizeof(double));
	endEffPos[0] = j6Pos[0]+T06[0][3]*lengthOfEndEff;
	endEffPos[1] = j6Pos[1]+T06[1][3]*lengthOfEndEff;
	endEffPos[2] = j6Pos[2]+T06[2][3]*lengthOfEndEff;


}


#endif