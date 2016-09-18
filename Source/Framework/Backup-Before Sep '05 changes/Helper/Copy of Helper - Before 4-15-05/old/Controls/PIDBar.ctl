VERSION 5.00
Begin VB.UserControl PIDBar 
   Alignable       =   -1  'True
   ClientHeight    =   360
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   6525
   DefaultCancel   =   -1  'True
   ScaleHeight     =   24
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   435
   Begin VB.TextBox txt 
      Enabled         =   0   'False
      Height          =   285
      Left            =   360
      Locked          =   -1  'True
      TabIndex        =   2
      Top             =   30
      Width           =   3495
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&OK"
      Enabled         =   0   'False
      Height          =   345
      Left            =   4200
      TabIndex        =   1
      Top             =   0
      Width           =   1125
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "&Cancel"
      Height          =   345
      Left            =   5400
      TabIndex        =   0
      Top             =   0
      Width           =   1125
   End
   Begin VB.Label lbl 
      Caption         =   "PID:"
      ForeColor       =   &H80000011&
      Height          =   255
      Left            =   0
      TabIndex        =   3
      Top             =   60
      Width           =   420
   End
End
Attribute VB_Name = "PIDBar"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
    Public Event OnCancel()
    Public Event OnOK()
    
    Private Sub cmdCancel_Click()
        RaiseEvent OnCancel
    End Sub

    Private Sub cmdOK_Click()
        RaiseEvent OnOK
    End Sub

    Private Sub UserControl_Resize()
    
        cmdCancel.Move UserControl.ScaleWidth - cmdCancel.Width
        cmdOK.Move cmdCancel.Left - cmdOK.Width - 5
        txt.Width = cmdOK.Left - 5 - txt.Left
    
    End Sub
    
    Public Property Get PID() As String
        PID = txt.Text
    End Property
    
    Public Property Let PID(NV As String)
        txt.Text = NV
        cmdOK.Enabled = NV <> ""
    End Property
    
