VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form frmFileOld 
   Caption         =   "Form1"
   ClientHeight    =   9015
   ClientLeft      =   60
   ClientTop       =   630
   ClientWidth     =   11070
   LinkTopic       =   "Form1"
   ScaleHeight     =   601
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   738
   Begin MSComctlLib.Slider sldBottom 
      Height          =   375
      Left            =   240
      TabIndex        =   3
      Top             =   8640
      Width           =   10695
      _ExtentX        =   18865
      _ExtentY        =   661
      _Version        =   393216
      Max             =   1000
      TickStyle       =   3
      TickFrequency   =   10000
   End
   Begin MSComctlLib.Slider sldLeft 
      Height          =   8535
      Left            =   0
      TabIndex        =   2
      Top             =   0
      Width           =   375
      _ExtentX        =   661
      _ExtentY        =   15055
      _Version        =   393216
      Orientation     =   1
      TickStyle       =   3
   End
   Begin VB.PictureBox pic 
      BackColor       =   &H8000000C&
      BorderStyle     =   0  'None
      Height          =   6015
      Left            =   480
      ScaleHeight     =   401
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   585
      TabIndex        =   0
      Top             =   0
      Width           =   8775
      Begin ManagerBook.SimpleWindow swn 
         Height          =   3000
         Index           =   0
         Left            =   720
         TabIndex        =   1
         Top             =   840
         Width           =   1935
         _ExtentX        =   3413
         _ExtentY        =   5292
         MinVisible      =   0   'False
         MinString       =   "+"
      End
   End
   Begin VB.Menu mnuSTD 
      Caption         =   "Std"
   End
   Begin VB.Menu mnuPage 
      Caption         =   "Page"
      Visible         =   0   'False
      Begin VB.Menu mnuPage_New 
         Caption         =   "New Page..."
      End
      Begin VB.Menu mnuPage_Sep0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuPage_Rename 
         Caption         =   "Rename Page..."
      End
      Begin VB.Menu mnuPage_Sep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuPage_Delete 
         Caption         =   "Delete Page"
      End
   End
End
Attribute VB_Name = "frmFileOld"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_Load()

    Dim AL As ILocator
    Dim Paths() As String
    Dim I As Integer
    Dim P As String
    Dim L As Integer
    Dim MaxLevel As Integer
    Dim S As SimpleWindow
    Dim SO As Object
    Dim Swns As New Collection
    ReDim Levels(0 To 100) As New Collection
    
    Set AL = GetLocator()
    Paths = AL.Components
    Call QuickSortStrings(Paths)
    
    For I = LBound(Paths) To UBound(Paths)
    
        P = Paths(I)
        L = PathLevel(P)
        
        If L > MaxLevel Then MaxLevel = L
        
        If I > 0 Then Load swn(I)
        Set S = swn(I)
        
        Call Levels(L).Add(S, P)
        
        
        With swn(I)
            .Visible = True
            .Top = L * 100
            .Height = 50
        End With
        
        With S
            .Index = I
            .Caption = NameFromPath(P)
            .Collapsed = True
        End With
    
    Next I
    
    
    For I = 1 To MaxLevel
        L = 0
        For Each S In Levels(I)
            swn(S.Index).Left = L * 150
            L = L + 1
        Next
    Next
    
    ReDim Preserve Levels(0 To MaxLevel)

    swn(0).Visible = True

End Sub

Private Sub Form_Resize()
    
    sldLeft.Height = Me.ScaleHeight - sldBottom.Height
    sldBottom.Width = Me.ScaleWidth - sldBottom.Left
    sldBottom.Top = sldLeft.Height
    pic.Move sldLeft.Width, 0, Me.ScaleWidth - sldLeft.Width, Me.ScaleHeight - sldBottom.Height
    
End Sub

Private Sub swn_LabelDblClick(Index As Integer)
    swn(Index).Collapsed = Not swn(Index).Collapsed
End Sub


