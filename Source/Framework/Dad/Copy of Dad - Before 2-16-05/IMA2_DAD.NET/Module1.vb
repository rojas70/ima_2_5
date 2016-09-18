Option Strict Off
Option Explicit On
Module ModMain
	'************************************************************************************************************************************
	' Public types
	'************************************************************************************************************************************
	'UPGRADE_ISSUE: PropertyBag object was not upgraded. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup2068"'
	Public UserOptions As New PropertyBag
	
	'************************************************************************************************************************************
	' API Declarations
	'************************************************************************************************************************************
	
	Public Declare Function CopyFile Lib "kernel32"  Alias "CopyFileA"(ByVal lpExistingFileName As String, ByVal lpNewFileName As String, ByVal bFailIfExists As Integer) As Integer
	
	'************************************************************************************************************************************
	'User Settings Functions
	'************************************************************************************************************************************
	Public Sub LoadFormPosition(ByRef F As System.Windows.Forms.Form)
		Dim W, T, L, H As Single
		T = Val(GetSetting(VB6.GetExeName(), F.Name, ".Left", CStr(VB6.PixelsToTwipsX(F.Left))))
		L = Val(GetSetting(VB6.GetExeName(), F.Name, ".Top", CStr(VB6.PixelsToTwipsY(F.Top))))
		W = Val(GetSetting(VB6.GetExeName(), F.Name, ".Width", CStr(VB6.PixelsToTwipsX(F.Width))))
		H = Val(GetSetting(VB6.GetExeName(), F.Name, ".Height", CStr(VB6.PixelsToTwipsY(F.Height))))
		F.SetBounds(VB6.TwipsToPixelsX(T), VB6.TwipsToPixelsY(L), VB6.TwipsToPixelsX(W), VB6.TwipsToPixelsY(H))
	End Sub
	
	Public Sub SaveFormPosition(ByRef F As System.Windows.Forms.Form)
		Call SaveSetting(VB6.GetExeName(), F.Name, ".Left", CStr(VB6.PixelsToTwipsX(F.Left)))
		Call SaveSetting(VB6.GetExeName(), F.Name, ".Top", CStr(VB6.PixelsToTwipsY(F.Top)))
		Call SaveSetting(VB6.GetExeName(), F.Name, ".Width", CStr(VB6.PixelsToTwipsX(F.Width)))
		Call SaveSetting(VB6.GetExeName(), F.Name, ".Height", CStr(VB6.PixelsToTwipsY(F.Height)))
	End Sub
	
	
	Public Sub ExpandAllNodes(ByRef tvw As AxMSComctlLib.AxTreeView)
		Dim I As Object
		For I = 1 To tvw.Nodes.Count Step 1
			tvw.Nodes(I).Expanded = True
		Next I
	End Sub
End Module