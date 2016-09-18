VERSION 5.00
Object = "{B3B088D0-73D0-4791-9B45-C4B154DF8823}#1.1#0"; "IMA2_HelperX.ocx"
Begin VB.Form frmTextSummary 
   Caption         =   "Text-based IMA2 Network Summary "
   ClientHeight    =   3852
   ClientLeft      =   2772
   ClientTop       =   3768
   ClientWidth     =   6036
   Icon            =   "frmTextSummary.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   3852
   ScaleWidth      =   6036
   Begin IMA2_HelperX.OKCancelBar ocb 
      Align           =   2  'Align Bottom
      Height          =   432
      Left            =   0
      TabIndex        =   1
      Top             =   3420
      Width           =   6036
      _ExtentX        =   10647
      _ExtentY        =   762
   End
   Begin VB.TextBox txt 
      BeginProperty Font 
         Name            =   "Courier New"
         Size            =   7.8
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

    Dim AL As ILocator
    Dim S() As String
    Dim P As String
    Dim F As String
    Dim T As String
    Dim N As String
    Dim C As Integer
    Dim I As Integer
    Dim Cmp As IComponent
    
    Set AL = GetLocator()
    S = AL.Components
    Call QuickSortStrings(S)
    
    For I = LBound(S) To UBound(S)
        P = S(I)
        C = StrCount(P, "\")
        Set Cmp = AL.Locate(P)
        T = "(" + Cmp.PID + ")"
        N = String(C - 2, "--") + NameFromPath(P)
        F = F + N + String(30 - Len(N), " ") + T + vbCrLf
    Next
    
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
