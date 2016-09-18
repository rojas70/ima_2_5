VERSION 5.00
Begin VB.Form frmConnect 
   Caption         =   "Connect to Computers"
   ClientHeight    =   3792
   ClientLeft      =   60
   ClientTop       =   348
   ClientWidth     =   5172
   LinkTopic       =   "Form1"
   ScaleHeight     =   3792
   ScaleWidth      =   5172
   StartUpPosition =   3  'Windows Default
   Begin VB.CheckBox chkUsePreset 
      Caption         =   "Use Preset"
      Height          =   195
      Left            =   2760
      TabIndex        =   4
      Top             =   600
      Width           =   1575
   End
   Begin VB.CommandButton cmdCancel 
      Caption         =   "Cancel"
      Height          =   495
      Left            =   3480
      TabIndex        =   3
      Top             =   3120
      Width           =   1215
   End
   Begin VB.CommandButton cmdConnect 
      Caption         =   "Connect"
      Height          =   495
      Left            =   1920
      TabIndex        =   2
      Top             =   3120
      Width           =   1215
   End
   Begin VB.ListBox listpresets 
      Height          =   1968
      Left            =   2640
      TabIndex        =   1
      Top             =   840
      Width           =   2175
   End
   Begin VB.ListBox listcompnames 
      Height          =   1968
      Left            =   240
      MultiSelect     =   1  'Simple
      TabIndex        =   0
      Top             =   840
      Width           =   2055
   End
   Begin VB.Label Label1 
      Caption         =   "Select the computers to connect to."
      Height          =   255
      Left            =   360
      TabIndex        =   5
      Top             =   120
      Width           =   4575
   End
End
Attribute VB_Name = "frmConnect"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim Presets() As String

Private Sub chkUsePreset_Click()
    listpresets.Enabled = chkUsePreset.Value
End Sub

Private Sub cmdCancel_Click()
    Me.Hide
End Sub

Private Sub cmdConnect_Click()
    Dim connect As VbMsgBoxResult
    Dim Computer As String
    Dim I As Integer
    
    connect = MsgBox("Please make sure that all selected computers are logged into" & Chr$(13) & _
        "and that DAD is running on each before continuing." & Chr$(13) & _
        "Failure to do this will crash DAD!", vbOKCancel, "Confirm Readiness")
       
    If (connect = vbCancel) Then Exit Sub
    
    On Error Resume Next
    Err.Clear
    
    For I = 0 To listcompnames.ListCount - 1
        If (listcompnames.Selected(I) = True) Then
            Computer = listcompnames.List(I)
            If (Computer <> "") Then
                If (UCase(g_AL.Machine) <> UCase(Computer)) Then
                       Call g_LA.connect(Computer)
                End If
            End If
            If Err Then
            '    MsgBoxString = MsgBoxString & UCase(Computer) & ": (" & Err & ") " & Err.Description & Chr$(13)
                Err.Clear
            End If
         End If
    Next I
    
    Me.Hide
End Sub

Private Sub Form_Load()
    Dim Computer As String
    Dim PresetCount As Integer
    Dim I As Integer
    
    On Error Resume Next
    
    Open "O:\System\Locator Settings2.txt" For Input As #1
    If Err Then
        MsgBox ("Cannot connect because file O:\System\Locator Settings2.txt is not found.")
        Err.Clear
        Exit Sub
    End If
    Input #1, Computer
    
    While (Err = 0)
        listcompnames.AddItem Computer
        Input #1, Computer
    Wend
    Err.Clear
    
    Close #1
    Open "O:\System\Locator Presets.txt" For Input As #1
    If Err Then
        ReDim Presets(1 To 0)
        Err.Clear
        chkUsePreset.Enabled = False
        Exit Sub
    End If
    Input #1, PresetCount
    ReDim Presets(1 To PresetCount)
    
    Err.Clear
    For I = 1 To PresetCount
        Input #1, Computer
        If Err Then
            Close #1
            ReDim Preserve Presets(1 To I - 1)
            Err.Clear
            Exit For
        End If
        Presets(I) = Computer
    Next I
    Close #1
    
    For I = LBound(Presets) To UBound(Presets)
        Computer = Left(Presets(I), InStr(1, Presets(I), ":") - 1)
        listpresets.AddItem Computer
    Next I
        
    listpresets.Enabled = False
    chkUsePreset.Value = 0
End Sub

Private Sub listpresets_Click()
    Dim Computers() As String
    Dim Splits() As String
    Dim Item As Integer
    Dim I As Integer
    Dim J As Integer
    
    Item = listpresets.ListIndex + 1
    
    Splits = Split(Presets(Item), ":")
    Computers = Split(Splits(1), ";")
    
    
    For J = 0 To listcompnames.ListCount - 1
        listcompnames.Selected(J) = False
        For I = LBound(Computers) To UBound(Computers)
            If (StrComp(UCase(listcompnames.List(J)), UCase(Trim(Computers(I)))) = 0) Then
                listcompnames.Selected(J) = True
                Exit For
            End If
        Next I
    Next J
End Sub
