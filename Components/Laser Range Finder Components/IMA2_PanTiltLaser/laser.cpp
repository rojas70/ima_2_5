// main laser move file
#include "stdafx.h"
#include "laser.h"
#include <math.h>				//for trig functions	
#include <time.h>



/******************************************************************************

	Name:			InitializeLaser()

	Purpose:		Do the final setup necessary for the proper operation
					 of this component.  Called by the IMA base classes.


*******************************************************************************/

BOOL laser::Initlaser()
{
	USES_CONVERSION;
	m_bsDevFilename3 = "\\COM3";	// set to COM3 for laser port
	// COM3 port.
	char* pFN3 = OLE2T(m_bsDevFilename3);
	pCommLaser	= new CCommPort( pFN3, 9600 );	// Capture COM3@9600baud

	// re-initialize pan-tilt unit
	char strOut[35];
	BOOL commResult1 = FALSE;
	
	// it won't hurt to set these commands each time this is called.

	// Enable terse feedback
	sprintf( strOut, "%s ", "ft");
	commResult1 = pCommLaser->WriteComm(strOut );

//	if ( commResult1 )
//	{
		// Disable DP head limits on startup
//		sprintf( strOut, "%s ", "ld" );
//		commResult1 = pCommLaser->WriteComm(strOut );

		if ( commResult1 )
		{
			// Disable command echo
			sprintf( strOut, "%s ", "ed" );
			commResult1 = pCommLaser->WriteComm(strOut );
		
			// set to the home position
			sprintf( strOut, "%s%d ", "tp", 0 );	//move to home
			commResult1 = pCommLaser->WriteComm( strOut );
			sprintf( strOut, "%s%d ", "tp", 0 );	//move to desired degree
			commResult1 = pCommLaser->WriteComm( strOut );
		}
		else
		{
//			ATLTRACE("****** CCatch::FinalComponentInit() -- Writing to COMM FAILED!\n" );
			return FALSE;
		}
//	}
//	else
//	{
//		ATLTRACE("****** CCatch::FinalComponentInit() -- Writing to COMM FAILED!\n" );
//		return FALSE;
//	}

	//set new speed and accel for pan/tilt
	BOOL result = FALSE;
	sprintf( strOut, "%s%d ", "ta", (long)8000 );
	result = pCommLaser->WriteComm( strOut );
	sprintf( strOut, "%s%d ", "ts", (long)2500 );
	result = pCommLaser->WriteComm( strOut );
	if(!result)
		return FALSE;


//	ATLTRACE("****** CCatch::FinalComponentInit -- RETURNED OK!\n" );
	return TRUE;
}


/******************************************************************************

	Name:			HomeLaser()

	Purpose:		Move Laser to home position.


*******************************************************************************/

void laser::Homelaser()
{
	if ( pCommLaser != NULL )
	{
		// set to the home position
		char strOut[35];
		sprintf( strOut, "%s%d ", "tp", 0 );	//move to home
		pCommLaser->WriteComm( strOut );
		sprintf( strOut, "%s%d ", "pp", 0 );	//move to desired degree
		pCommLaser->WriteComm( strOut );
	}
	else
		cout<<"pCommLaser not set"<<endl;
}


/*------------------------------------------------------------------------------

	Name:			Resetlaser()

	Purpose:		Reset the laser pan-tilt head.

-------------------------------------------------------------------------------*/

BOOL laser::Resetlaser()
{
	char strOut[35];
	BOOL result1 = FALSE;
	
	// reset pan and tilt
	sprintf( strOut, "%s ", "r" );
	result1 = pCommLaser->WriteComm( strOut );
	
	if ( !result1 )
	{
		return FALSE;
	}
	return TRUE;
}


/*------------------------------------------------------------------------------

	Name:			ParseStringToIntegerlaser()

	Purpose:		Parse those darn strings returned by the controller into a 
					usable integer.

-------------------------------------------------------------------------------*/

int
laser::ParseStringToIntegerlaser
	(
	char *	pStr			// change: string to convert
	)
{
	char	newStr[35];
	int		result = -1;

	// chop the first two characters
	strcpy( newStr, &(pStr[2]) );
	
	// find the position of the newline character
	int newline_position = 0;
	char* strJunk = strchr( newStr, '\n' );

	if ( strJunk != NULL )
	{
		newline_position = strJunk - newStr;

		// chop off the end of the string
		newStr[newline_position] = '\0';

		// ...finally, convert the integer.
		result = atoi( newStr );
	}
	else
		result = -1;

	return result;
}


