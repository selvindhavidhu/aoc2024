#include "stdheaders.h"
#include "day_4/day_4_header.h"

int main() {
    constexpr char input_file_path[] = "day_4_sample_input.txt";
    try {
        std::cout << solve_day_4_part_1(input_file_path) << '\n';
    } catch (const std::runtime_error& ex) {
        std::cerr << ex.what() << std::endl;
    }

    return 0;
}