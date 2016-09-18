
IMA2_BasicComponentsLibps.dll: dlldata.obj IMA2_BasicComponentsLib_p.obj IMA2_BasicComponentsLib_i.obj
	link /dll /out:IMA2_BasicComponentsLibps.dll /def:IMA2_BasicComponentsLibps.def /entry:DllMain dlldata.obj IMA2_BasicComponentsLib_p.obj IMA2_BasicComponentsLib_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del IMA2_BasicComponentsLibps.dll
	@del IMA2_BasicComponentsLibps.lib
	@del IMA2_BasicComponentsLibps.exp
	@del dlldata.obj
	@del IMA2_BasicComponentsLib_p.obj
	@del IMA2_BasicComponentsLib_i.obj
