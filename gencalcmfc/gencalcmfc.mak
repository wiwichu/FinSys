# Microsoft Developer Studio Generated NMAKE File, Based on gencalcmfc.dsp
!IF "$(CFG)" == ""
CFG=gencalcmfc - Win32 Debug
!MESSAGE No configuration specified. Defaulting to gencalcmfc - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "gencalcmfc - Win32 Release" && "$(CFG)" !=\
 "gencalcmfc - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gencalcmfc.mak" CFG="gencalcmfc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gencalcmfc - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "gencalcmfc - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "gencalcmfc - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\gencalcmfc.exe"

!ELSE 

ALL : "$(OUTDIR)\gencalcmfc.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\BondCalcScreen.obj"
	-@erase "$(INTDIR)\BondCalcWnd.obj"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\Classdef.obj"
	-@erase "$(INTDIR)\Coupload.obj"
	-@erase "$(INTDIR)\Datefunc.obj"
	-@erase "$(INTDIR)\DB.obj"
	-@erase "$(INTDIR)\Errproc.obj"
	-@erase "$(INTDIR)\Errtext.obj"
	-@erase "$(INTDIR)\Excoup.obj"
	-@erase "$(INTDIR)\gencalcmfc.obj"
	-@erase "$(INTDIR)\gencalcmfc.pch"
	-@erase "$(INTDIR)\gencalcmfc.res"
	-@erase "$(INTDIR)\gencalcmfcDoc.obj"
	-@erase "$(INTDIR)\gencalcmfcView.obj"
	-@erase "$(INTDIR)\Holidays.obj"
	-@erase "$(INTDIR)\HOLIx.obj"
	-@erase "$(INTDIR)\Intcalc.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Nom_adj.obj"
	-@erase "$(INTDIR)\Py_calc.obj"
	-@erase "$(INTDIR)\Pyfront.obj"
	-@erase "$(INTDIR)\Quick_Dates.obj"
	-@erase "$(INTDIR)\RateCurve.obj"
	-@erase "$(INTDIR)\RateCurvesScreen.obj"
	-@erase "$(INTDIR)\Redmpadj.obj"
	-@erase "$(INTDIR)\Redmparr.obj"
	-@erase "$(INTDIR)\Schedgen.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\gencalcmfc.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /Fp"$(INTDIR)\gencalcmfc.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\gencalcmfc.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\gencalcmfc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\gencalcmfc.pdb" /machine:I386 /out:"$(OUTDIR)\gencalcmfc.exe" 
LINK32_OBJS= \
	"$(INTDIR)\BondCalcScreen.obj" \
	"$(INTDIR)\BondCalcWnd.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\Classdef.obj" \
	"$(INTDIR)\Coupload.obj" \
	"$(INTDIR)\Datefunc.obj" \
	"$(INTDIR)\DB.obj" \
	"$(INTDIR)\Errproc.obj" \
	"$(INTDIR)\Errtext.obj" \
	"$(INTDIR)\Excoup.obj" \
	"$(INTDIR)\gencalcmfc.obj" \
	"$(INTDIR)\gencalcmfc.res" \
	"$(INTDIR)\gencalcmfcDoc.obj" \
	"$(INTDIR)\gencalcmfcView.obj" \
	"$(INTDIR)\Holidays.obj" \
	"$(INTDIR)\HOLIx.obj" \
	"$(INTDIR)\Intcalc.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Nom_adj.obj" \
	"$(INTDIR)\Py_calc.obj" \
	"$(INTDIR)\Pyfront.obj" \
	"$(INTDIR)\Quick_Dates.obj" \
	"$(INTDIR)\RateCurve.obj" \
	"$(INTDIR)\RateCurvesScreen.obj" \
	"$(INTDIR)\Redmpadj.obj" \
	"$(INTDIR)\Redmparr.obj" \
	"$(INTDIR)\Schedgen.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"..\..\..\..\oledbsdk\lib\Adoid.lib" \
	"..\..\..\..\oledbsdk\lib\Oledb.lib" \
	"..\..\..\..\oledbsdk\lib\Oledbd.lib" \
	"..\..\Vc\lib\Odbc32.lib"

"$(OUTDIR)\gencalcmfc.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "gencalcmfc - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\gencalcmfc.exe" "$(OUTDIR)\gencalcmfc.pch"\
 "$(OUTDIR)\gencalcmfc.bsc"

