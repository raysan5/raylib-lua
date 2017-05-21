/*******************************************************************************************
*
*   raylib [rlua] examples test suite
*
*   NOTE: This example requires Lua library (http://luabinaries.sourceforge.net/download.html)
*
*   Compile example using:
*   gcc -o rlua_tester.exe rlua_tester.c -s ../src/rlua_icon                /
*       -I../src -I../src/external/lua/include -L../src/external/lua/lib    /
*       -lraylib -lglfw3 -lopengl32 -lgdi32 -lopenal32 -lwinmm -llua53 -lpthread -static     /
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
#include "raylib-lua.h"               // raylib Lua binding

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitLuaDevice();
    //--------------------------------------------------------------------------------------

    // [core] module examples
    ChangeDirectory("./core");
    ExecuteLuaFile("core_basic_window.lua");
    // ExecuteLuaFile("core_input_keys.lua");
    // ExecuteLuaFile("core_input_mouse.lua");
    // ExecuteLuaFile("core_mouse_wheel.lua");
    // ExecuteLuaFile("core_input_gamepad.lua");
    // ExecuteLuaFile("core_random_values.lua");
    // ExecuteLuaFile("core_color_select.lua");
    // ExecuteLuaFile("core_drop_files.lua");
    // ExecuteLuaFile("core_storage_values.lua");
    // ExecuteLuaFile("core_gestures_detection.lua");
    // ExecuteLuaFile("core_3d_mode.lua");
    // ExecuteLuaFile("core_3d_picking.lua");
    // ExecuteLuaFile("core_3d_camera_free.lua");
    // ExecuteLuaFile("core_3d_camera_first_person.lua");
    // ExecuteLuaFile("core_2d_camera.lua");
    // ExecuteLuaFile("core_world_screen.lua");
    // ExecuteLuaFile("core_vr_simulator.lua");             // ERROR: Lua Error: attempt to index a nil value
    
    // [shapes] module examples
    // ChangeDirectory("./shapes");
    // ExecuteLuaFile("shapes_logo_raylib.lua");
    // ExecuteLuaFile("shapes_basic_shapes.lua");
    // ExecuteLuaFile("shapes_colors_palette.lua");
    // ExecuteLuaFile("shapes_logo_raylib_anim.lua");
    // ExecuteLuaFile("shapes_lines_bezier.lua");
    
    // [textures] module examples
    // ChangeDirectory("./textures");
    // ExecuteLuaFile("textures_logo_raylib.lua");
    // ExecuteLuaFile("textures_image_loading.lua");
    // ExecuteLuaFile("textures_image_drawing.lua");
    // ExecuteLuaFile("textures_image_processing.lua");     // ERROR: GetImageData() --> UpdateTexture()
    // ExecuteLuaFile("textures_rectangle.lua");
    // ExecuteLuaFile("textures_srcrec_dstrec.lua");
    // ExecuteLuaFile("textures_to_image.lua");
    // ExecuteLuaFile("textures_raw_data.lua");             // ERROR: LoadImageEx()
    // ExecuteLuaFile("textures_particles_blending.lua");

    // [text] module examples
    // ChangeDirectory("./text");
    // ExecuteLuaFile("text_sprite_fonts.lua");
    // ExecuteLuaFile("text_bmfont_ttf.lua");
    // ExecuteLuaFile("text_raylib_fonts.lua");
    // ExecuteLuaFile("text_format_text.lua");
    // ExecuteLuaFile("text_writing_anim.lua");
    // ExecuteLuaFile("text_ttf_loading.lua");
    // ExecuteLuaFile("text_bmfont_unordered.lua");
    // ExecuteLuaFile("text_input_box.lua");                // ERROR: Lua Error: attempt to index a string value
    
    // [models] module examples
    // ChangeDirectory("./models");
    // ExecuteLuaFile("models_geometric_shapes.lua");
    // ExecuteLuaFile("models_box_collisions.lua");
    // ExecuteLuaFile("models_billboard.lua");
    // ExecuteLuaFile("models_obj_loading.lua");
    // ExecuteLuaFile("models_heightmap.lua");
    // ExecuteLuaFile("models_cubicmap.lua");
    // ExecuteLuaFile("models_mesh_picking.lua");           // ERROR: Lua Error: attempt to index a nil value
    
    // [shaders] module examples
    // ChangeDirectory("./shaders");
    // ExecuteLuaFile("shaders_model_shader.lua");
    // ExecuteLuaFile("shaders_shapes_textures.lua");
    // ExecuteLuaFile("shaders_custom_uniform.lua");
    // ExecuteLuaFile("shaders_postprocessing.lua");
    
    // [audio] module examples
    // ChangeDirectory("./audio");
    // ExecuteLuaFile("audio_sound_loading.lua");
    // ExecuteLuaFile("audio_music_stream.lua");
    // ExecuteLuaFile("audio_module_playing.lua");
    // ExecuteLuaFile("audio_raw_stream.lua");              // ERROR: UpdateAudioStream()
    
    // TODO: [physac] module examples
    // ChangeDirectory("./physac");
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
