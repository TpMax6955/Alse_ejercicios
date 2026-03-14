#include <iostream>
using namespace std;

namespace space_age {

class space_age {
private:
    long long s;

public:
    space_age(long long seconds) {
        s = seconds;
    }

    long long seconds() {
        return s;
    }

    double on_earth() {
        return s / 31557600.0;
    }

    double on_mercury() {
        return on_earth() / 0.2408467;
    }

    double on_venus() {
        return on_earth() / 0.61519726;
    }

    double on_mars() {
        return on_earth() / 1.8808158;
    }

    double on_jupiter() {
        return on_earth() / 11.862615;
    }

    double on_saturn() {
        return on_earth() / 29.447498;
    }

    double on_uranus() {
        return on_earth() / 84.016846;
    }

    double on_neptune() {
        return on_earth() / 164.79132;
    }
};

}

int main() {
    space_age::space_age age(1000000000);

    cout << age.seconds() << endl;
    cout << age.on_earth() << endl;
    cout << age.on_mercury() << endl;
    cout << age.on_venus() << endl;
    cout << age.on_mars() << endl;
    cout << age.on_jupiter() << endl;
    cout << age.on_saturn() << endl;
    cout << age.on_uranus() << endl;
    cout << age.on_neptune() << endl;

    return 0;
}
