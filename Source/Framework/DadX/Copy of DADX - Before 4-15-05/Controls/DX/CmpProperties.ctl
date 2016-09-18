VERSION 5.00
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Begin VB.UserControl CmpPropertyView 
   ClientHeight    =   4650
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4800
   ScaleHeight     =   310
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   320
   Begin IMA2_HelperX.ImageLabel ImageLabel5 
      Height          =   495
      Left            =   120
      TabIndex        =   11
      Top             =   480
      Width           =   4335
      _ExtentX        =   7646
      _ExtentY        =   873
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin TabDlg.SSTab SSTab1 
      Height          =   4575
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   4695
      _ExtentX        =   8281
      _ExtentY        =   8070
      _Version        =   393216
      Style           =   1
      TabHeight       =   529
      TabCaption(0)   =   "General"
      TabPicture(0)   =   "CmpProperties.ctx":0000
      Tab(0).ControlEnabled=   -1  'True
      Tab(0).Control(0)=   "ImageLabel4"
      Tab(0).Control(0).Enabled=   0   'False
      Tab(0).Control(1)=   "ImageLabel3"
      Tab(0).Control(1).Enabled=   0   'False
      Tab(0).Control(2)=   "ImageLabel2"
      Tab(0).Control(2).Enabled=   0   'False
      Tab(0).Control(3)=   "Bevel2"
      Tab(0).Control(3).Enabled=   0   'False
      Tab(0).Control(4)=   "bvlBottom"
      Tab(0).Control(4).Enabled=   0   'False
      Tab(0).Control(5)=   "bvlTop"
      Tab(0).Control(5).Enabled=   0   'False
      Tab(0).Control(6)=   "ImageLabel1"
      Tab(0).Control(6).Enabled=   0   'False
      Tab(0).ControlCount=   7
      TabCaption(1)   =   "Bindings"
      TabPicture(1)   =   "CmpProperties.ctx":001C
      Tab(1).ControlEnabled=   0   'False
      Tab(1).Control(0)=   "Bevel1"
      Tab(1).Control(1)=   "Text1"
      Tab(1).Control(2)=   "Text2"
      Tab(1).ControlCount=   3
      TabCaption(2)   =   "Tab 2"
      TabPicture(2)   =   "CmpProperties.ctx":0038
      Tab(2).ControlEnabled=   0   'False
      Tab(2).ControlCount=   0
      Begin IMA2_HelperX.ImageLabel ImageLabel1 
         Height          =   255
         Left            =   240
         TabIndex        =   7
         Top             =   1200
         Width           =   4215
         _ExtentX        =   7435
         _ExtentY        =   450
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
      End
      Begin VB.TextBox Text2 
         Height          =   1455
         Left            =   -74760
         TabIndex        =   4
         Text            =   "Text2"
         Top             =   1560
         Width           =   2775
      End
      Begin VB.TextBox Text1 
         Height          =   285
         Left            =   -74760
         TabIndex        =   3
         Text            =   "Text1"
         Top             =   1200
         Width           =   2775
      End
      Begin IMA2_HelperX.Bevel bvlTop 
         Height          =   135
         Left            =   120
         TabIndex        =   1
         Top             =   1545
         Width           =   4455
         _ExtentX        =   4683
         _ExtentY        =   238
      End
      Begin IMA2_HelperX.Bevel bvlBottom 
         Height          =   45
         Left            =   120
         TabIndex        =   2
         Top             =   2760
         Width           =   4455
         _ExtentX        =   4683
         _ExtentY        =   79
      End
      Begin IMA2_HelperX.Bevel Bevel1 
         Height          =   45
         Left            =   -74880
         TabIndex        =   5
         Top             =   1080
         Width           =   4335
         _ExtentX        =   7646
         _ExtentY        =   79
      End
      Begin IMA2_HelperX.Bevel Bevel2 
         Height          =   135
         Left            =   120
         TabIndex        =   6
         Top             =   1080
         Width           =   4455
         _ExtentX        =   7858
         _ExtentY        =   238
      End
      Begin IMA2_HelperX.ImageLabel ImageLabel2 
         Height          =   255
         Left            =   240
         TabIndex        =   8
         Top             =   1680
         Width           =   4215
         _ExtentX        =   7435
         _ExtentY        =   450
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
      End
      Begin IMA2_HelperX.ImageLabel ImageLabel3 
         Height          =   255
         Left            =   240
         TabIndex        =   9
         Top             =   2040
         Width           =   4215
         _ExtentX        =   7435
         _ExtentY        =   450
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
      End
      Begin IMA2_HelperX.ImageLabel ImageLabel4 
         Height          =   255
         Left            =   240
         TabIndex        =   10
         Top             =   2400
         Width           =   4215
         _ExtentX        =   7435
         _ExtentY        =   450
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
      End
   End
End
Attribute VB_Name = "CmpPropertyView"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
