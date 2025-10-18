@echo off
setlocal enabledelayedexpansion

REM Stop on errors
set BUILD_DIR=Build
set BUILD_TYPE=Debug

echo === [RIFT CONFIGURE] ===
echo Configuring project in %BUILD_DIR% (%BUILD_TYPE% mode) for Visual Studio 2022 x64...

REM Create build directory if missing
if not exist "%BUILD_DIR%" (
    mkdir "%BUILD_DIR%"
)

cmake -B "%BUILD_DIR%" -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .
if errorlevel 1 (
    echo Configuration failed!
    exit /b 1
)

echo === Configuration complete! ===
endlocal
