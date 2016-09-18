#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <ipl.h>	//necessary for fast processor specific frame conversion to an iplImage

#include "cv.h"
#include "cvaux.h"
#include "highgui.h"

#include "pxc_display.h"
#include "resource.h"

FRAMELIB		FrameLib;
PXC				pxc;

//////////////////////////////////////////////////////////////////////////////////////
//	global definitions

// this program can use either 24 bit color or 8 bit gray frames
// the value of PIXEL_TYPE can be change to PBITS_RGB24 or PBITS_Y8
static short PIXEL_TYPE = PBITS_RGB24;

// set the DLL names
#define PXC_9X  "pxc_95.dll"
#define FRAME_NAME  "frame_32.dll"
#define PXC_NT    "pxc_nt.dll"

// frame grabber handle
static long		hFG;
static FRAME		*gpFrame = NULL;
static FRAME		*gpFrame2 = NULL;

//The variables are used by AppIdle() where the grabs are queued.
static BOOL bAcquire = FALSE;
static BOOL bSave = FALSE;
static BOOL bRestartClock;

// iGrabType controls the queuing of the grab. 
int iGrabType;
static int intBMPcount=0;

// image size: width (iImageX), height (iImageY)
static int iImageX, iImageY;
// Window size: width (iWindowX), height (iWindowY)
static int iWindowX, iWindowY;

// window procs for the dialog and video display windows
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK VideoProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

// functions to register and create video display window
void RegisterVideoWindow(HINSTANCE hInstance);
HWND CreateVideoWindow(HINSTANCE hInstance);


// these functions contain the knowledge of how to open and close the video
// display window. if you have variables that are coordinated with this
// window they can be set and cleared within these functions.
int OpenVideoWindow(void);
int CloseVideoWindow(void);
void SizeVideoWindow(void);
BOOL ResetBuffers(short PixelType);

//  displays the hardware/firmware revision
int DisplayRevision(long fgHandle);

// PXC control functions
long InitializePXC(void);
BOOL ResetPXC(void);

// application control functions
BOOL AppIdle(void);
void AppExit(void);

// these variables are static for one reason: to avoid name collisions with other
// modules.
static HINSTANCE hAppInst;
static HWND hDisplay = NULL;
static HWND hMainDlg = NULL;
static int iFrameCount;

// these variables are the class names for the two windows
static char szDLGClass[] = "PXC_IPL";
static char szVidClass[] = "VidWin";

// these two RECT structures contain the positions of the two windows
static RECT rectMain, rectVideo;

/*---------------------------< IPL data >------------------------------*/

// these variable are needed to keep IPL libary functions and operations
static char szSeqFile[250] = "PXC_IPL";
static int  iStart,iCount= 0;
static BOOL bThreshold =FALSE;

// max scroll number 
#define MaxCount 255
static int MaxRange = MaxCount;
static int MinRange = 3;
static int iScroll[9]={128,3,3,3,3,3,0,0,3};

static IplImage* img=NULL;
static IplImage* img2 =NULL;

// PXC image processing functions
BOOL create_ipl_Image(int MaxX,int MaxY,int iPixelType );
void Process_Image(HDC hdc);

