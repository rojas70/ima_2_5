mkdir C:\IMA2
mkdir C:\IMA2\Components
mkdir C:\IMA2\Configuration
mkdir C:\IMA2\Demos
mkdir C:\IMA2\Icons
mkdir C:\IMA2\Managers
copy Components\*.dll C:\IMA2\Components\*.dll /Y
copy Components\IMA2_Agent.exe C:\IMA2\Components\IMA2_Agent.exe /Y
copy Configuration\*.* C:\IMA2\Configuration\*.* /Y
copy Demos\*.* C:\IMA2\Demos\*.* /Y
copy Icons\*.* C:\IMA2\Icons\*.* /Y
copy Managers\*.ocx C:\IMA2\Managers\*.ocx /Y
xcopy System C:\IMA2\System /E /I /Y
copy *.bat C:\IMA2\*.bat /Y

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
IMA2_Agent.exe /regserver
IMA2_Locator.exe /regserver
IMA2_InfoService.exe /regserver
IMA2_EventService.exe /regserver
regsvr32 IMA2_HelperX.ocx /s

CD ..
CD Third Party
for %%F in (*.TLB) do ..\Applications\regtlib %%F -q
for %%F in (*.DLL) do regsvr32 %%F /s
for %%F in (*.EXE) do %%F /regserver

CD ..
CD ..

regsvr32 O:\Include\IMA2_PropertyBags.dll /s
copy O:\Components\SES\mysql++\mysql\lib\libmySQL.dll %SystemRoot%\System32\libmySQL.dll /Y
regsvr32 %SystemRoot%\System32\libmySQL.dll /s

mkdir C:\IMA2\Source\Compatibility\Framework
copy Source\Compatibility\Framework\IMA2_DADX.ocx C:\IMA2\Source\Compatibility\Framework\IMA2_DADX.ocx
"D:\Program Files\Microsoft Visual Studio\VB98\vb6" O:\Source\Framework\DADX\IMA2_DADX.vbp /m C:\IMA2\System\Framework\IMA2_DADX.ocx /out C:\IMA2\copylog.txt
regsvr32 C:\IMA2\System\Framework\IMA2_DADX.ocx /s
rmdir C:\IMA2\Source /s /q
"D:\Program Files\Microsoft Visual Studio\VB98\vb6" O:\Source\Framework\DAD\IMA2_DAD.vbp /m C:\IMA2\System\Framework\IMA2_DAD.exe /out C:\IMA2\copylog.txt
C:\IMA2\System\Framework\IMA2_DAD.exe /regserver
"D:\Program Files\Microsoft Visual Studio\VB98\vb6" O:\Source\Framework\ManagerBook\DLL\ManagerBook.vbp /m C:\IMA2\System\Framework\IMA2_ManagerBook.exe /out C:\IMA2\copylog.txt
C:\IMA2\System\Framework\IMA2_ManagerBook.exe /regserver



