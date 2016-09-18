// calibrate_camera.cpp : Defines the entry point for the console application.
// 
// Description: main routine for caculating the camera to world and world to camera transfroms
//		between ISAC and the Motoman arm. Makes use of Dr. Peter's Image Processing Class algorithm.
//		Pictures are taken manually (hitting the enter key) at each pause in the arm camera
//		calibration routine. Hue detection is used to locate the end effector in each picture. World
//		Coordinates need to be supplied to a text file called WorldCoordinates.txt
//

#include "stdafx.h"

#include "AttVision.h"
#include "camera.h"
#include <conio.h>

void grabPics(double dPan, double dTilt, int numpics);
void grabCameraCoords(double dPan, double dTilt);
void grabPics_writeTransform(double dPan, double dTilt, int numpics);
void getArmCoordinates(double dPan, double dTilt);

//CAMERA TRANSFORM PARAMETERS
//center to camera base = 140mm
//camera base to rotation base = 91.948mm
//rotation base to camera = 65.5mm
//camera to focal point = 39mm
//rotation about z is from dPan
//rotation about y if from dTilt

AttVision attnVis;
Camera CAM;

int main(int argc, char* argv[])
{
	double dPan = 0;
	double dTilt = -35;

	int numpics = 0;
	int value = 1;

	while(value != 0)
	{
		printf("0: EXIT.\n");
		printf("1: Take new pictures.\n");
		printf("2: Get coordinates of an object.\n");
		printf("3: Take pictures and computing transforms.\n");
		printf("4: Find object and compute coordinates.\n");
		
		cin >> value;

		switch(value)
		{
		case 0:
			break;
		case 1:
			printf("How many pictures? ");
			cin >> numpics;
			printf("\n");

			grabPics(dPan, dTilt, numpics);

			break;
		case 2:
			grabCameraCoords(dPan, dTilt);

			break;
		case 3:
			printf("How many pictures? ");
			cin >> numpics;
			printf("\n");

			grabPics_writeTransform(dPan, dTilt, numpics);
			break;
		case 4:
			getArmCoordinates(dPan, dTilt);
			break;
		default:
			break;
		}
	}


	char character;
	for(;;)
	{
		cout << "Q to Exit: ";
		cin >> character;
		if (character == 'Q' || character == 'q')
		{
			return 0;
		}
		cout << endl;
	}

	getchar();
	return 0;
}

