#!/bin/bash

# Define variables
REPO_URL=https://github.com/EpicGamesExt/PixelStreamingInfrastructure.git
DOWNLOAD_DIR=PixelStreamingInfrastructure
GAME_EXECUTABLE=RoveSoSimulator

# Step 1: Check if git is available
if ! command -v git &> /dev/null
then
    echo "git is not installed or not available in PATH. Please install git or add it to PATH."
    exit 1
fi

# Step 2: Clone the repository if it doesn't exist
if [ ! -d "$DOWNLOAD_DIR" ]; then
    echo "Cloning the repository..."
    git clone $REPO_URL $DOWNLOAD_DIR
    if [ $? -ne 0 ]; then
        echo "Failed to clone the repository. Please check your internet connection."
        exit 1
    fi
else
    echo "Repository already exists. Skipping clone."
fi

# Step 5: Navigate to the signaling server script directory
cd $DOWNLOAD_DIR/SignallingWebServer/platform_scripts/cmd

# Step 6: Start the signaling server
gnome-terminal -- bash -c "./start.sh; exec bash"

# Step 7: Wait a few seconds to ensure the server starts (optional)
sleep 5

# Step 8: Start the game
cd ../../../../
if [ -f "$GAME_EXECUTABLE" ]; then
    echo "Starting game..."
    gnome-terminal -- bash -c "./$GAME_EXECUTABLE; exec bash"
else
    echo "Game executable not found: $GAME_EXECUTABLE"
    exit 1
fi

# Done
echo "All processes started successfully."
exit 0