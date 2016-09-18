VERSION 5.00
Object = "{3B7C8863-D78F-101B-B9B5-04021C009402}#1.2#0"; "RICHTX32.OCX"
Begin VB.UserControl VSManager 
   ClientHeight    =   3240
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   3705
   ScaleHeight     =   3240
   ScaleWidth      =   3705
   Begin RichTextLib.RichTextBox RTB 
      Height          =   2535
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3495
      _ExtentX        =   6165
      _ExtentY        =   4471
      _Version        =   393217
      Enabled         =   -1  'True
      HideSelection   =   0   'False
      ReadOnly        =   -1  'True
      ScrollBars      =   1
      Appearance      =   0
      TextRTF         =   $"IMA2_Manager_VS.ctx":0000
   End
End
Attribute VB_Name = "VSManager"
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
    Dim VS As IVectorSignal
    Dim I As Integer
    Dim J As Integer
    Dim CurVec As Integer
    Dim SelStart As Integer
    Dim SelEnd As Integer
    Dim LI As ListItem
    
    If C Is Nothing Then Exit Sub
    
    RTB.TextRTF = ""
    Set VS = C
    
    Data = VS.UpdateManager("IVectorSignal")
    CurVec = Data(2)
    Txt = "VecLen: " & Data(0) & ", SigLen: " & Data(1) & ", CurVec: " & CurVec & Chr(13)
    'Call List1.AddItem("VecLen: " & Data(0) & ", SigLen: " & Data(1), 0)
    
    For I = LBound(Data(3), 1) To UBound(Data(3), 1)
        'Txt = ""
        If CurVec = I Then SelStart = Len(Txt)
        For J = LBound(Data(3), 2) To UBound(Data(3), 2)
            Txt = Txt & " " & Format(Data(3)(I, J), "##0.00")
        Next J
        Txt = Txt & Chr(13)
        If CurVec = I Then SelEnd = Len(Txt)
        'List1.AddItem Txt, I + 1
    Next I
    RTB.TextRTF = Txt
    RTB.SelStart = SelStart
    RTB.SelLength = SelEnd - SelStart
End Sub



Private Sub RTB_Click()
'    If C Is Nothing Then
'        Dim L As ILocator
'        Set L = CreateObject("IMA2_Locator.Locator")
'        Set C = L.Locate("\\sally\RightArm\DesiredPhysicalAngles")
'    End If
'    Call IManager_Update
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
