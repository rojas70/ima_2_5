VERSION 5.00
Begin VB.Form frmParams 
   Caption         =   "Call Method"
   ClientHeight    =   5670
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6480
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   ScaleHeight     =   378
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   432
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton CancelButton 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   5160
      TabIndex        =   7
      Top             =   5280
      Width           =   1215
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "Call Method"
      Height          =   375
      Left            =   3480
      TabIndex        =   6
      Top             =   5280
      Width           =   1455
   End
   Begin MSComctlLib.ListView lvw 
      Height          =   1215
      Left            =   0
      TabIndex        =   3
      Top             =   360
      Width           =   6495
      _ExtentX        =   11456
      _ExtentY        =   2143
      View            =   3
      LabelEdit       =   1
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      AllowReorder    =   -1  'True
      _Version        =   393217
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   4
      BeginProperty ColumnHeader(1) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         Text            =   "Value"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(2) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   1
         Text            =   "Name"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(3) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   2
         Text            =   "Type"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(4) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   3
         Text            =   "ArgNum"
         Object.Width           =   265
      EndProperty
   End
   Begin MSComctlLib.ListView lvw2 
      Height          =   1215
      Left            =   0
      TabIndex        =   4
      Top             =   2040
      Width           =   6495
      _ExtentX        =   11456
      _ExtentY        =   2143
      View            =   3
      LabelEdit       =   1
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      AllowReorder    =   -1  'True
      _Version        =   393217
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   4
      BeginProperty ColumnHeader(1) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         Text            =   "Value"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(2) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   1
         Text            =   "Name"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(3) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   2
         Text            =   "Type"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(4) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   3
         Text            =   "ArgNum"
         Object.Width           =   265
      EndProperty
   End
   Begin MSComctlLib.ListView lvw3 
      Height          =   1215
      Left            =   0
      TabIndex        =   5
      Top             =   3720
      Width           =   6495
      _ExtentX        =   11456
      _ExtentY        =   2143
      View            =   3
      LabelEdit       =   1
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      AllowReorder    =   -1  'True
      _Version        =   393217
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      Enabled         =   0   'False
      NumItems        =   4
      BeginProperty ColumnHeader(1) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         Text            =   "Value"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(2) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   1
         Text            =   "Name"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(3) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   2
         Text            =   "Type"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(4) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   3
         Text            =   "ArgNum"
         Object.Width           =   265
      EndProperty
   End
   Begin VB.Label Label3 
      Caption         =   "Outputs"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   3480
      Width           =   1575
   End
   Begin VB.Label Label2 
      Caption         =   "Optional Variables"
      Height          =   255
      Left            =   120
      TabIndex        =   1
      Top             =   1800
      Width           =   1335
   End
   Begin VB.Label Label1 
      Caption         =   "Input Variables"
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1335
   End
