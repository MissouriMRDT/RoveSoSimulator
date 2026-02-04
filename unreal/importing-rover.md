---
title: Importing the Rover
---

## **Technical Documentation: Importing and Rigging the Talos2025 Rover**

**Project Goal:** To import the new `Talos2025` Mars Rover 3D model into the Unreal Engine simulator, fully rig it as a drivable vehicle, and troubleshoot any issues encountered during the process. The existing `Hyperion2024` rover serves as a reference for the required components and final functionality.

### **Chapter 1: Initial Asset Import and the First Hurdle**

The first step in any asset pipeline is to get the 3D model into the engine. This initial stage immediately presented our first major technical distinction.

**Step 1.1: Importing the Model**
The `Talos2025` model was provided as a standard 3D file (e.g., FBX, OBJ). This was imported into a new `Talos2025` folder in the Content Browser.

**Step 1.2: The Static Mesh Problem**
Upon import, the rover existed in the engine as a **Static Mesh**.

*   **What this means:** A Static Mesh is a rigid, immovable object. It's like a statue. It has no concept of bones, joints, or moving parts. This is suitable for environmental props like rocks or buildings, but not for a vehicle.
*   **Challenge:** A Static Mesh cannot be used for a vehicle that requires rotating wheels and a physics-driven chassis. Attempting to use it would mean the rover would be a single, solid block with no moving parts.

This led to the immediate conclusion that we needed to convert the model into a **Skeletal Mesh**.

### **Chapter 2: The Skeleton - The Heart of the Vehicle**

A Skeletal Mesh is a 3D model that is bound to an internal "skeleton" or "armature." This skeleton is what allows for animation and the attachment of physics to individual parts, like wheels.

**Step 2.1: The Idea of Reusing the Existing Skeleton**
Our first idea was to save time by reusing the skeleton from the previous year's rover, `Hyperion2024_Skeleton`.

*   **The Theory:** If the new rover's basic structure (one body, six wheels) was similar to the old one, we could simply "reskin" the old skeleton with the new mesh. This would allow us to instantly reuse the old Animation Blueprint, Physics Asset, and other components, saving significant time.
*   **Challenge: The Failure to Assign the Skeleton.** We attempted to re-import the `Talos2025` model and assign the `Hyperion2024` skeleton during the import process. This repeatedly failed. The engine would not allow the assignment, essentially reporting that the skeleton and mesh were incompatible.
*   **The Reason:** For Unreal Engine to share a skeleton, the bone names and hierarchy inside the 3D model file must **exactly match** the bone names and hierarchy of the target skeleton asset. The `Talos2025` model had no internal skeleton, so there were no bone names to match. This was a critical roadblock that invalidated the reuse approach.

### **Chapter 3: The Manual Rigging Process in Unreal Engine**

Since we could not reuse the old skeleton, we had to create a new one from scratch for the `Talos2025` model directly within Unreal Engine.

**Step 3.1: Converting to a Skeletal Mesh**
First, we converted the `MarsRover2025` Static Mesh into a Skeletal Mesh asset. This created the asset but with only a single "root" bone.

**Step 3.2: Creating and Positioning the Bones**
Using the Skeletal Mesh Editor's skeleton editing tools, we manually added a new bone for every moving part of the rover. This included:
*   A primary bone for the main chassis.
*   A bone for each of the six wheels.
*   Bones for the suspension "knuckle" and arm components.

Each bone was carefully positioned at the exact pivot point of the part it was meant to control (e.g., the center of the wheel hub for wheel bones).

**Step 3.3: Skinning the Mesh (Assigning Weights)**
After creating the bones, we faced our next challenge. The bones were present but had no connection to the visual mesh. This is the **skinning** or **weight-painting** process.

*   **Challenge:** The bones were visible in the editor but were grayed out in the Skeleton Tree, and moving them did nothing. This was because we were in "Skeleton" editing mode, not "Skinning" mode.
*   **The Solution:** By switching to the "Skin" tab in the Skeletal Mesh Editor, we were able to assign vertices of the mesh to each bone. For a rigid object like a rover, this involved:
    1.  Selecting a bone (e.g., `LeftFrontWheel`).
    2.  Selecting all the vertices that make up the visual mesh of that wheel.
    3.  Binding those vertices with 100% influence to the selected bone.
    4.  This process was repeated for the chassis and every other moving part until the entire rover mesh was fully weighted to its new skeleton.

