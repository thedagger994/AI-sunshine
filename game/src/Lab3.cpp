#include "raylib.h"
#include <imgui.h>
#include <oleidl.h>

class Game {
public:
    static Game& GetInstance() {
        static Game instance;
        return instance;
    }

    void Run() {
        const int screenWidth = 800;
        const int screenHeight = 450;

        InitWindow(screenWidth, screenHeight, "State Machine Example");

        currentState = TITLE_SCREEN;
        stateTimer = 0.0f;
        gamePaused = false;

        SetTargetFPS(60);

        while (!WindowShouldClose()) {
            Update();
            Draw();
        }

        CloseWindow();
    }

private:
    enum GameState {
        TITLE_SCREEN,
        MAIN_MENU,
        CREDITS_SCREEN,
        GAME_SCREEN,
        PAUSE_SCREEN,
        WIN_SCREEN,
        LOSE_SCREEN
    };

    GameState currentState;
    float stateTimer;
    bool gamePaused;

    Rectangle player;
    Rectangle obstacle;

    Game() {
    }

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    void Update() {
        float deltaTime = GetFrameTime();

        switch (currentState) {
        case TITLE_SCREEN:
            stateTimer += deltaTime;
            if (stateTimer >= 4.0f) {
                currentState = MAIN_MENU;
                stateTimer = 0.0f;
            }
            break;

        case MAIN_MENU:
            if (IsKeyPressed(KEY_C)) {
                currentState = CREDITS_SCREEN;
            }
            else if (IsKeyPressed(KEY_G)) {
                currentState = GAME_SCREEN;
            }
            break;

        case CREDITS_SCREEN:
            if (IsKeyPressed(KEY_ESCAPE)) {
                currentState = MAIN_MENU;
            }
            break;

        case GAME_SCREEN:
            if (!gamePaused) {
                if (IsKeyDown(KEY_W)) player.y -= 200 * deltaTime;
                if (IsKeyDown(KEY_S)) player.y += 200 * deltaTime;
                if (IsKeyDown(KEY_A)) player.x -= 200 * deltaTime;
                if (IsKeyDown(KEY_D)) player.x += 200 * deltaTime;

                if (CheckCollisionRecs(player, obstacle)) {
                    currentState = LOSE_SCREEN;
                }

                stateTimer += deltaTime;
                if (stateTimer >= 20.0f) {
                    currentState = WIN_SCREEN;
                    stateTimer = 0.0f;
                }
            }

            if (IsKeyPressed(KEY_P)) {
                currentState = PAUSE_SCREEN;
                gamePaused = true;
            }
            break;

        case PAUSE_SCREEN:
            if (IsKeyPressed(KEY_ESCAPE)) {
                currentState = GAME_SCREEN;
                gamePaused = false;
            }
            break;

        case WIN_SCREEN:
            if (IsKeyPressed(KEY_SPACE)) {
                currentState = MAIN_MENU;
            }
            break;

        case LOSE_SCREEN:
            if (IsKeyPressed(KEY_SPACE)) {
                currentState = MAIN_MENU;
            }
            break;
        }
    }

    void Draw() {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        switch (currentState) {
        case TITLE_SCREEN:
            DrawText("Title Screen", 10, 10, 20, YELLOW);
            break;

        case MAIN_MENU:
            DrawText("Main Menu", 10, 10, 20, PURPLE);
            break;

        case CREDITS_SCREEN:
            DrawText("Credits Screen", 10, 10, 20, PINK);
            break;
        case GAME_SCREEN:
            DrawText("Game Screen", 10, 10, 20, BLUE);
            DrawRectangleRec(player, WHITE);
            DrawRectangleRec(obstacle, RED);
            break;

        case PAUSE_SCREEN:
            DrawText("Pause Screen", 10, 10, 20, GRAY);
            DrawText("Game Paused", GetScreenWidth() / 2 - MeasureText("Game Paused", 40) / 2, GetScreenHeight() / 2 - 40, 40, DARKGRAY);
            break;

        case WIN_SCREEN:
            DrawText("Win Screen", 10, 10, 20, GREEN);
            break;

        case LOSE_SCREEN:
            DrawText("Lose Screen", 10, 10, 20, RED);
            break;
        }

        EndDrawing();
    }
};

int main() {
    Game::GetInstance().Run();

    return 0;
}