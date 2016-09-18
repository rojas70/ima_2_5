VERSION 5.00
Begin VB.UserControl ImageLabel 
   ClientHeight    =   3600
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4800
   ScaleHeight     =   240
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   320
   Begin VB.Label lblInfo 
      BackColor       =   &H00C0C0C0&
      BackStyle       =   0  'Transparent
      Caption         =   "\\Icarus\Foo\"
      Height          =   255
      Left            =   1080
      TabIndex        =   1
      Top             =   15
      Width           =   1695
   End
   Begin VB.Label lblCaption 
      BackColor       =   &H00C0C0C0&
      BackStyle       =   0  'Transparent
      Caption         =   "Parent:"
      ForeColor       =   &H00FF0000&
      Height          =   255
      Left            =   285
      TabIndex        =   0
      Top             =   15
      Width           =   735
   End
   Begin VB.Image img 
      Appearance      =   0  'Flat
      Height          =   240
      Left            =   0
      Picture         =   "ImageLabel.ctx":0000
      Top             =   0
      Width           =   240
   End
End
Attribute VB_Name = "ImageLabel"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit


Public Property Get Caption1() As String
    Caption1 = lblCaption.Caption
End Property

Public Property Let Caption1(NV As String)
    lblCaption.Caption = NV
End Property

Public Property Get Caption2() As String
    Caption2 = lblInfo.Caption
End Property

Public Property Let Caption2(NV As String)
    lblInfo.Caption = NV
End Property

Public Property Get Indent1() As Long
    Indent1 = lblCaption.Left
End Property

Public Property Let Indent1(NV As Long)
    lblCaption.Left = NV
End Property

Public Property Get Indent2() As Long
    Indent2 = lblInfo.Left
End Property

Public Property Let Indent2(NV As Long)
    lblInfo.Left = NV
End Property

Public Property Get Picture() As StdPicture
    Set Picture = img.Picture
End Property

Public Property Set Picture(NV As StdPicture)
    Set img.Picture = NV
End Property

Public Property Get Font() As StdFont
    Set Font = lblCaption.Font
End Property

Public Property Set Font(NV As StdFont)
    Set lblCaption.Font = NV
    Set lblInfo.Font = NV
    Set UserControl.Font = NV
    UserControl_Resize
End Property

Public Property Get Color1() As Long
    Color1 = lblCaption.ForeColor
End Property

Public Property Get Color2() As Long
    Color2 = lblInfo.ForeColor
End Property

Public Property Let Color1(NV As Long)
    lblCaption.ForeColor = NV
End Property

Public Property Let Color2(NV As Long)
    lblInfo.ForeColor = NV
End Property

Private Sub UserControl_InitProperties()
    Caption1 = "Caption1"
    Caption2 = "Caption2"
    Indent1 = 20
    Indent2 = 70
End Sub

Private Sub UserControl_ReadProperties(PropBag As PropertyBag)
    Caption1 = PropBag.ReadProperty("Caption1", "Caption1")
    Caption2 = PropBag.ReadProperty("Caption2", "Caption2")
    Indent1 = PropBag.ReadProperty("Indent1", 20)
    Indent2 = PropBag.ReadProperty("Indent2", 70)
    Set Picture = PropBag.ReadProperty("Picture", Nothing)
    Set Font = PropBag.ReadProperty("Font", lblCaption.Font)
End Sub

Private Sub UserControl_Resize()
    On Error Resume Next
    lblCaption.Width = lblInfo.Left - lblCaption.Left
    lblInfo.Width = UserControl.ScaleWidth - lblInfo.Left
    
    lblCaption.Height = UserControl.TextHeight("jX")
    lblInfo.Height = lblCaption.Height
    
    lblCaption.Top = Fix(img.Height / 2) - Fix(lblCaption.Height / 2)
    lblInfo.Top = lblCaption.Top
    
End Sub

Private Sub UserControl_WriteProperties(PropBag As PropertyBag)
    PropBag.WriteProperty "Caption1", Caption1, "Caption1"
    PropBag.WriteProperty "Caption2", Caption2, "Caption2"
    PropBag.WriteProperty "Indent1", Indent1, 20
    PropBag.WriteProperty "Indent2", Indent2, 70
    PropBag.WriteProperty "Picture", Picture, Nothing
    PropBag.WriteProperty "Font", Font, Nothing
End Sub
