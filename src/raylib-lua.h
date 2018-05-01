/**********************************************************************************************
*
*   raylib-lua v1.7 - raylib Lua bindings for raylib v1.7
*
*   NOTES:
*
*   The following types are treated as objects with named fields, same as in C.
*       Color, Vector2, Vector3, Rectangle, Ray, Camera, Camera2D
*   
*   Lua defines utility functions to create those objects.
*
*   USAGE EXAMPLE:
*       local cl = Color(255,255,255,255)
*       local rec = Rectangle(10, 10, 100, 100)
*       local ray = Ray(Vector3(20, 20, 20), Vector3(50, 50, 50))
*       local x2 = rec.x + rec.width
*
*   The following types are immutable, and you can only read their non-pointer arguments.
*       Image, Texture2D, RenderTexture2D, SpriteFont
*
*   All other object types are opaque, that is, you cannot access or change their fields directly.
*
*   Remember that ALL raylib types have REFERENCE SEMANTICS in Lua.
*   There is currently no way to create a copy of an opaque object.
*
*   Some raylib functions take a pointer to an array, and the size of that array.
*   The equivalent Lua functions take only an array table of the specified type UNLESS
*   it's a pointer to a large char array (e.g. for images), then it takes (and potentially returns)
*   a Lua string (without the size argument, as Lua strings are sized by default).
*
*   Some raylib functions take pointers to objects to modify (e.g. ImageToPOT(), etc.)
*   In Lua, these functions take values and return a new changed value, instead.
*
*   So, in C:           ImageToPOT(&image, BLACK);
*   In Lua becomes:     image = ImageToPOT(image, BLACK)
*
*   Remember that Lua functions can return multiple values.
*   This is to preserve value semantics of raylib objects.
*
*   CONTRIBUTORS:
*       Ghassan Al-Mashareqa (ghassan@ghassan.pl): Original binding creation (for raylib 1.3)
*       Ramon Santamaria (@raysan5): Review, update and maintenance
*
*
*   LICENSE: zlib/libpng
*
*   Copyright (c) 2015-2017 Ghassan Al-Mashareqa and Ramon Santamaria (@raysan5)
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
**********************************************************************************************/

#pragma once

#include "raylib.h"

#define RLUA_STATIC
#ifdef RLUA_STATIC
    #define RLUADEF static            // Functions just visible to module including this file
#else
    #ifdef __cplusplus
        #define RLUADEF extern "C"    // Functions visible from other files (no name mangling of functions in C++)
    #else
        #define RLUADEF extern        // Functions visible from other files
    #endif
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
// ...

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
RLUADEF void InitLuaDevice(void);                   // Initialize Lua system
RLUADEF void ExecuteLuaCode(const char *code);      // Execute raylib Lua code
RLUADEF void ExecuteLuaFile(const char *filename);  // Execute raylib Lua script
RLUADEF void CloseLuaDevice(void);                  // De-initialize Lua system

/***********************************************************************************
*
*   RLUA IMPLEMENTATION
*
************************************************************************************/

#if defined(RLUA_IMPLEMENTATION)

#include "raylib.h"
#include "raymath.h"

#define PHYSAC_IMPLEMENTATION
#include "physac.h"

#include <string.h>
#include <stdlib.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
#define LuaPush_int(L, value)           lua_pushinteger(L, value)
#define LuaPush_float(L, value)         lua_pushnumber(L, value);
#define LuaPush_bool(L, value)          lua_pushboolean(L, value)
#define LuaPush_string(L, value)        lua_pushstring(L, value)

#define LuaPush_Image(L, img)           LuaPushOpaqueTypeWithMetatable(L, img, Image)
#define LuaPush_Texture2D(L, tex)       LuaPushOpaqueTypeWithMetatable(L, tex, Texture2D)
#define LuaPush_RenderTexture2D(L, tex) LuaPushOpaqueTypeWithMetatable(L, tex, RenderTexture2D)
#define LuaPush_SpriteFont(L, sf)       LuaPushOpaqueTypeWithMetatable(L, sf, SpriteFont)
#define LuaPush_Mesh(L, vd)             LuaPushOpaqueType(L, vd)
#define LuaPush_Shader(L, s)            LuaPushOpaqueType(L, s)
#define LuaPush_Sound(L, snd)           LuaPushOpaqueType(L, snd)
#define LuaPush_Wave(L, wav)            LuaPushOpaqueType(L, wav)
#define LuaPush_Music(L, mus)           LuaPushOpaqueType(L, mus)
#define LuaPush_AudioStream(L, aud)     LuaPushOpaqueType(L, aud)
#define LuaPush_PhysicsBody(L, body)    LuaPushOpaqueType(L, body)

#define LuaGetArgument_ptr              (void *)luaL_checkinteger
#define LuaGetArgument_int              (int)luaL_checkinteger
#define LuaGetArgument_unsigned         (unsigned)luaL_checkinteger
#define LuaGetArgument_char             (char)luaL_checkinteger
#define LuaGetArgument_float            (float)luaL_checknumber
#define LuaGetArgument_double           luaL_checknumber
#define LuaGetArgument_string           luaL_checkstring

#define LuaGetArgument_Image(L, img)        *(Image *)LuaGetArgumentOpaqueTypeWithMetatable(L, img, "Image")
#define LuaGetArgument_Texture2D(L, tex)    *(Texture2D *)LuaGetArgumentOpaqueTypeWithMetatable(L, tex, "Texture2D")
#define LuaGetArgument_RenderTexture2D(L, rtex) *(RenderTexture2D *)LuaGetArgumentOpaqueTypeWithMetatable(L, rtex, "RenderTexture2D")
#define LuaGetArgument_SpriteFont(L, sf)    *(SpriteFont *)LuaGetArgumentOpaqueTypeWithMetatable(L, sf, "SpriteFont")
#define LuaGetArgument_Mesh(L, vd)          *(Mesh *)LuaGetArgumentOpaqueType(L, vd)
#define LuaGetArgument_Shader(L, s)         *(Shader *)LuaGetArgumentOpaqueType(L, s)
#define LuaGetArgument_Sound(L, snd)        *(Sound *)LuaGetArgumentOpaqueType(L, snd)
#define LuaGetArgument_Wave(L, wav)         *(Wave *)LuaGetArgumentOpaqueType(L, wav)
#define LuaGetArgument_Music(L, mus)        *(Music *)LuaGetArgumentOpaqueType(L, mus)
#define LuaGetArgument_AudioStream(L, aud)  *(AudioStream *)LuaGetArgumentOpaqueType(L, aud)
#define LuaGetArgument_PhysicsBody(L, body) *(PhysicsBody *)LuaGetArgumentOpaqueType(L, body)

#define LuaPushOpaqueType(L, str)                    LuaPushOpaque(L, &str, sizeof(str))
#define LuaPushOpaqueTypeWithMetatable(L, str, meta) LuaPushOpaqueWithMetatable(L, &str, sizeof(str), #meta)

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
static lua_State* mainLuaState = 0;
static lua_State* L = 0;

//----------------------------------------------------------------------------------
// Module specific Functions Declaration
//----------------------------------------------------------------------------------
static void LuaPush_Color(lua_State* L, Color color);
static void LuaPush_Vector2(lua_State* L, Vector2 vec);
static void LuaPush_Vector3(lua_State* L, Vector3 vec);
static void LuaPush_Vector4(lua_State* L, Vector4 vec);
static void LuaPush_Quaternion(lua_State* L, Quaternion vec);
static void LuaPush_Matrix(lua_State* L, Matrix *matrix);
static void LuaPush_Rectangle(lua_State* L, Rectangle rect);
static void LuaPush_Camera(lua_State* L, Camera cam);
static void LuaPush_Camera2D(lua_State* L, Camera2D cam);
static void LuaPush_Model(lua_State* L, Model mdl);
static void LuaPush_Ray(lua_State* L, Ray ray);
static void LuaPush_RayHitInfo(lua_State* L, RayHitInfo hit);

static Color LuaGetArgument_Color(lua_State* L, int index);
static Vector2 LuaGetArgument_Vector2(lua_State* L, int index);
static Vector3 LuaGetArgument_Vector3(lua_State* L, int index);
static Vector4 LuaGetArgument_Vector4(lua_State* L, int index);
static Quaternion LuaGetArgument_Quaternion(lua_State* L, int index);
static Matrix LuaGetArgument_Matrix(lua_State* L, int index);
static Rectangle LuaGetArgument_Rectangle(lua_State* L, int index);
static Camera LuaGetArgument_Camera(lua_State* L, int index);
static Camera2D LuaGetArgument_Camera2D(lua_State* L, int index);
static Model LuaGetArgument_Model(lua_State* L, int index);
static Ray LuaGetArgument_Ray(lua_State* L, int index);

//----------------------------------------------------------------------------------
// rlua Helper Functions
//----------------------------------------------------------------------------------
static void LuaStartEnum(void)
{
    lua_newtable(L);
}

static void LuaSetEnum(const char *name, int value)
{
    LuaPush_int(L, value);
    lua_setfield(L, -2, name);
}

static void LuaSetEnumColor(const char *name, Color color)
{
    LuaPush_Color(L, color);
    lua_setfield(L, -2, name);
}

static void LuaEndEnum(const char *name)
{
    lua_setglobal(L, name);
}

static void LuaPushOpaque(lua_State* L, void *ptr, size_t size)
{
    void *ud = lua_newuserdata(L, size);
    memcpy(ud, ptr, size);
}

static void LuaPushOpaqueWithMetatable(lua_State* L, void *ptr, size_t size, const char *metatable_name)
{
    void *ud = lua_newuserdata(L, size);
    memcpy(ud, ptr, size);
    luaL_setmetatable(L, metatable_name);
}

static void* LuaGetArgumentOpaqueType(lua_State* L, int index)
{
    return lua_touserdata(L, index);
}

static void* LuaGetArgumentOpaqueTypeWithMetatable(lua_State* L, int index, const char *metatable_name)
{
    return luaL_checkudata(L, index, metatable_name);
}

//----------------------------------------------------------------------------------
// LuaIndex* functions
//----------------------------------------------------------------------------------
static int LuaIndexImage(lua_State* L)
{
    Image img = LuaGetArgument_Image(L, 1);
    const char *key = luaL_checkstring(L, 2);
    
    if (!strcmp(key, "width")) LuaPush_int(L, img.width);
    else if (!strcmp(key, "height")) LuaPush_int(L, img.height);
    else if (!strcmp(key, "mipmaps")) LuaPush_int(L, img.mipmaps);
    else if (!strcmp(key, "format")) LuaPush_int(L, img.format);
    else return 0;
    
    return 1;
}

static int LuaIndexTexture2D(lua_State* L)
{
    Texture2D img = LuaGetArgument_Texture2D(L, 1);
    const char *key = luaL_checkstring(L, 2);
    
    if (!strcmp(key, "width")) LuaPush_int(L, img.width);
    else if (!strcmp(key, "height")) LuaPush_int(L, img.height);
    else if (!strcmp(key, "mipmaps")) LuaPush_int(L, img.mipmaps);
    else if (!strcmp(key, "format")) LuaPush_int(L, img.format);
    else if (!strcmp(key, "id")) LuaPush_int(L, img.id);
    else return 0;

    return 1;
}

static int LuaIndexRenderTexture2D(lua_State* L)
{
    RenderTexture2D img = LuaGetArgument_RenderTexture2D(L, 1);
    const char *key = luaL_checkstring(L, 2);
    
    if (!strcmp(key, "texture")) LuaPush_Texture2D(L, img.texture);
    else if (!strcmp(key, "depth")) LuaPush_Texture2D(L, img.depth);
    else return 0;
    
    return 1;
}

static int LuaIndexSpriteFont(lua_State* L)
{
    SpriteFont img = LuaGetArgument_SpriteFont(L, 1);
    const char *key = luaL_checkstring(L, 2);
    
    if (!strcmp(key, "baseSize")) LuaPush_int(L, img.baseSize);
    else if (!strcmp(key, "texture")) LuaPush_Texture2D(L, img.texture);
    else if (!strcmp(key, "charsCount")) LuaPush_int(L, img.charsCount);
    else return 0;
    
    return 1;
}

static void LuaBuildOpaqueMetatables(void)
{
    luaL_newmetatable(L, "Image");
    lua_pushcfunction(L, &LuaIndexImage);
    lua_setfield(L, -2, "__index");
    lua_pop(L, 1);

    luaL_newmetatable(L, "Texture2D");
    lua_pushcfunction(L, &LuaIndexTexture2D);
    lua_setfield(L, -2, "__index");
    lua_pop(L, 1);

    luaL_newmetatable(L, "RenderTexture2D");
    lua_pushcfunction(L, &LuaIndexRenderTexture2D);
    lua_setfield(L, -2, "__index");
    lua_pop(L, 1);

    luaL_newmetatable(L, "SpriteFont");
    lua_pushcfunction(L, &LuaIndexSpriteFont);
    lua_setfield(L, -2, "__index");
    lua_pop(L, 1);
}

//----------------------------------------------------------------------------------
// LuaGetArgument functions
//----------------------------------------------------------------------------------

static Vector2 LuaGetArgument_Vector2(lua_State* L, int index)
{
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "x") == LUA_TNUMBER, index, "Expected Vector2");
    float x = (float)lua_tonumber(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "y") == LUA_TNUMBER, index, "Expected Vector2");
    float y = (float)lua_tonumber(L, -1);
    lua_pop(L, 2);
    return (Vector2) { x, y };
}

static Vector3 LuaGetArgument_Vector3(lua_State* L, int index)
{
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "x") == LUA_TNUMBER, index, "Expected Vector3");
    float x = (float)lua_tonumber(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "y") == LUA_TNUMBER, index, "Expected Vector3");
    float y = (float)lua_tonumber(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "z") == LUA_TNUMBER, index, "Expected Vector3");
    float z = (float)lua_tonumber(L, -1);
    lua_pop(L, 3);
    return (Vector3) { x, y, z };
}

static Quaternion LuaGetArgument_Quaternion(lua_State* L, int index)
{
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "x") == LUA_TNUMBER, index, "Expected Quaternion");
    float x = (float)lua_tonumber(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "y") == LUA_TNUMBER, index, "Expected Quaternion");
    float y = (float)lua_tonumber(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "z") == LUA_TNUMBER, index, "Expected Quaternion");
    float z = (float)lua_tonumber(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "w") == LUA_TNUMBER, index, "Expected Quaternion");
    float w = (float)lua_tonumber(L, -1);
    lua_pop(L, 4);
    return (Quaternion) { x, y, z, w };
}

static Matrix LuaGetArgument_Matrix(lua_State* L, int index)
{
    Matrix result = { 0 };
    float* ptr = &result.m0;
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values

    for (int i = 0; i < 16; i++)
    {
        lua_geti(L, index, i+1);
        ptr[i] = luaL_checknumber(L, -1);
    }
    lua_pop(L, 16);
    return result;
}

static Color LuaGetArgument_Color(lua_State* L, int index)
{
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "r") == LUA_TNUMBER, index, "Expected Color");
    unsigned char r = (unsigned char)lua_tointeger(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "g") == LUA_TNUMBER, index, "Expected Color");
    unsigned char g = (unsigned char)lua_tointeger(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "b") == LUA_TNUMBER, index, "Expected Color");
    unsigned char b = (unsigned char)lua_tointeger(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "a") == LUA_TNUMBER, index, "Expected Color");
    unsigned char a = (unsigned char)lua_tointeger(L, -1);
    lua_pop(L, 4);
    return (Color) { r, g, b, a };
}

static Rectangle LuaGetArgument_Rectangle(lua_State* L, int index)
{
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "x") == LUA_TNUMBER, index, "Expected Rectangle");
    int x = (int)lua_tointeger(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "y") == LUA_TNUMBER, index, "Expected Rectangle");
    int y = (int)lua_tointeger(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "width") == LUA_TNUMBER, index, "Expected Rectangle");
    int w = (int)lua_tointeger(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "height") == LUA_TNUMBER, index, "Expected Rectangle");
    int h = (int)lua_tointeger(L, -1);
    lua_pop(L, 4);
    return (Rectangle) { x, y, w, h };
}

static Camera LuaGetArgument_Camera(lua_State* L, int index)
{
    Camera result;
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "position") == LUA_TTABLE, index, "Expected Camera");
    result.position = LuaGetArgument_Vector3(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "target") == LUA_TTABLE, index, "Expected Camera");
    result.target = LuaGetArgument_Vector3(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "up") == LUA_TTABLE, index, "Expected Camera");
    result.up = LuaGetArgument_Vector3(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "fovy") == LUA_TNUMBER, index, "Expected Camera");
    result.fovy = LuaGetArgument_float(L, -1);
    lua_pop(L, 4);
    return result;
}

static Camera2D LuaGetArgument_Camera2D(lua_State* L, int index)
{
    Camera2D result;
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "offset") == LUA_TTABLE, index, "Expected Camera2D");
    result.offset = LuaGetArgument_Vector2(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "target") == LUA_TTABLE, index, "Expected Camera2D");
    result.target = LuaGetArgument_Vector2(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "rotation") == LUA_TNUMBER, index, "Expected Camera2D");
    result.rotation = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "zoom") == LUA_TNUMBER, index, "Expected Camera2D");
    result.zoom = LuaGetArgument_float(L, -1);
    lua_pop(L, 4);
    return result;
}

static BoundingBox LuaGetArgument_BoundingBox(lua_State* L, int index)
{
    BoundingBox result;
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "min") == LUA_TTABLE, index, "Expected BoundingBox");
    result.min = LuaGetArgument_Vector3(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "max") == LUA_TTABLE, index, "Expected BoundingBox");
    result.max = LuaGetArgument_Vector3(L, -1);
    lua_pop(L, 2);
    return result;
}

static Ray LuaGetArgument_Ray(lua_State* L, int index)
{
    Ray result;
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "position") == LUA_TTABLE, index, "Expected Ray");
    result.position = LuaGetArgument_Vector3(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "direction") == LUA_TTABLE, index, "Expected Ray");
    result.direction = LuaGetArgument_Vector3(L, -1);
    lua_pop(L, 2);
    return result;
}

static Material LuaGetArgument_Material(lua_State* L, int index)
{
    Material result;
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "shader") == LUA_TUSERDATA, index, "Expected Material");
    result.shader = LuaGetArgument_Shader(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "texDiffuse") == LUA_TUSERDATA, index, "Expected Material");
    result.texDiffuse = LuaGetArgument_Texture2D(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "texNormal") == LUA_TUSERDATA, index, "Expected Material");
    result.texNormal = LuaGetArgument_Texture2D(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "texSpecular") == LUA_TUSERDATA, index, "Expected Material");
    result.texSpecular = LuaGetArgument_Texture2D(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "colDiffuse") == LUA_TTABLE, index, "Expected Material");
    result.colDiffuse = LuaGetArgument_Color(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "colAmbient") == LUA_TTABLE, index, "Expected Material");
    result.colAmbient = LuaGetArgument_Color(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "colSpecular") == LUA_TTABLE, index, "Expected Material");
    result.colSpecular = LuaGetArgument_Color(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "glossiness") == LUA_TNUMBER, index, "Expected Material");
    result.glossiness = LuaGetArgument_float(L, -1);
    lua_pop(L, 8);
    return result;
}

static Model LuaGetArgument_Model(lua_State* L, int index)
{
    Model result;
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "mesh") == LUA_TUSERDATA, index, "Expected Model");
    result.mesh = LuaGetArgument_Mesh(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "transform") == LUA_TTABLE, index, "Expected Model");
    result.transform = LuaGetArgument_Matrix(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "material") == LUA_TTABLE, index, "Expected Model");
    result.material = LuaGetArgument_Material(L, -1);
    lua_pop(L, 3);
    return result;
}

//----------------------------------------------------------------------------------
// LuaPush functions
//----------------------------------------------------------------------------------
static void LuaPush_Color(lua_State* L, Color color)
{
    lua_createtable(L, 0, 4);
    LuaPush_int(L, color.r);
    lua_setfield(L, -2, "r");
    LuaPush_int(L, color.g);
    lua_setfield(L, -2, "g");
    LuaPush_int(L, color.b);
    lua_setfield(L, -2, "b");
    LuaPush_int(L, color.a);
    lua_setfield(L, -2, "a");
}

static void LuaPush_Vector2(lua_State* L, Vector2 vec)
{
    lua_createtable(L, 0, 2);
    LuaPush_float(L, vec.x);
    lua_setfield(L, -2, "x");
    LuaPush_float(L, vec.y);
    lua_setfield(L, -2, "y");
}

