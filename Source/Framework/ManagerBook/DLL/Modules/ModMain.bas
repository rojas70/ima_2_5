Attribute VB_Name = "ModMain"
Option Explicit

Global Funcs As New Functions
    Global g_AL            As ILocator                      'Locator running on the local machine
    Global g_LA            As ILocatorAdvanced              'Advanced Locator interface
    Global g_IS            As IDistributingInfoProvider     'Information service running on the local machine

    Public Function LoadManagerMappings(CPID As String) As String
    
        On Error Resume Next
        
        Dim FN      As String
        Dim FK      As Long
        Dim MPIDs   As String
        
        FN = SystemPath() + "\..\Mappings\" + CPID + ".txt"
        FK = FreeFile
        Open FN For Input As FK
        Line Input #FK, MPIDs
        LoadManagerMappings = MPIDs
        Close FK
    
        If Err Then Err.Clear
    
    End Function


    Public Sub SaveManagerMappings(CPID As String, MPIDs As String)
    
        On Error Resume Next
        
        Dim FN      As String
        Dim FK      As Long
        
        FN = SystemPath() + "\..\Mappings\" + CPID + ".txt"
        FK = FreeFile
        Open FN For Output As FK
        Print #FK, MPIDs
        Close FK
    
        If Err Then Err.Clear
    
    End Sub


