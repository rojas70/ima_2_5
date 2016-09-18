
IMA2_BarretLibps.dll: dlldata.obj IMA2_BarretLib_p.obj IMA2_BarretLib_i.obj
	link /dll /out:IMA2_BarretLibps.dll /def:IMA2_BarretLibps.def /entry:DllMain dlldata.obj IMA2_BarretLib_p.obj IMA2_BarretLib_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del IMA2_BarretLibps.dll
	@del IMA2_BarretLibps.lib
	@del IMA2_BarretLibps.exp
	@del dlldata.obj
	@del IMA2_BarretLib_p.obj
	@del IMA2_BarretLib_i.obj
