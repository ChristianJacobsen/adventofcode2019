#ifndef INTCODE_HPP
#define INTCODE_HPP
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include <boost/algorithm/string/split.hpp>

namespace intcode {

enum class OP_CODE {
    ADD = 1,
    MUL = 2,
    READ = 3,
    PRINT = 4,
    JMP = 5,
    JMPN = 6,
    LT = 7,
    EQ = 8,
    FIN = 99
};

enum class PARAM_MODE {
    POSITION = 0,
    IMMEDIATE = 1
};

namespace {
    int& get_value(std::vector<int>& program, int pos, PARAM_MODE m);
}

std::vector<int> build(std::istream& in);

void print_program(std::vector<int>& program);

void run(std::vector<int>& program, int pos);

} // namespace intcode

#endif // INTCODE_HPP
