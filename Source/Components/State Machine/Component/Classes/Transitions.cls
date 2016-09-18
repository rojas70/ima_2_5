VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 1  'Persistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Transitions"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

    Dim m_Transitions   As New IndexedArray
    Public Parent       As State
    
    Public Function Collection() As Collection
       Set Collection = ArrayToCollection(m_Transitions)
    End Function
    
    Public Property Get Item(I As Integer) As Transition
        Set Item = m_Transitions(I)
    End Property
    
    Public Sub Add(T As Transition)
        Call m_Transitions.Add(T)
        T.Index = m_Transitions.Count - (1 - m_Transitions.LowerBound)
    End Sub

    Public Sub Remove(I As Integer)
        Call m_Transitions.Remove(I)
        Dim N As Integer
        Dim O As Object
        For N = I To m_Transitions.UpperBound
            Set O = m_Transitions.Item(I)
            O.Index = O.Index - 1
        Next
    End Sub

    Public Property Get Count() As Integer
        Count = m_Transitions.Count
    End Property

    Private Sub Class_ReadProperties(PropBag As PropertyBag)
    
        Dim I As Integer
        Dim N As Integer
        Dim S As Transition
        
        N = PropBag.ReadProperty("Count")
        
        For I = 0 To N - 1
            Set S = PropBag.ReadProperty("Transition" & I)
            m_Transitions.Add S
        Next I
    
    End Sub
    
    Private Sub Class_WriteProperties(PropBag As PropertyBag)
    
        Dim I As Integer
        
        For I = m_Transitions.LowerBound To m_Transitions.UpperBound
            Call PropBag.WriteProperty("Transition" & I, m_Transitions(I))
        Next I
    
        Call PropBag.WriteProperty("Count", m_Transitions.Count)
    
    End Sub

