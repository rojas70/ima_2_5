VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 1  'Persistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Bindings"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Attribute VB_Ext_KEY = "SavedWithClassBuilder6" ,"Yes"
Attribute VB_Ext_KEY = "Collection" ,"Binding"
Attribute VB_Ext_KEY = "Member0" ,"Binding"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
Option Explicit

'*************************************************************************************************************************************************
'Implemented Interfaces
'*************************************************************************************************************************************************
    
    Implements IBindings
    Implements IConfigureBindings

'*************************************************************************************************************************************************
' Local Variables
'*************************************************************************************************************************************************
    
    'Local variable to hold collection
    Private m_Inf   As Collection       'Collection of BindingInfos
    Private m_AL    As ILocator
    Private m_Owner As String
    Private m_Bound As Boolean

'*************************************************************************************************************************************************
' IBindings Interfaces
'*************************************************************************************************************************************************
    
    Private Property Get IBindings_Collections(ByVal Name As String) As IMA2.IComponent()
        On Error Resume Next
        
        Dim I       As Integer
        Dim BI      As IMA2_BindingInfo
        Dim Paths() As String
        Dim Cmps()  As IComponent
        
        BI = m_Inf(Name)
        If BI.Path = "" Then Exit Property
        
        Paths = Split(BI.Path, ",")
        ReDim Cmps(0 To UBound(Paths)) As IComponent
        For I = 0 To UBound(Paths)
            Set Cmps(I) = m_AL.Locate(Paths(I))
        Next I
        
        IBindings_Collections = Cmps
    End Property
    
    '*************************************************************************************************************************************************

    Private Property Get IBindings_Pointers(ByVal Name As String) As IMA2.IComponent
        On Error Resume Next
        Dim BI As IMA2_BindingInfo
        BI = m_Inf(Name)
        Set IBindings_Pointers = m_AL.Locate(BI.Path)
    End Property

    '*************************************************************************************************************************************************
    
    Private Property Get IBindings_Settings() As IMA2.IConfigureBindings
        Set IBindings_Settings = Me
    End Property

'*************************************************************************************************************************************************
' IConfigureBindings
'*************************************************************************************************************************************************

    Private Sub IConfigureBindings_Add(BindInfo As IMA2.IMA2_BindingInfo)
        On Error Resume Next
        If m_Owner = "" Then Call Err.Raise(2000, "Binding collection not constructed.")
        m_Inf.Add BindInfo, BindInfo.Name
    End Sub

    '*************************************************************************************************************************************************
    
    Private Sub IConfigureBindings_Construct(ByVal Owner As String, AL As IMA2.ILocator)

        If m_Owner <> "" Then Call Err.Raise(2000, "Bindings collection already constructed.")
        m_Owner = Owner
        Set m_AL = AL
        If m_Inf Is Nothing Then Set m_Inf = New Collection

    End Sub

    '*************************************************************************************************************************************************
    
    Private Property Get IConfigureBindings_Item(ByVal Name As String) As IMA2.IMA2_BindingInfo
        IConfigureBindings_Item = m_Inf(Name)
    End Property
    
    '*************************************************************************************************************************************************
    
    Private Property Get IConfigureBindings_Items() As IMA2.IMA2_BindingInfo()
        ReDim BIs(0 To m_Inf.Count - 1) As IMA2_BindingInfo
        Dim I As Integer
        For I = 0 To m_Inf.Count - 1
            BIs(I) = m_Inf(I + 1)
        Next
        IConfigureBindings_Items = BIs
    End Property

    '*************************************************************************************************************************************************
    
    Private Sub IConfigureBindings_Remove(ByVal Name As String)
        m_Inf.Remove Name
    End Sub

    '*************************************************************************************************************************************************
    
    Private Sub IConfigureBindings_Destruct()
        If m_Owner = "" Then Call Err.Raise(2000, "Bindings collection already destructed.")
        m_Owner = ""
        Set m_AL = Nothing
        Set m_Inf = Nothing
    End Sub

    '*************************************************************************************************************************************************

    Private Property Get IConfigureBindings_Count() As Long
        IConfigureBindings_Count = m_Inf.Count
    End Property

'*************************************************************************************************************************************************
' Serialization
'*************************************************************************************************************************************************
    
    Private Sub Class_ReadProperties(PropBag As PropertyBag)
    
        Dim BI      As IMA2_BindingInfo
        Dim I       As Integer
        Dim Count   As Integer
        
        Count = PropBag.ReadProperty("Count")
        For I = 1 To Count
            BI = PropBag.ReadProperty("" & I)
            Call m_Inf.Add(BI, BI.Name)
        Next
    
    End Sub
    
    '*************************************************************************************************************************************************
    
    Private Sub Class_WriteProperties(PropBag As PropertyBag)
        
        Dim BI  As IMA2_BindingInfo
        Dim I   As Integer
        
        Call PropBag.WriteProperty("Count", m_Inf.Count)
        For I = 1 To m_Inf.Count
            BI = m_Inf(I)
            Call PropBag.WriteProperty("" & I, BI)
        Next
        
    End Sub

