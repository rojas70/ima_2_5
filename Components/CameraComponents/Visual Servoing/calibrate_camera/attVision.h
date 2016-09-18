//AttVision.h

#ifndef ATTVISION
#define ATTVISION

#include "stdafx.h"

//#include "CreateNewSES.h"
//#include "SESAttnManager.h"
//#include "FGate.h"
#include <iostream>
#include "C:\ScottTom\frameGrab\CameraHead.h"
#include "C:\ScottTom\frameGrab\PXCk_FG.H"

#include <math.h>				//for trig functions	
#include <time.h>				//for delay function
//#include <fstream>

using namespace std;


class AttVision
{
public:
	AttVision();
	virtual ~AttVision();
	/*void ChangeDB();
	void CaptureImgSingle();
	void CaptureImgList();
	
	void RunFGate(CImg<int> currentImage, int iNodeID);
	void SESSalience();
	void ResetSES();
	void SceneReconstruction();
	void CreateNewSES();
	
	void CreateTables();
	void UpdateDemo();
	void LoadCurrentImage(char * filename);
	//testing functions
	void ResetHead();
	void Test();
	void AutomaticProgram();
	void TakeImgSequence();
	//void SESUpdate();						//no longer needed
	*/
	void CaptureImg(char* imgFileName, bool cam_choice);
	void MoveCam(double *command);

private:

	//FGate myFGate;
	//CSESAttnManager sesAttMan;
	//CImg<double>* topN;						//array of top N most salient nodes on SES
	//CImg<int> currentImage;
	//CImgDisplay main_disp;      
	
	//	CImg<int>* nodeIDarray;				//array for reconstructed scene image
		
	//FeatureGate Parameters
	int iNumPts;							//number of points to store per image
	bool bLevels;							//type of processing: 0 for 1 level only, 1 for levels

	CameraHead hd;							//pan/tilt unit class
	CPXCk_FG camPicL;						//frame grabber class
	CPXCk_FG camPicR;						//Test right cam

	//double buff[4];							// buffer containing pan/tilt info for cameras
											// format:  0-leftPan, 1-leftTilt, 2-rightPan, 3-rightTilt
	//flags
	//bool	recFlag;						//flag to indicate whether scene was reconstructed or not
	//bool	saveImgToFile;					//save image to file (don't just put it in the buffer
};
#endif




		
	
	
	
	
	







