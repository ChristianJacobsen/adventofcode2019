#include "intcode.hpp"

namespace intcode {

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

} // namespace intcode
