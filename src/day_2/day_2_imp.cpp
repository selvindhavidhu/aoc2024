#include "day_2_header.h"
#include "stdheaders.h"

static bool is_increasing(const std::vector<int>& vec) {
	return std::is_sorted(vec.begin(), vec.end());
}

static bool is_decreasing(const std::vector<int>& vec) {
	return std::is_sorted(vec.rbegin(), vec.rend());
}

static bool is_in_range(int value) {
	value = std::abs(value);
	return (value >= 1 && value <= 3);
}

static bool is_safe(const std::vector<int>& levels) {
	// Edge case: list has only 1 element
	auto size = levels.size();
	if (size < 2) return true;

	// Edge case: list has only 2 elements
	if (size == 2) return is_in_range(levels[0] - levels[1]);

	// Assert that the list is in either increasing or decreasing order
	std::vector<int> differences(size);
	if (is_increasing(levels) || is_decreasing(levels)) {
		// Assert that the difference between adjacent levels is in the range [1, 3].
		std::adjacent_difference(std::begin(levels), std::end(levels), std::begin(differences));
		if (std::all_of(std::begin(differences) + 1, std::end(differences), is_in_range)) {
			return true;
		}
	}

	return false;
}

static bool is_safe_after_removing_single_level(const std::vector<int>& levels) {
	if (is_safe(levels)) return true;

	// remove one element at a time and check if the list is safe.
	size_t size = levels.size();
	for (size_t i = 0; i < size; ++i) {
		std::vector<int> temp(std::begin(levels), std::end(levels));
		temp.erase(temp.begin() + i);
		if (is_safe(temp)) return true;
	}

	return false;
}

int solve_day_2_part_1(const char* input_file_path) {
	int nsafe = 0;

	std::ifstream input_file(input_file_path);
	if (!input_file.is_open()) {
		std::stringstream error_message;
		error_message << "Unable to open file: " << input_file_path << '\n';
		throw std::runtime_error(error_message.str());
	}

	std::string line;
	while (std::getline(input_file, line)) {
		std::istringstream iss(line);
		std::vector<int> levels;
		
		int number;
		while (iss >> number) {
			levels.push_back(number);
		}

		if (is_safe(levels)) ++nsafe;

	}
	input_file.close();

	return nsafe;
}

int solve_day_2_part_2(const char* input_file_path) {
	int nsafe = 0;

	std::ifstream input_file(input_file_path);
	if (!input_file.is_open()) {
		std::stringstream error_message;
		error_message << "Unable to open file: " << input_file_path << '\n';
		throw std::runtime_error(error_message.str());
	}

	std::string line;
	while (std::getline(input_file, line)) {
		std::istringstream iss(line);
		std::vector<int> levels;

		int number;
		while (iss >> number) {
			levels.push_back(number);
		}

		if (is_safe_after_removing_single_level(levels)) ++nsafe;

	}
	input_file.close();

	return nsafe;
}