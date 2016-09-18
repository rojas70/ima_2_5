
IMA2_DynamicRepsLibps.dll: dlldata.obj IMA2_DynamicRepsLib_p.obj IMA2_DynamicRepsLib_i.obj
	link /dll /out:IMA2_DynamicRepsLibps.dll /def:IMA2_DynamicRepsLibps.def /entry:DllMain dlldata.obj IMA2_DynamicRepsLib_p.obj IMA2_DynamicRepsLib_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del IMA2_DynamicRepsLibps.dll
	@del IMA2_DynamicRepsLibps.lib
	@del IMA2_DynamicRepsLibps.exp
	@del dlldata.obj
	@del IMA2_DynamicRepsLib_p.obj
	@del IMA2_DynamicRepsLib_i.obj
