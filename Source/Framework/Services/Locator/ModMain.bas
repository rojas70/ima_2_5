Attribute VB_Name = "ModMain"
Option Explicit
Dim g_LF As LocatorFinder

Public Sub Main()
    On Error Resume Next
    Dim IC As IComponent
    Dim IL As ILocator
    
    Set g_LF = CreateObject("IMA2_LocatorFinder.LocatorFinder", "POPEYE")
    If Err Then
        MsgBox Err.Description, vbOKOnly Or vbCritical, "Could not create LocatorFinder"
        Err.Clear
        
        Set IL = CreateObject("IMA2_Locator.Locator", "POPEYE")
        Debug.Print IL.Machine
        
        Set IC = IL.Locate("\\" & IL.Machine)
        Debug.Print IC.Distributing.Process
        Exit Sub
    End If
    
    Set IL = g_LF.Locator
    Debug.Print IL.Machine
    
    Set IC = IL.Locate("\\" & IL.Machine)
    Debug.Print IC.Distributing.Process
    
End Sub
