"""
URC Terrain Material Rebuild Script for Unreal Engine 5.6.1
===========================================================
This script automates the complete recreation of the URC Hanksville terrain:
1. Imports the 7 clean PBR textures into /Game/MRDTModels/URC_Hanksville/Materials/
2. Builds and compiles the slope-aware URC_Map_Material graph
3. Assigns the material to the Landscape actor in the open level
4. Configures Ultra Dynamic Sky and Ultra Dynamic Weather atmospheric haze

How to run in Unreal Engine 5.6.1:
1. Open Unreal Editor 5.6.1 with the RoveSoSimulator project.
2. Open the level: /Game/MRDTModels/URC_Hanksville/URC_MDRS
3. Open the Output Log window (Window -> Output Log).
4. Change the 'Cmd' dropdown at bottom right to 'Python'.
5. Enter:
   py "/home/targed/Documents/Unreal Projects/URC_Map/build_urc_material.py"
"""

import os
import unreal

def safe_set_property(obj, prop_names, value):
    """Safely attempt to set an editor property across various Python binding naming conventions."""
    if isinstance(prop_names, str):
        prop_names = [prop_names]
    for name in prop_names:
        try:
            obj.set_editor_property(name, value)
            return True
        except Exception:
            pass
    return False

def import_textures(texture_dir, dest_path):
    """Imports 7 PBR textures and applies normal/color compression settings."""
    asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
    
    texture_files = [
        ("MDRS_Playa_Clean_Albedo.png", False, dest_path),
        ("MDRS_Playa_Clean_Normal.png", True, dest_path),
        ("MDRS_Gravel_Clean_Albedo.png", False, dest_path),
        ("MDRS_Gravel_Clean_Normal.png", True, dest_path),
        ("MDRS_Cliff_Strata_Albedo.png", False, dest_path),
        ("MDRS_Cliff_Normal.png", True, dest_path),
        ("urc_satellite_texture1_clean.png", False, "/Game/MRDTModels/URC_Hanksville"),
    ]
    
    imported = {}
    for filename, is_normal, target_folder in texture_files:
        full_path = os.path.join(texture_dir, filename)
        if not os.path.exists(full_path):
            unreal.log_warning(f"File not found on disk: {full_path}")
            continue
            
        base_name = os.path.splitext(filename)[0]
        
        task = unreal.AssetImportTask()
        task.filename = full_path
        task.destination_path = target_folder
        task.destination_name = base_name
        task.replace_existing = True
        task.automated = True
        task.save = True
        
        asset_tools.import_asset_tasks([task])
        
        tex_path = f"{target_folder}/{base_name}"
        tex_asset = unreal.EditorAssetLibrary.load_asset(tex_path)
        
        if tex_asset:
            if is_normal:
                safe_set_property(tex_asset, ["compression_settings"], unreal.TextureCompressionSettings.TC_NORMALMAP)
                safe_set_property(tex_asset, ["srgb", "SRGB", "s_rgb"], False)
                safe_set_property(tex_asset, ["lod_group"], unreal.TextureGroup.TEXTUREGROUP_WORLD_NORMAL_MAP)
            else:
                safe_set_property(tex_asset, ["compression_settings"], unreal.TextureCompressionSettings.TC_DEFAULT)
                safe_set_property(tex_asset, ["srgb", "SRGB", "s_rgb"], True)
                safe_set_property(tex_asset, ["lod_group"], unreal.TextureGroup.TEXTUREGROUP_WORLD)
                
            unreal.EditorAssetLibrary.save_loaded_asset(tex_asset)
            imported[base_name] = tex_asset
            unreal.log(f"Imported and configured texture: {base_name}")
        else:
            unreal.log_warning(f"Failed to load imported texture: {tex_path}")
            
    return imported

