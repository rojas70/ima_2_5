VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "IconManager"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
    Option Explicit

'****************************************************************************************************************************************
    
    Public ImageList As Object
    Dim m_Dir As String
'************************************************************************************************************************************
' Enumerations
'************************************************************************************************************************************
    
    Public Enum IMA2_Icons
        II_Network = 1
        II_Locator = 2
        II_Component = 3
        II_Container = 4
        II_NewComponent = 5
        II_GreyComponent = 6
        II_BadComponent = 7
        II_Manager = 8
        II_Library = 9
        II_Property = 10
        II_Method = 11
        II_Form = 12
        II_ComponentFile = 13
        II_Binding = 14
    End Enum

'************************************************************************************************************************************
' Component Icon Functions
'************************************************************************************************************************************
    Public Property Get Directory() As String
        Directory = m_Dir
    End Property
    
    Public Property Let Directory(NV As String)
        m_Dir = NV
    End Property
    
    Public Function IconIndex(PID As String) As Integer
        Dim IFN As String
        If InList(PID) Then
            IconIndex = ImageList.ListImages(PID).Index
        Else
            IFN = m_Dir + "\" + PID + ".ico"
            If Funcs.FileExists(IFN) Then
                ImageList.ListImages.Add , PID, LoadPicture(IFN)
                IconIndex = ImageList.ListImages(PID).Index
            Else
                IconIndex = II_Component
            End If
        End If
    End Function
    
    Public Function IconExists(PID As String) As Boolean
        Dim Path As String
        Path = m_Dir + "\" + PID + ".ico"
        IconExists = Funcs.FileExists(Path)
    End Function
    
    Public Function InList(PID As String) As Boolean
        Dim I As Object
        On Error Resume Next
        Set I = ImageList.ListImages(PID)
        Err.Clear
        InList = Not (I Is Nothing)
    End Function

    Private Sub Class_Initialize()
        Set ImageList = frm.iml
    End Sub
