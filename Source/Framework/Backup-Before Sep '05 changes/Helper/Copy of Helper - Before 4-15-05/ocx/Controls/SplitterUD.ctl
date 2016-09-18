VERSION 5.00
Begin VB.UserControl SplitterUD 
   Alignable       =   -1  'True
   BackColor       =   &H8000000E&
   ClientHeight    =   3600
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   2850
   MousePointer    =   7  'Size N S
   ScaleHeight     =   240
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   190
   ToolboxBitmap   =   "SplitterUD.ctx":0000
   Begin VB.Line Line1 
      BorderColor     =   &H00D0D0D0&
      BorderStyle     =   3  'Dot
      X1              =   0
      X2              =   7740
      Y1              =   48
      Y2              =   667
   End
End
Attribute VB_Name = "SplitterUD"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
    Dim m_OY As Single
    
    Public Event OnSplitterRelease(Delta As Single)
    Public Event OnSplitterBegin()
    
    Private Sub UserControl_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
        UserControl.ScaleMode = UserControl.Parent.ScaleMode
        m_OY = Y
        RaiseEvent OnSplitterBegin
    End Sub
    
    Private Sub UserControl_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
        RaiseEvent OnSplitterRelease(Y - m_OY)
    End Sub

    Private Sub UserControl_Resize()
        
        Line1.Y1 = Fix(UserControl.ScaleHeight / 2)
        Line1.Y2 = Line1.Y1
        
    End Sub
