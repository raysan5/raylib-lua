//----------------------------------------------------------------------------------
// Structures Definition
//----------------------------------------------------------------------------------
// Vector3 type
static Vector3 LuaGetArgument_Vector3(lua_State *L, int index)
{
    Vector3 result = { 0 };
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, x) == LUA_TNUMBER, index, "Expected Vector3.x");
    result.x = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, y) == LUA_TNUMBER, index, "Expected Vector3.y");
    result.y = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, z) == LUA_TNUMBER, index, "Expected Vector3.z");
    result.z = LuaGetArgument_float(L, -1);
    lua_pop(L, 3);
    return result;}

// RenderTexture2D type, for texture rendering
static RenderTexture2D LuaGetArgument_RenderTexture2D(lua_State *L, int index)
{
    RenderTexture2D result = { 0 };
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, int id) == LUA_TNUMBER, index, "Expected RenderTexture2D.int id");
    result.int id = LuaGetArgument_unsigned(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, texture) == LUA_TNUMBER, index, "Expected RenderTexture2D.texture");
    result.texture = LuaGetArgument_Texture2D(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, depth) == LUA_TNUMBER, index, "Expected RenderTexture2D.depth");
    result.depth = LuaGetArgument_Texture2D(L, -1);
    lua_pop(L, 3);
    return result;}

// SpriteFont type, includes texture and charSet array data
static SpriteFont LuaGetArgument_SpriteFont(lua_State *L, int index)
{
    SpriteFont result = { 0 };
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, texture) == LUA_TNUMBER, index, "Expected SpriteFont.texture");
    result.texture = LuaGetArgument_Texture2D(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, baseSize) == LUA_TNUMBER, index, "Expected SpriteFont.baseSize");
    result.baseSize = LuaGetArgument_int(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, charsCount) == LUA_TNUMBER, index, "Expected SpriteFont.charsCount");
    result.charsCount = LuaGetArgument_int(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, *chars) == LUA_TNUMBER, index, "Expected SpriteFont.*chars");
    result.*chars = LuaGetArgument_CharInfo(L, -1);
    lua_pop(L, 4);
    return result;}

// Bounding box type
static BoundingBox LuaGetArgument_BoundingBox(lua_State *L, int index)
{
    BoundingBox result = { 0 };
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, min) == LUA_TNUMBER, index, "Expected BoundingBox.min");
    result.min = LuaGetArgument_Vector3(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, max) == LUA_TNUMBER, index, "Expected BoundingBox.max");
    result.max = LuaGetArgument_Vector3(L, -1);
    lua_pop(L, 2);
    return result;}

// Vertex data definning a mesh
// NOTE: Data stored in CPU memory (and GPU)
static Mesh LuaGetArgument_Mesh(lua_State *L, int index)
{
    Mesh result = { 0 };
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, vertexCount) == LUA_TNUMBER, index, "Expected Mesh.vertexCount");
    result.vertexCount = LuaGetArgument_int(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, triangleCount) == LUA_TNUMBER, index, "Expected Mesh.triangleCount");
    result.triangleCount = LuaGetArgument_int(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, *vertices) == LUA_TNUMBER, index, "Expected Mesh.*vertices");
    result.*vertices = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, *texcoords) == LUA_TNUMBER, index, "Expected Mesh.*texcoords");
    result.*texcoords = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, *texcoords2) == LUA_TNUMBER, index, "Expected Mesh.*texcoords2");
    result.*texcoords2 = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, *normals) == LUA_TNUMBER, index, "Expected Mesh.*normals");
    result.*normals = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, *tangents) == LUA_TNUMBER, index, "Expected Mesh.*tangents");
    result.*tangents = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, char *colors) == LUA_TNUMBER, index, "Expected Mesh.char *colors");
    result.char *colors = LuaGetArgument_unsigned(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, short *indices) == LUA_TNUMBER, index, "Expected Mesh.short *indices");
    result.short *indices = LuaGetArgument_unsigned(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, int vaoId) == LUA_TNUMBER, index, "Expected Mesh.int vaoId");
    result.int vaoId = LuaGetArgument_unsigned(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, int vboId[7]) == LUA_TNUMBER, index, "Expected Mesh.int vboId[7]");
    result.int vboId[7] = LuaGetArgument_unsigned(L, -1);
    lua_pop(L, 11);
    return result;}

