VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "RegistryFuncs"
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
    
    Private Declare Function LoadTypeLib Lib "oleaut32.dll" (pFileName As Byte, pptlib As Object) As Long
    Private Declare Function RegisterTypeLib Lib "oleaut32.dll" (ByVal ptlib As Object, szFullPath As Byte, szHelpFile As Byte) As Long
    Private Declare Function UnRegisterTypeLib Lib "oleaut32.dll" ( _
          libID As GUID, _
          ByVal wVerMajor As Integer, _
          ByVal wVerMinor As Integer, _
          ByVal lCID As Long, _
          ByVal tSysKind As eSYSKIND _
       ) As Long
    
    Private Declare Function CLSIDFromString Lib "ole32.dll" (lpsz As Byte, pclsid As GUID) As Long
    Private Declare Function CLSIDFromProgID Lib "ole32.dll" (ByVal lpszProgID As Long, lpclsid As CLSID) As Long
    Private Declare Function StringFromCLSID Lib "ole32.dll" (rclsid As CLSID, ByRef lppsz As Long) As Long
    Private Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (lpvDest As Any, lpvSource As Any, ByVal cbCopy As Long)
    
'************************************************************************************************
    
    Private Const S_OK = 0
    
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
    
    Public Function VBCLSIDFromProgID(ByVal sProgId As String) As String
        
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
                VBCLSIDFromProgID = B
            End If
        End If
       
    End Function
