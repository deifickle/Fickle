#ifndef BUNTING_PANEL_H
#define BUNTING_PANEL_H

#include "../BuntingCommon_internal.h"
#include "../Buttons/BuntingButton.h"

struct BuntingSection : public BuntingObject {
	struct SectionSpec {
		const char* name;
		bool show;
	};

	bool m_show;

	virtual void init(const SectionSpec& spec);
	virtual void quash();

	virtual void draw();

	std::vector<BuntingButton*> buttons;
};

struct BuntingPanel : public BuntingObject {

	struct PanelSpec {
		const char* name;
		bool show;
	};

	bool m_show;

	virtual void init(const PanelSpec& spec);
	virtual void quash();

	virtual void begin();
	virtual void draw();
	virtual void end();

	std::vector<BuntingSection*> sections;
};

#endif // !BUNTING_PANEL_H
