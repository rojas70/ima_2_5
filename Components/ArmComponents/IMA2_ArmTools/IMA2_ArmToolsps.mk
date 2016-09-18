
IMA2_ArmToolsps.dll: dlldata.obj IMA2_ArmTools_p.obj IMA2_ArmTools_i.obj
	link /dll /out:IMA2_ArmToolsps.dll /def:IMA2_ArmToolsps.def /entry:DllMain dlldata.obj IMA2_ArmTools_p.obj IMA2_ArmTools_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del IMA2_ArmToolsps.dll
	@del IMA2_ArmToolsps.lib
	@del IMA2_ArmToolsps.exp
	@del dlldata.obj
	@del IMA2_ArmTools_p.obj
	@del IMA2_ArmTools_i.obj
