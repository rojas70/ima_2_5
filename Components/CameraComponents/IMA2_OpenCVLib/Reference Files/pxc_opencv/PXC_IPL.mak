# Microsoft Developer Studio Generated NMAKE File, Based on PXC_IPL.dsp
!IF "$(CFG)" == ""
CFG=PXC_IPL - Win32 Debug
!MESSAGE No configuration specified. Defaulting to PXC_IPL - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "PXC_IPL - Win32 Release" && "$(CFG)" != "PXC_IPL - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PXC_IPL.mak" CFG="PXC_IPL - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PXC_IPL - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "PXC_IPL - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PXC_IPL - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\PXC_IPL.exe"


CLEAN :
	-@erase "$(INTDIR)\dlg_main.res"
	-@erase "$(INTDIR)\pxc_display.obj"
	-@erase "$(INTDIR)\pxc_ipl.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\PXC_IPL.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "c:\Program Files\Intel\plsuite\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\PXC_IPL.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\dlg_main.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\PXC_IPL.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=cv.lib ipl.lib ilib_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\PXC_IPL.pdb" /machine:I386 /out:"$(OUTDIR)\PXC_IPL.exe" /libpath:"C:\PROGRAM FILES\INTEL\PLSUITE\LIB\MSVC" 
LINK32_OBJS= \
	"$(INTDIR)\pxc_display.obj" \
	"$(INTDIR)\pxc_ipl.obj" \
	"$(INTDIR)\dlg_main.res"

"$(OUTDIR)\PXC_IPL.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "PXC_IPL - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\PXC_IPL.exe"


CLEAN :
	-@erase "$(INTDIR)\dlg_main.res"
	-@erase "$(INTDIR)\pxc_display.obj"
	-@erase "$(INTDIR)\pxc_ipl.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\PXC_IPL.exe"
	-@erase "$(OUTDIR)\PXC_IPL.ilk"
	-@erase "$(OUTDIR)\PXC_IPL.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "c:\Program Files\Intel\plsuite\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\PXC_IPL.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\dlg_main.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\PXC_IPL.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=cv.lib ipl.lib ilib_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\PXC_IPL.pdb" /debug /machine:I386 /out:"$(OUTDIR)\PXC_IPL.exe" /pdbtype:sept /libpath:"C:\PROGRAM FILES\INTEL\PLSUITE\LIB\MSVC" 
LINK32_OBJS= \
	"$(INTDIR)\pxc_display.obj" \
	"$(INTDIR)\pxc_ipl.obj" \
	"$(INTDIR)\dlg_main.res"

"$(OUTDIR)\PXC_IPL.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("PXC_IPL.dep")
!INCLUDE "PXC_IPL.dep"
!ELSE 
!MESSAGE Warning: cannot find "PXC_IPL.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "PXC_IPL - Win32 Release" || "$(CFG)" == "PXC_IPL - Win32 Debug"
SOURCE=.\pxc_display.c

"$(INTDIR)\pxc_display.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\pxc_ipl.c

"$(INTDIR)\pxc_ipl.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\dlg_main.rc

"$(INTDIR)\dlg_main.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

