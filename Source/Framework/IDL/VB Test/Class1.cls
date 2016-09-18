VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Class1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Implements IComponent
Implements IContainer
Implements ILocator
Implements ILocatorEvents
Implements IManager

Private Property Get IComponent_Activated() As Boolean

End Property

Private Property Let IComponent_Activated(ByVal RHS As Boolean)

End Property

Private Sub IComponent_Construct(ByVal Path As String, ByVal PID As String, AL As IMA2.ILocator)

End Sub

Private Function IComponent_DataSize() As Long

End Function

Private Sub IComponent_Destruct()

End Sub

Private Sub IComponent_Load(ByVal Data As Variant)

End Sub

Private Property Get IComponent_Machine() As String

End Property

Private Property Get IComponent_Path() As String

End Property

Private Property Get IComponent_PID() As String

End Property

Private Property Get IComponent_Process() As Long

End Property

Private Function IComponent_Save() As Variant

End Function

Private Property Let IComponent_State(ByVal RHS As Variant)

End Property

Private Property Get IComponent_State() As Variant

End Property

Private Property Get IComponent_Thread() As Long

End Property

Private Function IContainer_CreateComponent(ByVal PID As String, ByVal Machine As String) As IMA2.IComponent

End Function

Private Property Get IContainer_InnateComponents() As IMA2.IComponent()

End Property

Private Function IContainer_Locator() As IMA2.ILocator

End Function

Private Function ILocator_BatchOperation(ByVal Operation As String, Args() As Variant) As Variant()

End Function

Private Property Get ILocator_Clients() As String()

End Property

Private Property Get ILocator_Components() As String()

End Property

Private Sub ILocator_Connect(ByVal Machine As String)

End Sub

Private Sub ILocator_Disconnect(ByVal Machine As String)

End Sub

Private Function ILocator_Locate(ByVal Path As String) As IMA2.IComponent

End Function

Private Property Get ILocator_Locators() As String()

End Property

Private Property Get ILocator_Machine() As String

End Property

Private Sub ILocator_Register(ByVal Cmp As IMA2.IComponent)

End Sub

Private Sub ILocator_Subscribe(ByVal Sink As IMA2.ILocatorEvents, ByVal Key As String, ByVal Flags As Long)

End Sub

Private Sub ILocator_Unregister(ByVal Path As String)

End Sub

Private Sub ILocator_Unsubscribe(ByVal Key As String)

End Sub

Private Sub ILocatorEvents_OnConnect(ByVal Machine As String)

End Sub

Private Sub ILocatorEvents_OnDisconnect(ByVal Machine As String)

End Sub

Private Sub ILocatorEvents_OnRegister(ByVal Path As String)

End Sub

Private Sub ILocatorEvents_OnSubscribe(ByVal Key As String)

End Sub

Private Sub ILocatorEvents_OnUnregister(ByVal Path As String)

End Sub

Private Sub ILocatorEvents_OnUnSubscribe(ByVal Key As String)

End Sub

Private Sub IManager_AddComponent(C As IMA2.IComponent)

End Sub

Private Sub IManager_RemoveComponent(C As IMA2.IComponent)

End Sub

Private Sub IManager_Update(Optional Flags As Variant)

End Sub
