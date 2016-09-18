VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.UserControl AgentListview 
   Alignable       =   -1  'True
   BackColor       =   &H80000005&
   ClientHeight    =   3600
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4800
   ScaleHeight     =   240
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   320
   ToolboxBitmap   =   "AgentListview.ctx":0000
   Begin VB.Timer tmrLabelEdit 
      Enabled         =   0   'False
      Interval        =   100
      Left            =   3960
      Top             =   1320
   End
   Begin VB.Timer tmrDrag 
      Enabled         =   0   'False
      Interval        =   400
      Left            =   3960
      Top             =   1920
   End
   Begin MSComctlLib.ListView lvw 
      Height          =   2535
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   3255
      _ExtentX        =   5741
      _ExtentY        =   4471
      View            =   3
      LabelEdit       =   1
      MultiSelect     =   -1  'True
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      _Version        =   393217
      SmallIcons      =   "iml"
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      Appearance      =   0
      NumItems        =   4
      BeginProperty ColumnHeader(1) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         Text            =   "Item Name"
         Object.Width           =   3969
      EndProperty
      BeginProperty ColumnHeader(2) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   1
         Text            =   "Type"
         Object.Width           =   2646
      EndProperty
      BeginProperty ColumnHeader(3) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   2
         Text            =   "Value"
         Object.Width           =   2646
      EndProperty
      BeginProperty ColumnHeader(4) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   3
         Text            =   "SortType"
         Object.Width           =   0
      EndProperty
   End
   Begin VB.Line Line1 
      BorderColor     =   &H80000014&
      X1              =   0
      X2              =   0
      Y1              =   18
      Y2              =   1000
   End
End
Attribute VB_Name = "AgentListview"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
    Option Explicit

'************************************************************************************************
' Enumerations
'************************************************************************************************
   
'************************************************************************************************
' Events
'************************************************************************************************
    Event KeyUp(KeyCode As Integer, Shift As Integer)
    Event KeyDown(KeyCode As Integer, Shift As Integer)
    Event KeyPress(KeyAscii As Integer)
    Event DblClick(ByVal Item As mscomctllib.ListItem)
    
    Event ItemClick(ByVal Item As mscomctllib.ListItem)
    Event ItemMenu(ByVal Item As mscomctllib.ListItem)
    Event ItemAdd(Key As String)
    Event ItemRemove(Key As String)
    
    Event AfterLabelEdit(Cancel As Integer, NewString As String)
    Event DragStart()
    
    Event ViewPathChange(NewPath As String)
    
'************************************************************************************************
' Member Variables
'************************************************************************************************

    Dim m_IS                As IDistributingInfoProvider
    Dim m_Icons             As New IconManager
    Dim WithEvents m_Net    As NetList
Attribute m_Net.VB_VarHelpID = -1
    Dim m_ViewPath          As String
    
    Dim m_ButtonDown        As Boolean
    Dim m_Editing           As Boolean

'************************************************************************************************
' Usercontrol Events
'************************************************************************************************

    Private Sub UserControl_Initialize()
        Set m_IS = CreateObject("IMA2_InfoService.InfoService")
        m_Icons.Directory = "C:\Ima2\Icons"
        Set lvw.SmallIcons = m_Icons.ImageList
        m_ViewPath = "\\"
    End Sub
    
    Private Sub UserControl_Resize()
        On Error Resume Next
        'lvw.Move -2, -2, UserControl.ScaleWidth + 2, UserControl.ScaleHeight + 2
        lvw.Move 1, 1, UserControl.ScaleWidth - 3, UserControl.ScaleHeight - 3
        lvw.ColumnHeaders(3).Width = UserControl.ScaleWidth - lvw.ColumnHeaders(1).Width - lvw.ColumnHeaders(2).Width - 20
        Err.Clear
    End Sub

'************************************************************************************************
' Timer Events
'************************************************************************************************
    Private Sub tmrDrag_Timer()
        tmrDrag.Enabled = False
        If m_ButtonDown Then RaiseEvent DragStart
    End Sub

    Private Sub tmrLabelEdit_Timer()
        tmrLabelEdit.Enabled = False
        m_Editing = True
        lvw.StartLabelEdit
    End Sub

