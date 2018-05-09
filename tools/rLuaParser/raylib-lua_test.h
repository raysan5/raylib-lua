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

// Trace log type
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
// Initialize window and OpenGL context
int lua_InitWindow(lua_State *L)
{
    int width = LuaGetArgument_int(L, 1);
    int height = LuaGetArgument_int(L, 2);
    const char = LuaGetArgument_const(L, 3);
    InitWindow(width, height, char);
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
    const char = LuaGetArgument_const(L, 1);
    SetWindowTitle(char);
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
int lua_Begin2dMode(lua_State *L)
{
    Camera2D camera = LuaGetArgument_Camera2D(L, 1);
    Begin2dMode(camera);
    return 0;
}

// Ends 2D mode with custom camera
int lua_End2dMode(lua_State *L)
{
    End2dMode();
    return 0;
}

// Initializes 3D mode with custom camera (3D)
int lua_Begin3dMode(lua_State *L)
{
    Camera camera = LuaGetArgument_Camera(L, 1);
    Begin3dMode(camera);
    return 0;
}

// Ends 3D mode and returns to default 2D orthographic mode
int lua_End3dMode(lua_State *L)
{
    End3dMode();
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
// Returns normalized float array for a Color
int lua_*ColorToFloat(lua_State *L)
{
    Color color = LuaGetArgument_Color(L, 1);
    float result = *ColorToFloat(color);
    LuaPush_float(L, result);
    return 1;
}

// Returns hexadecimal value for a Color
int lua_ColorToInt(lua_State *L)
{
    Color color = LuaGetArgument_Color(L, 1);
    int result = ColorToInt(color);
    LuaPush_int(L, result);
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
    unsigned char = LuaGetArgument_unsigned(L, 1);
    SetConfigFlags(char);
    return 0;
}

// Enable trace log message types (bit flags based)
int lua_SetTraceLog(lua_State *L)
{
    unsigned char = LuaGetArgument_unsigned(L, 1);
    SetTraceLog(char);
    return 0;
}

// Show trace log messages (LOG_INFO, LOG_WARNING, LOG_ERROR, LOG_DEBUG)
int lua_TraceLog(lua_State *L)
{
    int logType = LuaGetArgument_int(L, 1);
    const char = LuaGetArgument_const(L, 2);
    ... char = LuaGetArgument_...(L, 3);
    TraceLog(logType, char, char);
    return 0;
}

// Takes a screenshot of current screen (saved a .png)
int lua_TakeScreenshot(lua_State *L)
{
    const char = LuaGetArgument_const(L, 1);
    TakeScreenshot(char);
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
    const char = LuaGetArgument_const(L, 1);
    const char = LuaGetArgument_const(L, 2);
    bool result = IsFileExtension(char, char);
    LuaPush_bool(L, result);
    return 1;
}

//RLAPI const char *GetExtension(const char *fileName);             // Get pointer to extension for a filename string
//RLAPI const char *GetFileName(const char *filePath);              // Get pointer to filename for a path string
//RLAPI const char *GetDirectoryPath(const char *fileName);         // Get full path for a given fileName (uses static string)
//RLAPI const char *GetWorkingDirectory(void);                      // Get current working directory (uses static string)
// Change working directory, returns true if success
int lua_ChangeDirectory(lua_State *L)
{
    const char = LuaGetArgument_const(L, 1);
    bool result = ChangeDirectory(char);
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
int lua_**GetDroppedFiles(lua_State *L)
{
    int *count = LuaGetArgument_int(L, 1);
    char result = **GetDroppedFiles(*count);
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

// Check gamepad name (if available)
int lua_IsGamepadName(lua_State *L)
{
    int gamepad = LuaGetArgument_int(L, 1);
    const char = LuaGetArgument_const(L, 2);
    bool result = IsGamepadName(gamepad, char);
    LuaPush_bool(L, result);
    return 1;
}

//RLAPI const char *GetGamepadName(int gamepad);                // Return gamepad internal name id
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
    unsigned int = LuaGetArgument_unsigned(L, 1);
    SetGesturesEnabled(int);
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
    Camera *camera = LuaGetArgument_Camera(L, 1);
    UpdateCamera(*camera);
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
    Vector2 *points = LuaGetArgument_Vector2(L, 1);
    int numPoints = LuaGetArgument_int(L, 2);
    Color color = LuaGetArgument_Color(L, 3);
    DrawPolyEx(*points, numPoints, color);
    return 0;
}

// Draw polygon lines
int lua_DrawPolyExLines(lua_State *L)
{
    Vector2 *points = LuaGetArgument_Vector2(L, 1);
    int numPoints = LuaGetArgument_int(L, 2);
    Color color = LuaGetArgument_Color(L, 3);
    DrawPolyExLines(*points, numPoints, color);
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
    const char = LuaGetArgument_const(L, 1);
    Image result = LoadImage(char);
    LuaPush_Image(L, result);
    return 1;
}

// Load image from Color array data (RGBA - 32bit)
int lua_LoadImageEx(lua_State *L)
{
    Color *pixels = LuaGetArgument_Color(L, 1);
    int width = LuaGetArgument_int(L, 2);
    int height = LuaGetArgument_int(L, 3);
    Image result = LoadImageEx(*pixels, width, height);
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
    const char = LuaGetArgument_const(L, 1);
    int width = LuaGetArgument_int(L, 2);
    int height = LuaGetArgument_int(L, 3);
    int format = LuaGetArgument_int(L, 4);
    int headerSize = LuaGetArgument_int(L, 5);
    Image result = LoadImageRaw(char, width, height, format, headerSize);
    LuaPush_Image(L, result);
    return 1;
}

// Export image as a PNG file
int lua_ExportImage(lua_State *L)
{
    const char = LuaGetArgument_const(L, 1);
    Image image = LuaGetArgument_Image(L, 2);
    ExportImage(char, image);
    return 0;
}

// Load texture from file into GPU memory (VRAM)
int lua_LoadTexture(lua_State *L)
{
    const char = LuaGetArgument_const(L, 1);
    Texture2D result = LoadTexture(char);
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
int lua_*GetImageData(lua_State *L)
{
    Image image = LuaGetArgument_Image(L, 1);
    Color result = *GetImageData(image);
    LuaPush_Color(L, result);
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
    const void = LuaGetArgument_const(L, 2);
    UpdateTexture(texture, void);
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
    Image *image = LuaGetArgument_Image(L, 1);
    Color fillColor = LuaGetArgument_Color(L, 2);
    ImageToPOT(*image, fillColor);
    return 0;
}

// Convert image data to desired format
int lua_ImageFormat(lua_State *L)
{
    Image *image = LuaGetArgument_Image(L, 1);
    int newFormat = LuaGetArgument_int(L, 2);
    ImageFormat(*image, newFormat);
    return 0;
}

// Apply alpha mask to image
int lua_ImageAlphaMask(lua_State *L)
{
    Image *image = LuaGetArgument_Image(L, 1);
    Image alphaMask = LuaGetArgument_Image(L, 2);
    ImageAlphaMask(*image, alphaMask);
    return 0;
}

// Clear alpha channel to desired color
int lua_ImageAlphaClear(lua_State *L)
{
    Image *image = LuaGetArgument_Image(L, 1);
    Color color = LuaGetArgument_Color(L, 2);
    float threshold = LuaGetArgument_float(L, 3);
    ImageAlphaClear(*image, color, threshold);
    return 0;
}

// Crop image depending on alpha value
int lua_ImageAlphaCrop(lua_State *L)
{
    Image *image = LuaGetArgument_Image(L, 1);
    float threshold = LuaGetArgument_float(L, 2);
    ImageAlphaCrop(*image, threshold);
    return 0;
}

// Premultiply alpha channel
int lua_ImageAlphaPremultiply(lua_State *L)
{
    Image *image = LuaGetArgument_Image(L, 1);
    ImageAlphaPremultiply(*image);
    return 0;
}

// Crop an image to a defined rectangle
int lua_ImageCrop(lua_State *L)
{
    Image *image = LuaGetArgument_Image(L, 1);
    Rectangle crop = LuaGetArgument_Rectangle(L, 2);
    ImageCrop(*image, crop);
    return 0;
}

// Resize and image (bilinear filtering)
int lua_ImageResize(lua_State *L)
{
    Image *image = LuaGetArgument_Image(L, 1);
    int newWidth = LuaGetArgument_int(L, 2);
    int newHeight = LuaGetArgument_int(L, 3);
    ImageResize(*image, newWidth, newHeight);
    return 0;
}

// Resize and image (Nearest-Neighbor scaling algorithm)
int lua_ImageResizeNN(lua_State *L)
{
    Image *image = LuaGetArgument_Image(L, 1);
    int newWidth = LuaGetArgument_int(L, 2);
    int newHeight = LuaGetArgument_int(L, 3);
    ImageResizeNN(*image, newWidth, newHeight);
    return 0;
}

// Generate all mipmap levels for a provided image
int lua_ImageMipmaps(lua_State *L)
{
    Image *image = LuaGetArgument_Image(L, 1);
    ImageMipmaps(*image);
    return 0;
}

// Dither image data to 16bpp or lower (Floyd-Steinberg dithering)
int lua_ImageDither(lua_State *L)
{
    Image *image = LuaGetArgument_Image(L, 1);
    int rBpp = LuaGetArgument_int(L, 2);
    int gBpp = LuaGetArgument_int(L, 3);
    int bBpp = LuaGetArgument_int(L, 4);
    int aBpp = LuaGetArgument_int(L, 5);
    ImageDither(*image, rBpp, gBpp, bBpp, aBpp);
    return 0;
}

// Create an image from text (default font)
int lua_ImageText(lua_State *L)
{
    const char = LuaGetArgument_const(L, 1);
    int fontSize = LuaGetArgument_int(L, 2);
    Color color = LuaGetArgument_Color(L, 3);
    Image result = ImageText(char, fontSize, color);
    LuaPush_Image(L, result);
    return 1;
}

// Create an image from text (custom sprite font)
int lua_ImageTextEx(lua_State *L)
{
    SpriteFont font = LuaGetArgument_SpriteFont(L, 1);
    const char = LuaGetArgument_const(L, 2);
    float fontSize = LuaGetArgument_float(L, 3);
    int spacing = LuaGetArgument_int(L, 4);
    Color tint = LuaGetArgument_Color(L, 5);
    Image result = ImageTextEx(font, char, fontSize, spacing, tint);
    LuaPush_Image(L, result);
    return 1;
}

// Draw a source image within a destination image
int lua_ImageDraw(lua_State *L)
{
    Image *dst = LuaGetArgument_Image(L, 1);
    Image src = LuaGetArgument_Image(L, 2);
    Rectangle srcRec = LuaGetArgument_Rectangle(L, 3);
    Rectangle dstRec = LuaGetArgument_Rectangle(L, 4);
    ImageDraw(*dst, src, srcRec, dstRec);
    return 0;
}

// Draw rectangle within an image
int lua_ImageDrawRectangle(lua_State *L)
{
    Image *dst = LuaGetArgument_Image(L, 1);
    Vector2 position = LuaGetArgument_Vector2(L, 2);
    Rectangle rec = LuaGetArgument_Rectangle(L, 3);
    Color color = LuaGetArgument_Color(L, 4);
    ImageDrawRectangle(*dst, position, rec, color);
    return 0;
}

// Draw text (default font) within an image (destination)
int lua_ImageDrawText(lua_State *L)
{
    Image *dst = LuaGetArgument_Image(L, 1);
    Vector2 position = LuaGetArgument_Vector2(L, 2);
    const char = LuaGetArgument_const(L, 3);
    int fontSize = LuaGetArgument_int(L, 4);
    Color color = LuaGetArgument_Color(L, 5);
    ImageDrawText(*dst, position, char, fontSize, color);
    return 0;
}

// Draw text (custom sprite font) within an image (destination)
int lua_ImageDrawTextEx(lua_State *L)
{
    Image *dst = LuaGetArgument_Image(L, 1);
    Vector2 position = LuaGetArgument_Vector2(L, 2);
    SpriteFont font = LuaGetArgument_SpriteFont(L, 3);
    const char = LuaGetArgument_const(L, 4);
    float fontSize = LuaGetArgument_float(L, 5);
    int spacing = LuaGetArgument_int(L, 6);
    Color color = LuaGetArgument_Color(L, 7);
    ImageDrawTextEx(*dst, position, font, char, fontSize, spacing, color);
    return 0;
}

// Flip image vertically
int lua_ImageFlipVertical(lua_State *L)
{
    Image *image = LuaGetArgument_Image(L, 1);
    ImageFlipVertical(*image);
    return 0;
}

// Flip image horizontally
int lua_ImageFlipHorizontal(lua_State *L)
{
    Image *image = LuaGetArgument_Image(L, 1);
    ImageFlipHorizontal(*image);
    return 0;
}

// Modify image color: tint
int lua_ImageColorTint(lua_State *L)
{
    Image *image = LuaGetArgument_Image(L, 1);
    Color color = LuaGetArgument_Color(L, 2);
    ImageColorTint(*image, color);
    return 0;
}

// Modify image color: invert
int lua_ImageColorInvert(lua_State *L)
{
    Image *image = LuaGetArgument_Image(L, 1);
    ImageColorInvert(*image);
    return 0;
}

// Modify image color: grayscale
int lua_ImageColorGrayscale(lua_State *L)
{
    Image *image = LuaGetArgument_Image(L, 1);
    ImageColorGrayscale(*image);
    return 0;
}

// Modify image color: contrast (-100 to 100)
int lua_ImageColorContrast(lua_State *L)
{
    Image *image = LuaGetArgument_Image(L, 1);
    float contrast = LuaGetArgument_float(L, 2);
    ImageColorContrast(*image, contrast);
    return 0;
}

// Modify image color: brightness (-255 to 255)
int lua_ImageColorBrightness(lua_State *L)
{
    Image *image = LuaGetArgument_Image(L, 1);
    int brightness = LuaGetArgument_int(L, 2);
    ImageColorBrightness(*image, brightness);
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
    Texture2D *texture = LuaGetArgument_Texture2D(L, 1);
    GenTextureMipmaps(*texture);
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
// SpriteFont loading/unloading functions
// Get the default SpriteFont
int lua_GetDefaultFont(lua_State *L)
{
    SpriteFont result = GetDefaultFont();
    LuaPush_SpriteFont(L, result);
    return 1;
}

// Load SpriteFont from file into GPU memory (VRAM)
int lua_LoadSpriteFont(lua_State *L)
{
    const char = LuaGetArgument_const(L, 1);
    SpriteFont result = LoadSpriteFont(char);
    LuaPush_SpriteFont(L, result);
    return 1;
}

// Load SpriteFont from file with extended parameters
int lua_LoadSpriteFontEx(lua_State *L)
{
    const char = LuaGetArgument_const(L, 1);
    int fontSize = LuaGetArgument_int(L, 2);
    int charsCount = LuaGetArgument_int(L, 3);
    int *fontChars = LuaGetArgument_int(L, 4);
    SpriteFont result = LoadSpriteFontEx(char, fontSize, charsCount, *fontChars);
    LuaPush_SpriteFont(L, result);
    return 1;
}

// Unload SpriteFont from GPU memory (VRAM)
int lua_UnloadSpriteFont(lua_State *L)
{
    SpriteFont font = LuaGetArgument_SpriteFont(L, 1);
    UnloadSpriteFont(font);
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
    const char = LuaGetArgument_const(L, 1);
    int posX = LuaGetArgument_int(L, 2);
    int posY = LuaGetArgument_int(L, 3);
    int fontSize = LuaGetArgument_int(L, 4);
    Color color = LuaGetArgument_Color(L, 5);
    DrawText(char, posX, posY, fontSize, color);
    return 0;
}

// Draw text using SpriteFont and additional parameters
int lua_DrawTextEx(lua_State *L)
{
    SpriteFont font = LuaGetArgument_SpriteFont(L, 1);
    const char* = LuaGetArgument_const(L, 2);
    Vector2 position = LuaGetArgument_Vector2(L, 3);
    float fontSize = LuaGetArgument_float(L, 4);
    int spacing = LuaGetArgument_int(L, 5);
    Color tint = LuaGetArgument_Color(L, 6);
    DrawTextEx(font, char*, position, fontSize, spacing, tint);
    return 0;
}

// Text misc. functions
// Measure string width for default font
int lua_MeasureText(lua_State *L)
{
    const char = LuaGetArgument_const(L, 1);
    int fontSize = LuaGetArgument_int(L, 2);
    int result = MeasureText(char, fontSize);
    LuaPush_int(L, result);
    return 1;
}

// Measure string size for SpriteFont
int lua_MeasureTextEx(lua_State *L)
{
    SpriteFont font = LuaGetArgument_SpriteFont(L, 1);
    const char = LuaGetArgument_const(L, 2);
    float fontSize = LuaGetArgument_float(L, 3);
    int spacing = LuaGetArgument_int(L, 4);
    Vector2 result = MeasureTextEx(font, char, fontSize, spacing);
    LuaPush_Vector2(L, result);
    return 1;
}

// Formatting of text with variables to 'embed'
int lua_char *FormatText(lua_State *L)
{
    const char = LuaGetArgument_const(L, 1);
    ... char = LuaGetArgument_...(L, 2);
    const result = char *FormatText(char, char);
    LuaPush_const(L, result);
    return 1;
}

// Get a piece of a text string
int lua_char *SubText(lua_State *L)
{
    const char = LuaGetArgument_const(L, 1);
    int position = LuaGetArgument_int(L, 2);
    int length = LuaGetArgument_int(L, 3);
    const result = char *SubText(char, position, length);
    LuaPush_const(L, result);
    return 1;
}

// Returns index position for a unicode character on sprite font
int lua_GetGlyphIndex(lua_State *L)
{
    SpriteFont font = LuaGetArgument_SpriteFont(L, 1);
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
    const char = LuaGetArgument_const(L, 1);
    Model result = LoadModel(char);
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
    const char = LuaGetArgument_const(L, 1);
    Mesh result = LoadMesh(char);
    LuaPush_Mesh(L, result);
    return 1;
}

// Unload mesh from memory (RAM and/or VRAM)
int lua_UnloadMesh(lua_State *L)
{
    Mesh *mesh = LuaGetArgument_Mesh(L, 1);
    UnloadMesh(*mesh);
    return 0;
}

// Export mesh as an OBJ file
int lua_ExportMesh(lua_State *L)
{
    const char = LuaGetArgument_const(L, 1);
    Mesh mesh = LuaGetArgument_Mesh(L, 2);
    ExportMesh(char, mesh);
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
    Mesh *mesh = LuaGetArgument_Mesh(L, 1);
    MeshTangents(*mesh);
    return 0;
}

// Compute mesh binormals
int lua_MeshBinormals(lua_State *L)
{
    Mesh *mesh = LuaGetArgument_Mesh(L, 1);
    MeshBinormals(*mesh);
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
    const char = LuaGetArgument_const(L, 1);
    Material result = LoadMaterial(char);
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
    Vector3 *collisionPoint = LuaGetArgument_Vector3(L, 4);
    bool result = CheckCollisionRaySphereEx(ray, spherePosition, sphereRadius, *collisionPoint);
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
    Model *model = LuaGetArgument_Model(L, 2);
    RayHitInfo result = GetCollisionRayModel(ray, *model);
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
int lua_*LoadText(lua_State *L)
{
    const char = LuaGetArgument_const(L, 1);
    char result = *LoadText(char);
    LuaPush_char(L, result);
    return 1;
}

// Load shader from files and bind default locations
int lua_LoadShader(lua_State *L)
{
    const char = LuaGetArgument_const(L, 1);
    const char = LuaGetArgument_const(L, 2);
    Shader result = LoadShader(char, char);
    LuaPush_Shader(L, result);
    return 1;
}

// Load shader from code strings and bind default locations
int lua_LoadShaderCode(lua_State *L)
{
    char *vsCode = LuaGetArgument_char(L, 1);
    char *fsCode = LuaGetArgument_char(L, 2);
    Shader result = LoadShaderCode(*vsCode, *fsCode);
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
    const char = LuaGetArgument_const(L, 2);
    int result = GetShaderLocation(shader, char);
    LuaPush_int(L, result);
    return 1;
}

// Set shader uniform value (float)
int lua_SetShaderValue(lua_State *L)
{
    Shader shader = LuaGetArgument_Shader(L, 1);
    int uniformLoc = LuaGetArgument_int(L, 2);
    const float = LuaGetArgument_const(L, 3);
    int size = LuaGetArgument_int(L, 4);
    SetShaderValue(shader, uniformLoc, float, size);
    return 0;
}

// Set shader uniform value (int)
int lua_SetShaderValuei(lua_State *L)
{
    Shader shader = LuaGetArgument_Shader(L, 1);
    int uniformLoc = LuaGetArgument_int(L, 2);
    const int = LuaGetArgument_const(L, 3);
    int size = LuaGetArgument_int(L, 4);
    SetShaderValuei(shader, uniformLoc, int, size);
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
    Camera *camera = LuaGetArgument_Camera(L, 1);
    UpdateVrTracking(*camera);
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
    const char = LuaGetArgument_const(L, 1);
    Wave result = LoadWave(char);
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
    const char = LuaGetArgument_const(L, 1);
    Sound result = LoadSound(char);
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
    const void = LuaGetArgument_const(L, 2);
    int samplesCount = LuaGetArgument_int(L, 3);
    UpdateSound(sound, void, samplesCount);
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
    Wave *wave = LuaGetArgument_Wave(L, 1);
    int sampleRate = LuaGetArgument_int(L, 2);
    int sampleSize = LuaGetArgument_int(L, 3);
    int channels = LuaGetArgument_int(L, 4);
    WaveFormat(*wave, sampleRate, sampleSize, channels);
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
    Wave *wave = LuaGetArgument_Wave(L, 1);
    int initSample = LuaGetArgument_int(L, 2);
    int finalSample = LuaGetArgument_int(L, 3);
    WaveCrop(*wave, initSample, finalSample);
    return 0;
}

// Get samples data from wave as a floats array
int lua_*GetWaveData(lua_State *L)
{
    Wave wave = LuaGetArgument_Wave(L, 1);
    float result = *GetWaveData(wave);
    LuaPush_float(L, result);
    return 1;
}

// Music management functions
// Load music stream from file
int lua_LoadMusicStream(lua_State *L)
{
    const char = LuaGetArgument_const(L, 1);
    Music result = LoadMusicStream(char);
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
    unsigned int = LuaGetArgument_unsigned(L, 1);
    unsigned int = LuaGetArgument_unsigned(L, 2);
    unsigned int = LuaGetArgument_unsigned(L, 3);
    AudioStream result = InitAudioStream(int, int, int);
    LuaPush_AudioStream(L, result);
    return 1;
}

// Update audio stream buffers with data
int lua_UpdateAudioStream(lua_State *L)
{
    AudioStream stream = LuaGetArgument_AudioStream(L, 1);
    const void = LuaGetArgument_const(L, 2);
    int samplesCount = LuaGetArgument_int(L, 3);
    UpdateAudioStream(stream, void, samplesCount);
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

