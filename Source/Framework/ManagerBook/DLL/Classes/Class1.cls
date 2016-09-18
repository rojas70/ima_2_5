VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Class1"
Attribute VB_GlobalNameSpace = True
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public Sub ShowManagerBook()

    If frmFile.Visible = False Then
        frmFile.Show
    End If

End Sub

Public Sub ShowManagerBookModal()

    If frmFile.Visible = False Then
       frmFile.Show vbModal
    End If

End Sub

