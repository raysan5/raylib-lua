//----------------------------------------------------------------------------------
// Structures Definition
//----------------------------------------------------------------------------------
// Vector2 type
static Vector2 LuaGetArgument_Vector2(lua_State *L, int index)
{
    Vector2 result = { 0 };
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "x") == LUA_TNUMBER, index, "Expected Vector2.x");
    result.x = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "y") == LUA_TNUMBER, index, "Expected Vector2.y");
    result.y = LuaGetArgument_float(L, -1);
    lua_pop(L, 2);
    return result;
}

// Vector3 type
static Vector3 LuaGetArgument_Vector3(lua_State *L, int index)
{
    Vector3 result = { 0 };
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "x") == LUA_TNUMBER, index, "Expected Vector3.x");
    result.x = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "y") == LUA_TNUMBER, index, "Expected Vector3.y");
    result.y = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "z") == LUA_TNUMBER, index, "Expected Vector3.z");
    result.z = LuaGetArgument_float(L, -1);
    lua_pop(L, 3);
    return result;
}

// Vector4 type
static Vector4 LuaGetArgument_Vector4(lua_State *L, int index)
{
    Vector4 result = { 0 };
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "x") == LUA_TNUMBER, index, "Expected Vector4.x");
    result.x = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "y") == LUA_TNUMBER, index, "Expected Vector4.y");
    result.y = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "z") == LUA_TNUMBER, index, "Expected Vector4.z");
    result.z = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "w") == LUA_TNUMBER, index, "Expected Vector4.w");
    result.w = LuaGetArgument_float(L, -1);
    lua_pop(L, 4);
    return result;
}

// Quaternion type, same as Vector4
// Matrix type (OpenGL style 4x4 - right handed, column major)
static Matrix LuaGetArgument_Matrix(lua_State *L, int index)
{
    Matrix result = { 0 };
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "m0, m4, m8, m12") == LUA_TNUMBER, index, "Expected Matrix.m0, m4, m8, m12");
    result.m0, m4, m8, m12 = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "m1, m5, m9, m13") == LUA_TNUMBER, index, "Expected Matrix.m1, m5, m9, m13");
    result.m1, m5, m9, m13 = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "m2, m6, m10, m14") == LUA_TNUMBER, index, "Expected Matrix.m2, m6, m10, m14");
    result.m2, m6, m10, m14 = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "m3, m7, m11, m15") == LUA_TNUMBER, index, "Expected Matrix.m3, m7, m11, m15");
    result.m3, m7, m11, m15 = LuaGetArgument_float(L, -1);
    lua_pop(L, 4);
    return result;
}

// Color type, RGBA (32bit)
static Color LuaGetArgument_Color(lua_State *L, int index)
{
    Color result = { 0 };
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "char r") == LUA_TNUMBER, index, "Expected Color.char r");
    result.char r = LuaGetArgument_unsigned(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "char g") == LUA_TNUMBER, index, "Expected Color.char g");
    result.char g = LuaGetArgument_unsigned(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "char b") == LUA_TNUMBER, index, "Expected Color.char b");
    result.char b = LuaGetArgument_unsigned(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "char a") == LUA_TNUMBER, index, "Expected Color.char a");
    result.char a = LuaGetArgument_unsigned(L, -1);
    lua_pop(L, 4);
    return result;
}

// Rectangle type
static Rectangle LuaGetArgument_Rectangle(lua_State *L, int index)
{
    Rectangle result = { 0 };
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "x") == LUA_TNUMBER, index, "Expected Rectangle.x");
    result.x = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "y") == LUA_TNUMBER, index, "Expected Rectangle.y");
    result.y = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "width") == LUA_TNUMBER, index, "Expected Rectangle.width");
    result.width = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "height") == LUA_TNUMBER, index, "Expected Rectangle.height");
    result.height = LuaGetArgument_float(L, -1);
    lua_pop(L, 4);
    return result;
}

// Image type, bpp always RGBA (32bit)
// NOTE: Data stored in CPU memory (RAM)
static Image LuaGetArgument_Image(lua_State *L, int index)
{
    Image result = { 0 };
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "*data") == LUA_TNUMBER, index, "Expected Image.*data");
    result.*data = LuaGetArgument_void(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "width") == LUA_TNUMBER, index, "Expected Image.width");
    result.width = LuaGetArgument_int(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "height") == LUA_TNUMBER, index, "Expected Image.height");
    result.height = LuaGetArgument_int(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "mipmaps") == LUA_TNUMBER, index, "Expected Image.mipmaps");
    result.mipmaps = LuaGetArgument_int(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "format") == LUA_TNUMBER, index, "Expected Image.format");
    result.format = LuaGetArgument_int(L, -1);
    lua_pop(L, 5);
    return result;
}

// Texture2D type
// NOTE: Data stored in GPU memory
static Texture2D LuaGetArgument_Texture2D(lua_State *L, int index)
{
    Texture2D result = { 0 };
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "int id") == LUA_TNUMBER, index, "Expected Texture2D.int id");
    result.int id = LuaGetArgument_unsigned(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "width") == LUA_TNUMBER, index, "Expected Texture2D.width");
    result.width = LuaGetArgument_int(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "height") == LUA_TNUMBER, index, "Expected Texture2D.height");
    result.height = LuaGetArgument_int(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "mipmaps") == LUA_TNUMBER, index, "Expected Texture2D.mipmaps");
    result.mipmaps = LuaGetArgument_int(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "format") == LUA_TNUMBER, index, "Expected Texture2D.format");
    result.format = LuaGetArgument_int(L, -1);
    lua_pop(L, 5);
    return result;
}

// Texture type, same as Texture2D
// RenderTexture2D type, for texture rendering
static RenderTexture2D LuaGetArgument_RenderTexture2D(lua_State *L, int index)
{
    RenderTexture2D result = { 0 };
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "int id") == LUA_TNUMBER, index, "Expected RenderTexture2D.int id");
    result.int id = LuaGetArgument_unsigned(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "texture") == LUA_TNUMBER, index, "Expected RenderTexture2D.texture");
    result.texture = LuaGetArgument_Texture2D(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "depth") == LUA_TNUMBER, index, "Expected RenderTexture2D.depth");
    result.depth = LuaGetArgument_Texture2D(L, -1);
    lua_pop(L, 3);
    return result;
}

// RenderTexture type, same as RenderTexture2D
// Font character info
static CharInfo LuaGetArgument_CharInfo(lua_State *L, int index)
{
    CharInfo result = { 0 };
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "value") == LUA_TNUMBER, index, "Expected CharInfo.value");
    result.value = LuaGetArgument_int(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "rec") == LUA_TNUMBER, index, "Expected CharInfo.rec");
    result.rec = LuaGetArgument_Rectangle(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "offsetX") == LUA_TNUMBER, index, "Expected CharInfo.offsetX");
    result.offsetX = LuaGetArgument_int(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "offsetY") == LUA_TNUMBER, index, "Expected CharInfo.offsetY");
    result.offsetY = LuaGetArgument_int(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "advanceX") == LUA_TNUMBER, index, "Expected CharInfo.advanceX");
    result.advanceX = LuaGetArgument_int(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "char *data") == LUA_TNUMBER, index, "Expected CharInfo.char *data");
    result.char *data = LuaGetArgument_unsigned(L, -1);
    lua_pop(L, 6);
    return result;
}

// Font type, includes texture and charSet array data
static Font LuaGetArgument_Font(lua_State *L, int index)
{
    Font result = { 0 };
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "texture") == LUA_TNUMBER, index, "Expected Font.texture");
    result.texture = LuaGetArgument_Texture2D(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "baseSize") == LUA_TNUMBER, index, "Expected Font.baseSize");
    result.baseSize = LuaGetArgument_int(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "charsCount") == LUA_TNUMBER, index, "Expected Font.charsCount");
    result.charsCount = LuaGetArgument_int(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "*chars") == LUA_TNUMBER, index, "Expected Font.*chars");
    result.*chars = LuaGetArgument_CharInfo(L, -1);
    lua_pop(L, 4);
    return result;
}

// Camera type, defines a camera position/orientation in 3d space
static Camera3D LuaGetArgument_Camera3D(lua_State *L, int index)
{
    Camera3D result = { 0 };
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "position") == LUA_TNUMBER, index, "Expected Camera3D.position");
    result.position = LuaGetArgument_Vector3(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "target") == LUA_TNUMBER, index, "Expected Camera3D.target");
    result.target = LuaGetArgument_Vector3(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "up") == LUA_TNUMBER, index, "Expected Camera3D.up");
    result.up = LuaGetArgument_Vector3(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "fovy") == LUA_TNUMBER, index, "Expected Camera3D.fovy");
    result.fovy = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "type") == LUA_TNUMBER, index, "Expected Camera3D.type");
    result.type = LuaGetArgument_int(L, -1);
    lua_pop(L, 5);
    return result;
}

// Camera2D type, defines a 2d camera
static Camera2D LuaGetArgument_Camera2D(lua_State *L, int index)
{
    Camera2D result = { 0 };
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "offset") == LUA_TNUMBER, index, "Expected Camera2D.offset");
    result.offset = LuaGetArgument_Vector2(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "target") == LUA_TNUMBER, index, "Expected Camera2D.target");
    result.target = LuaGetArgument_Vector2(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "rotation") == LUA_TNUMBER, index, "Expected Camera2D.rotation");
    result.rotation = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "zoom") == LUA_TNUMBER, index, "Expected Camera2D.zoom");
    result.zoom = LuaGetArgument_float(L, -1);
    lua_pop(L, 4);
    return result;
}

// Bounding box type
static BoundingBox LuaGetArgument_BoundingBox(lua_State *L, int index)
{
    BoundingBox result = { 0 };
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "min") == LUA_TNUMBER, index, "Expected BoundingBox.min");
    result.min = LuaGetArgument_Vector3(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "max") == LUA_TNUMBER, index, "Expected BoundingBox.max");
    result.max = LuaGetArgument_Vector3(L, -1);
    lua_pop(L, 2);
    return result;
}

// Vertex data definning a mesh
// NOTE: Data stored in CPU memory (and GPU)
static Mesh LuaGetArgument_Mesh(lua_State *L, int index)
{
    Mesh result = { 0 };
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "vertexCount") == LUA_TNUMBER, index, "Expected Mesh.vertexCount");
    result.vertexCount = LuaGetArgument_int(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "triangleCount") == LUA_TNUMBER, index, "Expected Mesh.triangleCount");
    result.triangleCount = LuaGetArgument_int(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "*vertices") == LUA_TNUMBER, index, "Expected Mesh.*vertices");
    result.*vertices = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "*texcoords") == LUA_TNUMBER, index, "Expected Mesh.*texcoords");
    result.*texcoords = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "*texcoords2") == LUA_TNUMBER, index, "Expected Mesh.*texcoords2");
    result.*texcoords2 = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "*normals") == LUA_TNUMBER, index, "Expected Mesh.*normals");
    result.*normals = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "*tangents") == LUA_TNUMBER, index, "Expected Mesh.*tangents");
    result.*tangents = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "char *colors") == LUA_TNUMBER, index, "Expected Mesh.char *colors");
    result.char *colors = LuaGetArgument_unsigned(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "short *indices") == LUA_TNUMBER, index, "Expected Mesh.short *indices");
    result.short *indices = LuaGetArgument_unsigned(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "int vaoId") == LUA_TNUMBER, index, "Expected Mesh.int vaoId");
    result.int vaoId = LuaGetArgument_unsigned(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "int vboId[7]") == LUA_TNUMBER, index, "Expected Mesh.int vboId[7]");
    result.int vboId[7] = LuaGetArgument_unsigned(L, -1);
    lua_pop(L, 11);
    return result;
}

// Shader type (generic)
static Shader LuaGetArgument_Shader(lua_State *L, int index)
{
    Shader result = { 0 };
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "int id") == LUA_TNUMBER, index, "Expected Shader.int id");
    result.int id = LuaGetArgument_unsigned(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "locs[MAX_SHADER_LOCATIONS]") == LUA_TNUMBER, index, "Expected Shader.locs[MAX_SHADER_LOCATIONS]");
    result.locs[MAX_SHADER_LOCATIONS] = LuaGetArgument_int(L, -1);
    lua_pop(L, 2);
    return result;
}

// Material texture map
static MaterialMap LuaGetArgument_MaterialMap(lua_State *L, int index)
{
    MaterialMap result = { 0 };
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "texture") == LUA_TNUMBER, index, "Expected MaterialMap.texture");
    result.texture = LuaGetArgument_Texture2D(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "color") == LUA_TNUMBER, index, "Expected MaterialMap.color");
    result.color = LuaGetArgument_Color(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "value") == LUA_TNUMBER, index, "Expected MaterialMap.value");
    result.value = LuaGetArgument_float(L, -1);
    lua_pop(L, 3);
    return result;
}

// Material type (generic)
static Material LuaGetArgument_Material(lua_State *L, int index)
{
    Material result = { 0 };
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "shader") == LUA_TNUMBER, index, "Expected Material.shader");
    result.shader = LuaGetArgument_Shader(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "maps[MAX_MATERIAL_MAPS]") == LUA_TNUMBER, index, "Expected Material.maps[MAX_MATERIAL_MAPS]");
    result.maps[MAX_MATERIAL_MAPS] = LuaGetArgument_MaterialMap(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "*params") == LUA_TNUMBER, index, "Expected Material.*params");
    result.*params = LuaGetArgument_float(L, -1);
    lua_pop(L, 3);
    return result;
}

// Model type
static Model LuaGetArgument_Model(lua_State *L, int index)
{
    Model result = { 0 };
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "mesh") == LUA_TNUMBER, index, "Expected Model.mesh");
    result.mesh = LuaGetArgument_Mesh(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "transform") == LUA_TNUMBER, index, "Expected Model.transform");
    result.transform = LuaGetArgument_Matrix(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "material") == LUA_TNUMBER, index, "Expected Model.material");
    result.material = LuaGetArgument_Material(L, -1);
    lua_pop(L, 3);
    return result;
}

// Ray type (useful for raycast)
static Ray LuaGetArgument_Ray(lua_State *L, int index)
{
    Ray result = { 0 };
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "position") == LUA_TNUMBER, index, "Expected Ray.position");
    result.position = LuaGetArgument_Vector3(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "direction") == LUA_TNUMBER, index, "Expected Ray.direction");
    result.direction = LuaGetArgument_Vector3(L, -1);
    lua_pop(L, 2);
    return result;
}

// Raycast hit information
static RayHitInfo LuaGetArgument_RayHitInfo(lua_State *L, int index)
{
    RayHitInfo result = { 0 };
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "hit") == LUA_TNUMBER, index, "Expected RayHitInfo.hit");
    result.hit = LuaGetArgument_bool(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "distance") == LUA_TNUMBER, index, "Expected RayHitInfo.distance");
    result.distance = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "position") == LUA_TNUMBER, index, "Expected RayHitInfo.position");
    result.position = LuaGetArgument_Vector3(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "normal") == LUA_TNUMBER, index, "Expected RayHitInfo.normal");
    result.normal = LuaGetArgument_Vector3(L, -1);
    lua_pop(L, 4);
    return result;
}

// Wave type, defines audio wave data
static Wave LuaGetArgument_Wave(lua_State *L, int index)
{
    Wave result = { 0 };
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "int sampleCount") == LUA_TNUMBER, index, "Expected Wave.int sampleCount");
    result.int sampleCount = LuaGetArgument_unsigned(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "int sampleRate") == LUA_TNUMBER, index, "Expected Wave.int sampleRate");
    result.int sampleRate = LuaGetArgument_unsigned(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "int sampleSize") == LUA_TNUMBER, index, "Expected Wave.int sampleSize");
    result.int sampleSize = LuaGetArgument_unsigned(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "int channels") == LUA_TNUMBER, index, "Expected Wave.int channels");
    result.int channels = LuaGetArgument_unsigned(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "*data") == LUA_TNUMBER, index, "Expected Wave.*data");
    result.*data = LuaGetArgument_void(L, -1);
    lua_pop(L, 5);
    return result;
}

// Sound source type
static Sound LuaGetArgument_Sound(lua_State *L, int index)
{
    Sound result = { 0 };
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "*audioBuffer") == LUA_TNUMBER, index, "Expected Sound.*audioBuffer");
    result.*audioBuffer = LuaGetArgument_void(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "int source") == LUA_TNUMBER, index, "Expected Sound.int source");
    result.int source = LuaGetArgument_unsigned(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "int buffer") == LUA_TNUMBER, index, "Expected Sound.int buffer");
    result.int buffer = LuaGetArgument_unsigned(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "format") == LUA_TNUMBER, index, "Expected Sound.format");
    result.format = LuaGetArgument_int(L, -1);
    lua_pop(L, 4);
    return result;
}

