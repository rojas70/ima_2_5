VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "mscomctl.ocx"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "comdlg32.ocx"
Object = "{7B492EBB-3B8A-4D7E-9021-86BB71534052}#1.1#0"; "IMA2_HelperX.ocx"
Begin VB.UserControl InsertFileView 
   ClientHeight    =   3330
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   6165
   ScaleHeight     =   222
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   411
   ToolboxBitmap   =   "InsertFileView.ctx":0000
   Begin VB.PictureBox sp 
      Height          =   2295
      Left            =   3120
      ScaleHeight     =   2235
      ScaleWidth      =   2835
      TabIndex        =   6
      Top             =   375
      Width           =   2895
      Begin IMA2_HelperX.Bevel bvlTop 
         Height          =   255
         Left            =   120
         Top             =   360
         Width           =   2535
         _ExtentX        =   4471
         _ExtentY        =   450
         BS              =   1
         C1              =   -2147483632
         C2              =   -2147483628
      End
      Begin IMA2_HelperX.Bevel bvlBottom 
         Height          =   255
         Left            =   120
         Top             =   1200
         Width           =   2535
         _ExtentX        =   4471
         _ExtentY        =   450
         BS              =   1
         C1              =   -2147483632
         C2              =   -2147483628
      End
      Begin VB.Image img 
         Appearance      =   0  'Flat
         Height          =   240
         Index           =   3
         Left            =   120
         Picture         =   "InsertFileView.ctx":0312
         Top             =   1440
         Width           =   240
      End
      Begin VB.Image img 
         Appearance      =   0  'Flat
         Height          =   240
         Index           =   2
         Left            =   120
         Picture         =   "InsertFileView.ctx":045C
         Top             =   140
         Width           =   240
      End
      Begin VB.Image img 
         Appearance      =   0  'Flat
         Height          =   240
         Index           =   1
         Left            =   120
         Picture         =   "InsertFileView.ctx":05A6
         Top             =   945
         Width           =   240
      End
      Begin VB.Image img 
         Appearance      =   0  'Flat
         Height          =   240
         Index           =   0
         Left            =   120
         Picture         =   "InsertFileView.ctx":06F0
         Top             =   630
         Width           =   240
      End
      Begin VB.Label lblMachine 
         Caption         =   "NINJA"
         Height          =   255
         Left            =   960
         TabIndex        =   14
         Top             =   960
         Width           =   1695
      End
      Begin VB.Label lblDataSize 
         Caption         =   "100kb"
         Height          =   255
         Left            =   960
         TabIndex        =   13
         Top             =   1440
         Width           =   1695
      End
      Begin VB.Label lbl 
         Caption         =   "Data:"
         ForeColor       =   &H00FF0000&
         Height          =   255
         Index           =   3
         Left            =   415
         TabIndex        =   12
         Top             =   1440
         Width           =   495
      End
      Begin VB.Label lbl 
         Caption         =   "Host:"
         ForeColor       =   &H00FF0000&
         Height          =   255
         Index           =   2
         Left            =   415
         TabIndex        =   11
         Top             =   960
         Width           =   420
      End
      Begin VB.Label lblPID 
         Caption         =   "IMA2_Agent.Agent"
         Height          =   255
         Left            =   960
         TabIndex        =   10
         Top             =   660
         Width           =   1695
      End
      Begin VB.Label lbl 
         Caption         =   "PID:"
         ForeColor       =   &H00FF0000&
         Height          =   255
         Index           =   1
         Left            =   415
         TabIndex        =   9
         Top             =   660
         Width           =   420
      End
      Begin VB.Label lbl 
         Caption         =   "Parent:"
         ForeColor       =   &H00FF0000&
         Height          =   255
         Index           =   0
         Left            =   405
         TabIndex        =   7
         Top             =   135
         Width           =   495
      End
      Begin VB.Label lblParent 
         Caption         =   "\\Icarus\Foo\"
         Height          =   255
         Left            =   960
         TabIndex        =   8
         Top             =   135
         Width           =   1695
      End
   End
   Begin MSComctlLib.TreeView tvw 
      Height          =   2295
      Left            =   0
      TabIndex        =   5
      Top             =   375
      Width           =   3015
      _ExtentX        =   5318
      _ExtentY        =   4048
      _Version        =   393217
      HideSelection   =   0   'False
      Indentation     =   529
      LineStyle       =   1
      Style           =   7
      Appearance      =   1
   End
   Begin VB.CommandButton cmdCancel 
      Caption         =   "&Cancel"
      Height          =   345
      Left            =   4920
      TabIndex        =   4
      Top             =   2880
      Width           =   1125
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&OK"
      Enabled         =   0   'False
      Height          =   345
      Left            =   3720
      TabIndex        =   3
      Top             =   2880
      Width           =   1125
   End
   Begin VB.CommandButton cmdFile 
      DisabledPicture =   "InsertFileView.ctx":083A
      DownPicture     =   "InsertFileView.ctx":0B7C
      Height          =   285
      Left            =   5160
      Picture         =   "InsertFileView.ctx":0CC6
      Style           =   1  'Graphical
      TabIndex        =   0
      Top             =   30
      Width           =   300
   End
   Begin VB.TextBox txtPath 
      Enabled         =   0   'False
      Height          =   330
      Left            =   675
      Locked          =   -1  'True
      TabIndex        =   2
      Text            =   "(no file selected)"
      Top             =   0
      Width           =   4815
   End
   Begin MSComDlg.CommonDialog cdlg 
      Left            =   1320
      Top             =   2760
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      CancelError     =   -1  'True
      DefaultExt      =   "*.cmp"
      FileName        =   "*.cmp"
      Filter          =   "IMA2 Component Files (*.cmp)|*.cmp|All Files (*.*)|*.*"
      Flags           =   4
   End
   Begin VB.Label lblLookIn 
      Caption         =   "Look in:"
      Height          =   255
      Left            =   30
      TabIndex        =   1
      Top             =   45
      Width           =   600
   End
