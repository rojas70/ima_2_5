VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form frmControls 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "PXC200 & PXC200A Controls"
   ClientHeight    =   3870
   ClientLeft      =   5115
   ClientTop       =   4500
   ClientWidth     =   7110
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   3870
   ScaleWidth      =   7110
   Begin VB.Frame Frame4 
      Caption         =   "Video Mode"
      Height          =   1335
      Left            =   120
      TabIndex        =   29
      Top             =   240
      Width           =   1335
      Begin VB.OptionButton btnAcquire 
         Caption         =   "Stop"
         Height          =   375
         Index           =   1
         Left            =   240
         TabIndex        =   31
         Top             =   600
         Width           =   855
      End
      Begin VB.OptionButton btnAcquire 
         Caption         =   "Acquire"
         Height          =   375
         Index           =   0
         Left            =   240
         TabIndex        =   30
         Top             =   240
         Value           =   -1  'True
         Width           =   975
      End
   End
   Begin VB.CommandButton cmdReadBMP 
      Caption         =   "Read BMP"
      Height          =   255
      Index           =   0
      Left            =   3600
      TabIndex        =   28
      Top             =   2280
      Width           =   1095
   End
   Begin VB.CommandButton cmdWriteBMP 
      Caption         =   "Write BMP"
      Height          =   255
      Left            =   5040
      TabIndex        =   27
      Top             =   2280
      Width           =   1095
   End
   Begin VB.Frame Frame3 
      Caption         =   "Frame Size"
      Height          =   1335
      Left            =   3600
      TabIndex        =   23
      Top             =   240
      Width           =   1815
      Begin VB.OptionButton btnSize 
         Caption         =   "Full Size"
         Height          =   195
         Index           =   2
         Left            =   240
         TabIndex        =   26
         Top             =   960
         Value           =   -1  'True
         Width           =   1155
      End
      Begin VB.OptionButton btnSize 
         Caption         =   "Quarter Size"
         Height          =   195
         Index           =   1
         Left            =   240
         TabIndex        =   25
         Top             =   600
         Width           =   1275
      End
      Begin VB.OptionButton btnSize 
         Caption         =   "1/16 Size"
         Height          =   195
         Index           =   0
         Left            =   240
         TabIndex        =   24
         Top             =   240
         Width           =   1155
      End
   End
   Begin VB.Timer CamTimer 
      Interval        =   1000
      Left            =   2640
      Top             =   1680
   End
   Begin VB.TextBox ctlCamera 
      Enabled         =   0   'False
      Height          =   285
      Left            =   1440
      TabIndex        =   22
      Text            =   "Camera"
      Top             =   2280
      Width           =   1095
   End
   Begin VB.CommandButton btnReset 
      Caption         =   "Reset"
      Height          =   255
      Left            =   5040
      TabIndex        =   20
      Top             =   1920
      Width           =   1095
   End
   Begin VB.CommandButton btnGrab 
      Caption         =   "Grab One"
      Height          =   255
      Left            =   3600
      TabIndex        =   19
      Top             =   1920
      Width           =   1095
   End
   Begin VB.TextBox ctlBoard 
      Enabled         =   0   'False
      Height          =   285
      Left            =   1440
      TabIndex        =   17
      Text            =   "Board"
      Top             =   1920
      Width           =   1095
   End
   Begin VB.HScrollBar contrast 
      Height          =   255
      Left            =   4800
      Max             =   20
      TabIndex        =   12
      Top             =   3240
      Value           =   10
      Width           =   2055
   End
   Begin VB.HScrollBar Bright 
      Height          =   255
      Left            =   4800
      Max             =   50
      Min             =   -50
      TabIndex        =   11
      Top             =   2880
      Width           =   2055
   End
   Begin VB.HScrollBar Satur 
      Height          =   255
      Left            =   1080
      Max             =   20
      TabIndex        =   10
      Top             =   3240
      Value           =   10
      Width           =   2055
   End
   Begin VB.HScrollBar Hue 
      Height          =   255
      Left            =   1080
      Max             =   90
      Min             =   -90
      TabIndex        =   9
      Top             =   2880
      Width           =   2055
   End
   Begin VB.Frame Frame2 
      Caption         =   "Camera Input"
      Height          =   1335
      Left            =   5640
      TabIndex        =   4
      Top             =   240
      Width           =   1215
      Begin VB.OptionButton mux 
         Caption         =   "#3"
         Height          =   255
         Index           =   3
         Left            =   240
         TabIndex        =   8
         Top             =   960
         Width           =   735
      End
      Begin VB.OptionButton mux 
         Caption         =   "#2"
         Height          =   255
         Index           =   2
         Left            =   240
         TabIndex        =   7
         Top             =   720
         Width           =   735
      End
      Begin VB.OptionButton mux 
         Caption         =   "#1"
         Height          =   255
         Index           =   1
         Left            =   240
         TabIndex        =   6
         Top             =   480
         Width           =   615
      End
      Begin VB.OptionButton mux 
         Caption         =   "#0"
         Height          =   255
         Index           =   0
         Left            =   240
         TabIndex        =   5
         Top             =   240
         Value           =   -1  'True
         Width           =   735
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Input Mode"
      Height          =   1335
      Left            =   1680
      TabIndex        =   0
      Top             =   240
      Width           =   1695
      Begin VB.OptionButton btnOption 
         Caption         =   "S-Video"
         Height          =   255
         Index           =   2
         Left            =   240
         TabIndex        =   3
         Top             =   960
         Width           =   1095
      End
      Begin VB.OptionButton btnOption 
         Caption         =   "Composite"
         Height          =   375
         Index           =   1
         Left            =   240
         TabIndex        =   2
         Top             =   540
         Value           =   -1  'True
         Width           =   1095
      End
      Begin VB.OptionButton btnOption 
         Caption         =   "Monochrome"
         Height          =   255
         Index           =   0
         Left            =   240
         TabIndex        =   1
         Top             =   240
         Width           =   1335
      End
   End
   Begin MSComDlg.CommonDialog OpenDialog 
      Left            =   2880
      Top             =   2160
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.Label Label7 
      Caption         =   "Camera"
      Height          =   255
      Left            =   720
      TabIndex        =   21
      Top             =   2280
      Width           =   615
   End
   Begin VB.Label Label5 
      Caption         =   "PXC Series"
      Height          =   255
      Left            =   480
      TabIndex        =   18
      Top             =   1920
      Width           =   855
   End
   Begin VB.Label Label4 
      Caption         =   "Contrast"
      Height          =   255
      Left            =   3960
      TabIndex        =   16
      Top             =   3240
      Width           =   615
   End
   Begin VB.Label Label3 
      Caption         =   "Brightness"
      Height          =   255
      Left            =   3960
      TabIndex        =   15
      Top             =   2880
      Width           =   735
   End
   Begin VB.Label Label2 
      Caption         =   "Saturation"
      Height          =   255
      Left            =   240
      TabIndex        =   14
      Top             =   3240
      Width           =   735
   End
   Begin VB.Label Label1 
      Caption         =   "Hue"
      Height          =   255
      Left            =   240
      TabIndex        =   13
      Top             =   2880
      Width           =   615
   End
