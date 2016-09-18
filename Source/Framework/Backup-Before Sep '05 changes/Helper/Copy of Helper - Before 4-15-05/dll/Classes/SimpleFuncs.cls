VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "SimpleFuncs"
Attribute VB_GlobalNameSpace = True
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
    Option Explicit
    
'************************************************************************************************
    
    'Returns the current Process ID.
    Public Function CurrentProcessID() As Long
        CurrentProcessID = GetCurrentProcessId()
    End Function
    
'************************************************************************************************
    
    'Returns the current Thread ID.
    Public Function CurrentThreadID() As Long
        CurrentThreadID = GetCurrentThreadId()
    End Function

'************************************************************************************************
    
    Public Function ArraySize(Data As Variant) As Long
Attribute ArraySize.VB_Description = "Returns the number of elements in the first dimension of the array, or zero if the array is empty."
        On Error Resume Next
        ArraySize = (UBound(Data) - LBound(Data)) + 1
        Err.Clear
    End Function
    
'************************************************************************************************
    
    Public Function ArrayEmpty(Data As Variant) As Boolean
        Dim Temp As Long
        On Error Resume Next
        Temp = UBound(Data)
        ArrayEmpty = (Err <> 0)
        Err.Clear
    End Function
    
'************************************************************************************************
    
    Public Function SentenceCase(Val As String)
Attribute SentenceCase.VB_Description = "Turns a string into sentence case."
        SentenceCase = UCase(Left(Val, 1)) + LCase(Mid(Val, 2))
    End Function
    
'************************************************************************************************
    
    Public Function FindMatchingString(String1 As String, Strings() As String) As String
        Dim LS  As String
        Dim I   As Long
        LS = LCase(String1)
        For I = LBound(Strings) To UBound(Strings)
            If LS = LCase(Strings(I)) Then FindMatchingString = Strings(I): Exit Function
        Next I
    End Function
    
'************************************************************************************************
    
    Public Sub QuickSortStrings(sArray() As String, Optional Ascending As Boolean = True)
Attribute QuickSortStrings.VB_Description = "Quickly sorts an array of strings into ascending or descending order."
        If Ascending Then
            QuickSortStringsAscending sArray(), LBound(sArray), UBound(sArray)
        Else
            QuickSortStringsDescending sArray(), LBound(sArray), UBound(sArray)
        End If
    End Sub
    
'************************************************************************************************
    
    Public Sub RemoveBlankStrings(S() As String)
        Dim UB      As Integer
        Dim LB      As Integer
        Dim I       As Integer
        Dim Index   As Integer
        Dim RV()    As String
        Dim Count   As Integer
        
        If ArrayEmpty(S) Then Exit Sub
        LB = LBound(S)
        UB = UBound(S)
        
        For I = LB To UB
            If Len(S(I)) > 0 Then Count = Count + 1
        Next
        
        ReDim RV(LB To LB + Count - 1)
        
        Index = LB
        For I = LB To UB
            If Len(S(I)) > 0 Then
                RV(Index) = S(I)
                Index = Index + 1
            End If
        Next
        
        S = RV
    End Sub
    
'************************************************************************************************

    'Tests if the object passed is not nothing.
    Public Function NN(Obj As Object) As Boolean
Attribute NN.VB_Description = "Return Value =  Not (Object Is Nothing)"
        NN = Not (Obj Is Nothing)
    End Function

'************************************************************************************************

    'Returns the number of occurences of Match in Source.
    Public Function StrCount(Source As String, Match As String) As Long
Attribute StrCount.VB_Description = "Returns the number of times the specified substring was found in the source string."
    
        Dim CP&, SC&
        If Match$ = "" Then Exit Function
        CP& = 0
        SC& = 0
        Do
            CP& = InStr(CP& + 1, Source$, Match$)
            If CP& >= 1 Then SC& = SC& + 1
        Loop Until CP& < 1
    
        StrCount = SC&
    End Function

'************************************************************************************************************************************

    'Determines if any of the characters in Chars occurs in S.
    Public Function CharsInString(S As String, Chars As String) As Boolean
        Dim I As Long
        For I = 1 To Len(S)
            If InStr(S, Mid(Chars, 1, 1)) > 0 Then
                CharsInString = True
                Exit Function
            End If
        Next
        CharsInString = False
    End Function


