VERSION 5.00
Begin VB.UserControl EngineMgr 
   ClientHeight    =   1965
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4800
   ScaleHeight     =   1965
   ScaleWidth      =   4800
   ToolboxBitmap   =   "EngineMgr.ctx":0000
   Begin VB.TextBox txtClients 
      Height          =   1005
      Left            =   1920
      MultiLine       =   -1  'True
      TabIndex        =   4
      Text            =   "EngineMgr.ctx":0312
      Top             =   840
      Width           =   2775
   End
   Begin VB.TextBox txtInterval 
      Height          =   285
      Left            =   1920
      TabIndex        =   2
      Text            =   "100"
      Top             =   120
      Width           =   2775
   End
   Begin VB.TextBox txtMethod 
      Height          =   285
      Left            =   1920
      TabIndex        =   0
      Text            =   "Foo"
      Top             =   480
      Width           =   2775
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "Clients:"
      Height          =   195
      Left            =   0
      TabIndex        =   5
      Top             =   840
      Width           =   510
   End
   Begin VB.Label Label3 
      AutoSize        =   -1  'True
      Caption         =   "Interval (msec):"
      Height          =   195
      Left            =   0
      TabIndex        =   3
      Top             =   120
      Width           =   1080
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      Caption         =   "Method Name:"
      Height          =   195
      Left            =   0
      TabIndex        =   1
      Top             =   480
      Width           =   1050
   End
   Begin VB.Menu mnuComponent 
      Caption         =   "&Component"
      Begin VB.Menu mnuGet 
         Caption         =   "&Get"
      End
      Begin VB.Menu mnuSet 
         Caption         =   "&Set"
      End
   End
End
Attribute VB_Name = "EngineMgr"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
'********************************************************************************************
' Class:        BasicIMA.EngineMgr
' Author:       Roberto Olivares (olivarre@vuse.vanderbilt.edu)
' Last update:  (4/7/00)
'
' Description:  This is a simple IMA2 engine manager that lets you modify BasicIMA.Engine.
'               Remember to right click on the manager to bring up the get/set menu.
'********************************************************************************************
    
    Option Explicit             'Code like a man
    
    Implements IManager         'Now become a manager
    
    Dim m_Engine   As Engine    'Our client component

    Private Sub IManager_AddComponent(pCmp As IMA2.IComponent)
    
    End Sub
    
    Private Sub IManager_RemoveComponent(pCmp As IMA2.IComponent)
    
    End Sub

    Private Sub IManager_Update(pFlags As Variant)
        If m_Engine Is Nothing Then Exit Sub
        Call mnuGet_Click
    End Sub

'********************************************************************************************
' Usercontrol Events
'********************************************************************************************

    Private Sub UserControl_Initialize()
        'Call ShowAgent          'For debugging **ONLY** -- shows the AB2000 window.
    End Sub
    
    Private Sub UserControl_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
        If Button And vbRightButton Then PopupMenu mnuComponent
    End Sub

'********************************************************************************************
' Menu Events
'********************************************************************************************

    Private Sub mnuGet_Click()
        
        If m_Engine Is Nothing Then Exit Sub
        
        txtInterval = m_Engine.Interval
        txtMethod = m_Engine.Method
        txtClients = Join(m_Engine.Clients, vbCrLf)
        
    End Sub
    
    Private Sub mnuSet_Click()
    
        Dim Cs As String
        Dim CA() As String
        
        Cs = Replace(Trim(txtClients), " ", "")
        CA = Split(Cs, CStr(vbCrLf))
        
        m_Engine.Interval = txtInterval
        m_Engine.Method = txtMethod
        m_Engine.Clients = CA

    End Sub

'********************************************************************************************
' IManager Implementation
'********************************************************************************************

    'Called by AgentBuilder when a manager is attached to a component.
    Private Sub IManager_SetComponent(C As IMA2.IComponent)
        
        If (C Is Nothing) Then                  '1) Check if C is nothing
            Set m_Engine = Nothing              '   Unbind to the component
            mnuComponent.Enabled = False        '   Update UI
            Exit Sub                            '   Exit
        End If
        
        If Not (TypeOf C Is Engine) Then        '2) Check if TypeOf C is supported.
            Set m_Engine = Nothing              '   Unbind to the component
            mnuComponent.Enabled = False        '   Update UI
            Exit Sub                            '   Exit
        End If
    
        Set m_Engine = C                        '3) Set the member variable pointer
        Call mnuGet_Click                       '   and update the display.
    
    End Sub
    
    'Called by AgentBuilder when a manager is attached to a component.


