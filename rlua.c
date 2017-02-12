/*******************************************************************************************
*
*   rlua 1.0 - raylib Lua files launcher
*
*   DEPENDENCIES:
*
*   raylib 1.7 - This program uses latest raylib version (www.raylib.com)
*   Lua 5.3.4 - http://luabinaries.sourceforge.net/download.html
*
*   COMPILATION (MinGW 5.3.0):
*
*   gcc -o rlua.exe rlua.c -s $(RAYLIB_DIR)\raylib_icon                     /
*       -I../src -I../src/external/lua/include -L../src/external/lua/lib    /
*       -lraylib -lglfw3 -lopengl32 -lgdi32 -lopenal32 -lwinmm -llua53      /
*       -std=c99 -Wl,-allow-multiple-definition -Wl,--subsystem,windows
*
*   LICENSE: zlib/libpng
*
*   Copyright (c) 2016-2017 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
********************************************************************************************/

#include "raylib.h"

#define RLUA_IMPLEMENTATION
#include "rlua.h"

#include <string.h>             // Required for: strcmp()

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
//static const char *GetExtension(const char *fileName);  // Get extension from filename

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        // TODO: Support additional arguments for lua file execution
        
        if (strcmp(GetExtension(argv[1]), "lua") == 0)
        {
            InitLuaDevice();            // Initialize lua device
            
            ExecuteLuaFile(argv[1]);    // Execute lua program

            CloseLuaDevice();           // Close Lua device and free resources
        }
    }
    //--------------------------------------------------------------------------------------

    return 0;
}

//--------------------------------------------------------------------------------------------
// Helper functions
//--------------------------------------------------------------------------------------------
/*
// Get the extension for a filename
static const char *GetExtension(const char *fileName)
{
    const char *dot = strrchr(fileName, '.');
    if (!dot || dot == fileName) return "";
    return (dot + 1);
}
*/