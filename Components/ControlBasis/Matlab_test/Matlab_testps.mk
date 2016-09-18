
Matlab_testps.dll: dlldata.obj Matlab_test_p.obj Matlab_test_i.obj
	link /dll /out:Matlab_testps.dll /def:Matlab_testps.def /entry:DllMain dlldata.obj Matlab_test_p.obj Matlab_test_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del Matlab_testps.dll
	@del Matlab_testps.lib
	@del Matlab_testps.exp
	@del dlldata.obj
	@del Matlab_test_p.obj
	@del Matlab_test_i.obj
