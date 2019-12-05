#ifndef INTCODE_HPP
#define INTCODE_HPP
#include <vector>

namespace intcode {

enum class OP_CODES {
    ADD = 1,
    MUL = 2,
    FIN = 99
};

void run(std::vector<int>& program, int pos);

} // namespace intcode

#endif // INTCODE_HPP
