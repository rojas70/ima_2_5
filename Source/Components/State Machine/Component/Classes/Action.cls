VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 1  'Persistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Action"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

'************************************************************************************************************
'************************************************************************************************************
    
    Public Description      As String
    Public HelpURL          As String
    
    Public ComponentName    As String
    Public FunctionName     As String
    Public Parameters       As Variant
    
    Public DoAlways         As Boolean
    Public DoneOnce         As Boolean
    
    Public Index            As Integer
    Public Parent           As Task
    
    
'************************************************************************************************************
'************************************************************************************************************
    
    Public Property Get Name() As String
        Name = ComponentName + "." + FunctionName + "(...)"
    End Property

'************************************************************************************************************
'************************************************************************************************************
    
    Private Sub Class_ReadProperties(PropBag As PropertyBag)
    
        ComponentName = PropBag.ReadProperty("ComponentName")
        FunctionName = PropBag.ReadProperty("FunctionName")
        DoAlways = PropBag.ReadProperty("DoAlways")
        DoneOnce = PropBag.ReadProperty("DoneOnce")
        
        Description = PropBag.ReadProperty("Description")
        HelpURL = PropBag.ReadProperty("HelpURL")
    
        Index = PropBag.ReadProperty("Index")
    
    End Sub
    
    Private Sub Class_WriteProperties(PropBag As PropertyBag)
    
        Call PropBag.WriteProperty("ComponentName", ComponentName)
        Call PropBag.WriteProperty("FunctionName", FunctionName)
        Call PropBag.WriteProperty("DoAlways", DoAlways)
        Call PropBag.WriteProperty("DoneOnce", DoneOnce)
        'Call PropBag.WriteProperty("Parameters", Parameters)
        
        Call PropBag.WriteProperty("Name", Name)
        Call PropBag.WriteProperty("Description", Description)
        Call PropBag.WriteProperty("HelpURL", HelpURL)
        Call PropBag.WriteProperty("Index", Index)
    
    End Sub


