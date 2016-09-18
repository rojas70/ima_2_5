VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.UserControl StateMachineMgr 
   ClientHeight    =   3975
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   2775
   ScaleHeight     =   265
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   185
   Begin MSComDlg.CommonDialog dlgSave 
      Left            =   4080
      Top             =   2400
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      DefaultExt      =   "*.smf"
      DialogTitle     =   "Save state machine file"
      Filter          =   "State machine files (*.smf)|*.smf|All Files|*.*"
      Flags           =   2097156
   End
   Begin MSComDlg.CommonDialog dlgOpen 
      Left            =   4080
      Top             =   1800
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      DefaultExt      =   "*.smf"
      DialogTitle     =   "Open state machine file"
      Filter          =   "State machine files (*.smf)|*.smf|All Files|*.*"
      Flags           =   2099204
   End
   Begin MSComctlLib.ImageList iml 
      Left            =   4440
      Top             =   720
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      UseMaskColor    =   0   'False
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   5
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "StateMachine.ctx":0000
            Key             =   "Action"
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "StateMachine.ctx":015A
            Key             =   "Task"
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "StateMachine.ctx":02B4
            Key             =   "Transition"
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "StateMachine.ctx":040E
            Key             =   "State"
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "StateMachine.ctx":0568
            Key             =   "Machine"
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.TreeView tvw 
      Height          =   5175
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   3495
      _ExtentX        =   6165
      _ExtentY        =   9128
      _Version        =   393217
      Indentation     =   661
      Style           =   7
      Appearance      =   1
   End
   Begin VB.Menu mnuMachine 
      Caption         =   "Machine"
      Begin VB.Menu mnuNewState 
         Caption         =   "New State"
         Shortcut        =   ^N
      End
      Begin VB.Menu mnuMachineSep0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuSaveChanges 
         Caption         =   "Save Changes"
         Shortcut        =   ^S
      End
      Begin VB.Menu mnuUndoChanges 
         Caption         =   "Undo Changes"
         Enabled         =   0   'False
         Shortcut        =   ^Z
      End
      Begin VB.Menu mnuMachineSep2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFile 
         Caption         =   "&Export/Import"
         Begin VB.Menu mnuOpen 
            Caption         =   "&Open..."
            Shortcut        =   ^O
         End
         Begin VB.Menu mnuSaveAs 
            Caption         =   "&Save As..."
         End
      End
      Begin VB.Menu mnuMachineSep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuGo 
         Caption         =   "Go"
      End
      Begin VB.Menu mnuMachineProperties 
         Caption         =   "Properties..."
         Begin VB.Menu mnuMachineAutoLoop 
            Caption         =   "AutoLoop"
         End
         Begin VB.Menu mnuMachineInterval 
            Caption         =   "Interval..."
         End
      End
   End
   Begin VB.Menu mnuState 
      Caption         =   "State"
      Begin VB.Menu mnuNewTask 
         Caption         =   "New Task"
         Shortcut        =   ^T
      End
      Begin VB.Menu mnuNewTransition 
         Caption         =   "New Transition"
         Shortcut        =   ^R
      End
      Begin VB.Menu mnuStateSep0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuRemoveState 
         Caption         =   "Remove State"
      End
      Begin VB.Menu mnuStateSep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuStateProperties 
         Caption         =   "Properties..."
         Begin VB.Menu mnuStateAutoLoop 
            Caption         =   "AutoLoop"
         End
      End
   End
   Begin VB.Menu mnuTask 
      Caption         =   "Task"
      Begin VB.Menu mnuNewAction 
         Caption         =   "New Action"
         Shortcut        =   ^A
      End
      Begin VB.Menu mnuRemoveTask 
         Caption         =   "Remove Task"
      End
      Begin VB.Menu mnuActionSep0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuTaskProperties 
         Caption         =   "Properties..."
      End
   End
End
Attribute VB_Name = "StateMachineMgr"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit
    
    Implements IManager
    
    Type IndexType
        S As Integer
        T As Integer
        R As Integer
        A As Integer
    End Type
    
'************************************************************************************************
' Private Member Variables
'************************************************************************************************
    
    Dim m_SM            As New StateMachine
    Dim m_RootNode      As Node

'************************************************************************************************
    
    Private Property Let IManager_Component(ByVal RHS As IMA2.IComponent)
        Dim SM As StateMachine
        
        Set SM = m_SM
        
        'Attempt to extablish new state machine
        Set m_SM = RHS
        Call GenerateTree(tvw, m_SM)
        
        'If error, revert to old one
        If Err Then
            Set m_SM = SM
            Call GenerateTree(tvw, m_SM)
            MsgBox "Noooo"
            Err.Clear
        End If
        
    End Property
    
    Private Property Get IManager_Component() As IMA2.IComponent
        Set IManager_Component = m_SM
    End Property
    
    Private Sub IManager_Update(pFlags As Variant)
        
    End Sub
    
