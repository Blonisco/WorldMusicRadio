#include "apiProvider.hpp"
#include "Country.hpp"
#include "cpr/parameters.h"
#include <chrono>
#include <json.hpp>
#include "UI.h"
void apiProvider::search(std::string name, int limit, std::string country)
{
	start_time = std::chrono::steady_clock::now();
	search_limit = limit;
	retry_time = 0;
	seen_names.clear();
	list.clear();
	search_name = name;
	is_loading = true;
	search_country = country;
	get_response();
}

/*
@brief 获取搜索信息，更新res

@prama string name:电台的名字
*/
void apiProvider::get_response(int offset)
{
	cpr::Parameters params{
		{ "name", search_name },
		{ "limit", std::to_string(search_limit + 10) },
		{ "offset", std::to_string(offset) },
	};
	if (search_country != "") {
		params.Add({ "countrycode",
			     country_to_countrycode[search_country] });
	}

	retry_time++;
	res = cpr::GetAsync(
		cpr::Url{
			"https://de1.api.radio-browser.info/json/stations/search" },
		params, cpr::VerifySsl{ false });
}
/*
@brief 根据爬取获得res获得r的json信息
*/
void apiProvider::update()
{
	//检查网络爬取是否完成
	if (res && res->valid() &&
	    res->wait_for(std::chrono::seconds(0)) ==
		    std::future_status::ready) {
		r = res->get();

		if (r.status_code == 200) {
			parse_json(r.text);
		} else {
			ui->notice("Failed to get the information!");
		}
		if (retry_time == 6 && list.size() == 0) {
			ui->notice("Can't find anything!");
		}
		is_loading = false;
	}
	if ((retry_time <= 5) && (!is_loading) && list.size() < search_limit) {
		is_loading = true;
		get_response(list.size());
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
			if (list.size() > search_limit) {
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

apiProvider::apiProvider(UI *UI)
	: ui(UI)
{
}
