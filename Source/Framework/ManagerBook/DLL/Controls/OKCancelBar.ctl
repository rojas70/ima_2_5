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
   Begin ManagerBook.Bevel Bevel2 
      Align           =   1  'Align Top
      Height          =   45
      Left            =   0
      TabIndex        =   2
      Top             =   0
      Width           =   4800
      _ExtentX        =   8467
      _ExtentY        =   79
      Sides           =   2
      Weight          =   1
   End
End
Attribute VB_Name = "OKCancelBar"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public Event OnCancel()
Public Event OnOK()

Dim m_LastResult As VbMsgBoxResult

Private Sub cmdCancel_Click()
    RaiseEvent OnCancel
    m_LastResult = vbCancel
End Sub

Private Sub cmdOK_Click()
    RaiseEvent OnOK
    m_LastResult = vbOK
End Sub

Public Property Get LastResult() As VbMsgBoxResult
    LastResult = m_LastResult
End Property

Private Sub UserControl_Resize()
    
    On Error Resume Next
    
    Dim sp As Long
    
    sp = Fix((UserControl.ScaleHeight - cmdOK.Height) / 2)
    
    cmdCancel.Left = UserControl.ScaleWidth - cmdCancel.Width - sp
    cmdOK.Left = cmdCancel.Left - cmdOK.Width - 10
    
    cmdOK.Top = 2 + sp
    cmdCancel.Top = cmdOK.Top
    
End Sub

Public Property Get Ok() As CommandButton
    Ok = cmdOK
End Property

Public Property Get Cancel() As CommandButton
    Cancel = cmdCancel
End Property

Public Property Get OkEnabled() As Boolean
    OkEnabled = cmdOK.Enabled
End Property

Public Property Let OkEnabled(NV As Boolean)
    cmdOK.Enabled = NV
End Property

Public Property Get CancelEnabled() As Boolean
    CancelEnabled = cmdCancel.Enabled
End Property

Public Property Let CancelEnabled(NV As Boolean)
    cmdCancel.Enabled = NV
End Property

Private Sub UserControl_ReadProperties(PropBag As PropertyBag)
    cmdOK.Enabled = PropBag.ReadProperty("OE", True)
    cmdCancel.Enabled = PropBag.ReadProperty("CE", True)
End Sub

Private Sub UserControl_WriteProperties(PropBag As PropertyBag)
    Call PropBag.WriteProperty("OE", cmdOK.Enabled, True)
    Call PropBag.WriteProperty("CE", cmdCancel.Enabled, True)
End Sub
