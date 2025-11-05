Arm Development process
# Under Development
![arm diagram](../assets/images/armDiagram.png) ![arm diagram with rotations](../assets/images/armDiagramRot.png)

## Overview

++++++++++++++++++++++++++++++++++++++++++++++++++

## Part One: Measurements, Mesh, and the CAD Gripper 
Due to the sheer size (# of pieces and vertices) of the arm CAD file, it was decided that it would be easier to make the arm manually with measurements---with the exception of the gripper---rather than process the CAD file directly. The given measurements are as follows; 
x-axis - 21 inches long, 6 inches tall, *Depth*
Carraige - 1 inch of thickness, *height and length* made to match shoulder connection
Shoulder - 5.5 deep from x-axis out, 4.5 side to side, bottom of shoulder level with bottom of x-axis, 
+ **5.7 in wide?** - *not sure what this is, but also written down*
+ **pivot** placed by "5.5 deep from x-axis out" (might not be actual position) and 11 inches above the bottom (of the x-axis) (this part was under bicep, may also be incorrect)
Bicep - pivot (J2) to pivot (J3): 18 in., *depth - fit between shoulder*
Forearm roll - pivot (J3) to pivot (J4) 7.3 inches
Forearm - J4 to "pivot on wrist" **(J5 or J6)** - 11.2 in
Wrist - **no measurements :(**
+ Camera (near gripper, kinda wrist) - Used an image to approximate.

Gripper - **unknown/forgot to write down/get.** Used an image to approximate 

\*\*Bold values are lost/unclear/weren't measured, italized are creator's choice due to negligiblily (also not measured). 

The Gripper was exported without bolts/screws/whatever-I'm-not-mechanical, as an .obj file with measurements set to inches (maybe unnecessary, see next section). A toggle I forget the name of seemed like it would be good to press, but actually caused a bunch of things to have scrambled rotation.
**Double check that the file you get (if you get one) has correct position and orientation. Scale may not matter (or work), but you will want them rotated correctly and positioned so one side is a mirror of the other (rather than one being full up and the other full down or whatever)**

### Creating the mesh
The Mesh was created in Blender. May want to see some tips on how to use it.
The mesh was set up so the lower-left?-rear point of the x-axis is at the origin. 

To make your measurements
1. set up units to be inches (or whatever you are using) by going to Properties (a window type) -> Scene -> Units. 
2. go into edit mode (top left, or click tab sometimes) **after** selecting the mesh (create one if necessary) 
3. select a vertex, press "e" to extrude (create a new vertex connected to the old one), press "x"/"y"/"z" (locks the movement of the vertex to one axis) and type a number (extrude that number of inches in chosen direction)
4. Repeat to create the distances in the file. You can use the measure tool (too long to explain here) to double check your work.

The Pivots
1. The x-axis doesn't need much, but don't forget the carriage exists. I made it shaped like an "I" / sidesways "H", but I geniunely forgot what it looks like.
2. At J2 and J3, creating a cyclinder and a tube bigger than the cylinder at each of the points works well.
  + use ctrl-r and face extruding to get the tubes connected. You may want to cut your tube to have extra disks at both ends to connect the cylinder on one side.
3. At J4 and J5, inseting (extrude down along normal z) a circle base to create a hole for a cylinder works well. Adding the cylinder for the other piece. 

The Gripper
*quick tip! hover over something with your mouse and press "l" to select everything <u>linked</u> to it. This changes slightly if you are in vertex v. face selection mode*
1. Before you join it with everything else, you should probably scale it correctly; importing with .obj (in my experience) doesn't preserve units. It will likely be placed in meters, so look up the conversion and (in edit mode) scale down the whole thing by the right value.
2. Also before you combine it, you can...
   + press "p" in edit mode to separate things, including by loose parts. If you go to "3D Viewport" (window type) -> "Show Overlays" arrow (top right) -> "Statistics" checkbox, you can see how many vertices each thing has. You may want to get rid of the less significant but large vertex count pieces, such as the gears. Otherwise...
   + Using "limited dissolve" (select stuff, press x) can make level triangles turn (back?) into quads, which is better for selection
   + Using "m" or auto merge can reduce the vertices of curves. You can change the threshold for auto merge, and it only applies to stuff you actually move, so if you want some specific pieces to simiplify just select them and press "g" and then "0" to move them no where, activating auto merge. Be careful to keep pieces separate; this will help you later.
   + Decimate. The. Mesh. Do so in the properties tab; Modifiers -> add modifier -> generate -> decimate. The bar-value thing is how much to keep; I found 40% (0.4) changed very little of the geometry, even on the gears, but still reduced vertices to 40% of the original value.
4. You can use ctrl-J to join two meshes together; this can put the gripper pieces back together and combine the gripper with the main mesh. Order of selection should only matter for things not relevant to this tutorial.

Materials were added to each segment of the arm, with most of the gripper being one material. 

### Exporting

Make sure the thing you are exporting is at the origin. The offset will be taken into account when it is packaged.

Go to file -> export -> .fbx (for meshes, and **not the experimental one**)

I suggest using "Include" -> limit to -> "selected objects" and changing object types to just "mesh." Also change "Forward" to Z forward rather than -Z. You can save these presets for later use.

## Importing into Unreal

In the content browser, select "import." I imported it as a static mesh and converted it, but may work better to import it as a skeletal mesh. 
*tip: at least with the static mesh, you can use a reimport button to have unreal reimport the asset from the same file location. Good if you make some changes to the blender version and re-export. Noteworthy that it does not affect the skeletal mesh you create off it. Untested on importing and then reimporting for the skeletal mesh, but other experience found nonsensical conflicts. Unreal truly is one of the Game Engines of all time.*

Should be done as quick as that, though if you experience a bug (crash level) with weight painting later, you may want to see the entry on bugs.

## Venting and bugs
Process Location: Importing the created mesh, weight paint the mesh

#### Issue: 
Unreal Crashes after pressing accept on weight painting.
To be specific, it gives an error message of an "index out of range" error; its not very specific as to what it applies to, but it is the basic "list is # elements, list\[#\] does not exist (b/c 0 is the first entry, so # is the first entry out of range)"
Only occurs when you click "accept" after weight painting. Uploading seems uneffected.

#### Understanding: 
Importing and w-painting different objects was successful. Led to finding that it wasn't the file. 
Importing and w-painting the same object but with pieces removed was successful. Led to finding that it was specific geometry that was the problem.

#### Resolution: 
Geometry fixed on bicep and the gripper's actual gripping surface. Gears also had problematic geometry, but were too complicated to disconnect and sift through, so they were instead deleted. May be left over materials in blend and uasset files.