/******************************************************************************
 * Name:         WinMain
 *-----------------------------------------------------------------------------
 * Description:  Main dialog window program and message loop
 ******************************************************************************/
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
										PSTR szCmdLine, int iCmdShow)
{
	MSG		msg;
	short	sGrabbers;
    
	// save this instance of the program
	hAppInst = hInstance;

	// register the video display window class
	// it will be used to create a video display window later
	RegisterVideoWindow(hAppInst);

	// create the main window as a modeless dialog box
	hMainDlg = CreateDialog (hInstance, MAKEINTRESOURCE(IDD_GRAB),0, WndProc);

	// try to open the PXC library and the PXC frame library
	// all of this code will have to change
	sGrabbers = imagenation_OpenLibrary(PXC_9X, &pxc, sizeof(pxc));
	if (sGrabbers == 0)
	{
		sGrabbers = imagenation_OpenLibrary(PXC_NT, &pxc, sizeof(pxc));
		if (sGrabbers == 0)
		{
			MessageBox(0, "Could not load pxc_95.dll or pxc_nt.dll", szDLGClass, MB_OK);
			return FALSE;
		}
	}

	// now try to open the frame library
	if (!imagenation_OpenLibrary(FRAME_NAME, &FrameLib,sizeof(FrameLib)))
	{
		MessageBox(0, "Could not load frame_32.dll", szDLGClass, MB_OK);
		imagenation_CloseLibrary(&pxc);
		return FALSE;
	}

	// try to initialize any PXC in the computer
	if(!InitializePXC())
	{
		MessageBox(NULL, "Unable to find a PXC board", "Board initialization failure", 0);
		AppExit();
		return FALSE;
	}

	// now reset the PXC to known values 
	if(!ResetPXC())
	{
		MessageBox(NULL, "Unknown video type or no video signal", "ResetPXC Failure", 0);
		AppExit();
		return FALSE;
	}


	// create a pxc compatible frame for ipl image data 
	if(! create_ipl_Image(iImageX,iImageY,PIXEL_TYPE))
	{
		MessageBox(0, "Unable to create frame for ipl", "Frame Failure", 0);
		AppExit();
		return FALSE;
	}

	// set a gray scale palette to be used for display
	GrayscalePalette(NULL, PXC_PALETTE_CREATE);


	/*-------------------------------------------------------------------------
	watch for windows messages like mouse events, and otherwise call AppIdle
	to maintain a display of video.
	-------------------------------------------------------------------------*/
	for(;;) 
	{
		if(PeekMessage(&msg, NULL, 0, 0,PM_REMOVE)) 
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else 
		{
			if(AppIdle())
				WaitMessage();
		}
	}
    
    AppExit();
	return TRUE;
}

/******************************************************************************
 * Name:         AppIdle
 *-----------------------------------------------------------------------------
 * Description:  This idle function is called whenever the message queue
 *               is empty. We use this function to keep the grabs and the
 *               displays going.
 ******************************************************************************/
BOOL AppIdle(void)
{
	HDC hdc;
	
	//filename by date&time
	   time_t ltime;
	   char tmpbuf[128];
	   struct tm now;

	   time(&ltime);
	   now = *localtime(&ltime);
	   strftime(tmpbuf,128,"%Y-%m-%d_%H-%M-%S.bmp", &now );
			
	if (IsIconic(hDisplay))
		return TRUE;

	if (GetKeyState(VK_LBUTTON) >= 0)
	{
		// if we are in the acquire mode, queue a new grab and display
		// whatever was in the previous grab.
		if(bAcquire) 
		{
			pxc.Grab(hFG, gpFrame, (short)iGrabType);
		}
		if(bSave)	// show only one frame and save it to BMP
		{
			pxc.Grab(hFG, gpFrame, (short)iGrabType);
			
			//MessageBox(0,tmpbuf,"Time",0);
			
			switch(FrameLib.WriteBMP(gpFrame,tmpbuf,0))	//no overwrite
			{
			case FILE_EXISTS:
				MessageBox(0, "The file already exists, but the function call did not specify that the file should be overwritten.", "WriteBMP() failure", 0);
				break;
			case INVALID_FRAME:
				MessageBox(0, "The frame pointer is invalid or the frame data can’t be accessed.", "WriteBMP() failure", 0);
				break;
			case WRONG_BITS:
				MessageBox(0, "The file format does not accept data of the type contained in the frame.", "WriteBMP() failure", 0);
				break;
			case BAD_WRITE:
				MessageBox(0, "An error occurred while a file was being written.", "WriteBMP() failure", 0);
				break;
			}
			
			bSave=FALSE;
		}

		if(hDisplay)
		{
		hdc = GetDC(hDisplay);
		Process_Image(hdc);
		ReleaseDC(hDisplay, hdc);
		}
		return FALSE;
	}
	else 
	{
		return TRUE;      // background app; nothing to do.
	}
}

/******************************************************************************
 * Name:         WndProc
 *-----------------------------------------------------------------------------
 * Description:  Window procedure for main dialog box
 ******************************************************************************/
