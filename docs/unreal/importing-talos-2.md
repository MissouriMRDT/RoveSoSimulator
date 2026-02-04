---
title: Importing the Rover (ext.)
---

# Implementing Talos (2025), Experience 2
This is documentation of an additional experience of implementing the Talos (2025) rover into the simulator. It was done with Hyperon 2024 and an already assembled Talos 2025 as a reference, though the latter will not be referenced in this documentation.

Additionally, due to an issue with the implemention of Hyperion's skeleton, most of Talos had to be made the same way as Hyperion, verifying that it was consistant with Hyperion as it developed. If you wish to make a copy of Talos and alter it to make a new rover, this tutorial will not be as useful, though you may find some value in the processes.

Finally, [this youtube video](https://youtu.be/Wc6lUXOhRO0) was referenced in part to make Talos, as it was originally used to make Hyperion. This implementation deviates from the video at the very first step, but otherswise follows it almost exactly all the way to the suspension part, where the usage of the video ends (suspension part is not used). Also, if you follow only the video, it is noteworthy that you should copy-paste the rover blueprint rather than make a new ones, especially for the main rover blueprint, which contains a lot of nodes for other simulator interactions.  

## Initial Import - Static Mesh
As previously mentioned, this first part deviates from the tutorial a bit. 
The Talos model was imported into unreal as a **static** mesh from an fbx file, rather than a skeleton and a skeleton mesh. I believe all the defaults for importing were used. 

Extra notes;
The model was missing some pieces, such as a connector for the ZED camera (a piece in the front), the poles on the top which are used for gimbal cameras, and any extra pieces such as science modules or the arm. 

The fbx file did **not** contain an armature or animations; it was only vertices, edges and faces with basic materials assigned to them---hence why it was imported as a static mesh. Furthermore, the quality of the geometry varied at different places due to the original file being far too big, so many circles and small pieces can be rather jagged or overlap where they shouldn't. These details tended to be small enough to be negligable. Also, the mesh was technically in "pieces." Most components, as big as the wheels or as small as the screws, did not have any connection to their surroundings; this is good for texturing and moving large pieces, but is more of a burden when selecting lots of small pieces. 

## Skeleton and Skeletal Mesh

After importing the static mesh, a skeleton mesh was created from it. This was done by right-clicking and selecting "convert to skeletal mesh," near the top of the screen. Default options were used, so the static mesh was preserved. A skeleton mesh AND and skeleton were created from this activity.
### The skeleton
The next step was to remake Hyperion's skeleton, which may not be necessary for new rovers. Hyperion's skeleton was, I believe, "baked" into the mesh; basically, permanantly fused to the mesh, which makes it more efficent but harder or impossible to modify. Talos' skeleton should not be baked in, so it may be possible to duplicate it (see notes on file movements) and modify it slightly to match any new rovers.

Either way, the skeleton will need to be altered. Weirdly enough, this is done in the skeleton mesh asset window rather than the skeleton asset itself; so open up the skeleton **mesh.**

+ At the top right of the tab, you should see a skeleton and a body made of triangles. These can be clicked to switch between your skeleton and skeleton mesh, respectively.
  + The animation blueprint and Physics asset should also appear here **when you add them in.** This may be based on you created them from the mesh, or possibly from the blueprint.
+ On the left side of the screen (should be in mesh tab), there is a toolbox tab. The skeleton section can be used to edit the skeleton.
  + If you don't see the toolbox, there should be an "Editing tools" button at the top of the screen, middle, same row as skeleton and skeley mesh buttons.
  + For bone changes; keep in mind you need to press accept to press accept for them to fully save, and that clicking cancel can quite quickly undo your work (hazard; be careful not to *accidentally* press this button.
  + For selecting bones; the point-circle sphere things are the bones. Yellow is the path to its parent (in the heirarchy), and green is to its children. The red is a displacement from the origin or similar; only matters for the root bone.
  + Next to "Edit," where you start in, is the "Add" section, which adds bones (wow!). You shouldn't need this if you can copy paste, but if you can't...
    + while in add, click *precisely* on the bone you want to be its parent. Remember previous point about what the colors mean.
    + from there, click where you want the new bone to be. This system sucks, so use the section (in "Add") "Details" -> "Transform" -> "Location" values to move it precisely. It dones not have to be exact, or at least this Talos and Hyperion were not; see notes later, likely under weight painting.
    +  You can change its name in the details panel as well. The current names on both Talos and Hyperion are terrible, but this may be modified in the future. Stick to the naming sceme on Talos/Hyperion. If you don't, you may be able to change the bone names in the final blueprint and get away with it---untested as of yet, no promises.
  + If you are editing the skeleton...
    + ...you can move it in the viewport, which can be much easier than using the values under "Details." As per previous and a future statement, they do not *yet* need to be exact, but you can use the specific transform value to make it exact if necessary.
    + The names of bones can also be changed here; don't unless you are prepared for possibly a lot more work.

If you are wondering what your actually doing--- you likely need to just either recreate the skeleton on a new rover, or move the bones that they fit the new rover.

### Weight Painting
(This is the *long* part)
Weight painting is the process of assigning vertices to bones, which makes it so the vertices move when the corrisponding bone moves. The "weight" is how much a bone influnces a vertex (vertice?), out of one; a vertex can have weights from several different bones to, say, move to directly in between all of them. For this project, you should only need weight paint values of one and zero. 

I used, in the skin section of the toolbox, "edit weights" to assign weights. Other methods may be possible or even better, but I will only cover this one. In "edit weights," I used the weight editing modes Mesh and Bones only, as these are for more precise control.
+ Use bones mode to control what bone you are changing the influenced vertices of (which bone you are working on).
  + You may also be able to use the skeleton tree on the right.
  + Remember what the colors of bones mean.
+ Use mesh mode to select vertices and assign them weight.
  + select by clicking or making a box. Note that making a box will highlight "through;" that is, you will select vertices behind the ones you can see as well
  + use the flood button under "edit selection" to extend your vertice(s) selection to what is connected to them and connected to them and so on. Good for getting, say, the entire wheel piece from just one initial vertex on the wheel
  + Selecting can be kinda buggy at small levels. However, if you know where the vertices already have weight (by default the root/top bone in heirarchy), you can select all affected vertices, and then click "Isolate selected" (just above "flood"), which will make it so you can only see those vertices. This is useful because...
  + ...selected vertices stay selected when you switch bones! Very nice, though you need to make sure you reset your selected every so often, otherwise you could reassign something again by accident.

#### Some things...don't matter.
As of now (Oct. 2025), only the wheels and in some ways the root actually move. Basically, The wheels go up and down, and everything else tilts forward and backward as one thing. Because of this, it ***currently*** doesn't matter how the MSI and arms/legs/wheel connector thing-a-ma-jigs are weight painted, since those bones are frozen in place.

This may be changed in the future, but it would require some extra details to make the bones actually connect to the wheels and such.

### DONE???

Are the bones in the right place? Do the weights of bones look reasonable? If you question your work, know that you can absolutely fix it later---and the rest of this tutorial together might be equal in length to this weight painting journey. 

## Physics Asset

The Physics Asset is used for collisions.

Right click on skele mesh -> create -> physics asset -> "Create and assign"; "Create" should also work, since you should be able to assign it later if you don't, but I'm not sure where you actually assign it, so good luck if you choose that method. 

As with most things, mimic Talos/Hyperions' physic bodies; 6 spheres for the wheels, a box for the center piece, unspecific capsules for the MSIs, and more specific capsules for the legs/arms/thing-a-ma-jiggits.
**See the final bullet point in the below section if scaling seems like it doesn't work**
### Doing that

Position and Scale added bodies to match the rover, similar to how it was done in the tutorial.

The tutorial covers this quite well, and the defaults for many things also align with the rover. I have a few notes, however.
+ The video mentions...
  + importing a custom mesh - no, we don't have one.
  + Measuring the wheel - its probably fine, and I couldn't get the measurement too to function...so...
+ If you click on a physics body (be careful not to click the colored sphere), at the bottom left in a tab called "graph," you should see a set of connected bodys.
+ I do not completely understand this, but the green boxes are the physic bodies, one of which is the one you have selected, and the others are the kind of the parent or children of the physic body (actually the physic bodys of the bone-parent/children of the current physic body's bone. Weird, right?)
+ The yellow boxes are the constraints. I understand these even less, but the key note is this; you need to lock all the axiis of the MSI and knuckles and legs/arms/yada-yada-yada.
  + You may have seen **annoying red and green spheres** that you can actually select instead of the physic bodies. These (in some way) represent the constraints. I believe you can also click on them and lock all of their axiis, accomplishing what is *probably* the same thing. ( Right side -> Details -> angular limits -> Swing 1 motion, Swing 2 motion, Twist Motion -> lock'em )
    + This was an extremely annoying issue to find and fix. Figured out some good strategies though, which I will mention later.

## The Blueprint

The Blueprint adds a bunch of default and Rover Specific functionality, and makes different components work together.

Copy the blueprint from another rover rather than making a new one like the tutorial says. You do not want to have to copy all the other stuff over AND test it. Also, **for any blueprints, make sure to rename them.**

Initially, selecting the main piece of the blueprint in components gives an overwhelming amount of information on the left. Do not use this menu. It contains some stuff for nodes, some as far as I know used stuff for *clothing,* and very few things you need for this process. Use the mesh (child) directly underneath it and the Vehicle movement component that can be seen at the bottom by closing the mesh's heirarchy and looking below that line that is there for some reason. 

If the tutorial tells you to assign something, you should be good to assign it. If it tells you to create something, probably don't. In fact,
+ Don't make new wheels; instead, swap out the wheels; note the bone names, and the fact that, if you changed them, this *might* be the only place you need to change them again.
+ Don't make a new wheel class asset. Use a copy of the one(s?) from the older rovers. The center and rear don't actually seem to be used, so you might not need to copy them.
+ Copy the torque curve. As with others, don't forget to rename. Also, make sure to actually assign it to the place it was created in the video.
  + This may be altered in the future, since the rover is electic.
+ Don't add controls, enable simulate physics, add it to the world, etc.; move to the next step. The tutorial will resume on Animation Blueprint (directly after blueprint).
*note; there may be some other things in the blueprint that the video has not gotten to yet that need to be swapped out. See future sections.* 

### The Controls

You can see some of this...somewhere in the nodes, but it is far more useful to follow
Edit -> project settings -> Engine -> Input
And see the controls all laid out.

Do not edit these, or at least make sure not to commit the changes.
### Assigning as main

On the same level as the folder MRDT Models should be a folder poorly named "RoveSoSimulator" (or maybe its required idk). This contains an asset/blueprint class called RoveSoSimulatorGameMode. Following Classes -> Default Pawn Class, you should find the blueprint of the rover currently active. Switch it out for the blueprint of the new one you've created. You should then be able to run the simulator with your new rover, *possibly* without animations.

## Animation Blueprint

Resume the tutorial at the animation blueprint stage (skipping/ignoring the rest of "blueprint"). Create as it says

## Control Rig

Create the Control Rig and reconfigure the animation blueprint as done in the tutorial, **and then stop.**
Rover suspension is...different and basically unimplemented in the sim. Besides, this is mainly visual.
You should be done with the tutorial at this point.
Double check the rover still works.

## Repositioning Other Components (LED and Cameras), Material Change

In the rover blueprint, look in the centerpiece--- evil and obvious, the nightmare node-scape. Ignore it, and replace it by switching the tab from "Event Graph" to "Viewport." You should see the rover, plus a camera way behind it and a text-box-thing, and hopefully some other floaty bits. These other floaty bits are the second to last task; one is an LED panel and the other is a ZED camera (not the actual way back in-game camera, but the camera that will go on the rover). Move these...where they should be, which may very but should include the LED panel in the back, clearly visible to the game camera, and the ZED camera somewhere in the front; it should have a slot, but Talos' mesh, for example, doesn't have it. If there is a rear ZED camera now, there will hopefully be a place for it like the one in front; otherwise, ask your lead or put in back somewhere that it can't obstruct the LED panel too much.

Changing the materials was done in the **blueprint** (rather than the mesh), and went from "Mesh" (left panel) -> "Materials" (right panel, ~6 down) -> whatever materials need to be changed. No known order for the whole thing, unfortuately, but for Talos #2 was the body and the last (#18) was the wheels. This will likely vary with the order of how the files are combined together to create the original file. 

## Bugs I ran into and Advice for **Killing them Dead**

(Unreal Issue) Weight Painting Selection problems - see late weight paint bullet point about "Isolate Selected" 
- when weight painting and zoomed in a lot, some vertices would not let me select them


(Results Issue) Jangly legs - see physics asset, annoying red and green spheres
- The legs went wherever they want. Understanding of issue delayed by lack of understanding the lack of animation complexity.

### Debugging by Substitution

Many of the assets between the rovers, at least for Hyperion and Talos, could be substituted for each other with very little, if any, consequence. So; do that. If something is wrong, process of elimation is kinda available.

## A few notes on Unreal 
#### File Movements
+ Packing all of the materials into a folder affected nothing.
+ Moving the specific rover folder into a new set of rovers folder did not affect anything
 + Unreal's references allow you to select from all applicatable options; e.g. changing a material offers only materials. This is likely part of the reason the file changes don't cause problems. There are upsides to using a UI-thing.

#### Copy, paste, delete
+ Copying files and other things can be chaotic in unreal. If you want to duplicate something though, the way is simple---if unintuitive. Just try to move it by dragging the file where you want the copy, and Unreal will prompt you with whether you want to copy or move it there.
 + Fun Fact! Unreal 5.6 does not support importing Uasset files --- what it saves many files as in its projects! There may be a technical reason, but I still hate it. 
+ If you can't delete something from the right-click menu, try pressing the delete or backspace key. 
 + If that doesn't work, try to find an editor or similar where you can add more of whatever you want to destoy. If you can create it, you should be able to destroy it.  

#### Windows/Content Browser
Don't like the content browser being something thats not always on screen/that covers up the bottom? Right-click on a file and select "Show in new content browser" near the top. This will generate a tab with the content browser, so you can put it wherever you want. Very nice for opening several things in a row.
