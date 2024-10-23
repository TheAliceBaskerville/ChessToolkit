@echo off

REM %~dp0 is the absolute path to the batch file location.
set "PATH_TO_ROOT=%~dp0"
cd /d %PATH_TO_ROOT%

set "SILENT_MODE=0"
set "BUILD_TYPE=Debug"

:parseArgs
if "%~1"=="" goto continue
if "%~1"=="-d" set "BUILD_TYPE=Debug" & shift & goto parseArgs
if "%~1"=="--Debug" set "BUILD_TYPE=Debug" & shift & goto parseArgs
if "%~1"=="-r" set "BUILD_TYPE=Release" & shift & goto parseArgs
if "%~1"=="--Release" set "BUILD_TYPE=Release" & shift & goto parseArgs
if "%~1"=="-s" set "SILENT_MODE=1" & shift & goto parseArgs
if "%~1"=="--silent" set "SILENT_MODE=1" & shift & goto parseArgs
if "%~1"=="-h" goto help
if "%~1"=="--help" goto help

echo Invalid argument: %~1
echo Use --help for a list of available arguments.
exit /b 1

:help
echo Usage: %0 [OPTION]
echo Options:
echo   -d, --Debug     Build in Debug mode. ^(default^)
echo   -r, --Release   Build in Release mode.
echo   -s, --silent    Silent mode. ^(off by default^)
echo   -h, --help      Show help.
exit /b 0

:continue
if %SILENT_MODE%==0 (
    echo Selected build configuration: %BUILD_TYPE%
)

if exist build (
    if %SILENT_MODE%==0 (
        echo Clearing build directory...
    )
    rmdir /s /q build
    if exist build (
        echo Failed to remove build directory.
        exit /b 1
    )
)

mkdir build
if not exist build (
    echo Failed to create build directory.
    exit /b 1
)
if %SILENT_MODE%==0 (
    echo Build directory cleared successfully.
)

cd build

if %SILENT_MODE%==0 (
    cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ..
) else (
    cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=%BUILD_TYPE% .. >nul 2>&1
)
if %errorlevel% neq 0 (
    echo CMake failed
    cd /d %PATH_TO_ROOT%
    exit /b %errorlevel%
)

if %SILENT_MODE%==0 (
    mingw32-make
) else (
    mingw32-make >nul 2>&1
)
if %errorlevel% neq 0 (
    echo mingw32-make failed
    cd /d %PATH_TO_ROOT%
    exit /b %errorlevel%
)

cd "../bin"

if exist ChessToolkit.exe (
    ChessToolkit.exe
) else (
    echo ChessToolkit.exe not found
    cd /d %PATH_TO_ROOT%
    exit /b 1
)

cd /d %PATH_TO_ROOT%