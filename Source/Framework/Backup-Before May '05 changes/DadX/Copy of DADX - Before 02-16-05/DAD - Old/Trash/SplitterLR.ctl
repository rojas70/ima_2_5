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
Attribute VB_Exposed = False
    Dim m_OX As Single
    
    Public Event OnSplitterRelease(Delta As Single)
    Public Event OnSplitterBegin()
    
    Private Sub UserControl_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
        UserControl.ScaleMode = UserControl.Parent.ScaleMode
        m_OX = x
        RaiseEvent OnSplitterBegin
    End Sub
    
    Private Sub UserControl_MouseUp(Button As Integer, Shift As Integer, x As Single, y As Single)
        RaiseEvent OnSplitterRelease(x - m_OX)
    End Sub

    Private Sub UserControl_Resize()
        
        Line1.X1 = Fix(UserControl.ScaleWidth / 2)
        Line1.X2 = Line1.X1
        
    End Sub
