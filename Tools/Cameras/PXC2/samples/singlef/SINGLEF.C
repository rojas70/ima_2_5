/***************************************************************************
 |                             SINGLEF.C                                   |
 |-------------------------------------------------------------------------|
 | This program which was derived from our PXCDRAW2 sample with just a few |
 | simple modifications shows how to grab a single field of video and      |
 | display it in a window.                                                 |
 |                                                                         |
 | Standard interlaced video is comprised of two fields that are           |
 | interlaced to make a full frame of video. In the case of NTSC video,    |
 | the size of a frame is 640 x 480. Hence, the size of the individual     |
 | fields is 640 x 240. The horizontal dimension is unchanged, but there   |
 | are only half as many lines in a field as in a frame. When we display   |
 | a field of video we crop the horizontal dimension from 640 to 320 to    |
 | keep the aspect ratio the same as it was at 640 x 480 and make the      |
 | images look correct.                                                    |
 |                                                                         |
 | This sample creates a window just large enough to display a single      |
 | field of video and illustrates the correct coding for grabbing just a   |
 | single field from the PXC200A.                                          |
 |                                                                         |
 | The important changes between this program and PXCDRAW2 can be seen by  |
 | looking at the AppInit() function to see how we handle the variables    |
 | ImageMaxX and ImageMaxY. These two variables control both the image     |
 | and window sizes.                                                       |
 |                                                                         |
 | Another important change between this program and PXCDRAW2 is the       |
 | Grab() function. In this program we OR together several flags. Two of   |
 | them are SINGLE_FLD and FIELD0. We only grab field 0. You can modifiy   |
 | the Grab() command to grab field 1, but you should probably avoid       |
 | grabbing EITHER field at random because the image will bounce up and    |
 | down within the window.                                                 |
 |                                                                         |
 ***************************************************************************/
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <commdlg.h>
#include <time.h>
#include "pxc.h"
#include "iframe.h"
#include "resource.h"


/* this program can use either 24 bit color or 8 bit gray frames.
  change the value of PIXEL_TYPE to PBITS_RGB24 or PBITS_Y8 */
#define PIXEL_TYPE PBITS_RGB24
#ifdef _WIN32
#define PXC_NAME "pxc_95.dll"
#define FRAME_NAME "frame_32.dll"
#define PXC_NT "pxc_nt.dll"
#else
#define PXC_NAME "pxc_31.dll"
#define FRAME_NAME "frame_16.dll"
#define PXC_NT    "pxc_31.dll"
#endif

#define TEST_TIMER 1
#define ON  1
#define OFF 2


  /*-------------------------------------------------------------------------
   This button structure is used to create the function buttons as child
   windows. There are other ways to do this. We figured this would be the
   best way to do it for our example.
   -------------------------------------------------------------------------*/
#define NBUTTONS 7
typedef struct tagBUTTON {
  HWND hwnd;
  long style;
  LPSTR text;
  int id;
} BUTTON;

  /*-------------------------------------------------------------------------
  These values are used to control the processing of the WM_COMMAND message.
   -------------------------------------------------------------------------*/
#define ID_FBASE      101
#define ID_ACQUIRE    ID_FBASE+0
#define ID_STOP       ID_FBASE+1
#define ID_WRITE      ID_FBASE+2
#define ID_READ       ID_FBASE+3
#define ID_TIME       ID_FBASE+4
#define ID_COMPOSITE  ID_FBASE+5
#define ID_SVIDEO     ID_FBASE+6

BUTTON Functions[NBUTTONS] = {
  {NULL, BS_PUSHBUTTON, " Acquire ", ID_ACQUIRE},
  {NULL, BS_PUSHBUTTON, " Stop ", ID_STOP},
  {NULL, BS_PUSHBUTTON, " Write File", ID_WRITE},
  {NULL, BS_PUSHBUTTON, " Read File ", ID_READ},
  {NULL, BS_PUSHBUTTON, " Time Test ", ID_TIME},
  {NULL, BS_PUSHBUTTON, " Composite ", ID_COMPOSITE},
  {NULL, BS_PUSHBUTTON, " S-Video ", ID_SVIDEO},
};
static unsigned ButtonTextLen;
static int ButtonHeight, ButtonWidth;
static int ViewOffset;

