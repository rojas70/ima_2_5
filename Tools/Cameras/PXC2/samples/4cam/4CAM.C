////////////////////////////////////////////////////////////////////////////////
// 4CAM.C
//
// This program provides an example of switching cameras. The important thing
// to remember when switching cameras is to allow some time for the frame grabber
// to synchronize to the new video signal.
//
// This sample creates four windows, one for each input on the mux, and
// grabs to each in succession. For simplicity the sample assumes your desktop
// resolution is at least 1024 x 768. If you are using a smaller desktop, you
// will probably want to set the windows to a smaller size. The windows sizes
// are set in the CreateControlWindow() function.
////////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <stdio.h>
#include "pxc.h"
#include "resource.h"

// iframe.h is an exact copy of frame.h. We will be changing the name of frame.h
// in a future to iframe.h because Microsoft has a frame.h. I have included an
// iframe.h with this package to make your build work. You might want to move
// it to the c:\pxc2\include directory.
#include "iframe.h"

#define CAMERAS 4

/* this program can use either 24 bit color or 8 bit gray frames.
  change the value of PIXEL_TYPE to PBITS_RGB24 or PBITS_Y8 */
#define PIXEL_TYPE PBITS_RGB24
#define PXC_NAME  "pxc_95.dll"
#define FRAME_NAME  "frame_32.dll"
#define PXC_NT    "pxc_nt.dll"

BOOL AppInit(HINSTANCE hInst, HINSTANCE hPrev, LPSTR szCmdLine, int sw);
LONG WINAPI CtlProc(HWND, UINT, WPARAM, LPARAM);
void CreateControlWindows(HINSTANCE hInst, LPSTR szCmdLine, int sw);
void RegisterWindowClasses(HINSTANCE hInst, LPSTR szCmdLine, int sw);
void AppExit(void);
BOOL AppIdle(void);
void AppPaint(HWND hwnd, HDC hdc);
void GetGlobals(HWND hwnd, LPARAM lParam);
void GetImage(FRAME __PX_FAR *frh);
void SetBitMapHead(void);
int AllocBuffer(void);

static HINSTANCE hAppInst;
static HWND hwndCtl[CAMERAS];
static char szAppName[] = "4CAM" ;
static char szTitleBar[100];
static char szTitle[] = "4 Camera Sample";
static int  iBoardRev;
static BOOL fAcquire;

static int  ImageMaxX,
            ImageMaxY,
            WindowX,
            WindowY;

static int  StartTest,
            Testing,
            FrameCount,
            ErrorCount;

static char szVideoType[80];
static int videotype;
static int modelnumber;

static long fgh;
static FRAME __PX_FAR *frh[CAMERAS];
static int initflags=0;
static tagQ[CAMERAS];
static int frhIdx;        /* frhIdx, indexes both frh[] and tagQ[] */
PXC pxc;
FRAMELIB frame;

/*----------------------------< GDI Functions >------------------------------*/
void CreateGrayPalette(void);

static HPALETTE hpalette;
static HANDLE hBuf;
static BYTE *gpBits;

struct {
  BITMAPINFOHEADER head;
  RGBQUAD colors[256];
} maphead;

/*-------------------------------< file data >-------------------------------*/
static char tmp[201];

/*****************************************************************************
 * Name:         WinMain                                                     *
 * Description:  Main window program and message processing loop.            *
 *****************************************************************************/
