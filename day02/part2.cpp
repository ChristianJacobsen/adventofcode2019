#include <algorithm>
#include <iomanip>
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
    bool found{false};
    for (int i{0}; i < 100; i++) {
        if (found) break;

        for (int j{0}; j < 100; j++) {
            if (found) break;

            auto program_to_run{program};
            program_to_run[1] = i;
            program_to_run[2] = j;
            run(program_to_run, 0);
            if (program_to_run[0] == 19690720) {
                std::cout << std::setw(2) << std::setfill('0') << i << j << '\n';
                found = true;
            }
        }
    }

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
