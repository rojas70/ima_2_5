
IMA2_FTSensorLibps.dll: dlldata.obj IMA2_FTSensorLib_p.obj IMA2_FTSensorLib_i.obj
	link /dll /out:IMA2_FTSensorLibps.dll /def:IMA2_FTSensorLibps.def /entry:DllMain dlldata.obj IMA2_FTSensorLib_p.obj IMA2_FTSensorLib_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del IMA2_FTSensorLibps.dll
	@del IMA2_FTSensorLibps.lib
	@del IMA2_FTSensorLibps.exp
	@del dlldata.obj
	@del IMA2_FTSensorLib_p.obj
	@del IMA2_FTSensorLib_i.obj
