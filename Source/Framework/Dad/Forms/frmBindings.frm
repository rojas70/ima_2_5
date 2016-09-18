VERSION 5.00
Object = "{7B492EBB-3B8A-4D7E-9021-86BB71534052}#1.1#0"; "IMA2_HelperX.ocx"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{81605258-1A3B-47EE-A9BE-4F1963575A0F}#1.1#0"; "IMA2_DadX.ocx"
Begin VB.Form frmBindings 
   Caption         =   "Bindings Wizard"
   ClientHeight    =   5055
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7215
   ControlBox      =   0   'False
   Icon            =   "frmBindings.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   337
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   481
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton RemoveBind 
      Caption         =   "Remove Binding"
      Height          =   375
      Left            =   240
      TabIndex        =   5
      Top             =   4560
      Visible         =   0   'False
      Width           =   1335
   End
   Begin IMA2_HelperX.SplitterLR slr 
      Height          =   2895
      Left            =   3345
      TabIndex        =   4
      Top             =   1320
      Visible         =   0   'False
      Width           =   30
      _ExtentX        =   53
      _ExtentY        =   5106
   End
   Begin MSComctlLib.ListView lvw 
      Height          =   2895
      Left            =   3360
      TabIndex        =   3
      Top             =   1320
      Visible         =   0   'False
      Width           =   3855
      _ExtentX        =   6800
      _ExtentY        =   5106
      View            =   3
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      _Version        =   393217
      ForeColor       =   -2147483630
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   1
      BeginProperty ColumnHeader(1) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         Text            =   "Component Path"
         Object.Width           =   15875
      EndProperty
   End
   Begin IMA2_HelperX.OKCancelBar ocb 
      Align           =   2  'Align Bottom
      Height          =   690
      Left            =   0
      TabIndex        =   2
      Top             =   4365
      Width           =   7215
      _ExtentX        =   12726
      _ExtentY        =   1217
   End
   Begin IMA2_HelperX.WizardBar wb 
      Align           =   1  'Align Top
      Height          =   1245
      Left            =   0
      TabIndex        =   1
      Top             =   0
      Width           =   7215
      _ExtentX        =   12726
      _ExtentY        =   2196
      C               =   "Select A Component To Bind To:"
      Picture         =   "frmBindings.frx":0442
   End
   Begin IMA2_DADX.AgentTreeview atv 
      Height          =   2535
      Left            =   120
      TabIndex        =   0
      Top             =   1440
      Width           =   3180
      _ExtentX        =   5609
      _ExtentY        =   4471
   End
   Begin VB.Image imSel 
      Height          =   240
      Left            =   1440
      Picture         =   "frmBindings.frx":0894
      Top             =   4800
      Visible         =   0   'False
      Width           =   240
   End
End
Attribute VB_Name = "frmBindings"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

'**********************************************************************************************************************************
' Member Variables
'**********************************************************************************************************************************
    
    Dim m_Icons     As New IconManager
    Dim m_Path      As String
    Dim m_Binding   As IMA2_BindingInfo
    Dim m_Multiple  As Boolean
    Dim m_Cancelled As Boolean
    
    Dim m_MouseX    As Single
    Dim m_MouseY    As Single
    Dim m_Dragging  As Boolean
    
    Dim m_atvWidth  As Single
    Dim m_RBRelativeTop As Single
    