LRESULT CALLBACK WndProc (HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//HDC hDC;

	int  iseq=0;

	switch (iMsg)
	{
	case WM_INITDIALOG:
		
		// If you want to do something to the window before it displays,
		// do it in this message trap.
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD (wParam))
		{
		case IDC_START:
			OpenVideoWindow();
			bAcquire = TRUE;
			bRestartClock = TRUE;
			break;

		case IDC_STOP:
			bAcquire = FALSE;
			break;

		case IDC_SAVE:
			OpenVideoWindow();
			bAcquire = FALSE;
			bSave = TRUE;
			break;

		case ID_COMPOSITE:
			// Set the camera input to input 0
			pxc.SetCamera(hFG,0,0);

			// tell frame grabber that the video input is Monochrome or Composite
			pxc.SetChromaControl(hFG,NOTCH_FILTER|BW_DETECT);

			// resize buffers and set the value of pixel type to PBITS_RGB24
			ResetBuffers(PBITS_RGB24);
			break;

		case ID_MONOCHROME:
			// Set the camera input to input 0
			pxc.SetCamera(hFG,0,0);

			// tell frame grabber that the video input is Monochrome or Composite
			pxc.SetChromaControl(hFG,NOTCH_FILTER|BW_DETECT);

			// resize buffers and set the value of pixel type to PBITS_Y8
			ResetBuffers(PBITS_Y8);
			break;
		}
		return TRUE;
	
	case WM_CLOSE:
		DestroyWindow(hWnd);
		return TRUE;
	
	case WM_DESTROY:
		PostQuitMessage (0);
		return TRUE;
	}
	return FALSE;
}

/******************************************************************************
 * Name:         VideoProc
 *-----------------------------------------------------------------------------
 * Description:  Window procedure for the video display window(s). You can use
 *               this procedure for multiple display windows.
 ******************************************************************************/
LONG WINAPI VideoProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;

	switch (iMsg)
	{
	case WM_CREATE:
		// get the default main window size
		GetClientRect(hMainDlg, (LPRECT)&rectMain);

		// set video window size and position
		SetWindowPos(hWnd, NULL, rectMain.right+(GetSystemMetrics(SM_CXFRAME)*2),
			rectMain.top , iWindowX, iWindowY, 0);
		return 0;
	
	case WM_PAINT:
		// repaint video window 
		hDC = BeginPaint(hWnd, &ps);
		ShowFrame(gpFrame, hDC, iImageX, iImageY, PIXEL_TYPE);
		EndPaint(hWnd, &ps);	
		return 0;

	case WM_DESTROY:
		CloseVideoWindow();
		return 0;
	}
	return(DefWindowProc(hWnd, iMsg, wParam, lParam));
}

/******************************************************************************
 * Name:         AppExit
 *-----------------------------------------------------------------------------
 * Description:  This function contains common exit code.
 ******************************************************************************/
void AppExit(void)
{	
	if(hFG != 0)
	{
		// wait for all queued activity to stop before deleting the FG 
		pxc.WaitFinished(hFG, 0);
		pxc.FreeFG(hFG);
	}

	// free frame
	if(gpFrame != NULL)
		FrameLib.FreeFrame(gpFrame);
	// free frame
	if(gpFrame2 != NULL)
		FrameLib.FreeFrame(gpFrame2);

	// free IPL images
	if(img)
		iplDeallocate( img, IPL_IMAGE_ALL );
	if(img)
		iplDeallocate( img2, IPL_IMAGE_ALL );

	GrayscalePalette(NULL, PXC_PALETTE_DELETE);

	imagenation_CloseLibrary(&pxc);
	imagenation_CloseLibrary(&FrameLib);
}

/******************************************************************************
 * Name: RegisterVideoWindow
 ******************************************************************************/
void RegisterVideoWindow(HINSTANCE hInstance)
{
	WNDCLASS  wc;

	memset(&wc,0,sizeof(wc));         // clear stack variable

	// register the control window class

	wc.style         = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc   = VideoProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(CYBER_PXC));
	wc.hCursor       = NULL;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = szVidClass;

	RegisterClass (&wc);
}