//------------------------------------------------------------------------------------
// Global Variables Definition
//------------------------------------------------------------------------------------
// It's lonely here...
//------------------------------------------------------------------------------------
// Window and Graphics Device Functions (Module: core)
//------------------------------------------------------------------------------------
// Window-related functions
// Cursor-related functions
// Drawing-related functions
// Screen-space-related functions
// Timming-related functions
// Color-related functions
// Misc. functions
// Files management functions
//RLAPI const char *GetExtension(const char *fileName);             // Get pointer to extension for a filename string
//RLAPI const char *GetFileName(const char *filePath);              // Get pointer to filename for a path string
//RLAPI const char *GetDirectoryPath(const char *fileName);         // Get full path for a given fileName (uses static string)
//RLAPI const char *GetWorkingDirectory(void);                      // Get current working directory (uses static string)
// Persistent storage management
//------------------------------------------------------------------------------------
// Input Handling Functions (Module: core)
//------------------------------------------------------------------------------------
// Input-related functions: keyboard
// Input-related functions: gamepads
//RLAPI const char *GetGamepadName(int gamepad);                // Return gamepad internal name id
// Input-related functions: mouse
// Input-related functions: touch
//------------------------------------------------------------------------------------
// Gestures and Touch Handling Functions (Module: gestures)
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
// Camera System Functions (Module: camera)
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
// Basic Shapes Drawing Functions (Module: shapes)
//------------------------------------------------------------------------------------
// Basic shapes drawing functions
// Basic shapes collision detection functions
//------------------------------------------------------------------------------------
// Texture Loading and Drawing Functions (Module: textures)
//------------------------------------------------------------------------------------
// Image/Texture2D data loading/unloading/saving functions
// Image manipulation functions
// Image generation functions
// Texture2D configuration functions
// Texture2D drawing functions
//------------------------------------------------------------------------------------
// Font Loading and Text Drawing Functions (Module: text)
//------------------------------------------------------------------------------------
// SpriteFont loading/unloading functions
// Text drawing functions
// Text misc. functions
//------------------------------------------------------------------------------------
// Basic 3d Shapes Drawing Functions (Module: models)
//------------------------------------------------------------------------------------
// Basic geometric 3D shapes drawing functions
//DrawTorus(), DrawTeapot() could be useful?
//------------------------------------------------------------------------------------
// Model 3d Loading and Drawing Functions (Module: models)
//------------------------------------------------------------------------------------
// Model loading/unloading functions
// Mesh loading/unloading functions
// Mesh manipulation functions
// Mesh generation functions
// Material loading/unloading functions
// Model drawing functions
// Collision detection functions
//------------------------------------------------------------------------------------
// Shaders System Functions (Module: rlgl)
// NOTE: This functions are useless when using OpenGL 1.1
//------------------------------------------------------------------------------------
// Shader loading/unloading functions
// Shader configuration functions
// Texture maps generation (PBR)
// NOTE: Required shaders should be provided
// Shading begin/end functions
// VR control functions
//------------------------------------------------------------------------------------
// Audio Loading and Playing Functions (Module: audio)
//------------------------------------------------------------------------------------
// Audio device management functions
// Wave/Sound loading/unloading functions
// Wave/Sound management functions
// Music management functions
// AudioStream management functions
static void LuaPush_Vector3(lua_State* L, Vector3 obj)
{
    lua_createtable(L, 0, 3);
    LuaPush_float(L, obj.x);
    lua_setfield(L, -2, "x");
    LuaPush_float(L, obj.y);
    lua_setfield(L, -2, "y");
    LuaPush_float(L, obj.z);
    lua_setfield(L, -2, "z");
}

static void LuaPush_RenderTexture2D(lua_State* L, RenderTexture2D obj)
{
    lua_createtable(L, 0, 3);
    LuaPush_unsigned(L, obj.int id);
    lua_setfield(L, -2, "int id");
    LuaPush_Texture2D(L, obj.texture);
    lua_setfield(L, -2, "texture");
    LuaPush_Texture2D(L, obj.depth);
    lua_setfield(L, -2, "depth");
}

static void LuaPush_SpriteFont(lua_State* L, SpriteFont obj)
{
    lua_createtable(L, 0, 4);
    LuaPush_Texture2D(L, obj.texture);
    lua_setfield(L, -2, "texture");
    LuaPush_int(L, obj.baseSize);
    lua_setfield(L, -2, "baseSize");
    LuaPush_int(L, obj.charsCount);
    lua_setfield(L, -2, "charsCount");
    LuaPush_CharInfo(L, obj.chars);
    lua_setfield(L, -2, "*chars");
}

static void LuaPush_BoundingBox(lua_State* L, BoundingBox obj)
{
    lua_createtable(L, 0, 2);
    LuaPush_Vector3(L, obj.min);
    lua_setfield(L, -2, "min");
    LuaPush_Vector3(L, obj.max);
    lua_setfield(L, -2, "max");
}

static void LuaPush_Mesh(lua_State* L, Mesh obj)
{
    lua_createtable(L, 0, 11);
    LuaPush_int(L, obj.vertexCount);
    lua_setfield(L, -2, "vertexCount");
    LuaPush_int(L, obj.triangleCount);
    lua_setfield(L, -2, "triangleCount");
    LuaPush_float(L, obj.vertices);
    lua_setfield(L, -2, "*vertices");
    LuaPush_float(L, obj.texcoords);
    lua_setfield(L, -2, "*texcoords");
    LuaPush_float(L, obj.texcoords2);
    lua_setfield(L, -2, "*texcoords2");
    LuaPush_float(L, obj.normals);
    lua_setfield(L, -2, "*normals");
    LuaPush_float(L, obj.tangents);
    lua_setfield(L, -2, "*tangents");
    LuaPush_unsigned(L, obj.char *colors);
    lua_setfield(L, -2, "char *colors");
    LuaPush_unsigned(L, obj.short *indices);
    lua_setfield(L, -2, "short *indices");
    LuaPush_unsigned(L, obj.int vaoId);
    lua_setfield(L, -2, "int vaoId");
    LuaPush_unsigned(L, obj.int vboId[7]);
    lua_setfield(L, -2, "int vboId[7]");
}

