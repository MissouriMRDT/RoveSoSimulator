# URC Terrain Mesh Generation Pipeline

## Overview

This document details the pipeline used to acquire, preprocess, and generate a 1:1 scale 3D terrain mesh of the University Rover Challenge (URC) competition area for the 2026-2027 season.

The pipeline converts public domain United States Geological Survey (USGS) elevation data into a textured 3D mesh suitable for simulation environments (such as Gazebo, Isaac Sim, or Unreal Engine) and autonomy path planning.

---

## 1. Area of Interest

The target bounding coordinates near Hanksville, Utah (Mars Desert Research Station / URC grounds):

* **North Latitude:** 38.425 N
* **South Latitude:** 38.411 N
* **West Longitude:** -110.786 W
* **East Longitude:** -110.768 W
* **Dimensions:** Approximately 1.55 km (North-South) by 1.57 km (East-West), covering roughly 2.4 square kilometers.
* **Target Coordinate Reference System (CRS):** UTM Zone 12N (EPSG:26912) or WGS 84 (EPSG:4326).

---

## 2. Data Source Selection: DEM vs. Raw LiDAR

The USGS 3D Elevation Program (3DEP) provides two primary elevation products through its AWS public repositories and web portals:

1. **Raw LiDAR Point Clouds (`.laz` / EPT format):**
   * Collections of discrete laser return points (X, Y, Z coordinates).
   * Do not contain surface topology or polygon connectivity.
   * Require surface reconstruction algorithms (e.g., Screened Poisson Reconstruction, 2.5D Delaunay Triangulation) to produce a solid mesh. These algorithms are computationally intensive and prone to edge artifacts and vegetation noise.
2. **Digital Elevation Models (DEMs, 1m GeoTIFF):**
   * Gridded 2D rasters where each pixel stores the bare-earth ground elevation in meters.
   * Derived directly from raw LiDAR after filtering out non-ground returns (vegetation, vehicles, structures).
   * Map directly to a 3D vertex grid without surface reconstruction errors.

**Decision:** 1-meter resolution USGS 3DEP bare-earth DEMs were selected. They provide millimeter-accurate height data pre-filtered for ground level, directly converting to a clean polygon mesh.

---

## 3. Data Acquisition and Archival

