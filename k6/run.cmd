@echo off
setlocal enabledelayedexpansion

if "%1" == "" (
    echo Usage: run.cmd ^<suffix^>
    exit /b 1
)

set "suffix=%1"
if not exist result mkdir result

for /f %%a in ('wmic os get LocalDateTime /value') do (
    for /f %%b in ('echo %%a ^| findstr /r "^LocalDateTime=."') do (
        set "%%b"
    )
)

set "timestamp=!LocalDateTime:~0,8!_!LocalDateTime:~8,6!"
set "outputFile=result\output_%timestamp%%suffix%.txt"

k6 run test01.js > "%outputFile%"
