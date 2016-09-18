VERSION 5.00
Begin VB.UserControl OKCancelBar 
   Alignable       =   -1  'True
   ClientHeight    =   3600
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4800
   ScaleHeight     =   240
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   320
   Begin VB.CommandButton cmdCancel 
      Caption         =   "&Cancel"
      Height          =   345
      Left            =   3480
      TabIndex        =   1
      Top             =   120
      Width           =   1245
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&OK"
      Height          =   345
      Left            =   2160
      TabIndex        =   0
      Top             =   120
      Width           =   1245
   End
   Begin IMA2_HelperX.Bevel Bevel2 
      Align           =   1  'Align Top
      Height          =   45
      Left            =   0
      TabIndex        =   2
      Top             =   0
      Width           =   4800
      _ExtentX        =   8467
      _ExtentY        =   79
   End
End
Attribute VB_Name = "OKCancelBar"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
    Option Explicit
    
'************************************************************************************************************
' Public Events
'************************************************************************************************************
    
    Public Event OnCancel()
    Public Event OnOK()
    
'************************************************************************************************************
' Private Member Variables
'************************************************************************************************************
    
    Dim m_LastResult    As VbMsgBoxResult
    Dim m_Ok            As New ButtonWrapper
    Dim m_Cancel        As New ButtonWrapper
    
'************************************************************************************************************
' Public Interface
'************************************************************************************************************
   
    Public Property Get Ok() As ButtonWrapper
        Ok = m_Ok
    End Property
    
    Public Property Get Cancel() As ButtonWrapper
        Cancel = m_Cancel
    End Property
    
    Public Property Get LastResult() As VbMsgBoxResult
        LastResult = m_LastResult
    End Property
    
'************************************************************************************************************
' Control Events
'************************************************************************************************************
    
    Private Sub cmdCancel_Click()
        RaiseEvent OnCancel
        m_LastResult = vbCancel
    End Sub
    
    Private Sub cmdOK_Click()
        RaiseEvent OnOK
        m_LastResult = vbOK
    End Sub
    
'************************************************************************************************************
' Usercontrol Events
'************************************************************************************************************
    
    Private Sub UserControl_Initialize()
        Set m_Ok.Button = cmdOK
        Set m_Cancel.Button = cmdOK
    End Sub

    Private Sub UserControl_ReadProperties(PropBag As PropertyBag)
        cmdOK.Enabled = PropBag.ReadProperty("OE", True)
        cmdCancel.Enabled = PropBag.ReadProperty("CE", True)
    End Sub
    
    Private Sub UserControl_WriteProperties(PropBag As PropertyBag)
        Call PropBag.WriteProperty("OE", cmdOK.Enabled, True)
        Call PropBag.WriteProperty("CE", cmdCancel.Enabled, True)
    End Sub
    
    Private Sub UserControl_Resize()
        
        On Error Resume Next
        
        Dim sp As Long
        
        sp = Fix((UserControl.ScaleHeight - cmdOK.Height) / 2)
        
        cmdCancel.Left = UserControl.ScaleWidth - cmdCancel.Width - sp
        cmdOK.Left = cmdCancel.Left - cmdOK.Width - 10
        
        cmdOK.Top = 2 + sp
        cmdCancel.Top = cmdOK.Top
        
    End Sub

