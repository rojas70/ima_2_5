VERSION 5.00
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Begin VB.Form frmInsert 
   Caption         =   "Insert IMA2 Component"
   ClientHeight    =   3855
   ClientLeft      =   5430
   ClientTop       =   4410
   ClientWidth     =   6390
   Icon            =   "frmInsert.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   257
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   426
   Begin VB.CheckBox chkContext 
      Caption         =   "Create component in parent's process."
      Height          =   255
      Left            =   120
      TabIndex        =   1
      Top             =   3600
      Value           =   1  'Checked
      Width           =   3255
   End
   Begin IMA2_HelperX.Bevel bvlTop 
      Align           =   1  'Align Top
      Height          =   30
      Left            =   0
      Top             =   0
      Width           =   6390
      _ExtentX        =   11271
      _ExtentY        =   53
      BS              =   1
      A               =   1
      C1              =   -2147483632
      C2              =   -2147483628
   End
   Begin TabDlg.SSTab tbv 
      Height          =   3435
      Left            =   90
      TabIndex        =   0
      Top             =   120
      Width           =   6165
      _ExtentX        =   10874
      _ExtentY        =   6059
      _Version        =   393216
      Tabs            =   2
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
      Begin IMA2_DADX.InsertFileView ifv 
         Height          =   2895
         Left            =   -74880
         TabIndex        =   2
         Top             =   440
         Width           =   5895
         _ExtentX        =   10398
         _ExtentY        =   5106
      End
      Begin IMA2_DADX.InsertComponentView icv 
         Height          =   2895
         Left            =   120
         TabIndex        =   3
         Top             =   440
         Width           =   5895
         _ExtentX        =   10398
         _ExtentY        =   5106
      End
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
    
    Public Enum InsCmpContext
        ICC_Local = 0
        ICC_Parent = 1
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
        tbv.Height = Me.ScaleHeight - tbv.Top - 5 - chkContext.Height
        tbv.Width = Me.ScaleWidth - tbv.Left - 5
        
        icv.Width = (Screen.TwipsPerPixelX * tbv.Width) - 250
        icv.Height = (Screen.TwipsPerPixelY * tbv.Height) - 570
        
        ifv.Width = icv.Width
        ifv.Height = icv.Height
        
        chkContext.Top = Me.ScaleHeight - chkContext.Height
        
    End Sub

'****************************************************************************************************************************************
' Public Properties
'****************************************************************************************************************************************
    
    Public Property Get Context() As InsCmpContext
        Context = chkContext.Value
    End Property
    
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
    
    'Changes Made By Christina Campbell Feb '05 to remove
    'the compile error "Cannot set array to array".
    
    'Public Property Get Descriptions() As CmpDesc()
    '    If Not m_Choice = ICD_Cancel Then Descriptions = ifv.Descriptions
    'End Property

    Public Property Get DescriptionIndex(I As Integer) As CmpDesc
        Set DescriptionIndex = ifv.DescriptionIndex(I)
    End Property
    
    Public Property Get DescriptionLBound() As Integer
        DescriptionLBound = ifv.DescriptionLBound
    End Property

    Public Property Get DescriptionUBound() As Integer
        DescriptionUBound = ifv.DescriptionUBound
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


