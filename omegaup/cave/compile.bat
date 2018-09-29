@ECHO OFF
REM Auto-generated by libinteractive. Do not edit.
SETLOCAL EnableDelayedExpansion

REM Get all compilers/paths needed
CALL :getgxx || EXIT /B 1
CALL :getgcc || EXIT /B 1

REM Update all "links"

REM Build all binaries (if needed)
SET TARGET=libinteractive\Main\Main.exe
SET SOURCES=Main.cpp libinteractive\Main\Main_entry.cpp
call:recompile %TARGET% %SOURCES%
IF "%RECOMPILE%" == "1" (
<NUL SET /p elidenewline=Compiling %TARGET%... 
%GXX% -std=c++11 -o %TARGET% %SOURCES% -lm -O2 -g -Wl,-e,__entry -Wno-unused-result -Ilibinteractive/Main
IF !ERRORLEVEL! NEQ 0 EXIT /B !ERRORLEVEL!
ECHO DONE
)

SET TARGET=libinteractive\cave\cave.exe
SET SOURCES=cave.cpp libinteractive\cave\cave_entry.cpp
call:recompile %TARGET% %SOURCES%
IF "%RECOMPILE%" == "1" (
<NUL SET /p elidenewline=Compiling %TARGET%... 
%GXX% -std=c++11 -o %TARGET% %SOURCES% -lm -O2 -g  -Wno-unused-result -Ilibinteractive/cave
IF !ERRORLEVEL! NEQ 0 EXIT /B !ERRORLEVEL!
ECHO DONE
)

SET TARGET=libinteractive\cave\cave_debug.exe
SET SOURCES=cave.cpp libinteractive\cave\cave_entry.cpp
call:recompile %TARGET% %SOURCES%
IF "%RECOMPILE%" == "1" (
<NUL SET /p elidenewline=Compiling %TARGET%... 
%GXX% -std=c++11 -o %TARGET% %SOURCES% -lm -g  -Wno-unused-result -Ilibinteractive/cave
IF !ERRORLEVEL! NEQ 0 EXIT /B !ERRORLEVEL!
ECHO DONE
)

SET TARGET=libinteractive\run.exe
SET SOURCES=libinteractive\run.c
call:recompile %TARGET% %SOURCES%
IF "%RECOMPILE%" == "1" (
<NUL SET /p elidenewline=Compiling %TARGET%... 
%GCC% -std=c99 -o %TARGET% %SOURCES% -O2 -lpsapi -Wall
IF !ERRORLEVEL! NEQ 0 EXIT /B !ERRORLEVEL!
ECHO DONE
)


REM Done
EXIT /B 0
GOTO:EOF

:getgcc
FOR %%A IN (gcc.exe) DO (SET GCC="%%~$PATH:A")
IF %GCC% NEQ "" GOTO:EOF
REG QUERY HKCU\Software\CodeBlocks /v Path 2>NUL >NUL
IF "%ERRORLEVEL%" NEQ "0" (
ECHO Please install the latest version of CodeBlocks and launch it once
ECHO http://www.codeblocks.org/downloads/binaries#windows ^(mingw-setup.exe^)
EXIT /B 1
GOTO:EOF
)
FOR /F "tokens=2*" %%A IN ('REG QUERY HKCU\Software\CodeBlocks /v Path') DO SET GCC=%%B
SET PATH=%PATH%;%GCC%\MinGW\bin
SET GCC="%GCC%\MinGW\bin\gcc.exe"
GOTO:EOF

:getgxx
FOR %%A IN (g++.exe) DO (SET GXX="%%~$PATH:A")
IF %GXX% NEQ "" GOTO:EOF
REG QUERY HKCU\Software\CodeBlocks /v Path 2>NUL >NUL
IF "%ERRORLEVEL%" NEQ "0" (
ECHO Please install the latest version of CodeBlocks and launch it once
ECHO http://www.codeblocks.org/downloads/binaries#windows ^(mingw-setup.exe^)
EXIT /B 1
GOTO:EOF
)
FOR /F "tokens=2*" %%A IN ('REG QUERY HKCU\Software\CodeBlocks /v Path') DO SET GXX=%%B
SET PATH=%PATH%;%GXX%\MinGW\bin
SET GXX="%GXX%\MinGW\bin\g++.exe"
GOTO:EOF

