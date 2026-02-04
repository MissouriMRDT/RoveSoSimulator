---
title: Importing Static Meshes
---

## **Technical Documentation: Importing and Texturing PBR Static Meshes**

**Project Goal:** To establish a clear, repeatable workflow for importing 3D models and their associated textures into Unreal Engine, ensuring they appear physically accurate and visually correct. This guide covers the entire pipeline, from asset preparation to final material setup.

**Case Study:** The `Rock_Pick` model. This asset serves as our primary example, specifically addressing the common issue where a model appears shiny and correct in its authoring software (e.g., Blender) but looks dull and flat upon import into Unreal Engine.

### **The PBR Asset Pipeline**

Physically Based Rendering (PBR) is the industry-standard approach for creating realistic materials. It relies on a set of specific texture maps that describe the physical properties of a surface. A successful import requires both the 3D model and these textures.

**Required Assets**
Before starting in Unreal Engine, you must have the following files:
1.  **The 3D Model:** This should be in a standard format, with **`.fbx`** being the most common and recommended. This file contains the geometric shape of the object.
2.  **The PBR Textures:** These are image files (e.g., `.png`, `.tga`) that correspond to the model. A standard PBR set includes:
    *   **Base Color (or Albedo):** The flat color of the surface, as if it were viewed with no lighting. (e.g., `texture_pbr_...`)
    *   **Metallic:** A grayscale map where white means the surface is 100% raw metal and black means it is a non-metal (dielectric). (e.g., `texture_pbr_..._metallic`)
    *   **Roughness:** A grayscale map that is the key to "shininess." Black means the surface is perfectly smooth and mirror-like, while white means it is completely rough and diffuses light. (e.g., `texture_pbr_..._roughness`)
    *   **Normal Map:** A purple-colored map that creates the illusion of fine surface detail, like bumps and scratches, without adding extra geometry. (e.g., `texture_pbr_..._normal`)

### **Importing Assets into Unreal Engine**

This step brings the raw files into the project's Content Browser.

**Import All Files**
1.  Create a dedicated folder in the Content Browser for your new asset (e.g., `Content/Models/RockPick`).
2.  Drag and drop the `.fbx` model file and all of its associated texture maps directly into this folder from Windows Explorer.

**The Import Dialog**
*   When you import the `.fbx` file, an "FBX Import Options" dialog will appear. For a simple static mesh, the default settings are usually sufficient. Ensure that **`Generate Missing Collision`** is checked if you want the object to have basic physics collision. Click **`Import`**.
*   The textures will import directly without a dialog.

Upon successful import, you will have a `Static Mesh` asset (with a light blue stripe) and several `Texture` assets in your folder.

### **Creating and Configuring the Material**

This is the most critical stage and where the `Rock_Pick` issue was resolved. By default, an imported mesh has a very basic material that doesn't use our detailed PBR textures. We must create a new material and connect them correctly.

**Create the Material Asset**
1.  In your asset folder, right-click and select **`Material`**.
2.  Give it a descriptive name, like **`M_RockPick`**.

**The Problem - A Dull Appearance**
*   **Case Study (Rock Pick):** When the `Rock_Pick` was first imported, it was assigned a default material. This material did not use the Metallic or Roughness maps, so the entire object was treated as a dull, non-metallic plastic. The engine had no information about which parts were shiny metal and which were rough rubber.
*   **The Solution:** The solution is to connect our specific PBR texture maps to the corresponding inputs in our new `M_RockPick` material, providing the engine with the physical surface information it needs.

**Correctly Connecting PBR Textures**
Open your new `M_RockPick` material. You will see a final output node with several inputs. Drag all your texture assets for this model into the material graph to create Texture Sampler nodes. Now, connect them as follows:

1.  **Base Color:**
    *   Take the **RGB** output pin from your `Base Color` texture sampler.
    *   Connect it to the **Base Color** input on the final material node.

2.  **Metallic:**
    *   Take any single-channel output pin (e.g., the **R** pin) from your `Metallic` texture sampler. Since it's a grayscale map, all color channels contain the same information.
    *   Connect it to the **Metallic** input on the final material node.

3.  **Roughness (The "Shininess" Control):**
    *   Take any single-channel output pin (e.g., the **R** pin) from your `Roughness` texture sampler.
    *   Connect it to the **Roughness** input on the final material node. This is the connection that fixed the `Rock_Pick`'s dull appearance.

4.  **Normal Map (Special Case):**
    *   Take the **RGB** output pin from your `Normal Map` texture sampler.
    *   Connect it to the **Normal** input on the final material node.
    *   A Normal Map requires a one-time setup. Go to the Content Browser and double-click the normal map texture asset itself. In its settings window, find the **Compression** category and change the **Compression Settings** to **`Normalmap (BC5)`**. Save the texture. This tells Unreal to interpret the colors as directional vectors, which is essential for the effect to work.

After connecting all the nodes, your material graph should be clean and direct. Click **`Apply`** and **`Save`** in the Material Editor.

### **Final Assembly**

The final step is to assign your newly created, physically accurate material to the 3D model.

**Assigning the Material**
1.  In the Content Browser, double-click your `Rock_Pick` Static Mesh asset to open it.
2.  In the `Details` panel on the right, you will see the `Material Slots`.
3.  Find the material slot you want to change. Click the dropdown menu and search for your new material, **`M_RockPick`**.
4.  Select it. You will immediately see the model in the viewport update with its correct, shiny appearance.
5.  Save the Static Mesh asset.

Your model is now fully imported, textured, and ready to be placed in any level. This same workflow—**Import -> Create Material -> Connect PBR Textures -> Assign Material**—can and should be used for any static mesh to ensure it is rendered realistically and correctly within the engine.