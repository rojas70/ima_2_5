#include "stdafx.h"
#include "camera.h"

#define M_PI 3.14159265358979323846264338327950288419716939937510	// temp substitution


Camera::Camera()
{
	comptot = 0;
	compmax = 0;
	compcap = 20;
	
	sigma = 50.0;				// pixels per mm
	focal_length = 308.0/50.0;	// mm
	
	row_center = 120;		// pixels
	col_center = 160;		// pixels

	maxarea = 0;
	maxcomp = 0;

	tilt_direction =0;

	Comps = new CvConnectedComp*[40];
	int temp[] = {60};
	float range[] = {0, 180};
	float * rangep[] = {range};
	hist  = cvCreateHist(1,temp,CV_HIST_ARRAY,rangep,1);

	intrinsic_camera_parameters = cvCreateMat(3,3,CV_32FC1);
		for (int j = 0; j < 3; j++)
			intrinsic_camera_parameters->data.fl[j] = 0.5;

	distortion_coeffs		    = cvCreateMat(1,4,CV_32FC1);
	rotation_vectors			= cvCreateMat(1,3,CV_32FC1);
	rotation_matrix				= cvCreateMat(3,3,CV_32FC1);
	translation_vectors			= cvCreateMat(1,3,CV_32FC1);

	for (j = 0; j < 24; j++)
	{
		if (j < 4)
			pantilt[j] = 0;

		present[j] = 0;
		camera_coordinates_fixed[0][j] = 0;
		camera_coordinates_fixed[1][j] = 0;
	}


	HERE_L = 0;
	HERE_R = 0;
	CAMERA_X = 0;
	CAMERA_Y = 0;
	CAMERA_Z = 0;

	distance_from_ISAC	= 0;
	height_from_ISAC	= 0;
	shift_from_ISAC		= 0;
	rotation_from_ISAC	= 0;
		
	avg_count			= 0;

	sum_distance		= 0;
	sum_height			= 0;		
	sum_shift			= 0;
}

Camera::~Camera()
{
	for (int j = 0; j < compmax; j++)
		delete Comps[j];

	cvReleaseHist(&hist);
	cvReleaseMat(&intrinsic_camera_parameters);
	cvReleaseMat(&distortion_coeffs);
	cvReleaseMat(&rotation_vectors);
	cvReleaseMat(&rotation_matrix);
	cvReleaseMat(&translation_vectors);
}

//************************************************************************
//Description: obtains pixel coordinates of end effector location by using
//		hue detection.  getCameraCoordinates reads in images as defined by
//		the function call and returns the camera coordinates (pixel locations) 
//		by value.  The purpose of this function is to find the
//		largest hue blob in the frame, which it accomplishes by backprojecting a 
//		hue histogram followed by erosion to get rid of small noisy elements.  Then
//		the largest blob is chosen based upon the area of the foreground connected
//		components.  The center of this blob is calculated by finding the middle of the
//		bounding box and then returned.
//
//		Several function calls are commented out.  These functions use the highgui 
//		openCV library to display the operations being performed.  They range from
//		displaying the original image to placing a 10x10 block on the location of the 
//		center of the end effector.
//
//Variables:
//		cam_choice allows the user to pick the left or right camera (0 = left, 1 = right)
void Camera::getCameraCoordinates(char *image_location, bool cam_choice, int * camera_coordinates)
{
	// IplImages used for hue histogram matching
	IplImage * image = cvCreateImage(cvSize(320,240),8,3);
	IplImage * hue   = cvCreateImage(cvSize(320,240),8,1);
	IplImage * sat   = cvCreateImage(cvSize(320,240),8,1);
	IplImage * val   = cvCreateImage(cvSize(320,240),8,1);
	IplImage * grey  = cvCreateImage(cvSize(320,240),8,1);
	// window to display output images periodically
//	cvNamedWindow("ImageR:",1);
//	cvNamedWindow("HueR:",2);
//	cvNamedWindow("ImageL:",3);
//	cvNamedWindow("HueL:",4);
	// 3x3 rectangular mask used for morphological operations (erosion and dilation)
	IplConvKernel * mask = cvCreateStructuringElementEx(3,3,1,1,CV_SHAPE_RECT);

	image = cvLoadImage(image_location);
	//image = cvLoadImage("test_06purple.jpg");

	cvCvtColor(image,grey,CV_BGR2GRAY);									// used for displaying center of hue blob
	cvCvtColor(image,image,CV_BGR2HSV);
	cvSplit(image,hue,sat,val,NULL);									// split into hsv bands
//	cvShowImage("Image:",hue); cvWaitKey();

	// remap hue image by backprojecting hue histogram of specified hue
	getHistogram();
	cvCalcBackProject(&hue,hue,hist);
	// rid the image of noisy, small hue occurances and use the remaining to create a binary blob image
	// of the desired hue

//	cvShowImage("Image:",hue); cvWaitKey();
	cvSmooth(hue,hue,CV_GAUSSIAN,7,7,3);
//	cvShowImage("Image:",hue); cvWaitKey();
	cvThreshold(hue,hue,110,255,CV_THRESH_BINARY);
//	cvShowImage("Image:",hue); cvWaitKey();
	cvErode(hue,hue,mask,4);
	cvDilate(hue,hue,mask,8);

//	if (cam_choice == 1)
//		cvShowImage("HueR:",hue); //cvWaitKey();
//	else
//		cvShowImage("HueL:",hue);

		// separate hue blobs
		getConnectedComps(hue,Comps);
		// find largest hue blob and then its center
		if (comptot != 0)
		{
			maxcomp = 0;
			maxarea = Comps[0]->area;
			for (int j = 0; j < comptot; j++)
			{
				if (Comps[j]->area > maxarea)
				{
					maxarea = Comps[j]->area;
					maxcomp = j;
				}
			}
			camera_coordinates[0] = Comps[maxcomp]->rect.x + Comps[maxcomp]->rect.width/2;
			camera_coordinates[1] = Comps[maxcomp]->rect.y + Comps[maxcomp]->rect.height/2;

			for (int jx = -5; jx < 6; jx++)
				for (int jy = -5; jy < 6; jy++)
					//cvSet2D(grey,int(camera_coordinates[0]+jx),int(camera_coordinates[1]+jy),cvScalar(255));
					cvSet2D(grey,int(camera_coordinates[1]+jx),int(camera_coordinates[0]+jy),cvScalar(255));
			if (cam_choice == 0)
				HERE_L = 1;
			else
				HERE_R = 1;
		}
		else  // no point was detected
			if (cam_choice == 0)
				HERE_L = 0;
			else
				HERE_R = 0;

		// Show output grey image with square marking center to ensure the hue blob was located correctly
//		if (cam_choice == 1)
//			cvShowImage("ImageR:",grey);// cvWaitKey();
//		else
//			cvShowImage("ImageL:",grey);
		
//		cvWaitKey();

//	cvDestroyWindow("ImageR:");
//	cvDestroyWindow("HueR:");
	
//	cvDestroyWindow("ImageL:");
//	cvDestroyWindow("HueL:");

	cvReleaseImage(&image);
	cvReleaseImage(&hue);
	cvReleaseImage(&sat);
	cvReleaseImage(&val);
	cvReleaseImage(&grey);

/*	if (cam_choice == 0)
		printf("LEFT:\t%d\t%d\n",camera_coordinates[0],camera_coordinates[1]);
	else
		printf("\t\t\tRIGHT:\t%d\t%d\n",camera_coordinates[0],camera_coordinates[1]);
*/
	return;
}

