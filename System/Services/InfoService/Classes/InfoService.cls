VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "InfoService"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

    Implements IDistributingInfoProvider
    Implements ILocatorEvents
    
'************************************************************************************************************************
'#region "Default Interface"
'************************************************************************************************************************
    Public Sub Ping()
    End Sub
    
    Public Sub Shutdown()
        End
    End Sub

    Public Function FilePath() As String
        FilePath = App.Path
    End Function

    Public Sub Clear()
        'Hmmm... Locator should be able to clear the list (and we need to send a message indicating that)
    End Sub

'************************************************************************************************************************
'#region "IMA2.IDistributingInfoProvider Interface"
'************************************************************************************************************************

    Private Property Get IDistributingInfoProvider_Count() As Long
        On Error Resume Next
        IDistributingInfoProvider_Count = g_DIs.Count
    End Property
    
    Private Property Get IDistributingInfoProvider_Item(ByVal Path As String) As IMA2.IMA2_DistributingInfo
        On Error Resume Next
        IDistributingInfoProvider_Item = g_DIs.Item(Path)
    End Property
    
    Private Property Get IDistributingInfoProvider_Items() As IMA2.IMA2_DistributingInfo()
        On Error Resume Next
        ReDim DIs(0 To g_DIs.Count - 1) As IMA2.IMA2_DistributingInfo
        Dim I As Integer
        For I = 0 To UBound(DIs)
            DIs(I) = g_DIs(I + 1)
        Next
        IDistributingInfoProvider_Items = DIs
    End Property
    
    Private Property Get IDistributingInfoProvider_Components() As String()
        Dim I As Integer
        Dim DI As IMA2.IMA2_DistributingInfo
        ReDim S(0 To g_DIs.Count) As String
        For I = 1 To g_DIs.Count Step 1
            DI = g_DIs(I)
            S(I - 1) = DI.Path
        Next I
        IDistributingInfoProvider_Components = S
    End Property
    
    Private Property Get IDistributingInfoProvider_Locators() As String()
        
    End Property
    
    Private Function IDistributingInfoProvider_Search(ByVal Criteria As String) As IMA2.IMA2_DistributingInfo()
    
    End Function

'************************************************************************************************************************
'#region "IMA2.ILocatorEvents Interface"
'************************************************************************************************************************
    
    Private Sub ILocatorEvents_OnOtherEvent(Action As IMA2_LocatorAction, Args() As String)
        'Nada!
    End Sub
    
    Private Sub ILocatorEvents_OnRegistrationEvent(Action As IMA2_LocatorAction, DIs() As IMA2_DistributingInfo)
        On Error Resume Next
        Dim I   As Integer
        Dim P   As String
        Dim DI  As IMA2_DistributingInfo
            
        For I = LBound(DIs) To UBound(DIs)
            DI = DIs(I)
            If Action = LE_Register Then
                Call g_DIs.Add(DI, DI.Path)
            ElseIf Action = LE_UnRegister Then
                Call g_DIs.Remove(DI.Path)
            End If
        Next
    
    End Sub
