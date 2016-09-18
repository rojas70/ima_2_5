VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "cTextQueue"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Attribute VB_Ext_KEY = "SavedWithClassBuilder6" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
Implements IComponent
Implements IContainer


Dim m_CurrentValue As Long, m_QueueData(), m_QueueTime() As Double
Dim m_Path As String, m_PID As String               'Needed for all components.
Dim m_Machine As String, m_Activated As Boolean     'Needed for all components.
Dim m_AL As ILocator                                'Needed for all components.

Private mvarStringValue As String 'local copy
Private mvarQueueLength As Long 'local copy
Private mvarDataPersistent As Long 'local copy
Private mvarCurrentText As String 'local copy
Private mvarCurrentIndex As Long 'local copy
Private mvarAgentEventType As Long 'local copy
Private mvarAgentEventID As Long 'local copy
Public Sub FireAgentEvent(vType As Long, vId As Long)
End Sub

Public Sub setCurrentText(vText As String)
        If Not IsNull(m_QueueData) And Not IsNull(m_QueueTime) Then
            mvarCurrentIndex = (mvarCurrentIndex + 1) Mod mvarQueueLength 'Circular Buffer
            m_QueueData(mvarCurrentIndex) = vText
            m_QueueTime(mvarCurrentIndex) = Timer
        Else
            'Error Message (Invalid Argument)
        End If
End Sub

Public Sub setText(ByVal index As Long, vText As String)
    Dim i As Long
    If index > mvarQueueLength Then
        'It cann't go back that far.
        'Error Message (E_fail)
    End If
    ' The index is the distance "back from current" into the signal
    ' Handle circularity of the signal buffer
    index = ((mvarCurrentIndex + (2 * mvarQueueLength)) - index) Mod mvarQueueLength
    If Not IsNull(m_QueueData) And Not IsNull(m_QueueTime) Then
        If (index < mvarQueueLength) Then
            m_QueueData(index) = vText
            m_QueueTime(index) = Timer
        Else
            'Error Message (Invalid Argument)
        End If
    Else
        'Error Message (Invalid Argument)
    End If
End Sub


Public Sub setTextvalue(ByVal index As Long, vText As String)
    Dim i As Long
    If index > mvarQueueLength Then
        'It cann't go back that far.
        'Error Message (E_fail)
    End If
    ' The index is the distance "back from current" into the signal
    ' Handle circularity of the signal buffer
    index = ((mvarCurrentIndex + (2 * mvarQueueLength)) - index) Mod mvarQueueLength
    If Not IsNull(m_QueueData) And Not IsNull(m_QueueTime) Then
        If (index < mvarQueueLength) Then
            m_QueueData(index) = vText
            'm_QueueTime(index) = Timer
        Else
            'Error Message (Invalid Argument)
        End If
    Else
        'Error Message (Invalid Argument)
    End If
End Sub

Public Function getCurrenttext(pdTime As Double) As String
Dim i As Long
        If Not IsNull(m_VecData) Then
            getCurrenttext = m_QueueData(mvarCurrentIndex)
            If pdTime <> Null Then
                pdTime = m_QueueTime(mvarCurrentIndex)
            End If
        Else
            getCurrenttext = ""
            If pdTime <> Null Then
                pdTime = 7.7  'Default Value.
            End If
        End If
End Function

Public Function GetText(ByVal index As Long, pdTime As Double) As String
    Dim i As Long
    'Dim result() As String
    If index > mvarQueueLength Then
        'It cann't go back that far.
        'Error Message (E_fail)
    End If
    ' The index is the distance "back from current" into the signal
    ' Handle circularity of the signal buffer
    index = ((mvarCurrentIndex + mvarQueueLength) - index) Mod mvarQueueLength
    'ReDim result
    If Not IsNull(m_QueueData) Then
        If (index < mvarQueueLength) Then
            GetText = m_QueueData(index)
            pdTime = m_QueueTime(index)
        Else
            'Error Message (Invalid Argument)
        End If
    Else
        GetText = 7.8 'Default Value.
        pdTime = 8.7  'Default Value.
    End If
End Function

Public Property Let AgentEventID(ByVal vData As Long)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.AgentEventID = 5
    mvarAgentEventID = vData
End Property


Public Property Get AgentEventID() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.AgentEventID
    AgentEventID = mvarAgentEventID
End Property



Public Property Let AgentEventType(ByVal vData As Long)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.AgentEventType = 5
    mvarAgentEventType = vData
End Property


Public Property Get AgentEventType() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.AgentEventType
    AgentEventType = mvarAgentEventType
End Property



Public Property Let CurrentIndex(ByVal vData As Long)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.CurrentIndex = 5
    mvarCurrentIndex = vData
End Property


Public Property Get CurrentIndex() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.CurrentIndex
    CurrentIndex = mvarCurrentIndex
End Property



Public Property Let CurrentText(ByVal vData As String)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.CurrentText = 5
    mvarCurrentText = vData
End Property


Public Property Get CurrentText() As String
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.CurrentText
    CurrentText = mvarCurrentText
End Property



Public Property Let DataPersistent(ByVal vData As Long)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.DataPersistent = 5
    mvarDataPersistent = vData
End Property


Public Property Get DataPersistent() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.DataPersistent
    DataPersistent = mvarDataPersistent
End Property



Public Property Let QueueLength(ByVal vData As Long)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.QueueLength = 5
    mvarQueueLength = vData
End Property


Public Property Get QueueLength() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.QueueLength
    QueueLength = mvarQueueLength
End Property



Public Property Let StringValue(ByVal vData As String)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.StringValue = 5
    mvarStringValue = vData
End Property


Public Property Get StringValue() As String
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.StringValue
    StringValue = mvarStringValue
End Property
    Public Sub DoInitial()
        ReDim m_QueueData(mvarQueueLength)
        ReDim m_QueueTime(mvarQueueLength)
        mvarCurrentIndex = 0
    End Sub


Private Sub Class_Initialize()
    mvarQueueLength = 10
    Call DoInitial
    'Test initiallized data.
    m_QueueData(0) = "1234568790"
End Sub

Private Property Let IComponent_Activated(ByVal RHS As Boolean)

End Property

Private Property Get IComponent_Activated() As Boolean

End Property

Private Sub IComponent_Construct(ByVal Path As String, ByVal PID As String, AL As IMA2.ILocator)
        m_Machine = LocalMachine()
        m_Path = Path
        m_PID = PID
        Set m_AL = AL
        Call Class_Initialize
End Sub

Private Function IComponent_DataSize() As Long

End Function

Private Sub IComponent_Destruct()

End Sub

Private Sub IComponent_Load(ByVal Data As Variant)

End Sub

Private Property Get IComponent_Machine() As String
    IComponent_Machine = m_Machine
End Property

Private Property Get IComponent_Path() As String
    IComponent_Path = m_Path
End Property

Private Property Get IComponent_PID() As String
    IComponent_PID = m_PID
End Property

Private Function IComponent_Save() As Variant

End Function

Private Property Let IComponent_State(ByVal RHS As Variant)
    mvarCurrentText = RHS(2)(2) 'Retrieves MyValue
End Property

Private Property Get IComponent_State() As Variant
    IComponent_State = ComponentState(Me, Array(Array("Current Text", mvarCurrentText)))  'Stores MyValue
End Property

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
