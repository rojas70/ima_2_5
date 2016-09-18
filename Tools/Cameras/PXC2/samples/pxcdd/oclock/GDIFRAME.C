
/********************************************************************
 |                        GDIFRAME.C                                |
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
 |    This is NOT a complete executable program.  It cannot be run  |
 | by itself, but must be linked as part of an application.  The    |
 | TSTAMP sample program is one example of a complete program which |
 | uses this code.                                                  |
 |                                                                  |
 |             Copyright (c) Imagenation Corperation 1998           |
 |                                                                  |
 ********************************************************************/

#include <windows.h>
#include "gdiframe.h"

static BITMAPINFO mybmp={
	{
		sizeof(BITMAPINFOHEADER),
		-1, //biWidth
		-1,	//biHeight
		1,
		0,	//biBitCount
		0,
		0, //biSizeImage
		0,
		0,
		0,
		0
	},
	{0,0,0,0}
};

typedef struct tagGDIFRAME {
	FRAME  f;
	HBITMAP hbits;
} GDIFRAME;

/********************************************************************
	myclose
		This routine gets called by FreeFrame in the frame or PXC200
	library.  It is responsible for freeing any resources allocated by
	AllocateGDI.  This function is not externally visible, except
	through pointers in the FRAME structures created by AllocateGDI,
	so it cannot be called directly by user code.
********************************************************************/
static void __PX_CALL myclose(FRAME __PX_FAR *f)
{
	if (f) {
		DeleteObject(((GDIFRAME __PX_FAR *)f)->hbits);
		free(f);
	}
}

/********************************************************************
	AllocateGDI
		Allocates a FRAME which can be used by the frame library and the
	PXC200 library, and which can also be written to by Windows GDI 
	functions.  Supports only RGB15, RGB16, RGB24, RGB32 pixel types.
********************************************************************/
FRAME __PX_FAR *AllocateGDI(short dx,short dy,short pixtype)
{
GDIFRAME __PX_FAR *f;

	if (dx<=0)
		return NULL;
	if (dy<=0)
		return NULL;

/* set up a BMP header to describe the requested image.  Some
	fields of the structure are never changed, so they are set in 
	the declaration of mybmp rather than here. */

	mybmp.bmiHeader.biWidth=dx;
	mybmp.bmiHeader.biHeight=-dy;
	switch (pixtype) {
		case PBITS_RGB15:
			mybmp.bmiHeader.biBitCount=16;
			mybmp.bmiHeader.biSizeImage=2L*(long)dx*(long)dy;
			break;
		case PBITS_RGB16:
			mybmp.bmiHeader.biBitCount=16;
			mybmp.bmiHeader.biSizeImage=2L*(long)dx*(long)dy;
			break;
		case PBITS_RGB24:
			mybmp.bmiHeader.biBitCount=24;
			mybmp.bmiHeader.biSizeImage=3L*(long)dx*(long)dy;
			break;
		case PBITS_RGB32:
			mybmp.bmiHeader.biBitCount=32;
			mybmp.bmiHeader.biSizeImage=4L*(long)dx*(long)dy;
			break;
		default:
			return NULL;
	}

/* allocate a GDIFRAME structure.  This structure is a FRAME with
	some additional stuff added to the end, so we can pass pointers
	to a GDIFRAME to functions that expect a FRAME. */

	f=malloc(sizeof(GDIFRAME));
	if (!f)
		return NULL;

/* CreateDIBSection allocates memory for the image buffer, based on
	the information in mybmp.  It returns a bitmap handle, which we use
	later to attach a Device Context to the bitmap, and also returns a
	pointer to the buffer memory, which gets written into the FRAME
	structure's user.pointer field. */

	f->hbits=CreateDIBSection(NULL,&mybmp,DIB_RGB_COLORS,
														&(f->f.user.pointer),NULL,0L);
	if (!f->hbits) {
		free(f);
		return NULL;
	}

/* now we fill in the rest of the FRAME structure. */

	f->f.dx=dx;
	f->f.dy=dy;
	f->f.type=pixtype;
	f->f.dma_type=PTYPE_DVIRTUAL;
	f->f.user_type=PTYPE_UFLAT;
	f->f.dma.pointer=f->f.user.pointer;
	f->f.close=myclose;
	return (FRAME __PX_FAR *)f;
}

/********************************************************************
	CreateFrameDC
		Creates a device context for a FRAME allocated by AllocateGDI.
	Use DeleteDC to dispose of the context when finished with it.
*********************************************************************/
HDC CreateFrameDC(FRAME __PX_FAR *f)
{
HDC hdc;
	hdc=CreateCompatibleDC(NULL);
	if (!hdc)
		return NULL;
	SelectObject(hdc,((GDIFRAME __PX_FAR *)f)->hbits);
	return hdc;
}