'************************************************************************************************
' Menu Functions
'************************************************************************************************

    Private Sub mnuNewState_Click()
        
        'Add the state to the state machine.
        Dim S As New State
        S.Name = "New State"
        Call m_SM.States.Add(S)
        
        'Add the state to the tree.
        Dim N As Node
        Set N = tvw.Nodes.Add(tvw.SelectedItem, tvwChild, "K" & S.Index, "" & S.Index & " - " & S.Name, "State")
        
        'Setup node properties
        Call SetupNodeProps(N)
        
'        Set N = tvw.Nodes.Add(N, tvwChild, , "Transitions", "Transition")
'        N.ForeColor = QBColor(8)
        
    End Sub

    '************************************************************************************************

    Private Sub mnuNewTask_Click()

        'Add the task to the state machine.
        Dim S As State
        Dim T As New Task
        Dim K As String
        
        T.Name = "New Task"
        Set S = GetCurrentObject()
        Call S.Tasks.Add(T)
        K = tvw.SelectedItem.Key & "." & T.Index
        
        'Add the state to the tree.
        Dim N As Node
        Dim FT As Node
        Set FT = FirstTransition(tvw.SelectedItem)
        
        If FT Is Nothing Then
            Set N = tvw.Nodes.Add(tvw.SelectedItem, tvwChild, K, Mid(K, 2) & " - " & T.Name, "Task")
        Else
            Set N = tvw.Nodes.Add(FT, tvwPrevious, K, Mid(K, 2) & " - " & T.Name, "Task")
        End If
        
        'Setup node properties
        Call SetupNodeProps(N)
        
    End Sub

    '************************************************************************************************

    Private Sub mnuNewAction_Click()
        
        'Add the task to the state machine.
        Dim T   As Task
        Dim A   As New Action
        Dim K   As String
        
        A.ComponentName = "Component"
        A.FunctionName = "Function"
        Set T = GetCurrentObject()
        Call T.Actions.Add(A)
        K = tvw.SelectedItem.Key & "." & A.Index
        
        'Add the state to the tree.
        Dim N As Node
        
        Set N = tvw.Nodes.Add(tvw.SelectedItem, tvwChild, K, Mid(K, 2) & " - " & A.Name, "Action")
        
        'Setup node properties
        Call SetupNodeProps(N)
        
    End Sub

    '************************************************************************************************

    Private Sub mnuNewTransition_Click()
        
        'Add the task to the state machine.
        Dim S As State
        Dim R As New Transition
        Dim K As String
        
        Set S = m_SM.States.Item(Val(Token(tvw.SelectedItem.Text, " - ", 1)))
        R.Name = "New Transition"
        Call S.Transitions.Add(R)
        K = tvw.SelectedItem.Key & ".R" & R.Index
        
        'Add the state to the tree.
        Dim N As Node
        Set N = tvw.Nodes.Add(tvw.SelectedItem, tvwChild, K, R.Name, "Transition")
        Call SetupNodeProps(N)
        
    End Sub

    '************************************************************************************************
    
    Private Sub mnuMachineAutoLoop_Click()
        m_SM.AutoLoop = Not mnuMachineAutoLoop.Checked
        mnuMachineAutoLoop.Checked = Not mnuMachineAutoLoop.Checked
    End Sub

    '************************************************************************************************
    
    Private Sub mnuStateAutoLoop_Click()
        Dim S As State
        Set S = GetCurrentObject()
        S.AutoLoop = Not mnuStateAutoLoop.Checked
        mnuStateAutoLoop.Checked = Not mnuStateAutoLoop.Checked
    End Sub

    '************************************************************************************************
    
    Private Sub mnuGo_Click()
        Dim C As IComponent
        
        Set C = m_SM
        
        If mnuGo.Caption = "Go" Then
            mnuGo.Caption = "Stop"
            C.Activated = True
        Else
            mnuGo.Caption = "Go"
            C.Activated = False
        End If
        
    End Sub