/******************************************************************************
 * Name: CreateVideoWindow
 ******************************************************************************/
HWND CreateVideoWindow(HINSTANCE hInstance)
{
HWND hWnd;

  hWnd = CreateWindow (szVidClass,   // window class name
        NULL,
        WS_OVERLAPPEDWINDOW,         // window style
        CW_USEDEFAULT,               // initial x position
        CW_USEDEFAULT,               // initial y position
        CW_USEDEFAULT,               // initial x size
        CW_USEDEFAULT,               // initial y size
        NULL,                        // parent window handle
        NULL,                        // window menu handle
        hInstance,                   // program instance handle
        NULL);                       // creation parameters

  return hWnd;
}

/******************************************************************************
 * Name:         InitializePXC
 *-----------------------------------------------------------------------------
 * Description:  This function contains code that is unique to initializing
 *               the PXC. There is another function that contains code for
 *               resetting the PXC.
 ******************************************************************************/
long InitializePXC(void)
{
	// allocate any frame grabber
	hFG = pxc.AllocateFG(-1);
	if(!hFG)
	{
		return FALSE;
	}
	return TRUE;
 
}

/******************************************************************************
 * Name:         ResetPXC
 *-----------------------------------------------------------------------------
 * Description:  This function should contain initialization code that would
 *               be needed if the program or the PXC were reset, but not code
 *               that is used for first-time initialization. You should design
 *               this function so it can be called many times without creating
 *               problems.
 *               
 *               This function shows how to setup to grab a single field. In 
 *               this function you should look at the values of iImageX  and  
 *               iImageY. iImageX is set to half the expected pixel width to 
 *               make the display look good. iImageY is set to the actual  
 *               expected field length. When iImageY is used in the call to  
 *               SetYResolution it is multiplied by 2 to double the image  
 *               height for the library function:
 *                          pxc.SetYResolution(hFG,(short)(iImageY*2)); 
 ******************************************************************************/
BOOL ResetPXC(void)
{
int iVideoType;

	// reset the PXC to a default state
	pxc.Reset(hFG);

	// wait 2 1/2 seconds for CCIR detect
	Sleep(2500);

	iVideoType = pxc.VideoType(hFG);

	switch(iVideoType)
	{
	case 0:     /* no video */
	case 1:     /* NTSC */
		iGrabType = 0;
		iImageX = 640;
		iImageY = 486;
		if(iVideoType == 0)
			return FALSE;
		break;
	case 2:     /* CCIR */
		iGrabType = 0;
		iImageX = 768;
		iImageY = 576;
		break;
	}

	pxc.SetWidth(hFG,(short)iImageX);
	pxc.SetHeight(hFG,(short)(iImageY));
	pxc.SetLeft(hFG,0);
	pxc.SetTop(hFG,0);
	pxc.SetXResolution(hFG,(short)iImageX);
	pxc.SetYResolution(hFG,(short)(iImageY));
 

	// Size video Window.
    SizeVideoWindow();

	return TRUE;
}

/******************************************************************************
 * Name:         SizeVideoWindow
 *-----------------------------------------------------------------------------
 * Description:  This function will resize create a video window that can
 *               fit on the screen.
 ******************************************************************************/
void SizeVideoWindow(void)
{ 
	float AspectRatio;
	int FrameSizeX, FullScreenSizeX;

	AspectRatio = (float)iImageY/iImageX;
	iWindowY = iImageY;
	iWindowX = iImageX;
	
	// get the default window size
	GetClientRect(hMainDlg, (LPRECT)&rectMain);
	// if dwImageX to large then resize to fit screen
	if (GetSystemMetrics(SM_CXFULLSCREEN) < (int)(iImageX+rectMain.right))
	{
		FrameSizeX = GetSystemMetrics(SM_CXFRAME)*4;
		FullScreenSizeX = GetSystemMetrics(SM_CXFULLSCREEN);
		iWindowX = FullScreenSizeX - rectMain.right - FrameSizeX;
		// resize dwWindowY to match AspectRatio
		iWindowY= (int)(iWindowX*AspectRatio);
	}
	// get the initial window size
	iWindowX = GetSystemMetrics(SM_CXFRAME)*2+iWindowX;
	iWindowY = GetSystemMetrics(SM_CXFRAME)*2+GetSystemMetrics(SM_CYCAPTION)+iWindowY;
}