### The Locator Problem
The standard [USGS LidarExplorer](https://apps.nationalmap.gov/lidar-explorer/#/) does not provide coordinate bounding box search queries or name-based indexing for specific desert parcels.

### Solution
1. The MRDT visualizer tool at `https://visualizer.themrdt.org/lidar-tool/` was used to define the coordinate box:
   * (38.411 N, -110.786 W) to (38.425 N, -110.768 W).
2. The tool identified the exact USGS 1m DEM tile identifiers covering this footprint.
3. Three adjacent 1m USGS DEM tiles were downloaded to cover the complete area without boundary gaps.

### Team Storage
To prevent team members from repeating the search and download process, all source tiles and project files are archived on the team SharePoint:
* **Location:** [MRDT SharePoint - Simulator LiDAR Models](https://mailmissouri.sharepoint.com/sites/SDELC-MarsRoverDesignTeam-Ogrp/Shared%20Documents/Forms/AllItems.aspx?id=%2Fsites%2FSDELC-MarsRoverDesignTeam-Ogrp%2FShared%20Documents%2F%23ROVESODRIVE%2F2027%20(KICKFLIP)%2F2%20-%20Arch%20Software%2FSimulator%2FModels%2FLiDAR&viewid=222fe0bf-5a43-4286-af58-d0eeca5d2865&as=json&FolderCTID=0x012000D37049AE53A0094484D716DAB5E334B6)
* **Contents:**
  * Raw USGS 1m DEM `.tif` source tiles.
  * Merged and clipped raster: `urc_mdrs_1m.tif`.
  * Pre-configured QGIS project file (`.qgz`).

---

## 4. QGIS Preprocessing Pipeline

Importing raw USGS tiles directly into 3D software causes memory exhaustion. A single USGS 1m tile is roughly 10,000 by 10,000 pixels (100 million pixels). Three unclipped tiles total approximately 300 million pixels. Instantiating 300 million vertices in Blender requires 40 GB to 60 GB of RAM and crashes the host system.

QGIS (Free and Open Source GIS) was used to stitch, align, and crop the tiles down to the 1.5 km by 1.5 km study area (~2.25 million vertices, ~150 MB RAM).

### Step 4.1: Adding Spatial Reference Basemaps
1. In QGIS, navigate to the **Browser** panel on the left.
2. Locate **XYZ Tiles**.
3. Double-click **OpenStreetMap** to establish a global coordinate reference frame.
4. Add high-resolution Google Satellite imagery:
   * Right-click **XYZ Tiles** -> **New Connection...**
   * **Name:** `Google Satellite`
   * **URL:** `https://mt1.google.com/vt/lyrs=s&x={x}&y={y}&z={z}`
   * Click **OK**, then double-click the newly created entry.
5. In the **Layers** panel, position `Google Satellite` at the bottom of the layer stack.

### Step 4.2: Merging the 3 Source Tiles
1. Go to **Raster** -> **Miscellaneous** -> **Build Virtual Raster...**
2. Click the `...` button next to **Input layers**.
3. Select all three downloaded USGS `.tif` tiles.
4. Leave remaining parameters at defaults and click **Run**.
5. This generates a virtual merged layer (`Virtual`) referencing all three tiles without duplicating disk storage.

### Step 4.3: Clipping to the Exact URC Extent
1. Go to **Raster** -> **Extraction** -> **Clip Raster by Extent...**
2. Set **Input layer** to `Virtual`.
3. Set **Clipping extent** using the coordinates:
   ```text
   -110.786, -110.768, 38.411, 38.425 [EPSG:4326]
   ```
4. Scroll to **Clipped (extent)**, click `...`, select **Save to File...**, and specify `urc_mdrs_1m.tif`.
5. Click **Run**.
6. The resulting file covers only the target area (~1500 x 1500 pixels).

### Step 4.4: Terrain Visualization and Verification in QGIS
1. Uncheck the raw USGS source layers in the **Layers** panel.
2. Right-click `urc_mdrs_1m` -> **Properties** -> **Symbology**.
3. Change **Render type** from `Singleband gray` to `Hillshade` to verify ridge and wash topography.
4. Verify 3D relief natively:
   * Go to **View** -> **3D Map Views** -> **New 3D Map View**.
   * In the 3D viewport toolbar, click the **Options (wrench icon)**.
   * Under **Terrain**, set **Type** to `DEM (Raster Layer)` and **Elevation** to `urc_mdrs_1m`.
   * Inspect the 3D model using `Shift + Left Click + Drag` to rotate the viewport.

### Step 4.5: Exporting Aligned Satellite Textures
To ensure the satellite texture matches the 3D geometry identically:
1. In the **Layers** panel, right-click `Google Satellite`.
2. Select **Export** -> **Save As...**
3. Configure the export parameters:
   * **Output mode:** Check **Rendered image**.
   * **Format:** `GeoTIFF` (or `PNG`).
   * **File name:** `urc_satellite_texture.tif`.
   * **Extent:** Click **Calculate from Layer** and select `urc_mdrs_1m`. This forces identical bounding boundaries.
   * **Resolution:** Set Horizontal and Vertical resolution to `1.0` (or `0.5` for higher visual fidelity).
4. Click **OK**.

---

## 5. Blender 3D Mesh Generation (BlenderGIS)

### Step 5.1: Plugin Installation
1. Download the BlenderGIS add-on zip archive from `https://github.com/domlysz/blendergis`.
2. In Blender, navigate to **Edit** -> **Preferences** -> **Add-ons** -> **Install...**
3. Select the zip file and enable the checkbox for **3D View: BlenderGIS**.

### Step 5.2: Importing the Clipped DEM
1. In the 3D Viewport header, open the **GIS** menu.
2. Select **GIS** -> **Import** -> **Georeferenced raster**.
3. Select `urc_mdrs_1m.tif`.
4. Set the import configuration:
   * **Mode:** `DEM raw elevation`
   * **Sub-mode:** `Mesh`
5. Click **Import**.
6. Blender generates a solid polygonal surface where 1 Blender unit equals exactly 1.0 real-world meter. The file loads in 2 to 3 seconds with minimal memory usage.

### Step 5.3: Shading and Texture Application
By default, Blender initializes viewports in **Solid Shading** mode (the second circle in the top-right viewport corner). This displays all objects as uniform gray clay, obscuring textures.

To display the satellite texture:
1. Switch Viewport Shading to **Material Preview** (the third circle in the top-right corner, or press `Z` -> `Material Preview`).
2. Texture mapping can be completed using either method:
   * **Method A (Direct BlenderGIS draping):** Select the terrain mesh, navigate to **GIS** -> **Web geodata** -> **Basemap**, choose `Google` / `Satellite`, and click **OK**.
   * **Method B (Using QGIS exported texture):** Select `urc_mdrs_1m`, open the **Material Properties** tab, add a new material, set **Base Color** to an **Image Texture** pointing to `urc_satellite_texture.tif`, press `Numpad 7` (Top Orthographic view), press `Tab` (Edit Mode), press `A` (select all), press `U`, and select **Project from View (Bounds)**.

---

## 6. Exporting for Simulation

From Blender, the textured terrain can be exported for robotics simulation:

* **Gazebo / ROS (SDF / URDF World):** Export as `.dae` (Collada) or `.obj` with an associated `.mtl` material definition.
* **Gazebo Heightmap:** If using the native `<heightmap>` tag instead of a static mesh, convert `urc_mdrs_1m.tif` to a square 16-bit grayscale PNG using GDAL:
  ```bash
  gdal_translate -ot UInt16 -scale <min_elev> <max_elev> 0 65535 -outsize 1025 1025 urc_mdrs_1m.tif terrain_heightmap.png
  ```
* **Unreal Engine / Isaac Sim:** Export as `.fbx` or `.obj` with embedded textures.
