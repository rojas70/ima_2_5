VERSION 5.00
Begin VB.UserControl Bevel 
   Alignable       =   -1  'True
   ClientHeight    =   3600
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4800
   ScaleHeight     =   240
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   320
   Begin VB.Line Line2 
      X1              =   1
      X2              =   1
      Y1              =   0
      Y2              =   11240
   End
   Begin VB.Line Line1 
      BorderColor     =   &H80000010&
      X1              =   0
      X2              =   0
      Y1              =   0
      Y2              =   11240
   End
End
Attribute VB_Name = "Bevel"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Public Enum BevelSides
    bsLeft = 0
    bsRight = 1
    bsTop = 2
    bsDown = 3
End Enum
    
Public Enum BevelWeights
    bwHeavy = 0
    bwLight = 1
End Enum
    
Dim m_Side      As BevelSides
Dim m_Weight    As BevelWeights
    
Private Sub UserControl_Initialize()
    UserControl_Resize
End Sub

Private Sub UserControl_ReadProperties(PropBag As PropertyBag)
    m_Side = PropBag.ReadProperty("Sides", 0)
    m_Weight = PropBag.ReadProperty("Weight", 0)
    UserControl_Resize
End Sub

Private Sub UserControl_Resize()
    Dim W As Integer
    Dim H As Integer
    W = UserControl.ScaleWidth
    H = UserControl.ScaleHeight
    
    Select Case m_Side
        Case 0:
            L1X1 = 0: L1Y1 = 0: L1X2 = 0: L1Y2 = H
            L2X1 = 1: L2Y1 = 0: L2X2 = 1: L2Y2 = H
            Line1.BorderColor = QBColor(8)
            Line2.BorderColor = QBColor(0)
            
        Case 1:
            L1X1 = W - 1: L1Y1 = 0: L1X2 = W - 1: L1Y2 = H
            L2X1 = W - 2: L2Y1 = 0: L2X2 = W - 2: L2Y2 = H
            Line1.BorderColor = QBColor(15)
            Line2.BorderColor = QBColor(7)
        
        Case 2:
            L1X1 = 0: L1Y1 = 0: L1X2 = W: L1Y2 = 0
            L2X1 = 0: L2Y1 = 1: L2X2 = W: L2Y2 = 1
            Line1.BorderColor = QBColor(0)
            Line2.BorderColor = QBColor(8)
        Case 3:
            L1X1 = 0: L1Y1 = H - 2: L1X2 = W: L1Y2 = H - 2
            L2X1 = 0: L2Y1 = H - 1: L2X2 = W: L2Y2 = H - 1
            Line1.BorderColor = QBColor(7)
            Line2.BorderColor = QBColor(15)
    End Select
    
    If m_Weight = bwLight Then
        Line1.BorderColor = QBColor(8)
        Line2.BorderColor = QBColor(15)
    End If
    
    Line1.X1 = L1X1: Line1.Y1 = L1Y1
    Line1.X2 = L1X2: Line1.Y2 = L1Y2
    Line2.X1 = L2X1: Line2.Y1 = L2Y1
    Line2.X2 = L2X2: Line2.Y2 = L2Y2
    
End Sub

Private Sub UserControl_WriteProperties(PropBag As PropertyBag)
    Call PropBag.WriteProperty("Sides", m_Side, 0)
    Call PropBag.WriteProperty("Weight", m_Weight, 0)
End Sub

Public Property Get BevelSide() As BevelSides
    BevelSide = m_Side
End Property

Public Property Let BevelSide(Side As BevelSides)
    m_Side = Side
    UserControl_Resize
End Property

Public Property Get BevelWeight() As BevelWeights
    BevelWeight = m_Weight
End Property

Public Property Let BevelWeight(Weight As BevelWeights)
    m_Weight = Weight
    UserControl_Resize
End Property


