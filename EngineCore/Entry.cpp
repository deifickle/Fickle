#include "EngineHeader.h"

int main(void)
{
    InitWindow(800, 450, "Fickle Engine [v0.01]");

    SetTargetFPS(60);

    BuntingEditor editor;
    editor.init();


    while (!WindowShouldClose())
    {
        BeginDrawing();
        editor.drawMenu();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
