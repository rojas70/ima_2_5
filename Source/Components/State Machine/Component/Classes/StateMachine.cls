VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 1  'Persistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "StateMachine"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
'********************************************************************************************
' Class:        SMCmp.StateMachine
' Author:       Roberto Olivares (olivarre@vuse.vanderbilt.edu)
' Last update:  (12/20/01)
'
' Description:  This is a simple IMA2 engine that calls a method (Engine.Method) on a list
'               of registered IMA2 components (Engine.Clients) every (Engine.Interval) seconds.
'               Clients do not have to implement any special interfaces. they just have to
'               have a public function named (Engine.Method).
'
' Notes:
'
' To Do:        - Add transition capabilities
'               - Add parameter flexibility
'               - Add bindings support (??)
'               - Replace Public variables with property get/put
'               - Remove activated property from representations and mechanisms
'********************************************************************************************

    Option Explicit                                     'Code like a man

    Implements IComponent                               'Inherits IComponent interface.
    Dim m_AL        As ILocator                         'Needed for IComponent.
    Dim m_ES        As Object                           'Get a pointer to the event service to publish our activation/deactivation.
    Dim m_DI        As IMA2_DistributingInfo            'Needed for IComponent.
    Dim m_Bindings  As IBindings                        'Needed for IComponent.
    
'********************************************************************************************
' Default interface (Define YOUR properties and methods here.)
'********************************************************************************************

    Dim m_States        As New States
    Dim m_State         As Integer
    Dim m_Task          As Integer
    Dim m_Action        As Integer
    Dim m_AutoLoop      As Boolean
    
    Dim m_Name          As String
    Dim m_Description   As String
    Dim m_HelpURL       As String
    
    Dim WithEvents m_Timer      As Timer        'Timer control that dispatches notifications.
Attribute m_Timer.VB_VarHelpID = -1
    
'********************************************************************************************
' Public Interface
'********************************************************************************************
    
    '--------------------------------------------------------------------------------------------------------------
    ' Determines whether or not the state machine is currently running.
    '--------------------------------------------------------------------------------------------------------------
    Public Property Get Activated() As Boolean
        Activated = m_Timer.Enabled
    End Property
    
    Public Property Let Activated(NV As Boolean)
        m_Timer.Enabled = NV
        
        'Notify the network we're being activated/deactivated
        Dim S(0 To 0) As String
        S(0) = m_DI.Path
        If NV Then
            Call m_ES.DispatchOtherEvent(IMA2.LE_ActivateSeq, S)
        Else
            Call m_ES.DispatchOtherEvent(IMA2.LE_DeactivateSeq, S)
        End If
        
        'If RHS Then Call OnActivate Else Call OnDeactivate  'Set our activation state
    End Property
    
    '--------------------------------------------------------------------------------------------------------------
    ' Resets the state machine
    '--------------------------------------------------------------------------------------------------------------
    Public Sub Reset()
        Activated = False
        m_State = 0
        m_Task = 0
        m_Action = 0
    End Sub
    
    '--------------------------------------------------------------------------------------------------------------
    ' Atomic get/set for execution point
    '--------------------------------------------------------------------------------------------------------------
    Public Property Get ExecutionPoint() As String
        ExecutionPoint = State & "." & Task & "." & Action  'State.Task.Action
    End Property
    
    Public Property Let ExecutionPoint(NV As String)
        
        Dim S()  As String
        
        If StrCount(NV, ".") <> 2 Then Exit Property
        
        S = Split(NV, ".")
        m_State = Val(S(0))
        m_Task = Val(S(1))
        m_Action = Val(S(2))
    
    End Property
    
    '--------------------------------------------------------------------------------------------------------------
    ' Integer state properties
    '--------------------------------------------------------------------------------------------------------------
    Public Property Get State() As Integer:         State = m_State:                End Property
    Public Property Get Action() As Integer:        Action = m_Action:              End Property
    Public Property Get Task() As Integer:          Task = m_Task:                  End Property
    Public Property Get StateCount() As Integer:    StateCount = m_States.Count:    End Property
    
    '--------------------------------------------------------------------------------------------------------------
    ' Documentation Properties
    '--------------------------------------------------------------------------------------------------------------
    Public Property Get Name() As String:           Name = m_Name:                  End Property
    Public Property Get Description() As String:    Description = m_Description:    End Property
    Public Property Get HelpURL() As String:        HelpURL = m_HelpURL:            End Property
    
    Public Property Let Name(NV As String):         m_Name = NV:                    End Property
    Public Property Let Description(NV As String):  m_Description = NV:             End Property
    Public Property Let HelpURL(NV As String):      m_HelpURL = NV:                 End Property

    '--------------------------------------------------------------------------------------------------------------
    ' Integer state properties
    '--------------------------------------------------------------------------------------------------------------
    Public Property Get States() As States:         Set States = m_States:          End Property
    Public Property Get Interval() As Long:         Interval = m_Timer.Interval:    End Property
    Public Property Get AutoLoop() As Boolean:      AutoLoop = m_AutoLoop:          End Property
    
    Public Property Set States(NV As States):       Set m_States = NV:              End Property
    Public Property Let AutoLoop(NV As Boolean):    m_AutoLoop = NV:                End Property
    Public Property Let Interval(NV As Long):       m_Timer.Interval = NV:          End Property

