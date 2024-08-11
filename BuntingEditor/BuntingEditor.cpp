#include "BuntingEditor.h"

void BuntingEditor::init() {

    rect.width = 120;
    rect.height = 30;
    rect.x = 24;
    rect.y = 24;

    guiRect.width = 250;
    guiRect.height = 100;
    guiRect.x = 85;
    guiRect.y = 70;
}

void BuntingEditor::drawMenu() {

    if (GuiButton(rect, "#191#Show Message")) showMsgBox = true;

    if (showMsgBox)
    {
        int result = GuiMessageBox(guiRect,
            "#191#Message Box", "Hi! This is a message!", "Nice;Cool");

        if (result >= 0) showMsgBox = false;
    }

    DrawText("Hello Sailor!", 275, 150, 20, LIGHTGRAY);
    DrawText("**Welcome to Fickle editor**", 190, 200, 20, LIGHTGRAY);
    DrawText("We are just starting!", 230, 250, 20, LIGHTGRAY);

}