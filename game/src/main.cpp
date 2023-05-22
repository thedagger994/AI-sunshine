#include "rlImGui.h"
#include <corecrt_math.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

struct Circle {
    float x;
    float y;
    float radius;
    Color color;
};

void DrawCircle(int centerX, int centerY, float radius, Color color);

void DrawTriangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color);

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    SetTargetFPS(60);

    const int screenWidth = 800;
    const int screenHeight = 450;

    int mousePositionX = GetMouseX();
    int mousePositionY = GetMouseY();
   
    Circle circle1 = {640, 360, 100, GREEN };
    Circle circle2 = { mousePositionX, mousePositionY, 50, DARKBLUE };
    
    bool checkCircleCollision(const Circle & circle1, const Circle & circle2); {
        float distance = sqrt(pow(circle2.x - circle1.x, 2) + pow(circle2.y - circle1.y, 2));
        return distance <= circle1.radius + circle2.radius;
    }

    while (!WindowShouldClose())
    {
        if (checkCircleCollision(circle1, circle2)) {
            circle1.color = GREEN;
        }
        else {
            circle1.color = RED;
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Collision Detection.", 16, 9, 16, RED);
        DrawCircle(circle1.x, circle1.y, circle1.radius, circle1.color);
        DrawCircle(circle2.x, circle2.y, circle2.radius, circle2.color);

        EndDrawing();
        
    }

    CloseWindow();
    return 0;
}