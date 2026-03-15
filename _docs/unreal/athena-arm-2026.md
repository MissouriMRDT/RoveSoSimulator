---
title: Athena Arm 
---

## Athena Arm Implementation -- Incomplete
This is the documentation for the addition of the 2026 Athena Arm into the Simulator. This is the first arm to be *converted*, e.g. the original arm template has been created with another arm, but this is the first new arm.

### Pre Unreal
The arm mesh was originally imported from CAD and then modified in Blender 5.0. The mesh was decimated by using limited dissolve, removing small pieces, separating pieces into groups to decimate them differently, then decimating all the groups with the decimate modifier at a ratio of 0.3, and finally adding some basic cylinders to replace some gears and motors. To rephrase it simpler; 
1. limited dissolve was used on the full mesh
2. Pieces were taken off; done by taking everything that seemed necessary and then adding more when it wasn't enough, and dropping off pieces that had a lot of vertices but weren't very noticable.
3. They were separated into groups, but all groups were given the same (decimation) treatment, so giving them all the same modifier at once *may* work just as well
4. Pieces were all decimated with a ratio of 0.3; I believe that means 3 vertices replaced every 10. Total count; 33,681 vertices, 91,000 edges, 70,000 faces.
5. Cylinders were added to replace gears and motors; gears had a lot of vertices, and motors had a lot of sections. Replaceing them with very short and very tall cylinders respectively preserved the look while using *significantly* less vertices.

Exported as fbx, limited to selected objects, only "Mesh" for object types, scale 1, Forward Z-forward, Up Y-up, apply all local scalings, apply unit checked.

### Into Unreal
Imported arm form .fbx file as a static mesh. Kept all materials laid out until static mesh verified as the last import. 
[imageNeeded]

New folder created for arm. Duplicated old arm's blueprint, skeleton, control rig, and physics asset. Renamed as necessary.

### Skeletal Mesh
Converted static mesh to skeletal mesh with existing skeleton---the newly added and renamed skeleton for the arm. Default bone set to "root".

Verified the skeletal mesh could be weight painted. Saved all assets.

Edited Skeleton; used "T" (also a GUI button) to be able to select vertices.
1. Selected desired bone in heirarchy
2. Selected "update children" if applicable
3. Selected geometery whose average location would be where I want the bone. Click and drag to select a group. Shift to add to the group, ctrl to subtract. Change perspectives to more easily deselect sets
4. Pressed V to snap bone to vertices
5. Reset bone rotation and usually reset some location axi to zero.

Set root bone to the upper-back-right (right from back of rover looking forward) vertice of mounting piece;  
[imageNeeded]

Gripper Position in arm mesh is annoying to change; found to be 58 degrees open. Future changes take this into account. Also, G4L/R set to be at 32 degrees (90-58 = 32; compliementary angle).

Additionally---at least as I'm typing this---I am planning to alter how the gripper's hierarchy works, making the inner pieces the main drivers and the outer pieces follow by inverse kinematics. This may, however, give some inconsistency between the speeds for opening and closing the gripper, and may also cause problems with the physics implementation.

Mirror Toolset was not used for gripper movements, though it may work with some alterations.

Gripper Right side had an extra 180 degree rotation on the x-axis removed; may affect control rig. 

<br>

Weight-painted mesh. Note; xAxis bone is the "mount"; the x-axis itself is not bound to it, but the shoulder piece is. Selected the bone you want, a vague area of vertices you want, press flood, then replace (1.0), and then move on to the next bone.

Physics asset assigned. Control Rig assigned as default animating rig (likely no effect).

### Control Rig (Redone)

Reassinged Preview Mesh and refreshed skeleton (in "rig hierarchy", right-click on the most-parent bone (probably root), select "refresh" and pick the desired skeleton mesh). There were extra bones in mine; I did not get rid of them because it gave a warning, but it theorectically wouldn't matter.

#### Inital
Everything up until "Change" (heading 4) is from by inital changes, *many* of which are irrevelant because of me switching to feeding values directly into the control rig (further detailed in "Change"). 

Flipped xAxis limits and default to y axis. Measured total length of x-axis in Blender from two mirror-opposing points ("same thing but opposite side", not sure the term), then subtracted *twice* the distance between the center of the mount and the closer point that was previously measured (on the side the x-axis was on...weird to phrase. point is, arm was in a position that I could measure it). Measurements came out to 34.6538 cm. Cut in half for initial position.  

Adjusted bone axii, initial and updating, and control shapes---much of this would be reduced if both arms faced the same direction. Athena is in the more logical one though---but it may also be flipped 180.

Worth noting; you probably want to set the default bone positions to zero, *then* do the "updating" changes, *and then* do the initial positions (b/c overriding).  

*Controls are the...usually red circles and boxes and whatever else used to move the skeleton in the control rig editor. The shapes are only for the editor, but it can make the testing easier. Right-clicking in the preview area gives a menu with the option "snap offset to nearest bone" or similar; use this.

Wrist did need a limit this time around; only done in blueprint as of me writing this.

Gripper was offset on mesh; shifted 32 degrees, and then decreased by 3 (to 29) to make the grippers not intersect each other.

#### Change
Made "AlterBone" function, which takes in an x, y, or z value in the vector, a bone name, a boolean on whether to rotate or transform, and an execution feed. Uses quaternions to rotate the bones, and does not apply any limits. Also, **does not use controls,** so they no longer work.

Defined a variable for each joint (J1-J6), plus the gripper open-close and the newly renamed "poker." May also be one variable per control.

Each variable feeds into an AlterBone functionality. Default values for each variable defines the initial position of the arm (inital position and rotation of each joint).

### Blueprint
Reassigned skeletal mesh and control rig components. 

Refreshed limits, including adding one for the wrist. Solenoid renamed to "poker;" change not complete yet. Also, poker not yet given a limit (as of writing).

Make sure the axiis on the limits are also refreshed (both rate and max and min). Additionally, the negatives and positives of the contorl rig will not necessarily match that of the blueprint.

Lasers repositioned to where I think they are supposed to be.

+++++++++
### Source Files
### animBP (problem)
### materials?
### Athena

####further implementation
camera positions (+shoulder cam?)
lasers
exact limit of poker, wrist, J2 (same) and J3 (j shape)
rest position?




