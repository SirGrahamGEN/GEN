@echo off

set "DIR=%1%2"
set "OLDPATH=%CD%"

if not exist "%1%" (
  mkdir "%1%"
)
 
if exist "%DIR%" (
  del /s /q "%DIR%\*.*"
  rmdir /s /q "%%i"
)

if not exist "%DIR%" (
  mkdir "%DIR%"
)

cd "%DIR%"
 
%PRINTF% "Generate CMake %%-16s %%s " "%3%" "..."
cmake -G "Ninja" -DTARGET=PC ../..  >> "$OUTFILE" 
if %ERRORLEVEL% equ 0 (
    %PRINTF% "[Ok]\n"
) else (
    %PRINTF% "[Error!]\n"
)

%PRINTF% "Compilate project %%-16s %%s " "%3%" "..."
ninja  >> "$OUTFILE" 
if %ERRORLEVEL% equ 0 (
    %PRINTF% "[Ok]\n"
) else (
    %PRINTF% "[Error!]\n"
)

if exist "%3%tests.exe" (
  %PRINTF% "Test project %%-16s %%s " "%3%tests" "..."
  %3%tests.exe  >> "$OUTFILE"
  
  %PRINTF% "[Error level %%d]"  %ERRORLEVEL% 
  
  if %ERRORLEVEL% equ 0 (
    %PRINTF% "[Ok]\n"
  ) else (
    %PRINTF% "[Error!]\n"
  )
)

%PRINTF% " \n" 

cd "%OLDPATH%"



