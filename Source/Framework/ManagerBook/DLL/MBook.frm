VERSION 5.00
Begin VB.MDIForm MgrBook 
   BackColor       =   &H8000000C&
   Caption         =   "MDIForm1"
   ClientHeight    =   6090
   ClientLeft      =   165
   ClientTop       =   735
   ClientWidth     =   8355
   LinkTopic       =   "MDIForm1"
   StartUpPosition =   3  'Windows Default
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuFile_New 
         Caption         =   "&New"
      End
   End
End
Attribute VB_Name = "MgrBook"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim m_Children As New Collection

Private Sub mnuFile_New_Click()

    Dim F As frmFile
    
    Set F = New frmFile
    
    m_Children.Add F
    
    F.Show

End Sub
