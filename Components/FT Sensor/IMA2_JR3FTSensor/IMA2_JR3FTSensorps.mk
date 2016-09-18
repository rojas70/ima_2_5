
IMA2_JR3FTSensorps.dll: dlldata.obj IMA2_JR3FTSensor_p.obj IMA2_JR3FTSensor_i.obj
	link /dll /out:IMA2_JR3FTSensorps.dll /def:IMA2_JR3FTSensorps.def /entry:DllMain dlldata.obj IMA2_JR3FTSensor_p.obj IMA2_JR3FTSensor_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del IMA2_JR3FTSensorps.dll
	@del IMA2_JR3FTSensorps.lib
	@del IMA2_JR3FTSensorps.exp
	@del dlldata.obj
	@del IMA2_JR3FTSensor_p.obj
	@del IMA2_JR3FTSensor_i.obj
