#include "UI.h"
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <chrono>
#include <string>
#include "style.hpp"
#include "themes.hpp"
#include "apiProvider.hpp"
#include "Country.hpp"
char UI::search_input[30];
int UI::init(RadioPlayer *player_)
{
	player = player_;

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
	style.set_theme(theme::classic_dark);
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
			     ImGuiWindowFlags_NoCollapse |
			     ImGuiWindowFlags_NoTitleBar |
			     ImGuiWindowFlags_NoScrollbar);
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
					play(api.get_list()[i].url.c_str());
					now_playing = api.get_list()[i];
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
	if (ImGui::Button("Search")) {
		api.search(std::string(search_input), selected_limit,
			   search_country);
	}
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

	/*
   *  选择国家
   * */
	ImGui::BeginChild("##country", ImVec2{ 340, 0 });

	if (ImGui::TreeNode("Country")) //选择搜索Limit
	{
		if (ImGui::Selectable("None", search_country == "")) {
			search_country = "";
		}
		for (const auto &country : country_to_countrycode) {
			if (ImGui::Selectable(country.first.c_str(),
					      search_country ==
						      country.first)) {
				search_country = country.first;
			}
		}
		ImGui::TreePop();
	}
	ImGui::EndChild();
	ImGui::SameLine();
	ImGui::Text("%s", search_country.c_str());
	/*
 *通知信息显示
 */
	ImGui::SetCursorPos(ImVec2{ 10, 650 });
	if (std::chrono::steady_clock::now() < time) {
		ImGui::Text("%s", notice_what.c_str());
	};
	if (false) { //测试用
		ImGui::Text("Retry_time:%d", api.get_retry_time());
		ImGui::Text("Selected:%d", selected_index);
		ImGui::Text("Play:%d", player->is_playing());
	}
	ImGui::End();

	/*
   *按钮栏
   *由播放按钮和静音按钮组成
   * */
	ImGui::SetNextWindowPos(ImVec2{ 960, 500 });
	ImGui::SetNextWindowSize(ImVec2{ 320, 460 });
	ImGui::Begin("##Button", nullptr,
		     ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
			     ImGuiWindowFlags_NoCollapse |
			     ImGuiWindowFlags_NoTitleBar);
	ImGui::SetCursorPos(ImVec2(70, 40));
	if (ImGui::Button(player->is_playing() ? "\uf04c" : "\uf04b",
			  ImVec2{ 80, 80 })) { //播放恢复栏
		if (player->is_playing() == true) {
			player->stop();
		} else if (player->is_playing() == false) {
			player->resume();
		}
	}

	ImGui::SameLine();

	if (ImGui::Button(player->is_muted() ? "\uf026" : "\uf028", //静音键
			  ImVec2{ 80, 80 })) {
		player->change_muted();
	}
	if (false) {
		if (ImGui::Button("Test Notice")) { //通知键（测试用
			notice("Test");
		}
	}
	ImGui::End();

	/*
 *选择Theme部分
 可以选择6个Theme
 * */
	ImGui::SetNextWindowPos(ImVec2{ 960, 0 });
	ImGui::SetNextWindowSize(ImVec2{ 320, 500 });
	ImGui::Begin("##Style", nullptr,
		     ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
			     ImGuiWindowFlags_NoCollapse |
			     ImGuiWindowFlags_NoTitleBar);
	ImGui::SetCursorPos(ImVec2(90, 50));
	if (ImGui::Button("Classic", ImVec2{ 150, 40 })) {
		style.set_theme(theme::classic_dark);
	}
	ImGui::SetCursorPos(ImVec2(90, 90));
	if (ImGui::Button("Cherry", ImVec2{ 150, 40 })) {
		style.set_theme(theme::cherry);
	}
	ImGui::SetCursorPos(ImVec2(90, 130));
	if (ImGui::Button("Night Blue", ImVec2{ 150, 40 })) {
		style.set_theme(theme::night_blue);
	}
	ImGui::SetCursorPos(ImVec2(90, 170));
	if (ImGui::Button("Neon", ImVec2{ 150, 40 })) {
		style.set_theme(theme::neon);
	}
	ImGui::SetCursorPos(ImVec2(90, 210));
	if (ImGui::Button("Paper", ImVec2{ 150, 40 })) {
		style.set_theme(theme::paper);
	}
	ImGui::SetCursorPos(ImVec2(90, 250));
	if (ImGui::Button("Purple", ImVec2{ 150, 40 })) {
		style.set_theme(theme::purple);
	}
	ImGui::SetCursorPos(ImVec2{ 20, 350 });
	ImGui::Text("Playing:\n    %s", now_playing.name.c_str());

	ImGui::End();
}

void UI::play(const std::string &url)
{
	player->play(url);
}

void UI::notice(std::string what)
{
	notice_what = what;
	time = std::chrono::steady_clock::now() + std::chrono::seconds(5);
}