'**********************************************************************************************************************************
' Public Interface
'**********************************************************************************************************************************
    
    Public Sub ShowDialog(Binding As IMA2_BindingInfo)

        Dim LI As ListItem
        Dim I As Integer
        Dim IsRestricted As Boolean
        Dim C As IComponent
        Dim O As Object
        Dim IInfo As InterfaceInfo
        Dim TL As TypeLibInfo
        Dim Interf  As Interfaces
        Dim Paths() As String
       
        m_Binding = Binding
        m_Multiple = m_Binding.BindType And BT_Collection
        
        lvw.ListItems.Clear
        lvw.Visible = m_Multiple
        slr.Visible = m_Multiple
        
        'Added 3/21/05 to restrict the available binding options if the creator of the
        'component has specified that the component should bind only to certain kinds
        'of components (as specified by the PIDs and IIDs variable of IMA2_BindingInfo)
        'If the component matches any PID or IID, then it will be allowed.
        'This restriction occurs by removing incompatable components from the tree view.
        '-CLC
        IsRestricted = False
        If (Not ArrayEmpty(m_Binding.IIDs) And m_Binding.IIDs(0) <> "") Then
            Dim DI As IMA2_DistributingInfo
            Dim NodePaths() As String
            Dim Interfaces() As String
            Dim RemoveNode As Boolean
            Dim J As Integer
            Dim K As Integer
            IsRestricted = True
            NodePaths = atv.NetList.Items()
            For I = 0 To UBound(NodePaths)
                'get the distributing info of the node
                DI = g_IS.Item(NodePaths(I))
                RemoveNode = True
                'Ignore the root, locator, and all agents (only components are removed from the tree view)
                If Not (DI.PID = "" Or DI.PID = "IMA2_Locator.Locator" Or DI.PID = "IMA2_Agent.Agent") Then
                    Set C = g_AL.Locate(NodePaths(I))
                    Set IInfo = TLI.InterfaceInfoFromObject(C)
                    Set TL = IInfo.Parent
                    Paths = Split(DI.PID, ".")
                    Set Interf = TL.CoClasses.NamedItem(Paths(1)).Interfaces
                    For J = 0 To UBound(m_Binding.IIDs)
                        For K = 1 To Interf.Count
                            If StrComp(Interf(K).Name, m_Binding.IIDs(J)) = 0 Then
                                RemoveNode = False
                            End If
                        Next K
                    Next J
                    If RemoveNode Then
                        Call atv.Nodes.Remove(NodePaths(I))
                    End If
                End If
            Next I
        End If
        
        If m_Multiple Then
            
            wb.Description = "Double click on components in the treeview to add them to the bindings list. You can drag items in the list onto each other to change their order. Select an item in the list and push delete to remove it."
            
            Paths = Split(m_Binding.Path, ",")
                
            For I = 0 To UBound(Paths)
                Set LI = lvw.ListItems.Add(, Paths(I), Paths(I), , II_Component)
            Next I
            RemoveBind.Visible = False
            atv.Width = m_atvWidth
        Else
            
            wb.Description = "Double click a component to bind to."
            RemoveBind.Visible = Not (Len(m_Binding.Path) = 0)
            
            'Set LI = lvw.ListItems.Add(, m_Binding.Path, m_Binding.Path, , II_Component)
            'LI.ForeColor = 0
            'LI.SubItems(1) = "" & I
        
        End If

        'Added 3/21/05 to clarify to the user the restriction of components in the tree view. -CLC
        If IsRestricted Then
            wb.Description = wb.Description & vbCrLf & vbCrLf & "Note: The list below has been restricted to the following component type(s):"
            For J = 0 To UBound(m_Binding.PIDs)
                wb.Description = wb.Description & vbCrLf & m_Binding.PIDs(J)
            Next J
        End If

        Form_Resize
        Me.Show vbModal
        
    End Sub
    
    '**********************************************************************************************************************************
    
    Public Property Get Binding() As IMA2_BindingInfo
        Binding = m_Binding
    End Property
    
    '**********************************************************************************************************************************
    
    Public Property Get Cancelled() As Boolean
        Cancelled = m_Cancelled
    End Property
    
    '**********************************************************************************************************************************
    
    Public Property Get NetList() As NetList
        Set NetList = atv.NetList
    End Property

    '**********************************************************************************************************************************
    
    Public Property Set NetList(NV As NetList)
        Set atv.NetList = NV
        atv.ExpandAll
    End Property
   
