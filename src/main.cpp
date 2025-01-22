#include "day_2/day_2_header.h"
#include "stdheaders.h"

int main() {
    const char inpult_file_path[] = "day_2_part_1_input.txt";
    try {
        std::cout << solve_day_2_part_2(inpult_file_path) << '\n';
    } catch (const std::runtime_error& ex) {
        std::cerr << ex.what() << std::endl;
    }

    return 0;
}