BOOL AppInit(HINSTANCE hInst, HINSTANCE hPrev, LPSTR szCmdLine, int sw);
LONG WINAPI CtlProc(HWND, UINT, WPARAM, LPARAM);
HWND CreateControlWindow(HINSTANCE hInst, LPSTR szCmdLine, int sw);
void RegisterWindowClasses(HINSTANCE hInst, LPSTR szCmdLine, int sw);
void AppExit(void);
BOOL AppIdle(void);
void AppPaint(HWND hwnd, HDC hdc);
void GetGlobals(HWND hwnd, LPARAM lParam);
void GetImage(FRAME __PX_FAR *frh);
void DrawButtons(HWND hwnd, LPARAM lParam, int draw);
void SetBitMapHead(void);
int AllocBuffer(void);
void DoTest(HWND hwnd);
void HourGlass(int on);

  /* text data for drawing text */
static int cxChar,                               /* average character width */
           cyChar;                                      /* character height */

static HINSTANCE hAppInst;
static HWND hwndCtl;
static char szAppName[] = "CAMERA 1" ;
static char szTitleBar[100];
static char szTitle[] = \
  "Single Field Video Display Sample";
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

static long fgh=0L;
static FRAME __PX_FAR *frh[2]={NULL,NULL};
static tagQ[2];
static int frhIdx;        /* frhIdx, indexes both frh[] and tagQ[] */
static int initflags=0;
PXC pxc;
FRAMELIB frame;

/*----------------------------< GDI Functions >------------------------------*/
void CreateGrayPalette(void);

static HPALETTE hpalette;
static HANDLE hBuf;
static BYTE __PX_HW *gpBits;

struct {
  BITMAPINFOHEADER head;
  RGBQUAD colors[256];
} maphead;

/*-------------------------------< file data >-------------------------------*/
void pxReadFile(HWND, FRAME __PX_FAR *);
void pxWriteFile(HWND, FRAME __PX_FAR *);
void InitializeFileSave(HWND);

static OPENFILENAME rfn, sfn;
static char szFilterSel[] = "BMP files (*.bmp)\0*.bmp\0";

#define MAXPATH 128
#define MAXDIR  66
#define MAXEXT  5

static char szReadFileName[MAXPATH];
static char szSaveFileName[MAXPATH];
static char szReadFileTitle[MAXPATH];
static char szSaveFileTitle[MAXPATH];
static char szReadFileDir[MAXDIR];
static char szSaveFileDir[MAXDIR];
static char szReadExt[MAXEXT];
static char szSaveExt[MAXEXT];

static char tmp[201];
static char *WriteErr = "Stop acquiring an image before writing a file";
static char *ReadErr = "Stop acquiring an image before reading a file";
/*****************************************************************************
 * Name:         WinMain                                                     *
 * Description:  Main window program and message processing loop.            *
 *****************************************************************************/
