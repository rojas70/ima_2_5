VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form frmFile 
   Caption         =   "C:\Ima2\Agent1.Cmp"
   ClientHeight    =   5175
   ClientLeft      =   165
   ClientTop       =   735
   ClientWidth     =   5295
   Icon            =   "frmFile.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   345
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   353
   StartUpPosition =   3  'Windows Default
   Begin MSComctlLib.StatusBar stb 
      Align           =   2  'Align Bottom
      Height          =   240
      Left            =   0
      TabIndex        =   1
      Top             =   4935
      Width           =   5295
      _ExtentX        =   9340
      _ExtentY        =   423
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   1
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   1
            Object.Width           =   8837
         EndProperty
      EndProperty
   End
   Begin MSComDlg.CommonDialog cdlg 
      Left            =   3360
      Top             =   600
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
      Left            =   3360
      Top             =   0
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
            Picture         =   "frmFile.frx":014A
            Key             =   "Network"
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmFile.frx":02A4
            Key             =   "Computer"
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmFile.frx":03FE
            Key             =   "Folder"
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmFile.frx":0558
            Key             =   "Class"
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmFile.frx":06B2
            Key             =   "Class Grey"
         EndProperty
         BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmFile.frx":080C
            Key             =   "Class X"
         EndProperty
         BeginProperty ListImage7 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmFile.frx":0966
            Key             =   "Form"
         EndProperty
         BeginProperty ListImage8 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmFile.frx":0AC0
            Key             =   "Control"
         EndProperty
         BeginProperty ListImage9 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmFile.frx":0C1A
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.TreeView tvw 
      Height          =   4335
      Left            =   240
      TabIndex        =   0
      Top             =   840
      Width           =   3135
      _ExtentX        =   5530
      _ExtentY        =   7646
      _Version        =   393217
      Indentation     =   529
      LineStyle       =   1
      Style           =   7
      ImageList       =   "iml"
      Appearance      =   1
   End
   Begin VB.Line Line2 
      BorderColor     =   &H80000014&
      X1              =   0
      X2              =   800
      Y1              =   1
      Y2              =   1
   End
   Begin VB.Line Line1 
      BorderColor     =   &H80000010&
      Tag             =   "c"
      X1              =   0
      X2              =   800
      Y1              =   0
      Y2              =   0
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuFile_New 
         Caption         =   "&New..."
         Shortcut        =   ^N
      End
      Begin VB.Menu mnuFile_Open 
         Caption         =   "&Open..."
         Shortcut        =   ^O
      End
      Begin VB.Menu mnuFile_Sep0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFile_Save 
         Caption         =   "&Save"
         Shortcut        =   ^S
      End
      Begin VB.Menu mnuFile_SaveAs 
         Caption         =   "Save &As..."
         Shortcut        =   ^A
      End
      Begin VB.Menu mnuFile_Sep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFile_Close 
         Caption         =   "&Close"
      End
   End
End
Attribute VB_Name = "frmFile"
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
'  Private Enumerations
'************************************************************************************************
    
    Private Enum DlgType
        dlgOpen = 0
        dlgSave = 1
    End Enum

'************************************************************************************************
' Private Functions
'************************************************************************************************
    
    Private Sub UpdateFromPaths()
 
        On Error Resume Next
        
        Dim I   As Integer
        Dim PN  As Node
        Dim UB  As Integer
        Dim LB  As Integer
        Dim P() As String
        
        P = m_CF.Paths
        LB = LBound(P)
        UB = UBound(P)
        
        tvw.Nodes.Clear
        
        For I = LB To UB Step 1
            Set PN = tvw.Nodes.Item(ParentFromPath(P(I)))
            If PN Is Nothing Then
                tvw.Nodes.Add , , P(I), NameFromPath(P(I)), II_Component
            Else
                tvw.Nodes.Add PN, tvwChild, P(I), NameFromPath(P(I)), II_Component
            End If
        Next
        
        If Err Then Err.Clear
            
        Call ExpandAllNodes(tvw)
    End Sub

    '************************************************************************************************
    
    Private Sub UpdateFromDescriptions()
 
        Dim I   As Integer
        Dim PN  As Node
        Dim UB  As Integer
        Dim LB  As Integer
        Dim P() As String
        Dim CD()    As CmpDesc
        Dim Icon    As IMA2_Icons
        
        CD = m_CF.Descriptions
        P = m_CF.Paths
        LB = LBound(P)
        UB = UBound(P)
        
        tvw.Nodes.Clear
        For I = LB To UB Step 1
            On Error Resume Next
            Set PN = tvw.Nodes.Item(ParentFromPath(P(I)))
            If PN Is Nothing Then Err.Clear
            On Error GoTo 0
            
            Icon = m_Icons.IconIndex(CD(I).PID)

            If PN Is Nothing Then
                'tvw.Nodes.Add , , NameFromPath(P(I)), NameFromPath(P(I)), Icon
                tvw.Nodes.Add , , P(I), NameFromPath(P(I)), Icon
            Else
                tvw.Nodes.Add PN, tvwChild, PN.Key + "\" + NameFromPath(P(I)), NameFromPath(P(I)), Icon
            End If
        Next
        
        If Err Then Err.Clear
           
        Call ExpandAllNodes(tvw)
        
    End Sub

    '************************************************************************************************
    
    Public Sub Actualize()

        Dim Cmp     As IComponent
        Dim I       As Integer
        Dim CDs()   As CmpDesc
        Dim AL      As ILocator
        
        Set AL = GetLocator()
        
        CDs = m_CF.Descriptions
        For I = 0 To UBound(CDs)
            With CDs(I)
                Set Cmp = CreateIMA2Component(.Path, .PID, .Machine, True, AL)
                If Not IsEmpty(.Data) Then Call Cmp.Load(.Data)
            End With
        Next

    End Sub
    