End
Attribute VB_Name = "frmControls"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub btnAcquire_Click(Index As Integer)
    Call SetAcquireMode(Index)
End Sub

Private Sub cmdReadBMP_Click(Index As Integer)
    OpenDialog.Filter = "BMP Files (*.BMP)|*.BMP"
    OpenDialog.ShowOpen
    If OpenDialog.filename <> "" Then
        ' load the frmBMP form
        Load frmBMP
        ' load the selected BMP file into a PictureBox
        frmBMP.picBMP.Picture = LoadPicture(OpenDialog.filename)
        frmBMP.Show
        'size the form to match the BMP image size
        frmBMP.width = frmBMP.picBMP.width + 100
        frmBMP.Height = frmBMP.picBMP.Height + 400
        'set the caption of the form to the file name
        frmBMP.Caption = OpenDialog.filename
    End If
End Sub

Private Sub cmdWriteBMP_Click()
    WRITEBMP = True
End Sub

Private Sub Form_Load()
    If (FRAME_OpenLibrary(0, 0) = 0) Then
        MsgBox ("FRAME_OpenLibrary FAILED")
        End
    End If
    If (PXC_OpenLibrary(0, 0) = 0) Then
        FRAME_CloseLibrary (0)
        MsgBox ("PXC_OpenLibrary FAILED")
        End
    End If
    
    fgh = PXC_AllocateFG(-1)
    If (fgh = 0) Then
        FRAME_CloseLibrary (0)
        PXC_CloseLibrary (0)
        MsgBox ("PXC_AllocateFG FAILED")
        End
    End If
    
    ' Allocate 2 buffers larger than any NTSC or CCIR image
    ' Use one for RGB color and one for monochrome
    frhRGB = PXC_AllocateBuffer(800, 600, PBITS_RGB24)
    If (frhRGB = 0) Then
        FRAME_CloseLibrary (0)
        PXC_CloseLibrary (0)
        PXC_FreeFG (fgh)
        MsgBox ("PXC_AllocateBuffer FAILED for frhRGB")
        End
    End If
    frhMono = PXC_AllocateBuffer(800, 600, PBITS_Y8)
    If (frhMono = 0) Then
        FRAME_CloseLibrary (0)
        PXC_CloseLibrary (0)
        PXC_FreeFG (fgh)
        PXC_FreeFrame (frhRGB)
        MsgBox ("PXC_AllocateBuffer FAILED for frhMono")
        End
    End If
    
    ' Allocate a variable to hold the currently active buffer
    frh = frhRGB ' default to the RGB buffer
    
    ' Put the board into a known state
    Call Reset_Board
