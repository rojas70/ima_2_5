
IMA2_HP3JCAssemblyPositionLibps.dll: dlldata.obj IMA2_HP3JCAssemblyPositionLib_p.obj IMA2_HP3JCAssemblyPositionLib_i.obj
	link /dll /out:IMA2_HP3JCAssemblyPositionLibps.dll /def:IMA2_HP3JCAssemblyPositionLibps.def /entry:DllMain dlldata.obj IMA2_HP3JCAssemblyPositionLib_p.obj IMA2_HP3JCAssemblyPositionLib_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del IMA2_HP3JCAssemblyPositionLibps.dll
	@del IMA2_HP3JCAssemblyPositionLibps.lib
	@del IMA2_HP3JCAssemblyPositionLibps.exp
	@del dlldata.obj
	@del IMA2_HP3JCAssemblyPositionLib_p.obj
	@del IMA2_HP3JCAssemblyPositionLib_i.obj
