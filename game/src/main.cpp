#include "rlImGui.h"
#include "Tilemap.h"
#include "TileCoord.h"
#include <time.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Tilemap map;
Image noise;

int main(void)
{
    srand(time(NULL));
    map.Randomize();

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    rlImGuiSetup(true);
    noise = LoadImage("../game/assets/textures/perlin-noise.png");

    
    bool useGUI = false;
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {     



        BeginDrawing();
        ClearBackground(RAYWHITE);

        map.Draw();
        
        
        
        if (IsKeyPressed(ImGuiKey_GraveAccent)) useGUI = !useGUI;
        if (useGUI)
        {
            Tilemap tilemap;

            TileCoord startTile = { 0, 0 };
            TileCoord goalTile = { 10, 10 };

            std::vector<TileCoord> shortestPath = tilemap.Dijkstra(startTile, goalTile);
        }
        
        DrawFPS(10, 10);
        DrawText("Press ~ to open/close GUI", 10, 30, 20, GRAY);
        EndDrawing();
    }


    rlImGuiShutdown();
    CloseWindow();

    return 0;
}