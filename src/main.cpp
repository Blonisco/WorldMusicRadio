#include "UI.h"
#include <stdio.h>
#include <GLFW/glfw3.h>
#include "apiProvider.hpp"
int main()
{
	RadioPlayer player;
	if (!player.init()) {
		printf("Failed to init VLC\n");
		return -1;
	}
	UI ui;
	ui.init(&player);
	apiProvider api(&ui);

	while (!glfwWindowShouldClose(ui.window)) {
		api.update();
		ui.new_frame();
		//main ui control
		ui.search(api);

		//Render
		ui.render();
	}
	ui.clean();

	return 0;
}
