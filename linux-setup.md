# RoveSoSimulator Linux Setup

When attempting to setup RoveSoSimulator on Linux, it is likely that you will encounter multiple roadblocks, primarily to due with Unreal Editor's disaffinity for Linux. This guide will document known issues and workarounds, if you have a novel problem or solution please add it to this section of the docs.

## Installing / Running Unreal Editor

Make sure to download the Linux version [here](https://www.unrealengine.com/en-US/linux) by selecting the `Linux_Unreal_Engine_X.X.X.zip` download.

The path to the executable once extracted is `./Engine/Binaries/Linux/UnrealEditor`.

## Visual Studio is Required?

It seems that only the dotnet sdk is required, install instructions [here](https://learn.microsoft.com/en-us/dotnet/core/install/linux). 

## Getting the Diversion Plugin

The simplest solution to getting the plugin will be to ask another team member to zip/tar their copy of the plugin and send it to you. The location of the plugin varies depending on platform and method of install:

- Windows: `<UNREAL-EDITOR-INSTALL-LOCATION>\Engine\Plugins\Marketplace folder\Diversion`

  Default install location is `C:\Program Files\Epic Games\UE_<VERSION>`
- Linux: `<UNREAL-EDITOR-INSTALL-LOCATION>/Engine/Plugins/Diversion`
- Project: `RoveSoSimulator/Plugins/Diversion`

## Build Failure Due to RoveComm_CPP

See [Troubleshooting Cloning](/#3️⃣-troubleshooting-cloning)

## Build Failure Due to Missing "PlatformFilemanager.h"

Navigate to `<UNREAL-EDITOR-INSTALL-LOCATION>/Engine/Source/Runtime/Core/Public/HAL` and run the following:
```bash
cp PlatformFileManager.h PlatformFilemanager.h
```