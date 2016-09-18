VERSION 5.00
Object = "{5E9E78A0-531B-11CF-91F6-C2863C385E30}#1.0#0"; "MSFLXGRD.OCX"
Begin VB.UserControl VectorMgr 
   ClientHeight    =   4335
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   10665
   ScaleHeight     =   289
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   711
   Begin VB.Frame Frame3 
      Caption         =   "Other Cmmands"
      Height          =   735
      Left            =   5400
      TabIndex        =   16
      Top             =   3480
      Width           =   5175
      Begin VB.CommandButton cmdAddNewVector 
         Caption         =   "Add &New Vector"
         Height          =   375
         Left            =   120
         TabIndex        =   9
         Top             =   240
         Width           =   1575
      End
      Begin VB.CommandButton cmdexcel 
         Caption         =   "&Export to Excel"
         Height          =   375
         Left            =   3480
         TabIndex        =   11
         Top             =   240
         Width           =   1575
      End
      Begin VB.CommandButton cmdRefresh 
         Caption         =   "&Refresh"
         Height          =   375
         Left            =   1800
         TabIndex        =   10
         Top             =   240
         Width           =   1575
      End
   End
   Begin VB.TextBox txtAddgrid 
      Height          =   285
      Left            =   9240
      TabIndex        =   13
      Text            =   "0"
      Top             =   5520
      Width           =   1335
   End
   Begin VB.Frame Frame1 
      Height          =   135
      Left            =   0
      TabIndex        =   12
      Top             =   3240
      Width           =   10575
   End
   Begin VB.TextBox txtvalue 
      Height          =   285
      Left            =   9240
      TabIndex        =   5
      Top             =   480
      Width           =   1335
   End
   Begin VB.TextBox txtLength 
      Height          =   285
      Left            =   7320
      TabIndex        =   4
      Top             =   480
      Width           =   1215
   End
   Begin VB.TextBox txtIndex 
      Height          =   285
      Left            =   5400
      TabIndex        =   3
      Top             =   480
      Width           =   1215
   End
   Begin VB.TextBox txtVectorLength 
      Height          =   285
      Left            =   1080
      TabIndex        =   1
      Top             =   480
      Width           =   1215
   End
   Begin VB.TextBox txtSignalLength 
      Height          =   285
      Left            =   3480
      TabIndex        =   2
      Top             =   480
      Width           =   1335
   End
   Begin VB.Frame Frame2 
      Caption         =   "Update Command"
      Height          =   735
      Left            =   120
      TabIndex        =   0
      Top             =   3480
      Width           =   5175
      Begin VB.CommandButton cmdUpdateIni 
         Caption         =   "&Initial Data"
         Height          =   375
         Left            =   120
         TabIndex        =   6
         Top             =   240
         Width           =   1575
      End
      Begin VB.CommandButton cmdUpdateall 
         Caption         =   "&All Vectors"
         Height          =   375
         Left            =   3480
         TabIndex        =   8
         Top             =   240
         Width           =   1575
      End
      Begin VB.CommandButton cmdUpdateCurrent 
         Caption         =   "&Current Vector"
         Height          =   375
         Left            =   1800
         TabIndex        =   7
         Top             =   240
         Width           =   1575
      End
   End
   Begin MSFlexGridLib.MSFlexGrid grdAddVec 
      Height          =   855
      Left            =   0
      TabIndex        =   14
      Top             =   4440
      Width           =   10575
      _ExtentX        =   18653
      _ExtentY        =   1508
      _Version        =   393216
   End
   Begin MSFlexGridLib.MSFlexGrid grdVecData 
      Height          =   2295
      Left            =   0
      TabIndex        =   15
      Top             =   840
      Width           =   10575
      _ExtentX        =   18653
      _ExtentY        =   4048
      _Version        =   393216
      Rows            =   3
      Cols            =   5
      FocusRect       =   2
      HighLight       =   2
      AllowUserResizing=   3
   End
   Begin VB.Label Label6 
      AutoSize        =   -1  'True
      Caption         =   "Value:"
      Height          =   195
      Left            =   8760
      TabIndex        =   22
      Top             =   480
      Width           =   450
   End
   Begin VB.Label Label5 
      AutoSize        =   -1  'True
      Caption         =   "Length:"
      Height          =   195
      Left            =   6720
      TabIndex        =   21
      Top             =   480
      Width           =   540
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "Index:"
      Height          =   195
      Left            =   4920
      TabIndex        =   20
      Top             =   480
      Width           =   435
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "VectorLength:"
      Height          =   195
      Left            =   0
      TabIndex        =   19
      Top             =   480
      Width           =   1005
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      Caption         =   "SignalLength:"
      Height          =   195
      Left            =   2400
      TabIndex        =   18
      Top             =   480
      Width           =   975
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
      Left            =   4560
      TabIndex        =   17
      Top             =   0
      Width           =   1560
   End
