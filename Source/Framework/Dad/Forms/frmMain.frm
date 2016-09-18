VERSION 5.00
Object = "{7B492EBB-3B8A-4D7E-9021-86BB71534052}#1.1#0"; "IMA2_HelperX.ocx"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{81605258-1A3B-47EE-A9BE-4F1963575A0F}#1.1#0"; "IMA2_DadX.ocx"
Begin VB.Form frmMain 
   BackColor       =   &H80000005&
   Caption         =   "Distributed Agent Designer 1.0"
   ClientHeight    =   5085
   ClientLeft      =   165
   ClientTop       =   855
   ClientWidth     =   9660
   Icon            =   "frmMain.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   339
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   644
   StartUpPosition =   3  'Windows Default
   Begin IMA2_DADX.AgentListview alv 
      Height          =   2895
      Left            =   2760
      TabIndex        =   6
      Top             =   960
      Width           =   6855
      _ExtentX        =   12091
      _ExtentY        =   5106
   End
   Begin IMA2_DADX.AgentTreeview atv 
      Height          =   3735
      Left            =   0
      TabIndex        =   5
      Top             =   960
      Width           =   2655
      _ExtentX        =   4683
      _ExtentY        =   6588
   End
   Begin IMA2_DAD.CmpView cmv 
      Height          =   855
      Left            =   2760
      TabIndex        =   4
      Top             =   3840
      Width           =   6975
      _ExtentX        =   12303
      _ExtentY        =   1508
      BStyle          =   0
   End
   Begin IMA2_HelperX.Bevel Bevel1 
      Align           =   1  'Align Top
      Height          =   30
      Left            =   0
      Top             =   0
      Width           =   9660
      _ExtentX        =   17039
      _ExtentY        =   53
      BS              =   1
      A               =   1
      C1              =   -2147483632
      C2              =   -2147483627
   End
   Begin IMA2_HelperX.Bevel bvlRight 
      Align           =   4  'Align Right
      Height          =   4764
      Left            =   9624
      Top             =   36
      Width           =   36
      _ExtentX        =   53
      _ExtentY        =   8414
      BS              =   1
      D               =   1
      C1              =   -2147483633
      C2              =   -2147483634
   End
   Begin IMA2_HelperX.Bevel bvlBottom 
      Align           =   2  'Align Bottom
      Height          =   30
      Left            =   0
      Top             =   4800
      Width           =   9660
      _ExtentX        =   17039
      _ExtentY        =   53
      BS              =   1
      C1              =   -2147483633
      C2              =   -2147483639
   End
   Begin IMA2_HelperX.Bevel bvlLeft 
      Align           =   3  'Align Left
      Height          =   4764
      Left            =   0
      Top             =   36
      Width           =   36
      _ExtentX        =   53
      _ExtentY        =   8414
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
      Top             =   4836
      Width           =   9660
      _ExtentX        =   17039
      _ExtentY        =   423
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   1
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   1
            Object.Width           =   16510
         EndProperty
      EndProperty
   End
   Begin IMA2_HelperX.SplitterLR slr 
      Height          =   3750
      Left            =   2535
      TabIndex        =   3
      Top             =   960
      Width           =   75
      _ExtentX        =   132
      _ExtentY        =   6615
   End
   Begin IMA2_HelperX.SplitterUD sud 
      Height          =   75
      Left            =   0
      TabIndex        =   1
      Top             =   900
      Width           =   96750
      _ExtentX        =   170656
      _ExtentY        =   132
   End
   Begin IMA2_HelperX.WebView wbv 
      Height          =   435
      Left            =   0
      TabIndex        =   2
      TabStop         =   0   'False
      Top             =   360
      Width           =   10155
      _ExtentX        =   17912
      _ExtentY        =   767
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
         Begin VB.Menu mnuCmp_New_Context 
            Caption         =   "Parent Context"
            Checked         =   -1  'True
         End
         Begin VB.Menu mnuCmp_New_Favorites 
            Caption         =   "<Favorite1>"
            Index           =   0
         End
         Begin VB.Menu mnuCmp_New_Favorites 
            Caption         =   "<Favorite2>"
            Index           =   1
         End
         Begin VB.Menu mnuCmp_New_Favorites 
            Caption         =   "<Favorite3>"
            Index           =   2
         End
         Begin VB.Menu mnuCmp_New_Favorites 
            Caption         =   "<Favorite4>"
            Index           =   3
         End
         Begin VB.Menu mnuCmp_New_Favorites 
            Caption         =   "<Favorite5>"
            Index           =   4
         End
         Begin VB.Menu mnuCmp_New_Favorites 
            Caption         =   "<Favorite6>"
            Index           =   5
         End
         Begin VB.Menu mnuCmp_New_Favorites 
            Caption         =   "<Favorite7>"
            Index           =   6
         End
         Begin VB.Menu mnuCmp_New_Favorites 
            Caption         =   "<Favorite8>"
            Index           =   7
         End
         Begin VB.Menu mnuCmp_New_Favorites 
            Caption         =   "<Favorite9>"
            Index           =   8
         End
         Begin VB.Menu mnuCmp_New_Favorites 
            Caption         =   "<Favorite10>"
            Index           =   9
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
      Begin VB.Menu mnuTools_ListRefresh 
         Caption         =   "&List Refresh"
         Shortcut        =   ^R
      End
      Begin VB.Menu mnuTools_Options 
         Caption         =   "&Options..."
      End
      Begin VB.Menu mnuConnect 
         Caption         =   "&Connect"
      End
      Begin VB.Menu mnuDisconnect 
         Caption         =   "&Disconnect"
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
    Dim m_FavDisplay    As Collection
    Dim m_FavFileNames  As Collection
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
            
            'Had a wierd error with this: Set atv.SelectedItem=atv.Nodes.Add(...)
            'It tried to select the wrong item in the list. So I've separated it out
            'into two lines. 3/21/05-CLC
            Call atv.Nodes.Add(atv.Nodes(atv.Path), tvwChild, atv.Path + "\$new$", "<New Component>", m_Icons.IconIndex(m_CD.PID))
            Set atv.SelectedItem = atv.Nodes.Item(atv.Path + "\$new$")
            atv.StartLabelEdit
        
            'Added option to create "local process" components for VC++ debugging.
            If frmInsert.Context = ICC_Local Then m_CD.PID = m_CD.PID + "*"
        
        'Insert Saved Agent
        Else
            Dim I           As Integer
            Call AddToMRUList(Mid(frmInsert.FilePath, InStrRev(frmInsert.FilePath, "\") + 1), frmInsert.FilePath)
            For I = frmInsert.DescriptionLBound To frmInsert.DescriptionUBound
                Call LoadComponent(frmInsert.DescriptionIndex(I), frmInsert.Context)
            Next I
        End If
                
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
    
    Private Sub LoadComponent(CD As CmpDesc, Context As InsCmpContext)
    
            Dim J           As Integer
            Dim BindInfo()  As IMA2_BindingInfo
            Dim C           As IComponent
            Dim P           As String
            
            P = atv.Path
          
            On Error Resume Next
                        
            
                'atv.Nodes.Add(atv.Nodes(atv.Path),tvwChild,CDs(I).Path,
                'Check to see if we're creating it in the DAD process (with an asterisk).
                'This is added functionality to allow VC++ components to be debugged
                'since VC++ 6.0 requires that the component be created in the DAD process. (RO)
                'Copied and edited from tvw_AfterLabelEdit on 2/18/05 CLC
                
                If Context = ICC_Local Then
                    Dim PLA As ILocatorAdvanced                                     'Parent Locator (advanced)
                    Set PLA = g_AL.Locate(LocatorFromPath(P + "\" + CD.Path))   'Get the parent container's locator
                    Set C = CreateObject(CD.PID)                                'Create the local component
                    Call C.Construct(P + "\" + CD.Path, CD.PID, PLA)        'Construct the component
                    Call PLA.Register(C)                                            'Register it on it's parent locator
                Else
                    'This creates the IMA2 component according to the file
                    Set C = CreateIMA2Component(P + "\" + CD.Path, CD.PID, , True, atv.Locator)
                End If
                
                If StrComp(CD.PID, C.Distributing.PID) = 0 Then
                    If Err Then
                        MsgBox Err.Description, vbOKOnly Or vbCritical, "IMA2 Component Creation Error"
                        Err.Clear
                    End If
                    
                    If Not IsEmpty(CD.Data) Then C.Load CD.Data
                    
                    If Err Then
                        MsgBox Err.Description, vbOKOnly Or vbCritical, "IMA2 Component Data Load Error"
                        Err.Clear
                    End If
                    
                    'Now explicitly copy the binding information into the component. Added 3/18/05--CLC
                    BindInfo = CD.BindingInfo
                    
                    J = UBound(BindInfo)
                    If Err Then    'This tests to see if BindInfo is empty or not.
                        Err.Clear
                    Else
                       For J = LBound(BindInfo) To UBound(BindInfo)
                            Call C.Bindings.Settings.Remove(BindInfo(J).Name)
                            Call C.Bindings.Settings.Add(BindInfo(J))
                            If Err Then
                                MsgBox Err.Description, vbOKOnly Or vbCritical, "IMA2 Component Binding Update Error"
                                Err.Clear
                                Exit For
                            End If
                        Next J
                    End If
                Else
                    If Err Then
                        MsgBox Err.Description, vbOKOnly Or vbCritical, "IMA2 Component Creation Error"
                        Err.Clear
                    Else
                        MsgBox "Unknown Creation Problem:" & CD.Path, vbOKOnly Or vbCritical, "IMA2 Component Creation Error"
                    End If
                End If
                atv.Refresh     'Added 5/16/05 -CLC
                'atv.ExpandAll
               
    End Sub
    
    Private Sub DeleteComponent(Path As String)
        
        Dim C As IComponent
        Dim x As Integer
        
        If PathLevel(Path) <= PL_LOCATOR Then Exit Sub
        
        On Error Resume Next
        Set C = g_AL.Locate(Path)
        If Err Then Err.Clear: Call g_LA.UnRegister(Path)
        
        If C Is Nothing Then
            Call g_LA.UnRegister(Path)
        Else
            
            'TODO: Take into consideration activation and deactivation
            
            'If C.Activated Then
            '    Call ActivateBranch(Path, False)
            '    atv.Refresh
            '    atv.ExpandAll
            'Else
            '    Call ActivateBranch(Path, False, True)
                
'                If MsgBox("Deleting an activated component from the IMA2 network will release its bindings and shut down the component, possibly causing instability in other agents. Are you sure you wish to unregister " + Path + " while it is activated?", vbOKCancel, "Delete Activated Component") <> vbOK Then Exit Sub
 '               C.Activated = False
  '              If MsgBox("Are you sure you wish to delete " + Path + " from the IMA2 network?", vbOKCancel Or vbInformation, "Delete Deactivated Component") <> vbOK Then Exit Sub
            'End If
            
            'Dim Paths() As String
            
            'Paths = g_AL.Components
            'For I = LBound(Paths) To UBound(Paths)
                'Call C.Destruct
                'Call atv.Locator.Unregister(Path)
            'Next I
            
            'Added 4/3/05 by CLC to delete all the components of an agent being deleted
            'Before deleting that agent.
            If C.Distributing.PID = "IMA2_Agent.Agent" Then
                x = MsgBox("Delete agent '" & Path & "' and all children?", vbOKCancel, "Confirm Agent Delete")
                If (x = vbOK) Then
                    Dim nodeset As Nodes
                    Dim agentnode As Node
                    Dim I As Integer
                    Dim childnode As Node
                    Dim Keys() As String
                    Set nodeset = atv.Nodes
                    Set agentnode = nodeset.Item(Path)
                    Set childnode = agentnode.Child
                    ReDim Keys(1 To agentnode.Children)
                    For I = 1 To agentnode.Children
                        Keys(I) = childnode.Key
                        Set childnode = childnode.Next
                    Next I
                    For I = LBound(Keys) To UBound(Keys)
                        DeleteComponent Keys(I)
                    Next I
                    Call g_LA.UnRegister(Path)
                End If
            Else
                Call g_LA.UnRegister(Path)
            End If
        End If
           
    End Sub

    Private Sub ActivateBranch(Path As String, Activated As Boolean, Optional Destruct As Boolean = False)
        
        On Error Resume Next
        
        Dim Paths() As String
        Dim LP      As Integer
        Dim I       As Integer
        Dim C       As IComponent
        
        LP = Len(Path)
        Paths = g_LA.Components
        
        For I = LBound(Paths) To UBound(Paths)
            If Left(Paths(I), LP) <> Path Then Paths(I) = ""
        Next I
        
        Call QuickSortStrings(Paths)
        
        For I = UBound(Paths) To LBound(Paths) Step -1
            If Paths(I) <> "" Then
                Set C = g_AL.Locate(Paths(I))
                If NN(C) Then
                    'C.Activated = Activated
                    If Destruct Then
                        Call C.Destruct
                        Err.Clear
                        Call g_LA.UnRegister(Paths(I))
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
    
    Private Sub alv_ItemClick(ByVal Item As mscomctllib.ListItem)
        'wbv.Caption = alv.Path
    End Sub
    
    Private Sub alv_DblClick(ByVal Item As mscomctllib.ListItem)
        If Item Is Nothing Then Exit Sub
        Dim ItemText As String
        
        ItemText = Item.Text
        
        Select Case Item.SmallIcon
            Case II_Property:   Call SetProperty(atv.Path, Item.Text): Call RefreshComponent
            Case II_Method:     Call CallMethod(atv.Path, Item.Text): Call RefreshComponent
            Case II_Binding:    Call SetBindings(Item)
            Case Else:
                atv.Path = Item.Key
                If alv.ListItems.Count > 0 Then Call alv.SelectItem(1)
        End Select
    End Sub

    Private Sub alv_ItemMenu(ByVal Item As mscomctllib.ListItem)
        Dim IsContainer As Boolean
        If Item Is Nothing Then
            IsContainer = (atv.SelectedItem.Image = II_Container) Or (atv.SelectedItem.Image = II_Locator)
            Call CheckALVMenus(alv.ViewPath, False, IsContainer)
        Else
            Call CheckALVMenus(Item.Key, True, atv.SelectedItem.Image = II_Container)
        End If
        PopupMenu mnuCmp
    End Sub

    'Added 5/13/05 by Christina to implement the Delete key in the list view.
    Private Sub alv_KeyUp(KeyCode As Integer, Shift As Integer)
        If (alv.SelectedItem Is Nothing) Then
            Exit Sub
        End If
        If (ParentFromPath(alv.SelectedItem.Key) = "") Then
            Exit Sub
        End If
        If KeyCode = vbKeyDelete Then Call DeleteComponent(alv.SelectedItem.Key)
        If KeyCode = vbKeyF1 Then Call frmHelp.ShowHelp(alv.SelectedItem.Key)
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
        
        'Set C = atv.SelectedItem.Child
        'Set C1 = C
        
        'While NN(C)
        '    alv.ListItems(C.Key).ForeColor = C.ForeColor
        '    Set C = C.Next
        'Wend
        
    
    End Sub

'*********************************************************************************************************************************************************************
' AgentTreeview Events
'*********************************************************************************************************************************************************************

    Private Sub atv_DragStart()
        atv.BeginOLEDrag
    End Sub

    Private Sub atv_KeyUp(KeyCode As Integer, Shift As Integer)
        If KeyCode = vbKeyDelete Then Call DeleteComponent(atv.Path)
        If KeyCode = vbKeyF1 Then Call frmHelp.ShowHelp(atv.SelectedItem.Key)
    End Sub
    
    Private Sub atv_NodeClick(ByVal Node As mscomctllib.Node)
        Dim C As IComponent
        
        If atv.Path = "\\" Then
            wbv.Caption = atv.SelectedItem.Text
            wbv.ForeColor = atv.SelectedItem.ForeColor
        Else
            Set C = g_AL.Locate(Node.Key)
           If C Is Nothing Then                                                     'Is it an icomponent?
            'This if statement was added by CLC 3/03/05 to avoid a run-time
            'error when the system fails to update the tree view after a
            'component has been deleted.
                atv.Refresh
                Exit Sub
            End If
            wbv.Caption = atv.Path
            wbv.ForeColor = atv.SelectedItem.ForeColor
        End If
        atv.Refresh
        'atv.ExpandAll
        alv.ViewPath = atv.Path
        ViewComponent
        alv.Sort
    End Sub
    
    Private Sub atv_NodeMenu(ByVal Node As mscomctllib.Node)
       If Node Is Nothing Then Exit Sub
        
        If Node.Key = "\\" Then
            Call CheckATVMenus(Node.Key, True)
        Else
        Dim C As IComponent
            Set C = g_AL.Locate(Node.Key)
            If C Is Nothing Then
                'This if statement was added by CLC 3/03/05 to avoid a run-time
                'error when the system fails to update the tree view after a
                'component has been deleted.
                atv.Refresh
            Else
                Call CheckATVMenus(Node.Key, TypeOf C Is IContainer)
                PopupMenu mnuCmp
            End If
        End If
    End Sub

    Private Sub atv_AfterLabelEdit(Cancel As Boolean, NewString As String)

        'If it's not a valid name, force them to try again.
        If Not ValidComponentName(NewString) Then
            Cancel = True
            Exit Sub
        End If
        
        atv.Nodes.Remove atv.SelectedItem.Index     'Remove the name entering node
        m_CD.Path = m_CD.Path + NewString           'Update the prospective path
        
        On Error Resume Next
        
        'Check to see if we're creating it in the DAD process (with an asterisk).
        'This is added functionality to allow VC++ components to be debugged
        'since VC++ 6.0 requires that the component be created in the DAD process. (RO)
        If Right(m_CD.PID, 1) = "*" Then
            Dim C As IComponent             'Created component
            Dim PLA As ILocatorAdvanced     'Parent Locator (advanced)
            Dim RealPID As String           'The real PID (without the asterisk) of the new component
            RealPID = Left(m_CD.PID, Len(m_CD.PID) - 1)         'Ditch the asterisk
            Set PLA = g_AL.Locate(LocatorFromPath(m_CD.Path))   'Get the parent container's locator
            Set C = CreateObject(RealPID)                       'Create the local component
            Call C.Construct(m_CD.Path, RealPID, PLA)           'Construct the component
            Call PLA.Register(C)                                'Register it on it's parent locator
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
        Dim DI  As IMA2.IMA2_DistributingInfo
        
        Dim T   As TypeInfo
        Dim M   As Members
        Dim CD  As New CmpDesc
        
        If PathLevel(atv.Path) = PL_NETWORK Then
            cmv.Visible = False
            Exit Sub
        End If
        
        cmv.Visible = True
        
        'On Error Resume Next
        
         Set O = g_AL.Locate(atv.Path)                                      'You can see all the interface properties (and values) and methods currently in DAD
        If Err Or O Is Nothing Then Err.Clear: Exit Sub
                
        Set C = O
        
        DI = g_IS.Item(atv.Path)
        cmv.Info = DI                                                       'See the Dispatch Information
        
        If PathLevel(atv.Path) <= PL_LOCATOR Then Exit Sub
        
'        MsgBox "Before Interface call"
'        MsgBox "Info: " & C.Distributing.Path & "," & C.Distributing.PID
        Set M = TLI.InterfaceInfoFromObject(O).Members                      'Contains interface props/methods as items.
        
        Call ViewState(C)               'Empty, not used
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
        'mnuCmp_Activated.Checked = C.Activated
        'If mnuCmp_Activated.Checked Then
        '    atv.SelectedItem.ForeColor = QBColor(2)
        'Else
        '    atv.SelectedItem.ForeColor = QBColor(12)
        'End If
        'wbv.ForeColor = atv.SelectedItem.ForeColor
    End Sub
    
    Private Sub ShowBindings(O As Object)
'        MsgBox "In ShowBindings"
        
        Dim I       As Integer
        Dim C       As IComponent
        Dim BI()    As IMA2_BindingInfo
        Dim LI      As ListItem
        
        Set C = O
        On Error Resume Next
        If C.Bindings Is Nothing Then
            If Err = -2147220997 Then
                MsgBox ("Error connecting to component. Cannot display bindings. Delete and recreate.")
            End If
            Exit Sub
        End If
        If C.Bindings.Settings.Count = 0 Then Exit Sub
        
        BI = C.Bindings.Settings.Items
        
        For I = LBound(BI) To UBound(BI)
            Set LI = alv.ListItems.Add(, BI(I).Name, BI(I).Name, , II_Binding)
            LI.SubItems(3) = 2      'Added 5/13/05 to allow for sort-by-type -CLC

            If BI(I).BindType And BT_Collection Then
                LI.SubItems(1) = "Binding List"
                LI.SubItems(2) = BI(I).Path
            Else  'Edited to show non-collection bindings 3/21/05 -CLC
                LI.SubItems(1) = "Binding"
                LI.SubItems(2) = BI(I).Path
            End If
            
            If (Not ArrayEmpty(BI(I).IIDs)) And BI(I).IIDs(0) <> "" Then
                LI.SubItems(1) = LI.SubItems(1) & " - Restricted Type"
            ElseIf (Not ArrayEmpty(BI(I).IIDs)) And BI(I).IIDs(0) <> "" Then
                LI.SubItems(1) = LI.SubItems(1) & " - Restricted Type"
            End If
        Next
    
    End Sub
    
    Private Sub LoadMembers(M As Members)
        
'        MsgBox "In LoadMembers"
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
                    LI.SubItems(3) = 4   'Added 5/13/05 to allow for sort-by-type -CLC
                ElseIf (MI.InvokeKind <> INVOKE_FUNC) And mnuView_Object_Properties.Checked Then
                    Set LI = alv.ListItems.Add(, MI.Name, MI.Name, , II_Property)
                    LI.SubItems(3) = 3   'Added 5/13/05 to allow for sort-by-type -CLC
                End If
                LI.Tag = Str(I)
            End If
            OP = MI.Name
        Next
    End Sub
    
    Private Sub ShowParameters(M As Members)
'        MsgBox "In ShowParameters"
        
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
'        MsgBox "In UpdatePropertyValues"
        Dim LI  As ListItem
        For Each LI In alv.ListItems
            If LI.SmallIcon = II_Property Then LI.SubItems(2) = CStr(ReadProperty(O, LI.Text))
                If Err Then		'!!!!!!! Always get an exception here when doing debug mode in C++
                    Err.Clear
                End If
        Next
    End Sub
    
    Public Function ReadProperty(O As Object, PN As String) As Variant
        On Error Resume Next
        Dim V As Variant
        V = CallByName(O, PN, VbGet)                'O = type of component, PN = name of interface prop/method,
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
        Dim I As Integer 'Added Feb '05 to go with CallMethod Changes -CLC
        
        PD = ""
        RT = Replace(Replace(TypeName(MI.ReturnType.TypedVariant), "(", "["), ")", "]")
        If RT = "Empty" Then RT = ""

        For Each PI In MI.Parameters
            If PI.Flags And PARAMFLAG_FRETVAL Then
                RT = TypeName(PI.VarTypeInfo.TypedVariant)
            Else
                N = PI.Name
                T = TypeName(PI.VarTypeInfo.TypedVariant)
                'Added Feb '05 to go with CallMethod changes -CLC
                For I = 1 To PI.VarTypeInfo.PointerLevel
                    T = T + "*"
                Next I
                If PI.Flags And PARAMFLAG_FOUT Then T = T + " (out)"
                '*****
                If PI.Flags And PARAMFLAG_FOPT Then   'This is an optional parameter
                    PL = ", [" + N + " As " + T + "]"
                ElseIf PI.Flags And PARAMFLAG_FHASDEFAULT Then  'This is a parameter with a default value
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
    
    Private Sub SetBindings(Item As ListItem)
        Dim BindingName As String
        Dim C As IComponent
        Set C = g_AL.Locate(atv.Path)
            If C Is Nothing Then
                'This if statement was added by CLC 3/03/05 to avoid a run-time
                'error when the system fails to update the tree view after a
                'component has been deleted.
                atv.Refresh
                Exit Sub
            End If
        
        BindingName = Item.Text
        Set frmBindings.NetList = atv.NetList                               'Set up the bindings form
        Call frmBindings.ShowDialog(C.Bindings.Settings.Item(BindingName))  'Show the current bindings
        If frmBindings.Cancelled Then Exit Sub                              'If the cancel button is pushed, exit w/o changes
        Call C.Bindings.Settings.Remove(BindingName)                        'Otherwise, remove the old binding information
        Call C.Bindings.Settings.Add(frmBindings.Binding)                   'Add the new information
        Item.SubItems(2) = frmBindings.Binding.Path                         'Update our listview
        Unload frmBindings                                                  'Unload the bindings form
    End Sub

    Private Sub CallMethod(Path As String, MethName As String)
        
  'This was edited to work the way we wanted it to. --Feb. '05, Christina and Juan.
  '(See also: frmParams)
        'On Error Resume Next
        
        Dim Component       As Object
        Dim ArgumentText    As String   'Type string
        Dim Args            As String   'Args from TypeString
        Dim ArgCount        As Integer  'Argument count
        Dim RetVal          As Variant
        Dim Values()        As Variant
           
        Set Component = atv.Locator.Locate(Path)  'Find the component
        ArgumentText = alv.SelectedItem.SubItems(1)  'Pull the argument text of the method from the list view
        
        If InStr(ArgumentText, "(") Then   'If there are arguments, then
            ArgCount = StrCount(ArgumentText, ",") + 1     'Count the number of arguments by finding commas
            Args = Mid(ArgumentText, InStr(ArgumentText, "(") + 1)
            Args = Left(Args, Len(Args) - 1)            'Args is a string containing all the arguments
'
            ReDim Vars(0 To ArgCount - 1) As Variant
            Dim Strs()              As String
            Dim ArgName()           As String '***
            Dim ArgType()           As String '***
            Dim I                   As Integer
            Dim Indx                As Integer '***
            Dim LI                  As ListItem
            Dim InOptOut            As Integer
            Dim OutputVar           As Integer
            Dim MethID As Integer
   
            ReDim ArgName(0 To ArgCount - 1)
            ReDim ArgType(0 To ArgCount - 1)
            
            Strs = Split(Args, ",")  'Strings is a string array containing each argument separately
            
            'This error will only happen if something really messed up.
            If ArgCount <> UBound(Strs) + 1 Then
                MsgBox ("Number of parameters does not match.")
                Exit Sub
            End If
            OutputVar = 0
            'First, load the variables into frmParams
            For I = 0 To ArgCount - 1
                InOptOut = 0
                Strs(I) = Trim(Strs(I))
                If InStr(Strs(I), "[") = 1 Then
                    InOptOut = 1
                    Strs(I) = Trim(Mid(Strs(I), 2, Len(Strs(I)) - 2))
                End If
                Indx = InStr(Strs(I), "As")
                ArgName(I) = Trim(Left(Strs(I), Indx - 1))
                ArgType(I) = Trim(Mid(Strs(I), Indx + 2))
                Indx = InStr(ArgType(I), "(out)")
                If Indx > 0 Then
                    OutputVar = 1
                    InOptOut = 2
                    ArgType(I) = Trim(Left(ArgType(I), Len(ArgType(I)) - 5))
                End If
                Call frmParams.AddItem(ArgName(I), ArgType(I), "0", InOptOut, I)
            Next I
            
            'Show frmParams, which does the rest of the work.
            Call frmParams.ShowDialog(1)
            
            Values = frmParams.ReverseValues
            MethID = TLI.InvokeID(Component, MethName)
            Call TLI.InvokeHookArray(Component, MethID, INVOKE_FUNC, Values)
            'RetVal = CallByName(Component, MethName, VbMethod, Values(0))
            
            If (OutputVar = 1) Then
                'Call frmParams.Update
                If (Not RetVal = Empty) Then
                    Dim RetValString As String
                    If VarType(RetVal) = vbObject Then
                        RetValString = "object"
                    Else
                        RetValString = Str(RetVal)
                    End If
                    Call frmParams.AddItem("Returned Value", TypeName(RetVal), RetValString, 2, ArgCount)
                End If
                Call frmParams.ShowDialog(0)
            Else
                If (Not RetVal = Empty) Then
                    If VarType(RetVal) = vbObject Then
                        MsgBox MethName & " returned an object."
                    Else
                        MsgBox MethName & " returned: " & RetVal
                    End If
                End If
            End If
            
            
            
'            For I = 0 To AC - 1
'                Set LI = frmParams.lvw.FindItem(ArgName(I), lvwSubItem)
'                Select Case ArgType(I)
'                Case "Long"
'                    Vars(I) = CVar(CLng(LI.Text))
'                Case "Double"
'                    Vars(I) = CVar(CDbl(LI.Text))
'                Case "String"
'                    Vars(I) = CVar(CStr(LI.Text))
'                Case Else
'                    Vars(I) = CVar(LI.Text)
'                End Select
'            Next I
            
'            Stop
            
'            RetVal = CallByName(O, MethName, VbMethod, Vars)
        Else
            RetVal = CallByName(Component, MethName, VbMethod)
            If (StrComp(TypeName(RetVal), "Empty") <> 0) Then
                If VarType(RetVal) = vbObject Then
                    MsgBox MethName & " returned an object."
                Else
                    On Error Resume Next
                    MsgBox MethName & " returned: " & RetVal
                    If Err Then
                        MsgBox MethName & " returned a variant of type: " & TypeName(RetVal)
                        Err.Clear
                    End If
                End If
            End If
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
        m_Icons.Directory = "C:\IMA2\Icons"
        
        'Refresh component list
        'If m_Net Is Nothing Then Set m_Net = New NetList
        
        m_Net.Refresh
        
        'Initialize AgentTreeview and AgentListView
        Set atv.NetList = m_Net
        Set alv.NetList = m_Net
        
        'Refresh network information
        atv.Path = "\\"
        atv.ExpandAll
        
        'Patch into our services.
        On Error Resume Next
        Set g_AL = GetLocator()
        'The errors with not finding the locator were driving me crazy, especially since
        'it could often find it on the second time around. So, I added this error-catching
        'code, which asks if you want to retry or close. -CLC 5/13/05
        While (Err)
            Err.Clear
            If MsgBox("Couldn't find Locaor. Keep Trying?" & vbCr & "(Select No to close the program.)", vbYesNo) = vbYes Then
                Set g_AL = GetLocator()
            Else
                End
            End If
        Wend
        Set g_LA = g_AL
        Set g_IS = CreateObject("IMA2_InfoService.InfoService")
        
        'Load Favorites
        Call LoadMRUList
    
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
        
        TP_Top = 0 'Toolbar1.Height
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
        
        Stop
        'Paths = g_AL.Components
        
        For I = LBound(Paths) To UBound(Paths)
            If IsDescendant(Paths(I), Path) Then
                Set C = g_AL.Locate(Paths(I))
                'C.Activated = Value
                If Err Then
                    atv.Nodes(Paths(I)).ForeColor = QBColor(7)
                    Err.Clear
                'ElseIf C.Activated Then
                '    atv.Nodes(Paths(I)).ForeColor = QBColor(2)
                Else
                    atv.Nodes(Paths(I)).ForeColor = QBColor(12)
                End If
            End If
        Next I
        
        'mnuCmp_Activated.Checked = C.Activated
        wbv.ForeColor = atv.SelectedItem.ForeColor

    End Sub

    Private Sub mnuCmp_ActivateBranch_Click()
    
        If Me.ActiveControl Is atv Then
            Call ActivateBranch(atv.Path, True)
        ElseIf Me.ActiveControl Is alv Then
            Call ActivateBranch(alv.Path, True)
        End If
        
        m_Net.Refresh
        'atv.ExpandAll
     
    End Sub

Private Sub mnu_Cmp_Context_Click()

End Sub

    Private Sub mnuCmp_Activated_Click()
        Dim C As IComponent
        If Me.ActiveControl Is atv Then
            
            'Call ActivateBranch(atv.Path, Not mnuCmp_Activated.Checked)

            Set C = g_AL.Locate(atv.Path)
            'C.Activated = Not mnuCmp_Activated.Checked
            'mnuCmp_Activated.Checked = C.Activated
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
    'atv.ExpandAll

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


Private Sub mnuCmp_New_Context_Click()
    mnuCmp_New_Context.Checked = Not mnuCmp_New_Context.Checked
End Sub

Private Sub mnuCmp_New_Favorites_Click(Index As Integer)
    On Error Resume Next
    
    Dim I As Integer
    Dim CF As New ComponentFile
    
    CF.FilePath = m_FavFileNames(Index + 1)
    CF.Load
    
    If Err Then
        Err.Clear
        Call MsgBox(CF.FilePath + " could not be opened." + vbCrLf + vbCrLf + "The file is either corrupt or it was saved with a different version of DAD.", vbCritical Or vbOKOnly, "Could not load agent file")
        Exit Sub
    End If
    
    Call AddToMRUList(Mid(frmInsert.FilePath, InStrRev(frmInsert.FilePath, "\") + 1), frmInsert.FilePath)
    For I = CF.DescriptionLBound To CF.DescriptionUBound
        Call LoadComponent(CF.DescriptionIndex(I), mnuCmp_New_Context.Checked)
    Next I
    
End Sub

    Private Sub mnuConnect_Click()
        If (UCase(g_AL.Machine) = "SALLY") Then
            Call g_LA.Connect("octavia")
        ElseIf (UCase(g_AL.Machine) = "octavia") Then
            Call g_LA.Connect("SALLY")      'OLD IP 129.59.73.67
        End If
    End Sub

    Private Sub mnuDisconnect_Click()
        If (UCase(g_AL.Machine) = "SALLY") Then
            Call g_LA.Disconnect("HUNGERFORCE")
        ElseIf (UCase(g_AL.Machine) = "HUNGERFORCE") Then
            Call g_LA.Disconnect("SALLY")
        End If
    End Sub

    Private Sub mnuTextSummary_Click()
        frmTextSummary.ShowModal
    End Sub

    Private Sub mnuTools_ListRefresh_Click()
        atv.Refresh
        'atv.ExpandAll
    End Sub


    Private Sub mnuView_Refresh_Click()
        Call RefreshComponent
    End Sub
    
    Private Sub mnuCmp_New_Cmp_Click()
        Call NewComponent
'        atv.Refresh        'Commented out because of errors
    End Sub
    
    Private Sub mnuCmp_SaveAs_Click()
        
        Dim Dlg As New frmSaveAs
        Dim P() As String
        
        P = GetSavedPaths()                 'Get Saved Paths
        Call Dlg.StartWizard(P, atv.Nodes)  'Start the file save wizard
    
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
        Dim I As Integer
        For I = m_FavDisplay.Count To MAX_FAVS - 1
            mnuCmp_New_Favorites.Item(I).Visible = False
            mnuCmp_New_Favorites.Item(I).Enabled = False
        Next
        
        If m_FavDisplay.Count = 0 Then
            mnuCmp_New_Favorites.Item(0).Caption = "(no favorites)"
            mnuCmp_New_Favorites.Item(0).Visible = True
            mnuCmp_New_Favorites.Item(0).Enabled = False
        Else
            For I = 0 To m_FavDisplay.Count - 1
                mnuCmp_New_Favorites.Item(I).Caption = m_FavDisplay(I + 1)
                mnuCmp_New_Favorites.Item(I).Visible = True
                mnuCmp_New_Favorites.Item(I).Enabled = True
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
        
'        mnuCmp_Connect.Visible = (PL = PL_NETWORK)
 '       mnuCmp_Disconnect.Visible = (PL = PL_LOCATOR) And ItemSelected
  '      mnuCmp_Connect_Sep.Visible = mnuCmp_Disconnect.Visible Or (mnuCmp_Connect.Visible And ItemSelected)
        
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
        
'        mnuCmp_ActivateBranch.Visible = (PL >= PL_LOCATOR) And IsContainer
 '       mnuCmp_DeactivateBranch.Visible = mnuCmp_ActivateBranch.Visible
        
'        mnuCmp_Connect.Visible = (PL = PL_NETWORK)
 '       mnuCmp_Disconnect.Visible = (PL = PL_LOCATOR)
        
        mnuCmp_New.Visible = (PL >= PL_LOCATOR) And (IsContainer Or PL = PL_LOCATOR)
        
        mnuCmp_Copy.Visible = (PL > PL_NETWORK)
        mnuCmp_Paste.Visible = mnuCmp_Copy.Visible
        
        mnuCmp_Copy.Enabled = (PL > PL_NETWORK)
        mnuCmp_Paste.Enabled = (PL > PL_NETWORK) And (InStr(Clipboard.GetText(), "{IMA2 Component}") = 1)
        
        mnuCmp_Delete.Visible = (PL > PL_LOCATOR)
        mnuCmp_SaveAs.Visible = (PL > PL_LOCATOR)
        
        mnuCmp_New_Sep.Visible = mnuCmp_New.Visible
'        mnuCmp_Connect_Sep.Visible = mnuCmp_Disconnect.Visible Or mnuCmp_Connect.Visible
        mnuCmp_Activated_Sep.Visible = mnuCmp_Activated.Visible
'        mnuCmp_Branch_Sep.Visible = mnuCmp_ActivateBranch.Visible
        mnuCmp_Delete_Sep.Visible = mnuCmp_Delete.Visible
        mnuCmp_SaveAs_Sep.Visible = mnuCmp_SaveAs.Visible
        mnuCmp_Paste_Sep.Visible = mnuCmp_Copy.Visible And (mnuCmp_Delete.Visible Or mnuCmp_SaveAs.Visible Or mnuCmp_Properties.Visible)
    
    End Sub

'*********************************************************************************************************************************************************************
' MRU Functions
'*********************************************************************************************************************************************************************
'These functions were gotten from http://www.vb-helper.com/howto_mru_list.html
'and added to DAD on 1/24/06 by Christina
' Add this file to the MRU list.
Private Sub AddToMRUList(ByVal file_title As String, ByVal file_name As String)
Dim I As Integer

    ' Add the entry at the top of the list.
    If m_FavDisplay.Count = 0 Then
        m_FavDisplay.Add file_title
        m_FavFileNames.Add file_name
    Else
        m_FavDisplay.Add file_title, , 1
        m_FavFileNames.Add file_name, , 1
    End If

    ' Remove any duplicates.
    For I = m_FavDisplay.Count To 2 Step -1
        If m_FavDisplay(I) = file_title Then
            m_FavDisplay.Remove I
            m_FavFileNames.Remove I
        End If
    Next I

    ' Remove entries beyond four.
    Do While m_FavDisplay.Count > MAX_FAVS
        m_FavDisplay.Remove MAX_FAVS + 1
        m_FavFileNames.Remove MAX_FAVS + 1
    Loop

    ' Save the MRU list.
    SaveMRUList
End Sub

' Display the MRU list.
'Private Sub ShowMRUList()
'Dim i As Integer

'    For i = 1 To m_FavDisplay.Count
'        mnuFileMRU(i).Caption = "&" & Format$(i) & " " & m_FavDisplay(i)
'        mnuFileMRU(i).Visible = True
'    Next i

    ' If any file is visible, display the MRU separator.
'    mnuFileMRUSep.Visible = mnuFileMRU(1).Visible
'End Sub

' Load the MRU list.
Private Sub LoadMRUList()
Dim I As Integer
Dim txt As String

    Set m_FavDisplay = New Collection
    Set m_FavFileNames = New Collection

    ' Get the MRU files.
    For I = 1 To MAX_FAVS
        txt = GetSetting("IMA2_DAD", "MRU", "Title" & Format$(I), "")
        If Len(txt) = 0 Then Exit For

        m_FavDisplay.Add txt
        m_FavFileNames.Add GetSetting("IMA2_DAD", "MRU", "File" & Format$(I), "")
    Next I
End Sub
' Save the MRU list.
Private Sub SaveMRUList()
Dim I As Integer

    ' Save the MRU files.
    For I = 1 To m_FavDisplay.Count
        SaveSetting "IMA2_DAD", "MRU", "Title" & Format$(I), m_FavDisplay(I)
        SaveSetting "IMA2_DAD", "MRU", "File" & Format$(I), m_FavFileNames(I)
    Next I

    ' Delete any old entries.
    On Error Resume Next
    For I = m_FavDisplay.Count + 1 To MAX_FAVS
        DeleteSetting "IMA2_DAD", "MRU", "Title" & Format$(I)
        DeleteSetting "IMA2_DAD", "MRU", "File" & Format$(I)
    Next I
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
        
        Paths = g_IS.Components
        LB = LBound(Paths)
        UB = UBound(Paths)
        
        PC = atv.Path
        
        For I = LB To UB
            If Not IsDescendant(Paths(I), PC) Then Paths(I) = ""
        Next

        Call RemoveBlankStrings(Paths)
        
        GetSavedPaths = Paths
    
    End Function

