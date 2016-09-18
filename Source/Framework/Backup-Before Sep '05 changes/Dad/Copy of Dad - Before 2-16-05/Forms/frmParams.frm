VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form frmParams 
   Caption         =   "Specify Parameters Wizard"
   ClientHeight    =   5760
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6600
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   ScaleHeight     =   384
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   440
   StartUpPosition =   3  'Windows Default
   Begin MSComctlLib.ListView lvw 
      Height          =   3855
      Left            =   120
      TabIndex        =   2
      Top             =   960
      Width           =   6255
      _ExtentX        =   11033
      _ExtentY        =   6800
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
      NumItems        =   3
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
   End
   Begin IMA2_HelperX.WizardBar WizardBar1 
      Align           =   1  'Align Top
      Height          =   855
      Left            =   0
      TabIndex        =   1
      Top             =   0
      Width           =   6600
      _ExtentX        =   11642
      _ExtentY        =   1508
      C               =   "Specify Parameters Wizard"
   End
   Begin IMA2_HelperX.OKCancelBar OKCancelBar1 
      Align           =   2  'Align Bottom
      Height          =   570
      Left            =   0
      TabIndex        =   0
      Top             =   5190
      Width           =   6600
      _ExtentX        =   11642
      _ExtentY        =   1005
   End
End
Attribute VB_Name = "frmParams"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
    Option Explicit
    
    Public Sub ShowDialog()
       lvw.ColumnHeaders(2).Position = 1:        Me.Show vbModal
    End Sub
    
    Private Sub Form_Resize()
        lvw.Width = Me.ScaleWidth - (lvw.Left * 2)
        lvw.Height = Me.ScaleHeight - (lvw.Left * 1) - OKCancelBar1.Height - lvw.Top
        lvw.ColumnHeaders(1).Width = lvw.Width - lvw.ColumnHeaders(2).Width - lvw.ColumnHeaders(3).Width - 6
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

    Private Sub OKCancelBar1_OnCancel()
        Me.Hide
    End Sub
    
    Private Sub OKCancelBar1_OnOK()
        Me.Hide
    End Sub
    
    Public Sub AddItem(Name As String, TypeStr As String, Value As String)
        Dim LI As ListItem
        Set LI = lvw.ListItems.Add(, Name, Value)
        LI.SubItems(1) = Name
        LI.SubItems(2) = TypeStr
    End Sub
    
    Public Sub Clear()
        lvw.ListItems.Clear
    End Sub

