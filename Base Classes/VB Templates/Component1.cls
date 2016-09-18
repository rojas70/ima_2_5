VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Component1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Implements IComponent

Dim m_AL            As IMA2.ILocator
Dim m_Distributing  As IMA2.IMA2_DistributingInfo
Dim m_Bindings      As IMA2.IBindings

Private Property Get IComponent_Bindings() As IMA2.IBindings
    Set IComponent_Bindings = m_Bindings
End Property

Private Sub IComponent_Construct(ByVal Path As String, ByVal PID As String, pAL As IMA2.ILocator)
    m_DistributingInfo = GetDistributingInfo(Me, Path, PID)
    Set m_Bindings = GetBindingsObject()
End Sub

Private Function IComponent_DataSize() As Long

End Function

Private Sub IComponent_Destruct()

End Sub

Private Property Get IComponent_Distributing() As IMA2.IMA2_DistributingInfo
    IComponent_Distributing = m_DistributingInfo
End Property

Private Sub IComponent_Load(ByVal Data As Variant)

End Sub

Private Function IComponent_Save() As Variant

End Function
