VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Locator"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

    Implements IMA2.ILocator
    Implements IMA2.IComponent
    Implements IMA2.IContainer

'**************************************************************************************************
' Base Class Implementation
'**************************************************************************************************
    Private Sub Class_Initialize()
        g_InstanceCount = g_InstanceCount + 1
        If g_InstanceCount > 1 Then Call LogEvent(Str(g_InstanceCount), NewInstance)
    End Sub

    Private Sub Class_Terminate()
        g_InstanceCount = g_InstanceCount - 1
        Call LogEvent(Str(g_InstanceCount), ReleaseInstance)
    End Sub

'**************************************************************************************************
' Default Interface
'**************************************************************************************************
    Public Function FilePath() As String
        FilePath = App.Path
    End Function

'**************************************************************************************************
'IComponent Interface
'**************************************************************************************************

    '----------------------------------------------------------------------------------------------
    'IMA2 Component Constructor & Destructor
    '----------------------------------------------------------------------------------------------
    Private Sub IComponent_Construct(ByVal Path As String, ByVal PID As String, pAL As IMA2.ILocator)
        'Nothing much to do here
    End Sub
    
    Private Sub IComponent_Destruct()
        End                                     'Shutdown locator
    End Sub
    
    '----------------------------------------------------------------------------------------------
    'IMA2 Component distributing and binding info
    '----------------------------------------------------------------------------------------------
    Private Property Get IComponent_Distributing() As IMA2.IMA2_DistributingInfo
        IComponent_Distributing = g_DI          'Pass on our distributing info
    End Property
    
    Private Property Get IComponent_Bindings() As IMA2.IBindings
        Set IComponent_Bindings = Nothing       'No bindings on Locator
    End Property
    
    '----------------------------------------------------------------------------------------------
    'IMA2 Component serialization functions
    '----------------------------------------------------------------------------------------------
    Private Sub IComponent_Load(ByVal Data As Variant):     End Sub
    Private Function IComponent_Save() As Variant:          End Function
    
    Private Function IComponent_DataSize() As Long
        IComponent_DataSize = 0                 'No data to save
    End Function
    

'**************************************************************************************************
'ILocator Interface
'**************************************************************************************************
    Private Function IContainer_CreateComponent(ByVal PID As String, ByVal Machine As String) As IMA2.IComponent
        On Error Resume Next
        Set IContainer_CreateComponent = CreateObject(PID, Machine)
        If Err Then
            Err.Clear
            Call LogEvent("Component creation error - " & Err.Description, NewInstance)
        End If
    End Function
    
    Private Function IContainer_Locator() As IMA2.ILocator
        Set IContainer_Locator = Me 'Return ourself
    End Function
    
    Private Property Get IContainer_InnateComponents() As String()
        'No innate children. :(
    End Property
    
    Private Function IContainer_LocateChild(ByVal Path As String) As IMA2.IComponent
        If ParentFromPath(Path) <> g_DI.Path Then
            Exit Function
        Else
            Set IContainer_LocateChild = ILocator_Locate(Path)
        End If
    End Function
    
    Private Sub IContainer_AddChild(ByVal Path As String, Child As IMA2.IComponent)
        'Not necessary in Locator
    End Sub
    
    Private Sub IContainer_RemoveChild(ByVal Path As String)
        'Not necessary in Locator
    End Sub

    Private Property Get IContainer_ChildComponents() As String()
        'Not necessary in Locator
    End Property
    

