-------------------------------------------------------------------------------------------
--
--  raylib [shaders] example - Apply a postprocessing shader to a scene
--
--  NOTE: This example requires raylib OpenGL 3.3 or ES2 versions for shaders support,
--        OpenGL 1.1 does not support shaders, recompile raylib to OpenGL 3.3 version.
--
--  NOTE: Shaders used in this example are #version 330 (OpenGL 3.3), to test this example
--        on OpenGL ES 2.0 platforms (Android, Raspberry Pi, HTML5), use #version 100 shaders
--        raylib comes with shaders ready for both versions, check raylib/shaders install folder
--
--  This example has been created using raylib 1.6 (www.raylib.com)
--  raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
--
--  Copyright (c) 2014-2016 Ramon Santamaria (@raysan5)
--
-------------------------------------------------------------------------------------------

local MAX_POSTPRO_SHADERS = 12

-- enum PostproShader
local FX_GRAYSCALE = 1
local FX_POSTERIZATION = 2
local FX_DREAM_VISION = 3
local FX_PIXELIZER = 4
local FX_CROSS_HATCHING = 5
local FX_CROSS_STITCHING = 6
local FX_PREDATOR_VIEW = 7
local FX_SCANLINES = 8
local FX_FISHEYE = 9
local FX_SOBEL = 10
local FX_BLOOM = 11
local FX_BLUR = 12
-- local FX_FXAA = 13

local postproShaderText = {
    "GRAYSCALE",
    "POSTERIZATION",
    "DREAM_VISION",
    "PIXELIZER",
    "CROSS_HATCHING",
    "CROSS_STITCHING",
    "PREDATOR_VIEW",
    "SCANLINES",
    "FISHEYE",
    "SOBEL",
    "BLOOM",
    "BLUR",
    -- "FXAA"
}

-- Initialization
-------------------------------------------------------------------------------------------
local screenWidth = 800
local screenHeight = 450

SetConfigFlags(FLAG.MSAA_4X_HINT)      -- Enable Multi Sampling Anti Aliasing 4x (if available)

InitWindow(screenWidth, screenHeight, "raylib [shaders] example - postprocessing shaders")

-- Define the camera to look into our 3d world
local camera = Camera(Vector3(3.0, 3.0, 3.0), Vector3(0.0, 1.5, 0.0), Vector3(0.0, 1.0, 0.0), 45.0)

local dwarf = LoadModel("resources/model/dwarf.obj")                   -- Load OBJ model
local texture = LoadTexture("resources/model/dwarf_diffuse.png")       -- Load model texture (diffuse map)
dwarf.material.texDiffuse = texture                                    -- Set dwarf model diffuse texture

local position = Vector3(0.0, 0.0, 0.0)                                -- Set model position

-- Load all postpro shaders
-- NOTE 1: All postpro shader use the base vertex shader
-- NOTE 2: We load the correct shader depending on GLSL version
local shaders = {}

shaders[FX_GRAYSCALE] = LoadShader("resources/shaders/glsl330/base.vs", "resources/shaders/glsl330/grayscale.fs")
shaders[FX_POSTERIZATION] = LoadShader("resources/shaders/glsl330/base.vs", "resources/shaders/glsl330/posterization.fs")
shaders[FX_DREAM_VISION] = LoadShader("resources/shaders/glsl330/base.vs", "resources/shaders/glsl330/dream_vision.fs")
shaders[FX_PIXELIZER] = LoadShader("resources/shaders/glsl330/base.vs", "resources/shaders/glsl330/pixelizer.fs")
shaders[FX_CROSS_HATCHING] = LoadShader("resources/shaders/glsl330/base.vs", "resources/shaders/glsl330/cross_hatching.fs")
shaders[FX_CROSS_STITCHING] = LoadShader("resources/shaders/glsl330/base.vs", "resources/shaders/glsl330/cross_stitching.fs")
shaders[FX_PREDATOR_VIEW] = LoadShader("resources/shaders/glsl330/base.vs", "resources/shaders/glsl330/predator.fs")
shaders[FX_SCANLINES] = LoadShader("resources/shaders/glsl330/base.vs", "resources/shaders/glsl330/scanlines.fs")
shaders[FX_FISHEYE] = LoadShader("resources/shaders/glsl330/base.vs", "resources/shaders/glsl330/fisheye.fs")
shaders[FX_SOBEL] = LoadShader("resources/shaders/glsl330/base.vs", "resources/shaders/glsl330/sobel.fs")
shaders[FX_BLOOM] = LoadShader("resources/shaders/glsl330/base.vs", "resources/shaders/glsl330/bloom.fs")
shaders[FX_BLUR] = LoadShader("resources/shaders/glsl330/base.vs", "resources/shaders/glsl330/blur.fs")

local currentShader = FX_GRAYSCALE;

-- Create a RenderTexture2D to be used for render to texture
local target = LoadRenderTexture(screenWidth, screenHeight)

-- Setup orbital camera
SetCameraMode(camera, CameraMode.ORBITAL)   -- Set an orbital camera mode

SetTargetFPS(60)                            -- Set our game to run at 60 frames-per-second
-------------------------------------------------------------------------------------------

-- Main game loop
while not WindowShouldClose() do            -- Detect window close button or ESC key
    -- Update
    ---------------------------------------------------------------------------------------
    camera = UpdateCamera(camera)           -- Update camera
    
    if (IsKeyPressed(KEY.RIGHT)) then currentShader = currentShader + 1
    elseif (IsKeyPressed(KEY.LEFT)) then currentShader = currentShader - 1 end
    
    if (currentShader > MAX_POSTPRO_SHADERS) then currentShader = 1
    elseif (currentShader < 1) then currentShader = MAX_POSTPRO_SHADERS end
    ---------------------------------------------------------------------------------------

    -- Draw
    ---------------------------------------------------------------------------------------
    BeginDrawing()

        ClearBackground(RAYWHITE)

        BeginTextureMode(target)       -- Enable drawing to texture

            Begin3dMode(camera)

                DrawModel(dwarf, position, 2.0, WHITE)   -- Draw 3d model with texture

                DrawGrid(10, 1.0)      -- Draw a grid

            End3dMode()
            
        EndTextureMode()           -- End drawing to texture (now we have a texture available for next passes)
        
        BeginShaderMode(shaders[currentShader])
        
            -- NOTE: Render texture must be y-flipped due to default OpenGL coordinates (left-bottom)
            DrawTextureRec(target.texture, Rectangle(0, 0, target.texture.width, -target.texture.height), Vector2(0, 0), WHITE)
            
        EndShaderMode()
        
        DrawRectangle(0, 9, 580, 30, Fade(LIGHTGRAY, 0.7))
        
        DrawText("(c) Dwarf 3D model by David Moreno", screenWidth - 200, screenHeight - 20, 10, DARKGRAY)
        
        DrawText("CURRENT POSTPRO SHADER:", 10, 15, 20, BLACK)
        DrawText(postproShaderText[currentShader], 330, 15, 20, RED)
        DrawText("< >", 540, 10, 30, DARKBLUE)
        
        DrawFPS(700, 15)
            
    EndDrawing()
    ---------------------------------------------------------------------------------------
end

-- De-Initialization
-------------------------------------------------------------------------------------------

-- Unload all postpro shaders
for i = 1, MAX_POSTPRO_SHADERS do UnloadShader(shaders[i]) end

UnloadTexture(texture)         -- Unload texture
UnloadModel(dwarf)             -- Unload model
UnloadRenderTexture(target)    -- Unload render texture

CloseWindow()                  -- Close window and OpenGL context
-------------------------------------------------------------------------------------------