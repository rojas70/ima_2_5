VERSION 5.00
Begin VB.UserControl SimpleSizer 
   Alignable       =   -1  'True
   ClientHeight    =   3600
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4800
   ControlContainer=   -1  'True
   ScaleHeight     =   240
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   320
   ToolboxBitmap   =   "SimpleSizer.ctx":0000
   Begin VB.PictureBox picRight 
      Align           =   4  'Align Right
      BorderStyle     =   0  'None
      Height          =   3480
      Left            =   4740
      MousePointer    =   9  'Size W E
      ScaleHeight     =   232
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   4
      TabIndex        =   3
      TabStop         =   0   'False
      Top             =   60
      Width           =   60
      Begin VB.Line LineR2 
         BorderColor     =   &H8000000C&
         X1              =   2
         X2              =   2
         Y1              =   0
         Y2              =   10000
      End
      Begin VB.Line LineR1 
         X1              =   3
         X2              =   3
         Y1              =   0
         Y2              =   10000
      End
   End
   Begin VB.PictureBox picBottom 
      Align           =   2  'Align Bottom
      BorderStyle     =   0  'None
      CausesValidation=   0   'False
      ClipControls    =   0   'False
      Height          =   60
      Left            =   0
      MousePointer    =   7  'Size N S
      ScaleHeight     =   4
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   320
      TabIndex        =   0
      TabStop         =   0   'False
      Top             =   3540
      Width           =   4800
      Begin VB.PictureBox picDiag 
         BorderStyle     =   0  'None
         Height          =   90
         Left            =   4560
         MousePointer    =   8  'Size NW SE
         ScaleHeight     =   6
         ScaleMode       =   3  'Pixel
         ScaleWidth      =   6
         TabIndex        =   4
         TabStop         =   0   'False
         Top             =   0
         Width           =   90
         Begin VB.Shape shpDiag2 
            Height          =   75
            Left            =   -15
            Top             =   -15
            Width           =   105
         End
         Begin VB.Shape shpDiag1 
            BorderColor     =   &H80000010&
            Height          =   60
            Left            =   -15
            Top             =   -15
            Width           =   90
         End
      End
      Begin VB.Line LineB1 
         BorderColor     =   &H8000000C&
         X1              =   0
         X2              =   666.667
         Y1              =   2
         Y2              =   2
      End
      Begin VB.Line LineB2 
         X1              =   0
         X2              =   10000
         Y1              =   3
         Y2              =   3
      End
      Begin VB.Line LineB3 
         BorderColor     =   &H80000009&
         X1              =   0
         X2              =   0
         Y1              =   0
         Y2              =   5
      End
   End
   Begin VB.PictureBox picTop 
      Align           =   1  'Align Top
      BorderStyle     =   0  'None
      Height          =   60
      Left            =   0
      MousePointer    =   7  'Size N S
      ScaleHeight     =   4
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   320
      TabIndex        =   2
      TabStop         =   0   'False
      Top             =   0
      Width           =   4800
      Begin VB.Line LineT4 
         X1              =   100
         X2              =   100
         Y1              =   0
         Y2              =   10000
      End
      Begin VB.Line LineT3 
         BorderColor     =   &H8000000C&
         X1              =   99
         X2              =   99
         Y1              =   0
         Y2              =   10000
      End
      Begin VB.Line LineT2 
         BorderColor     =   &H80000009&
         X1              =   0
         X2              =   0
         Y1              =   0
         Y2              =   8
      End
      Begin VB.Line LineT 
         BorderColor     =   &H80000009&
         X1              =   0
         X2              =   10000
         Y1              =   0
         Y2              =   0
      End
   End
   Begin VB.PictureBox picLeft 
      Align           =   3  'Align Left
      BorderStyle     =   0  'None
      Height          =   3480
      Left            =   0
      MousePointer    =   9  'Size W E
      ScaleHeight     =   232
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   4
      TabIndex        =   1
      TabStop         =   0   'False
      Top             =   60
      Width           =   60
      Begin VB.Line LineL 
         BorderColor     =   &H80000009&
         X1              =   0
         X2              =   0
         Y1              =   0
         Y2              =   10000
      End
   End
End
Attribute VB_Name = "SimpleSizer"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
    Option Explicit
    
'****************************************************************************************************************
'   Private Member Variables
'****************************************************************************************************************
    Dim m_ST As Single, m_SL As Single, m_SW As Single, m_SH As Single
    Dim m_SY As Single, m_SX As Single
'****************************************************************************************************************
'   Public Events
'****************************************************************************************************************
    
    Public Event OnBeginResize()
    Public Event OnResize(L As Single, T As Single, W As Single, H As Single)
    Public Event OnFinishResize(L As Single, T As Single, W As Single, H As Single)

