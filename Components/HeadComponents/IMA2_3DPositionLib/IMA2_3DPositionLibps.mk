
IMA2_3DPositionLibps.dll: dlldata.obj IMA2_3DPositionLib_p.obj IMA2_3DPositionLib_i.obj
	link /dll /out:IMA2_3DPositionLibps.dll /def:IMA2_3DPositionLibps.def /entry:DllMain dlldata.obj IMA2_3DPositionLib_p.obj IMA2_3DPositionLib_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del IMA2_3DPositionLibps.dll
	@del IMA2_3DPositionLibps.lib
	@del IMA2_3DPositionLibps.exp
	@del dlldata.obj
	@del IMA2_3DPositionLib_p.obj
	@del IMA2_3DPositionLib_i.obj