End
Attribute VB_Name = "frmParams"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
   'Edited for actual functionality in Spring '05 by Christina and Juan
   'This has been almost complete redone from Roberto's work. Just about
   'The only thing here from before are function names.
    
    Private m_Values() As Variant
    
    Option Explicit
    
    
    Public Sub ShowDialog(Optional BeforeCall As Integer = 1)
        lvw.ColumnHeaders(2).Position = 1
        lvw2.ColumnHeaders(2).Position = 1
        lvw3.ColumnHeaders(2).Position = 1
        If (BeforeCall = 1) Then
            CancelButton.Caption = "Cancel"
            OKButton.Enabled = True
        Else
            CancelButton.Caption = "Done"
            OKButton.Enabled = False
        End If
        
        Me.Show vbModal
    End Sub
    
    Public Property Get Values() As Variant
        Values = m_Values
    End Property
    
    Public Property Get ReverseValues() As Variant
        'This r
        On Error Resume Next
        Dim tmp() As Variant
        Dim I As Integer
        I = UBound(m_Values)
        If (Err) Then
            Values = Nothing
            Exit Property
        End If
        ReDim tmp(LBound(m_Values) To UBound(m_Values))
        For I = LBound(m_Values) To UBound(m_Values)
            tmp(UBound(m_Values) + LBound(m_Values) - I) = m_Values(I)
        Next
        ReverseValues = tmp
    End Property

    Private Sub CancelButton_Click()
        Me.Hide
    End Sub

    Private Sub Form_Resize()
        If Me.Height < 4875 Then
            Me.Height = 4875
            If Me.ScaleWidth < lvw.ColumnHeaders(2).Width * 3 Then
                Me.Width = 4440
            End If
            Exit Sub
        End If
        If Me.ScaleWidth < lvw.ColumnHeaders(2).Width * 3 Then
            Me.Width = 4440
            Exit Sub
        End If
        
        lvw.Width = Me.ScaleWidth
        lvw2.Width = Me.ScaleWidth
        lvw3.Width = Me.ScaleWidth
        lvw.Height = (Me.ScaleHeight - 38 - 97) / 3
        lvw2.Height = (Me.ScaleHeight - 38 - 97) / 3
        lvw3.Height = (Me.ScaleHeight - 38 - 97) / 3
        Label2.Top = lvw.Top + lvw.Height + 16
        lvw2.Top = Label2.Top + 16
        Label3.Top = lvw2.Top + lvw2.Height + 16
        lvw3.Top = Label3.Top + 16
        lvw.ColumnHeaders(1).Width = Round(lvw.Width - lvw.ColumnHeaders(2).Width - lvw.ColumnHeaders(3).Width - 6)
        lvw2.ColumnHeaders(1).Width = Round(lvw.Width - lvw.ColumnHeaders(2).Width - lvw.ColumnHeaders(3).Width - 6)
        lvw3.ColumnHeaders(1).Width = Round(lvw.Width - lvw.ColumnHeaders(2).Width - lvw.ColumnHeaders(3).Width - 6)
    End Sub


    Private Sub lvw_KeyDown(KeyCode As Integer, Shift As Integer)
        If KeyCode = vbKeyUp Then Exit Sub
        If KeyCode = vbKeyDown Then Exit Sub
        lvw.StartLabelEdit
    End Sub

    Private Sub lvw_MouseUp(Button As Integer, Shift As Integer, x As Single, y As Single)
        If lvw.HitTest(x, y) Is Nothing Then Exit Sub
        Set lvw.SelectedItem = lvw.HitTest(x, y)
        lvw.StartLabelEdit
    End Sub
    Private Sub lvw2_KeyDown(KeyCode As Integer, Shift As Integer)
        If KeyCode = vbKeyUp Then Exit Sub
        If KeyCode = vbKeyDown Then Exit Sub
        lvw2.StartLabelEdit
    End Sub

    Private Sub lvw2_MouseUp(Button As Integer, Shift As Integer, x As Single, y As Single)
        If lvw2.HitTest(x, y) Is Nothing Then Exit Sub
        Set lvw2.SelectedItem = lvw2.HitTest(x, y)
        lvw2.StartLabelEdit
    End Sub

    
    
    Public Sub AddItem(Name As String, TypeStr As String, Value As String, InOptOut As Integer, ArgNum As Integer)
        Dim LI As ListItem
        Select Case InOptOut
        Case 0:
            Set LI = lvw.ListItems.Add(, Name, Value)
        Case 1:
            Set LI = lvw2.ListItems.Add(, Name, Value)
        Case 2:
            Set LI = lvw3.ListItems.Add(, Name, Value)
        End Select
        LI.SubItems(1) = Name
        LI.SubItems(2) = TypeStr
        LI.SubItems(3) = ArgNum
    End Sub
    
    Public Sub Clear()
        lvw.ListItems.Clear
    End Sub

    Private Sub OKButton_Click()
        Dim I As Integer
        Dim LI As ListItem
        Dim ArgCount As Integer
        Dim WhichType() As Integer
        Dim Names() As String
        Dim tmp() As String
        Dim tmp2() As Double
        Dim tmp3() As Integer
        Dim J As Integer
        
    
        ArgCount = lvw.ListItems.Count + lvw2.ListItems.Count + lvw3.ListItems.Count
        ReDim WhichType(0 To ArgCount - 1)
        ReDim Names(0 To ArgCount - 1)
        ReDim m_Values(0 To ArgCount - 1)
        
        For I = 1 To lvw.ListItems.Count
            Set LI = lvw.ListItems.Item(I)
            WhichType(LI.SubItems(3)) = 0
            Names(LI.SubItems(3)) = LI.SubItems(1)
        Next I
        For I = 1 To lvw2.ListItems.Count
            Set LI = lvw2.ListItems.Item(I)
            WhichType(LI.SubItems(3)) = 1
            Names(LI.SubItems(3)) = LI.SubItems(1)
        Next I
        For I = 1 To lvw3.ListItems.Count
            Set LI = lvw3.ListItems.Item(I)
            WhichType(LI.SubItems(3)) = 2
            Names(LI.SubItems(3)) = LI.SubItems(1)
        Next I
        
        For I = 0 To ArgCount - 1
            Select Case WhichType(I)
            Case 0: Set LI = lvw.ListItems(Names(I))
            Case 1: Set LI = lvw2.ListItems(Names(I))
            Case 2: Set LI = lvw3.ListItems(Names(I))
            End Select
            
            Trim (LI.Text)
            Select Case LI.SubItems(2)
            Case "BSTR": m_Values(I) = LI.Text
            Case "Double": m_Values(I) = CDbl(LI.Text)
            Case "Long": m_Values(I) = CLng(LI.Text)
            Case "Double*":
                If WhichType(I) = 2 Then
                    m_Values(I) = Array()
                Else
                    If InStr(LI.Text, "[") Then
                        tmp = Split(Trim(Mid(LI.Text, 2, Len(LI.Text) - 2)), ",")
                        ReDim tmp2(LBound(tmp) To UBound(tmp))
                        For J = LBound(tmp) To UBound(tmp)
                            tmp2(J) = CDbl(tmp(J))
                        Next
                        m_Values(I) = tmp2
                    Else
                        m_Values(I) = Array(CDbl(LI.Text))
                    End If
                End If
            Case "Long*":
                 If WhichType(I) = 2 Then
                    m_Values(I) = Array()
                Else
                    If InStr(LI.Text, "[") Then
                        m_Values(I) = Array(CLng(Split(Trim(Mid(LI.Text, 2, Len(LI.Text) - 2)), " ")))
                    Else
                        m_Values(I) = Array(CLng(LI.Text))
                    End If
                End If
            End Select
           
        Next I
        Me.Hide

    End Sub
