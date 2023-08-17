@echo off

set "DIR=%1%2"
set "OLDPATH=%CD%"
set "OUTFILE=..\..\..\..\..\Output.txt"
set "PRINTF=..\..\..\..\..\..\Utilities\printf\printf"

if not exist "%1%" (
  mkdir "%1%"
)
 
if exist "%DIR%" (
  del /s /q "%DIR%\*.*"
  rem for /d %%i in ("%DIR%\*") do rmdir "%%i"
  rmdir /s /q "%%i"
)

if not exist "%DIR%" (
  mkdir "%DIR%"
)

cd "%DIR%"
 
%PRINTF% "Generate CMake %-16s" "%3% ..."
cmake -G "Ninja" -DTARGET=pc ../..  >> "$OUTFILE" 
if %ERRORLEVEL% equ 0 (
    %PRINTF% "[Ok]\n"
) else (
    %PRINTF% "[Error!]\n"
)

%PRINTF% "Compilate project %-16s" "%3%..."
ninja  >> "$OUTFILE" 
if %ERRORLEVEL% equ 0 (
    %PRINTF% "[Ok]\n"
) else (
    %PRINTF% "[Error!]\n"
)

if exist "%3%tests" (
  %PRINTF% "Test project %-16s" "%3% ..."
  %3%tests  >> "$OUTFILE"
  if %ERRORLEVEL% equ 0 (
    %PRINTF% "[Ok]\n"
  ) else (
    %PRINTF% "[Error!]\n"
  )
)

%PRINTF% " \n" 

cd "%OLDPATH%"



