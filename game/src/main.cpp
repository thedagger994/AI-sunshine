#include "rlImGui.h"
#include "Tilemap.h"
#include <time.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Tilemap map;

int main(void)
{
    srand(time(NULL));
    map.Randomize();

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    rlImGuiSetup(true);
    InitAudioDevice();

    
    bool useGUI = false;
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {     



        BeginDrawing();
        ClearBackground(RAYWHITE);

        map.Draw();

        if (IsKeyPressed(KEY_GRAVE)) useGUI = !useGUI;
        if (useGUI)
        {
            rlImGuiBegin();

            rlImGuiEnd();
        }
        
        DrawFPS(10, 10);
        DrawText("Press ~ to open/close GUI", 10, 30, 20, GRAY);
        EndDrawing();
    }


    rlImGuiShutdown();
    CloseWindow();

    return 0;
}