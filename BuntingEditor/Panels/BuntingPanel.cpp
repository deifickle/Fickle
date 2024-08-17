#include "BuntingPanel.h"

void BuntingPanel::init(const PanelSpec& spec) {
	std::string jsonDataType = (*spec.panelData)["BuntingDataType"].GetString();
	assert(strcmp(jsonDataType.c_str(), "BuntingEditorButtonsPanel") == 0);

	m_name = (*spec.panelData)["PanelTitle"].GetString();
	m_show = false;

	const BuntingJsonValue& sectionData = (*spec.panelData)["sections"];
	assert(sectionData.IsArray());
	for (int i = 0; i < sectionData.Size(); i++) {// Uses SizeType instead of size_t
		std::cout << sectionData[i]["BuntingDataType"].GetString() << std::endl;
		std::cout << sectionData[i]["SectionTitle"].GetString() << std::endl;
		std::cout << sectionData[i]["PlatformType"].GetString() << std::endl;
	}
}

void BuntingPanel::quash() {

}

void BuntingPanel::begin() {
	ImGui::Begin(m_name, &m_show); //panel starting with panel.m_name & panel.m_show not button.m_clicked
}

void BuntingPanel::end() {
	ImGui::End();
}
