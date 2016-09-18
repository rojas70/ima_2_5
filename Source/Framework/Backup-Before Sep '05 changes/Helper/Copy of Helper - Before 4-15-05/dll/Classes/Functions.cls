VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Functions"
Attribute VB_GlobalNameSpace = True
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
    Option Explicit
    
'************************************************************************************************
    
    Private Type CLSID ' same as GUID
       Data1 As Long
       Data2 As Integer
       Data3 As Integer
       Data4(0 To 7) As Byte
    End Type
    
    Private Type GUID
        Data1 As Long
        Data2 As Integer
        Data3 As Integer
        Data4(0 To 7) As Byte
    End Type
    
    Private Enum eSYSKIND
       SYS_WIN16 = 0&
       SYS_WIN32 = 1&
       SYS_MAC = 2&
    End Enum
    
'************************************************************************************************
    
    Private Declare Function GetComputerName Lib "kernel32" Alias "GetComputerNameA" (ByVal lpBuffer As String, nSize As Long) As Long
    Private Declare Function GetCurrentProcessId Lib "kernel32.dll" () As Long
    Private Declare Function GetCurrentThreadId Lib "kernel32.dll" () As Long

    Private Declare Function LoadTypeLib Lib "oleaut32.dll" (pFileName As Byte, pptlib As Object) As Long
    Private Declare Function RegisterTypeLib Lib "oleaut32.dll" (ByVal ptlib As Object, szFullPath As Byte, szHelpFile As Byte) As Long
    Private Declare Function UnRegisterTypeLib Lib "oleaut32.dll" ( _
          libID As GUID, _
          ByVal wVerMajor As Integer, _
          ByVal wVerMinor As Integer, _
          ByVal lCID As Long, _
          ByVal tSysKind As eSYSKIND _
       ) As Long
    
    Private Declare Function CLSIDFromString Lib "ole32.dll" (lpsz As Byte, pCLSID As GUID) As Long
    Private Declare Function CLSIDFromProgID Lib "ole32.dll" (ByVal lpszProgID As Long, lpclsid As CLSID) As Long
    Private Declare Function StringFromCLSID Lib "ole32.dll" (rclsid As CLSID, ByRef lppsz As Long) As Long
    Private Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (lpvDest As Any, lpvSource As Any, ByVal cbCopy As Long)

    Private Declare Function ProgIDFromCLSID2 Lib "ole32.dll" Alias "ProgIDFromCLSID" (pCLSID As Any, lpszProgID As Long) As Long
    Private Declare Function CLSIDFromString2 Lib "ole32.dll" Alias "CLSIDFromString" (ByVal lpszProgID As Long, pCLSID As Any) As Long
    Private Declare Sub CopyMemory2 Lib "kernel32" Alias "RtlMoveMemory" (dest As Any, source As Any, ByVal bytes As Long)
    
    
'************************************************************************************************
    
    Private Const S_OK = 0

'************************************************************************************************
' Error Numbers
'************************************************************************************************

    Public Enum IMA2_Errors
        IE_CMP_CREATE = 2000
        IE_CMP_CONSTRUCT = 2001
        IE_CMP_REGISTER = 2002
        IE_CMP_REGISTERED = 2003
        
        IE_AL_CREATE = 2100
        IE_AL_NOT_SAME = 2101
        IE_AL_NOT_PARENT_MACHINE = 2102
        
        IE_PARENT_NOT_FOUND = 2200
        IE_PARENT_ACCESS_ERROR = 2201
        IE_PARENT_NOT_CONTAINER = 2202
        
        IE_UNKNOWN_CONTEXT = 2900
    End Enum

