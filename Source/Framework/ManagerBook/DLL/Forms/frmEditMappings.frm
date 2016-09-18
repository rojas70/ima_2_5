VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form frmEditMappings 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Manager Mappings"
   ClientHeight    =   5310
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   7110
   Icon            =   "frmEditMappings.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   354
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   474
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin MSComctlLib.ListView lvw 
      Height          =   3495
      Left            =   3120
      TabIndex        =   3
      Top             =   1200
      Width           =   3855
      _ExtentX        =   6800
      _ExtentY        =   6165
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      _Version        =   393217
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   0
   End
   Begin MSComctlLib.TreeView tvw 
      Height          =   3495
      Left            =   120
      TabIndex        =   2
      Top             =   1200
      Width           =   2895
      _ExtentX        =   5106
      _ExtentY        =   6165
      _Version        =   393217
      Style           =   7
      Appearance      =   1
   End
   Begin ManagerBook.WizardBar wzb 
      Align           =   1  'Align Top
      Height          =   1095
      Left            =   0
      TabIndex        =   1
      Top             =   0
      Width           =   7110
      _ExtentX        =   12541
      _ExtentY        =   1931
      C               =   "Please select a manager for your component."
      D               =   $"frmEditMappings.frx":0442
      Picture         =   "frmEditMappings.frx":04D3
   End
   Begin ManagerBook.OKCancelBar ocb 
      Align           =   2  'Align Bottom
      Height          =   495
      Left            =   0
      TabIndex        =   0
      Top             =   4815
      Width           =   7110
      _ExtentX        =   12541
      _ExtentY        =   873
   End
End
Attribute VB_Name = "frmEditMappings"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim m_Icons As New IMA2_Helper.IconManager

Public MPID As String


Public Property Get MPIDs() As String

    Dim I   As Integer
    Dim S   As String
    
    For I = 1 To lvwDef.ListItems.Count
        S = S + lvwDef.ListItems(I).Text + ","
    Next
    
    S = Left(S, Len(S) - 1)
    
    MPIDs = S

End Property


Private Sub Form_Load()

    m_Icons.Directory = "C:\IMA2\System\Icons"
    Set lvwDef.SmallIcons = m_Icons.ImageList
    lvwDef.ColumnHeaders(1).Width = (lvwDef.Width - 70) * 0.7
    lvwDef.ColumnHeaders(2).Width = (lvwDef.Width - 70) * 0.3

End Sub

Private Sub Form_Resize()

'    On Error Resume Next
    
 '   tbs.Move tbs.Left, tbs.Top, Me.ScaleWidth - tbs.Left * 2, (ocb.Top - tbs.Top) - (tbs.Left * 1.5)
  '  lvwDef.Width = (tbs.Width * Screen.TwipsPerPixelX) - lvwDef.Left * 2
    'lvwDef.Height = (tbs.Height * Screen.TwipsPerPixelY) - lvwDef.Top * 1.5
    'icv.Height = lvwDef.Height
    'icv.Width = lvwDef.Width
    
    'lvwDef.Move lvwDef.Left, lvwDef.Top, (tbs.Width * Screen.TwipsPerPixelX) - (lvwDef.Left * 2), (tbs.Height * Screen.TwipsPerPixelY) - (lvwDef.Top * 1.5)
   ' lvwDef.ColumnHeaders(2).Width = lvwDef.Width - lvwDef.ColumnHeaders(1).Width - 70
    'icv.Move lvwDef.Left, lvwDef.Top, lvwDef.Width, lvwDef.Height

End Sub

Private Sub icv_OnOK()
    
    On Error Resume Next
    
    Dim L As ListItem
    
    tbs.Tab = 0
    Set L = lvwDef.ListItems(icv.ClsInfo.PID)
    Set lvwDef.SelectedItem = L
    
    If NN(L) Then Exit Sub
    
    If m_Icons.IconExists(icv.ClsInfo.PID) Then
        lvwDef.ListItems.Add(, icv.ClsInfo.PID, icv.ClsInfo.PID, , m_Icons.IconIndex(icv.ClsInfo.PID)).SubItems(1) = NameFromPath(icv.LibInfo.Path)
    Else
        lvwDef.ListItems.Add(, icv.ClsInfo.PID, icv.ClsInfo.PID, , II_Manager).SubItems(1) = NameFromPath(icv.LibInfo.Path)
    End If
    
    Set lvwDef.SelectedItem = lvwDef.ListItems(icv.ClsInfo.PID)
    lvwDef.SetFocus
    
End Sub

Private Sub lvwDef_DblClick()
    Call ocb_OnOK
End Sub

Private Sub lvwDef_KeyUp(KeyCode As Integer, Shift As Integer)

    If KeyCode = vbKeyDelete Then lvwDef.ListItems.Remove lvwDef.SelectedItem.Index

End Sub

Private Sub ocb_OnCancel()

    MPID = ""
    Me.Hide

End Sub

Private Sub ocb_OnOK()
    
    MPID = lvwDef.SelectedItem.Key
    Me.Hide
    
End Sub

Public Function ShowMappings(CPID As String, MPIDs As String) As VbMsgBoxResult
    
    Dim S() As String
    Dim I As Integer
    
    wzb.Caption = "Please select a manager for " + CPID + "."

    If MPIDs > "" Then
    
        S = Split(MPIDs, ",")
        lvwDef.ListItems.Clear
        
        For I = 0 To UBound(S)
            lvwDef.ListItems.Add(, S(I), S(I), , m_Icons.IconIndex(S(I))).SubItems(1) = "(unknown)"
        Next
        
        tbs.Tab = 0
        'lvwDef.SetFocus
    
    End If
    
    Me.Show vbModal

    ShowMappings = ocb.LastResult

End Function
