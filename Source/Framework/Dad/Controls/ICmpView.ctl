VERSION 5.00
Object = "{7B492EBB-3B8A-4D7E-9021-86BB71534052}#1.1#0"; "IMA2_HelperX.ocx"
Begin VB.UserControl CmpView 
   BackColor       =   &H80000005&
   ClientHeight    =   1020
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   6585
   ScaleHeight     =   68
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   439
   Begin IMA2_HelperX.ImageLabel imlName 
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
   Begin IMA2_HelperX.ImageLabel imlMachine 
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
   Begin IMA2_HelperX.ImageLabel imlPID 
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
   Begin IMA2_HelperX.ImageLabel imlProcess 
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
   Begin IMA2_HelperX.ImageLabel imlThread 
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
   Begin IMA2_HelperX.ImageLabel imlActivated 
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
      X2              =   3680
      Y1              =   0
      Y2              =   0
   End
End
Attribute VB_Name = "CmpView"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

'***********************************************************************************************
    
    Public Enum CV_Style
        CV_Horizontal = 0
        CV_Vertical = 1
    End Enum
    
'***********************************************************************************************
    
    Dim m_DI As IMA2_DistributingInfo
    Dim m_Style As CV_Style
    Dim C(0 To 5) As Control

'***********************************************************************************************

    Public Property Get BorderStyle() As mscomctllib.BorderStyleConstants
        BorderStyle = UserControl.BorderStyle
    End Property

    Public Property Let BorderStyle(NV As mscomctllib.BorderStyleConstants)
        UserControl.BorderStyle = NV
        Line1.Visible = (NV = ccNone)
    End Property

    Public Property Get Info() As Variant
        Info = m_DI
    End Property
    
    'Yes, this is an absolute hack because VB wouldn't let me use Property Let with this structure.
    Public Property Let Info(NV As Variant)
        With NV
            m_DI = NV
            imlName.Caption2 = .Name
            imlPID.Caption2 = .PID
            imlMachine.Caption2 = .Machine
            imlProcess.Caption2 = "" & .Process
            imlThread.Caption2 = "" & .Thread
        End With
    End Property
    
    Public Property Let Activated(NV As Boolean)
        imlActivated.Caption2 = "" & NV
    End Property
    
    Public Property Get Activated() As Boolean
        Activated = LCase(imlActivated.Caption2) = "true"
    End Property
    
    Public Property Get Style() As CV_Style
        Style = m_Style
    End Property
    
    Public Property Let Style(NV As CV_Style)
        m_Style = NV
        UserControl_Resize
    End Property

'***********************************************************************************************
    
    Private Sub UserControl_Initialize()
        Set C(0) = imlName
        Set C(1) = imlPID
        Set C(2) = imlActivated
        Set C(3) = imlMachine
        Set C(4) = imlProcess
        Set C(5) = imlThread
    End Sub
    
    Private Sub UserControl_Resize()
        On Error Resume Next
        If m_Style = CV_Horizontal Then
            ResizeHorizontal
        Else
            ResizeVertical
        End If
    End Sub

    Private Sub UserControl_ReadProperties(PropBag As PropertyBag)
        Style = PropBag.ReadProperty("Style", 0)
        BorderStyle = PropBag.ReadProperty("BStyle", 1)
    End Sub

    Private Sub UserControl_WriteProperties(PropBag As PropertyBag)
        Call PropBag.WriteProperty("Style", Style, 0)
        Call PropBag.WriteProperty("BStyle", BorderStyle, 1)
    End Sub

'***********************************************************************************************
    
    Private Sub ResizeVertical()
        Dim I As Integer
        Dim T As Integer
        T = 8
        For I = 0 To 5
            C(I).Move 8, T, UserControl.ScaleWidth - 16, 16
            T = T + 18
            If I = 2 Then T = T + 8
        Next
    End Sub
    
    Private Sub ResizeHorizontal()
    
        Dim SWA As Integer
        Dim SWB As Integer
        Dim I As Integer
        
        SWA = UserControl.ScaleWidth * 0.55
        SWB = UserControl.ScaleWidth * 0.45
        
        For I = 0 To 2
            C(I).Move 8, 8 + (I * 16), SWA - 16, 16
        Next
        
        For I = 3 To 5
            C(I).Move SWA + 16, 8 + ((I - 3) * 16), SWB - 8, 16
        Next I
    
    End Sub
