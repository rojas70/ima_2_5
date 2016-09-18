VERSION 5.00
Begin VB.Form frmSaveAs 
   Caption         =   "Save Components To File"
   ClientHeight    =   3960
   ClientLeft      =   165
   ClientTop       =   450
   ClientWidth     =   7890
   Icon            =   "frmSaveAs.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   264
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   526
   StartUpPosition =   3  'Windows Default
   Begin IMA2_DAD.CmpView cmv 
      Height          =   2535
      Left            =   3960
      TabIndex        =   3
      Top             =   840
      Width           =   3735
      _ExtentX        =   6588
      _ExtentY        =   4471
      Style           =   1
   End
   Begin IMA2_HelperX.OKCancelBar ocb 
      Align           =   2  'Align Bottom
      Height          =   510
      Left            =   0
      TabIndex        =   2
      Top             =   3450
      Width           =   7890
      _ExtentX        =   13917
      _ExtentY        =   900
   End
   Begin IMA2_HelperX.WizardBar wiz 
      Align           =   1  'Align Top
      Height          =   735
      Left            =   0
      TabIndex        =   1
      Top             =   0
      Width           =   7890
      _ExtentX        =   13917
      _ExtentY        =   1296
      C               =   ""
      D               =   $"frmSaveAs.frx":014A
      Picture         =   "frmSaveAs.frx":01E1
   End
   Begin MSComDlg.CommonDialog cdlg 
      Left            =   8280
      Top             =   5040
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      CancelError     =   -1  'True
      DefaultExt      =   "*.cmp"
      FileName        =   "*.cmp"
      Filter          =   "IMA2 Component Files (*.cmp)|*.cmp|All Files (*.*)|*.*"
      Flags           =   4
   End
   Begin MSComctlLib.ImageList iml 
      Left            =   8280
      Top             =   4440
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   16777215
      UseMaskColor    =   0   'False
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   9
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmSaveAs.frx":0633
            Key             =   "Network"
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmSaveAs.frx":078D
            Key             =   "Computer"
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmSaveAs.frx":08E7
            Key             =   "Folder"
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmSaveAs.frx":0A41
            Key             =   "Class"
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmSaveAs.frx":0B9B
            Key             =   "Class Grey"
         EndProperty
         BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmSaveAs.frx":0CF5
            Key             =   "Class X"
         EndProperty
         BeginProperty ListImage7 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmSaveAs.frx":0E4F
            Key             =   "Form"
         EndProperty
         BeginProperty ListImage8 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmSaveAs.frx":0FA9
            Key             =   "Control"
         EndProperty
         BeginProperty ListImage9 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmSaveAs.frx":1103
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.TreeView tvw 
      Height          =   2535
      Left            =   120
      TabIndex        =   0
      Top             =   840
      Width           =   3615
      _ExtentX        =   6376
      _ExtentY        =   4471
      _Version        =   393217
      Indentation     =   529
      LineStyle       =   1
      Style           =   7
      ImageList       =   "iml"
      Appearance      =   1
   End
End
Attribute VB_Name = "frmSaveAs"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

'************************************************************************************************
' Private Member Variables
'************************************************************************************************
    
    Dim m_CF    As ComponentFile
    Dim m_Icons As New IconManager
    Dim m_Saved As Boolean
   
'************************************************************************************************
'  Public Functions
'************************************************************************************************
    
    Public Sub StartWizard(CmpPaths() As String, Nds As Nodes)

        Dim Paths() As String
        
        Paths = CmpPaths
        If ArrayEmpty(Paths) Then Exit Sub  'Check for wrong input args
        
        UpdateViewFromPaths Paths           'Generate tree from paths
        SynchronizeImages Nds               'Synchronize images across treeviews
        ExpandAllNodes tvw                  'Expand nodes
        
        Set m_CF = New ComponentFile        'Generate a new component file
        m_CF.Paths = Paths                  'Fill in the paths to save
        
        Set tvw.SelectedItem = tvw.Nodes(1)
        Call tvw_NodeClick(tvw.Nodes(1))
        
        Me.Show vbModal                     'Show the form
        
    End Sub

    '************************************************************************************************
    
    Private Sub SynchronizeImages(Nds As Nodes)

        Dim I As Integer
        
        For I = 1 To tvw.Nodes.Count Step 1
            tvw.Nodes(I).Image = Nds(tvw.Nodes(I).Key).Image
        Next I

    End Sub

