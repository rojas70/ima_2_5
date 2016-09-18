
/********************************************************************
 |                          CROSS.C                                 |
 |                                                                  |
 |    This program displays live video with an overlay created from |
 | the CROSS.BMP image file.  When the user clicks the moust button |
 | a 20x20 pixel region from the image is averaged, and the hue of  |
 | the average color is displayed.                                  |
 |                                                                  |
 |    Compile from Microsoft Visual C 4.0 or later using            |
 |       cl live.c gdi32.lib user32.lib ilib_32.lib                 |
 |                                                                  |
 |             Copyright (c) Imagenation Corperation 1998           |
 |                                                                  |
 ********************************************************************/
#include <windows.h>
#include <math.h>
#include <stdio.h>
#include "iframe.h"
#include "pxc.h"
#include "pxcdd.h"
#include "resource.h"

#define CLASSNAME "PXC200 DirectDraw Sample"
#define OVRFILE "cross.bmp"

PXC200 pxc200;
PXCDD pxcdd;
int doprocess=0;

long fgh;
FRAME __PX_FAR *frh;
long ovr;

/* tbuf is scratch space for building strings */
char tbuf[256];

void set_class(HINSTANCE hi);
long MakeOverlay(short type,char __PX_FAR *fname);
void Process(long fgh,FRAME __PX_FAR *frh);

/********************************************************************
	WinMain
 ********************************************************************/
int PASCAL WinMain(HINSTANCE hinstance, HINSTANCE hPrev, LPSTR cmd, int show)
{
HWND hwnd;
MSG msg;

/* get access to the PXC200 and PXCDD libraries */

	if (!imagenation_OpenLibrary("pxc2_95.dll",&pxc200,sizeof(pxc200)))
	if (!imagenation_OpenLibrary("pxc2_nt.dll",&pxc200,sizeof(pxc200))) {
		MessageBox(0,"Couldn't find PXC200 DLL or Driver.",CLASSNAME,MB_ICONSTOP);
		return 0;
	}

	if (!imagenation_OpenLibrary("pxcdd.dll",&pxcdd,sizeof(pxcdd))) {
		MessageBox(0,"Couldn't find PXCDD DLL and DirectDraw.",
													CLASSNAME,MB_ICONSTOP);
		imagenation_CloseLibrary(&pxc200);
		return 0;
	}

/* allocate a frame grabber */
	fgh=pxc200.AllocateFG(-1);
	if (!fgh) {
		MessageBox(0,"Couldn't allocate a frame grabber.",CLASSNAME,MB_ICONSTOP);
		imagenation_CloseLibrary(&pxc200);
		imagenation_CloseLibrary(&pxcdd);
		return 0;
	}

/* allocate a frame from PXCDD. */

	frh=pxcdd.CreateSurface(640,480);
	if (!frh) {
		MessageBox(0,"Couldn't allocate a video frame.",CLASSNAME,MB_ICONSTOP);
		pxc200.FreeFG(fgh);
		imagenation_CloseLibrary(&pxc200);
		imagenation_CloseLibrary(&pxcdd);
		return 0;
	}

/* create an overlay frame */
	ovr=MakeOverlay(frh->type,OVRFILE);
	if (!ovr) {
		MessageBox(0,"Couldn't create an overlay.",CLASSNAME,MB_ICONSTOP);
		pxc200.FreeFrame(frh);
		pxc200.FreeFG(fgh);
		imagenation_CloseLibrary(&pxc200);
		imagenation_CloseLibrary(&pxcdd);
		return 0;
	}

/* Create a window */
	set_class(hinstance);
	hwnd=CreateWindowEx(
		0,
		CLASSNAME,
		CLASSNAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		frh->dx + 2*GetSystemMetrics(SM_CXFRAME),
		frh->dy + 2*GetSystemMetrics(SM_CYFRAME)+
							GetSystemMetrics(SM_CYCAPTION),
		NULL,NULL,
		hinstance,
		NULL);

	if (!hwnd) {
		MessageBox(0,"Couldn't create a window.",CLASSNAME,MB_ICONSTOP);
		pxcdd.UnloadOverlay(ovr);
		pxc200.FreeFrame(frh);
		pxc200.FreeFG(fgh);
		imagenation_CloseLibrary(&pxc200);
		imagenation_CloseLibrary(&pxcdd);
		return 0;
	}
	
	
	pxc200.GrabContinuous(fgh,frh,-1,0);

	/* Set up PXCDD display */
	pxcdd.EnableOverlay(frh,ovr,270,190,TRUE);
	if (!pxcdd.EnableFastDisplay(hwnd,frh,fgh,TRUE)) {
		MessageBox(0,"Couldn't start PXCDD display.",CLASSNAME,MB_ICONSTOP);
		pxcdd.EnableOverlay(frh,ovr,270,190,FALSE);
		pxcdd.UnloadOverlay(ovr);
		pxc200.FreeFrame(frh);
		pxc200.FreeFG(fgh);
		imagenation_CloseLibrary(&pxc200);
		imagenation_CloseLibrary(&pxcdd);
		return 0;
	}






	/* display the window and start the main message loop */
	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);	

	while (GetMessage(&msg,NULL,0,0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (doprocess) {
			Process(fgh,frh);
			doprocess=0;
		}
	}

/* clean up everything and exit */
	pxc200.GrabContinuous(fgh,frh,0,0);
	pxcdd.EnableOverlay(frh,ovr,270,190,FALSE);
	pxcdd.UnloadOverlay(ovr);
	pxc200.FreeFrame(frh);
	pxc200.FreeFG(fgh);
	imagenation_CloseLibrary(&pxc200);
	imagenation_CloseLibrary(&pxcdd);
	return 0;
}

