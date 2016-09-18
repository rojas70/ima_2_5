VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.UserControl InsertComponentView 
   ClientHeight    =   3255
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   6225
   ScaleHeight     =   217
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   415
   Begin IMA2_HelperX.PIDBar pbr 
      Align           =   2  'Align Bottom
      Height          =   345
      Left            =   0
      TabIndex        =   4
      Top             =   2910
      Width           =   6225
      _ExtentX        =   10980
      _ExtentY        =   609
   End
   Begin VB.CommandButton cmd 
      DisabledPicture =   "InsertComponentView.ctx":0000
      DownPicture     =   "InsertComponentView.ctx":0342
      Enabled         =   0   'False
      Height          =   315
      Left            =   5640
      Picture         =   "InsertComponentView.ctx":0684
      Style           =   1  'Graphical
      TabIndex        =   0
      Top             =   0
      Width           =   345
   End
   Begin MSComctlLib.ListView lvw 
      Height          =   2415
      Left            =   -15
      TabIndex        =   1
      Top             =   375
      Width           =   6015
      _ExtentX        =   10610
      _ExtentY        =   4260
      View            =   2
      LabelEdit       =   1
      Sorted          =   -1  'True
      LabelWrap       =   -1  'True
      HideSelection   =   0   'False
      _Version        =   393217
      SmallIcons      =   "iml"
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   0
   End
   Begin MSComctlLib.ImageCombo cmb 
      Height          =   330
      Left            =   675
      TabIndex        =   2
      Top             =   0
      Width           =   4905
      _ExtentX        =   8652
      _ExtentY        =   582
      _Version        =   393216
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      Enabled         =   0   'False
      Locked          =   -1  'True
   End
   Begin VB.Label lblLookIn 
      Caption         =   "Look in:"
      Height          =   255
      Left            =   30
      TabIndex        =   3
      Top             =   45
      Width           =   600
   End
End
Attribute VB_Name = "InsertComponentView"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True

    Option Explicit
    
'****************************************************************************************************************************************
    
    Dim m_Icons     As New IconManager
    Dim m_Libs      As New Libraries
    Dim m_CurLib    As LibInfo
    Dim m_CurCls    As ClsInfo
    
'****************************************************************************************************************************************
    
    Public Event OnCancel()
    Public Event OnOK()
    
'****************************************************************************************************************************************
    Public Property Get LibInfo() As LibInfo
        Set LibInfo = m_CurLib
    End Property
    
    Public Property Get ClsInfo() As ClsInfo
        Set ClsInfo = m_CurCls
    End Property
    
    Public Property Get Path() As String
        Path = m_Libs.Path
    End Property
    
    Public Property Let Path(NV As String)
        m_Libs.Path = NV
        cmd.Enabled = lvw.ListItems.Count > 0
    End Property
    
    Private Sub cmb_Change()
'        Call ShowItems(cmb.SelectedItem.Image)
 '       cmd.Enabled = cmb.SelectedItem.Index > 0
    End Sub

    Private Sub cmb_Click()
  '      cmb_Change
    End Sub

'****************************************************************************************************************************************
    
    Private Sub cmd_Click()
        
        Set cmb.SelectedItem = cmb.ComboItems(cmb.SelectedItem.Index - 1)
        
        If cmb.SelectedItem.Image = II_Library Then
            Set m_CurLib = m_Libs(cmb.SelectedItem.Key)
            Set m_CurCls = Nothing
        ElseIf cmb.SelectedItem.Image = II_Network Then
            Set m_CurLib = Nothing
        End If
        
        Call ShowItems(cmb.SelectedItem.Image)
        Set lvw.SelectedItem = Nothing
        lvw.SetFocus
        pbr.PID = ""
 
    End Sub

    Private Sub lvw_Click()
        If lvw.SelectedItem Is Nothing Then
            pbr.PID = ""
        ElseIf lvw.SelectedItem.SmallIcon = II_Library Then
            pbr.PID = ""
        ElseIf lvw.SelectedItem.SmallIcon = II_Network Then
            pbr.PID = ""
        Else
            Set m_CurCls = m_CurLib.Classes(lvw.SelectedItem.Key)
            pbr.PID = m_CurCls.PID
        End If
    
    End Sub

