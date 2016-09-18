
IMA2_ControlBasisLibps.dll: dlldata.obj IMA2_ControlBasisLib_p.obj IMA2_ControlBasisLib_i.obj
	link /dll /out:IMA2_ControlBasisLibps.dll /def:IMA2_ControlBasisLibps.def /entry:DllMain dlldata.obj IMA2_ControlBasisLib_p.obj IMA2_ControlBasisLib_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del IMA2_ControlBasisLibps.dll
	@del IMA2_ControlBasisLibps.lib
	@del IMA2_ControlBasisLibps.exp
	@del dlldata.obj
	@del IMA2_ControlBasisLib_p.obj
	@del IMA2_ControlBasisLib_i.obj