// Music type (file streaming from memory)
// NOTE: Anything longer than ~10 seconds should be streamed
static MusicData LuaGetArgument_MusicData(lua_State *L, int index)
{
    MusicData result = { 0 };
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "Audio stream type
") == LUA_TNUMBER, index, "Expected MusicData.Audio stream type
");
    result.Audio stream type
 = LuaGetArgument_//(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "NOTE: Useful to create custom austruct AudioStream {
") == LUA_TNUMBER, index, "Expected MusicData.NOTE: Useful to create custom austruct AudioStream {
");
    result.NOTE: Useful to create custom austruct AudioStream {
 = LuaGetArgument_//(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "struct AudioStream {
") == LUA_TNUMBER, index, "Expected MusicData.struct AudioStream {
");
    result.struct AudioStream {
 = LuaGetArgument_typedef(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "int sampleRate") == LUA_TNUMBER, index, "Expected MusicData.int sampleRate");
    result.int sampleRate = LuaGetArgument_unsigned(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "int sampleSize") == LUA_TNUMBER, index, "Expected MusicData.int sampleSize");
    result.int sampleSize = LuaGetArgument_unsigned(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "int channels") == LUA_TNUMBER, index, "Expected MusicData.int channels");
    result.int channels = LuaGetArgument_unsigned(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "*audioBuffer") == LUA_TNUMBER, index, "Expected MusicData.*audioBuffer");
    result.*audioBuffer = LuaGetArgument_void(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "format") == LUA_TNUMBER, index, "Expected MusicData.format");
    result.format = LuaGetArgument_int(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "int source") == LUA_TNUMBER, index, "Expected MusicData.int source");
    result.int source = LuaGetArgument_unsigned(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "int buffers[2]") == LUA_TNUMBER, index, "Expected MusicData.int buffers[2]");
    result.int buffers[2] = LuaGetArgument_unsigned(L, -1);
    lua_pop(L, 10);
    return result;
}

// Head-Mounted-Display device parameters
static VrDeviceInfo LuaGetArgument_VrDeviceInfo(lua_State *L, int index)
{
    VrDeviceInfo result = { 0 };
    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values
    luaL_argcheck(L, lua_getfield(L, index, "hResolution") == LUA_TNUMBER, index, "Expected VrDeviceInfo.hResolution");
    result.hResolution = LuaGetArgument_int(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "vResolution") == LUA_TNUMBER, index, "Expected VrDeviceInfo.vResolution");
    result.vResolution = LuaGetArgument_int(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "hScreenSize") == LUA_TNUMBER, index, "Expected VrDeviceInfo.hScreenSize");
    result.hScreenSize = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "vScreenSize") == LUA_TNUMBER, index, "Expected VrDeviceInfo.vScreenSize");
    result.vScreenSize = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "vScreenCenter") == LUA_TNUMBER, index, "Expected VrDeviceInfo.vScreenCenter");
    result.vScreenCenter = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "eyeToScreenDistance") == LUA_TNUMBER, index, "Expected VrDeviceInfo.eyeToScreenDistance");
    result.eyeToScreenDistance = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "lensSeparationDistance") == LUA_TNUMBER, index, "Expected VrDeviceInfo.lensSeparationDistance");
    result.lensSeparationDistance = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "interpupillaryDistance") == LUA_TNUMBER, index, "Expected VrDeviceInfo.interpupillaryDistance");
    result.interpupillaryDistance = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "lensDistortionValues[4]") == LUA_TNUMBER, index, "Expected VrDeviceInfo.lensDistortionValues[4]");
    result.lensDistortionValues[4] = LuaGetArgument_float(L, -1);
    luaL_argcheck(L, lua_getfield(L, index, "chromaAbCorrection[4]") == LUA_TNUMBER, index, "Expected VrDeviceInfo.chromaAbCorrection[4]");
    result.chromaAbCorrection[4] = LuaGetArgument_float(L, -1);
    lua_pop(L, 10);
    return result;
}

//------------------------------------------------------------------------------------
// Global Variables Definition
//------------------------------------------------------------------------------------
// It's lonely here...
//------------------------------------------------------------------------------------
// Window and Graphics Device Functions (Module: core)
//------------------------------------------------------------------------------------
// Window-related functions
// Initialize window and OpenGL context
int lua_InitWindow(lua_State *L)
{
    int width = LuaGetArgument_int(L, 1);
    int height = LuaGetArgument_int(L, 2);
    const char title = LuaGetArgument_string(L, 3);
    InitWindow(width, height, title);
    return 0;
}

// Close window and unload OpenGL context
int lua_CloseWindow(lua_State *L)
{
    CloseWindow();
    return 0;
}

// Check if window has been initialized successfully
int lua_IsWindowReady(lua_State *L)
{
    bool result = IsWindowReady();
    LuaPush_bool(L, result);
    return 1;
}

// Check if KEY_ESCAPE pressed or Close icon pressed
int lua_WindowShouldClose(lua_State *L)
{
    bool result = WindowShouldClose();
    LuaPush_bool(L, result);
    return 1;
}

// Check if window has been minimized (or lost focus)
int lua_IsWindowMinimized(lua_State *L)
{
    bool result = IsWindowMinimized();
    LuaPush_bool(L, result);
    return 1;
}

// Toggle fullscreen mode (only PLATFORM_DESKTOP)
int lua_ToggleFullscreen(lua_State *L)
{
    ToggleFullscreen();
    return 0;
}

// Set icon for window (only PLATFORM_DESKTOP)
int lua_SetWindowIcon(lua_State *L)
{
    Image image = LuaGetArgument_Image(L, 1);
    SetWindowIcon(image);
    return 0;
}

// Set title for window (only PLATFORM_DESKTOP)
int lua_SetWindowTitle(lua_State *L)
{
    const char title = LuaGetArgument_string(L, 1);
    SetWindowTitle(title);
    return 0;
}

// Set window position on screen (only PLATFORM_DESKTOP)
int lua_SetWindowPosition(lua_State *L)
{
    int x = LuaGetArgument_int(L, 1);
    int y = LuaGetArgument_int(L, 2);
    SetWindowPosition(x, y);
    return 0;
}

// Set monitor for the current window (fullscreen mode)
int lua_SetWindowMonitor(lua_State *L)
{
    int monitor = LuaGetArgument_int(L, 1);
    SetWindowMonitor(monitor);
    return 0;
}

// Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
int lua_SetWindowMinSize(lua_State *L)
{
    int width = LuaGetArgument_int(L, 1);
    int height = LuaGetArgument_int(L, 2);
    SetWindowMinSize(width, height);
    return 0;
}

// Set window dimensions
int lua_SetWindowSize(lua_State *L)
{
    int width = LuaGetArgument_int(L, 1);
    int height = LuaGetArgument_int(L, 2);
    SetWindowSize(width, height);
    return 0;
}

// Get current screen width
int lua_GetScreenWidth(lua_State *L)
{
    int result = GetScreenWidth();
    LuaPush_int(L, result);
    return 1;
}

// Get current screen height
int lua_GetScreenHeight(lua_State *L)
{
    int result = GetScreenHeight();
    LuaPush_int(L, result);
    return 1;
}

// Cursor-related functions
// Shows cursor
int lua_ShowCursor(lua_State *L)
{
    ShowCursor();
    return 0;
}

// Hides cursor
int lua_HideCursor(lua_State *L)
{
    HideCursor();
    return 0;
}

// Check if cursor is not visible
int lua_IsCursorHidden(lua_State *L)
{
    bool result = IsCursorHidden();
    LuaPush_bool(L, result);
    return 1;
}

// Enables cursor (unlock cursor)
int lua_EnableCursor(lua_State *L)
{
    EnableCursor();
    return 0;
}

// Disables cursor (lock cursor)
int lua_DisableCursor(lua_State *L)
{
    DisableCursor();
    return 0;
}

// Drawing-related functions
// Set background color (framebuffer clear color)
int lua_ClearBackground(lua_State *L)
{
    Color color = LuaGetArgument_Color(L, 1);
    ClearBackground(color);
    return 0;
}

// Setup canvas (framebuffer) to start drawing
int lua_BeginDrawing(lua_State *L)
{
    BeginDrawing();
    return 0;
}

// End canvas drawing and swap buffers (double buffering)
int lua_EndDrawing(lua_State *L)
{
    EndDrawing();
    return 0;
}

// Initialize 2D mode with custom camera (2D)
int lua_BeginMode2D(lua_State *L)
{
    Camera2D camera = LuaGetArgument_Camera2D(L, 1);
    BeginMode2D(camera);
    return 0;
}

// Ends 2D mode with custom camera
int lua_EndMode2D(lua_State *L)
{
    EndMode2D();
    return 0;
}

// Initializes 3D mode with custom camera (3D)
int lua_BeginMode3D(lua_State *L)
{
    Camera3D camera = LuaGetArgument_Camera3D(L, 1);
    BeginMode3D(camera);
    return 0;
}

// Ends 3D mode and returns to default 2D orthographic mode
int lua_EndMode3D(lua_State *L)
{
    EndMode3D();
    return 0;
}

// Initializes render texture for drawing
int lua_BeginTextureMode(lua_State *L)
{
    RenderTexture2D target = LuaGetArgument_RenderTexture2D(L, 1);
    BeginTextureMode(target);
    return 0;
}

// Ends drawing to render texture
int lua_EndTextureMode(lua_State *L)
{
    EndTextureMode();
    return 0;
}

// Screen-space-related functions
// Returns a ray trace from mouse position
int lua_GetMouseRay(lua_State *L)
{
    Vector2 mousePosition = LuaGetArgument_Vector2(L, 1);
    Camera camera = LuaGetArgument_Camera(L, 2);
    Ray result = GetMouseRay(mousePosition, camera);
    LuaPush_Ray(L, result);
    return 1;
}

// Returns the screen space position for a 3d world space position
int lua_GetWorldToScreen(lua_State *L)
{
    Vector3 position = LuaGetArgument_Vector3(L, 1);
    Camera camera = LuaGetArgument_Camera(L, 2);
    Vector2 result = GetWorldToScreen(position, camera);
    LuaPush_Vector2(L, result);
    return 1;
}

// Returns camera transform matrix (view matrix)
int lua_GetCameraMatrix(lua_State *L)
{
    Camera camera = LuaGetArgument_Camera(L, 1);
    Matrix result = GetCameraMatrix(camera);
    LuaPush_Matrix(L, result);
    return 1;
}

// Timming-related functions
// Set target FPS (maximum)
int lua_SetTargetFPS(lua_State *L)
{
    int fps = LuaGetArgument_int(L, 1);
    SetTargetFPS(fps);
    return 0;
}

// Returns current FPS
int lua_GetFPS(lua_State *L)
{
    int result = GetFPS();
    LuaPush_int(L, result);
    return 1;
}

// Returns time in seconds for last frame drawn
int lua_GetFrameTime(lua_State *L)
{
    float result = GetFrameTime();
    LuaPush_float(L, result);
    return 1;
}

// Returns elapsed time in seconds since InitWindow()
int lua_GetTime(lua_State *L)
{
    double result = GetTime();
    LuaPush_double(L, result);
    return 1;
}

// Color-related functions
// Returns hexadecimal value for a Color
int lua_ColorToInt(lua_State *L)
{
    Color color = LuaGetArgument_Color(L, 1);
    int result = ColorToInt(color);
    LuaPush_int(L, result);
    return 1;
}

// Returns color normalized as float [0..1]
int lua_ColorNormalize(lua_State *L)
{
    Color color = LuaGetArgument_Color(L, 1);
    Vector4 result = ColorNormalize(color);
    LuaPush_Vector4(L, result);
    return 1;
}

// Returns HSV values for a Color
int lua_ColorToHSV(lua_State *L)
{
    Color color = LuaGetArgument_Color(L, 1);
    Vector3 result = ColorToHSV(color);
    LuaPush_Vector3(L, result);
    return 1;
}

// Returns a Color struct from hexadecimal value
int lua_GetColor(lua_State *L)
{
    int hexValue = LuaGetArgument_int(L, 1);
    Color result = GetColor(hexValue);
    LuaPush_Color(L, result);
    return 1;
}

// Color fade-in or fade-out, alpha goes from 0.0f to 1.0f
int lua_Fade(lua_State *L)
{
    Color color = LuaGetArgument_Color(L, 1);
    float alpha = LuaGetArgument_float(L, 2);
    Color result = Fade(color, alpha);
    LuaPush_Color(L, result);
    return 1;
}

// Misc. functions
// Activate raylib logo at startup (can be done with flags)
int lua_ShowLogo(lua_State *L)
{
    ShowLogo();
    return 0;
}

// Setup window configuration flags (view FLAGS)
int lua_SetConfigFlags(lua_State *L)
{
    unsigned char flags = LuaGetArgument_unsigned(L, 1);
    SetConfigFlags(flags);
    return 0;
}

// Enable trace log message types (bit flags based)
int lua_SetTraceLog(lua_State *L)
{
    unsigned char types = LuaGetArgument_unsigned(L, 1);
    SetTraceLog(types);
    return 0;
}


// Show trace log messages (LOG_INFO, LOG_WARNING, LOG_ERROR, LOG_DEBUG)
int lua_TraceLog(lua_State *L)
{
    int logType = LuaGetArgument_int(L, 1);
    const char text = LuaGetArgument_string(L, 2);
    ... title = LuaGetArgument_...(L, 3);
    TraceLog(logType, text, title);
    return 0;
}

// Takes a screenshot of current screen (saved a .png)
int lua_TakeScreenshot(lua_State *L)
{
    const char fileName = LuaGetArgument_string(L, 1);
    TakeScreenshot(fileName);
    return 0;
}

// Returns a random value between min and max (both included)
int lua_GetRandomValue(lua_State *L)
{
    int min = LuaGetArgument_int(L, 1);
    int max = LuaGetArgument_int(L, 2);
    int result = GetRandomValue(min, max);
    LuaPush_int(L, result);
    return 1;
}

// Files management functions
// Check file extension
int lua_IsFileExtension(lua_State *L)
{
    const char fileName = LuaGetArgument_string(L, 1);
    const char ext = LuaGetArgument_string(L, 2);
    bool result = IsFileExtension(fileName, ext);
    LuaPush_bool(L, result);
    return 1;
}

// Get pointer to extension for a filename string
int lua_GetExtension(lua_State *L)
{
    const char fileName = LuaGetArgument_string(L, 1);
    string result = GetExtension(fileName);
    LuaPush_string(L, result);
    return 1;
}

// Get pointer to filename for a path string
int lua_GetFileName(lua_State *L)
{
    const char filePath = LuaGetArgument_string(L, 1);
    string result = GetFileName(filePath);
    LuaPush_string(L, result);
    return 1;
}

// Get full path for a given fileName (uses static string)
int lua_GetDirectoryPath(lua_State *L)
{
    const char fileName = LuaGetArgument_string(L, 1);
    string result = GetDirectoryPath(fileName);
    LuaPush_string(L, result);
    return 1;
}

// Get current working directory (uses static string)
int lua_GetWorkingDirectory(lua_State *L)
{
    string result = GetWorkingDirectory();
    LuaPush_string(L, result);
    return 1;
}

// Change working directory, returns true if success
int lua_ChangeDirectory(lua_State *L)
{
    const char dir = LuaGetArgument_string(L, 1);
    bool result = ChangeDirectory(dir);
    LuaPush_bool(L, result);
    return 1;
}

// Check if a file has been dropped into window
int lua_IsFileDropped(lua_State *L)
{
    bool result = IsFileDropped();
    LuaPush_bool(L, result);
    return 1;
}

// Get dropped files names
int lua_GetDroppedFiles(lua_State *L)
{
    int count = LuaGetArgument_int(L, 1);
    char result = GetDroppedFiles(count);
    LuaPush_char(L, result);
    return 1;
}

// Clear dropped files paths buffer
int lua_ClearDroppedFiles(lua_State *L)
{
    ClearDroppedFiles();
    return 0;
}

// Persistent storage management
// Save integer value to storage file (to defined position)
int lua_StorageSaveValue(lua_State *L)
{
    int position = LuaGetArgument_int(L, 1);
    int value = LuaGetArgument_int(L, 2);
    StorageSaveValue(position, value);
    return 0;
}

// Load integer value from storage file (from defined position)
int lua_StorageLoadValue(lua_State *L)
{
    int position = LuaGetArgument_int(L, 1);
    int result = StorageLoadValue(position);
    LuaPush_int(L, result);
    return 1;
}

//------------------------------------------------------------------------------------
// Input Handling Functions (Module: core)
//------------------------------------------------------------------------------------
// Input-related functions: keyboard
// Detect if a key has been pressed once
int lua_IsKeyPressed(lua_State *L)
{
    int key = LuaGetArgument_int(L, 1);
    bool result = IsKeyPressed(key);
    LuaPush_bool(L, result);
    return 1;
}

// Detect if a key is being pressed
int lua_IsKeyDown(lua_State *L)
{
    int key = LuaGetArgument_int(L, 1);
    bool result = IsKeyDown(key);
    LuaPush_bool(L, result);
    return 1;
}

// Detect if a key has been released once
int lua_IsKeyReleased(lua_State *L)
{
    int key = LuaGetArgument_int(L, 1);
    bool result = IsKeyReleased(key);
    LuaPush_bool(L, result);
    return 1;
}

// Detect if a key is NOT being pressed
int lua_IsKeyUp(lua_State *L)
{
    int key = LuaGetArgument_int(L, 1);
    bool result = IsKeyUp(key);
    LuaPush_bool(L, result);
    return 1;
}

// Get latest key pressed
int lua_GetKeyPressed(lua_State *L)
{
    int result = GetKeyPressed();
    LuaPush_int(L, result);
    return 1;
}

// Set a custom key to exit program (default is ESC)
int lua_SetExitKey(lua_State *L)
{
    int key = LuaGetArgument_int(L, 1);
    SetExitKey(key);
    return 0;
}

// Input-related functions: gamepads
// Detect if a gamepad is available
int lua_IsGamepadAvailable(lua_State *L)
{
    int gamepad = LuaGetArgument_int(L, 1);
    bool result = IsGamepadAvailable(gamepad);
    LuaPush_bool(L, result);
    return 1;
}

// WARNING: Check gamepad name (if available)
int lua_IsGamepadName(lua_State *L)
{
    int gamepad = LuaGetArgument_int(L, 1);
    const char name = LuaGetArgument_string(L, 2);
    bool result = IsGamepadName(gamepad, name);
    LuaPush_bool(L, result);
    return 1;
}

