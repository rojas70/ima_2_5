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
        Dim I As Integer
        Dim J As Integer
        Dim BindCount As Integer
        Dim IDCount As Integer
        
        Path = PropBag.ReadProperty("Path")
        Machine = PropBag.ReadProperty("Machine")
        PID = PropBag.ReadProperty("PID")
        Data = PropBag.ReadProperty("Data")
        IsContainer = PropBag.ReadProperty("IsContainer")
        
        'Edited to read Bindings from file Mar '05 -CLC
        BindCount = PropBag.ReadProperty("BindingCount")
        If BindCount >= 0 Then ReDim m_BindingInfo(0 To BindCount)
        For I = 0 To BindCount
            m_BindingInfo(I).BindType = PropBag.ReadProperty("BindingInfo" & I & "BindType")
            m_BindingInfo(I).Name = PropBag.ReadProperty("BindingInfo" & I & "Name")
            m_BindingInfo(I).Path = PropBag.ReadProperty("BindingInfo" & I & "Path")
            
            IDCount = PropBag.ReadProperty("BindingInfo" & I & "PIDCount")
            If IDCount < 0 Then
                ReDim m_BindingInfo(I).PIDs(0)
            Else
                ReDim m_BindingInfo(I).PIDs(0 To IDCount)
                For J = 0 To IDCount
                    m_BindingInfo(I).PIDs(J) = PropBag.ReadProperty("BindingInfo" & I & "PIDs" & J)
                Next J
            End If

            IDCount = PropBag.ReadProperty("BindingInfo" & I & "IIDCount")
            If IDCount < 0 Then
                ReDim m_BindingInfo(I).IIDs(0)
            Else
                ReDim m_BindingInfo(I).IIDs(0 To IDCount)
                For J = 0 To IDCount
                    m_BindingInfo(I).IIDs(J) = PropBag.ReadProperty("BindingInfo" & I & "IIDs" & J)
                Next J
            End If
        Next I
        
        DataMask = CD_Path Or CD_Machine Or CD_PID Or CD_Data Or CD_BindingInfo Or CD_IsContainer
    
    End Sub
    
'******************************************************************************************
    
    Private Sub Class_WriteProperties(PropBag As PropertyBag)
        Dim I As Integer
        Dim J As Integer
        Call PropBag.WriteProperty("Path", Path)
        Call PropBag.WriteProperty("Machine", Machine)
        Call PropBag.WriteProperty("PID", PID)
        Call PropBag.WriteProperty("Data", Data)
        Call PropBag.WriteProperty("IsContainer", IsContainer)
        
        'Changed to write bindings to file Mar '05 -CLC
        If Funcs.ArrayEmpty(m_BindingInfo) Then
            Call PropBag.WriteProperty("BindingCount", -1)
        Else
            Call PropBag.WriteProperty("BindingCount", UBound(m_BindingInfo))
            For I = 0 To UBound(m_BindingInfo)
                Call PropBag.WriteProperty("BindingInfo" & I & "BindType", m_BindingInfo(I).BindType)
                Call PropBag.WriteProperty("BindingInfo" & I & "Name", m_BindingInfo(I).Name)
                Call PropBag.WriteProperty("BindingInfo" & I & "Path", m_BindingInfo(I).Path)
                If Funcs.ArrayEmpty(m_BindingInfo(I).PIDs) Then
                    Call PropBag.WriteProperty("BindingInfo" & I & "PIDCount", -1)
                Else
                    Call PropBag.WriteProperty("BindingInfo" & I & "PIDCount", UBound(m_BindingInfo(I).PIDs))
                    For J = 0 To UBound(m_BindingInfo(I).PIDs)
                        Call PropBag.WriteProperty("BindingInfo" & I & "PIDs" & J, m_BindingInfo(I).PIDs(J))
                    Next J
                End If
                If Funcs.ArrayEmpty(m_BindingInfo(I).IIDs) Then
                    Call PropBag.WriteProperty("BindingInfo" & I & "IIDCount", -1)
                Else
                    Call PropBag.WriteProperty("BindingInfo" & I & "IIDCount", UBound(m_BindingInfo(I).IIDs))
                    For J = 0 To UBound(m_BindingInfo(I).IIDs)
                        Call PropBag.WriteProperty("BindingInfo" & I & "IIDs" & J, m_BindingInfo(I).IIDs(J))
                    Next J
                End If
            Next I
        End If
        
    End Sub
