-------------------------------------------------------------------------------------------
--
--   raylib [shapes] example - Input Box
--
--  This example has been created using raylib 1.7 (www.raylib.com)
--  raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
--
--  Copyright (c) 2014-2017 Ramon Santamaria (@raysan5)
--
-------------------------------------------------------------------------------------------

local MAX_INPUT_CHARS = 9

-- Initialization
-------------------------------------------------------------------------------------------
local screenWidth = 800
local screenHeight = 450

InitWindow(screenWidth, screenHeight, "raylib [shapes] example - input box")

local name = ' '       -- TODO: name should be a string but its values must be accessed individually...
local letterCount = 0

local textBox = Rectangle(screenWidth/2 - 100, 180, 225, 50)
local mouseOnText = false

local framesCounter = 0

SetTargetFPS(60)       -- Set target frames-per-second
-------------------------------------------------------------------------------------------

-- Main game loop
while not WindowShouldClose() do            -- Detect window close button or ESC key
    -- Update
    ---------------------------------------------------------------------------------------
    if (CheckCollisionPointRec(GetMousePosition(), textBox)) then mouseOnText = true
    else mouseOnText = false end
    
    if (mouseOnText) then
        local key = GetKeyPressed()
        
        -- NOTE: Only allow keys in range [32..125]
        if ((key >= 32) and (key <= 125) and (letterCount < MAX_INPUT_CHARS)) then
            name[letterCount] = key
            letterCount = letterCount + 1
        end
        
        if (key == KEY_BACKSPACE) then
            letterCount = letterCount - 1
            name[letterCount] = '\0'
            
            if (letterCount < 0) then letterCount = 0 end
        end
    end
    
    if (mouseOnText) then framesCounter = framesCounter + 1
    else framesCounter = 0 end
    ---------------------------------------------------------------------------------------

    -- Draw
    ---------------------------------------------------------------------------------------
    BeginDrawing()

        ClearBackground(RAYWHITE)

        DrawText("PLACE MOUSE OVER INPUT BOX!", 240, 140, 20, GRAY)

        DrawRectangleRec(textBox, LIGHTGRAY)
        if (mouseOnText) then DrawRectangleLines(textBox.x, textBox.y, textBox.width, textBox.height, RED)
        else DrawRectangleLines(textBox.x, textBox.y, textBox.width, textBox.height, DARKGRAY) end
        
        DrawText(name, textBox.x + 5, textBox.y + 8, 40, MAROON)
        
        DrawText(string.format("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 315, 250, 20, DARKGRAY)

        if (mouseOnText) then
            if (letterCount < MAX_INPUT_CHARS) then
                -- Draw blinking underscore char
                if (((framesCounter/20)%2) == 0) then DrawText("_", textBox.x + 8 + MeasureText(name, 40), textBox.y + 12, 40, MAROON) end
            else DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY) end
        end

    EndDrawing()
    ---------------------------------------------------------------------------------------
end

-- De-Initialization
-------------------------------------------------------------------------------------------
CloseWindow()        -- Close window and OpenGL context
-------------------------------------------------------------------------------------------
