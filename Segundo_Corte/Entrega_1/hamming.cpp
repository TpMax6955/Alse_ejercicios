#include <iostream>
#include <string>
#include <stdexcept>

namespace hamming {

int compute(const std::string& left, const std::string& right) {
    if (left.length() != right.length()) {
        throw std::domain_error("Las cadenas deben tener la misma longitud");
    }

    int difference = 0;

    for (size_t i = 0; i < left.length(); i++) {
        if (left[i] != right[i]) {
            difference++;
        }
    }

    return difference;
}

}

int main() {
    std::cout << hamming::compute("GAGCCTACTAACGGGAT", "CATCGTAATGACGGCCT") << '\n'; // 7
    std::cout << hamming::compute("GGACTGA", "GGACTGA") << '\n';                     // 0
    std::cout << hamming::compute("ACCAGGG", "ACTATGG") << '\n';                     // 2

    return 0;
}
