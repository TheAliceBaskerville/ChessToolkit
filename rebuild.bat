@echo off

REM %~dp0 is absolute path to batch file location.
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
    echo   -r, --Release   Build in Release mode.
    echo   -d, --Debug     Build in Debug mode. ^(default^)
    echo   -h, --help      Show this help message.
    exit /b 0
) else if "%~1"=="--help" (
    echo Usage: %0 [OPTION]
    echo Options:
    echo   -r, --Release   Build in Release mode.
    echo   -d, --Debug     Build in Debug mode. ^(default^)
    echo   -h, --help      Show this help message.
    exit /b 0
) else (
    echo Invalid argument: %~1
    echo Use --help for a list of available arguments.
    exit /b 1
)

echo Selected build configuration: %BUILD_TYPE%

if exist build (
    echo Clearing build directory...
    del /s /q build\*.* > nul
    for /d %%p in (build\*) do rd /s /q "%%p"

    pushd build
    set "dir_empty=true"
    for /f "delims=" %%d in ('dir /b /a') do (
        set "dir_empty=false"
    )
    popd

    if "%dir_empty%"=="true" (
        echo Build directory cleared successfully.
    ) else (
        echo Build directory was not cleared successfully.
        exit /b 1
    )
) else (
    echo Build directory does not exist. Creating it now...
    mkdir build
)

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

cd "%~dp0/bin"
ChessToolkit
if %errorlevel% neq 0 (
    echo .exe launch failed
    cd /d "%~dp0"
    exit /b %errorlevel%
)

cd /d "%~dp0"