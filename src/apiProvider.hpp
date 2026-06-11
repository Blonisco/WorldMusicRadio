#ifndef API_PROVIDER_H_
#define API_PROVIDER_H_

#include <optional>
#include <vector>
#include <cpr/cpr.h>
#include "Radio.hpp"
#include <string>
#include <chrono>
class UI;
class apiProvider {
    private:
	std::vector<Radio> list;
	std::optional<cpr::AsyncResponse> res;
	cpr::Response r;
	std::string search_name;
	std::string search_country;
	bool is_loading;
	UI *ui;
	std::chrono::steady_clock::time_point start_time =
		std::chrono::steady_clock::now();
	std::set<std::string> seen_names;
	int retry_time = 6; //防止一开始就搜索
	int search_limit; //每次搜索最大数目

    public:
	void search(std::string, int limit = 20, std::string country = "");
	void update();
	apiProvider(UI *);
	void parse_json(const std::string &);
	std::vector<Radio> &get_list();
	void get_response(int offset = 0);
	int get_retry_time()
	{
		return retry_time;
	};
};

#endif
