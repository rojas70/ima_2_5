Option Strict Off
Option Explicit On
Friend Class frmInsert
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
	Public WithEvents chkContext As System.Windows.Forms.CheckBox
	Public WithEvents bvlTop As AxIMA2_HelperX.AxBevel2
	Public WithEvents icv As AxIMA2_HelperX.AxInsertComponentView
	Public WithEvents _tbv_TabPage0 As System.Windows.Forms.TabPage
	Public WithEvents ifv As AxIMA2_HelperX.AxInsertFileView
	Public WithEvents _tbv_TabPage1 As System.Windows.Forms.TabPage
	Public WithEvents _tbv_TabPage2 As System.Windows.Forms.TabPage
	Public WithEvents tbv As System.Windows.Forms.TabControl
	'NOTE: The following procedure is required by the Windows Form Designer
	'It can be modified using the Windows Form Designer.
	'Do not modify it using the code editor.
	<System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
		Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(frmInsert))
		Me.components = New System.ComponentModel.Container()
		Me.ToolTip1 = New System.Windows.Forms.ToolTip(components)
		Me.ToolTip1.Active = True
		Me.chkContext = New System.Windows.Forms.CheckBox
		Me.bvlTop = New AxIMA2_HelperX.AxBevel2
		Me.tbv = New System.Windows.Forms.TabControl
		Me._tbv_TabPage0 = New System.Windows.Forms.TabPage
		Me.icv = New AxIMA2_HelperX.AxInsertComponentView
		Me._tbv_TabPage1 = New System.Windows.Forms.TabPage
		Me.ifv = New AxIMA2_HelperX.AxInsertFileView
		Me._tbv_TabPage2 = New System.Windows.Forms.TabPage
		CType(Me.bvlTop, System.ComponentModel.ISupportInitialize).BeginInit()
		CType(Me.icv, System.ComponentModel.ISupportInitialize).BeginInit()
		CType(Me.ifv, System.ComponentModel.ISupportInitialize).BeginInit()
		Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
		Me.Text = "Insert IMA2 Component"
		Me.ClientSize = New System.Drawing.Size(424, 257)
		Me.Location = New System.Drawing.Point(185, 251)
		Me.Icon = CType(resources.GetObject("frmInsert.Icon"), System.Drawing.Icon)
		Me.MaximizeBox = False
		Me.MinimizeBox = False
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
		Me.Name = "frmInsert"
		Me.chkContext.Text = "Create component in parent's process."
		Me.chkContext.Size = New System.Drawing.Size(217, 17)
		Me.chkContext.Location = New System.Drawing.Point(8, 240)
		Me.chkContext.TabIndex = 3
		Me.chkContext.CheckState = System.Windows.Forms.CheckState.Checked
		Me.chkContext.Font = New System.Drawing.Font("Arial", 8!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
		Me.chkContext.CheckAlign = System.Drawing.ContentAlignment.MiddleLeft
		Me.chkContext.BackColor = System.Drawing.SystemColors.Control
		Me.chkContext.CausesValidation = True
		Me.chkContext.Enabled = True
		Me.chkContext.ForeColor = System.Drawing.SystemColors.ControlText
		Me.chkContext.Cursor = System.Windows.Forms.Cursors.Default
		Me.chkContext.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.chkContext.Appearance = System.Windows.Forms.Appearance.Normal
		Me.chkContext.TabStop = True
		Me.chkContext.Visible = True
		Me.chkContext.Name = "chkContext"
		bvlTop.OcxState = CType(resources.GetObject("bvlTop.OcxState"), System.Windows.Forms.AxHost.State)
		Me.bvlTop.Dock = System.Windows.Forms.DockStyle.Top
		Me.bvlTop.Size = New System.Drawing.Size(424, 2)
		Me.bvlTop.Location = New System.Drawing.Point(0, 0)
		Me.bvlTop.Name = "bvlTop"
		Me.tbv.Size = New System.Drawing.Size(411, 229)
		Me.tbv.Location = New System.Drawing.Point(6, 8)
		Me.tbv.TabIndex = 0
		Me.tbv.Appearance = System.Windows.Forms.TabAppearance.FlatButtons
		Me.tbv.ItemSize = New System.Drawing.Size(42, 18)
		Me.tbv.Font = New System.Drawing.Font("Arial", 8!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
		Me.tbv.Name = "tbv"
		Me._tbv_TabPage0.Text = "&New"
		icv.OcxState = CType(resources.GetObject("icv.OcxState"), System.Windows.Forms.AxHost.State)
		Me.icv.Size = New System.Drawing.Size(393, 193)
		Me.icv.Location = New System.Drawing.Point(8, 30)
		Me.icv.TabIndex = 1
		Me.icv.Name = "icv"
		Me._tbv_TabPage1.Text = "&Existing"
		ifv.OcxState = CType(resources.GetObject("ifv.OcxState"), System.Windows.Forms.AxHost.State)
		Me.ifv.Size = New System.Drawing.Size(393, 193)
		Me.ifv.Location = New System.Drawing.Point(8, 30)
		Me.ifv.TabIndex = 2
		Me.ifv.Name = "ifv"
		Me._tbv_TabPage2.Text = "&Recent"
		Me.Controls.Add(chkContext)
		Me.Controls.Add(bvlTop)
		Me.Controls.Add(tbv)
		Me.tbv.Controls.Add(_tbv_TabPage0)
		Me.tbv.Controls.Add(_tbv_TabPage1)
		Me.tbv.Controls.Add(_tbv_TabPage2)
		Me._tbv_TabPage0.Controls.Add(icv)
		Me._tbv_TabPage1.Controls.Add(ifv)
		CType(Me.ifv, System.ComponentModel.ISupportInitialize).EndInit()
		CType(Me.icv, System.ComponentModel.ISupportInitialize).EndInit()
		CType(Me.bvlTop, System.ComponentModel.ISupportInitialize).EndInit()
	End Sub
#End Region 
#Region "Upgrade Support "
	Private Shared m_vb6FormDefInstance As frmInsert
	Private Shared m_InitializingDefInstance As Boolean
	Public Shared Property DefInstance() As frmInsert
		Get
			If m_vb6FormDefInstance Is Nothing OrElse m_vb6FormDefInstance.IsDisposed Then
				m_InitializingDefInstance = True
				m_vb6FormDefInstance = New frmInsert()
				m_InitializingDefInstance = False
			End If
			DefInstance = m_vb6FormDefInstance
		End Get
		Set
			m_vb6FormDefInstance = Value
		End Set
	End Property
#End Region 
	
	'****************************************************************************************************************************************
	
	Public Enum InsCmpChoice
		ICD_Cancel = 0
		ICD_New = 1
		ICD_Load = 2
	End Enum
	
	Public Enum InsCmpContext
		ICC_Local = 0
		ICC_Parent = 1
	End Enum
	
	'****************************************************************************************************************************************
	
	Dim m_Choice As frmInsert.InsCmpChoice
	Dim m_ParentPath As String
	
	'****************************************************************************************************************************************
	' Form Events
	'****************************************************************************************************************************************
	
	Private Sub frmInsert_Load(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MyBase.Load
		m_Choice = InsCmpChoice.ICD_Cancel
		ParentPath = "(no parent specified)"
		tbv.SelectedIndex = 0
	End Sub
	
	'****************************************************************************************************************************************
	
	Private Sub frmInsert_KeyDown(ByVal eventSender As System.Object, ByVal eventArgs As System.Windows.Forms.KeyEventArgs) Handles MyBase.KeyDown
		Dim KeyCode As Short = eventArgs.KeyCode
		Dim Shift As Short = eventArgs.KeyData \ &H10000
		If KeyCode = System.Windows.Forms.Keys.Escape Then m_Choice = InsCmpChoice.ICD_Cancel : Me.Hide()
	End Sub
	
	'****************************************************************************************************************************************
	
	'UPGRADE_WARNING: Event frmInsert.Resize may fire when form is intialized. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup2075"'
	Private Sub frmInsert_Resize(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MyBase.Resize
		tbv.Height = Me.ClientRectangle.Height - tbv.Top - 5 - chkContext.Height
		tbv.Width = Me.ClientRectangle.Width - tbv.Left - 5
		
		icv.Width = VB6.TwipsToPixelsX((VB6.TwipsPerPixelX * tbv.Width) - 250)
		icv.Height = VB6.TwipsToPixelsY((VB6.TwipsPerPixelY * tbv.Height) - 570)
		
		ifv.Width = icv.Width
		ifv.Height = icv.Height
		
		chkContext.Top = Me.ClientRectangle.Height - chkContext.Height
		
	End Sub
	
	'****************************************************************************************************************************************
	' Public Properties
	'****************************************************************************************************************************************
	
	Public ReadOnly Property Context() As frmInsert.InsCmpContext
		Get
			Context = chkContext.CheckState
		End Get
	End Property
	
	Public ReadOnly Property Choice() As frmInsert.InsCmpChoice
		Get
			Choice = m_Choice
		End Get
	End Property
	
	'****************************************************************************************************************************************
	
	Public ReadOnly Property LibInfo() As IMA2_Helper.LibInfo
		Get
			If Not m_Choice = InsCmpChoice.ICD_Cancel Then LibInfo = icv.LibInfo
		End Get
	End Property
	
	'****************************************************************************************************************************************
	
	Public ReadOnly Property ClsInfo() As IMA2_Helper.ClsInfo
		Get
			If Not m_Choice = InsCmpChoice.ICD_Cancel Then ClsInfo = icv.ClsInfo
		End Get
	End Property
	
	'****************************************************************************************************************************************
	
	Public ReadOnly Property FilePath() As String
		Get
			If Not m_Choice = InsCmpChoice.ICD_Cancel Then FilePath = ifv.get_FilePath()
		End Get
	End Property
	
	'****************************************************************************************************************************************
	
	Public ReadOnly Property Descriptions() As IMA2_Helper.CmpDesc()
		Get
			If Not m_Choice = InsCmpChoice.ICD_Cancel Then Descriptions = VB6.CopyArray(ifv.Descriptions)
		End Get
	End Property
	
	'****************************************************************************************************************************************
	
	
	'****************************************************************************************************************************************
	
	Public Property ParentPath() As String
		Get
			ParentPath = m_ParentPath
		End Get
		Set(ByVal Value As String)
			m_ParentPath = Value
			ifv.set_ParentPath(Value)
			Me.Text = "Insert Component Into " & Value
		End Set
	End Property
	
	
	'****************************************************************************************************************************************
	'Control Events
	'****************************************************************************************************************************************
	
	Private Sub icv_OnCancel(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles icv.OnCancel
		m_Choice = InsCmpChoice.ICD_Cancel
		Me.Hide()
	End Sub
	
	'****************************************************************************************************************************************
	
	Private Sub icv_OnOK(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles icv.OnOK
		m_Choice = InsCmpChoice.ICD_New
		Me.Hide()
	End Sub
	
	'****************************************************************************************************************************************
	
	Private Sub ifv_OnCancel(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles ifv.OnCancel
		m_Choice = InsCmpChoice.ICD_Cancel
		Me.Hide()
	End Sub
	
	'****************************************************************************************************************************************
	
	Private Sub ifv_OnOK(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles ifv.OnOK
		m_Choice = InsCmpChoice.ICD_Load
		Me.Hide()
	End Sub
End Class