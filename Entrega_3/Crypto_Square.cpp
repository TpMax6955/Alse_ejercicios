#include <iostream>
#include <string>
#include <cmath>
#include <cctype>

using namespace std;

class CryptoSquare {
public:
    CryptoSquare(string input) {
        for (char c : input) {
            if (isalnum(c)) {
                text.push_back(tolower(c));
            }
        }
        size_t length = text.size();
        side_length = ceil(sqrt(length));

        text.resize(side_length * side_length, ' ');
    }

    string ciphertext() {
        string result;
        for (size_t i = 0; i < side_length; ++i) {
            for (size_t j = i; j < text.size(); j += side_length) {
                result.push_back(text[j]);
            }
            result.push_back(' ');
        }
        if (!result.empty() && result.back() == ' ') {
            result.pop_back();
        }
        return result;
    }

private:
    string text;
    size_t side_length;
};

int main() {
    string input = "If man was meant to stay on the ground, god would have given us roots.";
    CryptoSquare cs(input);

    cout << "Cifrado: " << cs.ciphertext() << endl;
    return 0;
}
