VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "cVectorSignal"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Attribute VB_Ext_KEY = "SavedWithClassBuilder6" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
Option Explicit

    Implements IComponent                               'Needed for all components.
    Dim m_Path As String, m_PID As String               'Needed for all components.
    Dim m_Machine As String, m_Activated As Boolean     'Needed for all components.
    Dim m_AL As ILocator                                'Needed for all components.
    
    Implements IContainer                               'Needed for containers

'********************************************************************************************
' IComponent
'********************************************************************************************

    Private m_currentVector As Long                         'Local variable
    Private m_SignalLength As Long                          'Local variable
    Private m_VectorLength As Long                          'Local variable
    Private m_CurrentIndex As Long                          'Local variable
    Private m_CurrentValue As Long                          'Local variable
    Private m_VecData() As Double                           'Vector Data
    Private m_VecTime() As Double                           'TimeStamp Data
    
    Public Property Get SignalLength() As Long
        SignalLength = m_SignalLength
    End Property
    Public Property Let SignalLength(NewVal As Long)
    If Not IsNull(NewVal) Then
        m_SignalLength = NewVal
    End If
    End Property
    Public Property Get VectorLength() As Long
        VectorLength = m_VectorLength
    End Property
    Public Property Let VectorLength(NewVal As Long)
    If Not IsNull(NewVal) Then
        m_VectorLength = NewVal
    End If
    End Property
    Public Property Get CurrentIndex() As Long
        CurrentIndex = m_CurrentIndex
    End Property
    Public Property Let CurrentIndex(NewVal As Long)
    If Not IsNull(NewVal) Then
        m_CurrentIndex = NewVal
    End If
    End Property
    Public Property Get CurrentValue(index As Long) As Double
        CurrentValue = m_VecData(m_CurrentIndex, index)
        
    End Property
    Public Property Let CurrentValue(index As Long, NewVal As Double)
    If Not IsNull(NewVal) Then
        m_VecData(m_CurrentIndex, index) = NewVal
    End If
    End Property
    Public Function GetCurrentVector(length As Long, pdTime As Double) As Double()
    Dim i As Long
    Dim result() As Double
    If length < m_VectorLength Then
        ReDim result(length)
        If Not IsNull(m_VecData) Then
            For i = 0 To length - 1
                result(i) = m_VecData(m_CurrentIndex, i)
            Next i
            If pdTime <> Null Then
                pdTime = m_VecTime(m_CurrentIndex)
            End If
        Else
            For i = 0 To length - 1
                result(i) = 7.7 'Default Value.
            Next i
            If pdTime <> Null Then
                pdTime = 7.7  'Default Value.
            End If
        End If
        GetCurrentVector = result()
    End If
    End Function
    Public Sub SetCurrentVector(length As Long, ByRef Data() As Double)
    Dim i As Long
        If Not IsNull(m_VecData) And Not IsNull(m_VecTime) Then
                m_CurrentIndex = (m_CurrentIndex + 1) Mod m_SignalLength 'Circular Buffer
                For i = 0 To length - 1
                    m_VecData(m_CurrentIndex, i) = Data(i)
                Next i
                m_VecTime(m_CurrentIndex) = Timer
        Else
            'Error Message (Invalid Argument)
        End If
    End Sub
    Public Sub DoInitial()
        ReDim m_VecData(m_SignalLength, m_VectorLength)
        ReDim m_VecTime(m_SignalLength)
    End Sub
    Public Function getvector(index As Long, length As Long, ByRef pdTime As Double) As Double()
    Dim i As Long
    Dim result() As Double
    If index > m_SignalLength Then
        'It cann't go back that far.
        'Error Message (E_fail)
    End If
    ' The index is the distance "back from current" into the signal
    ' Handle circularity of the signal buffer
    index = ((m_CurrentIndex + m_SignalLength) - index) Mod m_SignalLength
    ReDim result(length)
    If Not IsNull(m_VecData) Then
        If ((index < m_SignalLength) And (length <= m_VectorLength)) Then
            For i = 0 To length - 1
                result(i) = m_VecData(index, i)
                Debug.Print result(i)
            Next i
            pdTime = m_VecTime(index)
        Else
            'Error Message (Invalid Argument)
        End If
    Else
        For i = 0 To length - 1
            result(i) = 7.8 'Default Value.
        Next i
        pdTime = 8.7  'Default Value.
    End If
    getvector = result()
    End Function
    Public Sub SetVector(ByRef index As Long, length As Long, ByRef Data() As Double)
    Dim i As Long
    If index > m_SignalLength Then
        'It cann't go back that far.
        'Error Message (E_fail)
    End If
    ' The index is the distance "back from current" into the signal
    ' Handle circularity of the signal buffer
    index = ((m_CurrentIndex + (2 * m_SignalLength)) - index) Mod m_SignalLength
    If Not IsNull(m_VecData) And Not IsNull(m_VecTime) Then
        If ((index < m_SignalLength) And (length <= m_VectorLength)) Then
            For i = 0 To length - 1
                m_VecData(index, i) = Data(i)
            Next i
            m_VecTime(index) = Timer
        Else
            'Error Message (Invalid Argument)
        End If
    Else
        'Error Message (Invalid Argument)
    End If
    End Sub
    Public Sub SetVectorValue(ByRef index As Long, length As Long, ByRef Data() As Double)
    Dim i As Long
    If index > m_SignalLength Then
        'It cann't go back that far.
        'Error Message (E_fail)
    End If
    ' The index is the distance "back from current" into the signal
    ' Handle circularity of the signal buffer
    index = ((m_CurrentIndex + (2 * m_SignalLength)) - index) Mod m_SignalLength
    If Not IsNull(m_VecData) And Not IsNull(m_VecTime) Then
        If ((index < m_SignalLength) And (length <= m_VectorLength)) Then
            For i = 0 To length - 1
                m_VecData(index, i) = Data(i)
            Next i
        Else
            'Error Message (Invalid Argument)
        End If
    Else
        'Error Message (Invalid Argument)
    End If
    End Sub
    Private Sub Class_Initialize()
    Dim SgnlIndex, VctrIndex As Long
        m_Path = Path
        m_PID = PID
        Set m_AL = AL
        m_SignalLength = 10
        m_VectorLength = 20
        m_CurrentIndex = 0
        m_CurrentValue = 0
        Call DoInitial
        'Test initiallized data.
        'm_VecData(0, 0) = 1
        'm_VecData(0, 1) = 2
        'm_VecData(1, 0) = 3
        'm_VecData(1, 1) = 4
    End Sub

    Private Property Get IComponent_Activated() As Boolean
        IComponent_Activated = m_Activated
    End Property
    
    Private Property Let IComponent_Activated(ByVal RHS As Boolean)
    If Not IsNull(RHS) Then
        m_Activated = RHS
    End If
    End Property
    
    Private Sub IComponent_Destruct()
        'Unload (m_VecData)
        'Unload (m_VecTime)
    End Sub
    
    Private Sub IComponent_Construct(ByVal Path As String, ByVal PID As String, AL As IMA2.ILocator)
        'm_Machine = LocalMachine()
        'm_Path = Path
        'm_PID = PID
        'Set m_AL = AL
        Call Class_Initialize
    End Sub
    
    Private Function IComponent_DataSize() As Long
        'If VarType(m_Value) = vbString Then IComponent_DataSize = Len(m_Value)
    End Function
    Private Sub IComponent_Load(ByVal Data As Variant)
    Dim index, spindex As Long
    End Sub
    
    Private Function IComponent_Save() As Variant
    End Function
    
    Private Property Get IComponent_Machine() As String
        IComponent_Machine = m_Machine
    End Property
    
    Private Property Get IComponent_Path() As String
        IComponent_Path = m_Path
    End Property
    
    Private Property Get IComponent_PID() As String
        IComponent_PID = m_PID
    End Property
    Private Property Let IComponent_State(ByVal RHS As Variant):    End Property
    
    Private Property Get IComponent_State() As Variant
        'IComponent_State = ComponentState(Me, Array(Array("MyValue", m_Value)))
    End Property
    


'********************************************************************************************
' IContainer
'********************************************************************************************

    Private Property Get IContainer_ContextsAllowed() As IMA2.CLSCTX
        IContainer_ContextsAllowed = INPROC_SERVER Or LOCAL_SERVER Or REMOTE_SERVER
    End Property
    
    Private Function IContainer_CreateComponent(ByVal PID As String, ByVal Machine As String, ByVal Context As IMA2.CLSCTX) As IMA2.IComponent
        Set IContainer_CreateComponent = CreateObject(PID, Machine)
    End Function
    
    Private Property Get IContainer_InnateComponents() As Variant
    End Property
    
    Private Function IContainer_Locator() As IMA2.ILocator
        Set IContainer_Locator = m_AL
    End Function

