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
        DrawText("Hello World!", 16, 9, 16, RED);
        EndDrawing();
        Vector2 mousePosition= GetMousePosition();
        DrawCircle(640, 360, 100, GREEN);
        DrawCircleV(mousePosition, 5, DARKBLUE);
        DrawTriangleLines(mousePosition, {40,370}, {40, 350}, BLUE);
        CheckCollisionCircles(mousePosition, 5, { 640, 360 }, 100);
        while (true)
        {

        }
    }

    CloseWindow();
    return 0;
}