Attribute VB_Name = "ModMain"
'************************************************************************************************************************************
' Public types
'************************************************************************************************************************************
    Global UserOptions As New PropertyBag

    Global g_AL            As ILocator                      'Locator running on the local machine
    Global g_LA            As ILocatorAdvanced              'Advanced Locator interface
    Global g_IS            As IDistributingInfoProvider     'Information service running on the local machine


'************************************************************************************************************************************
' API Declarations
'************************************************************************************************************************************

Public Declare Function CopyFile Lib "kernel32" Alias "CopyFileA" (ByVal lpExistingFileName As String, ByVal lpNewFileName As String, ByVal bFailIfExists As Long) As Long

'************************************************************************************************************************************
'User Settings Functions
'************************************************************************************************************************************
    Public Sub LoadFormPosition(F As Form)
        Dim T As Single, L As Single, W As Single, H As Single
        T = Val(GetSetting(App.EXEName, F.Name, ".Left", CStr(F.Left)))
        L = Val(GetSetting(App.EXEName, F.Name, ".Top", CStr(F.Top)))
        W = Val(GetSetting(App.EXEName, F.Name, ".Width", CStr(F.Width)))
        H = Val(GetSetting(App.EXEName, F.Name, ".Height", CStr(F.Height)))
        F.Move T, L, W, H
    End Sub
    
    Public Sub SaveFormPosition(F As Form)
        Call SaveSetting(App.EXEName, F.Name, ".Left", F.Left)
        Call SaveSetting(App.EXEName, F.Name, ".Top", F.Top)
        Call SaveSetting(App.EXEName, F.Name, ".Width", F.Width)
        Call SaveSetting(App.EXEName, F.Name, ".Height", F.Height)
    End Sub


    Public Sub ExpandAllNodes(tvw As TreeView)
        For I = 1 To tvw.Nodes.Count Step 1
            tvw.Nodes(I).Expanded = True
        Next I
    End Sub
