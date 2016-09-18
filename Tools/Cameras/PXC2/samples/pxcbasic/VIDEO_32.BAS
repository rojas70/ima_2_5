Attribute VB_Name = "Video_32.bas"


Declare Sub pxPaintDisplay Lib "video_32.dll" (ByVal hDC As Long, ByVal frm As Long, ByVal x As Long, ByVal y As Long, ByVal dx As Long, ByVal dy As Long)
Declare Sub pxSetWindowSize Lib "video_32.dll" (ByVal x As Long, ByVal y As Long, ByVal dx As Long, ByVal dy As Long)
