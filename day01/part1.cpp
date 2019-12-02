#include <iostream>
#include <numeric>
#include <string>
#include <vector>

int calculateFuelGivenMass(int sum, int mass);

int main() {
    std::vector<int> masses;

    int in;
    while (std::cin >> in) {
        masses.push_back(in);
    }

    const int fuel_needed = std::accumulate(cbegin(masses), cend(masses), 0, calculateFuelGivenMass);

    std::cout << fuel_needed << '\n';

    return EXIT_SUCCESS;
}

int calculateFuelGivenMass(int sum, int mass) {
    return sum + ((mass / 3) - 2);
}
