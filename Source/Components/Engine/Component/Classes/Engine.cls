VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Engine"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
'********************************************************************************************
' Class:        BasicIMA.Engine
' Author:       Roberto Olivares (olivarre@vuse.vanderbilt.edu)
' Last update:  (8/13/04) by Juan Rojas (juan.rojas@vanderbilt.edu)
'
' Description:  This is a simple IMA2 engine that calls a method (Engine.Method) on a list
'               of registered IMA2 components (Engine.Clients) every (Engine.Interval) seconds.
'               Clients do not have to implement any special interfaces. they just have to
'               have a public function named (Engine.Method).
'
' Notes:        - Do not add your own path to the Clients() list. You will not be called because
'                 you have blocked your own thread.
'               - Args is an optional item. It's not working yet. Leave it alone.
''********************************************************************************************

    Option Explicit                                     'Code like a man

    Implements IComponent                               'Inherits IComponent interface.
    Dim m_Path      As String                           'Needed for IComponent.
    Dim m_PID       As String                           'Needed for IComponent.
    Dim m_Machine   As String                           'Needed for IComponent.
    Dim m_Activated As Boolean                          'Needed for IComponent.
    Dim m_Bindings  As IBindings                        'Needed for IComponent.
    Dim m_AL        As ILocator                         'Needed for IComponent.
    Dim m_DI        As IMA2_DistributingInfo            'Needed for IComponent.
    
'********************************************************************************************
' Default interface (Define YOUR properties and methods here.)
'********************************************************************************************

    Dim m_Timer     As Timer        'Timer control that dispatches notifications.
Attribute m_Timer.VB_VarHelpID = -1
    
    Dim m_Clients() As String       'List of client component paths.
    Dim m_Args      As String       'Arguments to be passed to the components.
    Dim m_Method    As String       'Method to be called on the clients.

'   Gets the interval (in milliseconds) at which the components should be notified.
    Public Property Get Interval() As Long
        Interval = m_Timer.Interval
    End Property

'   Sets the interval (in milliseconds) at which the components should be notified.
    Public Property Let Interval(NewVal As Long)
        If Not m_Activated Then m_Timer.Interval = NewVal
    End Property

'   Gets the name of the method that will be called on each component.
    Public Property Get Method() As String
        Method = m_Method
    End Property
    
'   Sets the name of the method that will be called on each component.
    Public Property Let Method(NewVal As String)
        If Not m_Activated Then m_Method = NewVal
    End Property

'   Gets the arguments of the method that will be called on each component.
    Public Property Get Args() As String
        Args = m_Args
    End Property
    
'   Sets the arguments of the method that will be called on each component. (optional)
    Public Property Let Args(NewVal As String)
        If Not m_Activated Then m_Args = NewVal
    End Property

'   Calls a method by name (Engine.Method) on the list of clients specified by Engine.Clients()
    Public Sub NotifyClients()
    
        Dim C As Object
        Dim I As Long
    
        If m_Method = "" Then Exit Sub
        
        For I = LBound(m_Clients) To UBound(m_Clients)
            Set C = m_AL.Locate(m_Clients(I))
            If C Is Nothing Then
                Debug.Print m_Path & " (Engine): " & m_Clients(I) & " could not be notified."
            Else
                On Error Resume Next
                If Len(m_Args) = 0 Then
                    Call CallByName(C, m_Method, VbMethod)
                Else
                    Call CallByName(C, m_Method, VbMethod, m_Args)
                End If
                Debug.Print Err.Number & " - " & Err.Description
                Err.Clear
           End If
        Next I
    
    End Sub

'********************************************************************************************
' Private functions
'********************************************************************************************



'********************************************************************************************
' IMA2 overloaded IComponent functions
' - You can overload these if you like. Most people overload OnActivate and OnDeactivate
'********************************************************************************************

    Private Sub OnActivate()
'   This is the code you wish to execute when the component is activated. (Required)
'       Set m_InCmp = m_AL.Locate(m_InPath)
'       Set m_OutCmp = m_AL.Locate(m_OutPath)

        m_Timer.Enabled = True

    End Sub

    Private Sub OnDeactivate()
        'This is the code you wish to execute when the component is deactivated. (Required)