'************************************************************************************************
' Object Events
'************************************************************************************************
    Private Sub m_Net_OnRefresh()
            
        Dim C()     As String
        Dim I       As Integer
            
        C = m_Net.Items
        If ArrayEmpty(C) Then Exit Sub
        
        Set SelectedItem = Nothing
        lvw.ListItems.Clear
        
        For I = 0 To UBound(C)
            If ParentFromPath(C(I)) = m_ViewPath Then Call AddItem(C(I))
        Next
        
    End Sub

    Private Sub m_Net_OnRegister(ByVal Path As String)
        If ParentFromPath(Path) = m_ViewPath Then Call AddItem(Path)
    End Sub
    
    Private Sub m_Net_OnUnregister(ByVal Path As String)
        If ParentFromPath(Path) = m_ViewPath Then Call RemoveItem(Path)
    End Sub

'************************************************************************************************
' Public Functions
'************************************************************************************************

    Public Property Get ColumnHeaders() As ColumnHeaders
        Set ColumnHeaders = lvw.ColumnHeaders
    End Property

    Public Property Get NetList() As NetList
        Set NetList = m_Net
    End Property

    Public Property Set NetList(Net As NetList)
        Set m_Net = Net
        m_Net_OnRefresh
    End Property
    
    Public Property Get Paths() As String()
        Dim RV() As String
        If lvw.ListItems.Count = 0 Then Paths = RV: Exit Property
        ReDim RV(0 To lvw.ListItems.Count - 1) As String
        Dim I As Integer
        For I = 0 To lvw.ListItems.Count - 1
            RV(I) = lvw.ListItems(I + 1).Key
        Next
        Paths = RV
    End Property
        
    Public Property Get Path() As String
        If lvw.SelectedItem Is Nothing Then Exit Function
        Path = lvw.SelectedItem.Key
    End Property
    
    Public Property Let Path(NewVal As String)
        Set lvw.SelectedItem = lvw.ListItems(NewVal)
    End Property
   
    Public Property Get ViewPath() As String
        ViewPath = m_ViewPath
    End Property
    
    Public Property Let ViewPath(NewVal As String)
        m_ViewPath = NewVal
        Call m_Net_OnRefresh
        RaiseEvent ViewPathChange(NewVal)
    End Property
   
    Public Property Get ItemIcons(Path As String) As IMA2_Icons
        ItemIcons = lvw.ListItems(Path).Icon
    End Property
    
    Public Property Get ListItems() As ListItems
        Set ListItems = lvw.ListItems
    End Property
    
    Public Sub Refresh()
        m_Net.Refresh
    End Sub
    
    Public Sub StartLabelEdit()
        DoEvents
        tmrLabelEdit.Enabled = True
        DoEvents
    End Sub
    
    Public Property Get SelectedItem() As ListItem
        Set SelectedItem = lvw.SelectedItem
    End Property
    
    Public Property Set SelectedItem(NewVal As ListItem)
        Dim LI As ListItem
        If Not (lvw.SelectedItem Is Nothing) Then lvw.SelectedItem.Selected = False
        Set lvw.SelectedItem = NewVal
    End Property
    
    Public Sub SelectItem(IndexKey As Variant)
        Set SelectedItem = lvw.ListItems(IndexKey)
        RaiseEvent ItemClick(lvw.SelectedItem)
    End Sub