/******************************************************************************
 * Name:         OpenVideoWindow
 *-----------------------------------------------------------------------------
 * Description:  This function creates the window where the video is displayed
 *               and sets all necessary variables accordingly.
 ******************************************************************************/
int OpenVideoWindow(void)
{
	// ungray the windows that pertain to the control of the video window
	EnableWindow(GetDlgItem (hMainDlg, IDC_START_RT), TRUE);
	EnableWindow(GetDlgItem (hMainDlg, IDC_STOP_RT), TRUE);
	EnableWindow(GetDlgItem (hMainDlg, IDC_GRAB), TRUE);

	// and set their default values
	CheckRadioButton(hMainDlg, IDC_OPEN, IDC_CLOSE, IDC_OPEN);
	CheckRadioButton(hMainDlg, IDC_START_RT, IDC_STOP_RT, IDC_STOP_RT);

	// open the video display window if it is not already open
	if(!hDisplay)
	{
		hDisplay = CreateVideoWindow(hAppInst);
		if(!CreateDisplayBuffer(iImageX, iImageY, PIXEL_TYPE)) 
		{
			MessageBox(0, "Unable to allocate Display buffer", 
			"Display Buffer allocation failure", MB_TASKMODAL | MB_TOPMOST);
			return FALSE;
		}
		ShowWindow(hDisplay, SW_SHOW);
	}

	//  displays the hardware/firmware revision
	if(!DisplayRevision(hFG));
		return FALSE;

	return TRUE;
}

/******************************************************************************
 * Name:         CloseVideoWindow
 *-----------------------------------------------------------------------------
 * Description:  Close the video display window and clear its handle so
 *               other functions know it is closed. Also delete is 
 *               associated buffer.
 ******************************************************************************/
int CloseVideoWindow(void)
{
	// turn off window control buttons
	EnableWindow(GetDlgItem (hMainDlg, IDC_START_RT), FALSE);
	EnableWindow(GetDlgItem (hMainDlg, IDC_STOP_RT), FALSE);
	EnableWindow(GetDlgItem (hMainDlg, IDC_GRAB), FALSE);

	// check the close button
	CheckRadioButton(hMainDlg, IDC_OPEN, IDC_CLOSE, IDC_CLOSE);

	// stop AppIdle from trying to display
	bAcquire = FALSE;
	// set hDisplay to null to show that the window is closed
	hDisplay = NULL;
 	// free the video windows buffer
	FreeDisplayBuffer();
	return TRUE;
}

/******************************************************************************
 * Name:         DisplayRevision 
 *-----------------------------------------------------------------------------
 * Description: The Read and displays the hardware/firmware revision of the 
 *              grabber and the driver in the display window title bar. 
 ******************************************************************************/
int DisplayRevision(long fgHandle)
{
	int	iHardwareRev;
	char szTitleBar[100];

	// get the hardware/firmware revision number
	iHardwareRev = pxc.ReadRevision(hFG);

	// check to see if valid revision number was returned
	if(iHardwareRev == 0)
		return FALSE;

	// show hardware revision in title bar of display window
	wsprintf(szTitleBar, "PXC - Hardware Rev:%X", iHardwareRev);
	SetWindowText(hDisplay, szTitleBar);

	return TRUE;
}

/*****************************************************************************
 * Name:         ResetBuffers 
 *-----------------------------------------------------------------------------
 * Description:  resize the frame buffers and display buffer to match 
 *               the pixel type                    
 *****************************************************************************/