!ELSE 

ALL : "$(OUTDIR)\gencalcmfc.exe" "$(OUTDIR)\gencalcmfc.pch"\
 "$(OUTDIR)\gencalcmfc.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\BondCalcScreen.obj"
	-@erase "$(INTDIR)\BondCalcScreen.sbr"
	-@erase "$(INTDIR)\BondCalcWnd.obj"
	-@erase "$(INTDIR)\BondCalcWnd.sbr"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ChildFrm.sbr"
	-@erase "$(INTDIR)\Classdef.obj"
	-@erase "$(INTDIR)\Classdef.sbr"
	-@erase "$(INTDIR)\Coupload.obj"
	-@erase "$(INTDIR)\Coupload.sbr"
	-@erase "$(INTDIR)\Datefunc.obj"
	-@erase "$(INTDIR)\Datefunc.sbr"
	-@erase "$(INTDIR)\DB.obj"
	-@erase "$(INTDIR)\DB.sbr"
	-@erase "$(INTDIR)\Errproc.obj"
	-@erase "$(INTDIR)\Errproc.sbr"
	-@erase "$(INTDIR)\Errtext.obj"
	-@erase "$(INTDIR)\Errtext.sbr"
	-@erase "$(INTDIR)\Excoup.obj"
	-@erase "$(INTDIR)\Excoup.sbr"
	-@erase "$(INTDIR)\gencalcmfc.obj"
	-@erase "$(INTDIR)\gencalcmfc.pch"
	-@erase "$(INTDIR)\gencalcmfc.res"
	-@erase "$(INTDIR)\gencalcmfc.sbr"
	-@erase "$(INTDIR)\gencalcmfcDoc.obj"
	-@erase "$(INTDIR)\gencalcmfcDoc.sbr"
	-@erase "$(INTDIR)\gencalcmfcView.obj"
	-@erase "$(INTDIR)\gencalcmfcView.sbr"
	-@erase "$(INTDIR)\Holidays.obj"
	-@erase "$(INTDIR)\Holidays.sbr"
	-@erase "$(INTDIR)\HOLIx.obj"
	-@erase "$(INTDIR)\HOLIx.sbr"
	-@erase "$(INTDIR)\Intcalc.obj"
	-@erase "$(INTDIR)\Intcalc.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\Nom_adj.obj"
	-@erase "$(INTDIR)\Nom_adj.sbr"
	-@erase "$(INTDIR)\Py_calc.obj"
	-@erase "$(INTDIR)\Py_calc.sbr"
	-@erase "$(INTDIR)\Pyfront.obj"
	-@erase "$(INTDIR)\Pyfront.sbr"
	-@erase "$(INTDIR)\Quick_Dates.obj"
	-@erase "$(INTDIR)\Quick_Dates.sbr"
	-@erase "$(INTDIR)\RateCurve.obj"
	-@erase "$(INTDIR)\RateCurve.sbr"
	-@erase "$(INTDIR)\RateCurvesScreen.obj"
	-@erase "$(INTDIR)\RateCurvesScreen.sbr"
	-@erase "$(INTDIR)\Redmpadj.obj"
	-@erase "$(INTDIR)\Redmpadj.sbr"
	-@erase "$(INTDIR)\Redmparr.obj"
	-@erase "$(INTDIR)\Redmparr.sbr"
	-@erase "$(INTDIR)\Schedgen.obj"
	-@erase "$(INTDIR)\Schedgen.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\gencalcmfc.bsc"
	-@erase "$(OUTDIR)\gencalcmfc.exe"
	-@erase "$(OUTDIR)\gencalcmfc.ilk"
	-@erase "$(OUTDIR)\gencalcmfc.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\gencalcmfc.pch" /YX\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\gencalcmfc.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\gencalcmfc.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\BondCalcScreen.sbr" \
	"$(INTDIR)\BondCalcWnd.sbr" \
	"$(INTDIR)\ChildFrm.sbr" \
	"$(INTDIR)\Classdef.sbr" \
	"$(INTDIR)\Coupload.sbr" \
	"$(INTDIR)\Datefunc.sbr" \
	"$(INTDIR)\DB.sbr" \
	"$(INTDIR)\Errproc.sbr" \
	"$(INTDIR)\Errtext.sbr" \
	"$(INTDIR)\Excoup.sbr" \
	"$(INTDIR)\gencalcmfc.sbr" \
	"$(INTDIR)\gencalcmfcDoc.sbr" \
	"$(INTDIR)\gencalcmfcView.sbr" \
	"$(INTDIR)\Holidays.sbr" \
	"$(INTDIR)\HOLIx.sbr" \
	"$(INTDIR)\Intcalc.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\Nom_adj.sbr" \
	"$(INTDIR)\Py_calc.sbr" \
	"$(INTDIR)\Pyfront.sbr" \
	"$(INTDIR)\Quick_Dates.sbr" \
	"$(INTDIR)\RateCurve.sbr" \
	"$(INTDIR)\RateCurvesScreen.sbr" \
	"$(INTDIR)\Redmpadj.sbr" \
	"$(INTDIR)\Redmparr.sbr" \
	"$(INTDIR)\Schedgen.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\gencalcmfc.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\gencalcmfc.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\gencalcmfc.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\BondCalcScreen.obj" \
	"$(INTDIR)\BondCalcWnd.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\Classdef.obj" \
	"$(INTDIR)\Coupload.obj" \
	"$(INTDIR)\Datefunc.obj" \
	"$(INTDIR)\DB.obj" \
	"$(INTDIR)\Errproc.obj" \
	"$(INTDIR)\Errtext.obj" \
	"$(INTDIR)\Excoup.obj" \
	"$(INTDIR)\gencalcmfc.obj" \
	"$(INTDIR)\gencalcmfc.res" \
	"$(INTDIR)\gencalcmfcDoc.obj" \
	"$(INTDIR)\gencalcmfcView.obj" \
	"$(INTDIR)\Holidays.obj" \
	"$(INTDIR)\HOLIx.obj" \
	"$(INTDIR)\Intcalc.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Nom_adj.obj" \
	"$(INTDIR)\Py_calc.obj" \
	"$(INTDIR)\Pyfront.obj" \
	"$(INTDIR)\Quick_Dates.obj" \
	"$(INTDIR)\RateCurve.obj" \
	"$(INTDIR)\RateCurvesScreen.obj" \
	"$(INTDIR)\Redmpadj.obj" \
	"$(INTDIR)\Redmparr.obj" \
	"$(INTDIR)\Schedgen.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"..\..\..\..\oledbsdk\lib\Adoid.lib" \
	"..\..\..\..\oledbsdk\lib\Oledb.lib" \
	"..\..\..\..\oledbsdk\lib\Oledbd.lib" \
	"..\..\Vc\lib\Odbc32.lib"

