#include "rlImGui.h"

#include "Tilemap.h"
#include "TileCoord.h"
#include <time.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
int randChance = 50;

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

        if (useGUI)
        {
              ImGui::Begin("Dijkstra's Algorithm Debug");

              ImGui::ShowDemoWindow();

              if (ImGui::Button("Randomize map"))
              {
                  map.RandomizeArea();
              }
              if (ImGui::SliderInt("Wall Chance", &(randChance), 0, 100))
              

              ImGui::End();
              ImGui::Render();
           
        }
        TileCoord startTile = { 0, 0 };
        TileCoord goalTile = { 10, 10 };
        std::vector<TileCoord> shortestPath = map.Dijkstra(startTile, goalTile);

        
        DrawFPS(10, 10);
        EndDrawing();
    }


    rlImGuiShutdown();
    CloseWindow();

    return 0;
}