'************************************************************************************************
' File I/O
'************************************************************************************************
    
    Private Sub mnuOpen_Click()
        
        Dim PB As PropertyBag
        
        dlgOpen.ShowOpen
        If dlgOpen.FileName = "" Then Exit Sub
        
        Set PB = LoadPB(dlgOpen.FileName)
        
        Dim SM As StateMachine
        Set SM = PB.ReadProperty("StateMachine")
        
        Set m_SM = SM
        
        Call GenerateTree(tvw, m_SM)

    End Sub

    '************************************************************************************************
    
    Private Sub mnuSaveAs_Click()
        
        Dim PB As New PropertyBag
        
        dlgSave.ShowSave
        If dlgSave.FileName = "" Then Exit Sub
        
        Call PB.WriteProperty("StateMachine", m_SM)
        Call SavePB(dlgSave.FileName, PB)
        
    End Sub

    '************************************************************************************************

    Private Sub mnuSaveChanges_Click()
        CopyToClipboard
    End Sub

'************************************************************************************************
' Treeview Functions
'************************************************************************************************

    Private Sub tvw_AfterLabelEdit(Cancel As Integer, NewString As String)
        If InStr(NewString, " - ") = 0 Then
            Dim CO As Object
            
            Set CO = GetCurrentObject()
            
            If tvw.SelectedItem.Image = "Action" Then
                CO.ComponentName = Left(NewString, InStr(NewString, ".") - 1)
                CO.FunctionName = Mid(NewString, InStr(NewString, ".") + 1)
            Else
                CO.Name = NewString
            End If
            
            
            NewString = Mid(tvw.SelectedItem.Key, 2) + " - " + NewString
        Else
            
                
            
        End If
    End Sub

    '************************************************************************************************
    
    Private Sub tvw_BeforeLabelEdit(Cancel As Integer)
        If tvw.SelectedItem.Index = 1 Then Cancel = True
    End Sub

    '************************************************************************************************
    
    Private Sub tvw_KeyDown(KeyCode As Integer, Shift As Integer)
        If KeyCode = vbKeyF2 Then tvw.StartLabelEdit
    End Sub

    '************************************************************************************************

    Private Sub tvw_KeyUp(KeyCode As Integer, Shift As Integer)
        
        Dim IT As IndexType
        Dim K As String
        
        If KeyCode = vbKeyDelete Then
            
            IT = CurrentPos()
            Select Case tvw.SelectedItem.Image
                Case "Machine":     Exit Sub
                Case "State":       m_SM.States.Remove IT.S
                Case "Task":        m_SM.States.Item(IT.S).Tasks.Remove IT.T
                Case "Transition":  m_SM.States.Item(IT.S).Transitions.Remove IT.R
                Case "Action":      m_SM.States.Item(IT.S).Tasks.Item(IT.T).Actions.Remove IT.A
            End Select
            
            K = tvw.SelectedItem.Parent.Key
            Call GenerateTree(tvw, m_SM)
            If K = "" Then
                tvw.Nodes(1).Expanded = True
            Else
                tvw.Nodes(K).Expanded = True
                tvw.Nodes(K).EnsureVisible
            End If
        End If
        
    End Sub

    '************************************************************************************************
    
    Private Sub tvw_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
    
        If Button And vbRightButton Then
            
            Dim Tag As String
            
            Tag = tvw.SelectedItem.Image
            
            If Tag = "Machine" Then
                PopupMenu mnuMachine
            ElseIf Tag = "State" Then
                PopupMenu mnuState
            ElseIf Tag = "Task" Then
                PopupMenu mnuTask
            End If
        
        End If
    
    End Sub

'************************************************************************************************
' Usercontrol Functions
'************************************************************************************************

    Private Sub UserControl_Initialize()
        
        Set tvw.ImageList = iml
        Set m_RootNode = tvw.Nodes.Add(, , , "My State Machine", "Machine")
        m_SM.Name = "My State Machine"
    
    End Sub
    
    Private Sub UserControl_Resize()
        tvw.Move 0, 0, UserControl.ScaleWidth, UserControl.ScaleHeight
    End Sub
    
