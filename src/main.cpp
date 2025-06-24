#include "stdheaders.h"
#include "day_3/day_3_header.h"

int main() {
    constexpr char input_file_path[] = "day_3_input.txt";
    try {
        std::cout << solve_day_3_part_1(input_file_path) << '\n';
    } catch (const std::runtime_error& ex) {
        std::cerr << ex.what() << std::endl;
    }

    return 0;
}