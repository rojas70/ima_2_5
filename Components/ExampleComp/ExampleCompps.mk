
ExampleCompps.dll: dlldata.obj ExampleComp_p.obj ExampleComp_i.obj
	link /dll /out:ExampleCompps.dll /def:ExampleCompps.def /entry:DllMain dlldata.obj ExampleComp_p.obj ExampleComp_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del ExampleCompps.dll
	@del ExampleCompps.lib
	@del ExampleCompps.exp
	@del dlldata.obj
	@del ExampleComp_p.obj
	@del ExampleComp_i.obj
