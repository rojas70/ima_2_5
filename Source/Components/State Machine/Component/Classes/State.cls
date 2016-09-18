VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 1  'Persistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "State"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

'************************************************************************************************************
'************************************************************************************************************
    
    Public Name             As String
    Public Description      As String
    Public HelpURL          As String
    
    Public Tasks            As New Tasks        'The tasks within this state
    Public Transitions      As New Transitions  'Transitions to other states
    
    Public Interval         As Long             'The number of seconds that must elapse before starting again
    Public TimeOut          As Long
    Public AutoLoop         As Boolean          'Keep looping in state?
    
    Public Index            As Integer
    Public Parent           As StateMachine

'************************************************************************************************************
'************************************************************************************************************
    
    Private Sub Class_ReadProperties(PropBag As PropertyBag)
    
        Set Tasks = PropBag.ReadProperty("Tasks")
        Set Transitions = PropBag.ReadProperty("Transitions")
        Interval = PropBag.ReadProperty("Interval")
        TimeOut = PropBag.ReadProperty("TimeOut")
        AutoLoop = PropBag.ReadProperty("AutoLoop")
        
        Name = PropBag.ReadProperty("Name")
        Description = PropBag.ReadProperty("Description")
        HelpURL = PropBag.ReadProperty("HelpURL")
        Index = PropBag.ReadProperty("Index")
    
    End Sub
    
    Private Sub Class_WriteProperties(PropBag As PropertyBag)

        Call PropBag.WriteProperty("Tasks", Tasks)
        Call PropBag.WriteProperty("Transitions", Transitions)
        Call PropBag.WriteProperty("Interval", Interval)
        Call PropBag.WriteProperty("TimeOut", TimeOut)
        Call PropBag.WriteProperty("AutoLoop", AutoLoop)
        
        Call PropBag.WriteProperty("Name", Name)
        Call PropBag.WriteProperty("Description", Description)
        Call PropBag.WriteProperty("HelpURL", HelpURL)
        Call PropBag.WriteProperty("Index", Index)

    End Sub

