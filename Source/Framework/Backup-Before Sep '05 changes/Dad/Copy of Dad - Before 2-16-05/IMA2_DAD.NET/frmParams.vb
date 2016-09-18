Option Strict Off
Option Explicit On
Friend Class frmParams
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
	Public WithEvents lvw As AxMSComctlLib.AxListView
	Public WithEvents WizardBar1 As AxIMA2_HelperX.AxWizardBar
	Public WithEvents OKCancelBar1 As AxIMA2_HelperX.AxOKCancelBar
	'NOTE: The following procedure is required by the Windows Form Designer
	'It can be modified using the Windows Form Designer.
	'Do not modify it using the code editor.
	<System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
		Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(frmParams))
		Me.components = New System.ComponentModel.Container()
		Me.ToolTip1 = New System.Windows.Forms.ToolTip(components)
		Me.ToolTip1.Active = True
		Me.lvw = New AxMSComctlLib.AxListView
		Me.WizardBar1 = New AxIMA2_HelperX.AxWizardBar
		Me.OKCancelBar1 = New AxIMA2_HelperX.AxOKCancelBar
		CType(Me.lvw, System.ComponentModel.ISupportInitialize).BeginInit()
		CType(Me.WizardBar1, System.ComponentModel.ISupportInitialize).BeginInit()
		CType(Me.OKCancelBar1, System.ComponentModel.ISupportInitialize).BeginInit()
		Me.Text = "Specify Parameters Wizard"
		Me.ClientSize = New System.Drawing.Size(440, 384)
		Me.Location = New System.Drawing.Point(4, 23)
		Me.ControlBox = False
		Me.StartPosition = System.Windows.Forms.FormStartPosition.WindowsDefaultLocation
		Me.Font = New System.Drawing.Font("Arial", 8!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
		Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
		Me.BackColor = System.Drawing.SystemColors.Control
		Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Sizable
		Me.Enabled = True
		Me.KeyPreview = False
		Me.MaximizeBox = True
		Me.MinimizeBox = True
		Me.Cursor = System.Windows.Forms.Cursors.Default
		Me.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.ShowInTaskbar = True
		Me.HelpButton = False
		Me.WindowState = System.Windows.Forms.FormWindowState.Normal
		Me.Name = "frmParams"
		lvw.OcxState = CType(resources.GetObject("lvw.OcxState"), System.Windows.Forms.AxHost.State)
		Me.lvw.Size = New System.Drawing.Size(417, 257)
		Me.lvw.Location = New System.Drawing.Point(8, 64)
		Me.lvw.TabIndex = 2
		Me.lvw.Name = "lvw"
		WizardBar1.OcxState = CType(resources.GetObject("WizardBar1.OcxState"), System.Windows.Forms.AxHost.State)
		Me.WizardBar1.Dock = System.Windows.Forms.DockStyle.Top
		Me.WizardBar1.Size = New System.Drawing.Size(440, 57)
		Me.WizardBar1.Location = New System.Drawing.Point(0, 0)
		Me.WizardBar1.TabIndex = 1
		Me.WizardBar1.Name = "WizardBar1"
		OKCancelBar1.OcxState = CType(resources.GetObject("OKCancelBar1.OcxState"), System.Windows.Forms.AxHost.State)
		Me.OKCancelBar1.Dock = System.Windows.Forms.DockStyle.Bottom
		Me.OKCancelBar1.Size = New System.Drawing.Size(440, 38)
		Me.OKCancelBar1.Location = New System.Drawing.Point(0, 346)
		Me.OKCancelBar1.TabIndex = 0
		Me.OKCancelBar1.Name = "OKCancelBar1"
		Me.Controls.Add(lvw)
		Me.Controls.Add(WizardBar1)
		Me.Controls.Add(OKCancelBar1)
		CType(Me.OKCancelBar1, System.ComponentModel.ISupportInitialize).EndInit()
		CType(Me.WizardBar1, System.ComponentModel.ISupportInitialize).EndInit()
		CType(Me.lvw, System.ComponentModel.ISupportInitialize).EndInit()
	End Sub
#End Region 
#Region "Upgrade Support "
	Private Shared m_vb6FormDefInstance As frmParams
	Private Shared m_InitializingDefInstance As Boolean
	Public Shared Property DefInstance() As frmParams
		Get
			If m_vb6FormDefInstance Is Nothing OrElse m_vb6FormDefInstance.IsDisposed Then
				m_InitializingDefInstance = True
				m_vb6FormDefInstance = New frmParams()
				m_InitializingDefInstance = False
			End If
			DefInstance = m_vb6FormDefInstance
		End Get
		Set
			m_vb6FormDefInstance = Value
		End Set
	End Property
#End Region 
	
	'UPGRADE_NOTE: ShowDialog was upgraded to ShowDialog_Renamed. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1061"'
	Public Sub ShowDialog_Renamed()
		lvw.ColumnHeaders(2).Position = 1 : Me.ShowDialog()
	End Sub
	
	'UPGRADE_WARNING: Event frmParams.Resize may fire when form is intialized. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup2075"'
	Private Sub frmParams_Resize(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MyBase.Resize
		lvw.Width = Me.ClientRectangle.Width - (lvw.Left * 2)
		lvw.Height = Me.ClientRectangle.Height - (lvw.Left * 1) - OKCancelBar1.Height - lvw.Top
		lvw.ColumnHeaders(1).Width = lvw.Width - lvw.ColumnHeaders(2).Width - lvw.ColumnHeaders(3).Width - 6
	End Sub
	
	Private Sub lvw_KeyDownEvent(ByVal eventSender As System.Object, ByVal eventArgs As AxMSComctlLib.ListViewEvents_KeyDownEvent) Handles lvw.KeyDownEvent
		If eventArgs.KeyCode = System.Windows.Forms.Keys.Up Then Exit Sub
		If eventArgs.KeyCode = System.Windows.Forms.Keys.Down Then Exit Sub
		lvw.StartLabelEdit()
	End Sub
	
	Private Sub lvw_MouseUpEvent(ByVal eventSender As System.Object, ByVal eventArgs As AxMSComctlLib.ListViewEvents_MouseUpEvent) Handles lvw.MouseUpEvent
		If lvw.HitTest(eventArgs.x, eventArgs.y) Is Nothing Then Exit Sub
		lvw.SelectedItem = lvw.HitTest(eventArgs.x, eventArgs.y)
		lvw.StartLabelEdit()
	End Sub
	
	Private Sub OKCancelBar1_OnCancel(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles OKCancelBar1.OnCancel
		Me.Hide()
	End Sub
	
	Private Sub OKCancelBar1_OnOK(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles OKCancelBar1.OnOK
		Me.Hide()
	End Sub
	
	'UPGRADE_NOTE: Name was upgraded to Name_Renamed. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1061"'
	Public Sub AddItem(ByRef Name_Renamed As String, ByRef TypeStr As String, ByRef Value As String)
		Dim LI As MSComctlLib.ListItem
		LI = lvw.ListItems.Add( , Name_Renamed, Value)
		LI.SubItems(1) = Name_Renamed
		LI.SubItems(2) = TypeStr
	End Sub
	
	Public Sub Clear()
		lvw.ListItems.Clear()
	End Sub
End Class