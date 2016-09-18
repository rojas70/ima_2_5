VERSION 5.00
Begin VB.Form frmTimer 
   BorderStyle     =   0  'None
   ClientHeight    =   450
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   435
   ClipControls    =   0   'False
   ControlBox      =   0   'False
   Icon            =   "frmTimer.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   450
   ScaleWidth      =   435
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.Timer tmr 
      Enabled         =   0   'False
      Interval        =   500
      Left            =   0
      Top             =   0
   End
End
Attribute VB_Name = "frmTimer"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub tmr_Timer()

End Sub