End
Attribute VB_Name = "VectorMgr"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Implements IManager
Dim m_comp As Vector
Dim para As Variant
Private Sub IManager_SetComponent(c As IMA2.IComponent)
    Set m_comp = c
    If Not (c Is Nothing) Then
        grdAddVec.Cols = m_comp.VectorLength + 1
        For i = 0 To m_comp.VectorLength - 1
            grdAddVec.Row = 0
            grdAddVec.Col = i + 1
            grdAddVec.Text = i
            grdAddVec.Row = 1
            grdAddVec.Col = i + 1
            grdAddVec.Text = "0"
        Next i
        cmdAddNewVector.Tag = 0
        grdVecData.ColWidth(0) = 1800
        Call cmdRefresh_Click
    End If
End Sub

Private Sub cmdAddNewVector_Click()
Dim i&
Dim dtData() As Double
    If cmdAddNewVector.Tag = 0 Then
        cmdAddNewVector.Caption = "&Update..."
        grdAddVec.Cols = m_comp.VectorLength + 1
        For i = 0 To m_comp.VectorLength - 1
            grdAddVec.Row = 0
            grdAddVec.Col = i + 1
            grdAddVec.Text = i
            grdAddVec.Row = 1
            grdAddVec.Col = i + 1
            grdAddVec.Text = "0"
        Next i
        UserControl.Height = 5350
        cmdAddNewVector.Tag = 1
    Else
        cmdAddNewVector.Caption = "&Add New Vector"
        ReDim dtData(m_comp.VectorLength)
        For i = 0 To m_comp.VectorLength - 1
            grdAddVec.Col = i + 1
            grdAddVec.Row = 1
            dtData(i) = CDbl(grdAddVec.Text)
        Next i
        UserControl.Height = 4330 '4335
        cmdAddNewVector.Tag = 0
        Call m_comp.SetCurrentVector(m_comp.VectorLength - 1, dtData())
        Call cmdRefresh_Click
    End If
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
    For i = 1 To grdVecData.Rows
        For j = 1 To grdVecData.Cols
            grdVecData.Row = i - 1
            grdVecData.Col = j - 1
            wSheet.Cells(i, j).Value = grdVecData.Text
        Next j
    Next i
End Sub

Private Sub cmdRefresh_Click()
Dim paraAs As Variant
Dim dtTime As Double, dtData() As Double
Dim c As IComponent
Dim pc As IContainer
Dim m_al As ILocator
Dim i&, j&, CurVector&
On Error GoTo errorhandler
    txtVectorLength.Text = m_comp.VectorLength
    txtSignalLength.Text = m_comp.SignalLength
    CurVector = m_comp.CurrentIndex
    grdVecData.Cols = m_comp.VectorLength + 1
    grdVecData.Rows = m_comp.SignalLength + 1
    grdVecData.Row = 0
    CurVector = m_comp.CurrentIndex + 1
    For i = 0 To m_comp.VectorLength - 1
        grdVecData.Col = i + 1
        grdVecData.Text = i
    Next i
    For i = 1 To m_comp.SignalLength
        dtData() = m_comp.getvector(CurVector + m_comp.SignalLength - i, m_comp.VectorLength, dtTime)  'Want to list vector
        grdVecData.Col = 0
        grdVecData.Row = i
        If i = CurVector Then
            grdVecData.Text = " Cur " + CStr(i) + " ==> " + CStr(dtTime)
        Else
            grdVecData.Text = "       " + CStr(i) + " ==> " + CStr(dtTime)
        End If
        For j = 0 To m_comp.VectorLength - 1
            grdVecData.Col = j + 1
            grdVecData.Row = i
            grdVecData.Text = dtData(j)
        Next j
    Next i
    Exit Sub
