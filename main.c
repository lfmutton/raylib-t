#include "raylib.h"

void GridLines(int x, int y);
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int i;

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;
    Vector2 mousePos;
    InitWindow(screenWidth, screenHeight, "Testing");
    HideCursor();

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        mousePos = GetMousePosition();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(BLACK);
        GridLines(screenWidth, screenHeight);
        DrawLine(GetMouseX(), GetMouseY(), screenWidth / 2, screenHeight / 2, RED);

        DrawCircle(screenWidth / 2, screenHeight / 2, 8, WHITE);
        DrawCircleV(mousePos, 8, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void GridLines(int x, int y)
{
    for (i = 0; i < x; i += 50)
    {
        DrawLine(i, 0, i, y, WHITE);
    }
    for (i = 0; i < y; i += 50)
    {
        DrawLine(0, i, x, i, WHITE);
    }
}