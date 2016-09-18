VERSION 5.00
Object = "{7B492EBB-3B8A-4D7E-9021-86BB71534052}#1.1#0"; "IMA2_HelperX.ocx"
Begin VB.UserControl ManagerTabs 
   Alignable       =   -1  'True
   ClientHeight    =   13005
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   8685
   ScaleHeight     =   867
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   579
   Begin VB.Timer tmr 
      Enabled         =   0   'False
      Interval        =   100
      Left            =   720
      Top             =   12480
   End
   Begin VB.Timer tmrDragDrop 
      Interval        =   10
      Left            =   120
      Top             =   12480
   End
   Begin VB.PictureBox pic 
      AutoSize        =   -1  'True
      BackColor       =   &H8000000C&
      Height          =   11775
      Left            =   240
      OLEDropMode     =   1  'Manual
      ScaleHeight     =   781
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   549
      TabIndex        =   0
      Top             =   480
      Width           =   8295
      Begin IMA2_HelperX.SimpleWindow swn 
         Height          =   3000
         Index           =   0
         Left            =   720
         TabIndex        =   1
         Top             =   840
         Width           =   1935
         _ExtentX        =   3413
         _ExtentY        =   5292
         Icon            =   "ManagerTabs.ctx":0000
         MinVisible      =   0   'False
      End
   End
   Begin IMA2_HelperX.EditTab etb 
      Height          =   12255
      Left            =   120
      TabIndex        =   2
      Top             =   120
      Width           =   8535
      _ExtentX        =   15055
      _ExtentY        =   21616
   End
End
Attribute VB_Name = "ManagerTabs"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

    Dim m_Pages     As New MgrPageCollection
    Dim m_DropText  As String
    Dim m_AL        As ILocator

    'Dim m_Pgs       As New IndexedArray
    Dim m_CurWindow As Integer
'*********************************************************************************************************************
' Public Properties
'*********************************************************************************************************************
    
    
    '------------------------------------------------------------------------------------------
    Public Property Get CurrentPage() As MgrPage
        Set CurrentPage = m_Pages.Item(etb.SelectedItem.Caption)
    End Property
    
    '------------------------------------------------------------------------------------------
    Public Property Get CurrentManager() As MgrInfo
        If m_CurWindow > -1 Then
            Dim Cap As String
            Dim CP As MgrPage
            Cap = swn(m_CurWindow).Caption
            Set CP = CurrentPage
            Set CurrentManager = CP.Managers.Item(Cap)
        End If
    End Property
    
    '------------------------------------------------------------------------------------------
    Public Property Get Running() As Boolean
        Running = tmr.Enabled
    End Property

    '------------------------------------------------------------------------------------------
    Public Property Let Running(NV As Boolean)
        tmr.Enabled = NV
    End Property

    '------------------------------------------------------------------------------------------
    
    Public Sub SaveToFile(Path As String)
    
        Dim B() As Byte
        Dim PB As New PropertyBag
        
        Call m_Pages.WritePB("Managers", PB)
        If Not (etb.SelectedItem Is Nothing) Then
            Call PB.WriteProperty("SelectedPage", etb.SelectedItem.Key)
        Else
            Call PB.WriteProperty("SelectedPage", "Nothing")
        End If
        
        Call SavePB(Path, PB)
        
    End Sub

    '------------------------------------------------------------------------------------------
    
    Public Sub LoadFromFile(Path As String)
    
        Dim PB      As New PropertyBag
        Dim page    As MgrPage
        Dim MI      As MgrInfo
        Dim T       As MSComctlLib.ITab
        Dim SelKey  As String
        
        Running = False
        m_Pages.RemoveAll
        etb.Tabs.Clear
        
        Set PB = LoadPB(Path)
        Call m_Pages.ReadPB("Managers", PB)
        
        Call etb.Tabs.Clear
        
        For Each page In m_Pages
            Set page.TabControl = etb.Tabs.Add(, page.Caption, page.Caption)
            Set etb.SelectedItem = page.TabControl
            For Each MI In page.Managers
                Call CreateManager(MI)
                Call swn_OnResize(MI.Window.Index)
            Next
        Next
        
        SelKey = PB.ReadProperty("SelectedPage")
        If StrComp(SelKey, "Nothing") <> 0 Then
            Set etb.SelectedItem = etb.Tabs(SelKey)
        Else
            Set etb.SelectedItem = etb.Tabs(1)
        End If
                
    End Sub

