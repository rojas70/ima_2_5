VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form frmDisplay 
   BackColor       =   &H80000005&
   Caption         =   "Video"
   ClientHeight    =   3645
   ClientLeft      =   3435
   ClientTop       =   915
   ClientWidth     =   4800
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   243
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   320
   Begin VB.Timer timer1 
      Left            =   360
      Top             =   360
   End
   Begin MSComDlg.CommonDialog SaveDialog 
      Left            =   360
      Top             =   960
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
End
Attribute VB_Name = "frmDisplay"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub Form_Load()
    ' Start the timer
    timer1.Interval = 10
    Call SetAcquireMode(0)
    Call VideoFormatChange
End Sub

Private Sub Form_Paint()
    ' call pxSetWindowSize and pxPaintDisplay as a pair
    Call pxSetWindowSize(0, 0, ImageWidth, ImageHeight)
    Call pxPaintDisplay(hDC, frh, 0, 0, ImageWidth, ImageHeight)
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Call SetAcquireMode(1)
End Sub

Private Sub Timer1_Timer()
    ' If the display size was changed, do the following
    If (ChangeSize) Then
        frmDisplay.width = Int(ScaleX(ImageWidth, 3, 1))
        frmDisplay.Height = Int(ScaleY(ImageHeight, 3, 1))
        
        t = PXC_SetXResolution(fgh, x_res)
        t = PXC_SetYResolution(fgh, y_res)
        
        t = PXC_SetWidth(fgh, ImageWidth)
        t = PXC_SetHeight(fgh, y_res)
        ChangeSize = False
    End If
      
    ' If we are acquiring video, do the following
    If (Acquiring) Then
        t = PXC_Grab(fgh, frh, GrabType)
        ' call pxSetWindowSize and pxPaintDisplay as a pair
        Call pxSetWindowSize(0, 0, ImageWidth, ImageHeight)
        Call pxPaintDisplay(hDC, frh, 0, 0, ImageWidth, ImageHeight)
    End If
      
    ' If the GrabOne button was pressed, do the following
    If (GrabOne) Then
        t = PXC_Grab(fgh, frh, GrabType)
        ' call pxSetWindowSize and pxPaintDisplay as a pair
        Call pxSetWindowSize(0, 0, ImageWidth, ImageHeight)
        Call pxPaintDisplay(hDC, frh, 0, 0, ImageWidth, ImageHeight)
        GrabOne = False
    End If
    
    ' Write a BMP file regardless of the status of the Acquiring variable
    If (WRITEBMP) Then
        Call WriteBMPFile
    Else
        WRITEBMP = False
    End If
End Sub

Private Sub WriteBMPFile()
    WRITEBMP = False
    SaveDialog.Filter = "BMP Files (*.BMP)|*.BMP"
    SaveDialog.ShowSave
    
    If (frh = frhRGB) Then
        frhBMP = PXC_AllocateBuffer(ImageWidth, ImageHeight, PBITS_RGB24)
    Else
        frhBMP = PXC_AllocateBuffer(ImageWidth, ImageHeight, PBITS_Y8)
    End If
    
    t = FRAME_CopyFrame(frh, 0, 0, frhBMP, 0, 0, ImageWidth, ImageHeight)
    
    If FRAME_WriteBMP(frhBMP, SaveDialog.filename, 0) = FILE_EXISTS Then
        t = MsgBox("File exists! Overwrite it?", vbOKCancel)
    
        If (t = vbOK) Then
            t = FRAME_WriteBMP(frhBMP, SaveDialog.filename, 1)
        End If
    End If
    PXC_FreeFrame (frhBMP)
End Sub