"$(OUTDIR)\gencalcmfc.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(CFG)" == "gencalcmfc - Win32 Release" || "$(CFG)" ==\
 "gencalcmfc - Win32 Debug"
SOURCE=.\BondCalcScreen.cpp

!IF  "$(CFG)" == "gencalcmfc - Win32 Release"

DEP_CPP_BONDC=\
	".\BondCalcScreen.h"\
	".\BondCalcWnd.h"\
	".\ChildFrm.h"\
	".\gencalcmfc.h"\
	".\guidecs.h"\
	".\holidays.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"DB.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"holihead.h"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"insevent.map"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\BondCalcScreen.obj" : $(SOURCE) $(DEP_CPP_BONDC) "$(INTDIR)"\
 "$(INTDIR)\gencalcmfc.pch"


!ELSEIF  "$(CFG)" == "gencalcmfc - Win32 Debug"

DEP_CPP_BONDC=\
	".\BondCalcScreen.h"\
	".\BondCalcWnd.h"\
	".\ChildFrm.h"\
	".\gencalcmfc.h"\
	".\guidecs.h"\
	".\holidays.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"DB.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"holihead.h"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\BondCalcScreen.obj"	"$(INTDIR)\BondCalcScreen.sbr" : $(SOURCE)\
 $(DEP_CPP_BONDC) "$(INTDIR)"


!ENDIF 

SOURCE=.\BondCalcWnd.cpp

!IF  "$(CFG)" == "gencalcmfc - Win32 Release"

