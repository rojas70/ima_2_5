VERSION 5.00
Begin VB.Form frmTextSummary 
   Caption         =   "Text-based IMA2 Network Summary "
   ClientHeight    =   3855
   ClientLeft      =   2775
   ClientTop       =   3765
   ClientWidth     =   6030
   Icon            =   "frmTextSummary.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   3855
   ScaleWidth      =   6030
   Begin IMA2_HelperX.OKCancelBar ocb 
      Align           =   2  'Align Bottom
      Height          =   432
      Left            =   0
      TabIndex        =   1
      Top             =   3420
      Width           =   6036
      _ExtentX        =   10636
      _ExtentY        =   767
   End
   Begin VB.TextBox txt 
      BeginProperty Font 
         Name            =   "Courier New"
         Size            =   7.5
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2892
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   0
      Text            =   "frmTextSummary.frx":044A
      Top             =   120
      Width           =   5772
   End
End
Attribute VB_Name = "frmTextSummary"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit

Public Sub ShowModal()

    LoadStrings
    Me.Show vbModal
    Unload Me
    
End Sub

Private Sub LoadStrings()

    Dim S() As String
    Dim DI As IMA2_DistributingInfo
    Dim I As Integer
    Dim P As String, F As String, N As String
    
    S = g_IS.Components
    Call QuickSortStrings(S)
    
    For I = LBound(S) To UBound(S)
        If S(I) <> "" Then
            P = S(I)                                                            'Get the component path
            DI = g_IS.Item(P)                                                   'Get it's information
            N = String(StrCount(P, "\") - 2, "--") + NameFromPath(P)            'Add in "--"s to show a hierarchy
            F = F + N + String(30 - Len(N), " ") + "(" + DI.PID + ")" + vbCrLf  'Keep generating our string.
        End If
    Next
    
    'Finish up the report.
    txt.Text = String(60, "*") + vbCrLf + "Component Name" + String(30 - 14, " ") + "Component Type" + vbCrLf + String(60, "*") + vbCrLf + F

End Sub

Private Sub Form_Resize()

    txt.Move txt.Left, txt.Top, Me.ScaleWidth - (txt.Left * 2), ocb.Top - (txt.Top * 2)

End Sub

Private Sub ocb_OnCancel()
    Me.Hide
End Sub

Private Sub ocb_OnOK()
    Me.Hide
End Sub
