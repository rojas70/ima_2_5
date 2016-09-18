VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "ComponentFile"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

    Public UserName     As String
    Public FileDate     As String
    Public FileTime     As String
    Public FilePath     As String
    Public ParentPath   As String
    
    Private m_Paths()   As String
    Private m_CDs()     As CmpDesc

'********************************************************************************************************
' Public File I/O Functions
'********************************************************************************************************
    
    Public Sub Save()
        
        Dim CD  As New CmpDesc
        Dim PB  As New PropertyBag
        Dim AI  As Integer
        Dim I   As Integer
        Dim AL  As ILocator
        Dim Cmp As IComponent
        
        Dim PP  As String
        Dim LB  As Integer
        Dim UB  As Integer
        Dim PPL As Integer
        
        Set AL = CreateObject(g_LOCATOR_PID)
        
        LB = LBound(m_Paths)
        UB = UBound(m_Paths)
        Call Funcs.QuickSortStrings(m_Paths)
        
        FileDate = CStr(Date)
        FileTime = CStr(Time)
        
        PP = Left(m_Paths(LB), InStrRev(m_Paths(LB), "\") - 1)
        PPL = Len(PP)
        
        Call PB.WriteProperty("UserName", UserName)
        Call PB.WriteProperty("Date", FileDate)
        Call PB.WriteProperty("Time", FileTime)
        Call PB.WriteProperty("ParentPath", PP)
        Call PB.WriteProperty("Count", (UBound(m_Paths) - LBound(m_Paths)) + 1)
        
        For I = LB To UB
            Set Cmp = AL.Locate(m_Paths(I))
            If Not (Cmp Is Nothing) Then
                Call CD.Read(Cmp)                   'Read component info
                CD.Path = Mid(CD.Path, PPL + 2)     'Generate relative path
                Call PB.WriteProperty("" & AI, CD)  'Write info to property bag
                AI = AI + 1                         'Incremement counter
            End If
        Next
    
        Open FilePath For Binary As 1
        Dim B() As Byte
        B = PB.Contents
        Put #1, , B
        Close #1
    
    End Sub

'***********************************************************************************************************************************************

    Public Sub Load()
        
        Dim CD      As CmpDesc
        Dim PB      As New PropertyBag
        Dim B()     As Byte
        Dim I       As Integer
        Dim Count   As Integer
        
        '****** Read property bag from file ******
        Open FilePath For Binary As 1
        ReDim B(0 To LOF(1) - 1)
        Get #1, , B
        Close #1
        PB.Contents = B
        
        '****** Read file information ******
        UserName = PB.ReadProperty("UserName")
        FileDate = PB.ReadProperty("Date")
        FileTime = PB.ReadProperty("Time")
        ParentPath = PB.ReadProperty("ParentPath")
        Count = PB.ReadProperty("Count")
        
        '****** Resize and arrays ******
        ReDim m_Paths(0 To Count - 1)
        ReDim m_CDs(0 To Count - 1)
        
        '****** Load component descriptions ******
        For I = 0 To Count - 1
            Set CD = PB.ReadProperty("" & I)
            m_Paths(I) = CD.Path
            Set m_CDs(I) = CD
        Next
    
    End Sub
    
'***********************************************************************************************************************************************
    
    Private Sub Class_Initialize()
        UserName = Environ("USERNAME")
    End Sub

'********************************************************************************************************
' Public Properties
'********************************************************************************************************

    Public Property Get Paths() As String()
        On Error Resume Next
        Dim Tmp As Integer
        Tmp = UBound(m_Paths)
        If Err Then Err.Clear: Exit Sub
        Paths = m_Paths
        Call Funcs.QuickSortStrings(m_Paths)
    End Property
    
    Public Property Let Paths(NV() As String)
        m_Paths = NV
    End Property
    
    Public Property Get Descriptions() As CmpDesc()
        Descriptions = m_CDs
    End Property
    
    Public Property Get DescriptionIndex(I As Integer) As CmpDesc
        Set DescriptionIndex = m_CDs(I)
    End Property
    
    Public Property Get DescriptionLBound() As Integer
        DescriptionLBound = LBound(m_CDs, 1)
    End Property

    Public Property Get DescriptionUBound() As Integer
        DescriptionUBound = UBound(m_CDs, 1)
    End Property

    


