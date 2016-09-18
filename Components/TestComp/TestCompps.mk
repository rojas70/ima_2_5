
TestCompps.dll: dlldata.obj TestComp_p.obj TestComp_i.obj
	link /dll /out:TestCompps.dll /def:TestCompps.def /entry:DllMain dlldata.obj TestComp_p.obj TestComp_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del TestCompps.dll
	@del TestCompps.lib
	@del TestCompps.exp
	@del dlldata.obj
	@del TestComp_p.obj
	@del TestComp_i.obj
