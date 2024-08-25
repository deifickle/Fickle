#include "BuntingEditor.h"

BuntingEditorState buntingState;


void buntingSetKeyCallback(BuntingKeyCallbackFPtr callback) {
    BUNTING_SWAP_POINTERS(BuntingKeyCallbackFPtr, buntingState.callback.key, callback);
}

void bunBuildEditor(BuntingEditor* editor, BuntingJsonDoc* doc) {

    const BuntingJsonValue& panelData = (*doc)["BuntingJsonData"];

    std::string jsonDataType = panelData["BuntingDataType"].GetString();
    assert(strcmp(jsonDataType.c_str(), "BuntingEditorButtonsPanel") == 0);

    BuntingPanel::PanelSpec panelSpec;
    panelSpec.name = panelData["PanelTitle"].GetString();
    panelSpec.show = false;

    BuntingPanel* panel = new BuntingPanel();
    panel->init(panelSpec);

    const BuntingJsonValue& sectionData = panelData["Sections"];
    assert(sectionData.IsArray());
    for (int i = 0; i < sectionData.Size(); i++) {

        std::string jsonDataType = sectionData[i]["BuntingDataType"].GetString();
        assert(strcmp(jsonDataType.c_str(), "BuntingEditorButtonsSection") == 0);

        BuntingSection::SectionSpec sectionSpec;
        sectionSpec.name = sectionData[i]["SectionTitle"].GetString();
        sectionSpec.show = false;

        BuntingSection* section = new BuntingSection();
        section->init(sectionSpec);

        const BuntingJsonValue& imageButtonData = sectionData[i]["ImageButtons"];
        assert(imageButtonData.IsArray());
        for (int j = 0; j < imageButtonData.Size(); j++) {

            std::string jsonDataType = imageButtonData[j]["BuntingDataType"].GetString();
            assert(strcmp(jsonDataType.c_str(), "BuntingEditorButton") == 0);

            std::string path = imageButtonData[j]["relativeFileLocation"].GetString();
            std::string name = imageButtonData[j]["filename"].GetString();
            std::string extn = imageButtonData[j]["filetype"].GetString();

            std::string fullname = path + name + '.' + extn;
            Texture2D* buttonTexture = new Texture2D();
            Texture2D texturObj = LoadTexture(fullname.c_str());
            memcpy(buttonTexture, &texturObj, sizeof(Texture2D));

            BuntingImageButton::ImageButtonSpec imageButtonSpec;
            imageButtonSpec.m_name = imageButtonData[j]["name"].GetString();
            imageButtonSpec.m_texture = buttonTexture;

            BuntingImageButton* imageButton = new BuntingImageButton();
            imageButton->init(imageButtonSpec);
            section->buttons.push_back(imageButton);
        }
        panel->sections.push_back(section);
    }
    editor->panels.push_back(panel);
}

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



    BuntingImageButton::ImageButtonSpec ibSpec;
    ibSpec.m_name = "parrot";
    ibSpec.m_texture = &parrot;

    imgButton.init(ibSpec);

    BuntingButton::ButtonSpec parrotBtnSpec({ "show parrot button" });
    button.init(parrotBtnSpec);

    BuntingJsonDoc* jd = spec.buttonData;
    bunBuildEditor(this, jd);


    //const rapidjson::Value & v = (*jd)["ButtonsDiv"];
    //std::cout << v["title"].GetString() << std::endl;


    BuntingButton::ButtonSpec counterBtnSpec({ "Counter Btn" });
    counterButton.init(counterBtnSpec);
}

void BuntingEditor::quash() {
    // no resource created ..
    // nothing to quash here! 
}

void BuntingEditor::processPanel(BuntingPanel* panel) {
    if (panel->m_show) {
        panel->begin();
        panel->draw();
        panel->end();
    }
}

void BuntingEditor::draw() {

    static float f = 0.0f;
    static int counter = 0;
    static int parrotCounter = 0;

    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
    ImGui::Checkbox("Another Window", &show_another_window);
    ImGui::Checkbox("Welcome Text", &show_welcome_text);
    for (auto panel : panels) {
        ImGui::Checkbox(panel->m_name, &panel->m_show);
    }

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

    counterButton.draw();
    if (counterButton.m_clicked) // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    for (auto panel : panels) {
        processPanel(panel);
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
        DrawText("Hello Sailor!", 375, 150, 20, LIGHTGRAY);
        DrawText("**Welcome to Bunting Editor**", 290, 200, 20, LIGHTGRAY);
        DrawText("We are just starting!", 330, 250, 20, LIGHTGRAY);
    }

}