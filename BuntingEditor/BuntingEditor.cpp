#include "BuntingEditor.h"

void BuntingEditor::init(const EditorSpec& spec) {

    assert(spec.m_fontFilename && spec.m_fontSize);
    
    m_fontFilename = spec.m_fontFilename;
    m_fontSize = spec.m_fontSize;
    m_fontConfig = spec.m_fontConfig;

    // Setup Dear ImGui context
    ImGui::CreateContext();
    io = ImGui::GetIO(); 
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
    ImFont* font = io.Fonts->AddFontFromFileTTF(m_fontFilename, m_fontSize, m_fontConfig, io.Fonts->GetGlyphRangesJapanese());
    IM_ASSERT(font != nullptr);

    // required to be called to cache the font texture with raylib
    Imgui_ImplRaylib_BuildFontAtlas();


    parrot = LoadTexture("./BuntingEditor/resources/parrots.png");
    parrot.width = 64;
    parrot.height = 64;



    BuntingImageButton::ImageButtonSpec ibSpec({ "parrot", &parrot });
    imgButton.init(ibSpec);

    BuntingButton::ButtonSpec parrotBtnSpec({ "show parrot button" });
    button.init(parrotBtnSpec);

    BuntingPanel::PanelSpec pSpec({ "Tiles Panel" });
    m_tilesPanel.init(pSpec);

    BuntingButton::ButtonSpec counterBtnSpec({ "Counter Btn" });
    counterButton.init(counterBtnSpec);
}

void BuntingEditor::quash() {
    // no resource created ..
    // nothing to quash here! 
}

void BuntingEditor::draw() {

    /*if (GuiButton(rect, "#191#Show Message")) showMsgBox = true;

    if (showMsgBox)
    {
        int result = GuiMessageBox(guiRect,
            "#191#Message Box", "Hi! This is a message!", "Nice;Cool");

        if (result >= 0) showMsgBox = false;
    }*/


    static float f = 0.0f;
    static int counter = 0;
    static int parrotCounter = 0;

    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
    ImGui::Checkbox("Another Window", &show_another_window);
    ImGui::Checkbox("Welcome Text", &show_welcome_text);
    ImGui::Checkbox("Show tile panle", &m_tilesPanel.m_show);

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

    counterButton.draw();
    if (counterButton.m_clicked) // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    if (m_tilesPanel.m_show) {
        m_tilesPanel.begin();
        imgButton.draw(); //all these butons are drawn there.. 
        if (imgButton.m_clicked)
            parrotCounter++;
        
        ImGui::Text("parrot counter = %d", parrotCounter);
        m_tilesPanel.end(); 
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

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::End();

    if (show_welcome_text) {
        DrawText("Hello Sailor!", 275, 150, 20, LIGHTGRAY);
        DrawText("**Welcome to Fickle editor**", 190, 200, 20, LIGHTGRAY);
        DrawText("We are just starting!", 230, 250, 20, LIGHTGRAY);
    }

}