#include <iostream>

namespace armstrong_numbers {

bool is_armstrong_number(int number) {
    int temp = number, digits = 0, sum = 0;

    do {
        digits++;
        temp /= 10;
    } while (temp > 0);

    temp = number;
    do {
        int digit = temp % 10;
        int power = 1;

        for (int i = 0; i < digits; i++) {
            power *= digit;
        }

        sum += power;
        temp /= 10;
    } while (temp > 0);

    return sum == number;
}

}

int main() {
    std::cout << armstrong_numbers::is_armstrong_number(153) << '\n'; // 1
    std::cout << armstrong_numbers::is_armstrong_number(10) << '\n';  // 0
}
