VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CEventQueue"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Attribute VB_Ext_KEY = "SavedWithClassBuilder6" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
Option Explicit

    Dim m_EC As New Collection

    Public Sub Add(EType&, Path$, State As Boolean)
        
        Dim CE As New CEvent
        
        With CE
            .EType = 1
            .Path = Path
            .State = State
        End With

        If m_EC.Count > 0 Then
            m_EC.Add CE, , , m_EC.Count
        Else
            m_EC.Add CE
        End If
    End Sub

    Public Function Pop() As CEvent

        If m_EC.Count = 0 Then Exit Function
        Set Pop = m_EC(1)
        Call m_EC.Remove(1)

    End Function
    
    