//************************************************************************
//Description: obtains pixel coordinates of end effector location by using
//		hue detection.  getCameraCoordinates reads in images from as defined by
//		the text files FilenamesL.txt and FilenamesR.txt.  There should be 24 
//		images within these files.  The purpose of this function is to find the
//		largest hue blob in the frame, which it accomplishes by backprojecting a 
//		hue histogram followed by erosion to get rid of small noisy elements.  Then
//		the largest blob is chosen based upon the area of the foreground connected
//		components.  The center of this blob is calculated by finding the middle of the
//		bounding box.  These values are then written to PixelCoordinatesL.txt and 
//		PixelCoordinatesR.txt, respectively.  If fewer than 8 locations are found, the
//		initialization of the arm must be redone
//
//		Several function calls are commented out.  These functions use the highgui 
//		openCV library to display the operations being performed.  They range from
//		displaying the original image to placing a 10x10 block on the location of the 
//		center of the end effector.
//
//Variables:
//		cam_choice allows the user to pick the left or right camera (0 = left, 1 = right)
//************************************************************************
void Camera::getFixedCameraCoordinates(bool cam_choice)
{
	// IplImages used for hue histogram matching
	IplImage * image = cvCreateImage(cvSize(320,240),8,3);
	IplImage * hue   = cvCreateImage(cvSize(320,240),8,1);
	IplImage * sat   = cvCreateImage(cvSize(320,240),8,1);
	IplImage * val   = cvCreateImage(cvSize(320,240),8,1);
	IplImage * grey  = cvCreateImage(cvSize(320,240),8,1);
	// window to display output images periodically
//	cvNamedWindow("Image:",1);
	// 3x3 rectangular mask used for morphological operations (erosion and dilation)
	IplConvKernel * mask = cvCreateStructuringElementEx(3,3,1,1,CV_SHAPE_RECT);

	string filepath;
	char ch;
	ifstream inFile;
	// open txt file containing file paths
	if (cam_choice == 0)
		inFile.open("FilenamesL.txt");
	else
		inFile.open("FilenamesR.txt");

	if (!inFile)
	{
		cout << "Unable to open filenames file.";
		cin.get();
		exit(1); // terminate with error
	}
	for (int i = 1; i < 11; i++)
	{
		// capture current file name
		filepath = "";
		do 
		{
			if(!inFile.get(ch))
				break;
			if(ch == '\n' || ch == EOF)
				break;
			filepath = filepath + ch;
		} while(1);
		// load in image[i] to compute pixel coordinates of the current location
		const char * filer = filepath.c_str();	
		image = cvLoadImage(filer);
		//image = cvLoadImage("test_06purple.jpg");

	cvCvtColor(image,grey,CV_BGR2GRAY);										// used for displaying center of hue blob
		cvCvtColor(image,image,CV_BGR2HSV);
		cvSplit(image,hue,sat,val,NULL);										// split into hsv bands
//	cvShowImage("Image:",hue); cvWaitKey();
		// remap hue image by backprojecting hue histogram of specified hue
		getHistogram();
		cvCalcBackProject(&hue,hue,hist);
		// rid the image of noisy, small hue occurances and use the remaining to create a binary blob image
		// of the desired hue
//	cvShowImage("Image:",hue); cvWaitKey();
		cvSmooth(hue,hue,CV_GAUSSIAN,7,7,3);
//	cvShowImage("Image:",hue); cvWaitKey();
		cvThreshold(hue,hue,110,255,CV_THRESH_BINARY);
//	cvShowImage("Image:",hue); cvWaitKey();
		cvErode(hue,hue,mask,4);
//	cvShowImage("Image:",hue); cvWaitKey();
		// separate hue blobs
		getConnectedComps(hue,Comps);
		// find largest hue blob and then its center
		if (comptot != 0)
		{
			maxcomp = 0;
			maxarea = Comps[0]->area;
			for (int j = 0; j < comptot; j++)
			{
				if (Comps[j]->area > maxarea)
				{
					maxarea = Comps[j]->area;
					maxcomp = j;
				}
			}
			camera_coordinates_fixed[0][i-1] = Comps[maxcomp]->rect.x + Comps[maxcomp]->rect.width/2;
			camera_coordinates_fixed[1][i-1] = Comps[maxcomp]->rect.y + Comps[maxcomp]->rect.height/2;

			for (int jx = -5; jx < 6; jx++)
				for (int jy = -5; jy < 6; jy++)
					cvSet2D(grey,int(camera_coordinates_fixed[1][i-1]+jx),int(camera_coordinates_fixed[0][i-1]+jy),cvScalar(0));
			present[i-1] = 1;
		}
		else  // no point was detected
			present[i-1] = 0;

		// Show output grey image with square marking center to ensure the hue blob was located correctly
//		cvShowImage("Image:",grey); cvWaitKey();
	}

	ofstream ccFile;
	// open output txt file to write the camera coordinates to
	if (cam_choice == 0)
		ccFile.open("PixelCoordinatesL.txt");
	else
		ccFile.open("PixelCoordinatesR.txt");

	if (!ccFile)
	{
		cout << "Unable to open PixelCoordinates file.";
		cin.get();
		exit(1); // terminate with error
    }
	for (int j = 0; j < 24; j++)
		if (present[j] == 1)
			ccFile <<  camera_coordinates_fixed[1][j] << "     " << camera_coordinates_fixed[0][j] << endl;

	numpoints = 0; // holds number of world points for current process
	for (j = 0; j < 24; j++)
		if (present[j] == 1)
			numpoints++;
	
	if (cam_choice == 0)
		cout << numpoints << " pixel locations were found from the left camera." << endl;
	else
		cout << numpoints << " pixel locations were found from the right camera." << endl;

	// ensure the number of points is great enough for calibration
	if (numpoints < 8)
	{
		cout << "Too few points for camera calibration." << endl;
		cout << "Move arm and restart program." << endl;
		cin.get();
		exit(1); // terminate with error
	}
		
	inFile.close();
	ccFile.close();

//	cvDestroyWindow("Image");

	cvReleaseImage(&image);
	cvReleaseImage(&hue);
	cvReleaseImage(&sat);
	cvReleaseImage(&val);
	cvReleaseImage(&grey);

	return;
}


