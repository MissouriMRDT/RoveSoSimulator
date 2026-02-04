---
title: Linux Setup
---

# RoveSoSimulator Linux Setup

When attempting to setup RoveSoSimulator on Linux, it is likely that you will encounter multiple roadblocks, primarily to due with Unreal Editor's disaffinity for Linux. This guide will document known issues and workarounds, if you have a novel problem or solution please add it to this section of the docs.

There are two ways to install unreal engine. The first is the portable way which will work for most linux systems. If you wanted a packaged version, go to the arch linux install section. 

## Installing / Running Unreal Editor (portable version)

Make sure to download the Linux version [here](https://www.unrealengine.com/en-US/linux) by selecting the `Linux_Unreal_Engine_X.X.X.zip` download.

The path to the executable once extracted is `./Engine/Binaries/Linux/UnrealEditor`.

If you have issues where the sim is unable to be compiled then you may need to manually build the sim. (Detailed below)

## Installing / Running packaged Unreal Editor

### 1. Environment Setup & Dependencies
Before interacting with the project, the Linux environment requires specific compilers and libraries that match Unreal Engine's toolchain (LLVM/Clang).

**Install required packages (For Arch Linux but should still work with your distros package manager):**
```bash
sudo pacman -S dotnet-sdk clang lld libc++ libc++abi ncurses5-compat-libs git make
```
*   `dotnet-sdk`: Required for Unreal Build Tool (UBT).
*   `clang` / `lld`: The compiler and linker used by Unreal.
*   `libc++` / `libc++abi`: Unreal and its third-party C++ plugins (UE4CMake) link against the LLVM standard library, not the GNU default. Without this, CMake generation fails.

### 2. Project Configuration Fixes
Unreal projects often contain Windows-specific settings that break Linux builds.

**Issue:** The `ChangesWatcher` plugin caused build rule errors.  
**Fix:** Explicitly disable the plugin for Linux in the project settings or engine configuration.
1.  Navigate to the engine directory: `.../Engine/Plugins/Marketplace/ChangesWatcher/`
2.  Edit `ChangesWatcher.uplugin`.
3.  Add `"Linux"` to the `PlatformDenyList` in the Modules section.

**Issue:** The `Diversion` plugin caused build rule errors.  
**Fix:**  Explicitly disable the plugin for Linux in the project settings or engine configuration.
1.  Open the `RoveSoSimulator.uproject` file with a text editor
2.  Scroll down to the plugins section and delete the lines pertaining to the diversion plugin

### 3. Building the Simulator
Building on Linux is a manual, command-line process consisting of cleaning, generating a Makefile, and compiling.

**Step A: Generate Project Files**
This creates the `Makefile` required to compile the C++ code.
*   *Note:* Use absolute paths. Do not use `~` inside quotes.
```bash
/path/to/UnrealEngine/Engine/Build/BatchFiles/Linux/GenerateProjectFiles.sh -project="/path/to/RoveSoSimulator/RoveSoSimulator.uproject" -game
```
**Step A-1: Setup Intellisense**
If you are using VSCode or a derived editor (VSCodium, etc.) these steps will enable Intellisense.
```bash
/path/to/UnrealEngine/Engine/Build/BatchFiles/Linux/GenerateProjectFiles.sh -project="/path/to/RoveSoSimulator/RoveSoSimulator.uproject" -vscode
cd /path/to/RoveSoSimulator
link .vscode/compileCommands_RoveSoSimulator.json compile_commands.json
```
Get the Clangd extension for your editor and disable the Microsoft C++ Extension if its installed. Open the `RoveSoSimulator.code-workspace` file with your editor and the Clangd extension should automatically begin scanning headers once you open a source file. 

**Step B: Compile (Make)**
Compiles the Editor binaries for the project.
```bash
make RoveSoSimulatorEditor Development Linux
```

**Troubleshooting CMake Errors:**
If you see `cannot find -lc++abi`, ensure the dependencies from Step 1 are installed. If installed and still failing, clear the cache:
```bash
rm -rf Intermediate/CMakeTarget
```

### 5. Running the Simulator
Launch the Unreal Editor with the project loaded.
```bash
/path/to/UnrealEngine/Engine/Binaries/Linux/UnrealEditor "/path/to/RoveSoSimulator/RoveSoSimulator.uproject"
```

## Troubleshooting

### Visual Studio is Required?

It seems that only the dotnet sdk is required, install instructions [here](https://learn.microsoft.com/en-us/dotnet/core/install/linux). 

### Getting the Diversion Plugin

The simplest solution to getting the plugin will be to ask another team member to zip/tar their copy of the plugin and send it to you. The location of the plugin varies depending on platform and method of install:

- Windows: `<UNREAL-EDITOR-INSTALL-LOCATION>\Engine\Plugins\Marketplace folder\Diversion`

  Default install location is `C:\Program Files\Epic Games\UE_<VERSION>`
- Linux: `<UNREAL-EDITOR-INSTALL-LOCATION>/Engine/Plugins/Diversion`
- Project: `RoveSoSimulator/Plugins/Diversion`

### Build Failure Due to RoveComm_CPP

See [Troubleshooting Cloning](../setup#troubleshooting-cloning)

## Build Failure Due to Missing "PlatformFilemanager.h"

Navigate to `<UNREAL-EDITOR-INSTALL-LOCATION>/Engine/Source/Runtime/Core/Public/HAL` and run the following:
```bash
cp PlatformFileManager.h PlatformFilemanager.h
```