End
Attribute VB_Name = "InsertFileView"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True

Option Explicit

'************************************************************************************************
' Private Member Variables
'************************************************************************************************
    
    Dim m_CF    As New ComponentFile
    Dim m_Icons As New IconManager
    
'****************************************************************************************************************************************
    
    Public Event OnCancel()
    Public Event OnOK()

'************************************************************************************************
' Private Functions
'************************************************************************************************
    
    Private Sub UpdateFromDescriptions()
 
        Dim I       As Integer
        Dim PN      As Node
        Dim UB      As Integer
        Dim LB      As Integer
        Dim P()     As String
        Dim CD()    As CmpDesc
        
        'Changes Made By Christina Campbell Feb '05 to remove
        'The visual basic error "Cannot set array to array"
        ReDim CD(m_CF.DescriptionLBound To m_CF.DescriptionUBound)
        For I = LBound(CD) To UBound(CD)
            Set CD(I) = m_CF.DescriptionIndex(I)
        Next I
        'The old code here was CD = m_CF.Descriptions
        
        P = m_CF.Paths
        LB = LBound(P)
        UB = UBound(P)
        
        tvw.Nodes.Clear
        
        tvw.Nodes.Add , , P(LB), NameFromPath(P(LB)), m_Icons.IconIndex(CD(LB).PID)
        
        For I = LB + 1 To UB
            Set PN = tvw.Nodes(ParentFromPath(P(I)))
            tvw.Nodes.Add(PN, tvwChild, P(I), NameFromPath(P(I)), m_Icons.IconIndex(CD(I).PID)).Tag = Str(I)
        Next
            
        Call ExpandAllNodes(tvw)
        
    End Sub

'************************************************************************************************
' Public Properties
'************************************************************************************************
    
    Public Property Get FilePath() As String
        FilePath = m_CF.FilePath
    End Property
    
    Public Property Let FilePath(NV As String)
        m_CF.FilePath = NV
    End Property
    
    Public Property Get ParentPath() As String
        ParentPath = lblParent.Caption
    End Property
    
    Public Property Let ParentPath(NV As String)
        lblParent.Caption = NV
    End Property
    
    '****************************************************************************************************************************************
    
    'Changes Made By Christina Campbell Feb '05 to remove
    'the compile error "Cannot set array to array".
    
    'Don't ever use this function. It's only here for compatibility
    Public Property Get Descriptions() As CmpDesc()
        Descriptions = m_CF.Descriptions
    End Property
    
    Public Property Get DescriptionIndex(I As Integer) As CmpDesc
        Set DescriptionIndex = m_CF.DescriptionIndex(I)
    End Property
    
    Public Property Get DescriptionLBound() As Integer
        DescriptionLBound = m_CF.DescriptionLBound
    End Property

    Public Property Get DescriptionUBound() As Integer
        DescriptionUBound = m_CF.DescriptionUBound
    End Property
    
