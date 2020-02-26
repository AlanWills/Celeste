set "ProjectDir=%1"
set "Configuration=%2"
set "Platform=%3"
set "OutputDir=bin\%Platform%\%Configuration%"
set "ResourcesDir=%OutputDir%\Resources"

cd %ProjectDir%

(robocopy ..\3rdParty\DLL\%Platform% %ResourcesDir% /IS /IT /XO)
(robocopy Resources %ResourcesDir% /E /IS /IT /XO)

echo "Executing Lua Script Validation"
call ..\DevTools\LuaScriptValidator\LuaScriptValidator.exe %ResourcesDir%

IF %ERRORLEVEL% NEQ 0 (
  echo "Lua Script Validation Failed"
  exit 1
)

echo "Lua Script Validation Passed"
echo "Executing Prefab Validation"
call ..\DevTools\PrefabValidator\PrefabValidator.exe %ResourcesDir%

IF %ERRORLEVEL% NEQ 0 (
  echo "Prefab Validation Failed"
  exit 1
)

echo "Prefab Validation Passed"
echo "Executing Scene Validation"
call ..\DevTools\SceneValidator\SceneValidator.exe %ResourcesDir%

IF %ERRORLEVEL% NEQ 0 (
  echo "Scene Validation Failed"
  exit 1
)

echo "Scene Validation Passed"
echo "Executing Scriptable Object Validation"
call ..\DevTools\ScriptableObjectValidator\ScriptableObjectValidator.exe %ResourcesDir%

IF %ERRORLEVEL% NEQ 0 (
  echo "Scriptable Object Validation Failed"
  exit 1
)