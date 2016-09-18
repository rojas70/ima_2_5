
IMA2_FrameGrabberLibps.dll: dlldata.obj IMA2_FrameGrabberLib_p.obj IMA2_FrameGrabberLib_i.obj
	link /dll /out:IMA2_FrameGrabberLibps.dll /def:IMA2_FrameGrabberLibps.def /entry:DllMain dlldata.obj IMA2_FrameGrabberLib_p.obj IMA2_FrameGrabberLib_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del IMA2_FrameGrabberLibps.dll
	@del IMA2_FrameGrabberLibps.lib
	@del IMA2_FrameGrabberLibps.exp
	@del dlldata.obj
	@del IMA2_FrameGrabberLib_p.obj
	@del IMA2_FrameGrabberLib_i.obj
