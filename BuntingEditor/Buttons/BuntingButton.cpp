#include "BuntingButton.h"


void BuntingButton::init(const ButtonSpec& spec) {
	if (spec.m_name) {
		m_name = spec.m_name;
	}
	if (spec.BuntingUserData) {
		userData = spec.BuntingUserData;
	}
}

void BuntingButton::quash() {

}

void BuntingButton::update() {

}

void BuntingButton::draw() {
	//rlImGuiImageButton(m_name, m_texture);
	m_clicked = ImGui::Button(m_name);
}

void BuntingImageButton::init(const ImageButtonSpec& spec) {
	if (spec.m_name && spec.m_texture) {
		m_name = spec.m_name;
		m_texture = spec.m_texture;
	}
}

void BuntingImageButton::quash() {

}

void BuntingImageButton::update() {

}

void BuntingImageButton::draw() {
	m_clicked = rlImGuiImageButton(m_name, m_texture);

	if (m_clicked) {
		if (buntingState.callback.key)
			buntingState.callback.key(this->userData);
	}
}