errorhandler:
    MsgBox ("Error on Command Refresh")
End Sub


Private Sub cmdUpdateall_Click()
Dim i&, j&
Dim tmpdata() As Double
On Error GoTo errorhander
ReDim tmpdata(m_comp.VectorLength)
    For i = 0 To m_comp.SignalLength - 1
        For j = 0 To m_comp.VectorLength - 1
            grdVecData.Col = j + 1
            grdVecData.Row = i + 1
            tmpdata(j) = grdVecData.Text
        Next j
        Call m_comp.SetVectorValue(m_comp.CurrentIndex + m_comp.SignalLength - i, m_comp.VectorLength, tmpdata())
        'Call m_comp.SetVector(i, m_comp.VectorLength - 1, tmpdata())
    Next i
    Call cmdRefresh_Click
    Exit Sub
errorhander:
    MsgBox "Could not complete the operation. Abort"
End Sub

Private Sub cmdUpdateCurrent_Click()
Dim i&, j&
On Error GoTo errorhander
    m_comp.CurrentIndex = grdVecData.Row - 1
    Call cmdRefresh_Click
    Exit Sub
errorhander:
    MsgBox "Could not complete the operation. Abort"
End Sub

Private Sub cmdUpdateIni_Click()
    If txtSignalLength.Text <> m_comp.SignalLength Then
        m_comp.SignalLength = txtSignalLength.Text
        Call m_comp.DoInitial
        Call cmdRefresh_Click
    End If
    If txtVectorLength.Text <> m_comp.VectorLength Then
        m_comp.VectorLength = txtVectorLength.Text
        Call m_comp.DoInitial
        Call cmdRefresh_Click
    End If
    
End Sub

Private Sub grdAddVec_Click()
    txtAddgrid.Text = grdAddVec.Text
    txtAddgrid.SetFocus
End Sub

Private Sub grdVecData_Click()
    txtIndex.Text = grdVecData.Row - 1
    txtLength.Text = grdVecData.Col - 1
    txtvalue.Text = grdVecData.Text
    txtvalue.SetFocus
End Sub

Private Sub grdVecData_DblClick()
    txtvalue.SetFocus
    'txtvalue.SelText
End Sub

Private Sub IManager_Update(Optional Flags As Variant)

End Sub

Private Sub txtAddgrid_Change()
    grdAddVec.Text = txtAddgrid.Text
End Sub

Private Sub txtvalue_Change()
'    grdVecData.Row = CLng(txtIndex.Text) + 1
'    grdVecData.Col = CLng(txtLength.Text) + 1
    grdVecData.Text = txtvalue.Text
End Sub

Private Sub UserControl_Initialize()

'    Set m_comp = CreateObject("vectorsignal.Vector", "yamato")
'    grdAddVec.Cols = m_comp.VectorLength + 1
'    For i = 0 To m_comp.VectorLength - 1
'        grdAddVec.Row = 0
'        grdAddVec.Col = i + 1
'        grdAddVec.Text = i
'        grdAddVec.Row = 1
'        grdAddVec.Col = i + 1
'        grdAddVec.Text = "0"
'    Next i
'    cmdAddNewVector.Tag = 0
'    grdVecData.ColWidth(0) = 1800
'    Call cmdRefresh_Click

End Sub

