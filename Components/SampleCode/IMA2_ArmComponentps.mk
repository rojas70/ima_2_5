
IMA2_ArmComponentps.dll: dlldata.obj IMA2_ArmComponent_p.obj IMA2_ArmComponent_i.obj
	link /dll /out:IMA2_ArmComponentps.dll /def:IMA2_ArmComponentps.def /entry:DllMain dlldata.obj IMA2_ArmComponent_p.obj IMA2_ArmComponent_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del IMA2_ArmComponentps.dll
	@del IMA2_ArmComponentps.lib
	@del IMA2_ArmComponentps.exp
	@del dlldata.obj
	@del IMA2_ArmComponent_p.obj
	@del IMA2_ArmComponent_i.obj
