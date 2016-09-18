VERSION 5.00
Begin VB.UserControl UserControl1 
   ClientHeight    =   4905
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4575
   ScaleHeight     =   4905
   ScaleWidth      =   4575
   Begin VB.CommandButton cmdClose 
      Caption         =   "&Close"
      Height          =   375
      Left            =   3240
      TabIndex        =   6
      Top             =   4200
      Width           =   1215
   End
   Begin VB.CommandButton cmdRefresh 
      Caption         =   "&Refresh"
      Height          =   375
      Left            =   1680
      TabIndex        =   5
      Top             =   4200
      Width           =   1215
   End
   Begin VB.CommandButton cmdUpdate 
      Caption         =   "&Update"
      Height          =   375
      Left            =   120
      TabIndex        =   4
      Top             =   4200
      Width           =   1215
   End
   Begin VB.TextBox txtSignalLength 
      Height          =   375
      Left            =   1680
      TabIndex        =   3
      Top             =   1200
      Width           =   2175
   End
   Begin VB.TextBox txtVectorLength 
      Height          =   375
      Left            =   1680
      TabIndex        =   1
      Top             =   720
      Width           =   2175
   End
   Begin VB.Label lblPath 
      AutoSize        =   -1  'True
      Height          =   195
      Left            =   480
      TabIndex        =   8
      Top             =   3480
      Width           =   45
   End
   Begin VB.Label Label3 
      AutoSize        =   -1  'True
      Caption         =   "VectorSignal"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   -1  'True
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   300
      Left            =   1680
      TabIndex        =   7
      Top             =   240
      Width           =   1560
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      Caption         =   "SignalLength:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   195
      Left            =   360
      TabIndex        =   2
      Top             =   1320
      Width           =   1185
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "VectorLength:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   195
      Left            =   360
      TabIndex        =   0
      Top             =   840
      Width           =   1215
   End
End
Attribute VB_Name = "UserControl1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Implements IManager

Dim m_Comp As cVectorSignal

Private Sub cmdUpdate_Click()
    Set m_Comp = New cVectorSignal
    'If txtVectorLength.Text <> m_Comp.VectorLength Then
    If txtVectorLength.Text <> "" Then
        m_Comp.VectorLength = CLng(txtVectorLength.Text)
    End If
    'If txtSignalLength.Text <> m_Comp.SignalLength Then
    If txtSignalLength.Text <> "" Then
        m_Comp.SignalLength = CLng(txtSignalLength.Text)
    End If
    
End Sub

Private Sub IManager_SetComponent(C As IMA2.IComponent)

    Set m_Comp = New cVectorSignal
    If Not (C Is Nothing) Then
        txtVectorLength.Text = m_Comp.VectorLength
        txtSignalLength.Text = m_Comp.SignalLength
        lblPath.Caption = C.Path
    End If
End Sub

Private Sub IManager_Update(Optional Flags As Variant)
    
    txtVectorLength.Text = m_Comp.VectorLength
    txtSignalLength.Text = m_Comp.SignalLength
End Sub


