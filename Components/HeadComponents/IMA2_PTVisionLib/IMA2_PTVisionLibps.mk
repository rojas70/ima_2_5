
IMA2_PTVisionLibps.dll: dlldata.obj IMA2_PTVisionLib_p.obj IMA2_PTVisionLib_i.obj
	link /dll /out:IMA2_PTVisionLibps.dll /def:IMA2_PTVisionLibps.def /entry:DllMain dlldata.obj IMA2_PTVisionLib_p.obj IMA2_PTVisionLib_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del IMA2_PTVisionLibps.dll
	@del IMA2_PTVisionLibps.lib
	@del IMA2_PTVisionLibps.exp
	@del dlldata.obj
	@del IMA2_PTVisionLib_p.obj
	@del IMA2_PTVisionLib_i.obj