def build_material(mat_asset_path, textures=None):
    """Constructs the complete 6-block slope-aware terrain material graph."""
    if textures is None:
        textures = {}

    def get_texture(base_name, fallback_path):
        if base_name in textures and textures[base_name]:
            return textures[base_name]
        return unreal.EditorAssetLibrary.load_asset(fallback_path)

    # Load or create Material
    mat = unreal.EditorAssetLibrary.load_asset(mat_asset_path)
    if not mat:
        asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
        folder, name = os.path.split(mat_asset_path)
        mat = asset_tools.create_asset(name, folder, unreal.Material, unreal.MaterialFactoryNew())
        
    # Clear existing expressions for a pristine rebuild
    unreal.MaterialEditingLibrary.delete_all_material_expressions(mat)
    
    # Helper wrappers
    def add_node(expr_class, x, y):
        return unreal.MaterialEditingLibrary.create_material_expression(mat, expr_class, x, y)
        
    def connect(from_node, from_pin, to_node, to_pin):
        unreal.MaterialEditingLibrary.connect_material_expressions(from_node, from_pin, to_node, to_pin)
        
    def connect_prop(from_node, from_pin, prop_enum):
        unreal.MaterialEditingLibrary.connect_material_property(from_node, from_pin, prop_enum)

    # -------------------------------------------------------------
    # 1. World Position Coordinates
    # -------------------------------------------------------------
    wp = add_node(unreal.MaterialExpressionWorldPosition, -1400, 0)
    
    # Satellite UV Math: (WP.XY - (-108250, -79833)) / 157500.0
    mask_wp_xy = add_node(unreal.MaterialExpressionComponentMask, -1200, -300)
    mask_wp_xy.set_editor_property("r", True)
    mask_wp_xy.set_editor_property("g", True)
    mask_wp_xy.set_editor_property("b", False)
    connect(wp, "XYZ", mask_wp_xy, "")
    
    c_sat_offset = add_node(unreal.MaterialExpressionConstant2Vector, -1200, -150)
    c_sat_offset.set_editor_property("r", -108250.0)
    c_sat_offset.set_editor_property("g", -79833.0)
    
    sub_sat = add_node(unreal.MaterialExpressionSubtract, -1000, -250)
    connect(mask_wp_xy, "", sub_sat, "A")
    connect(c_sat_offset, "", sub_sat, "B")
    
    c_sat_dim = add_node(unreal.MaterialExpressionScalarParameter, -1000, -100)
    safe_set_property(c_sat_dim, ["parameter_name"], "LandscapeDimensions")
    safe_set_property(c_sat_dim, ["default_value"], 157500.0)
    
    div_sat_uv = add_node(unreal.MaterialExpressionDivide, -800, -200)
    connect(sub_sat, "", div_sat_uv, "A")
    connect(c_sat_dim, "", div_sat_uv, "B")
    
    ts_sat = add_node(unreal.MaterialExpressionTextureSample, -600, -200)
    sat_tex = get_texture("urc_satellite_texture1_clean", "/Game/MRDTModels/URC_Hanksville/urc_satellite_texture1_clean")
    if sat_tex:
        ts_sat.set_editor_property("texture", sat_tex)
    connect(div_sat_uv, "", ts_sat, "Coordinates")

    # -------------------------------------------------------------
    # 2. Ground Playa UV (Micro: WP.XY / 400.0)
    # -------------------------------------------------------------
    c_playa_scale = add_node(unreal.MaterialExpressionConstant, -1000, 100)
    c_playa_scale.set_editor_property("r", 400.0)
    div_playa_uv = add_node(unreal.MaterialExpressionDivide, -800, 50)
    connect(mask_wp_xy, "", div_playa_uv, "A")
    connect(c_playa_scale, "", div_playa_uv, "B")
    
    ts_playa_alb = add_node(unreal.MaterialExpressionTextureSample, -550, 0)
    tex_playa_alb = get_texture("MDRS_Playa_Clean_Albedo", "/Game/MRDTModels/URC_Hanksville/Materials/MDRS_Playa_Clean_Albedo")
    if tex_playa_alb:
        ts_playa_alb.set_editor_property("texture", tex_playa_alb)
        safe_set_property(ts_playa_alb, ["sampler_source"], unreal.SamplerSourceMode.SSM_WRAP_WORLD_GROUP_SETTINGS)
    connect(div_playa_uv, "", ts_playa_alb, "Coordinates")
    
    ts_playa_nrm = add_node(unreal.MaterialExpressionTextureSample, -550, 200)
    tex_playa_nrm = get_texture("MDRS_Playa_Clean_Normal", "/Game/MRDTModels/URC_Hanksville/Materials/MDRS_Playa_Clean_Normal")
    if tex_playa_nrm:
        ts_playa_nrm.set_editor_property("texture", tex_playa_nrm)
        safe_set_property(ts_playa_nrm, ["sampler_source"], unreal.SamplerSourceMode.SSM_WRAP_WORLD_GROUP_SETTINGS)
    connect(div_playa_uv, "", ts_playa_nrm, "Coordinates")

    # -------------------------------------------------------------
    # 3. Ground Gravel UV (Rotated: Rotator(WP.XY) / 800.0)
    # -------------------------------------------------------------
    c_rot_time = add_node(unreal.MaterialExpressionConstant, -1000, 400)
    c_rot_time.set_editor_property("r", 0.5)
    rot_gravel = add_node(unreal.MaterialExpressionRotator, -850, 350)
    connect(mask_wp_xy, "", rot_gravel, "Coordinate")
    connect(c_rot_time, "", rot_gravel, "Time")
    
    c_gravel_scale = add_node(unreal.MaterialExpressionConstant, -850, 500)
    c_gravel_scale.set_editor_property("r", 800.0)
    div_gravel_uv = add_node(unreal.MaterialExpressionDivide, -700, 400)
    connect(rot_gravel, "", div_gravel_uv, "A")
    connect(c_gravel_scale, "", div_gravel_uv, "B")
    
    ts_gravel_alb = add_node(unreal.MaterialExpressionTextureSample, -550, 400)
    tex_gravel_alb = get_texture("MDRS_Gravel_Clean_Albedo", "/Game/MRDTModels/URC_Hanksville/Materials/MDRS_Gravel_Clean_Albedo")
    if tex_gravel_alb:
        ts_gravel_alb.set_editor_property("texture", tex_gravel_alb)
        safe_set_property(ts_gravel_alb, ["sampler_source"], unreal.SamplerSourceMode.SSM_WRAP_WORLD_GROUP_SETTINGS)
    connect(div_gravel_uv, "", ts_gravel_alb, "Coordinates")
    
    ts_gravel_nrm = add_node(unreal.MaterialExpressionTextureSample, -550, 600)
    tex_gravel_nrm = get_texture("MDRS_Gravel_Clean_Normal", "/Game/MRDTModels/URC_Hanksville/Materials/MDRS_Gravel_Clean_Normal")
    if tex_gravel_nrm:
        ts_gravel_nrm.set_editor_property("texture", tex_gravel_nrm)
        safe_set_property(ts_gravel_nrm, ["sampler_source"], unreal.SamplerSourceMode.SSM_WRAP_WORLD_GROUP_SETTINGS)
    connect(div_gravel_uv, "", ts_gravel_nrm, "Coordinates")

    # -------------------------------------------------------------
    # 4. Gravel Blend Mask: Power(Satellite.R, 1.8)
    # -------------------------------------------------------------
    pow_gravel = add_node(unreal.MaterialExpressionPower, -400, 100)
    c_pow_exp = add_node(unreal.MaterialExpressionConstant, -400, 220)
    c_pow_exp.set_editor_property("r", 1.8)
    safe_set_property(pow_gravel, ["const_exponent"], 1.8)
    connect(ts_sat, "R", pow_gravel, "Base")
    connect(c_pow_exp, "", pow_gravel, "Exponent")
    
    lerp_gnd_alb = add_node(unreal.MaterialExpressionLinearInterpolate, -250, 150)
    connect(ts_playa_alb, "RGB", lerp_gnd_alb, "A")
    connect(ts_gravel_alb, "RGB", lerp_gnd_alb, "B")
    connect(pow_gravel, "", lerp_gnd_alb, "Alpha")
    
    lerp_gnd_nrm = add_node(unreal.MaterialExpressionLinearInterpolate, -250, 350)
    connect(ts_playa_nrm, "RGB", lerp_gnd_nrm, "A")
    connect(ts_gravel_nrm, "RGB", lerp_gnd_nrm, "B")
    connect(pow_gravel, "", lerp_gnd_nrm, "Alpha")

    # -------------------------------------------------------------
    # 5. Cliff Strata UVs: U = (WP.X + WP.Y) / 3500.0, V = WP.Z / 2500.0
    # -------------------------------------------------------------
    mask_wp_x = add_node(unreal.MaterialExpressionComponentMask, -1200, 800)
    mask_wp_x.set_editor_property("r", True)
    mask_wp_x.set_editor_property("g", False)
    mask_wp_x.set_editor_property("b", False)
    connect(wp, "XYZ", mask_wp_x, "")
    
    mask_wp_y = add_node(unreal.MaterialExpressionComponentMask, -1200, 920)
    mask_wp_y.set_editor_property("r", False)
    mask_wp_y.set_editor_property("g", True)
    mask_wp_y.set_editor_property("b", False)
    connect(wp, "XYZ", mask_wp_y, "")
    
    add_wp_xy = add_node(unreal.MaterialExpressionAdd, -1000, 850)
    connect(mask_wp_x, "", add_wp_xy, "A")
    connect(mask_wp_y, "", add_wp_xy, "B")
    
    c_cliff_u = add_node(unreal.MaterialExpressionConstant, -1000, 970)
    c_cliff_u.set_editor_property("r", 3500.0)
    div_cliff_u = add_node(unreal.MaterialExpressionDivide, -850, 850)
    connect(add_wp_xy, "", div_cliff_u, "A")
    connect(c_cliff_u, "", div_cliff_u, "B")
    
    mask_wp_z = add_node(unreal.MaterialExpressionComponentMask, -1200, 1100)
    mask_wp_z.set_editor_property("r", False)
    mask_wp_z.set_editor_property("g", False)
    mask_wp_z.set_editor_property("b", True)
    connect(wp, "XYZ", mask_wp_z, "")
    
    c_cliff_v = add_node(unreal.MaterialExpressionConstant, -1000, 1200)
    c_cliff_v.set_editor_property("r", 2500.0)
    div_cliff_v = add_node(unreal.MaterialExpressionDivide, -850, 1100)
    connect(mask_wp_z, "", div_cliff_v, "A")
    connect(c_cliff_v, "", div_cliff_v, "B")
    
    append_cliff_uv = add_node(unreal.MaterialExpressionAppendVector, -700, 950)
    connect(div_cliff_u, "", append_cliff_uv, "A")
    connect(div_cliff_v, "", append_cliff_uv, "B")
    
    ts_cliff_alb = add_node(unreal.MaterialExpressionTextureSample, -500, 850)
    tex_cliff_alb = get_texture("MDRS_Cliff_Strata_Albedo", "/Game/MRDTModels/URC_Hanksville/Materials/MDRS_Cliff_Strata_Albedo")
    if tex_cliff_alb:
        ts_cliff_alb.set_editor_property("texture", tex_cliff_alb)
        safe_set_property(ts_cliff_alb, ["sampler_source"], unreal.SamplerSourceMode.SSM_WRAP_WORLD_GROUP_SETTINGS)
    connect(append_cliff_uv, "", ts_cliff_alb, "Coordinates")
    
    ts_cliff_nrm = add_node(unreal.MaterialExpressionTextureSample, -500, 1050)
    tex_cliff_nrm = get_texture("MDRS_Cliff_Normal", "/Game/MRDTModels/URC_Hanksville/Materials/MDRS_Cliff_Normal")
    if tex_cliff_nrm:
        ts_cliff_nrm.set_editor_property("texture", tex_cliff_nrm)
        safe_set_property(ts_cliff_nrm, ["sampler_source"], unreal.SamplerSourceMode.SSM_WRAP_WORLD_GROUP_SETTINGS)
    connect(append_cliff_uv, "", ts_cliff_nrm, "Coordinates")

    # -------------------------------------------------------------
    # 6. Slope Mask: saturate(( (1 - saturate(VertexNormalWS.Z)) - 0.12 ) * 5.0)
    # -------------------------------------------------------------
    vert_norm = add_node(unreal.MaterialExpressionVertexNormalWS, -1000, 1400)
    mask_norm_z = add_node(unreal.MaterialExpressionComponentMask, -850, 1400)
    mask_norm_z.set_editor_property("r", False)
    mask_norm_z.set_editor_property("g", False)
    mask_norm_z.set_editor_property("b", True)
    connect(vert_norm, "", mask_norm_z, "")
    
    sat_norm_z = add_node(unreal.MaterialExpressionSaturate, -720, 1400)
    connect(mask_norm_z, "", sat_norm_z, "")
    
    one_minus_z = add_node(unreal.MaterialExpressionOneMinus, -620, 1400)
    connect(sat_norm_z, "", one_minus_z, "")
    
    c_slope_th = add_node(unreal.MaterialExpressionConstant, -620, 1500)
    c_slope_th.set_editor_property("r", 0.12)
    sub_slope = add_node(unreal.MaterialExpressionSubtract, -480, 1400)
    connect(one_minus_z, "", sub_slope, "A")
    connect(c_slope_th, "", sub_slope, "B")
    
    c_slope_mul = add_node(unreal.MaterialExpressionConstant, -480, 1500)
    c_slope_mul.set_editor_property("r", 5.0)
    mul_slope = add_node(unreal.MaterialExpressionMultiply, -350, 1400)
    connect(sub_slope, "", mul_slope, "A")
    connect(c_slope_mul, "", mul_slope, "B")
    
    cliff_mask = add_node(unreal.MaterialExpressionSaturate, -220, 1400)
    connect(mul_slope, "", cliff_mask, "")

    # -------------------------------------------------------------
    # 7. Blend Ground vs Cliff
    # -------------------------------------------------------------
    lerp_surf_alb = add_node(unreal.MaterialExpressionLinearInterpolate, -50, 300)
    connect(lerp_gnd_alb, "", lerp_surf_alb, "A")
    connect(ts_cliff_alb, "RGB", lerp_surf_alb, "B")
    connect(cliff_mask, "", lerp_surf_alb, "Alpha")
    
    lerp_surf_nrm = add_node(unreal.MaterialExpressionLinearInterpolate, -50, 500)
    connect(lerp_gnd_nrm, "", lerp_surf_nrm, "A")
    connect(ts_cliff_nrm, "RGB", lerp_surf_nrm, "B")
    connect(cliff_mask, "", lerp_surf_nrm, "Alpha")

    # -------------------------------------------------------------
    # 8. Satellite Regional Color Modulation
    # -------------------------------------------------------------
    c_sat_boost = add_node(unreal.MaterialExpressionConstant, -50, -50)
    c_sat_boost.set_editor_property("r", 1.6)
    mul_sat_boost = add_node(unreal.MaterialExpressionMultiply, 100, -100)
    connect(ts_sat, "RGB", mul_sat_boost, "A")
    connect(c_sat_boost, "", mul_sat_boost, "B")
    
    fg_albedo = add_node(unreal.MaterialExpressionMultiply, 220, 100)
    connect(lerp_surf_alb, "", fg_albedo, "A")
    connect(mul_sat_boost, "", fg_albedo, "B")

    # -------------------------------------------------------------
    # 9. Distance Fade (Fade to raw Satellite at 250m)
    # -------------------------------------------------------------
    cam_pos = add_node(unreal.MaterialExpressionCameraPositionWS, -400, -400)
    dist_node = add_node(unreal.MaterialExpressionDistance, -200, -350)
    connect(cam_pos, "", dist_node, "A")
    connect(wp, "XYZ", dist_node, "B")
    
    c_dist_scale = add_node(unreal.MaterialExpressionConstant, -200, -220)
    c_dist_scale.set_editor_property("r", 25000.0)
    div_dist = add_node(unreal.MaterialExpressionDivide, -50, -300)
    connect(dist_node, "", div_dist, "A")
    connect(c_dist_scale, "", div_dist, "B")
    
    dist_fade = add_node(unreal.MaterialExpressionSaturate, 100, -300)
    connect(div_dist, "", dist_fade, "")
    
    final_albedo = add_node(unreal.MaterialExpressionLinearInterpolate, 400, 100)
    connect(fg_albedo, "", final_albedo, "A")
    connect(ts_sat, "RGB", final_albedo, "B")
    connect(dist_fade, "", final_albedo, "Alpha")
    
    c_flat_norm = add_node(unreal.MaterialExpressionConstant3Vector, 150, 650)
    c_flat_norm.set_editor_property("constant", unreal.LinearColor(0.0, 0.0, 1.0, 1.0))
    
    final_normal = add_node(unreal.MaterialExpressionLinearInterpolate, 400, 500)
    connect(lerp_surf_nrm, "", final_normal, "A")
    connect(c_flat_norm, "", final_normal, "B")
    connect(dist_fade, "", final_normal, "Alpha")

    # -------------------------------------------------------------
    # 10. Roughness and Specular
    # -------------------------------------------------------------
    c_rough_gnd = add_node(unreal.MaterialExpressionConstant, 150, 800)
    c_rough_gnd.set_editor_property("r", 0.85)
    c_rough_clf = add_node(unreal.MaterialExpressionConstant, 150, 880)
    c_rough_clf.set_editor_property("r", 0.90)
    lerp_rough = add_node(unreal.MaterialExpressionLinearInterpolate, 350, 820)
    connect(c_rough_gnd, "", lerp_rough, "A")
    connect(c_rough_clf, "", lerp_rough, "B")
    connect(cliff_mask, "", lerp_rough, "Alpha")
    
    c_spec = add_node(unreal.MaterialExpressionConstant, 350, 980)
    c_spec.set_editor_property("r", 0.22)

    # -------------------------------------------------------------
    # 11. Connect to Material Outputs
    # -------------------------------------------------------------
    connect_prop(final_albedo, "", unreal.MaterialProperty.MP_BASE_COLOR)
    connect_prop(final_normal, "", unreal.MaterialProperty.MP_NORMAL)
    connect_prop(lerp_rough, "", unreal.MaterialProperty.MP_ROUGHNESS)
    connect_prop(c_spec, "", unreal.MaterialProperty.MP_SPECULAR)
    
    unreal.MaterialEditingLibrary.recompile_material(mat)
    unreal.EditorAssetLibrary.save_loaded_asset(mat)
    unreal.log("Material URC_Map_Material successfully built, compiled, and saved.")
    return mat

