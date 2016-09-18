VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   5880
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   9900
   LinkTopic       =   "Form1"
   ScaleHeight     =   5880
   ScaleWidth      =   9900
   StartUpPosition =   3  'Windows Default
   Begin MSComDlg.CommonDialog Dialog1 
      Left            =   720
      Top             =   4920
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.CommandButton Command1 
      Caption         =   "&Load Image"
      Height          =   375
      Left            =   5400
      TabIndex        =   3
      Top             =   4920
      Width           =   1335
   End
   Begin VB.CommandButton cmdSaveimage 
      Caption         =   "&Save Image"
      Height          =   375
      Left            =   6840
      TabIndex        =   2
      Top             =   4920
      Width           =   1335
   End
   Begin VB.CommandButton cmfFileOpen 
      Caption         =   "&Open from file"
      Height          =   375
      Left            =   3960
      TabIndex        =   1
      Top             =   4920
      Width           =   1335
   End
   Begin VB.CommandButton cmdClose 
      Caption         =   "&Close"
      Height          =   375
      Left            =   8280
      TabIndex        =   0
      Top             =   4920
      Width           =   1335
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub cmdClose_Click()
    End
End Sub

Private Sub cmfFileOpen_Click()
Dim picturename As String
Dim pixel As Long
Dim i&, j&
   Dialog1.InitDir = App.Path
   Dialog1.Filter = "Images|*.BMP;*.GIP;*.JPG;*.DIB|All Files|*.*"
   Dialog1.Action = 1
   picturename = Dialog1.FileName
   If picturename = "" Then Exit Sub
   
End Sub
