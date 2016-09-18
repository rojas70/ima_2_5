VERSION 5.00
Object = "{7B492EBB-3B8A-4D7E-9021-86BB71534052}#1.1#0"; "IMA2_HelperX.ocx"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "mscomctl.ocx"
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
   Begin IMA2_HelperX.OKCancelBar OKCancelBar1 
      Align           =   2  'Align Bottom
      Height          =   570
      Left            =   0
      TabIndex        =   0
      Top             =   5100
      Width           =   6480
      _ExtentX        =   11430
      _ExtentY        =   1005
   End
   Begin MSComctlLib.ListView lvw 
      Height          =   1215
      Left            =   0
      TabIndex        =   4
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
      TabIndex        =   5
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
      TabIndex        =   6
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
      TabIndex        =   3
      Top             =   3480
      Width           =   1575
   End
   Begin VB.Label Label2 
      Caption         =   "Optional Variables"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   1800
      Width           =   1335
   End
   Begin VB.Label Label1 
      Caption         =   "Input Variables"
      Height          =   255
      Left            =   120
      TabIndex        =   1
      Top             =   120
      Width           =   1335
   End
End
Attribute VB_Name = "frmParams"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
   'Edited for actual functionality in Feb '05 by Christina and Juan
    
    Private m_Values() As Variant
    
    Option Explicit
    
    
    Public Sub ShowDialog()
        lvw.ColumnHeaders(2).Position = 1
        lvw2.ColumnHeaders(2).Position = 1
        lvw3.ColumnHeaders(2).Position = 1
        Me.Show vbModal
    End Sub
    
    Public Property Get Values() As Variant
        Values = m_Values
    End Property

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
        lvw.Height = (OKCancelBar1.Top - 97) / 3
        lvw2.Height = (OKCancelBar1.Top - 97) / 3
        lvw3.Height = (OKCancelBar1.Top - 97) / 3
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


    Private Sub OKCancelBar1_OnCancel()
        Me.Hide
    End Sub
    
    Private Sub OKCancelBar1_OnOK()
        Dim I As Integer
        Dim LI As ListItem
        Dim ArgCount As Integer
        Dim WhichType() As Integer
        Dim Names() As String
        
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
                        m_Values(I) = Array(CDbl(Split(Trim(Mid(LI.Text, 2, Len(LI.Text) - 2)), " ")))
                    Else
                        m_Values(I) = Array(CDbl(LI.Text))
                    End If
                End If
            Case "Long *":
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

