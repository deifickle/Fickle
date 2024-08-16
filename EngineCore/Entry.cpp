#include "EngineHeader.h"

    /*
    * ToDo:
    * ***** Editor ******
    * [|] Load Tiles as Texture 
    *   [|] Add imgui to project
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

//#define TEST_GUI_EXAMPLE

#ifndef TEST_GUI_EXAMPLE

int main(void)
{

    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1280;
    int screenHeight = 800;

    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Fickle Engine [v0.01]");

    SetTargetFPS(60);
    rlImGuiSetup(true);

    int id = bunOpenFile("./BuntingEditor/resources/", "test.json", BuntingFile::kOpenModeRead);
    
    BuntingEditor editor;
    BuntingEditor::EditorSpec editorSpec;
    editorSpec.m_fontConfig = nullptr;
    editorSpec.m_fontFilename = "./BuntingEditor/resources/driusstraight.ttf";
    editorSpec.m_fontSize = 18.0f;
    editorSpec.buttonData = &(bunGetFile(id))->jsonData;
    editor.init(editorSpec);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        // start ImGui Conent
        rlImGuiBegin();

        editor.draw();


        // end ImGui Content
        rlImGuiEnd();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    rlImGuiShutdown();

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
#endif // TEST_GUI_EXAMPLE

#ifdef TEST_GUI_EXAMPLE
// Dear ImGui: standalone example application for Raylib with OpenGL
// (Raylib is a simple learning library for game development)

// Learn about Dear ImGui:
// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).
// - Introduction, links and more at the top of imgui.cpp



// Main code
int main(int, char**)
{
    // Setup raylib window
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI);
    InitWindow(1280, 720, "Dear ImGui Raylib(OpenGL) example");

    // Setup Dear ImGui context
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplRaylib_Init();

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    ImFont* font = io.Fonts->AddFontFromFileTTF("./BuntingEditor/resources/driusstraight.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    IM_ASSERT(font != nullptr);

    // required to be called to cache the font texture with raylib
    Imgui_ImplRaylib_BuildFontAtlas();

    // Our state
    bool show_demo_window = false;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    bool done = false;
    while (!done)
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        ImGui_ImplRaylib_ProcessEvents();

        // Start the Dear ImGui frame
        ImGui_ImplRaylib_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }


        // Rendering
        ImGui::Render();
        BeginDrawing();
        ClearBackground(Color{ (unsigned char)(clear_color.x * 255), (unsigned char)(clear_color.y * 255),(unsigned char)(clear_color.z * 255),(unsigned char)(clear_color.w * 255) });
        ImGui_ImplRaylib_RenderDrawData(ImGui::GetDrawData());
        EndDrawing();

        done = WindowShouldClose();
    }
    // Cleanup
    ImGui_ImplRaylib_Shutdown();
    ImGui::DestroyContext();

    CloseWindow();

    return 0;
}


#endif // TEST_GUI_EXAMPLE
#undef TEST_GUI_EXAMPLE