static void LuaPush_Vector3(lua_State* L, Vector3 vec)
{
    lua_createtable(L, 0, 3);
    LuaPush_float(L, vec.x);
    lua_setfield(L, -2, "x");
    LuaPush_float(L, vec.y);
    lua_setfield(L, -2, "y");
    LuaPush_float(L, vec.z);
    lua_setfield(L, -2, "z");
}

static void LuaPush_Quaternion(lua_State* L, Quaternion vec)
{
    lua_createtable(L, 0, 4);
    LuaPush_float(L, vec.x);
    lua_setfield(L, -2, "x");
    LuaPush_float(L, vec.y);
    lua_setfield(L, -2, "y");
    LuaPush_float(L, vec.z);
    lua_setfield(L, -2, "z");
    LuaPush_float(L, vec.w);
    lua_setfield(L, -2, "w");
}

static void LuaPush_Matrix(lua_State* L, Matrix *matrix)
{
    int i;
    lua_createtable(L, 16, 0);
    float* num = (&matrix->m0);
    for (i = 0; i < 16; i++)
    {
        LuaPush_float(L, num[i]);
        lua_rawseti(L, -2, i + 1);
    }
}

static void LuaPush_Rectangle(lua_State* L, Rectangle rect)
{
    lua_createtable(L, 0, 4);
    LuaPush_int(L, rect.x);
    lua_setfield(L, -2, "x");
    LuaPush_int(L, rect.y);
    lua_setfield(L, -2, "y");
    LuaPush_int(L, rect.width);
    lua_setfield(L, -2, "width");
    LuaPush_int(L, rect.height);
    lua_setfield(L, -2, "height");
}

static void LuaPush_Ray(lua_State* L, Ray ray)
{
    lua_createtable(L, 0, 2);
    LuaPush_Vector3(L, ray.position);
    lua_setfield(L, -2, "position");
    LuaPush_Vector3(L, ray.direction);
    lua_setfield(L, -2, "direction");
}

static void LuaPush_RayHitInfo(lua_State* L, RayHitInfo hit)
{
    lua_createtable(L, 0, 4);
    LuaPush_int(L, hit.hit);
    lua_setfield(L, -2, "hit");
    LuaPush_float(L, hit.distance);
    lua_setfield(L, -2, "distance");
    LuaPush_Vector3(L, hit.position);
    lua_setfield(L, -2, "position");
    LuaPush_Vector3(L, hit.normal);
    lua_setfield(L, -2, "normal");
}

static void LuaPush_BoundingBox(lua_State* L, BoundingBox bb)
{
    lua_createtable(L, 0, 2);
    LuaPush_Vector3(L, bb.min);
    lua_setfield(L, -2, "min");
    LuaPush_Vector3(L, bb.max);
    lua_setfield(L, -2, "max");
}

static void LuaPush_Camera(lua_State* L, Camera cam)
{
    lua_createtable(L, 0, 4);
    LuaPush_Vector3(L, cam.position);
    lua_setfield(L, -2, "position");
    LuaPush_Vector3(L, cam.target);
    lua_setfield(L, -2, "target");
    LuaPush_Vector3(L, cam.up);
    lua_setfield(L, -2, "up");
    LuaPush_float(L, cam.fovy);
    lua_setfield(L, -2, "fovy");
}

static void LuaPush_Camera2D(lua_State* L, Camera2D cam)
{
    lua_createtable(L, 0, 4);
    LuaPush_Vector2(L, cam.offset);
    lua_setfield(L, -2, "offset");
    LuaPush_Vector2(L, cam.target);
    lua_setfield(L, -2, "target");
    LuaPush_float(L, cam.rotation);
    lua_setfield(L, -2, "rotation");
    LuaPush_float(L, cam.zoom);
    lua_setfield(L, -2, "zoom");
}

static void LuaPush_Material(lua_State* L, Material mat)
{
    lua_createtable(L, 0, 8);
    LuaPush_Shader(L, mat.shader);
    lua_setfield(L, -2, "shader");
    LuaPush_Texture2D(L, mat.texDiffuse);
    lua_setfield(L, -2, "texDiffuse");
    LuaPush_Texture2D(L, mat.texNormal);
    lua_setfield(L, -2, "texNormal");
    LuaPush_Texture2D(L, mat.texSpecular);
    lua_setfield(L, -2, "texSpecular");
    LuaPush_Color(L, mat.colDiffuse);
    lua_setfield(L, -2, "colDiffuse");
    LuaPush_Color(L, mat.colAmbient);
    lua_setfield(L, -2, "colAmbient");
    LuaPush_Color(L, mat.colSpecular);
    lua_setfield(L, -2, "colSpecular");
    LuaPush_float(L, mat.glossiness);
    lua_setfield(L, -2, "glossiness");
}

static void LuaPush_Model(lua_State* L, Model mdl)
{
    lua_createtable(L, 0, 4);
    LuaPush_Mesh(L, mdl.mesh);
    lua_setfield(L, -2, "mesh");
    LuaPush_Matrix(L, &mdl.transform);
    lua_setfield(L, -2, "transform");
    LuaPush_Material(L, mdl.material);
    lua_setfield(L, -2, "material");
}

//----------------------------------------------------------------------------------
// raylib Lua Structure constructors
//----------------------------------------------------------------------------------
static int lua_Color(lua_State* L)
{
    LuaPush_Color(L, (Color) { (unsigned char)luaL_checkinteger(L, 1), (unsigned char)luaL_checkinteger(L, 2), (unsigned char)luaL_checkinteger(L, 3), (unsigned char)luaL_checkinteger(L, 4) });
    return 1;
}

static int lua_Vector2(lua_State* L)
{
    LuaPush_Vector2(L, (Vector2) { (float)luaL_checknumber(L, 1), (float)luaL_checknumber(L, 2) });
    return 1;
}

static int lua_Vector3(lua_State* L)
{
    LuaPush_Vector3(L, (Vector3) { (float)luaL_checknumber(L, 1), (float)luaL_checknumber(L, 2), (float)luaL_checknumber(L, 3) });
    return 1;
}

static int lua_Quaternion(lua_State* L)
{
    LuaPush_Quaternion(L, (Quaternion) { (float)luaL_checknumber(L, 1), (float)luaL_checknumber(L, 2), (float)luaL_checknumber(L, 3), (float)luaL_checknumber(L, 4) });
    return 1;
}

static int lua_Rectangle(lua_State* L)
{
    LuaPush_Rectangle(L, (Rectangle) { (int)luaL_checkinteger(L, 1), (int)luaL_checkinteger(L, 2), (int)luaL_checkinteger(L, 3), (int)luaL_checkinteger(L, 4) });
    return 1;
}

static int lua_Ray(lua_State* L)
{
    Vector3 pos = LuaGetArgument_Vector3(L, 1);
    Vector3 dir = LuaGetArgument_Vector3(L, 2);
    LuaPush_Ray(L, (Ray) { { pos.x, pos.y, pos.z }, { dir.x, dir.y, dir.z } });
    return 1;
}

static int lua_RayHitInfo(lua_State* L)
{
    int hit = LuaGetArgument_int(L, 1);
    float dis = LuaGetArgument_float(L, 2);
    Vector3 pos = LuaGetArgument_Vector3(L, 3);
    Vector3 norm = LuaGetArgument_Vector3(L, 4);
    LuaPush_RayHitInfo(L, (RayHitInfo) { hit, dis, { pos.x, pos.y, pos.z }, { norm.x, norm.y, norm.z } });
    return 1;
}

static int lua_BoundingBox(lua_State* L)
{
    Vector3 min = LuaGetArgument_Vector3(L, 1);
    Vector3 max = LuaGetArgument_Vector3(L, 2);
    LuaPush_BoundingBox(L, (BoundingBox) { { min.x, min.y, min.z }, { max.x, max.y, max.z } });
    return 1;
}

static int lua_Camera(lua_State* L)
{
    Vector3 pos = LuaGetArgument_Vector3(L, 1);
    Vector3 tar = LuaGetArgument_Vector3(L, 2);
    Vector3 up = LuaGetArgument_Vector3(L, 3);
    float fovy = LuaGetArgument_float(L, 4);
    LuaPush_Camera(L, (Camera) { { pos.x, pos.y, pos.z }, { tar.x, tar.y, tar.z }, { up.x, up.y, up.z }, fovy });
    return 1;
}

static int lua_Camera2D(lua_State* L)
{
    Vector2 off = LuaGetArgument_Vector2(L, 1);
    Vector2 tar = LuaGetArgument_Vector2(L, 2);
    float rot = LuaGetArgument_float(L, 3);
    float zoom = LuaGetArgument_float(L, 4);
    LuaPush_Camera2D(L, (Camera2D) { { off.x, off.y }, { tar.x, tar.y }, rot, zoom });
    return 1;
}

/*************************************************************************************
*
*  raylib Lua Functions Bindings
*
**************************************************************************************/

//------------------------------------------------------------------------------------
// raylib [core] module functions - Window and Graphics Device
//------------------------------------------------------------------------------------

// Initialize window and OpenGL context
int lua_InitWindow(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    const char *arg3 = LuaGetArgument_string(L, 3);
    InitWindow(arg1, arg2, arg3);
    return 0;
}

// Close window and unload OpenGL context
int lua_CloseWindow(lua_State* L)
{
    CloseWindow();
    return 0;
}

// Check if KEY_ESCAPE pressed or Close icon pressed
int lua_WindowShouldClose(lua_State* L)
{
    bool result = WindowShouldClose();
    LuaPush_bool(L, result);
    return 1;
}

// Check if window has been minimized (or lost focus)
int lua_IsWindowMinimized(lua_State* L)
{
    bool result = IsWindowMinimized();
    LuaPush_bool(L, result);
    return 1;
}

// Toggle fullscreen mode (only PLATFORM_DESKTOP)
int lua_ToggleFullscreen(lua_State* L)
{
    ToggleFullscreen();
    return 0;
}

// Set icon for window (only PLATFORM_DESKTOP)
int lua_SetWindowIcon(lua_State* L)
{
    Image arg1 = LuaGetArgument_Image(L, 1);
    SetWindowIcon(arg1);
    return 0;
}

// Set window position on screen (only PLATFORM_DESKTOP)
int lua_SetWindowPosition(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    SetWindowPosition(arg1, arg2);
    return 0;
}

// Set monitor for the current window (fullscreen mode)
int lua_SetWindowMonitor(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    SetWindowMonitor(arg1);
    return 0;
}

// Set window minimum dimensions (FLAG_WINDOW_RESIZABLE)
int lua_SetWindowMinSize(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    SetWindowMinSize(arg1, arg2);
    return 0;
}

// Get current screen width
int lua_GetScreenWidth(lua_State* L)
{
    int result = GetScreenWidth();
    LuaPush_int(L, result);
    return 1;
}

// Get current screen height
int lua_GetScreenHeight(lua_State* L)
{
    int result = GetScreenHeight();
    LuaPush_int(L, result);
    return 1;
}

// Shows cursor
int lua_ShowCursor(lua_State* L)
{
    ShowCursor();
    return 0;
}

// Hides cursor
int lua_HideCursor(lua_State* L)
{
    HideCursor();
    return 0;
}

// Check if cursor is not visible
int lua_IsCursorHidden(lua_State* L)
{
    bool result = IsCursorHidden();
    LuaPush_bool(L, result);
    return 1;
}

// Enables cursor (unlock cursor)
int lua_EnableCursor(lua_State* L)
{
    EnableCursor();
    return 0;
}

// Disables cursor (lock cursor)
int lua_DisableCursor(lua_State* L)
{
    DisableCursor();
    return 0;
}

// Set background color (framebuffer clear color)
int lua_ClearBackground(lua_State* L)
{
    Color arg1 = LuaGetArgument_Color(L, 1);
    ClearBackground(arg1);
    return 0;
}

// Setup canvas (framebuffer) to start drawing
int lua_BeginDrawing(lua_State* L)
{
    BeginDrawing();
    return 0;
}

// End canvas drawing and swap buffers (double buffering)
int lua_EndDrawing(lua_State* L)
{
    EndDrawing();
    return 0;
}

// Initialize 2D mode with custom camera (2D)
int lua_Begin2dMode(lua_State* L)
{
    Camera2D arg1 = LuaGetArgument_Camera2D(L, 1);
    Begin2dMode(arg1);
    return 0;
}

// Ends 2D mode with custom camera
int lua_End2dMode(lua_State* L)
{
    End2dMode();
    return 0;
}

// Initializes 3D mode with custom camera (3D)
int lua_Begin3dMode(lua_State* L)
{
    Camera arg1 = LuaGetArgument_Camera(L, 1);
    Begin3dMode(arg1);
    return 0;
}

// Ends 3D mode and returns to default 2D orthographic mode
int lua_End3dMode(lua_State* L)
{
    End3dMode();
    return 0;
}

// Initializes render texture for drawing
int lua_BeginTextureMode(lua_State* L)
{
    RenderTexture2D arg1 = LuaGetArgument_RenderTexture2D(L, 1);
    BeginTextureMode(arg1);
    return 0;
}

// Ends drawing to render texture
int lua_EndTextureMode(lua_State* L)
{
    EndTextureMode();
    return 0;
}

// Returns a ray trace from mouse position
int lua_GetMouseRay(lua_State* L)
{
    Vector2 arg1 = LuaGetArgument_Vector2(L, 1);
    Camera arg2 = LuaGetArgument_Camera(L, 2);
    Ray result = GetMouseRay(arg1, arg2);
    LuaPush_Ray(L, result);
    return 1;
}

// Returns the screen space position for a 3d world space position
int lua_GetWorldToScreen(lua_State* L)
{
    Vector3 arg1 = LuaGetArgument_Vector3(L, 1);
    Camera arg2 = LuaGetArgument_Camera(L, 2);
    Vector2 result = GetWorldToScreen(arg1, arg2);
    LuaPush_Vector2(L, result);
    return 1;
}

// Returns camera transform matrix (view matrix)
int lua_GetCameraMatrix(lua_State* L)
{
    Camera arg1 = LuaGetArgument_Camera(L, 1);
    Matrix result = GetCameraMatrix(arg1);
    LuaPush_Matrix(L, &result);
    return 1;
}

#if defined(PLATFORM_WEB)
static int LuaDrawLoopFunc;

static void LuaDrawLoop()
{
    lua_rawgeti(L, LUA_REGISTRYINDEX, LuaDrawLoopFunc);
    lua_call(L, 0, 0);
}

int lua_SetDrawingLoop(lua_State* L)
{
    luaL_argcheck(L, lua_isfunction(L, 1), 1, "Loop function expected");
    lua_pushvalue(L, 1);
    LuaDrawLoopFunc = luaL_ref(L, LUA_REGISTRYINDEX);
    SetDrawingLoop(&LuaDrawLoop);
    return 0;
}
#else
// Set target FPS (maximum)
int lua_SetTargetFPS(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    SetTargetFPS(arg1);
    return 0;
}
#endif

// Returns current FPS
int lua_GetFPS(lua_State* L)
{
    float result = GetFPS();
    LuaPush_float(L, result);
    return 1;
}

// Returns time in seconds for last frame drawn
int lua_GetFrameTime(lua_State* L)
{
    float result = GetFrameTime();
    LuaPush_float(L, result);
    return 1;
}

// Returns a Color struct from hexadecimal value
int lua_GetColor(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    Color result = GetColor(arg1);
    LuaPush_Color(L, result);
    return 1;
}

// Returns hexadecimal value for a Color
int lua_GetHexValue(lua_State* L)
{
    Color arg1 = LuaGetArgument_Color(L, 1);
    int result = GetHexValue(arg1);
    LuaPush_int(L, result);
    return 1;
}

// Converts Color to float array and normalizes
int lua_ColorToFloat(lua_State* L)
{
    Color arg1 = LuaGetArgument_Color(L, 1);
    float *result = ColorToFloat(arg1);
    lua_createtable(L, 4, 0);
    for (int i = 0; i < 4; i++)
    {
        LuaPush_float(L, result[i]);
        lua_rawseti(L, -2, i + 1);
    }
    free(result);
    return 1;
}

// Converts Vector3 to float array
int lua_VectorToFloat(lua_State* L)
{
    Vector3 arg1 = LuaGetArgument_Vector3(L, 1);
    float *result = VectorToFloat(arg1);
    lua_createtable(L, 3, 0);
    for (int i = 0; i < 3; i++)
    {
        LuaPush_float(L, result[i]);
        lua_rawseti(L, -2, i + 1);
    }
    free(result);
    return 1;
}

// Converts Matrix to float array
int lua_MatrixToFloat(lua_State* L)
{
    Matrix arg1 = LuaGetArgument_Matrix(L, 1);
    float *result = MatrixToFloat(arg1);
    lua_createtable(L, 16, 0);
    for (int i = 0; i < 16; i++)
    {
        LuaPush_float(L, result[i]);
        lua_rawseti(L, -2, i + 1);
    }
    free(result);
    return 1;
}

// Returns a random value between min and max (both included)
int lua_GetRandomValue(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    int result = GetRandomValue(arg1, arg2);
    LuaPush_int(L, result);
    return 1;
}

