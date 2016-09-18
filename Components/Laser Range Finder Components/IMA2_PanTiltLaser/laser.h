//header file for laser range finder communication and setup and operation
//Chris Garber
//04/18/06

// Standard library
#include "stdafx.h"
#include "commport.h"
#include <string.h>
#include <stdio.h>
#include <iostream.h>
#include <conio.h>
#include <math.h>


class laser
{
	
public:
	  // COMMPORT parameters
	CComBSTR m_bsDevFilename3;		// Device filenames for laser
	CComBSTR m_bsCParam3;			// Device parameters for laser
	CCommPort*	pCommLaser;		// COM3 for Laser pan/tilt control
	// Functions for laser
	BOOL Initlaser();
	BOOL Resetlaser();
	void Homelaser();
	int ParseStringToIntegerlaser(char *pStr);		// change: string to readable integers
	void GetTiltMinMaxlaser(int &tiltmin, int &titmax);
	int GetTiltMinMaxlaser();
	BOOL GetLaserPosition(int &Pan, int &Tilt);
	void Movelaser(double deg);
	void Getcameras(double righteye[3], double lefteye[3], double headbuff[4]);
	void SphericalToCartesian(double rta[3]);
	void CartesianToSpherical(double xyz[3]);

};

