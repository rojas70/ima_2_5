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

    Implements IMA2.IComponent
    Implements IMA2.IContainer
    
    Implements IMA2.ILocator
    Implements IMA2.ILocatorAdvanced

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
    Private Sub IComponent_Load(ByVal Data As Variant)
    End Sub
    
    Private Function IComponent_Save() As Variant
    End Function
    
    Private Function IComponent_DataSize() As Long
        IComponent_DataSize = 0                 'No data to save
    End Function
    

'**************************************************************************************************
'IContainer Interface
'**************************************************************************************************
    Private Function IContainer_CreateComponent(ByVal PID As String, ByVal Machine As String) As IMA2.IComponent
        On Error Resume Next
        Set IContainer_CreateComponent = CreateObject(PID, Machine)
        If Err Then
            Call LogEvent("Component creation error - " & Err.Description, NewInstance)
            Err.Clear
        End If
    End Function
    
    Private Property Get IContainer_InnateComponents() As String()
        'No innate children. :(
    End Property

'**************************************************************************************************
'ILocator Interface
'**************************************************************************************************

    'ILocator Locating
    Private Function ILocator_Locate(ByVal Path As String) As IMA2.IComponent
        
        On Error Resume Next
        
        Dim CP As String
        Dim LP As String
        
        CP = LCase(Path)                                    'Component path
        LP = LCase(LocatorFromPath(CP))                     'Locator path
        
        If StrCount(CP, "\") = 2 Then                       'Is it a locator we're looking for?
            Set ILocator_Locate = FindLocator(CP)           'Try to find it in the locators collection.
        ElseIf LP = LCase("\\" + g_DI.Machine) Then            'Is it a local component?
            Set ILocator_Locate = FindLocalComponent(CP)    '
        Else                                                'Is it a remote component?
            Set ILocator_Locate = FindRemoteComponent(CP)   '
        End If
        
        If Err Then
            Call LogEvent("Locating error - " & Err.Description, NotLocated)
            Err.Clear
        End If
    
    End Function
    
    Private Property Get ILocator_Machine() As String
        ILocator_Machine = g_DI.Machine
    End Property
    
'**************************************************************************************************
'ILocatorAdvanced Interface
'**************************************************************************************************
    
    Private Sub ILocatorAdvanced_Register(ByVal Cmp As IMA2.IComponent)
        On Error Resume Next
        Dim CP              As String
        Dim DI(0)           As IMA2.IMA2_DistributingInfo
        Dim Loc             As ILocatorAdvanced
        Dim I               As Integer
        
        'Get the distributing information and the path
        DI(0) = Cmp.Distributing
        CP = DI(0).Path
        
        'Only put component in list if it belongs to this locator
        If LCase(LocatorFromPath(CP)) = LCase(g_DI.Path) Then
             'If the component is already registered...
             If g_Components.InArray(CP) Then
                 Call g_Components.Remove(CP)            'Remove it
                 Call g_DIs.Remove(CP)                   'Remove its description
                 Call LogEvent(CP, Unregistered)         'Log the event
             End If
                   
             'Add the component and its distributing information.
             Call g_Components.Add(Cmp, CP)
             Call g_DIs.Add(DI(0), CP)
        End If
             
        Call LogEvent(CP, Registered)
        
        'Notify the information and event services
        Call g_EventService.OnRegistrationEvent(LE_Register, DI)
        Call g_InfoService.OnRegistrationEvent(LE_Register, DI)
'**     Call g_EventQueue.Add(1, CP, True)

        'Register the component on all connected locators
        'if the component belongs to this locator
        If (LCase(LocatorFromPath(CP)) = LCase(g_DI.Path)) Then
            For I = 0 To g_Locators.Count - 1
                Set Loc = g_Locators(I)
                Call Loc.Register(Cmp)
            Next I
        End If
        
        If Err Then
            Call LogEvent("Registering error - " & Err.Description, NotRegistered)
            Err.Clear
        End If
    End Sub
    
    Private Sub ILocatorAdvanced_Unregister(ByVal Path As String)
        On Error Resume Next
        Dim CP      As String
        Dim DI(0)   As IMA2_DistributingInfo
        Dim I       As Integer
        Dim Loc     As ILocatorAdvanced
        
        CP = Path
        If StrComp(CP, "\\") = 0 Then Exit Sub  'Changed 1/17/06 by CLC to allow unregistering Locators.
        
        'Unregister the component on all connected locators
        'if the component belongs to this locator
        If (LCase(LocatorFromPath(CP)) = LCase(g_DI.Path)) Then
            For I = 0 To g_Locators.Count - 1
                Set Loc = g_Locators(I)
                Call Loc.Unregister(CP)
            Next I
        End If
       
        If g_Components.InArray(CP) Then
            DI(0) = g_DIs.Item(CP)
            Call g_Components.Remove(CP)
            Call g_DIs.Remove(CP)
            Call LogEvent(CP, Unregistered)

            'Notify the information and event services
            Call g_EventService.OnRegistrationEvent(LE_UnRegister, DI)
            Call g_InfoService.OnRegistrationEvent(LE_UnRegister, DI)
        ElseIf (LCase(LocatorFromPath(CP)) <> LCase(g_DI.Path)) Then
            DI(0) = FindRemoteComponent(CP).Distributing
            Call LogEvent(CP, Unregistered)
            Call g_EventService.OnRegistrationEvent(LE_UnRegister, DI)
            Call g_InfoService.OnRegistrationEvent(LE_UnRegister, DI)
        Else
            Call LogEvent(CP, NotUnregistered)
        End If
    
    
        If Err Then
            Call LogEvent("Unregistration error - " & Err.Description, NotUnregistered)
            Err.Clear
        End If
    End Sub
    
    Private Function ILocatorAdvanced_BatchOperation(Action As IMA2_LocatorAction, Args() As Variant) As Variant()
        
        Dim LB As Integer, UB As Integer, I As Integer
        
        LB = LBound(Args)
        UB = UBound(Args)

        Select Case Action
            Case LE_Locate:
                ReDim RetVal(LB To UB) As Variant
                For I = LB To UB: Set RetVal(I) = ILocator_Locate(Args(I)): Next I
                ILocatorAdvanced_BatchOperation = RetVal
            Case LE_Register:    For I = LB To UB: Call ILocatorAdvanced_Register(Args(I)): Next I
            Case LE_UnRegister:  For I = LB To UB: Call ILocatorAdvanced_Unregister(Args(I)): Next I
            Case LE_Connect:     For I = LB To UB: Call ILocatorAdvanced_Connect(Args(I)): Next I
            Case LE_Disconnect:  For I = LB To UB: Call ILocatorAdvanced_Disconnect(Args(I)): Next I
'            Case LE_Subscribe:   For I = LB To UB Step 3: Call ILocatorEventProvider_Subscribe(Args(I + 0), Args(I + 1), CInt(Args(I + 2))): Next I
'            Case LE_Unsubscribe: For I = LB To UB Step 3: Call ILocatorEventProvider_Unsubscribe(Args(I)): Next I
            Case Else:
        End Select
    
    End Function
    
    Private Sub ILocatorAdvanced_Connect(ByVal Machine As String)
        Dim CompNames() As String
        Dim LocatorNames() As String
        Dim Loc As String
        Dim Cmp As IMA2.IComponent
        Dim I As Integer
        
        'Break potential connection loops
        If g_Locators.InArray(Machine) Then Exit Sub
        If Machine = g_DI.Machine Then Exit Sub
        If LCase(g_DI.Machine) = "sally" And Machine = "129.59.73.67" Then Exit Sub
        
        On Error Resume Next
        Dim L As ILocator
        Dim LA As ILocatorAdvanced
        Set L = CreateObject("IMA2_Locator.Locator", Machine)
        If Err Or L Is Nothing Then
            Call LogEvent(Machine, NotConnected)
            Exit Sub
        End If
        Call g_Locators.Add(L, L.Machine)
        Call LogEvent(L.Machine, Connected)
        Set LA = L
                
        'Registers all components belonging to the other locator.
        'Note: The only components recieved by LA.Components are the
        'ones actually on the machine.
        CompNames = LA.Components
        For I = LBound(CompNames) To UBound(CompNames)
                Set Cmp = ILocator_Locate(CompNames(I))
                Call ILocatorAdvanced_Register(Cmp)
        Next I

        'Connects to all computers that the other computer is connected to.
        LocatorNames = LA.Locators
        For I = LBound(LocatorNames) To UBound(LocatorNames)
            If (Not g_Locators.InArray(LocatorNames(I))) Then Call ILocatorAdvanced_Connect(LocatorNames(I))
        Next I
        
        'Tell the other computer to connect to this computer.
'        If (LCase(g_DI.Machine) <> "sally") Then
            Call LA.Connect(g_DI.Machine)
'        Else
'            Call LA.Connect("129.59.73.67")
'        End If
        
    End Sub
    
    Private Sub ILocatorAdvanced_Disconnect(ByVal Machine As String)
        If Not g_Locators.InArray(Machine) Then Exit Sub
        Dim CompNames() As String
        Dim I As Integer
        Dim Loc As String
        Dim LA As ILocatorAdvanced
        Dim L As ILocator
        
        Set LA = g_Locators(Machine)
        Set L = LA
       
        CompNames = LA.Components
        For I = LBound(CompNames) To UBound(CompNames)
            Call ILocatorAdvanced_Unregister(CompNames(I))
        Next I
                
        Call g_Locators.Remove(Machine)
        Call LogEvent(Machine, Disconnected)
        
        Call LA.Disconnect(g_DI.Machine)
    End Sub
    
    Private Property Get ILocatorAdvanced_Components() As String()
        ILocatorAdvanced_Components = Variant2Strings(g_Components.Keys)
    End Property
    
    Private Property Get ILocatorAdvanced_Locators() As String()
        ILocatorAdvanced_Locators = Variant2Strings(g_Locators.Keys)
    End Property
    
'**************************************************************************************************
'ILocatorEventProvider Interface
'**************************************************************************************************
    
'    Private Property Get ILocatorEventProvider_Clients() As String()
 '       ILocatorEventProvider_Clients = Variant2Strings(g_Clients.Keys)
  '  End Property

   ' Private Sub ILocatorEventProvider_Subscribe(ByVal Sink As ILocatorEvents, ByVal Key As String, Flags As IMA2_LocatorAction)
    '    If g_Clients.InArray(Key) Then Call g_Clients.Remove(Key)
     '   Dim X As New CSubscriber
      '  X.Key = Key
       ' Set X.Sink = Sink
        'Call g_Clients.Add(X, Key)
'        Call LogEvent(Key, Subscribed)
 '   End Sub

  '  Private Sub ILocatorEventProvider_Unsubscribe(ByVal Key As String)
   '     If Not g_Clients.InArray(Key) Then Exit Sub
    '    If g_Clients.InArray(Key) Then
     '       Call g_Clients.Remove(Key)
      '      Call LogEvent(Key, UnSubscribed)
       ' Else
        '    Call LogEvent(Key, NotUnsubscribed)
'        End If
 '   End Sub

'**************************************************************************************************
'Miscellaneous private functions
'**************************************************************************************************

    Private Function FindLocator(CP As String) As ILocator
    
        If CP = LCase(g_DI.Path) Then                       'They're trying to find *us*
            Set FindLocator = g_Locator                 'Return us
            Call LogEvent(CP, Located)                  'Log it
        Else                                            'They're not trying to find *us*
            CP = Mid(CP, 3)         'Added by CLC 1/17/06 to eliminate the "\\" in the machine name.
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

    Private Function FindRemoteComponent(CP As String) As IComponent
    
        Dim LP      As String
        Dim RAL     As ILocator
        Dim C       As IComponent
            
        LP = LocatorFromPath(CP)            'Locator path
        
        If g_Locators.InArray(Mid(LP, 3)) Then
            Set RAL = g_Locators(Mid(LP, 3))
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
