
IMA2_MotomanLibps.dll: dlldata.obj IMA2_MotomanLib_p.obj IMA2_MotomanLib_i.obj
	link /dll /out:IMA2_MotomanLibps.dll /def:IMA2_MotomanLibps.def /entry:DllMain dlldata.obj IMA2_MotomanLib_p.obj IMA2_MotomanLib_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del IMA2_MotomanLibps.dll
	@del IMA2_MotomanLibps.lib
	@del IMA2_MotomanLibps.exp
	@del dlldata.obj
	@del IMA2_MotomanLib_p.obj
	@del IMA2_MotomanLib_i.obj