int PASCAL WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR szCmdLine, int sw)
{
	MSG msg;

  hAppInst = hInst;     /* save for later */

  /* Call initialization procedure */
  if(!AppInit(hInst, hInst, szCmdLine, sw)) 
	{
    AppExit();
    return FALSE;
  }

  /*-------------------------------------------------------------------------
    Polling messages from event queue
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
  return msg.wParam;
}
/*****************************************************************************
 * Name:         AppInit                                                     *
 *****************************************************************************/
BOOL AppInit(HINSTANCE hInst, HINSTANCE hPrev, LPSTR szCmdLine, int sw)
{
	int i;
  fgh = 0;
  fAcquire = TRUE;
  hBuf = NULL;

  /*-------------------------------------------------------------------------
  initialize the library
  -------------------------------------------------------------------------*/
  if (!imagenation_OpenLibrary(PXC_NAME,&pxc,sizeof(pxc)))
  {
    if (!imagenation_OpenLibrary(PXC_NT,&pxc,sizeof(pxc)))
    {
      MessageBox(0, "couldn't load pxc DLL", szAppName, MB_OK);
      return FALSE;
    }
  }
  initflags|=1;

  if (!imagenation_OpenLibrary(FRAME_NAME,&frame,sizeof(frame))) {
    MessageBox(0, "couldn't load "FRAME_NAME, szAppName, MB_OK);
    return FALSE;
  }
  initflags|=2;

  /*-------------------------------------------------------------------------
  allocate any frame grabber
  -------------------------------------------------------------------------*/
  fgh = pxc.AllocateFG(-1);
  if(!fgh) {
    MessageBox(0, "AllocateFG Failed", szAppName, MB_OK);
    return FALSE;
  }
  Sleep(2500); /* wait for CCIR autodetect */
  videotype = pxc.VideoType(fgh);
	modelnumber = pxc.GetModelNumber(fgh);
  switch(videotype) {
    case 0:     /* no video */
    case 1:     /* NTSC */
      ImageMaxX = 640;
      ImageMaxY = 486;
      break;
    case 2:     /* CCIR */
      ImageMaxX = 768;
      ImageMaxY = 576;
    	if(videotype == 0)
      	wsprintf(szVideoType, "Video: None.  ");
      break;
  }
  pxc.SetWidth(fgh,(short)ImageMaxX);
  pxc.SetHeight(fgh,(short)ImageMaxY);
  pxc.SetLeft(fgh,0);
  pxc.SetTop(fgh,0);
  pxc.SetXResolution(fgh,(short)ImageMaxX);
  pxc.SetYResolution(fgh,(short)ImageMaxY);

  /*-------------------------------------------------------------------------
  allocate four frame buffers (one for each window)
  -------------------------------------------------------------------------*/
	for (i=0; i<CAMERAS; i++)
	{
		frh[i] = pxc.AllocateBuffer((short)ImageMaxX, (short)ImageMaxY, PIXEL_TYPE);
		if (!frh[i])
		{
			sprintf(tmp, "AllocateBuffer() failed on frh[%d]", i);
	    MessageBox(0, tmp, szAppName, MB_OK);
		  return FALSE;
		}
	}

  SetBitMapHead();

  if(!AllocBuffer()) {
    MessageBox(0, "Cannot allocate scratch buffer", szAppName, MB_OK);
    return FALSE;
  }

  /* create windows */

  RegisterWindowClasses(hInst, szCmdLine, sw);
  CreateControlWindows(hInst, szCmdLine, sw);
	for (i=0; i<CAMERAS; i++)
	{
		if(!hwndCtl[i]) 
		{
			MessageBox(0, "Cannot create control window", szAppName, MB_OK);
			return FALSE;
		}
		ShowWindow(hwndCtl[i],sw);
	}

  CreateGrayPalette();

  return TRUE;
}
/*****************************************************************************
 * Name:         AppExit                                                     *
 *****************************************************************************/
void AppExit(void)
{
	int i;

  if(hBuf) {
    GlobalUnlock(hBuf);
    GlobalFree(hBuf);
  }
  if(hpalette)
    DeleteObject(hpalette);
  for(i=0; i<CAMERAS; ++i) 
	{
    if(frh[i])
      frame.FreeFrame(frh[i]);
  }
  if(fgh)
    pxc.FreeFG(fgh);
  if (initflags&1)
    imagenation_CloseLibrary(&pxc);
  if (initflags&2)
    imagenation_CloseLibrary(&frame);
}
/*****************************************************************************
 * Name: AppIdle                                                             *
 *****************************************************************************/
BOOL AppIdle(void)
{
	HDC hdc;
	int i;

  if (GetKeyState(VK_LBUTTON) >= 0) 
	{
    /* increment the index (mod CAMERAS) */
		frhIdx = (frhIdx + 1) % CAMERAS;

    /* copy the video ram to a memory buffer */
    if(tagQ[frhIdx]) 
		{
      while(!pxc.IsFinished(fgh, tagQ[frhIdx])) 
        pxc.WaitVB(fgh);
      GetImage(frh[frhIdx]);
      tagQ[frhIdx] = 0;
    }

    if(fAcquire) 
		{
			pxc.SetCamera(fgh, (short)frhIdx, 0);
			/* comment this line out to see what happens if you switch naively */
			if(modelnumber == PXC200_F)
			{
				// this wait period after a grab is somewhat dependent on lighting and
				// camera. You can tweek the number 2 until you get frames that look good
				// for your application. This is a single field wait, so the number 2 
				// means to wait for 2 fields or 1 frame.
				for(i=0; i<2; ++i)
					pxc.Wait(fgh, SINGLE_FLD);  // wait a single field
			}
			else
			{
				// this wait period after a grab is somewhat dependent on lighting and
				// camera. You can tweek the number 4 until you get frames that look good
				// for your application. Try reducing the number 4 to 3 or 2. This is a
				// complete field wait not a single field wait. If you substitute a single
				// field wait, change the 4 to an 8.
				for(i=0; i<4; ++i)
					pxc.Wait(fgh, 0); // wait a whole frame
			}
      tagQ[frhIdx] = pxc.Grab(fgh, frh[frhIdx], 0);
      hdc = GetDC(hwndCtl[frhIdx]);
      AppPaint(hwndCtl[frhIdx], hdc);
      ReleaseDC(hwndCtl[frhIdx], hdc);
    }
    return FALSE;
  }
  return TRUE;      // background app; nothing to do.
}
/*****************************************************************************
 * Name: AppPaint                                                            *
 *****************************************************************************/
void AppPaint(HWND hwnd, HDC hdc)
{
  if (hpalette&&(PIXEL_TYPE==PBITS_Y8)) {
    SelectPalette(hdc, hpalette, TRUE);
    RealizePalette(hdc);
  }

  SetDIBitsToDevice(
    hdc,
    0, 0, ImageMaxX, ImageMaxY,
    0, 0, 0, ImageMaxY,
    gpBits, (LPBITMAPINFO)&maphead, DIB_RGB_COLORS);
}
/*****************************************************************************
 * Name:         CtlProc                                                     *
 * Description:  Main window procedure.                                      *
 *****************************************************************************/
LONG WINAPI CtlProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT Rect;

  switch (message) 
	{
    case WM_CREATE:
      GetGlobals(hwnd, lParam);
      GetWindowRect(hwnd, &Rect);
      SetWindowPos(hwnd, NULL, 
				Rect.left, Rect.top, WindowX, WindowY, SWP_SHOWWINDOW);
      return 0L;

    case WM_SIZE:
      InvalidateRect(hwnd, NULL, TRUE);
      return 0L;

    case WM_PAINT:
      hdc = BeginPaint(hwnd,&ps);
      AppPaint(hwnd,hdc);
      EndPaint(hwnd,&ps);
      return 0L;

    case WM_PALETTECHANGED:
      InvalidateRect(hwnd, NULL, FALSE);
      return 0L;
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0L;
  }
  return(DefWindowProc(hwnd, message, wParam, lParam));
}
/*****************************************************************************
 * Name: CreateGrayPalette                                                   *
 *****************************************************************************/
