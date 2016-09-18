VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "comdlg32.ocx"
Begin VB.UserControl uscImageRep 
   ClientHeight    =   4560
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4815
   ScaleHeight     =   304
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   321
   Begin VB.TextBox Text1 
      Height          =   285
      Left            =   1440
      TabIndex        =   6
      Text            =   "\\Ninja\img1"
      Top             =   960
      Width           =   2895
   End
   Begin VB.CommandButton cmdClose 
      Caption         =   "&Save Image"
      Height          =   375
      Left            =   3000
      TabIndex        =   4
      Top             =   480
      Width           =   1335
   End
   Begin VB.CommandButton cmfFileOpen 
      Caption         =   "&Open from file"
      Height          =   375
      Left            =   120
      TabIndex        =   3
      Top             =   480
      Width           =   1335
   End
   Begin VB.CommandButton cmdLoadImage 
      Caption         =   "&Load Image"
      Height          =   375
      Left            =   1560
      TabIndex        =   2
      Top             =   480
      Width           =   1335
   End
   Begin VB.PictureBox Picture1 
      AutoRedraw      =   -1  'True
      AutoSize        =   -1  'True
      Height          =   2895
      Left            =   120
      ScaleHeight     =   2835
      ScaleWidth      =   4515
      TabIndex        =   1
      Top             =   1560
      Width           =   4575
   End
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   4440
      Top             =   600
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.Frame Frame1 
      Height          =   135
      Left            =   120
      TabIndex        =   0
      Top             =   1320
      Width           =   4215
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      Caption         =   "Image Representation Manager"
      Height          =   195
      Left            =   1200
      TabIndex        =   7
      Top             =   120
      Width           =   2235
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "Load Image Path:"
      Height          =   195
      Left            =   120
      TabIndex        =   5
      Top             =   960
      Width           =   1260
   End
   Begin VB.Menu mnuCmp 
      Caption         =   "&Component"
      Begin VB.Menu mnuCmp_Sep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuCmp_Get 
         Caption         =   "&Get Props"
         Shortcut        =   {F5}
      End
      Begin VB.Menu mnuCmp_Set 
         Caption         =   "&Set Props"
         Shortcut        =   {F6}
      End
   End
End
Attribute VB_Name = "uscImageRep"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
'********************************************************************************************
' Class:        Project1.Manager1
' Author:       Roberto Olivares (olivarre@vuse.vanderbilt.edu)
' Last update:  (4/12/00)
'
' Description:  This is a sample IMA2 manager
'********************************************************************************************
    
    Option Explicit             'Code like a man
    
    Implements IManager         'Now implement the IManager interface
    
    Dim m_cmp_save As cImageRep
    Dim m_cmp_load As cImageRep
    Dim m_AL As ILocator

Private Sub cmdClose_Click()
Dim PictureName$
    CommonDialog1.InitDir = App.Path
    CommonDialog1.Filter = "Images(*.bmp,*.gif,*.jpg,*.dib)|*.BMP;*.GIP;*.JPG;*.DIB|All Files|*.*"
    CommonDialog1.Action = 2
    PictureName = CommonDialog1.FileName
    SavePicture Picture1, PictureName
    'Picture1.Height = 1000
    'Picture1.Width = 1000
End Sub

Private Sub cmdLoadImage_Click()
   Dim i&, j&, x&, y&
   Dim tmpImage() As Byte
   Dim tmpCaption$
   On Error GoTo errorhandle
   Set m_AL = CreateObject("Locator2000.Locator")
   Set m_cmp_load = m_AL.Locate(Text1.Text)
   'Frm2.Visible = True
   'Frm1.Visible = False
   tmpImage = m_cmp_load.getData(0)
   'Form3.Show
   'Form3.Height = 5500
   'Form3.Width = 2500
   'Picture1.ScaleMode = 3
   'Picture1.AutoSize = False
   Picture1.Height = m_cmp_load.ImageHeight + 3
   Picture1.Width = m_cmp_load.ImageWidth + 3
   '.Width = Form3.ScaleX(Form3.Picture1.Width + 8, 3, 1)
   'Form3.Height = Form3.ScaleY(Form3.Picture1.Height + 26, 3, 1)
   'Form3.Width = Form3.Picture1.Width + 6
   'Form3.Height = Form3.Picture1.Height + 30
   'Form3.ScaleMode = 3
   'Form3.Refresh
   'tmpCaption = Frm1.Caption
   y = m_cmp_load.ImageHeight
   For i = 1 To m_cmp_load.ImageHeight
    For j = 1 To m_cmp_load.ImageWidth
       Picture1.PSet (j, i), RGB(tmpImage(0, j, i), tmpImage(1, j, i), tmpImage(2, j, i))
    Next j
    'Frm1.Caption = tmpCaption + " " + CStr(CInt(((i + 1) / (y)) * 100)) + "%"
   Next i
   'Frm1.Caption = tmpCaption
   Exit Sub