def get_all_actors_in_world():
    """Retrieve all actors currently present in the active editor world."""
    actors = []
    # Try EditorActorSubsystem
    try:
        subsystem = unreal.get_editor_subsystem(unreal.EditorActorSubsystem)
        if subsystem:
            actors = subsystem.get_all_level_actors()
    except Exception:
        pass
        
    # Fallback to EditorLevelLibrary
    if not actors:
        try:
            actors = unreal.EditorLevelLibrary.get_all_level_actors()
        except Exception:
            pass
            
    # Fallback to GameplayStatics
    if not actors:
        try:
            world = unreal.EditorLevelLibrary.get_editor_world()
            actors = unreal.GameplayStatics.get_all_actors_of_class(world, unreal.Actor)
        except Exception:
            pass
            
    return actors

def update_environment_and_landscape(mat):
    """Finds Landscape, UDS, and UDW in the loaded level and applies settings."""
    actors = get_all_actors_in_world()
    if not actors:
        unreal.log_warning("No level actors found. Ensure /Game/MRDTModels/URC_Hanksville/URC_MDRS is currently loaded in the viewport.")
        return

    landscape_found = False
    uds_found = False
    udw_found = False

    for actor in actors:
        actor_name = actor.get_name()
        label = ""
        try:
            label = actor.get_actor_label()
        except Exception:
            pass
        full_id = f"{actor_name} {label}".lower()

        # 1. Landscape Assignment
        if "landscape" in full_id and not landscape_found:
            try:
                safe_set_property(actor, ["landscape_material"], mat)
                landscape_found = True
                unreal.log(f"Successfully assigned URC_Map_Material to landscape actor: {actor_name}")
            except Exception as e:
                unreal.log_warning(f"Could not assign material to landscape: {e}")

        # 2. Ultra Dynamic Sky
        if ("ultra_dynamic_sky" in full_id or "ultradynamicsky" in full_id) and not uds_found:
            uds_found = True
            safe_set_property(actor, ["Dust Amount", "dust_amount", "dust"], 2.5)
            unreal.log(f"Configured atmospheric dust on {actor_name}: Dust Amount = 2.5")

        # 3. Ultra Dynamic Weather
        if ("ultra_dynamic_weather" in full_id or "ultradynamicweather" in full_id) and not udw_found:
            udw_found = True
            safe_set_property(actor, ["dust - Manual Override", "dust_manual_override"], True)
            safe_set_property(actor, ["dust"], 2.5)
            safe_set_property(actor, ["material Dust Coverage - Manual Override", "material_dust_coverage_manual_override"], True)
            safe_set_property(actor, ["material Dust Coverage", "material_dust_coverage"], 0.3)
            unreal.log(f"Configured dust weather overrides on {actor_name}")

if __name__ == "__main__":
    texture_folder = "/home/targed/Documents/Unreal Projects/URC_Map/Textures"
    mat_path = "/Game/MRDTModels/URC_Hanksville/URC_Map_Material"
    
    unreal.log("==================================================")
    unreal.log("Step 1: Importing PBR textures...")
    imported_textures = import_textures(texture_folder, "/Game/MRDTModels/URC_Hanksville/Materials")
    
    unreal.log("==================================================")
    unreal.log("Step 2: Building and compiling URC_Map_Material graph...")
    compiled_mat = build_material(mat_path, imported_textures)
    
    unreal.log("==================================================")
    unreal.log("Step 3: Assigning to Landscape and updating Sky/Weather...")
    update_environment_and_landscape(compiled_mat)
    
    unreal.log("==================================================")
    unreal.log("All URC Map updates completed successfully!")
