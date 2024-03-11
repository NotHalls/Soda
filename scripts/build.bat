@echo off
setlocal

:: Check if current directory is "scripts" folder
for %%A in ("%CD%") do set "CURRENT_DIR=%%~nxA"
if "%CURRENT_DIR%" == "scripts" (
    cd ..
)

:: Create the build folder if it doesn't exist
if not exist "build" (
    mkdir build
)
cd build

:: Run CMake configuration and build the project
cmake -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Debug ..

:: Build the project using Ninja
ninja

:: Return to the parent directory
cd ..

endlocal