DEP_CPP_BONDCA=\
	".\BondCalcWnd.h"\
	".\ChildFrm.h"\
	".\gencalcmfc.h"\
	".\guidecs.h"\
	".\holidays.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"DB.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"holihead.h"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"insevent.map"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\BondCalcWnd.obj" : $(SOURCE) $(DEP_CPP_BONDCA) "$(INTDIR)"\
 "$(INTDIR)\gencalcmfc.pch"


!ELSEIF  "$(CFG)" == "gencalcmfc - Win32 Debug"

DEP_CPP_BONDCA=\
	".\BondCalcWnd.h"\
	".\ChildFrm.h"\
	".\gencalcmfc.h"\
	".\guidecs.h"\
	".\holidays.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"DB.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"holihead.h"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\BondCalcWnd.obj"	"$(INTDIR)\BondCalcWnd.sbr" : $(SOURCE)\
 $(DEP_CPP_BONDCA) "$(INTDIR)"


!ENDIF 

SOURCE=.\ChildFrm.cpp

!IF  "$(CFG)" == "gencalcmfc - Win32 Release"

DEP_CPP_CHILD=\
	".\BondCalcWnd.h"\
	".\ChildFrm.h"\
	".\gencalcmfc.h"\
	".\guidecs.h"\
	".\holidays.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"DB.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"holihead.h"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"insevent.map"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\gencalcmfc.pch"


!ELSEIF  "$(CFG)" == "gencalcmfc - Win32 Debug"

DEP_CPP_CHILD=\
	".\BondCalcWnd.h"\
	".\ChildFrm.h"\
	".\gencalcmfc.h"\
	".\guidecs.h"\
	".\holidays.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"DB.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"holihead.h"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\ChildFrm.obj"	"$(INTDIR)\ChildFrm.sbr" : $(SOURCE) $(DEP_CPP_CHILD)\
 "$(INTDIR)"


!ENDIF 

SOURCE=.\bondsys\Csrc\Classdef.cpp

!IF  "$(CFG)" == "gencalcmfc - Win32 Release"

DEP_CPP_CLASS=\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"insevent.map"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"Locals.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\Classdef.obj" : $(SOURCE) $(DEP_CPP_CLASS) "$(INTDIR)"\
 "$(INTDIR)\gencalcmfc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gencalcmfc - Win32 Debug"

DEP_CPP_CLASS=\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"Locals.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\Classdef.obj"	"$(INTDIR)\Classdef.sbr" : $(SOURCE) $(DEP_CPP_CLASS)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\bondsys\Csrc\Coupload.cpp

!IF  "$(CFG)" == "gencalcmfc - Win32 Release"

DEP_CPP_COUPL=\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"insevent.map"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"Locals.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\Coupload.obj" : $(SOURCE) $(DEP_CPP_COUPL) "$(INTDIR)"\
 "$(INTDIR)\gencalcmfc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gencalcmfc - Win32 Debug"

DEP_CPP_COUPL=\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"Locals.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\Coupload.obj"	"$(INTDIR)\Coupload.sbr" : $(SOURCE) $(DEP_CPP_COUPL)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\bondsys\Csrc\Datefunc.cpp

!IF  "$(CFG)" == "gencalcmfc - Win32 Release"

DEP_CPP_DATEF=\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iodec.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"Locals.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\Datefunc.obj" : $(SOURCE) $(DEP_CPP_DATEF) "$(INTDIR)"\
 "$(INTDIR)\gencalcmfc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gencalcmfc - Win32 Debug"

DEP_CPP_DATEF=\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iodec.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"Locals.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\Datefunc.obj"	"$(INTDIR)\Datefunc.sbr" : $(SOURCE) $(DEP_CPP_DATEF)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\bondsys\Csrc\DB.cpp

!IF  "$(CFG)" == "gencalcmfc - Win32 Release"

DEP_CPP_DB_CP=\
	".\StdAfx.h"\
	{$(INCLUDE)}"DB.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\DB.obj" : $(SOURCE) $(DEP_CPP_DB_CP) "$(INTDIR)"\
 "$(INTDIR)\gencalcmfc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gencalcmfc - Win32 Debug"

DEP_CPP_DB_CP=\
	".\StdAfx.h"\
	{$(INCLUDE)}"DB.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\DB.obj"	"$(INTDIR)\DB.sbr" : $(SOURCE) $(DEP_CPP_DB_CP) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\bondsys\Csrc\Errproc.cpp

!IF  "$(CFG)" == "gencalcmfc - Win32 Release"