'**********************************************************************************************************************************
' Control Events
'**********************************************************************************************************************************
    
    Private Sub atv_DblClick(ByVal Node As mscomctllib.Node)
        
        On Error Resume Next
        
        If PathLevel(Node.Key) <= 1 Then Exit Sub
        
        If m_Multiple Then
            lvw.ListItems.Add , atv.Path, atv.Path, , Node.Image
            Node.Expanded = True
        Else
            m_Binding.Path = atv.Path   'Changed 3/21/05 from "m_Path=atv.Path" -CLC
            Me.Hide
        End If
        
    End Sub

    Private Sub Form_Unload(Cancel As Integer)
    
        Call SaveFormPosition(Me)
    
    End Sub
    
    Private Sub lvw_DblClick()
    
        atv.Path = lvw.SelectedItem.Text
    
    End Sub

    '**********************************************************************************************************************************
    
    Private Sub lvw_KeyDown(KeyCode As Integer, Shift As Integer)
        If KeyCode = vbKeyDelete Then
            On Error Resume Next
            Dim I As Integer
            I = lvw.SelectedItem.Index
            lvw.ListItems.Remove lvw.SelectedItem.Index
            lvw.ListItems(I).Selected = True
            If Err Then lvw.ListItems(I - 1).Selected = True
            Err.Clear
        End If
    End Sub

    '**********************************************************************************************************************************
    
    Private Sub lvw_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
    
        m_MouseX = x
        m_MouseY = y
        m_Dragging = True
    
    End Sub

    Private Sub lvw_MouseMove(Button As Integer, Shift As Integer, x As Single, y As Single)

        Dim LI As ListItem
        Dim TI As ListItem
        
        If m_Dragging Then
            
            Set TI = lvw.HitTest(x, y)
            If TI Is Nothing Then Exit Sub
            If TI.ForeColor = QBColor(8) Then Exit Sub
            
            For Each LI In lvw.ListItems
                LI.ForeColor = 0
            Next
            
            TI.ForeColor = QBColor(8)
            
        End If


    End Sub

    '**********************************************************************************************************************************
    
    Private Sub lvw_MouseUp(Button As Integer, Shift As Integer, x As Single, y As Single)

        Dim LI As ListItem
        Dim TI As ListItem
        Dim TIN As Integer
        
        If m_Dragging Then
            m_Dragging = False
            
            Set TI = lvw.HitTest(x, y)
            If TI Is Nothing Then Exit Sub
            
            TIN = TI.Index
            Set LI = lvw.SelectedItem
            
            If TIN = LI.Index Then Exit Sub
            
            lvw.ListItems.Remove LI.Index
            lvw.ListItems.Add(TIN, , LI.Text, , LI.SmallIcon).Selected = True
            
        End If
        
        For Each LI In lvw.ListItems
            LI.ForeColor = 0
        Next

        
    End Sub

    '**********************************************************************************************************************************
    
    Private Sub ocb_OnCancel()
        m_Cancelled = True
        Me.Hide
    End Sub

    '**********************************************************************************************************************************
    
    Private Sub ocb_OnOK()
        m_Cancelled = False
        
        Dim Paths As String
        
        If m_Multiple Then
        
            Dim LI As ListItem
            For Each LI In lvw.ListItems
                Paths = Paths + "," + LI.Text
            Next
            
            m_Binding.Path = Mid(Paths, 2)
        Else
            m_Binding.Path = atv.Path
        End If
        
        Me.Hide
    End Sub
    
    Private Sub RemoveBind_Click()
        m_Cancelled = False
        m_Binding.Path = ""
        Me.Hide
    End Sub


'**********************************************************************************************************************************
' Form Events
'**********************************************************************************************************************************

    Private Sub Form_Load()
        m_RBRelativeTop = ocb.Top - RemoveBind.Top
        m_Icons.Directory = "C:\Ima2\Icons"
        Set lvw.SmallIcons = m_Icons.ImageList
        Call LoadFormPosition(Me)
        m_atvWidth = (Me.ScaleWidth - (atv.Left * 2) - slr.Width) * 0.5
        
    End Sub

    '**********************************************************************************************************************************
    
    Private Sub Form_Resize()
        Dim W As Single
        Dim H As Single
        
        If m_Multiple Then
            H = ocb.Top - (wb.Height + atv.Left) - (atv.Left * 2)
            atv.Move atv.Left, wb.Height + atv.Left, atv.Width, H
            slr.Move atv.Left + atv.Width, wb.Height + atv.Left, slr.Width, H
            lvw.Move slr.Left + slr.Width, atv.Top, Me.ScaleWidth - slr.Width - atv.Width - atv.Left * 2, H
            lvw.ColumnHeaders(1).Width = lvw.Width - 6
        Else
            RemoveBind.Move RemoveBind.Left, ocb.Top - m_RBRelativeTop
            atv.Move atv.Left, atv.Top, Me.ScaleWidth - atv.Left * 2, ocb.Top - atv.Top - (atv.Left * 2)
        End If
            
    End Sub


    '**********************************************************************************************************************************
    Private Sub slr_OnSplitterRelease(Delta As Single)
        If atv.Width + Delta < 1 Then Exit Sub
        atv.Width = atv.Width + Delta
        m_atvWidth = atv.Width
        Form_Resize
    End Sub
