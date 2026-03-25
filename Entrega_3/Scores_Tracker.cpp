#include <bits/stdc++.h>
using namespace std;

class ExamTracker {
private:
    vector<int> times;
    vector<long long> prefix;

public:
    ExamTracker() {
        times.push_back(0);
        prefix.push_back(0LL);
    }

    void record(int time, int score) {
        times.push_back(time);
        prefix.push_back(prefix.back() + score);
    }

    long long totalScore(int startTime, int endTime) {
        int l = lower_bound(times.begin(), times.end(), startTime) - times.begin();
        int r = lower_bound(times.begin(), times.end(), endTime + 1) - times.begin();

        return prefix[r - 1] - prefix[l - 1];
    }
};

int main() {
    ExamTracker tracker;

    tracker.record(1, 98);
    cout << tracker.totalScore(1, 1)  << " (esperado: 98)\n";

    tracker.record(5, 99);
    cout << tracker.totalScore(1, 3)  << " (esperado: 98)\n";
    cout << tracker.totalScore(1, 5)  << " (esperado: 197)\n";
    cout << tracker.totalScore(3, 4)  << " (esperado: 0)\n";
    cout << tracker.totalScore(2, 5)  << " (esperado: 99)\n";

    return 0;
}