/*------------------------------------------------------------------------------

	Name:			GetTiltMinMaxlaser()

	Purpose:		Get the min and max tilt of ant pan/tilt laser unit.

-------------------------------------------------------------------------------*/

void laser::GetTiltMinMaxlaser(int &tilt_min, int &tilt_max)
{
	char strOut[35];
	char strIn[35];
	sprintf( strOut, "%s ", "tn" );	//tn=tilt min
	pCommLaser->WriteComm( strOut );
	pCommLaser->ReadComm( strIn, 10 );
	tilt_min = ParseStringToIntegerlaser( strIn );
//	cout<<"tilt min =  "<<tilt_min<<endl;

	sprintf( strOut, "%s ", "tx" );	//tx=tilt max
	pCommLaser->WriteComm( strOut );
	pCommLaser->ReadComm( strIn, 10 );
	tilt_max = ParseStringToIntegerlaser( strIn );
//	cout<<"tilt max =  "<<tilt_max<<endl;
}


/*------------------------------------------------------------------------------

	Name:			Movelaser(deg)

	Purpose:		Tilts laser degrees input (deg),
						if deg is positive, tilt up, if deg negative, tilt down

-------------------------------------------------------------------------------*/

void laser::Movelaser(double deg)
{
	char strOut[35];
	int degree_steps;
	int Min = 0;	//min tilt range
	int Max = 0;	//max tilt range
	int pan = 9999;	//current pan value, intialized at 9999
	int tilt = 9999;	//current tilt value, intialized at 9999
	int NewPos;	//if tilt move is done then this is the sum of CurrentPos[1] + degree_steps
	double stepTodeg=1/0.0129; //ratio to change degree to the number of steps
	degree_steps = floor(deg * stepTodeg);		
	GetTiltMinMaxlaser(Min, Max);
	GetLaserPosition(pan,tilt);
//	cout<<"steps wanting to move "<<degree_steps<<endl;
//	cout<<"CurrentPos tilt "<<tilt<<endl;
	NewPos = tilt + degree_steps;
//	cout<<"New position "<<NewPos<<endl;

	if ((NewPos >= Min)&&(NewPos <= Max))
	{
		sprintf( strOut, "%s%d ", "to", degree_steps );	//move to desired degree
		//hd.pCommRIGHT->WriteComm( strOut );
		pCommLaser->WriteComm( strOut );	
	}
	else
	{
		cout<<"Desired move is outside pan/tilt range."<<endl;
		if(NewPos >= 0)
			NewPos = Max;
		else
			NewPos = Min;
		sprintf( strOut, "%s%d ", "to", degree_steps );	//move to desired degree
		pCommLaser->WriteComm( strOut );	
	}
}



/*------------------------------------------------------------------------------

	Name:			GetLaserPosition()

	Purpose:		Get the position of the tilt of the laser.

-------------------------------------------------------------------------------*/

BOOL 
laser::GetLaserPosition(int &Pan, int &Tilt)
{
	char strOut[35];
	char strIn[35];
	BOOL result = FALSE;

	// get laser pan-tilt unit position
	strcpy( strIn, "" );
	strcpy( strOut, "" );

	if ( pCommLaser != NULL)
	{

		// get pan position
		sprintf( strOut, "%s ", "pp" );
		pCommLaser->WriteComm( strOut );

		strcpy( strOut, "" );

		result = pCommLaser->ReadComm( strIn, 10 );

		if ( result )
		{
		//	ATLTRACE("** DPSAMPLE RIGHT PAN = %s\n", strIn );
			// the returned command looks like: "* 0", so parse it properly.
			Pan = ParseStringToIntegerlaser( strIn );
			
			// get tilt position
			strcpy( strIn, "" );
			strcpy( strOut, "" );

			sprintf( strOut, "%s ", "tp" );
			pCommLaser->WriteComm( strOut );

			result = pCommLaser->ReadComm( strIn, 10 );

			if ( result )
			{
		//		ATLTRACE("** DPSAMPLE RIGHT TILT = %s\n", strIn );
				Tilt = ParseStringToIntegerlaser( strIn );
			}
			else
				return FALSE;
		}
		else
			return FALSE;
	}

	return TRUE;
}


/*------------------------------------------------------------------------------

	Name:			Getcameras(double righteye[3], double lefteye[3], double cambuff[6])

	Purpose:		Gets pan/tilt vlaues to Moves eyes to direction of detected motion,
						righteye and lefteye arrays should be in spherical coordinates
						in the following format:
						righteye[0]=range, righteye[1]=horizontial angle(theta),
						righteye[2]=vertical angle (alpha), with the plane of the floor 
						being 0 degree

						cambuff is updated to pan and tilt values to move camera using MoveHead()
						cambuff[0] = right pan
						cambuff[1] = right tilt
						cambuff[2] = right range
						cambuff[3] = left pan
						cambuff[4] = left tilt
						cambuff[5] = left range

-------------------------------------------------------------------------------*/

