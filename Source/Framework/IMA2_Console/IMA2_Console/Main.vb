Imports System.IO

Module Main

    Dim HelpString As String
    Dim TitleString As String
    Dim Machine As String

    Dim InS As String
    Dim Tokens() As String
    Dim Paths() As String

    Dim AL As IMA2.ILocator
    Dim LA As IMA2.ILocatorAdvanced
    Dim LC As IMA2.IComponent
    Dim LP As IMA2.IContainer
    Dim DS As IMA2.IDistributingInfoProvider
    Dim ES As IMA2.ILocatorEventProvider

    Sub Main()
        On Error Resume Next

        'Generate basic strings
        Machine = System.Environment.MachineName
        HelpString = " Valid commands are:" + vbCrLf + vbCrLf + Replace(" list [path],info [path],create [path] [pid] [machine],unregister [path],clibs,mlibs,exit,stop", ",", vbCrLf + " ")
        TitleString = StrDup(80, "-") + " IMA 2.5 System Command Console [v1.1.0]" + vbCrLf + " (C) Copyright 2002-2003 Vanderbilt Cognitive Robotics Laboratory." + vbCrLf + StrDup(80, "-")

        'Print out the program title
        Console.WriteLine(TitleString)

        'Attempt to connect to IMA2 Locator, Information, and Event services.
        AL = CreateObject("IMA2_Locator.Locator")
        LA = CreateObject("IMA2_Locator.Locator")           'CType(AL, IMA2.ILocatorAdvanced)
        LC = CreateObject("IMA2_Locator.Locator")           'CType(O, IMA2.IComponent)
        LP = CreateObject("IMA2_Locator.Locator")           'CType(O, IMA2.IComponent)
        ES = CreateObject("IMA2_EventService.EventService")
        DS = CreateObject("IMA2_InfoService.InfoService")

        'If unsuccessful, let them know.
        If Err.Number <> 0 Then
            Console.Write("Error connecting to Locator." + vbCrLf + vbCrLf + "Press any key to exit...")
            Console.Read()
            End
        End If

        'Otherwise, display status and basic help information
        Console.WriteLine("Successfully connected to Locator." + vbCrLf + "Type help for command information.")

        'Enter main command parsing loop
        Do
            If Tokens(0) <> "" Then Console.WriteLine("") 'If it's not a carriage return, add a spacer line.
            Console.Write("\\" + Machine + "> ")          'Display our command prompt
            InS = LCase(Console.ReadLine)                 'Read a command line
            Tokens = Split(InS, " ")                      'Tokenize it
            If Tokens(0) <> "" Then Console.WriteLine("") 'If it's not a carriage return, add a spacer line.

            'Parse entered commands
            Select Case Tokens(0)
                Case ""
                Case "ping" : Ping() 'Display the Event service client roster
                Case "events" : Events() 'Display the Event service client roster
                Case "info" : Info() 'Display the Information service data
                Case "list" : List() 'Displays Locator service data
                Case "clibs" : ShowComponents() 'Displays component libraries
                Case "mlibs" : ShowManagers() 'Displays manager libraries
                Case "create" : CreateComponent() 'Creates a components on the network.
                Case "unregister" : Unregister() 'Unregisters a component 
                Case "stop" : StopFunc() 'Attempts to stop the Locator, Information, and Event services.
                Case "shutdown" 'Should shut down the entire IMA2 network.
                Case "exit" : End 'Closes the command console
                Case "help" : Console.WriteLine(HelpString) 'Displays basic commands to the user
                Case Else : Console.WriteLine(" Unknown command.") 'Syntax error feedback
            End Select

            Err.Clear()
        Loop

    End Sub

    Private Sub ShowComponents()
        Dim D As New System.IO.DirectoryInfo("C:\IMA2\System\Components")
        Dim F As System.IO.FileInfo

        Console.WriteLine(" Component Libraries: " + vbCrLf)

        For Each F In D.GetFiles("*.DLL")
            Dim name As [String] = F.Name
            Console.WriteLine("  " + name)
        Next

        For Each F In D.GetFiles("*.EXE")
            Dim name As [String] = F.Name
            Console.WriteLine("  " + name)
        Next

    End Sub

    Private Sub ShowManagers()

        Dim D As New System.IO.DirectoryInfo("C:\IMA2\System\Managers")
        Dim F As System.IO.FileInfo

        Console.WriteLine(" Manager Libraries: " + vbCrLf)

        For Each F In D.GetFiles("*.OCX")
            Dim name As [String] = F.Name
            Console.WriteLine("  " + name)
        Next

    End Sub

    Private Sub Events()
        Dim S() As String
        Dim SL As Integer
        S = ES.Clients
        If Not (S Is Nothing) Then SL = S.Length
        Console.WriteLine(" Event service client list: " + vbCrLf)
        If SL > 0 Then Console.WriteLine(" " + Join(S, vbCrLf + " ") + vbCrLf)
        Console.WriteLine(Str(SL) + " client(s)")
    End Sub

    Private Sub Info()
        Dim DIs() As IMA2.IMA2_DistributingInfo
        Dim DL As Integer
        Dim I As Integer
        DIs = DS.Items
        Console.WriteLine(" Information service client list: " + vbCrLf)
        If Not (DIs Is Nothing) Then
            DL = DIs.Length
            For I = 0 To UBound(DIs)
                Console.WriteLine(" " + DIs(I).Path)
                Console.Write(" " + DIs(I).PID + " on " + DIs(I).Machine + " (" + CStr(DIs(I).Process) + ":" + CStr(DIs(I).Thread) + ")")
                If CBool(DIs(I).IsContainer) Then
                    Console.WriteLine(" <container>")
                Else
                    Console.WriteLine("")
                End If
                Console.WriteLine("")
            Next
        End If
        Console.WriteLine(Str(DL) + " component(s) listed.")
    End Sub

    Private Sub Ping()

        Dim P As String
        Dim NV As String
        Dim C As IMA2.IComponent
        Dim DI As IMA2.IMA2_DistributingInfo

        If IsNumeric(Tokens(1)) Then
            NV = Val(Tokens(1)) - 1
            Paths = LA.Components
            If NV > Paths.Length Then Exit Sub
            P = Paths(NV)
        Else
            P = Tokens(1)
        End If

        Dim Seconds As Long
        Dim T1 As New DateTime()
        Dim T2 As New DateTime()

        Try
            T1 = Now
            C = AL.Locate(P)
            DI = C.Distributing
            T2 = Now
            Seconds = (T2.Ticks - T1.Ticks) / 10000
            Console.WriteLine(" " + P + " successfully pinged in " + Seconds.ToString() + " milliseconds.")
        Catch ex As Exception
            Console.WriteLine(" Attempting to ping " + P + " gave the following error:" + vbCrLf)
            Console.WriteLine(ex.ToString())
        End Try

    End Sub

    Private Sub Unregister()
        Dim NV As Integer
        Dim P As String

        If IsNumeric(Tokens(1)) Then
            NV = Val(Tokens(1)) - 1
            Paths = LA.Components
            P = Paths(NV)
        Else
            P = Tokens(1)
        End If

        If LCase(P) = LCase("\\" + Machine) Then
            Console.WriteLine("Cannot unregister Locator components.")
            Exit Sub
        End If

        Console.Write("Unregister " + P + "? (Y/N) ")
        If LCase(Console.ReadLine()) = "n" Then Exit Sub

        Try
            LA.Unregister(P)
            Console.WriteLine(P + " successfully unregistered.")
        Catch ex As Exception
            Console.WriteLine("Error: " + Err.Description)
        End Try

    End Sub

    Private Sub List()
        Dim I As Integer
        Dim S As String
        Console.WriteLine(" Locator service component list: " + vbCrLf)
        Paths = LA.Components
        For I = 0 To UBound(Paths)
            S = Str(I + 1)
            Paths(I) = S + ") " + Paths(I)
        Next
        Console.WriteLine(Join(Paths, vbCrLf) + vbCrLf + vbCrLf + " " + CStr(UBound(Paths) + 1) + " registered component(s) on " + Machine)
    End Sub

    Private Sub Shutdown()

        On Error Resume Next

        LC.Destruct()
        CallByName(ES, "Shutdown", CallType.Method)
        CallByName(DS, "Shutdown", CallType.Method)
        DS = Nothing
        ES = Nothing
        AL = Nothing
        LA = Nothing
        LC = Nothing

        Console.Write(vbCrLf + " IMA2 Locator, Information, and Event Services successfully stopped." + vbCrLf + " Press any key to exit...")
        Console.Read()
        End
    End Sub

    Private Sub CreateComponent()

        Dim C As IMA2.IComponent
        Dim P As IMA2.IComponent    'Parent IComponent
        Dim PC As IMA2.IContainer   'Parent IContainer
        Dim PP As String            'Parent Path
        Dim N As String             'Child name
        Dim DI As IMA2.IMA2_DistributingInfo

        If UBound(Tokens) < 2 Then
            Console.WriteLine("Incorrect syntax for create command. Type help for more info.")
        Else
            Try
                'Locate the parent and break up the path into parent and name
                PP = Left(Tokens(1), InStrRev(Tokens(1), "\") - 1)
                N = Mid(Tokens(1), InStrRev(Tokens(1), "\") + 1)
                PC = AL.Locate(PP)
                P = AL.Locate(PP)

                'Do this to fix any path innacuracies in the path.
                DI = P.Distributing
                PP = DI.Path

                'Do this to fix any path innacuracies in the ProgID.
                Dim T As Type
                T = Type.GetTypeFromProgID(Tokens(2))

                'Create the component in the parent context
                If UBound(Tokens) = 2 Then
                    C = PC.CreateComponent(Tokens(2), "")            'No machine specified -- create on this one.
                Else
                    C = PC.CreateComponent(Tokens(2), Tokens(3))    'Create on machine specified.
                End If

                'Construct and register the new component
                C.Construct(PP + "\" + N, Tokens(2), AL)
                LA.Register(C)

                'Let em know
                Console.WriteLine(PP + "\" + N + " was succesfully created and registered.")
            Catch ex As Exception
                Console.WriteLine("Error creating " + Tokens(1) + ". Verify the path and PID.")
            End Try
        End If
    End Sub

    Private Sub StopFunc()
        Console.Write(" Shutting down the IMA2 system on this machine will unregister all" + vbCrLf + " local components. Are you sure you wish to proceed? (Y/N) ")
        If LCase(Console.ReadLine()) = "y" Then Shutdown()
    End Sub

End Module