DEP_CPP_ERRPR=\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"Locals.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\Errproc.obj" : $(SOURCE) $(DEP_CPP_ERRPR) "$(INTDIR)"\
 "$(INTDIR)\gencalcmfc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gencalcmfc - Win32 Debug"

DEP_CPP_ERRPR=\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"Locals.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\Errproc.obj"	"$(INTDIR)\Errproc.sbr" : $(SOURCE) $(DEP_CPP_ERRPR)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\bondsys\Csrc\Errtext.cpp

!IF  "$(CFG)" == "gencalcmfc - Win32 Release"

DEP_CPP_ERRTE=\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\Errtext.obj" : $(SOURCE) $(DEP_CPP_ERRTE) "$(INTDIR)"\
 "$(INTDIR)\gencalcmfc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gencalcmfc - Win32 Debug"

DEP_CPP_ERRTE=\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\Errtext.obj"	"$(INTDIR)\Errtext.sbr" : $(SOURCE) $(DEP_CPP_ERRTE)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\bondsys\Csrc\Excoup.cpp

!IF  "$(CFG)" == "gencalcmfc - Win32 Release"

DEP_CPP_EXCOU=\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"Locals.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\Excoup.obj" : $(SOURCE) $(DEP_CPP_EXCOU) "$(INTDIR)"\
 "$(INTDIR)\gencalcmfc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gencalcmfc - Win32 Debug"

DEP_CPP_EXCOU=\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"Locals.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\Excoup.obj"	"$(INTDIR)\Excoup.sbr" : $(SOURCE) $(DEP_CPP_EXCOU)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\gencalcmfc.cpp

!IF  "$(CFG)" == "gencalcmfc - Win32 Release"

DEP_CPP_GENCA=\
	".\BondCalcWnd.h"\
	".\ChildFrm.h"\
	".\gencalcmfc.h"\
	".\gencalcmfcDoc.h"\
	".\gencalcmfcView.h"\
	".\guidecs.h"\
	".\holidays.h"\
	".\MainFrm.h"\
	".\Quick_Dates.h"\
	".\RateCurvesScreen.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"DB.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"holihead.h"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"insevent.map"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\gencalcmfc.obj" : $(SOURCE) $(DEP_CPP_GENCA) "$(INTDIR)"\
 "$(INTDIR)\gencalcmfc.pch"


!ELSEIF  "$(CFG)" == "gencalcmfc - Win32 Debug"

DEP_CPP_GENCA=\
	".\BondCalcWnd.h"\
	".\ChildFrm.h"\
	".\gencalcmfc.h"\
	".\gencalcmfcDoc.h"\
	".\gencalcmfcView.h"\
	".\guidecs.h"\
	".\holidays.h"\
	".\MainFrm.h"\
	".\Quick_Dates.h"\
	".\RateCurvesScreen.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"DB.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"holihead.h"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\gencalcmfc.obj"	"$(INTDIR)\gencalcmfc.sbr" : $(SOURCE)\
 $(DEP_CPP_GENCA) "$(INTDIR)"


!ENDIF 

SOURCE=.\gencalcmfc.rc
DEP_RSC_GENCAL=\
	".\res\gencalcmfc.ico"\
	".\res\gencalcmfc.rc2"\
	".\res\gencalcmfcDoc.ico"\
	".\res\Toolbar.bmp"\
	

"$(INTDIR)\gencalcmfc.res" : $(SOURCE) $(DEP_RSC_GENCAL) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\gencalcmfcDoc.cpp

!IF  "$(CFG)" == "gencalcmfc - Win32 Release"

DEP_CPP_GENCALC=\
	".\BondCalcWnd.h"\
	".\ChildFrm.h"\
	".\gencalcmfc.h"\
	".\gencalcmfcDoc.h"\
	".\guidecs.h"\
	".\holidays.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"DB.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"holihead.h"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"insevent.map"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\gencalcmfcDoc.obj" : $(SOURCE) $(DEP_CPP_GENCALC) "$(INTDIR)"\
 "$(INTDIR)\gencalcmfc.pch"


!ELSEIF  "$(CFG)" == "gencalcmfc - Win32 Debug"