:getjavac
FOR %%A IN (javac.exe) DO (SET JAVAC="%%~$PATH:A")
IF %JAVAC% NEQ "" GOTO:EOF
REG QUERY "HKLM\Software\JavaSoft\Java Development Kit" /v CurrentVersion 2>NUL >NUL
IF "%ERRORLEVEL%" NEQ "0" (
ECHO Please install the latest version of the Java Development Kit
ECHO http://www.oracle.com/technetwork/java/javase/downloads/
EXIT /B 1
GOTO:EOF
)
FOR /F "tokens=2*" %%A IN ('REG QUERY "HKLM\Software\JavaSoft\Java Development Kit" /v CurrentVersion') DO SET JAVA_VERSION=%%B
FOR /F "tokens=2*" %%A IN ('REG QUERY "HKLM\Software\JavaSoft\Java Development Kit\%JAVA_VERSION%" /v JavaHome') DO SET JAVAC=%%B
SET PATH=%PATH%;%JAVAC%\bin
SET JAVAC="%JAVAC%\bin\javac.exe"
GOTO:EOF

:getpython
FOR %%A IN (python.exe) DO (SET PYTHON="%%~$PATH:A")
IF %PYTHON% NEQ "" GOTO:EOF
REG QUERY HKLM\Software\Python\PythonCore\2.7\InstallPath /ve 2>NUL >NUL
IF "%ERRORLEVEL%" NEQ "0" (
ECHO Please install the latest version of Python 2.7
ECHO https://www.python.org/downloads/
EXIT /B 1
GOTO:EOF
)
FOR /F "tokens=2*" %%A IN ('REG QUERY HKLM\Software\Python\PythonCore\2.7\InstallPath /ve') DO SET PYTHON=%%B
SET PATH=%PATH%;%PYTHON%
SET PYTHON="%PYTHON%\python.exe"
GOTO:EOF

:getfpc
FOR %%A IN (fpc.exe) DO (SET FPC="%%~$PATH:A")
IF %FPC% NEQ "" GOTO:EOF
IF NOT EXIST "%LOCALAPPDATA%\lazarus\environmentoptions.xml" (
ECHO Please install the latest version of Lazarus and run it once
ECHO http://www.lazarus.freepascal.org/index.php?page=downloads
EXIT /B 1
GOTO:EOF
)
FOR /F tokens^=2^ delims^=^" %%A IN ('findstr "<CompilerFilename" "%LOCALAPPDATA%\lazarus\environmentoptions.xml"') DO SET FPC=%%A
SET PATH=%PATH%;%FPC\..
SET FPC="%FPC%"
GOTO:EOF

:getModificationTime
set _FILE=%~f1
set _FILE=%_FILE:\=\\%
IF NOT EXIST %~1 (
	SET MODIFICATIONTIME=0
	GOTO:EOF
)
FOR /F "skip=1 tokens=1 usebackq" %%A IN (`wmic datafile where name^="%_FILE%" GET LastModified`) DO (
	SET MODIFICATIONTIME=%%A
	GOTO:EOF
)
GOTO:EOF

:recompile
SET RECOMPILE=0
IF NOT EXIST %~1 (
	SET RECOMPILE=1
	GOTO:EOF
)
SET _TARGET=%~f1
call:getModificationTime %_TARGET%
SET _TARGETTIME=%MODIFICATIONTIME%
:params
SHIFT
IF "%~1" == "" GOTO endparams
SET _SOURCE=%~f1
call:getModificationTime %_SOURCE%
SET _SOURCETIME=%MODIFICATIONTIME%
IF %_SOURCETIME% GTR %_TARGETTIME% (SET RECOMPILE=1) ELSE (GOTO params)
:endparams
GOTO:EOF