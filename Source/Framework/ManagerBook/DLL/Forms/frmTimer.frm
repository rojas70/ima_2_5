VERSION 5.00
Begin VB.Form frmTimer 
   BorderStyle     =   0  'None
   Caption         =   "Benchmarking Form"
   ClientHeight    =   1860
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   2475
   Icon            =   "frmTimer.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1860
   ScaleWidth      =   2475
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.Timer tmr 
      Interval        =   1
      Left            =   960
      Top             =   720
   End
End
Attribute VB_Name = "frmTimer"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim m_TimerCount As Long
Dim m_TimerEnd As Single

Public Event OnTrialFinished(EventsPerSec As Long)

Private Sub tmr_Timer()

    m_TimerCount = m_TimerCount + 1
    If Timer >= m_TimerEnd Then
        tmr.Enabled = False
        RaiseEvent OnTrialFinished(m_TimerCount)
        Unload Me
    End If

End Sub

Public Sub BeginTrial()

    tmr.Interval = 10
    m_TimerEnd = Timer + 0.5
    tmr.Enabled = True
    
End Sub


