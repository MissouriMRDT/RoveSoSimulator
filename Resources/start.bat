@echo off

REM Define variables
set REPO_URL=https://github.com/EpicGamesExt/PixelStreamingInfrastructure.git
set DOWNLOAD_DIR=PixelStreamingInfrastructure
set GAME_EXECUTABLE=RoveSoSimulator.exe

REM Step 1: Check if git is available
git --version >nul 2>&1
if %errorlevel% neq 0 (
    echo git is not installed or not available in PATH. Please install git or add it to PATH.
    exit /b 1
)

REM Step 2: Clone the repository if it doesn't exist
if not exist "%DOWNLOAD_DIR%" (
    echo Cloning the repository...
    git clone %REPO_URL% %DOWNLOAD_DIR%
    if %errorlevel% neq 0 (
        echo Failed to clone the repository. Please check your internet connection.
        exit /b 1
    )
) else (
    echo Repository already exists. Skipping clone.
)

REM Step 5: Navigate to the signaling server script directory
cd %DOWNLOAD_DIR%\SignallingWebServer\platform_scripts\cmd

REM Step 6: Start the signaling server
start "Signaling Server" cmd /k start.bat

REM Step 7: Wait a few seconds to ensure the server starts (optional)
timeout /t 5 /nobreak >nul

REM Step 8: Start the game
cd ..\..\..\..
set GAME_URL=ws://127.0.0.1:80

if exist "%GAME_EXECUTABLE%" (
    echo Starting game with URL %GAME_URL%...
    start "Game" %GAME_EXECUTABLE% -PixelStreamingURL="%GAME_URL%" -PixelStreamingHudStats=false -PixelStreamingWebRTCDisableFrameDropper=true -PixelStreamingWebRTCVideoPacingMaxDelay=50
) else (
    echo Game executable not found: %GAME_EXECUTABLE%
    exit /b 1
)

REM Done
echo All processes started successfully.
exit /b 0
