VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Begin VB.Form Form1 
   Caption         =   "MOTENC-100 Motion Control"
   ClientHeight    =   8295
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   11985
   LinkTopic       =   "Form1"
   ScaleHeight     =   8295
   ScaleWidth      =   11985
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton ReadADC 
      Caption         =   "Read"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2835
      Index           =   0
      Left            =   10320
      MaskColor       =   &H00808080&
      TabIndex        =   48
      Top             =   4560
      Width           =   915
   End
   Begin VB.CommandButton ReadCntr 
      Caption         =   "Read"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      Index           =   7
      Left            =   10380
      MaskColor       =   &H00808080&
      TabIndex        =   26
      Top             =   3660
      Width           =   915
   End
   Begin VB.CommandButton ReadCntr 
      Caption         =   "Read"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      Index           =   6
      Left            =   10380
      MaskColor       =   &H00808080&
      TabIndex        =   22
      Top             =   3240
      Width           =   915
   End
   Begin VB.CommandButton ReadCntr 
      Caption         =   "Read"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      Index           =   5
      Left            =   10380
      MaskColor       =   &H00808080&
      TabIndex        =   20
      Top             =   2820
      Width           =   915
   End
   Begin VB.CommandButton ReadCntr 
      Caption         =   "Read"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      Index           =   4
      Left            =   10380
      MaskColor       =   &H00808080&
      TabIndex        =   16
      Top             =   2400
      Width           =   915
   End
   Begin VB.CommandButton ReadCntr 
      Caption         =   "Read"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      Index           =   3
      Left            =   10380
      MaskColor       =   &H00808080&
      TabIndex        =   14
      Top             =   1980
      Width           =   915
   End
   Begin VB.CommandButton ReadCntr 
      Caption         =   "Read"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      Index           =   2
      Left            =   10380
      MaskColor       =   &H00808080&
      TabIndex        =   10
      Top             =   1560
      Width           =   915
   End
   Begin VB.CommandButton ReadCntr 
      Caption         =   "Read"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      Index           =   1
      Left            =   10380
      MaskColor       =   &H00808080&
      TabIndex        =   8
      Top             =   1140
      Width           =   915
   End
   Begin VB.CommandButton ReadCntr 
      Caption         =   "Read"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      Index           =   0
      Left            =   10380
      MaskColor       =   &H00808080&
      TabIndex        =   3
      Top             =   720
      Width           =   915
   End
   Begin ComctlLib.Slider DAC 
      Height          =   555
      Index           =   0
      Left            =   1740
      TabIndex        =   0
      Top             =   600
      Width           =   2835
      _ExtentX        =   5001
      _ExtentY        =   979
      _Version        =   327682
      LargeChange     =   2
      Min             =   -10
      TickStyle       =   1
   End
   Begin ComctlLib.Slider DAC 
      Height          =   555
      Index           =   1
      Left            =   1740
      TabIndex        =   28
      Top             =   1200
      Width           =   2835
      _ExtentX        =   5001
      _ExtentY        =   979
      _Version        =   327682
      LargeChange     =   2
      Min             =   -10
      TickStyle       =   1
   End
   Begin ComctlLib.Slider DAC 
      Height          =   555
      Index           =   2
      Left            =   1740
      TabIndex        =   30
      Top             =   1800
      Width           =   2835
      _ExtentX        =   5001
      _ExtentY        =   979
      _Version        =   327682
      LargeChange     =   2
      Min             =   -10
      TickStyle       =   1
   End
   Begin ComctlLib.Slider DAC 
      Height          =   555
      Index           =   3
      Left            =   1740
      TabIndex        =   34
      Top             =   2400
      Width           =   2835
      _ExtentX        =   5001
      _ExtentY        =   979
      _Version        =   327682
      LargeChange     =   2
      Min             =   -10
      TickStyle       =   1
   End
   Begin ComctlLib.Slider DAC 
      Height          =   555
      Index           =   4
      Left            =   1740
      TabIndex        =   36
      Top             =   3000
      Width           =   2835
      _ExtentX        =   5001
      _ExtentY        =   979
      _Version        =   327682
      LargeChange     =   2
      Min             =   -10
      TickStyle       =   1
   End
   Begin ComctlLib.Slider DAC 
      Height          =   555
      Index           =   5
      Left            =   1740
      TabIndex        =   40
      Top             =   3600
      Width           =   2835
      _ExtentX        =   5001
      _ExtentY        =   979
      _Version        =   327682
      LargeChange     =   2
      Min             =   -10
      TickStyle       =   1
   End
   Begin ComctlLib.Slider DAC 
      Height          =   555
      Index           =   6
      Left            =   1740
      TabIndex        =   42
      Top             =   4200
      Width           =   2835
      _ExtentX        =   5001
      _ExtentY        =   979
      _Version        =   327682
      LargeChange     =   2
      Min             =   -10
      TickStyle       =   1
   End
   Begin ComctlLib.Slider DAC 
      Height          =   555
      Index           =   7
      Left            =   1740
      TabIndex        =   46
      Top             =   4800
      Width           =   2835
      _ExtentX        =   5001
      _ExtentY        =   979
      _Version        =   327682
      LargeChange     =   2
      Min             =   -10
      TickStyle       =   1
   End
   Begin VB.Label Label21 
      Caption         =   "milli volts"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FF0000&
      Height          =   375
      Left            =   8880
      TabIndex        =   65
      Top             =   7440
      Width           =   1215
   End
   Begin VB.Label Label20 
      AutoSize        =   -1  'True
      Caption         =   "ADC Ch7"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   345
      Left            =   6600
      TabIndex        =   64
      Top             =   7080
      Width           =   1260
   End
   Begin VB.Label lblADC 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00000000&
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H0000FF00&
      Height          =   315
      Index           =   7
      Left            =   8220
      TabIndex        =   63
      Top             =   7080
      Width           =   1875
   End
   Begin VB.Label Label19 
      AutoSize        =   -1  'True
      Caption         =   "ADC Ch6"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   345
      Left            =   6600
      TabIndex        =   62
      Top             =   6720
      Width           =   1260
   End
   Begin VB.Label lblADC 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00000000&
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H0000FF00&
      Height          =   315
      Index           =   6
      Left            =   8220
      TabIndex        =   61
      Top             =   6720
      Width           =   1875
   End
   Begin VB.Label Label18 
      AutoSize        =   -1  'True
      Caption         =   "ADC Ch5"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   345
      Left            =   6600
      TabIndex        =   60
      Top             =   6360
      Width           =   1260
   End
   Begin VB.Label lblADC 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00000000&
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H0000FF00&
      Height          =   315
      Index           =   5
      Left            =   8220
      TabIndex        =   59
      Top             =   6360
      Width           =   1875
   End
   Begin VB.Label Label17 
      AutoSize        =   -1  'True
      Caption         =   "ADC Ch4"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   345
      Left            =   6600
      TabIndex        =   58
      Top             =   6000
      Width           =   1260
   End
   Begin VB.Label lblADC 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00000000&
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H0000FF00&
      Height          =   315
      Index           =   4
      Left            =   8220
      TabIndex        =   57
      Top             =   6000
      Width           =   1875
   End
   Begin VB.Label Label16 
      AutoSize        =   -1  'True
      Caption         =   "ADC Ch3"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   345
      Left            =   6600
      TabIndex        =   56
      Top             =   5640
      Width           =   1260
   End
   Begin VB.Label lblADC 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00000000&
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H0000FF00&
      Height          =   315
      Index           =   3
      Left            =   8220
      TabIndex        =   55
      Top             =   5640
      Width           =   1875
   End
   Begin VB.Label Label15 
      AutoSize        =   -1  'True
      Caption         =   "ADC Ch2"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   345
      Left            =   6600
      TabIndex        =   54
      Top             =   5280
      Width           =   1260
   End
   Begin VB.Label lblADC 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00000000&
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H0000FF00&
      Height          =   315
      Index           =   2
      Left            =   8220
      TabIndex        =   53
      Top             =   5280
      Width           =   1875
   End
   Begin VB.Label Label14 
      AutoSize        =   -1  'True
      Caption         =   "ADC Ch1"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   345
      Left            =   6600
      TabIndex        =   52
      Top             =   4920
      Width           =   1260
   End
   Begin VB.Label lblADC 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00000000&
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H0000FF00&
      Height          =   315
      Index           =   1
      Left            =   8220
      TabIndex        =   51
      Top             =   4920
      Width           =   1875
   End
   Begin VB.Label lblADC 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00000000&
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H0000FF00&
      Height          =   315
      Index           =   0
      Left            =   8220
      TabIndex        =   50
      Top             =   4560
      Width           =   1875
   End
   Begin VB.Label Label13 
      AutoSize        =   -1  'True
      Caption         =   "ADC Ch0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   345
      Left            =   6600
      TabIndex        =   49
      Top             =   4560
      Width           =   1260
   End
   Begin VB.Label lblDAC 
      Alignment       =   1  'Right Justify
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000080&
      Height          =   315
      Index           =   7
      Left            =   4740
      TabIndex        =   47
      Top             =   4920
      Width           =   795
   End
   Begin VB.Label lblDAC 
      Alignment       =   1  'Right Justify
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000080&
      Height          =   315
      Index           =   6
      Left            =   4740
      TabIndex        =   45
      Top             =   4320
      Width           =   795
   End
   Begin VB.Label Label12 
      AutoSize        =   -1  'True
      Caption         =   "DAC 6:"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   345
      Index           =   1
      Left            =   480
      TabIndex        =   44
      Top             =   4320
      Width           =   960
   End
   Begin VB.Label Label11 
      AutoSize        =   -1  'True
      Caption         =   "DAC 7:"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   345
      Index           =   1
      Left            =   480
      TabIndex        =   43
      Top             =   4920
      Width           =   960
   End
   Begin VB.Label lblDAC 
      Alignment       =   1  'Right Justify
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000080&
      Height          =   315
      Index           =   5
      Left            =   4740
      TabIndex        =   41
      Top             =   3720
      Width           =   795
   End
   Begin VB.Label lblDAC 
      Alignment       =   1  'Right Justify
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000080&
      Height          =   315
      Index           =   4
      Left            =   4740
      TabIndex        =   39
      Top             =   3120
      Width           =   795
   End
   Begin VB.Label Label5 
      AutoSize        =   -1  'True
      Caption         =   "DAC 4:"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   345
      Index           =   1
      Left            =   480
      TabIndex        =   38
      Top             =   3120
      Width           =   960
   End
   Begin VB.Label Label6 
      AutoSize        =   -1  'True
      Caption         =   "DAC 5:"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   345
      Index           =   1
      Left            =   480
      TabIndex        =   37
      Top             =   3720
      Width           =   960
   End
   Begin VB.Label lblDAC 
      Alignment       =   1  'Right Justify
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000080&
      Height          =   315
      Index           =   3
      Left            =   4740
      TabIndex        =   35
      Top             =   2520
      Width           =   795
   End
   Begin VB.Label lblDAC 
      Alignment       =   1  'Right Justify
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000080&
      Height          =   315
      Index           =   2
      Left            =   4740
      TabIndex        =   33
      Top             =   1920
      Width           =   795
   End
   Begin VB.Label Label12 
      AutoSize        =   -1  'True
      Caption         =   "DAC 2:"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   345
      Index           =   0
      Left            =   480
      TabIndex        =   32
      Top             =   1920
      Width           =   960
   End
   Begin VB.Label Label11 
      AutoSize        =   -1  'True
      Caption         =   "DAC 3:"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   345
      Index           =   0
      Left            =   480
      TabIndex        =   31
      Top             =   2520
      Width           =   960
   End
   Begin VB.Label lblDAC 
      Alignment       =   1  'Right Justify
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000080&
      Height          =   315
      Index           =   1
      Left            =   4740
      TabIndex        =   29
      Top             =   1320
      Width           =   795
   End
   Begin VB.Label lblCounter 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00000000&
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H0000FF00&
      Height          =   315
      Index           =   7
      Left            =   8280
      TabIndex        =   27
      Top             =   3660
      Width           =   1875
   End
   Begin VB.Label lblCounter 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00000000&
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H0000FF00&
      Height          =   315
      Index           =   6
      Left            =   8280
      TabIndex        =   25
      Top             =   3240
      Width           =   1875
   End
   Begin VB.Label Label10 
      AutoSize        =   -1  'True
      Caption         =   "Counter 6:"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   345
      Left            =   6660
      TabIndex        =   24
      Top             =   3240
      Width           =   1455
   End
   Begin VB.Label Label9 
      AutoSize        =   -1  'True
      Caption         =   "Counter 7:"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   345
      Left            =   6660
      TabIndex        =   23
      Top             =   3660
      Width           =   1455
   End
   Begin VB.Label lblCounter 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00000000&
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H0000FF00&
      Height          =   315
      Index           =   5
      Left            =   8280
      TabIndex        =   21
      Top             =   2820
      Width           =   1875
   End
   Begin VB.Label lblCounter 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00000000&
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H0000FF00&
      Height          =   315
      Index           =   4
      Left            =   8280
      TabIndex        =   19
      Top             =   2400
      Width           =   1875
   End
   Begin VB.Label Label8 
      AutoSize        =   -1  'True
      Caption         =   "Counter 4:"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   345
      Left            =   6660
      TabIndex        =   18
      Top             =   2400
      Width           =   1455
   End
   Begin VB.Label Label7 
      AutoSize        =   -1  'True
      Caption         =   "Counter 5:"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   345
      Left            =   6660
      TabIndex        =   17
      Top             =   2820
      Width           =   1455
   End
   Begin VB.Label lblCounter 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00000000&
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H0000FF00&
      Height          =   315
      Index           =   3
      Left            =   8280
      TabIndex        =   15
      Top             =   1980
      Width           =   1875
   End
   Begin VB.Label lblCounter 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00000000&
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H0000FF00&
      Height          =   315
      Index           =   2
      Left            =   8280
      TabIndex        =   13
      Top             =   1560
      Width           =   1875
   End
   Begin VB.Label Label3 
      AutoSize        =   -1  'True
      Caption         =   "Counter 2:"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   345
      Left            =   6660
      TabIndex        =   12
      Top             =   1560
      Width           =   1455
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "Counter 3:"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   345
      Left            =   6660
      TabIndex        =   11
      Top             =   1980
      Width           =   1455
   End
   Begin VB.Label lblCounter 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00000000&
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H0000FF00&
      Height          =   315
      Index           =   1
      Left            =   8280
      TabIndex        =   9
      Top             =   1140
      Width           =   1875
   End
   Begin VB.Label lblDAC 
      Alignment       =   1  'Right Justify
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000080&
      Height          =   315
      Index           =   0
      Left            =   4740
      TabIndex        =   7
      Top             =   720
      Width           =   795
   End
   Begin VB.Label Label6 
      AutoSize        =   -1  'True
      Caption         =   "DAC 1:"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   345
      Index           =   0
      Left            =   480
      TabIndex        =   6
      Top             =   1320
      Width           =   960
   End
   Begin VB.Label Label5 
      AutoSize        =   -1  'True
      Caption         =   "DAC 0:"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   345
      Index           =   0
      Left            =   480
      TabIndex        =   5
      Top             =   720
      Width           =   960
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "Counter 1:"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   345
      Index           =   0
      Left            =   6660
      TabIndex        =   4
      Top             =   1140
      Width           =   1455
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      Caption         =   "Counter 0:"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   345
      Left            =   6660
      TabIndex        =   2
      Top             =   720
      Width           =   1455
   End
   Begin VB.Label lblCounter 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00000000&
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H0000FF00&
      Height          =   315
      Index           =   0
      Left            =   8280
      TabIndex        =   1
      Top             =   720
      Width           =   1875
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Form_Load()

    On Error GoTo DLL_NOT_FOUND
    
    If MotencVB.vitalInit = 0 Then
        MsgBox "MOTENC Driver Error. Board or DLL not found", vbCritical, "Driver Initialization"
    End If
    
    On Error GoTo 0
    
    Exit Sub
    
