#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "intcode.hpp"

int main(const int argc, const char** argv) {
    if (argc < 2) {
        std::cerr << "Missing input file...\n";
        return EXIT_FAILURE;
    }

    std::ifstream in{argv[1]};
    if (!in) {
        std::cerr << "Invalid input file...\n";
        return EXIT_FAILURE;
    }

    std::vector<int> program = intcode::build(in);
    intcode::run(program, 0);
}
