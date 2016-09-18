VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.UserControl EditTab 
   ClientHeight    =   5910
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   9300
   OLEDropMode     =   1  'Manual
   ScaleHeight     =   5910
   ScaleWidth      =   9300
   Begin VB.TextBox txtEdit 
      Height          =   285
      Left            =   480
      TabIndex        =   0
      Text            =   "Text1"
      Top             =   1200
      Visible         =   0   'False
      Width           =   975
   End
   Begin VB.Timer tmrRename 
      Enabled         =   0   'False
      Interval        =   500
      Left            =   360
      Top             =   1800
   End
   Begin MSComctlLib.TabStrip tbs 
      Height          =   5175
      Left            =   0
      TabIndex        =   1
      Top             =   0
      Width           =   8295
      _ExtentX        =   14631
      _ExtentY        =   9128
      MultiRow        =   -1  'True
      Separators      =   -1  'True
      _Version        =   393216
      BeginProperty Tabs {1EFB6598-857C-11D1-B16A-00C0F0283628} 
         NumTabs         =   1
         BeginProperty Tab1 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "Page 1"
            ImageVarType    =   2
         EndProperty
      EndProperty
      OLEDropMode     =   1
   End
   Begin VB.Menu mnuTab 
      Caption         =   "Tab"
      Visible         =   0   'False
      Begin VB.Menu mnuTab_New 
         Caption         =   "New"
      End
      Begin VB.Menu mnuTab_Sep0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuTab_Rename 
         Caption         =   "Rename"
      End
      Begin VB.Menu mnuTab_Sep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuTab_Delete 
         Caption         =   "Delete"
      End
   End
End
Attribute VB_Name = "EditTab"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
    Option Explicit
    
    Dim m_OldText   As String
    Dim m_NewText   As String
    Dim m_TabEdited As Integer
    
    Public Event OLEDragDrop(Data As MSComctlLib.DataObject, Effect As Long, Button As Integer, Shift As Integer, X As Single, Y As Single)
    
    Public Event OnRename(T As MSComctlLib.Tab, NewName As String, Cancel As Boolean)
    Public Event OnNew(T As MSComctlLib.Tab, Cancel As Boolean)
    Public Event OnDelete(T As MSComctlLib.Tab, Cancel As Boolean)
    
    Public Property Get Tabs() As MSComctlLib.Tabs
        Set Tabs = tbs.Tabs
    End Property
    
    Public Property Get CurrentIndex() As Integer
        CurrentIndex = tbs.SelectedItem.Index
    End Property
    
    Public Property Get SelectedItem() As MSComctlLib.Tab
        Set SelectedItem = tbs.SelectedItem
    End Property
    
    Public Property Set SelectedItem(NV As MSComctlLib.Tab)
        Set tbs.SelectedItem = NV
    End Property
    
    Private Sub mnuTab_New_Click()
        Dim T       As MSComctlLib.Tab
        Dim Cancel  As Boolean
        Set T = tbs.Tabs.Add(tbs.SelectedItem.Index + 1, , "New Tab")
        T.Selected = True
        Cancel = False
        RaiseEvent OnNew(T, Cancel)
        tmrRename.Enabled = True
    End Sub
    
    Private Sub mnuTab_Rename_Click()
    
        Dim T       As MSComctlLib.Tab
        
        Set T = tbs.SelectedItem
        m_OldText = T.Caption
        m_NewText = T.Caption
        m_TabEdited = T.Index
        
        With txtEdit
            .Move T.Left, T.Top, T.Width, T.Height
            .Text = T.Caption
            .SelStart = 0
            .SelLength = Len(txtEdit.Text)
            .Visible = True
            .SetFocus
        End With
        
    End Sub
    
    Private Sub tbs_KeyPress(KeyAscii As Integer)
    
        If KeyAscii = 13 Then mnuTab_Rename_Click
    
    End Sub
    
    Private Sub tbs_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
    
        Dim T       As MSComctlLib.Tab
        Dim InX     As Boolean
        Dim InY     As Boolean
            
        For Each T In tbs.Tabs
            InX = (X >= T.Left And X <= T.Left + T.Width)
            InY = (Y >= (T.Top - tbs.Top) And Y <= (T.Top - tbs.Top) + T.Height)
            
            If InX And InY Then
                If (tbs.SelectedItem Is T) And (Button And vbLeftButton) Then
                    'tmrRename.Enabled = True
                Else
                    T.Selected = True
                End If
                Exit Sub
            End If
        Next
    
    End Sub
    
    Private Sub tbs_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    
        'If txtEdit.Visible Then Exit Sub
        If tmrRename.Enabled Then Exit Sub
    
        If Button And vbRightButton Then
            PopupMenu mnuTab, , tbs.SelectedItem.Left, tbs.SelectedItem.Top + tbs.SelectedItem.Height
        End If
    
    End Sub
    
    Public Property Get OLEDropMode() As OLEDropConstants
        OLEDropMode = UserControl.OLEDropMode
    End Property
    
    Public Property Let OLEDropMode(NV As OLEDropConstants)
        UserControl.OLEDropMode = NV
    End Property
    
    Private Sub tbs_OLEDragDrop(Data As MSComctlLib.DataObject, Effect As Long, Button As Integer, Shift As Integer, X As Single, Y As Single)
        RaiseEvent OLEDragDrop(Data, Effect, Button, Shift, X, Y)
    End Sub
    
    Private Sub tmrRename_Timer()
        tmrRename.Enabled = False
        mnuTab_Rename_Click
    End Sub
    
    Private Sub txtEdit_Change()
        Dim tpx As Long
        Dim tpy As Long
        With tbs.SelectedItem
            .Caption = txtEdit.Text
            tpx = Screen.TwipsPerPixelX
            tpy = Screen.TwipsPerPixelY
            txtEdit.Move .Left + (1 * tpx), .Top + (1 * tpy), .Width - (2 * tpx), .Height - (2 * tpy)
        End With
    End Sub
    
    Private Sub txtEdit_KeyDown(KeyCode As Integer, Shift As Integer)
        If KeyCode = vbKeyEscape Then txtEdit.Visible = False
        
        If KeyCode = vbKeyReturn Then
            m_NewText = txtEdit.Text
            txtEdit.Visible = False
        End If
    End Sub
    
    Private Sub txtEdit_LostFocus()
        Dim Cancel As Boolean
        tbs.SelectedItem.Caption = m_OldText
        If m_TabEdited = tbs.SelectedItem.Index Then
            If m_NewText <> m_OldText Then RaiseEvent OnRename(tbs.SelectedItem, m_NewText, Cancel)
            If Not Cancel Then tbs.SelectedItem.Caption = m_NewText
        Else
            If m_NewText <> m_OldText Then RaiseEvent OnRename(tbs.Tabs(m_TabEdited), m_NewText, Cancel)
            If Not Cancel Then tbs.Tabs(m_TabEdited).Caption = m_NewText
        End If
        txtEdit.Visible = False
    End Sub
    
    Private Sub UserControl_Resize()
        tbs.Move 0, 0, UserControl.ScaleWidth, UserControl.ScaleHeight
    End Sub
