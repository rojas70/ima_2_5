VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "IndexedArray"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Attribute VB_Ext_KEY = "SavedWithClassBuilder6" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
Option Explicit
    
'************************************************************************************************************************
'************************************************************************************************************************
        
    Const ES_ITEM_LET = "IMA2Helper.IndexedArray.Item(...)"
    Const ES_KEYFROMINDEX = "IMA2Helper.IndexedArray.KeyFromIndex(...)"
    Const ES_INDEXFROMKEY = "IMA2Helper.IndexedArray.IndexFromKey(...)"
    Const ES_ADD = "IMA2Helper.IndexedArray.Add(...)"
    Const ES_REMOVE = "IMA2Helper.IndexedArray.Remove(...)"
    
    Const EN_INVALID_IK = 3000
    Const EM_INVALID_IK = "The index or key provided is not valid"
        
    Const EN_KEY_EXISTS = 3001
    Const EM_KEY_EXISTS = "The key is not unique"
   
    Const EN_OUT_OF_BOUNDS = 3002
    Const EM_OUT_OF_BOUNDS = "The index provided is out of bounds"
      
   
    Const INVALID_INDEX = -1
   
'************************************************************************************************************************
    
    Dim m_Empty         As Variant      'Our default "Empty" array.
    
    Dim m_Data()        As Variant      'Our variant array.
    Dim m_Keys()        As String       'Associated keys.
    Dim m_Count         As Long         'Number of items.
    
    Dim m_CaseSensitive As Boolean      'Determines whether key matches are case sensitive.
    
'************************************************************************************************************************
' Consturctor/Destructor
'************************************************************************************************************************

    Private Sub Class_Initialize()
        m_CaseSensitive = True
        m_Count = 0
    End Sub
    
'************************************************************************************************************************
' Security properties
'************************************************************************************************************************
    
    Public Property Let CaseSensitive(RHS As Boolean)
Attribute CaseSensitive.VB_Description = "Determines if string keys comparisons will be case sensitive."
        m_CaseSensitive = RHS
    End Property
    
    Public Property Get CaseSensitive() As Boolean
        CaseSensitive = m_CaseSensitive
    End Property
    
'************************************************************************************************************************
' Boundary information and retrieval
'************************************************************************************************************************
    
    Public Property Get LowerBound() As Long
Attribute LowerBound.VB_Description = "Returns the lower bound of the indexed array."
        LowerBound = 0
    End Property
    
    Public Property Get UpperBound() As Long
Attribute UpperBound.VB_Description = "Returns the upper bound of the items array."
        UpperBound = m_Count - 1
    End Property

'************************************************************************************************************************
' Bulk Data Retrieval
'************************************************************************************************************************
    
    Public Property Get Data() As Variant
        If m_Count = 0 Then
            Data = m_Empty
        Else
            Data = m_Data
        End If
    End Property
    
    Public Property Get Keys() As Variant
Attribute Keys.VB_Description = "Returns an array of keys."
        If m_Count = 0 Then
            Keys = m_Empty
        Else
            Keys = m_Keys
        End If
    End Property

'************************************************************************************************************************
' Element I/O
'************************************************************************************************************************

    'Returns an item with a specific index or key.
    Public Property Get Item(IndexKey As Variant) As Variant
Attribute Item.VB_Description = "Returns and item given its index or key."
Attribute Item.VB_UserMemId = 0
Attribute Item.VB_MemberFlags = "200"
        Dim I As Long
        I = IndexFromKey(IndexKey)                      'Get the key for the item.
        If VarType(m_Data(I)) = vbObject Then           'Let or set the appropriate return value.
            Set Item = m_Data(I)
        Else
            Item = m_Data(I)
        End If
    End Property
   
    'Assigns an item with a specific index or key a new value.
    Public Property Let Item(IndexKey As Variant, Element As Variant)
        Dim I As Long
        I = IndexFromKey(IndexKey)
        Call VarAssign(m_Data(I), Element)
    End Property
   
'************************************************************************************************************************
' Element index/key checking
'************************************************************************************************************************
    
    'Returns the index for a specific key/index. (Case sensitivity determined by m_CaseSensitive)
    Public Function IndexFromKey(IndexKey As Variant) As Long
        Dim I As Long
        I = IndexFromVariant(IndexKey)
        If (I = INVALID_INDEX) Then Call Err.Raise(EN_INVALID_IK, ES_INDEXFROMKEY, EM_INVALID_IK & " '" & CStr(IndexKey) & "'")
        IndexFromKey = I
    End Function
   
    'Returns the key for a specific index.
    Public Function KeyFromIndex(Index As Long) As String
        If OutOfBounds(Index) Then Call Err.Raise(EN_INVALID_IK, ES_INDEXFROMKEY, EN_INVALID_IK & " '" & CStr(Index) & "'")
        KeyFromIndex = m_Keys(Index)
    End Function
    
    'Returns true if the specified index or key is in the array.
    Public Function InArray(IndexKey As Variant) As Boolean
        InArray = Not (IndexFromVariant(IndexKey) = INVALID_INDEX)
    End Function
   
    'Returns the case-insensitive match for a key.
    Public Function KeyMatch(Key As String) As String
        Dim I As Long
        I = SearchForKey(Key, False)
        If I = INVALID_INDEX Then
            KeyMatch = ""
        Else
            KeyMatch = m_Keys(I)
        End If
    End Function
   
