
IMA2_TrajectoryLibps.dll: dlldata.obj IMA2_TrajectoryLib_p.obj IMA2_TrajectoryLib_i.obj
	link /dll /out:IMA2_TrajectoryLibps.dll /def:IMA2_TrajectoryLibps.def /entry:DllMain dlldata.obj IMA2_TrajectoryLib_p.obj IMA2_TrajectoryLib_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del IMA2_TrajectoryLibps.dll
	@del IMA2_TrajectoryLibps.lib
	@del IMA2_TrajectoryLibps.exp
	@del dlldata.obj
	@del IMA2_TrajectoryLib_p.obj
	@del IMA2_TrajectoryLib_i.obj
