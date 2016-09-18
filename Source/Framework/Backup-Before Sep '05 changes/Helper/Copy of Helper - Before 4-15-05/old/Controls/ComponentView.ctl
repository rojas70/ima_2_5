VERSION 5.00
Begin VB.UserControl ComponentView 
   ClientHeight    =   3600
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4800
   ScaleHeight     =   3600
   ScaleWidth      =   4800
End
Attribute VB_Name = "ComponentView"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Dim m_Cmp As IComponent
Dim m_AL As IComponent

Private Sub UserControl_Resize()
    On Error Resume Next
    tvw.Move 0, 0, UserControl.ScaleWidth, UserControl.ScaleHeight
End Sub

Public Property Set Component(NewVal As IComponent)
    Set m_Cmp = NewVal
    Call Refresh
End Property

