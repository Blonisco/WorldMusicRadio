#ifndef API_PROVIDER_H_
#define API_PROVIDER_H_

#define WIN32_LEAN_AND_MEAN // 减少 Windows 头文件污染
#include <vector>
#include <cpr/cpr.h>
#include "Radio.hpp"
#include "json.hpp"
#include <string>
class apiProvider {
    private:
	std::vector<Radio> list;
	cpr::AsyncResponse res;
	cpr::Response r;
	std::string search_name;
	bool is_loading;
	std::set<std::string> seen_names;
	int retry_time = 6; //防止一开始就搜索
	int search_limit; //每次搜索最大数目

    public:
	void search(std::string, int limit = 20);
	void update();
	void parse_json(const std::string &);
	std::vector<Radio> &get_list();
	void get_response(int offset = 0);
	int get_retry_time()
	{
		return retry_time;
	};
};

#endif