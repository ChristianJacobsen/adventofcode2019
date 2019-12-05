#include <algorithm>
#include <iostream>
#include <vector>

#include <boost/algorithm/string.hpp>

#include "intcode.hpp"

int main() {
    std::string in;
    std::getline(std::cin, in);
    std::vector<std::string> results;
    boost::split(results, in, [](char c){ return c == ','; });
    std::vector<int> program;
    std::transform(
        begin(results),
        end(results),
        std::back_inserter(program),
        [](std::string s){ return atoi(s.c_str()); }
    );
    program[1] = 12;
    program[2] = 2;
    intcode::run(program, 0);

    std::cout << program[0] << '\n';

    return EXIT_SUCCESS;
}