End Sub
Private Sub Form_Unload(Cancel As Integer)
    Unload frmDisplay
    Unload frmBMP
    PXC_FreeFrame (frhRGB)
    PXC_FreeFrame (frhMono)
    PXC_FreeFG (fgh)
    FRAME_CloseLibrary (0)
    PXC_CloseLibrary (0)
End Sub
Private Sub Reset_Board()
'
' This routine is designed to either initialize or reset the board and the program.
' You should be able to call this routine after you have been running the program for
' some time and have made many modifications to parameters and this routine should
' put you back to where you were when the program began.
'
' This routine should be built and maintained such that it can be called at the
' beginning of the program right after AllocateFG() or later in response to a RESET.
'

    ' Unload the frmDisplay in case this is a reset
    Unload frmDisplay
    PXC_Reset (fgh)
    
    ' Set the GrabType to grab full frames
    GrabType = 0
    
    ' Set ImageSize to full frame to match the GrabType
    ImageSize = 2
    
    ' The ChangeSize variable is only TRUE after a size button is hit
    ChangeSize = True
    
    ' Enable all the camera buttons
    mux(0).Enabled = True
    mux(1).Enabled = True
    mux(2).Enabled = True
    mux(3).Enabled = True
    
    ' The initialization worked, so get the type of board
    BoardType = PXC_GetModelNumber(fgh)
    Select Case (BoardType)
        Case PXC200_LC
            ctlBoard.Text = "PXC200L"
        Case PXC200_LC_2
            ctlBoard.Text = "PXC200AL"
        Case PXC200_F
            ctlBoard.Text = "PXC200F"
        Case PXC200_F_2
            ctlBoard.Text = "PXC200AF"
        Case SP2019
            ctlBoard.Text = "SP2019"
            ' Disable 3 camera buttons, the SP2019 only has 1 input
            mux(1).Enabled = False
            mux(2).Enabled = False
            mux(3).Enabled = False
    End Select
    
    ' Set the Camera Input to match the board (should be 0)
    mux(PXC_GetCamera(fgh)).Value = True
    
    ' Set the slider controls to match the board
    Hue.Value = PXC_GetHue(fgh)
    Satur.Value = PXC_GetSaturation(fgh) * 10
    Bright.Value = PXC_GetBrightness(fgh) * 100
    contrast.Value = PXC_GetContrast(fgh) * 10
    
    ' Set the Frame Size button to full size
    btnSize(2).Value = True
    
    ' Set the Input Mode to composite
    btnOption(1).Value = True
    
    ' Set the video mode to acquire
    Call SetAcquireMode(0)
    
    VideoType = 3
    
    frmDisplay.Show
    
