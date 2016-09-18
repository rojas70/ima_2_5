
IMA2_SESManagerps.dll: dlldata.obj IMA2_SESManager_p.obj IMA2_SESManager_i.obj
	link /dll /out:IMA2_SESManagerps.dll /def:IMA2_SESManagerps.def /entry:DllMain dlldata.obj IMA2_SESManager_p.obj IMA2_SESManager_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del IMA2_SESManagerps.dll
	@del IMA2_SESManagerps.lib
	@del IMA2_SESManagerps.exp
	@del dlldata.obj
	@del IMA2_SESManager_p.obj
	@del IMA2_SESManager_i.obj
