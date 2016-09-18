VERSION 5.00
Begin VB.UserControl SimplePanel 
   BackStyle       =   0  'Transparent
   ClientHeight    =   3600
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4800
   ControlContainer=   -1  'True
   ScaleHeight     =   240
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   320
   Begin VB.Line b2 
      BorderColor     =   &H80000014&
      X1              =   0
      X2              =   800
      Y1              =   153
      Y2              =   153
   End
   Begin VB.Line r2 
      BorderColor     =   &H80000014&
      X1              =   100
      X2              =   100
      Y1              =   0
      Y2              =   10000
   End
   Begin VB.Line r1 
      BorderColor     =   &H80000010&
      X1              =   99
      X2              =   99
      Y1              =   0
      Y2              =   10000
   End
   Begin VB.Line t1 
      BorderColor     =   &H80000010&
      Tag             =   "c"
      X1              =   0
      X2              =   800
      Y1              =   0
      Y2              =   0
   End
   Begin VB.Line l2 
      BorderColor     =   &H80000014&
      X1              =   1
      X2              =   1
      Y1              =   0
      Y2              =   10000
   End
   Begin VB.Line l1 
      BorderColor     =   &H80000010&
      X1              =   0
      X2              =   0
      Y1              =   0
      Y2              =   10000
   End
   Begin VB.Line t2 
      BorderColor     =   &H80000014&
      X1              =   0
      X2              =   800
      Y1              =   1
      Y2              =   1
   End
   Begin VB.Line b1 
      BorderColor     =   &H80000010&
      X1              =   0
      X2              =   800
      Y1              =   152
      Y2              =   152
   End
End
Attribute VB_Name = "SimplePanel"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Enum SimplePanelStyle
    SP_Normal = 0
    SP_Raised = 1
    SP_Sunken = 2
End Enum

Enum SimplePanelBorder
    SP_NotBorder = 0
    SP_TopBorder = 1
    SP_LeftBorder = 2
    SP_RightBorder = 3
    SP_BottomBorder = 4
End Enum

Dim m_Style As SimplePanelStyle

Public Event BorderMouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single, Border As SimplePanelBorder)
Public Event BorderMouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single, Border As SimplePanelBorder)

Public Event MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
Public Event MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
Public Event MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)

Public Function BorderHitTest(X As Single, Y As Single) As SimplePanelBorder

    If X < 2 Then
        BorderHitTest = SP_TopBorder
    ElseIf Y < 2 Then
        BorderHitTest = SP_LeftBorder
    ElseIf X > UserControl.Width - 2 Then
        BorderHitTest = SP_RightBorder
    ElseIf Y > UserControl.Height - 2 Then
        BorderHitTest = SP_BottomBorder
    End If

End Function

Private Sub UserControl_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
    Dim B As SimplePanelBorder
    B = BorderHitTest(X, Y)
    If B = SP_NotBorder Then
        RaiseEvent MouseMove(Button, Shift, X, Y)
    Else
        RaiseEvent BorderMouseMove(Button, Shift, X, Y, B)
    End If
End Sub

Private Sub UserControl_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
    Dim B As SimplePanelBorder
    B = BorderHitTest(X, Y)
    If B = SP_NotBorder Then
        RaiseEvent MouseDown(Button, Shift, X, Y)
    Else
        RaiseEvent BorderMouseDown(Button, Shift, X, Y, B)
    End If
End Sub

Private Sub UserControl_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    RaiseEvent MouseUp(Button, Shift, X, Y)
End Sub

Private Sub UserControl_ReadProperties(PropBag As PropertyBag)
    Style = PropBag.ReadProperty("Style", 0)
End Sub

Private Sub UserControl_WriteProperties(PropBag As PropertyBag)
    Call PropBag.WriteProperty("Style", m_Style, 0)
End Sub

Private Sub UserControl_Resize()

    
    b1.Y1 = UserControl.ScaleHeight - 2
    b1.Y2 = UserControl.ScaleHeight - 2
    b2.Y1 = UserControl.ScaleHeight - 1
    b2.Y2 = UserControl.ScaleHeight - 1
    
    r1.X1 = UserControl.ScaleWidth - 2
    r1.X2 = UserControl.ScaleWidth - 2
    r2.X1 = UserControl.ScaleWidth - 1
    r2.X2 = UserControl.ScaleWidth - 1
    

End Sub


Public Property Get Style() As SimplePanelStyle
    Style = m_Style
End Property

Public Property Let Style(NS As SimplePanelStyle)
    
    m_Style = NS
    
    If NS = SP_Normal Then
        t1.BorderColor = QBColor(8)
        t2.BorderColor = QBColor(15)
        
        l1.BorderColor = QBColor(8)
        l2.BorderColor = QBColor(15)
        
        b1.BorderColor = QBColor(8)
        b2.BorderColor = QBColor(15)
        
        r1.BorderColor = QBColor(8)
        r2.BorderColor = QBColor(15)
    
    ElseIf NS = SP_Raised Then
    
        t1.BorderColor = QBColor(7)
        t2.BorderColor = QBColor(15)
        
        l1.BorderColor = QBColor(7)
        l2.BorderColor = QBColor(15)
        
        b1.BorderColor = QBColor(8)
        b2.BorderColor = QBColor(0)
        
        r1.BorderColor = QBColor(8)
        r2.BorderColor = QBColor(0)
    
    End If
    
End Property

