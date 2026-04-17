#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

namespace date_independent {

class clock {
public:
    explicit clock(int total_minutes) : minutes(normalize(total_minutes)) {}

    static clock at(int hour, int minute) {
        return clock(hour * 60 + minute);
    }

    clock plus(int minutes_) const {
        return clock(minutes + minutes_);
    }

    operator std::string() const {
        int hh = minutes / 60;
        int mm = minutes % 60;

        ostringstream out;
        out << setw(2) << setfill('0') << hh
            << ":"
            << setw(2) << setfill('0') << mm;
        return out.str();
    }

    bool operator==(const clock& other) const {
        return minutes == other.minutes;
    }

    bool operator!=(const clock& other) const {
        return !(*this == other);
    }

private:
    int minutes;

    static int normalize(int total) {
        const int DAY = 24 * 60;
        total %= DAY;
        if (total < 0) total += DAY;
        return total;
    }
};

} // namespace date_independent

int main() {
    using date_independent::clock;

    auto c1 = clock::at(8, 0);
    auto c2 = c1.plus(61);
    auto c3 = clock::at(25, 0);
    auto c4 = clock::at(-1, 15); 
    auto c5 = clock::at(3, -20);
    auto c6 = clock::at(15, 37);
    auto c7 = clock::at(39, 37); 

    cout << "c1 = " << string(c1) << "\n";
    cout << "c2 = " << string(c2) << "\n";
    cout << "c3 = " << string(c3) << "\n";
    cout << "c4 = " << string(c4) << "\n";
    cout << "c5 = " << string(c5) << "\n";

    cout << boolalpha;
    cout << "c6 == c7 ? " << (c6 == c7) << "\n";
    cout << "c1 != c2 ? " << (c1 != c2) << "\n";

    return 0;
}
