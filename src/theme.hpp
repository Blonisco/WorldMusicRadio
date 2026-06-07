#ifndef THEME_H_
#define THEME_H_

#include "imgui.h"
struct Theme {
	ImVec4 bg; // 背景
	ImVec4 panel; // 次级背景

	ImVec4 text; // 文字
	ImVec4 textDim; // 次要/禁用文字

	ImVec4 accent; // 主色
	ImVec4 accentHover; // 悬停
	ImVec4 accentActive; // 按下
};

#endif // !THEME_H_
