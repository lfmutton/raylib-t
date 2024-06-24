#include <iostream>
#include <string>
#include "raylib.h"
#include "rlgl.h"

#define BACKGRAY (Color){30, 30, 30, 255}



int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "raylib + rlgl");
    SetExitKey(KEY_NULL);

    bool growing = true;
    unsigned char k = 0;

    while (!WindowShouldClose()) {

        if (growing) ++k;
        else --k;
        if (k == 255 || k == 0) growing = !growing;


        BeginDrawing();
        ClearBackground(BACKGRAY);


        for (unsigned char i = 0; i < 255; ++i) {
            for (unsigned char j = 0; j < 255; ++j) {
                DrawPixel((GetScreenWidth()/2 - 128) + static_cast<int>(i), (GetScreenHeight()/2 - 128) + static_cast<int>(j), (Color){i,j,k,255});
            }
        }

        EndDrawing();
    }

    return 0;
}
