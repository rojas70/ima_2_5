VERSION 5.00
Object = "{7B492EBB-3B8A-4D7E-9021-86BB71534052}#1.1#0"; "IMA2_HelperX.ocx"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{81605258-1A3B-47EE-A9BE-4F1963575A0F}#1.1#0"; "IMA2_DadX.ocx"
Begin VB.Form frmAdd 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Add Manager"
   ClientHeight    =   3660
   ClientLeft      =   48
   ClientTop       =   336
   ClientWidth     =   7428
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3660
   ScaleWidth      =   7428
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin MSComctlLib.ListView lvw 
      Height          =   2655
      Left            =   3840
      TabIndex        =   2
      Top             =   360
      Width           =   3495
      _ExtentX        =   6160
      _ExtentY        =   4678
      View            =   3
      LabelEdit       =   1
      Sorted          =   -1  'True
      LabelWrap       =   -1  'True
      HideSelection   =   0   'False
      HideColumnHeaders=   -1  'True
      _Version        =   393217
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   1
      BeginProperty ColumnHeader(1) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         Text            =   "Name"
         Object.Width           =   2540
      EndProperty
   End
   Begin IMA2_HelperX.PIDBar pbr 
      Height          =   495
      Left            =   0
      TabIndex        =   1
      Top             =   3120
      Width           =   7335
      _ExtentX        =   12933
      _ExtentY        =   868
   End
   Begin IMA2_DADX.AgentTreeview atv 
      Height          =   2655
      Left            =   120
      TabIndex        =   0
      Top             =   360
      Width           =   3615
      _ExtentX        =   6371
      _ExtentY        =   4678
   End
   Begin VB.Label Label2 
      Caption         =   "Manager Control:"
      Height          =   255
      Left            =   3960
      TabIndex        =   4
      Top             =   120
      Width           =   1335
   End
   Begin VB.Label Label1 
      Caption         =   "Component:"
      Height          =   255
      Left            =   360
      TabIndex        =   3
      Top             =   120
      Width           =   975
   End
End
Attribute VB_Name = "frmAdd"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Public Enum ManAddChoice
    MAC_Cancel = 0
    MAC_OK = 1
End Enum

Dim m_Libs As New Libraries
Dim m_Choice As ManAddChoice
Dim m_Net As New NetList
Dim m_Path As String
Dim m_PID As String

'The following code (for resizing columns) was adapted from code found
'at buygold.net:VB tips -CLC
Private Const LVM_FIRST = &H1000&
Private Const LVM_SETCOLUMNWIDTH = (LVM_FIRST + 30)
Private Const LVSCW_AUTOSIZE            As Long = -1
Private Declare Function SendMessage Lib "User32" Alias "SendMessageA" _
       (ByVal hwnd As Long, ByVal Msg As Long, ByVal wParam As Long, ByVal lParam As Long) As Long


Private Sub Form_Load()
    Dim FP      As String
    Dim LI      As LibInfo
    Dim CI      As ClsInfo
    
    
    FP = "C:\IMA2\Managers"
    m_Libs.Path = FP

    For Each LI In m_Libs
        If InStr(1, LI.Path, ".ocx") <> 0 Then
            For Each CI In LI.Classes
                If InStr(1, CI.Interfaces, "IManager") <> 0 Then
                    lvw.ListItems.Add , CI.PID, NameFromPath(LI.Path) & ":" & CI.Name
                End If
            Next
        End If
    Next
    Set lvw.SelectedItem = lvw.ListItems(1)
    lvw.ListItems(1).Selected = False
    Set lvw.SelectedItem = Nothing
    lvw.Enabled = False
    Call SendMessage(lvw.hwnd, LVM_SETCOLUMNWIDTH, 0, LVSCW_AUTOSIZE)
    
    m_Net.Refresh
    
    Set atv.NetList = m_Net
End Sub


Private Sub lvw_Click()
    pbr.PID = lvw.SelectedItem.Key
    m_PID = lvw.SelectedItem.Key
End Sub

Private Sub atv_NodeClick(ByVal Node As MSComctlLib.INode)
    m_Path = atv.Path
    If Node.Image <> II_Locator And Node.Image <> II_Network And Node.Image <> 15 Then
        lvw.Enabled = True
    Else
        lvw.Enabled = False
        If Not (lvw.SelectedItem Is Nothing) Then
            lvw.SelectedItem.Selected = False
        End If
        pbr.PID = ""
        m_PID = ""
    End If
End Sub

Private Sub pbr_OnCancel()
    m_Choice = MAC_Cancel
    Me.Hide
End Sub

Private Sub pbr_OnOK()
    m_Choice = MAC_OK
    Me.Hide
End Sub

Public Property Get Choice() As ManAddChoice
    Choice = m_Choice
End Property

Public Property Get Path() As String
    Path = m_Path
End Property

Public Property Get PID() As String
    PID = m_PID
End Property
