#include <iostream>
#include <string>
#include <random>
#include "raylib.h"
#include "rlgl.h"

#define BACKGRAY (Color){30, 30, 30, 255}
#define MAP_ROWS = 5
#define MAP_COLUMNS = 5
#define MAP_SIZE = (MAP_ROWS * MAP_COLUMNS)
#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

enum texture {
    GRASS = 521,
    ROCK  = 518,
    WOOD = 2222
};
int tile_map[25];

void populate() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution dist(0, 2);

    for(int R = 0; R < 5; R++) {
        for(int W = 0; W < 5; W++ ) {
            tile_map[R*5+W] = dist(mt);
        }
    }
}

void createTexture(Texture2D atlas, RenderTexture2D target);




int main()
{
    populate();
    // Initialization
    //--------------------------------------------------------------------------------------
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GAME TEST");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

    const char *prev_dir = GetWorkingDirectory();
    const char *app_dir  = GetPrevDirectoryPath(prev_dir);

    ChangeDirectory(app_dir);
    const Texture2D fish = LoadTexture("resources/fish.png");
    const Texture2D link = LoadTexture("resources/link.png");
    const Texture2D atlas = LoadTexture("resources/atlas.png");
    ChangeDirectory(prev_dir);

    RenderTexture2D target =  LoadRenderTexture(160, 160);

    //int frameWidth = fish.width;
    //int frameHeight = fish.height;

    // Source rectangle (part of the texture to use for drawing)
    Rectangle sourceRecFish = { 0.0f, 0.0f, (float)fish.width, (float)fish.height };
    Rectangle sourceRecMap = { 0.0f, 0.0f, 160.0f, -160.0f };

    // Destination rectangle (screen rectangle where drawing part of texture)
    Rectangle destRec;

    // Origin of the texture (rotation/scale point), it's relative to destination rectangle size
    Vector2 origin = { 0.0f, 0.0f } ;

    createTexture(atlas, target);


    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        destRec = (Rectangle){ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()};
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BACKGRAY);

        //DrawTextureRec(target.texture, (Rectangle) { 0, 0, (float)target.texture.width, (float)-target.texture.height }, (Vector2) { 0, 0 }, WHITE);
        DrawTexturePro(target.texture, sourceRecMap, destRec, origin, 0.0f, WHITE);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }


    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(fish);        // Texture unloading
    UnloadTexture(link);
    UnloadTexture(atlas);
    UnloadRenderTexture(target);
    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}


void createTexture(Texture2D atlas, RenderTexture2D target) {
    BeginTextureMode(target);              // Begin drawing to render texture
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int tile;
            switch (tile_map[i*5 + j]) {
                case 0:
                    tile = GRASS;
                break;
                case 1:
                    tile = ROCK;
                break;
                case 2:
                    tile = WOOD;
                break;
                default:
                    tile = GRASS;
                break;
            }

            DrawTextureRec(atlas, (Rectangle){(float)(tile%100)*32, (float)(tile/100)*32, 32, 32 }, (Vector2){i*32.0f, j*32.0f} , WHITE);
        }
    }
    EndTextureMode();
}


