VERSION 5.00
Begin VB.UserControl RepMgr 
   BackColor       =   &H80000001&
   BorderStyle     =   1  'Fixed Single
   ClientHeight    =   2895
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4800
   ScaleHeight     =   2895
   ScaleWidth      =   4800
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   1320
      TabIndex        =   0
      Text            =   "Text1"
      Top             =   2040
      Width           =   2895
   End
End
Attribute VB_Name = "RepMgr"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

    Implements IManager
    
    Dim m_Cmp As Rep
    
    Private Property Let IManager_Component(ByVal RHS As IMA2.IComponent)
    
        Set m_Cmp = RHS
        
    End Property
    
    Private Property Get IManager_Component() As IMA2.IComponent
        
        Set IManager_Component = m_Cmp
        
    End Property
    
    Private Sub IManager_Update(pFlags As Variant)
    
        Text1.Text = "" & m_Cmp.Value
    
    End Sub
    
