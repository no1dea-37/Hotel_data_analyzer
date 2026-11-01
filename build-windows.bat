@echo off
setlocal
cd /d "%~dp0"
echo [1/2] Installing dependencies...
call npm install
if errorlevel 1 goto failed
echo [2/2] Building Windows installer...
call npm run dist:win
if errorlevel 1 goto failed
echo.
echo Build complete. See the dist folder.
pause
exit /b 0
:failed
echo.
echo Build failed. Please confirm Node.js LTS and npm are installed.
pause
exit /b 1
