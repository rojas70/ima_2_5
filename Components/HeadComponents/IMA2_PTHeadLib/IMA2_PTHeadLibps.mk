
IMA2_PTHeadLibps.dll: dlldata.obj IMA2_PTHeadLib_p.obj IMA2_PTHeadLib_i.obj
	link /dll /out:IMA2_PTHeadLibps.dll /def:IMA2_PTHeadLibps.def /entry:DllMain dlldata.obj IMA2_PTHeadLib_p.obj IMA2_PTHeadLib_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del IMA2_PTHeadLibps.dll
	@del IMA2_PTHeadLibps.lib
	@del IMA2_PTHeadLibps.exp
	@del dlldata.obj
	@del IMA2_PTHeadLib_p.obj
	@del IMA2_PTHeadLib_i.obj
