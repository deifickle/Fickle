#include "EngineHeader.h"

int main(void)
{
    InitWindow(800, 450, "Fickle Engine [v0.01]");

    SetTargetFPS(60);

    /*
    * ToDo:
    * ***** Editor ******
    * [|] Load Tiles as Texture 
    *   [|] Research
    *       [|] how to load texture
    *       [ ] How to set texture to button - pointer_tile
    *       [ ] How to move the pointer_tile with mouse
    * [ ] Buttons
    *   [ ] Create buttons with texture as tile image
    *   [ ] Button type classification
    *   [ ] add more buttons
    * [ ] Menu
    *   [ ] buttons system 
    *   [ ] manage buttons using csv or json
    *   [ ] menu navigation
    *   [ ] editor hints
    * [ ] Room layout
    *   [ ] Render grid
    *   [ ] Grid navigation using mouse
    *       [ ] System to move pointer_tile grid by grid
    *   [ ] Click to place
    *   [ ] Erase
    * 
    * Purpose of files
    * * Global config
    * * Buttons config
    * * User config
    * * Room config
    * * Tiles config & property
    * * Store a Config system
    * 
    * Testing
    * [ ] research on how to test a tile based platforming puzzle game
    * 
    * [ ] Config file viewer (must have a viewer for all file types)
    *   [ ] Able to select config files
    *   [ ] must be able to diff between versions of config files & report compatibility issues
    *   [ ] Manage editor layout
    *   [ ] save and load files
    *
    * [ ] Game config
    *   [ ] Tiles list
    *   [ ] Tile property
    *   [ ] Player config
    *       [ ] contain various player types
    *       [ ] chose among players for the game
    *   [ ] Player navigation properties
    *   [ ] Exposed at game editor level
    *
    * [ ] tile behaviour system
    *   [ ] research on system designing
    * 
    * [ ] Gameplay
    *   [ ] Any time swtich between edit and play mode
    *   [ ] controlable play speed (for test purpose)
    *   [ ] keys and doors
    *   [ ] moving platforms
    *   [ ] spikes 
    * [ ] create levels and order them
    * 
    */

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