'************************************************************************************************
' Miscellaneous Functions
'************************************************************************************************
    Public Sub Sort()
        Dim LI As ListItem
        Dim LI2 As ListItem
        Dim Sets(0 To 4) As Collection
        Dim I As Integer
        Dim J As Integer
        Dim Idx As Integer
        Dim Order() As String
        Dim funcs As New Functions
        Dim SI(1 To 3) As String
        
        For I = 0 To 4
            Set Sets(I) = New Collection
        Next
        
        For Each LI In lvw.ListItems
            Call Sets(LI.ListSubItems(3)).Add(LI, LI.Text)
        Next
        
        Idx = 0
        For I = 0 To 4
            If (Sets(I).Count > 0) Then
                ReDim Order(0 To Sets(I).Count - 1)
                For J = 1 To Sets(I).Count
                    Set LI = Sets(I).Item(J)
                    Order(J - 1) = LI.Text
                Next J
                Call funcs.QuickSortStrings(Order)
                For J = 1 To Sets(I).Count
                    Set LI = Sets(I).Item(Order(J - 1))
                    SI(1) = LI.SubItems(1)
                    SI(2) = LI.SubItems(2)
                    SI(3) = LI.SubItems(3)
                    Idx = Idx + 1
                    Call lvw.ListItems.Remove(LI.Key)
                    Set LI2 = lvw.ListItems.Add(Idx, LI.Key, LI.Text, LI.Icon, LI.SmallIcon)
                    LI2.SubItems(1) = SI(1)
                    LI2.SubItems(2) = SI(2)
                    LI2.SubItems(3) = SI(3)
                Next J
            End If
        Next I

        
        
    End Sub
    
    Private Sub CommitLabelEdit()
        m_Editing = False
        RaiseEvent AfterLabelEdit(False, lvw.SelectedItem.Text)
    End Sub
    
    Private Sub RemoveItem(Path As String)
        On Error Resume Next
        Call lvw.ListItems.Remove(Path) 'This may fail sometimes if the NetList is refreshed before the Locator event hits.
        Err.Clear
    End Sub
    
    Private Sub AddItem(Path As String)
        On Error Resume Next
        
        Dim LI      As ListItem
        Dim P       As String
        Dim DI      As IMA2_DistributingInfo
        
        P = ParentFromPath(Path)
        If P = "" Then P = "\\"
        
        If PathLevel(Path) = 1 Then
            Set LI = lvw.ListItems.Add(, Path, NameFromPath(Path), , II_Locator)
            LI.ForeColor = QBColor(0)
            LI.SubItems(1) = LocatorPID()
            LI.SubItems(3) = 0  'Added 5/13/05 to allow for sort-by-type -CLC
            Exit Sub
        End If
        
        'Check to make sure it's listed in the information service.
        DI = m_IS.Item(Path)
        
        'if it's not listed, add it to the list marked bad.
        If Err > 0 Then
            Set LI = lvw.ListItems.Add(, Path, NameFromPath(Path), , II_BadComponent)
            LI.SubItems(1) = "Component Error"
            LI.ForeColor = QBColor(8)
            Exit Sub
        End If
            
        'It's a normal component
        Set LI = lvw.ListItems.Add(, Path, NameFromPath(Path), , m_Icons.IconIndex(DI.PID))
        LI.SubItems(1) = DI.PID
        'Added 5/13/05 to allow for sort-by-type -CLC
        If (DI.PID = "IMA2_Agent.Agent") Then
            LI.SubItems(3) = 0
        Else
            LI.SubItems(3) = 1
        End If
        LI.ForeColor = QBColor(0)
        Err.Clear
    End Sub
    
'************************************************************************************************
' Treeview Events
'************************************************************************************************
    Private Sub lvw_KeyUp(KeyCode As Integer, Shift As Integer)
        If KeyCode = vbKeyReturn And m_Editing Then
            Call CommitLabelEdit
        Else
            RaiseEvent KeyUp(KeyCode, Shift)
        End If
    End Sub

    Private Sub lvw_KeyDown(KeyCode As Integer, Shift As Integer)
        RaiseEvent KeyDown(KeyCode, Shift)
    End Sub
    
    Private Sub lvw_KeyPress(KeyAscii As Integer)
        RaiseEvent KeyPress(KeyAscii)
    End Sub

    Private Sub lvw_AfterLabelEdit(Cancel As Integer, NewString As String)
        m_Editing = False
        RaiseEvent AfterLabelEdit(Cancel, NewString)
    End Sub

    Private Sub lvw_DblClick()
        RaiseEvent DblClick(lvw.SelectedItem)
    End Sub

    Private Sub lvw_LostFocus()
'        If m_Editing = True Then RaiseEvent AfterLabelEdit(False, lvw.SelectedItem.Text)
    End Sub

    Private Sub lvw_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
        If m_Editing = True Then Call CommitLabelEdit
        If lvw.HitTest(X, Y) Is Nothing Then
            Set lvw.SelectedItem = Nothing
        Else
            m_ButtonDown = True
            tmrDrag.Enabled = True
        End If
    End Sub

    Private Sub lvw_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
        Dim N As ListItem
        m_ButtonDown = False
        If (Button And vbRightButton) Then
            Set N = lvw.HitTest(X, Y)
            'Set lvw.SelectedItem = N
            RaiseEvent ItemMenu(N)
        End If
    End Sub

    Private Sub lvw_ItemClick(ByVal Item As mscomctllib.ListItem)
        RaiseEvent ItemClick(Item)
    End Sub