//************************************************************************
//Description: getConnectedComponents is used to distinguish between foreground
//		and background elements within the image.  It does so by rasterscanning the image
//		for foreground pixels (pixel == 255) and numbers the areas accordingly.
//		If adjacent areas have the same numbers and are both foreground or background pixels
//		they are combined into one connected component.  Only foreground pixels are placed
//		into Comps.  If more than 20 components are found, a new Comps is
//		initialized including old values.
//
//Variables:
//		image is a binary image that has foreground and backgroun elements
//		Comps holds all of the data for the connected components found in image
//************************************************************************
void Camera::getConnectedComps(IplImage *image, CvConnectedComp ** Comps)
{
	CvScalar pixval;
	comptot = 0;
	int CurrentCompVal = 0;
	// used if need  to reinitialize components array for more capacity
	CvConnectedComp ** NewComp;

	for (int j = 0; j < 320*240; j++)
	{
		pixval = cvGet2D(image,j/320,j%320);
		// if this pixel has the value of 255, this component has not yet been recorded
		if (pixval.val[0] > CurrentCompVal)
		{
			if (CurrentCompVal >= compmax)
				Comps[CurrentCompVal] = new CvConnectedComp;
			// fill this component in with the next lowest value
			cvFloodFill(image,cvPoint(j%320,j/320),cvScalar(CurrentCompVal + 1),cvScalar(0),cvScalar(0),Comps[CurrentCompVal],4);
			CurrentCompVal++;
			// if at capacity reinitialize array to higher capacity
			if (CurrentCompVal >= compcap)
			{
				NewComp = new CvConnectedComp*[compcap + 20];
				for (int i = 0; i < CurrentCompVal; i++)
				{
					// copy component values into new array
					NewComp[i] = new CvConnectedComp;
					NewComp[i]->area = Comps[i]->area;
					NewComp[i]->value.val[0] = Comps[i]->value.val[0];
					NewComp[i]->rect = Comps[i]->rect;
					// delete old values
					delete Comps[i];
				}
				// update pointers and capacity
				compcap = compcap + 20;
				Comps = NewComp;
			}
		}
	}
	// update total number of components being used
	comptot = CurrentCompVal;
	// ensure total number of components ever used is up to date (for deletion)
	if (comptot > compmax)
		compmax = comptot;
	return;
}


//************************************************************************
//Description: getHistogram creates a histogram from based upon the file
//		hue_test_05.bmp.  This file can be changed to find different hues.
//
//************************************************************************
void Camera::getHistogram(void)
{
	int w = 130; int h = 125;

	IplImage * samp  = cvCreateImage(cvSize(w,h),8,3);
	IplImage * hue   = cvCreateImage(cvSize(w,h),8,1);
	IplImage * sat   = cvCreateImage(cvSize(w,h),8,1);
	IplImage * val   = cvCreateImage(cvSize(w,h),8,1);

	samp  = cvLoadImage("hue_test_teal_beanbag.bmp");
	cvCvtColor(samp,samp,CV_BGR2HSV);

	cvCvtPixToPlane(samp,hue,sat,val,NULL);

	cvCalcHist(&hue,hist,0,0);
}