'**************************************************************************************************
'ILocator Interface
'**************************************************************************************************

    '----------------------------------------------------------------------------------------------
    'ILocator Locating
    '----------------------------------------------------------------------------------------------
    Private Function ILocator_Locate(ByVal Path As String) As IMA2.IComponent
        
        On Error Resume Next
        
        Dim CP As String
        Dim LP As String
        
        CP = LCase(Path)                                    'Component path
        LP = LCase(LocatorFromPath(CP))                     'Locator path
        
        If StrCount(CP, "\") = 2 Then                       'Is it a locator we're looking for?
            Set ILocator_Locate = FindLocator(CP)           'Try to find it in the locators collection.
        ElseIf LP = LCase("\\" + g_Machine) Then            'Is it a local component?
            Set ILocator_Locate = FindLocalComponent(CP)    '
        Else                                                'Is it a remote component?
            Set ILocator_Locate = FindRemoteComponent(CP)   '
        End If
        
        If Err Then
            Err.Clear
            Call LogEvent("Locating error - " & Err.Description, NotLocated)
        End If
    
    End Function
    
    '----------------------------------------------------------------------------------------------
    'ILocator Registration
    '----------------------------------------------------------------------------------------------
    Private Sub ILocator_Register(ByVal Cmp As IMA2.IComponent)
        
        On Error Resume Next
        
        Dim CP  As String
        
        CP = Cmp.Path
        If g_Components.InArray(CP) Then
            Call g_Components.Remove(CP)
            Call LogEvent(CP, Unregistered)
        End If
        
        Call g_Components.Add(Cmp, CP)
        Call LogEvent(CP, Registered)
        Call g_EventQueue.Add(1, CP, True)
        
        If Err Then
            Err.Clear
            Call LogEvent("Registering error - " & Err.Description, NotRegistered)
        End If
    
    End Sub
    
    Private Sub ILocator_Unregister(ByVal Path As String)
        
        On Error Resume Next
        
        Dim CP  As String
        
        CP = Path
        If g_Components.InArray(CP) Then
            Call g_Components.Remove(CP)
            Call LogEvent(CP, Unregistered)
            Call g_EventQueue.Add(1, CP, False)
        Else
            Call LogEvent(CP, NotUnregistered)
        End If
    
        If Err Then
            Err.Clear
            Call LogEvent("Locating error - " & Err.Description, NotUnregistered)
        End If
    
    End Sub

    '----------------------------------------------------------------------------------------------
    ' ILocator Batch Functionality
    '----------------------------------------------------------------------------------------------
    Private Function ILocator_BatchOperation(ByVal Operation As String, Args() As Variant) As Variant()
        
        Dim LB As Integer, UB As Integer, I As Integer
        
        LB = LBound(Args)
        UB = UBound(Args)

        Select Case LCase(Operation)
            Case "locate":
                ReDim RetVal(LB To UB) As Variant
                For I = LB To UB: Set RetVal(I) = ILocator_Locate(Args(I)): Next I
                ILocator_BatchOperation = RetVal
            Case "register":    For I = LB To UB: Call ILocator_Register(Args(I)): Next I
            Case "unregister":  For I = LB To UB: Call ILocator_Unregister(Args(I)): Next I
            Case "connect":     For I = LB To UB: Call ILocator_Connect(Args(I)): Next I
            Case "disconnect":  For I = LB To UB: Call ILocator_Disconnect(Args(I)): Next I
            Case "subscribe":   For I = LB To UB Step 3: Call ILocator_Subscribe(Args(I + 0), Args(I + 1), Args(I + 2)): Next I
            Case "unsubscribe": For I = LB To UB Step 3: Call ILocator_Unsubscribe(Args(I)): Next I
            Case Else:
        End Select
    
    End Function

    '----------------------------------------------------------------------------------------------
    'ILocator Properties
    '----------------------------------------------------------------------------------------------
    Private Property Get ILocator_Clients() As String()
        ILocator_Clients = Variant2Strings(g_Clients.Keys)
    End Property
    
    Private Property Get ILocator_Components() As String()
        ILocator_Components = Variant2Strings(g_Components.Keys)
    End Property
    
    Private Property Get ILocator_Locators() As String()
        ILocator_Locators = Variant2Strings(g_Locators.Keys)
    End Property
    
    Private Property Get ILocator_Machine() As String
        ILocator_Machine = g_Machine
    End Property

    '----------------------------------------------------------------------------------------------
    'ILocator Locator Connection
    '----------------------------------------------------------------------------------------------
    Private Sub ILocator_Connect(ByVal Machine As String)
        If g_Locators.InArray(Machine) Then Exit Sub
        Dim L As ILocator
        Set L = CreateObject("IMA2_Locator.Locator", Machine)
        Call g_Locators.Add(L, Machine)
        Call ILocator_Register(L)
        Call LogEvent(Machine, Connected)
    End Sub
    
    Private Sub ILocator_Disconnect(ByVal Machine As String)
        If Not g_Locators.InArray(Machine) Then Exit Sub
        Call ILocator_Unregister(g_Locators(Machine))
        Call g_Locators.Remove(Machine)
        Call LogEvent(Machine, Disconnected)
    End Sub
    
    '----------------------------------------------------------------------------------------------
    'ILocator Event Serving
    '----------------------------------------------------------------------------------------------
    Private Sub ILocator_Subscribe(ByVal Sink As IMA2.ILocatorEvents, ByVal Key As String, ByVal Flags As Long)
        If g_Clients.InArray(Key) Then Call g_Clients.Remove(Key)
        Dim X As New CSubscriber
        X.Key = Key
        Set X.Sink = Sink
        Call g_Clients.Add(X, Key)
        Call LogEvent(Key, Subscribed)
    End Sub
    
    Private Sub ILocator_Unsubscribe(ByVal Key As String)
        If Not g_Clients.InArray(Key) Then Exit Sub
        If g_Clients.InArray(Key) Then
            Call g_Clients.Remove(Key)
            Call LogEvent(Key, UnSubscribed)
        Else
            Call LogEvent(Key, NotUnsubscribed)
        End If
    End Sub

'**************************************************************************************************
'Miscellaneous private functions
'**************************************************************************************************

    Private Function FindLocator(CP As String) As ILocator
    
        If CP = LCase(g_Path) Then                      'They're trying to find *us*
            Set FindLocator = g_Locator                 'Return us
            Call LogEvent(CP, Located)                  'Log it
        Else                                            'They're not trying to find *us*
            If g_Locators.InArray(CP) Then              'Check if it's in the locators array.
                Set FindLocator = g_Locators(CP)        'if so, find it.
                Call LogEvent(CP, Located)              'Log it.
            Else                                        'Didn't find it
                Call LogEvent(CP, NotLocated)           'Log it.
            End If
        End If
    
    End Function

    Private Function FindLocalComponent(CP As String) As IComponent
    
        If g_Components.InArray(CP) Then
            Set FindLocalComponent = g_Components(CP)
            Call LogEvent(CP, Located)
        Else
            Call LogEvent(CP, NotLocated)
        End If
    
    End Function

    Public Function FindRemoteComponent(CP As String) As IComponent
    
        Dim LP      As String
        Dim RAL     As ILocator
        Dim C       As IComponent
            
        LP = LocatorFromPath(CP)            'Locator path
        
        If g_Locators.InArray(LP) Then
            Set RAL = g_Locators(LP)
            Set C = RAL.Locate(CP)
            If NN(C) Then
                Set FindRemoteComponent = C
                Call LogEvent(CP, Located)
            Else
                Call LogEvent(CP, NotLocated)
            End If
        Else
            Call LogEvent(CP, NotLocated)
        End If
        
    End Function

