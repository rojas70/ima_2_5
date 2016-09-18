VERSION 5.00
Begin VB.UserControl SplitterLR 
   Alignable       =   -1  'True
   BackColor       =   &H8000000E&
   ClientHeight    =   3600
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   2850
   MousePointer    =   9  'Size W E
   ScaleHeight     =   240
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   190
   Begin VB.Line Line1 
      BorderColor     =   &H00D0D0D0&
      BorderStyle     =   3  'Dot
      X1              =   8
      X2              =   8
      Y1              =   0
      Y2              =   666.667
   End
End
Attribute VB_Name = "SplitterLR"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
    Option Explicit
    
'****************************************************************************************************************
' Public Enumerations
'****************************************************************************************************************
    
    Public Enum SplitterDirection
        sdLeftRight = 0
        sdUpDown = 1
    End Enum
        
'****************************************************************************************************************
'Private Member Variables
'****************************************************************************************************************
    
    Dim m_OP    As Single
    Dim m_Dir   As SplitterDirection
    Dim m_Saved As Boolean
    
'****************************************************************************************************************
' Public Events
'****************************************************************************************************************
    
    Public Event OnSplitterRelease(Delta As Single)
    Public Event OnSplitterBegin()

'****************************************************************************************************************
' Public Interface
'****************************************************************************************************************
    
    Public Property Get Direction() As SplitterDirection
        Direction = m_Dir
    End Property

    Public Property Let Direction(NV As SplitterDirection)
        m_Dir = NV
    End Property

    Public Property Get BackStyle() As BackStyleConstants
        BackStyle = UserControl.BackStyle
    End Property
    
    Public Property Let BackStyle(NV As BackStyleConstants)
        UserControl.BackStyle = NV
    End Property
    

'****************************************************************************************************************
'Usercontrol Events
'****************************************************************************************************************
    
    Private Sub UserControl_InitProperties()
        m_Dir = sdUpDown
    End Sub

    Private Sub UserControl_ReadProperties(PropBag As PropertyBag)
        m_Dir = PropBag.ReadProperty("Dir", 0)
    End Sub
    
    Private Sub UserControl_WriteProperties(PropBag As PropertyBag)
        Call PropBag.WriteProperty("Dir", m_Dir, 0)
    End Sub
    
    Private Sub UserControl_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
        UserControl.ScaleMode = UserControl.Parent.ScaleMode
        If m_Dir = sdLeftRight Then
            m_OP = X
        Else
            m_OP = Y
        End If
        RaiseEvent OnSplitterBegin
    End Sub
    
    Private Sub UserControl_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
        If m_Dir = sdLeftRight Then
            RaiseEvent OnSplitterRelease(X - m_OP)
        Else
            RaiseEvent OnSplitterRelease(Y - m_OP)
        End If
    End Sub
    
    Private Sub UserControl_Resize()
        On Error Resume Next
        
        If Not m_Saved Then
            m_Saved = True
            If UserControl.Width > UserControl.Height Then m_Dir = sdUpDown
        End If
        
        If m_Dir = sdLeftRight Then
            Line1.X1 = Fix(UserControl.ScaleWidth / 2)
            Line1.X2 = Line1.X1
        Else
            Line1.Y1 = Fix(UserControl.ScaleHeight / 2)
            Line1.Y2 = Line1.Y1
        End If
    End Sub
