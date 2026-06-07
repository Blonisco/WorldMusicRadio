#ifndef THEMES_H_
#define THEMES_H_

#include "imgui.h"
#include "theme.hpp"

namespace theme
{

inline Theme cherry{
	.bg = ImVec4(0.10f, 0.05f, 0.06f, 1.0f),
	.panel = ImVec4(0.18f, 0.08f, 0.10f, 1.0f),

	.text = ImVec4(0.98f, 0.92f, 0.93f, 1.0f),
	.textDim = ImVec4(0.6f, 0.4f, 0.45f, 1.0f),

	.accent = ImVec4(0.80f, 0.10f, 0.20f, 1.0f),
	.accentHover = ImVec4(0.90f, 0.20f, 0.30f, 1.0f),
	.accentActive = ImVec4(0.65f, 0.05f, 0.15f, 1.0f),
};
inline Theme night_blue = {
	.bg = ImVec4(0.09f, 0.10f, 0.15f, 1.0f),
	.panel = ImVec4(0.14f, 0.15f, 0.22f, 1.0f),

	.text = ImVec4(0.80f, 0.82f, 0.90f, 1.0f),
	.textDim = ImVec4(0.5f, 0.55f, 0.65f, 1.0f),

	.accent = ImVec4(0.35f, 0.50f, 0.90f, 1.0f),
	.accentHover = ImVec4(0.45f, 0.60f, 1.00f, 1.0f),
	.accentActive = ImVec4(0.25f, 0.40f, 0.80f, 1.0f),
};
inline Theme neon = {
	.bg = ImVec4(0.02f, 0.03f, 0.02f, 1.0f),
	.panel = ImVec4(0.05f, 0.08f, 0.05f, 1.0f),

	.text = ImVec4(0.85f, 1.00f, 0.85f, 1.0f),
	.textDim = ImVec4(0.55f, 0.75f, 0.55f, 1.0f),
	.accent = ImVec4(0.20f, 1.00f, 0.30f, 1.0f),
	.accentHover = ImVec4(0.40f, 1.00f, 0.50f, 1.0f),
	.accentActive = ImVec4(0.10f, 0.80f, 0.20f, 1.0f),
};
inline Theme purple = {
	.bg = ImVec4(0.07f, 0.05f, 0.10f, 1.0f),
	.panel = ImVec4(0.12f, 0.08f, 0.16f, 1.0f),

	.text = ImVec4(0.90f, 0.85f, 0.95f, 1.0f),
	.textDim = ImVec4(0.5f, 0.45f, 0.6f, 1.0f),

	.accent = ImVec4(0.60f, 0.30f, 0.90f, 1.0f),
	.accentHover = ImVec4(0.70f, 0.40f, 1.00f, 1.0f),
	.accentActive = ImVec4(0.45f, 0.20f, 0.75f, 1.0f),
};
inline Theme paper = {
	.bg = ImVec4(0.96f, 0.93f, 0.85f, 1.0f),
	.panel = ImVec4(0.90f, 0.86f, 0.75f, 1.0f),

	.text = ImVec4(0.20f, 0.18f, 0.12f, 1.0f),
	.textDim = ImVec4(0.5f, 0.45f, 0.35f, 1.0f),

	.accent = ImVec4(0.75f, 0.55f, 0.20f, 1.0f),
	.accentHover = ImVec4(0.85f, 0.65f, 0.30f, 1.0f),
	.accentActive = ImVec4(0.60f, 0.45f, 0.15f, 1.0f),
};
}
#endif // !STYLE_THEME_H_
