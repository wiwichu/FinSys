# Microsoft Developer Studio Project File - Name="Calc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Calc - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Calc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Calc.mak" CFG="Calc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Calc - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Calc - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Calc - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CALC_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CALC_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Calc - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CALC_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CALC_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "Calc - Win32 Release"
# Name "Calc - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Calc.cpp
# End Source File
# Begin Source File

SOURCE=.\Coupload.cpp
# End Source File
# Begin Source File

SOURCE=.\Datefunc.cpp
# End Source File
# Begin Source File

SOURCE=.\Errtext.cpp
# End Source File
# Begin Source File

SOURCE=.\ExceptionCalc.cpp
# End Source File
# Begin Source File

SOURCE=.\FinCalc.cpp
# End Source File
# Begin Source File

SOURCE=.\holicodeproc.cpp
# End Source File
# Begin Source File

SOURCE=.\HOLIx.CPP
# End Source File
# Begin Source File

SOURCE=.\insevent.cpp
# End Source File
# Begin Source File

SOURCE=.\Instrument.cpp
# End Source File
# Begin Source File

SOURCE=.\Intcalc.cpp
# End Source File
# Begin Source File

SOURCE=.\PatCalc.cpp
# End Source File
# Begin Source File

SOURCE=.\Py_calc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pyfront.cpp
# End Source File
# Begin Source File

SOURCE=.\RateCurve.cpp
# End Source File
# Begin Source File

SOURCE=.\Redmparr.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Calc.h
# End Source File
# Begin Source File

SOURCE=.\Datedec.h
# End Source File
# Begin Source File

SOURCE=.\Envir.h
# End Source File
# Begin Source File

SOURCE=.\Errdecs.h
# End Source File
# Begin Source File

SOURCE=.\ExceptionCalc.h
# End Source File
# Begin Source File

SOURCE=.\FinCalc.h
# End Source File
# Begin Source File

SOURCE=.\FRADECS.H
# End Source File
# Begin Source File

SOURCE=.\Gendec.h
# End Source File
# Begin Source File

SOURCE=.\holicodeproc.h
# End Source File
# Begin Source File

SOURCE=.\HOLIDAYS.H
# End Source File
# Begin Source File

SOURCE=.\Holihead.h
# End Source File
# Begin Source File

SOURCE=.\Insclass.h
# End Source File
# Begin Source File

SOURCE=.\Insevent.h
# End Source File
# Begin Source File

SOURCE=.\Instr.h
# End Source File
# Begin Source File

SOURCE=.\Intdecs.h
# End Source File
# Begin Source File

SOURCE=.\Locals.h
# End Source File
# Begin Source File

SOURCE=.\PatCalc.h
# End Source File
# Begin Source File

SOURCE=.\POSPROC.H
# End Source File
# Begin Source File

SOURCE=.\Pydecs.h
# End Source File
# Begin Source File

SOURCE=.\Pyfront.h
# End Source File
# Begin Source File

SOURCE=.\RateCurve.h
# End Source File
# Begin Source File

SOURCE=.\Scrdec.h
# End Source File
# Begin Source File

SOURCE=.\Shrtdecs.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Wordsymb.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
