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

Private Sub tmrEvents_Timer()

        On Error GoTo DispError
        
        Dim ESR As CSubscriber
        Dim CE  As CEvent
        Dim I As Long
        
        Set CE = g_EventQueue.Pop
        If CE Is Nothing Then Exit Sub
        
        If Not (g_Clients Is Nothing) Then
fee:        On Error GoTo DispError
            For I = 1 To g_Clients.Count
                Set ESR = g_Clients(I - 1)
                Select Case CE.EType
                    Case 1:             'Component register/unregister
                        If CE.State Then
                            Call ESR.Sink.OnRegister(CE.Path)
                        Else
                            Call ESR.Sink.OnUnregister(CE.Path)
                        End If
                    Case 2:             'Locator connect/disconnect
                        If CE.State Then
                            Call ESR.Sink.OnConnect(CE.Path)
                        Else
                            Call ESR.Sink.OnDisconnect(CE.Path)
                        End If
                End Select
            Next
        End If
        
        Exit Sub

DispError:
    
    Dim RI As Long
    Dim S As String
    
    S = CE.Path & " to " & ESR.Key & " - " & Err.Source & ": " & Err.Description
    
    If CE.State Then
        Call LogEvent(S, RegDispError)
    Else
        Call LogEvent(S, UnRegDispError)
    End If
    
    On Error Resume Next
    
    RI = g_Clients.IndexFromKey(ESR.Key)
    g_Clients.Remove RI
    
    Err.Clear
    GoTo fee
    
End Sub