'****************************************************************************************************************************************
    
    Private Sub lvw_DblClick()
    
        If lvw.SelectedItem Is Nothing Then Exit Sub
        
        If lvw.SelectedItem.SmallIcon = II_Library Then
            Set m_CurLib = m_Libs(lvw.SelectedItem.Key)
            Set m_CurCls = Nothing
            Call ShowItems(II_Library)
        ElseIf lvw.SelectedItem.SmallIcon = II_Network Then
            Set m_CurLib = Nothing
            Call ShowItems(II_Network)
        Else
            Set m_CurCls = m_CurLib.Classes(lvw.SelectedItem.Key)
            RaiseEvent OnOK
            Exit Sub
        End If
        
    End Sub

    Private Sub pbr_OnCancel()
        RaiseEvent OnCancel
    End Sub

    Private Sub pbr_OnOK()
        RaiseEvent OnOK
    End Sub

'****************************************************************************************************************************************
' Usercontrol Events
'****************************************************************************************************************************************
    
    Private Sub UserControl_Initialize()
        m_Icons.Directory = "C:\Ima2\System\Icons"
        Set lvw.SmallIcons = m_Icons.ImageList
        Set cmb.ImageList = m_Icons.ImageList
    End Sub
    
    Private Sub UserControl_InitProperties()
        m_Libs.Path = "C:\Ima2\System\Components"
        Call ShowItems(II_Network)
    End Sub
    
    Private Sub UserControl_ReadProperties(PropBag As PropertyBag)
        m_Libs.Path = PropBag.ReadProperty("Path", "C:\Ima2\System\Components")
        Call ShowItems(II_Network)
    End Sub
    
    Private Sub UserControl_WriteProperties(PropBag As PropertyBag)
        Call PropBag.WriteProperty("Path", m_Libs.Path, "C:\Ima2\System\Components")
    End Sub

    '****************************************************************************************************************************************
    
    Private Sub UserControl_Resize()
        lvw.Height = UserControl.ScaleHeight - lvw.Top - (pbr.Height * 1.2)
        lvw.Width = UserControl.ScaleWidth - (lvw.Left * 2)
        cmd.Left = UserControl.ScaleWidth - cmd.Width
        cmb.Width = cmd.Left - 5 - cmb.Left
    End Sub
    
    
    Private Sub ShowItems(ItemIcon As IMA2_Icons)
        
        Dim LI  As LibInfo
        Dim CI  As ClsInfo
        Dim L   As ListItem
        
        Call cmb.ComboItems.Clear
        Call cmb.ComboItems.Add(, , "IMA2 Components on \\IRLSERVER", II_Network, , 0)
        If Not (m_CurLib Is Nothing) Then Call cmb.ComboItems.Add(, , m_CurLib.Description, II_Library, , 1)
        
        lvw.ListItems.Clear
        Select Case ItemIcon
            Case II_Network:
                For Each LI In m_Libs
                    lvw.ListItems.Add , LI.Name, LI.Description, , II_Library
                Next
                Set cmb.SelectedItem = cmb.ComboItems(1)
            Case II_Library:
                For Each CI In m_CurLib.Classes
                    If m_Icons.IconExists(CI.PID) Then
                        lvw.ListItems.Add , CI.Name, CI.Name, , m_Icons.IconIndex(CI.PID)
                    Else
                        lvw.ListItems.Add , CI.Name, CI.Name, , II_Manager
                    End If
                Next
                Set cmb.SelectedItem = cmb.ComboItems(2)
        End Select
            
        Set lvw.SelectedItem = Nothing
        cmd.Enabled = cmb.SelectedItem.Index > 1
    
    End Sub

'****************************************************************************************************************************************
    
    Private Sub lvw_ItemClick(ByVal Item As MSComctlLib.ListItem)

        If lvw.SelectedItem.SmallIcon = II_Component Then
            Set m_CurCls = m_CurLib.Classes(lvw.SelectedItem.Key)
            'pbr.PID = m_CurCls.PID
        End If

    End Sub
    
'****************************************************************************************************************************************
    
    Private Sub lvw_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
        Set lvw.SelectedItem = lvw.HitTest(X, Y)
    End Sub

