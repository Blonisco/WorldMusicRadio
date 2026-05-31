#ifndef UI_H_
#define UI_H_
#include "Radio.hpp"
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <string>
#include <vector>
#include "apiProvider.hpp"
class UI {
    private:
	int selected_index = -1;
	int selected_limit = 20;

	static char search_input[30];

    public:
	GLFWwindow *window;
	int init();
	void new_frame();
	void render();
	void play();
	void clean();
	void search(apiProvider &);
};
#endif
