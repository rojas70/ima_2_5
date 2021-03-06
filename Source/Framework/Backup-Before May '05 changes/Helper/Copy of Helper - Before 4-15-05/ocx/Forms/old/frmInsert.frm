VERSION 5.00
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Begin VB.Form frmInsert 
   Caption         =   "Insert IMA2 Component"
   ClientHeight    =   3645
   ClientLeft      =   2775
   ClientTop       =   3765
   ClientWidth     =   6360
   Icon            =   "frmInsert.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   243
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   424
   Begin TabDlg.SSTab tbv 
      Height          =   3435
      Left            =   90
      TabIndex        =   0
      Top             =   120
      Width           =   6165
      _ExtentX        =   10874
      _ExtentY        =   6059
      _Version        =   393216
      Style           =   1
      TabHeight       =   529
      TabCaption(0)   =   "&New"
      TabPicture(0)   =   "frmInsert.frx":014A
      Tab(0).ControlEnabled=   -1  'True
      Tab(0).Control(0)=   "icv"
      Tab(0).Control(0).Enabled=   0   'False
      Tab(0).ControlCount=   1
      TabCaption(1)   =   "&Existing"
      TabPicture(1)   =   "frmInsert.frx":0166
      Tab(1).ControlEnabled=   0   'False
      Tab(1).Control(0)=   "ifv"
      Tab(1).ControlCount=   1
      TabCaption(2)   =   "&Recent"
      TabPicture(2)   =   "frmInsert.frx":0182
      Tab(2).ControlEnabled=   0   'False
      Tab(2).ControlCount=   0
      Begin IMA2_DAD.InsertFileView ifv 
         Height          =   2895
         Left            =   -74880
         TabIndex        =   2
         Top             =   440
         Width           =   5895
         _ExtentX        =   10398
         _ExtentY        =   5106
      End
      Begin IMA2_DAD.InsertComponentView icv 
         Height          =   2895
         Left            =   120
         TabIndex        =   1
         Top             =   440
         Width           =   5895
         _ExtentX        =   10398
         _ExtentY        =   5106
      End
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
End
Attribute VB_Name = "frmInsert"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
    Option Explicit
    
'****************************************************************************************************************************************
    
    Public Enum InsCmpChoice
        ICD_Cancel = 0
        ICD_New = 1
        ICD_Load = 2
    End Enum
    
'****************************************************************************************************************************************
    
    Dim m_Choice        As InsCmpChoice
    Dim m_ParentPath    As String

'****************************************************************************************************************************************
' Form Events
'****************************************************************************************************************************************
    
    Private Sub Form_Load()
        m_Choice = ICD_Cancel
        ParentPath = "(no parent specified)"
        tbv.Tab = 0
    End Sub
    
    '****************************************************************************************************************************************
    
    Private Sub Form_KeyDown(KeyCode As Integer, Shift As Integer)
        If KeyCode = vbKeyEscape Then m_Choice = ICD_Cancel: Me.Hide
    End Sub
    
    '****************************************************************************************************************************************
    
    Private Sub Form_Resize()
        tbv.Height = Me.ScaleHeight - tbv.Top - 5
        tbv.Width = Me.ScaleWidth - tbv.Left - 5
        
        icv.Width = (Screen.TwipsPerPixelX * tbv.Width) - 250
        icv.Height = (Screen.TwipsPerPixelY * tbv.Height) - 570
        
        ifv.Width = icv.Width
        ifv.Height = icv.Height
        
    End Sub

'****************************************************************************************************************************************
' Public Properties
'****************************************************************************************************************************************
    
    Public Property Get Choice() As InsCmpChoice
        Choice = m_Choice
    End Property
    
    '****************************************************************************************************************************************
    
    Public Property Get LibInfo() As LibInfo
        If Not m_Choice = ICD_Cancel Then Set LibInfo = icv.LibInfo
    End Property
    
    '****************************************************************************************************************************************
    
    Public Property Get ClsInfo() As ClsInfo
        If Not m_Choice = ICD_Cancel Then Set ClsInfo = icv.ClsInfo
    End Property

    '****************************************************************************************************************************************
    
    Public Property Get FilePath() As String
        If Not m_Choice = ICD_Cancel Then FilePath = ifv.FilePath
    End Property
    
    '****************************************************************************************************************************************
    
    Public Property Get Descriptions() As CmpDesc()
        If Not m_Choice = ICD_Cancel Then Descriptions = ifv.Descriptions
    End Property

    '****************************************************************************************************************************************
    
    Public Property Get ParentPath() As String
        ParentPath = m_ParentPath
    End Property

    '****************************************************************************************************************************************
    
    Public Property Let ParentPath(NV As String)
        m_ParentPath = NV
        ifv.ParentPath = NV
        Me.Caption = "Insert Component Into " + NV
    End Property


'****************************************************************************************************************************************
'Control Events
'****************************************************************************************************************************************
    
    Private Sub icv_OnCancel()
        m_Choice = ICD_Cancel
        Me.Hide
    End Sub

    '****************************************************************************************************************************************
    
    Private Sub icv_OnOK()
        m_Choice = ICD_New
        Me.Hide
    End Sub

    '****************************************************************************************************************************************
    
    Private Sub ifv_OnCancel()
        m_Choice = ICD_Cancel
        Me.Hide
    End Sub

    '****************************************************************************************************************************************
    
    Private Sub ifv_OnOK()
        m_Choice = ICD_Load
        Me.Hide
    End Sub


