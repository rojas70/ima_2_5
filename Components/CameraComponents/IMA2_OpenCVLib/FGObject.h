// Written by Peter Humke and Jason Kientz

#ifndef _OPENCV_LIB_H_
#define _OPENCV_LIB_H_

/***************************************/
/* IMA Component Information           */
/***************************************/
#include "O:\Base Classes\ComponentImpl.h"
#include "O:\Components\msvbvm60.tlh" // property bag dll

/****************************************/
/* Header for PXC200 PCI frame grabber  */
/****************************************/
#include "I:\Etc\PXC2\iframe.h"
#include "I:\Etc\PXC2\pxc200.h"
#include "I:\Src\Mechanisms\FrameGrabberProj\FrameGrabberProj.h"
#include "I:\Src\Mechanisms\FrameGrabberProj\FrameGrabberProj_i.c"

/***************************************/
/* Head for ImageRepresentation        */
/***************************************/
#include "O:\Components\Representations\IMA2_ImageRepLib\IMA2_ImageRepLib.h"

/*************
	A frame grabber object to collect the information from the frame grabber
	and represent it as an image which can be manipulated.
**************/

class FrameGrabberObject
{
public:
	FrameGrabberObject(IUnknown* camPointer)
	{
		camera = camPointer;
		
		// assign the locaiton of the memory buffer for the camera to the image_in location
		camera->queryInterface(IID_IPXC_FG, &image_in);
	}

	~FrameGrabberObject()
	{
		image_in->Release();
	}

	// this routine needs to be fast as it may be called frequently when trying to gather real time data
	void Get_Image(IplImage*);

private:
	IUnknown *camera;  // or also try IComponent;
	IPXC_FG* image_in;
}

#endif //_OPENCV_LIB_H_