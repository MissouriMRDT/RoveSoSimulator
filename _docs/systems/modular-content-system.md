# **Technical Documentation: Modular Content System (DLC & Chunking)**

## **1. Executive Summary & Goals**
The RoveSoSimulator project reached a critical mass of **44 GB**, with approximately **36 GB** (81%) attributed to a single high-fidelity environment: **Ancient Valley**. This massive footprint caused extreme delays in cloning repositories (1+ hour), opening the editor (15+ minutes), and packaging the simulation (hours).

**The Goals:**
*   **Modularize Development:** Allow developers to clone a "Lite" version of the repo (approx. 8GB) and only download the heavy assets if needed.
*   **DLC Distribution:** Package the simulator such that the base program is small, allowing users to "drop-in" the Ancient Valley content as an optional folder/file.
*   **Optimize Build Times:** Reduce the time required to iterate on the core simulator logic by excluding heavy environments from the standard cook process.

---

## **2. Key Concepts: The "Pak" System**
In Unreal Engine 5, assets are not stored as individual files in the final build. They are bundled into containers.

### **The File Trinity (IoStore)**
Since UE5, Unreal uses the **IoStore** format, which splits every "Chunk" into three files:
1.  **`.utoc` (Table of Contents):** The "Index." It tells the engine exactly where in the big file a specific texture or mesh is located.
2.  **`.ucas` (Unreal Container Asset Stream):** The "Data." This is the large file containing the actual compressed bytes of your rocks, trees, and maps.
3.  **`.pak`:** A legacy wrapper used for mounting the container into the engine's virtual file system.

### **Chunks**
*   **Chunk 0:** The "Base Game." This contains the Engine, the Rover, the UI, and the startup map.
*   **Chunk 1-N:** Custom chunks (DLC). These contain specific features or maps that are not required for the game to boot.

---

## **3. Implementation: How we achieved the split**

### **Step 1: Breaking Hard References (The logic Fix)**
The most common reason chunking fails is a **Hard Reference**. If the Main Menu has a button that "points" directly to the Ancient Valley Map asset, the cooker will pull that map into Chunk 0 to ensure the button doesn't break.
*   **The Fix:** We converted all level-loading logic to **Soft References**. Instead of picking a "Level Object" in a dropdown, we use **`Open Level (By Name)`** and type the map name as a **String**. This allows Chunk 0 to exist without "knowing" that the Ancient Valley assets even exist.

### **Step 2: The Primary Asset Label (The physical Fix)**
We created a **`PrimaryAssetLabel`** data asset inside the Ancient Content folder.
*   **Location:** `Content/AncientContent/Label_AncientContent`
*   **Chunk ID:** Set to **1001**.
*   **Priority:** Set to **1000** (This ensures it takes precedence over the default engine assignment).
*   **Specific Assets:** We explicitly added the `NewSmallAncientWorld` map to this label.

### **Step 3: Asset Manager Configuration (The "Phone Book" Fix)**
The "Black Screen" and "Map Not Found" issues were caused by the **Asset Registry**. The game's "Phone Book" (the list of all available assets) must be in Chunk 0, even if the actual data is in Chunk 1001.
*   **Location:** `Project Settings > Game > Asset Manager`
*   **The Fix:** We added a specific entry for the **Map** type. By setting the Map scan rules to **Chunk ID 0**, we forced the engine to put the "knowledge" of the Ancient Valley map into the base game, while the **Label** from Step 2 kept the "heavy data" in Chunk 1001.

---

## **4. The "Master Build" Workflow**
To maintain a working DLC system, the team must follow the **Single Build Workflow**. You cannot mix files from a build where Ancient Valley was blacklisted with a build where it was whitelisted.

1.  **Package the FULL Sim:** Run the packaging process with all content enabled.
2.  **Verify the Output:** Ensure you see `pakchunk0-Windows.ucas` (Base) and `pakchunk1001-Windows.ucas` (DLC).
3.  **To Distribute "Lite":** Provide users with everything **except** the `pakchunk1001` files.
4.  **To Distribute "DLC":** Provide the user with the `pakchunk1001` `.pak`, `.ucas`, and `.utoc` files. They simply drop them into their `Paks` folder, and the "Ancient Valley" button in the menu will suddenly start working.

---

## **5. Summary of Optimization Results**
By implementing this system and excluding the heavy assets from the standard developer export, we achieved:
*   **Total Size Reduction:** **~70.5%** (Base Sim is now ~12GB vs ~44GB).
*   **Export Speed Increase:** **~3114%** (Reducing packaging from 1 hour to roughly 2 minutes).
*   **Editor Load Time:** Improved by **~90%** for developers who choose not to download the Optional Plugin.

---

## **6. Notes for Future Developers**
*   **Plugin Architecture:** In the future, the "Ancient Valley" should be moved entirely into a separate **Content-Only Plugin**. This allows the folder to be managed in a completely separate Git/Diversion repository, preventing it from ever being downloaded by developers who only need to work on the Rover or UI code.
*   **Circular Dependencies:** If the sim starts crashing with `AsyncLoading2.cpp` errors after adding new content, check the **Reference Viewer**. Ensure that no assets in the `Content/` folder are "Hard Referencing" assets in the `DLC/` folders.
*   **Validation:** Use the **`Audit Assets`** tool (Right-click folder -> Size Map / Reference Viewer) to verify which chunk an asset has been assigned to before packaging.