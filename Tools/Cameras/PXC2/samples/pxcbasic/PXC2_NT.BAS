Attribute VB_Name = "pxc"
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' PXC_V4.BAS : Visual Basic 4 declarations for  PXC series                '
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'               Model Numbers (added June 2000)
Global Const PXC200_LC = &H1
Global Const PXC200_F = &H2
Global Const SP2019 = &H4
Global Const PXC200_LC_2 = &H8
Global Const PXC200_F_2 = &H10

'               Flags

Global Const EITHER = &H3
Global Const FIELD0 = &H1
Global Const FIELD1 = &H2
Global Const IMMEDIATE = &H4
Global Const QUEUED = &H8
Global Const SINGLE_FLD = &H10


'               Trigger Types

Global Const LATCH_RISING = &H1
Global Const LATCH_FALLING = &H2
Global Const LATCH_CHANGE = &H3
Global Const IO_INPUT = &H4
Global Const IO_OUTPUT = &H5


'               Error Numbers

Global Const ERR_NONE = &H0
Global Const ERR_NOT_VALID = &H1
Global Const ERR_CORRUPT = &H2
Global Const ERR_IO_FAIL = &H4
Global Const WARN_OVERFLOW = &H8

'               Filter Control Flags
Global Const COMB_FILTER = &H1
Global Const SVIDEO = &H2
Global Const NOTCH_FILTER = &H4
Global Const BW_DETECT = &H8
Global Const AGC = &H10

Global Const GAMMA_CORRECT = &H2
Global Const CORE_8 = &H10
Global Const CORE_16 = &H20
Global Const CORE_32 = &H30
Global Const LOW_FILT_AUTO = &H800
Global Const LOW_FILT_1 = &H900
Global Const LOW_FILT_2 = &HA00
Global Const LOW_FILT_3 = &HB00
Global Const PEAK_FILT_0 = &HC00
Global Const PEAK_FILT_1 = &HD00
Global Const PEAK_FILT_2 = &HE00
Global Const PEAK_FILT_3 = &HF00


'               Video Detect Types
Global Const AUTO_FORMAT = 0
Global Const NTSC_FORMAT = 1
Global Const NTSCJ_FORMAT = 2
Global Const PAL_FORMAT = 3
Global Const PALM_FORMAT = 4
Global Const PALN_FORMAT = 5
Global Const SECAM_FORMAT = 6


'               Setup Functions

Declare Function PXC_OpenLibrary Lib "pxc_nt.dll" Alias "OpenLibrary" (ByVal i As Long, ByVal s As Integer) As Integer
Declare Sub PXC_CloseLibrary Lib "pxc_nt.dll" Alias "CloseLibrary" (ByVal i As Long)



' ----------General Device Maintenance functions--------------------
Declare Function PXC_AllocateFG Lib "pxc_nt.dll" Alias "AllocateFG" (ByVal n As Integer) As Long
Declare Sub PXC_FreeFG Lib "pxc_nt.dll" Alias "FreeFG" (ByVal fgh As Long)
Declare Function PXC_ReadRevision Lib "pxc_nt.dll" Alias "ReadRevision" (ByVal fgh As Long) As Integer
Declare Sub PXC_Reset Lib "pxc_nt.dll" Alias "Reset" (ByVal fgh As Long)
Declare Function PXC_CheckError Lib "pxc_nt.dll" Alias "CheckError" (ByVal fgh As Long) As Long
Declare Function PXC_ReadProtection Lib "pxc_nt.dll" Alias "ReadProtection" (ByVal fgh As Long) As Integer
Declare Function PXC_ReadSerial Lib "pxc_nt.dll" Alias "ReadSerial" (ByVal fgh As Long) As Long

