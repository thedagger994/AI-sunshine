#include "rlImGui.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

void DrawCircle(int centerX, int centerY, float radius, Color color);

void DrawTriangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color);

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello World!", 16, 9, 20, RED);
        EndDrawing();
        DrawCircle(640, 360, 100, GREEN);
       //Find out how to put Vectors as a parameter
       DrawTriangle((20, 360), (30, 370), (20,380), DARKBLUE);
    }

    CloseWindow();
    return 0;
}