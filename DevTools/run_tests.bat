set "test_exec=C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\CommonExtensions\Microsoft\TestWindow\vstest.console.exe"

set "var=%~dp0%..\TestCelesteEnginePlus\bin\Win32\Debug\TestCelesteEnginePlus.dll"
"%test_exec%" "%var%" /InIsolation /Platform:x86 /Logger:trx