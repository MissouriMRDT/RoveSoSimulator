# Implementing Talos (2025), Experience 2
This is documentation of an additional experience of implementing the Talos (2025) rover into the simulator. It was done with Hyperon 2024 and an already assembled Talos 2025 as a reference, though the latter will not be referenced in this documentation.

Additionally, due to an issue with the implemention of Hyperion's skeleton, most of Talos had to be made the same way as Hyperion, verifying that it was consistant with Hyperion as it developed. If you wish to make a copy of Talos and alter it to make a new rover, this tutorial will not be as useful, though you may find some value in the processes.

Finally, [this youtube video](https://youtu.be/Wc6lUXOhRO0) was referenced in part to make Talos, as it was originally used to make Hyperion. The suspension part is where the usage ends (not inclusive). Also, if you follow only the video, it is noteworthy that you should copy-paste the rover blueprint rather than make a new ones, especially for the main rover blueprint, which contains a lot of nodes for other simulator interactions.  

## Initial Import - Static Mesh

The Talos model was imported into unreal as a static mesh from an fbx file. I believe all the defaults for importing were used, as was done in the video. 

The model was missing some pieces, such as a connector for the ZED camera (a piece in the front), the poles on the top which are used for gimbal cameras, and any extra pieces such as science modules or the arm. 

The fbx file did **not** contain an armature or animations; it was only vertices, edges and faces with basic materials assigned to them. Additonally, the quality of the geometry varies due to the original file being far too big, so many circles and small pieces can be rather jagged or overlap where they shouldn't. These details tended to be small enough to be negligable. Also, the mesh was technically in "pieces." Most components, as big as the wheels or as small as the screws, did not have any connection to their surroundings; this is good for texturing and moving large pieces, but is more of a burden when selecting lots of small pieces.

## Skeleton and Skeletal Mesh

## Physics Asset

## Control Rig

## Animation Blueprint

## The Blueprint

### The controls

## Assigning as main

## Jangly legs issue

### debugging by substituation

## Repositioning Other Components (LED and Cameras)

## A few notes on Unreal 
#### File Movements
+ Packing all of the materials into a folder affected nothing.
+ Moving the specific rover folder into a new set of rovers folder did not affect anything
 + Unreal's references allow you to select from all applicatable options; e.g. changing a material offers only materials. This is likely part of the reason the file changes don't cause problems. 
#### Copy, paste, delete
+ Copying files and other things can be chaotic in unreal. If you want to duplicate something though, the way is simple---if unintuitive. Just try to move it by dragging the file where you want the copy, and unreal will prompt you with whether you want to copy or move it there.
 + Fun Fact! Unreal 5.6 does not support importing Uasset files --- what it saves files as in its projects! There may be a technical reason, but I still hate it. 
+ If you can't delete something from the right-click menu, try pressing the delete or backspace key. 
 + If that doesn't work, try to find an editor or similar where you can add more of whatever you want to destoy. If you can create it, you should be able to destroy it.  
File system move things ++++
#### Windows/Content Browser
Don't like the content browser being something thats not always on screen/that covers up the bottom? Right-click on a file and select "Show in new content browser" near the top. This will generate a tab with the content browser, so you can put it wherever you want. Very nice for opening several things in a row.
## Input
## Material Change
