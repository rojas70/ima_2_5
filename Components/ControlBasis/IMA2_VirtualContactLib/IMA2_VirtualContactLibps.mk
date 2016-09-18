
IMA2_VirtualContactLibps.dll: dlldata.obj IMA2_VirtualContactLib_p.obj IMA2_VirtualContactLib_i.obj
	link /dll /out:IMA2_VirtualContactLibps.dll /def:IMA2_VirtualContactLibps.def /entry:DllMain dlldata.obj IMA2_VirtualContactLib_p.obj IMA2_VirtualContactLib_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del IMA2_VirtualContactLibps.dll
	@del IMA2_VirtualContactLibps.lib
	@del IMA2_VirtualContactLibps.exp
	@del dlldata.obj
	@del IMA2_VirtualContactLib_p.obj
	@del IMA2_VirtualContactLib_i.obj
