Attribute VB_Name = "modMain"
Option Explicit

    Public Function ArrayToCollection(A As IndexedArray) As Collection
    
        Dim C As New Collection
        Dim I As Integer
    
        For I = A.LowerBound To A.UpperBound
            C.Add A(I)
        Next I
    
        Set ArrayToCollection = C
    
    End Function


