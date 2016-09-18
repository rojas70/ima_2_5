Attribute VB_Name = "global_data"
Global fgh As Long ' frame grabber handle
Global frhRGB As Long ' handle for RGB buffer
Global frhMono As Long ' handle for mono buffer
Global frh As Long ' current frame handle
Global ImageWidth As Long
Global ImageHeight As Long
Global x_res As Long
Global y_res As Long

' BoardType keeps the type of PXC200
Global BoardType As Integer

' VideoType keeps the current video
Global VideoType As Integer

' ImageSize keeps the size of the image
Global ImageSize As Integer

Global Acquiring As Integer ' TRUE if acquiring video
Global GrabOne As Integer  ' TRUE if we need to grab one frame
Global GrabType As Integer  ' type of grab (field or frame)
Global ChangeSize As Integer ' TRUE if the size of the window is to be changed
Global WRITEBMP

Public frhBMP As Long

Sub VideoFormatChange()
    
    ' Set the image sizes to maximum before making them smaller
    Select Case (VideoType)
        Case 0
            ImageWidth = 640
            ImageHeight = 480
        Case 1
            ImageWidth = 640
            ImageHeight = 480
        Case 2
            ImageWidth = 768
            ImageHeight = 570
        Case Else
            ImageWidth = 640
            ImageHeight = 480
    End Select
    
    ' Now set the image sizes to match the window
    Select Case (ImageSize)
        Case 0 ' sixteenth size
            ImageWidth = ImageWidth / 4
            ImageHeight = ImageHeight / 4
            x_res = ImageWidth
            y_res = ImageHeight * 2 ' double y_res on small values
        Case 1 ' quarter size
            ImageWidth = ImageWidth / 2
            ImageHeight = ImageHeight / 2
            x_res = ImageWidth
            y_res = ImageHeight * 2 ' double y_res on small values
       Case 2 ' full size
            x_res = ImageWidth
            y_res = ImageHeight
    End Select
    
    ChangeSize = True
End Sub
Sub SetAcquireMode(Index As Integer)
    Select Case (Index)
        Case 0
            Acquiring = True
            frmControls!btnAcquire(0).Value = True
        Case 1
            Acquiring = False
            frmControls!btnAcquire(1).Value = True
    End Select
End Sub
