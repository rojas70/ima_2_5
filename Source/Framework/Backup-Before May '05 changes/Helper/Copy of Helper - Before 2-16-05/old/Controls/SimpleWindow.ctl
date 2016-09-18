VERSION 5.00
Begin VB.UserControl SimpleWindow 
   ClientHeight    =   5100
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   7125
   ScaleHeight     =   340
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   475
   Begin IMA2_HelperX.SimpleSizer sms 
      Align           =   1  'Align Top
      Height          =   3495
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   7125
      _ExtentX        =   12568
      _ExtentY        =   6165
      Begin VB.CommandButton cmdMin 
         Caption         =   "_"
         BeginProperty Font 
            Name            =   "Terminal"
            Size            =   4.5
            Charset         =   255
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   195
         Left            =   2640
         Style           =   1  'Graphical
         TabIndex        =   1
         TabStop         =   0   'False
         Top             =   90
         Width           =   210
      End
      Begin VB.Image imgIcon 
         Height          =   240
         Left            =   80
         Picture         =   "SimpleWindow.ctx":0000
         Top             =   60
         Width           =   240
      End
      Begin VB.Label lblCaption 
         BackColor       =   &H8000000D&
         BackStyle       =   0  'Transparent
         Caption         =   "Caption"
         ForeColor       =   &H8000000E&
         Height          =   225
         Left            =   330
         TabIndex        =   2
         Top             =   75
         Width           =   20550
      End
      Begin VB.Shape shpCaption 
         BorderColor     =   &H8000000D&
         FillColor       =   &H8000000D&
         FillStyle       =   0  'Solid
         Height          =   300
         Left            =   0
         Top             =   0
         Width           =   2.45745e5
      End
      Begin VB.Line LineBevel2 
         BorderColor     =   &H80000014&
         X1              =   0
         X2              =   48000
         Y1              =   330
         Y2              =   330
      End
      Begin VB.Line LineBevel1 
         BorderColor     =   &H80000010&
         X1              =   0
         X2              =   48000
         Y1              =   320
         Y2              =   320
      End
   End
End
Attribute VB_Name = "SimpleWindow"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True

Option Explicit

'***************************************************************************************
'   Public Events
'***************************************************************************************

    Public Event OnMinimize()
    Public Event OnResize()
    
    Public Event CaptionDblClick()
    Public Event IconDblClick()
    Public Event IconClick()

    Public Event MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
    Public Event MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
    Public Event MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    
    Public Event KeyDown(KeyCode As Integer, Shift As Integer)
    Public Event KeyPress(KeyAscii As Integer)
    Public Event KeyUp(KeyCode As Integer, Shift As Integer)

'***************************************************************************************
'   Member Variables
'***************************************************************************************
    
    Dim m_SX As Single, m_SY As Single
    Dim m_SL As Single, m_ST As Single

    Dim m_Collapsed     As Boolean
    Dim m_SavedHeight   As Single

    Dim m_ControlObject As Object

'***************************************************************************************
'   Public Interface
'***************************************************************************************
    
    Public Function CreateControl(PID As String, Key As String) As Object
        On Error Resume Next
        Set m_ControlObject = UserControl.Controls.Add(PID, Key)
        If Err = 0 Then
            Set m_ControlObject.Container = sms
            m_ControlObject.Move 70, 390
        End If
        Set CreateControl = m_ControlObject
    End Function

    Private Sub imgIcon_Click()
        RaiseEvent IconClick
    End Sub

    Private Sub imgIcon_DblClick()
        RaiseEvent IconDblClick
    End Sub

'***************************************************************************************
'   Control Events
'***************************************************************************************
    
    Private Sub lblCaption_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
        If Button And vbLeftButton Then
            m_SX = (X / Screen.TwipsPerPixelX)
            m_SY = (Y / Screen.TwipsPerPixelY)
            m_SL = UserControl.Extender.Left
            m_ST = UserControl.Extender.Top
            lblCaption.MousePointer = 15
        End If
        
    End Sub

    Private Sub lblCaption_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    
        If Button And vbLeftButton Then
                Dim NewL, NewT
                With UserControl.Extender
                    NewL = m_SL + ((X / Screen.TwipsPerPixelX) - m_SX)
                    NewT = m_ST + ((Y / Screen.TwipsPerPixelX) - m_SY)
                    .Move NewL, NewT
                End With
                lblCaption.MousePointer = 0
        End If
    
    End Sub

    Private Sub cmdMin_Click()
        RaiseEvent OnMinimize
    End Sub
    
    Private Sub cmdMin_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
        UserControl.SetFocus
    End Sub

    Private Sub lbl_DblClick()
        RaiseEvent CaptionDblClick
    End Sub

    Private Sub sms_OnFinishResize(L As Single, T As Single, W As Single, H As Single)
    
        With UserControl.Extender
            .Move .Left + L, .Top + T, W, H
        End With
        RaiseEvent OnResize
    
    End Sub
    
