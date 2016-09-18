Attribute VB_Name = "modMain"
Option Explicit

    'Global g_EventQueue     As CEventQueue              'Our global pointer to the event pump.
    Global g_Clients        As New IndexedArray             'Array of event subscribers.
    