' ----------Basic Digital I/O Functions-----------------------------
Declare Function PXC_GetIOType Lib "pxc_nt.dll" Alias "GetIOType" (ByVal fgh As Long, ByVal n As Integer) As Integer
Declare Function PXC_SetIOType Lib "pxc_nt.dll" Alias "SetIOType" (ByVal fgh As Long, ByVal n As Integer, ByVal tp As Integer) As Integer
Declare Function PXC_ReadIO Lib "pxc_nt.dll" Alias "ReadIO" (ByVal fgh As Long) As Long
Declare Function PXC_WriteImmediateIO Lib "pxc_nt.dll" Alias "WriteImmediateIO" (ByVal fgh As Long, ByVal mask As Long, ByVal state As Long) As Integer

' ----------Basic Frame Grabber Functions---------------------------
Declare Function PXC_Grab Lib "pxc_nt.dll" Alias "Grab" (ByVal fgh As Long, ByVal frh As Long, ByVal flags As Integer) As Long
Declare Function PXC_Wait Lib "pxc_nt.dll" Alias "Wait" (ByVal fgh As Long, ByVal flags As Integer) As Long
Declare Function PXC_WaitVB Lib "pxc_nt.dll" Alias "WaitVB" (ByVal fgh As Long) As Integer
Declare Sub PXC_WaitFinished Lib "pxc_nt.dll" Alias "WaitFinished" (ByVal fgh As Long, ByVal qh As Long)
Declare Function PXC_IsFinished Lib "pxc_nt.dll" Alias "IsFinished" (ByVal fgh As Long, ByVal qh As Long) As Integer
Declare Sub PXC_KillQueue Lib "pxc_nt.dll" Alias "KillQueue" (ByVal fgh As Long)
Declare Function PXC_AllocateBuffer Lib "pxc_nt.dll" Alias "AllocateBuffer" (ByVal dx As Integer, ByVal dy As Integer, ByVal tp As Integer) As Long
Declare Sub PXC_FreeFrame Lib "pxc_nt.dll" Alias "FreeFrame" (ByVal frh As Long)
Declare Function PXC_SetFieldCount Lib "pxc_nt.dll" Alias "SetFieldCount" (ByVal fgh As Long, ByVal c As Long) As Integer
Declare Function PXC_GetFieldCount Lib "pxc_nt.dll" Alias "GetFieldCount" (ByVal fgh As Long) As Long

