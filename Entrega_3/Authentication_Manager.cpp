#include <bits/stdc++.h>
using namespace std;

class AuthenticationManager {
private:
    int timeToLive;
    unordered_map<string, int> tokenExpiry;

public:
    AuthenticationManager(int timeToLive) {
        this->timeToLive = timeToLive;
    }

    void generate(string tokenId, int currentTime) {
        tokenExpiry[tokenId] = currentTime + timeToLive;
    }

    void renew(string tokenId, int currentTime) {
        auto it = tokenExpiry.find(tokenId);
        if (it != tokenExpiry.end() && it->second > currentTime) {
            it->second = currentTime + timeToLive;
        }
    }

    int countUnexpiredTokens(int currentTime) {
        int count = 0;
        for (auto &p : tokenExpiry) {
            if (p.second > currentTime) {
                count++;
            }
        }
        return count;
    }
};

int main() {
    AuthenticationManager mgr(5);

    mgr.generate("aaa", 2);
    cout << "Unexpired at t=6: " << mgr.countUnexpiredTokens(6) << "\n";

    mgr.generate("bbb", 7);
    mgr.renew("aaa", 8);
    cout << "Unexpired at t=8: " << mgr.countUnexpiredTokens(8) << "\n";

    mgr.renew("bbb", 10);
    cout << "Unexpired at t=15: " << mgr.countUnexpiredTokens(15) << "\n";

    return 0;
}
