#include <iostream>
#include <stdexcept>
#include <utility>
#include <cmath>
using namespace std;

namespace queen_attack {

class chess_board {
private:
    pair<int, int> white_queen;
    pair<int, int> black_queen;

    bool valid(const pair<int, int>& p) const {
        return p.first >= 0 && p.first < 8 && p.second >= 0 && p.second < 8;
    }

public:
    chess_board(pair<int, int> white, pair<int, int> black)
        : white_queen(white), black_queen(black) {
        if (!valid(white_queen) || !valid(black_queen) || white_queen == black_queen) {
            throw domain_error("Posicion invalida");
        }
    }

    pair<int, int> white() const {
        return white_queen;
    }

    pair<int, int> black() const {
        return black_queen;
    }

    bool can_attack() const {
        return white_queen.first == black_queen.first ||
               white_queen.second == black_queen.second ||
               abs(white_queen.first - black_queen.first) ==
               abs(white_queen.second - black_queen.second);
    }
};

}

void probarTablero(pair<int, int> w, pair<int, int> b) {
    try {
        queen_attack::chess_board board(w, b);

        cout << "White: (" << board.white().first << ", " << board.white().second << ")\n";
        cout << "Black: (" << board.black().first << ", " << board.black().second << ")\n";
        cout << "Pueden atacarse? " << (board.can_attack() ? "SI" : "NO") << "\n";
        cout << "--------------------------\n";
    } catch (const domain_error& e) {
        cout << "Error: " << e.what() << "\n";
        cout << "--------------------------\n";
    }
}

int main() {
    probarTablero({2, 2}, {0, 3});
    probarTablero({2, 4}, {2, 6});
    probarTablero({4, 5}, {2, 5});
    probarTablero({2, 2}, {0, 4});
    probarTablero({3, 7}, {3, 7});
    probarTablero({8, 1}, {2, 2});

    return 0;
}
