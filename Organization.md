## RoveSoSimulator Organization
This document aims to give an overview of where things are stored and edited for RoveSoSimulator. 

### System/Version Notice
We are currently on Unreal Engine 5.6.1. <br>
We have several additions;
+ RoveComm - MRDT Library needed to send information to autonomy. Packets and Such.
+ UE4CMake; thirdparty download, for compiling RoveComm in an Unreal friendly way 
+ Sentry; thirdparty download, bug/crash reports
+ ChaosVehicles - Unreal Engine Plugin used for the rover. Designed for full on cars, but still flexible for things like motor bikes. Much harder to get information on, but still Unreal-supplied.

### What to edit with Unreal Editor vs. IDE

Programming with Unreal Engine is done in two main "regions"; the editor itself, and your Coding environment of choice. <br>
The latter is for the C++ work, which is generally the easiest for anything logic based, and should contain most actual logic for assets. <br>
The former contains most other things, including
+ visible, movable, and/or physics-interactable meshes
+ UI Layouts (but not there logic...for the most part. Transition in progress)
+ Materials (textures, colors)
+ Sets of Assets; Levels and blueprints. 
  + Levels are just the "world" played in. They are functionally weird blueprints.  
  + Blueprints are a broad category, but are generally a way of combining assets with other assets and/or setting up logic without C++ files. Examples;
    + Actor; Something placed or spawned in a world. Aka, part of a level thats not a single asset (single asset would be, say, a static mesh).
    + Pawn; Actor that a player controls.
    + RoverVehiclePawn; a custom blueprint, which connects to a c++ class, and derives from a ChaosVehicles pawn.
    + Actor Component; "reusable component that can be added to any actor"
    + Other niche examples from a list; ARActor, AmbientSound, BaseTransformGizmo, CameraRig_Crane, ChaosCacheManager
+ Input Assets (for now, not long?)

Currently, most logic is in the C++, but some, especially for the arm, is still primarily if not entirely blueprint.<br>
Also, blueprints contain the instances of the C++ assets, so to modify some characteristics such as the weight of an individual rover, it is often easiest to find the property in the blueprint. Custom properties in the C++ need to be exposed to the blueprint, but many values are edited in the blueprint specifically, since the values are part of the components of the blueprint. <br>
<br>
Editing any individual asset type is its own tutorial (that may or may not be written), especially for Sketetal Meshes and Physics Assets.

### Organization, In the Unreal Editor (.uassets); /Content/
In the Unreal Editor, the Content Browser is used to access folders and files and assets. <br>
Most if not all Unreal Editor content is in the `/Content/` Directory. <br>
It is not currently particularly organized, but each directory is fairly self explanitory. A few notes;
+ AncientContent and Fab are for specific maps and are very big. AncientContent should not be downloaded unless you specifically choose to get it, but I'm not entirely sure thats working.
+ MRDTModels contains more than the usual directories; it currently contains the rovers, arms, arm testing assets, autonomy testing objects, and some other nonsense.
<br>
There are actually more directories than `/Content/`, as you can see in the Content Browser, but the others are...
+ the custom c++ classes, which just open in an IDE, 
+ plugin c++ classes, like for sentry, and
+ Assets from the engine, from which about everything else derives
If you need any of these, it will probably be the custom c++ classes for one of many routes to making one, or some assets from the Engine.

### Organization, In Visual Studio and Similar (C++ files); /Source/
The C++ files are mainly in the `/Source/` directoy, viewed in an IDE or file browser. The only file not in the Private or Public directories that you are likely to edit is the `.Build.cs`, which is for plugins and such. <br>
The Categories of the Private/Public Directories are
+ Components - Not sure. RoveComm and Procedual Generation Stuff. Also the Map.
+ Core - Game assets (Game Instance, player controller, Input manager) and Parent Classes (general rover, general arm)
+ RoveComm - RoveComm Stuff. Wrappers.
+ Rovers - Individual Rovers, so Athena and Talos and such, but not the general rover stuff
+ UI - Menus and stuff
+ Widgets - More UI stuff

### Organization, in a File Directories (All the Files)
In a File browser, there are many directories. The `.stuff` I will not discuss.
+ Binaries is compiled stuff 
+ Intermediate is used for compiled/ing stuff
+ Build - Idk
+ Config - Most things in the project settings area of the Unreal Editor
+ Content - The assets. Primarily .uassets, primarily for Unreal Editor
+ Installers - Used to Package the game for steam and such
+ PackagedGame - See above. Location for that data.
+ Plugins - Exactly what it sounds like. Not the Unreal Engine supplied plugins, however, but truely third party ones like sentry. 
+ Resources - Idk. May be plugins, a little.
+ Saved - Logs, Autosaves, some other stuff. For reference, often deleted with Binaries and Intermediate to facilitate a high level reload.
+ Source - C++ files and all that. Also holds the RoveComm github copy.
There is also a .uproject. This contains other unreal information.
