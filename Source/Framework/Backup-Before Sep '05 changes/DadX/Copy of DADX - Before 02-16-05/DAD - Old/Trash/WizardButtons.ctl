VERSION 5.00
Begin VB.UserControl WizardButtons 
   Alignable       =   -1  'True
   ClientHeight    =   705
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4800
   ScaleHeight     =   47
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   320
   Begin VB.CommandButton cmdBack 
      Caption         =   "< &Back"
      Enabled         =   0   'False
      Height          =   345
      Left            =   1080
      TabIndex        =   2
      Top             =   180
      Width           =   1125
   End
   Begin VB.CommandButton cmdCancel 
      Caption         =   "&Cancel"
      Height          =   345
      Left            =   3600
      TabIndex        =   1
      Top             =   180
      Width           =   1125
   End
   Begin VB.CommandButton cmdNext 
      Caption         =   "&Next >"
      Height          =   345
      Left            =   2205
      TabIndex        =   0
      Top             =   180
      Width           =   1125
   End
   Begin IMA2_DAD.Bevel Bevel2 
      Align           =   1  'Align Top
      Height          =   45
      Left            =   0
      TabIndex        =   3
      Top             =   0
      Width           =   4800
      _ExtentX        =   8467
      _ExtentY        =   79
      Sides           =   2
      Weight          =   1
   End
End
Attribute VB_Name = "WizardButtons"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Private Sub UserControl_Resize()

    On Error Resume Next
    
    Dim sp As Long
    sp = Fix((UserControl.ScaleHeight - cmdNext.Height) / 2)
    
    cmdCancel.Left = UserControl.ScaleWidth - cmdCancel.Width - 10
    cmdNext.Left = cmdCancel.Left - cmdNext.Width - 15
    cmdBack.Left = cmdNext.Left - cmdBack.Width

    cmdCancel.Top = sp
    cmdNext.Top = cmdCancel.Top
    cmdBack.Top = cmdCancel.Top
    

End Sub
