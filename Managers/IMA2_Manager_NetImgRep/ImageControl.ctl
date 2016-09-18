VERSION 5.00
Begin VB.UserControl ImageControl 
   ClientHeight    =   3375
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4560
   ScaleHeight     =   225
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   304
   Begin VB.PictureBox Picture1 
      Appearance      =   0  'Flat
      AutoSize        =   -1  'True
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   3135
      Left            =   120
      ScaleHeight     =   207
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   287
      TabIndex        =   0
      Top             =   120
      Width           =   4335
   End
End
Attribute VB_Name = "ImageControl"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Implements IManager

Dim C As IComponent

Private Property Let IManager_Component(ByVal cmp As IMA2.IComponent)
    Set C = cmp
End Property

Private Property Get IManager_Component() As IComponent
    Set IManager_Component = C
End Property


Private Sub IManager_Update()
If C Is Nothing Then Exit Sub

Dim ImgRep As IImageRep
Dim Data As Variant
Dim ByteArr() As Byte
Dim I As Long
Dim X As Long
Dim Y As Long
Dim P As Long
Dim Pic As StdPicture

Set ImgRep = C
' Call the UpdateManager method on the FrameGrabber component and return a variant "Data".
Data = ImgRep.UpdateManager("IImageRep")

' Allocate memory for byteArray of size: depth by rows by cols.
ReDim ByteArr(0 To Data(0) * Data(1) * Data(2))

'Copy the image data over
ByteArr = Data(3)

'Adjust picture to dimensions of image
Picture1.Move Picture1.Left, Picture1.Top, Data(2), Data(1)
Depth = Data(0)

'Picture1.Cls
X = 0
Y = 0

'For a color image
If (Depth = 3) Then
    For I = LBound(Data(3)) To UBound(Data(3)) Step 3
        Picture1.PSet (X, Y), Data(3)(I) * 256 ^ 2 + Data(3)(I + 1) * 256 + Data(3)(I + 2)
        X = X + 1
        If X >= Data(2) Then
            X = 0
            Y = Y + 1
        End If
    Next I
    
'For a binary image
Else
    For I = LBound(Data(3)) To UBound(Data(3))
        Picture1.PSet (X, Y), RGB(Data(3)(I), Data(3)(I), Data(3)(I))
        X = X + 1
        If X >= Data(2) Then
            X = 0
            Y = Y + 1
        End If
    Next I
End If
' Picture1.Image
End Sub

Private Sub Picture1_Click()

End Sub
