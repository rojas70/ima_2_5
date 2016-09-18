// Written by Peter Humke and Jason Kientz

#include "stdafx.h"
#include "OpenCVLib.h"

void IMA2_Open_CV::BackgroudSubtraction(*FrameGrabberObject LCamera, *FrameGrabberObject RCamera, *double returnVals)
{
	
	const int C = 3;
	const int N = 10;
	double alpha = 1/N;
	IPLImage *theLeftImage;
    IPLImage *theRightImage;
    IPLImage *LMean;
    IPLImage *RMean;
    IPLImage *LSigma;
	IPLImage *RSigma;
	                                      //initialize the background information
	for (i = 1; i=N; i++){
		
	LCamera->Get_Image(theLeftImage);     // getting the current left image from the FG
	
	RCamera->Get_Image(theRightImage);    // getting the current right image from the FG
		
	void cvAcc( IplImage* LCamera, IplImage* LSum, IplImage* mask=0 );
    void cvAcc( IplImage* RCamera, IplImage* RSum, IplImage* mask=0 );
    void cvSquareAcc( IplImage* LCamera, IplImage* LsqSum, IplImage* mask=0 );
    void cvSquareAcc( IplImage* RCamera, IplImage* RsqSum, IplImage* mask=0 );
    
	void cvRunningAvg( IplImage* LCamera, IplImage* LAvg, double alpha,IplImage* mask=0 );
    void cvRunningAvg( IplImage* RCamera, IplImage* RAvg, double alpha,IplImage* mask=0 );

	}

	                                      // BG subtraction code here

    Mean = LSum/N;


}








