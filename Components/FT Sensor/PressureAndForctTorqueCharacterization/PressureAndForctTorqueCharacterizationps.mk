
PressureAndForctTorqueCharacterizationps.dll: dlldata.obj PressureAndForctTorqueCharacterization_p.obj PressureAndForctTorqueCharacterization_i.obj
	link /dll /out:PressureAndForctTorqueCharacterizationps.dll /def:PressureAndForctTorqueCharacterizationps.def /entry:DllMain dlldata.obj PressureAndForctTorqueCharacterization_p.obj PressureAndForctTorqueCharacterization_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del PressureAndForctTorqueCharacterizationps.dll
	@del PressureAndForctTorqueCharacterizationps.lib
	@del PressureAndForctTorqueCharacterizationps.exp
	@del dlldata.obj
	@del PressureAndForctTorqueCharacterization_p.obj
	@del PressureAndForctTorqueCharacterization_i.obj
