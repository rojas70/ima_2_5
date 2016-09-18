VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 1  'Persistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Tasks"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

    Public Parent       As State
    Dim m_Tasks         As New IndexedArray
    
    Public Function Collection() As Collection
       Set Collection = ArrayToCollection(m_Tasks)
    End Function
    
    Public Property Get Item(I As Integer) As Task
        Set Item = m_Tasks(I)
    End Property
    
    Public Sub Add(T As Task)
        Call m_Tasks.Add(T)
        T.Index = m_Tasks.Count - (1 - m_Tasks.LowerBound)
    End Sub

    Public Sub Remove(I As Integer)
        Call m_Tasks.Remove(I)
        Dim N As Integer
        Dim O As Object
        For N = I To m_Tasks.UpperBound
            Set O = m_Tasks.Item(I)
            O.Index = O.Index - 1
        Next
    End Sub

    Public Property Get Count() As Integer
        Count = m_Tasks.Count
    End Property

    Private Sub Class_ReadProperties(PropBag As PropertyBag)
    
        Dim I As Integer
        Dim N As Integer
        Dim S As Task
        
        N = PropBag.ReadProperty("Count")
        
        For I = 0 To N - 1
            Set S = PropBag.ReadProperty("Task" & I)
            m_Tasks.Add S
        Next I
    
    End Sub
    
    Private Sub Class_WriteProperties(PropBag As PropertyBag)
    
        Dim I As Integer
        
        For I = m_Tasks.LowerBound To m_Tasks.UpperBound
            Call PropBag.WriteProperty("Task" & I, m_Tasks(I))
        Next I
    
        Call PropBag.WriteProperty("Count", m_Tasks.Count)
    
    End Sub

