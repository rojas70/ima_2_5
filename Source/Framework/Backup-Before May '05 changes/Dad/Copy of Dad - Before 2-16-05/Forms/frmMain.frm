VERSION 5.00
Object = "{B3B088D0-73D0-4791-9B45-C4B154DF8823}#1.1#0"; "IMA2_HelperX.ocx"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "Mscomctl.ocx"
Begin VB.Form frmMain 
   BackColor       =   &H80000005&
   Caption         =   "Distributed Agent Designer 1.0"
   ClientHeight    =   5076
   ClientLeft      =   132
   ClientTop       =   816
   ClientWidth     =   9660
   Icon            =   "frmMain.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   423
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   805
   StartUpPosition =   3  'Windows Default
   Begin IMA2_DAD.ICmpView cmv 
      Height          =   930
      Left            =   2640
      TabIndex        =   7
      Top             =   3840
      Width           =   6975
      _ExtentX        =   12298
      _ExtentY        =   1630
   End
   Begin IMA2_HelperX.Bevel2 bvlRight 
      Align           =   4  'Align Right
      Height          =   4416
      Left            =   9624
      Top             =   372
      Visible         =   0   'False
      Width           =   36
      _ExtentX        =   64
      _ExtentY        =   7789
      BS              =   1
      D               =   1
      C1              =   -2147483633
      C2              =   -2147483634
   End
   Begin IMA2_HelperX.Bevel2 bvlBottom 
      Align           =   2  'Align Bottom
      Height          =   30
      Left            =   0
      Top             =   4785
      Width           =   9660
      _ExtentX        =   17039
      _ExtentY        =   64
      BS              =   1
      C1              =   -2147483633
      C2              =   -2147483639
   End
   Begin IMA2_HelperX.Bevel2 bvlLeft 
      Align           =   3  'Align Left
      Height          =   4410
      Left            =   0
      Top             =   375
      Visible         =   0   'False
      Width           =   30
      _ExtentX        =   64
      _ExtentY        =   7789
      BS              =   1
      D               =   1
      C1              =   -2147483632
      C2              =   -2147483640
   End
   Begin MSComctlLib.StatusBar stb 
      Align           =   2  'Align Bottom
      Height          =   252
      Left            =   0
      TabIndex        =   0
      Top             =   4824
      Width           =   9660
      _ExtentX        =   17039
      _ExtentY        =   445
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   1
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   1
            Object.Width           =   16531
         EndProperty
      EndProperty
   End
   Begin IMA2_HelperX.Toolbar Toolbar1 
      Align           =   1  'Align Top
      Height          =   375
      Left            =   0
      TabIndex        =   1
      TabStop         =   0   'False
      Top             =   0
      Width           =   9660
      _ExtentX        =   17039
      _ExtentY        =   656
   End
   Begin IMA2_HelperX.AgentTreeview atv 
      Height          =   3750
      Left            =   0
      TabIndex        =   4
      Top             =   960
      Width           =   2535
      _ExtentX        =   4466
      _ExtentY        =   6625
      BorderStyle     =   0
   End
   Begin IMA2_HelperX.AgentListview alv 
      Height          =   2835
      Left            =   2640
      TabIndex        =   2
      Top             =   960
      Width           =   6960
      _ExtentX        =   12277
      _ExtentY        =   4995
   End
   Begin IMA2_HelperX.SplitterLR slr 
      Height          =   3750
      Left            =   2535
      TabIndex        =   6
      Top             =   960
      Width           =   75
      _ExtentX        =   127
      _ExtentY        =   6625
   End
   Begin IMA2_HelperX.SplitterUD sud 
      Height          =   75
      Left            =   0
      TabIndex        =   3
      Top             =   900
      Width           =   96750
      _ExtentX        =   170646
      _ExtentY        =   127
   End
   Begin IMA2_HelperX.WebView wbv 
      Height          =   435
      Left            =   0
      TabIndex        =   5
      TabStop         =   0   'False
      Top             =   360
      Width           =   10155
      _ExtentX        =   17907
      _ExtentY        =   762
      Caption         =   "IMA2 Network"
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuFile_New 
         Caption         =   "&New File..."
      End
      Begin VB.Menu mnuFile_Open 
         Caption         =   "&Open File..."
      End
      Begin VB.Menu mnuFile_Sep0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFile_Favorite 
         Caption         =   "<favorite1>"
         Enabled         =   0   'False
         Index           =   0
      End
      Begin VB.Menu mnuFile_Sep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFile_Exit 
         Caption         =   "&Exit"
      End
   End
   Begin VB.Menu mnuCmp 
      Caption         =   "&Component"
      Visible         =   0   'False
      Begin VB.Menu mnuCmp_Activated 
         Caption         =   "&Activated"
         Checked         =   -1  'True
         Shortcut        =   ^A
      End
      Begin VB.Menu mnuCmp_Activated_Sep 
         Caption         =   "-"
      End
      Begin VB.Menu mnuCmp_ActivateBranch 
         Caption         =   "Activate &Branch"
         Shortcut        =   ^B
      End
      Begin VB.Menu mnuCmp_DeactivateBranch 
         Caption         =   "&Deactivate Branch"
         Shortcut        =   ^D
      End
      Begin VB.Menu mnuCmp_Branch_Sep 
         Caption         =   "-"
      End
      Begin VB.Menu mnuCmp_Disconnect 
         Caption         =   "&Disconnect"
      End
      Begin VB.Menu mnuCmp_Connect 
         Caption         =   "Connect &Locator..."
         Shortcut        =   ^L
         Visible         =   0   'False
      End
      Begin VB.Menu mnuCmp_Connect_Sep 
         Caption         =   "-"
      End
      Begin VB.Menu mnuCmp_New 
         Caption         =   "New"
         Begin VB.Menu mnuCmp_New_Agent 
            Caption         =   "&Agent"
            Shortcut        =   ^G
         End
         Begin VB.Menu mnuCmp_New_Sep0 
            Caption         =   "-"
         End
         Begin VB.Menu mnuCmp_New_Cmp 
            Caption         =   "&Component..."
            Shortcut        =   ^N
         End
         Begin VB.Menu mnuCmp_New_Sep1 
            Caption         =   "-"
         End
         Begin VB.Menu mnuCmp_New_Favorites 
            Caption         =   "<Favorite1>"
            Index           =   0
         End
      End
      Begin VB.Menu mnuCmp_New_Sep 
         Caption         =   "-"
      End
      Begin VB.Menu mnuCmp_Copy 
         Caption         =   "&Copy"
         Shortcut        =   ^C
      End
      Begin VB.Menu mnuCmp_Paste 
         Caption         =   "&Paste"
         Shortcut        =   +{INSERT}
      End
      Begin VB.Menu mnuCmp_Paste_Sep 
         Caption         =   "-"
      End
      Begin VB.Menu mnuCmp_Delete 
         Caption         =   "Delete"
         Shortcut        =   {DEL}
      End
      Begin VB.Menu mnuCmp_Delete_Sep 
         Caption         =   "-"
      End
      Begin VB.Menu mnuCmp_SaveAs 
         Caption         =   "&Save As..."
         Shortcut        =   ^S
      End
      Begin VB.Menu mnuCmp_SaveAs_Sep 
         Caption         =   "-"
      End
      Begin VB.Menu mnuCmp_Properties 
         Caption         =   "P&roperties"
         Shortcut        =   {F4}
      End
   End
   Begin VB.Menu mnuView 
      Caption         =   "&View"
      Begin VB.Menu mnuView_Toolbar 
         Caption         =   "&Toolbar"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuView_StatusBar 
         Caption         =   "&Status Bar"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuView_Sep0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuView_Views 
         Caption         =   "Views"
         Begin VB.Menu mnuView_Treeview 
            Caption         =   "Tr&ee View"
            Checked         =   -1  'True
         End
         Begin VB.Menu mnuView_Listview 
            Caption         =   "L&ist View"
            Checked         =   -1  'True
         End
         Begin VB.Menu mnuView_WebView 
            Caption         =   "&Web View"
            Checked         =   -1  'True
         End
         Begin VB.Menu mnuView_Sep_9 
            Caption         =   "-"
         End
         Begin VB.Menu mnuView_HideAll 
            Caption         =   "&Hide All"
         End
         Begin VB.Menu mnuView_ShowAll 
            Caption         =   "&Show All"
         End
      End
      Begin VB.Menu mnuView_Sep_8 
         Caption         =   "-"
      End
      Begin VB.Menu mnuView_List 
         Caption         =   "&List"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuView_Details 
         Caption         =   "&Details"
      End
      Begin VB.Menu mnuViewSep2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuView_Object 
         Caption         =   "&Object"
         Begin VB.Menu mnuView_Object_Properties 
            Caption         =   "&Properties"
            Checked         =   -1  'True
         End
         Begin VB.Menu mnuView_Object_Methods 
            Caption         =   "&Methods"
            Checked         =   -1  'True
         End
         Begin VB.Menu mnuView_Object_Bindings 
            Caption         =   "&Bindings"
            Checked         =   -1  'True
         End
      End
      Begin VB.Menu mnuView_Sep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuView_Refresh 
         Caption         =   "&Refresh"
         Shortcut        =   {F5}
      End
   End
   Begin VB.Menu muTools 
      Caption         =   "&Tools"
      Begin VB.Menu mnuTools_Options 
         Caption         =   "&Options..."
      End
      Begin VB.Menu mnuTextSummary 
         Caption         =   "&Text Summary..."
      End
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
    
