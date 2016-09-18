VERSION 5.00
Begin VB.UserControl MechMgr 
   BorderStyle     =   1  'Fixed Single
   ClientHeight    =   3300
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4380
   ScaleHeight     =   3300
   ScaleWidth      =   4380
   Begin VB.Label Label1 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Label1"
      Height          =   2415
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3735
   End
End
Attribute VB_Name = "MechMgr"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Implements IManager


Private Property Let IManager_Component(ByVal RHS As IMA2.IComponent)

End Property

Private Property Get IManager_Component() As IMA2.IComponent

End Property

Private Sub IManager_Update(pFlags As Variant)

End Sub

Private Sub UserControl_Resize()

    Label1.Width = UserControl.ScaleWidth - Label1.Left * 2
    Label1.Height = UserControl.ScaleHeight - Label1.Top * 2

End Sub