' ----------Optional FG Functions-----------------------------------
Declare Function PXC_GrabContinuous Lib "pxc_nt.dll" Alias "GrabContinuous" (ByVal fgh As Long, ByVal frh As Long, ByVal state As Integer, ByVal flags As Integer) As Long
Declare Function PXC_VideoType Lib "pxc_nt.dll" Alias "VideoType" (ByVal fgh As Long) As Integer
Declare Function PXC_SetXResolution Lib "pxc_nt.dll" Alias "SetXResolution" (ByVal fgh As Long, ByVal rez As Integer) As Integer
Declare Function PXC_SetYResolution Lib "pxc_nt.dll" Alias "SetYResolution" (ByVal fgh As Long, ByVal rez As Integer) As Integer
Declare Function PXC_SetWidth Lib "pxc_nt.dll" Alias "SetWidth" (ByVal fgh As Long, ByVal w As Integer) As Integer
Declare Function PXC_SetHeight Lib "pxc_nt.dll" Alias "SetHeight" (ByVal fgh As Long, ByVal h As Integer) As Integer
Declare Function PXC_SetLeft Lib "pxc_nt.dll" Alias "SetLeft" (ByVal fgh As Long, ByVal l As Integer) As Integer
Declare Function PXC_SetTop Lib "pxc_nt.dll" Alias "SetTop" (ByVal fgh As Long, ByVal t As Integer) As Integer
Declare Function PXC_GetXResolution Lib "pxc_nt.dll" Alias "GetXResolution" (ByVal fgh As Long) As Integer
Declare Function PXC_GetYResolution Lib "pxc_nt.dll" Alias "GetYResolution" (ByVal fgh As Long) As Integer
Declare Function PXC_GetWidth Lib "pxc_nt.dll" Alias "GetWidth" (ByVal fgh As Long) As Integer
Declare Function PXC_GetHeight Lib "pxc_nt.dll" Alias "GetHeight" (ByVal fgh As Long) As Integer
Declare Function PXC_GetLeft Lib "pxc_nt.dll" Alias "GetLeft" (ByVal fgh As Long) As Integer
Declare Function PXC_GetTop Lib "pxc_nt.dll" Alias "GetTop" (ByVal fgh As Long) As Integer
Declare Function PXC_WaitAnyEvent Lib "pxc_nt.dll" Alias "WaitAnyEvent" (ByVal fgh As Long, ByVal ioh As Long, ByVal mask As Long, ByVal state As Long, ByVal flags As Integer) As Long
Declare Function PXC_WaitAllEvents Lib "pxc_nt.dll" Alias "WaitAllEvents" (ByVal fgh As Long, ByVal ioh As Long, ByVal mask As Long, ByVal state As Long, ByVal flags As Integer) As Long
Declare Function PXC_SwitchGrab Lib "pxc_nt.dll" Alias "SwitchGrab" (ByVal fgh As Long, ByVal f0 As Long, ByVal f1 As Long, ByVal f2 As Long, ByVal f3 As Long, ByVal flags As Integer) As Long
Declare Function PXC_SwitchCamera Lib "pxc_nt.dll" Alias "SwitchCamera" (ByVal fgh As Long, ByVal flags As Integer) As Long
Declare Function PXC_GetSwitch Lib "pxc_nt.dll" Alias "GetSwitch" (ByVal fgh As Long) As Integer
Declare Function PXC_SetCamera Lib "pxc_nt.dll" Alias "SetCamera" (ByVal fgh As Long, ByVal n As Integer, ByVal flags As Integer) As Long
Declare Function PXC_GetCamera Lib "pxc_nt.dll" Alias "GetCamera" (ByVal fgh As Long) As Integer
Declare Function PXC_SetContrast Lib "pxc_nt.dll" Alias "SetContrast" (ByVal fgh As Long, ByVal c As Single, ByVal flags As Integer) As Long
Declare Function PXC_SetBrightness Lib "pxc_nt.dll" Alias "SetBrightness" (ByVal fgh As Long, ByVal b As Single, ByVal flags As Integer) As Long
Declare Function PXC_GetContrast Lib "pxc_nt.dll" Alias "GetContrast" (ByVal fgh As Long) As Single
Declare Function PXC_GetBrightness Lib "pxc_nt.dll" Alias "GetBrightness" (ByVal fgh As Long) As Single


' ---------- HSV custom functions---------------------------

Declare Function PXC_SetHue Lib "pxc_nt.dll" Alias "SetHue" (ByVal fgh As Long, ByVal h As Single, ByVal flags As Integer) As Long
Declare Function PXC_SetSaturation Lib "pxc_nt.dll" Alias "SetSaturation" (ByVal fgh As Long, ByVal s As Single, ByVal flags As Integer) As Long
Declare Function PXC_GetHue Lib "pxc_nt.dll" Alias "GetHue" (ByVal fgh As Long) As Single
Declare Function PXC_GetSaturation Lib "pxc_nt.dll" Alias "GetSaturation" (ByVal fgh As Long) As Single

' ----------- These are PXC custom features -------------
Declare Function PXC_SetPixelFormat Lib "pxc_nt.dll" Alias "SetPixelFormat" (ByVal fgh As Long, ByVal tp As Integer) As Integer

Declare Function PXC_SetVideoLevel Lib "pxc_nt.dll" Alias "SetVideoLevel" (ByVal fgh As Long, ByVal white As Single) As Single
Declare Function PXC_GetVideoLevel Lib "pxc_nt.dll" Alias "GetVideoLevel" (ByVal fgh As Long) As Single

