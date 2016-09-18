
trialps.dll: dlldata.obj trial_p.obj trial_i.obj
	link /dll /out:trialps.dll /def:trialps.def /entry:DllMain dlldata.obj trial_p.obj trial_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del trialps.dll
	@del trialps.lib
	@del trialps.exp
	@del dlldata.obj
	@del trial_p.obj
	@del trial_i.obj
