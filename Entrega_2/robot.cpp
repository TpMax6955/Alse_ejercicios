#include <iostream>
#include <string>
#include <utility>
using namespace std;

enum class Bearing {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
};

class Robot {
private:
    pair<int, int> position;
    Bearing bearing;

public:

    Robot() : position({0, 0}), bearing(Bearing::NORTH) {}


    Robot(pair<int, int> pos, Bearing dir) : position(pos), bearing(dir) {}

    pair<int, int> get_position() const {
        return position;
    }

    Bearing get_bearing() const {
        return bearing;
    }

    void turn_right() {
        bearing = static_cast<Bearing>((static_cast<int>(bearing) + 1) % 4);
    }

    void turn_left() {
        bearing = static_cast<Bearing>((static_cast<int>(bearing) + 3) % 4);
    }

    void advance() {
        int dir = static_cast<int>(bearing);

        if (dir == 0) position.second++;
        else if (dir == 1) position.first++;
        else if (dir == 2) position.second--;
        else if (dir == 3) position.first--;
    }

    void execute_sequence(const string& instructions) {
        for (char c : instructions) {
            if (c == 'R') turn_right();
            else if (c == 'L') turn_left();
            else if (c == 'A') advance();
        }
    }
};

string bearing_to_string(Bearing b) {
    if (b == Bearing::NORTH) return "NORTH";
    if (b == Bearing::EAST) return "EAST";
    if (b == Bearing::SOUTH) return "SOUTH";
    return "WEST";
}

void print_robot(const Robot& r) {
    auto pos = r.get_position();
    cout << "Posicion: (" << pos.first << ", " << pos.second << ")\n";
    cout << "Direccion: " << bearing_to_string(r.get_bearing()) << "\n";
    cout << "-------------------------\n";
}

int main() {
    Robot r1;
    cout << "Robot por defecto:\n";
    print_robot(r1);

    Robot r2({7, 3}, Bearing::NORTH);
    cout << "Robot inicial:\n";
    print_robot(r2);

    r2.turn_right();
    cout << "Despues de turn_right():\n";
    print_robot(r2);

    r2.advance();
    cout << "Despues de advance():\n";
    print_robot(r2);

    r2.turn_left();
    cout << "Despues de turn_left():\n";
    print_robot(r2);

    r2.execute_sequence("RAALAL");
    cout << "Despues de execute_sequence(\"RAALAL\"):\n";
    print_robot(r2);

    return 0;
}
