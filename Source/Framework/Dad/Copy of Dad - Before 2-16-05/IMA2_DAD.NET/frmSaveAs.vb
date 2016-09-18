Option Strict Off
Option Explicit On
Friend Class frmSaveAs
	Inherits System.Windows.Forms.Form
#Region "Windows Form Designer generated code "
	Public Sub New()
		MyBase.New()
		If m_vb6FormDefInstance Is Nothing Then
			If m_InitializingDefInstance Then
				m_vb6FormDefInstance = Me
			Else
				Try 
					'For the start-up form, the first instance created is the default instance.
					If System.Reflection.Assembly.GetExecutingAssembly.EntryPoint.DeclaringType Is Me.GetType Then
						m_vb6FormDefInstance = Me
					End If
				Catch
				End Try
			End If
		End If
		'This call is required by the Windows Form Designer.
		InitializeComponent()
	End Sub
	'Form overrides dispose to clean up the component list.
	Protected Overloads Overrides Sub Dispose(ByVal Disposing As Boolean)
		If Disposing Then
			If Not components Is Nothing Then
				components.Dispose()
			End If
		End If
		MyBase.Dispose(Disposing)
	End Sub
	'Required by the Windows Form Designer
	Private components As System.ComponentModel.IContainer
	Public ToolTip1 As System.Windows.Forms.ToolTip
	Public WithEvents ocb As AxIMA2_HelperX.AxOKCancelBar
	Public WithEvents wiz As AxIMA2_HelperX.AxWizardBar
	Public WithEvents cdlg As AxMSComDlg.AxCommonDialog
	Public WithEvents iml As AxMSComctlLib.AxImageList
	Public WithEvents tvw As AxMSComctlLib.AxTreeView
	'NOTE: The following procedure is required by the Windows Form Designer
	'It can be modified using the Windows Form Designer.
	'Do not modify it using the code editor.
	<System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
		Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(frmSaveAs))
		Me.components = New System.ComponentModel.Container()
		Me.ToolTip1 = New System.Windows.Forms.ToolTip(components)
		Me.ToolTip1.Active = True
		Me.ocb = New AxIMA2_HelperX.AxOKCancelBar
		Me.wiz = New AxIMA2_HelperX.AxWizardBar
		Me.cdlg = New AxMSComDlg.AxCommonDialog
		Me.iml = New AxMSComctlLib.AxImageList
		Me.tvw = New AxMSComctlLib.AxTreeView
		CType(Me.ocb, System.ComponentModel.ISupportInitialize).BeginInit()
		CType(Me.wiz, System.ComponentModel.ISupportInitialize).BeginInit()
		CType(Me.cdlg, System.ComponentModel.ISupportInitialize).BeginInit()
		CType(Me.iml, System.ComponentModel.ISupportInitialize).BeginInit()
		CType(Me.tvw, System.ComponentModel.ISupportInitialize).BeginInit()
		Me.Text = "C:\Ima2\Agent1.Cmp"
		Me.ClientSize = New System.Drawing.Size(481, 281)
		Me.Location = New System.Drawing.Point(11, 30)
		Me.Icon = CType(resources.GetObject("frmSaveAs.Icon"), System.Drawing.Icon)
		Me.MaximizeBox = False
		Me.MinimizeBox = False
		Me.StartPosition = System.Windows.Forms.FormStartPosition.WindowsDefaultLocation
		Me.Font = New System.Drawing.Font("Arial", 8!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
		Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
		Me.BackColor = System.Drawing.SystemColors.Control
		Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Sizable
		Me.ControlBox = True
		Me.Enabled = True
		Me.KeyPreview = False
		Me.Cursor = System.Windows.Forms.Cursors.Default
		Me.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.ShowInTaskbar = True
		Me.HelpButton = False
		Me.WindowState = System.Windows.Forms.FormWindowState.Normal
		Me.Name = "frmSaveAs"
		ocb.OcxState = CType(resources.GetObject("ocb.OcxState"), System.Windows.Forms.AxHost.State)
		Me.ocb.Dock = System.Windows.Forms.DockStyle.Bottom
		Me.ocb.Size = New System.Drawing.Size(481, 33)
		Me.ocb.Location = New System.Drawing.Point(0, 248)
		Me.ocb.TabIndex = 2
		Me.ocb.Name = "ocb"
		wiz.OcxState = CType(resources.GetObject("wiz.OcxState"), System.Windows.Forms.AxHost.State)
		Me.wiz.Dock = System.Windows.Forms.DockStyle.Top
		Me.wiz.Size = New System.Drawing.Size(481, 49)
		Me.wiz.Location = New System.Drawing.Point(0, 0)
		Me.wiz.TabIndex = 1
		Me.wiz.Name = "wiz"
		cdlg.OcxState = CType(resources.GetObject("cdlg.OcxState"), System.Windows.Forms.AxHost.State)
		Me.cdlg.Location = New System.Drawing.Point(552, 336)
		Me.cdlg.Name = "cdlg"
		iml.OcxState = CType(resources.GetObject("iml.OcxState"), System.Windows.Forms.AxHost.State)
		Me.iml.Location = New System.Drawing.Point(552, 296)
		Me.iml.Name = "iml"
		tvw.OcxState = CType(resources.GetObject("tvw.OcxState"), System.Windows.Forms.AxHost.State)
		Me.tvw.Size = New System.Drawing.Size(249, 185)
		Me.tvw.Location = New System.Drawing.Point(8, 56)
		Me.tvw.TabIndex = 0
		Me.tvw.Name = "tvw"
		Me.Controls.Add(ocb)
		Me.Controls.Add(wiz)
		Me.Controls.Add(cdlg)
		Me.Controls.Add(iml)
		Me.Controls.Add(tvw)
		CType(Me.tvw, System.ComponentModel.ISupportInitialize).EndInit()
		CType(Me.iml, System.ComponentModel.ISupportInitialize).EndInit()
		CType(Me.cdlg, System.ComponentModel.ISupportInitialize).EndInit()
		CType(Me.wiz, System.ComponentModel.ISupportInitialize).EndInit()
		CType(Me.ocb, System.ComponentModel.ISupportInitialize).EndInit()
	End Sub
#End Region 
#Region "Upgrade Support "
	Private Shared m_vb6FormDefInstance As frmSaveAs
	Private Shared m_InitializingDefInstance As Boolean
	Public Shared Property DefInstance() As frmSaveAs
		Get
			If m_vb6FormDefInstance Is Nothing OrElse m_vb6FormDefInstance.IsDisposed Then
				m_InitializingDefInstance = True
				m_vb6FormDefInstance = New frmSaveAs()
				m_InitializingDefInstance = False
			End If
			DefInstance = m_vb6FormDefInstance
		End Get
		Set
			m_vb6FormDefInstance = Value
		End Set
	End Property
#End Region 
	
	'************************************************************************************************
	' Private Member Variables
	'************************************************************************************************
	
	Dim m_CF As IMA2_Helper.ComponentFile
	Dim m_Icons As New IMA2_Helper.IconManager
	Dim m_Saved As Boolean
	
	'************************************************************************************************
	'  Public Functions
	'************************************************************************************************
	
	Public Sub DoSave(ByRef CmpPaths() As String, ByRef Nds As MSComctlLib.Nodes)
		
		Dim Paths() As String
		
		Paths = VB6.CopyArray(CmpPaths)
		If IMA2_HelperFunctions_definst.ArrayEmpty(Paths) Then Exit Sub 'Check for wrong input args
		
		UpdateViewFromPaths(Paths) 'Generate tree from paths
		SynchronizeImages(Nds) 'Synchronize images across treeviews
		ExpandAllNodes(tvw) 'Expand nodes
		
		m_CF = New IMA2_Helper.ComponentFile 'Generate a new component file
		m_CF.Paths = VB6.CopyArray(Paths) 'Fill in the paths to save
		
		Me.ShowDialog() 'Show the form
		
	End Sub
	
	'************************************************************************************************
	
	Private Sub SynchronizeImages(ByRef Nds As MSComctlLib.Nodes)
		
		Dim I As Short
		
		For I = 1 To tvw.Nodes.Count Step 1
			'UPGRADE_WARNING: Couldn't resolve default property of object Nds().Image. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
			tvw.Nodes(I).Image = Nds(tvw.Nodes(I).Key).Image
		Next I
		
	End Sub
	
	'************************************************************************************************
	' Private Functions
	'************************************************************************************************
	
	Private Sub UpdateViewFromPaths(ByRef P() As String)
		
		On Error Resume Next
		
		Dim I As Short
		Dim PN As MSComctlLib.Node
		Dim UB As Short
		Dim LB As Short
		
		LB = LBound(P)
		UB = UBound(P)
		If Err.Number Then MsgBox("Error in array")
		
		tvw.Nodes.Clear()
		
		tvw.Nodes.Add( ,  , P(LB), IMA2_HelperFunctions_definst.NameFromPath(P(LB)), IMA2_Helper.IMA2_Icons.II_Component)
		For I = LB + 1 To UB Step 1
			PN = tvw.Nodes.Item(IMA2_HelperFunctions_definst.ParentFromPath(P(I)))
			tvw.Nodes.Add(PN, MSComctlLib.TreeRelationshipConstants.tvwChild, P(I), IMA2_HelperFunctions_definst.NameFromPath(P(I)), IMA2_Helper.IMA2_Icons.II_Component)
		Next 
		
		If Err.Number Then MsgBox("Error in array 2")
		
	End Sub
	
	'************************************************************************************************
	
	Public Sub Actualize()
		
		Dim Cmp As IMA2.IComponent
		Dim I As Short
		Dim CDs() As IMA2_Helper.CmpDesc
		Dim AL As IMA2.ILocator
		
		AL = IMA2_HelperFunctions_definst.GetLocator()
		
		CDs = VB6.CopyArray(m_CF.Descriptions)
		For I = 0 To UBound(CDs)
			With CDs(I)
				Cmp = IMA2_HelperFunctions_definst.CreateIMA2Component(.Path, .PID, .Machine, True, AL)
				'UPGRADE_WARNING: IsEmpty was upgraded to IsNothing and has a new behavior. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1041"'
				If Not IsNothing(.Data) Then Call Cmp.Load(.Data)
			End With
		Next 
		
	End Sub
	
	'************************************************************************************************
	' Public Properties
	'************************************************************************************************
	
	'    Private Property Get Nodes() As Nodes
	'       Set Nodes = tvw.Nodes
	'  End Property
	
	'    Private Property Get Paths() As String()
	'       Paths = m_CF.Paths
	'  End Property
	
	'************************************************************************************************
	
	'    Public Property Let Paths(NewVal() As String)
	'       Dim S() As String
	'      If ArrayEmpty(NewVal) Then Exit Property
	'     S = NewVal
	'    m_CF.Paths = S
	'   Call UpdateViewFromPaths
	'End Property
	
	'************************************************************************************************
	' Menu Events
	'************************************************************************************************
	
	'************************************************************************************************
	' Public Properties
	'************************************************************************************************
	
	
	Public Property FilePath() As String
		Get
			FilePath = m_CF.FilePath
		End Get
		Set(ByVal Value As String)
			m_CF.FilePath = Value
			If m_Saved Then
				Me.Text = Value
			Else
				Me.Text = Value & "*"
			End If
		End Set
	End Property
	
	'************************************************************************************************
	' Form Events
	'************************************************************************************************
	
	Private Sub frmSaveAs_Load(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MyBase.Load
		'UPGRADE_WARNING: Couldn't resolve default property of object m_Icons.ImageList.GetOcx. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
		tvw.ImageList = m_Icons.ImageList.GetOcx
		m_CF = New IMA2_Helper.ComponentFile
	End Sub
	
	'UPGRADE_WARNING: Event frmSaveAs.Resize may fire when form is intialized. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup2075"'
	Private Sub frmSaveAs_Resize(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MyBase.Resize
		tvw.SetBounds(tvw.Left, tvw.Top, (Me.ClientRectangle.Width / 2) - (tvw.Left * 2), Me.ClientRectangle.Height - tvw.Top - ocb.Height - tvw.Left) ';- stb.Height
	End Sub
	
	'************************************************************************************************
	' Misc. Functions
	'************************************************************************************************
	
	Private Function GetFileName(ByRef OFN As String) As Object
		
		On Error Resume Next
		
		Dim Prompt As String
		Dim Temp As String
		
		cdlg.FileName = OFN
		
MFSAP: Me.Visible = False
		
		cdlg.ShowSave()
		
		If Err.Number > 0 Then
			Me.Visible = True
			Err.Clear()
			Exit Function
		End If
		
		If IMA2_HelperFunctions_definst.FileExists((cdlg.FileName)) Then
			Prompt = cdlg.FileName & " exists. Overwrite?"
			Select Case MsgBox(Prompt, MsgBoxStyle.YesNoCancel Or MsgBoxStyle.Question)
				Case MsgBoxResult.Yes : Kill(cdlg.FileName)
				Case MsgBoxResult.No : GoTo MFSAP
				Case MsgBoxResult.Cancel
					Me.Visible = True
					Exit Function
			End Select
		End If
		
		'UPGRADE_WARNING: Couldn't resolve default property of object GetFileName. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
		GetFileName = cdlg.FileName
		
	End Function
	
	'******************************************************************************************
	
	Private Sub ocb_OnCancel(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles ocb.OnCancel
		Me.Hide()
	End Sub
	
	'******************************************************************************************
	
	Private Sub ocb_OnOK(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles ocb.OnOK
		
		Dim FN As String
		
		'UPGRADE_WARNING: Couldn't resolve default property of object GetFileName(). Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
		FN = GetFileName((m_CF.FilePath))
		If FN = "" Then Exit Sub
		
		m_CF.FilePath = FN
		'Call UpdateFromPaths
		m_CF.Save()
		
		'        SavedBefore = True
		
		If Err.Number Then MsgBox("Oh no!")
		
	End Sub
End Class