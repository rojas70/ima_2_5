VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "ButtonWrapper"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

    Dim m_Button As CommandButton
    
    Friend Property Set Button(NV As CommandButton)
        Set m_Button = NV
    End Property
    
    Friend Property Get Button() As CommandButton
        Set Button = m_Button
    End Property
    
    Public Property Get Caption() As String
        Caption = m_Button.Caption
    End Property
    
    Public Property Let Caption(NV As String)
        m_Button.Caption = NV
    End Property
    
    Public Property Get Enabled() As Boolean
        Enabled = m_Button.Enabled
    End Property
    
    Public Property Let Enabled(NV As Boolean)
        m_Button.Enabled = NV
    End Property
    
    Public Property Get Width() As Single
        Width = m_Button.Width
    End Property

    Public Property Let Width(NV As Single)
        m_Button.Width = NV
    End Property

    Public Property Get Height() As Single
        Height = m_Button.Height
    End Property

    Public Property Let Height(NV As Single)
        m_Button.Height = NV
    End Property