//************************************************************************
//
//
//
//						>>>	DOES NOT WORK <<<
//
//
//
//Description: Prints out the homography matrices showing world to camera transformations
//		and camera to world transformations. Based off of Dr. Peter's Image Processing
//		Class algorithm.
//
//Variables:
//		cam_choice allows the user to pick the left or right camera (0 = left, 1 = right)
//		dpan is the pan angle of the camera
//		dtilt is the tilt angle of the camera
//************************************************************************
void Camera::getTransforms(bool cam_choice, double dpan, double dtilt)
{
	
	ifstream worldFile;		//file of world coordinates
	ifstream pixelFile;		//file of image coordinates

	//Allocate Matrices
	CvMat * world = cvCreateMat(3,numpoints,CV_32FC1);		//24
	CvMat * pixel = cvCreateMat(3,numpoints,CV_32FC1);		//24
	CvMat * Q     = cvCreateMat(2*numpoints,11,CV_32FC1);	//24
	CvMat * tempQ = cvCreateMat(11,2*numpoints,CV_32FC1);	//24
	CvMat * prodQ = cvCreateMat(11,11,CV_32FC1);
	CvMat * x     = cvCreateMat(2*numpoints,1,CV_32FC1);	//24
	CvMat * d	  = cvCreateMat(11,1,CV_32FC1);
	CvMat * D     = cvCreateMat(3,4,CV_32FC1);
	CvMat * M     = cvCreateMat(3,4,CV_32FC1);
	CvMat * m     = cvCreateMat(3,3,CV_32FC1);
	CvMat * t_C_W = cvCreateMat(3,1,CV_32FC1);
	CvMat * T_C_W = cvCreateMat(3,1,CV_32FC1);
	CvMat * U     = cvCreateMat(3,3,CV_32FC1);
	CvMat * V     = cvCreateMat(3,3,CV_32FC1);
	CvMat * v     = cvCreateMat(3,3,CV_32FC1);
	CvMat * S     = cvCreateMat(3,3,CV_32FC1);
	CvMat * s	  = cvCreateMat(3,3,CV_32FC1);
	CvMat * A_C_W = cvCreateMat(3,3,CV_32FC1);
	CvMat * a_c_w = cvCreateMat(3,3,CV_32FC1);
	CvMat * temp2 = cvCreateMat(3,1,CV_32FC1);
	CvMat * World2Camera = cvCreateMat(4,4,CV_32FC1);
	CvMat * Camera2World = cvCreateMat(4,4,CV_32FC1);

	double w,y,z,z_c_w;
	double k = 1/(sigma*focal_length);


	//Read in World and Pixel Coordinates
	worldFile.open("WorldCoordinates.txt");

	
	if (cam_choice == 0)								//Open either the left or right camera images
		pixelFile.open("PixelCoordinatesL.txt");
	else
		pixelFile.open("PixelCoordinatesR.txt");

	
	if (!worldFile)										//Make sure files were read in
	{
		cout << "Unable to open WorldCoordinates.txt";
		cin.get();
		exit(1); // terminate with error
    }
	if (!pixelFile)
	{
		cout << "Unable to open PixelCoordinates file";
		cin.get();
		exit(1); // terminate with error
    }


	//Set up the world and image pixel matrices
	for (int j = 0; j < numpoints; j++) //24
	{
		if (present[j] == 1)
		{
			worldFile >> w >> y >> z;
				cvmSet(world,0,j,w);
				cvmSet(world,1,j,y);
				cvmSet(world,2,j,z);
		}
		pixelFile >> w >> y;
			cvmSet(pixel,0,j,(w-row_center)*(-1));		// accounts for row center in the image plane
			cvmSet(pixel,1,j,(y-col_center)*(-1));		// accounts for column center in the image plane
			cvmSet(pixel,2,j,focal_length);		// inserts 3rd row make sure sigma and focal length are included
	}
	// initialize Q
	/*for (j = 0; j < 11; j++)
		for (int i = 0; i < 12; i++)	//48 = 2*rows of Q
		{
			if (j <= 3-1)
			{
				if(i % 2 == 0)
					cvmSet(Q,i,j,cvmGet(world,j,int(ceil(i/2))));
			}
			else if (j == 4-1)
			{
				if (i % 2 == 0)
					cvmSet(Q,i,j,1.0);
			}
			else if (j > 4-1 && j < 8-1)
			{
				if (i % 2 != 0)
					cvmSet(Q,i,j,cvmGet(world,j-4,int(ceil(i/2))));
			}
			else if (j == 8-1)
			{
				if (i % 2 != 0)
					cvmSet(Q,i,j,1.0);
			}
			else if (j >= 9-1)
			{
				if (i % 2 == 0)
					cvmSet(Q,i,j,cvmGet(pixel,1,i/2)*cvmGet(world,j-8,i/2));
				else
					cvmSet(Q,i,j,cvmGet(pixel,0,int(ceil(i/2)))*cvmGet(world,j-8,int(ceil(i/2))));
			}
		}*/


	//Set up the Q matrix

	for (int i = 0; i < 2*numpoints; i+=2)
		for( j = 0; j < 11; j++)
		{
			if (j < 3 )
				cvmSet(Q,i,j,cvmGet(world,j,i/2));
			else if (j == 3)
				cvmSet(Q,i,j,1.0);
			else if (j >=4 && j<=7)
				cvmSet(Q,i,j,0.0);
			else if (j > 7)
				cvmSet(Q,i,j,cvmGet(pixel,0,i/2)*cvmGet(world,j-8,i/2));
		}

	for (i = 1; i < 2*numpoints; i+=2)
		for( j = 0; j < 11; j++)
		{
			if (j < 4 )
				cvmSet(Q,i,j,0.0);
			else if (j >= 4 && j < 7)
				cvmSet(Q,i,j,cvmGet(world,j-4,i/2));
			else if (j == 7)
				cvmSet(Q,i,j,1.0);
			else if (j > 7)
				cvmSet(Q,i,j,cvmGet(pixel,1,i/2)*cvmGet(world,j-8,i/2));
		}


	// initialize x
	i = 0;
	
	for (j = 0; j < 2*numpoints; j+=2) //24
	{
		cvmSet(x,j,0,cvmGet(pixel,0,i));
		cvmSet(x,j+1,0,cvmGet(pixel,1,i));
		i++;
	}

	// fill up d, then create D and M
	// d = inv(Q'*Q)*Q'*x
	CvMat * invtQ = cvCreateMat(11,11,CV_32FC1);
	CvMat * prod2Q = cvCreateMat(11,2*numpoints,CV_32FC1);
	cvTranspose(Q,tempQ);
	cvMatMul(tempQ,Q,prodQ);
	cvInvert(prodQ,invtQ,CV_LU);
	cvMatMul(invtQ,tempQ,prod2Q);
	cvMatMul(prod2Q,x,d);

	int h = 0;

	for (i = 0; i < 3; i++)
		for (j = 0; j < 4; j++)
		{
			if(i==2 && j==3)
				cvmSet(D,i,j,1);
			else
				cvmSet(D,i,j,cvmGet(d,h,0));
			h++;
		}

	for (int kk = 0; kk < 3; kk++)
	{
		for (j = 0; j < 4; j++)
			cout << cvmGet(D,kk,j) << " ";
		cout << endl;
	}

//	for (i =0; i <3; i++)
//		for (j = 0; j < 4; j++)
//			cvmSet(M,i,j,cvmGet(D,i,j));

	//M = D;
	for (i = 0; i < 3; i++)
	{
		cvmSet(M,0,i,k*cvmGet(D,0,i));
		cvmSet(M,1,i,k*cvmGet(D,1,i));
//		cvmSet(M,0,i,cvmGet(M,0,i));
//		cvmSet(M,1,i,cvmGet(M,1,i));
		cvmSet(M,2,i,-cvmGet(D,2,i));
	}
//	cvmSet(M,0,i,k*cvmGet(M,0,i));
//	cvmSet(M,1,i,k*cvmGet(M,1,i));
	
	//T_C_W = M(:,4)
	for (i = 0; i < 3; i++)
		cvmSet(t_C_W,i,0,cvmGet(D,i,3));
	cvmSet(t_C_W,2,0,1.0);
	
	//M = M(:,1:3)
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			cvmSet(m,i,j,cvmGet(M,i,j));

	//svd(M)
	cvSVD(m,S,U,V,0);
	
	//z_c_w = trace(inv(S))/3;
	cvInvert(S,s,CV_LU);
	double trace = 0;

	for (i = 0; i < 3; i++)
		trace = trace + cvmGet(s,i,i);

	z_c_w = trace / 3;

	//A_C_W = z_c_w*M
	for (i = 0; i<3; i++)
	{
		for (j = 0; j<3; j++)
			cvmSet(A_C_W,i,j,z_c_w*cvmGet(m,i,j));
		cvmSet(T_C_W,i,0,z_c_w*cvmGet(t_C_W,i,0));
	}
//	cvTranspose(V,v);
//	cvMatMul(U,v,A_C_W);


	//World2Camera = [A_C_W T_C_W];
	for (i = 0; i<3; i++)
		for (j = 0; j<3; j++)
			cvmSet(World2Camera,i,j,cvmGet(A_C_W,i,j));
	
	cvmSet(World2Camera,0,3,cvmGet(T_C_W,0,0));
	cvmSet(World2Camera,1,3,cvmGet(T_C_W,1,0));
	cvmSet(World2Camera,2,3,cvmGet(T_C_W,2,0));
	
	//Homography matrix representation
	cvmSet(World2Camera,3,0,0.0);
	cvmSet(World2Camera,3,1,0.0);
	cvmSet(World2Camera,3,2,0.0);
	cvmSet(World2Camera,3,3,1.0);

	//Camera2World = [A_C_W' -A_C_W'*T_C_W];
	cvInvert(A_C_W,a_c_w);

	for (i = 0; i<3; i++)
		for (j = 0; j<3; j++)
		{
			cvmSet(Camera2World,i,j,cvmGet(a_c_w,i,j));
			cvmSet(a_c_w,i,j,-1*cvmGet(a_c_w,i,j));
		}

	cvMatMul(a_c_w,T_C_W,temp2);
	cvmSet(Camera2World,0,3,cvmGet(temp2,0,0));
	cvmSet(Camera2World,1,3,cvmGet(temp2,1,0));
	cvmSet(Camera2World,2,3,cvmGet(temp2,2,0));
	
	//Homography matrix representation
	cvmSet(Camera2World,3,0,0.0);
	cvmSet(Camera2World,3,1,0.0);
	cvmSet(Camera2World,3,2,0.0);
	cvmSet(Camera2World,3,3,1.0);
	
	//Transform cameras to a common middle point
//	getCameraTransforms(dpan,dtilt,Camera2World,1,cam_choice);
//	getCameraTransforms(dpan,dtilt,World2Camera,0,cam_choice);

	//Output 
	ofstream C2WFile;
	if (cam_choice == 0)
		C2WFile.open("Camera2WorldL.txt");
	else
		C2WFile.open("Camera2WorldR.txt");

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			w = cvmGet(Camera2World,i,j);
			if(j == 3)
			{
				C2WFile << w << endl;
			}
			else
			{
				C2WFile << w << "     ";
			}
		}
	
	ofstream W2CFile;
	if (cam_choice == 0)
		W2CFile.open("World2CameraL.txt");
	else
		W2CFile.open("World2CameraR.txt");

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			w = cvmGet(World2Camera,i,j);
			if(j == 3)
			{
				W2CFile << w << endl;
			}
			else
			{
				W2CFile << w << "     ";
			}
		}

	//close i/o files
	worldFile.close();
	pixelFile.close();
	C2WFile.close();
	W2CFile.close();

	//Release dynamic variables
	cvReleaseMat(&world);
	cvReleaseMat(&pixel);
	cvReleaseMat(&Q);
	cvReleaseMat(&tempQ);
	cvReleaseMat(&x);
	cvReleaseMat(&d);
	cvReleaseMat(&M);
	cvReleaseMat(&D);
	cvReleaseMat(&m);
	cvReleaseMat(&t_C_W);
	cvReleaseMat(&T_C_W);
	cvReleaseMat(&U);
	cvReleaseMat(&V);
	cvReleaseMat(&v);
	cvReleaseMat(&S);
	cvReleaseMat(&s);
	cvReleaseMat(&A_C_W);
	cvReleaseMat(&a_c_w);
	cvReleaseMat(&temp2);
	cvReleaseMat(&World2Camera);
	cvReleaseMat(&Camera2World);
	cvReleaseMat(&invtQ);
	cvReleaseMat(&prodQ);
	cvReleaseMat(&prod2Q);
}

