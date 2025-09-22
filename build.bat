@echo off
echo Flood Packer Build Process
echo ===============================

:: Set OpenSSL path
set OPENSSL_PATH=C:\OpenSSL-Win64

:: Compiler settings
set CXX=cl
set CXXFLAGS=/nologo /O2 /MT /GS- /Gy /GR- /EHa /fp:fast /DNDEBUG
set LDFLAGS=/NOLOGO /SUBSYSTEM:WINDOWS /DYNAMICBASE:NO

:: Build stub
echo Building stub...
%CXX% %CXXFLAGS% /I%OPENSSL_PATH%\include stub\main.cpp stub\stub.cpp crypto\crypto.cpp ^
    anti_analysis\anti_debug.cpp anti_analysis\anti_vm.cpp anti_analysis\integrity.cpp ^
    vm\vm.cpp utils\utils.cpp /link %LDFLAGS% /LIBPATH:%OPENSSL_PATH%\lib\VC ^
    libcrypto.lib libssl.lib /OUT:build\stub.bin

:: Build packer
echo Building packer...
%CXX% %CXXFLAGS% /I%OPENSSL_PATH%\include packer\main.cpp packer\packer.cpp crypto\crypto.cpp ^
    polymorphism\polymorphic.cpp anti_analysis\anti_debug.cpp anti_analysis\anti_vm.cpp ^
    anti_analysis\integrity.cpp vm\vm.cpp utils\utils.cpp utils\pe_parser.cpp ^
    /link %LDFLAGS% /LIBPATH:%OPENSSL_PATH%\lib\VC libcrypto.lib libssl.lib /OUT:packer.exe

echo Build complete.
echo.
echo Usage: packer.exe <input.exe> <output.exe>
pause