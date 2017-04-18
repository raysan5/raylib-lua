-------------------------------------------------------------------------------------------
--
--  raylib [text] example - raylib bitmap font (rbmf) loading and usage
--
--  NOTE: raylib is distributed with some free to use fonts (even for commercial pourposes!)
--        To view details and credits for those fonts, check raylib license file
--
--  This example has been created using raylib 1.6 (www.raylib.com)
--  raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
--
--  Copyright (c) 2014-2016 Ramon Santamaria (@raysan5)
--
-------------------------------------------------------------------------------------------

-- Initialization
-------------------------------------------------------------------------------------------
local screenWidth = 800
local screenHeight = 450

InitWindow(screenWidth, screenHeight, "raylib [text] example - rBMF fonts")

-- NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
local fonts = {}

fonts[1] = LoadSpriteFont("resources/fonts/alagard.png")
fonts[2] = LoadSpriteFont("resources/fonts/pixelplay.png")
fonts[3] = LoadSpriteFont("resources/fonts/mecha.png")
fonts[4] = LoadSpriteFont("resources/fonts/setback.png")
fonts[5] = LoadSpriteFont("resources/fonts/romulus.png")
fonts[6] = LoadSpriteFont("resources/fonts/pixantiqua.png")
fonts[7] = LoadSpriteFont("resources/fonts/alpha_beta.png")
fonts[8] = LoadSpriteFont("resources/fonts/jupiter_crash.png")

local messages = { "ALAGARD FONT designed by Hewett Tsoi", 
                   "PIXELPLAY FONT designed by Aleksander Shevchuk",
                   "MECHA FONT designed by Captain Falcon",  
                   "SETBACK FONT designed by Brian Kent (AEnigma)", 
                   "ROMULUS FONT designed by Hewett Tsoi", 
                   "PIXANTIQUA FONT designed by Gerhard Grossmann",
                   "ALPHA_BETA FONT designed by Brian Kent (AEnigma)",
                   "JUPITER_CRASH FONT designed by Brian Kent (AEnigma)" }
                            
local spacings = { 2, 4, 8, 4, 3, 4, 4, 1 }

local positions = {}

for i = 1, 8 do
    positions[i] = Vector2(0, 0)
    positions[i].x = screenWidth/2 - MeasureTextEx(fonts[i], messages[i], fonts[i].baseSize*2, spacings[i]).x/2
    positions[i].y = 60 + fonts[i].baseSize + 45*(i - 1)
end

-- Small Y position corrections
positions[4].y = positions[4].y + 8
positions[5].y = positions[5].y + 2
positions[8].y = positions[8].y - 8

local colors = { MAROON, ORANGE, DARKGREEN, DARKBLUE, DARKPURPLE, LIME, GOLD, RED }

SetTargetFPS(60)            -- Set target frames-per-second
-------------------------------------------------------------------------------------------

-- Main game loop
while not WindowShouldClose() do            -- Detect window close button or ESC key
    -- Update
    ---------------------------------------------------------------------------------------
    -- TODO: Update your variables here
    ---------------------------------------------------------------------------------------

    -- Draw
    ---------------------------------------------------------------------------------------
    BeginDrawing()

        ClearBackground(RAYWHITE)
        
        DrawText("free fonts included with raylib", 250, 20, 20, DARKGRAY)
        DrawLine(220, 50, 590, 50, DARKGRAY)
        
        for i = 1, 8 do
            DrawTextEx(fonts[i], messages[i], positions[i], fonts[i].baseSize*2, spacings[i], colors[i])
        end

    EndDrawing()
    ---------------------------------------------------------------------------------------
end

-- De-Initialization
-------------------------------------------------------------------------------------------
for i = 1, 8 do UnloadSpriteFont(fonts[i]) end       -- SpriteFont unloading

CloseWindow()                 -- Close window and OpenGL context
-------------------------------------------------------------------------------------------