'*********************************************************************************************************************
' Private Functions
'*********************************************************************************************************************

    '------------------------------------------------------------------------------------------
    'Given the path of a component, retrieves necessary information to create a manager
    '------------------------------------------------------------------------------------------
    Private Function GetManagerInfo(Path As String) As MgrInfo
    
        Dim M       As New MgrInfo
        Dim Cmp     As IComponent
        Dim CPID    As String
        Dim MPID    As String
        Dim MPIDs   As String
            
        Set Cmp = m_AL.Locate(Path)
        
        CPID = Cmp.Distributing.PID
        MPIDs = LoadManagerMappings(CPID)
        
        If MPIDs = "" Or StrCount(MPIDs, ",") > 0 Then
            If frmMappings.ShowMappings(CPID, MPIDs) = vbCancel Then Exit Function
            MPID = frmMappings.MPID
        Else
            MPID = MPIDs
        End If
        
        Call SaveManagerMappings(CPID, MPID)
        
        M.Path = Path
        M.MgrPID = MPID
        M.CmpPID = CPID
    
        Set GetManagerInfo = M
    
    End Function

    '------------------------------------------------------------------------------------------
    'Requires a blank MgrInfo object with CmpPID, MgrPID, and Path set.
    '------------------------------------------------------------------------------------------
    Private Sub CreateManager(NewMgr As MgrInfo)
    
        On Error Resume Next
        
        Dim Cmp     As IComponent
        Dim Msg     As String
        Dim Title   As String
            
        With NewMgr
            
            If .Caption = "" Then
                .Caption = .Path
                .Interval = 1000
                .Priority = 0
            End If
            
            Set Cmp = m_AL.Locate(.Path)
            Set .Window = GetNewSimpleWindow()
            Set .MgrControl = .Window.CreateControl(.MgrPID, "Manager")
            
            If Err Then
                Msg = "An error was encountered creating the " + .MgrPID + " ActiveX control:" + vbCrLf + OldErrorInfo() + vbCrLf + vbCrLf + "1) Try recompiling the IMA2 Manager project." + vbCrLf + "2) Make sure IManager is properly implemented." + vbCrLf + "3) If you are debugging a Manager use the MgrBook DLL, not the EXE."
                Title = "Could not create IMA2 Manager"
                Call MsgBox(Msg, vbOKOnly Or vbCritical, Title)
                Exit Sub
            End If
            
            Set .Manager = .MgrControl.object                           '// POUF! MAGIC!! //
            .Manager.Component = Cmp                                    '// Ha! Even worse! //
        End With
        
        Call ConfigureManagerWindow(NewMgr)
        
    End Sub
    
    '------------------------------------------------------------------------------------------
    'Requires a blank MgrInfo object with CmpPID, MgrPID, and Path set.
    '------------------------------------------------------------------------------------------
    Public Sub AddManager(NewMgr As MgrInfo)
        Dim page As MgrPage
        Set page = m_Pages.Item(etb.SelectedItem.Caption)
        Call CreateManager(NewMgr)
        If NN(NewMgr.Manager) Then Call page.Managers.Add(NewMgr)
    End Sub
    
    '------------------------------------------------------------------------------------------
    'Configures a manager's window
    '------------------------------------------------------------------------------------------
    Private Sub ConfigureManagerWindow(M As MgrInfo)
        
        With M.Window
            .ToolTipText = M.Path
            .Caption = M.Caption
            .MinVisible = True
            
            M.MgrControl.Left = 5 * Screen.TwipsPerPixelX
            M.MgrControl.Top = 26 * Screen.TwipsPerPixelY
            
            If M.WindowWidth = 0 Then
                .Width = (M.MgrControl.Width / Screen.TwipsPerPixelX) + 10
                .Height = (M.MgrControl.Height / Screen.TwipsPerPixelY) + 41
                '.Height = M.WindowHeight
            Else
  '              M.MgrControl.Left = 5
   '             M.MgrControl.Top = 27
                .Left = M.WindowLeft
                .Top = M.WindowTop
                .Width = M.WindowWidth '* Screen.TwipsPerPixelX
                .Height = M.WindowHeight '* Screen.TwipsPerPixelY
                'M.MgrControl.Left = (.Width * Screen.TwipsPerPixelX) + 105 * Screen.TwipsPerPixelX
                'M.MgrControl.Top = 26 * Screen.TwipsPerPixelY
                '.ControlObject.width =
            End If
        
            M.MgrControl.Visible = True
            .Visible = True
        End With
 
    End Sub
    
    '*********************************************************************************************************************
    
    Private Function GetNewSimpleWindow() As IMA2_HelperX.SimpleWindow
        Static SWI As Integer
        SWI = SWI + 1
        Load swn(SWI)
        Set GetNewSimpleWindow = swn(SWI)
    End Function

    Public Sub RemoveManager(P As String, C As String)
        
        Dim Ms As MgrInfoCollection
        Dim M As MgrInfo
        
        Set Ms = m_Pages.Item(P).Managers
        Set M = Ms.Item(C)
        
        On Error Resume Next
        Ms.Remove M.Caption
        Err.Clear

    End Sub

 

    Private Sub swn_GotFocus(Index As Integer)
        m_CurWindow = Index
    End Sub