'********************************************************************************************
' Class Functions
'********************************************************************************************
    
    Private Sub Class_Initialize()
        Set m_Timer = frmTimer.tmr
    End Sub

    '********************************************************************************************
    
    Private Sub Class_ReadProperties(PropBag As PropertyBag)
    
        Set States = PropBag.ReadProperty("States") 'States is an object. PropBag.ReadProperty gets the value
        Name = PropBag.ReadProperty("Name")
        Description = PropBag.ReadProperty("Description")
        m_Timer.Interval = PropBag.ReadProperty("Interval")
        HelpURL = PropBag.ReadProperty("HelpURL")
    
    End Sub
    
    '********************************************************************************************
    
    Private Sub Class_WriteProperties(PropBag As PropertyBag)
    
        Call PropBag.WriteProperty("States", States)    ' Store value in States to "States"
        Call PropBag.WriteProperty("Name", Name)
        Call PropBag.WriteProperty("Interval", m_Timer.Interval)
        Call PropBag.WriteProperty("Description", Description)
        Call PropBag.WriteProperty("HelpURL", HelpURL)
    
    End Sub

'********************************************************************************************
' Control Events
'********************************************************************************************

    Private Sub m_Timer_Timer()
        Call Run
    End Sub

'********************************************************************************************
' Private Functions
'********************************************************************************************
    
    '----------------------------------------------------------------------------------------
    ' Cycles through the state machine and calls the appropriate action
    '----------------------------------------------------------------------------------------
    Private Sub Run()
    
        Dim A As Action
        
        If States.Count = 0 Then Exit Sub
        Set A = CurrentAction()
        
        If A.DoAlways Or (A.DoneOnce = False) Then
            Call ExecuteAction(A)
            A.DoneOnce = True
        End If
        
        Call IncrementAction
    
    End Sub
    
    '----------------------------------------------------------------------------------------
    ' Executes the specified function call on the local component in the action class.
    '----------------------------------------------------------------------------------------
    Private Sub ExecuteAction(A As Action)
    
        Dim C As IComponent
        On Error Resume Next
        
        Set C = m_AL.Locate(A.Parent + "\" + A.Name)
        If Err Then Err.Clear: Exit Sub
        
        If IsEmpty(A.Parameters) Then
            Call CallByName(C, A.FunctionName, VbMethod)
        Else
            Call CallByName(C, A.FunctionName, VbMethod, A.Parameters)
        End If
        
        If Err Then
            Debug.Print Err.Number & " - " & Err.Description
            Err.Clear
        End If

    End Sub

    '*****************************************************************************************
    ' Assign the appropriate state, task, and action.
    
    Private Function CurrentAction() As Action
        Dim S As State
        Dim T As Task
        Dim I As Integer
        
        If (m_State >= States.Count) Then m_State = 0
        Set S = States.Item(m_State)
        
        If (m_Task >= S.Tasks.Count) Then m_Task = 0
        Set T = S.Tasks.Item(m_Task)
        
        If (m_Action >= T.Actions.Count) Then m_Action = 0
        
        If m_Action = 0 Then
            For I = 0 To T.Actions.Count - 1
                T.Actions.Item(I).DoneOnce = False
            Next
        End If

        Set CurrentAction = T.Actions.Item(m_Action)
    End Function
    
    '*****************************************************************************************
    
    Private Sub IncrementAction()
        
        Dim S As State
        Dim T As Task
        Dim A As Action
        
        Set S = States.Item(m_State)
        Set T = S.Tasks.Item(m_Task)
        Set A = T.Actions.Item(m_Action)
        
        m_Action = m_Action + 1
        If (m_Action >= T.Actions.Count) Then m_Action = 0: m_Task = m_Task + 1
        
        If (m_Task >= S.Tasks.Count) Then
            m_Task = 0
            If Not S.AutoLoop Then m_State = m_State + 1
        End If
        
        If (m_State >= States.Count) Then
            If m_AutoLoop Then
                m_State = 0
            Else
                Activated = False
            End If
        End If
        
    End Sub
    
'********************************************************************************************
' IMA2 overloaded IComponent functions
' - You can overload these if you like. Most people overload OnActivate and OnDeactivate
'********************************************************************************************

    Private Sub OnActivate()
        'This is the code you wish to execute when the component is activated. (Required)
        m_Timer.Enabled = True
    End Sub

    Private Sub OnDeactivate()
        'This is the code you wish to execute when the component is deactivated. (Required)
        m_Timer.Enabled = False
    End Sub

    Private Sub OnConstruct()
        'This is the code you wish to execute when the component is created. (Optional)
        Dim BI As IMA2_BindingInfo
        BI.BindType = BT_Collection
        BI.Name = "Clients"
        Call m_Bindings.Settings.Add(BI)        'Set up the clients bindings array.
        Name = NameFromPath(m_DI.Path)          'Assigns the path to the binding
'        Set m_Timer = frmTimer.CreateTimer(Me)
    End Sub
    
    Private Sub OnDestruct()
        'This is the code you wish to execute before the component is destroyed. (Optional)
'        Call Form1.ReleaseTimer(m_Timer)
    End Sub

    Private Function OnDataSize() As Long
        'This should return the size of your component's data. (Optional)
        '  Example:  OnDataSize = UBound(m_Data) * 2
        
        OnDataSize = UBound(OnSaveData)
        
    End Function

    Private Function OnSaveData() As Variant
        'This should return the data you wish to save to a file. (Optional)
        '  Example:  OnSaveData = Array(m_BinaryData, "MyData", 1, 2 3)
        Dim PB As New PropertyBag
        
        With PB
            Call .WriteProperty("States", m_States)
            Call .WriteProperty("Interval", m_Timer.Interval)
            Call .WriteProperty("AutoLoop", m_AutoLoop)
            
            Call .WriteProperty("Name", m_Name)
            Call .WriteProperty("Description", m_Description)
            Call .WriteProperty("HelpURL", m_HelpURL)
        End With
        OnSaveData = PB.Contents        ' PB.Contents contains the property information
                                        ' for the property bag. On SaveDate is of type Variant
                                        ' which means that it will ADOPT the type that it is set to.
                                        ' In this case a property bag.
        
    End Function

    Private Sub OnLoadData(Data As Variant)
        'This should return the data you wish to save to a file. (Optional)
        '  Example:  OnLoadData = Array(m_BinaryData, "MyData", 1, 2 3)
        
        Dim PB As New PropertyBag                                   'I like PropertyBags - RTFM
        PB.Contents = Data                                          'Assign the data we saved.
        
        With PB
            Set m_States = .ReadProperty("States")
            m_Timer.Interval = .ReadProperty("Interval")
            m_AutoLoop = .ReadProperty("AutoLoop")
            
            m_Name = .ReadProperty("Name")
            m_Description = .ReadProperty("Description")
            m_HelpURL = .ReadProperty("HelpURL")
        End With
    
    End Sub

'********************************************************************************************
' IComponent
' - This is the default IMA2 interface for all components. (In C++ this is a base class)
' - ** Copy this section to your code exactly as it is here. Do NOT change it. **
'********************************************************************************************

    'Called to retrieve the process in which the component resides.
    Private Property Get IComponent_Bindings() As IMA2.IBindings
        Set IComponent_Bindings = m_Bindings
    End Property
    
    'Called when the component is created by a client.
    Private Sub IComponent_Construct(ByVal Path As String, ByVal PID As String, pAL As IMA2.ILocator)
        m_DI = GetDistributingInfo(Me, Path, PID)                   'Generate our distributing information.
        Set m_AL = pAL                                              'Get our pointer to the Agent Locator.
        Set m_ES = CreateObject("IMA2_EventService.EventService")   'Get a pointer to the event service to publish our activation/deactivation.
        Set m_Bindings = GetBindingsObject()                        'Create our bindings object.
        Call m_Bindings.Settings.Construct(Path, m_AL)              'Construct our bindings collection.
        Call OnConstruct                                            'Pass on the event to the overloaded function.
    End Sub
    
    'Called when the component is destroyed.
    Private Sub IComponent_Destruct()
        Activated = False
        Call OnDestruct                                     'Pass on the event to the overloaded function.
        Call m_Bindings.Settings.Destruct                   'Destroy our bindings collection.
    End Sub
    
    'Called to query how large the data in the component is.
    Private Function IComponent_DataSize() As Long
        IComponent_DataSize = OnDataSize                    'Pass on the event to the overloaded function.
    End Function
    
    'Called to retrieve distributing information about our component.
    Private Property Get IComponent_Distributing() As IMA2.IMA2_DistributingInfo
        IComponent_Distributing = m_DI
    End Property
    
    'Called to deserialize the component.
    '   Data As Variant - What you stored in IComponent_Save())
    Private Sub IComponent_Load(ByVal Data As Variant)
        Call OnLoadData(Data)                               'Pass on the event to the overloaded function.
    End Sub
    
    'Called to serialize the component.
    '   IComponent_Save - The return value will be saved to a file.
    Private Function IComponent_Save() As Variant
        IComponent_Save = OnSaveData()                      'Pass on the event to the overloaded function.
    End Function
 
