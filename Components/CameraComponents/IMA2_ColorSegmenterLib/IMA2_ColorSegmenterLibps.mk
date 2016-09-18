
IMA2_ColorSegmenterLibps.dll: dlldata.obj IMA2_ColorSegmenterLib_p.obj IMA2_ColorSegmenterLib_i.obj
	link /dll /out:IMA2_ColorSegmenterLibps.dll /def:IMA2_ColorSegmenterLibps.def /entry:DllMain dlldata.obj IMA2_ColorSegmenterLib_p.obj IMA2_ColorSegmenterLib_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del IMA2_ColorSegmenterLibps.dll
	@del IMA2_ColorSegmenterLibps.lib
	@del IMA2_ColorSegmenterLibps.exp
	@del dlldata.obj
	@del IMA2_ColorSegmenterLib_p.obj
	@del IMA2_ColorSegmenterLib_i.obj
