
IMA2_CaptureManagerps.dll: dlldata.obj IMA2_CaptureManager_p.obj IMA2_CaptureManager_i.obj
	link /dll /out:IMA2_CaptureManagerps.dll /def:IMA2_CaptureManagerps.def /entry:DllMain dlldata.obj IMA2_CaptureManager_p.obj IMA2_CaptureManager_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del IMA2_CaptureManagerps.dll
	@del IMA2_CaptureManagerps.lib
	@del IMA2_CaptureManagerps.exp
	@del dlldata.obj
	@del IMA2_CaptureManager_p.obj
	@del IMA2_CaptureManager_i.obj