'*********************************************************************************************************************************************************************
' Enums
'*********************************************************************************************************************************************************************
    Public Enum PathLevels
        PL_INVALID = -1
        PL_NETWORK = 0
        PL_LOCATOR = 1
        PL_CONTAINER = 2
    End Enum
    
'*********************************************************************************************************************************************************************
' Constants
'*********************************************************************************************************************************************************************
    
    Const MAX_FAVS = 10
    
'*********************************************************************************************************************************************************************
' Member Variables
'*********************************************************************************************************************************************************************
    Dim m_Icons         As New IconManager
    Dim m_Net           As New NetList
    Dim m_CD            As New CmpDesc
    Dim m_Favs          As New Collection
    Dim m_AL            As ILocator
    
'*********************************************************************************************************************************************************************
' Component Operations
'*********************************************************************************************************************************************************************
    
    Private Sub NewAgentComponent()
        With m_CD
            .Path = atv.Path + "\"
            .PID = "IMA2_Agent.Agent"
            .Machine = MachineFromPath(atv.Path)
        End With
        Set atv.SelectedItem = atv.Nodes.Add(atv.Nodes(atv.Path), tvwChild, atv.Path + "\$new$", "<New Component>", II_Container)
        atv.StartLabelEdit
    End Sub
    
    Private Sub NewComponent()
        Dim NP  As String
        Dim LP  As String
        Dim P   As String
        
        frmInsert.ParentPath = atv.Path
        frmInsert.Show vbModal
        
        If frmInsert.Choice = ICD_Cancel Then Exit Sub
        
        P = atv.Path
        
        'Insert Single Component
        If frmInsert.Choice = ICD_New Then
        
            'Create object
            With m_CD
                .Path = P + "\"
                .PID = frmInsert.ClsInfo.PID
                .Machine = MachineFromPath(atv.Path)
            End With
            
            Set atv.SelectedItem = atv.Nodes.Add(atv.Nodes(atv.Path), tvwChild, atv.Path + "\$new$", "<New Component>", m_Icons.IconIndex(m_CD.PID))
            atv.StartLabelEdit
        
            'Added option to create "local process" components for VC++ debugging.
            If frmInsert.Context = ICC_Local Then m_CD.PID = m_CD.PID + "*"
        
        'Insert Saved Agent
        Else
            
            Dim CDs()   As CmpDesc
            Dim I       As Integer
            Dim C       As IComponent
            
            On Error Resume Next
            CDs = frmInsert.Descriptions
            For I = LBound(CDs) To UBound(CDs)
                Set C = CreateIMA2Component(P + "\" + CDs(I).Path, CDs(I).PID, , True, atv.Locator)
                If Err Then
                    MsgBox Err.Description, vbOKOnly Or vbCritical, "IMA2 Component Creation Error"
                    Err.Clear
                End If
                
                If Not IsEmpty(CDs(I).Data) Then C.Load CDs(I).Data
                
                If Err Then
                    MsgBox Err.Description, vbOKOnly Or vbCritical, "IMA2 Component Data Load Error"
                    Err.Clear
                End If
            
            Next I
        
        End If
        
        atv.ExpandAll
        
'        NP = frmInsert.LibInfo.Path
 '       LP = "C:\Ima2\Components\" + NameFromPath(NP) 'ParentFromPath(Ima2Directory()) + "\Components\" + NameFromPath(NP)
        
'        If Right(LP, 4) = ".tmp" Then
         '   P = frmInsert.ClsInfo.PID + " is running in the VB IDE. It will not be copied and registered to the local machine."
        '    Call MsgBox(P, vbOKOnly Or vbInformation, "IMA2 Component Library Manager")
       '     Exit Sub
      '  End If
     '
    '    If Not FileExists(LP) Then
   '         P = "The component library file for " + frmInsert.ClsInfo.PID + " is not registered on the local drive. Please wait while it is copied and registered."
  '          Call MsgBox(P, vbOKOnly Or vbInformation, "IMA2 Component Library Manager")
 '       Else
'            If FileLen(LP) <> FileLen(NP) Then
             '   If FileLocked(LP) Then
            '        P = "There is a different version of the library file for " + frmInsert.ClsInfo.PID + " on the server. The local library cannot be updated because it is in use."
           '         Call MsgBox(P, vbOKOnly Or vbInformation, "IMA2 Component Library Manager")
          '      Else
         '           P = "There is a different version of the library file for " + frmInsert.ClsInfo.PID + " on the server. The server file has been copied and registered."
        '            Call CopyFile(NP, LP, False)
       '             Call TLI.TypeLibInfoFromFile(LP).Register
      '              Call MsgBox(P, vbOKOnly Or vbInformation, "IMA2 Component Library Manager")
     '           End If
    '        Else
   '
  '              'Create object
 '           End If
'        End If
    
    End Sub
    
    Private Sub DeleteComponent(Path As String)
        
        Dim C As IComponent
        
        If PathLevel(Path) <= PL_LOCATOR Then Exit Sub
        
        On Error Resume Next
        Set C = m_AL.Locate(Path)
        If Err Then Err.Clear: Call atv.Locator.Unregister(Path)
        
        If C Is Nothing Then
            Call m_AL.Unregister(Path)
        Else
            If C.Activated Then
                Call ActivateBranch(Path, False)
                atv.Refresh
                atv.ExpandAll
            Else
                Call ActivateBranch(Path, False, True)
                
'                If MsgBox("Deleting an activated component from the IMA2 network will release its bindings and shut down the component, possibly causing instability in other agents. Are you sure you wish to unregister " + Path + " while it is activated?", vbOKCancel, "Delete Activated Component") <> vbOK Then Exit Sub
 '               C.Activated = False
  '              If MsgBox("Are you sure you wish to delete " + Path + " from the IMA2 network?", vbOKCancel Or vbInformation, "Delete Deactivated Component") <> vbOK Then Exit Sub
            End If
            
            'Dim Paths() As String
            
            'Paths = m_AL.Components
            'For I = LBound(Paths) To UBound(Paths)
                'Call C.Destruct
                'Call atv.Locator.Unregister(Path)
            'Next I
'            Call m_AL.Unregister(Path)
        End If
    
    End Sub

    Private Sub ActivateBranch(Path As String, Activated As Boolean, Optional Destruct As Boolean = False)
        
        On Error Resume Next
        
        Dim Paths() As String
        Dim LP      As Integer
        Dim I       As Integer
        Dim C       As IComponent
        
        LP = Len(Path)
        Paths = m_AL.Components
        
        For I = LBound(Paths) To UBound(Paths)
            If Left(Paths(I), LP) <> Path Then Paths(I) = ""
        Next I
        
        Call QuickSortStrings(Paths)
        
        For I = UBound(Paths) To LBound(Paths) Step -1
            If Paths(I) <> "" Then
                Set C = m_AL.Locate(Paths(I))
                If NN(C) Then
                    C.Activated = Activated
                    If Destruct Then
                        Call C.Destruct
                        Err.Clear
                        Call m_AL.Unregister(Paths(I))
                        Err.Clear
                    End If
                End If
            End If
        Next I
        
    End Sub
    
    Private Sub RefreshComponent()
        Dim O   As Object
        If PathLevel(atv.Path) <= PL_LOCATOR Then Exit Sub
        Set O = atv.Locator.Locate(atv.Path)
        Call UpdatePropertyValues(O)            'Read IDispatch properties values
        If Err Then Stop
    End Sub

'*********************************************************************************************************************************************************************
' AgentListview Events
'*********************************************************************************************************************************************************************
    
    Private Sub alv_ItemClick(ByVal Item As MSComctlLib.ListItem)
        'wbv.Caption = alv.Path
    End Sub
    
    Private Sub alv_DblClick(ByVal Item As MSComctlLib.ListItem)
        If Item Is Nothing Then Exit Sub
        Select Case Item.SmallIcon
            Case II_Property:   Call SetProperty(atv.Path, Item.Text): Call RefreshComponent
            Case II_Method:     Call CallMethod(atv.Path, Item.Text): Call RefreshComponent
            Case II_Binding:
                Dim C As IComponent
                Set C = m_AL.Locate(atv.Path)
                Set frmBindings.NetList = m_Net
                Call frmBindings.ShowDialog(C.Bindings.Settings.Description(Item.Text))
                If frmBindings.Cancelled Then Exit Sub
                Call C.Bindings.Settings.Remove(Item.Text)
                C.Bindings.Settings.Add Item.Text, frmBindings.Binding.Path, frmBindings.Binding.PIDs, frmBindings.Binding.IIDs, frmBindings.Binding.BindType
                C.Bindings.Settings.Description(Item.Text).Path = frmBindings.Binding.Path
                Item.SubItems(2) = frmBindings.Binding.Path
                Unload frmBindings
            Case Else:
                atv.Path = Item.Key
                If alv.ListItems.Count > 0 Then Call alv.SelectItem(1)
        End Select
    End Sub

    Private Sub alv_ItemMenu(ByVal Item As MSComctlLib.ListItem)
        Dim IsContainer As Boolean
        If Item Is Nothing Then
            IsContainer = (atv.SelectedItem.Image = II_Container) Or (atv.SelectedItem.Image = II_Locator)
            Call CheckALVMenus(alv.ViewPath, False, IsContainer)
        Else
            Call CheckALVMenus(Item.Key, True, atv.SelectedItem.Image = II_Container)
        End If
        PopupMenu mnuCmp
    End Sub

    Private Sub alv_KeyPress(KeyAscii As Integer)
    
        If KeyAscii = 13 Then Call alv_DblClick(alv.SelectedItem)
    
        If KeyAscii = 8 And Not (atv.SelectedItem.Parent Is Nothing) Then
            Call atv.SelectItem(atv.SelectedItem.Parent.Index)
            If alv.ListItems.Count > 0 Then Call alv.SelectItem(1)
        End If
    
    End Sub

    Private Sub alv_ViewPathChange(NewPath As String)
    
        
        Dim C As Node
        Dim C1 As Node
        
        Set C = atv.SelectedItem.Child
        Set C1 = C
        
        While NN(C)
            alv.ListItems(C.Key).ForeColor = C.ForeColor
            Set C = C.Next
        Wend
        
    
    End Sub

'*********************************************************************************************************************************************************************
' AgentTreeview Events
'*********************************************************************************************************************************************************************

    Private Sub atv_DragStart()
        atv.BeginOLEDrag
    End Sub

    Private Sub atv_KeyUp(KeyCode As Integer, Shift As Integer)
        If KeyCode = vbKeyDelete Then Call DeleteComponent(atv.Path)
    End Sub
    
    Private Sub atv_NodeClick(ByVal Node As MSComctlLib.Node)
        alv.ViewPath = atv.Path
        If atv.Path = "\\" Then
            wbv.Caption = atv.SelectedItem.Text
            wbv.ForeColor = atv.SelectedItem.ForeColor
        Else
            wbv.Caption = atv.Path
            wbv.ForeColor = atv.SelectedItem.ForeColor
        End If
        ViewComponent
    End Sub
    
    Private Sub atv_NodeMenu(ByVal Node As MSComctlLib.Node)
       If Node Is Nothing Then Exit Sub
        
        If Node.Key = "\\" Then
            Call CheckATVMenus(Node.Key, True)
        Else
        Dim C As IComponent
            Set C = m_AL.Locate(Node.Key)
            Call CheckATVMenus(Node.Key, TypeOf C Is IContainer)
        End If
        
        PopupMenu mnuCmp
    End Sub

    Private Sub atv_AfterLabelEdit(Cancel As Boolean, NewString As String)

        If Not ValidComponentName(NewString) Then
            Cancel = True
            Exit Sub
        End If
        
        atv.Nodes.Remove atv.SelectedItem.Index     'Remove the name entering node
        m_CD.Path = m_CD.Path + NewString           'Update the prospective path
        
        On Error Resume Next
        
        'Check to see if we're creating it in the DAD process or the normal way
        If Right(m_CD.PID, 1) = "*" Then
            
            Dim C As IComponent
            Dim P As IContainer
            Dim RealPID As String
            
            'This is added functionality to allow VC++ components to be debugged. (RO)
            RealPID = Left(m_CD.PID, Len(m_CD.PID) - 1)
            Set C = CreateObject(RealPID)
            Set P = m_AL.Locate(ParentFromPath(m_CD.Path))
            Call C.Construct(m_CD.Path, RealPID, P.Locator)
            Call P.Locator.Register(C)
        Else
            'This creates the IMA2 component according to factory defaults
            Call CreateIMA2Component(m_CD.Path, m_CD.PID, m_CD.Machine, True)
        End If
        If Err Then MsgBox Err.Description, vbOKOnly Or vbCritical, "IMA2 Component Creation Error"

    End Sub

'*********************************************************************************************************************************************************************
' Property Viewing Code
'*********************************************************************************************************************************************************************
    Private Sub ViewComponent()
        Dim O   As Object
        Dim C   As IComponent
        Dim T   As TypeInfo
        Dim M   As Members
        Dim CD  As New CmpDesc
        
        If PathLevel(atv.Path) = PL_NETWORK Then
            cmv.Visible = False
            
            Exit Sub
        End If
        
        cmv.Visible = True
        
        On Error Resume Next
        Set O = atv.Locator.Locate(atv.Path)
        If Err Or O Is Nothing Then Err.Clear: Exit Sub
        
        Set C = O
        
        With C
            cmv.CName = NameFromPath(.Path)
            cmv.Machine = .Machine
            cmv.PID = .PID
            cmv.Thread = .Thread
            cmv.Process = .Process
            cmv.Activated = .Activated
        End With
        
        If PathLevel(atv.Path) <= PL_LOCATOR Then Exit Sub
        
        Set M = TLI.InterfaceInfoFromObject(O).Members
        
        Call ViewState(C)
        Call LoadMembers(M)             'Load AgentListview with Prop/Method info
        Call ShowParameters(M)          'Show IDispatch parameter list
        Call UpdatePropertyValues(O)    'Read IDispatch properties values
        Call ShowBindings(O)

        If Err Then
            Err.Clear
            'Stop
        End If

    End Sub
    
    Private Sub ViewProperties()
        Dim O   As Object
        
        If PathLevel(atv.Path) <= PL_LOCATOR Then Exit Sub
        
        On Error Resume Next
        Set O = atv.Locator.Locate(atv.Path)
        If Err Or O Is Nothing Then Err.Clear: Exit Sub
        
        Call UpdatePropertyValues(O)    'Read IDispatch properties values
        Call ShowBindings(O)

        If Err Then Stop

    End Sub
    
    
    Private Sub ViewState(C As IComponent)
        mnuCmp_Activated.Checked = C.Activated
        If mnuCmp_Activated.Checked Then
            atv.SelectedItem.ForeColor = QBColor(2)
        Else
            atv.SelectedItem.ForeColor = QBColor(12)
        End If
        wbv.ForeColor = atv.SelectedItem.ForeColor
    End Sub
    
    Private Sub ShowBindings(O As Object)
        
        Dim I       As Integer
        Dim C       As IComponent
        Dim BI()    As BindingInfo
        Dim LI      As ListItem
        
        Set C = O
        If C.Bindings Is Nothing Then Exit Sub
        If C.Bindings.Settings.Count = 0 Then Exit Sub
        
        BI = C.Bindings.Settings.Descriptions
        
        For I = LBound(BI) To UBound(BI)
            Set LI = alv.ListItems.Add(, , BI(I).Name, , II_Binding)
            LI.SubItems(1) = "Binding"

            If BI(I).BindType And BT_Collection Then
                LI.SubItems(1) = "Binding List"
                LI.SubItems(2) = BI(I).Path
            
            ElseIf Not ArrayEmpty(BI(I).IIDs) Then
            
            ElseIf Not ArrayEmpty(BI(I).PIDs) Then
            
            
            End If
        Next
    
    End Sub
    
    Private Sub LoadMembers(M As Members)
        
        On Error Resume Next
        
        Dim I   As Integer
        Dim OP  As String       'Old procedure name
        Dim MI  As MemberInfo
        Dim LI  As ListItem
        
        For I = 8 To M.Count
            Set MI = M(I)
            If MI.Name <> OP Then
                If (MI.InvokeKind = INVOKE_FUNC) And mnuView_Object_Methods.Checked Then
                    Set LI = alv.ListItems.Add(, MI.Name, MI.Name, , II_Method)
                ElseIf (MI.InvokeKind <> INVOKE_FUNC) And mnuView_Object_Properties.Checked Then
                    Set LI = alv.ListItems.Add(, MI.Name, MI.Name, , II_Property)
                End If
                LI.Tag = Str(I)
            End If
            OP = MI.Name
        Next
    End Sub
    
    Private Sub ShowParameters(M As Members)
        Dim LI  As ListItem
        Dim MI  As MemberInfo
        Dim PD  As String               'Parameter Description
        Dim RT  As String               'Member Return Type
        
        For Each LI In alv.ListItems
            If LI.Tag <> "" Then
                Set MI = M(Val(LI.Tag))
                Call DecodeParameters(MI, PD, RT)
                RT = RT + " "
                If RT = " " Then RT = ""
                If LI.SmallIcon = II_Method Then RT = RT + "Method"
                If PD = "()" Then PD = "": RT = Trim(RT)
                LI.SubItems(1) = RT + PD
            End If
        Next
    End Sub
    
    Private Sub UpdatePropertyValues(O As Object)
        Dim LI  As ListItem
        For Each LI In alv.ListItems
            If LI.SmallIcon = II_Property Then LI.SubItems(2) = CStr(ReadProperty(O, LI.Text))
        Next
    End Sub
    
    Public Function ReadProperty(O As Object, PN As String) As Variant
        On Error Resume Next
        Dim V As Variant
        V = CallByName(O, PN, VbGet)
        If Err Then
            V = "(error reading property)"
        ElseIf (VarType(V) And vbArray) Then
            Err.Clear
            V = "(...)"
        ElseIf VarType(V) = vbString Then
            V = Chr(34) + V + Chr(34)
        End If
        ReadProperty = V
    End Function
    
    Private Sub DecodeParameters(MI As MemberInfo, PD As String, RT As String)
        
        Dim PI As ParameterInfo
        Dim N As String
        Dim T As String
        Dim PL As String
        
        PD = ""
        RT = Replace(Replace(TypeName(MI.ReturnType.TypedVariant), "(", "["), ")", "]")
        If RT = "Empty" Then RT = ""

        For Each PI In MI.Parameters
            If PI.Flags And PARAMFLAG_FRETVAL Then
                RT = TypeName(PI.VarTypeInfo.TypedVariant)
            Else
                N = PI.Name
                T = TypeName(PI.VarTypeInfo.TypedVariant)
                If PI.Optional Then
                    PL = ", [" + N + " As " + T + "]"
                ElseIf PI.Default Then
                    PL = ", [" + N + " As " + T + " = " + "]"
                Else
                    PL = ", " + N + " As " + T
                End If
                PD = PD + PL
            End If
        Next
        PD = "(" + Mid(PD, 3) + ")"
        'If PD = "()" Then PD = "(void)"
    
    End Sub
    
    Private Sub CallMethod(Path As String, MethName As String)
        
        On Error Resume Next
        
        Dim O       As Object
        Dim TS      As String   'Type string
        Dim Prompt  As String   'Prompt
        Dim Args    As String   'Args from TypeString
        Dim AC      As Integer  'Argument count
           
        Set O = atv.Locator.Locate(Path)
        TS = alv.SelectedItem.SubItems(1)
        
        If InStr(TS, "(") Then
            AC = StrCount(TS, ",") + 1
            Args = Mid(TS, InStr(TS, "(") + 1)
            Args = Left(Args, Len(Args) - 1)
            Prompt = "Call function '" + MethName + "' on " + Path
            'Args = InputBox(Prompt, "Call Component Method", Args)
            
            Call frmParams.AddItem("Name", "String", "Boo")
            Call frmParams.AddItem("Height", "Integer", "10")
            Call frmParams.AddItem("Width", "Integer", "15")
            
            frmParams.ShowDialog
            
            ReDim Vars(0 To AC - 1) As Variant
            Dim Strs()              As String
            Dim I                   As Integer
            
            Strs = Split(Args, ",")
            
            If AC <> UBound(Strs) + 1 Then
                MsgBox ("Number of parameters does not match.")
                Exit Sub
            End If
            
            For I = 0 To AC - 1
                Vars(I) = CVar(Strs(I))
            Next I
            
'            Stop
            
            Call CallByName(O, MethName, VbMethod, CDbl(0))
        Else
            Call CallByName(O, MethName, VbMethod)
        End If
        
        
        Unload frmParams
        
        If Err Then Err.Clear: Exit Sub
    
    End Sub
    
    
    Private Sub SetProperty(Path As String, PropName As String)
        Dim NV  As String
        Dim OV  As String
        Dim P   As String
        Dim V   As Variant
        Dim O   As Object
           
        Set O = atv.Locator.Locate(Path)
        
        On Error Resume Next
        V = CallByName(O, PropName, VbGet)
        If Err Then Err.Clear: Exit Sub
        
        OV = CStr(V)
        P = "Set property '" + PropName + "' on " + Path
        NV = InputBox(P, "Change Component Property", OV)
        If NV = "" Then Exit Sub
        Call CallByName(O, PropName, VbLet, CVar(NV))
    End Sub

'*********************************************************************************************************************************************************************
' Form Events
'*********************************************************************************************************************************************************************

    Private Sub Form_Load()
        Dim I As Integer
        
        'Call LoadUserOptions
        Call LoadFormPosition(Me)
        
        'Update user UI settings
        mnuView_Object_Properties.Checked = CBool(GetSetting(App.EXEName, "frmMain", ".ShowProperties", True))
        mnuView_Object_Methods.Checked = CBool(GetSetting(App.EXEName, "frmMain", ".ShowMethods", True))
        alv.ColumnHeaders(1).Width = Val(GetSetting(App.EXEName, "frmMain", "CH1W", "" & alv.ColumnHeaders(1).Width))
        alv.ColumnHeaders(2).Width = Val(GetSetting(App.EXEName, "frmMain", "CH2W", "" & alv.ColumnHeaders(2).Width))
        atv.Width = Val(GetSetting(App.EXEName, "frmMain", "AtvWidth", "" & atv.Width))
        
        'Set up Icon Manager
        m_Icons.ImageList.UseMaskColor = True
        m_Icons.Directory = "C:\IMA2\System\Icons"
        
        'Refresh component list
        m_Net.Refresh
        
        'Initialize AgentTreeview and AgentListView
        Set atv.NetList = m_Net
        Set alv.NetList = m_Net
        
        'Refresh network information
        atv.Path = "\\"
        atv.ExpandAll
        Set m_AL = atv.Locator
        
        'Load Favorites
        For I = 1 To 10
            Load mnuCmp_New_Favorites(I)
            mnuCmp_New_Favorites(I).Visible = False
        Next I
    
    End Sub
    
    '******************************************************************************************************
    
    Private Sub Form_Resize()
        
        On Error Resume Next
        Dim BP_Top, BP_Left, BP_Width, BP_Height, TP_Height, TP_Top
        
        If Me.Visible = False Then Exit Sub
        If Me.WindowState = vbMinimized Then Exit Sub
        
        slr.Visible = alv.Visible And atv.Visible
        sud.Visible = (alv.Visible Or atv.Visible) And wbv.Visible
        
        If wbv.Visible Then TP_Height = wbv.Height + sud.Height
        
        TP_Top = Toolbar1.Height
        BP_Left = bvlLeft.Width
        BP_Top = TP_Top + TP_Height
        BP_Height = Me.ScaleHeight - stb.Height - BP_Top
        BP_Width = Me.ScaleWidth - (2 * bvlLeft.Width)
            
        wbv.Move BP_Left, TP_Top, BP_Width, wbv.Height
        sud.Move BP_Left, TP_Top + wbv.Height, BP_Width, sud.Height
        
        If Not alv.Visible Then
            atv.Move BP_Left, BP_Top, BP_Width, BP_Height
        ElseIf Not atv.Visible Then
            cmv.Move BP_Left, BP_Top + (BP_Height - cmv.Height), BP_Width
            alv.Move BP_Left, BP_Top, BP_Width, BP_Height - cmv.Height
        Else
            atv.Move BP_Left, BP_Top, atv.Width, BP_Height
            slr.Move atv.Left + atv.Width, BP_Top, slr.Width, BP_Height
            
            cmv.Move slr.Left + slr.Width, BP_Top + (BP_Height - cmv.Height) - 2, Me.ScaleWidth - slr.Width - atv.Width - (bvlLeft.Width) - 2
            alv.Move slr.Left + slr.Width, BP_Top, Me.ScaleWidth - slr.Width - atv.Width - (bvlLeft.Width * 1), BP_Height - cmv.Height
        End If
       
       
    End Sub

    '******************************************************************************************************
    
    Private Sub Form_Unload(Cancel As Integer)
    
        Call SaveFormPosition(Me)
        Call SaveSetting(App.EXEName, "frmMain", ".ShowProperties", CStr(mnuView_Object_Properties.Checked))
        Call SaveSetting(App.EXEName, "frmMain", ".ShowMethods", CStr(mnuView_Object_Methods.Checked))
        Call SaveSetting(App.EXEName, "frmMain", "CH1W", "" & alv.ColumnHeaders(1).Width)
        Call SaveSetting(App.EXEName, "frmMain", "CH2W", "" & alv.ColumnHeaders(2).Width)
        Call SaveSetting(App.EXEName, "frmMain", "AtvWidth", "" & atv.Width)
    
        Dim F As Form
        
        For Each F In Forms
            If Not (F Is Me) Then Unload F
        Next
    
    End Sub

    '******************************************************************************************************
    
    Private Sub XXXActivateBranch(Path As String, Value As Boolean)

        On Error Resume Next
        Dim Paths() As String
        Dim C       As IComponent
        Dim I       As Integer
        
        Paths = m_AL.Components
        
        For I = LBound(Paths) To UBound(Paths)
            If IsDescendant(Paths(I), Path) Then
                Set C = m_AL.Locate(Paths(I))
                C.Activated = Value
                If Err Then
                    atv.Nodes(Paths(I)).ForeColor = QBColor(7)
                    Err.Clear
                ElseIf C.Activated Then
                    atv.Nodes(Paths(I)).ForeColor = QBColor(2)
                Else
                    atv.Nodes(Paths(I)).ForeColor = QBColor(12)
                End If
            End If
        Next I
        
        mnuCmp_Activated.Checked = C.Activated
        wbv.ForeColor = atv.SelectedItem.ForeColor

    End Sub

Private Sub mnuCmp_ActivateBranch_Click()

    If Me.ActiveControl Is atv Then
        Call ActivateBranch(atv.Path, True)
    ElseIf Me.ActiveControl Is alv Then
        Call ActivateBranch(alv.Path, True)
    End If
    
    m_Net.Refresh
    atv.ExpandAll
 
End Sub

    Private Sub mnuCmp_Activated_Click()
        Dim C As IComponent
        If Me.ActiveControl Is atv Then
            
            'Call ActivateBranch(atv.Path, Not mnuCmp_Activated.Checked)

            Set C = m_AL.Locate(atv.Path)
            C.Activated = Not mnuCmp_Activated.Checked
            mnuCmp_Activated.Checked = C.Activated
            If mnuCmp_Activated.Checked Then
                atv.SelectedItem.ForeColor = QBColor(2)
            Else
                atv.SelectedItem.ForeColor = QBColor(12)
            End If
            wbv.ForeColor = atv.SelectedItem.ForeColor
        End If
    End Sub

Private Sub mnuCmp_Copy_Click()
    Clipboard.Clear
    Clipboard.SetText "{IMA2 Component} " + atv.Path, vbCFText
End Sub

Private Sub mnuCmp_DeactivateBranch_Click()

    If Me.ActiveControl Is atv Then
        Call ActivateBranch(atv.Path, False)
    ElseIf Me.ActiveControl Is alv Then
        Call ActivateBranch(alv.Path, False)
    End If

    m_Net.Refresh
    atv.ExpandAll

End Sub

'*********************************************************************************************************************************************************************
' Menu Events
'*********************************************************************************************************************************************************************
    Private Sub mnuCmp_New_Agent_Click()
        Call NewAgentComponent
    End Sub
    
    Private Sub mnuCmp_Delete_Click()
        If Me.ActiveControl Is atv Then
            Call DeleteComponent(atv.Path)
        ElseIf Me.ActiveControl Is alv Then
            Call DeleteComponent(alv.Path)
        End If
        
    End Sub

    Private Sub mnuTextSummary_Click()
        frmTextSummary.ShowModal
    End Sub

    Private Sub mnuView_Refresh_Click()
        Call RefreshComponent
    End Sub
    
    Private Sub mnuCmp_New_Cmp_Click()
        Call NewComponent
    End Sub

    Private Sub mnuCmp_SaveAs_Click()
        
        Dim Dlg As New frmSaveAs
        Dim P() As String
        
        P = GetSavedPaths()                 'Get Saved Paths
        Call Dlg.DoSave(P, atv.Nodes)       'Start the file save wizard
    
    End Sub

    Private Sub mnuFile_Exit_Click()
        End
    End Sub

'*********************************************************************************************************************************************************************
' View Menu Events
'*********************************************************************************************************************************************************************
    
    Private Sub mnuView_Listview_Click()
        mnuView_Listview.Checked = Not mnuView_Listview.Checked
        alv.Visible = mnuView_Listview.Checked
        slr.Visible = False
        Form_Resize
    End Sub
    
    Private Sub mnuView_Treeview_Click()
        mnuView_Treeview.Checked = Not mnuView_Treeview.Checked
        atv.Visible = mnuView_Treeview.Checked
        Form_Resize
    End Sub
    
    Private Sub mnuView_WebView_Click()
        mnuView_WebView.Checked = Not mnuView_WebView.Checked
        wbv.Visible = mnuView_WebView.Checked
        Form_Resize
    End Sub

'*********************************************************************************************************************************************************************
' Property and Method View Menus
'*********************************************************************************************************************************************************************
    Private Sub mnuView_Object_Methods_Click()
        mnuView_Object_Methods.Checked = Not mnuView_Object_Methods.Checked
        Call atv_NodeClick(atv.SelectedItem)
    End Sub
    
    Private Sub mnuView_Object_Properties_Click()
        mnuView_Object_Properties.Checked = Not mnuView_Object_Properties.Checked
        Call atv_NodeClick(atv.SelectedItem)
    End Sub

'*********************************************************************************************************************************************************************
' Splitter Events
'*********************************************************************************************************************************************************************

    Private Sub slr_OnSplitterRelease(Delta As Single)
        If atv.Width + Delta < 1 Then Exit Sub
        atv.Width = atv.Width + Delta
        Form_Resize
    End Sub
    
    Private Sub sud_OnSplitterRelease(Delta As Single)
        If wbv.Height + Delta < 1 Then Exit Sub
        wbv.Height = wbv.Height + Delta
        Form_Resize
    End Sub

'*********************************************************************************************************************************************************************
' Menu Management
'*********************************************************************************************************************************************************************
    
    Private Sub DisplayFavorites()
        If m_Favs.Count = 0 Then
            mnuCmp_New_Favorites.Item(0).Caption = "(no favorites)"
            mnuCmp_New_Favorites.Item(0).Enabled = False
        Else
            Dim I As Integer
            For I = m_Favs.Count To MAX_FAVS
                mnuCmp_New_Favorites.Item(I).Visible = False
            Next
            For I = 0 To m_Favs.Count - 1
                mnuCmp_New_Favorites.Item(I).Caption = m_Favs(I + 1)
                mnuCmp_New_Favorites.Item(I).Visible = True
            Next
        End If
    End Sub

    Private Sub CheckALVMenus(Path As String, ItemSelected As Boolean, IsContainer As Boolean)
    
        Dim PL As Integer
        
        PL = PathLevel(Path)
        
        Call DisplayFavorites
        
        mnuCmp_Properties.Visible = True

        mnuCmp_Activated.Visible = (PL > PL_LOCATOR)
        mnuCmp_Activated_Sep.Visible = mnuCmp_Activated.Visible
        
        mnuCmp_Connect.Visible = (PL = PL_NETWORK)
        mnuCmp_Disconnect.Visible = (PL = PL_LOCATOR) And ItemSelected
        mnuCmp_Connect_Sep.Visible = mnuCmp_Disconnect.Visible Or (mnuCmp_Connect.Visible And ItemSelected)
        
        mnuCmp_New.Visible = (PL >= PL_LOCATOR)
        mnuCmp_New_Sep.Visible = mnuCmp_New.Visible
        
        mnuCmp_Copy.Visible = PL > PL_NETWORK
        mnuCmp_Paste.Visible = PL > PL_NETWORK
        
        mnuCmp_Copy.Enabled = ItemSelected And (PL > PL_LOCATOR)
        mnuCmp_Paste.Enabled = (Not ItemSelected) And (PL > PL_NETWORK)
        
        mnuCmp_Delete.Visible = ItemSelected And (PL > PL_LOCATOR)
        
        mnuCmp_SaveAs.Visible = ItemSelected And (PL > PL_LOCATOR)
        
        mnuCmp_Properties.Visible = ItemSelected
    
        mnuCmp_Delete_Sep.Visible = mnuCmp_Delete.Visible
        mnuCmp_SaveAs_Sep.Visible = mnuCmp_SaveAs.Visible
        mnuCmp_Paste_Sep.Visible = mnuCmp_Copy.Visible And (mnuCmp_Delete.Visible Or mnuCmp_SaveAs.Visible Or mnuCmp_Properties.Visible)
    
    End Sub

    Private Sub CheckATVMenus(Path As String, IsContainer As Boolean)
    
        Dim PL As Integer
        
        PL = PathLevel(Path)
        
        Call DisplayFavorites
        mnuCmp_Properties.Visible = True
        
        mnuCmp_Activated.Visible = (PL > PL_LOCATOR)
        
        mnuCmp_ActivateBranch.Visible = (PL >= PL_LOCATOR) And IsContainer
        mnuCmp_DeactivateBranch.Visible = mnuCmp_ActivateBranch.Visible
        
        mnuCmp_Connect.Visible = (PL = PL_NETWORK)
        mnuCmp_Disconnect.Visible = (PL = PL_LOCATOR)
        
        mnuCmp_New.Visible = (PL >= PL_LOCATOR) And (IsContainer Or PL = PL_LOCATOR)
        
        mnuCmp_Copy.Visible = (PL > PL_NETWORK)
        mnuCmp_Paste.Visible = mnuCmp_Copy.Visible
        
        mnuCmp_Copy.Enabled = (PL > PL_NETWORK)
        mnuCmp_Paste.Enabled = (PL > PL_NETWORK) And (InStr(Clipboard.GetText(), "{IMA2 Component}") = 1)
        
        mnuCmp_Delete.Visible = (PL > PL_LOCATOR)
        mnuCmp_SaveAs.Visible = (PL > PL_LOCATOR)
        
        mnuCmp_New_Sep.Visible = mnuCmp_New.Visible
        mnuCmp_Connect_Sep.Visible = mnuCmp_Disconnect.Visible Or mnuCmp_Connect.Visible
        mnuCmp_Activated_Sep.Visible = mnuCmp_Activated.Visible
        mnuCmp_Branch_Sep.Visible = mnuCmp_ActivateBranch.Visible
        mnuCmp_Delete_Sep.Visible = mnuCmp_Delete.Visible
        mnuCmp_SaveAs_Sep.Visible = mnuCmp_SaveAs.Visible
        mnuCmp_Paste_Sep.Visible = mnuCmp_Copy.Visible And (mnuCmp_Delete.Visible Or mnuCmp_SaveAs.Visible Or mnuCmp_Properties.Visible)
    
    End Sub


'*********************************************************************************************************************************************************************
' Misc. Functions
'*********************************************************************************************************************************************************************
    
    Private Function GetSavedPaths() As String()
        
        Dim Paths() As String
        Dim PC      As String
        Dim UB      As Integer
        Dim LB      As Integer
        Dim I       As Integer
        
        Paths = m_Net.Items
        LB = LBound(Paths)
        UB = UBound(Paths)
        
        PC = atv.Path
        
        For I = LB To UB
            If Not IsDescendant(Paths(I), PC) Then Paths(I) = ""
        Next

        Call RemoveBlankStrings(Paths)
        
        GetSavedPaths = Paths
    
    End Function

