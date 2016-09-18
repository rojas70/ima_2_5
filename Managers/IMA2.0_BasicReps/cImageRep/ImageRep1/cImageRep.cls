VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "cImageRep"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Attribute VB_Ext_KEY = "SavedWithClassBuilder6" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
    Implements IComponent                               'Inherits IComponent interface.
    Dim m_Path As String, m_PID As String               'Needed for IComponent.
    Dim m_Machine As String, m_Activated As Boolean     'Needed for IComponent.
    Dim m_AL As ILocator                                'Needed for IComponent.
    
'********************************************************************************************
'********************************************************************************************
' Default interface (Define YOUR properties and methods here.)
'********************************************************************************************
'********************************************************************************************

    Dim m_Value     As Long

    Dim m_InPath    As String
    Dim m_InCmp     As IComponent
    
    Dim m_OutPath   As String
    Dim m_OutCmp    As IComponent                          'Needed for IComponent.
    
Dim m_ImageLength As Long
Dim m_CurrentIndex As Long
Private m_ImageData() As Byte
Private m_ImageTime As Double
Private mvarDepth As Long 'local copy
Private mvarHeight As Long 'local copy
Private mvarWidths As Long 'local copy
Private mvarTime As Double 'local copy
'local variable(s) to hold property value(s)
Private mvarPoint As Variant 'local copy
Public Sub Update()
End Sub

Public Function getData(Index As Long) As Byte()
Dim result() As Byte
    'Index = ((m_CurrentIndex + m_ImageLength) - Index) Mod m_ImageLength
    'ReDim result(m_ImageLength)
    'If Not IsNull(m_ImageData) Then
    '    If ((Index <= m_ImageLength)) Then
    '        For i = 0 To length - 1
    '            result = m_ImageData(Index)
    '        Next i
    '    Else
    '        'Error Message (Invalid Argument)
    '    End If
    'Else
    'End If
    'Data = result()
    getData = m_ImageData
End Function

Public Function putData(Index As Long, ByRef Data() As Byte)
Dim result() As Byte
    'Index = ((m_CurrentIndex + m_ImageLength) - Index) Mod m_ImageLength
    'ReDim result(m_ImageLength)
    'If Not IsNull(m_ImageData) Then
    '    If ((Index <= m_ImageLength)) Then
    '        For i = 0 To length - 1
    '            result = m_ImageData
    '        Next i
    '    Else
            'Error Message (Invalid Argument)
    '    End If
    'Else
    'End If
    'Data = result()
    m_ImageData = Data
End Function

Public Property Let Point(ByVal vData As Variant)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.Point = 5
    mvarPoint = vData
End Property

Public Property Set Point(ByVal vData As Variant)
'used when assigning an Object to the property, on the left side of a Set statement.
'Syntax: Set x.Point = Form1
    Set mvarPoint = vData
End Property

Public Property Get Point() As Variant
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Point
    If IsObject(mvarPoint) Then
        Set Point = mvarPoint
    Else
        Point = mvarPoint
    End If
End Property



Public Property Let Time(ByVal vData As Double)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.Time = 5
    mvarTime = vData
End Property


Public Property Get Time() As Double
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Time
    Time = mvarTime
End Property



Public Property Let ImageWidth(ByVal vData As Long)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.Widths = 5
    mvarWidths = vData
End Property


Public Property Get ImageWidth() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Widths
    ImageWidth = mvarWidths
End Property



Public Property Let ImageHeight(ByVal vData As Long)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.Height = 5
    mvarHeight = vData
End Property


Public Property Get ImageHeight() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Height
    ImageHeight = mvarHeight
End Property



Public Property Let ImageDepth(ByVal vData As Long)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.Depth = 5
    mvarDepth = vData
End Property


Public Property Get ImageDepth() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Depth
    ImageDepth = mvarDepth
End Property

Public Sub DoInitial()
    ReDim m_ImageData(mardepth, mvarWidths, mvarHeight)
End Sub

Private Sub Class_Initialize()
    mvarWidths = 800
    mvarHeight = 800
    m_ImageLength = 5
    mvarDepth = 2 'RGB: 0=RED,1=GREEN,2=BLUE
    Call DoInitial
End Sub

 Public Property Let InputComponent(NewVal As String)
        If Not m_Activated Then m_InPath = NewVal
    End Property
    
    Public Property Get InputComponent() As String
        InputComponent = m_InPath
    End Property

    Public Property Let OutputComponent(NewVal As String)
        If Not m_Activated Then m_OutPath = NewVal
    End Property
    
    Public Property Get OutputComponent() As String
        OutputComponent = m_OutPath
    End Property
    
    Public Property Get Value() As Long
        Value = m_Value
    End Property

    Public Property Let Value(NewVal As Long)
        If Not m_Activated Then m_Value = NewVal
    End Property
    
    Public Sub IncrementValue()
        If Not m_Activated Then m_Value = m_Value + 1
    End Sub

    Public Sub DecrementValue()
        If Not m_Activated Then m_Value = m_Value - 1
    End Sub

    Public Sub DoSomethingBig()
        If Not m_Activated Then Exit Sub
        'm_OutCmp.Data = m_InCmp.Data        'Transfer
    End Sub

