#include "style.hpp"
#include "imgui.h"
#include "theme.hpp"

void Style::set_theme(const Theme &theme)
{
	auto c = ImGui::GetStyle().Colors;

	c[ImGuiCol_WindowBg] = theme.bg;
	c[ImGuiCol_ChildBg] = theme.panel;
	c[ImGuiCol_PopupBg] = theme.panel;

	c[ImGuiCol_Text] = theme.text;
	c[ImGuiCol_TextDisabled] = theme.textDim;

	c[ImGuiCol_FrameBg] = theme.panel;
	c[ImGuiCol_FrameBgHovered] = theme.panel;
	c[ImGuiCol_FrameBgActive] = theme.panel;

	c[ImGuiCol_Button] = theme.accent;
	c[ImGuiCol_ButtonHovered] = theme.accentHover;
	c[ImGuiCol_ButtonActive] = theme.accentActive;

	c[ImGuiCol_Header] = theme.accent;
	c[ImGuiCol_HeaderHovered] = theme.accentHover;
	c[ImGuiCol_HeaderActive] = theme.accentActive;

	c[ImGuiCol_TextSelectedBg] = theme.accent;
	c[ImGuiCol_NavHighlight] = theme.accent;
	c[ImGuiCol_ChildBg] = ImVec4(0, 0, 0, 0);

	c[ImGuiCol_TableRowBg] = ImVec4(0, 0, 0, 0);
	c[ImGuiCol_TableRowBgAlt] = ImVec4(0, 0, 0, 0);

	c[ImGuiCol_TableHeaderBg] = ImVec4(0, 0, 0, 0);

	c[ImGuiCol_PopupBg] = theme.bg; // 或者透明
}
