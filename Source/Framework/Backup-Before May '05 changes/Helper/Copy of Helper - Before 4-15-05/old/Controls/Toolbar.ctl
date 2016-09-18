VERSION 5.00
Begin VB.UserControl Toolbar 
   Alignable       =   -1  'True
   ClientHeight    =   420
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4800
   ControlContainer=   -1  'True
   ScaleHeight     =   28
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   320
   Begin VB.Line Line4 
      BorderColor     =   &H80000010&
      X1              =   0
      X2              =   10000
      Y1              =   24
      Y2              =   24
   End
   Begin VB.Line Line3 
      BorderColor     =   &H80000015&
      X1              =   0
      X2              =   10000
      Y1              =   25
      Y2              =   25
   End
   Begin VB.Line Line2 
      BorderColor     =   &H80000014&
      X1              =   0
      X2              =   10000
      Y1              =   1
      Y2              =   1
   End
   Begin VB.Line Line1 
      BorderColor     =   &H80000010&
      X1              =   0
      X2              =   10000
      Y1              =   0
      Y2              =   0
   End
End
Attribute VB_Name = "Toolbar"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Private Sub UserControl_Resize()

    Line3.Y1 = UserControl.ScaleHeight - 1
    Line3.Y2 = UserControl.ScaleHeight - 1
    Line4.Y1 = UserControl.ScaleHeight - 2
    Line4.Y2 = UserControl.ScaleHeight - 2
    

End Sub
