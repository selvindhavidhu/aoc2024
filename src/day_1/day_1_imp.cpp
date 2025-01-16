#include "day_1_header.h"
#include "stdheaders.h"

long long solve_day_1_part_2(const char* input_file_path) {
	std::vector<int> left;
	std::unordered_map<int, int> count_map;
	long long sum = 0;

	std::ifstream input_file(input_file_path);
	if (input_file && input_file.is_open()) {
		std::pair<int, int> p;
		while (input_file >> p.first >> p.second) {
			left.push_back(p.first);
			count_map[p.second]++;
		}

		input_file.close();
	}

	for (int i : left) {
		auto it = count_map.find(i);
		if (it != count_map.end()) {
			sum += static_cast<long long>(i) * it->second;
		}
	}

	return sum;
}