// Return gamepad internal name id
int lua_GetGamepadName(lua_State *L)
{
    int gamepad = LuaGetArgument_int(L, 1);
    string result = GetGamepadName(gamepad);
    LuaPush_string(L, result);
    return 1;
}

// Detect if a gamepad button has been pressed once
int lua_IsGamepadButtonPressed(lua_State *L)
{
    int gamepad = LuaGetArgument_int(L, 1);
    int button = LuaGetArgument_int(L, 2);
    bool result = IsGamepadButtonPressed(gamepad, button);
    LuaPush_bool(L, result);
    return 1;
}

// Detect if a gamepad button is being pressed
int lua_IsGamepadButtonDown(lua_State *L)
{
    int gamepad = LuaGetArgument_int(L, 1);
    int button = LuaGetArgument_int(L, 2);
    bool result = IsGamepadButtonDown(gamepad, button);
    LuaPush_bool(L, result);
    return 1;
}

// Detect if a gamepad button has been released once
int lua_IsGamepadButtonReleased(lua_State *L)
{
    int gamepad = LuaGetArgument_int(L, 1);
    int button = LuaGetArgument_int(L, 2);
    bool result = IsGamepadButtonReleased(gamepad, button);
    LuaPush_bool(L, result);
    return 1;
}

// Detect if a gamepad button is NOT being pressed
int lua_IsGamepadButtonUp(lua_State *L)
{
    int gamepad = LuaGetArgument_int(L, 1);
    int button = LuaGetArgument_int(L, 2);
    bool result = IsGamepadButtonUp(gamepad, button);
    LuaPush_bool(L, result);
    return 1;
}

// Get the last gamepad button pressed
int lua_GetGamepadButtonPressed(lua_State *L)
{
    int result = GetGamepadButtonPressed();
    LuaPush_int(L, result);
    return 1;
}

// Return gamepad axis count for a gamepad
int lua_GetGamepadAxisCount(lua_State *L)
{
    int gamepad = LuaGetArgument_int(L, 1);
    int result = GetGamepadAxisCount(gamepad);
    LuaPush_int(L, result);
    return 1;
}

// Return axis movement value for a gamepad axis
int lua_GetGamepadAxisMovement(lua_State *L)
{
    int gamepad = LuaGetArgument_int(L, 1);
    int axis = LuaGetArgument_int(L, 2);
    float result = GetGamepadAxisMovement(gamepad, axis);
    LuaPush_float(L, result);
    return 1;
}

// Input-related functions: mouse
// Detect if a mouse button has been pressed once
int lua_IsMouseButtonPressed(lua_State *L)
{
    int button = LuaGetArgument_int(L, 1);
    bool result = IsMouseButtonPressed(button);
    LuaPush_bool(L, result);
    return 1;
}

// Detect if a mouse button is being pressed
int lua_IsMouseButtonDown(lua_State *L)
{
    int button = LuaGetArgument_int(L, 1);
    bool result = IsMouseButtonDown(button);
    LuaPush_bool(L, result);
    return 1;
}

// Detect if a mouse button has been released once
int lua_IsMouseButtonReleased(lua_State *L)
{
    int button = LuaGetArgument_int(L, 1);
    bool result = IsMouseButtonReleased(button);
    LuaPush_bool(L, result);
    return 1;
}

// Detect if a mouse button is NOT being pressed
int lua_IsMouseButtonUp(lua_State *L)
{
    int button = LuaGetArgument_int(L, 1);
    bool result = IsMouseButtonUp(button);
    LuaPush_bool(L, result);
    return 1;
}

// Returns mouse position X
int lua_GetMouseX(lua_State *L)
{
    int result = GetMouseX();
    LuaPush_int(L, result);
    return 1;
}

// Returns mouse position Y
int lua_GetMouseY(lua_State *L)
{
    int result = GetMouseY();
    LuaPush_int(L, result);
    return 1;
}

// Returns mouse position XY
int lua_GetMousePosition(lua_State *L)
{
    Vector2 result = GetMousePosition();
    LuaPush_Vector2(L, result);
    return 1;
}

// Set mouse position XY
int lua_SetMousePosition(lua_State *L)
{
    Vector2 position = LuaGetArgument_Vector2(L, 1);
    SetMousePosition(position);
    return 0;
}

// Set mouse scaling
int lua_SetMouseScale(lua_State *L)
{
    float scale = LuaGetArgument_float(L, 1);
    SetMouseScale(scale);
    return 0;
}

// Returns mouse wheel movement Y
int lua_GetMouseWheelMove(lua_State *L)
{
    int result = GetMouseWheelMove();
    LuaPush_int(L, result);
    return 1;
}

// Input-related functions: touch
// Returns touch position X for touch point 0 (relative to screen size)
int lua_GetTouchX(lua_State *L)
{
    int result = GetTouchX();
    LuaPush_int(L, result);
    return 1;
}

// Returns touch position Y for touch point 0 (relative to screen size)
int lua_GetTouchY(lua_State *L)
{
    int result = GetTouchY();
    LuaPush_int(L, result);
    return 1;
}

// Returns touch position XY for a touch point index (relative to screen size)
int lua_GetTouchPosition(lua_State *L)
{
    int index = LuaGetArgument_int(L, 1);
    Vector2 result = GetTouchPosition(index);
    LuaPush_Vector2(L, result);
    return 1;
}

//------------------------------------------------------------------------------------
// Gestures and Touch Handling Functions (Module: gestures)
//------------------------------------------------------------------------------------
// Enable a set of gestures using flags
int lua_SetGesturesEnabled(lua_State *L)
{
    unsigned int gestureFlags = LuaGetArgument_unsigned(L, 1);
    SetGesturesEnabled(gestureFlags);
    return 0;
}

// Check if a gesture have been detected
int lua_IsGestureDetected(lua_State *L)
{
    int gesture = LuaGetArgument_int(L, 1);
    bool result = IsGestureDetected(gesture);
    LuaPush_bool(L, result);
    return 1;
}

// Get latest detected gesture
int lua_GetGestureDetected(lua_State *L)
{
    int result = GetGestureDetected();
    LuaPush_int(L, result);
    return 1;
}

// Get touch points count
int lua_GetTouchPointsCount(lua_State *L)
{
    int result = GetTouchPointsCount();
    LuaPush_int(L, result);
    return 1;
}

// Get gesture hold time in milliseconds
int lua_GetGestureHoldDuration(lua_State *L)
{
    float result = GetGestureHoldDuration();
    LuaPush_float(L, result);
    return 1;
}

// Get gesture drag vector
int lua_GetGestureDragVector(lua_State *L)
{
    Vector2 result = GetGestureDragVector();
    LuaPush_Vector2(L, result);
    return 1;
}

// Get gesture drag angle
int lua_GetGestureDragAngle(lua_State *L)
{
    float result = GetGestureDragAngle();
    LuaPush_float(L, result);
    return 1;
}

// Get gesture pinch delta
int lua_GetGesturePinchVector(lua_State *L)
{
    Vector2 result = GetGesturePinchVector();
    LuaPush_Vector2(L, result);
    return 1;
}

// Get gesture pinch angle
int lua_GetGesturePinchAngle(lua_State *L)
{
    float result = GetGesturePinchAngle();
    LuaPush_float(L, result);
    return 1;
}

//------------------------------------------------------------------------------------
// Camera System Functions (Module: camera)
//------------------------------------------------------------------------------------
// Set camera mode (multiple camera modes available)
int lua_SetCameraMode(lua_State *L)
{
    Camera camera = LuaGetArgument_Camera(L, 1);
    int mode = LuaGetArgument_int(L, 2);
    SetCameraMode(camera, mode);
    return 0;
}

// Update camera position for selected mode
int lua_UpdateCamera(lua_State *L)
{
    Camera camera = LuaGetArgument_Camera(L, 1);
    UpdateCamera(camera);
    return 0;
}

// Set camera pan key to combine with mouse movement (free camera)
int lua_SetCameraPanControl(lua_State *L)
{
    int panKey = LuaGetArgument_int(L, 1);
    SetCameraPanControl(panKey);
    return 0;
}

// Set camera alt key to combine with mouse movement (free camera)
int lua_SetCameraAltControl(lua_State *L)
{
    int altKey = LuaGetArgument_int(L, 1);
    SetCameraAltControl(altKey);
    return 0;
}

// Set camera smooth zoom key to combine with mouse (free camera)
int lua_SetCameraSmoothZoomControl(lua_State *L)
{
    int szKey = LuaGetArgument_int(L, 1);
    SetCameraSmoothZoomControl(szKey);
    return 0;
}

// Set camera move controls (1st person and 3rd person cameras)
int lua_SetCameraMoveControls(lua_State *L)
{
    int frontKey = LuaGetArgument_int(L, 1);
    int backKey = LuaGetArgument_int(L, 2);
    int rightKey = LuaGetArgument_int(L, 3);
    int leftKey = LuaGetArgument_int(L, 4);
    int upKey = LuaGetArgument_int(L, 5);
    int downKey = LuaGetArgument_int(L, 6);
    SetCameraMoveControls(frontKey, backKey, rightKey, leftKey, upKey, downKey);
    return 0;
}

//------------------------------------------------------------------------------------
// Basic Shapes Drawing Functions (Module: shapes)
//------------------------------------------------------------------------------------
// Basic shapes drawing functions
// Draw a pixel
int lua_DrawPixel(lua_State *L)
{
    int posX = LuaGetArgument_int(L, 1);
    int posY = LuaGetArgument_int(L, 2);
    Color color = LuaGetArgument_Color(L, 3);
    DrawPixel(posX, posY, color);
    return 0;
}

// Draw a pixel (Vector version)
int lua_DrawPixelV(lua_State *L)
{
    Vector2 position = LuaGetArgument_Vector2(L, 1);
    Color color = LuaGetArgument_Color(L, 2);
    DrawPixelV(position, color);
    return 0;
}

// Draw a line
int lua_DrawLine(lua_State *L)
{
    int startPosX = LuaGetArgument_int(L, 1);
    int startPosY = LuaGetArgument_int(L, 2);
    int endPosX = LuaGetArgument_int(L, 3);
    int endPosY = LuaGetArgument_int(L, 4);
    Color color = LuaGetArgument_Color(L, 5);
    DrawLine(startPosX, startPosY, endPosX, endPosY, color);
    return 0;
}

// Draw a line (Vector version)
int lua_DrawLineV(lua_State *L)
{
    Vector2 startPos = LuaGetArgument_Vector2(L, 1);
    Vector2 endPos = LuaGetArgument_Vector2(L, 2);
    Color color = LuaGetArgument_Color(L, 3);
    DrawLineV(startPos, endPos, color);
    return 0;
}

// Draw a line defining thickness
int lua_DrawLineEx(lua_State *L)
{
    Vector2 startPos = LuaGetArgument_Vector2(L, 1);
    Vector2 endPos = LuaGetArgument_Vector2(L, 2);
    float thick = LuaGetArgument_float(L, 3);
    Color color = LuaGetArgument_Color(L, 4);
    DrawLineEx(startPos, endPos, thick, color);
    return 0;
}

// Draw a line using cubic-bezier curves in-out
int lua_DrawLineBezier(lua_State *L)
{
    Vector2 startPos = LuaGetArgument_Vector2(L, 1);
    Vector2 endPos = LuaGetArgument_Vector2(L, 2);
    float thick = LuaGetArgument_float(L, 3);
    Color color = LuaGetArgument_Color(L, 4);
    DrawLineBezier(startPos, endPos, thick, color);
    return 0;
}

// Draw a color-filled circle
int lua_DrawCircle(lua_State *L)
{
    int centerX = LuaGetArgument_int(L, 1);
    int centerY = LuaGetArgument_int(L, 2);
    float radius = LuaGetArgument_float(L, 3);
    Color color = LuaGetArgument_Color(L, 4);
    DrawCircle(centerX, centerY, radius, color);
    return 0;
}

// Draw a gradient-filled circle
int lua_DrawCircleGradient(lua_State *L)
{
    int centerX = LuaGetArgument_int(L, 1);
    int centerY = LuaGetArgument_int(L, 2);
    float radius = LuaGetArgument_float(L, 3);
    Color color1 = LuaGetArgument_Color(L, 4);
    Color color2 = LuaGetArgument_Color(L, 5);
    DrawCircleGradient(centerX, centerY, radius, color1, color2);
    return 0;
}

// Draw a color-filled circle (Vector version)
int lua_DrawCircleV(lua_State *L)
{
    Vector2 center = LuaGetArgument_Vector2(L, 1);
    float radius = LuaGetArgument_float(L, 2);
    Color color = LuaGetArgument_Color(L, 3);
    DrawCircleV(center, radius, color);
    return 0;
}

// Draw circle outline
int lua_DrawCircleLines(lua_State *L)
{
    int centerX = LuaGetArgument_int(L, 1);
    int centerY = LuaGetArgument_int(L, 2);
    float radius = LuaGetArgument_float(L, 3);
    Color color = LuaGetArgument_Color(L, 4);
    DrawCircleLines(centerX, centerY, radius, color);
    return 0;
}

// Draw a color-filled rectangle
int lua_DrawRectangle(lua_State *L)
{
    int posX = LuaGetArgument_int(L, 1);
    int posY = LuaGetArgument_int(L, 2);
    int width = LuaGetArgument_int(L, 3);
    int height = LuaGetArgument_int(L, 4);
    Color color = LuaGetArgument_Color(L, 5);
    DrawRectangle(posX, posY, width, height, color);
    return 0;
}

// Draw a color-filled rectangle (Vector version)
int lua_DrawRectangleV(lua_State *L)
{
    Vector2 position = LuaGetArgument_Vector2(L, 1);
    Vector2 size = LuaGetArgument_Vector2(L, 2);
    Color color = LuaGetArgument_Color(L, 3);
    DrawRectangleV(position, size, color);
    return 0;
}

// Draw a color-filled rectangle
int lua_DrawRectangleRec(lua_State *L)
{
    Rectangle rec = LuaGetArgument_Rectangle(L, 1);
    Color color = LuaGetArgument_Color(L, 2);
    DrawRectangleRec(rec, color);
    return 0;
}

// Draw a color-filled rectangle with pro parameters
int lua_DrawRectanglePro(lua_State *L)
{
    Rectangle rec = LuaGetArgument_Rectangle(L, 1);
    Vector2 origin = LuaGetArgument_Vector2(L, 2);
    float rotation = LuaGetArgument_float(L, 3);
    Color color = LuaGetArgument_Color(L, 4);
    DrawRectanglePro(rec, origin, rotation, color);
    return 0;
}

// Draw a vertical-gradient-filled rectangle
int lua_DrawRectangleGradientV(lua_State *L)
{
    int posX = LuaGetArgument_int(L, 1);
    int posY = LuaGetArgument_int(L, 2);
    int width = LuaGetArgument_int(L, 3);
    int height = LuaGetArgument_int(L, 4);
    Color color1 = LuaGetArgument_Color(L, 5);
    Color color2 = LuaGetArgument_Color(L, 6);
    DrawRectangleGradientV(posX, posY, width, height, color1, color2);
    return 0;
}

// Draw a horizontal-gradient-filled rectangle
int lua_DrawRectangleGradientH(lua_State *L)
{
    int posX = LuaGetArgument_int(L, 1);
    int posY = LuaGetArgument_int(L, 2);
    int width = LuaGetArgument_int(L, 3);
    int height = LuaGetArgument_int(L, 4);
    Color color1 = LuaGetArgument_Color(L, 5);
    Color color2 = LuaGetArgument_Color(L, 6);
    DrawRectangleGradientH(posX, posY, width, height, color1, color2);
    return 0;
}

// Draw a gradient-filled rectangle with custom vertex colors
int lua_DrawRectangleGradientEx(lua_State *L)
{
    Rectangle rec = LuaGetArgument_Rectangle(L, 1);
    Color col1 = LuaGetArgument_Color(L, 2);
    Color col2 = LuaGetArgument_Color(L, 3);
    Color col3 = LuaGetArgument_Color(L, 4);
    Color col4 = LuaGetArgument_Color(L, 5);
    DrawRectangleGradientEx(rec, col1, col2, col3, col4);
    return 0;
}

// Draw rectangle outline
int lua_DrawRectangleLines(lua_State *L)
{
    int posX = LuaGetArgument_int(L, 1);
    int posY = LuaGetArgument_int(L, 2);
    int width = LuaGetArgument_int(L, 3);
    int height = LuaGetArgument_int(L, 4);
    Color color = LuaGetArgument_Color(L, 5);
    DrawRectangleLines(posX, posY, width, height, color);
    return 0;
}

// Draw rectangle outline with extended parameters
int lua_DrawRectangleLinesEx(lua_State *L)
{
    Rectangle rec = LuaGetArgument_Rectangle(L, 1);
    int lineThick = LuaGetArgument_int(L, 2);
    Color color = LuaGetArgument_Color(L, 3);
    DrawRectangleLinesEx(rec, lineThick, color);
    return 0;
}

// Draw a color-filled triangle
int lua_DrawTriangle(lua_State *L)
{
    Vector2 v1 = LuaGetArgument_Vector2(L, 1);
    Vector2 v2 = LuaGetArgument_Vector2(L, 2);
    Vector2 v3 = LuaGetArgument_Vector2(L, 3);
    Color color = LuaGetArgument_Color(L, 4);
    DrawTriangle(v1, v2, v3, color);
    return 0;
}

// Draw triangle outline
int lua_DrawTriangleLines(lua_State *L)
{
    Vector2 v1 = LuaGetArgument_Vector2(L, 1);
    Vector2 v2 = LuaGetArgument_Vector2(L, 2);
    Vector2 v3 = LuaGetArgument_Vector2(L, 3);
    Color color = LuaGetArgument_Color(L, 4);
    DrawTriangleLines(v1, v2, v3, color);
    return 0;
}

