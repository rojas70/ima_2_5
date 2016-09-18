VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "NetworkFuncs"
Attribute VB_GlobalNameSpace = True
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
    Option Explicit

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
    
    Public Function CurrentUserName() As String
        CurrentUserName = Environ("USERNAME")
    End Function
        
'************************************************************************************************
    
    Public Function CurrentUserProfile() As String
        CurrentUserProfile = Environ("USERPROFILE")
    End Function

