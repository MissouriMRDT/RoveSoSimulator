# Pixel Streaming Setup Scripts

This repository contains scripts to set up and run the Pixel Streaming feature for the RoveSoSimulator packaged builds. These scripts ensure that the signalling server is started and the camera streaming works correctly.

## Scripts

- `start.bat`: A batch script for Windows to start the game with Pixel Streaming configured, along with the signalling server and web interface running.
- `start.sh`: A shell script for Linux to start the game with Pixel Streaming configured, along with the signalling server and web interface running.

## Usage

1. **Copy Scripts**: Copy the provided scripts (`start.bat` for Windows or `start.sh` for Linux) to the packaged build directory.
2. **Run Script**: Execute the appropriate script to start the game with Pixel Streaming enabled.

These scripts will ensure that the signalling server is started and the camera streaming works as expected.

## Note

Make sure to include these scripts in the packaged builds whenever they are made to ensure proper setup and functionality of the Pixel Streaming feature.