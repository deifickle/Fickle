#ifndef BUNTING_BUILDER_H
#define BUNTING_BUILDER_H

#include "../Panels/BuntingPanel.h"
#include "../Buttons/BuntingButton.h"

struct BuntingBuilder : public BuntingObject {

	struct BuilderSpec {
		const char* m_name;
		const char* m_configFilename;
	};

	virtual void init();
	virtual void quash();
};

#endif // !BUNTING_BUILDER_H
