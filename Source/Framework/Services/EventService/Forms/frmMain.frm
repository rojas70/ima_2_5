VERSION 5.00
Begin VB.Form frmMain 
   Caption         =   "Form1"
   ClientHeight    =   915
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   2445
   Icon            =   "frmMain.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   915
   ScaleWidth      =   2445
   StartUpPosition =   3  'Windows Default
   Begin VB.Timer tmrGarbage 
      Enabled         =   0   'False
      Interval        =   10000
      Left            =   960
      Top             =   120
   End
   Begin VB.Timer tmrEvents 
      Enabled         =   0   'False
      Interval        =   100
      Left            =   120
      Top             =   120
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

    Dim m_Action As IMA2_LocatorAction
    Dim m_DIs() As IMA2_DistributingInfo
    Dim m_Args() As String
    Dim m_Type As Integer

'***********************************************************************************************************************
    
    Public Sub DispatchOtherEvent(Action As IMA2_LocatorAction, Args() As String)
        
        m_Action = Action
        m_Args = Args
        m_Type = 1
        tmrEvents.Enabled = True
    
    End Sub

'***********************************************************************************************************************
    
    Public Sub DispatchRegistrationEvent(Action As IMA2_LocatorAction, DIs() As IMA2_DistributingInfo)
        
        m_Action = Action
        m_DIs = DIs
        m_Type = 0
        tmrEvents.Enabled = True
    
    End Sub
    
'***********************************************************************************************************************
    
    Private Sub DispatchEvents()
    
        On Error Resume Next
        
        Dim C As ILocatorEvents
        Dim I As Integer
        
        'Attempt to weed out invalid references
        I = 0
        Do
            'Access the next client in the queue
            Set C = g_Clients(I)
            
            'Dispatch the appropriate type of event
            If m_Type = 0 Then
                C.OnRegistrationEvent m_Action, m_DIs
            Else
                C.OnOtherEvent m_Action, m_Args
            End If
            
            'If there was an error dispatching the event, remove the client from the list.
            If Err.Number = 0 Then
                I = I + 1
            Else
                g_Clients.Remove I
                Err.Clear
            End If

        Loop While I < g_Clients.Count
    
    End Sub
    
'***********************************************************************************************************************
    
    Private Sub tmrEvents_Timer()
    
        On Error Resume Next
        If g_Clients.Count = 0 Then Exit Sub
        Call DispatchEvents
        tmrEvents.Enabled = False
       
    End Sub
    