'************************************************************************************************
' Miscellaneous functions
'************************************************************************************************
    Private Sub CopyToClipboard()
    
        Dim N   As Node
        Dim S   As String
    
        S = ""
        For Each N In tvw.Nodes
            S = S + N.FullPath + "@" + N.Text + "@" + N.Image + vbCrLf
        Next
        
        Call Clipboard.Clear
        Call Clipboard.SetText(S)
        
        'Dim N As Node
        
        For Each N In tvw.Nodes
            N.ForeColor = QBColor(0)
        Next
        

    End Sub

    Private Sub CopyFromClipboard()
    
        Dim N   As Node
        Dim S() As String
        Dim D() As String
        Dim I   As Integer
        
        S = Split(Clipboard.GetText, vbCrLf)
        Call QuickSortStrings(S)
        
        D = Split(S(1), "@")
        tvw.Nodes.Add(, tvwChild, D(1), D(1), D(2)).Tag = D(2)
        
        For I = 2 To UBound(S)
            D = Split(S(I), "@")
            tvw.Nodes.Add NameFromPath(ParentFromPath(D(0))), tvwChild, D(1), D(1), D(2)
        Next
        
        Call Clipboard.Clear

    End Sub

    Private Function FirstTransition(PN As Node) As Node
    
        Dim N As Node
        Dim Count As Integer
        
        Set N = PN.Child
        Do Until (N Is Nothing)
            If N.Image = "Transition" Then Exit Do
            Set N = N.Next
        Loop
        
        Set FirstTransition = N
        
    End Function

    Public Function Token(Src As String, Delim As String, Index As Integer)
    
        Dim S() As String
        S = Split(Src, Delim)
        Token = S(Index - 1)
    
    End Function


    Private Sub SetupNodeProps(N As Node)
        'Setup the properties
        N.ForeColor = QBColor(8)
        N.Expanded = True
        N.EnsureVisible
    End Sub


    Private Function GetCurrentObject() As Object
    
        Dim SI  As Integer
        Dim TI  As Integer
        Dim AI  As Integer
        Dim SC  As Integer
        Dim K   As String
        
        K = Mid(tvw.SelectedItem.Key, 2)
        SC = StrCount(K, ".")
        
        If SC = 0 Then
            SI = Val(Token(K, ".", 1))
            Set GetCurrentObject = m_SM.States.Item(SI)
        ElseIf SC = 1 And StrCount(K, "R") = 0 Then
            SI = Val(Token(K, ".", 1))
            TI = Val(Token(K, ".", 2))
            Set GetCurrentObject = m_SM.States.Item(SI).Tasks.Item(TI)
        ElseIf SC = 1 Then
            SI = Val(Token(K, ".", 1))
            TI = Val(Token(K, ".", 2))
            Set GetCurrentObject = m_SM.States.Item(SI).Transitions.Item(TI)
        ElseIf SC = 2 Then
            SI = Val(Token(K, ".", 1))
            TI = Val(Token(K, ".", 2))
            AI = Val(Token(K, ".", 3))
            Set GetCurrentObject = m_SM.States.Item(SI).Tasks.Item(TI).Actions.Item(AI)
        Else
            Stop
        End If
    
    End Function
    
    Private Sub GenerateTree(tvw As TreeView, SM As StateMachine)

        Dim S   As State
        Dim T   As Task
        Dim R   As Transition
        Dim A   As Action
        Dim SN  As Node
        Dim TN  As Node
        Dim KS  As String
        
        Dim SC As Collection
        Dim TC As Collection
        Dim RC As Collection
        Dim AC As Collection
        
        tvw.Nodes.Clear
        
        Set m_RootNode = tvw.Nodes.Add(, , "Machine", SM.Name, "Machine")
        
        Set SC = SM.States.Collection
        For Each S In SC
            KS = "" & S.Index
            Set SN = tvw.Nodes.Add(m_RootNode, tvwChild, "K" & S.Index, KS + " - " + S.Name, "State")
            
            Set TC = S.Tasks.Collection
            For Each T In TC
                KS = "" & S.Index & "." & T.Index
                Set TN = tvw.Nodes.Add(SN, tvwChild, "K" + KS, KS + " - " + T.Name, "Task")
                
                Set AC = T.Actions.Collection
                For Each A In AC
                    KS = "" & S.Index & "." & T.Index & "." & A.Index
                    Call tvw.Nodes.Add(TN, tvwChild, "K" + KS, KS + " - " + A.Name, "Action")
                Next
            Next
            
            Set RC = S.Transitions.Collection
            For Each R In RC
                KS = "" & S.Index & ".R" & R.Index
                Call tvw.Nodes.Add(SN, tvwChild, "K" + KS, R.Name, "Transition")
            Next
        Next

    End Sub


    Private Function CurrentPos() As IndexType
    
        Dim S As Integer, T As Integer, R As Integer, A As Integer
        
        Dim K As String
        Dim I As String
        Dim E() As String
        Dim IT As IndexType
        
        S = -1:        T = -1:        R = -1:        A = -1
        
        K = Mid(tvw.SelectedItem.Key, 2)
        
        If K = "" Then
            CurrentPos = IT
            Exit Function
        End If
        
        E = Split(K, ".")
        
        S = Val(E(0))
        
        If UBound(E) >= 1 Then
            If InStr(E(1), "R") > 0 Then
                R = Val(Mid(E(1), 2))
            Else
                T = Val(E(1))
            End If
        End If
        
        If UBound(E) = 2 Then A = Val(E(2))

        IT.A = A:        IT.R = R:        IT.S = S:        IT.T = T
        
        CurrentPos = IT
    
    End Function