'************************************************************************************************
' Command Button Events
'************************************************************************************************
    
    Private Sub cmdFile_Click()
    
        On Error Resume Next
        
        Dim NF As New ComponentFile
        
        NF.FilePath = GetFileName(m_CF.FilePath)
        If NF.FilePath = "" Then Exit Sub
        
        NF.Load
        
        If Err Then
            Err.Clear
            Call MsgBox(NF.FilePath + " could not be opened." + vbCrLf + vbCrLf + "The file is either corrupt or it was saved with a different version of DAD.", vbCritical Or vbOKOnly, "Could not load agent file")
            txtPath.Text = "(no file selected)"
            cmdOK.Enabled = False
            Call SetVisibleControls(False)
            Exit Sub
        End If
        
        Set m_CF = NF
               
        txtPath.Text = m_CF.FilePath
        cmdOK.Enabled = True
        Call SetVisibleControls(True)
        
        UpdateFromDescriptions
        tvw.SetFocus
        
        tvw.Nodes(1).Selected = True
        Call tvw_NodeClick(tvw.Nodes(1))
    
    End Sub

    Private Sub SetVisibleControls(NV As Boolean)
        Dim I As Integer
        For I = 0 To 3
            lbl(I).Visible = NV
            img(I).Visible = NV
        Next I
        lblParent.Visible = NV
        bvlTop.Visible = NV
        bvlBottom.Visible = NV
        cmdOK.Enabled = NV
    End Sub

    Private Sub cmdFile_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
        tvw.SetFocus
    End Sub

    Private Sub cmdOK_Click()
        RaiseEvent OnOK
    End Sub
    
    Private Sub cmdCancel_Click()
        RaiseEvent OnCancel
    End Sub


    Private Sub tvw_AfterLabelEdit(Cancel As Integer, NewString As String)
        Cancel = Not ValidComponentName(NewString)
        'If Not Cancel Then m_CF.Descriptions (
    End Sub

    Private Sub tvw_NodeClick(ByVal Node As MSComctlLib.Node)
    
        Dim CDs()   As CmpDesc
        
        If Node Is Nothing Then Exit Sub
        
        'Changes Made By Christina Campbell Feb '05 to remove
        'the compile error "Cannot set array to array".
        Dim I As Integer
        ReDim CDs(m_CF.DescriptionLBound To m_CF.DescriptionUBound)
        For I = LBound(CDs) To UBound(CDs)
            Set CDs(I) = m_CF.DescriptionIndex(I)
        Next I
        'The old code here was CDs = m_CF.Descriptions
        
        With CDs(Val(Node.Tag))
            lblPID.Caption = .PID
            lblDataSize.Caption = "(no data)"
            lblMachine.Caption = .Machine
            
            If .DataSize > 1000 Then
                lblDataSize.Caption = "" & Fix(.DataSize / 1000) & " Kb"
            ElseIf .DataSize > 0 Then
                lblDataSize.Caption = "" & .DataSize & " bytes"
            End If
        End With
    
    End Sub

'************************************************************************************************
' Usercontrol Events
'************************************************************************************************

    Private Sub UserControl_Initialize()

        m_Icons.Directory = "C:\IMA2\Icons"
        Set tvw.ImageList = m_Icons.ImageList
        lblPID = ""
        lblDataSize = ""
        lblMachine = ""
        Call SetVisibleControls(False)

    End Sub

    '************************************************************************************************
    
    Private Sub UserControl_Resize()
    
        txtPath.Width = UserControl.ScaleWidth - txtPath.Left
        cmdFile.Left = UserControl.ScaleWidth - cmdFile.Width - 2
        
        tvw.Width = (UserControl.ScaleWidth / 2) - 2
        tvw.Height = UserControl.ScaleHeight - tvw.Top - cmdOK.Height - 4
        
        sp.Width = tvw.Width
        sp.Height = tvw.Height
        sp.Left = UserControl.ScaleWidth - sp.Width
        
        cmdCancel.Top = UserControl.ScaleHeight - cmdCancel.Height
        cmdCancel.Left = UserControl.ScaleWidth - cmdCancel.Width
        
        cmdOK.Top = UserControl.ScaleHeight - cmdOK.Height
        cmdOK.Left = cmdCancel.Left - cmdOK.Width - 5
    
        bvlTop.Width = (Screen.TwipsPerPixelX * sp.Width) - (bvlTop.Left * 2)
        bvlBottom.Width = bvlTop.Width
        
    
    End Sub

'************************************************************************************************
' Misc. Functions
'************************************************************************************************

    Private Function GetFileName(OFN As String) As String
    
        On Error Resume Next
        
        cdlg.FileName = OFN
        cdlg.ShowOpen
    
        If Err.Number > 0 Then Err.Clear: Exit Function
        
        GetFileName = cdlg.FileName
        
    End Function


