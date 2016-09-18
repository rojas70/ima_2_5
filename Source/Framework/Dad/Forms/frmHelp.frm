VERSION 5.00
Begin VB.Form frmHelp 
   Caption         =   "DAD Component Information"
   ClientHeight    =   5535
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   8715
   Icon            =   "frmHelp.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   369
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   581
   StartUpPosition =   3  'Windows Default
   Begin IMA2_DAD.WebBrowser wb 
      Height          =   2895
      Left            =   240
      TabIndex        =   4
      Top             =   1560
      Width           =   7335
      _ExtentX        =   12938
      _ExtentY        =   5106
      URL             =   "http://eecs.vanderbilt.edu/CIS/IRL"
   End
   Begin RichTextLib.RichTextBox rtb 
      Height          =   3015
      Left            =   360
      TabIndex        =   3
      Top             =   1560
      Width           =   7575
      _ExtentX        =   13361
      _ExtentY        =   5318
      _Version        =   393217
      BorderStyle     =   0
      Enabled         =   -1  'True
      ScrollBars      =   3
      DisableNoScroll =   -1  'True
      TextRTF         =   $"frmHelp.frx":0442
   End
   Begin IMA2_HelperX.OKCancelBar ocb 
      Align           =   2  'Align Bottom
      Height          =   495
      Left            =   0
      TabIndex        =   0
      Top             =   5040
      Width           =   8715
      _ExtentX        =   15372
      _ExtentY        =   873
   End
   Begin IMA2_HelperX.WizardBar wzb 
      Align           =   1  'Align Top
      Height          =   975
      Left            =   0
      TabIndex        =   1
      Top             =   0
      Width           =   8715
      _ExtentX        =   15372
      _ExtentY        =   1720
      C               =   "Component Information File"
      D               =   $"frmHelp.frx":04C4
      BC              =   -2147483643
      Picture         =   "frmHelp.frx":0579
   End
   Begin MSComctlLib.TabStrip tbs 
      Height          =   3735
      Left            =   120
      TabIndex        =   2
      Top             =   1080
      Width           =   8415
      _ExtentX        =   14843
      _ExtentY        =   6588
      _Version        =   393216
      BeginProperty Tabs {1EFB6598-857C-11D1-B16A-00C0F0283628} 
         NumTabs         =   3
         BeginProperty Tab1 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "&Class"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab2 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "&Agent"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab3 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "&Internet"
            ImageVarType    =   2
         EndProperty
      EndProperty
   End
End
Attribute VB_Name = "frmHelp"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
    Option Explicit

    Dim m_DI    As IMA2_DistributingInfo
    Dim m_File  As String
    
    Public Sub ShowHelp(Path As String)
    
        If Path = "" Then Exit Sub
        
        On Error Resume Next
        m_DI = g_IS.Item(Path)
        
        If m_DI.Name = "" Then
            'Handle grave error here.
            Exit Sub
        End If
        
        m_File = "C:\Ima2\System\Help\Components\" + m_DI.PID + ".rtf"
        
        If FileExists(m_File) Then
            'Load the server specific help file
            Call rtb.LoadFile(m_File)
        Else
            'Create a new skeleton file from the type information
            Call CreateNewServerFile(m_DI.PID)
        End If
    
        Me.Caption = "Documentation for " + m_DI.Path + " (" + m_DI.PID + ")"
        tbs.SelectedItem = tbs.Tabs(1)
        rtb.SetFocus
        
        'tbs.Tabs(1).Caption = m_DI.PID
        'tbs.Tabs(0).Caption = m_DI.Path
    
        Me.Show
    
    End Sub

    Private Sub CreateNewServerFile(PID As String)
    
        rtb.Text = ""
        rtb.Font.Name = "Courier New"
        rtb.Font.Size = 10
        rtb.Text = rtb.Text + "Class Name: " + PID + vbCrLf
        rtb.Text = rtb.Text + "Updated:    " + CStr(Date) + "(" + CStr(Time) + ") by " + Environ("USERNAME") + vbCrLf + vbCrLf + vbCrLf
    
    End Sub

    Private Sub Form_Load()
            
        'http://eecs.vanderbilt.edu/CIS/IRL
        
    End Sub

    Private Sub Form_Resize()
        On Error Resume Next
        tbs.Move tbs.Left, tbs.Top, Me.ScaleWidth - (tbs.Left * 2), ocb.Top - tbs.Top - tbs.Left
        rtb.Move tbs.ClientLeft + tbs.Left, tbs.ClientTop + tbs.Left, tbs.ClientWidth - (tbs.Left * 2), tbs.ClientHeight - (tbs.Left * 2)
        wb.Move rtb.Left, rtb.Top, rtb.Width, rtb.Height
    End Sub

    Private Sub ocb_OnCancel()
        Me.Hide
    End Sub

    Private Sub ocb_OnOK()
        'Load the server specific help file
        Call rtb.SaveFile(m_File)
        Me.Hide
    End Sub


    Private Sub tbs_Click()
        rtb.Visible = tbs.SelectedItem.Index = 1
        wb.Visible = tbs.SelectedItem.Index = 3
    End Sub
