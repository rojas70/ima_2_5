VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Libraries"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
    Option Explicit

'****************************************************************************************************************************************
    
    Dim m_Path      As String
    Dim m_Libs      As New Collection
    
'****************************************************************************************************************************************
    
    Public Property Get Count() As Integer
        Count = m_Libs.Count
    End Property
    
    Public Property Get Item(IndexKey As Variant) As LibInfo
Attribute Item.VB_UserMemId = 0
Attribute Item.VB_MemberFlags = "200"
        Set Item = m_Libs(IndexKey)
    End Property
    
    Public Function NewEnum() As IUnknown
Attribute NewEnum.VB_UserMemId = -4
Attribute NewEnum.VB_MemberFlags = "40"
       Set NewEnum = m_Libs.[_NewEnum]
    End Function
    
    Public Property Let Path(NV As String)
        m_Path = NV
        Set m_Libs = GetLibs(m_Path)
    End Property
    
    Public Property Get Path() As String
        Path = m_Path
    End Property
    
'****************************************************************************************************************************************
    
    Private Function GetLibs(Path As String) As Collection
        Dim RV As New Collection
        Call GetLibsFromPath(RV, Path + "\*.DLL")
        Call GetLibsFromPath(RV, Path + "\*.EXE")
        Call GetLibsFromPath(RV, Path + "\*.OCX")
        Set GetLibs = RV
    End Function
    
    Private Sub GetLibsFromPath(C As Collection, FP As String)
        Dim T       As TypeLibInfo
        Dim LI      As LibInfo
        Dim I       As Integer
        Dim FN      As String
        Dim PD      As String

        PD = Funcs.ParentFromPath(FP)
        FN = Dir(FP)                ' Retrieve the first entry.
        Do While FN <> ""           ' Start the loop.
            Set T = TLI.TypeLibInfoFromFile(PD + "\" + FN)
            Set LI = New LibInfo
            With LI
                .Name = T.Name
                .GUID = T.GUID
                .Path = T.ContainingFile
                .Version = T.MajorVersion & "." & T.MinorVersion
                .Description = T.HelpString
                Set .Classes = GetClasses(T)
            End With
            If LI.Classes.Count > 0 Then
                C.Add LI, LI.Name
            End If
            FN = Dir()               ' Get next entry.
        Loop
    End Sub
    
'****************************************************************************************************************************************
    
    Private Function GetClasses(T As TypeLibInfo) As Collection
    
        Dim I       As Integer
        Dim C       As CoClassInfo
        Dim II      As InterfaceInfo
        Dim CI      As ClsInfo
        Dim RV      As New Collection
        
            
        For Each C In T.CoClasses
            Set CI = New ClsInfo
            With CI
                .Name = C.Name
                .PID = Funcs.CLSIDToProgID(C.GUID)
                If .PID = "" Then
                    MsgBox "Library " & T.Name & " is not correctly registered."
                    Exit Function
                End If
                
                For Each II In C.Interfaces
                    .Interfaces = .Interfaces + II.Name + ","
                Next
                
                .Interfaces = Left(.Interfaces, Len(.Interfaces) - 1)
                
                If InStr(.Interfaces, "IManager") Or InStr(.Interfaces, "IComponent") Then
                    RV.Add CI, CI.Name
                End If
            
            End With
        Next

        Set GetClasses = RV

    End Function
    

