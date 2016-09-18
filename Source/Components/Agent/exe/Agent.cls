VERSION 1.0 CLASS
BEGIN
  MultiUse = 0   'False
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Agent"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit
    
    Implements IComponent                               'Needed for all IMA2 components.
        
    Dim m_DI            As IMA2_DistributingInfo
    Dim m_Bindings      As IBindings                    'Component's binding collection
    Dim m_AL            As ILocator                     'Component's Locator pointer (where it is registered)
    
    Implements IMA2.IContainer                          'Needed for containers

'********************************************************************************************
' Default interface (All the stuff that makes your component unique.)
'********************************************************************************************


'********************************************************************************************
' IComponent
' - Default IMA2 interface for all components.
' - ** Copy this section to your code exactly as it is here. **
'********************************************************************************************

    'Called when the component is created.
    Private Sub IComponent_Construct(ByVal Path As String, ByVal PID As String, AL As IMA2.ILocator)
        m_DI = GetDistributingInfo(Me, Path, PID)
        Set m_AL = AL
        App.Title = App.Title + Path
 '      Set m_Bindings = CreateObject("IMA2_Bindings.Bindings")
 '      Call m_Bindings.Construct(Path, AL)
    End Sub
    
    'Called when the component is destroyed.
    Private Sub IComponent_Destruct()
'        Call m_Bindings.Destruct
        End
    End Sub
    
    'Called to query how large the data in the component is.
    Private Function IComponent_DataSize() As Long
        IComponent_DataSize = 0
    End Function
    
    Private Property Get IComponent_Distributing() As IMA2.IMA2_DistributingInfo
        IComponent_Distributing = m_DI
    End Property

    'Called to deserialize the component. (Data is what you stored in IComponent_Save())
    Private Sub IComponent_Load(ByVal Data As Variant)
    End Sub
    
    'Called to serialize the component. (Whatever you pass as the result value will be saved to a file.)
    Private Function IComponent_Save() As Variant
    End Function
    
    Private Property Get IComponent_Bindings() As IMA2.IBindings
        Set IComponent_Bindings = m_Bindings
    End Property

'********************************************************************************************
' IContainer
' - Implemented only by components that will contain other components.
'********************************************************************************************

    Private Function IContainer_CreateComponent(ByVal PID As String, ByVal Machine As String) As IMA2.IComponent
        Set IContainer_CreateComponent = CreateObject(PID, Machine)
    End Function
    
    Private Property Get IContainer_InnateComponents() As String()
    
    End Property
