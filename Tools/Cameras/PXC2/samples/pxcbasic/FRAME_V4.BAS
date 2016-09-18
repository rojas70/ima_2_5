Attribute VB_Name = "Frame"



Declare Function FRAME_AllocateMemoryFrame Lib "frame_32.dll" Alias "AllocateMemoryFrame" (ByVal dx As Integer, ByVal dy As Integer, ByVal tp As Integer) As Long
Declare Function FRAME_AllocateFlatFrame Lib "frame_32.dll" Alias "AllocateFlatFrame" (ByVal dx As Integer, ByVal dy As Integer, ByVal tp As Integer) As Long
Declare Function FRAME_AllocateAddress Lib "frame_32.dll" Alias "AllocateAddress" (ByVal physaddress As Long, ByVal dx As Integer, ByVal dy As Integer, ByVal tp As Integer) As Long
Declare Function FRAME_AliasFrame Lib "frame_32.dll" Alias "AliasFrame" (ByVal f As Long, ByVal x0 As Integer, ByVal y0 As Integer, ByVal dx As Integer, ByVal dy As Integer, ByVal tp As Integer) As Long
Declare Sub FRAME_FreeFrame Lib "frame_32.dll" Alias "FreeFrame" (ByVal f As Long)
Declare Function FRAME_WriteBin Lib "frame_32.dll" Alias "WriteBin" (ByVal f As Long, ByVal filename As String, ByVal overwrite As Integer) As Integer
Declare Function FRAME_ReadBin Lib "frame_32.dll" Alias "ReadBin" (ByVal f As Long, ByVal filename As String) As Integer
Declare Function FRAME_GetPixel Lib "frame_32.dll" Alias "GetPixel" (ByVal f As Long, pixel As Any, ByVal x As Integer, ByVal y As Integer) As Integer
Declare Function FRAME_PutPixel Lib "frame_32.dll" Alias "PutPixel" (pixel As Any, ByVal f As Long, ByVal x As Integer, ByVal y As Integer) As Integer
Declare Function FRAME_GetRow Lib "frame_32.dll" Alias "GetRow" (ByVal f As Long, buf As Any, ByVal row As Integer) As Integer
Declare Function FRAME_PutRow Lib "frame_32.dll" Alias "PutRow" (buf As Any, ByVal f As Long, ByVal row As Integer) As Integer
Declare Function FRAME_GetColumn Lib "frame_32.dll" Alias "GetColumn" (ByVal f As Long, buf As Any, ByVal column As Integer) As Integer
Declare Function FRAME_PutColumn Lib "frame_32.dll" Alias "PutColumn" (buf As Any, ByVal f As Long, ByVal column As Integer) As Integer
Declare Function FRAME_GetRectangle Lib "frame_32.dll" Alias "GetRectangle" (ByVal f As Long, buf As Any, ByVal x0 As Integer, ByVal y0 As Integer, ByVal dx As Integer, ByVal dy As Integer) As Integer
Declare Function FRAME_PutRectangle Lib "frame_32.dll" Alias "PutRectangle" (buf As Any, ByVal f As Long, ByVal x0 As Integer, ByVal y0 As Integer, ByVal dx As Integer, ByVal dy As Integer) As Integer
Declare Function FRAME_CopyFrame Lib "frame_32.dll" Alias "CopyFrame" (ByVal source As Long, ByVal sourcex As Integer, ByVal sourcey As Integer, ByVal dest As Long, ByVal destx As Integer, ByVal desty As Integer, ByVal dx As Integer, ByVal dy As Integer) As Integer
Declare Function FRAME_ExtractPlane Lib "frame_32.dll" Alias "ExtractPlane" (ByVal f As Long, ByVal plane As Integer) As Long
Declare Function FRAME_WriteBMP Lib "frame_32.dll" Alias "WriteBMP" (ByVal f As Long, ByVal filename As String, ByVal overwrite As Integer) As Integer
Declare Function FRAME_ReadBMP Lib "frame_32.dll" Alias "ReadBMP" (ByVal f As Long, ByVal filename As String) As Integer
Declare Function FRAME_FrameBuffer Lib "frame_32.dll" Alias "FrameBuffer" (ByVal f As Long) As Long
Declare Function FRAME_FrameAddress Lib "frame_32.dll" Alias "FrameAddress" (ByVal f As Long) As Long
Declare Function FRAME_FrameWidth Lib "frame_32.dll" Alias "FrameWidth" (ByVal f As Long) As Integer
Declare Function FRAME_FrameHeight Lib "frame_32.dll" Alias "FrameHeight" (ByVal f As Long) As Integer
Declare Function FRAME_FrameType Lib "frame_32.dll" Alias "FrameType" (ByVal f As Long) As Integer

'---------- some common image data types ----------
Global Const PBITS_Y8 = &H8
Global Const PBITS_Y16 = &H10
Global Const PBITS_Yf = &H120
Global Const PBITS_RGB15 = &H60F
Global Const PBITS_RGB16 = &H210
Global Const PBITS_RGB24 = &H218
Global Const PBITS_RGB32 = &H620
Global Const PBITS_RGBf = &H360
Global Const PBITS_YUV422 = &H810
Global Const PBITS_YUV444 = &H818
Global Const PBITS_YUV422P = &H1810
Global Const PBITS_YUV444P = &H1818

' --------- masks for parsing pixel types ------------
Global Const PBITS_FLOAT = &H100
Global Const PBITS_BITS = &HFF
Global Const PBITS_RGB = &H200
Global Const PBITS_ALPHA = &H400
Global Const PBITS_YUV = &H800
Global Const PBITS_PLANES = &H1000

'----------- File I/O return values -----------------
Global Const SUCCESS = 0
Global Const FILE_EXISTS = 2
Global Const FILE_OPEN_ERROR = 3
Global Const BAD_WRITE = 4
Global Const BAD_READ = 5
Global Const WRONG_BITS = 8
Global Const FRAME_SIZE = 9
Global Const BAD_FILE = 11
Global Const INVALID_FRAME = 12


Declare Function FRAME_OpenLibrary Lib "frame_32.dll" Alias "OpenLibrary" (ByVal i As Long, ByVal s As Integer) As Integer
Declare Sub FRAME_CloseLibrary Lib "frame_32.dll" Alias "CloseLibrary" (ByVal i As Long)


Type PIX_RGB24
    blue As Byte
    green As Byte
    red As Byte
End Type

Type PIX_RGB32
    blue As Byte
    green As Byte
    red As Byte
    alpha As Byte
End Type

Type PIX_RGBf
    blue As Single
    green As Single
    red As Single
End Type