DEP_CPP_GENCALC=\
	".\BondCalcWnd.h"\
	".\ChildFrm.h"\
	".\gencalcmfc.h"\
	".\gencalcmfcDoc.h"\
	".\guidecs.h"\
	".\holidays.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"DB.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"holihead.h"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\gencalcmfcDoc.obj"	"$(INTDIR)\gencalcmfcDoc.sbr" : $(SOURCE)\
 $(DEP_CPP_GENCALC) "$(INTDIR)"


!ENDIF 

SOURCE=.\gencalcmfcView.cpp

!IF  "$(CFG)" == "gencalcmfc - Win32 Release"

DEP_CPP_GENCALCM=\
	".\BondCalcWnd.h"\
	".\ChildFrm.h"\
	".\gencalcmfc.h"\
	".\gencalcmfcDoc.h"\
	".\gencalcmfcView.h"\
	".\guidecs.h"\
	".\holidays.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"DB.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"holihead.h"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"insevent.map"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\gencalcmfcView.obj" : $(SOURCE) $(DEP_CPP_GENCALCM) "$(INTDIR)"\
 "$(INTDIR)\gencalcmfc.pch"


!ELSEIF  "$(CFG)" == "gencalcmfc - Win32 Debug"

DEP_CPP_GENCALCM=\
	".\BondCalcWnd.h"\
	".\ChildFrm.h"\
	".\gencalcmfc.h"\
	".\gencalcmfcDoc.h"\
	".\gencalcmfcView.h"\
	".\guidecs.h"\
	".\holidays.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"DB.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"holihead.h"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\gencalcmfcView.obj"	"$(INTDIR)\gencalcmfcView.sbr" : $(SOURCE)\
 $(DEP_CPP_GENCALCM) "$(INTDIR)"


!ENDIF 

SOURCE=.\Holidays.cpp

!IF  "$(CFG)" == "gencalcmfc - Win32 Release"

DEP_CPP_HOLID=\
	".\BondCalcWnd.h"\
	".\ChildFrm.h"\
	".\gencalcmfc.h"\
	".\guidecs.h"\
	".\holidays.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"DB.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"holihead.h"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"insevent.map"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\Holidays.obj" : $(SOURCE) $(DEP_CPP_HOLID) "$(INTDIR)"\
 "$(INTDIR)\gencalcmfc.pch"


!ELSEIF  "$(CFG)" == "gencalcmfc - Win32 Debug"

DEP_CPP_HOLID=\
	".\BondCalcWnd.h"\
	".\ChildFrm.h"\
	".\gencalcmfc.h"\
	".\guidecs.h"\
	".\holidays.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"DB.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"holihead.h"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\Holidays.obj"	"$(INTDIR)\Holidays.sbr" : $(SOURCE) $(DEP_CPP_HOLID)\
 "$(INTDIR)"


!ENDIF 

SOURCE=.\bondsys\Csrc\HOLIx.CPP

!IF  "$(CFG)" == "gencalcmfc - Win32 Release"

DEP_CPP_HOLIX=\
	".\StdAfx.h"\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"DB.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"holihead.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\HOLIx.obj" : $(SOURCE) $(DEP_CPP_HOLIX) "$(INTDIR)"\
 "$(INTDIR)\gencalcmfc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gencalcmfc - Win32 Debug"

DEP_CPP_HOLIX=\
	".\StdAfx.h"\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"DB.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"holihead.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\HOLIx.obj"	"$(INTDIR)\HOLIx.sbr" : $(SOURCE) $(DEP_CPP_HOLIX)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\bondsys\Csrc\Intcalc.cpp

!IF  "$(CFG)" == "gencalcmfc - Win32 Release"

DEP_CPP_INTCA=\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"Gendec.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"insevent.map"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iodec.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"Locals.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\Intcalc.obj" : $(SOURCE) $(DEP_CPP_INTCA) "$(INTDIR)"\
 "$(INTDIR)\gencalcmfc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gencalcmfc - Win32 Debug"

DEP_CPP_INTCA=\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"Gendec.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iodec.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"Locals.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\Intcalc.obj"	"$(INTDIR)\Intcalc.sbr" : $(SOURCE) $(DEP_CPP_INTCA)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "gencalcmfc - Win32 Release"

DEP_CPP_MAINF=\
	".\BondCalcWnd.h"\
	".\ChildFrm.h"\
	".\gencalcmfc.h"\
	".\guidecs.h"\
	".\holidays.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"DB.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"holihead.h"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"insevent.map"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\gencalcmfc.pch"


