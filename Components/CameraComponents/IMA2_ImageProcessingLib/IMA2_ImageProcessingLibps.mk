
IMA2_ImageProcessingLibps.dll: dlldata.obj IMA2_ImageProcessingLib_p.obj IMA2_ImageProcessingLib_i.obj
	link /dll /out:IMA2_ImageProcessingLibps.dll /def:IMA2_ImageProcessingLibps.def /entry:DllMain dlldata.obj IMA2_ImageProcessingLib_p.obj IMA2_ImageProcessingLib_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del IMA2_ImageProcessingLibps.dll
	@del IMA2_ImageProcessingLibps.lib
	@del IMA2_ImageProcessingLibps.exp
	@del dlldata.obj
	@del IMA2_ImageProcessingLib_p.obj
	@del IMA2_ImageProcessingLib_i.obj
