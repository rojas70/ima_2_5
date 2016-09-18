

/********************************************************************
 |                        GDIFRAME.H                                |
 |                                                                  |
 |    This is a set of routines designed to work with the FRAME and |
 | PXC200 libraries under WIN32.  It creates image buffers which    |
 | can be used as targets for PXC200 Grab functions, can be         |
 | accessed by FRAME library image manipulation functions, and can  |
 | be drawn on by Windows GDI functions.  For instance, a program   |
 | could use one of these frames to grab an image with PXC2_95.dll, |
 | write a time stamp on it with the WIN32 DrawText function, and   |
 | save the modified image with the WriteBMP function from the      |
 | FRAME_32.dll.                                                    |
 |    The source code for the functions prototyped in this file is  |
 | in GDIFRAME.C.                                                   |
 |                                                                  |
 |             Copyright (c) Imagenation Corperation 1998           |
 |                                                                  |
 ********************************************************************/
#include "iframe.h"

FRAME __PX_FAR *AllocateGDI(short dx,short dy,short pixtype);
HDC CreateFrameDC(FRAME __PX_FAR *f);