// Draw a regular polygon (Vector version)
int lua_DrawPoly(lua_State *L)
{
    Vector2 center = LuaGetArgument_Vector2(L, 1);
    int sides = LuaGetArgument_int(L, 2);
    float radius = LuaGetArgument_float(L, 3);
    float rotation = LuaGetArgument_float(L, 4);
    Color color = LuaGetArgument_Color(L, 5);
    DrawPoly(center, sides, radius, rotation, color);
    return 0;
}

// Draw a closed polygon defined by points
int lua_DrawPolyEx(lua_State *L)
{
    Vector2 points = LuaGetArgument_Vector2(L, 1);
    int numPoints = LuaGetArgument_int(L, 2);
    Color color = LuaGetArgument_Color(L, 3);
    DrawPolyEx(points, numPoints, color);
    return 0;
}

// Draw polygon lines
int lua_DrawPolyExLines(lua_State *L)
{
    Vector2 points = LuaGetArgument_Vector2(L, 1);
    int numPoints = LuaGetArgument_int(L, 2);
    Color color = LuaGetArgument_Color(L, 3);
    DrawPolyExLines(points, numPoints, color);
    return 0;
}

// Basic shapes collision detection functions
// Check collision between two rectangles
int lua_CheckCollisionRecs(lua_State *L)
{
    Rectangle rec1 = LuaGetArgument_Rectangle(L, 1);
    Rectangle rec2 = LuaGetArgument_Rectangle(L, 2);
    bool result = CheckCollisionRecs(rec1, rec2);
    LuaPush_bool(L, result);
    return 1;
}

// Check collision between two circles
int lua_CheckCollisionCircles(lua_State *L)
{
    Vector2 center1 = LuaGetArgument_Vector2(L, 1);
    float radius1 = LuaGetArgument_float(L, 2);
    Vector2 center2 = LuaGetArgument_Vector2(L, 3);
    float radius2 = LuaGetArgument_float(L, 4);
    bool result = CheckCollisionCircles(center1, radius1, center2, radius2);
    LuaPush_bool(L, result);
    return 1;
}

// Check collision between circle and rectangle
int lua_CheckCollisionCircleRec(lua_State *L)
{
    Vector2 center = LuaGetArgument_Vector2(L, 1);
    float radius = LuaGetArgument_float(L, 2);
    Rectangle rec = LuaGetArgument_Rectangle(L, 3);
    bool result = CheckCollisionCircleRec(center, radius, rec);
    LuaPush_bool(L, result);
    return 1;
}

// Get collision rectangle for two rectangles collision
int lua_GetCollisionRec(lua_State *L)
{
    Rectangle rec1 = LuaGetArgument_Rectangle(L, 1);
    Rectangle rec2 = LuaGetArgument_Rectangle(L, 2);
    Rectangle result = GetCollisionRec(rec1, rec2);
    LuaPush_Rectangle(L, result);
    return 1;
}

// Check if point is inside rectangle
int lua_CheckCollisionPointRec(lua_State *L)
{
    Vector2 point = LuaGetArgument_Vector2(L, 1);
    Rectangle rec = LuaGetArgument_Rectangle(L, 2);
    bool result = CheckCollisionPointRec(point, rec);
    LuaPush_bool(L, result);
    return 1;
}

// Check if point is inside circle
int lua_CheckCollisionPointCircle(lua_State *L)
{
    Vector2 point = LuaGetArgument_Vector2(L, 1);
    Vector2 center = LuaGetArgument_Vector2(L, 2);
    float radius = LuaGetArgument_float(L, 3);
    bool result = CheckCollisionPointCircle(point, center, radius);
    LuaPush_bool(L, result);
    return 1;
}

// Check if point is inside a triangle
int lua_CheckCollisionPointTriangle(lua_State *L)
{
    Vector2 point = LuaGetArgument_Vector2(L, 1);
    Vector2 p1 = LuaGetArgument_Vector2(L, 2);
    Vector2 p2 = LuaGetArgument_Vector2(L, 3);
    Vector2 p3 = LuaGetArgument_Vector2(L, 4);
    bool result = CheckCollisionPointTriangle(point, p1, p2, p3);
    LuaPush_bool(L, result);
    return 1;
}

//------------------------------------------------------------------------------------
// Texture Loading and Drawing Functions (Module: textures)
//------------------------------------------------------------------------------------
// Image/Texture2D data loading/unloading/saving functions
// Load image from file into CPU memory (RAM)
int lua_LoadImage(lua_State *L)
{
    const char fileName = LuaGetArgument_string(L, 1);
    Image result = LoadImage(fileName);
    LuaPush_Image(L, result);
    return 1;
}

// Load image from Color array data (RGBA - 32bit)
int lua_LoadImageEx(lua_State *L)
{
    Color pixels = LuaGetArgument_Color(L, 1);
    int width = LuaGetArgument_int(L, 2);
    int height = LuaGetArgument_int(L, 3);
    Image result = LoadImageEx(pixels, width, height);
    LuaPush_Image(L, result);
    return 1;
}

// Load image from raw data with parameters
int lua_LoadImagePro(lua_State *L)
{
    Image result = LoadImagePro();
    LuaPush_Image(L, result);
    return 1;
}

// Load image from RAW file data
int lua_LoadImageRaw(lua_State *L)
{
    const char fileName = LuaGetArgument_string(L, 1);
    int width = LuaGetArgument_int(L, 2);
    int height = LuaGetArgument_int(L, 3);
    int format = LuaGetArgument_int(L, 4);
    int headerSize = LuaGetArgument_int(L, 5);
    Image result = LoadImageRaw(fileName, width, height, format, headerSize);
    LuaPush_Image(L, result);
    return 1;
}

// Export image as a PNG file
int lua_ExportImage(lua_State *L)
{
    const char fileName = LuaGetArgument_string(L, 1);
    Image image = LuaGetArgument_Image(L, 2);
    ExportImage(fileName, image);
    return 0;
}

// Load texture from file into GPU memory (VRAM)
int lua_LoadTexture(lua_State *L)
{
    const char fileName = LuaGetArgument_string(L, 1);
    Texture2D result = LoadTexture(fileName);
    LuaPush_Texture2D(L, result);
    return 1;
}

// Load texture from image data
int lua_LoadTextureFromImage(lua_State *L)
{
    Image image = LuaGetArgument_Image(L, 1);
    Texture2D result = LoadTextureFromImage(image);
    LuaPush_Texture2D(L, result);
    return 1;
}

// Load texture for rendering (framebuffer)
int lua_LoadRenderTexture(lua_State *L)
{
    int width = LuaGetArgument_int(L, 1);
    int height = LuaGetArgument_int(L, 2);
    RenderTexture2D result = LoadRenderTexture(width, height);
    LuaPush_RenderTexture2D(L, result);
    return 1;
}

// Unload image from CPU memory (RAM)
int lua_UnloadImage(lua_State *L)
{
    Image image = LuaGetArgument_Image(L, 1);
    UnloadImage(image);
    return 0;
}

// Unload texture from GPU memory (VRAM)
int lua_UnloadTexture(lua_State *L)
{
    Texture2D texture = LuaGetArgument_Texture2D(L, 1);
    UnloadTexture(texture);
    return 0;
}

// Unload render texture from GPU memory (VRAM)
int lua_UnloadRenderTexture(lua_State *L)
{
    RenderTexture2D target = LuaGetArgument_RenderTexture2D(L, 1);
    UnloadRenderTexture(target);
    return 0;
}

// Get pixel data from image as a Color struct array
int lua_GetImageData(lua_State *L)
{
    Image image = LuaGetArgument_Image(L, 1);
    Color result = GetImageData(image);
    LuaPush_Color(L, result);
    return 1;
}

// Get pixel data from image as Vector4 array (float normalized)
int lua_GetImageDataNormalized(lua_State *L)
{
    Image image = LuaGetArgument_Image(L, 1);
    Vector4 result = GetImageDataNormalized(image);
    LuaPush_Vector4(L, result);
    return 1;
}

// Get pixel data size in bytes (image or texture)
int lua_GetPixelDataSize(lua_State *L)
{
    int width = LuaGetArgument_int(L, 1);
    int height = LuaGetArgument_int(L, 2);
    int format = LuaGetArgument_int(L, 3);
    int result = GetPixelDataSize(width, height, format);
    LuaPush_int(L, result);
    return 1;
}

// Get pixel data from GPU texture and return an Image
int lua_GetTextureData(lua_State *L)
{
    Texture2D texture = LuaGetArgument_Texture2D(L, 1);
    Image result = GetTextureData(texture);
    LuaPush_Image(L, result);
    return 1;
}

// Update GPU texture with new data
int lua_UpdateTexture(lua_State *L)
{
    Texture2D texture = LuaGetArgument_Texture2D(L, 1);
    const void pixels = LuaGetArgument_void(L, 2);
    UpdateTexture(texture, pixels);
    return 0;
}

// Image manipulation functions
// Create an image duplicate (useful for transformations)
int lua_ImageCopy(lua_State *L)
{
    Image image = LuaGetArgument_Image(L, 1);
    Image result = ImageCopy(image);
    LuaPush_Image(L, result);
    return 1;
}

// Convert image to POT (power-of-two)
int lua_ImageToPOT(lua_State *L)
{
    Image image = LuaGetArgument_Image(L, 1);
    Color fillColor = LuaGetArgument_Color(L, 2);
    ImageToPOT(image, fillColor);
    return 0;
}

// Convert image data to desired format
int lua_ImageFormat(lua_State *L)
{
    Image image = LuaGetArgument_Image(L, 1);
    int newFormat = LuaGetArgument_int(L, 2);
    ImageFormat(image, newFormat);
    return 0;
}

// Apply alpha mask to image
int lua_ImageAlphaMask(lua_State *L)
{
    Image image = LuaGetArgument_Image(L, 1);
    Image alphaMask = LuaGetArgument_Image(L, 2);
    ImageAlphaMask(image, alphaMask);
    return 0;
}

// Clear alpha channel to desired color
int lua_ImageAlphaClear(lua_State *L)
{
    Image image = LuaGetArgument_Image(L, 1);
    Color color = LuaGetArgument_Color(L, 2);
    float threshold = LuaGetArgument_float(L, 3);
    ImageAlphaClear(image, color, threshold);
    return 0;
}

// Crop image depending on alpha value
int lua_ImageAlphaCrop(lua_State *L)
{
    Image image = LuaGetArgument_Image(L, 1);
    float threshold = LuaGetArgument_float(L, 2);
    ImageAlphaCrop(image, threshold);
    return 0;
}

// Premultiply alpha channel
int lua_ImageAlphaPremultiply(lua_State *L)
{
    Image image = LuaGetArgument_Image(L, 1);
    ImageAlphaPremultiply(image);
    return 0;
}

// Crop an image to a defined rectangle
int lua_ImageCrop(lua_State *L)
{
    Image image = LuaGetArgument_Image(L, 1);
    Rectangle crop = LuaGetArgument_Rectangle(L, 2);
    ImageCrop(image, crop);
    return 0;
}

// Resize image (bilinear filtering)
int lua_ImageResize(lua_State *L)
{
    Image image = LuaGetArgument_Image(L, 1);
    int newWidth = LuaGetArgument_int(L, 2);
    int newHeight = LuaGetArgument_int(L, 3);
    ImageResize(image, newWidth, newHeight);
    return 0;
}

// Resize image (Nearest-Neighbor scaling algorithm)
int lua_ImageResizeNN(lua_State *L)
{
    Image image = LuaGetArgument_Image(L, 1);
    int newWidth = LuaGetArgument_int(L, 2);
    int newHeight = LuaGetArgument_int(L, 3);
    ImageResizeNN(image, newWidth, newHeight);
    return 0;
}

// Resize canvas and fill with color
int lua_ImageResizeCanvas(lua_State *L)
{
    Image image = LuaGetArgument_Image(L, 1);
    int newWidth = LuaGetArgument_int(L, 2);
    int newHeight = LuaGetArgument_int(L, 3);
    int offsetX = LuaGetArgument_int(L, 4);
    int offsetY = LuaGetArgument_int(L, 5);
    Color color = LuaGetArgument_Color(L, 6);
    ImageResizeCanvas(image, newWidth, newHeight, offsetX, offsetY, color);
    return 0;
}

// Generate all mipmap levels for a provided image
int lua_ImageMipmaps(lua_State *L)
{
    Image image = LuaGetArgument_Image(L, 1);
    ImageMipmaps(image);
    return 0;
}

// Dither image data to 16bpp or lower (Floyd-Steinberg dithering)
int lua_ImageDither(lua_State *L)
{
    Image image = LuaGetArgument_Image(L, 1);
    int rBpp = LuaGetArgument_int(L, 2);
    int gBpp = LuaGetArgument_int(L, 3);
    int bBpp = LuaGetArgument_int(L, 4);
    int aBpp = LuaGetArgument_int(L, 5);
    ImageDither(image, rBpp, gBpp, bBpp, aBpp);
    return 0;
}

// Create an image from text (default font)
int lua_ImageText(lua_State *L)
{
    const char text = LuaGetArgument_string(L, 1);
    int fontSize = LuaGetArgument_int(L, 2);
    Color color = LuaGetArgument_Color(L, 3);
    Image result = ImageText(text, fontSize, color);
    LuaPush_Image(L, result);
    return 1;
}

// Create an image from text (custom sprite font)
int lua_ImageTextEx(lua_State *L)
{
    Font font = LuaGetArgument_Font(L, 1);
    const char text = LuaGetArgument_string(L, 2);
    float fontSize = LuaGetArgument_float(L, 3);
    float spacing = LuaGetArgument_float(L, 4);
    Color tint = LuaGetArgument_Color(L, 5);
    Image result = ImageTextEx(font, text, fontSize, spacing, tint);
    LuaPush_Image(L, result);
    return 1;
}

// Draw a source image within a destination image
int lua_ImageDraw(lua_State *L)
{
    Image dst = LuaGetArgument_Image(L, 1);
    Image src = LuaGetArgument_Image(L, 2);
    Rectangle srcRec = LuaGetArgument_Rectangle(L, 3);
    Rectangle dstRec = LuaGetArgument_Rectangle(L, 4);
    ImageDraw(dst, src, srcRec, dstRec);
    return 0;
}

// Draw rectangle within an image
int lua_ImageDrawRectangle(lua_State *L)
{
    Image dst = LuaGetArgument_Image(L, 1);
    Vector2 position = LuaGetArgument_Vector2(L, 2);
    Rectangle rec = LuaGetArgument_Rectangle(L, 3);
    Color color = LuaGetArgument_Color(L, 4);
    ImageDrawRectangle(dst, position, rec, color);
    return 0;
}

// Draw text (default font) within an image (destination)
int lua_ImageDrawText(lua_State *L)
{
    Image dst = LuaGetArgument_Image(L, 1);
    Vector2 position = LuaGetArgument_Vector2(L, 2);
    const char text = LuaGetArgument_string(L, 3);
    int fontSize = LuaGetArgument_int(L, 4);
    Color color = LuaGetArgument_Color(L, 5);
    ImageDrawText(dst, position, text, fontSize, color);
    return 0;
}

// Draw text (custom sprite font) within an image (destination)
int lua_ImageDrawTextEx(lua_State *L)
{
    Image dst = LuaGetArgument_Image(L, 1);
    Vector2 position = LuaGetArgument_Vector2(L, 2);
    Font font = LuaGetArgument_Font(L, 3);
    const char text = LuaGetArgument_string(L, 4);
    float fontSize = LuaGetArgument_float(L, 5);
    float spacing = LuaGetArgument_float(L, 6);
    Color color = LuaGetArgument_Color(L, 7);
    ImageDrawTextEx(dst, position, font, text, fontSize, spacing, color);
    return 0;
}

// Flip image vertically
int lua_ImageFlipVertical(lua_State *L)
{
    Image image = LuaGetArgument_Image(L, 1);
    ImageFlipVertical(image);
    return 0;
}

// Flip image horizontally
int lua_ImageFlipHorizontal(lua_State *L)
{
    Image image = LuaGetArgument_Image(L, 1);
    ImageFlipHorizontal(image);
    return 0;
}

// Rotate image clockwise 90deg
int lua_ImageRotateCW(lua_State *L)
{
    Image image = LuaGetArgument_Image(L, 1);
    ImageRotateCW(image);
    return 0;
}

// Rotate image counter-clockwise 90deg
int lua_ImageRotateCCW(lua_State *L)
{
    Image image = LuaGetArgument_Image(L, 1);
    ImageRotateCCW(image);
    return 0;
}

// Modify image color: tint
int lua_ImageColorTint(lua_State *L)
{
    Image image = LuaGetArgument_Image(L, 1);
    Color color = LuaGetArgument_Color(L, 2);
    ImageColorTint(image, color);
    return 0;
}

// Modify image color: invert
int lua_ImageColorInvert(lua_State *L)
{
    Image image = LuaGetArgument_Image(L, 1);
    ImageColorInvert(image);
    return 0;
}

// Modify image color: grayscale
int lua_ImageColorGrayscale(lua_State *L)
{
    Image image = LuaGetArgument_Image(L, 1);
    ImageColorGrayscale(image);
    return 0;
}

// Modify image color: contrast (-100 to 100)
int lua_ImageColorContrast(lua_State *L)
{
    Image image = LuaGetArgument_Image(L, 1);
    float contrast = LuaGetArgument_float(L, 2);
    ImageColorContrast(image, contrast);
    return 0;
}

// Modify image color: brightness (-255 to 255)
int lua_ImageColorBrightness(lua_State *L)
{
    Image image = LuaGetArgument_Image(L, 1);
    int brightness = LuaGetArgument_int(L, 2);
    ImageColorBrightness(image, brightness);
    return 0;
}

