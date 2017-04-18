-------------------------------------------------------------------------------------------
--
--  raylib [textures] example - Texture loading and drawing a part defined by a rectangle
--
--  This example has been created using raylib 1.6 (www.raylib.com)
--  raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
--
--  Copyright (c) 2014-2016 Ramon Santamaria (@raysan5)
--
-------------------------------------------------------------------------------------------

local MAX_FRAME_SPEED = 14
local MIN_FRAME_SPEED = 1

-- Initialization
-------------------------------------------------------------------------------------------
local screenWidth = 800
local screenHeight = 450

InitWindow(screenWidth, screenHeight, "raylib [texture] example - texture rectangle")

-- NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
local scarfy = LoadTexture("resources/scarfy.png")        -- Texture loading

local position = Vector2(350.0, 280.0)
local frameRec = Rectangle(0, 0, scarfy.width/6, scarfy.height)
local currentFrame = 0

local framesCounter = 0
local framesSpeed = 8           -- Number of spritesheet frames shown by second

SetTargetFPS(60);               -- Set our game to run at 60 frames-per-second
-------------------------------------------------------------------------------------------

-- Main game loop
while not WindowShouldClose() do            -- Detect window close button or ESC key
    -- Update
    ---------------------------------------------------------------------------------------
    framesCounter = framesCounter + 1
        
    if (framesCounter >= (60/framesSpeed)) then
        framesCounter = 0
        currentFrame = currentFrame + 1
            
        if (currentFrame > 5) then currentFrame = 0 end
            
        frameRec.x = currentFrame*scarfy.width/6
    end
        
    if (IsKeyPressed(KEY.RIGHT)) then framesSpeed = framesSpeed + 1
    elseif (IsKeyPressed(KEY.LEFT)) then framesSpeed = framesSpeed - 1 end
        
    if (framesSpeed > MAX_FRAME_SPEED) then framesSpeed = MAX_FRAME_SPEED
    elseif (framesSpeed < MIN_FRAME_SPEED) then framesSpeed = MIN_FRAME_SPEED end
    ---------------------------------------------------------------------------------------

    -- Draw
    ---------------------------------------------------------------------------------------
    BeginDrawing()

        ClearBackground(RAYWHITE)

        DrawTexture(scarfy, 15, 40, WHITE)
        DrawRectangleLines(15, 40, scarfy.width, scarfy.height, LIME)
        
        DrawRectangleLines(15 + frameRec.x, 40 + frameRec.y, frameRec.width, frameRec.height, RED)
            
        DrawText("FRAME SPEED: ", 165, 210, 10, DARKGRAY)
        DrawText(string.format("%02i FPS", framesSpeed), 575, 210, 10, DARKGRAY)
        DrawText("PRESS RIGHT/LEFT KEYS to CHANGE SPEED!", 290, 240, 10, DARKGRAY)
            
        for i = 1, MAX_FRAME_SPEED do
            if (i <= framesSpeed) then DrawRectangle(250 + 21*i, 205, 20, 20, RED) end
            DrawRectangleLines(250 + 21*i, 205, 20, 20, MAROON)
        end
            
        DrawTextureRec(scarfy, frameRec, position, WHITE)   -- Draw part of the texture

        DrawText("(c) Scarfy sprite by Eiden Marsal", screenWidth - 200, screenHeight - 20, 10, GRAY)

    EndDrawing()
    ---------------------------------------------------------------------------------------
end

-- De-Initialization
-------------------------------------------------------------------------------------------
UnloadTexture(scarfy)         -- Texture unloading

CloseWindow()                 -- Close window and OpenGL context
-------------------------------------------------------------------------------------------
