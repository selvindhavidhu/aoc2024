#include "day_4_header.h"
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

static std::vector<std::vector<char>> string_to_grid(const std::string& text) {
	std::vector<std::vector<char>> result;
	std::vector<char> row;

	for (char ch : text)
	{
		if (ch == '\n')
		{
			result.push_back(row);
			row.clear();
		}
		if (!std::isspace(ch))
			row.push_back(ch);
	}
	result.push_back(row);

	return result;
}

static bool is_valid(const int x, const int y, const int row, const int col)
{
	return (x >= 0 && x < row) && (y >= 0 && y < col);
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

int solve_day_4_part_1(const char* input_file_path) {
	const std::string file_contents = read_file_contents(std::string(input_file_path));
	const auto grid = string_to_grid(file_contents);

	int row_index {0}, col_index{0};
	int count {0};

	// Define the 8 possible directions for searching:
	// {dr, dc} pairs where dr is change in row, dc is change in column.
	// 0: Right (0, 1)
	// 1: Left (0, -1)
	// 2: Down (1, 0)
	// 3: Up (-1, 0)
	// 4: Down-Right Diagonal (1, 1)
	// 5: Up-Left Diagonal (-1, -1)
	// 6: Down-Left Diagonal (1, -1)
	// 7: Up-Right Diagonal (-1, 1)
	int dr[] = {0, 0, 1, -1, 1, -1, 1, -1};
	int dc[] = {1, -1, 0, 0, 1, -1, -1, 1};
	for (const auto& row : grid)
	{
		col_index = 0;
		for (const auto& col : row)
		{
			constexpr int DIR_COUNT = 8;
			int new_row_index {row_index};
			int new_col_index {col_index};
			for (int d = 0; d < DIR_COUNT; d++)
			{
				constexpr int CHAR_COUNT = 4;
				int k;
				for (k = 0; k < CHAR_COUNT; k++)
				{
					if (constexpr char search_for[] = {'X', 'M', 'A', 'S'}; !is_valid(new_row_index, new_col_index, row_index, col_index) || col != search_for[k]) break;
					new_row_index += dr[d];
					new_col_index += dc[d];
				}

				if (k == 4) count++;
			}

			++col_index;
		}
		++row_index;
	}

	// for (int i = 0; i < static_cast<int>(grid.size()); i++)
	// {
	// 	for (int j = 0; j < static_cast<int>(grid[i].size()); j++)
	// 	{
	// 		constexpr int DIR_COUNT = 8;
	// 		int x = i, y = j;
	// 		for (int d = 0; d < DIR_COUNT; d++)
	// 		{
	// 			constexpr int CHAR_COUNT = 4;
	// 			int k;
	// 			for (k = 0; k < CHAR_COUNT; k++)
	// 			{
	// 				if (constexpr char search_for[] = {'X', 'M', 'A', 'S'}; !is_valid(x, y, i, j) || grid[i][j] != search_for[k]) break;
	// 				x += dr[d];
	// 				y += dc[d];
	// 			}
	//
	// 			if (k == 4) count++;
	// 		}
	// 	}
	// }

	return count;
}

long long solve_day_4_part_2(const char* input_file_path) {
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
