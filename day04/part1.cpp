#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

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

    int lower_bound{};
    int upper_bound{};
    in >> lower_bound >> upper_bound;

    int password_count{0};
    for (int i = lower_bound; i < upper_bound; i++) {
        const auto str = std::to_string(i);
        if (std::is_sorted(cbegin(str), cend(str))) {
            std::array<int, 10> arr{0};
            for (const auto c : str) {
                arr[c - '0']++;
            }

            if (std::any_of(begin(arr), end(arr), [](const int i){ return i >= 2; })) password_count++;
        }
    }

    std::cout << password_count << '\n';

    return EXIT_SUCCESS;
}