// Modify image color: replace color
int lua_ImageColorReplace(lua_State *L)
{
    Image image = LuaGetArgument_Image(L, 1);
    Color color = LuaGetArgument_Color(L, 2);
    Color replace = LuaGetArgument_Color(L, 3);
    ImageColorReplace(image, color, replace);
    return 0;
}

// Image generation functions
// Generate image: plain color
int lua_GenImageColor(lua_State *L)
{
    int width = LuaGetArgument_int(L, 1);
    int height = LuaGetArgument_int(L, 2);
    Color color = LuaGetArgument_Color(L, 3);
    Image result = GenImageColor(width, height, color);
    LuaPush_Image(L, result);
    return 1;
}

// Generate image: vertical gradient
int lua_GenImageGradientV(lua_State *L)
{
    int width = LuaGetArgument_int(L, 1);
    int height = LuaGetArgument_int(L, 2);
    Color top = LuaGetArgument_Color(L, 3);
    Color bottom = LuaGetArgument_Color(L, 4);
    Image result = GenImageGradientV(width, height, top, bottom);
    LuaPush_Image(L, result);
    return 1;
}

// Generate image: horizontal gradient
int lua_GenImageGradientH(lua_State *L)
{
    int width = LuaGetArgument_int(L, 1);
    int height = LuaGetArgument_int(L, 2);
    Color left = LuaGetArgument_Color(L, 3);
    Color right = LuaGetArgument_Color(L, 4);
    Image result = GenImageGradientH(width, height, left, right);
    LuaPush_Image(L, result);
    return 1;
}

// Generate image: radial gradient
int lua_GenImageGradientRadial(lua_State *L)
{
    int width = LuaGetArgument_int(L, 1);
    int height = LuaGetArgument_int(L, 2);
    float density = LuaGetArgument_float(L, 3);
    Color inner = LuaGetArgument_Color(L, 4);
    Color outer = LuaGetArgument_Color(L, 5);
    Image result = GenImageGradientRadial(width, height, density, inner, outer);
    LuaPush_Image(L, result);
    return 1;
}

// Generate image: checked
int lua_GenImageChecked(lua_State *L)
{
    int width = LuaGetArgument_int(L, 1);
    int height = LuaGetArgument_int(L, 2);
    int checksX = LuaGetArgument_int(L, 3);
    int checksY = LuaGetArgument_int(L, 4);
    Color col1 = LuaGetArgument_Color(L, 5);
    Color col2 = LuaGetArgument_Color(L, 6);
    Image result = GenImageChecked(width, height, checksX, checksY, col1, col2);
    LuaPush_Image(L, result);
    return 1;
}

// Generate image: white noise
int lua_GenImageWhiteNoise(lua_State *L)
{
    int width = LuaGetArgument_int(L, 1);
    int height = LuaGetArgument_int(L, 2);
    float factor = LuaGetArgument_float(L, 3);
    Image result = GenImageWhiteNoise(width, height, factor);
    LuaPush_Image(L, result);
    return 1;
}

// Generate image: perlin noise
int lua_GenImagePerlinNoise(lua_State *L)
{
    int width = LuaGetArgument_int(L, 1);
    int height = LuaGetArgument_int(L, 2);
    int offsetX = LuaGetArgument_int(L, 3);
    int offsetY = LuaGetArgument_int(L, 4);
    float scale = LuaGetArgument_float(L, 5);
    Image result = GenImagePerlinNoise(width, height, offsetX, offsetY, scale);
    LuaPush_Image(L, result);
    return 1;
}

// Generate image: cellular algorithm. Bigger tileSize means bigger cells
int lua_GenImageCellular(lua_State *L)
{
    int width = LuaGetArgument_int(L, 1);
    int height = LuaGetArgument_int(L, 2);
    int tileSize = LuaGetArgument_int(L, 3);
    Image result = GenImageCellular(width, height, tileSize);
    LuaPush_Image(L, result);
    return 1;
}

// Texture2D configuration functions
// Generate GPU mipmaps for a texture
int lua_GenTextureMipmaps(lua_State *L)
{
    Texture2D texture = LuaGetArgument_Texture2D(L, 1);
    GenTextureMipmaps(texture);
    return 0;
}

// Set texture scaling filter mode
int lua_SetTextureFilter(lua_State *L)
{
    Texture2D texture = LuaGetArgument_Texture2D(L, 1);
    int filterMode = LuaGetArgument_int(L, 2);
    SetTextureFilter(texture, filterMode);
    return 0;
}

// Set texture wrapping mode
int lua_SetTextureWrap(lua_State *L)
{
    Texture2D texture = LuaGetArgument_Texture2D(L, 1);
    int wrapMode = LuaGetArgument_int(L, 2);
    SetTextureWrap(texture, wrapMode);
    return 0;
}

// Texture2D drawing functions
// Draw a Texture2D
int lua_DrawTexture(lua_State *L)
{
    Texture2D texture = LuaGetArgument_Texture2D(L, 1);
    int posX = LuaGetArgument_int(L, 2);
    int posY = LuaGetArgument_int(L, 3);
    Color tint = LuaGetArgument_Color(L, 4);
    DrawTexture(texture, posX, posY, tint);
    return 0;
}

// Draw a Texture2D with position defined as Vector2
int lua_DrawTextureV(lua_State *L)
{
    Texture2D texture = LuaGetArgument_Texture2D(L, 1);
    Vector2 position = LuaGetArgument_Vector2(L, 2);
    Color tint = LuaGetArgument_Color(L, 3);
    DrawTextureV(texture, position, tint);
    return 0;
}

// Draw a Texture2D with extended parameters
int lua_DrawTextureEx(lua_State *L)
{
    Texture2D texture = LuaGetArgument_Texture2D(L, 1);
    Vector2 position = LuaGetArgument_Vector2(L, 2);
    float rotation = LuaGetArgument_float(L, 3);
    float scale = LuaGetArgument_float(L, 4);
    Color tint = LuaGetArgument_Color(L, 5);
    DrawTextureEx(texture, position, rotation, scale, tint);
    return 0;
}

// Draw a part of a texture defined by a rectangle
int lua_DrawTextureRec(lua_State *L)
{
    Texture2D texture = LuaGetArgument_Texture2D(L, 1);
    Rectangle sourceRec = LuaGetArgument_Rectangle(L, 2);
    Vector2 position = LuaGetArgument_Vector2(L, 3);
    Color tint = LuaGetArgument_Color(L, 4);
    DrawTextureRec(texture, sourceRec, position, tint);
    return 0;
}

// Draw a part of a texture defined by a rectangle with 'pro' parameters
int lua_DrawTexturePro(lua_State *L)
{
    Texture2D texture = LuaGetArgument_Texture2D(L, 1);
    Rectangle sourceRec = LuaGetArgument_Rectangle(L, 2);
    Rectangle destRec = LuaGetArgument_Rectangle(L, 3);
    Vector2 origin = LuaGetArgument_Vector2(L, 4);
    float rotation = LuaGetArgument_float(L, 5);
    Color tint = LuaGetArgument_Color(L, 6);
    DrawTexturePro(texture, sourceRec, destRec, origin, rotation, tint);
    return 0;
}

//------------------------------------------------------------------------------------
// Font Loading and Text Drawing Functions (Module: text)
//------------------------------------------------------------------------------------
// Font loading/unloading functions
// Get the default Font
int lua_GetFontDefault(lua_State *L)
{
    Font result = GetFontDefault();
    LuaPush_Font(L, result);
    return 1;
}

// Load font from file into GPU memory (VRAM)
int lua_LoadFont(lua_State *L)
{
    const char fileName = LuaGetArgument_string(L, 1);
    Font result = LoadFont(fileName);
    LuaPush_Font(L, result);
    return 1;
}

// Load font from file with extended parameters
int lua_LoadFontEx(lua_State *L)
{
    const char fileName = LuaGetArgument_string(L, 1);
    int fontSize = LuaGetArgument_int(L, 2);
    int charsCount = LuaGetArgument_int(L, 3);
    int fontChars = LuaGetArgument_int(L, 4);
    Font result = LoadFontEx(fileName, fontSize, charsCount, fontChars);
    LuaPush_Font(L, result);
    return 1;
}

// Load font data for further use
int lua_LoadFontData(lua_State *L)
{
    const char fileName = LuaGetArgument_string(L, 1);
    int fontSize = LuaGetArgument_int(L, 2);
    int fontChars = LuaGetArgument_int(L, 3);
    int charsCount = LuaGetArgument_int(L, 4);
    bool sdf = LuaGetArgument_bool(L, 5);
    CharInfo result = LoadFontData(fileName, fontSize, fontChars, charsCount, sdf);
    LuaPush_CharInfo(L, result);
    return 1;
}

// Generate image font atlas using chars info
int lua_GenImageFontAtlas(lua_State *L)
{
    CharInfo chars = LuaGetArgument_CharInfo(L, 1);
    int fontSize = LuaGetArgument_int(L, 2);
    int charsCount = LuaGetArgument_int(L, 3);
    int padding = LuaGetArgument_int(L, 4);
    int packMethod = LuaGetArgument_int(L, 5);
    Image result = GenImageFontAtlas(chars, fontSize, charsCount, padding, packMethod);
    LuaPush_Image(L, result);
    return 1;
}

// Unload Font from GPU memory (VRAM)
int lua_UnloadFont(lua_State *L)
{
    Font font = LuaGetArgument_Font(L, 1);
    UnloadFont(font);
    return 0;
}

// Text drawing functions
// Shows current FPS
int lua_DrawFPS(lua_State *L)
{
    int posX = LuaGetArgument_int(L, 1);
    int posY = LuaGetArgument_int(L, 2);
    DrawFPS(posX, posY);
    return 0;
}

// Draw text (using default font)
int lua_DrawText(lua_State *L)
{
    const char text = LuaGetArgument_string(L, 1);
    int posX = LuaGetArgument_int(L, 2);
    int posY = LuaGetArgument_int(L, 3);
    int fontSize = LuaGetArgument_int(L, 4);
    Color color = LuaGetArgument_Color(L, 5);
    DrawText(text, posX, posY, fontSize, color);
    return 0;
}

// Draw text using font and additional parameters
int lua_DrawTextEx(lua_State *L)
{
    Font font = LuaGetArgument_Font(L, 1);
    const char* text = LuaGetArgument_char*(L, 2);
    Vector2 position = LuaGetArgument_Vector2(L, 3);
    float fontSize = LuaGetArgument_float(L, 4);
    float spacing = LuaGetArgument_float(L, 5);
    Color tint = LuaGetArgument_Color(L, 6);
    DrawTextEx(font, text, position, fontSize, spacing, tint);
    return 0;
}

// Text misc. functions
// Measure string width for default font
int lua_MeasureText(lua_State *L)
{
    const char text = LuaGetArgument_string(L, 1);
    int fontSize = LuaGetArgument_int(L, 2);
    int result = MeasureText(text, fontSize);
    LuaPush_int(L, result);
    return 1;
}

// Measure string size for Font
int lua_MeasureTextEx(lua_State *L)
{
    Font font = LuaGetArgument_Font(L, 1);
    const char text = LuaGetArgument_string(L, 2);
    float fontSize = LuaGetArgument_float(L, 3);
    float spacing = LuaGetArgument_float(L, 4);
    Vector2 result = MeasureTextEx(font, text, fontSize, spacing);
    LuaPush_Vector2(L, result);
    return 1;
}

// Formatting of text with variables to 'embed'
int lua_FormatText(lua_State *L)
{
    const char text = LuaGetArgument_string(L, 1);
    ... text = LuaGetArgument_...(L, 2);
    string result = FormatText(text, text);
    LuaPush_string(L, result);
    return 1;
}

// Get a piece of a text string
int lua_SubText(lua_State *L)
{
    const char text = LuaGetArgument_string(L, 1);
    int position = LuaGetArgument_int(L, 2);
    int length = LuaGetArgument_int(L, 3);
    string result = SubText(text, position, length);
    LuaPush_string(L, result);
    return 1;
}

// Get index position for a unicode character on font
int lua_GetGlyphIndex(lua_State *L)
{
    Font font = LuaGetArgument_Font(L, 1);
    int character = LuaGetArgument_int(L, 2);
    int result = GetGlyphIndex(font, character);
    LuaPush_int(L, result);
    return 1;
}

//------------------------------------------------------------------------------------
// Basic 3d Shapes Drawing Functions (Module: models)
//------------------------------------------------------------------------------------
// Basic geometric 3D shapes drawing functions
// Draw a line in 3D world space
int lua_DrawLine3D(lua_State *L)
{
    Vector3 startPos = LuaGetArgument_Vector3(L, 1);
    Vector3 endPos = LuaGetArgument_Vector3(L, 2);
    Color color = LuaGetArgument_Color(L, 3);
    DrawLine3D(startPos, endPos, color);
    return 0;
}

// Draw a circle in 3D world space
int lua_DrawCircle3D(lua_State *L)
{
    Vector3 center = LuaGetArgument_Vector3(L, 1);
    float radius = LuaGetArgument_float(L, 2);
    Vector3 rotationAxis = LuaGetArgument_Vector3(L, 3);
    float rotationAngle = LuaGetArgument_float(L, 4);
    Color color = LuaGetArgument_Color(L, 5);
    DrawCircle3D(center, radius, rotationAxis, rotationAngle, color);
    return 0;
}

// Draw cube
int lua_DrawCube(lua_State *L)
{
    Vector3 position = LuaGetArgument_Vector3(L, 1);
    float width = LuaGetArgument_float(L, 2);
    float height = LuaGetArgument_float(L, 3);
    float length = LuaGetArgument_float(L, 4);
    Color color = LuaGetArgument_Color(L, 5);
    DrawCube(position, width, height, length, color);
    return 0;
}

// Draw cube (Vector version)
int lua_DrawCubeV(lua_State *L)
{
    Vector3 position = LuaGetArgument_Vector3(L, 1);
    Vector3 size = LuaGetArgument_Vector3(L, 2);
    Color color = LuaGetArgument_Color(L, 3);
    DrawCubeV(position, size, color);
    return 0;
}

// Draw cube wires
int lua_DrawCubeWires(lua_State *L)
{
    Vector3 position = LuaGetArgument_Vector3(L, 1);
    float width = LuaGetArgument_float(L, 2);
    float height = LuaGetArgument_float(L, 3);
    float length = LuaGetArgument_float(L, 4);
    Color color = LuaGetArgument_Color(L, 5);
    DrawCubeWires(position, width, height, length, color);
    return 0;
}

// Draw cube textured
int lua_DrawCubeTexture(lua_State *L)
{
    Texture2D texture = LuaGetArgument_Texture2D(L, 1);
    Vector3 position = LuaGetArgument_Vector3(L, 2);
    float width = LuaGetArgument_float(L, 3);
    float height = LuaGetArgument_float(L, 4);
    float length = LuaGetArgument_float(L, 5);
    Color color = LuaGetArgument_Color(L, 6);
    DrawCubeTexture(texture, position, width, height, length, color);
    return 0;
}

// Draw sphere
int lua_DrawSphere(lua_State *L)
{
    Vector3 centerPos = LuaGetArgument_Vector3(L, 1);
    float radius = LuaGetArgument_float(L, 2);
    Color color = LuaGetArgument_Color(L, 3);
    DrawSphere(centerPos, radius, color);
    return 0;
}

// Draw sphere with extended parameters
int lua_DrawSphereEx(lua_State *L)
{
    Vector3 centerPos = LuaGetArgument_Vector3(L, 1);
    float radius = LuaGetArgument_float(L, 2);
    int rings = LuaGetArgument_int(L, 3);
    int slices = LuaGetArgument_int(L, 4);
    Color color = LuaGetArgument_Color(L, 5);
    DrawSphereEx(centerPos, radius, rings, slices, color);
    return 0;
}

// Draw sphere wires
int lua_DrawSphereWires(lua_State *L)
{
    Vector3 centerPos = LuaGetArgument_Vector3(L, 1);
    float radius = LuaGetArgument_float(L, 2);
    int rings = LuaGetArgument_int(L, 3);
    int slices = LuaGetArgument_int(L, 4);
    Color color = LuaGetArgument_Color(L, 5);
    DrawSphereWires(centerPos, radius, rings, slices, color);
    return 0;
}

// Draw a cylinder/cone
int lua_DrawCylinder(lua_State *L)
{
    Vector3 position = LuaGetArgument_Vector3(L, 1);
    float radiusTop = LuaGetArgument_float(L, 2);
    float radiusBottom = LuaGetArgument_float(L, 3);
    float height = LuaGetArgument_float(L, 4);
    int slices = LuaGetArgument_int(L, 5);
    Color color = LuaGetArgument_Color(L, 6);
    DrawCylinder(position, radiusTop, radiusBottom, height, slices, color);
    return 0;
}

// Draw a cylinder/cone wires
int lua_DrawCylinderWires(lua_State *L)
{
    Vector3 position = LuaGetArgument_Vector3(L, 1);
    float radiusTop = LuaGetArgument_float(L, 2);
    float radiusBottom = LuaGetArgument_float(L, 3);
    float height = LuaGetArgument_float(L, 4);
    int slices = LuaGetArgument_int(L, 5);
    Color color = LuaGetArgument_Color(L, 6);
    DrawCylinderWires(position, radiusTop, radiusBottom, height, slices, color);
    return 0;
}

// Draw a plane XZ
int lua_DrawPlane(lua_State *L)
{
    Vector3 centerPos = LuaGetArgument_Vector3(L, 1);
    Vector2 size = LuaGetArgument_Vector2(L, 2);
    Color color = LuaGetArgument_Color(L, 3);
    DrawPlane(centerPos, size, color);
    return 0;
}

