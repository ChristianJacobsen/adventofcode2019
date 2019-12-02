#include <algorithm>
#include <iostream>
#include <vector>

#include <boost/algorithm/string.hpp>

enum class OP_CODES {
    ADD = 1,
    MUL = 2,
    FIN = 99
};

void run(std::vector<int>& program, int pos);

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
    run(program, 0);

    std::cout << program[0] << '\n';

    return EXIT_SUCCESS;
}

void run(std::vector<int>& program, int pos) {
    switch(static_cast<OP_CODES>(program[pos])) {
        case OP_CODES::ADD: {
            const int target_pos = program[pos + 3];
            program[target_pos] = program[program[pos + 1]] + program[program[pos + 2]];
            return run(program, pos + 4);
        }
        case OP_CODES::MUL: {
            const int target_pos = program[pos + 3];
            program[target_pos] = program[program[pos + 1]] * program[program[pos + 2]];
            return run(program, pos + 4);
        }
        case OP_CODES::FIN:
            return;
    }
}
