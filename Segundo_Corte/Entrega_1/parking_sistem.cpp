#include <iostream>

class ParkingSystem {
private:
    int bigSpaces;
    int mediumSpaces;
    int smallSpaces;

public:
    ParkingSystem(int big, int medium, int small) {
        bigSpaces = big;
        mediumSpaces = medium;
        smallSpaces = small;
    }

    bool addCar(int carType) {
        if (carType == 1) {
            if (bigSpaces > 0) {
                bigSpaces--;
                return true;
            }
        } else if (carType == 2) {
            if (mediumSpaces > 0) {
                mediumSpaces--;
                return true;
            }
        } else if (carType == 3) {
            if (smallSpaces > 0) {
                smallSpaces--;
                return true;
            }
        }
        return false;
    }
};

int main() {
    ParkingSystem parkingSystem(1, 1, 0);

    std::cout << parkingSystem.addCar(1) << std::endl;
    std::cout << parkingSystem.addCar(2) << std::endl;
    std::cout << parkingSystem.addCar(3) << std::endl;
    std::cout << parkingSystem.addCar(1) << std::endl;

    return 0;
}
