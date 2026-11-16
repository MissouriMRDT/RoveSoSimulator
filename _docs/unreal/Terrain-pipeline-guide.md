# Hanksville and MDRS Terrain Pipeline Guide

This guide documents the complete process of building the Mars Desert Research Station (MDRS / Hanksville) terrain environment in Unreal Engine from scratch. It covers raw elevation sourcing, raster cropping, scale calculations, heightmap importing, satellite texture alignment, procedural PBR material construction, geospatial coordinate calibration, and every troubleshooting issue encountered along the way.

---

## 1. Source data acquisition and area of interest

The simulation map covers a 1.575 km by 1.575 km square centered around the Mars Desert Research Station and the Bentonite Hills near Hanksville, Utah.

### Geographic coordinates
The terrain boundaries are defined in the WGS84 coordinate reference system (EPSG:4326):

| Corner | Latitude | Longitude | Landmark |
| :--- | :--- | :--- | :--- |
| South-West | 38°24'39.6"N (38.411000°) | 110°47'09.6"W (-110.786000°) | Red placemark (banded rock formation) |
| North-West | 38°25'30.7"N (38.425189°) | 110°47'09.6"W (-110.786000°) | Blue placemark (northern wash) |
| North-East | 38°25'30.7"N (38.425189°) | 110°46'04.7"W (-110.767967°) | Crescent ridge line |
| South-East | 38°24'39.6"N (38.411000°) | 110°46'04.7"W (-110.767967°) | Canyon badlands |