//************************************************************************
//
//
//
//						>>> DOES NOT WORK <<<
//
//
//
//Description: The transforms that are created from getTransforms() are from the arm's
//		base to the camera focal point. The camera and its focal point move during ISAC
//		operation. The transforms need to be based off constant reference points. This
//		function rotates and translates the transforms to a constant reference point
//		between the two cameras.
// 
//Variables:
//		cam_choice: allows the user to pick the left or right camera (0 = left, 1 = right)
//		dpan: is the pan angle of the camera
//		dtilt: is the tilt angle of the camera
//		inv: is a flag, 0 specifies not to take the inverse
//		transform: to be rotated and translated
//************************************************************************
/*void Camera::getCameraTransforms(double dpan, double dtilt, CvMat* transform, bool inv, bool cam_choice)
{
	
	//Allocate Matrices
	CvMat * r_pan  = cvCreateMat(4,4,CV_32FC1);
	CvMat * r_tilt = cvCreateMat(4,4,CV_32FC1);
	CvMat * trans  = cvCreateMat(4,4,CV_32FC1);

	CvMat * base2cam   = cvCreateMat(4,4,CV_32FC1);
	CvMat * base2cam2	= cvCreateMat(4,4,CV_32FC1);
	CvMat * r_base2cam  = cvCreateMat(3,3,CV_32FC1);
	CvMat * t_base2cam  = cvCreateMat(3,1,CV_32FC1);

	CvMat * cam2base    = cvCreateMat(4,4,CV_32FC1);
	
	double s_theta, c_theta;

	//Set up the rotational and translational matrices for the camera

	if (cam_choice == 0)							//LEFT camera
	{
		s_theta = sin(dpan);
		c_theta = cos(-dpan);

			cvmSet(r_pan,0,0,c_theta);				//set up rotation
			cvmSet(r_pan,0,1,-s_theta);
			cvmSet(r_pan,0,2,0.0);
			cvmSet(r_pan,1,0,s_theta);
			cvmSet(r_pan,1,1,c_theta);
			cvmSet(r_pan,1,2,0.0);
			cvmSet(r_pan,2,0,0.0);
			cvmSet(r_pan,2,1,0.0);
			cvmSet(r_pan,2,2,1.0);
			for (int i = 0; i < 3; i++)
			{
				cvmSet(r_pan,i,3,0.0);
				cvmSet(r_pan,3,i,0.0);
			}
			cvmSet(r_pan,3,3,1.0);

			for (i = 0; i < 3; i++)					//set up translation
				for (int j = 0; j < 4; j++)
				{
					if(i==j)
						cvmSet(trans,j,i,1.0);
					else
						cvmSet(trans,j,i,0.0);
				}
			
			cvmSet(trans,0,3,-39.0);				
			cvmSet(trans,1,3,140.0);
			cvmSet(trans,2,3,-65.5);
			cvmSet(trans,3,3,1.0);
	}
	else											//RIGHT camera
	{				
		s_theta = sin(dpan);
		c_theta = cos(-dpan);

			cvmSet(r_pan,0,0,c_theta);				//set up rotation
			cvmSet(r_pan,0,1,-s_theta);
			cvmSet(r_pan,0,2,0.0);
			cvmSet(r_pan,1,0,s_theta);
			cvmSet(r_pan,1,1,c_theta);
			cvmSet(r_pan,1,2,0.0);
			cvmSet(r_pan,2,0,0.0);
			cvmSet(r_pan,2,1,0.0);
			cvmSet(r_pan,2,2,1.0);
			for (int i = 0; i < 3; i++)
			{
				cvmSet(r_pan,i,3,0.0);
				cvmSet(r_pan,3,i,0.0);
			}
			cvmSet(r_pan,3,3,1.0);

			for (i = 0; i < 3; i++)					//set up translation
				for (int j = 0; j < 4; j++)
				{
					if(i==j)
						cvmSet(trans,j,i,1.0);
					else
						cvmSet(trans,j,i,0.0);
				}
			
			cvmSet(trans,0,3,-39.0);
			cvmSet(trans,1,3,-140.0);
			cvmSet(trans,2,3,-65.5);
			cvmSet(trans,3,3,1.0);
	}

	
		s_theta = sin(dtilt);
		c_theta = cos(dtilt);

			cvmSet(r_tilt,0,0,c_theta);
			cvmSet(r_tilt,0,1,0.0);
			cvmSet(r_tilt,0,2,s_theta);
			cvmSet(r_tilt,1,0,0.0);
			cvmSet(r_tilt,1,1,1.0);
			cvmSet(r_tilt,1,2,0.0);
			cvmSet(r_tilt,2,0,-s_theta);
			cvmSet(r_tilt,2,1,0.0);
			cvmSet(r_tilt,2,2,c_theta);
			for (int i = 0; i < 3; i++)
			{
				cvmSet(r_tilt,i,3,0.0);
				cvmSet(r_tilt,3,i,0.0);
			}
			cvmSet(r_tilt,3,3,1.0);

	cvMatMul(r_pan,r_tilt,base2cam2);				//combine the matrices
	cvMatMul(base2cam2,trans,base2cam);
//	double w;


	cout << endl << endl;
	
	if (inv == 0)									//see if inverse should be taken
	{
		cvMatMul(transform,base2cam,transform);
	}
	else
	{
		for (i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
				cvmSet(r_base2cam,j,i,cvmGet(base2cam,i,j));
			cvmSet(t_base2cam,i,0,cvmGet(base2cam,i,3));
		}

		for (i = 0; i<3; i++)
			for (int j = 0; j<3; j++)
			{
				cvmSet(cam2base,i,j,cvmGet(r_base2cam,i,j));
				cvmSet(r_base2cam,i,j,-1*cvmGet(r_base2cam,i,j));
			}
		
		cvMatMul(r_base2cam,t_base2cam,t_base2cam);
		cvmSet(cam2base,0,3,cvmGet(t_base2cam,0,0));
		cvmSet(cam2base,1,3,cvmGet(t_base2cam,1,0));
		cvmSet(cam2base,2,3,cvmGet(t_base2cam,2,0));

		cvmSet(cam2base,3,0,0.0);
		cvmSet(cam2base,3,1,0.0);
		cvmSet(cam2base,3,2,0.0);
		cvmSet(cam2base,3,3,1.0);

		cvMatMul(transform,cam2base,transform);
	}

	
	//Release dynamic variables
	cvReleaseMat(&r_pan);
	cvReleaseMat(&r_tilt);
	cvReleaseMat(&trans);
	cvReleaseMat(&base2cam);
	cvReleaseMat(&r_base2cam);
	cvReleaseMat(&t_base2cam);
	cvReleaseMat(&cam2base);
}
*/
//if the object is far from the center move it a lot, close a medium, really close, a small amount
// stolen from sean begley	 
void Camera::centerCams(int lX, int lY, int rX, int rY)
{
	int Y = int((lY+rY)/2);
//	double pantilt[4];	//placeholder... real pantilt should be global... but this function isnt used anymore
//	printf("%f\t%f\t%f\t%f\n",pantilt[0],pantilt[1],pantilt[2],pantilt[3]);
	
	/*//left cam X (pan)
	if (lX < 80)
	{ pantilt[0] = pantilt[0] + DELTA_B;}
	else if (lX >= 80 && lX < 150)
	{ pantilt[0] = pantilt[0] + DELTA_M;}
	else if (lX >= 150 && lX < 158)
	{ pantilt[0] = pantilt[0] + DELTA_S;}
	//else if (*lX = 160) no change;
	else if (lX > 162 && lX <= 170)
	{ pantilt[0] = pantilt[0] - DELTA_S;}
	else if (lX > 170 && lX < 240)
	{ pantilt[0] = pantilt[0] - DELTA_M;}
	else{} 
	// no change {pantilt[0] = pantilt[0] - DELTA_B;}*/

/*	//left cam Y (tilt)
	if (*lY < 60)
	{ pantilt[1] = pantilt[1] + DELTA_B;}
	else if (*lY >= 60 && *lY < 110)
	{ pantilt[1] = pantilt[1] + DELTA_M;}
	else if (*lY >= 110 && *lY < 118)
	{ pantilt[1] = pantilt[1] + DELTA_S;}
	//else if (*lY = 120) no change;
	else if (*lY >= 122 && *lY <= 130)
	{ pantilt[1] = pantilt[1] - DELTA_S;}
	else if (*lY >= 130 && *lY < 180)
	{ pantilt[1] = pantilt[1] - DELTA_M;}
	else 
	{pantilt[1] = pantilt[1] + DELTA_B;}
*/
/*	//right cam X (pan)
	if (rX < 80)
	{ pantilt[2] = pantilt[2] + DELTA_B;}
	else if (rX >= 80 && rX < 150)
	{ pantilt[2] = pantilt[2] + DELTA_M;}
	else if (rX >= 150 && rX < 158)
	{ pantilt[2] = pantilt[2] + DELTA_S;}
	//else if (*rX = 160) no change;
	else if (rX > 162 && rX <= 170)
	{ pantilt[2] = pantilt[2] - DELTA_S;}
	else if (rX > 170 && rX < 240)
	{pantilt[2] = pantilt[2] - DELTA_M;}
	else 
	{} 
	// no change {pantilt[2] = pantilt[2] - DELTA_B;}*/

	double tilt_up_limit= 9;
	double tilt_down_limit = -58;

	if(HERE_L == 0 || HERE_R == 0)
	{
		if(tilt_direction == 0)
		{
			pantilt[3] = pantilt[3] - DELTA_B;
			pantilt[1] = pantilt[1] - DELTA_B;
		}
		else
		{
			pantilt[3] = pantilt[3] + DELTA_B;
			pantilt[1] = pantilt[1] + DELTA_B;
		}

		if(pantilt[3] <= tilt_down_limit)
			tilt_direction = 1;

		if(pantilt[3] >= tilt_up_limit)
			tilt_direction = 0;
	}
	else
	{

		//right cam Y (tilt)
		if (Y < 60) 
		{
			pantilt[3] = pantilt[3] + DELTA_B;
			pantilt[1] = pantilt[1] + DELTA_B;
		}
		else if (Y >= 60 && Y < 110)
		{
			pantilt[3] = pantilt[3] + DELTA_M;
			pantilt[1] = pantilt[1] + DELTA_M;
		}
		else if (Y >= 110 && Y < 118)
		{
			pantilt[3] = pantilt[3] + DELTA_S;
			pantilt[1] = pantilt[1] + DELTA_S;
		}
		//else if (*rY = 120) no change;
		else if (Y >= 122 && Y <= 130) 
		{
			pantilt[3] = pantilt[3] - DELTA_S;
			pantilt[1] = pantilt[1] - DELTA_S;
		}
		else if (Y > 130 && Y < 180) 
		{
			pantilt[3] = pantilt[3] - DELTA_M;
			pantilt[1] = pantilt[1] - DELTA_M;
		}
		else if (Y >= 180) 
		{
			pantilt[3] = pantilt[3] - DELTA_B;
			pantilt[1] = pantilt[1] - DELTA_B;
		}
		else {} // nochange
	}

	//move cameras to center object on the screen
//	hd.MoveHead(pantilt);

	//printf("%f\t%f\t%f\t%f\n\n",pantilt[0],pantilt[1],pantilt[2],pantilt[3]);
}


