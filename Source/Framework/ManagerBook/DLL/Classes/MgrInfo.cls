VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "MgrInfo"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder6" ,"Yes"
Attribute VB_Ext_KEY = "Member0" ,"MgrInfoCollection"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
Option Explicit

    Public Enum MgrPriority
        PP_Low = 0
        PP_Medium = 1
        PP_High = 2
        PP_UserDefined = 3
    End Enum

    Public CmpPID      As String
    Public MgrPID      As String
    Public Priority    As MgrPriority
    Public Interval    As Long
    
    Public Caption     As String
    Public Description As String
    Public Notes       As String
    
    Public Path         As String
    Public Manager      As IManager
    Public MgrControl   As Object

    Public WindowLeft   As Single
    Public WindowTop    As Single
    Public WindowWidth  As Single
    Public WindowHeight As Single

    Private m_Window    As SimpleWindow

    Friend Property Get Window() As SimpleWindow
        Set Window = m_Window
    End Property
    
    Friend Property Set Window(NV As SimpleWindow)
        Set m_Window = NV
    End Property

    Public Sub UpdateWindowProperties()
        If m_Window Is Nothing Then Exit Sub
        WindowLeft = m_Window.Left
        WindowTop = m_Window.Top
        WindowWidth = m_Window.Width
        WindowHeight = m_Window.Height
    End Sub

    Public Sub CleanUp()
        If Manager Is Nothing Then Exit Sub
        Unload m_Window
        Manager.Component = Nothing
    End Sub
    
    Public Sub ReadPB(Header As String, PropBag As PropertyBag)
        
        With Me
            .Caption = PropBag.ReadProperty(Header & "Caption", "<No Caption>")
            .CmpPID = PropBag.ReadProperty(Header & "CmpPID", "<No CmpPID>")
            .Path = PropBag.ReadProperty(Header & "Path", "<No Path>")
            .Interval = PropBag.ReadProperty(Header & "Interval", 500)
            .MgrPID = PropBag.ReadProperty(Header & "MgrPID", "<No MgrPID>")
            .Description = PropBag.ReadProperty(Header & "Description", "<No Description>")
            .Notes = PropBag.ReadProperty(Header & "Notes", "<No Notes>")
        
            .WindowLeft = PropBag.ReadProperty(Header & "WindowLeft", 0)
            .WindowTop = PropBag.ReadProperty(Header & "WindowTop", 0)
            .WindowHeight = PropBag.ReadProperty(Header & "WindowWidth", 0)
            .WindowWidth = PropBag.ReadProperty(Header & "WindowTop", 0)
        End With
    
    End Sub

    Public Sub WritePB(Header As String, PropBag As PropertyBag)
    
        With Me
            Call PropBag.WriteProperty(Header & "Caption", .Caption, "<No Caption>")
            Call PropBag.WriteProperty(Header & "CmpPID", .CmpPID, "<No CmpPID>")
            Call PropBag.WriteProperty(Header & "Path", .Path, "<No Path>")
            Call PropBag.WriteProperty(Header & "Interval", .Interval, "<No Interval>")
            Call PropBag.WriteProperty(Header & "MgrPID", .MgrPID, "<No MgrPID>")
            Call PropBag.WriteProperty(Header & "Description", .Description, "<No Description>")
            Call PropBag.WriteProperty(Header & "Notes", .Notes, "<No Notes>")
        
            Call UpdateWindowProperties
            
            Call PropBag.WriteProperty(Header & "WindowLeft", .WindowLeft, 0)
            Call PropBag.WriteProperty(Header & "WindowTop", .WindowTop, 0)
            Call PropBag.WriteProperty(Header & "WindowWidth", .WindowHeight, 0)
            Call PropBag.WriteProperty(Header & "WindowTop", .WindowWidth, 0)
        End With
    
    End Sub
