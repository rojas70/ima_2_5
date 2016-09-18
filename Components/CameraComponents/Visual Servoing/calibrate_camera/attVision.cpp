//attVision.cpp
#include "stdafx.h"
#include "AttVision.h"



AttVision::AttVision()

{

	time_t start_time, cur_time;


	//Default Parameters for FeatureGate Processing
	iNumPts = 12;		//number of points to store per image
	bLevels = 1;		//type of processing: 0 for 1 level only, 1 for levels

	//COM port / Camera Initialization
	cout << "Initalizing..." << endl;
	//Initialize Com port
	//cout << "Initializing COM port!" << endl;
	if(!hd.Initialize())
	{
		cout << "Failed to initialize COM port!" << endl;
		return;
	}
	cout << "Initialize COM success!" << endl;

	//Initialize Camera
	cout << "Initializing Camera!" << endl;
	camPicL.Initialize(0);
	camPicR.put_FrameGrabberID(1);
	camPicR.Initialize(0);
	//camPicR.put_FrameGrabberID(1);

	//Put camera at Home position
	cout << "Cameras in home position..." << endl;
	hd.Home();
	time(&start_time);
	do
	{
	    time(&cur_time);
	}
	while((cur_time - start_time) < 3);
	
}

AttVision::~AttVision()
{
}


//************************************************************************
//Description: Function to capture an image give pan, tilt, and a filename to save it as
//
//Variables:
//		cam_choice allows the user to pick the left or right camera (0 = left, 1 = right)
//		imgFileName is name image is to be saved as
//************************************************************************
void AttVision::CaptureImg(char* imgFileName, bool cam_choice)
{

	if (cam_choice == 0)				//LEFT camera
		camPicL.GetImage(imgFileName);
	else								//RIGHT camera
		camPicR.GetImage(imgFileName);

}

//************************************************************************
//Description: hd is a private variable, function allows access to hd move function
//
//Variables:
//		command is a buffer containing pan/tilt angles for the cameras
//************************************************************************
void AttVision::MoveCam(double *command)
{
	hd.MoveHead(command);
}