#include "day_2_header.h"
#include "stdheaders.h"

static bool is_increasing(const std::vector<int>& vec) {
	return std::is_sorted(vec.begin(), vec.end());
}

static bool is_decreasing(const std::vector<int>& vec) {
	return std::is_sorted(vec.rbegin(), vec.rend());
}

static bool is_in_range(int value) {
	return (value >= 1 && value <= 3) || (value <= -1 && value >= -3);
}

int solve_day_2_part_1(const char* input_file_path) {
	int unsafe_count = 0;
	int total = 0;

	std::ifstream input_file(input_file_path);
	if (!input_file.is_open()) {
		std::stringstream error_message;
		error_message << "Unable to open file: " << input_file_path << '\n';
		throw std::runtime_error(error_message.str());
	}

	std::string line;
	while (std::getline(input_file, line)) {
		++total;
		std::istringstream iss(line);
		std::vector<int> numbers;
		
		int number;
		while (iss >> number) {
			numbers.push_back(number);
		}

		std::vector<int> differences(numbers.size());
		if (is_increasing(numbers) || is_decreasing(numbers)) {
			std::adjacent_difference(numbers.begin(), numbers.end(), differences.begin());
			if (!std::all_of(differences.begin() + 1, differences.end(), is_in_range)) {
				++unsafe_count;
			}
		} else {
			++unsafe_count;
		}

	}
	input_file.close();

	return (total - unsafe_count);
}