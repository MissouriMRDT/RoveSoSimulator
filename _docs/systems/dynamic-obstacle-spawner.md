
# Procedural Obstacle Spawner (`BP_DynamicObstacleSpawner`)

## 1. What It Does
The `BP_DynamicObstacleSpawner` is a highly optimized, procedural generation tool designed to create randomized fields of environmental hazards (rocks, craters, debris) for the rover to navigate. Instead of spawning hundreds of individual, resource-heavy Actors, this tool dynamically pools and renders obstacles using **Hierarchical Instanced Static Meshes (HISM)**. It supports vast visual variety by automatically generating a pool of rendering components based on a custom list of 3D meshes provided by the user.

## 2. Location & Dependencies
* **Blueprint Location:** *(`Content/MRDTProcedural//BP_DynamicObstacleSpawner`)*
* **Dependencies:** 
  * Requires **Static Mesh** assets to be assigned in the Details Panel to function.
  * Optionally interacts with UI/Editor utility buttons to trigger the **Clear** or **Refresh** functionality.
  * Relies on the Unreal Engine Chaos/Physics system (instances retain collision data for the rover to interact with).

## 3. Why It Is Needed
**Performance (Optimization):** Spawning 500 individual "Rock Actors" would severely degrade the simulator's frame rate and CPU performance due to draw calls and actor overhead. Using HISMs groups identical meshes into a single GPU draw call, allowing for massive, dense obstacle fields with near-zero performance cost.

**Visual Variety (The HISM Pool):** By default, a single HISM component can only render *one* specific 3D model. If we only used one HISM, the entire map would be covered in the exact same rock. This tool was created to bypass that limitation. By dynamically creating an array of HISM components at runtime, we can feed the spawner 10 different meshes, and it will effortlessly mix and match them across the landscape, providing realistic terrain variance for autonomy testing.

## 4. How It Works in Detail
The spawner operates in three distinct phases:

### A. Initialization (The Construction Script)
When the Spawner is placed in the world (or when the game starts), the Construction Script reads the user-defined `ObstacleMeshes` array. 
1. It clears out any old data from the `HISM_Pool`.
2. It runs a **For Each Loop** through the `ObstacleMeshes` array.
3. For every mesh in the list, it adds a new, invisible `Hierarchical Instanced Static Mesh Component` to the Actor.
4. It sets the component's mesh to the current array element, and adds the newly created component into the `HISM_Pool` array.

### B. Spawning Logic (Generation)
During the generation phase, the blueprint determines random transforms (X/Y coordinates and rotations) within the defined spawn area.
1. Right before spawning, it uses a **Random Integer in Range** node (from 0 to `HISM_Pool Length - 1`).
2. It retrieves the randomly selected HISM component from the `HISM_Pool`.
3. It calls **Add Instance**, plugging in the random transform. 
4. This results in the tool randomly picking a different rock/crater type for every single generated obstacle.

### C. Clearing and Refreshing
To prevent the level from becoming cluttered or to allow on-the-fly layout regeneration, a **Clear Event** is utilized.
1. It runs a **For Each Loop** across the entire `HISM_Pool`.
2. It calls **Clear Instances** on every component, instantly wiping the physical and visual meshes from the map without deleting the components themselves.
3. If acting as a **Refresh** button, the `Completed` pin of this loop immediately triggers the Spawning Logic to generate a brand new map layout.

## 5. How to Use It

**Step 1: Placement**
Drag and drop `BP_DynamicObstacleSpawner` from the Content Browser into your level. Then spawn the rover into the world as it is what calls the spawner to generate the obstacles when the game starts.

**Step 2: Defining the Spawn Area**
There are input fields in the Basestation UI where you can specify the dimensions of the spawn area (e.g., 100m x 100m) and the number of obstacles to generate. Adjust these parameters to create a denser or sparser field of hazards for the rover to navigate.

**Step 3: Adding Meshes**
1. Select the Spawner in the level viewport.
2. Look at the **Details Panel** and find the `Obstacle Meshes` variable.
3. Click the **[+]** icon to add new slots to the array.
4. Drop in any Static Meshes you want to spawn (e.g., Martian rocks, craters, debris, sample return tubes). You can add as many as you like; the system will scale automatically.

**Step 4: Generation**
* Play the level. The spawner will automatically generate the obstacles based on your parameters. 
* To clear or reroll the map during runtime, press the designated UI button or trigger the custom event linked to the Clear/Refresh logic.