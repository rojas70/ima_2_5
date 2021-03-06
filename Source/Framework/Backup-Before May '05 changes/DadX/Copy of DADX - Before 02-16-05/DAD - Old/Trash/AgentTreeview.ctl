VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.UserControl AgentTreeview 
   Alignable       =   -1  'True
   ClientHeight    =   3600
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   6495
   OLEDropMode     =   1  'Manual
   ScaleHeight     =   240
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   433
   Begin VB.Timer tmrStateCheck 
      Interval        =   1000
      Left            =   4680
      Top             =   120
   End
   Begin VB.Timer tmrDrag 
      Enabled         =   0   'False
      Interval        =   400
      Left            =   4680
      Top             =   1560
   End
   Begin VB.Timer tmrLabelEdit 
      Enabled         =   0   'False
      Interval        =   100
      Left            =   4680
      Top             =   960
   End
   Begin MSComctlLib.TreeView tvw 
      Height          =   3255
      Left            =   0
      TabIndex        =   0
      Top             =   15
      Width           =   4455
      _ExtentX        =   7858
      _ExtentY        =   5741
      _Version        =   393217
      HideSelection   =   0   'False
      Indentation     =   529
      LabelEdit       =   1
      LineStyle       =   1
      Sorted          =   -1  'True
      Style           =   7
      Appearance      =   1
      OLEDropMode     =   1
   End
End
Attribute VB_Name = "AgentTreeview"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
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
    Event DblClick(ByVal Node As Node)
    
    Event NodeClick(ByVal Node As Node)
    Event NodeMenu(ByVal Node As Node)
    Event NodeAdd(Key As String)
    Event NodeRemove(Key As String)
    
    Event AfterLabelEdit(Cancel As Boolean, NewString As String)
    Event DragStart()
    
'************************************************************************************************
' Member Variables
'************************************************************************************************

    Dim m_Icons             As New IconManager
    Dim m_AL                As ILocator
    Dim WithEvents m_Net    As NetList
Attribute m_Net.VB_VarHelpID = -1
    Dim m_ViewPath          As String
    
    Dim m_ButtonDown        As Boolean
    Dim m_Editing           As Boolean
    Dim m_BorderStyle       As MSComctlLib.BorderStyleConstants
    Dim m_DragPath          As String
    
'************************************************************************************************
' Usercontrol Events
'************************************************************************************************

    Private Sub tvw_OLEStartDrag(Data As MSComctlLib.DataObject, AllowedEffects As Long)
        Data.SetData m_DragPath, vbCFText
        AllowedEffects = vbDropEffectCopy
    End Sub

    Private Sub UserControl_Initialize()
        Set m_AL = GetLocator()
        m_Icons.Directory = "C:\Ima2\System\Icons"
        Set tvw.ImageList = m_Icons.ImageList
        m_ViewPath = "\\"
    End Sub
    
    Private Sub UserControl_InitProperties()
        m_BorderStyle = 1
    End Sub

    Private Sub UserControl_ReadProperties(PropBag As PropertyBag)
        m_BorderStyle = PropBag.ReadProperty("BorderStyle", 1)
        UserControl_Resize
    End Sub
    
    Private Sub UserControl_WriteProperties(PropBag As PropertyBag)
        Call PropBag.WriteProperty("BorderStyle", m_BorderStyle, 1)
    End Sub

    Private Sub UserControl_Resize()
        On Error Resume Next
        If m_BorderStyle = ccNone Then
            tvw.Move -2, -2, UserControl.Width + 4, UserControl.Height + 4
        Else
            tvw.Move 0, 0, UserControl.ScaleWidth, UserControl.ScaleHeight
        End If
    End Sub

