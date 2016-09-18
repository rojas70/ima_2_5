
IMA2_SESLibps.dll: dlldata.obj IMA2_SESLib_p.obj IMA2_SESLib_i.obj
	link /dll /out:IMA2_SESLibps.dll /def:IMA2_SESLibps.def /entry:DllMain dlldata.obj IMA2_SESLib_p.obj IMA2_SESLib_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del IMA2_SESLibps.dll
	@del IMA2_SESLibps.lib
	@del IMA2_SESLibps.exp
	@del dlldata.obj
	@del IMA2_SESLib_p.obj
	@del IMA2_SESLib_i.obj
