VERSION 5.00
Object = "{B3B088D0-73D0-4791-9B45-C4B154DF8823}#1.1#0"; "IMA2_HelperX.ocx"
Begin VB.UserControl ICmpView 
   BackColor       =   &H80000005&
   ClientHeight    =   1020
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   6585
   ScaleHeight     =   1020
   ScaleWidth      =   6585
   Begin IMA2_HelperX.ImageLabel2 imlName 
      Height          =   255
      Left            =   120
      Top             =   120
      Width           =   2775
      _ExtentX        =   4895
      _ExtentY        =   450
      Color1          =   12582912
      Color2          =   8421504
      BackColor       =   -2147483643
      Caption1        =   "Name"
      Caption2        =   "ComponentXXX"
      Indent2         =   80
      Picture         =   "ICmpView.ctx":0000
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin IMA2_HelperX.ImageLabel2 imlMachine 
      Height          =   255
      Left            =   3240
      Top             =   120
      Width           =   2775
      _ExtentX        =   4895
      _ExtentY        =   450
      Color1          =   12582912
      Color2          =   8421504
      BackColor       =   -2147483643
      Caption1        =   "Machine"
      Caption2        =   "KANGAROO"
      Indent2         =   80
      Picture         =   "ICmpView.ctx":015A
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin IMA2_HelperX.ImageLabel2 imlPID 
      Height          =   255
      Left            =   120
      Top             =   360
      Width           =   2775
      _ExtentX        =   4895
      _ExtentY        =   450
      Color1          =   12582912
      Color2          =   8421504
      BackColor       =   -2147483643
      Caption1        =   "PID"
      Caption2        =   "SuperX.CmpX.1"
      Indent2         =   80
      Picture         =   "ICmpView.ctx":02B4
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin IMA2_HelperX.ImageLabel2 imlProcess 
      Height          =   255
      Left            =   3240
      Top             =   360
      Width           =   2775
      _ExtentX        =   4895
      _ExtentY        =   450
      Color1          =   12582912
      Color2          =   8421504
      BackColor       =   -2147483643
      Caption1        =   "Process"
      Caption2        =   "128"
      Indent2         =   80
      Picture         =   "ICmpView.ctx":040E
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin IMA2_HelperX.ImageLabel2 imlThread 
      Height          =   255
      Left            =   3240
      Top             =   600
      Width           =   2775
      _ExtentX        =   4895
      _ExtentY        =   450
      Color1          =   12582912
      Color2          =   8421504
      BackColor       =   -2147483643
      Caption1        =   "Thread"
      Caption2        =   "64"
      Indent2         =   80
      Picture         =   "ICmpView.ctx":0568
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin IMA2_HelperX.ImageLabel2 imlActivated 
      Height          =   255
      Left            =   120
      Top             =   600
      Width           =   2775
      _ExtentX        =   4895
      _ExtentY        =   450
      Color1          =   12582912
      Color2          =   8421504
      BackColor       =   -2147483643
      Caption1        =   "Activated"
      Caption2        =   "TRUE"
      Indent2         =   80
      Picture         =   "ICmpView.ctx":06C2
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin VB.Line Line1 
      BorderColor     =   &H80000004&
      BorderStyle     =   3  'Dot
      X1              =   0
      X2              =   55200
      Y1              =   0
      Y2              =   0
   End
End
Attribute VB_Name = "ICmpView"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Private Sub UserControl_Resize()

    On Error Resume Next
    
    Dim SW  As Integer
    Dim SWA As Integer
    Dim SWB As Integer
    
    SW = UserControl.ScaleWidth - (2 * imlName.Left)
    SWA = SW * 0.55
    SWB = SW * 0.45
    
    imlName.Width = SWA
    imlPID.Width = SWA
    imlActivated.Width = SWA

    imlMachine.Left = (2 * imlName.Left) + SWA
    imlProcess.Left = (2 * imlName.Left) + SWA
    imlThread.Left = (2 * imlName.Left) + SWA

    imlMachine.Width = SWB
    imlProcess.Width = SWB
    imlThread.Width = SWB

End Sub

Public Property Get CName() As String
    CName = imlName.Caption2
End Property

Public Property Let CName(NV As String)
    imlName.Caption2 = NV
End Property

Public Property Get PID() As String
    PID = imlPID.Caption2
End Property

Public Property Let PID(NV As String)
    imlPID.Caption2 = NV
End Property

Public Property Get Machine() As String
    Machine = imlMachine.Caption2
End Property

Public Property Let Machine(NV As String)
    imlMachine.Caption2 = NV
End Property
        
Public Property Get Process() As Long
    Process = Val(imlProcess.Caption2)
End Property

Public Property Let Process(NV As Long)
    imlProcess.Caption2 = "" & NV
End Property

Public Property Get Thread() As Long
    Thread = Val(imlThread.Caption2)
End Property

Public Property Let Thread(NV As Long)
    imlThread.Caption2 = "" & NV
End Property

Public Property Get Activated() As Boolean
    Activated = Val(imlActivated.Caption2)
End Property

Public Property Let Activated(NV As Boolean)
    imlActivated.Caption2 = "" & NV
End Property