//***********************************************************
//
//		Attempt at Depth from Vergence... DOES NOT WORK
//
//
//
//
//***********************************************************
void Camera::calcXYZ(void)
{
	double A = 285;  // distance between focal points of cameras in mm
	double d = 0;


	double theta_r = M_PI/2-M_PI/180*pantilt[2];

	d = A/(tan(-M_PI/180*pantilt[0]) + tan(M_PI/180*pantilt[2]));

	CAMERA_X = d*cos(M_PI/180*pantilt[1]);			// tilt angles will be the same
	if (pantilt[1] > 0 )
		CAMERA_Z = d*sin(M_PI/180*pantilt[1]) - 65.5;
	else
		CAMERA_Z = d*sin(M_PI/180*pantilt[1]) + 65.5;
	CAMERA_Y = A/2 - d/tan(theta_r);


	printf("%f\t%f\t%f\t%f\n",CAMERA_X,CAMERA_Y,CAMERA_Z,d);

	return;
}

//CAMERA TRANSFORM PARAMETERS
//center to camera base = 140mm (baseline = 280mm)
//camera base to rotation base = 91.948mm
//rotation base to camera = 65.5mm
//camera to focal point = 305.25mm
//sigma = 50 pixels per mm
//rotation about z is from dPan
//rotation about y if from dTilt
//effective picture elements: 768x494
//CCD sensing area: 6.4 x 4.8 mm