Declare Function PXC_SetChromaControl Lib "pxc_nt.dll" Alias "SetChromaControl" (ByVal fgh As Long, ByVal cf As Integer) As Integer
Declare Function PXC_GetChromaControl Lib "pxc_nt.dll" Alias "GetChromaControl" (ByVal fgh As Long) As Integer
Declare Function PXC_SetLumaControl Lib "pxc_nt.dll" Alias "SetLumaControl" (ByVal fgh As Long, ByVal cf As Integer) As Integer
Declare Function PXC_GetLumaControl Lib "pxc_nt.dll" Alias "GetLumaControl" (ByVal fgh As Long) As Integer
Declare Function PXC_SetVideoDetect Lib "pxc_nt.dll" Alias "SetVideoDetect" (ByVal fgh As Long, ByVal tp As Integer) As Integer
Declare Function PXC_GetVideoDetect Lib "pxc_nt.dll" Alias "GetVideoDetect" (ByVal fgh As Long) As Integer

'Control Package functions
Declare Function PXC_SetStrobePeriod Lib "pxc_nt.dll" Alias "SetStrobePeriod" (ByVal fgh As Long, ByVal n As Integer, ByVal p As Single) As Single
Declare Function PXC_GetStrobePeriod Lib "pxc_nt.dll" Alias "GetStrobePeriod" (ByVal fgh As Long, ByVal n As Integer) As Single
Declare Function PXC_SetHoldoffStart Lib "pxc_nt.dll" Alias "SetHoldoffStart" (ByVal fgh As Long, ByVal field_num As Integer, ByVal start As Integer) As Integer
Declare Function PXC_SetHoldoffWidth Lib "pxc_nt.dll" Alias "SetHoldoffWidth" (ByVal fgh As Long, ByVal field_num As Integer, ByVal width As Integer) As Integer
Declare Function PXC_SetHoldoffMask Lib "pxc_nt.dll" Alias "SetHoldoffMask" (ByVal fgh As Long, ByVal mask As Long) As Integer
Declare Function PXC_GetHoldoffStart Lib "pxc_nt.dll" Alias "GetHoldoffStart" (ByVal fgh As Long, ByVal field_num As Integer) As Integer
Declare Function PXC_GetHoldoffWidth Lib "pxc_nt.dll" Alias "GetHoldoffWidth" (ByVal fgh As Long, ByVal field_num As Integer) As Integer
Declare Function PXC_GetHoldoffMask Lib "pxc_nt.dll" Alias "GetHoldoffMask" (ByVal fgh As Long) As Long
Declare Function PXC_SetDoubleStrobe Lib "pxc_nt.dll" Alias "SetDoubleStrobe" (ByVal fgh As Long, ByVal n As Integer, ByVal p As Single) As Single
Declare Function PXC_GetDoubleStrobe Lib "pxc_nt.dll" Alias "GetDoubleStrobe" (ByVal fgh As Long, ByVal n As Integer) As Single
Declare Function PXC_TriggerStrobe Lib "pxc_nt.dll" Alias "TriggerStrobe" (ByVal fgh As Long, ByVal n As Integer, ByVal mask As Long) As Integer
Declare Function PXC_SyncStrobe Lib "pxc_nt.dll" Alias "SyncStrobe" (ByVal fgh As Long, ByVal n As Integer, ByVal field_num As Integer, ByVal line As Integer) As Integer
Declare Function PXC_FireStrobe Lib "pxc_nt.dll" Alias "FireStrobe" (ByVal fgh As Long, ByVal mask As Long) As Integer
Declare Function PXC_SetDecisionPoint Lib "pxc_nt.dll" Alias "SetDecisionPoint" (ByVal fgh As Long, ByVal field_num As Integer, ByVal line As Integer) As Integer
Declare Function PXC_GetDecisionPoint Lib "pxc_nt.dll" Alias "GetDecisionPoint" (ByVal fgh As Long, ByVal field_num As Integer) As Integer
Declare Function PXC_SetDebounce Lib "pxc_nt.dll" Alias "SetDebounce" (ByVal fgh As Long, ByVal n As Integer, ByVal db As Integer) As Integer
Declare Function PXC_GetDebounce Lib "pxc_nt.dll" Alias "GetDebounce" (ByVal fgh As Long, ByVal n As Integer) As Integer

'------------- New functions added to unified driver ----------
Declare Function PXC_GetModelNumber Lib "pxc_nt.dll" Alias "GetModelNumber" (ByVal fgh As Long) As Integer


