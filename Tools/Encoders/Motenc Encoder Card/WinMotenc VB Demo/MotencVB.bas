Attribute VB_Name = "MotencVB"
Option Explicit

'WINMOTENC.DLL

Declare Function vitalInit Lib "WINMOTENC" () As Long
Declare Function vitalAioReset Lib "WINMOTENC" () As Long
Declare Function vitalQuit Lib "WINMOTENC" () As Long

Declare Function vitalGetMaxEncoders Lib "WINMOTENC" () As Long
Declare Function vitalEncoderRead Lib "WINMOTENC" (ByVal Axis As Long, ByRef pCounts As Long) As Long
Declare Function vitalResetCounter Lib "WINMOTENC" (ByVal Axis As Long) As Long

Declare Function vitalReadIndexLevel Lib "WINMOTENC" (ByVal Axis As Long, ByRef Flag As Long) As Long
Declare Function vitalEncoderIndexModel Lib "WINMOTENC" () As Long
Declare Function vitalEncoderSetIndexModel Lib "WINMOTENC" (ByVal Model As Long) As Long
Declare Function vitalEncoderResetIndex Lib "WINMOTENC" (ByVal Axis As Long) As Long
Declare Function vitalEncoderReadLatch Lib "WINMOTENC" (ByVal Axis As Long, ByRef Flag As Long) As Long

Declare Function vitalReadAnalogInputs Lib "WINMOTENC" (ByVal BankIndex As Long, ByRef AnalogLevel As Double) As Long

Declare Function vitalDacNum Lib "WINMOTENC" () As Long
Declare Function vitalDacWrite Lib "WINMOTENC" (ByVal Axis As Long, ByVal Volts As Double) As Long
Declare Function vitalDacWriteAll Lib "WINMOTENC" (ByVal Max As Long, ByRef Volts As Double) As Long

Declare Function vitalDioRead Lib "WINMOTENC" (ByVal Index As Long, ByRef Value As Long) As Long

Declare Function vitalDioWrite Lib "WINMOTENC" (ByVal Index As Long, ByVal Value As Long) As Long
Declare Function vitalDioReset Lib "WINMOTENC" () As Long
Declare Function vitalDioCheck Lib "WINMOTENC" (ByVal Index As Long, ByRef Value As Long) As Long

Declare Function vitalReadReg Lib "WINMOTENC" (ByVal nReg As Long, ByRef pRegData As Long) As Long
Declare Function vitalWriteReg Lib "WINMOTENC" (ByVal nReg As Long, ByVal RegData As Long) As Long