int PASCAL WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR szCmdLine, int sw)
{
MSG msg;

  hAppInst = hInst;     /* save for later */

  /* Call initialization procedure */
  if(!AppInit(hInst, hPrev, szCmdLine, sw)) {
    AppExit();
    return FALSE;
  }

  /*-------------------------------------------------------------------------
    Polling messages from event queue
   -------------------------------------------------------------------------*/
  for(;;) {
    if(PeekMessage(&msg, NULL, 0, 0,PM_REMOVE)) {
      if (msg.message == WM_QUIT)
        break;
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else {
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
  fgh = 0;
  fAcquire = TRUE;
  hBuf = NULL;
  Testing = FALSE;

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
  switch(pxc.VideoType(fgh)) {
    case 0:     /* no video */
    case 1:     /* NTSC */
      ImageMaxX = 640/2; 
      ImageMaxY = 486/2;
      break;
    case 2:     /* CCIR */
      ImageMaxX = 768/2; 
      ImageMaxY = 576/2;
      break;
  }
  if(GetSystemMetrics(SM_CXSCREEN) <= ImageMaxX) {
    ImageMaxX/=2;
    ImageMaxY/=2;
  }
  pxc.SetWidth(fgh,(short)ImageMaxX);
  pxc.SetHeight(fgh,(short)(ImageMaxY*2));
  pxc.SetLeft(fgh,0);
  pxc.SetTop(fgh,0);
  pxc.SetXResolution(fgh,(short)ImageMaxX);
  pxc.SetYResolution(fgh,(short)(ImageMaxY*2));
  iBoardRev = pxc.ReadRevision(fgh);

  /*-------------------------------------------------------------------------
  allocate frame buffers
  -------------------------------------------------------------------------*/
  frh[0] = pxc.AllocateBuffer((short)ImageMaxX, (short)ImageMaxY, PIXEL_TYPE);
  if(!frh[0]) {
    MessageBox(0, "Allocate Buffer #0 Failed", szAppName, MB_OK);
    return FALSE;
  }
  frh[1] = pxc.AllocateBuffer((short)ImageMaxX, (short)ImageMaxY, PIXEL_TYPE);
  if(!frh[1]) {
    MessageBox(0, "Allocate Buffer #1 Failed", szAppName, MB_OK);
    return FALSE;
  }

  SetBitMapHead();

  if(!AllocBuffer()) {
    MessageBox(0, "Cannot allocate scratch buffer", szAppName, MB_OK);
    return FALSE;
  }

  /* create windows */

  RegisterWindowClasses(hInst, szCmdLine, sw);
  hwndCtl = CreateControlWindow(hInst, szCmdLine, sw);
  if(!hwndCtl) {
    MessageBox(0, "Cannot create window", szAppName, MB_OK);
    return FALSE;
  }
  ShowWindow(hwndCtl,sw);

  SetTimer(hwndCtl, TEST_TIMER, 1000, NULL);    /* 1-second timer */
  CreateGrayPalette();
  InitializeFileSave(hwndCtl);

  return TRUE;
}
/*****************************************************************************
 * Name:         AppExit                                                     *
 *****************************************************************************/
void AppExit(void)
{
int i;

  /* wait for the grabs to stop before deleting the buffers */
  for(i=0; i<2; ++i) {
    if(tagQ[i])
      pxc.WaitFinished(fgh, tagQ[i]);
  }
  for(i=0; i<2; ++i) {
    if(frh[i])
      frame.FreeFrame(frh[i]);
  }

  if(hBuf) {
    GlobalUnlock(hBuf);
    GlobalFree(hBuf);
  }
  if(hpalette)
    DeleteObject(hpalette);
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

  if (IsIconic(hwndCtl))
    return TRUE;

  if (GetKeyState(VK_LBUTTON) >= 0) {
    /* swap the index from 0 to 1 or vice versa */
    frhIdx = (frhIdx == 1) ? 0 : 1;

    /* copy the video ram to a memory buffer */
    if(tagQ[frhIdx]) {
      pxc.WaitFinished(fgh, tagQ[frhIdx]);
      if(pxc.CheckError(fgh)&ERR_CORRUPT) {
        ++ErrorCount;
      }
      else {
        GetImage(frh[frhIdx]);
        ++FrameCount;
      }
      tagQ[frhIdx] = 0;
    }

    if(fAcquire) {
      tagQ[frhIdx] = pxc.Grab(fgh, frh[frhIdx], SINGLE_FLD | QUEUED | FIELD0);
      hdc = GetDC(hwndCtl);
      AppPaint(hwndCtl, hdc);
      ReleaseDC(hwndCtl, hdc);
    }
    return FALSE;
  }
  else {
    return TRUE;      // background app; nothing to do.
  }
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
    0, ViewOffset, ImageMaxX, ImageMaxY,
    0, 0, 0, ImageMaxY,
    gpBits, (LPBITMAPINFO)&maphead, DIB_RGB_COLORS);
}
/*****************************************************************************
 * Name:         CtlProc                                                     *
 * Description:  Main window procedure.                                      *
 *****************************************************************************/
LONG WINAPI CtlProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
//MINMAXINFO *lpmmi;
HDC hdc;
PAINTSTRUCT ps;

  switch (message) {

    case WM_CREATE:
      GetGlobals(hwnd, lParam);
      SetWindowPos(hwnd, NULL, 0, 0, WindowX, WindowY,
        SWP_NOMOVE | SWP_SHOWWINDOW | SWP_DRAWFRAME);
      DrawButtons(hwnd, lParam, TRUE);
      SendMessage(Functions[5].hwnd,BM_SETSTATE,1,0l);
      SendMessage(Functions[6].hwnd,BM_SETSTATE,0,0l);
      return 0L;

    case WM_SIZE:
      InvalidateRect(hwnd, NULL, TRUE);
      DrawButtons(hwnd, lParam, FALSE);
      return 0L;

    /* if you wish to lock the window size, un-comment this code */
    case WM_GETMINMAXINFO:
      //lpmmi = (MINMAXINFO *)lParam;
      //lpmmi->ptMinTrackSize.x = WindowX;
      //lpmmi->ptMinTrackSize.y = WindowY;
      //lpmmi->ptMaxTrackSize.x = WindowX;
      //lpmmi->ptMaxTrackSize.y = WindowY;
      //lpmmi->ptMaxSize.x = WindowX;
      //lpmmi->ptMaxSize.y = WindowY;
      return 0L;

    case WM_PAINT:
      hdc = BeginPaint(hwnd,&ps);
      AppPaint(hwnd,hdc);
      EndPaint(hwnd,&ps);
      return 0L;

    case WM_PALETTECHANGED:
      InvalidateRect(hwnd, NULL, FALSE);
      return 0L;

    case WM_TIMER:
      if(Testing || StartTest)
        DoTest(hwnd);
      return 0L;

    case WM_COMMAND:
      switch(wParam) {
        default:
        break;

        case ID_ACQUIRE:
          fAcquire = TRUE;
          return 0L;

        case ID_STOP:
          fAcquire = FALSE;
          return 0L;

        case ID_WRITE:
          if(fAcquire)
            MessageBox(hwnd, WriteErr, szAppName, MB_OK);
          else
            pxWriteFile(hwnd, frh[frhIdx]);
          return 0L;

        case ID_READ:
          if(fAcquire)
            MessageBox(hwnd, ReadErr, szAppName, MB_OK);
          else {
            pxReadFile(hwnd, frh[frhIdx]);
            GetImage(frh[frhIdx]);
            InvalidateRect(hwnd,NULL,TRUE);
          }
          return 0L;

        case ID_TIME:
          if (!fAcquire) {
            frhIdx = 0;
            tagQ[frhIdx] = pxc.Grab(fgh, frh[frhIdx], SINGLE_FLD | QUEUED | FIELD0);
            frhIdx = 1;
            tagQ[frhIdx] = pxc.Grab(fgh, frh[frhIdx], SINGLE_FLD | QUEUED | FIELD0);
            fAcquire = TRUE;
          }
          StartTest = TRUE;
          return 0L;

        case ID_COMPOSITE:
          pxc.SetCamera(fgh,0,0);
          pxc.SetChromaControl(fgh,NOTCH_FILTER|BW_DETECT);
          SendMessage(Functions[5].hwnd,BM_SETSTATE,1,0l);
          SendMessage(Functions[6].hwnd,BM_SETSTATE,0,0l);
          return 0L;

        case ID_SVIDEO:
          pxc.SetCamera(fgh,1,0);
          pxc.SetChromaControl(fgh,SVIDEO);
          SendMessage(Functions[5].hwnd,BM_SETSTATE,0,0l);
          SendMessage(Functions[6].hwnd,BM_SETSTATE,1,0l);
          return 0L;


      }
      break;

    case WM_DESTROY:
      KillTimer(hwnd, TEST_TIMER);
      PostQuitMessage(0);
      return 0L;
  }
  return(DefWindowProc(hwnd, message, wParam, lParam));
}
/*****************************************************************************
 * Name: DrawButtons                                                         *
 *****************************************************************************/
void DrawButtons(HWND hwnd, LPARAM lParam, int draw)
{
int i;
int rem;
RECT Rect;

  GetClientRect(hwnd, (LPRECT)&Rect);
  ButtonWidth = Rect.right/NBUTTONS;
  rem = Rect.right % NBUTTONS;

  if(draw) {
    /*---------------------------------------------------------------------
    create the function buttons as child windows
    ---------------------------------------------------------------------*/
    for(i=0; i<NBUTTONS; i++) {
      if(i == NBUTTONS-1)
        Functions[i].hwnd = CreateWindow("button", Functions[i].text,
          WS_CHILD | WS_VISIBLE | Functions[i].style,
          ButtonWidth*i, 0, ButtonWidth+rem, ButtonHeight,
          hwnd, (HMENU)Functions[i].id, hAppInst, NULL);
      else
        Functions[i].hwnd = CreateWindow("button", Functions[i].text,
          WS_CHILD | WS_VISIBLE | Functions[i].style,
          ButtonWidth*i, 0, ButtonWidth, ButtonHeight,
          hwnd, (HMENU)Functions[i].id, hAppInst, NULL);
    }
  }
  else {
    /*---------------------------------------------------------------------
    resize the function buttons
    ---------------------------------------------------------------------*/
    for(i=0; i<NBUTTONS; i++) {
      if(i == NBUTTONS-1)
        SetWindowPos(Functions[i].hwnd,NULL,ButtonWidth*i,0,
          ButtonWidth+rem,ButtonHeight,SWP_SHOWWINDOW);
      else
        SetWindowPos(Functions[i].hwnd,NULL,ButtonWidth*i,0,
          ButtonWidth,ButtonHeight,SWP_SHOWWINDOW);
    }
  }
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
  for (i=0; i<256; ++i) {
    Palette.aEntries[i].peRed = i;
    Palette.aEntries[i].peGreen = i;
    Palette.aEntries[i].peBlue = i;
    Palette.aEntries[i].peFlags = PC_NOCOLLAPSE;
    maphead.colors[i].rgbBlue = i;
    maphead.colors[i].rgbGreen= i;
    maphead.colors[i].rgbRed = i;
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

  len=ImageMaxX*(((PIXEL_TYPE&0xFF)+7)>>3);
  p = gpBits;
  //for(i=(ImageMaxY/2)-1; i>=0; --i) {
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
  static ATOM aClass = 0;

  memset(&wc,0,sizeof(wc));         /* clear stack variable */

  /* register the control window class */

  if(aClass == 0) {
    wc.style = CS_BYTEALIGNWINDOW | CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
    wc.lpfnWndProc   = CtlProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hAppInst;
    wc.hIcon         = LoadIcon(hInst, MAKEINTRESOURCE(PXC_ICON));
    wc.hCursor       = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = szAppName;

    RegisterClass (&wc);
  }
}
/*****************************************************************************
 * Name: CreateControlWindow                                                 *
 *****************************************************************************/
HWND CreateControlWindow(HINSTANCE hInst, LPSTR szCmdLine, int sw)
{
HWND hwnd;

  wsprintf(szTitleBar, "%s", szTitle);
  hwnd = CreateWindow (szAppName,    // window class name
        szTitleBar,
        WS_OVERLAPPEDWINDOW,         // window style
        CW_USEDEFAULT,               // initial x position
        CW_USEDEFAULT,               // initial y position
        CW_USEDEFAULT,               // initial x size
        CW_USEDEFAULT,               // initial y size
        NULL,                        // parent window handle
        NULL,                        // window menu handle
        hAppInst,                    // program instance handle
        NULL);                       // creation parameters

  return hwnd;
}
/*****************************************************************************
 * Name: GetGlobals                                                          *
 *****************************************************************************/
void GetGlobals(HWND hwnd, LPARAM lParam)
{
int i;
HDC hdc;
TEXTMETRIC tm;                              /* text metric structure */

  /* get the maximum button length */
  ButtonTextLen = 0;
  for(i=0; i<NBUTTONS; i++)
    if(ButtonTextLen < strlen(Functions[i].text))
      ButtonTextLen = strlen(Functions[i].text);

  hdc = GetDC (hwndCtl);
  SelectObject(hdc, GetStockObject(SYSTEM_FONT));
  GetTextMetrics (hdc, &tm);
  ReleaseDC (hwndCtl, hdc);
  cxChar = tm.tmAveCharWidth;
  cyChar = tm.tmHeight + tm.tmExternalLeading;
  ButtonHeight = 4*cyChar/3;
  ViewOffset = ButtonHeight;

  /* calculate the initial window size */
  WindowX = ImageMaxX + (GetSystemMetrics(SM_CXFRAME)*2);
  WindowY = ImageMaxY + ButtonHeight + 
    GetSystemMetrics (SM_CYCAPTION) + GetSystemMetrics (SM_CYFRAME)*2;
}
/*****************************************************************************
 * Name: AllocBuffer                                                         *
 *****************************************************************************/
int AllocBuffer(void)
{
  hBuf = GlobalAlloc(GMEM_FIXED, (long)ImageMaxX * ImageMaxY 
                                  *(((PIXEL_TYPE&0xFF)+7L)>>3));
  if(hBuf == NULL) {
    MessageBox(0, "Cannot allocate buffer", szAppName, MB_OK);
    return FALSE;
  }
  gpBits = (BYTE *)GlobalLock(hBuf);
  return TRUE;
}
/*****************************************************************************
 * Name: DoTest                                                              *
 *****************************************************************************/
void DoTest(HWND hwnd)
{
static int i, Timer; 
static clock_t StartTime;
static double dTestTime, dFPS;

  if(StartTest) {
    for(i=0; i<NBUTTONS; ++i)
      EnableWindow(Functions[i].hwnd, 0);
    EnableWindow(Functions[ID_TIME-ID_FBASE].hwnd, 1);
    fAcquire = TRUE;
    Timer = 9;
    FrameCount = 0;
    ErrorCount = 0;
    StartTest = FALSE;
    Testing = TRUE;
    StartTime = clock();
  }
  else {
    --Timer;
    EnableWindow(Functions[ID_TIME-ID_FBASE].hwnd, Timer%2);
    if(Timer < 0) {
      dTestTime = (double)(clock()-StartTime) / (double)CLOCKS_PER_SEC;
      dFPS = FrameCount / dTestTime;
      Testing = FALSE;
      wsprintf(tmp, (LPSTR)"Fields per second: %d\nTotal Errors: %d", 
        (int)dFPS, ErrorCount);
      MessageBox(hwnd, tmp, "Test Results", MB_OK);
      for(i=0; i<NBUTTONS; ++i)
        EnableWindow(Functions[i].hwnd, 1);
    }
  }
}
/*****************************************************************************
 * Name:         ReadFile                                                    *
 *****************************************************************************/
void pxReadFile(HWND hwnd, FRAME __PX_FAR *frh)
{
int i, j, ret;
static char *szReadError = \
"An error was encountered reading data from the file.\n\
The file header is probably corrupt.";

  if(GetOpenFileName(&rfn)) {
    HourGlass(ON);
    ret = frame.ReadBMP(frh, rfn.lpstrFile);
    HourGlass(OFF);
    if(ret != 0) {
      wsprintf(tmp, "Read error: %d", ret);
      MessageBox(hwnd, tmp, szReadError, MB_OK);
    }
    else {
      lstrcpy(szReadFileDir,szReadFileName);
      j = lstrlen(szReadFileDir);
      for(i=j; i>0; --i) {
        if(szReadFileDir[i] != '\\') {
          szReadFileDir[i] = '\0';
        }
        else {
          if(szReadFileDir[i-1] != ':')
            szReadFileDir[i] = '\0';
          break;
        }
      }
      lstrcpy(szReadFileName,szReadFileTitle);
    }
  }
}
/*****************************************************************************
 * Name:         WriteFile                                                   *
 *****************************************************************************/
void pxWriteFile(HWND hwnd, FRAME __PX_FAR *frh)
{
int i, j, ret; 
OFSTRUCT ofs;
static char *szWriteError = \
"An error was encountered writing data to the file.\n\
The file is incomplete and the data is invalid.";
static char *szComplete = \
"The file was written successfully.";

  if(GetSaveFileName(&sfn)) {
    HourGlass(ON);
    ret = frame.WriteBMP(frh, sfn.lpstrFile, 1);
    HourGlass(OFF);
    if(ret != 0) {
      wsprintf(tmp, "Write error: %d", ret);
      MessageBox(hwnd, tmp, szWriteError, MB_OK);
    }
    else {
      MessageBox(hwnd, szComplete, "Write File", MB_OK);
      lstrcpy(szSaveFileName,szSaveFileTitle);
      lstrcpy(szSaveFileDir,ofs.szPathName);
      j = lstrlen(szSaveFileDir);
      for(i=j; i>0; --i) {
        if(szSaveFileDir[i] != '\\') {
          szSaveFileDir[i] = '\0';
        }
        else {
          if(szSaveFileDir[i-1] != ':')
            szSaveFileDir[i] = '\0';
          break;
        }
      }
    }
  }
}
/*****************************************************************************
 * Name:         InitializeFileSave                                          *
 * Description:  Initialize the file open/save structures                    *
 *****************************************************************************/
void InitializeFileSave(HWND hwnd)
{
  rfn.lpstrTitle = "Read an Image from a File";
  rfn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
  rfn.lStructSize = sizeof(OPENFILENAME);
  rfn.hwndOwner = hwnd;
  rfn.lpstrFilter = szFilterSel;
  rfn.nMaxCustFilter = 0;
  rfn.nFilterIndex = 2l;
  rfn.nMaxFile = MAXPATH;
  rfn.nMaxFileTitle = MAXPATH;
  rfn.lpstrFile = szReadFileName;
  rfn.lpstrInitialDir = szReadFileDir;
  rfn.lpstrFileTitle = szReadFileTitle;
  rfn.lpstrDefExt = szReadExt;

  sfn.lpstrTitle = "Save Image in File";
  sfn.Flags = OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;
  sfn.lStructSize = sizeof(OPENFILENAME);
  sfn.hwndOwner = hwnd;
  sfn.lpstrFilter = szFilterSel;
  sfn.nMaxCustFilter = 0;
  sfn.nFilterIndex = 2l;
  sfn.nMaxFile = MAXPATH;
  sfn.nMaxFileTitle = MAXPATH;
  sfn.lpstrFile = szSaveFileName;
  sfn.lpstrInitialDir = szSaveFileDir;
  sfn.lpstrFileTitle = szSaveFileTitle;
  sfn.lpstrDefExt = szSaveExt;
}
/*****************************************************************************
 * Name: HourGlass                                                           *
 *****************************************************************************/
void HourGlass(int on)
{
static HCURSOR hCursor;

  if(on == ON) {
    hCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));
    ShowCursor(TRUE);
  }
  else {
    ShowCursor(FALSE);
    SetCursor(hCursor);
  }
}
