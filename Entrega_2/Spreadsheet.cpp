#include <bits/stdc++.h>
using namespace std;

class Spreadsheet {
private:
    unordered_map<string, int> cell;

    int val(const string& s) {
        if (isdigit(s[0])) return stoi(s);
        return cell[s];
    }

public:
    Spreadsheet(int rows) {}

    void setCell(string c, int v) {
        cell[c] = v;
    }

    void resetCell(string c) {
        cell[c] = 0;
    }

    int getValue(string formula) {
        formula = formula.substr(1);
        int p = formula.find('+');
        return val(formula.substr(0, p)) + val(formula.substr(p + 1));
    }
};

int main() {
    Spreadsheet spreadsheet(3);

    cout << spreadsheet.getValue("=5+7") << "\n";
    spreadsheet.setCell("A1", 10);
    cout << spreadsheet.getValue("=A1+6") << "\n";
    spreadsheet.setCell("B2", 15);
    cout << spreadsheet.getValue("=A1+B2") << "\n";
    spreadsheet.resetCell("A1");
    cout << spreadsheet.getValue("=A1+B2") << "\n";

    return 0;
}
