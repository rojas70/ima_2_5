Attribute VB_Name = "MainModule"
    Option Explicit
    
'************************************************************************************************************************
' API Declarations
'************************************************************************************************************************
    
    Declare Function CoLockObjectExternal Lib "ole32.dll" (pUnk As Object, ByVal fLock As Boolean, ByVal fLastUnlockReleases As Boolean) As Long
    
'************************************************************************************************************************
' Global variables
'************************************************************************************************************************
   
    Global g_DIs            As New Collection           'Array of registered components.
    Global g_Components     As IndexedArray             'Array of registered components.
    Global g_Locators       As IndexedArray             'Array of connected locators.
    
    Global g_DI             As IMA2_DistributingInfo    'Holds our Locator's IComponent description
    
    Global g_Locator        As ILocator                 'Our global pointer to the first locator instance
    Global g_EventService   As ILocatorEvents           'Our event service pointer
    Global g_InfoService    As ILocatorEvents           'Our information service provider
    
    Global g_InstanceCount  As Long
    Global g_LogFileNum     As Long
    
'************************************************************************************************************************
' Public Enumerations
'************************************************************************************************************************
    
    Public Enum AL_Events
        Started = 0
        Stopped = 1
        Located = 2
        Registered = 3
        Unregistered = 4
        Subscribed = 5
        UnSubscribed = 6
        Connected = 7
        Disconnected = 8
        NotRegistered = 9
        NotLocated = 10
        NotSubscribed = 11
        NotUnregistered = 12
        NotUnsubscribed = 13
        NotConnected = 14
        NotDisconnected = 15
        RegDispError = 50
        UnRegDispError = 51
        NewInstance = 1000
        ReleaseInstance = 1001
        Initialize = 1002
        EventService = 1003
        InfoService = 1004
    End Enum

'*********************************************************************************************************************
' Main Function
'*********************************************************************************************************************
    
    Public Sub Main()
    
        On Error Resume Next
        
        'Open log file
        Call OpenLogFile("C:\IMA2\System\Locator Log.txt", "C:\IMA2\System\Locator Log (Backup).txt")
        
        'Instantiate Locator object and Event Queue
        Set g_Locator = New Locator
        
        'Obtain a reference to the current event service.
        Set g_EventService = CreateObject("IMA2_EventService.EventService")
        If Err Then Call LogEvent(Err.Source + ": " + Err.Description, EventService): Err.Clear
        
        'Obtain a reference to the information service.
        Set g_InfoService = CreateObject("IMA2_InfoService.InfoService")
        If Err Then Call LogEvent(Err.Source + ": " + Err.Description, InfoService): End
             
        'Enable error handling
        On Error GoTo InitError
        
        'Set up basic Locator properties
        With g_DI
            .Name = SentenceCase(LocalMachine())
            .Path = "\\" + .Name
            .PID = "IMA2_Locator.Locator"
            .Machine = LocalMachine()
            .Thread = CurrentThreadID()
            .Process = CurrentProcessID()
            .IsContainer = True
        End With
        
        'Allocate arrays
        Set g_Components = New IndexedArray
        Set g_Locators = New IndexedArray
        
        'Desensitize to spelling errors
        g_Components.CaseSensitive = False
        g_Locators.CaseSensitive = False
        
        'Add the locator to the registry, but don't reference it
        Call g_Components.Add(Nothing, g_DI.Path)
        
        'Add ourselves to the info service
        Dim DIs(0) As IMA2_DistributingInfo
        DIs(0) = g_DI
        Call g_InfoService.OnRegistrationEvent(LE_Register, DIs)
        
        'Log successful start
        Debug.Print vbCrLf & vbCrLf & vbCrLf & vbCrLf & vbCrLf & vbCrLf & vbCrLf
        Call LogEvent(g_DI.Machine, Started)
        
        'Return
        Exit Sub
        
InitError:
    
        'This would not be good.
        Call LogEvent(Err.Source + ": " + Err.Description, Initialize)
        End
        
    End Sub

    Public Sub test()
    
        Dim Al As ILocator
        Dim C As IComponent
        
  '      Set Al = g_Locator
 '       Set C = Al.Locate("\\mccoy")
'        Debug.Print C.Path
    
    End Sub

'*********************************************************************************************************************
' Logging Functions
'*********************************************************************************************************************

    Public Sub LogEvent(ByVal A As String, E As AL_Events)

        Dim S As String
        Dim M As String
        Dim ES As String
        
        S = DateTime() & vbTab & " [" & Trim(A) & "] "
        
        Select Case E
            Case Started:           M = "Locator v" & App.Major & "." & App.Minor & "." & App.Revision & " started"
            Case Stopped:           M = "Locator stopped"
            Case Located:           M = "located"
            Case Registered:        M = "registered"
            Case Subscribed:        M = "subscribed"
            Case UnSubscribed:      M = "unsubscribed"
            Case Connected:         M = "registered"
            Case Unregistered:      M = "unregistered"
            Case NotConnected:      M = "NOT connected"
            Case NotLocated:        M = "NOT located"
            Case NotRegistered:     M = "NOT registered"
            Case NotUnregistered:   M = "NOT unregistered"
            Case NotSubscribed:     M = "NOT subscribed"
            Case NotUnsubscribed:   M = "NOT unsubscribed"
            Case NotDisconnected:   M = "NOT disconnected"
            Case RegDispError:      M = "ERROR dispatching register event"
            Case UnRegDispError:    M = "ERROR dispatching unregister event"
            Case NewInstance:       M = "outstanding Locator references (+1)"
            Case ReleaseInstance:   M = "outstanding Locator references (-1)"
            Case Initialize:        M = "ERROR initializing Locator"
            Case InfoService:       M = "ERROR initializing Info Service"
            Case EventService:      M = "ERROR initializing Event Service"
        End Select
        
        ES = S & M & "."
        
        Debug.Print ES
        Print #g_LogFileNum, ES
        'Call App.LogEvent(S & M & ".", vbLogEventTypeInformation)

    End Sub
    
    Private Sub OpenLogFile(Path As String, BackupPath As String)
        
        On Error Resume Next
        
        Name Path As BackupPath                         'Rename the previous log file if one exists.
        Call SafeKill("C:\IMA2\System\Locator Log.txt") 'Delete our old log file
        If Err Then Err.Clear                           'Clear any error that may exist
        
        'Setup our new log file
        g_LogFileNum = FreeFile
        Open "C:\IMA2\System\Locator Log.txt" For Output As g_LogFileNum
        
        If Err Then MsgBox "Error opening log file. " + Err.Description: End

    End Sub
    
    
'*********************************************************************************************************************
' Logging Functions
'*********************************************************************************************************************

    Public Function DateTime() As String
        DateTime = "(" & Date & ", " & Time & ")"
    End Function

