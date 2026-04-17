#include <iostream>
#include <unordered_map>
#include <set>
using namespace std;

class AuctionSystem {
private:
    unordered_map<int, set<pair<int, int>>> items;

    unordered_map<int, unordered_map<int, int>> users;

public:
    AuctionSystem() {}

    void addBid(int userId, int itemId, int bidAmount) {

        if (users.count(userId) && users[userId].count(itemId)) {
            int oldAmount = users[userId][itemId];
            items[itemId].erase({oldAmount, userId});
        }

        users[userId][itemId] = bidAmount;
        items[itemId].insert({bidAmount, userId});
    }

    void updateBid(int userId, int itemId, int newAmount) {
        int oldAmount = users[userId][itemId];
        items[itemId].erase({oldAmount, userId});

        users[userId][itemId] = newAmount;
        items[itemId].insert({newAmount, userId});
    }

    void removeBid(int userId, int itemId) {
        int oldAmount = users[userId][itemId];
        items[itemId].erase({oldAmount, userId});
        users[userId].erase(itemId);

        // limpieza opcional
        if (users[userId].empty()) {
            users.erase(userId);
        }
        if (items[itemId].empty()) {
            items.erase(itemId);
        }
    }

    int getHighestBidder(int itemId) {
        if (!items.count(itemId) || items[itemId].empty()) {
            return -1;
        }
        return items[itemId].rbegin()->second;
    }
};

int main() {
    AuctionSystem auctionSystem;

    auctionSystem.addBid(1, 7, 5);
    auctionSystem.addBid(2, 7, 6);
    cout << "Highest bidder for item 7: "
         << auctionSystem.getHighestBidder(7) << "\n";

    auctionSystem.updateBid(1, 7, 8);
    cout << "Highest bidder for item 7 after update: "
         << auctionSystem.getHighestBidder(7) << "\n";

    auctionSystem.removeBid(2, 7);
    cout << "Highest bidder for item 7 after removing user 2: "
         << auctionSystem.getHighestBidder(7) << "\n";

    cout << "Highest bidder for item 3: "
         << auctionSystem.getHighestBidder(3) << "\n";

    auctionSystem.addBid(10, 9, 100);
    auctionSystem.addBid(20, 9, 100);
    cout << "Highest bidder for item 9 (tie): "
         << auctionSystem.getHighestBidder(9) << "\n";

    return 0;
}