'************************************************************************************************
' Error Messages
'************************************************************************************************

    Const EM_CMP_CONSTRUCT = "Error in the IComponent::Construct(...) method on component"
    Const EM_CMP_CREATE = "Error creating component"
    Const EM_CMP_REGISTER = "Error registering component"
    Const EM_CMP_REGISTERED = "Component already registered"
    
    Const EM_AL_CREATE = "Error creating locator object"
    Const EM_AL_NOT_SAME = "Provided and expected ILocator pointers did not match"
    Const EM_AL_NOT_PARENT_MACHINE = "Provided locator is not the parent's locator"
    
    Const EM_PARENT_ACCESS_ERROR = "Error locating parent component"
    Const EM_PARENT_NOT_FOUND = "Parent component not registered"
    Const EM_PARENT_NOT_CONTAINER = "Parent component not a container"
    
    Const EM_UNKNOWN_CONTEXT = "Unknown IMA2 context"
    
'************************************************************************************************
' IMA2 FUNCTIONS
'************************************************************************************************
    
    Public Function OldErrorInfo() As String
        If Err.Number = 0 Then Exit Function
        OldErrorInfo = vbCrLf & "-> Error " & Err.Number & " in " & Err.source & " : " & Err.Description
    End Function
    
    '************************************************************************************************
    
    Public Function SystemPath() As String
        Dim O As Object
        Set O = CreateObject(g_LOCATOR_PID)
        SystemPath = O.FilePath()
    End Function
    
    '************************************************************************************************
    
    Public Function GetLocator() As ILocator
        Set GetLocator = CreateObject(g_LOCATOR_PID)
    End Function
    
    '************************************************************************************************
    
    Public Function GetBindingsObject() As IBindings
        Set GetBindingsObject = CreateObject(g_BINDINGS_PID)
    End Function
    
    '************************************************************************************************
    
    Public Function BindingsPID() As String
        BindingsPID = g_BINDINGS_PID
    End Function
    
    '************************************************************************************************
    
    Public Function LocatorPID() As String
        LocatorPID = g_LOCATOR_PID
    End Function
    
    '************************************************************************************************

    'Returns the default forbidden characters in IMA2 names.
    Public Function ForbiddenChars() As String
        ForbiddenChars = IMA2_ForbiddenChars
    End Function
    
    '************************************************************************************************
    
    'Creates a component on the IMA2 network and registers it.
    Public Function CreateIMA2Component(FullPath As String, PID As String, Optional Machine As String = "", Optional Register As Boolean = False, Optional pAL As ILocator = Nothing) As IComponent
    
        On Error Resume Next
        
        Dim AL  As ILocator
        Dim LA  As ILocatorAdvanced
        Dim C   As IComponent
        Dim PC  As IContainer
        Dim LC  As IComponent
        Dim PK  As String
        
        Dim CtS As String
        Dim Src As String
        Dim Old As String
        Dim Path As String
        
        'Work with a copy instead of the orignal
        Path = FullPath
        
        'Source function for error reporting.
        Src = "IMA2Helper.IMA2Funcs.CreateComponent(" & FullPath & "," & PID & ", ...)"
        
        'If a full path is not specified, register the component under this machine's locator.
        If Left(FullPath, 2) <> "\\" Then Path = LocalMachine() + "\" + FullPath
        
        'Clear any existing errors.
        Err.Clear

        'If the pAL argument is missing,
        If pAL Is Nothing Then
            
            'Attempt to create a new locator on the parent machine.
            Set AL = CreateObject("IMA2_Locator.Locator", MachineFromPath(Path))
            
            'If locator creation failed, raise an error.
            Old = OldErrorInfo()
            If Err Then On Error GoTo 0: Call Err.Raise(IE_AL_CREATE, Src, EM_AL_CREATE + " on " + MachineFromPath(Path) & Old)
        
        'If the argument isn't missing then use it.
        Else
            'Attempt to QI for ILocator off given pointer.
            Set AL = pAL
            
            'If not the same, signal an error.
            Old = OldErrorInfo()
            If Err Then On Error GoTo 0: Call Err.Raise(IE_AL_NOT_SAME, Src, EM_AL_NOT_SAME & Old)
            
            'If the given locator and parent component locator machines disagree, signal an error.
            If LCase(AL.Machine) <> LCase(MachineFromPath(Path)) Then On Error GoTo 0: Call Err.Raise(IE_AL_NOT_PARENT_MACHINE, Src, EM_AL_NOT_PARENT_MACHINE & " " & LCase(AL.Machine) & " <> " & LCase(MachineFromPath(Path)))
        End If

        'Make sure this component isn't already in the agent locator.
        Old = OldErrorInfo()
        If (Not (AL.Locate(Path) Is Nothing)) Or Err Then On Error GoTo 0: Call Err.Raise(IE_CMP_REGISTERED, Src, EM_CMP_REGISTERED & " " & Path & Old)
        
        'Locate the parent.
        PK = ParentFromPath(Path)
        Set LC = AL.Locate(PK)
        
        'Error accessing the parent component.
        Old = OldErrorInfo()
        If Err Then On Error GoTo 0: Call Err.Raise(IE_PARENT_ACCESS_ERROR, Src, EM_PARENT_ACCESS_ERROR & " " & PK & Old)
        
        'No parent found, raise an error.
        Old = OldErrorInfo()
        If (LC Is Nothing) Or Err Then On Error GoTo 0: Call Err.Raise(IE_PARENT_NOT_FOUND, Src, EM_PARENT_NOT_FOUND & " " & PK & Old)
        
        'Parent found, but it's not a container?
        If Not (TypeOf LC Is IContainer) Then On Error GoTo 0: Call Err.Raise(IE_PARENT_NOT_CONTAINER, Src, EM_PARENT_NOT_CONTAINER)
        
        'Parent container found.
        Set PC = LC
        
        'Create the component in the appropriate context.
        Set C = PC.CreateComponent(PID, Machine): CtS = "parent container"
        
        'Correct context, but the creation failed.
        Old = OldErrorInfo()
        If (C Is Nothing) Or Err Then On Error GoTo 0: Call Err.Raise(IE_CMP_CREATE, Src, EM_CMP_CREATE + " with path '" & Path & "' and PID '" + PID + "' in '" + CtS + "' context" & Old)
            
        'Construct the component
        Call C.Construct(Path, PID, AL)
        
        'Check for a construction error.
        Old = OldErrorInfo()
        If Err Then On Error GoTo 0: Call Err.Raise(IE_CMP_CONSTRUCT, Src, EM_CMP_CONSTRUCT + vbCrLf + "Path: '" & Path & vbCrLf & "'PID: '" + PID & vbCrLf & Old)
        
        'Register it with the parent's locator.
        If Register Then
            Set LA = AL
            Call LA.Register(C)
        End If
        
        'Check for a registration error.
        Old = OldErrorInfo()
        If Err Then On Error GoTo 0: Call Err.Raise(IE_CMP_REGISTER, Src, EM_CMP_REGISTER & " with path '" & Path & "'" & Old)
        
        'Return the component.
        Set CreateIMA2Component = C
        
    End Function

    '************************************************************************************************
    
    'Returns an assesment of whether or not a component name is valid.
    Public Function ValidComponentName(N As String) As Boolean
        ValidComponentName = Not CharsInString(N, IMA2_ForbiddenChars)
    End Function

    '************************************************************************************************

    'Returns true if the passed component is alive.
    Public Function PingComponent(Cmp As IComponent) As Boolean
        Dim F As String
        On Error Resume Next
        F = Cmp.DataSize
        PingComponent = Not (Err.Number > 0)
        Err.Clear
    End Function

    '************************************************************************************************

    'Returns the parent's path from a child's path.
    Public Function ParentFromPath(Path As String) As String
        Dim P As Long
        P = InStrRev(Path, "\")
        If P < 1 Then Exit Function
        If P = 2 Then ParentFromPath = "\\": Exit Function
        If P = 1 Then ParentFromPath = "": Exit Function
        ParentFromPath = Left(Path, P - 1)
    End Function

    '************************************************************************************************

    'Returns a component's name from it's path.
    Public Function NameFromPath(Path As String) As String
        Dim P As Long
        P = InStrRev(Path, "\") + 1
        If P > 0 Then NameFromPath = Mid(Path, P)
    End Function

    '************************************************************************************************

    'Returns the locator path responsible for a component of a specified path.
    Public Function LocatorFromPath(Path As String) As String
        If InStr(Path, "\\") < 1 Then Exit Function
        LocatorFromPath = "\\" + MachineFromPath(Path)
    End Function

    '************************************************************************************************
    
    'Returns the machine name for a component's path.
    Public Function MachineFromPath(Path As String) As String
        Dim ML As Long
        If Left(Path, 2) = "\\" Then
            ML = InStr(3, Path$, "\") - 3
            If ML <= 0 Then ML = Len(Path)
            MachineFromPath = UCase(Mid(Path, 3, ML))
        Else
            MachineFromPath = Path
        End If
    End Function


    '************************************************************************************************
    
    'Returns a path with Level(s) names in it (1 = "\\Mccoy", etc).
    Public Function PathOfLevel(Path As String, Level As Long) As String
        Dim x As Long
        Dim C As Long
        C = -2
        
        If Level < 1 Then
            PathOfLevel = ""
            Exit Function
        End If
            
        For x = 1 To Len(Path$)
            If Mid$(Path$, x, 1) = "\" Then C = C + 1
            If C = Level Then
                PathOfLevel = Left$(Path$, x - 1)
                Exit Function
            End If
        Next x
    End Function

    '************************************************************************************************
    
    'Returns the number of levels a path is above the network by.
    Public Function PathLevel(Path As String) As Integer
Attribute PathLevel.VB_Description = "Returns the number of levels a path is above the network by."
        If Path = "" Then PathLevel = -1: Exit Function
        If Path = "\\" Then PathLevel = 0: Exit Function
        PathLevel = StrCount(Path, "\") - 1
    End Function

    '************************************************************************************************
    
    'Determines if any of the characters in Chars occurs in S.
    Public Function CharsInString(S As String, Chars As String) As Boolean
        Dim I As Long
        For I = 1 To Len(Chars)
            If InStr(S, Mid(Chars, I, 1)) > 0 Then
                CharsInString = True
                Exit Function
            End If
        Next
        CharsInString = False
    End Function
    
    '************************************************************************************************
    
    'Returns the number of occurences of match in Source.
    Public Function StrCount(source As String, Match As String) As Long
        Dim CP As Long, SC As Long
        If Match = "" Then Exit Function
        CP = 0
        SC = 0
        Do
            CP = InStr(CP + 1, source, Match)
            If CP >= 1 Then SC = SC + 1
        Loop Until CP < 1
        StrCount = SC
    End Function

    '************************************************************************************************
    
    Public Function IsDescendant(sChild As String, sParent As String) As Boolean
        IsDescendant = InStr(LCase(sChild), LCase(sParent)) = 1
    End Function

'************************************************************************************************
' NETWORK FUNCTIONS
'************************************************************************************************
    
    'Returns the name of the machine the current process is executing on.
    Public Function LocalMachine() As String
        Dim M   As String
        Dim ML  As Long
        M = "                                   "
        ML = Len(M)
        Call GetComputerName(M, ML)
        LocalMachine = Left(M, ML)
    End Function

    '************************************************************************************************

    'Returns the name of all machines in this computer's workgroup.
    Public Function NetworkMachines() As String()
    
        ReDim Arr(1 To 1) As String
        Dim Count       As Long
        Dim x           As New NETWKOBJLib.WNet
        Dim bDone       As Boolean
        Dim resource    As String

        x.OpenEnumeration WNetResNeighborhood, ""
    
        bDone = False
        While bDone = False
            resource = x.EnumResources
            If (resource = vbNullString) Then
                bDone = True
            Else
                 Count = Count + 1
                 ReDim Preserve Arr(1 To Count) As String
                 Arr(Count) = resource
            End If
        Wend
        
        x.CloseEnumeration
        
        NetworkMachines = Arr
    
    End Function

    '************************************************************************************************
    
    'Returns the current Process ID.
    Public Function CurrentProcessID() As Long
        CurrentProcessID = GetCurrentProcessId()
    End Function
    
    '************************************************************************************************
    
    'Returns the current Thread ID.
    Public Function CurrentThreadID() As Long
        CurrentThreadID = GetCurrentThreadId()
    End Function

    '************************************************************************************************
    
    Public Function CurrentUserName() As String
        CurrentUserName = Environ("USERNAME")
    End Function
        
    '************************************************************************************************
    
    Public Function CurrentUserProfile() As String
        CurrentUserProfile = Environ("USERPROFILE")
    End Function
    
'************************************************************************************************
' FILE FUNCTIONS
'************************************************************************************************
    
    'Deletes a file regardles of whether it's there.
    Public Sub SafeKill(FN As String)
        On Error Resume Next
        Kill FN
        Err.Clear
    End Sub
    
    '************************************************************************************************
    
    'Returns a boolean value indicating the file FN exists.
    Public Function FileExists(FN As String) As Boolean
        FileExists = Dir(FN, vbHidden) > ""
    End Function
    
    '************************************************************************************************
    
    'Returns a boolean value indicating the file FN exists.
    Public Function FileLocked(FN As String) As Boolean
        On Error Resume Next
        Err.Clear
        Open FN For Append As 1
        FileLocked = FileExists(FN) And (Err > 0)
        Close 1
        Err.Clear
    End Function
    
    '************************************************************************************************
    
    'Takes a propertybag and returns a variant containing a byte array.
    Function PB2VT(PB As PropertyBag) As Variant
        PB2VT = PB.Contents
    End Function
    
    '************************************************************************************************
    
    'Takes a variant containing a byte array and returns a propertybag.
    Function VT2PB(VT As Variant) As PropertyBag
        Dim PB As New PropertyBag
        Dim BArr() As Byte
        BArr = VT
        PB.Contents = BArr
        Set VT2PB = PB
    End Function

    '************************************************************************************************

    'Saves a propertybag to a file.
    Public Sub SavePB(FN As String, PB As PropertyBag)
        SafeKill FN$                                    'Safely delete the existing file if it exists.
        Open FN$ For Binary As #1                       'Open the file for binary I/O.
        Put #1, , PB2VT(PB)                            'Store the Variant-converted property bag.
        Close #1                                        'Close the file.
    End Sub

    '************************************************************************************************

    'Loads a propertybag from a file.
    Public Function LoadPB(FN As String) As PropertyBag
        Dim VT      As Variant
        Dim PB      As New PropertyBag
        If Not FileExists(FN$) Then Exit Function
        Open FN$ For Binary As #1                   ' Read the file contents into a Variant.
        Get #1, , VT                                '
        Close #1                                    '
        Set LoadPB = VT2PB(VT)                      ' Assign to the PropertyBag Contents property.
    End Function

    '************************************************************************************************

    Public Function LoadByteArray(Path As String) As Byte()
        
        Dim Data() As Byte
        Dim FN As Long
        
        FN = FreeFile
        Open Path For Binary As FN
        ReDim Data(1 To LOF(FN))
        Get FN, , Data
        Close FN
        LoadByteArray = Data
    
    End Function
    
    '************************************************************************************************
    
    Public Sub SaveByteArray(Path As String, Data() As Byte)
            
        Dim FN As Long
        FN = FreeFile
        Open Path For Binary As FN
        Put FN, , Data()
        Close FN
    
    End Sub

'************************************************************************************************
' SIMPLE FUNCTIONS
'************************************************************************************************
    
    Public Function ArraySize(Data As Variant) As Long
        On Error Resume Next
        ArraySize = (UBound(Data) - LBound(Data)) + 1
        Err.Clear
    End Function
    
    '************************************************************************************************
    
    Public Function ArrayEmpty(Data As Variant) As Boolean
        Dim Temp As Long
        On Error Resume Next
        Temp = UBound(Data)
        ArrayEmpty = (Err <> 0)
        Err.Clear
    End Function
    
    '************************************************************************************************
    
    Public Function SentenceCase(Val As String)
        SentenceCase = UCase(Left(Val, 1)) + LCase(Mid(Val, 2))
    End Function
    
    '************************************************************************************************
    
    Public Function FindMatchingString(String1 As String, Strings() As String) As String
        Dim LS  As String
        Dim I   As Long
        LS = LCase(String1)
        For I = LBound(Strings) To UBound(Strings)
            If LS = LCase(Strings(I)) Then FindMatchingString = Strings(I): Exit Function
        Next I
    End Function
    
    '************************************************************************************************
    
    Public Function Variant2Strings(V As Variant) As String()
        If IsEmpty(V) Then Exit Function
        ReDim RV(LBound(V) To UBound(V)) As String
        Dim I As Integer
        For I = LBound(V) To UBound(V)
            RV(I) = V(I)
        Next I
        Variant2Strings = RV
    End Function

    '************************************************************************************************
    
    Public Function GetDistributingInfo(Cmp As IComponent, Path As String, PID As String)
    
        Dim DI As IMA2_DistributingInfo
    
        With DI
            .Name = NameFromPath(Path)
            .Path = Path
            .Machine = LocalMachine()
            .PID = PID
            .Process = CurrentProcessID()
            .Thread = CurrentThreadID()
            .IsContainer = TypeOf Cmp Is IContainer
        End With
    
        GetDistributingInfo = DI
    
    End Function

    '************************************************************************************************
    
    Public Sub QuickSortStrings(sArray() As String, Optional Ascending As Boolean = True)
        If Ascending Then
            QuickSortStringsAscending sArray(), LBound(sArray), UBound(sArray)
        Else
            QuickSortStringsDescending sArray(), LBound(sArray), UBound(sArray)
        End If
    End Sub

    '************************************************************************************************

    Private Sub QuickSortStringsAscending(sArray() As String, inLow As Long, inHi As Long)
      
       Dim pivot As String
       Dim tmpSwap As String
       Dim tmpLow As Long
       Dim tmpHi As Long
       
       tmpLow = inLow
       tmpHi = inHi
       
       pivot = sArray((inLow + inHi) / 2)
      
       While (tmpLow <= tmpHi)
       
          While (sArray(tmpLow) < pivot And tmpLow < inHi)
             tmpLow = tmpLow + 1
          Wend
          
          While (pivot < sArray(tmpHi) And tmpHi > inLow)
             tmpHi = tmpHi - 1
          Wend
          
          If (tmpLow <= tmpHi) Then
             tmpSwap = sArray(tmpLow)
             sArray(tmpLow) = sArray(tmpHi)
             sArray(tmpHi) = tmpSwap
             tmpLow = tmpLow + 1
             tmpHi = tmpHi - 1
          End If
       
       Wend
      
       If (inLow < tmpHi) Then QuickSortStringsAscending sArray(), inLow, tmpHi
       If (tmpLow < inHi) Then QuickSortStringsAscending sArray(), tmpLow, inHi
      
    End Sub
    
    '************************************************************************************************
    
    Private Sub QuickSortStringsDescending(sArray() As String, inLow As Long, inHi As Long)
      
       Dim pivot As String
       Dim tmpSwap As String
       Dim tmpLow As Long
       Dim tmpHi As Long
       
       tmpLow = inLow
       tmpHi = inHi
       
       pivot = sArray((inLow + inHi) / 2)
       
       While (tmpLow <= tmpHi)
          
          While (sArray(tmpLow) > pivot And tmpLow < inHi)
             tmpLow = tmpLow + 1
          Wend
        
          While (pivot > sArray(tmpHi) And tmpHi > inLow)
             tmpHi = tmpHi - 1
          Wend
    
          If (tmpLow <= tmpHi) Then
             tmpSwap = sArray(tmpLow)
             sArray(tmpLow) = sArray(tmpHi)
             sArray(tmpHi) = tmpSwap
             tmpLow = tmpLow + 1
             tmpHi = tmpHi - 1
          End If
      
       Wend
      
       If (inLow < tmpHi) Then QuickSortStringsDescending sArray(), inLow, tmpHi
       If (tmpLow < inHi) Then QuickSortStringsDescending sArray(), tmpLow, inHi

    End Sub
    
    '************************************************************************************************
    
    Public Sub RemoveBlankStrings(S() As String)
        Dim UB      As Integer
        Dim LB      As Integer
        Dim I       As Integer
        Dim Index   As Integer
        Dim RV()    As String
        Dim Count   As Integer
        
        If ArrayEmpty(S) Then Exit Sub
        LB = LBound(S)
        UB = UBound(S)
        
        For I = LB To UB
            If Len(S(I)) > 0 Then Count = Count + 1
        Next
        
        ReDim RV(LB To LB + Count - 1)
        
        Index = LB
        For I = LB To UB
            If Len(S(I)) > 0 Then
                RV(Index) = S(I)
                Index = Index + 1
            End If
        Next
        
        S = RV
    End Sub
    
    '************************************************************************************************

    'Tests if the object passed is not nothing.
    Public Function NN(Obj As Object) As Boolean
        NN = Not (Obj Is Nothing)
    End Function

    
'************************************************************************************************
' REGISTRY FUNCTIONS
'************************************************************************************************
    
    Public Function RegisterTLB(sLib As String) As Long
        
        Dim suLib() As Byte
        Dim errOK As Long
        Dim tlb As Object
       
        ' Basic automatically translates strings to Unicode Byte arrays
        ' but doesn't null-terminate, so you must do it yourself
        suLib = sLib & vbNullChar
        ' Pass first byte of array
        errOK = LoadTypeLib(suLib(0), tlb)
        If errOK = 0 Then errOK = RegisterTypeLib(tlb, suLib(0), 0)
        RegisterTLB = errOK
       
    End Function
    
    '************************************************************************************************************************************
    
    Public Function UnregisterTLB(sLib As String) As Long
    
        Dim suLib() As Byte
        Dim errOK As Long
        Dim tlb As Object
          
        Dim cTLI As TypeLibInfo
        Dim tGUID As GUID, sCLSID As String
        Dim iMajor As Integer, iMinor As Integer
        Dim lCID As Long
    
          Set cTLI = TLI.TypeLibInfoFromFile(sLib)
          sCLSID = cTLI.GUID
          iMajor = cTLI.MajorVersion
          iMinor = cTLI.MinorVersion
          lCID = cTLI.lCID
          Set cTLI = Nothing
          
          suLib = sCLSID & vbNullChar
          errOK = CLSIDFromString(suLib(0), tGUID)
          If errOK = 0 Then errOK = UnRegisterTypeLib(tGUID, iMajor, iMinor, lCID, SYS_WIN32)
        
        UnregisterTLB = errOK
    
    End Function

    '************************************************************************************************************************************
    
    Public Function PID2CLSID(ByVal sProgId As String) As String
        
        Dim tG      As CLSID
        Dim sCLSID  As String
        Dim lR      As Long
        Dim lPtr    As Long
        Dim B()     As Byte
       
        lPtr = StrPtr(sProgId)
        lR = CLSIDFromProgID(lPtr, tG)
        If (lR = S_OK) Then
            sCLSID = String$(255, vbNullChar)
            lR = StringFromCLSID(tG, lPtr)
            If (lR = S_OK) Then
                ReDim B(0 To 38 * 2 - 1) As Byte
                CopyMemory B(0), ByVal lPtr, 38 * 2
                PID2CLSID = B
            End If
        End If
       
    End Function

    ' Convert a string representation of a CLSID, including the
    ' surrounding brace brackets, into the corresponding ProgID.
    
    Function CLSIDToProgID(ByVal CLSID As String) As String
        Dim pResult As Long, pChar As Long
        Dim char As Integer, length As Long
        ' No need to use a special UDT
        Dim GUID(15) As Byte
    
        ' convert from string to a binary CLSID
        CLSIDFromString2 StrPtr(CLSID), GUID(0)
        ' convert to a string, get pointer to result
        ProgIDFromCLSID2 GUID(0), pResult
        ' find the terminating null char
        pChar = pResult - 2
        Do
            pChar = pChar + 2
            CopyMemory2 char, ByVal pChar, 2
        Loop While char
        ' now get the entire string in one operation
        length = pChar - pResult
        ' no need for a temporary string
        CLSIDToProgID = Space$(length \ 2)
        CopyMemory2 ByVal StrPtr(CLSIDToProgID), ByVal pResult, length
    End Function
    
    
    
