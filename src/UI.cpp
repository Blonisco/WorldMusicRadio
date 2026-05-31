#include "UI.h"
char UI::search_input[30];
int UI::init()
{
	if (!glfwInit())
		return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(1280, 720, "WorldMusicRadio", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	(void)io;
	io.Fonts->AddFontFromFileTTF("font/UbuntuNerdFont-Regular.ttf", 25,
				     nullptr,
				     io.Fonts->GetGlyphRangesChineseFull());
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui::StyleColorsClassic();
	return 0;
}

void UI::new_frame()
{
	glfwPollEvents();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void UI::clean()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();
}

void UI::render()
{
	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window);
}

void UI::search(apiProvider &api)
{
	ImGui::SetNextWindowPos(ImVec2{ 0, 0 });
	ImGui::SetNextWindowSize(ImVec2{ 960, 720 });

	//搜索栏界面
	ImGui::Begin("##search", nullptr,
		     ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
			     ImGuiWindowFlags_NoCollapse);
	//搜索表
	if (ImGui::BeginTable(
		    "RadioTable", 3,
		    ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY |
			    ImGuiTableFlags_ScrollX | ImGuiTableFlags_RowBg |
			    ImGuiTableFlags_Borders,
		    ImVec2(0, 500))) {
		// 设置表头
		ImGui::TableSetupColumn("Station Name",
					ImGuiTableColumnFlags_WidthFixed,
					200.0f);
		ImGui::TableSetupColumn(
			"Country", ImGuiTableColumnFlags_WidthFixed, 100.0f);
		ImGui::TableSetupColumn("URL (Resolved)",
					ImGuiTableColumnFlags_WidthFixed,
					600.0f);
		ImGui::TableHeadersRow();

		for (int i = 0; i < api.get_list().size(); i++) {
			ImGui::TableNextRow();

			ImGui::TableSetColumnIndex(0); //名字
			if (ImGui::Selectable(
				    api.get_list()[i].name.c_str(),
				    selected_index == i,
				    ImGuiSelectableFlags_SpanAllColumns |
					    ImGuiSelectableFlags_AllowDoubleClick)) {
				if (ImGui::IsMouseDoubleClicked(0)) {
					selected_index = i;
				}
			}

			ImGui::TableSetColumnIndex(1); //国家
			ImGui::TextUnformatted(
				api.get_list()[i].country.c_str());

			ImGui::TableSetColumnIndex(2); //url
			ImGui::TextUnformatted(api.get_list()[i].url.c_str());
		}
		ImGui::EndTable();
	}
	ImGui::InputText("##Search", search_input, 29);
	ImGui::SameLine();
	ImGui::BeginChild("##search_limit", ImVec2{ 150, 100 });
	if (ImGui::TreeNode("Limit")) //选择搜索Limit
	{
		if (ImGui::Selectable("20", selected_limit == 20)) {
			selected_limit = 20;
		}
		if (ImGui::Selectable("40", selected_limit == 40)) {
			selected_limit = 40;
		}
		ImGui::TreePop();
	}
	ImGui::EndChild();
	ImGui::SameLine();
	if (ImGui::Button("Search")) {
		api.search(std::string(search_input), selected_limit);
	}

	if (true) { //测试用
		ImGui::Text("Retry_time:%d", api.get_retry_time());
		ImGui::Text("Selected:%d", selected_index);
	}
	ImGui::End();
}