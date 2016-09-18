VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 1  'Persistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CmpDesc"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

'******************************************************************************************
    
    Public Path         As String
    Public PID          As String
    Public Machine      As String
    Public DataSize     As Long
    Public Data         As Variant
    Public IsContainer  As Boolean
    
    Private m_BindingInfo()  As IMA2_BindingInfo
    
    Public MgrInfo      As Object
    Public DataMask     As CmpDesc_Data_Mask

'******************************************************************************************

    Public Enum CmpDesc_Data_Mask
        CD_None = 0
        CD_Path = 1
        CD_PID = 2
        CD_Machine = 4
        CD_DataSize = 8
        CD_Data = 16
        CD_BindingInfo = 32
        CD_MgrInfo = 64
        CD_IsContainer = 64
    End Enum

'******************************************************************************************
    
    Public Property Get BindingInfo() As IMA2_BindingInfo()
        BindingInfo = m_BindingInfo
    End Property

    Public Property Let BindingInfo(NV() As IMA2_BindingInfo)
        m_BindingInfo = NV
    End Property

'******************************************************************************************
    
    Public Sub Read(Cmp As IComponent)
    
        On Error Resume Next
        Dim PB As New PropertyBag
        Dim BC As IConfigureBindings
        Dim DI As IMA2_DistributingInfo
        
        If Cmp Is Nothing Then Exit Sub
        
        With Cmp
            DI = Cmp.Distributing
            Path = DI.Path
            PID = DI.PID
            Machine = DI.Machine
            IsContainer = DI.IsContainer
            
            Data = .Save
            DataSize = .DataSize
            
            Set BC = .Bindings
            BindingInfo = BC.Items
        End With
            
        DataMask = CD_Path Or CD_DataSize Or CD_Machine Or CD_PID Or CD_Data Or CD_BindingInfo Or CD_IsContainer
        Err.Clear
        
    End Sub
    
'******************************************************************************************
    
    Private Sub Class_ReadProperties(PropBag As PropertyBag)
    
        Path = PropBag.ReadProperty("Path")
        Machine = PropBag.ReadProperty("Machine")
        PID = PropBag.ReadProperty("PID")
        Data = PropBag.ReadProperty("Data")
        IsContainer = PropBag.ReadProperty("IsContainer")
        'm_BindingInfo = PropBag.ReadProperty("BindingInfo", "")
        
        DataMask = CD_Path Or CD_Machine Or CD_PID Or CD_Data Or CD_BindingInfo Or CD_IsContainer
    
    End Sub
    
'******************************************************************************************
    
    Private Sub Class_WriteProperties(PropBag As PropertyBag)
    
        Call PropBag.WriteProperty("Path", Path)
        Call PropBag.WriteProperty("Machine", Machine)
        Call PropBag.WriteProperty("PID", PID)
        Call PropBag.WriteProperty("Data", Data)
        Call PropBag.WriteProperty("IsContainer", IsContainer)
        'If Not ArrayEmpty(m_BindingInfo) Then
         '   Call PropBag.WriteProperty("BindingInfo", CVar(m_BindingInfo))
        'End If
        
    End Sub
