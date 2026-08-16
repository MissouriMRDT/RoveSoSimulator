---
title: Debugging In Unreal
---

This document contains methods/infomation for general and specific debugging.
This includes information such as detailing how basic things like duplicating files works in unreal and how Unreal's Diff feature for comparing blueprints works.

### Copying

Duplicating a file is very useful for making backups or alternate versions for debugging. Selecting a file in the content brower and using ctrl-d or ctrl-c and ctrl-v are easy ways to copy a file and keep it in the same location. To copy something to a different folder, dragging the asset (copy or original) to a file location (new or not) brings up a menu to...
+ copy the asset
+ move the asset, or
+ use "advance copy here", which also affects dependencies (ex. copy a mesh and its materials, mesh copy will reference material copies). Untested by me.

### Comparing Blueprints

You can use a Diff against featrue to compare two blueprints (any class, same or different). 
<br>
With a blueprint open and selected (in view, so tab selected) you can use the Asset button at the top left (with File and Edit and such) to access Diff Against, or you can right click an asset in the content browser and select the option.<br>
<br>
To get an old version from diversion, you can select a commit with the asset, use the all items tree to find it and select send to workspace to **overwrite it** (Above display for file, with download, looks like a circle with an arrow going to the left). To keep your copy, rename it (not entirely tested), and send the old version, or commit it, send the old version to your workspace, move that one, and then send the current/committed version back. Alternatively, download it (untested) to somewhere else.<br>
Also noteworthy that having two assets of the same name breaks some features I believe. I recommend renaming the fetched copies. <br>
(One issue seemly was opening up the blueprints. Defaulted to the older one (the non import)? resulting in being unable to look at the import alone. Diff still worked though.)

#### Flaws
Defaults
+ not being able to identify reordered sections as the same (no idea why it orders the way it does)
+ hiding some differences between closed sections. (need to open some to see differences)
+ Graphs are not compared
Components
+ differences not highlighted. Entirely manual :(

### CPP Files

The main way to debug CPP files is to use the LOG macro. Because of its nature, statements need *not* end with a semicolon. For possibly more general information, search for UE_LOG on the Epic Games website (no link, their pages change too much). <br>
<br>
Log statements are weird but simple. The first argument allocates the type to print, and the second is the value to log.
The first argument, a string (const char *) is usually a percent sign followed by at least one letter. The Epic Games page should contain all the letters, but here are a few common ones;
+ "%f", float
+ "%d", integer
+ "%hs", string (const char *)

Log statements can be found in the Unreal Engine Log in Visual Studio, and are part of the RoveSoSimulator catagory. <br>

At the moment, I am uncertain whether or not this is custom to RoveSoSimulator. UE_LOG is not, however. <br>

### Command Line

The command line is quiet useful for debugging while the game is running, and for seeing things like physics. It can be accessed in game by hitting \`/~, which is the key to the left of the 1 key. Hitting it twice shows terminal history as well, and three times closes it. Using the up and down arrows, you can get previous commands.<br>
<br>
Capitialization does not appear to matter.<br>
<br>
Here is a list of potentially useful commands:
+ `Show Collision` ; shows collison :O . Useful if you want to see hitboxes. Can also be gotten with alt-c when playing in editor.
+ `ShowDebug Vehicle` ; shows information relating to ChaosVehicles. This includes mph, acceleration, throttle (seemed inaccurate), brake, wheel friction, wheel load (newtons), etc. 
+ `r.SetNearClipPlane 0.1` ; changes how close the camera can get to objects before it sees through them. Good for arm.
<br>
When attempting to do commands, the recommendations won't tell you about any arguments. If the command appears to be about a property but when ran just gives information about the property (and how its been set) try adding a 1 or a 0 (space before) to the end, likely setting it to true/false or 1 or 0 or whatever.

### Miscellanous

Flipping the rover currently also kills its momentum (super brake, not =0, therefore not absolute), so use that if you need to stop quickly.
