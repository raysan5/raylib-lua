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

// Get pointer to extension for a filename string
int lua_char *GetExtension(lua_State *L)
{
    const char = LuaGetArgument_const(L, 1);
    const result = char *GetExtension(char);
    LuaPush_const(L, result);
    return 1;
}

// Get pointer to filename for a path string
int lua_char *GetFileName(lua_State *L)
{
    const char = LuaGetArgument_const(L, 1);
    const result = char *GetFileName(char);
    LuaPush_const(L, result);
    return 1;
}

// Get full path for a given fileName (uses static string)
int lua_char *GetDirectoryPath(lua_State *L)
{
    const char = LuaGetArgument_const(L, 1);
    const result = char *GetDirectoryPath(char);
    LuaPush_const(L, result);
    return 1;
}

// Get current working directory (uses static string)
int lua_char *GetWorkingDirectory(lua_State *L)
{
    const result = char *GetWorkingDirectory();
    LuaPush_const(L, result);
    return 1;
}

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

// Return gamepad internal name id
int lua_char *GetGamepadName(lua_State *L)
{
    int gamepad = LuaGetArgument_int(L, 1);
    const result = char *GetGamepadName(gamepad);
    LuaPush_const(L, result);
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

// Basic shapes colli