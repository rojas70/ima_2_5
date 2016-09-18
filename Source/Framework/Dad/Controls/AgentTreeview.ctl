VERSION 5.00
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
   ToolboxBitmap   =   "AgentTreeview.ctx":0000
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
      Top             =   0
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
    Dim m_IS                As IDistributingInfoProvider
    
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
        Set m_AL = GetLocator()                                 'Get pointer to locator
        Set m_IS = CreateObject("IMA2_InfoService.InfoService") 'Get pointer to infoservice
        m_Icons.Directory = "C:\Ima2\Icons"                     'Set icon directory for treeview
        Set tvw.ImageList = m_Icons.ImageList                   'Share imagelist in IconManager
        m_ViewPath = "\\"                                       'Look at entire network by default
        
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
    
    Private Sub m_Net_OnOtherEvent(ByVal Action As IMA2.IMA2_LocatorAction, Args() As String)
        On Error Resume Next
        
        Dim N As Node
        
        If Action = LE_ActivateSeq Then
            Set N = tvw.Nodes(Args(0))
            N.ForeColor = QBColor(2)
        ElseIf Action = LE_DeactivateSeq Then
            Set N = tvw.Nodes(Args(0))
            N.ForeColor = QBColor(12)
        End If
                
    End Sub

    Private Sub m_Net_OnRefresh()
            
        Dim C()     As String
        Dim I       As Integer
        Dim SelPath As String
            
        C = m_Net.Items
        If ArrayEmpty(C) Then Exit Sub
            
        If Not (SelectedItem Is Nothing) Then
            SelPath = SelectedItem.Key
        Else
            SelPath = ""
        End If
        
        tvw.Nodes.Clear
        tvw.Nodes.Add(, , "\\", "IMA2 Network", II_Network).ForeColor = QBColor(0)
            
        For I = 0 To UBound(C)
            Call AddNode(C(I))
        Next
        
        ExpandAll
        
        If SelPath <> "" Then
            On Error Resume Next
            Set tvw.SelectedItem = tvw.Nodes(SelPath)
            If Err Then
                tvw.SelectedItem.Selected = False
                Err.Clear
                Exit Sub
            End If
        End If
        
        
    End Sub

    Private Sub m_Net_OnRegister(ByVal Path As String)
        On Error Resume Next
        
        Call AddNode(Path)
                
        Err.Clear
    End Sub
    
    Private Sub m_Net_OnUnregister(ByVal Path As String)
        On Error Resume Next
        
        Call RemoveNode(Path)
        
        Err.Clear
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
        Err.Clear
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
         On Error Resume Next
        
        Dim P       As String
        Dim DI      As IMA2_DistributingInfo
        Dim Color   As Long
        
        P = ParentFromPath(Path)
                
        'If it's a locator then it's easy.
        If PathLevel(Path) = 1 Then
            tvw.Nodes.Add(P, tvwChild, Path, NameFromPath(Path), II_Locator).ForeColor = QBColor(0)
            Exit Sub
        End If
        
        'If it's a normal component, get it's information first.
       DI = m_IS.Item(Path)
        If Err > 0 Then
            tvw.Nodes.Add(P, tvwChild, Path, NameFromPath(Path), II_BadComponent).ForeColor = QBColor(12)
        Else
            tvw.Nodes.Add(P, tvwChild, Path, NameFromPath(Path), m_Icons.IconIndex(DI.PID)).ForeColor = 0    'Color
        End If
    
        Err.Clear
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

    Private Sub tvw_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
        Dim NN As Node
        
        If m_Editing = True Then Call CommitLabelEdit
        
        Set NN = tvw.HitTest(X, Y)
        
        If NN Is Nothing Then Exit Sub
            
        Set tvw.SelectedItem = tvw.HitTest(X, Y)
        m_ButtonDown = True
        m_DragPath = tvw.HitTest(X, Y).Key
        tmrDrag.Enabled = True
        
        If NN Is tvw.SelectedItem Then RaiseEvent NodeClick(NN)
    
    End Sub

    Private Sub tvw_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
        Dim N As Node
        m_ButtonDown = False
        If (Button And vbRightButton) Then
            Set N = tvw.HitTest(X, Y)
            'Set tvw.SelectedItem = N
            RaiseEvent NodeMenu(N)
        End If
    End Sub

    Private Sub tvw_NodeClick(ByVal Node As MSComctlLib.Node)
        If m_Editing Then tvw.StartLabelEdit: Exit Sub
        RaiseEvent NodeClick(Node)
    End Sub