'************************************************************************************************
' Public Properties
'************************************************************************************************
    
    Public Property Get Nodes() As Nodes
        Set Nodes = tvw.Nodes
    End Property
    
    Public Property Get Paths() As String()
        Paths = m_CF.Paths
    End Property
    
  '************************************************************************************************
    
    Public Property Let Paths(NewVal() As String)
        Dim S() As String
        If ArrayEmpty(NewVal) Then Exit Property
        S = NewVal
        m_CF.Paths = S
        Call UpdateFromPaths
    End Property
  
'************************************************************************************************
' Menu Events
'************************************************************************************************
    Public Sub ShowOpen()
        mnuFile_Open_Click
    End Sub
    
    Public Sub ShowSave()
        mnuFile_SaveAs_Click
    End Sub
    
    Private Sub mnuFile_SaveAs_Click()

        Dim FN  As String
        
        FN = GetFileName(m_CF.FilePath, dlgSave)
        If FN = "" Then Exit Sub
        
        m_CF.FilePath = FN
        m_CF.Save
        
        SavedBefore = True
        
        If Err Then MsgBox "Oh no!"
    
    End Sub

  '************************************************************************************************
    
    Private Sub mnuFile_Open_Click()
    
        Dim FN  As String
        
        FN = GetFileName(m_CF.FilePath, dlgOpen)
        If FN = "" Then Exit Sub
        
        m_CF.FilePath = FN
        
'        Stop
        On Error Resume Next
        m_CF.Load
        
        If Err Then
            Call MsgBox(m_CF.FilePath + " could not be opened." + vbCrLf + vbCrLf + "The file is either corrupt or it was saved with a different version of DAD.", vbCritical Or vbOKOnly, "Could not load agent file")
            Exit Sub
        End If
        
        On Error GoTo 0
        
        UpdateFromDescriptions
        SavedBefore = True
    
    End Sub

'************************************************************************************************
' Public Properties
'************************************************************************************************
    
    Public Property Get SavedBefore() As Boolean
        SavedBefore = m_Saved
    End Property
    
    Public Property Let SavedBefore(NV As Boolean)
        m_Saved = NV
        Me.Caption = m_CF.FilePath
        If Not m_Saved Then Me.Caption = Me.Caption + "*"
    End Property
    
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
        tvw.Move 0, 0, Me.ScaleWidth, Me.ScaleHeight - stb.Height
    End Sub

'************************************************************************************************
' Misc. Functions
'************************************************************************************************

    Private Function GetFileName(OFN As String, DT As DlgType)
    
        On Error Resume Next
        
        Dim Prompt As String
        Dim Temp As String

        cdlg.FileName = OFN
        
MFSAP:  If DT = dlgSave Then
            cdlg.ShowSave
        Else
            cdlg.ShowOpen
        End If
    
        If Err.Number > 0 Then Err.Clear: Exit Function
        
        If FileExists(cdlg.FileName) And DT = dlgSave Then
            Prompt = cdlg.FileName & " exists. Overwrite?"
            Select Case MsgBox(Prompt, vbYesNoCancel Or vbQuestion)
                Case vbYes:     Kill cdlg.FileName
                Case vbNo:      GoTo MFSAP
                Case vbCancel:  Exit Function
            End Select
        End If

        GetFileName = cdlg.FileName
        
    End Function