//*************************************************************************
//*************************************************************************
//
// Calculate 3D camera points... use Stereopsis
//
//
//
//*************************************************************************
//*************************************************************************
void Camera::calculateXYZ(double lx, double ly, double rx, double ry)
{
	double f = 305.25;	//focal length: 305.25 millimeters (50 px/mm) = 15262.5 px
	double b = 14000;	//base: millimeters (50 px/mm) = 14000 px
	double sigma = 50;  //pixels per mm

	double xri = 0;
	double xli = 0;
	double yli = 0;
	double yri = 0;

	double xr = 0;
	double xl = 0;
	double yr = 0;
	double yl = 0;

	double d = 0;

	double z = 0;
	double y = 0;
	double x = 0;


	//get pixel coords
	xri = rx - 160;
	xli = lx - 160;
	yri = ry - 120;
	yli = ly - 120;

//	printf("LEFT:\t%f\t%f\n",xli,yli);
//	printf("\t\t\tRIGHT:\t%f\t%f\n",xri,yri);

	//find z in weird units
	d=f*b/((double)xli-(double)xri);
	z=d*sin(M_PI/180*(90-pantilt[1]));

	//calculate real y and x values in weird units
	yr=yri*d/f;
	yl=yli*d/f;
	xr=xri*d/f;
	xl=xli*d/f;

	//average y
//	y=(yl+yr)/2;
	y=d*cos(M_PI/180*(90-pantilt[1]));
	
	//average x
	x=(xr+xl)/2;

	//printf("%f\t%f\t%f\n",-z/sigma,x/sigma,y/sigma);

	// coordinates are transformed into the same orientation as the arm where the x+ axis
	// is pointing towards ISAC.  y+ is towards the restrooms, and z+ is towards the ceiling
	// helps simplify coordinate transforms
	CAMERA_X = -z/sigma;
	CAMERA_Y = x/sigma;
	CAMERA_Z = y/sigma;
}

void Camera::Calculate_Point(const char* t_filepath,const char* p_filepath)
{
	CvMat * transform = cvCreateMat(4,4,CV_32FC1);
	CvMat * point	  = cvCreateMat(4,1,CV_32FC1);
	CvMat * newpoint  = cvCreateMat(4,1,CV_32FC1);

	ifstream inTransformFile;
	ifstream inPointFile;

	double val;
	int i,j;

	inTransformFile.open(t_filepath);
	inPointFile.open(p_filepath);

	if (!inTransformFile || !inPointFile)
	{
		cout << "Error";
		cin.get();
		exit(1);
	}

	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			inTransformFile >> val;
			cvmSet(transform,i,j,val);
		}
	}

	for(i = 0; i < 4; i++)
	{
		inPointFile >> val;
		cvmSet(point,i,0,val);
	}

	inTransformFile.close();
	inPointFile.close();

	cvMatMul(transform,point,newpoint);

	cout << "Calculated Point: ";

	for(i = 0; i < 4; i++)
		cout << cvmGet(newpoint,i,0) << " ";

	cout << endl << endl;

	cvReleaseMat(&transform);
	cvReleaseMat(&point);
	cvReleaseMat(&newpoint);

	return;
}

