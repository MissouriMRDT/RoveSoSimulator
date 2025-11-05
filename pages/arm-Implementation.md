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

+ make an inch
+ make points at the measurements
+ make connector at that point for the given axis

####
++++++++++++++++++

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
