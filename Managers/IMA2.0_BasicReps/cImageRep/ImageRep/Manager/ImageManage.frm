VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form Form1 
   AutoRedraw      =   -1  'True
   Caption         =   "ImageRepresentation Manager."
   ClientHeight    =   690
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5025
   LinkTopic       =   "Form1"
   ScaleHeight     =   690
   ScaleWidth      =   5025
   StartUpPosition =   2  'CenterScreen
   Begin MSComDlg.CommonDialog Dialog1 
      Left            =   120
      Top             =   120
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.CommandButton cmdLoadImage 
      Caption         =   "&Load Image"
      Height          =   375
      Left            =   2160
      TabIndex        =   2
      Top             =   120
      Width           =   1335
   End
   Begin VB.CommandButton cmfFileOpen 
      Caption         =   "&Open from file"
      Height          =   375
      Left            =   720
      TabIndex        =   1
      Top             =   120
      Width           =   1335
   End
   Begin VB.CommandButton cmdClose 
      Caption         =   "&Close"
      Height          =   375
      Left            =   3600
      TabIndex        =   0
      Top             =   120
      Width           =   1335
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim m_comp As cImageRep
Private Sub cmdClose_Click()
    End
End Sub

Private Sub cmdLoadImage_Click()
Dim i&, j&
Dim tmpImage() As Byte
Dim tmpCaption$
On Error GoTo errorhandle
tmpImage = m_comp.GetData(0)
Form3.Show
'Form3.Height = 5500
'Form3.Width = 2500
Form3.ScaleMode = 3
Form3.Picture1.Height = m_comp.ImageHeight + 3
Form3.Picture1.Width = m_comp.ImageWidth + 3
Form3.Width = Form3.ScaleX(Form3.Picture1.Width + 8, 3, 1)
Form3.Height = Form3.ScaleY(Form3.Picture1.Height + 26, 3, 1)
'Form3.Width = Form3.Picture1.Width + 6
'Form3.Height = Form3.Picture1.Height + 30
Form3.ScaleMode = 3
Form3.Refresh
tmpCaption = Form1.Caption
y = m_comp.ImageHeight
For i = 1 To m_comp.ImageHeight
 For j = 1 To m_comp.ImageWidth
    Form3.Picture1.PSet (j, i), RGB(tmpImage(0, j, i), tmpImage(1, j, i), tmpImage(2, j, i))
 Next j
 Form1.Caption = tmpCaption + " " + CStr(CInt(((i + 1) / (y)) * 100)) + "%"
Next i
Form1.Caption = tmpCaption
Exit Sub
errorhandle:
    MsgBox "Could not complete the operation. Abort"
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
   Form2.Show
   Form2.Picture1.Picture = LoadPicture(Picturename)
   Form2.Picture1.ScaleMode = 3
   x = Form2.Picture1.ScaleWidth
   y = Form2.Picture1.ScaleHeight
 '  If x > m_comp.Widths Or y > m_comp.Height Then
        'MsgBox "Image is too large. Please send Width and Height and try again"
 '       x = 600
 '       y = 800
        m_comp.ImageWidth = x
        m_comp.ImageHeight = y
        Call m_comp.DoInitial
        'Exit Sub
 '  End If
   Form2.ScaleMode = 1
   Form2.Picture1.ScaleMode = 1
   Form2.Width = 80
   'Form2.Height = 2000
   Form2.Width = Form2.Picture1.Width + 105
   Form2.Height = Form2.Picture1.Height + 375
   Form2.Show
   Form2.Refresh
   Form2.Picture1.ScaleMode = 3
   ReDim PixelData(2, x, y)
   tmpCaption = Form1.Caption
   For i = 0 To y - 1
    For j = 0 To x - 1
        Pixel& = Form2.Picture1.Point(j, i)
        If Pixel& <> -1 Then
            '*****RED*****
            PixelData(0, j, i) = Pixel& Mod 256
            '*****GREEN*****
            PixelData(1, j, i) = ((Pixel And &HFF00FF00) / 256&)
            '*****BLUE*****
            PixelData(2, j, i) = (Pixel And &HFF0000) / 65536
        End If
    Next j
    Form1.Caption = tmpCaption + " " + CStr(CInt(((i + 1) / (y)) * 100)) + "%"
   Next i
   Form1.Caption = tmpCaption
   'Form2.Show
   'Form2.Refresh
   Call m_comp.putData(0, PixelData)
   Erase PixelData
   Exit Sub
errorhandle:
    MsgBox "Could not complete the operation. Abort"
End Sub

Private Sub Command1_Click()

End Sub

Private Sub Form_Load()
    Set m_comp = CreateObject("Imagerep.cimagerep", "ninja")
    'Set m_comp = CreateObject("Imagerep.cimagerep", "kirin")
End Sub
