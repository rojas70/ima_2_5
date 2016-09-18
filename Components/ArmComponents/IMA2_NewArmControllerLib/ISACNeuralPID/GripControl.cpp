/* Functions for the gripper control class
Author: Jack Noble
Date:	3/29/07

Modified By Erdem
Date:   09/26/2007
Modifications : Disabled GCCalibrate() when constructor created, disabled GCHalfOpen() and created SimplyOpen and
GrabSomething functions. The delay in the GrabSomething can be adjusted by changing value at the code line;
while ((clock()-t<"value")){}
Comments : As I modified the GCCalibrate() and GCHalfOpen(), the other function may malfunction.
*/

#include "Headers/GripControl.h"


GripControl::GripControl(){
	char result;
	int ii;
	//BOOL swt;
	
	com1.WriteChar(0x41);
	com1.ReadComm(&result,1);
	int counter = 0;
	int tryagain = 0;
	while ((result!=0x06)&&(counter < 1000)){
		com1.WriteChar(0x41);
		com1.ReadComm(&result,1);
		counter++;
	}
	if (counter>=1000){
		perror("Serial communication with microcontroller is not possible.\n\
			Check that the cable has been plugged in to the correct port (Default='COM1').\n\
			Make sure the microcontroller is on.  If so, hit reset on the microcontroller\n\
			and try again.  To use a different port, e.g. 'COM2', initialize your GripControl\n\
			object as 'GripControl gripper = GripControl(''COM2'');");
		exit(0);
	}

	//Tables derived Heuristically
	com1.WriteChar(STOP);
//	GCGetLastCloseAmps(result);

//	GCGetLeftSwitch(swt);
//	printf("%d ",20*swt);
//	GCGetRightSwitch(swt);
//	printf("%d ",10*swt);
	
	//GCCalibrate();  /// This part is changed by Erdem
	tablesize = 10;
	float disttab[] =  {8.5 , 7.6 , 6.3 , 5.0 , 3.6 , 3.1 , 2.1 , 1.4 , 0.6 , 0};
//	float	volttab[] = {111,110,109,108,105,101,94,84,71};
	float volttab[] = {0,0.0057,0.0114,0.0171,0.0286,0.0571,.1086,0.2,0.4114,1};
	for (ii=0; ii<tablesize; ii++)
		volttab[ii] = OpenedAngle - (OpenedAngle-ClosedAngle)*volttab[ii];
	
	disttable = new float[tablesize];
	voltstable = new float[tablesize];
	for (ii=0; ii<tablesize; ii++){
		disttable[ii] = disttab[ii];
		voltstable[ii] = volttab[ii];
	}

	return;
}

GripControl::GripControl(char* port){
	com1 = CCommPort(port);
	GripControl();

}

GripControl::~GripControl(){
	delete [] disttable;
	delete [] voltstable;
	//GCHalfOpen();   /// This part is changed by Erdem

	return;
}

void GripControl::GCCalibrate(){
	BOOL left;
	BOOL right;
	char result;
	GCGetLeftSwitch(left);
	GCGetRightSwitch(right);
	clock_t t;
	if ((!left)&&(!right)){
        com1.WriteChar(OPEN);
		t = clock();
		while ((clock()-t<300)){}
		com1.WriteChar(STOP);
	}
	GCCloseUntilObject();
	GCGetWidth(result);
	ClosedAngle = (unsigned char)result;

	com1.WriteChar(OPEN);
	t = clock();
	while ((clock()-t) < OPENTIME){};
	com1.WriteChar(STOP);
	GCGetWidth(result);
	OpenedAngle = (unsigned char) result;
	HalfAngle = OpenedAngle-3;
	GCHalfOpen();

	return;
}

void GripControl::GCGetWidth(char & result){

	com1.WriteChar(GETANGLE);
	com1.ReadComm(&result,1);
	return;
}

void GripControl::GCFullyClose(){
	char result;
	
	com1.WriteChar(GETANGLE);
	com1.ReadComm(&result,1);
	if ((unsigned char)result > ClosedAngle)
		com1.WriteChar(CLOSE);
	while ((unsigned char)result > ClosedAngle){
		com1.WriteChar(GETANGLE);
		com1.ReadComm(&result,1);
	}
	com1.WriteChar(STOP);
	return;

}

void GripControl::GCHalfOpen(){

	char result;
	
	com1.WriteChar(GETANGLE);
	com1.ReadComm(&result,1);
	if ((unsigned char)result > HalfAngle){
		com1.WriteChar(CLOSE);
		while ((unsigned char)result > HalfAngle){
			com1.WriteChar(GETANGLE);
			com1.ReadComm(&result,1);
		}
	}
	else if ((unsigned char)result < HalfAngle){
		com1.WriteChar(OPEN);
		while ((unsigned char)result < HalfAngle){
			com1.WriteChar(GETANGLE);
			com1.ReadComm(&result,1);
		}
	}
	com1.WriteChar(STOP);
	return;
}

