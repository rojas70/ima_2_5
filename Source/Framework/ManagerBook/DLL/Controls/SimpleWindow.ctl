VERSION 5.00
Begin VB.UserControl SimpleWindow 
   ClientHeight    =   3540
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4560
   ScaleHeight     =   236
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   304
   ToolboxBitmap   =   "SimpleWindow.ctx":0000
   Begin ManagerBook.Bevel bvl 
      Height          =   30
      Left            =   60
      TabIndex        =   2
      Top             =   315
      Width           =   3495
      _ExtentX        =   6165
      _ExtentY        =   53
      Sides           =   2
      Weight          =   1
   End
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
      Left            =   1890
      Style           =   1  'Graphical
      TabIndex        =   1
      TabStop         =   0   'False
      Top             =   75
      Width           =   210
   End
   Begin VB.Shape shpGrey 
      BorderColor     =   &H8000000C&
      Height          =   3540
      Left            =   -15
      Top             =   -15
      Visible         =   0   'False
      Width           =   4500
   End
   Begin VB.Shape shpBlack 
      Height          =   3555
      Left            =   -15
      Top             =   -15
      Visible         =   0   'False
      Width           =   4575
   End
   Begin VB.Shape shpWhite 
      BorderColor     =   &H80000005&
      Height          =   35550
      Left            =   15
      Top             =   15
      Visible         =   0   'False
      Width           =   45750
   End
   Begin VB.Label lbl 
      Alignment       =   2  'Center
      BackColor       =   &H8000000D&
      Caption         =   "Caption"
      ForeColor       =   &H8000000E&
      Height          =   225
      Left            =   60
      TabIndex        =   0
      Top             =   60
      Width           =   2055
   End
End
Attribute VB_Name = "SimpleWindow"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

'***************************************************************************************
    
    Public Event OnMinimize()
    Public Event Resize()
    Public Event LabelDblClick()
    
    Public Event MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
    Public Event MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
    Public Event MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    
    Public Event KeyDown(KeyCode As Integer, Shift As Integer)
    Public Event KeyPress(KeyAscii As Integer)
    Public Event KeyUp(KeyCode As Integer, Shift As Integer)

'***************************************************************************************
    
    Dim m_X As Long, m_Y As Long, m_Moving As Boolean, m_Sizing

    Dim m_Sizeable      As Boolean
    Dim m_SavedHeight   As Single
    Dim m_Collapsed     As Boolean
    
'***************************************************************************************

    Public Index            As Integer
    Public ControlObject    As Object
    
'***************************************************************************************
' Public Interface
'***************************************************************************************

    Public Property Set Container(NewVal As Object)
        Set UserControl.Extender.Container = NewVal
    End Property
    
    Public Function CreateControl(PID As String, Key As String) As Object
       On Error Resume Next
       Set ControlObject = UserControl.Controls.Add(PID, Key)
       Set CreateControl = ControlObject
    End Function
    
'***************************************************************************************
' UI Properties
'***************************************************************************************
    
    Public Property Get ToolTipText() As String
        ToolTipText = lbl.ToolTipText
    End Property
    
    Public Property Let ToolTipText(NV As String)
        lbl.ToolTipText = NV
    End Property
    
    Public Property Get MinString() As String
        MinString = cmdMin.Caption
    End Property
    
    Public Property Let MinString(NewVal As String)
        cmdMin.Caption = NewVal
    End Property

    Public Property Get Caption() As String
        Caption = lbl.Caption
    End Property
    
    Public Property Let Caption(NewVal As String)
        lbl.Caption = NewVal
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
        Sizeable = m_Sizeable
    End Property
    
    Public Property Let Sizeable(NV As Boolean)
        m_Sizeable = NV
    End Property
    
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

'***************************************************************************************
' Redundant Control Properties
'***************************************************************************************
    
    Public Property Get Visible() As Boolean
        Visible = UserControl.Extender.Visible
    End Property
    
    Public Property Let Visible(NewVal As Boolean)
        Dim Ctl As Control
        UserControl.Extender.Visible = NewVal
        For Each Ctl In UserControl.Controls
            Ctl.Visible = NewVal
        Next
    End Property
    
    Public Sub Show()
        Me.Visible = True
    End Sub
    
    Public Sub Hide()
        Me.Visible = False
    End Sub
    
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

'***************************************************************************************
' Control Events
'***************************************************************************************

    Private Sub cmdMin_Click()
        RaiseEvent OnMinimize
    End Sub
    
    Private Sub cmdMin_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
        UserControl.SetFocus
    End Sub

    Private Sub lbl_DblClick()
        RaiseEvent LabelDblClick
    End Sub

    Private Sub lbl_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
        m_Moving = True
        Call UserControl_MouseDown(Button, Shift, lbl.Left + (X / Screen.TwipsPerPixelX), lbl.Top + (Y / Screen.TwipsPerPixelY))
    End Sub
    
    Private Sub lbl_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
        Call UserControl_MouseMove(Button, Shift, lbl.Left + (X / Screen.TwipsPerPixelX), lbl.Top + (Y / Screen.TwipsPerPixelY))
    End Sub
    
    Private Sub lbl_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
        Call UserControl_MouseUp(Button, Shift, lbl.Left + (X / Screen.TwipsPerPixelX), lbl.Top + (Y / Screen.TwipsPerPixelY))
        m_Moving = False
    End Sub
    
'***************************************************************************************
'UserControl Events
'***************************************************************************************
    
    Private Sub UserControl_InitProperties()
 '       m_SavedHeight = 100
    End Sub

    Private Sub UserControl_Resize()
        On Error Resume Next
        Dim W, H
    
        W = UserControl.ScaleWidth
        H = UserControl.ScaleHeight
        
        bvl.Visible = H > 25
        