// Color fade-in or fade-out, alpha goes from 0.0f to 1.0f
int lua_Fade(lua_State* L)
{
    Color arg1 = LuaGetArgument_Color(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    Color result = Fade(arg1, arg2);
    LuaPush_Color(L, result);
    return 1;
}

// Activate raylib logo at startup (can be done with flags)
int lua_ShowLogo(lua_State* L)
{
    ShowLogo();
    return 0;
}

// Setup window configuration flags (view FLAGS)
int lua_SetConfigFlags(lua_State* L)
{
    char arg1 = LuaGetArgument_char(L, 1);
    SetConfigFlags(arg1);
    return 0;
}

// Show trace log messages (INFO, WARNING, ERROR, DEBUG)
int lua_TraceLog(lua_State* L)
{
    int num_args = lua_gettop(L) - 1;
    int arg1 = LuaGetArgument_int(L, 1);

    /// type, fmt, args...

    lua_rotate(L, 1, -1); /// fmt, args..., type
    lua_pop(L, 1); /// fmt, args...

    lua_getglobal(L, "string"); /// fmt, args..., [string]
    lua_getfield(L, 1, "format"); /// fmt, args..., [string], format()
    lua_rotate(L, 1, 2); /// [string], format(), fmt, args...
    lua_call(L, num_args, 1); /// [string], formatted_string

    TraceLog(arg1, "%s", luaL_checkstring(L,-1));
    return 0;
}

// Takes a screenshot and saves it in the same folder as executable
int lua_TakeScreenshot(lua_State* L)
{
    const char *arg1 = LuaGetArgument_string(L, 1);
    TakeScreenshot(arg1);
    return 0;
}

// Check file extension
int lua_IsFileExtension(lua_State* L)
{
    const char *arg1 = LuaGetArgument_string(L, 1);
    const char *arg2 = LuaGetArgument_string(L, 2);
    bool result = IsFileExtension(arg1, arg2);
    LuaPush_bool(L, result);
    return 1;
}

// Check if a file has been dropped into window
int lua_IsFileDropped(lua_State* L)
{
    bool result = IsFileDropped();
    LuaPush_bool(L, result);
    return 1;
}

// Get dropped files names
int lua_GetDroppedFiles(lua_State* L)
{
    int count = 0;
    char ** result = GetDroppedFiles(&count);
    lua_createtable(L, count, 0);
    for (int i = 0; i < count; i++)
    {
        LuaPush_string(L, result[i]);
        lua_rawseti(L, -2, i + 1);
    }
    return 1;
}

// Clear dropped files paths buffer
int lua_ClearDroppedFiles(lua_State* L)
{
    ClearDroppedFiles();
    return 0;
}

// Save integer value to storage file (to defined position)
int lua_StorageSaveValue(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    StorageSaveValue(arg1, arg2);
    return 0;
}

// Load integer value from storage file (from defined position)
int lua_StorageLoadValue(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    int result = StorageLoadValue(arg1);
    LuaPush_int(L, result);
    return 1;
}

//------------------------------------------------------------------------------------
// raylib [core] module functions - Input Handling
//------------------------------------------------------------------------------------

// Detect if a key has been pressed once
int lua_IsKeyPressed(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    bool result = IsKeyPressed(arg1);
    LuaPush_bool(L, result);
    return 1;
}

// Detect if a key is being pressed
int lua_IsKeyDown(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    bool result = IsKeyDown(arg1);
    LuaPush_bool(L, result);
    return 1;
}

// Detect if a key has been released once
int lua_IsKeyReleased(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    bool result = IsKeyReleased(arg1);
    LuaPush_bool(L, result);
    return 1;
}

// Detect if a key is NOT being pressed
int lua_IsKeyUp(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    bool result = IsKeyUp(arg1);
    LuaPush_bool(L, result);
    return 1;
}

// Get latest key pressed
int lua_GetKeyPressed(lua_State* L)
{
    int result = GetKeyPressed();
    LuaPush_int(L, result);
    return 1;
}

// Set a custom key to exit program (default is ESC)
int lua_SetExitKey(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    SetExitKey(arg1);
    return 0;
}

// Detect if a gamepad is available
int lua_IsGamepadAvailable(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    bool result = IsGamepadAvailable(arg1);
    LuaPush_bool(L, result);
    return 1;
}

// Check gamepad name (if available)
int lua_IsGamepadName(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    const char *arg2 = LuaGetArgument_string(L, 2);
    bool result = IsGamepadName(arg1, arg2);
    LuaPush_bool(L, result);
    return 1;
}

// Return gamepad internal name id
int lua_GetGamepadName(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    const char *result = GetGamepadName(arg1);
    LuaPush_string(L, result);
    return 1;
}

// Detect if a gamepad button has been pressed once
int lua_IsGamepadButtonPressed(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    bool result = IsGamepadButtonPressed(arg1, arg2);
    LuaPush_bool(L, result);
    return 1;
}

// Detect if a gamepad button is being pressed
int lua_IsGamepadButtonDown(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    bool result = IsGamepadButtonDown(arg1, arg2);
    LuaPush_bool(L, result);
    return 1;
}

// Detect if a gamepad button has been released once
int lua_IsGamepadButtonReleased(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    bool result = IsGamepadButtonReleased(arg1, arg2);
    LuaPush_bool(L, result);
    return 1;
}

// Detect if a gamepad button is NOT being pressed
int lua_IsGamepadButtonUp(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    bool result = IsGamepadButtonUp(arg1, arg2);
    LuaPush_bool(L, result);
    return 1;
}

// Get the last gamepad button pressed
int lua_GetGamepadButtonPressed(lua_State* L)
{
    int result = GetGamepadButtonPressed();
    LuaPush_int(L, result);
    return 1;
}

// Return gamepad axis count for a gamepad
int lua_GetGamepadAxisCount(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    int result = GetGamepadAxisCount(arg1);
    LuaPush_int(L, result);
    return 1;
}

// Return axis movement value for a gamepad axis
int lua_GetGamepadAxisMovement(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    float result = GetGamepadAxisMovement(arg1, arg2);
    LuaPush_float(L, result);
    return 1;
}

// Detect if a mouse button has been pressed once
int lua_IsMouseButtonPressed(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    bool result = IsMouseButtonPressed(arg1);
    LuaPush_bool(L, result);
    return 1;
}

// Detect if a mouse button is being pressed
int lua_IsMouseButtonDown(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    bool result = IsMouseButtonDown(arg1);
    LuaPush_bool(L, result);
    return 1;
}

// Detect if a mouse button has been released once
int lua_IsMouseButtonReleased(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    bool result = IsMouseButtonReleased(arg1);
    LuaPush_bool(L, result);
    return 1;
}

// Detect if a mouse button is NOT being pressed
int lua_IsMouseButtonUp(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    bool result = IsMouseButtonUp(arg1);
    LuaPush_bool(L, result);
    return 1;
}

// Returns mouse position X
int lua_GetMouseX(lua_State* L)
{
    int result = GetMouseX();
    LuaPush_int(L, result);
    return 1;
}

// Returns mouse position Y
int lua_GetMouseY(lua_State* L)
{
    int result = GetMouseY();
    LuaPush_int(L, result);
    return 1;
}

// Returns mouse position XY
int lua_GetMousePosition(lua_State* L)
{
    Vector2 result = GetMousePosition();
    LuaPush_Vector2(L, result);
    return 1;
}

// Set mouse position XY
int lua_SetMousePosition(lua_State* L)
{
    Vector2 arg1 = LuaGetArgument_Vector2(L, 1);
    SetMousePosition(arg1);
    return 0;
}

// Returns mouse wheel movement Y
int lua_GetMouseWheelMove(lua_State* L)
{
    int result = GetMouseWheelMove();
    LuaPush_int(L, result);
    return 1;
}

// Returns touch position X for touch point 0 (relative to screen size)
int lua_GetTouchX(lua_State* L)
{
    int result = GetTouchX();
    LuaPush_int(L, result);
    return 1;
}

// Returns touch position Y for touch point 0 (relative to screen size)
int lua_GetTouchY(lua_State* L)
{
    int result = GetTouchY();
    LuaPush_int(L, result);
    return 1;
}

// Returns touch position XY for a touch point index (relative to screen size)
int lua_GetTouchPosition(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    Vector2 result = GetTouchPosition(arg1);
    LuaPush_Vector2(L, result);
    return 1;
}

//------------------------------------------------------------------------------------
// raylib [gestures] module functions - Gestures and Touch Handling
//------------------------------------------------------------------------------------

// Enable a set of gestures using flags
int lua_SetGesturesEnabled(lua_State* L)
{
    unsigned arg1 = LuaGetArgument_unsigned(L, 1);
    SetGesturesEnabled(arg1);
    return 0;
}

// Check if a gesture have been detected
int lua_IsGestureDetected(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    bool result = IsGestureDetected(arg1);
    LuaPush_bool(L, result);
    return 1;
}

// Get latest detected gesture
int lua_GetTouchPointsCount(lua_State* L)
{
    int result = GetTouchPointsCount();
    LuaPush_int(L, result);
    return 1;
}

// Get touch points count
int lua_GetGestureDetected(lua_State* L)
{
    int result = GetGestureDetected();
    LuaPush_int(L, result);
    return 1;
}

// Get gesture hold time in milliseconds
int lua_GetGestureHoldDuration(lua_State* L)
{
    int result = GetGestureHoldDuration();
    LuaPush_int(L, result);
    return 1;
}

// Get gesture drag vector
int lua_GetGestureDragVector(lua_State* L)
{
    Vector2 result = GetGestureDragVector();
    LuaPush_Vector2(L, result);
    return 1;
}

// Get gesture drag angle
int lua_GetGestureDragAngle(lua_State* L)
{
    float result = GetGestureDragAngle();
    LuaPush_float(L, result);
    return 1;
}

// Get gesture pinch delta
int lua_GetGesturePinchVector(lua_State* L)
{
    Vector2 result = GetGesturePinchVector();
    LuaPush_Vector2(L, result);
    return 1;
}

// Get gesture pinch angle
int lua_GetGesturePinchAngle(lua_State* L)
{
    float result = GetGesturePinchAngle();
    LuaPush_float(L, result);
    return 1;
}

//------------------------------------------------------------------------------------
// raylib [camera] module functions - Camera System
//------------------------------------------------------------------------------------

// Set camera mode (multiple camera modes available)
int lua_SetCameraMode(lua_State* L)
{
    Camera arg1 = LuaGetArgument_Camera(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    SetCameraMode(arg1, arg2);
    return 0;
}

// Update camera position for selected mode
int lua_UpdateCamera(lua_State* L)
{
    Camera arg1 = LuaGetArgument_Camera(L, 1);
    UpdateCamera(&arg1);
    LuaPush_Camera(L, arg1);
    return 1;
}

// Set camera pan key to combine with mouse movement (free camera)
int lua_SetCameraPanControl(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    SetCameraPanControl(arg1);
    return 0;
}

// Set camera alt key to combine with mouse movement (free camera)
int lua_SetCameraAltControl(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    SetCameraAltControl(arg1);
    return 0;
}

// Set camera smooth zoom key to combine with mouse (free camera)
int lua_SetCameraSmoothZoomControl(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    SetCameraSmoothZoomControl(arg1);
    return 0;
}

// Set camera move controls (1st person and 3rd person cameras)
int lua_SetCameraMoveControls(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    int arg3 = LuaGetArgument_int(L, 3);
    int arg4 = LuaGetArgument_int(L, 4);
    int arg5 = LuaGetArgument_int(L, 5);
    int arg6 = LuaGetArgument_int(L, 6);
    SetCameraMoveControls(arg1, arg2, arg3, arg4, arg5, arg6);
    return 0;
}

//------------------------------------------------------------------------------------
// raylib [shapes] module functions - Basic Shapes Drawing
//------------------------------------------------------------------------------------

// Draw a pixel
int lua_DrawPixel(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    Color arg3 = LuaGetArgument_Color(L, 3);
    DrawPixel(arg1, arg2, arg3);
    return 0;
}

// Draw a pixel (Vector version)
int lua_DrawPixelV(lua_State* L)
{
    Vector2 arg1 = LuaGetArgument_Vector2(L, 1);
    Color arg2 = LuaGetArgument_Color(L, 2);
    DrawPixelV(arg1, arg2);
    return 0;
}

// Draw a line
int lua_DrawLine(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    int arg3 = LuaGetArgument_int(L, 3);
    int arg4 = LuaGetArgument_int(L, 4);
    Color arg5 = LuaGetArgument_Color(L, 5);
    DrawLine(arg1, arg2, arg3, arg4, arg5);
    return 0;
}

// Draw a line (Vector version)
int lua_DrawLineV(lua_State* L)
{
    Vector2 arg1 = LuaGetArgument_Vector2(L, 1);
    Vector2 arg2 = LuaGetArgument_Vector2(L, 2);
    Color arg3 = LuaGetArgument_Color(L, 3);
    DrawLineV(arg1, arg2, arg3);
    return 0;
}

// Draw a line defining thickness
int lua_DrawLineEx(lua_State* L)
{
    Vector2 arg1 = LuaGetArgument_Vector2(L, 1);
    Vector2 arg2 = LuaGetArgument_Vector2(L, 2);
    float arg3 = LuaGetArgument_float(L, 3);
    Color arg4 = LuaGetArgument_Color(L, 4);
    DrawLineEx(arg1, arg2, arg3, arg4);
    return 0;
}

// Draw a line using cubic-bezier curves in-out                       
int lua_DrawLineBezier(lua_State* L)
{
    Vector2 arg1 = LuaGetArgument_Vector2(L, 1);
    Vector2 arg2 = LuaGetArgument_Vector2(L, 2);
    float arg3 = LuaGetArgument_float(L, 3);
    Color arg4 = LuaGetArgument_Color(L, 4);
    DrawLineBezier(arg1, arg2, arg3, arg4);
    return 0;
}              

// Draw a color-filled circle
int lua_DrawCircle(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    float arg3 = LuaGetArgument_float(L, 3);
    Color arg4 = LuaGetArgument_Color(L, 4);
    DrawCircle(arg1, arg2, arg3, arg4);
    return 0;
}

// Draw a gradient-filled circle
int lua_DrawCircleGradient(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    float arg3 = LuaGetArgument_float(L, 3);
    Color arg4 = LuaGetArgument_Color(L, 4);
    Color arg5 = LuaGetArgument_Color(L, 5);
    DrawCircleGradient(arg1, arg2, arg3, arg4, arg5);
    return 0;
}

// Draw a color-filled circle (Vector version)
int lua_DrawCircleV(lua_State* L)
{
    Vector2 arg1 = LuaGetArgument_Vector2(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    Color arg3 = LuaGetArgument_Color(L, 3);
    DrawCircleV(arg1, arg2, arg3);
    return 0;
}

// Draw circle outline
int lua_DrawCircleLines(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    float arg3 = LuaGetArgument_float(L, 3);
    Color arg4 = LuaGetArgument_Color(L, 4);
    DrawCircleLines(arg1, arg2, arg3, arg4);
    return 0;
}

// Draw a color-filled rectangle
int lua_DrawRectangle(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    int arg3 = LuaGetArgument_int(L, 3);
    int arg4 = LuaGetArgument_int(L, 4);
    Color arg5 = LuaGetArgument_Color(L, 5);
    DrawRectangle(arg1, arg2, arg3, arg4, arg5);
    return 0;
}

// Draw a color-filled rectangle
int lua_DrawRectangleRec(lua_State* L)
{
    Rectangle arg1 = LuaGetArgument_Rectangle(L, 1);
    Color arg2 = LuaGetArgument_Color(L, 2);
    DrawRectangleRec(arg1, arg2);
    return 0;
}

// Draw a color-filled rectangle with pro parameters
int lua_DrawRectanglePro(lua_State* L)
{
    Rectangle arg1 = LuaGetArgument_Rectangle(L, 1);
    Vector2 arg2 = LuaGetArgument_Vector2(L, 2);
    float arg3 = LuaGetArgument_float(L, 3);
    Color arg4 = LuaGetArgument_Color(L, 4);
    DrawRectanglePro(arg1, arg2, arg3, arg4);
    return 0;
}

// Draw a gradient-filled rectangle
int lua_DrawRectangleGradient(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    int arg3 = LuaGetArgument_int(L, 3);
    int arg4 = LuaGetArgument_int(L, 4);
    Color arg5 = LuaGetArgument_Color(L, 5);
    Color arg6 = LuaGetArgument_Color(L, 6);
    DrawRectangleGradient(arg1, arg2, arg3, arg4, arg5, arg6);
    return 0;
}

// Draw a color-filled rectangle (Vector version)
int lua_DrawRectangleV(lua_State* L)
{
    Vector2 arg1 = LuaGetArgument_Vector2(L, 1);
    Vector2 arg2 = LuaGetArgument_Vector2(L, 2);
    Color arg3 = LuaGetArgument_Color(L, 3);
    DrawRectangleV(arg1, arg2, arg3);
    return 0;
}

// Draw rectangle outline
int lua_DrawRectangleLines(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    int arg3 = LuaGetArgument_int(L, 3);
    int arg4 = LuaGetArgument_int(L, 4);
    Color arg5 = LuaGetArgument_Color(L, 5);
    DrawRectangleLines(arg1, arg2, arg3, arg4, arg5);
    return 0;
}

// Draw a color-filled triangle
int lua_DrawTriangle(lua_State* L)
{
    Vector2 arg1 = LuaGetArgument_Vector2(L, 1);
    Vector2 arg2 = LuaGetArgument_Vector2(L, 2);
    Vector2 arg3 = LuaGetArgument_Vector2(L, 3);
    Color arg4 = LuaGetArgument_Color(L, 4);
    DrawTriangle(arg1, arg2, arg3, arg4);
    return 0;
}

// Draw triangle outline
int lua_DrawTriangleLines(lua_State* L)
{
    Vector2 arg1 = LuaGetArgument_Vector2(L, 1);
    Vector2 arg2 = LuaGetArgument_Vector2(L, 2);
    Vector2 arg3 = LuaGetArgument_Vector2(L, 3);
    Color arg4 = LuaGetArgument_Color(L, 4);
    DrawTriangleLines(arg1, arg2, arg3, arg4);
    return 0;
}

// Draw a regular polygon (Vector version)
int lua_DrawPoly(lua_State* L)
{
    Vector2 arg1 = LuaGetArgument_Vector2(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    float arg3 = LuaGetArgument_float(L, 3);
    float arg4 = LuaGetArgument_float(L, 4);
    Color arg5 = LuaGetArgument_Color(L, 5);
    DrawPoly(arg1, arg2, arg3, arg4, arg5);
    return 0;
}

// TODO: This thing should be here?
#define GET_TABLE(type, name, index) \
    type* name = 0; \
    size_t name##_size = 0; \
    { \
        size_t sz = 0; \
        luaL_checktype(L, index, LUA_TTABLE); \
        lua_pushnil(L); \
        while (lua_next(L, index)) { \
            LuaGetArgument_##type(L, -1); \
            sz++; \
            lua_pop(L, 1); \
        } \
        name = calloc(sz, sizeof(type)); \
        sz = 0; \
        lua_pushnil(L); \
        while (lua_next(L, index)) { \
            name[sz] = LuaGetArgument_##type(L, -1); \
            sz++; \
            lua_pop(L, 1); \
        } \
        lua_pop(L, 1); \
        name##_size = sz; \
    }

// Draw a closed polygon defined by points
int lua_DrawPolyEx(lua_State* L)
{
    GET_TABLE(Vector2, arg1, 1);
    Color arg2 = LuaGetArgument_Color(L, 2);
    DrawPolyEx(arg1, arg1_size, arg2);
    free(arg1);
    return 0;
}

// Draw polygon lines
int lua_DrawPolyExLines(lua_State* L)
{
    GET_TABLE(Vector2, arg1, 1);
    Color arg2 = LuaGetArgument_Color(L, 2);
    DrawPolyExLines(arg1, arg1_size, arg2);
    free(arg1);
    return 0;
}

// Check collision between two rectangles
int lua_CheckCollisionRecs(lua_State* L)
{
    Rectangle arg1 = LuaGetArgument_Rectangle(L, 1);
    Rectangle arg2 = LuaGetArgument_Rectangle(L, 2);
    bool result = CheckCollisionRecs(arg1, arg2);
    LuaPush_bool(L, result);
    return 1;
}

// Check collision between two circles
int lua_CheckCollisionCircles(lua_State* L)
{
    Vector2 arg1 = LuaGetArgument_Vector2(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    Vector2 arg3 = LuaGetArgument_Vector2(L, 3);
    float arg4 = LuaGetArgument_float(L, 4);
    bool result = CheckCollisionCircles(arg1, arg2, arg3, arg4);
    LuaPush_bool(L, result);
    return 1;
}

// Check collision between circle and rectangle
int lua_CheckCollisionCircleRec(lua_State* L)
{
    Vector2 arg1 = LuaGetArgument_Vector2(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    Rectangle arg3 = LuaGetArgument_Rectangle(L, 3);
    bool result = CheckCollisionCircleRec(arg1, arg2, arg3);
    LuaPush_bool(L, result);
    return 1;
}

// Get collision rectangle for two rectangles collision
int lua_GetCollisionRec(lua_State* L)
{
    Rectangle arg1 = LuaGetArgument_Rectangle(L, 1);
    Rectangle arg2 = LuaGetArgument_Rectangle(L, 2);
    Rectangle result = GetCollisionRec(arg1, arg2);
    LuaPush_Rectangle(L, result);
    return 1;
}

// Check if point is inside rectangle
int lua_CheckCollisionPointRec(lua_State* L)
{
    Vector2 arg1 = LuaGetArgument_Vector2(L, 1);
    Rectangle arg2 = LuaGetArgument_Rectangle(L, 2);
    bool result = CheckCollisionPointRec(arg1, arg2);
    LuaPush_bool(L, result);
    return 1;
}

// Check if point is inside circle
int lua_CheckCollisionPointCircle(lua_State* L)
{
    Vector2 arg1 = LuaGetArgument_Vector2(L, 1);
    Vector2 arg2 = LuaGetArgument_Vector2(L, 2);
    float arg3 = LuaGetArgument_float(L, 3);
    bool result = CheckCollisionPointCircle(arg1, arg2, arg3);
    LuaPush_bool(L, result);
    return 1;
}

// Check if point is inside a triangle
int lua_CheckCollisionPointTriangle(lua_State* L)
{
    Vector2 arg1 = LuaGetArgument_Vector2(L, 1);
    Vector2 arg2 = LuaGetArgument_Vector2(L, 2);
    Vector2 arg3 = LuaGetArgument_Vector2(L, 3);
    Vector2 arg4 = LuaGetArgument_Vector2(L, 4);
    bool result = CheckCollisionPointTriangle(arg1, arg2, arg3, arg4);
    LuaPush_bool(L, result);
    return 1;
}

//------------------------------------------------------------------------------------
// raylib [textures] module functions - Texture Loading and Drawing
//------------------------------------------------------------------------------------

// Load image from file into CPU memory (RAM)
int lua_LoadImage(lua_State* L)
{
    const char *arg1 = LuaGetArgument_string(L, 1);
    Image result = LoadImage(arg1);
    LuaPush_Image(L, result);
    return 1;
}

// Load image from Color array data (RGBA - 32bit)
int lua_LoadImageEx(lua_State* L)
{
    // TODO: arg1 parameter is a Color array...
    
    GET_TABLE(Color, arg1, 1);              // Color *pixels
    int arg2 = LuaGetArgument_int(L, 2);
    int arg3 = LuaGetArgument_int(L, 3);
    Image result = LoadImageEx(arg1, arg2, arg3); // ISSUE: #3 number expected, got no value
    LuaPush_Image(L, result);
    free(arg1);
    return 1;
}

// Load image from raw data with pro parameters
int lua_LoadImagePro(lua_State* L)
{
    // TODO: arg1 parameter is a void pointer...
    
    void *arg1 = LuaGetArgument_ptr(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    int arg3 = LuaGetArgument_int(L, 3);
    int arg4 = LuaGetArgument_int(L, 4);
    Image result = LoadImagePro(arg1, arg2, arg3, arg4);
    LuaPush_Image(L, result);
    free(arg1);
    return 1;
}

// Load image from RAW file data
int lua_LoadImageRaw(lua_State* L)
{
    const char *arg1 = LuaGetArgument_string(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    int arg3 = LuaGetArgument_int(L, 3);
    int arg4 = LuaGetArgument_int(L, 4);
    int arg5 = LuaGetArgument_int(L, 5);
    Image result = LoadImageRaw(arg1, arg2, arg3, arg4, arg5);
    LuaPush_Image(L, result);
    return 1;
}

// Load texture from file into GPU memory (VRAM)
int lua_LoadTexture(lua_State* L)
{
    const char *arg1 = LuaGetArgument_string(L, 1);
    Texture2D result = LoadTexture(arg1);
    LuaPush_Texture2D(L, result);
    return 1;
}

// Load texture from image data
int lua_LoadTextureFromImage(lua_State* L)
{
    Image arg1 = LuaGetArgument_Image(L, 1);
    Texture2D result = LoadTextureFromImage(arg1);
    LuaPush_Texture2D(L, result);
    return 1;
}

// Load texture for rendering (framebuffer)
int lua_LoadRenderTexture(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    RenderTexture2D result = LoadRenderTexture(arg1, arg2);
    LuaPush_RenderTexture2D(L, result);
    return 1;
}

// Unload image from CPU memory (RAM)
int lua_UnloadImage(lua_State* L)
{
    Image arg1 = LuaGetArgument_Image(L, 1);
    UnloadImage(arg1);
    return 0;
}

// Unload texture from GPU memory (VRAM)
int lua_UnloadTexture(lua_State* L)
{
    Texture2D arg1 = LuaGetArgument_Texture2D(L, 1);
    UnloadTexture(arg1);
    return 0;
}

// Unload render texture from GPU memory (VRAM)
int lua_UnloadRenderTexture(lua_State* L)
{
    RenderTexture2D arg1 = LuaGetArgument_RenderTexture2D(L, 1);
    UnloadRenderTexture(arg1);
    return 0;
}

// Get pixel data from image as a Color struct array
int lua_GetImageData(lua_State* L)
{
    // TODO: return value is a Color array

    Image arg1 = LuaGetArgument_Image(L, 1);
    Color *result = GetImageData(arg1);
    lua_createtable(L, arg1.width*arg1.height, 0);
    for (int i = 0; i < arg1.width*arg1.height; i++)
    {
        LuaPush_Color(L, result[i]);
        lua_rawseti(L, -2, i + 1);
    }
    free(result);
    return 1;
}

// Get pixel data from GPU texture and return an Image
int lua_GetTextureData(lua_State* L)
{
    Texture2D arg1 = LuaGetArgument_Texture2D(L, 1);
    Image result = GetTextureData(arg1);
    LuaPush_Image(L, result);
    return 1;
}

// Update GPU texture with new data
int lua_UpdateTexture(lua_State* L)
{
    // TODO: arg2 parameters is a void pointer...
    
    Texture2D arg1 = LuaGetArgument_Texture2D(L, 1);
    void *arg2 = LuaGetArgument_ptr(L, 2);
    UpdateTexture(arg1, arg2);      // ISSUE: #2 string expected, got table -> GetImageData() returns a table!
    return 0;
}

// Convert image to POT (power-of-two)
int lua_ImageToPOT(lua_State* L)
{
    Image arg1 = LuaGetArgument_Image(L, 1);
    Color arg2 = LuaGetArgument_Color(L, 2);
    ImageToPOT(&arg1, arg2);
    LuaPush_Image(L, arg1);
    return 1;
}

// Convert image data to desired format
int lua_ImageFormat(lua_State* L)
{
    Image arg1 = LuaGetArgument_Image(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    ImageFormat(&arg1, arg2);
    LuaPush_Image(L, arg1);
    return 1;
}

// Apply alpha mask to image
int lua_ImageAlphaMask(lua_State* L)
{
    Image arg1 = LuaGetArgument_Image(L, 1);
    Image arg2 = LuaGetArgument_Image(L, 2);
    ImageAlphaMask(&arg1, arg2);
    LuaPush_Image(L, arg1);
    return 1;
}

// Dither image data to 16bpp or lower (Floyd-Steinberg dithering)
int lua_ImageDither(lua_State* L)
{
    Image arg1 = LuaGetArgument_Image(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    int arg3 = LuaGetArgument_int(L, 3);
    int arg4 = LuaGetArgument_int(L, 4);
    int arg5 = LuaGetArgument_int(L, 5);
    ImageDither(&arg1, arg2, arg3, arg4, arg5);
    LuaPush_Image(L, arg1);
    return 1;
}

// Create an image duplicate (useful for transformations)
int lua_ImageCopy(lua_State* L)
{
    Image arg1 = LuaGetArgument_Image(L, 1);
    Image result = ImageCopy(arg1);
    LuaPush_Image(L, result);
    return 1;
}

// Crop an image to a defined rectangle
int lua_ImageCrop(lua_State* L)
{
    Image arg1 = LuaGetArgument_Image(L, 1);
    Rectangle arg2 = LuaGetArgument_Rectangle(L, 2);
    ImageCrop(&arg1, arg2);
    LuaPush_Image(L, arg1);
    return 1;
}

// Resize and image (bilinear filtering)
int lua_ImageResize(lua_State* L)
{
    Image arg1 = LuaGetArgument_Image(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    int arg3 = LuaGetArgument_int(L, 3);
    ImageResize(&arg1, arg2, arg3);
    LuaPush_Image(L, arg1);
    return 1;
}

// Resize and image (Nearest-Neighbor scaling algorithm)
int lua_ImageResizeNN(lua_State* L)
{
    Image arg1 = LuaGetArgument_Image(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    int arg3 = LuaGetArgument_int(L, 3);
    ImageResizeNN(&arg1, arg2, arg3);
    LuaPush_Image(L, arg1);
    return 1;
}

// Create an image from text (default font)
int lua_ImageText(lua_State* L)
{
    const char *arg1 = LuaGetArgument_string(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    Color arg3 = LuaGetArgument_Color(L, 3);
    Image result = ImageText(arg1, arg2, arg3);
    LuaPush_Image(L, result);
    return 1;
}

// Create an image from text (custom sprite font)
int lua_ImageTextEx(lua_State* L)
{
    SpriteFont arg1 = LuaGetArgument_SpriteFont(L, 1);
    const char *arg2 = LuaGetArgument_string(L, 2);
    int arg3 = LuaGetArgument_int(L, 3);
    int arg4 = LuaGetArgument_int(L, 4);
    Color arg5 = LuaGetArgument_Color(L, 5);
    Image result = ImageTextEx(arg1, arg2, arg3, arg4, arg5);
    LuaPush_Image(L, result);
    return 1;
}

// Draw a source image within a destination image
int lua_ImageDraw(lua_State* L)
{
    Image arg1 = LuaGetArgument_Image(L, 1);
    Image arg2 = LuaGetArgument_Image(L, 2);
    Rectangle arg3 = LuaGetArgument_Rectangle(L, 3);
    Rectangle arg4 = LuaGetArgument_Rectangle(L, 4);
    ImageDraw(&arg1, arg2, arg3, arg4);
    LuaPush_Image(L, arg1);
    return 1;
}

// Draw text (default font) within an image (destination)
int lua_ImageDrawText(lua_State* L)
{
    Image arg1 = LuaGetArgument_Image(L, 1);
    Vector2 arg2 = LuaGetArgument_Vector2(L, 2);
    const char *arg3 = LuaGetArgument_string(L, 3);
    int arg4 = LuaGetArgument_int(L, 4);
    Color arg5 = LuaGetArgument_Color(L, 5);
    ImageDrawText(&arg1, arg2, arg3, arg4, arg5);
    LuaPush_Image(L, arg1);
    return 1;
}

// Draw text (custom sprite font) within an image (destination)
int lua_ImageDrawTextEx(lua_State* L)
{
    Image arg1 = LuaGetArgument_Image(L, 1);
    Vector2 arg2 = LuaGetArgument_Vector2(L, 2);
    SpriteFont arg3 = LuaGetArgument_SpriteFont(L, 3);
    const char *arg4 = LuaGetArgument_string(L, 4);
    float arg5 = LuaGetArgument_float(L, 5);
    int arg6 = LuaGetArgument_int(L, 6);
    Color arg7 = LuaGetArgument_Color(L, 7);
    ImageDrawTextEx(&arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    LuaPush_Image(L, arg1);
    return 1;
}

// Flip image vertically
int lua_ImageFlipVertical(lua_State* L)
{
    Image arg1 = LuaGetArgument_Image(L, 1);
    ImageFlipVertical(&arg1);
    LuaPush_Image(L, arg1);
    return 1;
}

// Flip image horizontally
int lua_ImageFlipHorizontal(lua_State* L)
{
    Image arg1 = LuaGetArgument_Image(L, 1);
    ImageFlipHorizontal(&arg1);
    LuaPush_Image(L, arg1);
    return 1;
}

// Modify image color: tint
int lua_ImageColorTint(lua_State* L)
{
    Image arg1 = LuaGetArgument_Image(L, 1);
    Color arg2 = LuaGetArgument_Color(L, 2);
    ImageColorTint(&arg1, arg2);
    LuaPush_Image(L, arg1);
    return 1;
}

// Modify image color: invert
int lua_ImageColorInvert(lua_State* L)
{
    Image arg1 = LuaGetArgument_Image(L, 1);
    ImageColorInvert(&arg1);
    LuaPush_Image(L, arg1);
    return 1;
}

// Modify image color: grayscale
int lua_ImageColorGrayscale(lua_State* L)
{
    Image arg1 = LuaGetArgument_Image(L, 1);
    ImageColorGrayscale(&arg1);
    LuaPush_Image(L, arg1);
    return 1;
}

// Modify image color: contrast (-100 to 100)
int lua_ImageColorContrast(lua_State* L)
{
    Image arg1 = LuaGetArgument_Image(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    ImageColorContrast(&arg1, arg2);
    LuaPush_Image(L, arg1);
    return 1;
}

// Modify image color: brightness (-255 to 255)
int lua_ImageColorBrightness(lua_State* L)
{
    Image arg1 = LuaGetArgument_Image(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    ImageColorBrightness(&arg1, arg2);
    LuaPush_Image(L, arg1);
    return 1;
}

// Generate GPU mipmaps for a texture
int lua_GenTextureMipmaps(lua_State* L)
{
    Texture2D arg1 = LuaGetArgument_Texture2D(L, 1);
    GenTextureMipmaps(&arg1);
    LuaPush_Texture2D(L, arg1);
    return 1;
}

// Set texture scaling filter mode
int lua_SetTextureFilter(lua_State* L)
{
    Texture2D arg1 = LuaGetArgument_Texture2D(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    SetTextureFilter(arg1, arg2);
    return 0;
}

// Set texture wrapping mode
int lua_SetTextureWrap(lua_State* L)
{
    Texture2D arg1 = LuaGetArgument_Texture2D(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    SetTextureWrap(arg1, arg2);
    return 0;
}

// Draw a Texture2D
int lua_DrawTexture(lua_State* L)
{
    Texture2D arg1 = LuaGetArgument_Texture2D(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    int arg3 = LuaGetArgument_int(L, 3);
    Color arg4 = LuaGetArgument_Color(L, 4);
    DrawTexture(arg1, arg2, arg3, arg4);
    return 0;
}

// Draw a Texture2D with position defined as Vector2
int lua_DrawTextureV(lua_State* L)
{
    Texture2D arg1 = LuaGetArgument_Texture2D(L, 1);
    Vector2 arg2 = LuaGetArgument_Vector2(L, 2);
    Color arg3 = LuaGetArgument_Color(L, 3);
    DrawTextureV(arg1, arg2, arg3);
    return 0;
}

// Draw a Texture2D with extended parameters
int lua_DrawTextureEx(lua_State* L)
{
    Texture2D arg1 = LuaGetArgument_Texture2D(L, 1);
    Vector2 arg2 = LuaGetArgument_Vector2(L, 2);
    float arg3 = LuaGetArgument_float(L, 3);
    float arg4 = LuaGetArgument_float(L, 4);
    Color arg5 = LuaGetArgument_Color(L, 5);
    DrawTextureEx(arg1, arg2, arg3, arg4, arg5);
    return 0;
}

// Draw a part of a texture defined by a rectangle
int lua_DrawTextureRec(lua_State* L)
{
    Texture2D arg1 = LuaGetArgument_Texture2D(L, 1);
    Rectangle arg2 = LuaGetArgument_Rectangle(L, 2);
    Vector2 arg3 = LuaGetArgument_Vector2(L, 3);
    Color arg4 = LuaGetArgument_Color(L, 4);
    DrawTextureRec(arg1, arg2, arg3, arg4);
    return 0;
}

// Draw a part of a texture defined by a rectangle with 'pro' parameters
int lua_DrawTexturePro(lua_State* L)
{
    Texture2D arg1 = LuaGetArgument_Texture2D(L, 1);
    Rectangle arg2 = LuaGetArgument_Rectangle(L, 2);
    Rectangle arg3 = LuaGetArgument_Rectangle(L, 3);
    Vector2 arg4 = LuaGetArgument_Vector2(L, 4);
    float arg5 = LuaGetArgument_float(L, 5);
    Color arg6 = LuaGetArgument_Color(L, 6);
    DrawTexturePro(arg1, arg2, arg3, arg4, arg5, arg6);
    return 0;
}

//------------------------------------------------------------------------------------
// raylib [text] module functions - Font Loading and Text Drawing
//------------------------------------------------------------------------------------

// Get the default SpriteFont
int lua_GetDefaultFont(lua_State* L)
{
    SpriteFont result = GetDefaultFont();
    LuaPush_SpriteFont(L, result);
    return 1;
}

// Load SpriteFont from file into GPU memory (VRAM)
int lua_LoadSpriteFont(lua_State* L)
{
    const char *arg1 = LuaGetArgument_string(L, 1);
    SpriteFont result = LoadSpriteFont(arg1);
    LuaPush_SpriteFont(L, result);
    return 1;
}

// Load SpriteFont from file with extended parameters
int lua_LoadSpriteFontEx(lua_State* L)
{
    const char *arg1 = LuaGetArgument_string(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    int arg3 = LuaGetArgument_int(L, 3);
    int arg4 = LuaGetArgument_int(L, 4);
    SpriteFont result = LoadSpriteFontEx(arg1, arg2, arg3, &arg4);
    LuaPush_SpriteFont(L, result);
    return 1;
}

// Unload SpriteFont from GPU memory (VRAM)
int lua_UnloadSpriteFont(lua_State* L)
{
    SpriteFont arg1 = LuaGetArgument_SpriteFont(L, 1);
    UnloadSpriteFont(arg1);
    return 0;
}

// Draw text (using default font)
int lua_DrawText(lua_State* L)
{
    const char *arg1 = LuaGetArgument_string(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    int arg3 = LuaGetArgument_int(L, 3);
    int arg4 = LuaGetArgument_int(L, 4);
    Color arg5 = LuaGetArgument_Color(L, 5);
    DrawText(arg1, arg2, arg3, arg4, arg5);
    return 0;
}

// Draw text using SpriteFont and additional parameters
int lua_DrawTextEx(lua_State* L)
{
    SpriteFont arg1 = LuaGetArgument_SpriteFont(L, 1);
    const char *arg2 = LuaGetArgument_string(L, 2);
    Vector2 arg3 = LuaGetArgument_Vector2(L, 3);
    float arg4 = LuaGetArgument_float(L, 4);
    int arg5 = LuaGetArgument_int(L, 5);
    Color arg6 = LuaGetArgument_Color(L, 6);
    DrawTextEx(arg1, arg2, arg3, arg4, arg5, arg6);
    return 0;
}

// Measure string width for default font
int lua_MeasureText(lua_State* L)
{
    const char *arg1 = LuaGetArgument_string(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    int result = MeasureText(arg1, arg2);
    LuaPush_int(L, result);
    return 1;
}

// Measure string size for SpriteFont
int lua_MeasureTextEx(lua_State* L)
{
    SpriteFont arg1 = LuaGetArgument_SpriteFont(L, 1);
    const char *arg2 = LuaGetArgument_string(L, 2);
    int arg3 = LuaGetArgument_int(L, 3);
    int arg4 = LuaGetArgument_int(L, 4);
    Vector2 result = MeasureTextEx(arg1, arg2, arg3, arg4);
    LuaPush_Vector2(L, result);
    return 1;
}

// Shows current FPS
int lua_DrawFPS(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    DrawFPS(arg1, arg2);
    return 0;
}

// NOTE: FormatText() can be replaced by Lua function: string.format()
// NOTE: SubText() can be replaced by Lua function: string.sub()

//------------------------------------------------------------------------------------
// raylib [models] module functions - Basic 3d Shapes Drawing Functions
//------------------------------------------------------------------------------------

// Draw a line in 3D world space
int lua_DrawLine3D(lua_State* L)
{
    Vector3 arg1 = LuaGetArgument_Vector3(L, 1);
    Vector3 arg2 = LuaGetArgument_Vector3(L, 2);
    Color arg3 = LuaGetArgument_Color(L, 3);
    DrawLine3D(arg1, arg2, arg3);
    return 0;
}

// Draw a circle in 3D world space
int lua_DrawCircle3D(lua_State* L)
{
    Vector3 arg1 = LuaGetArgument_Vector3(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    Vector3 arg3 = LuaGetArgument_Vector3(L, 3);
    float arg4 = LuaGetArgument_float(L, 4);
    Color arg5 = LuaGetArgument_Color(L, 5);
    DrawCircle3D(arg1, arg2, arg3, arg4, arg5);
    return 0;
}

// Draw cube
int lua_DrawCube(lua_State* L)
{
    Vector3 arg1 = LuaGetArgument_Vector3(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    float arg3 = LuaGetArgument_float(L, 3);
    float arg4 = LuaGetArgument_float(L, 4);
    Color arg5 = LuaGetArgument_Color(L, 5);
    DrawCube(arg1, arg2, arg3, arg4, arg5);
    return 0;
}

// Draw cube (Vector version)
int lua_DrawCubeV(lua_State* L)
{
    Vector3 arg1 = LuaGetArgument_Vector3(L, 1);
    Vector3 arg2 = LuaGetArgument_Vector3(L, 2);
    Color arg3 = LuaGetArgument_Color(L, 3);
    DrawCubeV(arg1, arg2, arg3);
    return 0;
}

// Draw cube wires
int lua_DrawCubeWires(lua_State* L)
{
    Vector3 arg1 = LuaGetArgument_Vector3(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    float arg3 = LuaGetArgument_float(L, 3);
    float arg4 = LuaGetArgument_float(L, 4);
    Color arg5 = LuaGetArgument_Color(L, 5);
    DrawCubeWires(arg1, arg2, arg3, arg4, arg5);
    return 0;
}

// Draw cube textured
int lua_DrawCubeTexture(lua_State* L)
{
    Texture2D arg1 = LuaGetArgument_Texture2D(L, 1);
    Vector3 arg2 = LuaGetArgument_Vector3(L, 2);
    float arg3 = LuaGetArgument_float(L, 3);
    float arg4 = LuaGetArgument_float(L, 4);
    float arg5 = LuaGetArgument_float(L, 5);
    Color arg6 = LuaGetArgument_Color(L, 6);
    DrawCubeTexture(arg1, arg2, arg3, arg4, arg5, arg6);
    return 0;
}

// Draw sphere
int lua_DrawSphere(lua_State* L)
{
    Vector3 arg1 = LuaGetArgument_Vector3(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    Color arg3 = LuaGetArgument_Color(L, 3);
    DrawSphere(arg1, arg2, arg3);
    return 0;
}

// Draw sphere with extended parameters
int lua_DrawSphereEx(lua_State* L)
{
    Vector3 arg1 = LuaGetArgument_Vector3(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    int arg3 = LuaGetArgument_int(L, 3);
    int arg4 = LuaGetArgument_int(L, 4);
    Color arg5 = LuaGetArgument_Color(L, 5);
    DrawSphereEx(arg1, arg2, arg3, arg4, arg5);
    return 0;
}

// Draw sphere wires
int lua_DrawSphereWires(lua_State* L)
{
    Vector3 arg1 = LuaGetArgument_Vector3(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    int arg3 = LuaGetArgument_int(L, 3);
    int arg4 = LuaGetArgument_int(L, 4);
    Color arg5 = LuaGetArgument_Color(L, 5);
    DrawSphereWires(arg1, arg2, arg3, arg4, arg5);
    return 0;
}

// Draw a cylinder/cone
int lua_DrawCylinder(lua_State* L)
{
    Vector3 arg1 = LuaGetArgument_Vector3(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    float arg3 = LuaGetArgument_float(L, 3);
    float arg4 = LuaGetArgument_float(L, 4);
    int arg5 = LuaGetArgument_int(L, 5);
    Color arg6 = LuaGetArgument_Color(L, 6);
    DrawCylinder(arg1, arg2, arg3, arg4, arg5, arg6);
    return 0;
}

// Draw a cylinder/cone wires
int lua_DrawCylinderWires(lua_State* L)
{
    Vector3 arg1 = LuaGetArgument_Vector3(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    float arg3 = LuaGetArgument_float(L, 3);
    float arg4 = LuaGetArgument_float(L, 4);
    int arg5 = LuaGetArgument_int(L, 5);
    Color arg6 = LuaGetArgument_Color(L, 6);
    DrawCylinderWires(arg1, arg2, arg3, arg4, arg5, arg6);
    return 0;
}

// Draw a plane XZ
int lua_DrawPlane(lua_State* L)
{
    Vector3 arg1 = LuaGetArgument_Vector3(L, 1);
    Vector2 arg2 = LuaGetArgument_Vector2(L, 2);
    Color arg3 = LuaGetArgument_Color(L, 3);
    DrawPlane(arg1, arg2, arg3);
    return 0;
}

// Draw a ray line
int lua_DrawRay(lua_State* L)
{
    Ray arg1 = LuaGetArgument_Ray(L, 1);
    Color arg2 = LuaGetArgument_Color(L, 2);
    DrawRay(arg1, arg2);
    return 0;
}

// Draw a grid (centered at (0, 0, 0))
int lua_DrawGrid(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    DrawGrid(arg1, arg2);
    return 0;
}

// Draw simple gizmo
int lua_DrawGizmo(lua_State* L)
{
    Vector3 arg1 = LuaGetArgument_Vector3(L, 1);
    DrawGizmo(arg1);
    return 0;
}

//------------------------------------------------------------------------------------
// raylib [models] module functions
//------------------------------------------------------------------------------------

// Load mesh from file
int lua_LoadMesh(lua_State* L)
{
    const char *arg1 = LuaGetArgument_string(L, 1);
    Mesh result = LoadMesh(arg1);
    LuaPush_Mesh(L, result);
    return 1;
}

// Load mesh from vertex data
int lua_LoadMeshEx(lua_State* L)
{
    // TODO: arg2, arg3, arg4, arg5 params should be float arrays...
    /*
    int arg1 = LuaGetArgument_int(L, 1);
    float *arg2 = LuaGetArgument_ptr(L, 2);   // float *vData
    float *arg3 = LuaGetArgument_ptr(L, 3);   // float *vtData
    float *arg4 = LuaGetArgument_ptr(L, 4);   // float *vnData
    float *arg5 = LuaGetArgument_ptr(L, 5);   // float *cData
    Mesh result = LoadMeshEx(arg1, arg2, arg3, arg4, arg5);
    LuaPush_Mesh(L, result);
    return 1;
    */
    return 0;
}

// Load model from file
int lua_LoadModel(lua_State* L)
{
    const char *arg1 = LuaGetArgument_string(L, 1);
    Model result = LoadModel(arg1);
    LuaPush_Model(L, result);
    return 1;
}

// Load model from mesh data
int lua_LoadModelFromMesh(lua_State* L)
{
    Mesh arg1 = LuaGetArgument_Mesh(L, 1);
    bool arg2 = LuaGetArgument_int(L, 2);           // bool
    Model result = LoadModelFromMesh(arg1, arg2);
    LuaPush_Model(L, result);
    return 1;
}

// Load heightmap model from image data
int lua_LoadHeightmap(lua_State* L)
{
    Image arg1 = LuaGetArgument_Image(L, 1);
    Vector3 arg2 = LuaGetArgument_Vector3(L, 2);
    Model result = LoadHeightmap(arg1, arg2);
    LuaPush_Model(L, result);
    return 1;
}

// Load cubes-based map model from image data
int lua_LoadCubicmap(lua_State* L)
{
    Image arg1 = LuaGetArgument_Image(L, 1);
    Model result = LoadCubicmap(arg1);
    LuaPush_Model(L, result);
    return 1;
}

// Unload mesh from memory (RAM and/or VRAM)
int lua_UnloadMesh(lua_State* L)
{
    Mesh arg1 = LuaGetArgument_Mesh(L, 1);
    UnloadMesh(&arg1);
    LuaPush_Mesh(L, arg1);
    return 1;
}

// Unload model from memory (RAM and/or VRAM)
int lua_UnloadModel(lua_State* L)
{
    Model arg1 = LuaGetArgument_Model(L, 1);
    UnloadModel(arg1);
    return 0;
}

// Load material from file
int lua_LoadMaterial(lua_State* L)
{
    const char *arg1 = LuaGetArgument_string(L, 1);
    Material result = LoadMaterial(arg1);
    LuaPush_Material(L, result);
    return 1;
}

// Load default material (uses default models shader)
int lua_LoadDefaultMaterial(lua_State* L)
{
    Material result = LoadDefaultMaterial();
    LuaPush_Material(L, result);
    return 1;
}

// Unload material from GPU memory (VRAM)
int lua_UnloadMaterial(lua_State* L)
{
    Material arg1 = LuaGetArgument_Material(L, 1);
    UnloadMaterial(arg1);
    return 0;
}

// Draw a model (with texture if set)
int lua_DrawModel(lua_State* L)
{
    Model arg1 = LuaGetArgument_Model(L, 1);
    Vector3 arg2 = LuaGetArgument_Vector3(L, 2);
    float arg3 = LuaGetArgument_float(L, 3);
    Color arg4 = LuaGetArgument_Color(L, 4);
    DrawModel(arg1, arg2, arg3, arg4);
    return 0;
}

// Draw a model with extended parameters
int lua_DrawModelEx(lua_State* L)
{
    Model arg1 = LuaGetArgument_Model(L, 1);
    Vector3 arg2 = LuaGetArgument_Vector3(L, 2);
    Vector3 arg3 = LuaGetArgument_Vector3(L, 3);
    float arg4 = LuaGetArgument_float(L, 4);
    Vector3 arg5 = LuaGetArgument_Vector3(L, 5);
    Color arg6 = LuaGetArgument_Color(L, 6);
    DrawModelEx(arg1, arg2, arg3, arg4, arg5, arg6);
    return 0;
}

// Draw a model wires (with texture if set)
int lua_DrawModelWires(lua_State* L)
{
    Model arg1 = LuaGetArgument_Model(L, 1);
    Vector3 arg2 = LuaGetArgument_Vector3(L, 2);
    float arg3 = LuaGetArgument_float(L, 3);
    Color arg4 = LuaGetArgument_Color(L, 4);
    DrawModelWires(arg1, arg2, arg3, arg4);
    return 0;
}

// Draw a model wires (with texture if set) with extended parameters
int lua_DrawModelWiresEx(lua_State* L)
{
    Model arg1 = LuaGetArgument_Model(L, 1);
    Vector3 arg2 = LuaGetArgument_Vector3(L, 2);
    Vector3 arg3 = LuaGetArgument_Vector3(L, 3);
    float arg4 = LuaGetArgument_float(L, 4);
    Vector3 arg5 = LuaGetArgument_Vector3(L, 5);
    Color arg6 = LuaGetArgument_Color(L, 6);
    DrawModelWiresEx(arg1, arg2, arg3, arg4, arg5, arg6);
    return 0;
}

// Draw bounding box (wires)
int lua_DrawBoundingBox(lua_State* L)
{
    BoundingBox arg1 = LuaGetArgument_BoundingBox(L, 1);
    Color arg2 = LuaGetArgument_Color(L, 2);
    DrawBoundingBox(arg1, arg2);
    return 0;
}

// Draw a billboard texture
int lua_DrawBillboard(lua_State* L)
{
    Camera arg1 = LuaGetArgument_Camera(L, 1);
    Texture2D arg2 = LuaGetArgument_Texture2D(L, 2);
    Vector3 arg3 = LuaGetArgument_Vector3(L, 3);
    float arg4 = LuaGetArgument_float(L, 4);
    Color arg5 = LuaGetArgument_Color(L, 5);
    DrawBillboard(arg1, arg2, arg3, arg4, arg5);
    return 0;
}

// Draw a billboard texture defined by sourceRec
int lua_DrawBillboardRec(lua_State* L)
{
    Camera arg1 = LuaGetArgument_Camera(L, 1);
    Texture2D arg2 = LuaGetArgument_Texture2D(L, 2);
    Rectangle arg3 = LuaGetArgument_Rectangle(L, 3);
    Vector3 arg4 = LuaGetArgument_Vector3(L, 4);
    float arg5 = LuaGetArgument_float(L, 5);
    Color arg6 = LuaGetArgument_Color(L, 6);
    DrawBillboardRec(arg1, arg2, arg3, arg4, arg5, arg6);
    return 0;
}

// Calculate mesh bounding box limits
int lua_CalculateBoundingBox(lua_State* L)
{
    Mesh arg1 = LuaGetArgument_Mesh(L, 1);
    BoundingBox result = CalculateBoundingBox(arg1);
    LuaPush_BoundingBox(L, result);
    return 1;
}

// Detect collision between two spheres
int lua_CheckCollisionSpheres(lua_State* L)
{
    Vector3 arg1 = LuaGetArgument_Vector3(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    Vector3 arg3 = LuaGetArgument_Vector3(L, 3);
    float arg4 = LuaGetArgument_float(L, 4);
    bool result = CheckCollisionSpheres(arg1, arg2, arg3, arg4);
    LuaPush_bool(L, result);
    return 1;
}

// Detect collision between two bounding boxes
int lua_CheckCollisionBoxes(lua_State* L)
{
    BoundingBox arg1 = LuaGetArgument_BoundingBox(L, 1);
    BoundingBox arg2 = LuaGetArgument_BoundingBox(L, 2);
    bool result = CheckCollisionBoxes(arg1, arg2);
    LuaPush_bool(L, result);
    return 1;
}

// Detect collision between box and sphere
int lua_CheckCollisionBoxSphere(lua_State* L)
{
    BoundingBox arg1 = LuaGetArgument_BoundingBox(L, 1);
    Vector3 arg2 = LuaGetArgument_Vector3(L, 2);
    float arg3 = LuaGetArgument_float(L, 3);
    bool result = CheckCollisionBoxSphere(arg1, arg2, arg3);
    LuaPush_bool(L, result);
    return 1;
}

// Detect collision between ray and sphere
int lua_CheckCollisionRaySphere(lua_State* L)
{
    Ray arg1 = LuaGetArgument_Ray(L, 1);
    Vector3 arg2 = LuaGetArgument_Vector3(L, 2);
    float arg3 = LuaGetArgument_float(L, 3);
    bool result = CheckCollisionRaySphere(arg1, arg2, arg3);
    LuaPush_bool(L, result);
    return 1;
}

// Detect collision between ray and sphere, returns collision point
int lua_CheckCollisionRaySphereEx(lua_State* L)
{
    Ray arg1 = LuaGetArgument_Ray(L, 1);
    Vector3 arg2 = LuaGetArgument_Vector3(L, 2);
    float arg3 = LuaGetArgument_float(L, 3);
    Vector3 arg4 = LuaGetArgument_Vector3(L, 4);
    bool result = CheckCollisionRaySphereEx(arg1, arg2, arg3, &arg4);
    LuaPush_bool(L, result);
    LuaPush_Vector3(L, arg4);
    return 2;
}

// Detect collision between ray and box
int lua_CheckCollisionRayBox(lua_State* L)
{
    Ray arg1 = LuaGetArgument_Ray(L, 1);
    BoundingBox arg2 = LuaGetArgument_BoundingBox(L, 2);
    bool result = CheckCollisionRayBox(arg1, arg2);
    LuaPush_bool(L, result);
    return 1;
}

// Get collision info between ray and mesh
int lua_GetCollisionRayMesh(lua_State* L)
{
    // TODO: arg2 param should be Mesh pointer...
    
    Ray arg1 = LuaGetArgument_Ray(L, 1);
    Mesh arg2 = LuaGetArgument_Mesh(L, 2);      // Mesh *mesh
    RayHitInfo result = GetCollisionRayMesh(arg1, &arg2);
    LuaPush_RayHitInfo(L, result);
    return 1;
}

// Get collision info between ray and triangle
int lua_GetCollisionRayTriangle(lua_State* L)
{
    Ray arg1 = LuaGetArgument_Ray(L, 1);
    Vector3 arg2 = LuaGetArgument_Vector3(L, 2);
    Vector3 arg3 = LuaGetArgument_Vector3(L, 3);
    Vector3 arg4 = LuaGetArgument_Vector3(L, 4);
    RayHitInfo result = GetCollisionRayTriangle(arg1, arg2, arg3, arg4);
    LuaPush_RayHitInfo(L, result);
    return 1;
}

// Get collision info between ray and ground plane (Y-normal plane)
int lua_GetCollisionRayGround(lua_State* L)
{
    Ray arg1 = LuaGetArgument_Ray(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    RayHitInfo result = GetCollisionRayGround(arg1, arg2);
    LuaPush_RayHitInfo(L, result);
    return 1;
}

//------------------------------------------------------------------------------------
// raylib [raymath] module functions - Shaders
//------------------------------------------------------------------------------------

// Load chars array from text file
int lua_LoadText(lua_State* L)
{
    const char *arg1 = LuaGetArgument_string(L, 1);
    char *result = LoadText(arg1);
    LuaPush_string(L, result);
    return 1;
}

// Load shader from files and bind default locations
int lua_LoadShader(lua_State* L)
{
    char *arg1 = (char *)LuaGetArgument_string(L, 1);
    char *arg2 = (char *)LuaGetArgument_string(L, 2);
    Shader result = LoadShader(arg1, arg2);
    LuaPush_Shader(L, result);
    return 1;
}

// Unload shader from GPU memory (VRAM)
int lua_UnloadShader(lua_State* L)
{
    Shader arg1 = LuaGetArgument_Shader(L, 1);
    UnloadShader(arg1);
    return 0;
}

// Get default shader
int lua_GetDefaultShader(lua_State* L)
{
    Shader result = GetDefaultShader();
    LuaPush_Shader(L, result);
    return 1;
}

// Get default texture
int lua_GetDefaultTexture(lua_State* L)
{
    Texture2D result = GetDefaultTexture();
    LuaPush_Texture2D(L, result);
    return 1;
}

// Get shader uniform location
int lua_GetShaderLocation(lua_State* L)
{
    Shader arg1 = LuaGetArgument_Shader(L, 1);
    const char *arg2 = LuaGetArgument_string(L, 2);
    int result = GetShaderLocation(arg1, arg2);
    LuaPush_int(L, result);
    return 1;
}

// Set shader uniform values (float)
int lua_SetShaderValue(lua_State* L)
{
    Shader arg1 = LuaGetArgument_Shader(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    GET_TABLE(float, arg3, 3);
    SetShaderValue(arg1, arg2, arg3, arg3_size);
    free(arg3);
    return 0;
}

// Set shader uniform values (int)
int lua_SetShaderValuei(lua_State* L)
{
    Shader arg1 = LuaGetArgument_Shader(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    GET_TABLE(int, arg3, 3);
    SetShaderValuei(arg1, arg2, arg3, arg3_size);
    free(arg3);
    return 0;
}

// Set shader uniform value (matrix 4x4)
int lua_SetShaderValueMatrix(lua_State* L)
{
    Shader arg1 = LuaGetArgument_Shader(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    Matrix arg3 = LuaGetArgument_Matrix(L, 3);
    SetShaderValueMatrix(arg1, arg2, arg3);
    return 0;
}

// Set a custom projection matrix (replaces internal projection matrix)
int lua_SetMatrixProjection(lua_State* L)
{
    Matrix arg1 = LuaGetArgument_Matrix(L, 1);
    SetMatrixProjection(arg1);
    return 0;
}

// Set a custom modelview matrix (replaces internal modelview matrix)
int lua_SetMatrixModelview(lua_State* L)
{
    Matrix arg1 = LuaGetArgument_Matrix(L, 1);
    SetMatrixModelview(arg1);
    return 0;
}

// Begin custom shader drawing
int lua_BeginShaderMode(lua_State* L)
{
    Shader arg1 = LuaGetArgument_Shader(L, 1);
    BeginShaderMode(arg1);
    return 0;
}

// End custom shader drawing (use default shader)
int lua_EndShaderMode(lua_State* L)
{
    EndShaderMode();
    return 0;
}

// Begin blending mode (alpha, additive, multiplied)
int lua_BeginBlendMode(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    BeginBlendMode(arg1);
    return 0;
}

// End blending mode (reset to default: alpha blending)
int lua_EndBlendMode(lua_State* L)
{
    EndBlendMode();
    return 0;
}

//------------------------------------------------------------------------------------
// raylib [rlgl] module functions - VR experience
//------------------------------------------------------------------------------------

// Init VR simulator for selected device
int lua_InitVrSimulator(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    InitVrSimulator(arg1);
    return 0;
}

// Close VR simulator for current device
int lua_CloseVrSimulator(lua_State* L)
{
    CloseVrSimulator();
    return 0;
}

// Detect if VR device is ready
int lua_IsVrSimulatorReady(lua_State* L)
{
    bool result = IsVrSimulatorReady();
    LuaPush_bool(L, result);
    return 1;
}

// Update VR tracking (position and orientation) and camera
int lua_UpdateVrTracking(lua_State* L)
{
    Camera arg1 = LuaGetArgument_Camera(L, 1);
    UpdateVrTracking(&arg1);
    LuaPush_Camera(L, arg1);
    return 1;
}

// Enable/Disable VR experience (device or simulator)
int lua_ToggleVrMode(lua_State* L)
{
    ToggleVrMode();
    return 0;
}

// Begin VR simulator stereo rendering
int lua_BeginVrDrawing(lua_State* L)
{
    BeginVrDrawing();
    return 0;
}

// End VR simulator stereo rendering
int lua_EndVrDrawing(lua_State* L)
{
    EndVrDrawing();
    return 0;
}

//------------------------------------------------------------------------------------
// raylib [audio] module functions - Audio Loading and Playing
//------------------------------------------------------------------------------------

// Initialize audio device and context
int lua_InitAudioDevice(lua_State* L)
{
    InitAudioDevice();
    return 0;
}

// Close the audio device and context
int lua_CloseAudioDevice(lua_State* L)
{
    CloseAudioDevice();
    return 0;
}

// Check if audio device has been initialized successfully
int lua_IsAudioDeviceReady(lua_State* L)
{
    bool result = IsAudioDeviceReady();
    LuaPush_bool(L, result);
    return 1;
}

// Set master volume (listener)
int lua_SetMasterVolume(lua_State* L)
{
    float arg1 = LuaGetArgument_float(L, 1);
    SetMasterVolume(arg1);
    return 0;
}

// Load wave data from file
int lua_LoadWave(lua_State* L)
{
    const char *arg1 = LuaGetArgument_string(L, 1);
    Wave result = LoadWave((char *)arg1);
    LuaPush_Wave(L, result);
    return 1;
}

// Load wave data from raw array data
int lua_LoadWaveEx(lua_State* L)
{
    // TODO: arg1 parameter should be a float arrat...
    
    float *arg1 = 0;
    int arg2 = LuaGetArgument_int(L, 2);
    int arg3 = LuaGetArgument_int(L, 3);
    int arg4 = LuaGetArgument_int(L, 4);
    int arg5 = LuaGetArgument_int(L, 5);
    Wave result = LoadWaveEx(arg1, arg2, arg3, arg4, arg5);
    LuaPush_Wave(L, result);
    return 1;
}

// Load sound from file
int lua_LoadSound(lua_State* L)
{
    const char *arg1 = LuaGetArgument_string(L, 1);
    Sound result = LoadSound((char*)arg1);
    LuaPush_Sound(L, result);
    return 1;
}

// Load sound from wave data
int lua_LoadSoundFromWave(lua_State* L)
{
    Wave arg1 = LuaGetArgument_Wave(L, 1);
    Sound result = LoadSoundFromWave(arg1);
    LuaPush_Sound(L, result);
    return 1;
}

// Update sound buffer with new data
int lua_UpdateSound(lua_State* L)
{
    // TODO: arg2 parameter is a void pointer...
    
    Sound arg1 = LuaGetArgument_Sound(L, 1);
    void *arg2 = LuaGetArgument_ptr(L, 2);
    int arg3 = LuaGetArgument_int(L, 3);
    UpdateSound(arg1, arg2, arg3);
    return 0;
}

// Unload wave data
int lua_UnloadWave(lua_State* L)
{
    Wave arg1 = LuaGetArgument_Wave(L, 1);
    UnloadWave(arg1);
    return 0;
}

// Unload sound
int lua_UnloadSound(lua_State* L)
{
    Sound arg1 = LuaGetArgument_Sound(L, 1);
    UnloadSound(arg1);
    return 0;
}

// Play a sound
int lua_PlaySound(lua_State* L)
{
    Sound arg1 = LuaGetArgument_Sound(L, 1);
    PlaySound(arg1);
    return 0;
}

// Pause a sound
int lua_PauseSound(lua_State* L)
{
    Sound arg1 = LuaGetArgument_Sound(L, 1);
    PauseSound(arg1);
    return 0;
}

// Resume a paused sound
int lua_ResumeSound(lua_State* L)
{
    Sound arg1 = LuaGetArgument_Sound(L, 1);
    ResumeSound(arg1);
    return 0;
}

// Stop playing a sound
int lua_StopSound(lua_State* L)
{
    Sound arg1 = LuaGetArgument_Sound(L, 1);
    StopSound(arg1);
    return 0;
}

// Check if a sound is currently playing
int lua_IsSoundPlaying(lua_State* L)
{
    Sound arg1 = LuaGetArgument_Sound(L, 1);
    bool result = IsSoundPlaying(arg1);
    LuaPush_bool(L, result);
    return 1;
}

// Set volume for a sound (1.0 is max level)
int lua_SetSoundVolume(lua_State* L)
{
    Sound arg1 = LuaGetArgument_Sound(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    SetSoundVolume(arg1, arg2);
    return 0;
}

// Set pitch for a sound (1.0 is base level)
int lua_SetSoundPitch(lua_State* L)
{
    Sound arg1 = LuaGetArgument_Sound(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    SetSoundPitch(arg1, arg2);
    return 0;
}

// Convert wave data to desired format
int lua_WaveFormat(lua_State* L)
{
    Wave arg1 = LuaGetArgument_Wave(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    int arg3 = LuaGetArgument_int(L, 3);
    int arg4 = LuaGetArgument_int(L, 4);
    WaveFormat(&arg1, arg2, arg3, arg4);
    return 0;
}

// Copy a wave to a new wave
int lua_WaveCopy(lua_State* L)
{
    Wave arg1 = LuaGetArgument_Wave(L, 1);
    Wave result = WaveCopy(arg1);
    LuaPush_Wave(L, result);
    return 1;
}

// Crop a wave to defined samples range
int lua_WaveCrop(lua_State* L)
{
    Wave arg1 = LuaGetArgument_Wave(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    int arg3 = LuaGetArgument_int(L, 3);
    WaveCrop(&arg1, arg2, arg3);
    return 0;
}

// Get samples data from wave as a floats array
int lua_GetWaveData(lua_State* L)
{
    // TODO: return value should be a float array...
    
    Wave arg1 = LuaGetArgument_Wave(L, 1);
    float *result = GetWaveData(arg1);
    //LuaPush_float(L, result);
    //LuaPush_float(L, result);
    return 0;
}

// Load music stream from file
int lua_LoadMusicStream(lua_State* L)
{
    const char *arg1 = LuaGetArgument_string(L, 1);
    Music result = LoadMusicStream((char *)arg1);
    LuaPush_Music(L, result);
    return 1;
}

// Unload music stream
int lua_UnloadMusicStream(lua_State* L)
{
    Music arg1 = LuaGetArgument_Music(L, 1);
    UnloadMusicStream(arg1);
    return 0;
}

// Start music playing
int lua_PlayMusicStream(lua_State* L)
{
    Music arg1 = LuaGetArgument_Music(L, 1);
    PlayMusicStream(arg1);
    return 0;
}

// Updates buffers for music streaming
int lua_UpdateMusicStream(lua_State* L)
{
    Music arg1 = LuaGetArgument_Music(L, 1);
    UpdateMusicStream(arg1);
    return 0;
}

// Stop music playing
int lua_StopMusicStream(lua_State* L)
{
    Music arg1 = LuaGetArgument_Music(L, 1);
    StopMusicStream(arg1);
    return 0;
}

// Pause music playing
int lua_PauseMusicStream(lua_State* L)
{
    Music arg1 = LuaGetArgument_Music(L, 1);
    PauseMusicStream(arg1);
    return 0;
}

// Resume playing paused music
int lua_ResumeMusicStream(lua_State* L)
{
    Music arg1 = LuaGetArgument_Music(L, 1);
    ResumeMusicStream(arg1);
    return 0;
}

// Check if music is playing
int lua_IsMusicPlaying(lua_State* L)
{
    Music arg1 = LuaGetArgument_Music(L, 1);
    bool result = IsMusicPlaying(arg1);
    LuaPush_bool(L, result);
    return 1;
}

// Set volume for music (1.0 is max level)
int lua_SetMusicVolume(lua_State* L)
{
    Music arg1 = LuaGetArgument_Music(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    SetMusicVolume(arg1, arg2);
    return 0;
}

// Set pitch for a music (1.0 is base level)
int lua_SetMusicPitch(lua_State* L)
{
    Music arg1 = LuaGetArgument_Music(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    SetMusicPitch(arg1, arg2);
    return 0;
}

// Set music loop count (loop repeats)
int lua_SetMusicLoopCount(lua_State* L)
{
    Music arg1 = LuaGetArgument_Music(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    SetMusicLoopCount(arg1, arg2);
    return 0;
}

// Get music time length (in seconds)
int lua_GetMusicTimeLength(lua_State* L)
{
    Music arg1 = LuaGetArgument_Music(L, 1);
    float result = GetMusicTimeLength(arg1);
    LuaPush_float(L, result);
    return 1;
}

// Get current music time played (in seconds)
int lua_GetMusicTimePlayed(lua_State* L)
{
    Music arg1 = LuaGetArgument_Music(L, 1);
    float result = GetMusicTimePlayed(arg1);
    LuaPush_float(L, result);
    return 1;
}

// Init audio stream (to stream raw audio pcm data)
int lua_InitAudioStream(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    int arg3 = LuaGetArgument_int(L, 3);
    AudioStream result = InitAudioStream(arg1, arg2, arg3);
    LuaPush_AudioStream(L, result);
    return 1;
}

// Update audio stream buffers with data
int lua_UpdateAudioStream(lua_State* L)
{
    // TODO: arg2 parameter is a void pointer...
    
    AudioStream arg1 = LuaGetArgument_AudioStream(L, 1);
    void *arg2 = LuaGetArgument_ptr(L, 2);
    int arg3 = LuaGetArgument_int(L, 3);
    UpdateAudioStream(arg1, arg2, arg3);
    return 0;
}

// Close audio stream and free memory
int lua_CloseAudioStream(lua_State* L)
{
    AudioStream arg1 = LuaGetArgument_AudioStream(L, 1);
    CloseAudioStream(arg1);
    return 0;
}

// Check if any audio stream buffers requires refill
int lua_IsAudioBufferProcessed(lua_State* L)
{
    AudioStream arg1 = LuaGetArgument_AudioStream(L, 1);
    bool result = IsAudioBufferProcessed(arg1);
    LuaPush_bool(L, result);
    return 1;
}

// Play audio stream
int lua_PlayAudioStream(lua_State* L)
{
    AudioStream arg1 = LuaGetArgument_AudioStream(L, 1);
    PlayAudioStream(arg1);
    return 0;
}

// Stop audio stream
int lua_StopAudioStream(lua_State* L)
{
    AudioStream arg1 = LuaGetArgument_AudioStream(L, 1);
    StopAudioStream(arg1);
    return 0;
}

// Pause audio stream
int lua_PauseAudioStream(lua_State* L)
{
    AudioStream arg1 = LuaGetArgument_AudioStream(L, 1);
    PauseAudioStream(arg1);
    return 0;
}

// Resume audio stream
int lua_ResumeAudioStream(lua_State* L)
{
    AudioStream arg1 = LuaGetArgument_AudioStream(L, 1);
    ResumeAudioStream(arg1);
    return 0;
}

//----------------------------------------------------------------------------------
// Module Functions Definition - Utils math
//----------------------------------------------------------------------------------
int lua_Clamp(lua_State* L)
{
    float arg1 = LuaGetArgument_float(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    float arg3 = LuaGetArgument_float(L, 3);
    float result = Clamp(arg1, arg2, arg3);
    LuaPush_float(L, result);
    return 1;
}

//----------------------------------------------------------------------------------
// Module Functions Definition - Vector2 math
//----------------------------------------------------------------------------------
int lua_Vector2Zero(lua_State* L)
{
    Vector2 result = Vector2Zero();
    LuaPush_Vector2(L, result);
    return 1;
}

int lua_Vector2One(lua_State* L)
{
    Vector2 result = Vector2One();
    LuaPush_Vector2(L, result);
    return 1;
}

int lua_Vector2Add(lua_State* L)
{
    Vector2 arg1 = LuaGetArgument_Vector2(L, 1);
    Vector2 arg2 = LuaGetArgument_Vector2(L, 2);
    Vector2 result = Vector2Add(arg1, arg2);
    LuaPush_Vector2(L, result);
    return 1;
}

int lua_Vector2Subtract(lua_State* L)
{
    Vector2 arg1 = LuaGetArgument_Vector2(L, 1);
    Vector2 arg2 = LuaGetArgument_Vector2(L, 2);
    Vector2 result = Vector2Subtract(arg1, arg2);
    LuaPush_Vector2(L, result);
    return 1;
}

int lua_Vector2Lenght(lua_State* L)
{
    Vector2 arg1 = LuaGetArgument_Vector2(L, 1);
    float result = Vector2Lenght(arg1);
    LuaPush_float(L, result);
    return 1;
}

int lua_Vector2DotProduct(lua_State* L)
{
    Vector2 arg1 = LuaGetArgument_Vector2(L, 1);
    Vector2 arg2 = LuaGetArgument_Vector2(L, 2);
    float result = Vector2DotProduct(arg1, arg2);
    LuaPush_float(L, result);
    return 1;
}

int lua_Vector2Distance(lua_State* L)
{
    Vector2 arg1 = LuaGetArgument_Vector2(L, 1);
    Vector2 arg2 = LuaGetArgument_Vector2(L, 2);
    float result = Vector2Distance(arg1, arg2);
    LuaPush_float(L, result);
    return 1;
}

int lua_Vector2Angle(lua_State* L)
{
    Vector2 arg1 = LuaGetArgument_Vector2(L, 1);
    Vector2 arg2 = LuaGetArgument_Vector2(L, 2);
    float result = Vector2Angle(arg1, arg2);
    LuaPush_float(L, result);
    return 1;
}

int lua_Vector2Scale(lua_State* L)
{
    Vector2 arg1 = LuaGetArgument_Vector2(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    Vector2Scale(&arg1, arg2);
    LuaPush_Vector2(L, arg1);
    return 1;
}

int lua_Vector2Negate(lua_State* L)
{
    Vector2 arg1 = LuaGetArgument_Vector2(L, 1);
    Vector2Negate(&arg1);
    LuaPush_Vector2(L, arg1);
    return 1;
}

int lua_Vector2Divide(lua_State* L)
{
    Vector2 arg1 = LuaGetArgument_Vector2(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    Vector2Divide(&arg1, arg2);
    LuaPush_Vector2(L, arg1);
    return 1;
}

int lua_Vector2Normalize(lua_State* L)
{
    Vector2 arg1 = LuaGetArgument_Vector2(L, 1);
    Vector2Normalize(&arg1);
    LuaPush_Vector2(L, arg1);
    return 1;
}

//----------------------------------------------------------------------------------
// raylib [raymath] module functions - Vector3 math
//----------------------------------------------------------------------------------
int lua_VectorZero(lua_State* L)
{
    Vector3 result = VectorZero();
    LuaPush_Vector3(L, result);
    return 1;
}

int lua_VectorOne(lua_State* L)
{
    Vector3 result = VectorOne();
    LuaPush_Vector3(L, result);
    return 1;
}

int lua_VectorAdd(lua_State* L)
{
    Vector3 arg1 = LuaGetArgument_Vector3(L, 1);
    Vector3 arg2 = LuaGetArgument_Vector3(L, 2);
    Vector3 result = VectorAdd(arg1, arg2);
    LuaPush_Vector3(L, result);
    return 1;
}

int lua_VectorSubtract(lua_State* L)
{
    Vector3 arg1 = LuaGetArgument_Vector3(L, 1);
    Vector3 arg2 = LuaGetArgument_Vector3(L, 2);
    Vector3 result = VectorSubtract(arg1, arg2);
    LuaPush_Vector3(L, result);
    return 1;
}

int lua_VectorCrossProduct(lua_State* L)
{
    Vector3 arg1 = LuaGetArgument_Vector3(L, 1);
    Vector3 arg2 = LuaGetArgument_Vector3(L, 2);
    Vector3 result = VectorCrossProduct(arg1, arg2);
    LuaPush_Vector3(L, result);
    return 1;
}

int lua_VectorPerpendicular(lua_State* L)
{
    Vector3 arg1 = LuaGetArgument_Vector3(L, 1);
    Vector3 result = VectorPerpendicular(arg1);
    LuaPush_Vector3(L, result);
    return 1;
}

int lua_VectorDotProduct(lua_State* L)
{
    Vector3 arg1 = LuaGetArgument_Vector3(L, 1);
    Vector3 arg2 = LuaGetArgument_Vector3(L, 2);
    float result = VectorDotProduct(arg1, arg2);
    LuaPush_float(L, result);
    return 1;
}

int lua_VectorLength(lua_State* L)
{
    const Vector3 arg1 = LuaGetArgument_Vector3(L, 1);
    float result = VectorLength(arg1);
    LuaPush_float(L, result);
    return 1;
}

int lua_VectorScale(lua_State* L)
{
    Vector3 arg1 = LuaGetArgument_Vector3(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    VectorScale(&arg1, arg2);
    LuaPush_Vector3(L, arg1);
    return 1;
}

int lua_VectorNegate(lua_State* L)
{
    Vector3 arg1 = LuaGetArgument_Vector3(L, 1);
    VectorNegate(&arg1);
    LuaPush_Vector3(L, arg1);
    return 1;
}

int lua_VectorNormalize(lua_State* L)
{
    Vector3 arg1 = LuaGetArgument_Vector3(L, 1);
    VectorNormalize(&arg1);
    LuaPush_Vector3(L, arg1);
    return 1;
}

int lua_VectorDistance(lua_State* L)
{
    Vector3 arg1 = LuaGetArgument_Vector3(L, 1);
    Vector3 arg2 = LuaGetArgument_Vector3(L, 2);
    float result = VectorDistance(arg1, arg2);
    LuaPush_float(L, result);
    return 1;
}

int lua_VectorLerp(lua_State* L)
{
    Vector3 arg1 = LuaGetArgument_Vector3(L, 1);
    Vector3 arg2 = LuaGetArgument_Vector3(L, 2);
    float arg3 = LuaGetArgument_float(L, 3);
    Vector3 result = VectorLerp(arg1, arg2, arg3);
    LuaPush_Vector3(L, result);
    return 1;
}

int lua_VectorReflect(lua_State* L)
{
    Vector3 arg1 = LuaGetArgument_Vector3(L, 1);
    Vector3 arg2 = LuaGetArgument_Vector3(L, 2);
    Vector3 result = VectorReflect(arg1, arg2);
    LuaPush_Vector3(L, result);
    return 1;
}

int lua_VectorTransform(lua_State* L)
{
    Vector3 arg1 = LuaGetArgument_Vector3(L, 1);
    Matrix arg2 = LuaGetArgument_Matrix(L, 2);
    VectorTransform(&arg1, arg2);
    LuaPush_Vector3(L, arg1);
    return 1;
}

//----------------------------------------------------------------------------------
// raylib [raymath] module functions - Matrix math
//----------------------------------------------------------------------------------
int lua_MatrixDeterminant(lua_State* L)
{
    Matrix arg1 = LuaGetArgument_Matrix(L, 1);
    float result = MatrixDeterminant(arg1);
    LuaPush_float(L, result);
    return 1;
}

int lua_MatrixTrace(lua_State* L)
{
    Matrix arg1 = LuaGetArgument_Matrix(L, 1);
    float result = MatrixTrace(arg1);
    LuaPush_float(L, result);
    return 1;
}

int lua_MatrixTranspose(lua_State* L)
{
    Matrix arg1 = LuaGetArgument_Matrix(L, 1);
    MatrixTranspose(&arg1);
    LuaPush_Matrix(L, &arg1);
    return 1;
}

int lua_MatrixInvert(lua_State* L)
{
    Matrix arg1 = LuaGetArgument_Matrix(L, 1);
    MatrixInvert(&arg1);
    LuaPush_Matrix(L, &arg1);
    return 1;
}

int lua_MatrixNormalize(lua_State* L)
{
    Matrix arg1 = LuaGetArgument_Matrix(L, 1);
    MatrixNormalize(&arg1);
    LuaPush_Matrix(L, &arg1);
    return 1;
}

int lua_MatrixIdentity(lua_State* L)
{
    Matrix result = MatrixIdentity();
    LuaPush_Matrix(L, &result);
    return 1;
}

int lua_MatrixAdd(lua_State* L)
{
    Matrix arg1 = LuaGetArgument_Matrix(L, 1);
    Matrix arg2 = LuaGetArgument_Matrix(L, 2);
    Matrix result = MatrixAdd(arg1, arg2);
    LuaPush_Matrix(L, &result);
    return 1;
}

int lua_MatrixSubstract(lua_State* L)
{
    Matrix arg1 = LuaGetArgument_Matrix(L, 1);
    Matrix arg2 = LuaGetArgument_Matrix(L, 2);
    Matrix result = MatrixSubstract(arg1, arg2);
    LuaPush_Matrix(L, &result);
    return 1;
}

int lua_MatrixTranslate(lua_State* L)
{
    float arg1 = LuaGetArgument_float(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    float arg3 = LuaGetArgument_float(L, 3);
    Matrix result = MatrixTranslate(arg1, arg2, arg3);
    LuaPush_Matrix(L, &result);
    return 1;
}

int lua_MatrixRotate(lua_State* L)
{
    Vector3 arg1 = LuaGetArgument_Vector3(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    Matrix result = MatrixRotate(arg1, arg2);
    LuaPush_Matrix(L, &result);
    return 1;
}

int lua_MatrixRotateX(lua_State* L)
{
    float arg1 = LuaGetArgument_float(L, 1);
    Matrix result = MatrixRotateX(arg1);
    LuaPush_Matrix(L, &result);
    return 1;
}

int lua_MatrixRotateY(lua_State* L)
{
    float arg1 = LuaGetArgument_float(L, 1);
    Matrix result = MatrixRotateY(arg1);
    LuaPush_Matrix(L, &result);
    return 1;
}

int lua_MatrixRotateZ(lua_State* L)
{
    float arg1 = LuaGetArgument_float(L, 1);
    Matrix result = MatrixRotateZ(arg1);
    LuaPush_Matrix(L, &result);
    return 1;
}

int lua_MatrixScale(lua_State* L)
{
    float arg1 = LuaGetArgument_float(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    float arg3 = LuaGetArgument_float(L, 3);
    Matrix result = MatrixScale(arg1, arg2, arg3);
    LuaPush_Matrix(L, &result);
    return 1;
}

int lua_MatrixMultiply(lua_State* L)
{
    Matrix arg1 = LuaGetArgument_Matrix(L, 1);
    Matrix arg2 = LuaGetArgument_Matrix(L, 2);
    Matrix result = MatrixMultiply(arg1, arg2);
    LuaPush_Matrix(L, &result);
    return 1;
}

int lua_MatrixFrustum(lua_State* L)
{
    double arg1 = LuaGetArgument_double(L, 1);
    double arg2 = LuaGetArgument_double(L, 2);
    double arg3 = LuaGetArgument_double(L, 3);
    double arg4 = LuaGetArgument_double(L, 4);
    double arg5 = LuaGetArgument_double(L, 5);
    double arg6 = LuaGetArgument_double(L, 6);
    Matrix result = MatrixFrustum(arg1, arg2, arg3, arg4, arg5, arg6);
    LuaPush_Matrix(L, &result);
    return 1;
}

int lua_MatrixPerspective(lua_State* L)
{
    double arg1 = LuaGetArgument_double(L, 1);
    double arg2 = LuaGetArgument_double(L, 2);
    double arg3 = LuaGetArgument_double(L, 3);
    double arg4 = LuaGetArgument_double(L, 4);
    Matrix result = MatrixPerspective(arg1, arg2, arg3, arg4);
    LuaPush_Matrix(L, &result);
    return 1;
}

int lua_MatrixOrtho(lua_State* L)
{
    double arg1 = LuaGetArgument_double(L, 1);
    double arg2 = LuaGetArgument_double(L, 2);
    double arg3 = LuaGetArgument_double(L, 3);
    double arg4 = LuaGetArgument_double(L, 4);
    double arg5 = LuaGetArgument_double(L, 5);
    double arg6 = LuaGetArgument_double(L, 6);
    Matrix result = MatrixOrtho(arg1, arg2, arg3, arg4, arg5, arg6);
    LuaPush_Matrix(L, &result);
    return 1;
}

int lua_MatrixLookAt(lua_State* L)
{
    Vector3 arg1 = LuaGetArgument_Vector3(L, 1);
    Vector3 arg2 = LuaGetArgument_Vector3(L, 2);
    Vector3 arg3 = LuaGetArgument_Vector3(L, 3);
    Matrix result = MatrixLookAt(arg1, arg2, arg3);
    LuaPush_Matrix(L, &result);
    return 1;
}

//----------------------------------------------------------------------------------
// raylib [raymath] module functions - Quaternion math
//----------------------------------------------------------------------------------
int lua_QuaternionLength(lua_State* L)
{
    Quaternion arg1 = LuaGetArgument_Quaternion(L, 1);
    float result = QuaternionLength(arg1);
    LuaPush_float(L, result);
    return 1;
}

int lua_QuaternionNormalize(lua_State* L)
{
    Quaternion arg1 = LuaGetArgument_Quaternion(L, 1);
    QuaternionNormalize(&arg1);
    LuaPush_Quaternion(L, arg1);
    return 1;
}

int lua_QuaternionMultiply(lua_State* L)
{
    Quaternion arg1 = LuaGetArgument_Quaternion(L, 1);
    Quaternion arg2 = LuaGetArgument_Quaternion(L, 2);
    Quaternion result = QuaternionMultiply(arg1, arg2);
    LuaPush_Quaternion(L, result);
    return 1;
}

int lua_QuaternionSlerp(lua_State* L)
{
    Quaternion arg1 = LuaGetArgument_Quaternion(L, 1);
    Quaternion arg2 = LuaGetArgument_Quaternion(L, 2);
    float arg3 = LuaGetArgument_float(L, 3);
    Quaternion result = QuaternionSlerp(arg1, arg2, arg3);
    LuaPush_Quaternion(L, result);
    return 1;
}

int lua_QuaternionFromMatrix(lua_State* L)
{
    Matrix arg1 = LuaGetArgument_Matrix(L, 1);
    Quaternion result = QuaternionFromMatrix(arg1);
    LuaPush_Quaternion(L, result);
    return 1;
}

int lua_QuaternionToMatrix(lua_State* L)
{
    Quaternion arg1 = LuaGetArgument_Quaternion(L, 1);
    Matrix result = QuaternionToMatrix(arg1);
    LuaPush_Matrix(L, &result);
    return 1;
}

int lua_QuaternionFromAxisAngle(lua_State* L)
{
    Vector3 arg1 = LuaGetArgument_Vector3(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    Quaternion result = QuaternionFromAxisAngle(arg1, arg2);
    LuaPush_Quaternion(L, result);
    return 1;
}

int lua_QuaternionToAxisAngle(lua_State* L)
{
    Quaternion arg1 = LuaGetArgument_Quaternion(L, 1);
    Vector3 arg2;
    float arg3 = 0;
    QuaternionToAxisAngle(arg1, &arg2, &arg3);
    LuaPush_Vector3(L, arg2);
    LuaPush_float(L, arg3);
    return 2;
}

int lua_QuaternionFromEuler(lua_State* L)
{
    float arg1 = LuaGetArgument_float(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    float arg3 = LuaGetArgument_float(L, 3);
    Quaternion result = QuaternionFromEuler(arg1, arg2, arg3);
    LuaPush_Quaternion(L, result);
    return 1;
}

int lua_QuaternionToEuler(lua_State* L)
{
    Quaternion arg1 = LuaGetArgument_Quaternion(L, 1);
    Vector3 result = QuaternionToEuler(arg1);
    LuaPush_Vector3(L, result);
    return 1;
}

int lua_QuaternionTransform(lua_State* L)
{
    Quaternion arg1 = LuaGetArgument_Quaternion(L, 1);
    Matrix arg2 = LuaGetArgument_Matrix(L, 2);
    QuaternionTransform(&arg1, arg2);
    LuaPush_Quaternion(L, arg1);
    return 1;
}

//----------------------------------------------------------------------------------
// physics [physac] module functions
//----------------------------------------------------------------------------------

// Initializes physics values, pointers and creates physics loop thread
int lua_InitPhysics(lua_State* L)
{
    InitPhysics();
    return 0;
}

// Returns true if physics thread is currently enabled
int lua_IsPhysicsEnabled(lua_State* L)
{
    bool result = IsPhysicsEnabled();
    LuaPush_bool(L, result);
    return 1;
}

// Sets physics global gravity force
int lua_SetPhysicsGravity(lua_State* L)
{
    float arg1 = LuaGetArgument_float(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    SetPhysicsGravity(arg1, arg2);
    return 0;
}

// Creates a new circle physics body with generic parameters
int lua_CreatePhysicsBodyCircle(lua_State* L)
{
    Vector2 arg1 = LuaGetArgument_Vector2(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    float arg3 = LuaGetArgument_float(L, 3);
    PhysicsBody result = CreatePhysicsBodyCircle(arg1, arg2, arg3);
    LuaPush_PhysicsBody(L, result);
    return 1;
}

// Creates a new rectangle physics body with generic parameters
int lua_CreatePhysicsBodyRectangle(lua_State* L)
{
    Vector2 arg1 = LuaGetArgument_Vector2(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    float arg3 = LuaGetArgument_float(L, 3);
    float arg4 = LuaGetArgument_float(L, 4);
    PhysicsBody result = CreatePhysicsBodyRectangle(arg1, arg2, arg3, arg4);
    LuaPush_PhysicsBody(L, result);
    return 1;
}

// Creates a new polygon physics body with generic parameters
int lua_CreatePhysicsBodyPolygon(lua_State* L)
{
    Vector2 arg1 = LuaGetArgument_Vector2(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    int arg3 = LuaGetArgument_int(L, 3);
    float arg4 = LuaGetArgument_float(L, 4);
    PhysicsBody result = CreatePhysicsBodyPolygon(arg1, arg2, arg3, arg4);
    LuaPush_PhysicsBody(L, result);
    return 1;
}

// Adds a force to a physics body
int lua_PhysicsAddForce(lua_State* L)
{
    PhysicsBody arg1 = LuaGetArgument_PhysicsBody(L, 1);
    Vector2 arg2 = LuaGetArgument_Vector2(L, 2);
    PhysicsAddForce(arg1, arg2);
    return 0;
}

// Adds an angular force to a physics body
int lua_PhysicsAddTorque(lua_State* L)
{
    PhysicsBody arg1 = LuaGetArgument_PhysicsBody(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    PhysicsAddTorque(arg1, arg2);
    return 0;
}

// Shatters a polygon shape physics body to little physics bodies with explosion force
int lua_PhysicsShatter(lua_State* L)
{
    PhysicsBody arg1 = LuaGetArgument_PhysicsBody(L, 1);
    Vector2 arg2 = LuaGetArgument_Vector2(L, 2);
    float arg3 = LuaGetArgument_float(L, 3);
    PhysicsShatter(arg1, arg2, arg3);
    return 0;
}

// Returns the current amount of created physics bodies
int lua_GetPhysicsBodiesCount(lua_State* L)
{
    int result = GetPhysicsBodiesCount();
    LuaPush_int(L, result);
    return 1;
}

// Returns a physics body of the bodies pool at a specific index
int lua_GetPhysicsBody(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    PhysicsBody result = GetPhysicsBody(arg1);
    LuaPush_PhysicsBody(L, result);
    return 1;
}

// Returns the physics body shape type (PHYSICS_CIRCLE or PHYSICS_POLYGON)
int lua_GetPhysicsShapeType(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    int result = GetPhysicsShapeType(arg1);
    LuaPush_int(L, result);
    return 1;
}

// Returns the amount of vertices of a physics body shape
int lua_GetPhysicsShapeVerticesCount(lua_State* L)
{
    int arg1 = LuaGetArgument_int(L, 1);
    int result = GetPhysicsShapeVerticesCount(arg1);
    LuaPush_int(L, result);
    return 1;
}

// Returns transformed position of a body shape (body position + vertex transformed position)
int lua_GetPhysicsShapeVertex(lua_State* L)
{
    PhysicsBody arg1 = LuaGetArgument_PhysicsBody(L, 1);
    int arg2 = LuaGetArgument_int(L, 2);
    Vector2 result = GetPhysicsShapeVertex(arg1, arg2);
    LuaPush_Vector2(L, result);
    return 1;
}

// Sets physics body shape transform based on radians parameter
int lua_SetPhysicsBodyRotation(lua_State* L)
{
    PhysicsBody arg1 = LuaGetArgument_PhysicsBody(L, 1);
    float arg2 = LuaGetArgument_float(L, 2);
    SetPhysicsBodyRotation(arg1, arg2);
    return 0;
}

// Unitializes and destroy a physics body
int lua_DestroyPhysicsBody(lua_State* L)
{
    PhysicsBody arg1 = LuaGetArgument_PhysicsBody(L, 1);
    DestroyPhysicsBody(arg1);
    return 0;
}

// Destroys created physics bodies and manifolds and resets global values
int lua_ResetPhysics(lua_State* L)
{
    ResetPhysics();
    return 0;
}

// Unitializes physics pointers and closes physics loop thread
int lua_ClosePhysics(lua_State* L)
{
    ClosePhysics();
    return 0;
}

//----------------------------------------------------------------------------------
// Functions Registering
//----------------------------------------------------------------------------------
#define REG(name) { #name, lua_##name },

// raylib Functions (and data types) list
static luaL_Reg raylib_functions[] = {

    // Register non-opaque data types
    REG(Color)
    REG(Vector2)
    REG(Vector3)
    //REG(Matrix)
    REG(Quaternion)
    REG(Rectangle)
    REG(Ray)
    REG(RayHitInfo)
    REG(Camera)
    REG(Camera2D)
    REG(BoundingBox)
    //REG(Material)

    // Register functions
    //--------------------
    
    // [core] module functions
    REG(InitWindow)
    REG(CloseWindow)
    REG(WindowShouldClose)
    REG(IsWindowMinimized)
    REG(ToggleFullscreen)
    REG(SetWindowIcon)
    REG(SetWindowPosition)
    REG(SetWindowMonitor)
    REG(SetWindowMinSize)
	REG(GetScreenWidth)
    REG(GetScreenHeight)

    REG(ShowCursor)
    REG(HideCursor)
    REG(IsCursorHidden)
    REG(EnableCursor)
    REG(DisableCursor)

    REG(ClearBackground)
    REG(BeginDrawing)
    REG(EndDrawing)
    REG(Begin2dMode)
    REG(End2dMode)
    REG(Begin3dMode)
    REG(End3dMode)
    REG(BeginTextureMode)
    REG(EndTextureMode)

    REG(GetMouseRay)
    REG(GetWorldToScreen)
    REG(GetCameraMatrix)

#if defined(PLATFORM_WEB)
    REG(SetDrawingLoop)
#else
    REG(SetTargetFPS)
#endif
    REG(GetFPS)
    REG(GetFrameTime)

    REG(GetColor)
    REG(GetHexValue)
    REG(ColorToFloat)
    REG(VectorToFloat)
    REG(MatrixToFloat)
    REG(GetRandomValue)
    REG(Fade)
    
    REG(ShowLogo)
    REG(SetConfigFlags)
    REG(TraceLog)
    REG(TakeScreenshot)
    REG(IsFileExtension)

    REG(IsFileDropped)
    REG(GetDroppedFiles)
    REG(ClearDroppedFiles)
    REG(StorageSaveValue)
    REG(StorageLoadValue)

    REG(IsKeyPressed)
    REG(IsKeyDown)
    REG(IsKeyReleased)
    REG(IsKeyUp)
    REG(GetKeyPressed)
    REG(SetExitKey)

    REG(IsGamepadAvailable)
    REG(IsGamepadName)
    REG(GetGamepadName)
    REG(IsGamepadButtonPressed)
    REG(IsGamepadButtonDown)
    REG(IsGamepadButtonReleased)
    REG(IsGamepadButtonUp)
    REG(GetGamepadButtonPressed)
    REG(GetGamepadAxisCount)
    REG(GetGamepadAxisMovement)

    REG(IsMouseButtonPressed)
    REG(IsMouseButtonDown)
    REG(IsMouseButtonReleased)
    REG(IsMouseButtonUp)
    REG(GetMouseX)
    REG(GetMouseY)
    REG(GetMousePosition)
    REG(SetMousePosition)
    REG(GetMouseWheelMove)
    
    REG(GetTouchX)
    REG(GetTouchY)
    REG(GetTouchPosition)

    // [gestures] module functions
    REG(SetGesturesEnabled)
    REG(IsGestureDetected)
    REG(GetGestureDetected)
    REG(GetTouchPointsCount)
    REG(GetGestureHoldDuration)
    REG(GetGestureDragVector)
    REG(GetGestureDragAngle)
    REG(GetGesturePinchVector)
    REG(GetGesturePinchAngle)

    // [camera] module functions
    REG(SetCameraMode)
    REG(UpdateCamera)
    REG(SetCameraPanControl)
    REG(SetCameraAltControl)
    REG(SetCameraSmoothZoomControl)
    REG(SetCameraMoveControls)

    // [shapes] module functions
    REG(DrawPixel)
    REG(DrawPixelV)
    REG(DrawLine)
    REG(DrawLineV)
    REG(DrawLineEx)
    REG(DrawLineBezier)
    REG(DrawCircle)
    REG(DrawCircleGradient)
    REG(DrawCircleV)
    REG(DrawCircleLines)
    REG(DrawRectangle)
    REG(DrawRectangleRec)
    REG(DrawRectanglePro)
    REG(DrawRectangleGradient)
    REG(DrawRectangleV)
    REG(DrawRectangleLines)
    REG(DrawTriangle)
    REG(DrawTriangleLines)
    REG(DrawPoly)
    REG(DrawPolyEx)
    REG(DrawPolyExLines)

    REG(CheckCollisionRecs)
    REG(CheckCollisionCircles)
    REG(CheckCollisionCircleRec)
    REG(GetCollisionRec)
    REG(CheckCollisionPointRec)
    REG(CheckCollisionPointCircle)
    REG(CheckCollisionPointTriangle)

    // [textures] module functions
    REG(LoadImage)
    REG(LoadImageEx)
    REG(LoadImagePro)
    REG(LoadImageRaw)
    REG(LoadTexture)
    REG(LoadTextureFromImage)
    REG(LoadRenderTexture)
    REG(UnloadImage)
    REG(UnloadTexture)
    REG(UnloadRenderTexture)
    REG(GetImageData)
    REG(GetTextureData)
    REG(UpdateTexture)
    REG(ImageToPOT)
    REG(ImageFormat)
    REG(ImageAlphaMask)
    REG(ImageDither)
    REG(ImageCopy)
    REG(ImageCrop)
    REG(ImageResize)
    REG(ImageResizeNN)
    REG(ImageText)
    REG(ImageTextEx)
    REG(ImageDraw)
    REG(ImageDrawText)
    REG(ImageDrawTextEx)
    REG(ImageFlipVertical)
    REG(ImageFlipHorizontal)
    REG(ImageColorTint)
    REG(ImageColorInvert)
    REG(ImageColorGrayscale)
    REG(ImageColorContrast)
    REG(ImageColorBrightness)
    REG(GenTextureMipmaps)
    REG(SetTextureFilter)
    REG(SetTextureWrap)
    
    REG(DrawTexture)
    REG(DrawTextureV)
    REG(DrawTextureEx)
    REG(DrawTextureRec)
    REG(DrawTexturePro)

    // [text] module functions
    REG(GetDefaultFont)
    REG(LoadSpriteFont)
    REG(LoadSpriteFontEx)
    REG(UnloadSpriteFont)
    REG(DrawText)
    REG(DrawTextEx)
    REG(MeasureText)
    REG(MeasureTextEx)
    REG(DrawFPS)

    // [models] module functions
    REG(DrawLine3D)
    REG(DrawCircle3D)
    REG(DrawCube)
    REG(DrawCubeV)
    REG(DrawCubeWires)
    REG(DrawCubeTexture)
    REG(DrawSphere)
    REG(DrawSphereEx)
    REG(DrawSphereWires)
    REG(DrawCylinder)
    REG(DrawCylinderWires)
    REG(DrawPlane)
    REG(DrawRay)
    REG(DrawGrid)
    REG(DrawGizmo)

    REG(LoadMesh)
    REG(LoadMeshEx)
    REG(LoadModel)
    REG(LoadModelFromMesh)
    REG(LoadHeightmap)
    REG(LoadCubicmap)
    REG(UnloadMesh)
    REG(UnloadModel)
    
    REG(LoadMaterial)
    REG(LoadDefaultMaterial)
    REG(UnloadMaterial)

    REG(DrawModel)
    REG(DrawModelEx)
    REG(DrawModelWires)
    REG(DrawBoundingBox)
    REG(DrawModelWiresEx)
    REG(DrawBillboard)
    REG(DrawBillboardRec)
    REG(CalculateBoundingBox)
    REG(CheckCollisionSpheres)
    REG(CheckCollisionBoxes)
    REG(CheckCollisionBoxSphere)
    REG(CheckCollisionRaySphere)
    REG(CheckCollisionRaySphereEx)
    REG(CheckCollisionRayBox)
    REG(GetCollisionRayMesh)
    REG(GetCollisionRayTriangle)
    REG(GetCollisionRayGround)

    // [rlgl] module functions
    REG(LoadText)
    REG(LoadShader)
    REG(UnloadShader)
    REG(GetDefaultShader)
    REG(GetDefaultTexture)
    REG(GetShaderLocation)
    REG(SetShaderValue)
    REG(SetShaderValuei)
    REG(SetShaderValueMatrix)
    REG(SetMatrixProjection)
    REG(SetMatrixModelview)
    REG(BeginShaderMode)
    REG(EndShaderMode)
    REG(BeginBlendMode)
    REG(EndBlendMode)

    REG(InitVrSimulator)
    REG(CloseVrSimulator)
    REG(IsVrSimulatorReady)
    REG(UpdateVrTracking)
    REG(ToggleVrMode)
    REG(BeginVrDrawing)
    REG(EndVrDrawing)

    // [audio] module functions
    REG(InitAudioDevice)
    REG(CloseAudioDevice)
    REG(IsAudioDeviceReady)
    REG(SetMasterVolume)

    REG(LoadWave)
    REG(LoadWaveEx)
    REG(LoadSound)
    REG(LoadSoundFromWave)
    REG(UpdateSound)
    REG(UnloadWave)
    REG(UnloadSound)
    REG(PlaySound)
    REG(PauseSound)
    REG(ResumeSound)
    REG(StopSound)
    REG(IsSoundPlaying)
    REG(SetSoundVolume)
    REG(SetSoundPitch)
    REG(WaveFormat)
    REG(WaveCopy)
    REG(WaveCrop)
    REG(GetWaveData)

    REG(LoadMusicStream)
    REG(UnloadMusicStream)
    REG(UpdateMusicStream)
    REG(PlayMusicStream)
    REG(StopMusicStream)
    REG(PauseMusicStream)
    REG(ResumeMusicStream)
    REG(IsMusicPlaying)
    REG(SetMusicVolume)
    REG(SetMusicPitch)
    REG(SetMusicLoopCount)
    REG(GetMusicTimeLength)
    REG(GetMusicTimePlayed)

    REG(InitAudioStream)
    REG(UpdateAudioStream)
    REG(CloseAudioStream)
    REG(IsAudioBufferProcessed)
    REG(PlayAudioStream)
    REG(PauseAudioStream)
    REG(ResumeAudioStream)
    REG(StopAudioStream)

    // [raymath] module functions - general
    REG(Clamp)
    
    // [raymath] module functions - Vector2
    REG(Vector2Zero)
    REG(Vector2One)
    REG(Vector2Add)
    REG(Vector2Subtract)
    REG(Vector2Lenght)
    REG(Vector2DotProduct)
    REG(Vector2Distance)
    REG(Vector2Angle)
    REG(Vector2Scale)
    REG(Vector2Negate)
    REG(Vector2Divide)
    REG(Vector2Normalize)

    // [raymath] module functions - Vector3
    REG(VectorZero)
    REG(VectorOne)
    REG(VectorAdd)
    REG(VectorSubtract)
    REG(VectorCrossProduct)
    REG(VectorPerpendicular)
    REG(VectorLength)
    REG(VectorDotProduct)
    REG(VectorDistance)
    REG(VectorScale)
    REG(VectorNegate)
    REG(VectorNormalize)
    REG(VectorTransform)
    REG(VectorLerp)
    REG(VectorReflect)
    
    // [raymath] module functions - Matrix
    REG(MatrixDeterminant)
    REG(MatrixTrace)
    REG(MatrixTranspose)
    REG(MatrixInvert)
    REG(MatrixNormalize)
    REG(MatrixIdentity)
    REG(MatrixAdd)
    REG(MatrixSubstract)
    REG(MatrixTranslate)
    REG(MatrixRotate)
    REG(MatrixRotateX)
    REG(MatrixRotateY)
    REG(MatrixRotateZ)
    REG(MatrixScale)
    REG(MatrixMultiply)
    REG(MatrixFrustum)
    REG(MatrixPerspective)
    REG(MatrixOrtho)
    REG(MatrixLookAt)
    
    // [raymath] module functions - Quaternion
    REG(QuaternionLength)
    REG(QuaternionNormalize)
    REG(QuaternionMultiply)
    REG(QuaternionSlerp)
    REG(QuaternionFromMatrix)
    REG(QuaternionToMatrix)
    REG(QuaternionFromAxisAngle)
    REG(QuaternionToAxisAngle)
    REG(QuaternionFromEuler)
    REG(QuaternionToEuler)
    REG(QuaternionTransform)
    
    // [physac] module functions
    REG(InitPhysics)
    REG(IsPhysicsEnabled)
    REG(SetPhysicsGravity)
    REG(CreatePhysicsBodyCircle)
    REG(CreatePhysicsBodyRectangle)
    REG(CreatePhysicsBodyPolygon)
    REG(PhysicsAddForce)
    REG(PhysicsAddTorque)
    REG(PhysicsShatter)
    REG(GetPhysicsBodiesCount)
    REG(GetPhysicsBody)
    REG(GetPhysicsShapeType)
    REG(GetPhysicsShapeVerticesCount)
    REG(GetPhysicsShapeVertex)
    REG(SetPhysicsBodyRotation)
    REG(DestroyPhysicsBody)
    REG(ResetPhysics)
    REG(ClosePhysics)

    { NULL, NULL }  // sentinel: end signal
};

// Register raylib Lua functionality
static void RegisterLuaFunctions(const char *opt_table)
{
    if (opt_table) lua_createtable(L, 0, sizeof(raylib_functions)/sizeof(raylib_functions[0]));
    else lua_pushglobaltable(L);

    luaL_setfuncs(L, raylib_functions, 0);
}

//----------------------------------------------------------------------------------
// raylib Lua API
//----------------------------------------------------------------------------------

// Initialize Lua system
RLUADEF void InitLuaDevice(void)
{
    mainLuaState = luaL_newstate();
    L = mainLuaState;
    
    LuaStartEnum();
    LuaSetEnum("SHOW_LOGO", 1);
    LuaSetEnum("FULLSCREEN_MODE", 2);
    LuaSetEnum("WINDOW_RESIZABLE", 4);
    LuaSetEnum("WINDOW_DECORATED", 8);
    LuaSetEnum("WINDOW_TRANSPARENT", 16);
    LuaSetEnum("MSAA_4X_HINT", 32);
    LuaSetEnum("VSYNC_HINT", 64);
    LuaEndEnum("FLAG");

    LuaStartEnum();
    LuaSetEnum("SPACE", 32);
    LuaSetEnum("ESCAPE", 256);
    LuaSetEnum("ENTER", 257);
    LuaSetEnum("BACKSPACE", 259);
    LuaSetEnum("RIGHT", 262);
    LuaSetEnum("LEFT", 263);
    LuaSetEnum("DOWN", 264);
    LuaSetEnum("UP", 265);
    LuaSetEnum("F1", 290);
    LuaSetEnum("F2", 291);
    LuaSetEnum("F3", 292);
    LuaSetEnum("F4", 293);
    LuaSetEnum("F5", 294);
    LuaSetEnum("F6", 295);
    LuaSetEnum("F7", 296);
    LuaSetEnum("F8", 297);
    LuaSetEnum("F9", 298);
    LuaSetEnum("F10", 299);
    LuaSetEnum("LEFT_SHIFT", 340);
    LuaSetEnum("LEFT_CONTROL", 341);
    LuaSetEnum("LEFT_ALT", 342);
    LuaSetEnum("RIGHT_SHIFT", 344);
    LuaSetEnum("RIGHT_CONTROL", 345);
    LuaSetEnum("RIGHT_ALT", 346);
    LuaSetEnum("ZERO", 48);
    LuaSetEnum("ONE", 49);
    LuaSetEnum("TWO", 50);
    LuaSetEnum("THREE", 51);
    LuaSetEnum("FOUR", 52);
    LuaSetEnum("FIVE", 53);
    LuaSetEnum("SIX", 54);
    LuaSetEnum("SEVEN", 55);
    LuaSetEnum("EIGHT", 56);
    LuaSetEnum("NINE", 57);
    LuaSetEnum("A", 65);
    LuaSetEnum("B", 66);
    LuaSetEnum("C", 67);
    LuaSetEnum("D", 68);
    LuaSetEnum("E", 69);
    LuaSetEnum("F", 70);
    LuaSetEnum("G", 71);
    LuaSetEnum("H", 72);
    LuaSetEnum("I", 73);
    LuaSetEnum("J", 74);
    LuaSetEnum("K", 75);
    LuaSetEnum("L", 76);
    LuaSetEnum("M", 77);
    LuaSetEnum("N", 78);
    LuaSetEnum("O", 79);
    LuaSetEnum("P", 80);
    LuaSetEnum("Q", 81);
    LuaSetEnum("R", 82);
    LuaSetEnum("S", 83);
    LuaSetEnum("T", 84);
    LuaSetEnum("U", 85);
    LuaSetEnum("V", 86);
    LuaSetEnum("W", 87);
    LuaSetEnum("X", 88);
    LuaSetEnum("Y", 89);
    LuaSetEnum("Z", 90);
    LuaEndEnum("KEY");

    LuaStartEnum();
    LuaSetEnum("LEFT_BUTTON", 0);
    LuaSetEnum("RIGHT_BUTTON", 1);
    LuaSetEnum("MIDDLE_BUTTON", 2);
    LuaEndEnum("MOUSE");
    
    LuaStartEnum();
    LuaSetEnum("PLAYER1", 0);
    LuaSetEnum("PLAYER2", 1);
    LuaSetEnum("PLAYER3", 2);
    LuaSetEnum("PLAYER4", 3);

    LuaSetEnum("PS3_BUTTON_TRIANGLE", 0);
    LuaSetEnum("PS3_BUTTON_CIRCLE", 1);
    LuaSetEnum("PS3_BUTTON_CROSS", 2);
    LuaSetEnum("PS3_BUTTON_SQUARE", 3);
    LuaSetEnum("PS3_BUTTON_L1", 6);
    LuaSetEnum("PS3_BUTTON_R1", 7);
    LuaSetEnum("PS3_BUTTON_L2", 4);
    LuaSetEnum("PS3_BUTTON_R2",  5);
    LuaSetEnum("PS3_BUTTON_START", 8);
    LuaSetEnum("PS3_BUTTON_SELECT", 9);
    LuaSetEnum("PS3_BUTTON_UP", 24);
    LuaSetEnum("PS3_BUTTON_RIGHT", 25);
    LuaSetEnum("PS3_BUTTON_DOWN", 26);
    LuaSetEnum("PS3_BUTTON_LEFT", 27);
    LuaSetEnum("PS3_BUTTON_PS", 12);
    LuaSetEnum("PS3_AXIS_LEFT_X", 0);
    LuaSetEnum("PS3_AXIS_LEFT_Y", 1);
    LuaSetEnum("PS3_AXIS_RIGHT_X", 2);
    LuaSetEnum("PS3_AXIS_RIGHT_Y", 5);
    LuaSetEnum("PS3_AXIS_L2", 3);       // [1..-1] (pressure-level)
    LuaSetEnum("PS3_AXIS_R2", 4);       // [1..-1] (pressure-level)

// Xbox360 USB Controller Buttons
    LuaSetEnum("XBOX_BUTTON_A", 0);
    LuaSetEnum("XBOX_BUTTON_B", 1);
    LuaSetEnum("XBOX_BUTTON_X", 2);
    LuaSetEnum("XBOX_BUTTON_Y", 3);
    LuaSetEnum("XBOX_BUTTON_LB", 4);
    LuaSetEnum("XBOX_BUTTON_RB", 5);
    LuaSetEnum("XBOX_BUTTON_SELECT", 6);
    LuaSetEnum("XBOX_BUTTON_START", 7);
    LuaSetEnum("XBOX_BUTTON_UP", 10);
    LuaSetEnum("XBOX_BUTTON_RIGHT", 11);
    LuaSetEnum("XBOX_BUTTON_DOWN", 12);
    LuaSetEnum("XBOX_BUTTON_LEFT", 13);
    LuaSetEnum("XBOX_BUTTON_HOME", 8);
#if defined(PLATFORM_RPI)
    LuaSetEnum("XBOX_AXIS_LEFT_X", 0);      // [-1..1] (left->right)
    LuaSetEnum("XBOX_AXIS_LEFT_Y", 1);      // [-1..1] (up->down)
    LuaSetEnum("XBOX_AXIS_RIGHT_X", 3);     // [-1..1] (left->right)
    LuaSetEnum("XBOX_AXIS_RIGHT_Y", 4);     // [-1..1] (up->down)
    LuaSetEnum("XBOX_AXIS_LT", 2);          // [-1..1] (pressure-level)
    LuaSetEnum("XBOX_AXIS_RT", 5);          // [-1..1] (pressure-level)
#else
    LuaSetEnum("XBOX_AXIS_LEFT_X", 0);      // [-1..1] (left->right)
    LuaSetEnum("XBOX_AXIS_LEFT_Y", 1);      // [1..-1] (up->down)
    LuaSetEnum("XBOX_AXIS_RIGHT_X", 2);     // [-1..1] (left->right)
    LuaSetEnum("XBOX_AXIS_RIGHT_Y", 3);     // [1..-1] (up->down)
    LuaSetEnum("XBOX_AXIS_LT", 4);          // [-1..1] (pressure-level)
    LuaSetEnum("XBOX_AXIS_RT", 5);          // [-1..1] (pressure-level)
#endif
    LuaEndEnum("GAMEPAD");

    lua_pushglobaltable(L);
    LuaSetEnumColor("LIGHTGRAY", LIGHTGRAY);
    LuaSetEnumColor("GRAY", GRAY);
    LuaSetEnumColor("DARKGRAY", DARKGRAY);
    LuaSetEnumColor("YELLOW", YELLOW);
    LuaSetEnumColor("GOLD", GOLD);
    LuaSetEnumColor("ORANGE", ORANGE);
    LuaSetEnumColor("PINK", PINK);
    LuaSetEnumColor("RED", RED);
    LuaSetEnumColor("MAROON", MAROON);
    LuaSetEnumColor("GREEN", GREEN);
    LuaSetEnumColor("LIME", LIME);
    LuaSetEnumColor("DARKGREEN", DARKGREEN);
    LuaSetEnumColor("SKYBLUE", SKYBLUE);
    LuaSetEnumColor("BLUE", BLUE);
    LuaSetEnumColor("DARKBLUE", DARKBLUE);
    LuaSetEnumColor("PURPLE", PURPLE);
    LuaSetEnumColor("VIOLET", VIOLET);
    LuaSetEnumColor("DARKPURPLE", DARKPURPLE);
    LuaSetEnumColor("BEIGE", BEIGE);
    LuaSetEnumColor("BROWN", BROWN);
    LuaSetEnumColor("DARKBROWN", DARKBROWN);
    LuaSetEnumColor("WHITE", WHITE);
    LuaSetEnumColor("BLACK", BLACK);
    LuaSetEnumColor("BLANK", BLANK);
    LuaSetEnumColor("MAGENTA", MAGENTA);
    LuaSetEnumColor("RAYWHITE", RAYWHITE);
    lua_pop(L, 1);

    LuaStartEnum();
    LuaSetEnum("UNCOMPRESSED_GRAYSCALE", UNCOMPRESSED_GRAYSCALE);
    LuaSetEnum("UNCOMPRESSED_GRAY_ALPHA", UNCOMPRESSED_GRAY_ALPHA);
    LuaSetEnum("UNCOMPRESSED_R5G6B5", UNCOMPRESSED_R5G6B5);
    LuaSetEnum("UNCOMPRESSED_R8G8B8", UNCOMPRESSED_R8G8B8);
    LuaSetEnum("UNCOMPRESSED_R5G5B5A1", UNCOMPRESSED_R5G5B5A1);
    LuaSetEnum("UNCOMPRESSED_R4G4B4A4", UNCOMPRESSED_R4G4B4A4);
    LuaSetEnum("UNCOMPRESSED_R8G8B8A8", UNCOMPRESSED_R8G8B8A8);
    LuaSetEnum("COMPRESSED_DXT1_RGB", COMPRESSED_DXT1_RGB);
    LuaSetEnum("COMPRESSED_DXT1_RGBA", COMPRESSED_DXT1_RGBA);
    LuaSetEnum("COMPRESSED_DXT3_RGBA", COMPRESSED_DXT3_RGBA);
    LuaSetEnum("COMPRESSED_DXT5_RGBA", COMPRESSED_DXT5_RGBA);
    LuaSetEnum("COMPRESSED_ETC1_RGB", COMPRESSED_ETC1_RGB);
    LuaSetEnum("COMPRESSED_ETC2_RGB", COMPRESSED_ETC2_RGB);
    LuaSetEnum("COMPRESSED_ETC2_EAC_RGBA", COMPRESSED_ETC2_EAC_RGBA);
    LuaSetEnum("COMPRESSED_PVRT_RGB", COMPRESSED_PVRT_RGB);
    LuaSetEnum("COMPRESSED_PVRT_RGBA", COMPRESSED_PVRT_RGBA);
    LuaSetEnum("COMPRESSED_ASTC_4x4_RGBA", COMPRESSED_ASTC_4x4_RGBA);
    LuaSetEnum("COMPRESSED_ASTC_8x8_RGBA", COMPRESSED_ASTC_8x8_RGBA);
    LuaEndEnum("TextureFormat");

    LuaStartEnum();
    LuaSetEnum("ALPHA", BLEND_ALPHA);
    LuaSetEnum("ADDITIVE", BLEND_ADDITIVE);
    LuaSetEnum("MULTIPLIED", BLEND_MULTIPLIED);
    LuaEndEnum("BlendMode");
    
    LuaStartEnum();
    LuaSetEnum("POINT", FILTER_POINT);
    LuaSetEnum("BILINEAR", FILTER_BILINEAR);
    LuaSetEnum("TRILINEAR", FILTER_TRILINEAR);
    LuaSetEnum("ANISOTROPIC_4X", FILTER_ANISOTROPIC_4X);
    LuaSetEnum("ANISOTROPIC_8X", FILTER_ANISOTROPIC_8X);
    LuaSetEnum("ANISOTROPIC_16X", FILTER_ANISOTROPIC_16X);
    LuaEndEnum("TextureFilter");

    LuaStartEnum();
    LuaSetEnum("NONE", GESTURE_NONE);
    LuaSetEnum("TAP", GESTURE_TAP);
    LuaSetEnum("DOUBLETAP", GESTURE_DOUBLETAP);
    LuaSetEnum("HOLD", GESTURE_HOLD);
    LuaSetEnum("DRAG", GESTURE_DRAG);
    LuaSetEnum("SWIPE_RIGHT", GESTURE_SWIPE_RIGHT);
    LuaSetEnum("SWIPE_LEFT", GESTURE_SWIPE_LEFT);
    LuaSetEnum("SWIPE_UP", GESTURE_SWIPE_UP);
    LuaSetEnum("SWIPE_DOWN", GESTURE_SWIPE_DOWN);
    LuaSetEnum("PINCH_IN", GESTURE_PINCH_IN);
    LuaSetEnum("PINCH_OUT", GESTURE_PINCH_OUT);
    LuaEndEnum("Gestures");

    LuaStartEnum();
    LuaSetEnum("CUSTOM", CAMERA_CUSTOM);
    LuaSetEnum("FREE", CAMERA_FREE);
    LuaSetEnum("ORBITAL", CAMERA_ORBITAL);
    LuaSetEnum("FIRST_PERSON", CAMERA_FIRST_PERSON);
    LuaSetEnum("THIRD_PERSON", CAMERA_THIRD_PERSON);
    LuaEndEnum("CameraMode");

    LuaStartEnum();
    LuaSetEnum("DEFAULT_DEVICE", HMD_DEFAULT_DEVICE);
    LuaSetEnum("OCULUS_RIFT_DK2", HMD_OCULUS_RIFT_DK2);
    LuaSetEnum("OCULUS_RIFT_CV1", HMD_OCULUS_RIFT_CV1);
    LuaSetEnum("VALVE_HTC_VIVE", HMD_VALVE_HTC_VIVE);
    LuaSetEnum("SAMSUNG_GEAR_VR", HMD_SAMSUNG_GEAR_VR);
    LuaSetEnum("GOOGLE_CARDBOARD", HMD_GOOGLE_CARDBOARD);
    LuaSetEnum("SONY_PLAYSTATION_VR", HMD_SONY_PLAYSTATION_VR);
    LuaSetEnum("RAZER_OSVR", HMD_RAZER_OSVR);
    LuaSetEnum("FOVE_VR", HMD_FOVE_VR);
    LuaEndEnum("VrDevice");

    lua_pushglobaltable(L);
    LuaSetEnum("INFO", INFO);
    LuaSetEnum("ERROR", ERROR);
    LuaSetEnum("WARNING", WARNING);
    LuaSetEnum("DEBUG", DEBUG);
    LuaSetEnum("OTHER", OTHER);
    lua_pop(L, 1);

    LuaPush_bool(L, true);
#if defined(PLATFORM_DESKTOP)
    lua_setglobal(L, "PLATFORM_DESKTOP");
#elif defined(PLATFORM_ANDROID)
    lua_setglobal(L, "PLATFORM_ANDROID");
#elif defined(PLATFORM_RPI)
    lua_setglobal(L, "PLATFORM_RPI");
#elif defined(PLATFORM_WEB)
    lua_setglobal(L, "PLATFORM_WEB");
#endif

    luaL_openlibs(L);
    LuaBuildOpaqueMetatables();

    RegisterLuaFunctions(0);        // Register Lua raylib functions
}

// De-initialize Lua system
RLUADEF void CloseLuaDevice(void)
{
    if (mainLuaState)
    {
        lua_close(mainLuaState);
        mainLuaState = 0;
        L = 0;
    }
}

// Execute raylib Lua code
RLUADEF void ExecuteLuaCode(const char *code)
{
    if (!mainLuaState)
    {
        TraceLog(WARNING, "Lua device not initialized");
        return;
    }

    int result = luaL_dostring(L, code);

    switch (result)
    {
        case LUA_OK: break;
        case LUA_ERRRUN: TraceLog(ERROR, "Lua Runtime Error: %s", lua_tostring(L, -1)); break;
        case LUA_ERRMEM: TraceLog(ERROR, "Lua Memory Error: %s", lua_tostring(L, -1)); break;
        default: TraceLog(ERROR, "Lua Error: %s", lua_tostring(L, -1)); break;
    }
}

// Execute raylib Lua script
RLUADEF void ExecuteLuaFile(const char *filename)
{
    if (!mainLuaState)
    {
        TraceLog(WARNING, "Lua device not initialized");
        return;
    }

    int result = luaL_dofile(L, filename);

    switch (result)
    {
        case LUA_OK: break;
        case LUA_ERRRUN: TraceLog(ERROR, "Lua Runtime Error: %s", lua_tostring(L, -1));
        case LUA_ERRMEM: TraceLog(ERROR, "Lua Memory Error: %s", lua_tostring(L, -1));
        default: TraceLog(ERROR, "Lua Error: %s", lua_tostring(L, -1));
    }
}
#endif // RLUA_IMPLEMENTATION
