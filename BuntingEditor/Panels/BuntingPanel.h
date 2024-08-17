#ifndef BUNTING_PANEL_H
#define BUNTING_PANEL_H

#include "../BuntingCommon_internal.h"

struct BuntingImageButton;
struct BuntingButton;

struct BuntingPanel : public BuntingObject {

	struct PanelSpec {
		const BuntingJsonValue* panelData;
	};

	bool m_show;

	virtual void init(const PanelSpec& spec);
	virtual void quash();

	virtual void begin();
	virtual void end();
};

#endif // !BUNTING_PANEL_H