void laser::Getcameras(double righteye[3], double lefteye[3], double cambuff[6])
{
	//transform from laser reference frame to ISAC camera reference frame
	
	double pi = 3.14159265359;
	double rx = 0.0;	//intialize x,y,z for right and left camera
	double ry = 0.0;
	double rz = 0.0;
	double lx = 0.0;
	double ly = 0.0;
	double lz = 0.0;
	
	//transform range, horizontial angle(theta), from positive x-dir to y-dir,
	//and vertical angle (alpha), from positive z-dir to y-dir,
	//from laser to range, theta, and alpha of object to track with right camera 

	//calculate x,y,z from range,theta,alpha for theta=0,or 0<theta<0
	//to go from laser reference frame to axis of rotation of laser Pan/Tilt unit reference frame
	if(righteye[1] == 0)
	{
		rx = righteye[0] * cos(righteye[2] * (pi/180));//convert to radians and calculate x
		ry = righteye[0] * sin(righteye[2] * (pi/180));//convert to radians and calculate y
		rz = 105;	//millimeters
	}
	else
	{
		rx = (sqrt((105*105)+((righteye[0]*cos(righteye[2]*(pi/180)))*(righteye[0]*cos(righteye[2]*(pi/180)))))*sin(((atan2(righteye[0]*cos(righteye[2]*(pi/180)),105)*(180/pi))+righteye[1])*(pi/180)));
		ry = righteye[0]*sin(righteye[2]*(pi/180));
		rz = (sqrt((105*105)+((righteye[0]*cos(righteye[2]*(pi/180)))*(righteye[0]*cos(righteye[2]*(pi/180)))))*cos(((atan2(righteye[0]*cos(righteye[2]*(pi/180)),105)*(180/pi))+righteye[1])*(pi/180)))*-1.0;
	}
	//cout<<"rx "<<rx<<" ry "<<ry<<" rz "<<rz<<endl;

	//Translate from axis of rotation of laser Pan/Tilt unit reference frame (l) to
	//  axis of rotation of right camera reference frame (cr)
	// Tl w.r.t cr = [115 15 732]T
	rx = rx + 115;	//millimeters
	ry = ry + 15;
	rz = rz + 732;
	//cout<<"rx "<<rx<<" ry "<<ry<<" rz "<<rz<<endl;

	//Translate from x,y,z of axis of rotation of right camera reference frame (cr) to
	//  pan and tilt needed to point right camera at detected motion
	//  range from center of camera to detected motion = rrange
	//if(sqrt((rx*rx)+(ry*ry)-(65*65)) < 65)
	// ?
	//else

	cambuff[0] = atan2(ry,rx) * (180/pi);
	cambuff[1] = ((acos(rz/sqrt((rx*rx)+(ry*ry)+(rz*rz)))-acos(65/sqrt((rx*rx)+(ry*ry)+(rz*rz))))* (180/pi)) * -1.0;
	cambuff[2] = sqrt((rx*rx)+(ry*ry)+(rz*rz)-(65*65));


	//calculate x,y,z from range,theta,alpha for theta=0,or 0<theta<0
	//to go from laser reference frame to axis of rotation of laser Pan/Tilt unit reference frame
	if(lefteye[1] == 0)
	{
		lx = lefteye[0] * cos(lefteye[2] * (pi/180));//convert to radians and calculate x
		ly = lefteye[0] * sin(lefteye[2] * (pi/180));//convert to radians and calculate y
		lz = 105;	//millimeters
	}
	else
	{
		lx = (sqrt((105*105)+((lefteye[0]*cos(lefteye[2]*(pi/180)))*(lefteye[0]*cos(lefteye[2]*(pi/180)))))*sin(((atan2(lefteye[0]*cos(lefteye[2]*(pi/180)),105)*(180/pi))+lefteye[1])*(pi/180)));
		ly = lefteye[0]*sin(lefteye[2]*(pi/180));
		lz = (sqrt((105*105)+((lefteye[0]*cos(lefteye[2]*(pi/180)))*(lefteye[0]*cos(lefteye[2]*(pi/180)))))*cos(((atan2(lefteye[0]*cos(lefteye[2]*(pi/180)),105)*(180/pi))+lefteye[1])*(pi/180)))*-1.0;
	}
	//cout<<"lx "<<lx<<" ly "<<ly<<" lz "<<lz<<endl;

	//Translate from axis of rotation of laser Pan/Tilt unit reference frame (l) to
	//  axis of rotation of left camera reference frame (cl)
	// Tl w.r.t cl = [115 -263 732]T
	lx = lx + 115;	//millimeters
	ly = ly - 263;
	lz = lz + 732;
	//cout<<"lx "<<lx<<" ly "<<ly<<" lz "<<lz<<endl;
	
	//Translate from x,y,z of axis of rotation of left camera reference frame (lr) to
	//  pan and tilt needed to point left camera at detected motion
	//  range from center of camera to detected motion = rrange
	//if(sqrt((rx*rx)+(ry*ry)+(rz*rz)) < 65)
	// ?
	//else

	cambuff[3] = atan2(ly,lx) * (180/pi);
	cambuff[4] = ((acos(lz/sqrt((lx*lx)+(ly*ly)+(lz*lz)))-acos(65/sqrt((lx*lx)+(ly*ly)+(lz*lz))))* (180/pi))* -1.0;
	cambuff[5] = sqrt((lx*lx)+(ly*ly)+(lz*lz)-(65*65));

//	cout<<"panR "<<cambuff[0]<<" tiltR "<<cambuff[1]<<" rangR "<<cambuff[2]<<endl;
//	cout<<"panL "<<cambuff[3]<<" tiltL "<<cambuff[4]<<" rangeL "<<cambuff[5]<<endl;
}




