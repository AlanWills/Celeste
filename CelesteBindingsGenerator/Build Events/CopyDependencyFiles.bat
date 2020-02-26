set "OutputDir=%1"
set "Configuration=%2"
set "Platform=%3"

rem Debugging
rem echo %OutputDir% > log.txt

cd %OutputDir%

(robocopy ..\..\..\..\CelesteEngine\bin\%Platform%\%Configuration%\ .\ /IS /IT /XO) ^&
(robocopy ..\..\..\..\BindingsGenerator\bin\%Platform%\%Configuration%\ .\ /IS /IT /XO) ^& exit 0