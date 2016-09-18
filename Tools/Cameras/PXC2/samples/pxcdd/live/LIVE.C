
/********************************************************************
 |                          LIVE.C                                  |
 |                                                                  |
 |    This is a WIN32 program that uses the PXC200 and PXCDD.DLL    |
 |    to display live video in a window.                            |
 |                                                                  |
 |    Compile from Microsoft Visual C 4.0 or later using            |
 |       cl live.c gdi32.lib user32.lib ilib_32.lib                 |
 |                                                                  |
 |             Copyright (c) Imagenation Corperation 1998           |
 |                                                                  |
 ********************************************************************/
#include <windows.h>
#include <stdio.h>
#include "iframe.h"
#include "pxc.h"
#include "pxcdd.h"
#include "resource.h"


#define CLASSNAME "PXC200 DirectDraw Sample"

PXC200 pxc200;
PXCDD pxcdd;
HWND hwnd;
long fgh;
FRAME __PX_FAR *frh;

void set_class(HINSTANCE hi);

char tbuf[256];

/********************************************************************
	WinMain
 ********************************************************************/
int PASCAL WinMain(HINSTANCE hinstance, HINSTANCE hPrev, LPSTR cmd, int show)
{
MSG msg;
BOOL small_size = FALSE;

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

/* allocate a frame from PXCDD.  Try a half sized image if a full one
	doesn't work, in case the system's low on video memory. */

	frh=pxcdd.CreateSurface(640,486);
	if (!frh)	
	{
		small_size = TRUE;
		frh=pxcdd.CreateSurface(320,243);
	}
	if (!frh) {
		MessageBox(0,"Couldn't allocate a video frame.",CLASSNAME,MB_ICONSTOP);
		pxc200.FreeFG(fgh);
		imagenation_CloseLibrary(&pxc200);
		imagenation_CloseLibrary(&pxcdd);
		return 0;
	}

/* Configure the PXC200 settings to match the size of the frame we configured. */
if (small_size) {
	pxc200.SetWidth (fgh, 320);
	pxc200.SetHeight (fgh, 243);
	pxc200.SetXResolution (fgh, 320);
	pxc200.SetYResolution (fgh, 243);
}
else /* full-size image */ {
	pxc200.SetWidth (fgh, 640);
	pxc200.SetHeight (fgh, 486);
	pxc200.SetXResolution (fgh, 640);
	pxc200.SetYResolution (fgh, 486);
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
		pxc200.FreeFrame(frh);
		pxc200.FreeFG(fgh);
		imagenation_CloseLibrary(&pxc200);
		imagenation_CloseLibrary(&pxcdd);
		return 0;
	}

	pxc200.GrabContinuous(fgh,frh,-1,0);

	/* Set up PXCDD display */
	if (!pxcdd.EnableFastDisplay(hwnd,frh,fgh,TRUE)) {
		MessageBox(0,"Couldn't start PXCDD display.",CLASSNAME,MB_ICONSTOP);
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
	}

/* display frame count */
	sprintf(tbuf,"%d frames",pxcdd.GetRenderCount());
	MessageBox(0,tbuf,CLASSNAME,MB_OK);
/* clean up everything and exit */
	pxc200.GrabContinuous(fgh,frh,0,0);
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
	w.hIcon=LoadIcon(hi,MAKEINTRESOURCE(PXC_ICON));
	w.hCursor=LoadCursor(hi,IDC_ARROW);
	w.hbrBackground=GetStockObject(WHITE_BRUSH);
	w.lpszMenuName=NULL;
	w.lpszClassName=CLASSNAME;
	RegisterClass(&w);
}

