#ifndef BUNTINE_BUTTON_H
#define BUNTINE_BUTTON_H

#include "../BuntingCommon_internal.h"

struct BuntingButton : public BuntingObject {

	struct ButtonSpec {
		const char* m_name = nullptr;
		void* BuntingUserData = nullptr;
	};

	bool		m_clicked;
	void		*userData;

	virtual void init(const ButtonSpec& spec);
	virtual void quash();

	virtual void update();
	virtual void draw();
};

struct BuntingImageButton : public BuntingButton {

	struct ImageButtonSpec : public BuntingButton::ButtonSpec {
		Texture*	m_texture = nullptr;
	};

	Texture* m_texture;

	virtual void init(const ImageButtonSpec& spec);
	virtual void quash();

	virtual void update();
	virtual void draw();
};

#endif // !BUNTINE_BUTTON_H