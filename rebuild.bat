@echo off

REM %~dp0 is the absolute path to the batch file location.
cd /d "%~dp0"

if "%~1"=="" (
    set "BUILD_TYPE=Debug"
) else if "%~1"=="-d" (
    set "BUILD_TYPE=Debug"
) else if "%~1"=="--Debug" (
    set "BUILD_TYPE=Debug"
) else if "%~1"=="-r" (
    set "BUILD_TYPE=Release"
) else if "%~1"=="--Release" (
    set "BUILD_TYPE=Release"
) else if "%~1"=="-h" (
    echo Usage: %0 [OPTION]
    echo Options:
    echo   -d, --Debug     Build in Debug mode. ^(default^)
    echo   -r, --Release   Build in Release mode.
    echo   -h, --help      Show help.
    exit /b 0
) else if "%~1"=="--help" (
    echo Usage: %0 [OPTION]
    echo Options:
    echo   -d, --Debug     Build in Debug mode. ^(default^)
    echo   -r, --Release   Build in Release mode.
    echo   -h, --help      Show help.
    exit /b 0
) else (
    echo Invalid argument: %~1
    echo Use --help for a list of available arguments.
    exit /b 1
)

echo Selected build configuration: %BUILD_TYPE%

if exist build (
    echo Clearing build directory...
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
echo Build directory clear successfully.

cd build

cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ..\
if %errorlevel% neq 0 (
    echo CMake failed
    cd /d "%~dp0"
    exit /b %errorlevel%
)

mingw32-make
if %errorlevel% neq 0 (
    echo mingw32-make failed
    cd /d "%~dp0"
    exit /b %errorlevel%
)

cd "../bin"

if exist ChessToolkit.exe (
    ChessToolkit.exe
) else (
    echo ChessToolkit.exe not found
    cd /d "%~dp0"
    exit /b 1
)

cd /d "%~dp0"