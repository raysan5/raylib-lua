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
#include "raylib-lua.h"         // raylib Lua binding

int main()
{
    //--------------------------------------------------------------------------------------
    InitLuaDevice();            // Init Lua device and resources

    ExecuteLuaFile("core_basic_window.lua");

    CloseLuaDevice();           // Close Lua device and free resources
    //--------------------------------------------------------------------------------------

    return 0;
}