'********************************************************************************************
'********************************************************************************************
' IMA2 overloaded IComponent functions
' - You can overload these if you like. Most people overload OnActivate and OnDeactivate
'********************************************************************************************
'********************************************************************************************

    Private Sub OnActivate()
        'This is the code you wish to execute when the component is activated. (Required)
'        Set m_InCmp = m_AL.Locate(m_InPath)
 '       Set m_OutCmp = m_AL.Locate(m_OutPath)
    
    End Sub

    Private Sub OnDeactivate()
        'This is the code you wish to execute when the component is deactivated. (Required)
'        Set m_InCmp = Nothing
'        Set m_OutCmp = Nothing
    End Sub

    Private Sub OnConstruct()
        'This is the code you wish to execute when the component is created. (Optional)
    End Sub
    
    Private Sub OnDestruct()
        'This is the code you wish to execute before the component is destroyed. (Optional)
    End Sub

    Private Function OnDataSize() As Long
        'This should return the size of your component's data. (Optional)
        '  Example:  OnDataSize = UBound(m_Data) * 2
    End Function

    Private Function OnSaveData() As Variant
        'This should return the data you wish to save to a file. (Optional)
        '  Example:  OnSaveData = Array(m_BinaryData, "MyData", 1, 2 3)
    End Function

    Private Sub OnLoadData(Data As Variant)
        'This should return the data you wish to save to a file. (Optional)
        '  Example:  OnLoadData = Array(m_BinaryData, "MyData", 1, 2 3)
    End Sub

    Private Function OnGetState() As Variant
        'This should return a list of variable names and their values for the user to see. (Optional)
        '  Example:  OnGetState = Array( Array("MyValue", m_Value), Array("MyCmpPath", m_MyCmpPath) )
    End Function

    Private Sub OnLetState(Data As Variant)
        'You should set the variables you returned in GetState() (Optional)
        '  Example:
        '
        ' Dim I As Integer
        '
        ' For I = 0 To UBound(Data) Step 1                    'Only set properties are returned.
        '     Select Case Data(I)(0)                          'Check the title
        '         Case "MyValue": m_MyValue = Data(I)(1)      'Set our first variable
        '         Case "MyCmpPath": m_MyCmpPath = Data(I)(1)  'Set our other variable
        '         Case Else:                                  'Unknown property
        '     End Select
        ' Next I
    End Sub


'********************************************************************************************
'********************************************************************************************
' IComponent
' - This is the default IMA2 interface for all components. (In C++ this is a base class)
' - ** Copy this section to your code exactly as it is here. Do NOT change it. **
'********************************************************************************************
'********************************************************************************************

    'Called when the component is created by a client.
    Private Sub IComponent_Construct(ByVal Path As String, ByVal PID As String, AL As IMA2.ILocator)
        m_Machine = LocalMachine()          'Save the machine we're running on.
        m_Path = Path                       'Save our path.
        m_PID = PID                         'Save our PID
        Set m_AL = AL                       'Get our pointer to the Agent Locator.
        Call OnConstruct                    'Pass on the event to the overloaded function.
    End Sub
    
    'Called when the component is destroyed.
    Private Sub IComponent_Destruct()
        Call OnDestruct                     'Pass on the event to the overloaded function.
    End Sub
    
    'Called to query how large the data in the component is.
    Private Function IComponent_DataSize() As Long
        IComponent_DataSize = OnDataSize    'Pass on the event to the overloaded function.
    End Function
    
    'Called to deserialize the component.
    '   Data As Variant - What you stored in IComponent_Save())
    Private Sub IComponent_Load(ByVal Data As Variant)
        Call OnLoadData(Data)               'Pass on the event to the overloaded function.
    End Sub
    
    'Called to serialize the component.
    '   IComponent_Save - The result value will be saved to a file.
    Private Function IComponent_Save() As Variant
        IComponent_Save = OnSaveData()      'Pass on the event to the overloaded function.
    End Function
    
    'Assigns a new state to the component.
    Private Property Let IComponent_State(ByVal RHS As Variant)
        Call OnLetState(RHS(1))             'Pass on the event to the overloaded function.
    End Property
    
    'Retrieves the component state.
    Private Property Get IComponent_State() As Variant
        IComponent_State = ComponentState(Me, OnGetState()) 'Pass on the event to the overloaded function.
    End Property
    
    'Returns our activation state.
    Private Property Get IComponent_Activated() As Boolean
        IComponent_Activated = m_Activated                  'Return our activation state
    End Property
    
    'Sets our activation state.
    Private Property Let IComponent_Activated(ByVal RHS As Boolean)
        m_Activated = RHS
        If RHS Then Call OnActivate Else Call OnDeactivate  'Set our activation state
    End Property
    
    'Returns the name of the machine we're running on.
    Private Property Get IComponent_Machine() As String
        IComponent_Machine = m_Machine                      'Return our machine name
    End Property
    
    'Returns our component path.
    Private Property Get IComponent_Path() As String
        IComponent_Path = m_Path                            'Return our path
    End Property
    
    'Returns our COM ProgID. (ProjectName.ClassName)
    Private Property Get IComponent_PID() As String
        IComponent_PID = m_PID                              'Return our ProgID
    End Property