End Sub

Private Sub btnGrab_Click()
    GrabOne = True
    Call SetAcquireMode(1)
End Sub

Private Sub btnOption_Click(Index As Integer)
Static Svideo As Integer
    Select Case (Index)
        Case 0
            frh = frhMono
            ' Set the notch filter in case the user was in  s-video mode
            t = PXC_SetChromaControl(fgh, NOTCH_FILTER)
            ' If this is a PXC200L or PXC200AL and if we were in s-video, then
            ' assume the user wants the channel set back to 0, and enable all the
            ' cameras again
            If (BoardType = PXC200_LC) Or (BoardType = PXC200_LC_2) Then
                If (Svideo = True) Then
                    mux(0).Enabled = True
                    mux(1).Enabled = True
                    mux(2).Enabled = True
                    mux(3).Enabled = True
                    mux(0).Value = True
                End If
            End If
            Svideo = False
        Case 1
            frh = frhRGB
            ' Set the notch filter in case the user was in  s-video mode
            t = PXC_SetChromaControl(fgh, NOTCH_FILTER)
            ' If this is a PXC200L or PXC200AL and if we were in s-video, then
            ' assume the user wants the channel set back to 0, and enable all the
            ' cameras again
            If (BoardType = PXC200_LC) Or (BoardType = PXC200_LC_2) Then
                If (Svideo = True) Then
                    mux(0).Enabled = True
                    mux(1).Enabled = True
                    mux(2).Enabled = True
                    mux(3).Enabled = True
                    mux(0).Value = True
                End If
            End If
            Svideo = False
        Case 2
            Svideo = True
            frh = frhRGB
            t = PXC_SetChromaControl(fgh, Svideo)
            If (BoardType = PXC200_LC) Or (BoardType = PXC200_LC_2) Then
                t = PXC_SetCamera(fgh, 1, 0)
                t = PXC_GetCamera(fgh)
                mux(0).Enabled = False
                mux(1).Enabled = True
                mux(2).Enabled = False
                mux(3).Enabled = False
                mux(t).Value = True
            End If
    End Select
End Sub

Private Sub btnReset_Click()
    Call Reset_Board
End Sub

Private Sub btnSize_Click(Index As Integer)
    ' Set the global ImageSize
    ImageSize = Index
    Select Case (ImageSize)
        Case 0
            ' Grab only a single field on small sizes and start on the same
            ' field each time to avoid image bounce
            GrabType = SINGLE_FLD + FIELD0
        Case 1
            ' Grab only a single field on small sizes and start on the same
            ' field each time to avoid image bounce
            GrabType = SINGLE_FLD + FIELD0
        Case 2
            GrabType = 0
    End Select
    Call VideoFormatChange
End Sub

Private Sub CamTimer_Timer()
    ' Check the video type every second and update the
    ' Camera control ctlCamera.
    '
    ' It may take up to 2 seconds for the LC board to detect
    ' the video format correctly. The F board is more like 1/2 second.
    If (VideoType <> PXC_VideoType(fgh)) Then
        VideoType = PXC_VideoType(fgh)
        Call VideoFormatChange
        Select Case (VideoType)
            Case 0
                ctlCamera.Text = "No Video"
            Case 1
                ctlCamera.Text = "NTSC"
            Case 2
                ctlCamera.Text = "CCIR/PAL"
            Case Else
                ctlCamera.Text = "Unknown"
        End Select
    End If
End Sub

Private Sub contrast_Change()
    t = PXC_SetContrast(fgh, contrast.Value / 10, 0)
End Sub

Private Sub Hue_Change()
    t = PXC_SetHue(fgh, Hue.Value, 0)
End Sub

Private Sub Bright_Change()
    t = PXC_SetBrightness(fgh, Bright.Value / 100, 0)
End Sub

Private Sub Satur_Change()
    t = PXC_SetSaturation(fgh, Satur.Value / 10, 0)
End Sub

Private Sub mux_Click(Index As Integer)
    t = PXC_SetCamera(fgh, Index, 0)
End Sub


