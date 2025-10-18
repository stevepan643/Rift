@echo off
setlocal enabledelayedexpansion

REM Stop on errors
set BUILD_DIR=Build
set BUILD_TYPE=Release

echo === [RIFT CONFIGURE] ===
echo Configuring project in %BUILD_DIR% (%BUILD_TYPE% mode) for Visual Studio 2022 x64...

REM Create build directory if missing
if not exist "%BUILD_DIR%" (
    mkdir "%BUILD_DIR%"
)

REM Configure project with CMake for Visual Studio 2022 x64
cmake -B "%BUILD_DIR%" -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
if errorlevel 1 (
    echo Configuration failed!
    exit /b 1
)

echo === Configuration complete! ===
endlocal
