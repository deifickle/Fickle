#include "BuntingPanel.h"


void BuntingSection::init(const SectionSpec& spec) {

	m_name = spec.name;
	m_show = spec.show;

}
void BuntingSection::quash() {

}

void BuntingSection::draw() {
	/**-/if (ImGui::BeginTable("table_padding", 3, flags1))
        {
            if (show_headers)
            {
                ImGui::TableSetupColumn("One");
                ImGui::TableSetupColumn("Two");
                ImGui::TableSetupColumn("Three");
                ImGui::TableHeadersRow();
            }

            for (int row = 0; row < 5; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    if (row == 0)
                    {
                        ImGui::Text("Avail %.2f", ImGui::GetContentRegionAvail().x);
                    }
                    else
                    {
                        char buf[32];
                        sprintf(buf, "Hello %d,%d", column, row);
                        ImGui::Button(buf, ImVec2(-FLT_MIN, 0.0f));
                    }
                    //if (ImGui::TableGetColumnFlags() & ImGuiTableColumnFlags_IsHovered)
                    //    ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(0, 100, 0, 255));
                }
            }
            ImGui::EndTable();
        }/**/

    /*int MAX_ROW = 16;
    int MAX_COL = 4;
    for (int r = 0; r < MAX_ROW; r++) {
        for (int c = 0; c < MAX_COL; c++) {
            int buttonIndex = (r * 4) + c;
            if (buttonIndex < buttons.size()) {
                if(buttonIndex%4 > 0)
                    ImGui::SameLine();
                buttons[buttonIndex]->draw();
            }
            else
            {
                return;
            }
        }

    }*/
    for (int i = 0; i < buttons.size(); i++) {

        if (i % 3 > 0) {
            ImGui::SameLine();
        }
        buttons[i]->draw();
    }
}

void BuntingPanel::init(const PanelSpec& spec) {
	m_name = spec.name;
	m_show = spec.show;
}

void BuntingPanel::quash() {

}

void BuntingPanel::begin() {

	ImGui::Begin(m_name, &m_show, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove); //panel starting with panel.m_name & panel.m_show not button.m_clicked
    ImGui::SetWindowSize({ 248, 600 });
}

void BuntingPanel::draw() {
    if (!m_show) return;
	for (auto section : sections) {
		if(ImGui::CollapsingHeader(section->m_name))
		    section->draw();
	}
}

void BuntingPanel::end() {
	ImGui::End();
}
