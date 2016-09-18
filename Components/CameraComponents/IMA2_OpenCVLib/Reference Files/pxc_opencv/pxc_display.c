/******************************************************************************
 * PXC_DISPLAY
 *
 * Copyright (c) 2001 by Imagenation
 *
 * Display Routines for PXC Series
 * 
 * This source code is intended to be used for drawing a frame to a
 * display window for a PXC series frame garbber.
 ******************************************************************************/
#include "pxc_display.h"

extern FRAMELIB		FrameLib;

// the static modifier keeps these variable names local to this file
static BYTE *gpBits = NULL;

typedef struct {
	BITMAPINFOHEADER bmiHeader; 
	RGBQUAD          bmiColors[256]; 
} XBITMAPINFO; 

static XBITMAPINFO bmi;

/******************************************************************************
 * Name:         ShowFrame
 *-----------------------------------------------------------------------------
 * Description:  Call this function when you need to repaint the video window.
 *               SetDIBitsToDevice() the fastest method of displaying a buffer.
 *               If you need to change the image size, you would need to use
 *               StretchDIBits(). For SetDIBits you need to flip the image
 *               upside down, but for StrecthDIBits you don't.
 ******************************************************************************/
void ShowFrame(FRAME __PX_FAR *pFrame, HDC hDC, int iWidth, int iHeight, int iPixelType)
{
	int i, iLen;
	BYTE *p;

	// calculate length
	iLen = iWidth * (((iPixelType & 0xFF) + 7) >> 3);
	
	// flip the image upside down row by row before display
	p = gpBits;
	for(i=iHeight-1; i>=0; --i) 
	{
		FrameLib.GetRow(pFrame, p, (short)i);
		p += iLen;
	}

	// if it is grayscale, realize the palette each time you display
	if(iPixelType == PBITS_Y8)
		GrayscalePalette(hDC, PXC_PALETTE_REALIZE);

	// SetDIBitsToDevice needs the bitmap header and a pointer to the upside
	// down image
	SetDIBitsToDevice(
		hDC,
		0, 0, iWidth, iHeight,
		0, 0, 0, iHeight,
		gpBits, (LPBITMAPINFO)&bmi, DIB_RGB_COLORS);
}

/******************************************************************************
 * Name:         SetBitmapHead
 *-----------------------------------------------------------------------------
 * Description:  In order to do a DIB (Device Independent Bitmap) display, you
 *               need to put the image in a BMP structure which means the
 *               image is upside down and has a header. This function creates
 *               the header.
 ******************************************************************************/
void SetBitmapHead(int iWidth, int iHeight, int iPixelType)
{
	// set up bitmap header 
	int i;

	memset (&bmi, 0, sizeof (BITMAPINFO));
	bmi.bmiHeader.biSize		  = sizeof (BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth		  = iWidth;
	bmi.bmiHeader.biHeight		  = iHeight;
	bmi.bmiHeader.biPlanes		  = 1;
	bmi.bmiHeader.biBitCount	  = iPixelType & 0xFF;
	bmi.bmiHeader.biCompression   = BI_RGB ;
	bmi.bmiHeader.biSizeImage	  = 0;
	bmi.bmiHeader.biXPelsPerMeter = 0;
	bmi.bmiHeader.biYPelsPerMeter = 0;
	bmi.bmiHeader.biClrUsed		  = 0;
	bmi.bmiHeader.biClrImportant  = 0;

	// Create a palette for the bitmap, and Windows, so that the image
	// will be displayed with the correct colors.
	
	if (iPixelType == PBITS_Y8)
	{
		for (i = 0; i < 256; i++)
		{
			bmi.bmiColors[i].rgbRed =		(BYTE)i;
			bmi.bmiColors[i].rgbGreen =	(BYTE)i;
			bmi.bmiColors[i].rgbBlue =		(BYTE)i;
			bmi.bmiColors[i].rgbReserved = 0;
		}
	}
}

/******************************************************************************
 * Name:         GrayscalePalette
 *-----------------------------------------------------------------------------
 * Description:  Windows is a color system. If you try to display a monochrome
 *               image in a window without changing the palette you will have 
 *               colors in your image. This function establishes a monochrome 
 *               or grayscale palette that you can use for your display window.
 ******************************************************************************/
void GrayscalePalette(HDC hDC, UINT uMessage)
{

	typedef struct {
		 WORD         palVersion; 
		 WORD         palNumEntries; 
		 PALETTEENTRY palPalEntry[256]; 
	} XLOGPALETTE; 

	XLOGPALETTE Palette;
	DWORD dwCounter = 0;
	static HPALETTE hPalette = NULL;


	switch (uMessage)
	{
	case PXC_PALETTE_CREATE:
		Palette.palVersion = 0x300;
		
		// Places 128 gray scale colors in unused entries in the system palette
		// Once these color are in the system palette, colors in other logical 
		// palettes can be matched to these colors. If we are in eight bit color
		// mode the color will match more closely to our gray scale values 
		// eliminating unwanted color artifacts in our image.
		Palette.palNumEntries = 128;
		for (dwCounter = 0; dwCounter < 128; dwCounter++)
		{
			Palette.palPalEntry[dwCounter].peFlags = PC_NOCOLLAPSE;
			Palette.palPalEntry[dwCounter].peRed = (BYTE)dwCounter*2;
			Palette.palPalEntry[dwCounter].peGreen = (BYTE)dwCounter*2;
			Palette.palPalEntry[dwCounter].peBlue = (BYTE)dwCounter*2;
		}
		hPalette = CreatePalette((LOGPALETTE *)&Palette);
		break;

	case PXC_PALETTE_DELETE:
		if(hPalette)
		{
			DeleteObject(hPalette);
			hPalette = NULL;
		}
		break;

	case PXC_PALETTE_REALIZE:
		if(hPalette)
		{
			// The palette must be realized each time it is used. We set
			// the bForceBackground flag false so that logical palette is
			// copied into the device palette when the application is in 
			// the foreground
			SelectPalette(hDC, hPalette, FALSE);
			RealizePalette(hDC);
		}
		break;
	}
}

/******************************************************************************
 * Name:         CreateDisplayBuffer
 *-----------------------------------------------------------------------------
 * Description:  This function creates the buffer you will use later to flip
 *               the image upside down prior to display.
 ******************************************************************************/
int CreateDisplayBuffer(int iWidth, int iHeight, int iPixelType)
{

	// create a buffer from global storage
	gpBits = malloc(iWidth * iHeight * (((iPixelType & 0xFF)+7) >> 3));
	if(gpBits == NULL)
		return FALSE;

	// create the bitmap header once each time a buffer is allocated
	SetBitmapHead(iWidth, iHeight, iPixelType);

	return TRUE;
}

/******************************************************************************
 * Name:         FreeDisplayBuffer
 *-----------------------------------------------------------------------------
 * Description:  This function frees the buffer created by CreateDisplayBuffer.
 ******************************************************************************/
void FreeDisplayBuffer(void)
{
	if(gpBits)
		free(gpBits);
}

