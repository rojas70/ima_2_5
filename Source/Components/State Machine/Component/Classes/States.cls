VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 1  'Persistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "States"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
    Option Explicit

    Dim m_States        As New IndexedArray
    Public Parent       As StateMachine
    
    Public Function Collection() As Collection
       Set Collection = ArrayToCollection(m_States)
    End Function
    
    Public Property Get Item(I As Integer) As State
        Set Item = m_States(I)
    End Property
    
    Public Sub Add(S As State)
        Call m_States.Add(S)
        S.Index = m_States.Count - (1 - m_States.LowerBound)
    End Sub

    Public Sub Remove(I As Integer)
        Call m_States.Remove(I)
        Dim N As Integer
        Dim O As Object
        For N = I To m_States.UpperBound
            Set O = m_States.Item(I)
            O.Index = O.Index - 1
        Next
    End Sub

    Public Property Get Count() As Integer
        Count = m_States.Count
    End Property

    Private Sub Class_ReadProperties(PropBag As PropertyBag)
    
        Dim I As Integer
        Dim N As Integer
        Dim S As State
        
        N = PropBag.ReadProperty("Count")
        
        For I = 0 To N - 1
            Set S = PropBag.ReadProperty("State" & I)
            m_States.Add S
        Next I
    
    End Sub
    
    Private Sub Class_WriteProperties(PropBag As PropertyBag)
    
        Dim I As Integer
        
        For I = m_States.LowerBound To m_States.UpperBound
            Call PropBag.WriteProperty("State" & I, m_States(I))
        Next I
    
        Call PropBag.WriteProperty("Count", m_States.Count)
    
    End Sub
