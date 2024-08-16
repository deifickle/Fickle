#ifndef BUNTING_EDITOR_H
#define BUNTING_EDITOR_H

#include "BuntingBuilder/BuntingBuilder.h"
#include "FileIO/BuntingFileIO.h"

struct BuntingEditor : public BuntingObject {

	struct EditorSpec {
		const char* m_fontFilename	= nullptr;
		float m_fontSize			= -1.0f;
		ImFontConfig* m_fontConfig	= nullptr;
		BuntingJsonData* buttonData = nullptr;
	};

	const char* m_fontFilename	= nullptr;
	float m_fontSize			= -1.0f;
	ImFontConfig* m_fontConfig	= nullptr;

	// Our state
	bool show_demo_window = false;
	bool show_another_window = false;
	bool show_welcome_text = true;
	bool show_button = true;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	Texture parrot;
	BuntingImageButton imgButton;
	BuntingButton button, counterButton;
	BuntingPanel m_tilesPanel;

	ImGuiIO io;

	virtual void init(const EditorSpec& spec);
	virtual void quash();

	void draw();
};

#endif // !BUNTING_EDITOR_H