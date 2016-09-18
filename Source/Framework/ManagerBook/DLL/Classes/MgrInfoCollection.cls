VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "MgrInfoCollection"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder6" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"No"
Attribute VB_Ext_KEY = "Collection" ,"MgrInfo"
Attribute VB_Ext_KEY = "Member0" ,"MgrInfo"
    Option Explicit
    
    Private m_Col As New Collection     'local variable to hold collection
    
'****************************************************************************************************************
' Public Interface
'****************************************************************************************************************
    Public Sub RemoveAll()
        While m_Col.Count > 0
            Remove 1
        Wend
    End Sub
    
    Public Function Add(M As MgrInfo) As MgrInfo
        m_Col.Add M, M.Caption
        Set Add = M
    End Function
    
    Public Property Get Item(IndexKey As Variant) As MgrInfo
        Set Item = m_Col(IndexKey)
    End Property
    
    Public Property Get Count() As Long
        Count = m_Col.Count
    End Property
    
    Public Sub Remove(IndexKey As Variant)
        Dim MI As MgrInfo
        Set MI = m_Col(IndexKey)
        MI.CleanUp
        m_Col.Remove IndexKey
    End Sub

    Public Property Get NewEnum() As IUnknown
Attribute NewEnum.VB_UserMemId = -4
        Set NewEnum = m_Col.[_NewEnum]
    End Property
    
'****************************************************************************************************************
' Class Functions
'****************************************************************************************************************
    
    Public Sub WritePB(Header As String, PropBag As PropertyBag)
    
        Dim M       As MgrInfo
        Dim Index   As Integer
        
        For Each M In m_Col
            Index = Index + 1
            Call M.WritePB(Header & Index, PropBag)
        Next M
        
        Call PropBag.WriteProperty(Header & "Count", m_Col.Count, 0)
        
    End Sub

    Public Sub ReadPB(Header As String, PropBag As PropertyBag)
    
        Dim M       As New MgrInfo
        Dim Index   As Integer
        Dim Count   As Integer
        
        Count = PropBag.ReadProperty(Header & "Count", 0)
        
        For Index = 1 To Count
            Call M.ReadPB(Header & Index, PropBag)
            Call m_Col.Add(M, M.Caption)
            Set M = Nothing
        Next
    
    End Sub
