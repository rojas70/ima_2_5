VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "MgrPage"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder6" ,"Yes"
Attribute VB_Ext_KEY = "Member0" ,"MgrPageCollection"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
Option Explicit

    Public TabControl   As MSComctlLib.Tab
    Public Managers     As New MgrInfoCollection
    Public Description  As String
    Public Caption      As String
    
    Public Function CleanUp()
        Call Managers.RemoveAll
    End Function

    Public Sub WritePB(Header As String, PropBag As PropertyBag)
        Call Managers.WritePB(Header & "MgrInfos", PropBag)
        Call PropBag.WriteProperty(Header & "Description", Description)
        Call PropBag.WriteProperty(Header & "Caption", Caption)
    End Sub
    
    Public Sub ReadPB(Header As String, PropBag As PropertyBag)
        Call Managers.ReadPB(Header & "MgrInfos", PropBag)
        Description = PropBag.ReadProperty(Header & "Description")
        Caption = PropBag.ReadProperty(Header & "Caption")
    End Sub
    
    
