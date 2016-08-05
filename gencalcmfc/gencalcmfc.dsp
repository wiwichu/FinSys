# Microsoft Developer Studio Project File - Name="gencalcmfc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=gencalcmfc - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gencalcmfc.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "gencalcmfc - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /ZI /I "../calc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 calc.lib /nologo /subsystem:windows /machine:I386 /libpath:"../calc/release"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "gencalcmfc - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../calc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 calc.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"../calc/release"
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ENDIF 

# Begin Target

# Name "gencalcmfc - Win32 Release"
# Name "gencalcmfc - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Library Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\oledbsdk\lib\Adoid.lib
# End Source File
# Begin Source File

SOURCE=..\..\Vc\lib\Odbc32.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\oledbsdk\lib\Oledb.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\oledbsdk\lib\Oledbd.lib
# End Source File
# End Group
# Begin Source File

SOURCE=.\BondCalcScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\BondCalculator.cpp
# End Source File
# Begin Source File

SOURCE=.\BondCalcWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\gencalcmfc.cpp
# End Source File
# Begin Source File

SOURCE=.\gencalcmfc.rc
# End Source File
# Begin Source File

SOURCE=.\gencalcmfcDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\gencalcmfcView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "gencalcmfc - Win32 Release"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "gencalcmfc - Win32 Debug"

# ADD CPP /D "_ANSIC" /Yc"stdafx.h"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\bondcalc.h
# End Source File
# Begin Source File

SOURCE=.\BondCalcScreen.h
# End Source File
# Begin Source File

SOURCE=.\BondCalculator.h
# End Source File
# Begin Source File

SOURCE=.\BondCalcWnd.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\gencalcmfc.h
# End Source File
# Begin Source File

SOURCE=.\gencalcmfcDoc.h
# End Source File
# Begin Source File

SOURCE=.\gencalcmfcView.h
# End Source File
# Begin Source File

SOURCE=.\guidecs.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\gencalcmfc.ico
# End Source File
# Begin Source File

SOURCE=.\res\gencalcmfc.rc2
# End Source File
# Begin Source File

SOURCE=.\res\gencalcmfcDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
