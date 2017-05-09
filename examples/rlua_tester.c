/*******************************************************************************************
*
*   raylib [rlua] examples test suite
*
*   NOTE: This example requires Lua library (http://luabinaries.sourceforge.net/download.html)
*
*   Compile example using:
*   gcc -o rlua_tester.exe rlua_tester.c -s ../src/rlua_icon                /
*       -I../src -I../src/external/lua/include -L../src/external/lua/lib    /
*       -lraylib -lglfw3 -lopengl32 -lgdi32 -lopenal32 -lwinmm -llua53      /
*       -std=c99 -Wl,-allow-multiple-definition -Wl,--subsystem,windows
*
*   This example has been created using raylib 1.7 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2016-2017 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#define RLUA_IMPLEMENTATION
#include "rlua.h"               // raylib Lua binding

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitLuaDevice();
    //--------------------------------------------------------------------------------------

    // [core] module examples
    // ExecuteLuaFile("core/core_basic_window.lua");
    // ExecuteLuaFile("core/core_input_keys.lua");
    // ExecuteLuaFile("core/core_input_mouse.lua");
    // ExecuteLuaFile("core/core_mouse_wheel.lua");
    // ExecuteLuaFile("core/core_input_gamepad.lua");
    // ExecuteLuaFile("core/core_random_values.lua");
    // ExecuteLuaFile("core/core_color_select.lua");
    // ExecuteLuaFile("core/core_drop_files.lua");
    // ExecuteLuaFile("core/core_storage_values.lua");
    // ExecuteLuaFile("core/core_gestures_detection.lua");
    // ExecuteLuaFile("core/core_3d_mode.lua");
    // ExecuteLuaFile("core/core_3d_picking.lua");
    // ExecuteLuaFile("core/core_3d_camera_free.lua");
    // ExecuteLuaFile("core/core_3d_camera_first_person.lua");
    // ExecuteLuaFile("core/core_2d_camera.lua");
    // ExecuteLuaFile("core/core_world_screen.lua");
    // ExecuteLuaFile("core/core_vr_simulator.lua");
    
    // [shapes] module examples
    // ExecuteLuaFile("shapes/shapes_logo_raylib.lua");
    // ExecuteLuaFile("shapes/shapes_basic_shapes.lua");
    // ExecuteLuaFile("shapes/shapes_colors_palette.lua");
    // ExecuteLuaFile("shapes/shapes_logo_raylib_anim.lua");
    // ExecuteLuaFile("shapes/shapes_lines_bezier.lua");
    
    // [textures] module examples
    // ExecuteLuaFile("textures/textures_logo_raylib.lua");
    // ExecuteLuaFile("textures/textures_image_loading.lua");
    // ExecuteLuaFile("textures/textures_image_drawing.lua");
    // ExecuteLuaFile("textures/textures_image_processing.lua");    // ERROR: GetImageData() --> UpdateTexture()
    // ExecuteLuaFile("textures/textures_rectangle.lua");
    // ExecuteLuaFile("textures/textures_srcrec_dstrec.lua");
    // ExecuteLuaFile("textures/textures_to_image.lua");
    // ExecuteLuaFile("textures/textures_raw_data.lua");            // ERROR: LoadImageEx()
    // ExecuteLuaFile("textures/textures_particles_blending.lua");

    // [text] module examples
    // ExecuteLuaFile("text_sprite_fonts.lua");
    // ExecuteLuaFile("text_bmfont_ttf.lua");
    // ExecuteLuaFile("text_raylib_fonts.lua");
    // ExecuteLuaFile("text_format_text.lua");
    // ExecuteLuaFile("text_writing_anim.lua");
    // ExecuteLuaFile("text_ttf_loading.lua");
    // ExecuteLuaFile("text_bmfont_unordered.lua");
    ExecuteLuaFile("text/text_input_box.lua");
    
    // [models] module examples
    // ExecuteLuaFile("models_geometric_shapes.lua");
    // ExecuteLuaFile("models_box_collisions.lua");
    // ExecuteLuaFile("models_billboard.lua");
    // ExecuteLuaFile("models_obj_loading.lua");
    // ExecuteLuaFile("models_heightmap.lua");
    // ExecuteLuaFile("models_cubicmap.lua");
    // ExecuteLuaFile("models/models_mesh_picking.lua");
    
    // [shaders] module examples
    // ExecuteLuaFile("shaders_model_shader.lua");
    // ExecuteLuaFile("shaders_shapes_textures.lua");
    // ExecuteLuaFile("shaders_custom_uniform.lua");
    // ExecuteLuaFile("shaders_postprocessing.lua");
    
    // [audio] module examples
    // ExecuteLuaFile("audio_sound_loading.lua");
    // ExecuteLuaFile("audio_music_stream.lua");
    // ExecuteLuaFile("audio_module_playing.lua");
    // ExecuteLuaFile("audio_raw_stream.lua");      // ERROR: UpdateAudioStream()
    
    // [physac] module examples
    // ExecuteLuaFile("physics_demo.lua");
    // ExecuteLuaFile("physics_movement.lua");
    // ExecuteLuaFile("physics_friction.lua");
    // ExecuteLuaFile("physics_restitution.lua");
    // ExecuteLuaFile("physics_shatter.lua");
    
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseLuaDevice();        // Close Lua device and free resources
    //--------------------------------------------------------------------------------------

    return 0;
}