'*********************************************************************************************************************
' SImpleWindow Events
'*********************************************************************************************************************
   Private Sub swn_KeyUp(Index As Integer, KeyCode As Integer, Shift As Integer)
        
       ' If KeyCode = vbKeyDelete Then Call RemoveManager(Index)
            
    End Sub

    Private Sub swn_OnMinimize(Index As Integer)
        PopupMenu frmFile.mnuManagers
    End Sub

    Private Sub swn_OnResize(Index As Integer)
    
        Dim M As MgrInfo
        Set M = CurrentPage.Managers.Item(swn(Index).Caption)
        
        With M.MgrControl
            .Width = (swn(Index).Width - 10) * Screen.TwipsPerPixelX
            .Height = (swn(Index).Height - 32) * Screen.TwipsPerPixelY
        End With
    
    End Sub

'*********************************************************************************************************************
' Timer functions
'*********************************************************************************************************************
    
    Private Sub tmrDragDrop_Timer()
    
        tmrDragDrop.Enabled = False
        If m_DropText <> "" Then
            Call AddManager(GetManagerInfo(m_DropText))
        End If
    
    End Sub

'*********************************************************************************************************************
' Tab Strip Functions
'*********************************************************************************************************************
        
   Private Sub etb_OnSwitch(NewTab As MSComctlLib.Tab)
        Dim T As MSComctlLib.Tab
        Dim MI As MgrInfo
        Dim MP As MgrPage
        
        Set T = etb.SelectedItem
        
        Set MP = m_Pages.Item(T.Caption)
        For Each MI In MP.Managers
            MI.Window.Hide
        Next
            
        Set MP = m_Pages.Item(NewTab.Caption)
        For Each MI In MP.Managers
            MI.Window.Show
        Next
    End Sub
    
    Private Sub etb_OnRename(T As MSComctlLib.Tab, NewName As String, Cancel As Boolean)
    
        Dim M As MgrPage
        
        Set M = m_Pages.Item(T.Caption)
        M.Caption = NewName
        
        m_Pages.Remove (T.Caption)
        Call m_Pages.Add(M)
    
    End Sub

    Private Sub etb_OnNew(T As MSComctlLib.Tab, Cancel As Boolean)
    
        Dim M As New MgrPage
        
        M.Caption = T.Caption
        Set M.TabControl = T
        
        Call m_Pages.Add(M)

    
    End Sub

    Private Sub etb_OnDelete(T As MSComctlLib.ITab, Cancel As Boolean)
        Running = False
        Call m_Pages.Remove(T.Caption)
    End Sub

'*********************************************************************************************************************
' Form Functions
'*********************************************************************************************************************

    Private Sub UserControl_Initialize()

        etb.Tabs.Clear
        
        Dim M As New MgrPage
        
        With M
            Set .TabControl = etb.Tabs.Add(, "Page 1", "Page 1")
            .Caption = "Page 1"
            .Description = "No description provided"
        End With
    
        m_Pages.Add M
    
        swn(0).Visible = False
        Set m_AL = GetLocator()
        
    End Sub
    
    '*********************************************************************************************************************
    
    Private Sub UserControl_Resize()
    
        etb.Move etb.Left, etb.Top, UserControl.ScaleWidth - (etb.Left * 2), UserControl.ScaleHeight - (etb.Top * 2)
        pic.Move etb.Left * 2, etb.Top * 5, UserControl.ScaleWidth - etb.Left * 4, UserControl.ScaleHeight - etb.Top * 7
        
    End Sub

'*********************************************************************************************************************
' Picturebox Functions
'*********************************************************************************************************************
    
    Private Sub pic_Click()
    
    End Sub
        
    '*********************************************************************************************************************
    
    Private Sub pic_OLEDragDrop(Data As DataObject, Effect As Long, Button As Integer, Shift As Integer, X As Single, Y As Single)
    
        If Data.GetFormat(vbCFText) = True Then
            m_DropText = Data.GetData(vbCFText)
            tmrDragDrop.Enabled = True
        Else
            m_DropText = ""
        End If
    
    End Sub

'*********************************************************************************************************************
' Timer Functions
'*********************************************************************************************************************

    Private Sub tmr_Timer()
    
        On Error Resume Next
        
        Dim page    As MgrPage
        Dim Mgr     As MgrInfo
        
        Set page = m_Pages.Item(etb.SelectedItem.Caption)
        
        For Each Mgr In page.Managers
            
            Call Mgr.Manager.Update
            
            If Err Then
                'Stop
                Err.Clear
            End If
            DoEvents
            Err.Clear
        Next
    
    End Sub

    
