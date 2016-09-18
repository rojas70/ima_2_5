VERSION 5.00
Object = "{7B492EBB-3B8A-4D7E-9021-86BB71534052}#1.1#0"; "IMA2_HelperX.ocx"
Object = "{81605258-1A3B-47EE-A9BE-4F1963575A0F}#1.1#0"; "IMA2_DadX.ocx"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form frmBindings 
   Caption         =   "Bindings Wizard"
   ClientHeight    =   5355
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7980
   ControlBox      =   0   'False
   Icon            =   "frmBindings.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   357
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   532
   StartUpPosition =   3  'Windows Default
   Begin MSComctlLib.ListView lvw 
      Height          =   2415
      Left            =   240
      TabIndex        =   3
      Top             =   1440
      Visible         =   0   'False
      Width           =   6735
      _ExtentX        =   11880
      _ExtentY        =   4260
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
      Top             =   4665
      Width           =   7980
      _ExtentX        =   14076
      _ExtentY        =   1217
   End
   Begin IMA2_HelperX.WizardBar wb 
      Align           =   1  'Align Top
      Height          =   1245
      Left            =   0
      TabIndex        =   1
      Top             =   0
      Width           =   7980
      _ExtentX        =   14076
      _ExtentY        =   2196
      C               =   "Select A Component To Bind To:"
      Picture         =   "frmBindings.frx":0442
   End
   Begin IMA2_DADX.AgentTreeview atv 
      Height          =   3255
      Left            =   240
      TabIndex        =   0
      Top             =   1920
      Width           =   7980
      _ExtentX        =   14076
      _ExtentY        =   5741
   End
   Begin VB.Image imSel 
      Height          =   240
      Left            =   1320
      Picture         =   "frmBindings.frx":0894
      Top             =   4440
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
    
'**********************************************************************************************************************************
' Public Interface
'**********************************************************************************************************************************
    
    Public Sub ShowDialog(Binding As IMA2_BindingInfo)

        Dim LI As ListItem
        
        m_Binding = Binding
        m_Multiple = m_Binding.BindType And BT_Collection
        
        lvw.ListItems.Clear
        lvw.Visible = m_Multiple
        
        If m_Multiple Then
            
            wb.Description = "Double click on components in the treeview to add them to the bindings list. You can drag items in the list onto each other to change their order. Select an item in the list and push delete to remove it."
            
            Dim Paths() As String
            Dim I As Integer
            Paths = Split(m_Binding.Path, ",")
                
            For I = 0 To UBound(Paths)
                Set LI = lvw.ListItems.Add(, Paths(I), Paths(I), , II_Component)
            Next I
            
        Else
            
            wb.Description = "Double click a component to bind to."
            
            'Set LI = lvw.ListItems.Add(, m_Binding.Path, m_Binding.Path, , II_Component)
            'LI.ForeColor = 0
            'LI.SubItems(1) = "" & I
        
        End If

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
            m_Path = atv.Path
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


'**********************************************************************************************************************************
' Form Events
'**********************************************************************************************************************************

    Private Sub Form_Load()
        
        m_Icons.Directory = "C:\Ima2\Icons"
        Set lvw.SmallIcons = m_Icons.ImageList
        Call LoadFormPosition(Me)
        
    End Sub

    '**********************************************************************************************************************************
    
    Private Sub Form_Resize()
        Dim W As Single
        Dim H As Single
        
        If m_Multiple Then
            W = Me.ScaleWidth - (atv.Left * 3)
            H = ocb.Top - (wb.Height + atv.Left) - (atv.Left * 2)
            atv.Move atv.Left, wb.Height + atv.Left, W * 0.4, H
            lvw.Move (atv.Left * 2) + atv.Width, atv.Top, W * 0.6, H
            lvw.ColumnHeaders(1).Width = lvw.Width - 6
        Else
            atv.Move atv.Left, atv.Top, Me.ScaleWidth - atv.Left * 2, ocb.Top - atv.Top - (atv.Left * 2)
        End If
            
    End Sub

    '**********************************************************************************************************************************
    
