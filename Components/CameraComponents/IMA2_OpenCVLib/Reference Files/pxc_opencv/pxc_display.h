/******************************************************************************
 * PXC_DISPLAY.H
 * 
 * Copyright (c) 2001 by Imagenation
 *
 * This header file belongs to the PXC_DISPLAY.C file. If your program uses
 * the pxc_display.c file for display, you will need to include this header.
 ******************************************************************************/
#ifndef __IMAGENATION_PXCDISPLAY_H_
	#define __IMAGENATION_PXCDISPLAY_H_
	#ifdef __cplusplus
		extern "C" {
	#endif

	#include <windows.h>
	#include "iframe.h"
	#include "pxc.h"

	void FreeDisplayBuffer(void);
	int CreateDisplayBuffer(int iWidth, int iHeight, int iPixelType);
	void GrayscalePalette(HDC hDC, UINT uMessage);
	void SetBitmapHead(int iWidth, int iHeight, int iPixelType);
	void ShowFrame(FRAME __PX_FAR *pFrame, HDC hDC, int iWidth, int iHeight, int iPixelType);

	enum PALETTEmsg {PXC_PALETTE_CREATE, PXC_PALETTE_DELETE, PXC_PALETTE_REALIZE};

	#ifdef __cplusplus
		}
	#endif
#endif

