VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Agent"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

    
    Implements IComponent                   'Needed for all IMA2 components.
        
        Dim m_Path          As String       'Component's path
        Dim m_PID           As String       'Component's COM ProgID
        Dim m_Machine       As String       'Component's host machine
        Dim m_Activated     As Boolean      'Flag indicating the component is active
        Dim m_Process       As Long         'Component's process ID
        Dim m_Thread        As Long         'Component's thread ID
        Dim m_AL            As ILocator     'Component's Locator pointer (where it is registered)
        Dim m_Bindings      As IBindings    'Component's binding collection
    
    Implements IContainer                   'Needed for containers

'********************************************************************************************
' Default interface (All the stuff that makes your component unique.)
'********************************************************************************************


'********************************************************************************************
' IComponent
' - Default IMA2 interface for all components.
' - ** Copy this section to your code exactly as it is here. **
'********************************************************************************************

    'Called when the component is created.
    Private Sub IComponent_Construct(ByVal Path As String, ByVal PID As String, AL As IMA2.ILocator)
        m_Machine = LocalMachine()
        m_Process = CurrentProcessID()
        m_Thread = CurrentThreadID()
        m_Path = Path
        m_PID = PID
        Set m_AL = AL
 '      Set m_Bindings = CreateObject("IMA2_Bindings.Bindings")
 '      Call m_Bindings.Construct(Path, AL)
    End Sub
    
    'Called when the component is destroyed.
    Private Sub IComponent_Destruct()
'        Call m_Bindings.Destruct
'        End
    End Sub
    
    'Called to query how large the data in the component is.
    Private Function IComponent_DataSize() As Long
        IComponent_DataSize = 0
    End Function
    
    'Called to deserialize the component. (Data is what you stored in IComponent_Save())
    Private Sub IComponent_Load(ByVal Data As Variant)
    End Sub
    
    'Called to query the component's Process ID.
    Private Property Get IComponent_Process() As Long
        IComponent_Process = m_Process
    End Property
    
    'Called to query the component's Thread ID.
    Private Property Get IComponent_Thread() As Long
        IComponent_Thread = m_Thread
    End Property

    'Called to serialize the component. (Whatever you pass as the result value will be saved to a file.)
    Private Function IComponent_Save() As Variant
    End Function
    
    'Assigns a new state to the component. (You can change this)
    'Format: RHS(1) = Default Component Parameters (See AB2000->Component->Properties)
    'Format: RHS(2..X) = Other properties defined by you.
    Private Property Let IComponent_State(ByVal RHS As Variant)
    End Property
    
    'Retrieves the component state. (You can change this, but keep the ComponentState() call.)
    Private Property Get IComponent_State() As Variant
        IComponent_State = ComponentState(Me)
    End Property
    
    'Called to set the component to active or inactive.
    Private Property Get IComponent_Activated() As Boolean
        IComponent_Activated = m_Activated
    End Property
    
    Private Property Let IComponent_Activated(ByVal RHS As Boolean)
        m_Activated = RHS
    End Property
    
    Private Property Get IComponent_Machine() As String
        IComponent_Machine = m_Machine
    End Property
    
    Private Property Get IComponent_Path() As String
        IComponent_Path = m_Path
    End Property
    
    Private Property Get IComponent_PID() As String
        IComponent_PID = m_PID
    End Property

    Private Property Get IComponent_Bindings() As IMA2.IBindings
        Set IComponent_Bindings = m_Bindings
    End Property

'********************************************************************************************
' IContainer
' - Implemented only by components that will contain other components.
'********************************************************************************************

    Private Function IContainer_CreateComponent(ByVal PID As String, ByVal Machine As String) As IMA2.IComponent
        Set IContainer_CreateComponent = CreateObject(PID, Machine)
    End Function
    
    Private Property Get IContainer_InnateComponents() As IComponent()
    End Property
    
    Private Function IContainer_Locator() As IMA2.ILocator
        Set IContainer_Locator = m_AL
    End Function


