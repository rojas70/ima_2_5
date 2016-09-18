VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.UserControl uscImageRep 
   ClientHeight    =   4455
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4710
   ScaleHeight     =   4455
   ScaleWidth      =   4710
   Begin VB.Frame Frame2 
      Caption         =   "Picture:"
      Height          =   3375
      Left            =   120
      TabIndex        =   4
      Top             =   960
      Width           =   4455
      Begin VB.PictureBox Picture1 
         Height          =   3015
         Left            =   120
         ScaleHeight     =   2955
         ScaleWidth      =   4155
         TabIndex        =   5
         Top             =   240
         Width           =   4215
      End
   End
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   4080
      Top             =   240
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.CommandButton cmdClose 
      Caption         =   "&Clear"
      Height          =   375
      Left            =   3120
      TabIndex        =   2
      Top             =   360
      Width           =   1335
   End
   Begin VB.CommandButton cmfFileOpen 
      Caption         =   "&Open from file"
      Height          =   375
      Left            =   240
      TabIndex        =   1
      Top             =   360
      Width           =   1335
   End
   Begin VB.CommandButton cmdLoadImage 
      Caption         =   "&Load Image"
      Height          =   375
      Left            =   1680
      TabIndex        =   0
      Top             =   360
      Width           =   1335
   End
   Begin VB.Frame Frame1 
      Caption         =   "ImageRepresentation Manager."
      Height          =   735
      Left            =   120
      TabIndex        =   3
      Top             =   120
      Width           =   4455
   End
End
Attribute VB_Name = "uscImageRep"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Implements IManager
Dim m_comp As cImageRep
Private Sub cmdClose_Click()
    Picture1.Cls
End Sub

Private Sub cmdLoadImage_Click()
Dim i&, j&
Dim tmpImage() As Byte
Dim tmpCaption$
'On Error GoTo errorhandle
'tmpImage = m_comp.getData(0)
'Form3.Show
'Form3.Height = 5500
'Form3.Width = 2500
'Frame2.ScaleMode = 3
'Form3.Picture1.Height = m_comp.ImageHeight + 3
'Form3.Picture1.Width = m_comp.ImageWidth + 3
'Form3.Width = Form3.ScaleX(Form3.Picture1.Width + 8, 3, 1)
'Form3.Height = Form3.ScaleY(Form3.Picture1.Height + 26, 3, 1)
'Form3.Width = Form3.Picture1.Width + 6
'Form3.Height = Form3.Picture1.Height + 30
'Form3.ScaleMode = 3
'Form3.Refresh
'tmpCaption = Frame1.Caption
'y = m_comp.ImageHeight
'For i = 1 To m_comp.ImageHeight
' For j = 1 To m_comp.ImageWidth
'    Form3.Picture1.PSet (j, i), RGB(tmpImage(0, j, i), tmpImage(1, j, i), tmpImage(2, j, i))
' Next j
' Frame1.Caption = tmpCaption + " " + CStr(CInt(((i + 1) / (y)) * 100)) + "%"
'Next i
'Frame1.Caption = tmpCaption
'Exit Sub
'errorhandle:
'    MsgBox "Could not complete the operation. Abort"
End Sub

Private Sub cmfFileOpen_Click()
Dim Picturename As String
Dim Pixel As Long
Dim i&, j&
Dim PixelData() As Byte
Dim tmpCaption$
On Error GoTo errorhandle
   Dialog1.InitDir = App.Path
   Dialog1.Filter = "Images(*.bmp,*.gif,*.jpg,*.dib)|*.BMP;*.GIP;*.JPG;*.DIB|All Files|*.*"
   Dialog1.Action = 1
   Picturename = Dialog1.FileName
   If Picturename = "" Then Exit Sub
   Picture1.Picture = LoadPicture(Picturename)
   Picture1.ScaleMode = 3
   x = Picture1.ScaleWidth
   y = Picture1.ScaleHeight
 '  If x > m_comp.Widths Or y > m_comp.Height Then
        'MsgBox "Image is too large. Please send Width and Height and try again"
 '       x = 600
 '       y = 800
        m_comp.ImageWidth = x
        m_comp.ImageHeight = y
        Call m_comp.DoInitial
        'Exit Sub
 '  End If
  ' Form2.ScaleMode = 1
  ' Form2.Picture1.ScaleMode = 1
  ' Form2.Width = 80
   'Form2.Height = 2000
'   Form2.Width = Form2.Picture1.Width + 105
'   Form2.Height = Form2.Picture1.Height + 375
'   Form2.Show
'   Form2.Refresh
'   Form2.Picture1.ScaleMode = 3
   ReDim PixelData(2, x, y)
   tmpCaption = Frame1.Caption
   For i = 0 To y - 1
    For j = 0 To x - 1
        Pixel& = Picture1.Point(j, i)
        If Pixel& <> -1 Then
            '*****RED*****
            PixelData(0, j, i) = Pixel& Mod 256
            '*****GREEN*****
            PixelData(1, j, i) = ((Pixel And &HFF00FF00) / 256&)
            '*****BLUE*****
            PixelData(2, j, i) = (Pixel And &HFF0000) / 65536
        End If
    Next j
    Frame1.Caption = tmpCaption + " " + CStr(CInt(((i + 1) / (y)) * 100)) + "%"
   Next i
   Frame1.Caption = tmpCaption
   'Form2.Show
   'Form2.Refresh
   Call m_comp.putData(0, PixelData)
   Erase PixelData
   Exit Sub
errorhandle:
    MsgBox "Could not complete the operation. Abort"
End Sub


Private Sub Form_Load()
    'Set m_comp = CreateObject("Imagerep.cimagerep", "ninja")
    'Set m_comp = CreateObject("Imagerep.cimagerep", "kirin")
End Sub

Private Sub IManager_SetComponent(C As IMA2.IComponent)
    Dim VC As Boolean
    Set m_Cmp = C
    
    VC = Not (C Is Nothing)
    If VC Then VC = (TypeOf C Is cImageRep)
'    Text1.Enabled = VC
'    Text2.Enabled = VC
'    Text3.Enabled = VC
    mnuComponent.Enabled = VC

   Call IManager_Update(0)
End Sub

Private Sub IManager_Update(Optional Flags As Variant)

End Sub

