VERSION 5.00
Object = "{EAB22AC0-30C1-11CF-A7EB-0000C05BAE0B}#1.1#0"; "shdocvw.dll"
Begin VB.UserControl WebBrowser 
   ClientHeight    =   3600
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   7590
   ScaleHeight     =   3600
   ScaleWidth      =   7590
   Begin VB.TextBox txtURL 
      Height          =   285
      Left            =   0
      TabIndex        =   1
      Text            =   "http://www.yahoo.com"
      Top             =   0
      Width           =   5895
   End
   Begin SHDocVwCtl.WebBrowser wb 
      Height          =   2535
      Left            =   0
      TabIndex        =   0
      Top             =   360
      Width           =   7815
      ExtentX         =   13785
      ExtentY         =   4471
      ViewMode        =   0
      Offline         =   0
      Silent          =   0
      RegisterAsBrowser=   0
      RegisterAsDropTarget=   1
      AutoArrange     =   0   'False
      NoClientEdge    =   0   'False
      AlignLeft       =   0   'False
      NoWebView       =   0   'False
      HideFileNames   =   0   'False
      SingleClick     =   0   'False
      SingleSelection =   0   'False
      NoFolders       =   0   'False
      Transparent     =   0   'False
      ViewID          =   "{0057D0E0-3573-11CF-AE69-08002B2E1262}"
      Location        =   ""
   End
End
Attribute VB_Name = "WebBrowser"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Private Sub txtURL_KeyUp(KeyCode As Integer, Shift As Integer)

    If KeyCode = vbKeyReturn Then
        If Shift And vbCtrlMask Then txtURL = "http://www." + txtURL + ".com"
        wb.Navigate txtURL
        wb.SetFocus
    End If

End Sub

Private Sub UserControl_ReadProperties(PropBag As PropertyBag)
    URL = PropBag.ReadProperty("URL", "http://www.yahoo.com")
End Sub

Private Sub UserControl_Resize()
    wb.Move wb.Left, wb.Top, UserControl.ScaleWidth, UserControl.ScaleHeight - wb.Top
    txtURL.Width = UserControl.ScaleWidth
End Sub

Public Property Get URL() As String
    URL = wb.LocationURL
End Property

Public Property Let URL(NV As String)
    wb.Navigate NV
    txtURL = NV
End Property

Private Sub UserControl_WriteProperties(PropBag As PropertyBag)
    PropBag.WriteProperty "URL", txtURL.Text, "http://www.yahoo.com"
End Sub
