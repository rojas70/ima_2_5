
IMA2_TextQueueLibps.dll: dlldata.obj IMA2_TextQueueLib_p.obj IMA2_TextQueueLib_i.obj
	link /dll /out:IMA2_TextQueueLibps.dll /def:IMA2_TextQueueLibps.def /entry:DllMain dlldata.obj IMA2_TextQueueLib_p.obj IMA2_TextQueueLib_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del IMA2_TextQueueLibps.dll
	@del IMA2_TextQueueLibps.lib
	@del IMA2_TextQueueLibps.exp
	@del dlldata.obj
	@del IMA2_TextQueueLib_p.obj
	@del IMA2_TextQueueLib_i.obj