!ELSEIF  "$(CFG)" == "gencalcmfc - Win32 Debug"

DEP_CPP_MAINF=\
	".\BondCalcWnd.h"\
	".\ChildFrm.h"\
	".\gencalcmfc.h"\
	".\guidecs.h"\
	".\holidays.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"DB.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"holihead.h"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF)\
 "$(INTDIR)"


!ENDIF 

SOURCE=.\bondsys\Csrc\Nom_adj.cpp

!IF  "$(CFG)" == "gencalcmfc - Win32 Release"

DEP_CPP_NOM_A=\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iodec.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"Locals.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\Nom_adj.obj" : $(SOURCE) $(DEP_CPP_NOM_A) "$(INTDIR)"\
 "$(INTDIR)\gencalcmfc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gencalcmfc - Win32 Debug"

DEP_CPP_NOM_A=\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iodec.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"Locals.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\Nom_adj.obj"	"$(INTDIR)\Nom_adj.sbr" : $(SOURCE) $(DEP_CPP_NOM_A)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\bondsys\Csrc\Py_calc.cpp

!IF  "$(CFG)" == "gencalcmfc - Win32 Release"

DEP_CPP_PY_CA=\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"Gendec.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"insevent.map"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"Locals.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\Py_calc.obj" : $(SOURCE) $(DEP_CPP_PY_CA) "$(INTDIR)"\
 "$(INTDIR)\gencalcmfc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gencalcmfc - Win32 Debug"

DEP_CPP_PY_CA=\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"Gendec.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"Locals.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\Py_calc.obj"	"$(INTDIR)\Py_calc.sbr" : $(SOURCE) $(DEP_CPP_PY_CA)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\bondsys\Csrc\Pyfront.cpp

!IF  "$(CFG)" == "gencalcmfc - Win32 Release"

DEP_CPP_PYFRO=\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"Envir.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"Gendec.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"insevent.map"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iodec.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"Locals.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Scrdec.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\Pyfront.obj" : $(SOURCE) $(DEP_CPP_PYFRO) "$(INTDIR)"\
 "$(INTDIR)\gencalcmfc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gencalcmfc - Win32 Debug"

DEP_CPP_PYFRO=\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"Envir.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"Gendec.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iodec.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"Locals.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Scrdec.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\Pyfront.obj"	"$(INTDIR)\Pyfront.sbr" : $(SOURCE) $(DEP_CPP_PYFRO)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Quick_Dates.cpp

!IF  "$(CFG)" == "gencalcmfc - Win32 Release"

DEP_CPP_QUICK=\
	".\BondCalcWnd.h"\
	".\ChildFrm.h"\
	".\gencalcmfc.h"\
	".\guidecs.h"\
	".\holidays.h"\
	".\Quick_Dates.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"DB.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"holihead.h"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"insevent.map"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\Quick_Dates.obj" : $(SOURCE) $(DEP_CPP_QUICK) "$(INTDIR)"\
 "$(INTDIR)\gencalcmfc.pch"


!ELSEIF  "$(CFG)" == "gencalcmfc - Win32 Debug"

DEP_CPP_QUICK=\
	".\BondCalcWnd.h"\
	".\ChildFrm.h"\
	".\gencalcmfc.h"\
	".\guidecs.h"\
	".\holidays.h"\
	".\Quick_Dates.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"DB.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"holihead.h"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\Quick_Dates.obj"	"$(INTDIR)\Quick_Dates.sbr" : $(SOURCE)\
 $(DEP_CPP_QUICK) "$(INTDIR)"


!ENDIF 

SOURCE=.\RateCurve.cpp

!IF  "$(CFG)" == "gencalcmfc - Win32 Release"

DEP_CPP_RATEC=\
	".\BondCalcWnd.h"\
	".\ChildFrm.h"\
	".\gencalcmfc.h"\
	".\guidecs.h"\
	".\holidays.h"\
	".\RateCurve.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"DB.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"holihead.h"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"insevent.map"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\RateCurve.obj" : $(SOURCE) $(DEP_CPP_RATEC) "$(INTDIR)"\
 "$(INTDIR)\gencalcmfc.pch"


!ELSEIF  "$(CFG)" == "gencalcmfc - Win32 Debug"

