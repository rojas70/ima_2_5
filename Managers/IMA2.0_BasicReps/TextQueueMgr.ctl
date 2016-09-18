VERSION 5.00
Object = "{5E9E78A0-531B-11CF-91F6-C2863C385E30}#1.0#0"; "MSFLXGRD.OCX"
Object = "{3B7C8863-D78F-101B-B9B5-04021C009402}#1.2#0"; "RICHTX32.OCX"
Begin VB.UserControl TextQueueMgr 
   ClientHeight    =   6345
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   10695
   ScaleHeight     =   423
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   713
   Begin VB.CommandButton cmdViewTxt 
      Caption         =   "&Maximize View"
      Height          =   375
      Left            =   7200
      TabIndex        =   12
      Top             =   480
      Width           =   1575
   End
   Begin VB.CommandButton cmdClose 
      Caption         =   "&Close"
      Height          =   375
      Left            =   8880
      TabIndex        =   11
      Top             =   480
      Width           =   1575
   End
   Begin VB.Frame Frame1 
      Height          =   135
      Left            =   120
      TabIndex        =   10
      Top             =   5280
      Width           =   10410
   End
   Begin VB.Frame Frame3 
      Caption         =   "Other Cmmands"
      Height          =   735
      Left            =   5400
      TabIndex        =   6
      Top             =   5520
      Width           =   5175
      Begin VB.CommandButton cmdAddNewVector 
         Caption         =   "Save as &New Text"
         Height          =   375
         Left            =   120
         TabIndex        =   9
         Top             =   240
         Width           =   1575
      End
      Begin VB.CommandButton cmdRefresh 
         Caption         =   "&Refresh"
         Height          =   375
         Left            =   3480
         TabIndex        =   8
         Top             =   240
         Width           =   1575
      End
      Begin VB.CommandButton cmdexcel 
         Caption         =   "&Export to Excel"
         Height          =   375
         Left            =   1800
         TabIndex        =   7
         Top             =   240
         Width           =   1575
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "Update Command"
      Height          =   735
      Left            =   120
      TabIndex        =   2
      Top             =   5520
      Width           =   5175
      Begin VB.CommandButton cmdUpdateCurrent 
         Caption         =   "Set &Current Text"
         Height          =   375
         Left            =   1800
         TabIndex        =   5
         Top             =   240
         Width           =   1575
      End
      Begin VB.CommandButton cmdUpdateall 
         Caption         =   "&All Text"
         Height          =   375
         Left            =   3480
         TabIndex        =   4
         Top             =   240
         Width           =   1575
      End
      Begin VB.CommandButton cmdUpdateIni 
         Caption         =   "&Initial Data"
         Height          =   375
         Left            =   120
         TabIndex        =   3
         Top             =   240
         Width           =   1575
      End
   End
   Begin VB.TextBox txtqueueLength 
      Height          =   285
      Left            =   1200
      TabIndex        =   1
      Top             =   480
      Width           =   1215
   End
   Begin VB.TextBox txtIndex 
      Height          =   285
      Left            =   3000
      TabIndex        =   0
      Top             =   480
      Width           =   1215
   End
   Begin RichTextLib.RichTextBox rtbQueue 
      Height          =   2535
      Left            =   120
      TabIndex        =   13
      Top             =   6360
      Width           =   10455
      _ExtentX        =   18441
      _ExtentY        =   4471
      _Version        =   393217
      TextRTF         =   $"TextQueueMgr.ctx":0000
   End
   Begin MSFlexGridLib.MSFlexGrid grdQueue 
      Height          =   4215
      Left            =   120
      TabIndex        =   14
      Top             =   960
      Width           =   10455
      _ExtentX        =   18441
      _ExtentY        =   7435
      _Version        =   393216
   End
   Begin VB.Label Label3 
      AutoSize        =   -1  'True
      Caption         =   "Text Queue"
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
      Left            =   4560
      TabIndex        =   17
      Top             =   0
      Width           =   1395
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "QueueLength:"
      Height          =   195
      Left            =   120
      TabIndex        =   16
      Top             =   480
      Width           =   1020
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "Index:"
      Height          =   195
      Left            =   2520
      TabIndex        =   15
      Top             =   480
      Width           =   435
   End
End
Attribute VB_Name = "TextQueueMgr"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Implements IManager
Dim m_comp As Object ' TextQueue
Dim para As Variant

Private Sub cmdAddNewVector_Click()
Dim i&
Dim dtData As String
    dtData = rtbQueue.Text
    Call m_comp.SetCurrenttext(dtData)
    Call cmdRefresh_Click
End Sub

