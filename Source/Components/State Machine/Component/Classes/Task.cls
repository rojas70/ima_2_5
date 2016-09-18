VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 1  'Persistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Task"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

'************************************************************************************************************
'************************************************************************************************************
    
    Public Name         As String
    Public Description  As String
    Public HelpURL      As String
    
    Public Actions      As New Actions

    Public Index        As Integer
    Public Parent       As State

'************************************************************************************************************
'************************************************************************************************************
    
    Private Sub Class_ReadProperties(PropBag As PropertyBag)
    
        Set Actions = PropBag.ReadProperty("Actions")
        
        Name = PropBag.ReadProperty("Name")
        Description = PropBag.ReadProperty("Description")
        HelpURL = PropBag.ReadProperty("HelpURL")
        Index = PropBag.ReadProperty("Index")
    
    End Sub
    
    Private Sub Class_WriteProperties(PropBag As PropertyBag)
    
        Call PropBag.WriteProperty("Actions", Actions)
        
        Call PropBag.WriteProperty("Name", Name)
        Call PropBag.WriteProperty("Description", Description)
        Call PropBag.WriteProperty("HelpURL", HelpURL)
        Call PropBag.WriteProperty("Index", Index)
   
    End Sub



