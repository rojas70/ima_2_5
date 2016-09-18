
IMA2_CopyRepsLibps.dll: dlldata.obj IMA2_CopyRepsLib_p.obj IMA2_CopyRepsLib_i.obj
	link /dll /out:IMA2_CopyRepsLibps.dll /def:IMA2_CopyRepsLibps.def /entry:DllMain dlldata.obj IMA2_CopyRepsLib_p.obj IMA2_CopyRepsLib_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del IMA2_CopyRepsLibps.dll
	@del IMA2_CopyRepsLibps.lib
	@del IMA2_CopyRepsLibps.exp
	@del dlldata.obj
	@del IMA2_CopyRepsLib_p.obj
	@del IMA2_CopyRepsLib_i.obj