'************************************************************************************************
' Timer Events
'************************************************************************************************
    Private Sub tmrDrag_Timer()
        tmrDrag.Enabled = False
        If m_ButtonDown Then RaiseEvent DragStart
    End Sub

    Public Sub BeginOLEDrag()
        On Error Resume Next
        tvw.OLEDrag
        Err.Clear
    End Sub

    Private Sub tmrLabelEdit_Timer()
        tmrLabelEdit.Enabled = False
        m_Editing = True
        tvw.StartLabelEdit
    End Sub

'************************************************************************************************
' Object Events
'************************************************************************************************
    
    Private Sub tmrStateCheck_Timer()
    
        'update component colors for activated components
    
    End Sub
    
    Private Sub m_Net_OnRefresh()
            
        Dim C()     As String
        Dim I       As Integer
            
        C = m_Net.Items
        If ArrayEmpty(C) Then Exit Sub
            
        tvw.Nodes.Clear
        tvw.Nodes.Add(, , "\\", "IMA2 Network", II_Network).ForeColor = QBColor(0)
            
        For I = 0 To UBound(C)
            Call AddNode(C(I))
        Next
        
        tvw.Nodes("\\").Expanded = True
    
    End Sub

    Private Sub m_Net_OnRegister(ByVal Path As String)
        Call AddNode(Path)
    End Sub
    
    Private Sub m_Net_OnUnregister(ByVal Path As String)
        Call RemoveNode(Path)
    End Sub

'************************************************************************************************
' Public Functions
'************************************************************************************************

    Public Property Get NetList() As NetList
        Set NetList = m_Net
    End Property

    Public Property Set NetList(Net As NetList)
        Set m_Net = Net
        m_Net_OnRefresh
    End Property

    Public Property Get ViewPath() As String
        ViewPath = m_ViewPath
    End Property
    
    Public Property Let ViewPath(NewVal As String)
        m_ViewPath = NewVal
        Call m_Net_OnRefresh
    End Property
    
    Public Property Let Path(NewVal As String)
        On Error Resume Next
        Set tvw.SelectedItem = tvw.Nodes(NewVal)
        If Err Then
            tvw.SelectedItem.Selected = False
            Err.Clear
            Exit Property
        End If
        RaiseEvent NodeClick(tvw.SelectedItem)
    End Property
    
    Public Property Get Path() As String
        If tvw.SelectedItem Is Nothing Then Exit Function
        Path = tvw.SelectedItem.Key
    End Property

    Public Property Get NodeIcons(Path As String) As IMA2_Icons
        NodeIcons = tvw.Nodes(Path).Image
    End Property
    
    Public Property Get Locator() As ILocator
        Set Locator = m_AL
    End Property
    
    Public Sub Refresh()
        m_Net.Refresh
    End Sub
    
    Public Sub StartLabelEdit()
        DoEvents
        tvw.SetFocus
        tmrLabelEdit.Enabled = True
        DoEvents
    End Sub
    
    Public Property Get Nodes() As Nodes
        Set Nodes = tvw.Nodes
    End Property

    Public Property Get SelectedItem() As Node
        Set SelectedItem = tvw.SelectedItem
    End Property
    
    Public Property Set SelectedItem(NewVal As Node)
        Set tvw.SelectedItem = NewVal
    End Property

    Public Property Get BorderStyle() As MSComctlLib.BorderStyleConstants
        BorderStyle = m_BorderStyle
    End Property
    
    Public Property Let BorderStyle(NewVal As MSComctlLib.BorderStyleConstants)
        m_BorderStyle = NewVal
        UserControl_Resize
    End Property

    Public Sub ExpandAll()
        Call ExpandAllNodes(tvw)
    End Sub

    Public Sub CollapseAll()
        Dim N As Node
        For Each N In tvw.Nodes
            N.Expanded = False
        Next
    End Sub