'****************************************************************************************************************
'   Private Functions
'****************************************************************************************************************
    
    Private Sub SaveStartValues(X As Single, Y As Single)
        With UserControl
            m_SX = X
            m_SY = Y
            m_SL = .Extender.Left
            m_ST = .Extender.Top
            m_SW = .Extender.Width
            m_SH = .Extender.Height
        End With
        RaiseEvent OnBeginResize
    End Sub
    
    Private Sub ThrowUpdate(dL As Single, dT As Single, dW As Single, dH As Single)
       ' Debug.Print UserControl.Extender.Width + dW, m_SW
        'If UserControl.Extender.Width + dW = m_SW Then Exit Sub
        'RaiseEvent OnResize(m_SL + dL, m_ST + dT, m_SW + dW, m_SH + dH)
        'DoEvents
        'Debug.Print UserControl.Extender.Width; "-------"
    End Sub
    
    Private Sub FinishUpdate(dL As Single, dT As Single, dW As Single, dH As Single)
        RaiseEvent OnFinishResize(m_SL + dL, m_ST + dT, m_SW + dW, m_SH + dH)
    End Sub

'****************************************************************************************************************
'   Control Events
'****************************************************************************************************************
    
    Private Sub picTop_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
        Call SaveStartValues(X, Y)
    End Sub
    
    Private Sub picTop_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
        If Button And vbLeftButton Then Call ThrowUpdate(0, Y - m_SY, 0, -(Y - m_SY))
    End Sub
    
    Private Sub picTop_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
        If Button And vbLeftButton Then Call FinishUpdate(0, Y - m_SY, 0, -(Y - m_SY))
    End Sub

    '----------------------------------------------------------------------------------------------------

    Private Sub picBottom_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
        Call SaveStartValues(X, Y)
    End Sub
    
    Private Sub picBottom_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
        If Button And vbLeftButton Then Call ThrowUpdate(0, 0, 0, Y - m_SY)
    End Sub
    
    Private Sub picBottom_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
        If Button And vbLeftButton Then Call FinishUpdate(0, 0, 0, Y - m_SY)
    End Sub
    
    '----------------------------------------------------------------------------------------------------
    
    Private Sub picLeft_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
        Call SaveStartValues(X, Y)
    End Sub
    
    Private Sub picLeft_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
        If Button And vbLeftButton Then Call ThrowUpdate(X - m_SX, 0, -(X - m_SX), 0)
    End Sub
    
    Private Sub picLeft_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
        If Button And vbLeftButton Then Call FinishUpdate(X - m_SX, 0, -(X - m_SX), 0)
    End Sub
    
    '----------------------------------------------------------------------------------------------------
    
    Private Sub picRight_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
        Call SaveStartValues(X, Y)
    End Sub
    
    Private Sub picRight_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
        If Button And vbLeftButton Then Call ThrowUpdate(0, 0, X - m_SX, 0)
    End Sub
    
    Private Sub picRight_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
        If Button And vbLeftButton Then Call FinishUpdate(0, 0, X - m_SX, 0)
    End Sub
    
    '----------------------------------------------------------------------------------------------------
    
    Private Sub picDiag_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
        Call SaveStartValues(X, Y)
    End Sub
    
    Private Sub picDiag_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
        If Button And vbLeftButton Then Call ThrowUpdate(0, 0, X - m_SX, Y - m_SY)
    End Sub

    Private Sub picDiag_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
        If Button And vbLeftButton Then Call FinishUpdate(0, 0, X - m_SX, Y - m_SY)
    End Sub

    '----------------------------------------------------------------------------------------------------

    Private Sub UserControl_Resize()
    
        picDiag.Move picBottom.ScaleWidth - picDiag.Width, 0
        'LineB4.X1 = picBottom.ScaleWidth - 1
        'LineB4.X2 = LineB4.X1
        'LineB5.X1 = picBottom.ScaleWidth - 2
        'LineB5.X2 = LineB5.X1
        
        LineT4.X1 = picBottom.ScaleWidth - 1
        LineT4.X2 = LineT4.X1
        LineT3.X1 = picBottom.ScaleWidth - 2
        LineT3.X2 = LineT3.X1
        
    
    End Sub

    Public Property Get Enabled() As Boolean
        Enabled = picTop.Enabled
    End Property

    Public Property Let Enabled(NV As Boolean)
        picTop.Enabled = NV
        picBottom.Enabled = NV
        picLeft.Enabled = NV
        picRight.Enabled = NV
        picDiag.Enabled = NV
    End Property

