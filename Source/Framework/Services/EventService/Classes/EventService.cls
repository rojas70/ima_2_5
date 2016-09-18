VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "EventService"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

    Implements IMA2.ILocatorEventProvider
    Implements IMA2.ILocatorEvents

    Public Sub Shutdown()
        End
    End Sub

    Public Sub DispatchOtherEvent(Action As IMA2_LocatorAction, Args() As String)
        Call ILocatorEvents_OnOtherEvent(Action, Args)
    End Sub

'************************************************************************************************************************************************

    Private Property Get ILocatorEventProvider_Clients() As String()
        On Error Resume Next
        ILocatorEventProvider_Clients = g_Clients.Keys
    End Property
    
    Private Sub ILocatorEventProvider_Subscribe(ByVal Sink As IMA2.ILocatorEvents, ByVal Key As String, Flags As IMA2.IMA2_LocatorAction)
        On Error Resume Next
        g_Clients.Add Sink, Key
    End Sub
    
    Private Sub ILocatorEventProvider_Unsubscribe(ByVal Key As String)
        On Error Resume Next
        g_Clients.Remove Key
    End Sub
    
    Private Sub ILocatorEvents_OnOtherEvent(Action As IMA2_LocatorAction, Args() As String)
        On Error Resume Next
        frmMain.DispatchOtherEvent Action, Args
    End Sub
    
    Private Sub ILocatorEvents_OnRegistrationEvent(Action As IMA2_LocatorAction, DIs() As IMA2_DistributingInfo)
        On Error Resume Next
        frmMain.DispatchRegistrationEvent Action, DIs
    End Sub
