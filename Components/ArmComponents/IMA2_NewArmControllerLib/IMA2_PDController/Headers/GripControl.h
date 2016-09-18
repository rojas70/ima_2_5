/*GripControl.h
Author: Jack Noble
Date:	03/30/07

This is the header file for the GripControl class for operating 
the gripper in the ISAC lab.  
*/

#include <windows.h>
#include "Headers/commport.h"
#include <stdio.h>
#include <time.h>


/////Microcontroller commands
////Don't change unless you change the microcontroller program as well
#define GETANGLE		0x31
#define	GETLEFTSWITCH	0x32
#define	GETRIGHTSWITCH	0x33
#define	GETMAXCURRENT	0x34
#define	CLOSE			0x35
#define	OPEN			0x36
#define	STOP			0x37


/////Experimentally derived values
#define	OPENTIME	2900 //ms
#define CalCorrect	1

//Number of samples to take when averaging (the higher the number,
//the more accurate the sample, but the longer the response time is)
#define NUMSAMPLES	4


class GripControl
{
public:
	GripControl();
	//Use this constructor if not plugging in to COM1
	GripControl(char* port);
	~GripControl();
	
	// GCCloseUnitObject() is better to use to close the gripper than FullyClose
	void GCFullyClose();
	void GCFullyOpen();
	void GCHalfOpen();
	void GCGetLeftSwitch(BOOL & switchstat);
	void GCGetRightSwitch(BOOL & switchstat);
	void GCCloseUntilObject();
	void GCGoToWidth(float dist);
	void GCGetCurrentDist(float & dist);
	void GCCalibrate();
	void SimpleOpen();
	void GrabSomething();
	

private:
	CCommPort com1;
	char buf[128];
	float* disttable;
	float* voltstable;
	int tablesize;
	void GCGetWidth(char & result);
	void GCGetLastCloseAmps(char & result);
	//this is private because it gets hit or miss values.  Not really useful.
	short ClosedAngle;
	short HalfAngle;
	short OpenedAngle;

};
