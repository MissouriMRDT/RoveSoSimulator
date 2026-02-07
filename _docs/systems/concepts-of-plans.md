---
title: Concepts of Plans
---

# **Project Knowledge Base: Attempted & Concept Initiatives**

This document serves as a **"Project Legacy & Repository of Knowledge"** for the Mars Rover Design Team’s Simulator sub-team. It outlines major initiatives that were either fully implemented, partially attempted, or kept as future concepts.

The goal is to prevent "re-inventing the wheel" and to provide future developers with the specific technical roadblocks that halted certain paths. Please add your unfinished projects, moonshots, and or anything else to this list so other people can reference it in the future. 

## **Section 1: High-Fidelity Cinematic Rendering (Attempted/Pivoted)**

### **1.1 Overview of the Technology**
To produce a high-quality video for competition, we explored Unreal Engine’s professional cinematic pipeline:
*   **Take Recorder:** Captures live gameplay data (pawn movement, wheel rotation, arm positions) and saves it as a "Level Sequence."
*   **Sequencer:** A multi-track animation editor used to arrange "Takes," place cinematic cameras, and animate lighting/focus.
*   **Movie Render Queue (MRQ):** An offline rendering system that produces 4K frames with high-end anti-aliasing and motion blur, superior to what is visible on a standard monitor.

### **1.2 Methodology**
1.  **Recording:** We used Take Recorder to "record" the rover performing search patterns and arm interactions.
2.  **Cinematography:** We created a Master Sequence, dragged the recorded data into it, and added **CineCameraActors** with low apertures (f/2.8) for realistic depth of field.
3.  **Overrides:** We implemented `Game Overrides` in the MRQ settings to ensure our custom GameMode was used during the render.

### **1.3 Roadblocks & Technical Challenges**
*   **The Physics Conflict:** A "Hard Stop" occurred where the Sequencer (trying to set the rover's position) fought with the Chaos Physics Engine (trying to calculate gravity/friction). This resulted in jittering or the rover "snapping back" to its origin.
*   **Game Instance Desync:** MRQ launches a separate, "clean" instance of the game. Our rover logic relies heavily on the **BP_GameInstance** to manage attachments and RoveComm. Because MRQ didn't always initialize the GameInstance correctly, the rover's front end or signal mast would frequently "pop off" or fail to attach during the render.
*   **UI/HUD Omission:** MRQ is designed for movies, not software demos. Capturing the **Basestation UI** and the **Secondary Camera Views** required complex "UI Widget" tracks that were extremely difficult to align with the recorded rover movement.

### **1.4 Conclusion & Current Path**
**Status:** Abandoned in favor of **OBS High-Bitrate Viewport Capture.**
**Reasoning:** For a technical demonstration, the "True Physics" and "Live UI" visible in a real-time session are more valuable than cinematic lighting. We shifted to using **OBS with CQP 16 encoding** and enabled **Camera Lag** in the SpringArm component to simulate the smooth motion of the professional renderer without the technical overhead.

---

## **Section 2: Linux-to-Windows Cross-Compilation (Failed)**

### **2.1 Overview**
The goal was to allow developers working in the Arch Linux environment to build and package `.exe` files for Windows users directly from their Linux machines.

### **2.2 Roadblocks**
*   **Proprietary SDKs:** Windows packaging requires the Windows SDK and the Clang-cl toolchain. These are not natively available on Linux.
*   **Dependency Chain:** Our `RoveComm_CPP` library is integrated via CMake. Cross-compiling a third-party C++ library from Linux to Windows while nested inside an Unreal build process proved to be highly unstable.

### **2.3 Conclusion & Current Path**
**Status:** Failed/Infeasible.
**Alternative:** We implemented a **Self-Hosted GitHub Action Runner** on a dedicated Windows machine. Linux developers push code to the repo, and the Windows "Build Mule" automatically packages the `.exe` and uploads it.

---

## **Section 3: Sentry Editor-Mode Filtering (Implemented)**

### **3.1 Overview**
We integrated Sentry for crash reporting but found that it captured too many "false positives" from developers purposefully stopping the editor or encountering minor bugs during iteration.

### **3.2 Implementation**
We created a C++ helper function `IsRunningInEditor()` using the `WITH_EDITOR` macro. This was used in a Blueprint gate within the **BP_GameInstance**.

### **3.3 Conclusion**
**Status:** Successful.
**Result:** Sentry only initializes if the sim is running as a standalone packaged build, unless a manual "Debug Reporting" toggle is checked in the GameInstance.

---

## **Section 4: VR Immersive Teleoperation (Concept)**

### **4.1 Overview**
The concept is to use a Meta Quest 2 headset to provide arm operators with actual depth perception. The operator would see the ZED camera feeds in 3D and use the Quest's "head tracking" to move a gimbal-mounted camera on the rover.

### **4.2 Proposed Workflow**
*   **Phase 1:** Integration of the **OpenXR** and **Meta XR** plugins.
*   **Phase 2:** Development of a **VR_Pawn** that maps the Quest's HMD (Head Mounted Display) rotation to the `SceneCaptureComponent2D` on the rover.
*   **Phase 3:** Using 3D depth buffers to provide stereoscopic feedback to the headset.

### **4.3 Known Hurdles**
*   **Latency:** The delay between moving one's head and the virtual camera updating (latency) can cause severe motion sickness.
*   **Performance:** Rendering the scene twice (once for each eye) at 72Hz+ may require significant optimization of the "Ancient Valley" assets.

---

## **Notes for Future Developers**
*   If you attempt to revive the **Sequencer/MRQ** project, focus on converting all actors to **"Possessable"** rather than "Spawnable" and ensure physics is disabled on the first frame of the sequence.
*   When adding new tools to the `Tools/` directory, ensure the **Additional Non-Asset Directories to Copy** setting in Project Settings is updated, or the tool will not exist in the packaged version.