DEP_CPP_RATEC=\
	".\BondCalcWnd.h"\
	".\ChildFrm.h"\
	".\gencalcmfc.h"\
	".\guidecs.h"\
	".\holidays.h"\
	".\RateCurve.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"DB.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"holihead.h"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\RateCurve.obj"	"$(INTDIR)\RateCurve.sbr" : $(SOURCE)\
 $(DEP_CPP_RATEC) "$(INTDIR)"


!ENDIF 

SOURCE=.\RateCurvesScreen.cpp

!IF  "$(CFG)" == "gencalcmfc - Win32 Release"

DEP_CPP_RATECU=\
	".\BondCalcWnd.h"\
	".\ChildFrm.h"\
	".\gencalcmfc.h"\
	".\guidecs.h"\
	".\holidays.h"\
	".\RateCurvesScreen.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"DB.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"holihead.h"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"insevent.map"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\RateCurvesScreen.obj" : $(SOURCE) $(DEP_CPP_RATECU) "$(INTDIR)"\
 "$(INTDIR)\gencalcmfc.pch"


!ELSEIF  "$(CFG)" == "gencalcmfc - Win32 Debug"

DEP_CPP_RATECU=\
	".\BondCalcWnd.h"\
	".\ChildFrm.h"\
	".\gencalcmfc.h"\
	".\guidecs.h"\
	".\holidays.h"\
	".\RateCurvesScreen.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"DB.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"holihead.h"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"Pydecs.h"\
	{$(INCLUDE)}"Pyfront.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"transact.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\RateCurvesScreen.obj"	"$(INTDIR)\RateCurvesScreen.sbr" : $(SOURCE)\
 $(DEP_CPP_RATECU) "$(INTDIR)"


!ENDIF 

SOURCE=.\bondsys\Csrc\Redmpadj.cpp

!IF  "$(CFG)" == "gencalcmfc - Win32 Release"

DEP_CPP_REDMP=\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"Locals.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\Redmpadj.obj" : $(SOURCE) $(DEP_CPP_REDMP) "$(INTDIR)"\
 "$(INTDIR)\gencalcmfc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gencalcmfc - Win32 Debug"

DEP_CPP_REDMP=\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"Locals.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\Redmpadj.obj"	"$(INTDIR)\Redmpadj.sbr" : $(SOURCE) $(DEP_CPP_REDMP)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\bondsys\Csrc\Redmparr.cpp

!IF  "$(CFG)" == "gencalcmfc - Win32 Release"

DEP_CPP_REDMPA=\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"Locals.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\Redmparr.obj" : $(SOURCE) $(DEP_CPP_REDMPA) "$(INTDIR)"\
 "$(INTDIR)\gencalcmfc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gencalcmfc - Win32 Debug"

DEP_CPP_REDMPA=\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"Locals.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\Redmparr.obj"	"$(INTDIR)\Redmparr.sbr" : $(SOURCE) $(DEP_CPP_REDMPA)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\bondsys\Csrc\Schedgen.cpp

!IF  "$(CFG)" == "gencalcmfc - Win32 Release"

DEP_CPP_SCHED=\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"Locals.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\Schedgen.obj" : $(SOURCE) $(DEP_CPP_SCHED) "$(INTDIR)"\
 "$(INTDIR)\gencalcmfc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gencalcmfc - Win32 Debug"

DEP_CPP_SCHED=\
	{$(INCLUDE)}"Datedec.h"\
	{$(INCLUDE)}"Errdecs.h"\
	{$(INCLUDE)}"holidays.map"\
	{$(INCLUDE)}"Insclass.h"\
	{$(INCLUDE)}"Insevent.h"\
	{$(INCLUDE)}"Instr.h"\
	{$(INCLUDE)}"Intdecs.h"\
	{$(INCLUDE)}"Iokeys.h"\
	{$(INCLUDE)}"Locals.h"\
	{$(INCLUDE)}"Shrtdecs.h"\
	{$(INCLUDE)}"wordsymb.h"\
	

"$(INTDIR)\Schedgen.obj"	"$(INTDIR)\Schedgen.sbr" : $(SOURCE) $(DEP_CPP_SCHED)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "gencalcmfc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /Fp"$(INTDIR)\gencalcmfc.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\gencalcmfc.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gencalcmfc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\gencalcmfc.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\gencalcmfc.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

