CD Components
for %%F in (*.TLB) do ..\System\Applications\regtlib %%F -q
for %%F in (*.DLL) do regsvr32 %%F /s
for %%F in (*.EXE) do %%F /regserver


CD ..
CD Managers
for %%F in (*.TLB) do ..\System\Applications\regtlib %%F -q
for %%F in (*.DLL) do regsvr32 %%F /s
for %%F in (*.OCX) do regsvr32 %%F /s
for %%F in (*.EXE) do %%F /regserver

CD ..
CD System
CD Framework
for %%F in (*.TLB) do ..\Applications\regtlib %%F -q
for %%F in (*.DLL) do regsvr32 %%F /s
regsvr32 IMA2_HelperX.ocx /s
regsvr32 IMA2_DADX.ocx /s
IMA2_Agent.exe /regserver
IMA2_Locator.exe /regserver
IMA2_InfoService.exe /regserver
IMA2_EventService.exe /regserver
IMA2_DAD.exe /regserver
IMA2_ManagerBook.exe /regserver

CD ..
CD Third Party
for %%F in (*.TLB) do ..\Applications\regtlib %%F -q
for %%F in (*.DLL) do regsvr32 %%F /s
for %%F in (*.EXE) do %%F /regserver

CD ..
CD ..

regsvr32 O:\Include\IMA2_PropertyBags.dll /s