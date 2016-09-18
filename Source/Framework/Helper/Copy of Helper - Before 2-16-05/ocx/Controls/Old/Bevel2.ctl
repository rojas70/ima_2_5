VERSION 5.00
Begin VB.UserControl Bevel2 
   Alignable       =   -1  'True
   CanGetFocus     =   0   'False
   ClientHeight    =   3600
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4800
   HasDC           =   0   'False
   ScaleHeight     =   240
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   320
   Begin VB.Line Line1 
      BorderColor     =   &H80000010&
      X1              =   0
      X2              =   0
      Y1              =   0
      Y2              =   11240
   End
   Begin VB.Line Line2 
      BorderColor     =   &H80000014&
      X1              =   1
      X2              =   1
      Y1              =   0
      Y2              =   11240
   End
End
Attribute VB_Name = "Bevel2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
'******************************************************************************************************************************
' Public Enumerations
'******************************************************************************************************************************
    Public Enum BevelAlignment
        baCenter = 0
        baLeftTop = 1
        baRightBottom = 2
    End Enum
        
    Public Enum BevelDirection
        bdHorizontal = 0
        bdVertical = 1
    End Enum
        
'******************************************************************************************************************************
' Private Member Variables
'******************************************************************************************************************************

    Dim m_Alignment As BevelAlignment
    Dim m_Direction As BevelDirection
    Dim m_AutoSize  As Boolean

'******************************************************************************************************************************
' Public Interface
'******************************************************************************************************************************
    
    Public Property Get AutoSize() As Boolean
        AutoSize = m_AutoSize
    End Property
    
    Public Property Let AutoSize(NV As Boolean)
        If NV Then
            If m_Direction = bdHorizontal Then
                UserControl.Extender.Height = 2
            Else
                UserControl.Extender.Width = 2
            End If
        End If
        m_AutoSize = NV
    End Property
    
    Public Property Get BackStyle() As BackStyleConstants
        BackStyle = UserControl.BackStyle
    End Property
    
    Public Property Let BackStyle(NV As BackStyleConstants)
        UserControl.BackStyle = NV
    End Property
    
    Public Property Get BackColor() As OLE_COLOR
        BackColor = UserControl.BackColor
    End Property
    
    Public Property Let BackColor(NV As OLE_COLOR)
        UserControl.BackColor = NV
    End Property
    
    Public Property Get Alignment() As BevelAlignment
        Alignment = m_Alignment
    End Property
    
    Public Property Let Alignment(NV As BevelAlignment)
        m_Alignment = NV
        UpdateLines
    End Property

    Public Property Get Direction() As BevelDirection
        Direction = m_Direction
    End Property

    Public Property Let Direction(NV As BevelDirection)
        m_Direction = NV
        UpdateLines
    End Property

    Public Property Get ColorA() As OLE_COLOR
Attribute ColorA.VB_ProcData.VB_Invoke_Property = ";Appearance"
Attribute ColorA.VB_UserMemId = -501
        ColorA = Line1.BorderColor
    End Property
    
    Public Property Let ColorA(NV As OLE_COLOR)
        Line1.BorderColor = NV
    End Property
    
    Public Property Get ColorB() As OLE_COLOR
Attribute ColorB.VB_ProcData.VB_Invoke_Property = ";Appearance"
Attribute ColorB.VB_UserMemId = -513
        ColorB = Line2.BorderColor
    End Property
    
    Public Property Let ColorB(NV As OLE_COLOR)
        Line2.BorderColor = NV
    End Property

'******************************************************************************************************************************
' Usercontrol Events
'******************************************************************************************************************************
        
    Private Sub UserControl_Initialize()
    End Sub
    
    Private Sub UserControl_InitProperties()
  '      m_Side = bsLeft
   '     m_Weight = bwLight
    End Sub

    Private Sub UserControl_ReadProperties(PropBag As PropertyBag)
        m_Alignment = PropBag.ReadProperty("A", 0)
        m_Direction = PropBag.ReadProperty("D", 0)
        UserControl.BackStyle = PropBag.ReadProperty("BS", 0)
        Line1.BorderColor = PropBag.ReadProperty("C1", QBColor(8))
        Line2.BorderColor = PropBag.ReadProperty("C2", QBColor(15))
    End Sub
    
    Private Sub UserControl_Resize()
        If m_AutoSize Then m_AutoSize = False
        UpdateLines
    End Sub

    Private Sub UserControl_WriteProperties(PropBag As PropertyBag)
        Call PropBag.WriteProperty("BS", UserControl.BackStyle, 0)
        Call PropBag.WriteProperty("A", m_Alignment, 0)
        Call PropBag.WriteProperty("D", m_Direction, 0)
        Call PropBag.WriteProperty("C1", Line1.BorderColor, QBColor(8))
        Call PropBag.WriteProperty("C2", Line2.BorderColor, QBColor(15))
    End Sub
    
    Private Sub UpdateLines()
    
        Dim W As Integer
        Dim H As Integer
        
        W = UserControl.ScaleWidth
        H = UserControl.ScaleHeight
        
        If m_Direction = bdHorizontal Then
        
            Line1.X1 = 0: Line1.X2 = 10000
            Line2.X1 = 0: Line2.X2 = 10000
        
            If m_Alignment = baLeftTop Then
                Line1.Y1 = 0: Line1.Y2 = Line1.Y1
                Line2.Y1 = 1: Line2.Y2 = Line2.Y1
            ElseIf m_Alignment = baCenter Then
                Line1.Y1 = Fix(H / 2) - 1: Line1.Y2 = Line1.Y1
                Line2.Y1 = Fix(H / 2) - 0: Line2.Y2 = Line2.Y1
            Else
                Line1.Y1 = H - 2: Line1.Y2 = Line1.Y1
                Line2.Y1 = H - 1: Line2.Y2 = Line2.Y1
            End If
        
        Else
        
            Line1.Y1 = 0: Line1.Y2 = 10000
            Line2.Y1 = 0: Line2.Y2 = 10000
            
            If m_Alignment = baLeftTop Then
                Line1.X1 = 0: Line1.X2 = Line1.X1
                Line2.X1 = 1: Line2.X2 = Line2.X1
            ElseIf m_Alignment = baCenter Then
                Line1.X1 = Fix(W / 2) - 1: Line1.X2 = Line1.X1
                Line2.X1 = Fix(W / 2) - 0: Line2.X2 = Line2.X1
            Else
                Line1.X1 = W - 2: Line1.X2 = Line1.X1
                Line2.X1 = W - 1: Line2.X2 = Line2.X1
            End If
        
        End If
    
    End Sub
