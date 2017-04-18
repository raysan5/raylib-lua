-------------------------------------------------------------------------------------------
--
--  raylib [models] example - Ray picking in 3d mode, ground plane, triangle, mesh
--
--  This example has been created using raylib 1.7 (www.raylib.com)
--  raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
--
--  Copyright (c) 2014-2017 Ramon Santamaria (@raysan5)
--  Example contributed by Joel Davis (@joeld42)
--
-------------------------------------------------------------------------------------------

-- Initialization
-------------------------------------------------------------------------------------------
local screenWidth = 800
local screenHeight = 450

InitWindow(screenWidth, screenHeight, "raylib [models] example - 3d ray picking")

-- Define the camera to look into our 3d world
local camera = Camera(Vector3(10.0, 8.0, 10.0), Vector3(0.0, 2.3, 0.0), Vector3(0.0, 1.6, 0.0), 45.0)

local ray = Ray()

local tower = LoadModel("resources/tower.obj")      -- Load OBJ model
local texture = LoadTexture("resources/tower.png")  -- Load model texture
dwarf.material.texDiffuse = texture                 -- Set dwarf model diffuse texture
local towerPos = Vector3(0.0, 0.0, 0.0)             -- Set model position
local towerBBox = CalculateBoundingBox(tower.mesh)  -- Calculate model bounding box

local hitMeshBBox = false
local hitTriangle = false

-- Test triangle
local ta = Vector3(-25.0, 0.5, 0.0)    
local tb = Vector3(-4.0, 2.5, 1.0)
local tc = Vector3(-8.0, 6.5, 0.0)

local bary = Vector3(0.0, 0.0, 0.0)

SetCameraMode(camera, CAMERA_FREE)                 -- Set a free camera mode

SetTargetFPS(60)        -- Set our game to run at 60 frames-per-second
-------------------------------------------------------------------------------------------

-- Main game loop
while not WindowShouldClose() do            -- Detect window close button or ESC key
    -- Update
    ---------------------------------------------------------------------------------------
    camera = UpdateCamera(camera)           -- Update camera
        
    -- Display information about closest hit
    local nearestHit = RayHitInfo()
    local hitObjectName = "None"
    nearestHit.distance = 100000;           -- Very far distance...
    nearestHit.hit = false
    cursorColor = WHITE

    -- Get ray and test against ground, triangle, and mesh
    ray = GetMouseRay(GetMousePosition(), camera)
    
    -- Check ray collision aginst ground plane
    local groundHitInfo = GetCollisionRayGround(ray, 0.0)
    
    if ((groundHitInfo.hit) and (groundHitInfo.distance < nearestHit.distance)) then
        nearestHit = groundHitInfo
        cursorColor = GREEN
        hitObjectName = "Ground"
    end

    -- Check ray collision against test triangle
    local triHitInfo = GetCollisionRayTriangle(ray, ta, tb, tc)
    
    if ((triHitInfo.hit) and (triHitInfo.distance < nearestHit.distance)) then
        nearestHit = triHitInfo
        cursorColor = PURPLE
        hitObjectName = "Triangle"

        bary = VectorBarycenter(nearestHit.hitPosition, ta, tb, tc)
        hitTriangle = true
    else 
        hitTriangle = false
    end

    local meshHitInfo = RayHitInfo()

    -- Check ray collision against bounding box first, before trying the full ray-mesh test
    if (CheckCollisionRayBox(ray, towerBBox)) then
        hitMeshBBox = true
        
        -- Check ray collision against mesh
        meshHitInfo = GetCollisionRayMesh(ray, tower.mesh)    
        
        if ((meshHitInfo.hit) and (meshHitInfo.distance < nearestHit.distance)) then
            nearestHit = meshHitInfo
            cursorColor = ORANGE
            hitObjectName = "Mesh"
        end
        
    end
    
    hitMeshBBox = false 
    ---------------------------------------------------------------------------------------

    -- Draw
    ---------------------------------------------------------------------------------------
    BeginDrawing()

        ClearBackground(RAYWHITE)

        Begin3dMode(camera)

            -- Draw the tower
            DrawModel(tower, towerPos, 1.0, WHITE)
            
            -- Draw the test triangle
            DrawLine3D(ta, tb, PURPLE)
            DrawLine3D(tb, tc, PURPLE)
            DrawLine3D(tc, ta, PURPLE)

            -- Draw the mesh bbox if we hit it
            if (hitMeshBBox) then DrawBoundingBox(towerBBox, LIME) end

            -- If we hit something, draw the cursor at the hit point
            if (nearestHit.hit) then
                DrawCube(nearestHit.hitPosition, 0.5, 0.5, 0.5, cursorColor)
                DrawCubeWires(nearestHit.hitPosition, 0.5, 0.5, 0.5, YELLOW)

                normalEnd = Vector3(0, 0, 0)
                normalEnd.x = nearestHit.hitPosition.x + nearestHit.hitNormal.x
                normalEnd.y = nearestHit.hitPosition.y + nearestHit.hitNormal.y
                normalEnd.z = nearestHit.hitPosition.z + nearestHit.hitNormal.z
                
                DrawLine3D(nearestHit.hitPosition, normalEnd, YELLOW)
            end

            DrawRay(ray, MAROON)
            
            DrawGrid(100, 1.0)

        End3dMode()
        
        -- Draw some debug GUI text
        DrawText(string.format("Hit Object: %s", hitObjectName), 10, 50, 10, BLACK)

        if (nearestHit.hit) then
            local ypos = 70

            DrawText(string.format("Distance: %3.2f", nearestHit.distance), 10, ypos, 10, BLACK)
            DrawText(string.format("Hit Pos: %3.2f %3.2f %3.2f", 
                                nearestHit.hitPosition.x, 
                                nearestHit.hitPosition.y, 
                                nearestHit.hitPosition.z), 10, ypos + 15, 10, BLACK)
            DrawText(string.format("Hit Norm: %3.2f %3.2f %3.2f", 
                                nearestHit.hitNormal.x, 
                                nearestHit.hitNormal.y, 
                                nearestHit.hitNormal.z), 10, ypos + 30, 10, BLACK)

            if (hitTriangle) then DrawText(string.format("Barycenter: %3.2f %3.2f %3.2f",  bary.x, bary.y, bary.z), 10, ypos + 45, 10, BLACK) end
        end

        DrawText("Use Mouse to Move Camera", 10, 430, 10, GRAY)

        DrawFPS(10, 10)

    EndDrawing()
    ---------------------------------------------------------------------------------------
end

-- De-Initialization
-------------------------------------------------------------------------------------------
UnloadModel(tower)        -- Unload model
UnloadTexture(texture)    -- Unload texture

CloseWindow()             -- Close window and OpenGL context
-------------------------------------------------------------------------------------------