'        shpWhite.Move 1, 1, 3000, 3000
 '       shpGrey.Move -1, -1, W, H
  '      shpBlack.Move -1, -1, W + 1, H + 1
        mp.Move 0, 0, W, H
        
        lbl.Move lbl.Left, lbl.Top, W - 9
        bvl.Move bvl.Left, bvl.Top, W - 9
        cmdMin.Move W - cmdMin.Width - 6, 5
        
        RaiseEvent Resize
    End Sub
    
    Private Sub UserControl_EnterFocus()
        lbl.BackColor = QBColor(1)
        lbl.ForeColor = QBColor(15)
        UserControl.Extender.ZOrder 0
    End Sub
    
    Private Sub UserControl_ExitFocus()
        lbl.BackColor = QBColor(8)
        lbl.ForeColor = QBColor(7)
    End Sub
    
    Private Sub UserControl_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
        If m_Moving Then
            m_X = X
            m_Y = Y
        ElseIf UserControl.MousePointer <> vbDefault Then
            m_X = X
            m_Y = Y
            m_Sizing = True And m_Sizeable
        Else
            RaiseEvent MouseDown(Button, Shift, X, Y)
        End If
    End Sub
    
    Private Sub UserControl_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
        If m_Moving Then
            Call Moving(CLng(X), CLng(Y))
        ElseIf m_Sizing And m_Sizeable Then
            Call Sizing(CLng(X), CLng(Y))
        Else
            If m_Sizeable Then Call CheckSizing(CLng(X), CLng(Y))
            If UserControl.MousePointer = vbDefault Then RaiseEvent MouseMove(Button, Shift, X, Y)
        End If
    End Sub
    
    Private Sub UserControl_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
        m_Moving = False
        m_Sizing = False
        UserControl.MousePointer = vbDefault
        RaiseEvent MouseUp(Button, Shift, X, Y)
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
' Private Functions
'***************************************************************************************
    
    Private Sub Moving(CX As Long, CY As Long)
    
        If (m_X - CX) = 0 And (m_Y - CY) = 0 Then Exit Sub
            
        With UserControl
            .Extender.Move .Extender.Left - (m_X - CX), .Extender.Top - (m_Y - CY)
            m_X = CX + (m_X - CX)
            m_Y = CY + (m_Y - CY)
        End With
    
    
    End Sub
    
    Private Sub CheckSizing(X As Long, Y As Long)
        
        Dim SW As Long, SH As Long
        Dim NWSE As Boolean, NESW As Boolean
        Dim NS As Boolean, EW As Boolean
        Dim XL, XR, XM, YT, YM, YB
    
        SW = Me.ScaleWidth: SH = Me.ScaleHeight
            
        XL = X < 5:        XR = X > SW - 20:         XM = Not XL And Not XR
        YT = Y < 5:        YB = Y > SH - 20:         YM = Not YT And Not YB
        
        YT = False
        XL = False
        NWSE = (XL And YT) Or (XR And YB):          NESW = (XR And YT) Or (XL And YB)
        NS = XM And (YT Or YB):                     EW = YM And (XL Or XR)
            
        If NWSE Then UserControl.MousePointer = vbSizeNWSE: Exit Sub
        If NESW Then UserControl.MousePointer = vbSizeNESW: Exit Sub
        If NS Then UserControl.MousePointer = vbSizeNS: Exit Sub
        If EW Then UserControl.MousePointer = vbSizeWE: Exit Sub
        
        UserControl.MousePointer = vbDefault
    
    End Sub
    
    Private Sub Sizing(CX As Long, CY As Long)
    
        Dim OW As Long, OH As Long
        Dim NW As Long, NH As Long
        
        If CX < (UserControl.TextWidth(lbl.Caption) + 20) Then CX = (UserControl.TextWidth(lbl.Caption) + 20)
        If CY < 24 Then CY = 24
        
        With UserControl
            OW = .Extender.Width
            OH = .Extender.Height
            
            Select Case .MousePointer
                Case vbSizeNS
                    .Extender.Move .Extender.Left, .Extender.Top, OW, CY
                Case vbSizeWE
                    .Extender.Move .Extender.Left, .Extender.Top, CX
                Case Else
                    .Extender.Move .Extender.Left, .Extender.Top, CX, CY
            End Select
    
        End With
    
    End Sub
    
    
Private Sub UserControl_ReadProperties(PropBag As PropertyBag)
    Caption = PropBag.ReadProperty("Caption", "Caption")
    MinVisible = PropBag.ReadProperty("MinVisible", True)
    MinString = PropBag.ReadProperty("MinString", "_")
    m_Sizeable = PropBag.ReadProperty("Sizeable", True)
    m_SavedHeight = PropBag.ReadProperty("SavedHeight", 200)
    m_Collapsed = PropBag.ReadProperty("Collapsed", False)
End Sub

Private Sub UserControl_WriteProperties(PropBag As PropertyBag)
    Call PropBag.WriteProperty("Caption", Caption, "Caption")
    Call PropBag.WriteProperty("MinVisible", MinVisible, True)
    Call PropBag.WriteProperty("MinString", MinString, "_")
    Call PropBag.WriteProperty("Sizeable", m_Sizeable, True)
    Call PropBag.WriteProperty("SavedHeight", m_SavedHeight, 200)
    Call PropBag.WriteProperty("Collapsed", m_Collapsed, False)
End Sub

