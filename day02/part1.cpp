#include <iostream>
#include <vector>

#include "intcode.hpp"

int main() {
    std::vector<int> program = intcode::build(std::cin);
    program[1] = 12;
    program[2] = 2;
    intcode::run(program, 0);

    std::cout << program[0] << '\n';

    return EXIT_SUCCESS;
}
