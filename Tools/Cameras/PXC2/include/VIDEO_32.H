
#include "iframe.h"

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef __VIDEODLL__
#define _VIDEOAPI __declspec(dllexport)
#else
#define _VIDEOAPI __declspec(dllimport)
#endif

void _VIDEOAPI _stdcall
		pxPaintDisplay(HDC hdc, FRAME __PX_FAR *frm, int x, int y, int dx, int dy);
void _VIDEOAPI _stdcall pxSetWindowSize(int x, int y, int dx, int dy);


#ifdef  __cplusplus
}
#endif