// grabPics takes the pan and tilt angles of the camera (pan should always be zero), and moves
//		the cameras to the desired location.  from this point, it will take a picture every time
//		the return key is pressed on the keyboard for as many times as is specified in numpics.
//		the images names are saved in a text file (FilenamesL.txt and FilenamesR.txt) for the left
//		and right cameras, respectively.  they can also be directly accessed in the C:\ScottTom\Images
//		directory.
void grabPics(double dPan, double dTilt, int numpics)
{
	//AttVision attnVis;
	double buff[4];						// buffer containing pan/tilt info for cameras
										// format:  0-leftPan, 1-leftTilt, 2-rightPan, 3-rightTilt
	
	buff[0] = -1*dPan; buff[1] = dTilt; 
	buff[2] = dPan; buff[3] = dTilt;

	attnVis.MoveCam(buff);				//move the cameras to the correct position

	//time delay, wait 3 seconds to ensure the right pan/tilt is returned
	time_t start_time, cur_time;
	time(&start_time);
	do
	{
	    time(&cur_time);
	}
	while((cur_time - start_time) < 3);


	//Open Picture Names
	string filepathL,filepathR;
	char chL,chR;
	ifstream inFileL;
    inFileL.open("FilenamesL.txt");

	ifstream inFileR;
	inFileR.open("FilenamesR.txt");
	
	if (!inFileL || !inFileR)
	{
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

	cout << "Arm Calibration Running. Press Enter key when arm pauses." <<endl;
	
	//********************
	//Arm Calibration Routine of Motoman Arm should start now
	//********************

	for(int j=1;j<numpics+1;j++)
	{
		filepathL = "";
		filepathR = "";
		do 
		{
			if(!inFileL.get(chL))
				break;
			if(chL == '\n' || chL == EOF)
				break;
			filepathL = filepathL + chL;
		} while(1);

		do
		{
			if(!inFileR.get(chR))
				break;
			if(chR == '\n' || chR == EOF)
				break;
			filepathR = filepathR + chR;
		} while(1);
		
		char * filerL = (char*)filepathL.c_str();
		char * filerR = (char*)filepathR.c_str();
		
		//"Press any key"
		getch();
		attnVis.CaptureImg(filerL,0);
		attnVis.CaptureImg(filerR,1);
		cout << "Picture Number " << j << " Taken" << endl;
		

	}//end for loop 
	inFileL.close();
	inFileR.close();

	cout << "Images Saved " << endl;

	// routines used to calculate the transforms between the arm and the camera
	// and vice versa.  this was our attempt at the 6 point method, but somewhere
	// we got lost in the numbers.

	Camera test;

	test.getFixedCameraCoordinates(0);
	test.getTransforms(0,double(dPan),double(dTilt));
	test.getFixedCameraCoordinates(1);
	test.getTransforms(1,double(dPan),double(dTilt));

	test.Calculate_Point("World2CameraL.txt","Wpoint.txt");
	test.Calculate_Point("World2CameraR.txt","Wpoint.txt");

	test.Calculate_Point("Camera2WorldL.txt","Cpoint.txt");
	test.Calculate_Point("Camera2WorldR.txt","Cpoint.txt");

	return;
}

// grabCameraCoords looks around until it centers on the desired object as defined by hue.  the camera
//		coordinates of this object will be constantly calculated until the object is found to be within 
//		the bounding box for both cameras.  at this point, the average coordinates should be transformed
//		and sent to the arm.
void grabCameraCoords(double dPan, double dTilt)
{
	//AttVision attnVis;
	//Camera CAM;

	char * frameL = "frameL.bmp";
	char * frameR = "frameR.bmp";

	CAM.pantilt[0] = dPan;
	CAM.pantilt[1] = dTilt;
	CAM.pantilt[2] = dPan;
	CAM.pantilt[3] = dTilt;

	attnVis.MoveCam(CAM.pantilt);


	int fL[2];
	int fR[2];

	fL[0] = 0;
	fL[1] = 0;
	fR[0] = 0;
	fR[1] = 0;

	int box_min_x = 150;
	int box_max_x = 170;
	int box_min_y = 110;
	int box_max_y = 130;

	while (1)
	{
		attnVis.CaptureImg(frameL,0);
		attnVis.CaptureImg(frameR,1);

		CAM.getCameraCoordinates(frameL,0,fL);
		CAM.getCameraCoordinates(frameR,1,fR);

		if (((fL[0] > box_min_x) && (fL[0] < box_max_x) && (fL[1] > box_min_y) && (fL[1] < box_max_y))
			&& ((fR[0] > box_min_x) && (fR[0] < box_max_x) && (fR[1] > box_min_y) && (fR[1] < box_max_y)))
		{
			CAM.calculateXYZ(fL[0],fL[1],fR[0],fR[1]);
			getchar();
			getchar();
			
		}
		else
		{
			CAM.centerCams(fL[0],fL[1],fR[0],fR[1]);
			attnVis.MoveCam(CAM.pantilt);
		}

		if (CAM.HERE_L == 1 && CAM.HERE_R == 1)
		{
			CAM.calculateXYZ(fL[0],fL[1],fR[0],fR[1]);		// send average coordinates to arm
			getchar();
			//break;				
		}
	}
	
	return;
}



void grabPics_writeTransform(double dPan, double dTilt, int numpics)
{
	//AttVision attnVis;

	CAM.pantilt[0] = -1*dPan;
	CAM.pantilt[1] = dTilt;
	CAM.pantilt[2] = -dPan;
	CAM.pantilt[3] = dTilt;


	int fL[2];
	int fR[2];

	fL[0] = 0;
	fL[1] = 0;
	fR[0] = 0;
	fR[1] = 0;

	double x,y,z;

	attnVis.MoveCam(CAM.pantilt);				//move the cameras to the correct position

	//time delay, wait 3 seconds to ensure the right pan/tilt is returned
	time_t start_time, cur_time;
	time(&start_time);
	do
	{
	    time(&cur_time);
	}
	while((cur_time - start_time) < 3);


	//Open Picture Names
	string filepathL,filepathR;
	char chL,chR;
	ifstream inFileL;
    inFileL.open("FilenamesL.txt");

	ifstream inFileR;
	inFileR.open("FilenamesR.txt");
	
	if (!inFileL || !inFileR)
	{
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

	cout << "Arm Calibration Running. Press Enter key when arm pauses." <<endl;
	
	//********************
	//Arm Calibration Routine of Motoman Arm should start now
	//********************

	ifstream inFileArm;
	inFileArm.open("ArmPos.txt");

	for(int j=1;j<numpics+1;j++)
	{
		filepathL = "";
		filepathR = "";
		do 
		{
			if(!inFileL.get(chL))
				break;
			if(chL == '\n' || chL == EOF)
				break;
			filepathL = filepathL + chL;
		} while(1);

		do
		{
			if(!inFileR.get(chR))
				break;
			if(chR == '\n' || chR == EOF)
				break;
			filepathR = filepathR + chR;
		} while(1);
		
		char * filerL = (char*)filepathL.c_str();
		char * filerR = (char*)filepathR.c_str();
		
		//"Press any key"
		getch();
//		attnVis.CaptureImg(filerL,0);
//		attnVis.CaptureImg(filerR,1);

		CAM.getCameraCoordinates(filerL,0,fL);
		CAM.getCameraCoordinates(filerR,1,fR);

		CAM.calculateXYZ(fL[0],fL[1],fR[0],fR[1]);
		x = CAM.CAMERA_X;
		y = CAM.CAMERA_Y;
		z = CAM.CAMERA_Z;
		CAM.Find_Arm(x,y,z,inFileArm);

		cout << "Picture Number " << j << " Taken and Processed" << endl;
		

	}//end for loop 
	inFileL.close();
	inFileR.close();
	inFileArm.close();

	cout << "Images Saved " << endl;

	CAM.Find_Arm_Coordinates();

	return;
}

void getArmCoordinates(double dPan, double dTilt)
{
	char * frameL = "frameL.bmp";
	char * frameR = "frameR.bmp";

	CAM.pantilt[0] = -1*dPan;
	CAM.pantilt[1] = dTilt;
	CAM.pantilt[2] = dPan;
	CAM.pantilt[3] = dTilt;

	attnVis.MoveCam(CAM.pantilt);


	int fL[2];
	int fR[2];

	fL[0] = 0;
	fL[1] = 0;
	fR[0] = 0;
	fR[1] = 0;

	int box_min_y = 110;
	int box_max_y = 130;

	int wait = 10;			//let it run for a bit even in box

	while (1)
	{
		attnVis.CaptureImg(frameL,0);
		attnVis.CaptureImg(frameR,1);

		CAM.getCameraCoordinates(frameL,0,fL);
		CAM.getCameraCoordinates(frameR,1,fR);


		if (((fL[1] > box_min_y) && (fL[1] < box_max_y)) && ((fR[1] > box_min_y) && (fR[1] < box_max_y)) )//&& (wait == 0))
		{
			CAM.calculateXYZ(fL[0],fL[1],fR[0],fR[1]);	//sets CAMERA_X, CAMERA_Y, CAMERA_Z

			break;			
		}
		else
		{
			CAM.centerCams(fL[0],fL[1],fR[0],fR[1]);
			attnVis.MoveCam(CAM.pantilt);
			//if (wait != 0)
			//	wait--;
		}

	}


	CAM.get_writeCoordinates();
	
	return;
}
