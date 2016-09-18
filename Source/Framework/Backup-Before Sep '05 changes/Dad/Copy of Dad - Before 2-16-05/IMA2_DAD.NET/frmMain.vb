Option Strict Off
Option Explicit On
Imports VB = Microsoft.VisualBasic
Friend Class frmMain
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
	Public WithEvents bvlRight As AxIMA2_HelperX.AxBevel2
	Public WithEvents bvlBottom As AxIMA2_HelperX.AxBevel2
	Public WithEvents bvlLeft As AxIMA2_HelperX.AxBevel2
	Public WithEvents stb As AxMSComctlLib.AxStatusBar
	Public WithEvents Toolbar1 As AxIMA2_HelperX.AxToolbar
	Public WithEvents atv As AxIMA2_HelperX.AxAgentTreeview
	Public WithEvents alv As AxIMA2_HelperX.AxAgentListview
	Public WithEvents slr As AxIMA2_HelperX.AxSplitterLR
	Public WithEvents sud As AxIMA2_HelperX.AxSplitterUD
	Public WithEvents wbv As AxIMA2_HelperX.AxWebView
	Public WithEvents cmv As System.Windows.Forms.Label
	Public WithEvents mnuCmp_New_Favorites As Microsoft.VisualBasic.Compatibility.VB6.MenuItemArray
	Public WithEvents mnuFile_Favorite As Microsoft.VisualBasic.Compatibility.VB6.MenuItemArray
	Public WithEvents mnuFile_New As System.Windows.Forms.MenuItem
	Public WithEvents mnuFile_Open As System.Windows.Forms.MenuItem
	Public WithEvents mnuFile_Sep0 As System.Windows.Forms.MenuItem
	Public WithEvents _mnuFile_Favorite_0 As System.Windows.Forms.MenuItem
	Public WithEvents mnuFile_Sep1 As System.Windows.Forms.MenuItem
	Public WithEvents mnuFile_Exit As System.Windows.Forms.MenuItem
	Public WithEvents mnuFile As System.Windows.Forms.MenuItem
	Public WithEvents mnuCmp_Activated As System.Windows.Forms.MenuItem
	Public WithEvents mnuCmp_Activated_Sep As System.Windows.Forms.MenuItem
	Public WithEvents mnuCmp_ActivateBranch As System.Windows.Forms.MenuItem
	Public WithEvents mnuCmp_DeactivateBranch As System.Windows.Forms.MenuItem
	Public WithEvents mnuCmp_Branch_Sep As System.Windows.Forms.MenuItem
	Public WithEvents mnuCmp_Disconnect As System.Windows.Forms.MenuItem
	Public WithEvents mnuCmp_Connect As System.Windows.Forms.MenuItem
	Public WithEvents mnuCmp_Connect_Sep As System.Windows.Forms.MenuItem
	Public WithEvents mnuCmp_New_Agent As System.Windows.Forms.MenuItem
	Public WithEvents mnuCmp_New_Sep0 As System.Windows.Forms.MenuItem
	Public WithEvents mnuCmp_New_Cmp As System.Windows.Forms.MenuItem
	Public WithEvents mnuCmp_New_Sep1 As System.Windows.Forms.MenuItem
	Public WithEvents _mnuCmp_New_Favorites_0 As System.Windows.Forms.MenuItem
	Public WithEvents mnuCmp_New As System.Windows.Forms.MenuItem
	Public WithEvents mnuCmp_New_Sep As System.Windows.Forms.MenuItem
	Public WithEvents mnuCmp_Copy As System.Windows.Forms.MenuItem
	Public WithEvents mnuCmp_Paste As System.Windows.Forms.MenuItem
	Public WithEvents mnuCmp_Paste_Sep As System.Windows.Forms.MenuItem
	Public WithEvents mnuCmp_Delete As System.Windows.Forms.MenuItem
	Public WithEvents mnuCmp_Delete_Sep As System.Windows.Forms.MenuItem
	Public WithEvents mnuCmp_SaveAs As System.Windows.Forms.MenuItem
	Public WithEvents mnuCmp_SaveAs_Sep As System.Windows.Forms.MenuItem
	Public WithEvents mnuCmp_Properties As System.Windows.Forms.MenuItem
	Public WithEvents mnuCmp As System.Windows.Forms.MenuItem
	Public WithEvents mnuView_Toolbar As System.Windows.Forms.MenuItem
	Public WithEvents mnuView_StatusBar As System.Windows.Forms.MenuItem
	Public WithEvents mnuView_Sep0 As System.Windows.Forms.MenuItem
	Public WithEvents mnuView_Treeview As System.Windows.Forms.MenuItem
	Public WithEvents mnuView_Listview As System.Windows.Forms.MenuItem
	Public WithEvents mnuView_WebView As System.Windows.Forms.MenuItem
	Public WithEvents mnuView_Sep_9 As System.Windows.Forms.MenuItem
	Public WithEvents mnuView_HideAll As System.Windows.Forms.MenuItem
	Public WithEvents mnuView_ShowAll As System.Windows.Forms.MenuItem
	Public WithEvents mnuView_Views As System.Windows.Forms.MenuItem
	Public WithEvents mnuView_Sep_8 As System.Windows.Forms.MenuItem
	Public WithEvents mnuView_List As System.Windows.Forms.MenuItem
	Public WithEvents mnuView_Details As System.Windows.Forms.MenuItem
	Public WithEvents mnuViewSep2 As System.Windows.Forms.MenuItem
	Public WithEvents mnuView_Object_Properties As System.Windows.Forms.MenuItem
	Public WithEvents mnuView_Object_Methods As System.Windows.Forms.MenuItem
	Public WithEvents mnuView_Object_Bindings As System.Windows.Forms.MenuItem
	Public WithEvents mnuView_Object As System.Windows.Forms.MenuItem
	Public WithEvents mnuView_Sep1 As System.Windows.Forms.MenuItem
	Public WithEvents mnuView_Refresh As System.Windows.Forms.MenuItem
	Public WithEvents mnuView As System.Windows.Forms.MenuItem
	Public WithEvents mnuTools_Options As System.Windows.Forms.MenuItem
	Public WithEvents muTools As System.Windows.Forms.MenuItem
	Public MainMenu1 As System.Windows.Forms.MainMenu
	'NOTE: The following procedure is required by the Windows Form Designer
	'It can be modified using the Windows Form Designer.
	'Do not modify it using the code editor.
	<System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
		Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(frmMain))
		Me.components = New System.ComponentModel.Container()
		Me.ToolTip1 = New System.Windows.Forms.ToolTip(components)
		Me.ToolTip1.Active = True
		Me.bvlRight = New AxIMA2_HelperX.AxBevel2
		Me.bvlBottom = New AxIMA2_HelperX.AxBevel2
		Me.bvlLeft = New AxIMA2_HelperX.AxBevel2
		Me.stb = New AxMSComctlLib.AxStatusBar
		Me.Toolbar1 = New AxIMA2_HelperX.AxToolbar
		Me.atv = New AxIMA2_HelperX.AxAgentTreeview
		Me.alv = New AxIMA2_HelperX.AxAgentListview
		Me.slr = New AxIMA2_HelperX.AxSplitterLR
		Me.sud = New AxIMA2_HelperX.AxSplitterUD
		Me.wbv = New AxIMA2_HelperX.AxWebView
		Me.cmv = New System.Windows.Forms.Label
		Me.mnuCmp_New_Favorites = New Microsoft.VisualBasic.Compatibility.VB6.MenuItemArray(components)
		Me.mnuFile_Favorite = New Microsoft.VisualBasic.Compatibility.VB6.MenuItemArray(components)
		Me.MainMenu1 = New System.Windows.Forms.MainMenu
		Me.mnuFile = New System.Windows.Forms.MenuItem
		Me.mnuFile_New = New System.Windows.Forms.MenuItem
		Me.mnuFile_Open = New System.Windows.Forms.MenuItem
		Me.mnuFile_Sep0 = New System.Windows.Forms.MenuItem
		Me._mnuFile_Favorite_0 = New System.Windows.Forms.MenuItem
		Me.mnuFile_Sep1 = New System.Windows.Forms.MenuItem
		Me.mnuFile_Exit = New System.Windows.Forms.MenuItem
		Me.mnuCmp = New System.Windows.Forms.MenuItem
		Me.mnuCmp_Activated = New System.Windows.Forms.MenuItem
		Me.mnuCmp_Activated_Sep = New System.Windows.Forms.MenuItem
		Me.mnuCmp_ActivateBranch = New System.Windows.Forms.MenuItem
		Me.mnuCmp_DeactivateBranch = New System.Windows.Forms.MenuItem
		Me.mnuCmp_Branch_Sep = New System.Windows.Forms.MenuItem
		Me.mnuCmp_Disconnect = New System.Windows.Forms.MenuItem
		Me.mnuCmp_Connect = New System.Windows.Forms.MenuItem
		Me.mnuCmp_Connect_Sep = New System.Windows.Forms.MenuItem
		Me.mnuCmp_New = New System.Windows.Forms.MenuItem
		Me.mnuCmp_New_Agent = New System.Windows.Forms.MenuItem
		Me.mnuCmp_New_Sep0 = New System.Windows.Forms.MenuItem
		Me.mnuCmp_New_Cmp = New System.Windows.Forms.MenuItem
		Me.mnuCmp_New_Sep1 = New System.Windows.Forms.MenuItem
		Me._mnuCmp_New_Favorites_0 = New System.Windows.Forms.MenuItem
		Me.mnuCmp_New_Sep = New System.Windows.Forms.MenuItem
		Me.mnuCmp_Copy = New System.Windows.Forms.MenuItem
		Me.mnuCmp_Paste = New System.Windows.Forms.MenuItem
		Me.mnuCmp_Paste_Sep = New System.Windows.Forms.MenuItem
		Me.mnuCmp_Delete = New System.Windows.Forms.MenuItem
		Me.mnuCmp_Delete_Sep = New System.Windows.Forms.MenuItem
		Me.mnuCmp_SaveAs = New System.Windows.Forms.MenuItem
		Me.mnuCmp_SaveAs_Sep = New System.Windows.Forms.MenuItem
		Me.mnuCmp_Properties = New System.Windows.Forms.MenuItem
		Me.mnuView = New System.Windows.Forms.MenuItem
		Me.mnuView_Toolbar = New System.Windows.Forms.MenuItem
		Me.mnuView_StatusBar = New System.Windows.Forms.MenuItem
		Me.mnuView_Sep0 = New System.Windows.Forms.MenuItem
		Me.mnuView_Views = New System.Windows.Forms.MenuItem
		Me.mnuView_Treeview = New System.Windows.Forms.MenuItem
		Me.mnuView_Listview = New System.Windows.Forms.MenuItem
		Me.mnuView_WebView = New System.Windows.Forms.MenuItem
		Me.mnuView_Sep_9 = New System.Windows.Forms.MenuItem
		Me.mnuView_HideAll = New System.Windows.Forms.MenuItem
		Me.mnuView_ShowAll = New System.Windows.Forms.MenuItem
		Me.mnuView_Sep_8 = New System.Windows.Forms.MenuItem
		Me.mnuView_List = New System.Windows.Forms.MenuItem
		Me.mnuView_Details = New System.Windows.Forms.MenuItem
		Me.mnuViewSep2 = New System.Windows.Forms.MenuItem
		Me.mnuView_Object = New System.Windows.Forms.MenuItem
		Me.mnuView_Object_Properties = New System.Windows.Forms.MenuItem
		Me.mnuView_Object_Methods = New System.Windows.Forms.MenuItem
		Me.mnuView_Object_Bindings = New System.Windows.Forms.MenuItem
		Me.mnuView_Sep1 = New System.Windows.Forms.MenuItem
		Me.mnuView_Refresh = New System.Windows.Forms.MenuItem
		Me.muTools = New System.Windows.Forms.MenuItem
		Me.mnuTools_Options = New System.Windows.Forms.MenuItem
		CType(Me.bvlRight, System.ComponentModel.ISupportInitialize).BeginInit()
		CType(Me.bvlBottom, System.ComponentModel.ISupportInitialize).BeginInit()
		CType(Me.bvlLeft, System.ComponentModel.ISupportInitialize).BeginInit()
		CType(Me.stb, System.ComponentModel.ISupportInitialize).BeginInit()
		CType(Me.Toolbar1, System.ComponentModel.ISupportInitialize).BeginInit()
		CType(Me.atv, System.ComponentModel.ISupportInitialize).BeginInit()
		CType(Me.alv, System.ComponentModel.ISupportInitialize).BeginInit()
		CType(Me.slr, System.ComponentModel.ISupportInitialize).BeginInit()
		CType(Me.sud, System.ComponentModel.ISupportInitialize).BeginInit()
		CType(Me.wbv, System.ComponentModel.ISupportInitialize).BeginInit()
		CType(Me.mnuCmp_New_Favorites, System.ComponentModel.ISupportInitialize).BeginInit()
		CType(Me.mnuFile_Favorite, System.ComponentModel.ISupportInitialize).BeginInit()
		Me.BackColor = System.Drawing.SystemColors.Window
		Me.Text = "Distributed Agent Designer 1.0"
		Me.ClientSize = New System.Drawing.Size(644, 338)
		Me.Location = New System.Drawing.Point(11, 49)
		Me.Icon = CType(resources.GetObject("frmMain.Icon"), System.Drawing.Icon)
		Me.StartPosition = System.Windows.Forms.FormStartPosition.WindowsDefaultLocation
		Me.Font = New System.Drawing.Font("Arial", 8!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
		Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
		Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Sizable
		Me.ControlBox = True
		Me.Enabled = True
		Me.KeyPreview = False
		Me.MaximizeBox = True
		Me.MinimizeBox = True
		Me.Cursor = System.Windows.Forms.Cursors.Default
		Me.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.ShowInTaskbar = True
		Me.HelpButton = False
		Me.WindowState = System.Windows.Forms.FormWindowState.Normal
		Me.Name = "frmMain"
		bvlRight.OcxState = CType(resources.GetObject("bvlRight.OcxState"), System.Windows.Forms.AxHost.State)
		Me.bvlRight.Dock = System.Windows.Forms.DockStyle.Right
		Me.bvlRight.Size = New System.Drawing.Size(2, 294)
		Me.bvlRight.Location = New System.Drawing.Point(642, 25)
		Me.bvlRight.Name = "bvlRight"
		bvlBottom.OcxState = CType(resources.GetObject("bvlBottom.OcxState"), System.Windows.Forms.AxHost.State)
		Me.bvlBottom.Dock = System.Windows.Forms.DockStyle.Bottom
		Me.bvlBottom.Size = New System.Drawing.Size(644, 2)
		Me.bvlBottom.Location = New System.Drawing.Point(0, 319)
		Me.bvlBottom.Name = "bvlBottom"
		bvlLeft.OcxState = CType(resources.GetObject("bvlLeft.OcxState"), System.Windows.Forms.AxHost.State)
		Me.bvlLeft.Dock = System.Windows.Forms.DockStyle.Left
		Me.bvlLeft.Size = New System.Drawing.Size(2, 294)
		Me.bvlLeft.Location = New System.Drawing.Point(0, 25)
		Me.bvlLeft.Name = "bvlLeft"
		stb.OcxState = CType(resources.GetObject("stb.OcxState"), System.Windows.Forms.AxHost.State)
		Me.stb.Dock = System.Windows.Forms.DockStyle.Bottom
		Me.stb.Size = New System.Drawing.Size(644, 17)
		Me.stb.Location = New System.Drawing.Point(0, 321)
		Me.stb.TabIndex = 0
		Me.stb.Name = "stb"
		Toolbar1.OcxState = CType(resources.GetObject("Toolbar1.OcxState"), System.Windows.Forms.AxHost.State)
		Me.Toolbar1.Dock = System.Windows.Forms.DockStyle.Top
		Me.Toolbar1.Size = New System.Drawing.Size(644, 25)
		Me.Toolbar1.Location = New System.Drawing.Point(0, 0)
		Me.Toolbar1.TabIndex = 1
		Me.Toolbar1.Name = "Toolbar1"
		atv.OcxState = CType(resources.GetObject("atv.OcxState"), System.Windows.Forms.AxHost.State)
		Me.atv.Size = New System.Drawing.Size(169, 250)
		Me.atv.Location = New System.Drawing.Point(0, 64)
		Me.atv.TabIndex = 4
		Me.atv.set_BorderStyle(0)
		Me.atv.Name = "atv"
		alv.OcxState = CType(resources.GetObject("alv.OcxState"), System.Windows.Forms.AxHost.State)
		Me.alv.Size = New System.Drawing.Size(464, 189)
		Me.alv.Location = New System.Drawing.Point(176, 64)
		Me.alv.TabIndex = 2
		Me.alv.Name = "alv"
		slr.OcxState = CType(resources.GetObject("slr.OcxState"), System.Windows.Forms.AxHost.State)
		Me.slr.Size = New System.Drawing.Size(5, 250)
		Me.slr.Location = New System.Drawing.Point(169, 64)
		Me.slr.TabIndex = 6
		Me.slr.Name = "slr"
		sud.OcxState = CType(resources.GetObject("sud.OcxState"), System.Windows.Forms.AxHost.State)
		Me.sud.Size = New System.Drawing.Size(6450, 5)
		Me.sud.Location = New System.Drawing.Point(0, 60)
		Me.sud.TabIndex = 3
		Me.sud.Name = "sud"
		wbv.OcxState = CType(resources.GetObject("wbv.OcxState"), System.Windows.Forms.AxHost.State)
		Me.wbv.Size = New System.Drawing.Size(677, 29)
		Me.wbv.Location = New System.Drawing.Point(0, 24)
		Me.wbv.TabIndex = 5
		Me.wbv.Name = "wbv"
		Me.cmv.BackColor = System.Drawing.Color.Red
		Me.cmv.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
		Me.cmv.ForeColor = System.Drawing.Color.Black
		Me.cmv.Text = "cmv"
		Me.cmv.Size = New System.Drawing.Size(465, 62)
		Me.cmv.Location = New System.Drawing.Point(176, 256)
		Me.cmv.Name = "cmv"
		Me.mnuFile.Text = "&File"
		Me.mnuFile.Checked = False
		Me.mnuFile.Enabled = True
		Me.mnuFile.Visible = True
		Me.mnuFile.MDIList = False
		Me.mnuFile_New.Text = "&New File..."
		Me.mnuFile_New.Checked = False
		Me.mnuFile_New.Enabled = True
		Me.mnuFile_New.Visible = True
		Me.mnuFile_New.MDIList = False
		Me.mnuFile_Open.Text = "&Open File..."
		Me.mnuFile_Open.Checked = False
		Me.mnuFile_Open.Enabled = True
		Me.mnuFile_Open.Visible = True
		Me.mnuFile_Open.MDIList = False
		Me.mnuFile_Sep0.Text = "-"
		Me.mnuFile_Sep0.Checked = False
		Me.mnuFile_Sep0.Enabled = True
		Me.mnuFile_Sep0.Visible = True
		Me.mnuFile_Sep0.MDIList = False
		Me._mnuFile_Favorite_0.Text = "<favorite1>"
		Me._mnuFile_Favorite_0.Enabled = False
		Me._mnuFile_Favorite_0.Checked = False
		Me._mnuFile_Favorite_0.Visible = True
		Me._mnuFile_Favorite_0.MDIList = False
		Me.mnuFile_Sep1.Text = "-"
		Me.mnuFile_Sep1.Checked = False
		Me.mnuFile_Sep1.Enabled = True
		Me.mnuFile_Sep1.Visible = True
		Me.mnuFile_Sep1.MDIList = False
		Me.mnuFile_Exit.Text = "&Exit"
		Me.mnuFile_Exit.Checked = False
		Me.mnuFile_Exit.Enabled = True
		Me.mnuFile_Exit.Visible = True
		Me.mnuFile_Exit.MDIList = False
		Me.mnuCmp.Text = "&Component"
		Me.mnuCmp.Visible = False
		Me.mnuCmp.Checked = False
		Me.mnuCmp.Enabled = True
		Me.mnuCmp.MDIList = False
		Me.mnuCmp_Activated.Text = "&Activated"
		Me.mnuCmp_Activated.Checked = True
		Me.mnuCmp_Activated.Shortcut = System.Windows.Forms.Shortcut.CtrlA
		Me.mnuCmp_Activated.Enabled = True
		Me.mnuCmp_Activated.Visible = True
		Me.mnuCmp_Activated.MDIList = False
		Me.mnuCmp_Activated_Sep.Text = "-"
		Me.mnuCmp_Activated_Sep.Checked = False
		Me.mnuCmp_Activated_Sep.Enabled = True
		Me.mnuCmp_Activated_Sep.Visible = True
		Me.mnuCmp_Activated_Sep.MDIList = False
		Me.mnuCmp_ActivateBranch.Text = "Activate &Branch"
		Me.mnuCmp_ActivateBranch.Shortcut = System.Windows.Forms.Shortcut.CtrlB
		Me.mnuCmp_ActivateBranch.Checked = False
		Me.mnuCmp_ActivateBranch.Enabled = True
		Me.mnuCmp_ActivateBranch.Visible = True
		Me.mnuCmp_ActivateBranch.MDIList = False
		Me.mnuCmp_DeactivateBranch.Text = "&Deactivate Branch"
		Me.mnuCmp_DeactivateBranch.Shortcut = System.Windows.Forms.Shortcut.CtrlD
		Me.mnuCmp_DeactivateBranch.Checked = False
		Me.mnuCmp_DeactivateBranch.Enabled = True
		Me.mnuCmp_DeactivateBranch.Visible = True
		Me.mnuCmp_DeactivateBranch.MDIList = False
		Me.mnuCmp_Branch_Sep.Text = "-"
		Me.mnuCmp_Branch_Sep.Checked = False
		Me.mnuCmp_Branch_Sep.Enabled = True
		Me.mnuCmp_Branch_Sep.Visible = True
		Me.mnuCmp_Branch_Sep.MDIList = False
		Me.mnuCmp_Disconnect.Text = "&Disconnect"
		Me.mnuCmp_Disconnect.Checked = False
		Me.mnuCmp_Disconnect.Enabled = True
		Me.mnuCmp_Disconnect.Visible = True
		Me.mnuCmp_Disconnect.MDIList = False
		Me.mnuCmp_Connect.Text = "Connect &Locator..."
		Me.mnuCmp_Connect.Shortcut = System.Windows.Forms.Shortcut.CtrlL
		Me.mnuCmp_Connect.Visible = False
		Me.mnuCmp_Connect.Checked = False
		Me.mnuCmp_Connect.Enabled = True
		Me.mnuCmp_Connect.MDIList = False
		Me.mnuCmp_Connect_Sep.Text = "-"
		Me.mnuCmp_Connect_Sep.Checked = False
		Me.mnuCmp_Connect_Sep.Enabled = True
		Me.mnuCmp_Connect_Sep.Visible = True
		Me.mnuCmp_Connect_Sep.MDIList = False
		Me.mnuCmp_New.Text = "New"
		Me.mnuCmp_New.Checked = False
		Me.mnuCmp_New.Enabled = True
		Me.mnuCmp_New.Visible = True
		Me.mnuCmp_New.MDIList = False
		Me.mnuCmp_New_Agent.Text = "&Agent"
		Me.mnuCmp_New_Agent.Shortcut = System.Windows.Forms.Shortcut.CtrlG
		Me.mnuCmp_New_Agent.Checked = False
		Me.mnuCmp_New_Agent.Enabled = True
		Me.mnuCmp_New_Agent.Visible = True
		Me.mnuCmp_New_Agent.MDIList = False
		Me.mnuCmp_New_Sep0.Text = "-"
		Me.mnuCmp_New_Sep0.Checked = False
		Me.mnuCmp_New_Sep0.Enabled = True
		Me.mnuCmp_New_Sep0.Visible = True
		Me.mnuCmp_New_Sep0.MDIList = False
		Me.mnuCmp_New_Cmp.Text = "&Component..."
		Me.mnuCmp_New_Cmp.Shortcut = System.Windows.Forms.Shortcut.CtrlN
		Me.mnuCmp_New_Cmp.Checked = False
		Me.mnuCmp_New_Cmp.Enabled = True
		Me.mnuCmp_New_Cmp.Visible = True
		Me.mnuCmp_New_Cmp.MDIList = False
		Me.mnuCmp_New_Sep1.Text = "-"
		Me.mnuCmp_New_Sep1.Checked = False
		Me.mnuCmp_New_Sep1.Enabled = True
		Me.mnuCmp_New_Sep1.Visible = True
		Me.mnuCmp_New_Sep1.MDIList = False
		Me._mnuCmp_New_Favorites_0.Text = "<Favorite1>"
		Me._mnuCmp_New_Favorites_0.Checked = False
		Me._mnuCmp_New_Favorites_0.Enabled = True
		Me._mnuCmp_New_Favorites_0.Visible = True
		Me._mnuCmp_New_Favorites_0.MDIList = False
		Me.mnuCmp_New_Sep.Text = "-"
		Me.mnuCmp_New_Sep.Checked = False
		Me.mnuCmp_New_Sep.Enabled = True
		Me.mnuCmp_New_Sep.Visible = True
		Me.mnuCmp_New_Sep.MDIList = False
		Me.mnuCmp_Copy.Text = "&Copy"
		Me.mnuCmp_Copy.Shortcut = System.Windows.Forms.Shortcut.CtrlC
		Me.mnuCmp_Copy.Checked = False
		Me.mnuCmp_Copy.Enabled = True
		Me.mnuCmp_Copy.Visible = True
		Me.mnuCmp_Copy.MDIList = False
		Me.mnuCmp_Paste.Text = "&Paste"
		Me.mnuCmp_Paste.Shortcut = System.Windows.Forms.Shortcut.ShiftIns
		Me.mnuCmp_Paste.Checked = False
		Me.mnuCmp_Paste.Enabled = True
		Me.mnuCmp_Paste.Visible = True
		Me.mnuCmp_Paste.MDIList = False
		Me.mnuCmp_Paste_Sep.Text = "-"
		Me.mnuCmp_Paste_Sep.Checked = False
		Me.mnuCmp_Paste_Sep.Enabled = True
		Me.mnuCmp_Paste_Sep.Visible = True
		Me.mnuCmp_Paste_Sep.MDIList = False
		Me.mnuCmp_Delete.Text = "Delete"
		Me.mnuCmp_Delete.Shortcut = System.Windows.Forms.Shortcut.Del
		Me.mnuCmp_Delete.Checked = False
		Me.mnuCmp_Delete.Enabled = True
		Me.mnuCmp_Delete.Visible = True
		Me.mnuCmp_Delete.MDIList = False
		Me.mnuCmp_Delete_Sep.Text = "-"
		Me.mnuCmp_Delete_Sep.Checked = False
		Me.mnuCmp_Delete_Sep.Enabled = True
		Me.mnuCmp_Delete_Sep.Visible = True
		Me.mnuCmp_Delete_Sep.MDIList = False
		Me.mnuCmp_SaveAs.Text = "&Save As..."
		Me.mnuCmp_SaveAs.Shortcut = System.Windows.Forms.Shortcut.CtrlS
		Me.mnuCmp_SaveAs.Checked = False
		Me.mnuCmp_SaveAs.Enabled = True
		Me.mnuCmp_SaveAs.Visible = True
		Me.mnuCmp_SaveAs.MDIList = False
		Me.mnuCmp_SaveAs_Sep.Text = "-"
		Me.mnuCmp_SaveAs_Sep.Checked = False
		Me.mnuCmp_SaveAs_Sep.Enabled = True
		Me.mnuCmp_SaveAs_Sep.Visible = True
		Me.mnuCmp_SaveAs_Sep.MDIList = False
		Me.mnuCmp_Properties.Text = "P&roperties"
		Me.mnuCmp_Properties.Shortcut = System.Windows.Forms.Shortcut.F4
		Me.mnuCmp_Properties.Checked = False
		Me.mnuCmp_Properties.Enabled = True
		Me.mnuCmp_Properties.Visible = True
		Me.mnuCmp_Properties.MDIList = False
		Me.mnuView.Text = "&View"
		Me.mnuView.Checked = False
		Me.mnuView.Enabled = True
		Me.mnuView.Visible = True
		Me.mnuView.MDIList = False
		Me.mnuView_Toolbar.Text = "&Toolbar"
		Me.mnuView_Toolbar.Checked = True
		Me.mnuView_Toolbar.Enabled = True
		Me.mnuView_Toolbar.Visible = True
		Me.mnuView_Toolbar.MDIList = False
		Me.mnuView_StatusBar.Text = "&Status Bar"
		Me.mnuView_StatusBar.Checked = True
		Me.mnuView_StatusBar.Enabled = True
		Me.mnuView_StatusBar.Visible = True
		Me.mnuView_StatusBar.MDIList = False
		Me.mnuView_Sep0.Text = "-"
		Me.mnuView_Sep0.Checked = False
		Me.mnuView_Sep0.Enabled = True
		Me.mnuView_Sep0.Visible = True
		Me.mnuView_Sep0.MDIList = False
		Me.mnuView_Views.Text = "Views"
		Me.mnuView_Views.Checked = False
		Me.mnuView_Views.Enabled = True
		Me.mnuView_Views.Visible = True
		Me.mnuView_Views.MDIList = False
		Me.mnuView_Treeview.Text = "Tr&ee View"
		Me.mnuView_Treeview.Checked = True
		Me.mnuView_Treeview.Enabled = True
		Me.mnuView_Treeview.Visible = True
		Me.mnuView_Treeview.MDIList = False
		Me.mnuView_Listview.Text = "L&ist View"
		Me.mnuView_Listview.Checked = True
		Me.mnuView_Listview.Enabled = True
		Me.mnuView_Listview.Visible = True
		Me.mnuView_Listview.MDIList = False
		Me.mnuView_WebView.Text = "&Web View"
		Me.mnuView_WebView.Checked = True
		Me.mnuView_WebView.Enabled = True
		Me.mnuView_WebView.Visible = True
		Me.mnuView_WebView.MDIList = False
		Me.mnuView_Sep_9.Text = "-"
		Me.mnuView_Sep_9.Checked = False
		Me.mnuView_Sep_9.Enabled = True
		Me.mnuView_Sep_9.Visible = True
		Me.mnuView_Sep_9.MDIList = False
		Me.mnuView_HideAll.Text = "&Hide All"
		Me.mnuView_HideAll.Checked = False
		Me.mnuView_HideAll.Enabled = True
		Me.mnuView_HideAll.Visible = True
		Me.mnuView_HideAll.MDIList = False
		Me.mnuView_ShowAll.Text = "&Show All"
		Me.mnuView_ShowAll.Checked = False
		Me.mnuView_ShowAll.Enabled = True
		Me.mnuView_ShowAll.Visible = True
		Me.mnuView_ShowAll.MDIList = False
		Me.mnuView_Sep_8.Text = "-"
		Me.mnuView_Sep_8.Checked = False
		Me.mnuView_Sep_8.Enabled = True
		Me.mnuView_Sep_8.Visible = True
		Me.mnuView_Sep_8.MDIList = False
		Me.mnuView_List.Text = "&List"
		Me.mnuView_List.Checked = True
		Me.mnuView_List.Enabled = True
		Me.mnuView_List.Visible = True
		Me.mnuView_List.MDIList = False
		Me.mnuView_Details.Text = "&Details"
		Me.mnuView_Details.Checked = False
		Me.mnuView_Details.Enabled = True
		Me.mnuView_Details.Visible = True
		Me.mnuView_Details.MDIList = False
		Me.mnuViewSep2.Text = "-"
		Me.mnuViewSep2.Checked = False
		Me.mnuViewSep2.Enabled = True
		Me.mnuViewSep2.Visible = True
		Me.mnuViewSep2.MDIList = False
		Me.mnuView_Object.Text = "&Object"
		Me.mnuView_Object.Checked = False
		Me.mnuView_Object.Enabled = True
		Me.mnuView_Object.Visible = True
		Me.mnuView_Object.MDIList = False
		Me.mnuView_Object_Properties.Text = "&Properties"
		Me.mnuView_Object_Properties.Checked = True
		Me.mnuView_Object_Properties.Enabled = True
		Me.mnuView_Object_Properties.Visible = True
		Me.mnuView_Object_Properties.MDIList = False
		Me.mnuView_Object_Methods.Text = "&Methods"
		Me.mnuView_Object_Methods.Checked = True
		Me.mnuView_Object_Methods.Enabled = True
		Me.mnuView_Object_Methods.Visible = True
		Me.mnuView_Object_Methods.MDIList = False
		Me.mnuView_Object_Bindings.Text = "&Bindings"
		Me.mnuView_Object_Bindings.Checked = True
		Me.mnuView_Object_Bindings.Enabled = True
		Me.mnuView_Object_Bindings.Visible = True
		Me.mnuView_Object_Bindings.MDIList = False
		Me.mnuView_Sep1.Text = "-"
		Me.mnuView_Sep1.Checked = False
		Me.mnuView_Sep1.Enabled = True
		Me.mnuView_Sep1.Visible = True
		Me.mnuView_Sep1.MDIList = False
		Me.mnuView_Refresh.Text = "&Refresh"
		Me.mnuView_Refresh.Shortcut = System.Windows.Forms.Shortcut.F5
		Me.mnuView_Refresh.Checked = False
		Me.mnuView_Refresh.Enabled = True
		Me.mnuView_Refresh.Visible = True
		Me.mnuView_Refresh.MDIList = False
		Me.muTools.Text = "&Tools"
		Me.muTools.Checked = False
		Me.muTools.Enabled = True
		Me.muTools.Visible = True
		Me.muTools.MDIList = False
		Me.mnuTools_Options.Text = "&Options..."
		Me.mnuTools_Options.Checked = False
		Me.mnuTools_Options.Enabled = True
		Me.mnuTools_Options.Visible = True
		Me.mnuTools_Options.MDIList = False
		Me.Controls.Add(bvlRight)
		Me.Controls.Add(bvlBottom)
		Me.Controls.Add(bvlLeft)
		Me.Controls.Add(stb)
		Me.Controls.Add(Toolbar1)
		Me.Controls.Add(atv)
		Me.Controls.Add(alv)
		Me.Controls.Add(slr)
		Me.Controls.Add(sud)
		Me.Controls.Add(wbv)
		Me.Controls.Add(cmv)
		Me.mnuCmp_New_Favorites.SetIndex(_mnuCmp_New_Favorites_0, CType(0, Short))
		Me.mnuFile_Favorite.SetIndex(_mnuFile_Favorite_0, CType(0, Short))
		CType(Me.mnuFile_Favorite, System.ComponentModel.ISupportInitialize).EndInit()
		CType(Me.mnuCmp_New_Favorites, System.ComponentModel.ISupportInitialize).EndInit()
		CType(Me.wbv, System.ComponentModel.ISupportInitialize).EndInit()
		CType(Me.sud, System.ComponentModel.ISupportInitialize).EndInit()
		CType(Me.slr, System.ComponentModel.ISupportInitialize).EndInit()
		CType(Me.alv, System.ComponentModel.ISupportInitialize).EndInit()
		CType(Me.atv, System.ComponentModel.ISupportInitialize).EndInit()
		CType(Me.Toolbar1, System.ComponentModel.ISupportInitialize).EndInit()
		CType(Me.stb, System.ComponentModel.ISupportInitialize).EndInit()
		CType(Me.bvlLeft, System.ComponentModel.ISupportInitialize).EndInit()
		CType(Me.bvlBottom, System.ComponentModel.ISupportInitialize).EndInit()
		CType(Me.bvlRight, System.ComponentModel.ISupportInitialize).EndInit()
		Me.mnuFile.Index = 0
		Me.mnuCmp.Index = 1
		Me.mnuView.Index = 2
		Me.muTools.Index = 3
		MainMenu1.MenuItems.AddRange(New System.Windows.Forms.MenuItem(){Me.mnuFile, Me.mnuCmp, Me.mnuView, Me.muTools})
		Me.mnuFile_New.Index = 0
		Me.mnuFile_Open.Index = 1
		Me.mnuFile_Sep0.Index = 2
		Me._mnuFile_Favorite_0.Index = 3
		Me.mnuFile_Sep1.Index = 4
		Me.mnuFile_Exit.Index = 5
		mnuFile.MenuItems.AddRange(New System.Windows.Forms.MenuItem(){Me.mnuFile_New, Me.mnuFile_Open, Me.mnuFile_Sep0, Me._mnuFile_Favorite_0, Me.mnuFile_Sep1, Me.mnuFile_Exit})
		Me.mnuCmp_Activated.Index = 0
		Me.mnuCmp_Activated_Sep.Index = 1
		Me.mnuCmp_ActivateBranch.Index = 2
		Me.mnuCmp_DeactivateBranch.Index = 3
		Me.mnuCmp_Branch_Sep.Index = 4
		Me.mnuCmp_Disconnect.Index = 5
		Me.mnuCmp_Connect.Index = 6
		Me.mnuCmp_Connect_Sep.Index = 7
		Me.mnuCmp_New.Index = 8
		Me.mnuCmp_New_Sep.Index = 9
		Me.mnuCmp_Copy.Index = 10
		Me.mnuCmp_Paste.Index = 11
		Me.mnuCmp_Paste_Sep.Index = 12
		Me.mnuCmp_Delete.Index = 13
		Me.mnuCmp_Delete_Sep.Index = 14
		Me.mnuCmp_SaveAs.Index = 15
		Me.mnuCmp_SaveAs_Sep.Index = 16
		Me.mnuCmp_Properties.Index = 17
		mnuCmp.MenuItems.AddRange(New System.Windows.Forms.MenuItem(){Me.mnuCmp_Activated, Me.mnuCmp_Activated_Sep, Me.mnuCmp_ActivateBranch, Me.mnuCmp_DeactivateBranch, Me.mnuCmp_Branch_Sep, Me.mnuCmp_Disconnect, Me.mnuCmp_Connect, Me.mnuCmp_Connect_Sep, Me.mnuCmp_New, Me.mnuCmp_New_Sep, Me.mnuCmp_Copy, Me.mnuCmp_Paste, Me.mnuCmp_Paste_Sep, Me.mnuCmp_Delete, Me.mnuCmp_Delete_Sep, Me.mnuCmp_SaveAs, Me.mnuCmp_SaveAs_Sep, Me.mnuCmp_Properties})
		Me.mnuCmp_New_Agent.Index = 0
		Me.mnuCmp_New_Sep0.Index = 1
		Me.mnuCmp_New_Cmp.Index = 2
		Me.mnuCmp_New_Sep1.Index = 3
		Me._mnuCmp_New_Favorites_0.Index = 4
		mnuCmp_New.MenuItems.AddRange(New System.Windows.Forms.MenuItem(){Me.mnuCmp_New_Agent, Me.mnuCmp_New_Sep0, Me.mnuCmp_New_Cmp, Me.mnuCmp_New_Sep1, Me._mnuCmp_New_Favorites_0})
		Me.mnuView_Toolbar.Index = 0
		Me.mnuView_StatusBar.Index = 1
		Me.mnuView_Sep0.Index = 2
		Me.mnuView_Views.Index = 3
		Me.mnuView_Sep_8.Index = 4
		Me.mnuView_List.Index = 5
		Me.mnuView_Details.Index = 6
		Me.mnuViewSep2.Index = 7
		Me.mnuView_Object.Index = 8
		Me.mnuView_Sep1.Index = 9
		Me.mnuView_Refresh.Index = 10
		mnuView.MenuItems.AddRange(New System.Windows.Forms.MenuItem(){Me.mnuView_Toolbar, Me.mnuView_StatusBar, Me.mnuView_Sep0, Me.mnuView_Views, Me.mnuView_Sep_8, Me.mnuView_List, Me.mnuView_Details, Me.mnuViewSep2, Me.mnuView_Object, Me.mnuView_Sep1, Me.mnuView_Refresh})
		Me.mnuView_Treeview.Index = 0
		Me.mnuView_Listview.Index = 1
		Me.mnuView_WebView.Index = 2
		Me.mnuView_Sep_9.Index = 3
		Me.mnuView_HideAll.Index = 4
		Me.mnuView_ShowAll.Index = 5
		mnuView_Views.MenuItems.AddRange(New System.Windows.Forms.MenuItem(){Me.mnuView_Treeview, Me.mnuView_Listview, Me.mnuView_WebView, Me.mnuView_Sep_9, Me.mnuView_HideAll, Me.mnuView_ShowAll})
		Me.mnuView_Object_Properties.Index = 0
		Me.mnuView_Object_Methods.Index = 1
		Me.mnuView_Object_Bindings.Index = 2
		mnuView_Object.MenuItems.AddRange(New System.Windows.Forms.MenuItem(){Me.mnuView_Object_Properties, Me.mnuView_Object_Methods, Me.mnuView_Object_Bindings})
		Me.mnuTools_Options.Index = 0
		muTools.MenuItems.AddRange(New System.Windows.Forms.MenuItem(){Me.mnuTools_Options})
		Me.Menu = MainMenu1
	End Sub
#End Region 
#Region "Upgrade Support "
	Private Shared m_vb6FormDefInstance As frmMain
	Private Shared m_InitializingDefInstance As Boolean
	Public Shared Property DefInstance() As frmMain
		Get
			If m_vb6FormDefInstance Is Nothing OrElse m_vb6FormDefInstance.IsDisposed Then
				m_InitializingDefInstance = True
				m_vb6FormDefInstance = New frmMain()
				m_InitializingDefInstance = False
			End If
			DefInstance = m_vb6FormDefInstance
		End Get
		Set
			m_vb6FormDefInstance = Value
		End Set
	End Property
#End Region 
	
	'*********************************************************************************************************************************************************************
	' Enums
	'*********************************************************************************************************************************************************************
	Public Enum PathLevels
		PL_INVALID = -1
		PL_NETWORK = 0
		PL_LOCATOR = 1
		PL_CONTAINER = 2
	End Enum
	
	'*********************************************************************************************************************************************************************
	' Constants
	'*********************************************************************************************************************************************************************
	
	Const MAX_FAVS As Short = 10
	
	'*********************************************************************************************************************************************************************
	' Member Variables
	'*********************************************************************************************************************************************************************
	Dim m_Icons As New IMA2_Helper.IconManager
	Dim m_Net As New IMA2_Helper.NetList
	Dim m_CD As New IMA2_Helper.CmpDesc
	Dim m_Favs As New Collection
	Dim m_AL As IMA2.ILocator
	
	'*********************************************************************************************************************************************************************
	' Component Operations
	'*********************************************************************************************************************************************************************
	
	Private Sub NewAgentComponent()
		With m_CD
			.Path = atv.get_Path() & "\"
			.PID = "IMA2_Agent.Agent"
			.Machine = IMA2_HelperFunctions_definst.MachineFromPath((atv.get_Path()))
		End With
		atv.set_SelectedItem(atv.Nodes.Add(atv.Nodes(atv.get_Path()), MSComctlLib.TreeRelationshipConstants.tvwChild, atv.get_Path() & "\$new$", "<New Component>", IMA2_Helper.IMA2_Icons.II_Container))
		atv.StartLabelEdit()
	End Sub
	
	Private Sub NewComponent()
		Dim NP As String
		Dim LP As String
		Dim P As String
		
		frmInsert.DefInstance.ParentPath = atv.get_Path()
		frmInsert.DefInstance.ShowDialog()
		
		If frmInsert.DefInstance.Choice = frmInsert.InsCmpChoice.ICD_Cancel Then Exit Sub
		
		P = atv.get_Path()
		
		'Insert Single Component
		Dim CDs() As IMA2_Helper.CmpDesc
		Dim I As Short
		Dim C As IMA2.IComponent
		If frmInsert.DefInstance.Choice = frmInsert.InsCmpChoice.ICD_New Then
			
			'Create object
			With m_CD
				.Path = P & "\"
				.PID = frmInsert.DefInstance.ClsInfo.PID
				.Machine = IMA2_HelperFunctions_definst.MachineFromPath((atv.get_Path()))
			End With
			
			atv.set_SelectedItem(atv.Nodes.Add(atv.Nodes(atv.get_Path()), MSComctlLib.TreeRelationshipConstants.tvwChild, atv.get_Path() & "\$new$", "<New Component>", m_Icons.IconIndex((m_CD.PID))))
			atv.StartLabelEdit()
			
			'Added option to create "local process" components for VC++ debugging.
			If frmInsert.DefInstance.Context = frmInsert.InsCmpContext.ICC_Local Then m_CD.PID = m_CD.PID & "*"
			
			'Insert Saved Agent
		Else
			
			
			On Error Resume Next
			CDs = VB6.CopyArray(frmInsert.DefInstance.Descriptions)
			For I = LBound(CDs) To UBound(CDs)
				C = IMA2_HelperFunctions_definst.CreateIMA2Component(P & "\" & CDs(I).Path, (CDs(I).PID),  , True, atv.Locator)
				If Err.Number Then
					MsgBox(Err.Description, MsgBoxStyle.OKOnly Or MsgBoxStyle.Critical, "IMA2 Component Creation Error")
					Err.Clear()
				End If
				
				'UPGRADE_WARNING: IsEmpty was upgraded to IsNothing and has a new behavior. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1041"'
				If Not IsNothing(CDs(I).Data) Then C.Load(CDs(I).Data)
				
				If Err.Number Then
					MsgBox(Err.Description, MsgBoxStyle.OKOnly Or MsgBoxStyle.Critical, "IMA2 Component Data Load Error")
					Err.Clear()
				End If
				
			Next I
			
		End If
		
		atv.ExpandAll()
		
		'        NP = frmInsert.LibInfo.Path
		'       LP = "C:\Ima2\Components\" + NameFromPath(NP) 'ParentFromPath(Ima2Directory()) + "\Components\" + NameFromPath(NP)
		
		'        If Right(LP, 4) = ".tmp" Then
		'   P = frmInsert.ClsInfo.PID + " is running in the VB IDE. It will not be copied and registered to the local machine."
		'    Call MsgBox(P, vbOKOnly Or vbInformation, "IMA2 Component Library Manager")
		'     Exit Sub
		'  End If
		'
		'    If Not FileExists(LP) Then
		'         P = "The component library file for " + frmInsert.ClsInfo.PID + " is not registered on the local drive. Please wait while it is copied and registered."
		'          Call MsgBox(P, vbOKOnly Or vbInformation, "IMA2 Component Library Manager")
		'       Else
		'            If FileLen(LP) <> FileLen(NP) Then
		'   If FileLocked(LP) Then
		'        P = "There is a different version of the library file for " + frmInsert.ClsInfo.PID + " on the server. The local library cannot be updated because it is in use."
		'         Call MsgBox(P, vbOKOnly Or vbInformation, "IMA2 Component Library Manager")
		'      Else
		'           P = "There is a different version of the library file for " + frmInsert.ClsInfo.PID + " on the server. The server file has been copied and registered."
		'            Call CopyFile(NP, LP, False)
		'             Call TLI.TypeLibInfoFromFile(LP).Register
		'              Call MsgBox(P, vbOKOnly Or vbInformation, "IMA2 Component Library Manager")
		'           End If
		'        Else
		'
		'              'Create object
		'           End If
		'        End If
		
	End Sub
	
	Private Sub DeleteComponent(ByRef Path As String)
		
		Dim C As IMA2.IComponent
		
		If IMA2_HelperFunctions_definst.PathLevel(Path) <= PathLevels.PL_LOCATOR Then Exit Sub
		
		On Error Resume Next
		C = m_AL.Locate(Path)
		If Err.Number Then Err.Clear() : Call atv.Locator.Unregister(Path)
		
		If C Is Nothing Then
			Call m_AL.Unregister(Path)
		Else
			If C.Activated Then
				Call ActivateBranch(Path, False)
				atv.CtlRefresh()
				atv.ExpandAll()
			Else
				Call ActivateBranch(Path, False, True)
				
				'                If MsgBox("Deleting an activated component from the IMA2 network will release its bindings and shut down the component, possibly causing instability in other agents. Are you sure you wish to unregister " + Path + " while it is activated?", vbOKCancel, "Delete Activated Component") <> vbOK Then Exit Sub
				'               C.Activated = False
				'              If MsgBox("Are you sure you wish to delete " + Path + " from the IMA2 network?", vbOKCancel Or vbInformation, "Delete Deactivated Component") <> vbOK Then Exit Sub
			End If
			
			'Dim Paths() As String
			
			'Paths = m_AL.Components
			'For I = LBound(Paths) To UBound(Paths)
			'Call C.Destruct
			'Call atv.Locator.Unregister(Path)
			'Next I
			'            Call m_AL.Unregister(Path)
		End If
		
	End Sub
	
	'UPGRADE_NOTE: Activated was upgraded to Activated_Renamed. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1061"'
	Private Sub ActivateBranch(ByRef Path As String, ByRef Activated_Renamed As Boolean, Optional ByRef Destruct As Boolean = False)
		
		On Error Resume Next
		
		Dim Paths() As String
		Dim LP As Short
		Dim I As Short
		Dim C As IMA2.IComponent
		
		LP = Len(Path)
		Paths = VB6.CopyArray(m_AL.Components)
		
		For I = LBound(Paths) To UBound(Paths)
			If VB.Left(Paths(I), LP) <> Path Then Paths(I) = ""
		Next I
		
		Call IMA2_HelperFunctions_definst.QuickSortStrings(Paths)
		
		For I = UBound(Paths) To LBound(Paths) Step -1
			If Paths(I) <> "" Then
				C = m_AL.Locate(Paths(I))
				If IMA2_HelperFunctions_definst.NN(C) Then
					C.Activated = Activated_Renamed
					If Destruct Then
						Call C.Destruct()
						Err.Clear()
						Call m_AL.Unregister(Paths(I))
						Err.Clear()
					End If
				End If
			End If
		Next I
		
	End Sub
	
	Private Sub RefreshComponent()
		Dim O As Object
		If IMA2_HelperFunctions_definst.PathLevel((atv.get_Path())) <= PathLevels.PL_LOCATOR Then Exit Sub
		O = atv.Locator.Locate(atv.get_Path())
		Call UpdatePropertyValues(O) 'Read IDispatch properties values
		If Err.Number Then Stop
	End Sub
	
	'*********************************************************************************************************************************************************************
	' AgentListview Events
	'*********************************************************************************************************************************************************************
	
	Private Sub alv_ItemClick(ByVal eventSender As System.Object, ByVal eventArgs As AxIMA2_HelperX.__AgentListview_ItemClickEvent) Handles alv.ItemClick
		'wbv.Caption = alv.Path
	End Sub
	
	Private Sub alv_DblClick(ByVal eventSender As System.Object, ByVal eventArgs As AxIMA2_HelperX.__AgentListview_DblClickEvent) Handles alv.DblClick
		If eventArgs.Item Is Nothing Then Exit Sub
		Dim C As IMA2.IComponent
		Select Case eventArgs.Item.SmallIcon
			Case IMA2_Helper.IMA2_Icons.II_Property : Call SetProperty((atv.get_Path()), (eventArgs.Item.Text)) : Call RefreshComponent()
			Case IMA2_Helper.IMA2_Icons.II_Method : Call CallMethod((atv.get_Path()), (eventArgs.Item.Text)) : Call RefreshComponent()
			Case IMA2_Helper.IMA2_Icons.II_Binding
				C = m_AL.Locate(atv.get_Path())
				frmBindings.DefInstance.NetList = m_Net
				Call frmBindings.DefInstance.ShowDialog_Renamed(C.Bindings.Settings.Description(eventArgs.Item.Text))
				If frmBindings.DefInstance.Cancelled Then Exit Sub
				Call C.Bindings.Settings.Remove(eventArgs.Item.Text)
				C.Bindings.Settings.Add(eventArgs.Item.Text, frmBindings.DefInstance.Binding.Path, frmBindings.DefInstance.Binding.PIDs, frmBindings.DefInstance.Binding.IIDs, frmBindings.DefInstance.Binding.BindType)
				C.Bindings.Settings.Description(eventArgs.Item.Text).Path = frmBindings.DefInstance.Binding.Path
				eventArgs.Item.SubItems(2) = frmBindings.DefInstance.Binding.Path
				frmBindings.DefInstance.Close()
			Case Else
				atv.set_Path(eventArgs.Item.Key)
				If alv.ListItems.Count > 0 Then Call alv.SelectItem(1)
		End Select
	End Sub
	
	Private Sub alv_ItemMenu(ByVal eventSender As System.Object, ByVal eventArgs As AxIMA2_HelperX.__AgentListview_ItemMenuEvent) Handles alv.ItemMenu
		Dim IsContainer As Boolean
		If eventArgs.Item Is Nothing Then
			IsContainer = (atv.get_SelectedItem().Image = IMA2_Helper.IMA2_Icons.II_Container) Or (atv.get_SelectedItem().Image = IMA2_Helper.IMA2_Icons.II_Locator)
			Call CheckALVMenus((alv.get_ViewPath()), False, IsContainer)
		Else
			Call CheckALVMenus((eventArgs.Item.Key), True, atv.get_SelectedItem().Image = IMA2_Helper.IMA2_Icons.II_Container)
		End If
		'UPGRADE_ISSUE: Form method frmMain.PopupMenu was not upgraded. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup2064"'
		PopupMenu(mnuCmp)
	End Sub
	
	Private Sub alv_KeyPressEvent(ByVal eventSender As System.Object, ByVal eventArgs As AxIMA2_HelperX.__AgentListview_KeyPressEvent) Handles alv.KeyPressEvent
		
		If eventArgs.KeyAscii = 13 Then Call alv_DblClick(alv, New AxIMA2_HelperX.__AgentListview_DblClickEvent(alv.get_SelectedItem()))
		
		If eventArgs.KeyAscii = 8 And Not (atv.get_SelectedItem().Parent Is Nothing) Then
			Call atv.SelectItem(atv.get_SelectedItem().Parent.Index)
			If alv.ListItems.Count > 0 Then Call alv.SelectItem(1)
		End If
		
	End Sub
	
	Private Sub alv_ViewPathChange(ByVal eventSender As System.Object, ByVal eventArgs As AxIMA2_HelperX.__AgentListview_ViewPathChangeEvent) Handles alv.ViewPathChange
		
		
		Dim C As MSComctlLib.Node
		Dim C1 As MSComctlLib.Node
		
		C = atv.get_SelectedItem().Child
		C1 = C
		
		While IMA2_HelperFunctions_definst.NN(C)
			alv.ListItems(C.Key).ForeColor = System.Convert.ToUInt32(System.Drawing.ColorTranslator.FromOle(System.Convert.ToInt32(C.ForeColor)))
			C = C.Next
		End While
		
		
	End Sub
	
	'*********************************************************************************************************************************************************************
	' AgentTreeview Events
	'*********************************************************************************************************************************************************************
	
	Private Sub atv_DragStart(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles atv.DragStart
		atv.BeginOLEDrag()
	End Sub
	
	Private Sub atv_KeyUpEvent(ByVal eventSender As System.Object, ByVal eventArgs As AxIMA2_HelperX.__AgentTreeview_KeyUpEvent) Handles atv.KeyUpEvent
		If eventArgs.KeyCode = System.Windows.Forms.Keys.Delete Then Call DeleteComponent((atv.get_Path()))
	End Sub
	
	Private Sub atv_NodeClick(ByVal eventSender As System.Object, ByVal eventArgs As AxIMA2_HelperX.__AgentTreeview_NodeClickEvent) Handles atv.NodeClick
		alv.set_ViewPath(atv.get_Path())
		If atv.get_Path() = "\\" Then
			wbv.set_Caption(atv.get_SelectedItem().Text)
			wbv.Ctlset_ForeColor(System.Drawing.ColorTranslator.FromOle(System.Convert.ToInt32(atv.get_SelectedItem().ForeColor)))
		Else
			wbv.set_Caption(atv.get_Path())
			wbv.Ctlset_ForeColor(System.Drawing.ColorTranslator.FromOle(System.Convert.ToInt32(atv.get_SelectedItem().ForeColor)))
		End If
		ViewComponent()
	End Sub
	
	Private Sub atv_NodeMenu(ByVal eventSender As System.Object, ByVal eventArgs As AxIMA2_HelperX.__AgentTreeview_NodeMenuEvent) Handles atv.NodeMenu
		If eventArgs.Node Is Nothing Then Exit Sub
		
		Dim C As IMA2.IComponent
		If eventArgs.Node.Key = "\\" Then
			Call CheckATVMenus((eventArgs.Node.Key), True)
		Else
			C = m_AL.Locate(eventArgs.Node.Key)
			'UPGRADE_WARNING: TypeOf has a new behavior. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1041"'
			Call CheckATVMenus((eventArgs.Node.Key), TypeOf C Is IMA2.IContainer)
		End If
		
		'UPGRADE_ISSUE: Form method frmMain.PopupMenu was not upgraded. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup2064"'
		PopupMenu(mnuCmp)
	End Sub
	
	Private Sub atv_AfterLabelEdit(ByVal eventSender As System.Object, ByVal eventArgs As AxIMA2_HelperX.__AgentTreeview_AfterLabelEditEvent) Handles atv.AfterLabelEdit
		
		If Not IMA2_HelperFunctions_definst.ValidComponentName(eventArgs.NewString) Then
			eventArgs.Cancel = True
			Exit Sub
		End If
		
		atv.Nodes.Remove(atv.get_SelectedItem().Index) 'Remove the name entering node
		m_CD.Path = m_CD.Path & eventArgs.NewString 'Update the prospective path
		
		On Error Resume Next
		
		'Check to see if we're creating it in the DAD process or the normal way
		Dim C As IMA2.IComponent
		Dim P As IMA2.IContainer
		Dim RealPID As String
		If VB.Right(m_CD.PID, 1) = "*" Then
			
			
			'This is added functionality to allow VC++ components to be debugged. (RO)
			RealPID = VB.Left(m_CD.PID, Len(m_CD.PID) - 1)
			C = CreateObject(RealPID)
			P = m_AL.Locate(IMA2_HelperFunctions_definst.ParentFromPath((m_CD.Path)))
			Call C.Construct(m_CD.Path, RealPID, P.Locator)
			Call P.Locator.Register(C)
		Else
			'This creates the IMA2 component according to factory defaults
			Call IMA2_HelperFunctions_definst.CreateIMA2Component((m_CD.Path), (m_CD.PID), m_CD.Machine, True)
		End If
		If Err.Number Then MsgBox(Err.Description, MsgBoxStyle.OKOnly Or MsgBoxStyle.Critical, "IMA2 Component Creation Error")
		
	End Sub
	
	'*********************************************************************************************************************************************************************
	' Property Viewing Code
	'*********************************************************************************************************************************************************************
	Private Sub ViewComponent()
		Dim O As Object
		Dim C As IMA2.IComponent
		Dim T As TLI.TypeInfo
		Dim M As TLI.Members
		Dim CD As New IMA2_Helper.CmpDesc
		
		If IMA2_HelperFunctions_definst.PathLevel((atv.get_Path())) = PathLevels.PL_NETWORK Then
			cmv.Visible = False
			
			Exit Sub
		End If
		
		cmv.Visible = True
		
		On Error Resume Next
		O = atv.Locator.Locate(atv.get_Path())
		If Err.Number Or O Is Nothing Then Err.Clear() : Exit Sub
		
		C = O
		
		With C
			cmv.CName = IMA2_HelperFunctions_definst.NameFromPath(.Path)
			cmv.Machine = .Machine
			cmv.PID = .PID
			cmv.Thread = .Thread
			cmv.Process = .Process
			cmv.Activated = .Activated
		End With
		
		If IMA2_HelperFunctions_definst.PathLevel((atv.get_Path())) <= PathLevels.PL_LOCATOR Then Exit Sub
		
		M = TLITLIApplication_definst.InterfaceInfoFromObject(O).Members
		
		Call ViewState(C)
		Call LoadMembers(M) 'Load AgentListview with Prop/Method info
		Call ShowParameters(M) 'Show IDispatch parameter list
		Call UpdatePropertyValues(O) 'Read IDispatch properties values
		Call ShowBindings(O)
		
		If Err.Number Then
			Err.Clear()
			'Stop
		End If
		
	End Sub
	
	Private Sub ViewProperties()
		Dim O As Object
		
		If IMA2_HelperFunctions_definst.PathLevel((atv.get_Path())) <= PathLevels.PL_LOCATOR Then Exit Sub
		
		On Error Resume Next
		O = atv.Locator.Locate(atv.get_Path())
		If Err.Number Or O Is Nothing Then Err.Clear() : Exit Sub
		
		Call UpdatePropertyValues(O) 'Read IDispatch properties values
		Call ShowBindings(O)
		
		If Err.Number Then Stop
		
	End Sub
	
	
	Private Sub ViewState(ByRef C As IMA2.IComponent)
		mnuCmp_Activated.Checked = C.Activated
		If mnuCmp_Activated.Checked Then
			atv.get_SelectedItem().ForeColor = System.Convert.ToUInt32(QBColor(2))
		Else
			atv.get_SelectedItem().ForeColor = System.Convert.ToUInt32(QBColor(12))
		End If
		wbv.Ctlset_ForeColor(System.Drawing.ColorTranslator.FromOle(System.Convert.ToInt32(atv.get_SelectedItem().ForeColor)))
	End Sub
	
	Private Sub ShowBindings(ByRef O As Object)
		
		Dim I As Short
		Dim C As IMA2.IComponent
		Dim BI() As IMA2.BindingInfo
		Dim LI As MSComctlLib.ListItem
		
		C = O
		If C.Bindings Is Nothing Then Exit Sub
		If C.Bindings.Settings.Count = 0 Then Exit Sub
		
		BI = VB6.CopyArray(C.Bindings.Settings.Descriptions)
		
		For I = LBound(BI) To UBound(BI)
			LI = alv.ListItems.Add( ,  , BI(I).Name,  , IMA2_Helper.IMA2_Icons.II_Binding)
			LI.SubItems(1) = "Binding"
			
			If BI(I).BindType And IMA2.IMA2_BindingType.BT_Collection Then
				LI.SubItems(1) = "Binding List"
				LI.SubItems(2) = BI(I).Path
				
			ElseIf Not IMA2_HelperFunctions_definst.ArrayEmpty(BI(I).IIDs) Then 
				
			ElseIf Not IMA2_HelperFunctions_definst.ArrayEmpty(BI(I).PIDs) Then 
				
				
			End If
		Next 
		
	End Sub
	
	Private Sub LoadMembers(ByRef M As TLI.Members)
		
		On Error Resume Next
		
		Dim I As Short
		Dim OP As String 'Old procedure name
		Dim MI As TLI.MemberInfo
		Dim LI As MSComctlLib.ListItem
		
		For I = 8 To M.Count
			MI = M(I)
			If MI.Name <> OP Then
				If (MI.InvokeKind = TLI.InvokeKinds.INVOKE_FUNC) And mnuView_Object_Methods.Checked Then
					LI = alv.ListItems.Add( , MI.Name, MI.Name,  , IMA2_Helper.IMA2_Icons.II_Method)
				ElseIf (MI.InvokeKind <> TLI.InvokeKinds.INVOKE_FUNC) And mnuView_Object_Properties.Checked Then 
					LI = alv.ListItems.Add( , MI.Name, MI.Name,  , IMA2_Helper.IMA2_Icons.II_Property)
				End If
				LI.let_Tag(Str(I))
			End If
			OP = MI.Name
		Next 
	End Sub
	
	Private Sub ShowParameters(ByRef M As TLI.Members)
		Dim LI As MSComctlLib.ListItem
		Dim MI As TLI.MemberInfo
		Dim PD As String 'Parameter Description
		Dim RT As String 'Member Return Type
		
		For	Each LI In alv.ListItems
			If LI.Tag <> "" Then
				MI = M(Val(LI.Tag))
				Call DecodeParameters(MI, PD, RT)
				RT = RT & " "
				If RT = " " Then RT = ""
				If LI.SmallIcon = IMA2_Helper.IMA2_Icons.II_Method Then RT = RT & "Method"
				If PD = "()" Then PD = "" : RT = Trim(RT)
				LI.SubItems(1) = RT & PD
			End If
		Next LI
	End Sub
	
	Private Sub UpdatePropertyValues(ByRef O As Object)
		Dim LI As MSComctlLib.ListItem
		For	Each LI In alv.ListItems
			'UPGRADE_WARNING: Couldn't resolve default property of object ReadProperty(). Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
			If LI.SmallIcon = IMA2_Helper.IMA2_Icons.II_Property Then LI.SubItems(2) = CStr(ReadProperty(O, (LI.Text)))
		Next LI
	End Sub
	
	Public Function ReadProperty(ByRef O As Object, ByRef PN As String) As Object
		On Error Resume Next
		Dim V As Object
		'UPGRADE_WARNING: Couldn't resolve default property of object CallByName(). Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
		'UPGRADE_WARNING: Couldn't resolve default property of object V. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
		V = CallByName(O, PN, CallType.Get)
		If Err.Number Then
			'UPGRADE_WARNING: Couldn't resolve default property of object V. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
			V = "(error reading property)"
			'UPGRADE_WARNING: VarType has a new behavior. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1041"'
		ElseIf (VarType(V) And VariantType.Array) Then 
			Err.Clear()
			'UPGRADE_WARNING: Couldn't resolve default property of object V. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
			V = "(...)"
		ElseIf VarType(V) = VariantType.String Then 
			'UPGRADE_WARNING: Couldn't resolve default property of object V. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
			V = Chr(34) + V + Chr(34)
		End If
		'UPGRADE_WARNING: Couldn't resolve default property of object V. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
		'UPGRADE_WARNING: Couldn't resolve default property of object ReadProperty. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
		ReadProperty = V
	End Function
	
	Private Sub DecodeParameters(ByRef MI As TLI.MemberInfo, ByRef PD As String, ByRef RT As String)
		
		Dim PI As TLI.ParameterInfo
		Dim N As String
		Dim T As String
		Dim PL As String
		
		PD = ""
		'UPGRADE_WARNING: TypeName has a new behavior. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1041"'
		RT = Replace(Replace(TypeName(MI.ReturnType.TypedVariant), "(", "["), ")", "]")
		If RT = "Empty" Then RT = ""
		
		For	Each PI In MI.Parameters
			If PI.Flags And TLI.ParamFlags.PARAMFLAG_FRETVAL Then
				'UPGRADE_WARNING: TypeName has a new behavior. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1041"'
				RT = TypeName(PI.VarTypeInfo.TypedVariant)
			Else
				N = PI.Name
				'UPGRADE_WARNING: TypeName has a new behavior. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1041"'
				T = TypeName(PI.VarTypeInfo.TypedVariant)
				If PI.Optional Then
					PL = ", [" & N & " As " & T & "]"
				ElseIf PI.Default Then 
					PL = ", [" & N & " As " & T & " = " & "]"
				Else
					PL = ", " & N & " As " & T
				End If
				PD = PD & PL
			End If
		Next PI
		PD = "(" & Mid(PD, 3) & ")"
		'If PD = "()" Then PD = "(void)"
		
	End Sub
	
	Private Sub CallMethod(ByRef Path As String, ByRef MethName As String)
		
		On Error Resume Next
		
		Dim O As Object
		Dim TS As String 'Type string
		Dim Prompt As String 'Prompt
		Dim Args As String 'Args from TypeString
		Dim AC As Short 'Argument count
		
		O = atv.Locator.Locate(Path)
		TS = alv.get_SelectedItem().SubItems(1)
		
		Dim Strs() As String
		Dim I As Short
		If InStr(TS, "(") Then
			AC = IMA2_HelperFunctions_definst.StrCount(TS, ",") + 1
			Args = Mid(TS, InStr(TS, "(") + 1)
			Args = VB.Left(Args, Len(Args) - 1)
			Prompt = "Call function '" & MethName & "' on " & Path
			'Args = InputBox(Prompt, "Call Component Method", Args)
			
			Call frmParams.DefInstance.AddItem("Name", "String", "Boo")
			Call frmParams.DefInstance.AddItem("Height", "Integer", "10")
			Call frmParams.DefInstance.AddItem("Width", "Integer", "15")
			
			frmParams.DefInstance.ShowDialog_Renamed()
			
			Dim Vars(AC - 1) As Object
			
			Strs = Split(Args, ",")
			
			If AC <> UBound(Strs) + 1 Then
				MsgBox("Number of parameters does not match.")
				Exit Sub
			End If
			
			For I = 0 To AC - 1
				'UPGRADE_WARNING: Couldn't resolve default property of object Vars(I). Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
				Vars(I) = CObj(Strs(I))
			Next I
			
			'            Stop
			
			Call CallByName(O, MethName, CallType.Method, CDbl(0))
		Else
			Call CallByName(O, MethName, CallType.Method)
		End If
		
		
		frmParams.DefInstance.Close()
		
		If Err.Number Then Err.Clear() : Exit Sub
		
	End Sub
	
	
	Private Sub SetProperty(ByRef Path As String, ByRef PropName As String)
		Dim NV As String
		Dim OV As String
		Dim P As String
		Dim V As Object
		Dim O As Object
		
		O = atv.Locator.Locate(Path)
		
		On Error Resume Next
		'UPGRADE_WARNING: Couldn't resolve default property of object CallByName(). Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
		'UPGRADE_WARNING: Couldn't resolve default property of object V. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
		V = CallByName(O, PropName, CallType.Get)
		If Err.Number Then Err.Clear() : Exit Sub
		
		'UPGRADE_WARNING: Couldn't resolve default property of object V. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
		OV = CStr(V)
		P = "Set property '" & PropName & "' on " & Path
		NV = InputBox(P, "Change Component Property", OV)
		If NV = "" Then Exit Sub
		Call CallByName(O, PropName, CallType.Set, CObj(NV))
	End Sub
	
	'*********************************************************************************************************************************************************************
	' Form Events
	'*********************************************************************************************************************************************************************
	
	Private Sub frmMain_Load(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MyBase.Load
		Dim I As Short
		
		'Call LoadUserOptions
		Call LoadFormPosition(Me)
		
		'Update user UI settings
		mnuView_Object_Properties.Checked = CBool(GetSetting(VB6.GetExeName(), "frmMain", ".ShowProperties", CStr(True)))
		mnuView_Object_Methods.Checked = CBool(GetSetting(VB6.GetExeName(), "frmMain", ".ShowMethods", CStr(True)))
		alv.ColumnHeaders(1).Width = Val(GetSetting(VB6.GetExeName(), "frmMain", "CH1W", "" & alv.ColumnHeaders(1).Width))
		alv.ColumnHeaders(2).Width = Val(GetSetting(VB6.GetExeName(), "frmMain", "CH2W", "" & alv.ColumnHeaders(2).Width))
		atv.Width = Val(GetSetting(VB6.GetExeName(), "frmMain", "AtvWidth", "" & atv.Width))
		
		'Set up Icon Manager
		'UPGRADE_WARNING: Couldn't resolve default property of object m_Icons.ImageList.UseMaskColor. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
		m_Icons.ImageList.UseMaskColor = True
		m_Icons.Directory = "C:\IMA2\System\Icons"
		
		'Refresh component list
		m_Net.Refresh()
		
		'Initialize AgentTreeview and AgentListView
		atv.set_NetList(m_Net)
		alv.set_NetList(m_Net)
		
		'Refresh network information
		atv.set_Path("\\")
		atv.ExpandAll()
		m_AL = atv.Locator
		
		'Load Favorites
		For I = 1 To 10
			mnuCmp_New_Favorites.Load(I)
			mnuCmp_New_Favorites(I).Visible = False
		Next I
		
	End Sub
	
	'******************************************************************************************************
	
	'UPGRADE_WARNING: Event frmMain.Resize may fire when form is intialized. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup2075"'
	Private Sub frmMain_Resize(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MyBase.Resize
		
		On Error Resume Next
		Dim TP_Height, BP_Width, BP_Top, BP_Left, BP_Height, TP_Top As Object
		
		If Me.Visible = False Then Exit Sub
		If Me.WindowState = System.Windows.Forms.FormWindowState.Minimized Then Exit Sub
		
		slr.Visible = alv.Visible And atv.Visible
		sud.Visible = (alv.Visible Or atv.Visible) And wbv.Visible
		
		'UPGRADE_WARNING: Couldn't resolve default property of object TP_Height. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
		If wbv.Visible Then TP_Height = wbv.Height + sud.Height
		
		'UPGRADE_WARNING: Couldn't resolve default property of object TP_Top. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
		TP_Top = Toolbar1.Height
		'UPGRADE_WARNING: Couldn't resolve default property of object BP_Left. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
		BP_Left = bvlLeft.Width
		'UPGRADE_WARNING: Couldn't resolve default property of object TP_Height. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
		'UPGRADE_WARNING: Couldn't resolve default property of object TP_Top. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
		'UPGRADE_WARNING: Couldn't resolve default property of object BP_Top. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
		BP_Top = TP_Top + TP_Height
		'UPGRADE_WARNING: Couldn't resolve default property of object BP_Top. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
		'UPGRADE_WARNING: Couldn't resolve default property of object BP_Height. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
		BP_Height = Me.ClientRectangle.Height - stb.Height - BP_Top
		'UPGRADE_WARNING: Couldn't resolve default property of object BP_Width. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
		BP_Width = Me.ClientRectangle.Width - (2 * bvlLeft.Width)
		
		wbv.SetBounds(BP_Left, TP_Top, BP_Width, wbv.Height)
		'UPGRADE_WARNING: Couldn't resolve default property of object TP_Top. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
		sud.SetBounds(BP_Left, TP_Top + wbv.Height, BP_Width, sud.Height)
		
		If Not alv.Visible Then
			atv.SetBounds(BP_Left, BP_Top, BP_Width, BP_Height)
		ElseIf Not atv.Visible Then 
			'UPGRADE_WARNING: Couldn't resolve default property of object BP_Height. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
			'UPGRADE_WARNING: Couldn't resolve default property of object BP_Top. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
			cmv.Move(BP_Left, BP_Top + (BP_Height - cmv.Height), BP_Width)
			'UPGRADE_WARNING: Couldn't resolve default property of object BP_Height. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
			alv.SetBounds(BP_Left, BP_Top, BP_Width, BP_Height - cmv.Height)
		Else
			atv.SetBounds(BP_Left, BP_Top, atv.Width, BP_Height)
			slr.SetBounds(atv.Left + atv.Width, BP_Top, slr.Width, BP_Height)
			
			'UPGRADE_WARNING: Couldn't resolve default property of object BP_Height. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
			'UPGRADE_WARNING: Couldn't resolve default property of object BP_Top. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
			cmv.Move(slr.Left + slr.Width, BP_Top + (BP_Height - cmv.Height) - 2, Me.ClientRectangle.Width - slr.Width - atv.Width - (bvlLeft.Width) - 2)
			'UPGRADE_WARNING: Couldn't resolve default property of object BP_Height. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
			alv.SetBounds(slr.Left + slr.Width, BP_Top, Me.ClientRectangle.Width - slr.Width - atv.Width - (bvlLeft.Width * 1), BP_Height - cmv.Height)
		End If
		
		
	End Sub
	
	'******************************************************************************************************
	
	'UPGRADE_WARNING: Form event frmMain.Unload has a new behavior. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup2065"'
	Private Sub frmMain_Closed(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MyBase.Closed
		
		Call SaveFormPosition(Me)
		Call SaveSetting(VB6.GetExeName(), "frmMain", ".ShowProperties", CStr(mnuView_Object_Properties.Checked))
		Call SaveSetting(VB6.GetExeName(), "frmMain", ".ShowMethods", CStr(mnuView_Object_Methods.Checked))
		Call SaveSetting(VB6.GetExeName(), "frmMain", "CH1W", "" & alv.ColumnHeaders(1).Width)
		Call SaveSetting(VB6.GetExeName(), "frmMain", "CH2W", "" & alv.ColumnHeaders(2).Width)
		Call SaveSetting(VB6.GetExeName(), "frmMain", "AtvWidth", "" & atv.Width)
		
		Dim F As System.Windows.Forms.Form
		
		'UPGRADE_ISSUE: Forms collection was not upgraded. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup2068"'
		For	Each F In Forms
			If Not (F Is Me) Then F.Close()
		Next F
		
	End Sub
	
	'******************************************************************************************************
	
	Private Sub XXXActivateBranch(ByRef Path As String, ByRef Value As Boolean)
		
		On Error Resume Next
		Dim Paths() As String
		Dim C As IMA2.IComponent
		Dim I As Short
		
		Paths = VB6.CopyArray(m_AL.Components)
		
		For I = LBound(Paths) To UBound(Paths)
			If IMA2_HelperFunctions_definst.IsDescendant(Paths(I), Path) Then
				C = m_AL.Locate(Paths(I))
				C.Activated = Value
				If Err.Number Then
					atv.Nodes(Paths(I)).ForeColor = System.Convert.ToUInt32(QBColor(7))
					Err.Clear()
				ElseIf C.Activated Then 
					atv.Nodes(Paths(I)).ForeColor = System.Convert.ToUInt32(QBColor(2))
				Else
					atv.Nodes(Paths(I)).ForeColor = System.Convert.ToUInt32(QBColor(12))
				End If
			End If
		Next I
		
		mnuCmp_Activated.Checked = C.Activated
		wbv.Ctlset_ForeColor(System.Drawing.ColorTranslator.FromOle(System.Convert.ToInt32(atv.get_SelectedItem().ForeColor)))
		
	End Sub
	
	Public Sub mnuCmp_ActivateBranch_Popup(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles mnuCmp_ActivateBranch.Popup
		mnuCmp_ActivateBranch_Click(eventSender, eventArgs)
	End Sub
	Public Sub mnuCmp_ActivateBranch_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles mnuCmp_ActivateBranch.Click
		
		If Me.ActiveControl Is atv Then
			Call ActivateBranch((atv.get_Path()), True)
		ElseIf Me.ActiveControl Is alv Then 
			Call ActivateBranch((alv.get_Path()), True)
		End If
		
		m_Net.Refresh()
		atv.ExpandAll()
		
	End Sub
	
	Public Sub mnuCmp_Activated_Popup(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles mnuCmp_Activated.Popup
		mnuCmp_Activated_Click(eventSender, eventArgs)
	End Sub
	Public Sub mnuCmp_Activated_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles mnuCmp_Activated.Click
		Dim C As IMA2.IComponent
		If Me.ActiveControl Is atv Then
			
			'Call ActivateBranch(atv.Path, Not mnuCmp_Activated.Checked)
			
			C = m_AL.Locate(atv.get_Path())
			C.Activated = Not mnuCmp_Activated.Checked
			mnuCmp_Activated.Checked = C.Activated
			If mnuCmp_Activated.Checked Then
				atv.get_SelectedItem().ForeColor = System.Convert.ToUInt32(QBColor(2))
			Else
				atv.get_SelectedItem().ForeColor = System.Convert.ToUInt32(QBColor(12))
			End If
			wbv.Ctlset_ForeColor(System.Drawing.ColorTranslator.FromOle(System.Convert.ToInt32(atv.get_SelectedItem().ForeColor)))
		End If
	End Sub
	
	Public Sub mnuCmp_Copy_Popup(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles mnuCmp_Copy.Popup
		mnuCmp_Copy_Click(eventSender, eventArgs)
	End Sub
	Public Sub mnuCmp_Copy_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles mnuCmp_Copy.Click
		'UPGRADE_ISSUE: Clipboard method Clipboard.Clear was not upgraded. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup2069"'
		Clipboard.Clear()
		'UPGRADE_ISSUE: Constant vbCFText was not upgraded. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup2070"'
		'UPGRADE_ISSUE: Clipboard method Clipboard.SetText was not upgraded. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup2069"'
		Clipboard.SetText("{IMA2 Component} " & atv.get_Path(), vbCFText)
	End Sub
	
	Public Sub mnuCmp_DeactivateBranch_Popup(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles mnuCmp_DeactivateBranch.Popup
		mnuCmp_DeactivateBranch_Click(eventSender, eventArgs)
	End Sub
	Public Sub mnuCmp_DeactivateBranch_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles mnuCmp_DeactivateBranch.Click
		
		If Me.ActiveControl Is atv Then
			Call ActivateBranch((atv.get_Path()), False)
		ElseIf Me.ActiveControl Is alv Then 
			Call ActivateBranch((alv.get_Path()), False)
		End If
		
		m_Net.Refresh()
		atv.ExpandAll()
		
	End Sub
	
	'*********************************************************************************************************************************************************************
	' Menu Events
	'*********************************************************************************************************************************************************************
	Public Sub mnuCmp_New_Agent_Popup(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles mnuCmp_New_Agent.Popup
		mnuCmp_New_Agent_Click(eventSender, eventArgs)
	End Sub
	Public Sub mnuCmp_New_Agent_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles mnuCmp_New_Agent.Click
		Call NewAgentComponent()
	End Sub
	
	Public Sub mnuCmp_Delete_Popup(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles mnuCmp_Delete.Popup
		mnuCmp_Delete_Click(eventSender, eventArgs)
	End Sub
	Public Sub mnuCmp_Delete_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles mnuCmp_Delete.Click
		If Me.ActiveControl Is atv Then
			Call DeleteComponent((atv.get_Path()))
		ElseIf Me.ActiveControl Is alv Then 
			Call DeleteComponent((alv.get_Path()))
		End If
		
	End Sub
	
	Public Sub mnuView_Refresh_Popup(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles mnuView_Refresh.Popup
		mnuView_Refresh_Click(eventSender, eventArgs)
	End Sub
	Public Sub mnuView_Refresh_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles mnuView_Refresh.Click
		Call RefreshComponent()
	End Sub
	
	Public Sub mnuCmp_New_Cmp_Popup(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles mnuCmp_New_Cmp.Popup
		mnuCmp_New_Cmp_Click(eventSender, eventArgs)
	End Sub
	Public Sub mnuCmp_New_Cmp_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles mnuCmp_New_Cmp.Click
		Call NewComponent()
	End Sub
	
	Public Sub mnuCmp_SaveAs_Popup(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles mnuCmp_SaveAs.Popup
		mnuCmp_SaveAs_Click(eventSender, eventArgs)
	End Sub
	Public Sub mnuCmp_SaveAs_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles mnuCmp_SaveAs.Click
		
		Dim Dlg As New frmSaveAs
		Dim P() As String
		
		P = VB6.CopyArray(GetSavedPaths) 'Get Saved Paths
		Call Dlg.DoSave(P, atv.Nodes) 'Start the file save wizard
		
	End Sub
	
	Public Sub mnuFile_Exit_Popup(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles mnuFile_Exit.Popup
		mnuFile_Exit_Click(eventSender, eventArgs)
	End Sub
	Public Sub mnuFile_Exit_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles mnuFile_Exit.Click
		End
	End Sub
	
	'*********************************************************************************************************************************************************************
	' View Menu Events
	'*********************************************************************************************************************************************************************
	
	Public Sub mnuView_Listview_Popup(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles mnuView_Listview.Popup
		mnuView_Listview_Click(eventSender, eventArgs)
	End Sub
	Public Sub mnuView_Listview_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles mnuView_Listview.Click
		mnuView_Listview.Checked = Not mnuView_Listview.Checked
		alv.Visible = mnuView_Listview.Checked
		slr.Visible = False
		frmMain_Resize(Me, New System.EventArgs())
	End Sub
	
	Public Sub mnuView_Treeview_Popup(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles mnuView_Treeview.Popup
		mnuView_Treeview_Click(eventSender, eventArgs)
	End Sub
	Public Sub mnuView_Treeview_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles mnuView_Treeview.Click
		mnuView_Treeview.Checked = Not mnuView_Treeview.Checked
		atv.Visible = mnuView_Treeview.Checked
		frmMain_Resize(Me, New System.EventArgs())
	End Sub
	
	Public Sub mnuView_WebView_Popup(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles mnuView_WebView.Popup
		mnuView_WebView_Click(eventSender, eventArgs)
	End Sub
	Public Sub mnuView_WebView_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles mnuView_WebView.Click
		mnuView_WebView.Checked = Not mnuView_WebView.Checked
		wbv.Visible = mnuView_WebView.Checked
		frmMain_Resize(Me, New System.EventArgs())
	End Sub
	
	'*********************************************************************************************************************************************************************
	' Property and Method View Menus
	'*********************************************************************************************************************************************************************
	Public Sub mnuView_Object_Methods_Popup(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles mnuView_Object_Methods.Popup
		mnuView_Object_Methods_Click(eventSender, eventArgs)
	End Sub
	Public Sub mnuView_Object_Methods_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles mnuView_Object_Methods.Click
		mnuView_Object_Methods.Checked = Not mnuView_Object_Methods.Checked
		Call atv_NodeClick(atv, New AxIMA2_HelperX.__AgentTreeview_NodeClickEvent(atv.get_SelectedItem()))
	End Sub
	
	Public Sub mnuView_Object_Properties_Popup(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles mnuView_Object_Properties.Popup
		mnuView_Object_Properties_Click(eventSender, eventArgs)
	End Sub
	Public Sub mnuView_Object_Properties_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles mnuView_Object_Properties.Click
		mnuView_Object_Properties.Checked = Not mnuView_Object_Properties.Checked
		Call atv_NodeClick(atv, New AxIMA2_HelperX.__AgentTreeview_NodeClickEvent(atv.get_SelectedItem()))
	End Sub
	
	'*********************************************************************************************************************************************************************
	' Splitter Events
	'*********************************************************************************************************************************************************************
	
	Private Sub slr_OnSplitterRelease(ByVal eventSender As System.Object, ByVal eventArgs As AxIMA2_HelperX.__SplitterLR_OnSplitterReleaseEvent) Handles slr.OnSplitterRelease
		If atv.Width + eventArgs.Delta < 1 Then Exit Sub
		atv.Width = atv.Width + eventArgs.Delta
		frmMain_Resize(Me, New System.EventArgs())
	End Sub
	
	Private Sub sud_OnSplitterRelease(ByVal eventSender As System.Object, ByVal eventArgs As AxIMA2_HelperX.__SplitterUD_OnSplitterReleaseEvent) Handles sud.OnSplitterRelease
		If wbv.Height + eventArgs.Delta < 1 Then Exit Sub
		wbv.Height = wbv.Height + eventArgs.Delta
		frmMain_Resize(Me, New System.EventArgs())
	End Sub
	
	'*********************************************************************************************************************************************************************
	' Menu Management
	'*********************************************************************************************************************************************************************
	
	Private Sub DisplayFavorites()
		Dim I As Short
		If m_Favs.Count() = 0 Then
			mnuCmp_New_Favorites(0).Text = "(no favorites)"
			mnuCmp_New_Favorites(0).Enabled = False
		Else
			For I = m_Favs.Count() To MAX_FAVS
				mnuCmp_New_Favorites(I).Visible = False
			Next 
			For I = 0 To m_Favs.Count() - 1
				'UPGRADE_WARNING: Couldn't resolve default property of object m_Favs(). Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup1037"'
				mnuCmp_New_Favorites(I).Text = m_Favs.Item(I + 1)
				mnuCmp_New_Favorites(I).Visible = True
			Next 
		End If
	End Sub
	
	Private Sub CheckALVMenus(ByRef Path As String, ByRef ItemSelected As Boolean, ByRef IsContainer As Boolean)
		
		Dim PL As Short
		
		PL = IMA2_HelperFunctions_definst.PathLevel(Path)
		
		Call DisplayFavorites()
		
		mnuCmp_Properties.Visible = True
		
		mnuCmp_Activated.Visible = (PL > PathLevels.PL_LOCATOR)
		mnuCmp_Activated_Sep.Visible = mnuCmp_Activated.Visible
		
		mnuCmp_Connect.Visible = (PL = PathLevels.PL_NETWORK)
		mnuCmp_Disconnect.Visible = (PL = PathLevels.PL_LOCATOR) And ItemSelected
		mnuCmp_Connect_Sep.Visible = mnuCmp_Disconnect.Visible Or (mnuCmp_Connect.Visible And ItemSelected)
		
		mnuCmp_New.Visible = (PL >= PathLevels.PL_LOCATOR)
		mnuCmp_New_Sep.Visible = mnuCmp_New.Visible
		
		mnuCmp_Copy.Visible = PL > PathLevels.PL_NETWORK
		mnuCmp_Paste.Visible = PL > PathLevels.PL_NETWORK
		
		mnuCmp_Copy.Enabled = ItemSelected And (PL > PathLevels.PL_LOCATOR)
		mnuCmp_Paste.Enabled = (Not ItemSelected) And (PL > PathLevels.PL_NETWORK)
		
		mnuCmp_Delete.Visible = ItemSelected And (PL > PathLevels.PL_LOCATOR)
		
		mnuCmp_SaveAs.Visible = ItemSelected And (PL > PathLevels.PL_LOCATOR)
		
		mnuCmp_Properties.Visible = ItemSelected
		
		mnuCmp_Delete_Sep.Visible = mnuCmp_Delete.Visible
		mnuCmp_SaveAs_Sep.Visible = mnuCmp_SaveAs.Visible
		mnuCmp_Paste_Sep.Visible = mnuCmp_Copy.Visible And (mnuCmp_Delete.Visible Or mnuCmp_SaveAs.Visible Or mnuCmp_Properties.Visible)
		
	End Sub
	
	Private Sub CheckATVMenus(ByRef Path As String, ByRef IsContainer As Boolean)
		
		Dim PL As Short
		
		PL = IMA2_HelperFunctions_definst.PathLevel(Path)
		
		Call DisplayFavorites()
		mnuCmp_Properties.Visible = True
		
		mnuCmp_Activated.Visible = (PL > PathLevels.PL_LOCATOR)
		
		mnuCmp_ActivateBranch.Visible = (PL >= PathLevels.PL_LOCATOR) And IsContainer
		mnuCmp_DeactivateBranch.Visible = mnuCmp_ActivateBranch.Visible
		
		mnuCmp_Connect.Visible = (PL = PathLevels.PL_NETWORK)
		mnuCmp_Disconnect.Visible = (PL = PathLevels.PL_LOCATOR)
		
		mnuCmp_New.Visible = (PL >= PathLevels.PL_LOCATOR) And (IsContainer Or PL = PathLevels.PL_LOCATOR)
		
		mnuCmp_Copy.Visible = (PL > PathLevels.PL_NETWORK)
		mnuCmp_Paste.Visible = mnuCmp_Copy.Visible
		
		mnuCmp_Copy.Enabled = (PL > PathLevels.PL_NETWORK)
		'UPGRADE_ISSUE: Clipboard method Clipboard.GetText was not upgraded. Click for more: 'ms-help://MS.VSCC/commoner/redir/redirect.htm?keyword="vbup2069"'
		mnuCmp_Paste.Enabled = (PL > PathLevels.PL_NETWORK) And (InStr(Clipboard.GetText(), "{IMA2 Component}") = 1)
		
		mnuCmp_Delete.Visible = (PL > PathLevels.PL_LOCATOR)
		mnuCmp_SaveAs.Visible = (PL > PathLevels.PL_LOCATOR)
		
		mnuCmp_New_Sep.Visible = mnuCmp_New.Visible
		mnuCmp_Connect_Sep.Visible = mnuCmp_Disconnect.Visible Or mnuCmp_Connect.Visible
		mnuCmp_Activated_Sep.Visible = mnuCmp_Activated.Visible
		mnuCmp_Branch_Sep.Visible = mnuCmp_ActivateBranch.Visible
		mnuCmp_Delete_Sep.Visible = mnuCmp_Delete.Visible
		mnuCmp_SaveAs_Sep.Visible = mnuCmp_SaveAs.Visible
		mnuCmp_Paste_Sep.Visible = mnuCmp_Copy.Visible And (mnuCmp_Delete.Visible Or mnuCmp_SaveAs.Visible Or mnuCmp_Properties.Visible)
		
	End Sub
	
	
	'*********************************************************************************************************************************************************************
	' Misc. Functions
	'*********************************************************************************************************************************************************************
	
	Private Function GetSavedPaths() As String()
		
		Dim Paths() As String
		Dim PC As String
		Dim UB As Short
		Dim LB As Short
		Dim I As Short
		
		Paths = VB6.CopyArray(m_Net.Items)
		LB = LBound(Paths)
		UB = UBound(Paths)
		
		PC = atv.get_Path()
		
		For I = LB To UB
			If Not IMA2_HelperFunctions_definst.IsDescendant(Paths(I), PC) Then Paths(I) = ""
		Next 
		
		Call IMA2_HelperFunctions_definst.RemoveBlankStrings(Paths)
		
		GetSavedPaths = VB6.CopyArray(Paths)
		
	End Function
End Class