// Draw a ray line
int lua_DrawRay(lua_State *L)
{
    Ray ray = LuaGetArgument_Ray(L, 1);
    Color color = LuaGetArgument_Color(L, 2);
    DrawRay(ray, color);
    return 0;
}

// Draw a grid (centered at (0, 0, 0))
int lua_DrawGrid(lua_State *L)
{
    int slices = LuaGetArgument_int(L, 1);
    float spacing = LuaGetArgument_float(L, 2);
    DrawGrid(slices, spacing);
    return 0;
}

// Draw simple gizmo
int lua_DrawGizmo(lua_State *L)
{
    Vector3 position = LuaGetArgument_Vector3(L, 1);
    DrawGizmo(position);
    return 0;
}

//DrawTorus(), DrawTeapot() could be useful?
//------------------------------------------------------------------------------------
// Model 3d Loading and Drawing Functions (Module: models)
//------------------------------------------------------------------------------------
// Model loading/unloading functions
// Load model from files (mesh and material)
int lua_LoadModel(lua_State *L)
{
    const char fileName = LuaGetArgument_string(L, 1);
    Model result = LoadModel(fileName);
    LuaPush_Model(L, result);
    return 1;
}

// Load model from generated mesh
int lua_LoadModelFromMesh(lua_State *L)
{
    Mesh mesh = LuaGetArgument_Mesh(L, 1);
    Model result = LoadModelFromMesh(mesh);
    LuaPush_Model(L, result);
    return 1;
}

// Unload model from memory (RAM and/or VRAM)
int lua_UnloadModel(lua_State *L)
{
    Model model = LuaGetArgument_Model(L, 1);
    UnloadModel(model);
    return 0;
}

// Mesh loading/unloading functions
// Load mesh from file
int lua_LoadMesh(lua_State *L)
{
    const char fileName = LuaGetArgument_string(L, 1);
    Mesh result = LoadMesh(fileName);
    LuaPush_Mesh(L, result);
    return 1;
}

// Unload mesh from memory (RAM and/or VRAM)
int lua_UnloadMesh(lua_State *L)
{
    Mesh mesh = LuaGetArgument_Mesh(L, 1);
    UnloadMesh(mesh);
    return 0;
}

// Export mesh as an OBJ file
int lua_ExportMesh(lua_State *L)
{
    const char fileName = LuaGetArgument_string(L, 1);
    Mesh mesh = LuaGetArgument_Mesh(L, 2);
    ExportMesh(fileName, mesh);
    return 0;
}

// Mesh manipulation functions
// Compute mesh bounding box limits
int lua_MeshBoundingBox(lua_State *L)
{
    Mesh mesh = LuaGetArgument_Mesh(L, 1);
    BoundingBox result = MeshBoundingBox(mesh);
    LuaPush_BoundingBox(L, result);
    return 1;
}

// Compute mesh tangents
int lua_MeshTangents(lua_State *L)
{
    Mesh mesh = LuaGetArgument_Mesh(L, 1);
    MeshTangents(mesh);
    return 0;
}

// Compute mesh binormals
int lua_MeshBinormals(lua_State *L)
{
    Mesh mesh = LuaGetArgument_Mesh(L, 1);
    MeshBinormals(mesh);
    return 0;
}

// Mesh generation functions
// Generate plane mesh (with subdivisions)
int lua_GenMeshPlane(lua_State *L)
{
    float width = LuaGetArgument_float(L, 1);
    float length = LuaGetArgument_float(L, 2);
    int resX = LuaGetArgument_int(L, 3);
    int resZ = LuaGetArgument_int(L, 4);
    Mesh result = GenMeshPlane(width, length, resX, resZ);
    LuaPush_Mesh(L, result);
    return 1;
}

// Generate cuboid mesh
int lua_GenMeshCube(lua_State *L)
{
    float width = LuaGetArgument_float(L, 1);
    float height = LuaGetArgument_float(L, 2);
    float length = LuaGetArgument_float(L, 3);
    Mesh result = GenMeshCube(width, height, length);
    LuaPush_Mesh(L, result);
    return 1;
}

// Generate sphere mesh (standard sphere)
int lua_GenMeshSphere(lua_State *L)
{
    float radius = LuaGetArgument_float(L, 1);
    int rings = LuaGetArgument_int(L, 2);
    int slices = LuaGetArgument_int(L, 3);
    Mesh result = GenMeshSphere(radius, rings, slices);
    LuaPush_Mesh(L, result);
    return 1;
}

// Generate half-sphere mesh (no bottom cap)
int lua_GenMeshHemiSphere(lua_State *L)
{
    float radius = LuaGetArgument_float(L, 1);
    int rings = LuaGetArgument_int(L, 2);
    int slices = LuaGetArgument_int(L, 3);
    Mesh result = GenMeshHemiSphere(radius, rings, slices);
    LuaPush_Mesh(L, result);
    return 1;
}

// Generate cylinder mesh
int lua_GenMeshCylinder(lua_State *L)
{
    float radius = LuaGetArgument_float(L, 1);
    float height = LuaGetArgument_float(L, 2);
    int slices = LuaGetArgument_int(L, 3);
    Mesh result = GenMeshCylinder(radius, height, slices);
    LuaPush_Mesh(L, result);
    return 1;
}

// Generate torus mesh
int lua_GenMeshTorus(lua_State *L)
{
    float radius = LuaGetArgument_float(L, 1);
    float size = LuaGetArgument_float(L, 2);
    int radSeg = LuaGetArgument_int(L, 3);
    int sides = LuaGetArgument_int(L, 4);
    Mesh result = GenMeshTorus(radius, size, radSeg, sides);
    LuaPush_Mesh(L, result);
    return 1;
}

// Generate trefoil knot mesh
int lua_GenMeshKnot(lua_State *L)
{
    float radius = LuaGetArgument_float(L, 1);
    float size = LuaGetArgument_float(L, 2);
    int radSeg = LuaGetArgument_int(L, 3);
    int sides = LuaGetArgument_int(L, 4);
    Mesh result = GenMeshKnot(radius, size, radSeg, sides);
    LuaPush_Mesh(L, result);
    return 1;
}

// Generate heightmap mesh from image data
int lua_GenMeshHeightmap(lua_State *L)
{
    Image heightmap = LuaGetArgument_Image(L, 1);
    Vector3 size = LuaGetArgument_Vector3(L, 2);
    Mesh result = GenMeshHeightmap(heightmap, size);
    LuaPush_Mesh(L, result);
    return 1;
}

// Generate cubes-based map mesh from image data
int lua_GenMeshCubicmap(lua_State *L)
{
    Image cubicmap = LuaGetArgument_Image(L, 1);
    Vector3 cubeSize = LuaGetArgument_Vector3(L, 2);
    Mesh result = GenMeshCubicmap(cubicmap, cubeSize);
    LuaPush_Mesh(L, result);
    return 1;
}

// Material loading/unloading functions
// Load material from file
int lua_LoadMaterial(lua_State *L)
{
    const char fileName = LuaGetArgument_string(L, 1);
    Material result = LoadMaterial(fileName);
    LuaPush_Material(L, result);
    return 1;
}

// Load default material (Supports: DIFFUSE, SPECULAR, NORMAL maps)
int lua_LoadMaterialDefault(lua_State *L)
{
    Material result = LoadMaterialDefault();
    LuaPush_Material(L, result);
    return 1;
}

// Unload material from GPU memory (VRAM)
int lua_UnloadMaterial(lua_State *L)
{
    Material material = LuaGetArgument_Material(L, 1);
    UnloadMaterial(material);
    return 0;
}

// Model drawing functions
// Draw a model (with texture if set)
int lua_DrawModel(lua_State *L)
{
    Model model = LuaGetArgument_Model(L, 1);
    Vector3 position = LuaGetArgument_Vector3(L, 2);
    float scale = LuaGetArgument_float(L, 3);
    Color tint = LuaGetArgument_Color(L, 4);
    DrawModel(model, position, scale, tint);
    return 0;
}

// Draw a model with extended parameters
int lua_DrawModelEx(lua_State *L)
{
    Model model = LuaGetArgument_Model(L, 1);
    Vector3 position = LuaGetArgument_Vector3(L, 2);
    Vector3 rotationAxis = LuaGetArgument_Vector3(L, 3);
    float rotationAngle = LuaGetArgument_float(L, 4);
    Vector3 scale = LuaGetArgument_Vector3(L, 5);
    Color tint = LuaGetArgument_Color(L, 6);
    DrawModelEx(model, position, rotationAxis, rotationAngle, scale, tint);
    return 0;
}

// Draw a model wires (with texture if set)
int lua_DrawModelWires(lua_State *L)
{
    Model model = LuaGetArgument_Model(L, 1);
    Vector3 position = LuaGetArgument_Vector3(L, 2);
    float scale = LuaGetArgument_float(L, 3);
    Color tint = LuaGetArgument_Color(L, 4);
    DrawModelWires(model, position, scale, tint);
    return 0;
}

// Draw a model wires (with texture if set) with extended parameters
int lua_DrawModelWiresEx(lua_State *L)
{
    Model model = LuaGetArgument_Model(L, 1);
    Vector3 position = LuaGetArgument_Vector3(L, 2);
    Vector3 rotationAxis = LuaGetArgument_Vector3(L, 3);
    float rotationAngle = LuaGetArgument_float(L, 4);
    Vector3 scale = LuaGetArgument_Vector3(L, 5);
    Color tint = LuaGetArgument_Color(L, 6);
    DrawModelWiresEx(model, position, rotationAxis, rotationAngle, scale, tint);
    return 0;
}

// Draw bounding box (wires)
int lua_DrawBoundingBox(lua_State *L)
{
    BoundingBox box = LuaGetArgument_BoundingBox(L, 1);
    Color color = LuaGetArgument_Color(L, 2);
    DrawBoundingBox(box, color);
    return 0;
}

// Draw a billboard texture
int lua_DrawBillboard(lua_State *L)
{
    Camera camera = LuaGetArgument_Camera(L, 1);
    Texture2D texture = LuaGetArgument_Texture2D(L, 2);
    Vector3 center = LuaGetArgument_Vector3(L, 3);
    float size = LuaGetArgument_float(L, 4);
    Color tint = LuaGetArgument_Color(L, 5);
    DrawBillboard(camera, texture, center, size, tint);
    return 0;
}

// Draw a billboard texture defined by sourceRec
int lua_DrawBillboardRec(lua_State *L)
{
    Camera camera = LuaGetArgument_Camera(L, 1);
    Texture2D texture = LuaGetArgument_Texture2D(L, 2);
    Rectangle sourceRec = LuaGetArgument_Rectangle(L, 3);
    Vector3 center = LuaGetArgument_Vector3(L, 4);
    float size = LuaGetArgument_float(L, 5);
    Color tint = LuaGetArgument_Color(L, 6);
    DrawBillboardRec(camera, texture, sourceRec, center, size, tint);
    return 0;
}

// Collision detection functions
// Detect collision between two spheres
int lua_CheckCollisionSpheres(lua_State *L)
{
    Vector3 centerA = LuaGetArgument_Vector3(L, 1);
    float radiusA = LuaGetArgument_float(L, 2);
    Vector3 centerB = LuaGetArgument_Vector3(L, 3);
    float radiusB = LuaGetArgument_float(L, 4);
    bool result = CheckCollisionSpheres(centerA, radiusA, centerB, radiusB);
    LuaPush_bool(L, result);
    return 1;
}

// Detect collision between two bounding boxes
int lua_CheckCollisionBoxes(lua_State *L)
{
    BoundingBox box1 = LuaGetArgument_BoundingBox(L, 1);
    BoundingBox box2 = LuaGetArgument_BoundingBox(L, 2);
    bool result = CheckCollisionBoxes(box1, box2);
    LuaPush_bool(L, result);
    return 1;
}

// Detect collision between box and sphere
int lua_CheckCollisionBoxSphere(lua_State *L)
{
    BoundingBox box = LuaGetArgument_BoundingBox(L, 1);
    Vector3 centerSphere = LuaGetArgument_Vector3(L, 2);
    float radiusSphere = LuaGetArgument_float(L, 3);
    bool result = CheckCollisionBoxSphere(box, centerSphere, radiusSphere);
    LuaPush_bool(L, result);
    return 1;
}

// Detect collision between ray and sphere
int lua_CheckCollisionRaySphere(lua_State *L)
{
    Ray ray = LuaGetArgument_Ray(L, 1);
    Vector3 spherePosition = LuaGetArgument_Vector3(L, 2);
    float sphereRadius = LuaGetArgument_float(L, 3);
    bool result = CheckCollisionRaySphere(ray, spherePosition, sphereRadius);
    LuaPush_bool(L, result);
    return 1;
}

// Detect collision between ray and sphere, returns collision point
int lua_CheckCollisionRaySphereEx(lua_State *L)
{
    Ray ray = LuaGetArgument_Ray(L, 1);
    Vector3 spherePosition = LuaGetArgument_Vector3(L, 2);
    float sphereRadius = LuaGetArgument_float(L, 3);
    Vector3 collisionPoint = LuaGetArgument_Vector3(L, 4);
    bool result = CheckCollisionRaySphereEx(ray, spherePosition, sphereRadius, collisionPoint);
    LuaPush_bool(L, result);
    return 1;
}

// Detect collision between ray and box
int lua_CheckCollisionRayBox(lua_State *L)
{
    Ray ray = LuaGetArgument_Ray(L, 1);
    BoundingBox box = LuaGetArgument_BoundingBox(L, 2);
    bool result = CheckCollisionRayBox(ray, box);
    LuaPush_bool(L, result);
    return 1;
}

// Get collision info between ray and model
int lua_GetCollisionRayModel(lua_State *L)
{
    Ray ray = LuaGetArgument_Ray(L, 1);
    Model model = LuaGetArgument_Model(L, 2);
    RayHitInfo result = GetCollisionRayModel(ray, model);
    LuaPush_RayHitInfo(L, result);
    return 1;
}

// Get collision info between ray and triangle
int lua_GetCollisionRayTriangle(lua_State *L)
{
    Ray ray = LuaGetArgument_Ray(L, 1);
    Vector3 p1 = LuaGetArgument_Vector3(L, 2);
    Vector3 p2 = LuaGetArgument_Vector3(L, 3);
    Vector3 p3 = LuaGetArgument_Vector3(L, 4);
    RayHitInfo result = GetCollisionRayTriangle(ray, p1, p2, p3);
    LuaPush_RayHitInfo(L, result);
    return 1;
}

// Get collision info between ray and ground plane (Y-normal plane)
int lua_GetCollisionRayGround(lua_State *L)
{
    Ray ray = LuaGetArgument_Ray(L, 1);
    float groundHeight = LuaGetArgument_float(L, 2);
    RayHitInfo result = GetCollisionRayGround(ray, groundHeight);
    LuaPush_RayHitInfo(L, result);
    return 1;
}

//------------------------------------------------------------------------------------
// Shaders System Functions (Module: rlgl)
// NOTE: This functions are useless when using OpenGL 1.1
//------------------------------------------------------------------------------------
// Shader loading/unloading functions
// Load chars array from text file
int lua_LoadText(lua_State *L)
{
    const char fileName = LuaGetArgument_string(L, 1);
    char result = LoadText(fileName);
    LuaPush_char(L, result);
    return 1;
}

// Load shader from files and bind default locations
int lua_LoadShader(lua_State *L)
{
    const char vsFileName = LuaGetArgument_string(L, 1);
    const char fsFileName = LuaGetArgument_string(L, 2);
    Shader result = LoadShader(vsFileName, fsFileName);
    LuaPush_Shader(L, result);
    return 1;
}

// Load shader from code strings and bind default locations
int lua_LoadShaderCode(lua_State *L)
{
    char vsCode = LuaGetArgument_char(L, 1);
    char fsCode = LuaGetArgument_char(L, 2);
    Shader result = LoadShaderCode(vsCode, fsCode);
    LuaPush_Shader(L, result);
    return 1;
}

// Unload shader from GPU memory (VRAM)
int lua_UnloadShader(lua_State *L)
{
    Shader shader = LuaGetArgument_Shader(L, 1);
    UnloadShader(shader);
    return 0;
}

// Get default shader
int lua_GetShaderDefault(lua_State *L)
{
    Shader result = GetShaderDefault();
    LuaPush_Shader(L, result);
    return 1;
}

// Get default texture
int lua_GetTextureDefault(lua_State *L)
{
    Texture2D result = GetTextureDefault();
    LuaPush_Texture2D(L, result);
    return 1;
}

// Shader configuration functions
// Get shader uniform location
int lua_GetShaderLocation(lua_State *L)
{
    Shader shader = LuaGetArgument_Shader(L, 1);
    const char uniformName = LuaGetArgument_string(L, 2);
    int result = GetShaderLocation(shader, uniformName);
    LuaPush_int(L, result);
    return 1;
}

// Set shader uniform value (float)
int lua_SetShaderValue(lua_State *L)
{
    Shader shader = LuaGetArgument_Shader(L, 1);
    int uniformLoc = LuaGetArgument_int(L, 2);
    const float value = LuaGetArgument_float(L, 3);
    int size = LuaGetArgument_int(L, 4);
    SetShaderValue(shader, uniformLoc, value, size);
    return 0;
}

// Set shader uniform value (int)
int lua_SetShaderValuei(lua_State *L)
{
    Shader shader = LuaGetArgument_Shader(L, 1);
    int uniformLoc = LuaGetArgument_int(L, 2);
    const int value = LuaGetArgument_int(L, 3);
    int size = LuaGetArgument_int(L, 4);
    SetShaderValuei(shader, uniformLoc, value, size);
    return 0;
}

