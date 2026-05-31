#include "apiProvider.hpp"

void apiProvider::search(std::string name, int limit)
{
	search_limit = limit;
	retry_time = 0;
	seen_names.clear();
	list.clear();
	search_name = name;
	is_loading = true;
	get_response();
}

/*
@brief 获取搜索信息，更新res

@prama string name:电台的名字
*/
void apiProvider::get_response(int offset)
{
	retry_time++;
	res = cpr::GetAsync(
		cpr::Url{
			"https://de1.api.radio-browser.info/json/stations/search" },
		cpr::Parameters{ { "name", search_name },
				 { "limit", std::to_string(search_limit + 10) },
				 { "offset", std::to_string(offset) } },
		cpr::VerifySsl{ false });
}
/*
@brief 根据爬取获得res获得r的json信息
*/
void apiProvider::update()
{
	//检查网络爬取是否完成
	if (res.valid() && res.wait_for(std::chrono::seconds(0)) ==
				   std::future_status::ready) {
		r = res.get();

		if (r.status_code == 200) {
			parse_json(r.text);
		} else {
			//error
		}
		is_loading = false;
	}
	if ((retry_time <= 5) && (!is_loading) && list.size() < 20) {
		is_loading = true;
		get_response(list.size()); //待修改：数字错误。
	}
}

void apiProvider::parse_json(const std::string &json_text)
{
	using json = nlohmann::json;
	try {
		auto data = json::parse(json_text);
		if (data.empty()) {
			is_loading = false;
			return;
		}
		for (const auto &item : data) {
			if (list.size() >
			    search_limit) { //超过20个就舍弃（待修改：取消硬编码）
				break;
			}

			std::string name =
				item.value("name", "Unknown Station");
			std::string url = item.value("url_resolved", "");
			//去除重复
			if (name.empty() ||
			    seen_names.find(name) != seen_names.end()) {
				continue;
			}

			Radio radio_temp;
			radio_temp.name = name;
			radio_temp.url = url;
			radio_temp.country = item.value("country", "");

			list.push_back(radio_temp);

			seen_names.insert(name);
		}

	} catch (json::parse_error &e) {
	}
}

std::vector<Radio> &apiProvider::get_list()
{
	return list;
};