void CreateGrayPalette(void)
{
int i;
struct
{
  WORD Version;
  WORD NumberOfEntries;
  PALETTEENTRY aEntries[256];
} Palette;

  if (hpalette)
    DeleteObject(hpalette);

  Palette.Version = 0x300;
  Palette.NumberOfEntries = 256;
  for (i=0; i<256; ++i) 
	{
    Palette.aEntries[i].peRed = i;
    Palette.aEntries[i].peGreen = i;
    Palette.aEntries[i].peBlue = i;
    Palette.aEntries[i].peFlags = PC_NOCOLLAPSE;
    maphead.colors[i].rgbRed = i;
    maphead.colors[i].rgbGreen= i;
    maphead.colors[i].rgbBlue = i;
    maphead.colors[i].rgbReserved = 0;
  }
  hpalette = CreatePalette((LOGPALETTE *)&Palette);
}
/*****************************************************************************
 * Name: GetImage                                                            *
 *****************************************************************************
 * This function copies the frame buffer to a memory buffer upside down.     *
 * StretchDIBits expects the image to be reversed line for line. If you want *
 * the image to be right side up in the buffer you need to mofify the data   *
 * in the call to StretchDIBits and in the maphead structure.                *
 *****************************************************************************/
void GetImage(FRAME __PX_FAR *frh)
{
int i,len;
BYTE __PX_HUGE *p;

  len = ImageMaxX*(((PIXEL_TYPE&0xFF)+7)>>3);
  p = gpBits;
  for(i=ImageMaxY-1; i>=0; --i) {
    frame.GetRow(frh, p, (short)i);
    p += len;
  }
}
/*****************************************************************************
 * Name: SetBitMapHead                                                       *
 *****************************************************************************/
