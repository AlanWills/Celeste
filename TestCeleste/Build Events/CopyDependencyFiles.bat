set "OutputDir=%1"
set "Configuration=%2"
set "Platform=%3"

rem Debugging
rem echo %OutputDir% > log.txt
rem echo %OutputDir%..\..\..\..\TestCelesteEngine\bin\%Platform%\Debug\ >> log.txt

cd %OutputDir%

(robocopy ..\..\..\..\Celeste\bin\%Platform%\%Configuration%\ .\ /E /IS /IT /XO) &
(robocopy ..\..\..\..\TestUtils\bin\%Platform%\%Configuration%\ .\ /E /IS /IT /XO) &
(robocopy ..\..\..\..\CelesteTestUtils\bin\%Platform%\%Configuration%\ .\ /E /IS /IT /XO) & exit 0