'************************************************************************************************************************
' List methods
'************************************************************************************************************************
   
    'Returns the number of items in the collection.
    Public Property Get Count() As Long
        Count = m_Count
    End Property

'************************************************************************************************************************
   
    'Clears the collection.
    Public Sub Clear()
        ReDim m_Data(0 To 0)
        ReDim m_Keys(0 To 0)
        m_Count = 0
    End Sub
   
'************************************************************************************************************************
   
   'Adds a variant to the collection.
    Public Sub Add(Element As Variant, Optional Key As String = "")
Attribute Add.VB_Description = "Adds an item to the indexed array."
        If Key <> "" Then
            If InArray(Key) Then Call Err.Raise(EN_KEY_EXISTS, ES_ADD, EM_KEY_EXISTS & " '" & Key & "'")
        End If
        Call Resize(m_Count + 1)                            'Make space for the element.
        Call VarAssign(m_Data(m_Count - 1), Element)        'Assign the element.
        m_Keys(m_Count - 1) = Key                           'Assign the new key.
    End Sub
    
   'Removes a variant from the collection.
    Public Sub Remove(IndexKey As Variant)
        Dim I As Long
        I = IndexFromKey(IndexKey)                          'Make sure its in the array.
        Call Delete(I)                                      'Remove the space for that element.
        Call Resize(m_Count - 1)                            'Shrink the array.
    End Sub
    
'    Public Sub Insert(NewElement As Variant, IndexKey As Variant, Optional NewKey As Variant)
 '
  '  End Sub
    
'************************************************************************************************************************
' Array Methods
'************************************************************************************************************************
   
    Public Sub Resize(NewSize As Long)
        If NewSize > 0 Then
            ReDim Preserve m_Data(0 To NewSize - 1)     'Resize the pointer array,
            ReDim Preserve m_Keys(0 To NewSize - 1)     'Resize the key array,
            m_Count = NewSize
        Else
            Call Clear
        End If
    End Sub
    
'************************************************************************************************************************
' Utility functions
'************************************************************************************************************************

    Private Function OutOfBounds(Index As Long) As Boolean
        OutOfBounds = (Index < 0) Or (Index > m_Count - 1)
    End Function

    Private Sub Delete(I As Long)
        
        Dim x As Long
        
        If m_Count = 0 Then Exit Sub
        
        Call ZeroElement(I)
        
        If VarType(m_Data(I)) = vbObject Then Set m_Data(I) = Nothing
        
        For x = I To m_Count - 2
            Call VarAssign(m_Data(x), m_Data(x + 1))
            m_Keys(x) = m_Keys(x + 1)
        Next x

        Call ZeroElement(m_Count - 1)

    End Sub

    Private Sub ZeroElement(I As Long)
        
        If VarType(m_Data(I)) = vbObject Then Set m_Data(I) = Nothing
        m_Data(I) = m_Empty
        m_Keys(I) = ""
    
    End Sub

    Private Sub VarAssign(LHS As Variant, RHS As Variant)

        'Let or set the appropriate return value.
        If VarType(RHS) = vbObject Then
            Set LHS = RHS
        Else
            LHS = RHS
        End If

    End Sub

    ' Returns INVALID_INDEX if the key is not found.
    Private Function SearchForKey(Key As String, CaseSensitive As Boolean) As Long

        Dim I As Long

        'Default to invalid key.
        SearchForKey = INVALID_INDEX
        
        'If there's nothing in the list, just exit.
        If m_Count = 0 Then Exit Function

        'We're dealing with a key, search for it.
        For I = LBound(m_Keys) To UBound(m_Keys)
            If CaseSensitive Then
                If m_Keys(I) = Key Then SearchForKey = I: Exit Function
            Else
                If LCase(m_Keys(I)) = LCase(Key) Then SearchForKey = I: Exit Function
            End If
        Next I
    
    End Function

    ' Returns INVALID_INDEX if the key or index is not found.
    Private Function IndexFromVariant(IndexKey As Variant) As Long
        IndexFromVariant = INVALID_INDEX
        Select Case VarType(IndexKey)
            Case vbString:
                If IndexKey = "" Then Exit Function
                IndexFromVariant = SearchForKey(CStr(IndexKey), m_CaseSensitive)
            Case Else:
                On Error Resume Next
                Dim OB As Long
                OB = OutOfBounds(CLng(IndexKey))
                If Err Or OB Then Err.Clear: Exit Function
                IndexFromVariant = IndexKey
        End Select
    End Function
   