'************************************************************************************************
' Private Functions
'************************************************************************************************
    
    Private Sub UpdateViewFromPaths(P() As String)
 
        On Error Resume Next
        
        Dim I   As Integer
        Dim PN  As Node
        Dim UB  As Integer
        Dim LB  As Integer
        
        LB = LBound(P)
        UB = UBound(P)
        If Err Then MsgBox Err.Description, , "Error in array (frmSaveAs.UpdateViewFromPaths)"
        
        tvw.Nodes.Clear
        
        tvw.Nodes.Add , , P(LB), NameFromPath(P(LB)), II_Component
        For I = LB + 1 To UB Step 1
            Set PN = tvw.Nodes.Item(ParentFromPath(P(I)))
            tvw.Nodes.Add PN, tvwChild, P(I), NameFromPath(P(I)), II_Component
        Next
        
        If Err Then MsgBox Err.Description, , "Error in array (2nd: frmSaveAs.UpdateViewFromPaths)"
            
    End Sub

    '************************************************************************************************
    
'    Public Sub Actualize()

 '       Dim Cmp     As IComponent
  '      Dim I       As Integer
   '     Dim CDs()   As CmpDesc
        
    '    CDs = m_CF.Descriptions
     '   For I = 0 To UBound(CDs)
      '      With CDs(I)
       '         Set Cmp = CreateIMA2Component(.Path, .PID, .Machine, True, g_AL)
        '        If Not IsEmpty(.Data) Then Call Cmp.Load(.Data)
         '   End With
'        Next

 '   End Sub
    
'************************************************************************************************
' Public Properties
'************************************************************************************************
    
  
'************************************************************************************************
' Menu Events
'************************************************************************************************
    
'************************************************************************************************
' Public Properties
'************************************************************************************************
    
    Public Property Get FilePath() As String
        FilePath = m_CF.FilePath
    End Property
    
    Public Property Let FilePath(NV As String)
        m_CF.FilePath = NV
        If m_Saved Then
            Me.Caption = NV
        Else
            Me.Caption = NV + "*"
        End If
    End Property
    
'************************************************************************************************
' Form Events
'************************************************************************************************
    
    Private Sub Form_Load()
        Set tvw.ImageList = m_Icons.ImageList
        Set m_CF = New ComponentFile
    End Sub

    Private Sub Form_Resize()
        'On Error Resume Next
        cmv.Move Me.ScaleWidth - cmv.Width - tvw.Left, cmv.Top, cmv.Width, ocb.Top - cmv.Top - tvw.Left
        tvw.Move tvw.Left, tvw.Top, cmv.Left - (2 * tvw.Left), cmv.Height
    End Sub

'************************************************************************************************
' Misc. Functions
'************************************************************************************************

    Private Function GetFileName(OFN As String)
    
        On Error Resume Next
        
        Dim Prompt As String
        Dim Temp As String

        cdlg.FileName = OFN
        
MFSAP:  Me.Visible = False
        
        cdlg.ShowSave
    
        If Err.Number > 0 Then
            Me.Visible = True
            Err.Clear
            Exit Function
        End If
        
        If FileExists(cdlg.FileName) Then
            Prompt = cdlg.FileName & " exists. Overwrite?"
            Select Case MsgBox(Prompt, vbYesNoCancel Or vbQuestion)
                Case vbYes:     Kill cdlg.FileName
                Case vbNo:      GoTo MFSAP
                Case vbCancel:
                    Me.Visible = True
                    Exit Function
            End Select
        End If

        GetFileName = cdlg.FileName
        
    End Function

    '******************************************************************************************

    Private Sub ocb_OnCancel()
        Me.Hide
    End Sub

    '******************************************************************************************

    Private Sub ocb_OnOK()

        Dim FN  As String
        
        FN = GetFileName(m_CF.FilePath)
        If FN = "" Then Exit Sub
        
        m_CF.FilePath = FN
        'Call UpdateFromPaths
        m_CF.Save
        
'        SavedBefore = True
        
        If Err Then MsgBox "Oh no!"
    
    End Sub

    Private Sub tvw_NodeClick(ByVal Node As mscomctllib.Node)
        cmv.Info = g_IS.Item(Node.Key)
    End Sub
