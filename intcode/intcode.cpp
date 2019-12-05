#include "intcode.hpp"

namespace intcode {

namespace {
    int& get_value(std::vector<int>& program, int pos, PARAM_MODE m) {
        switch (m) {
            case PARAM_MODE::IMMEDIATE: {
                return program[pos];
            }
            case PARAM_MODE::POSITION:
            default: {
                return program[program[pos]];
            }
        }
    }
}

std::vector<int> build(std::istream& in) {
    std::string s;
    std::getline(in, s);
    std::vector<std::string> split;
    boost::algorithm::split(split, s, [](unsigned char c){ return c == ','; });
    std::vector<int> program;
    std::transform(
        begin(split),
        end(split),
        std::back_inserter(program),
        [] (const std::string& s) {
            return std::stoi(s);
        }
    );
    return program;
}

void print_program(std::vector<int>& program) {
    bool is_first{true};
    for (const auto i : program) {
        if (is_first) is_first = false;
        else std::cout << ", ";
        std::cout << i;
    }
    std::cout << '\n';
}

void run(std::vector<int>& program, int pos) {
    auto op_code = static_cast<OP_CODE>(program[pos] % 100);

    auto param_a_mode = static_cast<PARAM_MODE>(program[pos] / 100 % 10);
    auto param_b_mode = static_cast<PARAM_MODE>(program[pos] / 1000 % 10);
    auto param_c_mode = static_cast<PARAM_MODE>(program[pos] / 10000 % 10);

    switch(op_code) {
        case OP_CODE::ADD: {
            const auto param_a = get_value(program, pos + 1, param_a_mode);
            const auto param_b = get_value(program, pos + 2, param_b_mode);
            auto& param_c = get_value(program, pos + 3, param_c_mode);

            param_c = param_a + param_b;

            return run(program, pos + 4);
        }

        case OP_CODE::MUL: {
            const auto param_a = get_value(program, pos + 1, param_a_mode);
            const auto param_b = get_value(program, pos + 2, param_b_mode);
            auto& param_c = get_value(program, pos + 3, param_c_mode);

            param_c = param_a * param_b;

            return run(program, pos + 4);
        }

        case OP_CODE::READ: {
            auto& param_a = get_value(program, pos + 1, param_a_mode);

            std::cin >> param_a;

            return run(program, pos + 2);
        }

        case OP_CODE::PRINT: {
            const auto param_a = get_value(program, pos + 1, param_a_mode);

            std::cout << param_a << '\n';

            return run(program, pos + 2);
        }

        case OP_CODE::JMP: {
            const auto param_a = get_value(program, pos + 1, param_a_mode);
            const auto param_b = get_value(program, pos + 2, param_b_mode);

            if (param_a) {
                return run(program, param_b);
            }
            return run(program, pos + 3);
        }

        case OP_CODE::JMPN: {
            const auto param_a = get_value(program, pos + 1, param_a_mode);
            const auto param_b = get_value(program, pos + 2, param_b_mode);

            if (!param_a) {
                return run(program, param_b);
            }
            return run(program, pos + 3);
        }

        case OP_CODE::LT: {
            const auto param_a = get_value(program, pos + 1, param_a_mode);
            const auto param_b = get_value(program, pos + 2, param_b_mode);
            auto& param_c = get_value(program, pos + 3, param_c_mode);

            param_c = param_a < param_b;

            return run(program, pos + 4);
        }

        case OP_CODE::EQ: {
            const auto param_a = get_value(program, pos + 1, param_a_mode);
            const auto param_b = get_value(program, pos + 2, param_b_mode);
            auto& param_c = get_value(program, pos + 3, param_c_mode);

            param_c = param_a == param_b;

            return run(program, pos + 4);
        }

        case OP_CODE::FIN:
            return;
    }
}

} // namespace intcode
