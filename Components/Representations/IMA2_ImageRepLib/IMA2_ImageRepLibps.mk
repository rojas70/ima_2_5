
IMA2_ImageRepLibps.dll: dlldata.obj IMA2_ImageRepLib_p.obj IMA2_ImageRepLib_i.obj
	link /dll /out:IMA2_ImageRepLibps.dll /def:IMA2_ImageRepLibps.def /entry:DllMain dlldata.obj IMA2_ImageRepLib_p.obj IMA2_ImageRepLib_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del IMA2_ImageRepLibps.dll
	@del IMA2_ImageRepLibps.lib
	@del IMA2_ImageRepLibps.exp
	@del dlldata.obj
	@del IMA2_ImageRepLib_p.obj
	@del IMA2_ImageRepLib_i.obj
