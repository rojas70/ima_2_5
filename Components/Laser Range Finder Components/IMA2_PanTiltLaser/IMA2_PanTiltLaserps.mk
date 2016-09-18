
IMA2_PanTiltLaserps.dll: dlldata.obj IMA2_PanTiltLaser_p.obj IMA2_PanTiltLaser_i.obj
	link /dll /out:IMA2_PanTiltLaserps.dll /def:IMA2_PanTiltLaserps.def /entry:DllMain dlldata.obj IMA2_PanTiltLaser_p.obj IMA2_PanTiltLaser_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del IMA2_PanTiltLaserps.dll
	@del IMA2_PanTiltLaserps.lib
	@del IMA2_PanTiltLaserps.exp
	@del dlldata.obj
	@del IMA2_PanTiltLaser_p.obj
	@del IMA2_PanTiltLaser_i.obj