DLL_NOT_FOUND:
        MsgBox "MOTENC Driver DLL missing", vbCritical, "Driver Initialization"
        End
End Sub

Private Sub Form_Terminate()
    MotencVB.vitalQuit
End Sub

Private Sub Form_Unload(Cancel As Integer)
    MotencVB.vitalQuit
End Sub

Private Sub DAC_Change(Index As Integer)

    If MotencVB.vitalDacWrite(Index, DAC(Index).Value) = 1 Then
        lblDAC(Index) = DAC(Index).Value
    Else
        MsgBox "Error Writing to DAC " & Index
    End If

End Sub

Private Sub ReadADC_Click(Index As Integer)

    Dim ADCdata As Long
    
'    MotencVB.vitalReadReg 5, ADCdata
'
'    If ADCdata And &H40000 <> &H40000 Then
'        MsgBox "ADC Done Bit Active. aborting"
'        Exit Sub
'    End If
'
'    ' Start Conversion
'    MotencVB.vitalWriteReg 32, 0    'ch 0 only conversion
'    MotencVB.vitalWriteReg 40, 1    'start conversion
'
'    DoEvents
'
'    While ADCdata And &H40000 = &H40000
'        DoEvents
'    Wend
'
'    MotencVB.vitalReadReg 32, ADCdata
    
    Dim AnalogDat(4) As Double
    
    If MotencVB.vitalReadAnalogInputs(0, AnalogDat(0)) = 0 Then
        MsgBox "Error Reading Analog Inputs or J5"
        Exit Sub
    End If
    
    Me.lblADC(0) = AnalogDat(0)
    Me.lblADC(1) = AnalogDat(1)
    Me.lblADC(2) = AnalogDat(2)
    Me.lblADC(3) = AnalogDat(3)
        
    If MotencVB.vitalReadAnalogInputs(1, AnalogDat(0)) = 0 Then
        MsgBox "Error Reading Analog Inputs on J8"
        Exit Sub
    End If
    
    Me.lblADC(4) = AnalogDat(0)
    Me.lblADC(5) = AnalogDat(1)
    Me.lblADC(6) = AnalogDat(2)
    Me.lblADC(7) = AnalogDat(3)
        
End Sub

Private Sub ReadCntr_Click(Index As Integer)

    Dim Count As Long
    
    If MotencVB.vitalEncoderRead(Index, Count) = 0 Then
        MsgBox "Error Reading Encoder Counter " & Index
    End If
        
    Me.lblCounter(Index) = Count

End Sub
