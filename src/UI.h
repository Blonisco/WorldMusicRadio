#ifndef UI_H_
#define UI_H_
#include "style.hpp"
#include <GLFW/glfw3.h>
#include "RadioPlayer.h"
#include "apiProvider.hpp"
class UI {
    private:
	int selected_index = -1;
	int selected_limit = 20;
	RadioPlayer *player;
	static char search_input[30];
	Style style;

    public:
	GLFWwindow *window;
	int init(RadioPlayer *);
	void new_frame();
	void render();
	void play(const std::string &url);
	void clean();
	void search(apiProvider &);
};
#endif