errorhandle:
    MsgBox "Could not complete the operation. Abort"
End Sub

Private Sub cmfFileOpen_Click()
Dim PictureName As String
Dim Pixel As Long
Dim i&, j&, x&, y&
Dim PixelData() As Byte
Dim tmpCaption$
'On Error GoTo errorhandle
   CommonDialog1.InitDir = App.Path
   CommonDialog1.Filter = "Images(*.bmp,*.gif,*.jpg,*.dib)|*.BMP;*.GIP;*.JPG;*.DIB|All Files|*.*"
   CommonDialog1.Action = 1
   PictureName = CommonDialog1.FileName
   If PictureName = "" Then
    Exit Sub
   End If
   Picture1.Picture = LoadPicture(PictureName)
   Picture1.ScaleMode = 3
   x = Picture1.ScaleWidth
   y = Picture1.ScaleHeight
 '  If x > m_comp.Widths Or y > m_comp.Height Then
        'MsgBox "Image is too large. Please send Width and Height and try again"
 '       x = 600
 '       y = 800
        m_cmp_save.ImageWidth = x
        m_cmp_save.ImageHeight = y
        Call m_cmp_save.DoInitial
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
   'tmpCaption = Frame1.Caption
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
    'Frame1.Caption = tmpCaption + " " + CStr(CInt(((i + 1) / (y)) * 100)) + "%"
   Next i
   'Frame1.Caption = tmpCaption
   'Form2.Show
   'Form2.Refresh
   Call m_cmp_save.putData(0, PixelData)
   Erase PixelData
   Exit Sub
errorhandle:
    MsgBox "Could not complete the operation. Abort"
End Sub

'********************************************************************************************
' Usercontrol Events
'********************************************************************************************

    Private Sub UserControl_Initialize()
        'For debugging **ONLY** you should show the AB2000 window.
        '
        'Ex:        Call ShowAgent
    End Sub
    
    Private Sub UserControl_MouseUp(Button As Integer, Shift As Integer, x As Single, y As Single)
         'You should popup a menu when someone right-clicks.
        '
        ' Ex:   If Button And vbRightButton Then PopupMenu mnuCmp
    End Sub

    Public Sub OnGetComponentData()
        'Put code to update the UI from the component here.
        '
        '       Text1.Text = m_Cmp.MyString
    End Sub

    Public Sub OnPutComponentData()
        'Put code to update the component from the UI here.
        '
        'Ex:    m_Cmp.MyString = Text1.Text
    End Sub

'********************************************************************************************
' Menu Events
'********************************************************************************************

    Private Sub mnuCmp_Get_Click()
        If m_cmp_save Is Nothing Then Exit Sub
        Call OnGetComponentData
    End Sub
    
    Private Sub mnuCmp_Set_Click()
        If m_cmp_save Is Nothing Then Exit Sub
        Call OnPutComponentData
    End Sub

'********************************************************************************************
' IManager Implementation
'********************************************************************************************

    'Called by AgentBuilder when a manager is attached to a component.
    Private Sub IManager_SetComponent(C As IMA2.IComponent)
        
        If (C Is Nothing) Then                  '1) Check if C is nothing
            Set m_cmp_save = Nothing                 '   Unbind to the component
            mnuCmp.Enabled = False              '   Update UI
            Exit Sub                            '   Exit
       ' ElseIf Not (TypeOf C Is Engine) Then    '2) Check if TypeOf C is supported.
       '     Set m_cmp = Nothing                 '   Unbind to the component
       '     mnuCmp.Enabled = False              '   Update UI
       '     Exit Sub                            '   Exit
        End If
    
'        call S
        Set m_cmp_save = C                           '3) Set the member variable pointer
        'Call mnuGet_Click                       '   and update the display.
    
    End Sub
    
    'Called by AgentBuilder when a manager is attached to a component.
    Private Sub IManager_Update(Optional Flags As Variant)
        'If m_Engine Is Nothing Then Exit Sub
        'Call mnuGet_Click
    End Sub
