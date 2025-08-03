@echo off

REM ===================================================
REM  NOTE FOR FIRST-TIME USERS:
REM  ---------------------------------
REM  If you get an error like:
REM  "running scripts is disabled on this system"
REM  you need to enable PowerShell script execution.
REM
REM  Copy and paste this command into PowerShell:
REM      Set-ExecutionPolicy -Scope CurrentUser -ExecutionPolicy RemoteSigned
REM  Then press Y and Enter.
REM ===================================================

REM Single-file Unreal clean & regenerate: deletes all but Config, Content, Plugins, Source and calls the shell menu

REM Where to write the PowerShell script (temp file in the same folder)
set PS1_FILE=%TEMP%\_ue_cleanregen.ps1

REM Write the PowerShell script to file
>%PS1_FILE% echo $keep = @("Config","Content","Plugins","Source")
>>%PS1_FILE% echo Get-ChildItem -Directory ^| Where-Object { $keep -notcontains $_.Name } ^| Remove-Item -Recurse -Force
>>%PS1_FILE% echo $uproject = Get-ChildItem *.uproject ^| Select-Object -First 1
>>%PS1_FILE% echo if ($uproject) {
>>%PS1_FILE% echo.    $shell = New-Object -ComObject Shell.Application
>>%PS1_FILE% echo.    $folder = $shell.Namespace((Get-Location).Path)
>>%PS1_FILE% echo.    $item = $folder.ParseName($uproject.Name)
>>%PS1_FILE% echo.    $verb = $item.Verbs() ^| Where-Object { $_.Name -match "Generate Visual Studio" }
>>%PS1_FILE% echo.    if ($verb) {
>>%PS1_FILE% echo.        $verb.DoIt()
>>%PS1_FILE% echo.        Start-Sleep -Seconds 8
>>%PS1_FILE% echo.    }
>>%PS1_FILE% echo }

REM Run the PowerShell script silently
powershell -WindowStyle Hidden -ExecutionPolicy Bypass -File "%PS1_FILE%"

REM Optionally delete the temp .ps1 (uncomment if you want to remove after run)
REM del "%PS1_FILE%"