// Set shader uniform value (matrix 4x4)
int lua_SetShaderValueMatrix(lua_State *L)
{
    Shader shader = LuaGetArgument_Shader(L, 1);
    int uniformLoc = LuaGetArgument_int(L, 2);
    Matrix mat = LuaGetArgument_Matrix(L, 3);
    SetShaderValueMatrix(shader, uniformLoc, mat);
    return 0;
}

// Set a custom projection matrix (replaces internal projection matrix)
int lua_SetMatrixProjection(lua_State *L)
{
    Matrix proj = LuaGetArgument_Matrix(L, 1);
    SetMatrixProjection(proj);
    return 0;
}

// Set a custom modelview matrix (replaces internal modelview matrix)
int lua_SetMatrixModelview(lua_State *L)
{
    Matrix view = LuaGetArgument_Matrix(L, 1);
    SetMatrixModelview(view);
    return 0;
}

// Get internal modelview matrix
int lua_GetMatrixModelview(lua_State *L)
{
    Matrix view = LuaGetArgument_Matrix(L, 1);
    Matrix result = GetMatrixModelview(view);
    LuaPush_Matrix(L, result);
    return 1;
}

// Texture maps generation (PBR)
// NOTE: Required shaders should be provided
// Generate cubemap texture from HDR texture
int lua_GenTextureCubemap(lua_State *L)
{
    Shader shader = LuaGetArgument_Shader(L, 1);
    Texture2D skyHDR = LuaGetArgument_Texture2D(L, 2);
    int size = LuaGetArgument_int(L, 3);
    Texture2D result = GenTextureCubemap(shader, skyHDR, size);
    LuaPush_Texture2D(L, result);
    return 1;
}

// Generate irradiance texture using cubemap data
int lua_GenTextureIrradiance(lua_State *L)
{
    Shader shader = LuaGetArgument_Shader(L, 1);
    Texture2D cubemap = LuaGetArgument_Texture2D(L, 2);
    int size = LuaGetArgument_int(L, 3);
    Texture2D result = GenTextureIrradiance(shader, cubemap, size);
    LuaPush_Texture2D(L, result);
    return 1;
}

// Generate prefilter texture using cubemap data
int lua_GenTexturePrefilter(lua_State *L)
{
    Shader shader = LuaGetArgument_Shader(L, 1);
    Texture2D cubemap = LuaGetArgument_Texture2D(L, 2);
    int size = LuaGetArgument_int(L, 3);
    Texture2D result = GenTexturePrefilter(shader, cubemap, size);
    LuaPush_Texture2D(L, result);
    return 1;
}

// Generate BRDF texture using cubemap data
int lua_GenTextureBRDF(lua_State *L)
{
    Shader shader = LuaGetArgument_Shader(L, 1);
    Texture2D cubemap = LuaGetArgument_Texture2D(L, 2);
    int size = LuaGetArgument_int(L, 3);
    Texture2D result = GenTextureBRDF(shader, cubemap, size);
    LuaPush_Texture2D(L, result);
    return 1;
}

// Shading begin/end functions
// Begin custom shader drawing
int lua_BeginShaderMode(lua_State *L)
{
    Shader shader = LuaGetArgument_Shader(L, 1);
    BeginShaderMode(shader);
    return 0;
}

// End custom shader drawing (use default shader)
int lua_EndShaderMode(lua_State *L)
{
    EndShaderMode();
    return 0;
}

// Begin blending mode (alpha, additive, multiplied)
int lua_BeginBlendMode(lua_State *L)
{
    int mode = LuaGetArgument_int(L, 1);
    BeginBlendMode(mode);
    return 0;
}

// End blending mode (reset to default: alpha blending)
int lua_EndBlendMode(lua_State *L)
{
    EndBlendMode();
    return 0;
}

// VR control functions
// Get VR device information for some standard devices
int lua_GetVrDeviceInfo(lua_State *L)
{
    int vrDeviceType = LuaGetArgument_int(L, 1);
    VrDeviceInfo result = GetVrDeviceInfo(vrDeviceType);
    LuaPush_VrDeviceInfo(L, result);
    return 1;
}

// Init VR simulator for selected device parameters
int lua_InitVrSimulator(lua_State *L)
{
    VrDeviceInfo info = LuaGetArgument_VrDeviceInfo(L, 1);
    InitVrSimulator(info);
    return 0;
}

// Close VR simulator for current device
int lua_CloseVrSimulator(lua_State *L)
{
    CloseVrSimulator();
    return 0;
}

// Detect if VR simulator is ready
int lua_IsVrSimulatorReady(lua_State *L)
{
    bool result = IsVrSimulatorReady();
    LuaPush_bool(L, result);
    return 1;
}

// Set VR distortion shader for stereoscopic rendering
int lua_SetVrDistortionShader(lua_State *L)
{
    Shader shader = LuaGetArgument_Shader(L, 1);
    SetVrDistortionShader(shader);
    return 0;
}

// Update VR tracking (position and orientation) and camera
int lua_UpdateVrTracking(lua_State *L)
{
    Camera camera = LuaGetArgument_Camera(L, 1);
    UpdateVrTracking(camera);
    return 0;
}

// Enable/Disable VR experience
int lua_ToggleVrMode(lua_State *L)
{
    ToggleVrMode();
    return 0;
}

// Begin VR simulator stereo rendering
int lua_BeginVrDrawing(lua_State *L)
{
    BeginVrDrawing();
    return 0;
}

// End VR simulator stereo rendering
int lua_EndVrDrawing(lua_State *L)
{
    EndVrDrawing();
    return 0;
}

//------------------------------------------------------------------------------------
// Audio Loading and Playing Functions (Module: audio)
//------------------------------------------------------------------------------------
// Audio device management functions
// Initialize audio device and context
int lua_InitAudioDevice(lua_State *L)
{
    InitAudioDevice();
    return 0;
}

// Close the audio device and context
int lua_CloseAudioDevice(lua_State *L)
{
    CloseAudioDevice();
    return 0;
}

// Check if audio device has been initialized successfully
int lua_IsAudioDeviceReady(lua_State *L)
{
    bool result = IsAudioDeviceReady();
    LuaPush_bool(L, result);
    return 1;
}

// Set master volume (listener)
int lua_SetMasterVolume(lua_State *L)
{
    float volume = LuaGetArgument_float(L, 1);
    SetMasterVolume(volume);
    return 0;
}

// Wave/Sound loading/unloading functions
// Load wave data from file
int lua_LoadWave(lua_State *L)
{
    const char fileName = LuaGetArgument_string(L, 1);
    Wave result = LoadWave(fileName);
    LuaPush_Wave(L, result);
    return 1;
}

// Load wave data from raw array data
int lua_LoadWaveEx(lua_State *L)
{
    Wave result = LoadWaveEx();
    LuaPush_Wave(L, result);
    return 1;
}

// Load sound from file
int lua_LoadSound(lua_State *L)
{
    const char fileName = LuaGetArgument_string(L, 1);
    Sound result = LoadSound(fileName);
    LuaPush_Sound(L, result);
    return 1;
}

// Load sound from wave data
int lua_LoadSoundFromWave(lua_State *L)
{
    Wave wave = LuaGetArgument_Wave(L, 1);
    Sound result = LoadSoundFromWave(wave);
    LuaPush_Sound(L, result);
    return 1;
}

// Update sound buffer with new data
int lua_UpdateSound(lua_State *L)
{
    Sound sound = LuaGetArgument_Sound(L, 1);
    const void data = LuaGetArgument_void(L, 2);
    int samplesCount = LuaGetArgument_int(L, 3);
    UpdateSound(sound, data, samplesCount);
    return 0;
}

// Unload wave data
int lua_UnloadWave(lua_State *L)
{
    Wave wave = LuaGetArgument_Wave(L, 1);
    UnloadWave(wave);
    return 0;
}

// Unload sound
int lua_UnloadSound(lua_State *L)
{
    Sound sound = LuaGetArgument_Sound(L, 1);
    UnloadSound(sound);
    return 0;
}

// Wave/Sound management functions
// Play a sound
int lua_PlaySound(lua_State *L)
{
    Sound sound = LuaGetArgument_Sound(L, 1);
    PlaySound(sound);
    return 0;
}

// Pause a sound
int lua_PauseSound(lua_State *L)
{
    Sound sound = LuaGetArgument_Sound(L, 1);
    PauseSound(sound);
    return 0;
}

// Resume a paused sound
int lua_ResumeSound(lua_State *L)
{
    Sound sound = LuaGetArgument_Sound(L, 1);
    ResumeSound(sound);
    return 0;
}

// Stop playing a sound
int lua_StopSound(lua_State *L)
{
    Sound sound = LuaGetArgument_Sound(L, 1);
    StopSound(sound);
    return 0;
}

// Check if a sound is currently playing
int lua_IsSoundPlaying(lua_State *L)
{
    Sound sound = LuaGetArgument_Sound(L, 1);
    bool result = IsSoundPlaying(sound);
    LuaPush_bool(L, result);
    return 1;
}

// Set volume for a sound (1.0 is max level)
int lua_SetSoundVolume(lua_State *L)
{
    Sound sound = LuaGetArgument_Sound(L, 1);
    float volume = LuaGetArgument_float(L, 2);
    SetSoundVolume(sound, volume);
    return 0;
}

// Set pitch for a sound (1.0 is base level)
int lua_SetSoundPitch(lua_State *L)
{
    Sound sound = LuaGetArgument_Sound(L, 1);
    float pitch = LuaGetArgument_float(L, 2);
    SetSoundPitch(sound, pitch);
    return 0;
}

// Convert wave data to desired format
int lua_WaveFormat(lua_State *L)
{
    Wave wave = LuaGetArgument_Wave(L, 1);
    int sampleRate = LuaGetArgument_int(L, 2);
    int sampleSize = LuaGetArgument_int(L, 3);
    int channels = LuaGetArgument_int(L, 4);
    WaveFormat(wave, sampleRate, sampleSize, channels);
    return 0;
}

// Copy a wave to a new wave
int lua_WaveCopy(lua_State *L)
{
    Wave wave = LuaGetArgument_Wave(L, 1);
    Wave result = WaveCopy(wave);
    LuaPush_Wave(L, result);
    return 1;
}

// Crop a wave to defined samples range
int lua_WaveCrop(lua_State *L)
{
    Wave wave = LuaGetArgument_Wave(L, 1);
    int initSample = LuaGetArgument_int(L, 2);
    int finalSample = LuaGetArgument_int(L, 3);
    WaveCrop(wave, initSample, finalSample);
    return 0;
}

// Get samples data from wave as a floats array
int lua_GetWaveData(lua_State *L)
{
    Wave wave = LuaGetArgument_Wave(L, 1);
    float result = GetWaveData(wave);
    LuaPush_float(L, result);
    return 1;
}

// Music management functions
// Load music stream from file
int lua_LoadMusicStream(lua_State *L)
{
    const char fileName = LuaGetArgument_string(L, 1);
    Music result = LoadMusicStream(fileName);
    LuaPush_Music(L, result);
    return 1;
}

// Unload music stream
int lua_UnloadMusicStream(lua_State *L)
{
    Music music = LuaGetArgument_Music(L, 1);
    UnloadMusicStream(music);
    return 0;
}

// Start music playing
int lua_PlayMusicStream(lua_State *L)
{
    Music music = LuaGetArgument_Music(L, 1);
    PlayMusicStream(music);
    return 0;
}

// Updates buffers for music streaming
int lua_UpdateMusicStream(lua_State *L)
{
    Music music = LuaGetArgument_Music(L, 1);
    UpdateMusicStream(music);
    return 0;
}

// Stop music playing
int lua_StopMusicStream(lua_State *L)
{
    Music music = LuaGetArgument_Music(L, 1);
    StopMusicStream(music);
    return 0;
}

// Pause music playing
int lua_PauseMusicStream(lua_State *L)
{
    Music music = LuaGetArgument_Music(L, 1);
    PauseMusicStream(music);
    return 0;
}

// Resume playing paused music
int lua_ResumeMusicStream(lua_State *L)
{
    Music music = LuaGetArgument_Music(L, 1);
    ResumeMusicStream(music);
    return 0;
}

// Check if music is playing
int lua_IsMusicPlaying(lua_State *L)
{
    Music music = LuaGetArgument_Music(L, 1);
    bool result = IsMusicPlaying(music);
    LuaPush_bool(L, result);
    return 1;
}

// Set volume for music (1.0 is max level)
int lua_SetMusicVolume(lua_State *L)
{
    Music music = LuaGetArgument_Music(L, 1);
    float volume = LuaGetArgument_float(L, 2);
    SetMusicVolume(music, volume);
    return 0;
}

// Set pitch for a music (1.0 is base level)
int lua_SetMusicPitch(lua_State *L)
{
    Music music = LuaGetArgument_Music(L, 1);
    float pitch = LuaGetArgument_float(L, 2);
    SetMusicPitch(music, pitch);
    return 0;
}

// Set music loop count (loop repeats)
int lua_SetMusicLoopCount(lua_State *L)
{
    Music music = LuaGetArgument_Music(L, 1);
    int count = LuaGetArgument_int(L, 2);
    SetMusicLoopCount(music, count);
    return 0;
}

// Get music time length (in seconds)
int lua_GetMusicTimeLength(lua_State *L)
{
    Music music = LuaGetArgument_Music(L, 1);
    float result = GetMusicTimeLength(music);
    LuaPush_float(L, result);
    return 1;
}

// Get current music time played (in seconds)
int lua_GetMusicTimePlayed(lua_State *L)
{
    Music music = LuaGetArgument_Music(L, 1);
    float result = GetMusicTimePlayed(music);
    LuaPush_float(L, result);
    return 1;
}

// AudioStream management functions
// Init audio stream (to stream raw audio pcm data)
int lua_InitAudioStream(lua_State *L)
{
    unsigned int sampleRate = LuaGetArgument_unsigned(L, 1);
    unsigned int sampleSize = LuaGetArgument_unsigned(L, 2);
    unsigned int channels = LuaGetArgument_unsigned(L, 3);
    AudioStream result = InitAudioStream(sampleRate, sampleSize, channels);
    LuaPush_AudioStream(L, result);
    return 1;
}

// Update audio stream buffers with data
int lua_UpdateAudioStream(lua_State *L)
{
    AudioStream stream = LuaGetArgument_AudioStream(L, 1);
    const void data = LuaGetArgument_void(L, 2);
    int samplesCount = LuaGetArgument_int(L, 3);
    UpdateAudioStream(stream, data, samplesCount);
    return 0;
}

// Close audio stream and free memory
int lua_CloseAudioStream(lua_State *L)
{
    AudioStream stream = LuaGetArgument_AudioStream(L, 1);
    CloseAudioStream(stream);
    return 0;
}

// Check if any audio stream buffers requires refill
int lua_IsAudioBufferProcessed(lua_State *L)
{
    AudioStream stream = LuaGetArgument_AudioStream(L, 1);
    bool result = IsAudioBufferProcessed(stream);
    LuaPush_bool(L, result);
    return 1;
}

// Play audio stream
int lua_PlayAudioStream(lua_State *L)
{
    AudioStream stream = LuaGetArgument_AudioStream(L, 1);
    PlayAudioStream(stream);
    return 0;
}

// Pause audio stream
int lua_PauseAudioStream(lua_State *L)
{
    AudioStream stream = LuaGetArgument_AudioStream(L, 1);
    PauseAudioStream(stream);
    return 0;
}

// Resume audio stream
int lua_ResumeAudioStream(lua_State *L)
{
    AudioStream stream = LuaGetArgument_AudioStream(L, 1);
    ResumeAudioStream(stream);
    return 0;
}

// Check if audio stream is playing
int lua_IsAudioStreamPlaying(lua_State *L)
{
    AudioStream stream = LuaGetArgument_AudioStream(L, 1);
    bool result = IsAudioStreamPlaying(stream);
    LuaPush_bool(L, result);
    return 1;
}

// Stop audio stream
int lua_StopAudioStream(lua_State *L)
{
    AudioStream stream = LuaGetArgument_AudioStream(L, 1);
    StopAudioStream(stream);
    return 0;
}

// Set volume for audio stream (1.0 is max level)
int lua_SetAudioStreamVolume(lua_State *L)
{
    AudioStream stream = LuaGetArgument_AudioStream(L, 1);
    float volume = LuaGetArgument_float(L, 2);
    SetAudioStreamVolume(stream, volume);
    return 0;
}

// Set pitch for audio stream (1.0 is base level)
int lua_SetAudioStreamPitch(lua_State *L)
{
    AudioStream stream = LuaGetArgument_AudioStream(L, 1);
    float pitch = LuaGetArgument_float(L, 2);
    SetAudioStreamPitch(stream, pitch);
    return 0;
}

static void LuaPush_Vector2(lua_State* L, Vector2 obj)
{
    lua_createtable(L, 0, 2);
    LuaPush_float(L, obj.x);
    lua_setfield(L, -2, "x");
    LuaPush_float(L, obj.y);
    lua_setfield(L, -2, "y");
}

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

static void LuaPush_Vector4(lua_State* L, Vector4 obj)
{
    lua_createtable(L, 0, 4);
    LuaPush_float(L, obj.x);
    lua_setfield(L, -2, "x");
    LuaPush_float(L, obj.y);
    lua_setfield(L, -2, "y");
    LuaPush_float(L, obj.z);
    lua_setfield(L, -2, "z");
    LuaPush_float(L, obj.w);
    lua_setfield(L, -2, "w");
}

