
#ifndef CAMERA
#define CAMERA

#include "stdafx.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <math.h>

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

using namespace std;

//big/medium/small changes for camera angles
const double DELTA_B = 2;
const double DELTA_M = .5;
const double DELTA_S = .01;
// camera coordinates in 3 dimensions
/*double CAMERA_X = 0;
double CAMERA_Y = 0;
double CAMERA_Z = 0;

// object present during getCameraCoordinates
bool HERE_L = 0;
bool HERE_R = 0;
*/
//#include "camera_coordinates.cpp"

class Camera
{
	public:
		void getCameraCoordinates(char *image_location, bool cam_choice, int * camera_coordinates);
		void getFixedCameraCoordinates(bool cam_choice); // getCameraCoordinates must be called in tandem with getTransforms
		void getTransforms(bool cam_choice, double dpan, double dtilt);		// so that data is not lost
		void getConnectedComps(IplImage *image, CvConnectedComp **Comps);
		void getHistogram(void);
		void getCameraTransforms(double dpan, double dtilt,CvMat* transform,bool inv, bool cam_choice);
		void centerCams(int lX, int lY, int rX, int rY);
		void calcXYZ(void);
		void calculateXYZ(double lx, double ly, double rx, double ry);
		void Calculate_Point(const char* t_filepath,const char* p_filepath);

		void Find_Arm(double camera_x, double camera_y, double camera_z, ifstream & inFileArm);//double camera_y2, double camera_z);
		void Find_Arm_Coordinates(void);

		void Update_Shifts(void);
		void Reset_Shifts(void);

		void get_writeCoordinates(void);
		
		double pantilt[4];
		bool HERE_L;
		bool HERE_R;
		double CAMERA_X;
		double CAMERA_Y;
		double CAMERA_Z;

		Camera();
		~Camera();

	private:
		int    comptot;		// total number of components in use
		int    compmax;		// maximum number of components ever used
		int	   compcap;		// number of components possible before reallocation necessary
							// used to define CvConnectedComp ** Comps = CvConnectedComp*[compcap];
		double maxarea;		// holds the maximum area for a hue blob
		int    maxcomp;		// holds the number of the best component (ie the one that correlates to maxarea)
		bool   present[24];	// holds if a pixel location was found for a given picture
		int	   numpoints;	// holds total number of points captured for image

		
		double focal_length;
		double sigma;

		double row_center;
		double col_center;

		double distance_from_ISAC;              //how far base is from ISAC
		double height_from_ISAC;                //how far down base is from cameras
		double shift_from_ISAC;                 //how for left/right base is from ISAC head
		double rotation_from_ISAC;              //angle arm box has been rotated (hopefully 0)
		
		int	   avg_count;

		double sum_distance;					//collects all distances for running average (divide by avg_count)
		double sum_height;
		double sum_shift;

		bool tilt_direction;

		CvConnectedComp ** Comps;
		CvHistogram * hist;

		CvMat * intrinsic_camera_parameters;
		CvMat * distortion_coeffs;
		CvMat * rotation_vectors;
		CvMat * rotation_matrix;
		CvMat * translation_vectors;

		double camera_coordinates_fixed[2][24];

		//double pantilt[4];
};


#endif

