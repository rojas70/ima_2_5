VERSION 5.00
Begin VB.UserControl WizardBar 
   Alignable       =   -1  'True
   BackColor       =   &H80000005&
   ClientHeight    =   2355
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4800
   ScaleHeight     =   157
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   320
   Begin IMA2_DAD.Bevel Bevel2 
      Align           =   2  'Align Bottom
      Height          =   45
      Left            =   0
      TabIndex        =   0
      Top             =   2310
      Width           =   4800
      _ExtentX        =   8467
      _ExtentY        =   79
      Sides           =   3
      Weight          =   1
   End
   Begin VB.Image img 
      Height          =   480
      Left            =   4080
      Picture         =   "WizardBar.ctx":0000
      Top             =   120
      Width           =   480
   End
   Begin VB.Label lblDescription 
      BackStyle       =   0  'Transparent
      Caption         =   "Description"
      Height          =   375
      Left            =   480
      TabIndex        =   2
      Top             =   480
      Width           =   4575
   End
   Begin VB.Label lblCaption 
      BackStyle       =   0  'Transparent
      Caption         =   "Caption"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   240
      TabIndex        =   1
      Top             =   120
      Width           =   4815
   End
End
Attribute VB_Name = "WizardBar"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public Property Get Caption() As String
    Caption = lblCaption.Caption
End Property

Public Property Let Caption(NV As String)
    If NV = "" Then
        lblDescription.Move 16, 8
    Else
        lblDescription.Move 32, 32
    End If
    lblCaption.Caption = NV
End Property

Public Property Get Description() As String
    Description = lblDescription.Caption
End Property

Public Property Let Description(NV As String)
    lblDescription.Caption = NV
End Property

Public Property Get Picture() As StdPicture
    Set Picture = img.Picture
End Property

Public Property Set Picture(NV As StdPicture)
    Set img.Picture = NV
End Property
    
Private Sub UserControl_ReadProperties(PropBag As PropertyBag)
    Caption = PropBag.ReadProperty("C", "Caption")
    Description = PropBag.ReadProperty("D", "Description")
    Set Picture = PropBag.ReadProperty("Picture", Nothing)
End Sub

Private Sub UserControl_Resize()
    On Error Resume Next
    img.Left = UserControl.ScaleWidth - img.Width - 10
    img.Top = Fix((UserControl.ScaleHeight - img.Width) / 2) - 1
    lblDescription.Width = img.Left - (lblDescription.Left * 2)
    lblDescription.Height = UserControl.ScaleHeight - lblDescription.Top - 3

End Sub

Private Sub UserControl_WriteProperties(PropBag As PropertyBag)
    Call PropBag.WriteProperty("C", lblCaption.Caption, "Caption")
    Call PropBag.WriteProperty("D", lblDescription.Caption, "Description")
    PropBag.WriteProperty "Picture", Picture, Nothing
End Sub