'************************************************************************************************
' Miscellaneous Functions
'************************************************************************************************
    Public Sub SelectItem(IndexKey As Variant)
        Set tvw.SelectedItem = tvw.Nodes(IndexKey)
        RaiseEvent NodeClick(tvw.SelectedItem)
    End Sub
    
    Private Sub CommitLabelEdit()
        Dim Cancel As Integer
        m_Editing = False
        RaiseEvent AfterLabelEdit(m_Editing, tvw.SelectedItem.Text)
        If m_Editing Then StartLabelEdit
    End Sub
    
    Private Sub RemoveNode(Path As String)
        'On Error Resume Next
        Call tvw.Nodes.Remove(Path)
        RaiseEvent NodeClick(tvw.SelectedItem)
    End Sub
    
    Private Sub AddNode(Path As String)
        Dim P       As String
        Dim C       As IComponent
        Dim Color   As Long
        
        P = ParentFromPath(Path)
        
        If PathLevel(Path) = 1 Then
            tvw.Nodes.Add(P, tvwChild, Path, NameFromPath(Path), II_Locator).ForeColor = QBColor(0)
        Else
            On Error Resume Next
            Set C = m_AL.Locate(Path)
            Color = QBColor(12)
            If C.Activated Then Color = QBColor(2)
            If Err > 0 Then
                tvw.Nodes.Add(P, tvwChild, Path, NameFromPath(Path), II_BadComponent).ForeColor = Color
            ElseIf TypeOf C Is IContainer Then
                tvw.Nodes.Add(P, tvwChild, Path, NameFromPath(Path), II_Container).ForeColor = Color
            Else
                tvw.Nodes.Add(P, tvwChild, Path, NameFromPath(Path), m_Icons.IconIndex(C.PID)).ForeColor = Color
            End If
        End If
    End Sub
    
'************************************************************************************************
' Treeview Events
'************************************************************************************************
    Private Sub tvw_KeyUp(KeyCode As Integer, Shift As Integer)
        If KeyCode = vbKeyReturn And m_Editing Then
            Call CommitLabelEdit
        Else
            RaiseEvent KeyUp(KeyCode, Shift)
        End If
    End Sub

    Private Sub tvw_KeyDown(KeyCode As Integer, Shift As Integer)
        RaiseEvent KeyDown(KeyCode, Shift)
    End Sub
    
    Private Sub tvw_KeyPress(KeyAscii As Integer)
        RaiseEvent KeyPress(KeyAscii)
    End Sub

    Private Sub tvw_AfterLabelEdit(Cancel As Integer, NewString As String)
        m_Editing = False
        RaiseEvent AfterLabelEdit(m_Editing, NewString)
        If m_Editing = True Then Cancel = True: StartLabelEdit
    End Sub

    Private Sub tvw_DblClick()
        RaiseEvent DblClick(tvw.SelectedItem)
    End Sub

    Private Sub tvw_LostFocus()
'        If m_Editing = True Then RaiseEvent AfterLabelEdit(False, tvw.SelectedItem.Text)
    End Sub

    Private Sub tvw_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
        Dim NN As Node
        
        If m_Editing = True Then Call CommitLabelEdit
        
        Set NN = tvw.HitTest(x, y)
        
        If NN Is Nothing Then Exit Sub
            
        Set tvw.SelectedItem = tvw.HitTest(x, y)
        If NN Is tvw.SelectedItem Then RaiseEvent NodeClick(NN)
        
        m_ButtonDown = True
        m_DragPath = tvw.HitTest(x, y).Key
        tmrDrag.Enabled = True
    
    End Sub

    Private Sub tvw_MouseUp(Button As Integer, Shift As Integer, x As Single, y As Single)
        Dim N As Node
        m_ButtonDown = False
        If (Button And vbRightButton) Then
            Set N = tvw.HitTest(x, y)
            'Set tvw.SelectedItem = N
            RaiseEvent NodeMenu(N)
        End If
    End Sub

    Private Sub tvw_NodeClick(ByVal Node As MSComctlLib.Node)
        If m_Editing Then tvw.StartLabelEdit: Exit Sub
        RaiseEvent NodeClick(Node)
    End Sub