static void LuaPush_Matrix(lua_State* L, Matrix obj)
{
    lua_createtable(L, 0, 4);
    LuaPush_float(L, obj.m0, m4, m8, m12);
    lua_setfield(L, -2, "m0, m4, m8, m12");
    LuaPush_float(L, obj.m1, m5, m9, m13);
    lua_setfield(L, -2, "m1, m5, m9, m13");
    LuaPush_float(L, obj.m2, m6, m10, m14);
    lua_setfield(L, -2, "m2, m6, m10, m14");
    LuaPush_float(L, obj.m3, m7, m11, m15);
    lua_setfield(L, -2, "m3, m7, m11, m15");
}

static void LuaPush_Color(lua_State* L, Color obj)
{
    lua_createtable(L, 0, 4);
    LuaPush_unsigned(L, obj.char r);
    lua_setfield(L, -2, "char r");
    LuaPush_unsigned(L, obj.char g);
    lua_setfield(L, -2, "char g");
    LuaPush_unsigned(L, obj.char b);
    lua_setfield(L, -2, "char b");
    LuaPush_unsigned(L, obj.char a);
    lua_setfield(L, -2, "char a");
}

static void LuaPush_Rectangle(lua_State* L, Rectangle obj)
{
    lua_createtable(L, 0, 4);
    LuaPush_float(L, obj.x);
    lua_setfield(L, -2, "x");
    LuaPush_float(L, obj.y);
    lua_setfield(L, -2, "y");
    LuaPush_float(L, obj.width);
    lua_setfield(L, -2, "width");
    LuaPush_float(L, obj.height);
    lua_setfield(L, -2, "height");
}

static void LuaPush_Image(lua_State* L, Image obj)
{
    lua_createtable(L, 0, 5);
    LuaPush_void(L, obj.data);
    lua_setfield(L, -2, "*data");
    LuaPush_int(L, obj.width);
    lua_setfield(L, -2, "width");
    LuaPush_int(L, obj.height);
    lua_setfield(L, -2, "height");
    LuaPush_int(L, obj.mipmaps);
    lua_setfield(L, -2, "mipmaps");
    LuaPush_int(L, obj.format);
    lua_setfield(L, -2, "format");
}

static void LuaPush_Texture2D(lua_State* L, Texture2D obj)
{
    lua_createtable(L, 0, 5);
    LuaPush_unsigned(L, obj.int id);
    lua_setfield(L, -2, "int id");
    LuaPush_int(L, obj.width);
    lua_setfield(L, -2, "width");
    LuaPush_int(L, obj.height);
    lua_setfield(L, -2, "height");
    LuaPush_int(L, obj.mipmaps);
    lua_setfield(L, -2, "mipmaps");
    LuaPush_int(L, obj.format);
    lua_setfield(L, -2, "format");
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

static void LuaPush_CharInfo(lua_State* L, CharInfo obj)
{
    lua_createtable(L, 0, 6);
    LuaPush_int(L, obj.value);
    lua_setfield(L, -2, "value");
    LuaPush_Rectangle(L, obj.rec);
    lua_setfield(L, -2, "rec");
    LuaPush_int(L, obj.offsetX);
    lua_setfield(L, -2, "offsetX");
    LuaPush_int(L, obj.offsetY);
    lua_setfield(L, -2, "offsetY");
    LuaPush_int(L, obj.advanceX);
    lua_setfield(L, -2, "advanceX");
    LuaPush_unsigned(L, obj.char *data);
    lua_setfield(L, -2, "char *data");
}

static void LuaPush_Font(lua_State* L, Font obj)
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

static void LuaPush_Camera3D(lua_State* L, Camera3D obj)
{
    lua_createtable(L, 0, 5);
    LuaPush_Vector3(L, obj.position);
    lua_setfield(L, -2, "position");
    LuaPush_Vector3(L, obj.target);
    lua_setfield(L, -2, "target");
    LuaPush_Vector3(L, obj.up);
    lua_setfield(L, -2, "up");
    LuaPush_float(L, obj.fovy);
    lua_setfield(L, -2, "fovy");
    LuaPush_int(L, obj.type);
    lua_setfield(L, -2, "type");
}

static void LuaPush_Camera2D(lua_State* L, Camera2D obj)
{
    lua_createtable(L, 0, 4);
    LuaPush_Vector2(L, obj.offset);
    lua_setfield(L, -2, "offset");
    LuaPush_Vector2(L, obj.target);
    lua_setfield(L, -2, "target");
    LuaPush_float(L, obj.rotation);
    lua_setfield(L, -2, "rotation");
    LuaPush_float(L, obj.zoom);
    lua_setfield(L, -2, "zoom");
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

static void LuaPush_Shader(lua_State* L, Shader obj)
{
    lua_createtable(L, 0, 2);
    LuaPush_unsigned(L, obj.int id);
    lua_setfield(L, -2, "int id");
    LuaPush_int(L, obj.locs[MAX_SHADER_LOCATIONS]);
    lua_setfield(L, -2, "locs[MAX_SHADER_LOCATIONS]");
}

static void LuaPush_MaterialMap(lua_State* L, MaterialMap obj)
{
    lua_createtable(L, 0, 3);
    LuaPush_Texture2D(L, obj.texture);
    lua_setfield(L, -2, "texture");
    LuaPush_Color(L, obj.color);
    lua_setfield(L, -2, "color");
    LuaPush_float(L, obj.value);
    lua_setfield(L, -2, "value");
}

static void LuaPush_Material(lua_State* L, Material obj)
{
    lua_createtable(L, 0, 3);
    LuaPush_Shader(L, obj.shader);
    lua_setfield(L, -2, "shader");
    LuaPush_MaterialMap(L, obj.maps[MAX_MATERIAL_MAPS]);
    lua_setfield(L, -2, "maps[MAX_MATERIAL_MAPS]");
    LuaPush_float(L, obj.params);
    lua_setfield(L, -2, "*params");
}

static void LuaPush_Model(lua_State* L, Model obj)
{
    lua_createtable(L, 0, 3);
    LuaPush_Mesh(L, obj.mesh);
    lua_setfield(L, -2, "mesh");
    LuaPush_Matrix(L, obj.transform);
    lua_setfield(L, -2, "transform");
    LuaPush_Material(L, obj.material);
    lua_setfield(L, -2, "material");
}

static void LuaPush_Ray(lua_State* L, Ray obj)
{
    lua_createtable(L, 0, 2);
    LuaPush_Vector3(L, obj.position);
    lua_setfield(L, -2, "position");
    LuaPush_Vector3(L, obj.direction);
    lua_setfield(L, -2, "direction");
}

static void LuaPush_RayHitInfo(lua_State* L, RayHitInfo obj)
{
    lua_createtable(L, 0, 4);
    LuaPush_bool(L, obj.hit);
    lua_setfield(L, -2, "hit");
    LuaPush_float(L, obj.distance);
    lua_setfield(L, -2, "distance");
    LuaPush_Vector3(L, obj.position);
    lua_setfield(L, -2, "position");
    LuaPush_Vector3(L, obj.normal);
    lua_setfield(L, -2, "normal");
}

static void LuaPush_Wave(lua_State* L, Wave obj)
{
    lua_createtable(L, 0, 5);
    LuaPush_unsigned(L, obj.int sampleCount);
    lua_setfield(L, -2, "int sampleCount");
    LuaPush_unsigned(L, obj.int sampleRate);
    lua_setfield(L, -2, "int sampleRate");
    LuaPush_unsigned(L, obj.int sampleSize);
    lua_setfield(L, -2, "int sampleSize");
    LuaPush_unsigned(L, obj.int channels);
    lua_setfield(L, -2, "int channels");
    LuaPush_void(L, obj.data);
    lua_setfield(L, -2, "*data");
}

static void LuaPush_Sound(lua_State* L, Sound obj)
{
    lua_createtable(L, 0, 4);
    LuaPush_void(L, obj.audioBuffer);
    lua_setfield(L, -2, "*audioBuffer");
    LuaPush_unsigned(L, obj.int source);
    lua_setfield(L, -2, "int source");
    LuaPush_unsigned(L, obj.int buffer);
    lua_setfield(L, -2, "int buffer");
    LuaPush_int(L, obj.format);
    lua_setfield(L, -2, "format");
}

static void LuaPush_MusicData(lua_State* L, MusicData obj)
{
    lua_createtable(L, 0, 10);
    LuaPush_//(L, obj.Audio stream type
);
    lua_setfield(L, -2, "Audio stream type
");
    LuaPush_//(L, obj.NOTE: Useful to create custom austruct AudioStream {
);
    lua_setfield(L, -2, "NOTE: Useful to create custom austruct AudioStream {
");
    LuaPush_typedef(L, obj.struct AudioStream {
);
    lua_setfield(L, -2, "struct AudioStream {
");
    LuaPush_unsigned(L, obj.int sampleRate);
    lua_setfield(L, -2, "int sampleRate");
    LuaPush_unsigned(L, obj.int sampleSize);
    lua_setfield(L, -2, "int sampleSize");
    LuaPush_unsigned(L, obj.int channels);
    lua_setfield(L, -2, "int channels");
    LuaPush_void(L, obj.audioBuffer);
    lua_setfield(L, -2, "*audioBuffer");
    LuaPush_int(L, obj.format);
    lua_setfield(L, -2, "format");
    LuaPush_unsigned(L, obj.int source);
    lua_setfield(L, -2, "int source");
    LuaPush_unsigned(L, obj.int buffers[2]);
    lua_setfield(L, -2, "int buffers[2]");
}

static void LuaPush_VrDeviceInfo(lua_State* L, VrDeviceInfo obj)
{
    lua_createtable(L, 0, 10);
    LuaPush_int(L, obj.hResolution);
    lua_setfield(L, -2, "hResolution");
    LuaPush_int(L, obj.vResolution);
    lua_setfield(L, -2, "vResolution");
    LuaPush_float(L, obj.hScreenSize);
    lua_setfield(L, -2, "hScreenSize");
    LuaPush_float(L, obj.vScreenSize);
    lua_setfield(L, -2, "vScreenSize");
    LuaPush_float(L, obj.vScreenCenter);
    lua_setfield(L, -2, "vScreenCenter");
    LuaPush_float(L, obj.eyeToScreenDistance);
    lua_setfield(L, -2, "eyeToScreenDistance");
    LuaPush_float(L, obj.lensSeparationDistance);
    lua_setfield(L, -2, "lensSeparationDistance");
    LuaPush_float(L, obj.interpupillaryDistance);
    lua_setfield(L, -2, "interpupillaryDistance");
    LuaPush_float(L, obj.lensDistortionValues[4]);
    lua_setfield(L, -2, "lensDistortionValues[4]");
    LuaPush_float(L, obj.chromaAbCorrection[4]);
    lua_setfield(L, -2, "chromaAbCorrection[4]");
}

// raylib Functions (and data types) list
static luaL_Reg raylib_functions[] = {
REG(InitWindow)
REG(CloseWindow)
REG(IsWindowReady)
REG(WindowShouldClose)
REG(IsWindowMinimized)
REG(ToggleFullscreen)
REG(SetWindowIcon)
REG(SetWindowTitle)
REG(SetWindowPosition)
REG(SetWindowMonitor)
REG(SetWindowMinSize)
REG(SetWindowSize)
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
REG(BeginMode2D)
REG(EndMode2D)
REG(BeginMode3D)
REG(EndMode3D)
REG(BeginTextureMode)
REG(EndTextureMode)
REG(GetMouseRay)
REG(GetWorldToScreen)
REG(GetCameraMatrix)
REG(SetTargetFPS)
REG(GetFPS)
REG(GetFrameTime)
REG(GetTime)
REG(ColorToInt)
REG(ColorNormalize)
REG(ColorToHSV)
REG(GetColor)
REG(Fade)
REG(ShowLogo)
REG(SetConfigFlags)
REG(SetTraceLog)
REG(TraceLog)
REG(TakeScreenshot)
REG(GetRandomValue)
REG(IsFileExtension)
REG(GetExtension)
REG(GetFileName)
REG(GetDirectoryPath)
REG(GetWorkingDirectory)
REG(ChangeDirectory)
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
REG(SetMouseScale)
REG(GetMouseWheelMove)
REG(GetTouchX)
REG(GetTouchY)
REG(GetTouchPosition)
REG(SetGesturesEnabled)
REG(IsGestureDetected)
REG(GetGestureDetected)
REG(GetTouchPointsCount)
REG(GetGestureHoldDuration)
REG(GetGestureDragVector)
REG(GetGestureDragAngle)
REG(GetGesturePinchVector)
REG(GetGesturePinchAngle)
REG(SetCameraMode)
REG(UpdateCamera)
REG(SetCameraPanControl)
REG(SetCameraAltControl)
REG(SetCameraSmoothZoomControl)
REG(SetCameraMoveControls)
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
REG(DrawRectangleV)
REG(DrawRectangleRec)
REG(DrawRectanglePro)
REG(DrawRectangleGradientV)
REG(DrawRectangleGradientH)
REG(DrawRectangleGradientEx)
REG(DrawRectangleLines)
REG(DrawRectangleLinesEx)
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
REG(LoadImage)
REG(LoadImageEx)
REG(LoadImagePro)
REG(LoadImageRaw)
REG(ExportImage)
REG(LoadTexture)
REG(LoadTextureFromImage)
REG(LoadRenderTexture)
REG(UnloadImage)
REG(UnloadTexture)
REG(UnloadRenderTexture)
REG(GetImageData)
REG(GetImageDataNormalized)
REG(GetPixelDataSize)
REG(GetTextureData)
REG(UpdateTexture)
REG(ImageCopy)
REG(ImageToPOT)
REG(ImageFormat)
REG(ImageAlphaMask)
REG(ImageAlphaClear)
REG(ImageAlphaCrop)
REG(ImageAlphaPremultiply)
REG(ImageCrop)
REG(ImageResize)
REG(ImageResizeNN)
REG(ImageResizeCanvas)
REG(ImageMipmaps)
REG(ImageDither)
REG(ImageText)
REG(ImageTextEx)
REG(ImageDraw)
REG(ImageDrawRectangle)
REG(ImageDrawText)
REG(ImageDrawTextEx)
REG(ImageFlipVertical)
REG(ImageFlipHorizontal)
REG(ImageRotateCW)
REG(ImageRotateCCW)
REG(ImageColorTint)
REG(ImageColorInvert)
REG(ImageColorGrayscale)
REG(ImageColorContrast)
REG(ImageColorBrightness)
REG(ImageColorReplace)
REG(GenImageColor)
REG(GenImageGradientV)
REG(GenImageGradientH)
REG(GenImageGradientRadial)
REG(GenImageChecked)
REG(GenImageWhiteNoise)
REG(GenImagePerlinNoise)
REG(GenImageCellular)
REG(GenTextureMipmaps)
REG(SetTextureFilter)
REG(SetTextureWrap)
REG(DrawTexture)
REG(DrawTextureV)
REG(DrawTextureEx)
REG(DrawTextureRec)
REG(DrawTexturePro)
REG(GetFontDefault)
REG(LoadFont)
REG(LoadFontEx)
REG(LoadFontData)
REG(GenImageFontAtlas)
REG(UnloadFont)
REG(DrawFPS)
REG(DrawText)
REG(DrawTextEx)
REG(MeasureText)
REG(MeasureTextEx)
REG(FormatText)
REG(SubText)
REG(GetGlyphIndex)
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
REG(LoadModel)
REG(LoadModelFromMesh)
REG(UnloadModel)
REG(LoadMesh)
REG(UnloadMesh)
REG(ExportMesh)
REG(MeshBoundingBox)
REG(MeshTangents)
REG(MeshBinormals)
REG(GenMeshPlane)
REG(GenMeshCube)
REG(GenMeshSphere)
REG(GenMeshHemiSphere)
REG(GenMeshCylinder)
REG(GenMeshTorus)
REG(GenMeshKnot)
REG(GenMeshHeightmap)
REG(GenMeshCubicmap)
REG(LoadMaterial)
REG(LoadMaterialDefault)
REG(UnloadMaterial)
REG(DrawModel)
REG(DrawModelEx)
REG(DrawModelWires)
REG(DrawModelWiresEx)
REG(DrawBoundingBox)
REG(DrawBillboard)
REG(DrawBillboardRec)
REG(CheckCollisionSpheres)
REG(CheckCollisionBoxes)
REG(CheckCollisionBoxSphere)
REG(CheckCollisionRaySphere)
REG(CheckCollisionRaySphereEx)
REG(CheckCollisionRayBox)
REG(GetCollisionRayModel)
REG(GetCollisionRayTriangle)
REG(GetCollisionRayGround)
REG(LoadText)
REG(LoadShader)
REG(LoadShaderCode)
REG(UnloadShader)
REG(GetShaderDefault)
REG(GetTextureDefault)
REG(GetShaderLocation)
REG(SetShaderValue)
REG(SetShaderValuei)
REG(SetShaderValueMatrix)
REG(SetMatrixProjection)
REG(SetMatrixModelview)
REG(GetMatrixModelview)
REG(GenTextureCubemap)
REG(GenTextureIrradiance)
REG(GenTexturePrefilter)
REG(GenTextureBRDF)
REG(BeginShaderMode)
REG(EndShaderMode)
REG(BeginBlendMode)
REG(EndBlendMode)
REG(GetVrDeviceInfo)
REG(InitVrSimulator)
REG(CloseVrSimulator)
REG(IsVrSimulatorReady)
REG(SetVrDistortionShader)
REG(UpdateVrTracking)
REG(ToggleVrMode)
REG(BeginVrDrawing)
REG(EndVrDrawing)
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
REG(PlayMusicStream)
REG(UpdateMusicStream)
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
REG(IsAudioStreamPlaying)
REG(StopAudioStream)
REG(SetAudioStreamVolume)
REG(SetAudioStreamPitch)

    { NULL, NULL }  // sentinel: end signal
};