void Camera::Find_Arm(double camera_x, double camera_y, double camera_z, ifstream &inFileArm)//, double camera_y2, double camera_z)
//Take calibration pictures first
//Then call this function
{

	//arm coordinates of end effector (read in from file?)
	double arm_x;
	//double arm_x2;
	double arm_y;
	double arm_z;

	//ifstream inFileArm;
	//inFileArm.open("ArmPos.txt");

	inFileArm >> arm_x;
	inFileArm >> arm_y;
	inFileArm >> arm_z;

	distance_from_ISAC = -camera_x + arm_x;

	height_from_ISAC = (-1)*(-camera_z + arm_z);

	shift_from_ISAC = camera_y;// - arm_y;

	/// now pretending arm has moved again ///

	//inFileArm >> arm_x2;
	//inFileArm >> arm_y;
	//inFileArm >> arm_z;

	//double arm_x_distance_moved;        //in mm
	//double change_in_camera_y;

	//arm_x_distance_moved = arm_x2 - arm_x;

	//change_in_camera_y = camera_y2 - camera_y;

	//rotation_from_ISAC = asin(change_in_camera_y / arm_x_distance_moved); //gives angle that arm is rotated

	//inFileArm.close();

	Update_Shifts();

	return;
}

void Camera::Find_Arm_Coordinates()
{
	//TODO: figure it out based on rotation, distance, height, shift
	/*CvMat * rotatez		= cvCreateMat(4,4,CV_32FC1);
	CvMat * cam2base    = cvCreateMat(4,4,CV_32FC1);
	CvMat * trans		= cvCreateMat(4,4,CV_32FC1);

	CvMat * camera		= cvCreateMat(4,1,CV_32FC1);
	CvMat * arm			= cvCreateMat(4,1,CV_32FC1);
	
	double s_theta, c_theta;
	int i;

	// SET UP Z-ROTATION by amount from ISAC

	s_theta = sin(rotation_from_ISAC);
	c_theta = cos(rotation_from_ISAC);

		cvmSet(rotatez,0,0,c_theta);				//set up rotation
		cvmSet(rotatez,0,1,-s_theta);
		cvmSet(rotatez,0,2,0.0);
		cvmSet(rotatez,1,0,s_theta);
		cvmSet(rotatez,1,1,c_theta);
		cvmSet(rotatez,1,2,0.0);
		cvmSet(rotatez,2,0,0.0);
		cvmSet(rotatez,2,1,0.0);
		cvmSet(rotatez,2,2,1.0);
		for (i = 0; i < 3; i++)
		{
			cvmSet(rotatez,i,3,0.0);
			cvmSet(rotatez,3,i,0.0);
		}
		cvmSet(rotatez,3,3,1.0);

		for (i = 0; i < 3; i++)					//set up translation
			for (int j = 0; j < 4; j++)
			{
				if(i==j)
					cvmSet(trans,j,i,1.0);
				else
					cvmSet(trans,j,i,0.0);
			}
	*/
	int i,j;
	double w;

	CvMat * trans = cvCreateMat(4,4,CV_32FC1);

	for (i = 0; i < 3; i++)					//set up translation
		for (int j = 0; j < 4; j++)
		{
			if(i==j)
				cvmSet(trans,j,i,1.0);
			else
				cvmSet(trans,j,i,0.0);
		}


	cvmSet(trans,0,3,sum_distance/avg_count);				
	cvmSet(trans,1,3,-sum_shift/avg_count);
	cvmSet(trans,2,3,-sum_height/avg_count);
	cvmSet(trans,3,3,1.0);


	ofstream Transform;
	
	Transform.open("Cam2ArmTransform.txt");

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			w = cvmGet(trans,i,j);
			if(j == 3)
			{
				Transform << w << endl;
			}
			else
			{
				Transform << w << "     ";
			}
		}

	//close i/o files
	Transform.close();



	/*if (avg_count == 2)
	{
		cvmSet(camera,0,0,CAMERA_X);
		cvmSet(camera,1,0,CAMERA_Y);
		cvmSet(camera,2,0,CAMERA_Z);
		cvmSet(camera,3,0,1.0);
	}
	else if (avg_count == 1)
	{
		cvmSet(camera,0,0,-530);
		cvmSet(camera,1,0,-36);
		cvmSet(camera,2,0,-371);
		cvmSet(camera,3,0,1.0);
	}
	else
	{
		cvmSet(camera,0,0,-593);
		cvmSet(camera,1,0,-37);
		cvmSet(camera,2,0,-415);
		cvmSet(camera,3,0,1.0);
	}*/

	//cvMatMul(trans,camera,arm);

//	for (i = 0; i < 4; i++)
//		printf("%f\t",cvmGet(arm,i,0));
//	printf("\n");

	//Release dynamic variables
	//cvReleaseMat(&rotatez);
	cvReleaseMat(&trans);
	//cvReleaseMat(&cam2base);
	//cvReleaseMat(&camera);
	//cvReleaseMat(&arm);

	Reset_Shifts();
	
	return;
}

void Camera::Update_Shifts(void)
{
	avg_count += 1;
	
	sum_distance = sum_distance + distance_from_ISAC;
	sum_height   = sum_height + height_from_ISAC;
	sum_shift	 = sum_shift + shift_from_ISAC;
}


void Camera::Reset_Shifts(void)
{
	avg_count	 = 0;
	sum_distance = 0;
	sum_height   = 0;
	sum_shift	 = 0;
}

void Camera::get_writeCoordinates(void)
{
	CvMat * trans  = cvCreateMat(4,4,CV_32FC1);
	CvMat * camera = cvCreateMat(4,1,CV_32FC1);
	CvMat * arm	   = cvCreateMat(4,1,CV_32FC1);

	ifstream inTransforms;
	inTransforms.open("Cam2ArmTransform.txt");

	int i,j;
	float val;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			inTransforms >> val;
			cvmSet(trans,i,j,(double)val);
		}

	cvmSet(camera,0,0,CAMERA_X);
	cvmSet(camera,1,0,CAMERA_Y);
	cvmSet(camera,2,0,CAMERA_Z);
	cvmSet(camera,3,0,1.0);

//	cvmSet(camera,0,0,-530);
//	cvmSet(camera,1,0,-36);
//	cvmSet(camera,2,0,-371);
//	cvmSet(camera,3,0,1.0);

	cvMatMul(trans,camera,arm);

	inTransforms.close();

	ofstream outArms;
	outArms.open("I:\\ScottTomSucks\\WinShell_MotomanLib\\ArmCoordinates.txt");

	for (j = 0; j < 4; j++)
	{
		val = cvmGet(arm,j,0);
		outArms << val << "     ";
	}
	
	outArms.close();
}