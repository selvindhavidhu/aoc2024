#include "day_3_header.h"
#include "stdheaders.h"

static std::string read_file_contents(const std::string& file_path) {
	std::ifstream file(file_path, std::ios::in | std::ios::binary);
	if (!file) {
		throw std::runtime_error("Failed to open file: " + file_path);
	}

	std::ostringstream contents;
	contents << file.rdbuf();
	return contents.str();
}

static int safe_string_to_int(const std::string& str) {
	try {
		return std::stoi(str);
	}
	catch (const std::invalid_argument&) {
		throw std::runtime_error("conversion failed: invalid input '"
			+ str + "'");
	}
	catch (const std::out_of_range&) {
		throw std::runtime_error("conversion failed: value out of range for"
			" input '" + str + "'");
	}
}

long long solve_day_3_part_1(const char* input_file_path) {
	std::string file_contents = read_file_contents(std::string(input_file_path));

	const std::regex mul_pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
	std::sregex_iterator begin(file_contents.begin(), file_contents.end(), mul_pattern);
	std::sregex_iterator end;

	long long sum = 0;
	for (auto it = begin; it != end; ++it) {
		int lhs = safe_string_to_int((*it)[1]);
		int rhs = safe_string_to_int((*it)[2]);
		sum += lhs * rhs;
	}

	return sum;
}

long long solve_day_3_part_2(const char* input_file_path) {
	std::string file_contents = read_file_contents(std::string(input_file_path));

	const std::regex token_regex(R"(do\(\)|don't\(\)|mul\(\d{1,3},\d{1,3}\))");
	const std::regex mul_regex(R"(mul\((\d{1,3}),(\d{1,3})\))");
	std::sregex_iterator begin(file_contents.begin(), file_contents.end(), token_regex);
	std::sregex_iterator end;

	int sum = 0;
	bool mul_enabled = true;
	for (auto it = begin; it != end; ++it) {
		std::string token = it->str();

		if (token == "do()") {
			mul_enabled = true;
		} else if (token == "don't()") {
			mul_enabled = false;
		} else if (mul_enabled) {
			std::smatch mul_match;
			if (std::regex_match(token, mul_match, mul_regex)) {
				int lhs = safe_string_to_int(mul_match[1]);
				int rhs = safe_string_to_int(mul_match[2]);
				sum += lhs * rhs;
			}
		}
	}

	return sum;
}