'***************************************************************************************
'   Usercontrol Events
'***************************************************************************************
    
    Private Sub UserControl_Resize()
    
        sms.Height = UserControl.ScaleHeight
        cmdMin.Left = UserControl.Width - cmdMin.Width - cmdMin.Top + 10
    
    End Sub

    Private Sub UserControl_ReadProperties(PropBag As PropertyBag)
        Caption = PropBag.ReadProperty("Caption", "Caption")
        Set Icon = PropBag.ReadProperty("Icon", imgIcon.Picture)
        MinString = PropBag.ReadProperty("MinString", "_")
        MinVisible = PropBag.ReadProperty("MinVisible", True)
        Sizeable = PropBag.ReadProperty("Sizeable", True)
        m_SavedHeight = PropBag.ReadProperty("SavedHeight", 200)
        m_Collapsed = PropBag.ReadProperty("Collapsed", False)
    End Sub
    
    Private Sub UserControl_WriteProperties(PropBag As PropertyBag)
        Call PropBag.WriteProperty("Caption", Caption, "Caption")
        Call PropBag.WriteProperty("Icon", imgIcon.Picture)
        Call PropBag.WriteProperty("MinString", MinString, "_")
        Call PropBag.WriteProperty("MinVisible", MinVisible, True)
        Call PropBag.WriteProperty("Sizeable", Sizeable, True)
        Call PropBag.WriteProperty("SavedHeight", m_SavedHeight, 200)
        Call PropBag.WriteProperty("Collapsed", m_Collapsed, False)
    End Sub


    Private Sub UserControl_EnterFocus()
        shpCaption.FillColor = QBColor(1)
        shpCaption.BorderColor = shpCaption.FillColor
        lblCaption.ForeColor = QBColor(15)
        UserControl.Extender.ZOrder 0
    End Sub
    
    Private Sub UserControl_ExitFocus()
        shpCaption.FillColor = QBColor(8)
        shpCaption.BorderColor = shpCaption.FillColor
        lblCaption.ForeColor = QBColor(7)
    End Sub
    
    Private Sub UserControl_KeyDown(KeyCode As Integer, Shift As Integer)
        RaiseEvent KeyDown(KeyCode, Shift)
    End Sub

    Private Sub UserControl_KeyPress(KeyAscii As Integer)
        RaiseEvent KeyPress(KeyAscii)
    End Sub
    
    Private Sub UserControl_KeyUp(KeyCode As Integer, Shift As Integer)
        RaiseEvent KeyUp(KeyCode, Shift)
    End Sub

'***************************************************************************************
'   Redundant Control Properties
'***************************************************************************************
    
    Public Property Get Icon() As StdPicture
        Set Icon = imgIcon.Picture
    End Property
    
    Public Property Set Icon(NV As StdPicture)
        Set imgIcon.Picture = NV
    End Property
    
    Public Property Get ToolTipText() As String
        ToolTipText = lblCaption.ToolTipText
    End Property
    
    Public Property Let ToolTipText(NV As String)
        lblCaption.ToolTipText = NV
    End Property
    
    Public Property Get MinString() As String
        MinString = cmdMin.Caption
    End Property
    
    Public Property Let MinString(NewVal As String)
        cmdMin.Caption = NewVal
    End Property

    Public Property Get Caption() As String
        Caption = lblCaption.Caption
    End Property
    
    Public Property Let Caption(NewVal As String)
        lblCaption.Caption = NewVal
    End Property

    Public Property Let Collapsed(NV As Boolean)
    
        If NV Then
            If Not m_Collapsed Then m_SavedHeight = UserControl.Extender.Height
            UserControl.Extender.Height = 24
        Else
            UserControl.Extender.Height = m_SavedHeight
        End If
        
        m_Collapsed = NV
    
    End Property
    
    Public Property Get Collapsed() As Boolean
        Collapsed = m_Collapsed
    End Property

    Public Property Get MinVisible() As Boolean
        MinVisible = cmdMin.Visible
    End Property

    Public Property Let MinVisible(NV As Boolean)
        cmdMin.Visible = NV
    End Property

    Public Property Get ScaleHeight() As Single
        ScaleHeight = UserControl.ScaleHeight
    End Property
    
    Public Property Get ScaleWidth() As Single
        ScaleWidth = UserControl.ScaleWidth
    End Property
    
    Public Property Get Sizeable() As Boolean
        Sizeable = sms.Enabled
    End Property
    
    Public Property Let Sizeable(NV As Boolean)
        sms.Enabled = NV
    End Property
    
    Public Property Set Container(NewVal As Object)
        Set UserControl.Extender.Container = NewVal
    End Property
    
    Public Property Get Visible() As Boolean
        Visible = UserControl.Extender.Visible
    End Property
    
    Public Property Let Visible(NewVal As Boolean)
        Dim Ctl As Control
        UserControl.Extender.Visible = NewVal
        'For Each Ctl In UserControl.Controls
         '   Ctl.Visible = NewVal
        'Next
    End Property
    
    Public Property Get Top() As Single
        Top = UserControl.Extender.Top
    End Property
    
    Public Property Get Left() As Single
        Left = UserControl.Extender.Left
    End Property
    
    Public Property Get Width() As Single
        Width = UserControl.Extender.Width
    End Property
    
    Public Property Get Height() As Single
        Height = UserControl.Extender.Height
    End Property
    
    Public Property Let Top(NV As Single)
        UserControl.Extender.Top = NV
    End Property
    
    Public Property Let Left(NV As Single)
        UserControl.Extender.Left = NV
    End Property
    
    Public Property Let Width(NV As Single)
        UserControl.Width = NV
    End Property
    
    Public Property Let Height(NV As Single)
        UserControl.Height = NV
    End Property
    Public Sub Show()
        Visible = True
    End Sub
    
    Public Sub Hide()
        Visible = False
    End Sub
    
    Public Sub Move(Optional Left, Optional Top, Optional Width, Optional Height)

        Dim CX, CY, CW, CH
        
        CX = Left
        CY = Top
        CW = Width
        CH = Height
        With UserControl.Extender
            If IsMissing(Left) Then CX = .Left
            If IsMissing(Top) Then CY = .Top
            If IsMissing(Width) Then CW = .Width
            If IsMissing(Height) Then CH = .Height
            .Move CX, CY, CW, CH
        End With
    
    End Sub

