#include <iostream>
#include <vector>
using namespace std;

class ATM {
private:
    vector<int> denominations = {20, 50, 100, 200, 500};
    vector<long long> count;

public:
    ATM() : count(5, 0) {}

    void deposit(vector<int> banknotesCount) {
        for (int i = 0; i < 5; i++) {
            count[i] += banknotesCount[i];
        }
    }

    vector<int> withdraw(int amount) {
        vector<int> used(5, 0);

        for (int i = 4; i >= 0; i--) {
            long long canTake = min(count[i], (long long)amount / denominations[i]);
            used[i] = (int)canTake;
            amount -= used[i] * denominations[i];
        }

        if (amount != 0) {
            return {-1};
        }

        for (int i = 0; i < 5; i++) {
            count[i] -= used[i];
        }

        return used;
    }
};

void printVector(const vector<int>& v) {
    cout << "[";
    for (int i = 0; i < (int)v.size(); i++) {
        cout << v[i];
        if (i + 1 < (int)v.size()) cout << ", ";
    }
    cout << "]\n";
}

int main() {
    ATM atm;

    // Ejemplo parecido al del enunciado
    atm.deposit({0, 0, 1, 2, 1});
    cout << "withdraw(600): ";
    printVector(atm.withdraw(600));

    atm.deposit({0, 1, 0, 1, 1});
    cout << "withdraw(600): ";
    printVector(atm.withdraw(600));

    cout << "withdraw(550): ";
    printVector(atm.withdraw(550));

    return 0;
}
