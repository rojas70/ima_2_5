// Written by Peter Humke and Jason Kientz

// PXC_FG.h : Declaration of the CPXC_FG

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
#include "I:\Etc\PXC2\PCX_FG.h"

/***************************************/
/* Head for ImageRepresentation        */
/***************************************/
#include "O:\Components\Representations\IMA2_ImageRepLib\IMA2_ImageRepLib.h"

/*************
	General substructure for all of the openCV functions that we are planning to call
**************/

class IMA2_Open_CV
{
public:
	IMA2_Open_CV()
	{}

	~IMA2_Open_CV()
	{}

public:
	// include all of the functions declarations from the openCV library to be used
	
	void BackgroudSubtraction(*FrameGrabberObject, *FrameGrabberObject, *double);

private:
	long YResolution;
	long XResolution;
	long Width;
	long Height;
	long Top;
	long Left;

	// Linking variables
	IComponent* m_pIUnkImgOutput;
	IComponent* m_pIUnkVSpos;
}

#endif //_OPENCV_LIB_H_