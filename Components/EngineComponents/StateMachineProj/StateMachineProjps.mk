
StateMachineProjps.dll: dlldata.obj StateMachineProj_p.obj StateMachineProj_i.obj
	link /dll /out:StateMachineProjps.dll /def:StateMachineProjps.def /entry:DllMain dlldata.obj StateMachineProj_p.obj StateMachineProj_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del StateMachineProjps.dll
	@del StateMachineProjps.lib
	@del StateMachineProjps.exp
	@del dlldata.obj
	@del StateMachineProj_p.obj
	@del StateMachineProj_i.obj
