#include "BuntingPanel.h"

void BuntingPanel::init(const PanelSpec& spec) {
	m_name = (*spec.panelData)["panel title"].GetString();
	m_show = false;
}

void BuntingPanel::quash() {

}

void BuntingPanel::begin() {
	ImGui::Begin(m_name, &m_show); //panel starting with panel.m_name & panel.m_show not button.m_clicked
}

void BuntingPanel::end() {
	ImGui::End();
}
