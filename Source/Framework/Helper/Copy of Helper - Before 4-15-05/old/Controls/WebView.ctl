VERSION 5.00
Begin VB.UserControl WebView 
   Alignable       =   -1  'True
   BackColor       =   &H80000005&
   ClientHeight    =   885
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   8745
   ControlContainer=   -1  'True
   FillColor       =   &H00FFFFFF&
   ScaleHeight     =   59
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   583
   Begin VB.TextBox Text1 
      BorderStyle     =   0  'None
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   13.5
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   360
      Left            =   120
      Locked          =   -1  'True
      TabIndex        =   0
      Text            =   "Text1g"
      Top             =   45
      Width           =   2655
   End
   Begin VB.Line Line1 
      BorderColor     =   &H00CC9966&
      BorderWidth     =   2
      X1              =   -8
      X2              =   2144
      Y1              =   48
      Y2              =   48
   End
   Begin VB.Image Image1 
      Height          =   705
      Left            =   0
      Picture         =   "WebView.ctx":0000
      Top             =   -120
      Visible         =   0   'False
      Width           =   1770
   End
End
Attribute VB_Name = "WebView"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True

Private Sub Text1_KeyPress(KeyAscii As Integer)
    KeyAscii = 0
End Sub

Private Sub UserControl_ReadProperties(PropBag As PropertyBag)

    Text1.Text = PropBag.ReadProperty("Caption", "My Computer")

End Sub

Private Sub UserControl_Resize()

    'Text1.Top = UserControl.ScaleHeight - 2 - Text1.Height
    Text1.Width = UserControl.ScaleWidth - Text1.Left
    Line1.Y1 = UserControl.ScaleHeight - 1
    Line1.Y2 = Line1.Y1
    
End Sub

Private Sub UserControl_WriteProperties(PropBag As PropertyBag)

    Call PropBag.WriteProperty("Caption", Text1.Text, "My Computer")
    
End Sub

Public Property Get Caption() As String
    Caption = Text1.Text
End Property

Public Property Let Caption(NV As String)
    Text1.Text = NV
End Property

Public Property Get ForeColor() As Long
    ForeColor = Text1.ForeColor
End Property

Public Property Let ForeColor(NV As Long)
    Text1.ForeColor = NV
End Property


