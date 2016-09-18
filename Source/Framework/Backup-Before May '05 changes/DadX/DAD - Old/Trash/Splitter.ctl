VERSION 5.00
Begin VB.UserControl Splitter 
   Alignable       =   -1  'True
   BackColor       =   &H8000000E&
   BackStyle       =   0  'Transparent
   ClientHeight    =   3600
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   2850
   MousePointer    =   9  'Size W E
   ScaleHeight     =   3600
   ScaleWidth      =   2850
   Begin VB.Line Line1 
      BorderColor     =   &H00F0F0F0&
      BorderStyle     =   3  'Dot
      X1              =   120
      X2              =   120
      Y1              =   0
      Y2              =   10000
   End
End
Attribute VB_Name = "Splitter"
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
        
        Line1.X1 = UserControl.ScaleWidth / 2
        Line1.X2 = Line1.X1
        
    End Sub
