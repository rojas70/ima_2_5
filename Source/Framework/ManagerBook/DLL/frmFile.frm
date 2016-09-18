VERSION 5.00
Object = "{7B492EBB-3B8A-4D7E-9021-86BB71534052}#1.1#0"; "IMA2_HelperX.ocx"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form frmFile 
   AutoRedraw      =   -1  'True
   Caption         =   "IMA2 ManagerBook"
   ClientHeight    =   7545
   ClientLeft      =   60
   ClientTop       =   630
   ClientWidth     =   10935
   Icon            =   "frmFile.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   503
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   729
   Begin ManagerBook.ManagerTabs mtb 
      Height          =   6975
      Left            =   0
      TabIndex        =   1
      Top             =   120
      Width           =   10935
      _extentx        =   19288
      _extenty        =   12303
   End
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   120
      Top             =   6960
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin MSComctlLib.StatusBar stb 
      Align           =   2  'Align Bottom
      Height          =   315
      Left            =   0
      TabIndex        =   0
      Top             =   7230
      Width           =   10935
      _ExtentX        =   19288
      _ExtentY        =   556
      Style           =   1
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   1
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
         EndProperty
      EndProperty
   End
   Begin IMA2_HelperX.Bevel bvl 
      Align           =   1  'Align Top
      Height          =   135
      Left            =   0
      Top             =   0
      Width           =   10935
      _ExtentX        =   19288
      _ExtentY        =   238
   End
   Begin VB.Timer tmr 
      Left            =   10320
      Top             =   600
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuFile_Load 
         Caption         =   "&Load..."
      End
      Begin VB.Menu mnuFile_SaveAs 
         Caption         =   "Save &As..."
      End
      Begin VB.Menu mnuFile_Sep0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFile_Mappings 
         Caption         =   "&Mappings..."
      End
      Begin VB.Menu mnuFile_Sep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFile_Exit 
         Caption         =   "&Exit"
      End
   End
   Begin VB.Menu mnuManagers 
      Caption         =   "&Managers"
      Begin VB.Menu mnuRun 
         Caption         =   "&Run"
      End
      Begin VB.Menu mnuStop 
         Caption         =   "&Stop"
      End
      Begin VB.Menu mnuManagersSep0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuManagersDelete 
         Caption         =   "&Delete"
      End
      Begin VB.Menu mnuManagersAdd 
         Caption         =   "Add &Manager"
      End
   End
End
Attribute VB_Name = "frmFile"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

'*********************************************************************************************************************
' Private Functions
'*********************************************************************************************************************

        
'*********************************************************************************************************************
' Form Functions
'*********************************************************************************************************************

    Private Sub Form_Load()
    
    End Sub
    
    '*********************************************************************************************************************
    
    Private Sub Form_Resize()
    
        mtb.Height = stb.Top - mtb.Top
        
    End Sub


    Private Sub mnuFile_Load_Click()
    
        CommonDialog1.Filter = "All Files (*.*)|*.*|ManagerFile (*.mgf)|*.mgf"
        ' Specify default filter.
        CommonDialog1.FilterIndex = 2

        ' Display the Open dialog box.
        CommonDialog1.ShowOpen
        If CommonDialog1.FileName <> "" Then
            Call mtb.LoadFromFile(CommonDialog1.FileName)
        End If
    
    End Sub

    Private Sub mnuFile_Mappings_Click()
        frmMappings.Show vbModal
    End Sub

    Private Sub mnuFile_SaveAs_Click()
         CommonDialog1.Filter = "All Files (*.*)|*.*|ManagerFile (*.mgf)|*.mgf"
        ' Specify default filter.
        CommonDialog1.FilterIndex = 2

        ' Display the Open dialog box.
        CommonDialog1.ShowSave
        If CommonDialog1.FileName <> "" Then
            Call mtb.SaveToFile(CommonDialog1.FileName)
        End If
    
    End Sub

    Private Sub mnuManagersAdd_Click()
        Dim MI As New MgrInfo
        
        frmAdd.Show vbModal
        
        If frmAdd.Choice = MAC_OK Then
                
            MI.Path = frmAdd.Path
            MI.MgrPID = frmAdd.PID
        
            mtb.AddManager MI
        End If
        
        Unload frmAdd
    End Sub

    Private Sub mnuManagersDelete_Click()
        mtb.RemoveManager mtb.CurrentPage.Caption, mtb.CurrentManager.Caption
    End Sub

    Private Sub mnuRun_Click()
    
        mtb.Running = True
    
    End Sub

    Private Sub mnuStop_Click()
    
        mtb.Running = False
    
    End Sub


'*********************************************************************************************************************
' Timer Functions
'*********************************************************************************************************************

    Private Sub tmr_Timer()
    
        On Error Resume Next
    
    End Sub
