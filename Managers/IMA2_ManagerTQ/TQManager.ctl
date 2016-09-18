VERSION 5.00
Object = "{3B7C8863-D78F-101B-B9B5-04021C009402}#1.2#0"; "RICHTX32.OCX"
Begin VB.UserControl TQManager 
   ClientHeight    =   2880
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   3840
   ScaleHeight     =   2880
   ScaleWidth      =   3840
   Begin RichTextLib.RichTextBox RTB 
      Height          =   2535
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3495
      _ExtentX        =   6165
      _ExtentY        =   4471
      _Version        =   393217
      HideSelection   =   0   'False
      ReadOnly        =   -1  'True
      ScrollBars      =   1
      Appearance      =   0
      TextRTF         =   $"TQManager.ctx":0000
   End
End
Attribute VB_Name = "TQManager"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Implements IManager

Dim C As IComponent
Private Property Let IManager_Component(ByVal Cmp As IMA2.IComponent)
    Set C = Cmp
End Property
Private Property Get IManager_Component() As IMA2.IComponent
    Set IManager_Component = C
End Property
Private Sub IManager_Update()
    Dim Data As Variant
    Dim Txt As String
    Dim TQ As ITextQueue
    Dim I As Integer
    Dim J As Integer
    Dim CurText As String
    Dim Selstart As Integer
    Dim SelEnd As Integer
    Dim LI As ListItem
    
    If C Is Nothing Then Exit Sub
    
    RTB.TextRTF = ""
    Set TQ = C
    
    Data = TQ.UpdateManager("ITextQueue")
    CurText = Data(1)
    
    Txt = "QueueLength: " & Data(0) & Chr(13)
    
    For I = LBound(Data(1), 1) To UBound(Data(1), 1)
        If CurText = I Then Selstart = Len(Txt)
            Txt = Txt & " " & Data(1)(I)
        Txt = Txt & Chr(13)
        If CurText = I Then SelEnd = Len(Txt)
    Next I
    
    RTB.TextRTF = Txt
    RTB.Selstart = Selstart
    RTB.SelLength = SelEnd - Selstart
End Sub


Private Sub UserControl_Initialize()
    RTB.TextRTF = ""
    RTB.RightMargin = 65535 'This turns off word wrap
End Sub

Private Sub UserControl_Resize()
    RTB.Top = 0
    RTB.Left = 0
    RTB.Width = UserControl.Width
    RTB.Height = UserControl.Height
End Sub