/********************************************************************
	myproc
	this is the callback function that processes window messages.
	It doesn't do very much, because our window isn't doing anything 
	but displaying video, and that's handled automatically by the 
	PXCDD dll.
 ********************************************************************/
long _stdcall myproc(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam)
{

	switch (msg) {
		case WM_CREATE:
			break;
		case WM_MOVING:
			break;
		case WM_MOVE:
			break;
		case WM_CLOSE:
			pxcdd.EnableFastDisplay(hwnd,frh,fgh,FALSE);
			break;
		case WM_PAINT:
			break;
		case WM_LBUTTONDOWN:
			doprocess=1;
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hwnd,msg,wparam,lparam);
}

/********************************************************************
	set_class
	this function creates a window class.
 ********************************************************************/
void set_class(HINSTANCE hi)
{
static WNDCLASS w;
	w.style=0;
	w.lpfnWndProc=myproc;
	w.cbClsExtra=0;
	w.cbWndExtra=0;
	w.hInstance=hi;
	w.hIcon=LoadIcon(hi, MAKEINTRESOURCE(PXC_ICON));
	w.hCursor=LoadCursor(NULL,IDC_ARROW);
	w.hbrBackground=GetStockObject(WHITE_BRUSH);
	w.lpszMenuName=NULL;
	w.lpszClassName=CLASSNAME;
	RegisterClass(&w);
}

/********************************************************************
	MakeOverlay
 ********************************************************************/
 FRAMELIB flib;
long MakeOverlay(short type,char __PX_FAR *fname)
{
FRAME __PX_FAR *tf;
long ovr=0;

/* open the FRAME library so we can use the BMP file routines */
	if (!imagenation_OpenLibrary("frame_32.dll",&flib,sizeof(flib))) {
		MessageBox(0,"Couldn't find FRAME_32.DLL.",CLASSNAME,MB_ICONSTOP);
		return 0L;
	}
	tf=flib.AllocateMemoryFrame(100,100,type);
	if (!tf) {
		imagenation_CloseLibrary(&flib);
		MessageBox(0,"Not enough memory for overlay frame.",CLASSNAME,MB_ICONSTOP);
		return 0;
	}
	if (SUCCESS!=flib.ReadBMP(tf,fname)) {
		MessageBox(0,"Couldn't load BMP image.",CLASSNAME,MB_ICONSTOP);
		flib.FreeFrame(tf);
		imagenation_CloseLibrary(&flib);
		return 0;
	}

	ovr=pxcdd.LoadOverlay(tf,0L);
	if (!ovr) {
		flib.FreeFrame(tf);
		imagenation_CloseLibrary(&flib);
		return 0;
	}

	flib.FreeFrame(tf);
	imagenation_CloseLibrary(&flib);
	return ovr;
}


#define SQRT_3_DIV_2 0.866025
#define RAD_TO_DEG (360.0/6.28319)

void Process(long fgh,FRAME __PX_FAR *frh)
{
long x,y;
long red,blue,green;
PIX_RGB32 __PX_HW *rgb32;
PIX_RGB24 __PX_HW *rgb24;
PIX_RGB16 __PX_HW *rgb16;
PIX_RGB15 __PX_HW *rgb15;
double huex,huey;

	red=0;
	green=0;
	blue=0;
	pxc200.GrabContinuous(fgh,frh,0,0);

/* this code computes the sum of the red, blue, and green components
	of the rectangle (310,230)-(330,250) from the captured image.
	The switch statement handles the differences between the possible 
	pixel types.  Which pixel type is actually used depends of the current
	video display mode. */

	switch (frh->type) {
		case PBITS_RGB32:
			rgb32=frh->user.pointer;
			for (y=230;y<250;y++)
			for (x=310;x<330;x++) {
				red+=rgb32[x+640*y].red;
				green+=rgb32[x+640*y].green;
				blue+=rgb32[x+640*y].blue;
			}
			break;
		case PBITS_RGB24:
			rgb24=frh->user.pointer;
			for (y=230;y<250;y++)
			for (x=310;x<330;x++) {
				red+=rgb24[x+640*y].red;
				green+=rgb24[x+640*y].green;
				blue+=rgb24[x+640*y].blue;
			}
			break;
		case PBITS_RGB16:
			rgb16=frh->user.pointer;
			for (y=230;y<250;y++)
			for (x=310;x<330;x++) {
				red+=rgb16[x+640*y].red;
				green+=rgb16[x+640*y].green;
				blue+=rgb16[x+640*y].blue;
			}
			break;
		case PBITS_RGB15:
			rgb15=frh->user.pointer;
			for (y=230;y<250;y++)
			for (x=310;x<330;x++) {
				red+=rgb15[x+640*y].red;
				green+=rgb15[x+640*y].green;
				blue+=rgb15[x+640*y].blue;
			}
			break;
	}

	pxc200.GrabContinuous(fgh,frh,-1,0);

/* compute hue */
	huex=green*SQRT_3_DIV_2 - blue*SQRT_3_DIV_2;
	huey=red-blue*0.5-green*0.5;
	if ((huex*huex+huey*huey)<1) {
		sprintf(tbuf,"Hue is Gray.");
	}
	else {
		sprintf(tbuf,"Hue=%d degrees.",(int)( RAD_TO_DEG*atan2(huey,huex) ) );
	}
	MessageBox(0,tbuf,"Cross",MB_OK);
}

