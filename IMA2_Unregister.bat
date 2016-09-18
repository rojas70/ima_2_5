CD System
CD Framework

for %%F in (*.DLL) do regsvr32 %%F /u /s
for %%F in (*.OCX) do regsvr32 %%F /u /s
IMA2_Agent.exe /unregserver
IMA2_Locator.exe /unregserver
IMA2_InfoService.exe /unregserver
IMA2_EventService.exe /unregserver
IMA2_DAD.exe /unregserver
IMA2_ManagerBook.exe /unregserver

CD ..
CD ..
CD Components

for %%F in (*.DLL) do regsvr32 %%F /u /s
for %%F in (*.EXE) do %%F /unregserver

CD ..
CD Managers

for %%F in (*.DLL) do regsvr32 %%F /u /s
for %%F in (*.OCX) do regsvr32 %%F /u /s
for %%F in (*.EXE) do %%F /unregserver

CD ..

regsvr32 O:\Include\IMA2_PropertyBags.dll /u /s