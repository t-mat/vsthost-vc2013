@echo off & setlocal
set SLN=vsthost24.sln
call "%VS120COMNTOOLS%\vsvars32.bat"
pushd vsthostsrc
msbuild %SLN% /nologo /v:q /t:Rebuild /p:Platform=Win32 /p:Configuration=Release
popd
