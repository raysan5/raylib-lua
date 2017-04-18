-------------------------------------------------------------------------------------------
--
--   raylib [shapes] example - Cubic-bezier lines
--
--  This example has been created using raylib 1.7 (www.raylib.com)
--  raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
--
--  Copyright (c) 2014-2017 Ramon Santamaria (@raysan5)
--
-------------------------------------------------------------------------------------------

-- Initialization
-------------------------------------------------------------------------------------------
local screenWidth = 800
local screenHeight = 450

SetConfigFlags(FLAG.MSAA_4X_HINT);
InitWindow(screenWidth, screenHeight, "raylib [shapes] example - cubic-bezier lines")

local startPoint = Vector2(0, 0)
local endPoint = Vector2(screenWidth, screenHeight)

SetTargetFPS(60)       -- Set target frames-per-second
-------------------------------------------------------------------------------------------

-- Main game loop
while not WindowShouldClose() do            -- Detect window close button or ESC key
    -- Update
    ---------------------------------------------------------------------------------------
    if (IsMouseButtonDown(MOUSE.LEFT_BUTTON)) then startPoint = GetMousePosition()
    elseif (IsMouseButtonDown(MOUSE.RIGHT_BUTTON)) then endPoint = GetMousePosition() end
    ---------------------------------------------------------------------------------------

    -- Draw
    ---------------------------------------------------------------------------------------
    BeginDrawing()

        ClearBackground(RAYWHITE)

        DrawText("USE MOUSE LEFT-RIGHT CLICK to DEFINE LINE START and END POINTS", 15, 20, 20, GRAY)

        DrawLineBezier(startPoint, endPoint, 2.0, RED)

    EndDrawing()
    ---------------------------------------------------------------------------------------
end

-- De-Initialization
-------------------------------------------------------------------------------------------
CloseWindow()        -- Close window and OpenGL context
-------------------------------------------------------------------------------------------
