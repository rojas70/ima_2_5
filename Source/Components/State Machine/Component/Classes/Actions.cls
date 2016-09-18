VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 1  'Persistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Actions"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

    Dim m_Actions       As New IndexedArray
    Public Parent       As Task

    Public Function Collection() As Collection
       Set Collection = ArrayToCollection(m_Actions)
    End Function

    Public Property Get Item(I As Integer) As Action
        Set Item = m_Actions(I)
    End Property
    
    Public Sub Add(A As Action)
        Call m_Actions.Add(A)
        A.Index = m_Actions.Count - (1 - m_Actions.LowerBound)
    End Sub

    Public Sub Remove(I As Integer)
        Call m_Actions.Remove(I)
        Dim N As Integer
        Dim O As Object
        For N = I To m_Actions.UpperBound
            Set O = m_Actions.Item(I)
            O.Index = O.Index - 1
        Next
    End Sub

    Public Property Get Count() As Integer
        Count = m_Actions.Count
    End Property

    Private Sub Class_ReadProperties(PropBag As PropertyBag)
    
        Dim I As Integer
        Dim N As Integer
        Dim S As Action
        
        N = PropBag.ReadProperty("Count")
        
        For I = 0 To N - 1
            Set S = PropBag.ReadProperty("Action" & I)
            m_Actions.Add S
        Next I
    
    End Sub
    
    Private Sub Class_WriteProperties(PropBag As PropertyBag)
    
        Dim I As Integer
        
        For I = m_Actions.LowerBound To m_Actions.UpperBound
            Call PropBag.WriteProperty("Action" & I, m_Actions(I))
        Next I
    
        Call PropBag.WriteProperty("Count", m_Actions.Count)
    
    End Sub

