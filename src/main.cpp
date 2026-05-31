#include "UI.h"
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <windows.h>
#include <direct.h>
#include "apiProvider.hpp"
int main()
{
	printf("Text");
	UI ui;
	ui.init();

	apiProvider api;

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