/*------------------------------------------------------------------------------

	Name:			SphericalToCartesian(double rta[3])

	Purpose:		Transforms range, theta and alpha to x, y, and z
						rta[0]=distance, 
						rta[1]=horizontial angle(theta), from positive x-dir to y-dir
						rta[2]=vertical angle (alpha), from positive z-dir to y-dir

					rta is updated to rta[0] = x, rta[1] = y, rta[2] = z
-------------------------------------------------------------------------------*/

void laser::SphericalToCartesian(double rta[3])
{
	double pi = 3.14159265359;
	double r = rta[0];
	double theta = rta[1]*(pi/180);	//convert to radians
	double alpha = rta[2]*(pi/180);	//convert to radians
	rta[0] = r * sin(alpha)*cos(theta);
	rta[1] = r * sin(alpha)*sin(theta);
	rta[2] = r * cos(alpha);
	if(((rta[0] < 0.00001)&&(rta[0] > 0))||((rta[0] < 0)&&(rta[0] > -0.000001)))
		rta[0] = 0;
	if(((rta[1] < 0.00001)&&(rta[1] > 0))||((rta[1] < 0)&&(rta[1] > -0.000001)))
		rta[1] = 0;
	if(((rta[2] < 0.00001)&&(rta[2] > 0))||((rta[2] < 0)&&(rta[2] > -0.000001)))
		rta[2] = 0;
}



/*------------------------------------------------------------------------------

	Name:			CartesianToSpherical(double xyz[3])

	Purpose:		Transforms x, y, and z to range, theta, and alpha
						xyz is xyz[0] = x, xyz[1] = y, xyz[2] = z

					xyz[3] is updated to: 
						xyz[0]=distance, 
						xyz[1]=horizontial angle(theta), from positive x-dir to y-dir
						xyz[2]=vertical angle (alpha), from positive z-dir to y-dir

-------------------------------------------------------------------------------*/

void laser::CartesianToSpherical(double xyz[3])
{
	double pi = 3.14159265359;
	double x = xyz[0];
	double y = xyz[1];
	double z = xyz[2];
	if((x==0)&&(y==0)&&(z==0))
	{
		xyz[0] = 0;
		xyz[1] = 0;
		xyz[2] = 0;
	}
	else
	{

		xyz[0] = sqrt(x*x +y*y +z*z);	
		xyz[1] = atan2(y,x)*(180/pi);	//convert to degree
		double r = xyz[0];				//convert to degree
		xyz[2] = acos(z/r)*(180/pi);
		if(((xyz[0] < 0.00001)&&(xyz[0] > 0))||((xyz[0] < 0)&&(xyz[0] > -0.000001)))
			xyz[0] = 0;
		if(((xyz[1] < 0.00001)&&(xyz[1] > 0))||((xyz[1] < 0)&&(xyz[1] > -0.000001)))
			xyz[1] = 0;
		if(((xyz[2] < 0.00001)&&(xyz[2] > 0))||((xyz[2] < 0)&&(xyz[2] > -0.000001)))
			xyz[2] = 0;
	}
}