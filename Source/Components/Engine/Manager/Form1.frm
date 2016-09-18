VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Index           =   0
      Left            =   120
      Top             =   120
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'********************************************************************************************
' Class:        BasicIMA.Form1
' Author:       Roberto Olivares (olivarre@vuse.vanderbilt.edu)
' Last update:  (4/7/00)
'
' Description:  This form holds Timers that our engines use to notify event clients with.
'********************************************************************************************

    Option Explicit
    
    Dim TCount      As Integer      'Current client index we're on
    Dim Engines()   As Engine       'List of engines subscribed
    
'********************************************************************************************
' Public Functions
'********************************************************************************************
    
    Public Function CreateTimer(Eng As Engine) As Timer
    
        TCount = TCount + 1
        ReDim Preserve Engines(1 To TCount)
        
        Call Load(Timer1(TCount))
        
        Set CreateTimer = Timer1(TCount)
        Set Engines(TCount) = Eng
    
    End Function
    
    Public Function ReleaseTimer(T As Timer)
        
        Unload T
        Set Engines(T.Index) = Nothing
    
    End Function
    
Private Sub AgentMgr1_AgentEvent(ByVal lEventType As Long, ByVal lEventID As Long, ByVal pIDispComp As Object)

End Sub

'********************************************************************************************
' Event Handlers
'********************************************************************************************
    
    Private Sub Timer1_Timer(Index As Integer)
    
   '     Call Engines(Index).NotifyClients
    
    End Sub
