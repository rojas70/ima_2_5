
// FIXME change header
/********************************************************************
 |                          OCLOCK.C                                  |
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
#include <time.h>
#include <math.h>
#include <windows.h>
#include "iframe.h"
#include "pxc.h"
#include "pxcdd.h"
#include "gdiframe.h"
#include "resource.h"

#define CLASSNAME "PXC200 DirectDraw Sample"
#define ID_TIMER 1

PXC200 pxc200;
PXCDD pxcdd;
long fgh;

void set_class(HINSTANCE hi);
void UpdateClock(void);
void DrawClock(HDC hdc);

FRAME __PX_FAR *frh;
FRAME __PX_FAR *ovr;
long ovrhandle=0L;

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

/* allocate an overlay frame from GDIFRAME */
	ovr=AllocateGDI(52,49,frh->type);
	if (!ovr) {
		MessageBox(0,"Couldn't allocate a GDI frame.",CLASSNAME,MB_ICONSTOP);
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
		pxc200.FreeFrame(frh);
		pxc200.FreeFrame(ovr);
		pxc200.FreeFG(fgh);
		imagenation_CloseLibrary(&pxc200);
		imagenation_CloseLibrary(&pxcdd);
		return 0;
	}

	if (!SetTimer(hwnd,ID_TIMER,1000,NULL)) {
		MessageBox(0,"Couldn't allocate a system timer.",CLASSNAME,MB_ICONSTOP);
		pxc200.FreeFrame(frh);
		pxc200.FreeFrame(ovr);
		pxc200.FreeFG(fgh);
		imagenation_CloseLibrary(&pxc200);
		imagenation_CloseLibrary(&pxcdd);
		return 0;
	}

	pxc200.GrabContinuous(fgh,frh,-1,0);

/* Set up PXCDD display */
	if (!pxcdd.EnableFastDisplay(hwnd,frh,fgh,TRUE)) {
		MessageBox(0,"Couldn't start PXCDD display.",CLASSNAME,MB_ICONSTOP);
		KillTimer(hwnd,ID_TIMER);
		pxc200.FreeFrame(frh);
		pxc200.FreeFrame(ovr);
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

	/* clean up everything and exit */
	KillTimer(hwnd,ID_TIMER);
	if (ovrhandle) {
		pxcdd.EnableOverlay(frh,ovrhandle,0,0,FALSE);
		pxcdd.UnloadOverlay(ovrhandle);
	}
	pxc200.GrabContinuous(fgh,frh,0,0);
	pxc200.FreeFrame(frh);
	pxc200.FreeFrame(ovr);
	pxc200.FreeFG(fgh);
	imagenation_CloseLibrary(&pxc200);
	imagenation_CloseLibrary(&pxcdd);
	return 0;
}

/********************************************************************
	myproc
	this is the callback function that processes window messages.
	Only the DESTROY and TIMER messages are handled.
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
		case WM_TIMER:
			UpdateClock();
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
	w.hCursor=LoadCursor(NULL,IDC_ARROW);
	w.hbrBackground=GetStockObject(WHITE_BRUSH);
	w.lpszMenuName=NULL;
	w.lpszClassName=CLASSNAME;
	RegisterClass(&w);
}

/********************************************************************
	UpdateClock
	This function updates the clock image by unloading, altering and
	reloading the overlay.
 ********************************************************************/
void UpdateClock(void)
{
HDC hdc;

/* redraw the clock image */
	hdc=CreateFrameDC(ovr);
	DrawClock(hdc);
	DeleteDC(hdc);
	if (ovrhandle) {
		pxcdd.EnableOverlay(frh,ovrhandle,0,0,FALSE);
		pxcdd.UnloadOverlay(ovrhandle);
	}
	ovrhandle=pxcdd.LoadOverlay(ovr,0L);
	pxcdd.EnableOverlay(frh,ovrhandle,0,0,TRUE);
}

/********************************************************************
	DrawClock
	This function uses a device context attached to the ovr frame to
	draw a picture of a clock.
 ********************************************************************/
#define PI 3.1415926
RECT rect={0,0,52,49};
void DrawClock(HDC hdc)
{
HPEN pen,oldpen;
HBRUSH brush;
double seca,mina,houra;
time_t ltime;
struct tm *datetime;

	time(&ltime);
	datetime=localtime(&ltime);

	seca=datetime->tm_sec * (6.0*2.0*PI/360.0);
	mina=datetime->tm_min * (6.0*2.0*PI/360.0);
	houra=datetime->tm_hour * (30.0*2.0*PI/360.0) + mina*(1.0/12.0);

	brush=GetStockObject(BLACK_BRUSH);
	FillRect(hdc,&rect,brush);

	pen=CreatePen(PS_SOLID,0,RGB(0,0,0));
	oldpen=SelectObject(hdc,pen);
		Ellipse(hdc,0,0,48,48);
	SelectObject(hdc,oldpen);
	DeleteObject(pen);

	pen=CreatePen(PS_SOLID,0,RGB(255,0,0));
	oldpen=SelectObject(hdc,pen);
		MoveToEx(hdc,24,24,NULL);
		LineTo(hdc,24+(int)(22*sin(seca)),24-(int)(22*cos(seca)));
	SelectObject(hdc,oldpen);
	DeleteObject(pen);

	pen=CreatePen(PS_SOLID,0,RGB(0,0,0));
	oldpen=SelectObject(hdc,pen);
		MoveToEx(hdc,24,24,NULL);
		LineTo(hdc,24+(int)(22*sin(mina)),24-(int)(22*cos(mina)));
		MoveToEx(hdc,24,24,NULL);
		LineTo(hdc,24+(int)(15*sin(houra)),24-(int)(15*cos(houra)));
	SelectObject(hdc,oldpen);
	DeleteObject(pen);

}