At the end of this stage, we had a complete, fully rigged `MarsRover2025` Skeletal Mesh with its own unique skeleton.

### **Chapter 4: Creating the Physics Asset**

A rigged mesh still doesn't know how to collide with the world. That is the job of the Physics Asset.

**Step 4.1: Asset Creation**
We right-clicked our new `MarsRover2025` Skeletal Mesh and chose `Create -> Physics Asset -> Create and Assign`.

**Step 4.2: Configuring Collision Bodies**
The Physics Asset Editor allowed us to create simplified collision shapes and attach them to the bones of our new skeleton.
1.  **Chassis:** A simple `Box` shape was created and scaled to cover the main body, attached to the root bone.
2.  **Wheels:** A `Sphere` shape was created for each wheel bone and sized to match the visual wheel.
3.  **Suspension:** `Capsule` shapes were used for the suspension arms to provide more accurate collision.

**Step 4.3: Setting Physics Types (A Critical Step)**
This was another crucial point where a common mistake can be made.
*   The main body's collision shape was set to **`Simulated`**. This allows it to be affected by gravity, forces, and collisions—it's the physical part of the rover.
*   The collision shapes for **all wheels and suspension arms** were set to **`Kinematic`**. This is vital. Kinematic bodies are driven by animation, not physics. This setting prevents the wheels from simply falling off the rover due to gravity and ensures they follow the commands of the Animation Blueprint.

### **Chapter 5: Assembling the Drivable Rover Blueprint**

With all the foundational assets created, we assembled them into the final, drivable `WheeledVehiclePawn`.

**Step 5.1: Asset Replication**
Following the `Hyperion2024` example, we created the remaining necessary components in our `Talos2025` folder:
1.  **Wheel Blueprints:** We created `BP_Talos_FrontWheel` and `BP_Talos_RearWheel` blueprints (parent class: `VehicleWheel`) to define the radius, width, and steering angle of our wheels.
2.  **Animation Blueprint:** We created an `AnimBP_Talos_Rover` to visually drive the rotation of the bones. A simple `Wheel Controller for WheeledVehicle` node was used to handle wheel spin.
3.  **Main Rover Blueprint:** We created a `BP_Talos2025` (parent class: `WheeledVehiclePawn`). Inside this blueprint, we:
    *   Assigned our `MarsRover2025` Skeletal Mesh to the `Mesh` component.
    *   Assigned our `AnimBP_Talos_Rover` to the mesh's `Anim Class`.
    *   In the `VehicleMovement` component, we configured the `Wheel Setup`, creating an entry for each of the six wheels and carefully typing in the matching **Bone Name** from our custom skeleton.

### **Chapter 6: Final Troubleshooting and Success**

The final step was to place the `BP_Talos2025` in the level and test it. This revealed the final set of challenges.

*   **Challenge 1: The Floating Rover.** When we pressed Play, the rover would spawn but float in the air, completely unaffected by gravity. It also would not respond to controls. The Physics Asset worked fine on its own, so the problem was in the Blueprint.
    *   **The Cause:** The `Collision Presets` on the `Mesh` component inside the `BP_Talos2025` blueprint were incorrect. For a vehicle to interact with the world, its collision must be enabled and set to the `Vehicle` preset.
    *   **The Red Herring:** We initially suspected the grayed-out "Simulate Physics" checkbox, but learned that this is normal for a `WheeledVehiclePawn`, as its physics are automatically managed by the `VehicleMovementComponent`.

*   **Challenge 2: Rover Driving Sideways.** After fixing the collision, the rover would fall to the ground but would not drive correctly. Throttle would cause it to slide sideways.
    *   **The Cause:** The 3D model was authored facing the `-Y` direction. Unreal's vehicle system is hard-coded to assume that the `+X` direction is "forward."
    *   **The Solution:** We had to go back to the 3D modeling software (Blender), rotate the model and its skeleton to face the `+X` axis, "Apply" the transforms, and re-export. We then reimported the mesh in Unreal.

After fixing the collision presets and the forward-axis orientation, the `Talos2025` rover behaved as expected. It now correctly simulates physics, responds to player input, and is a fully functional, drivable vehicle in the simulator.