void GripControl::GCFullyOpen(){
	char result;
	int total;

	//com1.WriteChar(GETANGLE);
	//debug
	for (int ii=0; ii<10; ii++){
		com1.WriteChar(GETANGLE);
		com1.ReadComm(&result,1);
	}
	if ((unsigned char)result < OpenedAngle)
		com1.WriteChar(OPEN);
	while ((unsigned char)result < OpenedAngle){
		total = 0;
		for (int ii=0; ii<NUMSAMPLES; ii++){
			com1.WriteChar(GETANGLE);
			com1.ReadComm(&result,1);
			total += (unsigned char)result;
		}
		result = total/NUMSAMPLES;
	}
	com1.WriteChar(STOP);
	return;
}

/// This part is changed by Erdem
void GripControl::SimpleOpen(){

	clock_t t;

	//com1.WriteChar(GETANGLE);
	//debug
	com1.WriteChar(OPEN);
	t = clock();
	while ((clock()-t<3500)){}
	com1.WriteChar(STOP);
	return;
}

/// This part is changed by Erdem
void GripControl::GrabSomething(){

	clock_t t;

	//com1.WriteChar(GETANGLE);
	//debug
	com1.WriteChar(OPEN);
	t = clock();
	while ((clock()-t<3000)){}
	GCCloseUntilObject();
	com1.WriteChar(STOP);
	return;
}

void GripControl::GCGetLastCloseAmps(char & result){
	com1.WriteChar(GETMAXCURRENT);
	com1.ReadComm(&result,1);

	return;
}

void GripControl::GCGetLeftSwitch(BOOL & switchstat){
	char result;
	switchstat = false;
	com1.WriteChar(GETLEFTSWITCH);
	com1.ReadComm(&result,1);
	if ((unsigned char)result > 128)
		switchstat = true;
	
	return;
}

void GripControl::GCGetRightSwitch(BOOL & switchstat){
	char result;
	switchstat = false;
	com1.WriteChar(GETRIGHTSWITCH);
	com1.ReadComm(&result,1);
	if ((unsigned char)result > 128)
		switchstat = true;
	
	return;
}

void GripControl::GCCloseUntilObject(){
	char result;
	clock_t t1;
	BOOL left = true;
	BOOL right = true;

//	GCFullyOpen();

	GCGetLeftSwitch(left);
	GCGetRightSwitch(right);
	GCGetWidth(result);
	if ((left||right)&&((unsigned char)result>ClosedAngle)){
			com1.WriteChar(CLOSE);
		while (left||right){
			GCGetLeftSwitch(left);
			GCGetRightSwitch(right);
		}
		t1 = clock();
		while (clock()-t1<250){}
	}

	com1.WriteChar(STOP);

}

void GripControl::GCGoToWidth(float dist){
	dist = dist + CalCorrect;

	char voltsval;
	char result;
	int ave;
	int indx = 0;
	if (dist > disttable[0]){
		GCFullyOpen();
		return;}
	if (dist < disttable[tablesize]){
		GCFullyClose();
		return;
	}
	while ((indx<tablesize)&&(disttable[indx]>dist))
		indx++;

	voltsval = (char)(((int)(voltstable[indx]*(-dist+disttable[indx-1])/
		(disttable[indx-1]-disttable[indx])+
		voltstable[indx-1]*(dist-disttable[indx])/
		(disttable[indx-1]-disttable[indx])))/1);

	GCGetWidth(result);
	if ((unsigned char)result > (unsigned char)voltsval){
		ave = 256;
		com1.WriteChar(CLOSE);
		while (ave > (unsigned char)voltsval){
			ave = 0;
			for (int ii=0; ii<NUMSAMPLES; ii++){
				GCGetWidth(result);
				ave+=(unsigned char)result;
			}
			ave/=NUMSAMPLES;
		}
	}
	else if ((unsigned char)result < (unsigned char)voltsval){
		GCGetWidth(result);
		ave = 0;
		com1.WriteChar(OPEN);
		while (ave < (unsigned char)voltsval){
			ave = 0;
			for (int ii=0; ii<NUMSAMPLES; ii++){
				GCGetWidth(result);
				ave+=(unsigned char)result;
			}
			ave/=(NUMSAMPLES);
		}
	}
	com1.WriteChar(STOP);
	return;
}

void GripControl::GCGetCurrentDist(float & dist){

	//char voltsval;
	char result;
	int ave;
	int indx = 0;

	ave = 0;
	for (int ii=0; ii<NUMSAMPLES; ii++){
        GCGetWidth(result);
		ave+=(unsigned char)result;
	}
	ave/=NUMSAMPLES;

	while ((indx<tablesize)&&(voltstable[indx]>(float)ave))
		indx++;

	dist = disttable[indx]*(-ave+voltstable[indx-1])/
		(voltstable[indx-1]-voltstable[indx])+
		disttable[indx-1]*(ave-voltstable[indx])/
		(voltstable[indx-1]-voltstable[indx])-CalCorrect;

	return;
}