BOOL ResetBuffers(short PixelType)
{	
	// set the value of pixel type 
	PIXEL_TYPE = PixelType;
	
	// wait for all queued activity to stop before deleting the frames 
	pxc.WaitFinished(hFG, 0);
 
	if(gpFrame != NULL)
		FrameLib.FreeFrame(gpFrame);
	if(gpFrame2 != NULL)
		FrameLib.FreeFrame(gpFrame2);
	if(img)
		iplDeallocate( img, IPL_IMAGE_ALL );
	if(img2)
		iplDeallocate( img2, IPL_IMAGE_ALL );
		
	/*------ allocate a frame buffers ------*/
	
	// create a pxc compatible frame from ipl image data 
	if(! create_ipl_Image(iImageX,iImageY,PIXEL_TYPE))
	{
		MessageBox(0, "Unable to create frame for ipl", "Frame Failure", 0);
		AppExit();
		return FALSE;
	}
	

	if(hDisplay)
	{
		// free the video windows buffer
		FreeDisplayBuffer();
		if(!CreateDisplayBuffer(iImageX, iImageY, PixelType)) 
		{
			MessageBox(0, "Unable to allocate Display buffer", 
				"Display Buffer allocation failure", MB_TASKMODAL | MB_TOPMOST);
			return FALSE;
		}
	}
	return TRUE;
}


/*****************************************************************************
 * Name: Process_Image
 *-----------------------------------------------------------------------------
 * Description:  Image processing procedure
 * 
 *****************************************************************************/
void Process_Image(HDC hdc)
{
	ShowFrame(gpFrame, hdc, iImageX, iImageY, PIXEL_TYPE);

	//ShowFrame(gpFrame2, hdc, iImageX, iImageY, PIXEL_TYPE);

}


/*****************************************************************************
 * Name: create_ipl_Image
 *-----------------------------------------------------------------------------
 * Description:  create a pxc compatible frame for ipl image data 
 * 
 *****************************************************************************/

BOOL create_ipl_Image(int MaxX,int MaxY,int iPixelType ) 
{
    
	if(iPixelType==PBITS_Y8) // for gray scale
		img = iplCreateImageHeader( 
		  1,                            // 1 channel
		  0,                            // no alpha channel
		  IPL_DEPTH_8U,                 // data type is ushort
		  "GRAY",                       // color model
		  "GRAY",                       // channel sequence
		  IPL_DATA_ORDER_PIXEL,         // channel arrangement
		  IPL_ORIGIN_TL,                // top left orientation
		  IPL_ALIGN_DWORD,              // 4 bytes align
		  MaxX,MaxY,                    // image width and height
		  NULL, NULL,                   // no ROI, no mask ROI
		  NULL, NULL);                  // image ID, not tiled
	else // for color 24bit RGB
		img = iplCreateImageHeader( 
		  3,                            // 3 channels
		  0,                            // no alpha channel
		  IPL_DEPTH_8U,                 // data type is ushort
		  "RGB",                        // color model
		  "RGB",                        // channel sequence
		  IPL_DATA_ORDER_PIXEL,         // channel arrangement
		  IPL_ORIGIN_TL,                // top left orientation
		  IPL_ALIGN_DWORD,              // 4 bytes align
		  MaxX,MaxY,                    // image width and height
		  NULL, NULL,                   // no ROI, no mask ROI
		  NULL, NULL);                  // image ID, not tiled

   /// allocate image data without filling
   iplAllocateImage( img, 0, 0 ); 

   // make a clone
   img2 = iplCloneImage(img);

   // create a frame from pointer to image clone buffer
   if( img2->imageData ) 
   {
	   // allocate a frame buffer using a pointer to the image data
	   gpFrame2 = FrameLib.FrameFromPointer(img2->imageData,(short)MaxX, (short)MaxY, (short)iPixelType);

	   if(!gpFrame2)
	   {
			MessageBox(0, "Allocate Buffer Failed", "Frame2 Failure", 0);
			return FALSE;
	   }
   }
   else 
	   return FALSE;
  
   /// create a frame from pointer to image buffer
   if( img->imageData ) 
   {
	  // allocate a frame buffer using a pointer to the image data
	  gpFrame = FrameLib.FrameFromPointer(img->imageData,(short)MaxX, (short)MaxY, (short)iPixelType);

	  if(!gpFrame)
	  {
		MessageBox(0, "Allocate Buffer Failed", "Frame Failure", 0);
		return FALSE;
	  }
   }
   else 
	   return FALSE;

   
   return TRUE;

}
