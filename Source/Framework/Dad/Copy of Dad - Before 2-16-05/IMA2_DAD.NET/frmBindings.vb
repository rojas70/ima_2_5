Option Strict Off
Option Explicit On
Friend Class frmBindings
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
	Public WithEvents ocb As AxIMA2_HelperX.AxOKCancelBar
	Public WithEvents wb As AxIMA2_HelperX.AxWizardBar
	Public WithEvents atv As AxIMA2_HelperX.AxAgentTreeview
	Public WithEvents imSel As System.Windows.Forms.PictureBox
	'NOTE: The following procedure is required by the Windows Form Designer
	'It can be modified using the Windows Form Designer.
	'Do not modify it using the code editor.
	<System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
		Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(frmBindings))
		Me.components = New System.ComponentModel.Container()
		Me.ToolTip1 = New System.Windows.Forms.ToolTip(components)
		Me.ToolTip1.Active = True
		Me.lvw = New AxMSComctlLib.AxListView
		Me.ocb = New AxIMA2_HelperX.AxOKCancelBar
		Me.wb = New AxIMA2_HelperX.AxWizardBar
		Me.atv = New AxIMA2_HelperX.AxAgentTreeview
		Me.imSel = New System.Windows.Forms.PictureBox
		CType(Me.lvw, System.ComponentModel.ISupportInitialize).BeginInit()
		CType(Me.ocb, System.ComponentModel.ISupportInitialize).BeginInit()
		CType(Me.wb, System.ComponentModel.ISupportInitialize).BeginInit()
		CType(Me.atv, System.ComponentModel.ISupportInitialize).BeginInit()
		Me.Text = "Bindings Wizard"
		Me.ClientSize = New System.Drawing.Size(532, 357)
		Me.Location = New System.Drawing.Point(4, 23)
		Me.ControlBox = False
		Me.Icon = CType(resources.GetObject("frmBindings.Icon"), System.Drawing.Icon)
		Me.MaximizeBox = False
		Me.MinimizeBox = False
		Me.StartPosition = System.Windows.Forms.FormStartPosition.WindowsDefaultLocation
		Me.Font = New System.Drawing.Font("Arial", 8!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
		Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
		Me.BackColor = System.Drawing.SystemColors.Control
		Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Sizable
		Me.Enabled = True
		Me.KeyPreview = False
		Me.Cursor = System.Windows.Forms.Cursors.Default
		Me.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.ShowInTaskbar = True
		Me.HelpButton = False
		Me.WindowState = System.Windows.Forms.FormWindowState.Normal
		Me.Name = "frmBindings"
		lvw.OcxState = CType(resources.GetObject("lvw.OcxState"), System.Windows.Forms.AxHost.State)
		Me.lvw.Size = New System.Drawing.Size(449, 161)
		Me.lvw.Location = New System.Drawing.Point(16, 96)
		Me.lvw.TabIndex = 3
		Me.lvw.Visible = False
		Me.lvw.Name = "lvw"
		ocb.OcxState = CType(resources.GetObject("ocb.OcxState"), System.Windows.Forms.AxHost.State)
		Me.ocb.Dock = System.Windows.Forms.DockStyle.Bottom
		Me.ocb.Size = New System.Drawing.Size(532, 46)
		Me.ocb.Location = New System.Drawing.Point(0, 311)
		Me.ocb.TabIndex = 2
		Me.ocb.Name = "ocb"
		wb.OcxState = CType(resources.GetObject("wb.OcxState"), System.Windows.Forms.AxHost.State)
		Me.wb.Dock = System.Windows.Forms.DockStyle.Top
		Me.wb.Size = New System.Drawing.Size(532, 83)
		Me.wb.Location = New System.Drawing.Point(0, 0)
		Me.wb.TabIndex = 1
		Me.wb.Name = "wb"
		atv.OcxState = CType(resources.GetObject("atv.OcxState"), System.Windows.Forms.AxHost.State)
		Me.atv.Size = New System.Drawing.Size(532, 217)
		Me.atv.Location = New System.Drawing.Point(16, 128)
		Me.atv.TabIndex = 0
		Me.atv.Name = "atv"
		Me.imSel.Size = New System.Drawing.Size(16, 16)
		Me.imSel.Location = New System.Drawing.Point(88, 296)
		Me.imSel.Image = CType(resources.GetObject("imSel.Image"), System.Drawing.Image)
		Me.imSel.Enabled = True
		Me.imSel.Cursor = System.Windows.Forms.Cursors.Default
		Me.imSel.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Normal
		Me.imSel.Visible = True
		Me.imSel.BorderStyle = System.Windows.Forms.BorderStyle.None
		Me.imSel.Name = "imSel"
		Me.Controls.Add(lvw)
		Me.Controls.Add(ocb)
		Me.Controls.Add(wb)
		Me.Controls.Add(atv)
		Me.Controls.Add(imSel)
		CType(Me.atv, System.ComponentModel.ISupportInitialize).EndInit()
		CType(Me.wb, System.ComponentModel.ISupportInitialize).EndInit()
		CType(Me.ocb, System.ComponentModel.ISupportInitialize).EndInit()
		CType(Me.lvw, System.ComponentModel.ISupportInitialize).EndInit()
	End Sub
#End Region 
#Region "Upgrade Support "
	Private Shared m_vb6FormDefInstance As frmBindings
	Private Shared m_InitializingDefInstance As Boolean
	Public Shared Property DefInstance() As frmBindings
		Get
			If m_vb6FormDefInstance Is Nothing OrElse m_vb6FormDefInstance.IsDisposed Then
				m_InitializingDefInstance = True
				m_vb6FormDefInstance = New frmBindings()
				m_InitializingDefInstance = False
			End If
			DefInstance = m_vb6FormDefInstance
		End Get
		Set
			m_vb6FormDefInstance = Value
		End Set
	End Property
#End Region 
	
	'**********************************************************************************************************************************
	' Member Variables
	'**********************************************************************************************************************************
	
	Dim m_Icons As New IMA2_Helper.IconManager
	Dim m_Path As String
	'UPGRADE_WARNING: Arrays in structure m_Binding may need to be initialized before they can be used. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1063"'
	Dim m_Binding As IMA2.BindingInfo
	Dim m_Multiple As Boolean
	Dim m_Cancelled As Boolean
	
	Dim m_MouseX As Single
	Dim m_MouseY As Single
	Dim m_Dragging As Boolean
	
	'**********************************************************************************************************************************
	' Public Interface
	'**********************************************************************************************************************************
	
	'UPGRADE_NOTE: ShowDialog was upgraded to ShowDialog_Renamed. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1061"'
	Public Sub ShowDialog_Renamed(ByRef Binding As IMA2.BindingInfo)
		
		Dim LI As MSComctlLib.ListItem
		
		'UPGRADE_WARNING: Couldn't resolve default property of object m_Binding. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
		m_Binding = Binding
		m_Multiple = m_Binding.BindType And IMA2.IMA2_BindingType.BT_Collection
		
		lvw.ListItems.Clear()
		lvw.Visible = m_Multiple
		
		Dim Paths() As String
		Dim I As Short
		If m_Multiple Then
			
			wb.set_Description("Double click on components in the treeview to add them to the bindings list. You can drag items in the list onto each other to change their order. Select an item in the list and push delete to remove it.")
			
			Paths = Split(m_Binding.Path, ",")
			
			For I = 0 To UBound(Paths)
				LI = lvw.ListItems.Add( , Paths(I), Paths(I),  , IMA2_Helper.IMA2_Icons.II_Component)
			Next I
			
		Else
			
			wb.set_Description("Double click a component to bind to.")
			
			'Set LI = lvw.ListItems.Add(, m_Binding.Path, m_Binding.Path, , II_Component)
			'LI.ForeColor = 0
			'LI.SubItems(1) = "" & I
			
		End If
		
		Me.ShowDialog()
		
	End Sub
	
	'**********************************************************************************************************************************
	
	Public ReadOnly Property Binding() As IMA2.BindingInfo
		Get
			'UPGRADE_WARNING: Couldn't resolve default property of object Binding. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
			Binding = m_Binding
		End Get
	End Property
	
	'**********************************************************************************************************************************
	
	Public ReadOnly Property Cancelled() As Boolean
		Get
			Cancelled = m_Cancelled
		End Get
	End Property
	
	'**********************************************************************************************************************************
	
	
	'**********************************************************************************************************************************
	
	Public Property NetList() As IMA2_Helper.NetList
		Get
			NetList = atv.get_NetList()
		End Get
		Set(ByVal Value As IMA2_Helper.NetList)
			atv.set_NetList(Value)
			atv.ExpandAll()
		End Set
	End Property
	
	'**********************************************************************************************************************************
	' Control Events
	'**********************************************************************************************************************************
	
	Private Sub atv_DblClick(ByVal eventSender As System.Object, ByVal eventArgs As AxIMA2_HelperX.__AgentTreeview_DblClickEvent) Handles atv.DblClick
		
		On Error Resume Next
		
		If IMA2_HelperFunctions_definst.PathLevel((eventArgs.Node.Key)) <= 1 Then Exit Sub
		
		If m_Multiple Then
			lvw.ListItems.Add( , atv.get_Path(), atv.get_Path(),  , eventArgs.Node.Image)
			eventArgs.Node.Expanded = True
		Else
			m_Path = atv.get_Path()
			Me.Hide()
		End If
		
	End Sub
	
	'UPGRADE_WARNING: Form event frmBindings.Unload has a new behavior. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup2065"'
	Private Sub frmBindings_Closed(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MyBase.Closed
		
		Call SaveFormPosition(Me)
		
	End Sub
	
	Private Sub lvw_DblClick(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles lvw.DblClick
		
		atv.set_Path(lvw.SelectedItem.Text)
		
	End Sub
	
	'**********************************************************************************************************************************
	
	Private Sub lvw_KeyDownEvent(ByVal eventSender As System.Object, ByVal eventArgs As AxMSComctlLib.ListViewEvents_KeyDownEvent) Handles lvw.KeyDownEvent
		Dim I As Short
		If eventArgs.KeyCode = System.Windows.Forms.Keys.Delete Then
			On Error Resume Next
			I = lvw.SelectedItem.Index
			lvw.ListItems.Remove(lvw.SelectedItem.Index)
			lvw.ListItems(I).Selected = True
			If Err.Number Then lvw.ListItems(I - 1).Selected = True
			Err.Clear()
		End If
	End Sub
	
	'**********************************************************************************************************************************
	
	Private Sub lvw_MouseDownEvent(ByVal eventSender As System.Object, ByVal eventArgs As AxMSComctlLib.ListViewEvents_MouseDownEvent) Handles lvw.MouseDownEvent
		
		m_MouseX = eventArgs.x
		m_MouseY = eventArgs.y
		m_Dragging = True
		
	End Sub
	
	Private Sub lvw_MouseMoveEvent(ByVal eventSender As System.Object, ByVal eventArgs As AxMSComctlLib.ListViewEvents_MouseMoveEvent) Handles lvw.MouseMoveEvent
		
		Dim LI As MSComctlLib.ListItem
		Dim TI As MSComctlLib.ListItem
		
		If m_Dragging Then
			
			TI = lvw.HitTest(eventArgs.x, eventArgs.y)
			If TI Is Nothing Then Exit Sub
			If System.Convert.ToInt32(TI.ForeColor) = QBColor(8) Then Exit Sub
			
			For	Each LI In lvw.ListItems
				LI.ForeColor = System.Convert.ToUInt32(0)
			Next LI
			
			TI.ForeColor = System.Convert.ToUInt32(QBColor(8))
			
		End If
		
		
	End Sub
	
	'**********************************************************************************************************************************
	
	Private Sub lvw_MouseUpEvent(ByVal eventSender As System.Object, ByVal eventArgs As AxMSComctlLib.ListViewEvents_MouseUpEvent) Handles lvw.MouseUpEvent
		
		Dim LI As MSComctlLib.ListItem
		Dim TI As MSComctlLib.ListItem
		Dim TIN As Short
		
		If m_Dragging Then
			m_Dragging = False
			
			TI = lvw.HitTest(eventArgs.x, eventArgs.y)
			If TI Is Nothing Then Exit Sub
			
			TIN = TI.Index
			LI = lvw.SelectedItem
			
			If TIN = LI.Index Then Exit Sub
			
			lvw.ListItems.Remove(LI.Index)
			lvw.ListItems.Add(TIN,  , LI.Text,  , LI.SmallIcon).Selected = True
			
		End If
		
		For	Each LI In lvw.ListItems
			LI.ForeColor = System.Convert.ToUInt32(0)
		Next LI
		
		
	End Sub
	
	'**********************************************************************************************************************************
	
	Private Sub ocb_OnCancel(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles ocb.OnCancel
		m_Cancelled = True
		Me.Hide()
	End Sub
	
	'**********************************************************************************************************************************
	
	Private Sub ocb_OnOK(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles ocb.OnOK
		m_Cancelled = False
		
		Dim Paths As String
		
		Dim LI As MSComctlLib.ListItem
		If m_Multiple Then
			
			For	Each LI In lvw.ListItems
				Paths = Paths & "," & LI.Text
			Next LI
			
			m_Binding.Path = Mid(Paths, 2)
		Else
			m_Binding.Path = atv.get_Path()
		End If
		
		Me.Hide()
	End Sub
	
	
	'**********************************************************************************************************************************
	' Form Events
	'**********************************************************************************************************************************
	
	Private Sub frmBindings_Load(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MyBase.Load
		
		m_Icons.Directory = "C:\Ima2\System\Icons"
		lvw.SmallIcons = m_Icons.ImageList
		Call LoadFormPosition(Me)
		
	End Sub
	
	'**********************************************************************************************************************************
	
	'UPGRADE_WARNING: Event frmBindings.Resize may fire when form is intialized. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup2075"'
	Private Sub frmBindings_Resize(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MyBase.Resize
		Dim W As Single
		Dim H As Single
		
		If m_Multiple Then
			W = Me.ClientRectangle.Width - (atv.Left * 3)
			H = ocb.Top - (wb.Height + atv.Left) - (atv.Left * 2)
			atv.SetBounds(atv.Left, wb.Height + atv.Left, W * 0.4, H)
			lvw.SetBounds((atv.Left * 2) + atv.Width, atv.Top, W * 0.6, H)
			lvw.ColumnHeaders(1).Width = lvw.Width - 6
		Else
			atv.SetBounds(atv.Left, atv.Top, Me.ClientRectangle.Width - atv.Left * 2, ocb.Top - atv.Top - (atv.Left * 2))
		End If
		
	End Sub
	
	'**********************************************************************************************************************************
End Class