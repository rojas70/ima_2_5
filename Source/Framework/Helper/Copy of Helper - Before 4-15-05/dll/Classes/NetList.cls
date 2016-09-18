VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "NetList"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit
    
    Private Declare Function GetCurrentProcessId Lib "kernel32.dll" () As Long

'************************************************************************************************
    
    Implements ILocatorEvents
        
'************************************************************************************************
    
    Dim m_Items()       As String
    Dim m_IS            As IDistributingInfoProvider
    Dim m_ES            As ILocatorEventProvider
    Dim m_Filter        As String
    Dim m_Key           As String
    
'************************************************************************************************
    
    Public WantRegisters    As Boolean
    Public WantSubscribes   As Boolean
    Public WantConnects     As Boolean
    
'************************************************************************************************
    
    Public Event OnRefresh()
    Public Event OnRegister(ByVal Path As String)
    Public Event OnUnregister(ByVal Path As String)
    Public Event OnSubscribe(ByVal Key As String)
    Public Event OnUnsubscribe(ByVal Key As String)
    Public Event OnConnect(ByVal Machine As String)
    Public Event OnDisconnect(ByVal Machine As String)
    Public Event OnOtherEvent(ByVal Action As IMA2_LocatorAction, Args() As String)
    
'************************************************************************************
    Public Sub Refresh()
        m_Items = m_IS.Components
        Call Funcs.QuickSortStrings(m_Items)
        RaiseEvent OnRefresh
    End Sub

    Public Property Get Items() As String()
        Items = m_Items
    End Property

'************************************************************************************
    
    Private Sub Class_Initialize()
        m_Key = "IMA2NetList (" & GetCurrentProcessId() & ") - " & Date & " " & Time & " "
        WantRegisters = True
        WantSubscribes = False
        WantConnects = False
        Set m_IS = CreateObject("IMA2_InfoService.InfoService")
        Set m_ES = CreateObject("IMA2_EventService.EventService")
        Call m_ES.Subscribe(Me, m_Key, 0)
    End Sub

    Private Sub Class_Terminate()
        On Error Resume Next
        Call m_ES.Unsubscribe(m_Key)
        Set m_ES = Nothing
        Set m_IS = Nothing
    End Sub

'************************************************************************************
' Locator Events
'************************************************************************************
    Private Sub ILocatorEvents_OnRegistrationEvent(Action As IMA2.IMA2_LocatorAction, DIs() As IMA2_DistributingInfo)
    
        Dim I   As Integer
        Dim P   As String
        
        If IsEmpty(DIs) Then Exit Sub
        
        For I = LBound(DIs) To UBound(DIs)
            P = DIs(I).Path
            If Action = LE_Register Then
                Call CmpRegistered(P)
            ElseIf Action = LE_UnRegister Then
                Call CmpUnregistered(P)
            End If
        Next I
        
    End Sub
    
    
    Private Sub ILocatorEvents_OnOtherEvent(Action As IMA2.IMA2_LocatorAction, Args() As String)
    
        If Action = LE_Connect Then
            If WantConnects And InStr(LCase(Args(0)), LCase(m_Filter)) = 1 Then RaiseEvent OnConnect(Args(0))
        ElseIf Action = LE_Disconnect Then
            If WantConnects And InStr(LCase(Args(0)), LCase(m_Filter)) = 1 Then RaiseEvent OnConnect(Args(0))
        ElseIf Action = LE_Subscribe Then
            If WantSubscribes Then RaiseEvent OnSubscribe(Args(0))
        ElseIf Action = LE_Unsubscribe Then
            If WantSubscribes Then RaiseEvent OnUnsubscribe(Args(0))
        Else
            RaiseEvent OnOtherEvent(Action, Args)
        End If
    
    End Sub
    
'************************************************************************************
' Misc. Functions
'************************************************************************************
    
    Private Sub CmpUnregistered(sPath As String)
        Dim UB As Integer
        Dim I As Integer
        UB = UBound(m_Items)
        If IsEmpty(m_Items) Then Exit Sub
            
        If InStr(LCase(sPath), LCase(m_Filter)) = 1 Then
            For I = 0 To UB
                If m_Items(I) = sPath Then
                    m_Items(I) = m_Items(UB)
                    ReDim Preserve m_Items(0 To UB - 1)
                    Exit For
                End If
            Next
            If WantRegisters Then RaiseEvent OnUnregister(sPath)
        End If
    
    End Sub
    
    Private Sub CmpRegistered(sPath As String)
        Dim UB As Integer
        If IsEmpty(m_Items) Then UB = -1
        If InStr(LCase(sPath), LCase(m_Filter)) = 1 Then
            ReDim Preserve m_Items(0 To UB + 1)
            m_Items(UB + 1) = sPath
            Call Funcs.QuickSortStrings(m_Items)
            If WantRegisters Then RaiseEvent OnRegister(sPath)
        End If
    End Sub
    

