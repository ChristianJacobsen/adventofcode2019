#include <iomanip>
#include <iostream>
#include <vector>

#include "intcode.hpp"

int main() {
    std::vector<int> program = intcode::build(std::cin);
    bool found{false};
    for (int i{0}; i < 100; i++) {
        if (found) break;

        for (int j{0}; j < 100; j++) {
            if (found) break;

            auto program_to_run{program};
            program_to_run[1] = i;
            program_to_run[2] = j;
            intcode::run(program_to_run, 0);
            if (program_to_run[0] == 19690720) {
                std::cout << std::setw(2) << std::setfill('0') << i << j << '\n';
                found = true;
            }
        }
    }

    return EXIT_SUCCESS;
}