### Sourcing elevation data
Elevation data comes from the USGS 3DEP (3D Elevation Program) LiDAR collection:
1. Open the [USGS 3DEP LidarExplorer](https://apps.nationalmap.gov/lidar-explorer/).
2. Locate Hanksville, Utah, and use the bounding box tool to select the area between latitudes 38.4110° to 38.4252° and longitudes -110.7860° to -110.7680°.
3. Download the Digital Elevation Model (DEM) raster (1-meter resolution GeoTIFF) or the corresponding point cloud tiles (.laz files).

### Sourcing satellite imagery
1. Export orthorectified satellite imagery covering the exact same bounding box at high resolution (minimum 4096 x 4096 pixels).
2. Ensure the image is exported with a North-up orientation without lens distortion or perspective tilt.
3. Clean the image in an image editor to remove watermarks, road labels, navigation overlays, and cloud shadows.

---

## 2. Terrain cropping and heightmap preparation

Unreal Engine landscape components require specific vertex dimensions to support level-of-detail (LOD) transitions and continuous geometry across seams.

### Landscape dimension constraints
Unreal calculates landscape vertex resolution using the formula:
```text
Total Vertices = (Quads Per Section * Sections Per Component * Components Count) + 1
```

For a 1-meter horizontal grid resolution across a 1,575-meter terrain:
- Quads per section: 63
- Sections per component: 1 x 1
- Number of components: 25 x 25 (625 total components)
- Total resolution: (63 * 1 * 25) + 1 = 1,576 x 1,576 vertices
- Total horizontal span: 1,575 quads * 100 cm = 157,500 cm (1.575 km)

### Cropping and bit depth
1. Import the raw DEM into QGIS or an image processing tool.
2. Clip the raster to the exact coordinate bounding box.
3. Resample the raster to exactly 1,576 x 1,576 pixels using bilinear or bicubic interpolation.
4. Export the raster as a **16-bit grayscale PNG** or **16-bit raw image (r16)**.

Do not use 8-bit images. An 8-bit image only provides 256 discrete gray values. Across a 75-meter elevation range, each step represents approximately 30 cm of vertical jump, creating stepped terraces across hillsides. A 16-bit image provides 65,536 values, giving sub-millimeter vertical precision.

---

## 3. Scale and elevation math

Unreal Engine stores 16-bit landscape height values as signed integers between -32,768 and +32,767. At a default Z scale of 100.0, the full range represents 512 meters (-256 m to +256 m).

### Calculating the Z-scale factor
To convert the real-world height range into the correct Unreal landscape Z scale:
```text
Scale Z = (Elevation Span in Meters * 100) / 512
Scale Z = Elevation Span in Meters * 0.1953125
```

For the Hanksville MDRS site:
- Minimum elevation (valley wash): 1,362.52 meters
- Maximum elevation (highest ridge): 1,438.00 meters
- Total elevation span: 75.48 meters

Calculate the Z scale:
```text
Scale Z = 75.48 * 0.1953125 = 14.742
```

Horizontal scaling:
- Scale X = 100.0 (1 vertex per meter = 100 cm per quad)
- Scale Y = 100.0 (1 vertex per meter = 100 cm per quad)

---

## 4. Importing the terrain as an Unreal Landscape

1. Open the target map in Unreal Engine (`/Game/MRDTModels/URC_Hanksville/URC_MDRS`).
2. Switch to **Landscape Mode** (Shift + 2).
3. Select **Import from File**.
4. Browse to the 16-bit heightmap file (`.png` or `.r16`).
5. Confirm the import settings:
   - Section Size: 63 x 63 Quads
   - Sections Per Component: 1 x 1
   - Number of Components: 25 x 25
   - Overall Resolution: 1,576 x 1,576
   - Scale: X = 100.0, Y = 100.0, Z = 14.742
   - Location: X = 0.0, Y = 0.0, Z = 0.0
   - Rotation: Pitch = 0.0, Yaw = 0.0, Roll = 0.0
6. Click **Import**.

The landscape actor (`Landscape_1`) now occupies world coordinates from X = 0 to 157,500 cm and Y = 0 to 157,500 cm.

---

## 5. Satellite imagery preparation and alignment

The base color of the terrain relies on a satellite orthophoto exported from the same coordinate boundaries.

### Texture import settings
Save the image as `urc_satellite_texture1_clean.png` (4096 x 4096 pixels) and import it into `/Game/MRDTModels/URC_Hanksville/`. In the Texture Editor, configure:

| Setting | Value | Reason |
| :--- | :--- | :--- |
| Compression Settings | `TC_Default` | Standard DXT1/DXT5 compression for color textures |
| sRGB | True | Image contains color data in standard gamma |
| Texture Group | `TEXTUREGROUP_World` | Standard world streaming settings |
| Mip Gen Settings | `TMGS_FromTextureGroup` | Generates mipmaps for smooth distant rendering |
| Never Stream | False | Allows streaming to conserve GPU memory |

### Satellite UV formula
Because the landscape origin sits at `(0, 0)` with a total span of 157,500 cm:
```text
U = WorldPosition.X / 157500.0
V = WorldPosition.Y / 157500.0
```

In the material graph, connect `WorldPosition (XY)` into a `Divide` node with scalar parameter `LandscapeDimensions = 157500.0`, then wire the result into the UV input of the satellite texture sampler.

---

## 6. Terrain material and PBR surface construction

Relying solely on a satellite texture creates blurry ground when viewed from the rover's cameras. The material combines the macro satellite photograph with high-frequency PBR textures (playa silt, gravel, and cliff strata) blended dynamically by slope and camera distance.

### Texture library
Store detail textures in `/Game/MRDTModels/URC_Hanksville/Materials/`:
- `MDRS_Playa_Clean_Albedo.png` and `_Normal.png` (fine dried silt wash)
- `MDRS_Gravel_Clean_Albedo.png` and `_Normal.png` (rocky desert pavement)
- `MDRS_Cliff_Strata_Albedo.png` and `_Normal.png` (layered sedimentary stone)

All normal maps must have `Compression Settings = TC_Normalmap` and `sRGB = False`.

### Solving the 16-sampler DirectX limit
A complex terrain material uses multiple albedo, normal, and mask textures. DirectX limits materials to 16 texture samplers. If exceeded, the material will fail to compile.

To resolve this, select every `Texture Sample` node in the material graph and set:
```text
Sampler Source: Shared: Wrap (SSM_Wrap_WorldGroupSettings)
```
This reuses sampler states across textures, allowing dozens of textures in a single material.

### Ground detail blending
1. **Playa wash:** Sample playa textures with `UV = WorldPosition.XY / 400.0` (tiles every 4 meters).
2. **Gravel:** Sample gravel textures with a 45-degree rotation (`Rotator(WorldPosition.XY, 45°) / 800.0`) to avoid repetitive directional alignment.
3. **Playa to gravel mask:** Extract the red channel of the satellite texture, raise it to an exponent of 1.8 (`Power(Satellite.R, 1.8)`), and use it as the alpha input of a `LinearInterpolate` node between playa and gravel.

### Solving cliff texture stretching with vertical Z-mapping
Standard planar mapping (`WorldPosition.XY`) projects textures from directly above. On vertical canyon walls and badland slopes, this causes severe vertical stretching.

The solution is to map cliff textures using world elevation (Z) for the vertical texture coordinate:
```text
Cliff U = (WorldPosition.X + WorldPosition.Y) / 3500.0
Cliff V = WorldPosition.Z / 2500.0
Cliff UV = Append(Cliff U, Cliff V)
```
This causes sedimentary rock strata to wrap horizontally around hills while keeping layers parallel to the real geological horizon.

### Slope masking via vertex normals
Blend between flat ground and cliff strata using the vertical component of the world vertex normal:
```text
Slope = Saturate( ( (1.0 - VertexNormalWS.Z) - 0.12 ) * 5.0 )
```
- Flat ground (`Normal.Z = 1.0`): Slope evaluates to 0.0 (ground playa/gravel).
- Moderate slopes: Smooth transition between 0.0 and 1.0.
- Steep cliffs (`Normal.Z < 0.88`, greater than 28 degrees): Slope evaluates to 1.0 (cliff strata).

### Macro color modulation and distance fading
1. **Color modulation:** Multiply the blended PBR albedo by the satellite color scaled by 1.6 (`PBR_Albedo * (Satellite_Albedo * 1.6)`). This imparts the large-scale regional hues (reds, ochres, and whites) directly into the high-resolution ground textures.
2. **Distance fading:** Compute camera distance using `Distance(CameraPositionWS, WorldPosition)`. Divide by 25,000 cm (250 meters) and saturate. Use this factor to interpolate the surface base color toward the pure satellite texture at a distance, eliminating tiling artifacts on far mountains.
3. **Roughness and specular:** Set Roughness to 0.92 and Specular to 0.22. Do not connect Fresnel nodes to specular or base color, as Fresnel reflections make dry desert clay look like wet plastic in direct sunlight.

---

## 7. Geospatial calibration and GeoReferencingSystem setup

Unreal Engine's GeoReferencing plugin connects local engine units (centimeters) to geographic coordinates (WGS84 latitude, longitude, altitude) and projected coordinates (UTM).

### Coordinate axes convention
Epic's `GeoReferencingSystem` uses the following coordinate frame:
- Engine `+X` = Easting (positive moves East)
- Engine `-Y` = Northing (Engine `+Y` is Southing, positive moves South)
- Engine `+Z` = Altitude (positive moves Up)

Because the landscape occupies positive space (X from 0 to 157,500 cm, Y from 0 to 157,500 cm):
- Moving in `+X` moves East across the map.
- Moving in `+Y` moves South across the map.
- The coordinate origin `(0, 0, 0)` is mathematically the **North-West corner** of the area.

### Actor properties setup
Select `GeoReferencingSystem_0` in the level and configure:

| Property | Value | Description |
| :--- | :--- | :--- |
| `PlanetShape` | `RoundPlanet` | Geodetic ellipsoidal calculations |
| `ProjectedCRS` | `EPSG:32612` | UTM Zone 12N (Hanksville region) |
| `GeographicCRS` | `EPSG:4326` | WGS84 standard GPS format |
| `bOriginLocationInProjectedCRS` | False | Defines origin via latitude and longitude |
| `OriginLatitude` | `38.425189` | North-West corner latitude (38°25'30.7"N) |
| `OriginLongitude` | `-110.786000` | North-West corner longitude (110°47'09.6"W) |
| `OriginAltitude` | `1400.0` | Base reference elevation in meters |

### Coordinate verification
Verifying coordinates across the landscape confirms alignment:
- At `(0, 0, 0)` (NW origin): Returns 38.425189°N, -110.786000°W.
- At `(0, 157500, 0)` (SW corner): Returns 38.411000°N, -110.786000°W (matches the red placemark).
- At `(157500, 157500, 0)` (SE corner): Returns 38.411000°N, -110.767967°W (matches canyon badlands).
- At `(157500, 0, 0)` (NE corner): Returns 38.425189°N, -110.767967°W (matches northern ridge).

### Aligning MapManager bounds
Select the two target points used by `MapManager` and update their transforms:
- `Scan_Min_Marker` (`TargetPoint_0`): Location `(X = 0, Y = 0, Z = 0)`
- `Scan_Max_Marker` (`TargetPoint_1`): Location `(X = 157500, Y = 157500, Z = 0)`
- `MapManager_0`: Set `worldBoundsMin = (0, 0)` and `worldBoundsMax = (157500, 157500)`

---

## 8. Troubleshooting and lessons learned

### Terraced contours and stair-stepping
- **Symptom:** Hills look like stepped pyramids rather than smooth slopes.
- **Cause:** Using an 8-bit heightmap image (256 discrete levels).
- **Fix:** Convert and export heightmaps strictly as 16-bit grayscale PNG or 16-bit raw files (65,536 levels).

### Vertical cliff texture stretching
- **Symptom:** Textures on badland slopes and canyon walls look smeared vertically.
- **Cause:** Top-down planar mapping (`WorldPosition.XY`) lacks texture resolution along steep surfaces.
- **Fix:** Separate cliff surfaces using `VertexNormalWS.Z` and project cliff textures using world elevation (`WorldPosition.Z`) for the vertical UV coordinate.

### Shiny ground and metallic mud
- **Symptom:** Ground looks like reflective wet plastic or polished linoleum when facing the sun.
- **Cause:** Connecting Fresnel or camera-facing falloff nodes to specular or base color, combined with low roughness values.
- **Fix:** Disconnect all Fresnel nodes. Set ground roughness to 0.92 and specular to 0.22.

### Hot reload metadata crashes during engine rebuild
- **Symptom:** Unreal crashes on startup with `Cannot replace existing object of a different class: SentryAttachment`.
- **Cause:** Hot reload leftover binaries (`-0001.so` and `Metadata-HotReload.dat`) conflicting with newly compiled classes.
- **Fix:** Delete all `-0001.so`, `-0002.so`, and `Metadata-HotReload.dat` files in `Binaries/Linux/`. Always compile using `-NoHotReloadFromIDE`.

### Missing AVCodecs shared library crash
- **Symptom:** Engine fails to load with `dlopen failed: libUnrealEditor-AVCodecsCore.so: cannot open shared object file`.
- **Cause:** The `PixelStreaming` plugin pulling in optional hardware video encoding libraries that were not compiled on the Linux workstation.
- **Fix:** Disable `PixelStreaming` in the `.uproject` file if not actively using browser streaming.

### USGS server rate-limiting (HTTP 429)
- **Symptom:** Batch tile downloads fail with `HTTP Error 429: Too Many Requests` or connection resets.
- **Cause:** USGS web servers throttle concurrent connections from the same IP address.
- **Fix:** Use sequential downloads (single worker thread) with a 1.0-second delay between requests. When a 429 occurs, parse the `Retry-After` header and apply exponential backoff (15 to 30 seconds) before retrying.
