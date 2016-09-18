VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "PropertyBagWrapper"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
' ***********************************************************************************
' This PropertyBagWrapper Class is used by C++ IMA 2.5 components to SAVE/LOAD data in
' AgentBuilder. PropertyBags are not accessible in C++ b/c OLEAUT32.dll (aka VBRUN)
' cannot be imported into C++, therefore we had to omit the defs of PBs
' This class was implemented to get around those problems.
'
' MyPropertyBag is a pointer that points to the components PropertyBag
' A pointer from the wrapper class in C++ will point to an interface to this class.
'
' Created Roberto Olivares, Juan Rojas 11/26/04
' Last Updated 5/2/05
' ***********************************************************************************

Dim MyPropertyBag As New PropertyBag
'Returns a PropertyBag.
Public Function GetPropertyBag() As Variant

    ' R-Val must be set equal to .Contents so that the C++ container gets it as a
    ' variant instead of a PropertyBag (creating an error)
    GetPropertyBag = MyPropertyBag.Contents

End Function
'Save into the PropertyBag the data that you pass to the function.
Public Sub SetPropertyBag(Contents As Variant)
    
    MyPropertyBag.Contents = Contents

End Sub
'Adds an item to the PropertyBag. You pass it a name and a value.

Public Sub AddToPropertyBag(ItemName As String, ItemValue As Variant)
    Call MyPropertyBag.WriteProperty(ItemName, ItemValue)
End Sub

Public Sub AddArrayToPropertyBag(ItemName As String, ItemValue As Variant)

    Dim I As Integer
    Dim Tp As String
    Dim LB As Integer
    Dim UB As Integer
    
    If IsArray(ItemValue) Then
        LB = LBound(ItemValue)
        UB = UBound(ItemValue)
        Tp = TypeName(ItemValue)
        Call MyPropertyBag.WriteProperty(ItemName & "LBound", LB)
        Call MyPropertyBag.WriteProperty(ItemName & "UBound", UB)
        Call MyPropertyBag.WriteProperty(ItemName & "Type", Tp)
        For I = LBound(ItemValue) To UBound(ItemValue)
            Call MyPropertyBag.WriteProperty(ItemName & I, ItemValue(I))
        Next I
    Else
       Call MyPropertyBag.WriteProperty(ItemName, ItemValue)
    End If
   
End Sub

'Returns the value associated with the string name that it was saved with.
Public Function GetFromPropertyBag(ItemName As String) As Variant
    GetFromPropertyBag = MyPropertyBag.ReadProperty(ItemName)
End Function

Public Function GetArrayFromPropertyBag(ItemName As String) As Variant
    Dim I As Integer
    Dim LB As Integer
    Dim UB As Integer
    Dim Tp As String
    Dim SArr() As Single
    Dim DArr() As Double
    Dim IArr() As Integer
    Dim LArr() As Long
    Dim VArr() As Variant
    
    LB = MyPropertyBag.ReadProperty(ItemName & "LBound")
    UB = MyPropertyBag.ReadProperty(ItemName & "UBound")
    Tp = MyPropertyBag.ReadProperty(ItemName & "Type")
        If (StrComp(Tp, "Single()") = 0) Then
            ReDim SArr(LB To UB)
        ElseIf (StrComp(Tp, "Double()") = 0) Then
            ReDim DArr(LB To UB)
        ElseIf (StrComp(Tp, "Integer()") = 0) Then
            ReDim IArr(LB To UB)
        ElseIf (StrComp(Tp, "Long()") = 0) Then
            ReDim LArr(LB To UB)
        Else
            ReDim VArr(LB To UB)
        End If
        For I = LB To UB
            If (StrComp(Tp, "Single()") = 0) Then
                SArr(I) = MyPropertyBag.ReadProperty(ItemName & I)
            ElseIf (StrComp(Tp, "Double()") = 0) Then
                DArr(I) = MyPropertyBag.ReadProperty(ItemName & I)
            ElseIf (StrComp(Tp, "Integer()") = 0) Then
                IArr(I) = MyPropertyBag.ReadProperty(ItemName & I)
            ElseIf (StrComp(Tp, "Long()") = 0) Then
                LArr(I) = MyPropertyBag.ReadProperty(ItemName & I)
            Else
                VArr(I) = MyPropertyBag.ReadProperty(ItemName & I)
            End If
        Next I
        If (StrComp(Tp, "Single()") = 0) Then
            GetArrayFromPropertyBag = SArr
        ElseIf (StrComp(Tp, "Double()") = 0) Then
            GetArrayFromPropertyBag = DArr
        ElseIf (StrComp(Tp, "Integer()") = 0) Then
            GetArrayFromPropertyBag = IArr
        ElseIf (StrComp(Tp, "Long()") = 0) Then
            GetArrayFromPropertyBag = LArr
        Else
            GetArrayFromPropertyBag = VArr
        End If
    'Else
     '   GetArrayFromPropertyBag = MyPropertyBag.ReadProperty(ItemName)
   ' End If
End Function