void SetBitMapHead(void)
{
  /* set up bitmap header */

  maphead.head.biSize=sizeof(BITMAPINFOHEADER);
  maphead.head.biWidth=ImageMaxX;
  maphead.head.biHeight=ImageMaxY;
  maphead.head.biPlanes=1;
  maphead.head.biBitCount=PIXEL_TYPE&0xFF;
  maphead.head.biCompression=BI_RGB;
  maphead.head.biSizeImage=0;
  maphead.head.biXPelsPerMeter=0;
  maphead.head.biYPelsPerMeter=0;
  maphead.head.biClrUsed=0;
  maphead.head.biClrImportant=0;
}
/*****************************************************************************
 * Name: RegisterWindowClasses                                               *
 *****************************************************************************/
void RegisterWindowClasses(HINSTANCE hInst, LPSTR szCmdLine, int sw)
{
	WNDCLASS  wc;
	static aClass = 0;

  memset(&wc,0,sizeof(wc));         /* clear stack variable */

  /* register the control window class */

  if(aClass == 0) 
	{
    wc.style = CS_BYTEALIGNWINDOW | CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
    wc.lpfnWndProc   = (WNDPROC)CtlProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hAppInst;
    wc.hIcon         = LoadIcon(hInst, MAKEINTRESOURCE(PXC_ICON));
    wc.hCursor       = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = szAppName;

    aClass = RegisterClass (&wc);
  }
}
/*****************************************************************************
 * Name: CreateControlWindow                                                 *
 *****************************************************************************/
void CreateControlWindows(HINSTANCE hInst, LPSTR szCmdLine, int sw)
{
	int i;

	for (i=0; i<CAMERAS; i++)
	{
		sprintf(szTitleBar, "%s, input %d", szTitle, i);
		hwndCtl[i] = CreateWindow (szAppName,    // window class name
			    szTitleBar,
				  WS_OVERLAPPEDWINDOW,         // window style
					(i%2)*512,                   // initial x position
	        (i/2)*384,			             // initial y position
		      CW_USEDEFAULT,		           // initial x size
			    CW_USEDEFAULT,               // initial y size
				  NULL,                        // parent window handle
					NULL,                        // window menu handle
	        hAppInst,                    // program instance handle
		      NULL);                       // creation parameters
	}
}
/*****************************************************************************
 * Name: GetGlobals                                                          *
 *****************************************************************************/
void GetGlobals(HWND hwnd, LPARAM lParam)
{
  /* calculate the initial window size */
  WindowX = 500;
  WindowY = 375;
}
/*****************************************************************************
 * Name: AllocBuffer                                                         *
 *****************************************************************************/
int AllocBuffer(void)
{
  hBuf = GlobalAlloc(GMEM_FIXED, (long)ImageMaxX * ImageMaxY 
                                  *(((PIXEL_TYPE&0xFF)+7L)>>3));
  if(hBuf == NULL) {
    return FALSE;
  }
  gpBits = (BYTE __PX_HUGE *)GlobalLock(hBuf);
  return TRUE;
}