Private Sub cmdexcel_Click()
Dim i&, j&
Dim wSheet As Worksheet
Dim wBook As Workbook
    Set appexcel = CreateObject("Excel.Application")
    appexcel.Visible = True
    If appexcel Is Nothing Then
        MsgBox "Could not start Excel."
        Exit Sub
    End If
    Set wBook = appexcel.Workbooks.Add
    Set wSheet = appexcel.Sheets(1)
    For i = 1 To grdQueue.Rows
        For j = 1 To grdQueue.Cols
            grdQueue.Row = i - 1
            grdQueue.Col = j - 1
            wSheet.Cells(i, j).Value = grdQueue.Text
        Next j
    Next i
End Sub

Private Sub cmdRefresh_Click()
Dim paraAs As Variant
Dim dtTime As Double, dtData() As Double
Dim i&, j&, CurVector&, tmpStr$

    txtqueueLength.Text = m_comp.queueLength
    CurVector = m_comp.CurrentIndex + 1
    grdQueue.Rows = m_comp.queueLength + 1
    For i = 1 To m_comp.queueLength
        tmpStr = m_comp.GetText(CurVector + m_comp.queueLength - i, dtTime)  'Want to list vector
        grdQueue.Col = 0
        grdQueue.Row = i
        If i = CurVector Then
            grdQueue.Text = " Cur " + CStr(i) + " ==> " + CStr(dtTime)
        Else
            grdQueue.Text = "       " + CStr(i) + " ==> " + CStr(dtTime)
        End If
        grdQueue.Col = 1
        grdQueue.Row = i
        grdQueue.Text = tmpStr
    Next i
    'Call m_comp.SetCurrentVector(3, para)
End Sub

Private Sub cmdUpdateall_Click()
Dim i&, j&
Dim tmpdata$
On Error GoTo errorhander
    For i = 0 To m_comp.queueLength - 1
        grdQueue.Col = 1
        grdQueue.Row = i + 1
        tmpdata = grdQueue.Text
        Call m_comp.SetTextvalue(m_comp.CurrentIndex + m_comp.queueLength - i, tmpdata)
    Next i
    Call cmdRefresh_Click
    Exit Sub
errorhander:
    MsgBox "Could complete the operation. Abort"
End Sub

Private Sub cmdUpdateCurrent_Click()
Dim i&, j&
On Error GoTo errorhander
    m_comp.CurrentIndex = grdQueue.Row - 1
    Call cmdRefresh_Click
    Exit Sub
errorhander:
    MsgBox "Could complete the operation. Abort"
End Sub

Private Sub cmdUpdateIni_Click()
    If Not (txtqueueLength.Text) = "" Then
    If CLng(txtqueueLength.Text) <> m_comp.queueLength Then
        m_comp.queueLength = txtqueueLength.Text
        Call m_comp.DoInitial
        Call cmdRefresh_Click
    End If
    End If
End Sub
Private Sub cmdView_Click()
End Sub

Private Sub cmdViewTxt_Click()
    If cmdViewTxt.Tag = 0 Then
        UserControl.Height = 9360
        cmdViewTxt.Caption = "&Minimize View"
        cmdViewTxt.Tag = 1
    Else
        UserControl.Height = 6810
        cmdViewTxt.Caption = "&Maximize View"
        cmdViewTxt.Tag = 0
    End If
End Sub

Private Sub Form_Load()
End Sub

Private Sub grdQueue_Click()
    txtIndex.Text = grdQueue.Row - 1
    rtbQueue.Text = grdQueue.Text
    rtbQueue.SetFocus
End Sub

Private Sub IManager_SetComponent(c As IMA2.IComponent)
    'Set m_comp = CreateObject("vectorsignal.ctextqueue", "ninja")
    'Set m_comp = CreateObject("vectorsignal.ctextqueue", "yamato")
    Set m_comp = c
    If Not (c Is Nothing) Then
        cmdViewTxt.Tag = 0
        grdQueue.ColWidth(0) = 1800
        grdQueue.ColWidth(1) = 8500
        grdQueue.Cols = m_comp.queueLength + 1
        rtbQueue.Text = ""
        Call m_comp.DoInitial
        Call cmdRefresh_Click
    End If
    
End Sub

Private Sub IManager_Update(Optional Flags As Variant)

End Sub

Private Sub rtbQueue_Change()
    grdQueue.Text = rtbQueue.Text
End Sub

Private Sub UserControl_Initialize()
    'Set m_comp = CreateObject("vectorsignal.ctextqueue", "ninja")
    'Set m_comp = CreateObject("vectorsignal.ctextqueue", "yamato")
    'cmdViewTxt.Tag = 0
    'grdQueue.ColWidth(0) = 1800
    'grdQueue.ColWidth(1) = 8500
    'grdQueue.Cols = m_comp.queueLength + 1
    'rtbQueue.Text = ""
    'Call m_comp.DoInitial
    'Call cmdRefresh_Click
End Sub