'        Set m_InCmp = Nothing
'        Set m_OutCmp = Nothing
    
        m_Timer.Enabled = False
    
    End Sub

    Private Sub OnConstruct()
        'This is the code you wish to execute when the component is created. (Optional)
        Call m_Bindings.Settings.Add("Clients", , , , BT_Collection)     'Set up the clients bindings array.
        Set m_Timer = Form1.CreateTimer(Me)
    End Sub
    
    Private Sub OnDestruct()
        'This is the code you wish to execute before the component is destroyed. (Optional)
        Call Form1.ReleaseTimer(m_Timer)
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
            .WriteProperty "Interval", m_Timer.Interval
            .WriteProperty "Method", m_Method
            .WriteProperty "Clients", Join(m_Clients, vbCrLf)
            .WriteProperty "Args", m_Args
        End With
        OnSaveData = PB.Contents
        
    End Function

    Private Sub OnLoadData(Data As Variant)
        'This should return the data you wish to save to a file. (Optional)
        '  Example:  OnLoadData = Array(m_BinaryData, "MyData", 1, 2 3)
        
        Dim PB As New PropertyBag                                   'I like PropertyBags - RTFM
        PB.Contents = Data                                          'Assign the data we saved.
        With PB
            m_Timer.Interval = .ReadProperty("Interval")            'Get the interval property
            m_Method = .ReadProperty("Method")                      'Get the method property
            m_Clients = Split(.ReadProperty("Clients"), vbCrLf)     'Get & decode the clients property
            m_Args = .ReadProperty("Args")                          'Get the args property
        End With
    
    End Sub

    Private Function OnGetState() As Variant
        'This should return a list of variable names and their values for the user to see. (Optional)
        '  Example:  OnGetState = Array( Array("MyValue", m_Value), Array("MyCmpPath", m_MyCmpPath) )
        'OnGetState = Array(Array("Interval", m_Timer.Interval), _
                            Array("Method", m_Method), _
                            Array("Args", m_Args), _
                            Array("Clients", Join(m_Clients, ",")))
    
    End Function

    Private Sub OnLetState(Data As Variant)
        'You should set the variables you returned in GetState() (Optional)
        '  Example:
        '
        ' Dim I As Integer
        '
        ' For I = 0 To UBound(Data) Step 1                    'Only set properties are returned.
        '     Select Case Data(I)(0)                          'Check the title
        '         Case "MyValue": m_MyValue = Data(I)(1)      'Set our first variable
        '         Case "MyCmpPath": m_MyCmpPath = Data(I)(1)  'Set our other variable
        '         Case Else:                                  'Unknown property
        '     End Select
        ' Next I
    End Sub

'********************************************************************************************
'********************************************************************************************
' IComponent
' - This is the default IMA2 interface for all components. (In C++ this is a base class)
' - ** Copy this section to your code exactly as it is here. Do NOT change it. **
'********************************************************************************************
'********************************************************************************************

    'Called when the component is created by a client.
    Private Sub IComponent_Construct(ByVal Path As String, ByVal PID As String, pAL As IMA2.ILocator)
        m_Machine = LocalMachine()                          'Save the machine we're running on.
        m_Path = Path                                       'Save our path.
        m_PID = PID                                         'Save our PID
        Set m_AL = pAL                                      'Get our pointer to the Agent Locator.
        Set m_Bindings = GetBindingsObject()                'Create our bindings object.
        Call m_Bindings.Settings.Construct(m_Path, m_AL)    'Construct our bindings collection.
        Call OnConstruct                                    'Pass on the event to the overloaded function.
    End Sub
    
    'Called when the component is destroyed.
    Private Sub IComponent_Destruct()
        Call OnDestruct                                     'Pass on the event to the overloaded function.
        Call m_Bindings.Settings.Destruct                   'Destroy our bindings collection.
    End Sub
    
    'Called to retrieve the process in which the component resides.
    Private Property Get IComponent_Bindings() As IMA2.IBindings
        Set IComponent_Bindings = m_Bindings
    End Property

    'Called to retrieve the process in which the component resides.
    Private Property Get IComponent_Process() As Long
        IComponent_Process = CurrentProcessID()
    End Property

    'Called to retrieve the thread on which the component resides.
    Private Property Get IComponent_Thread() As Long
        IComponent_Thread = CurrentThreadID()
    End Property

    'Called to query how large the data in the component is.
    Private Function IComponent_DataSize() As Long
        IComponent_DataSize = OnDataSize                    'Pass on the event to the overloaded function.
    End Function
    
    'Called to deserialize the component.
    '   Data As Variant - What you stored in IComponent_Save())
    Private Sub IComponent_Load(ByVal Data As Variant)
        Call OnLoadData(Data)                               'Pass on the event to the overloaded function.
    End Sub
    
    'Called to serialize the component.
    '   IComponent_Save - The result value will be saved to a file.
    Private Function IComponent_Save() As Variant
        IComponent_Save = OnSaveData()                      'Pass on the event to the overloaded function.
    End Function
    
    'Assigns a new state to the component.
    Private Property Let IComponent_State(ByVal RHS As Variant)
        'Call OnLetState(RHS(1))                             'Pass on the event to the overloaded function.
    End Property
    
    'Retrieves the component state.
    Private Property Get IComponent_State() As Variant
        'IComponent_State = ComponentState(Me, OnGetState()) 'Pass on the event to the overloaded function.
    End Property
    
    'Returns our activation state.
    Private Property Get IComponent_Activated() As Boolean
        IComponent_Activated = m_Activated                  'Return our activation state
    End Property
    
    'Sets our activation state.
    Private Property Let IComponent_Activated(ByVal RHS As Boolean)
        m_Activated = RHS
        If RHS Then Call OnActivate Else Call OnDeactivate  'Set our activation state
    End Property
    
    'Returns the name of the machine we're running on.
    Private Property Get IComponent_Machine() As String
        IComponent_Machine = m_Machine                      'Return our machine name
    End Property
    
    'Returns our component path.
    Private Property Get IComponent_Path() As String
        IComponent_Path = m_Path                            'Return our path
    End Property
    
    'Returns our COM ProgID. (ProjectName.ClassName)
    Private Property Get IComponent_PID() As String
        IComponent_PID = m_PID                              'Return our ProgID
    End Property


