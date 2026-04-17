#include <bits/stdc++.h>
using namespace std;

class Twitter {
private:
    struct Tweet {
        int id;
        int time;
        Tweet* next;
        Tweet(int tweetId, int timestamp, Tweet* nxt = nullptr)
            : id(tweetId), time(timestamp), next(nxt) {}
    };

    int globalTime = 0;
    unordered_map<int, unordered_set<int>> followees;
    unordered_map<int, Tweet*> tweetHead;

public:
    Twitter() {}

    void postTweet(int userId, int tweetId) {
        Tweet* newTweet = new Tweet(tweetId, globalTime++, tweetHead[userId]);
        tweetHead[userId] = newTweet;
    }

    vector<int> getNewsFeed(int userId) {
        vector<int> result;

        auto cmp = [](Tweet* a, Tweet* b) {
            return a->time < b->time;
        };

        priority_queue<Tweet*, vector<Tweet*>, decltype(cmp)> pq(cmp);

        if (tweetHead.count(userId) && tweetHead[userId] != nullptr) {
            pq.push(tweetHead[userId]);
        }

        if (followees.count(userId)) {
            for (int followeeId : followees[userId]) {
                if (followeeId == userId) continue;
                if (tweetHead.count(followeeId) && tweetHead[followeeId] != nullptr) {
                    pq.push(tweetHead[followeeId]);
                }
            }
        }

        while (!pq.empty() && result.size() < 10) {
            Tweet* topTweet = pq.top();
            pq.pop();

            result.push_back(topTweet->id);

            if (topTweet->next != nullptr) {
                pq.push(topTweet->next);
            }
        }

        return result;
    }

    void follow(int followerId, int followeeId) {
        if (followerId == followeeId) return;
        followees[followerId].insert(followeeId);
    }

    void unfollow(int followerId, int followeeId) {
        if (followees.count(followerId)) {
            followees[followerId].erase(followeeId);
        }
    }
};

void printFeed(const vector<int>& feed) {
    for (int tweetId : feed) {
        cout << tweetId << " ";
    }
    cout << "\n";
}

int main() {
    Twitter twitter;

    twitter.postTweet(1, 5);
    cout << "Feed de 1 despues de postear 5: ";
    printFeed(twitter.getNewsFeed(1));

    twitter.follow(1, 2);
    twitter.postTweet(2, 6);

    cout << "Feed de 1 despues de seguir a 2 y que 2 postee 6: ";
    printFeed(twitter.getNewsFeed(1));

    twitter.unfollow(1, 2);

    cout << "Feed de 1 despues de dejar de seguir a 2: ";
    printFeed(twitter.getNewsFeed(1));


    twitter.postTweet(1, 7);
    twitter.postTweet(1, 8);
    twitter.postTweet(2, 9);
    twitter.follow(1, 2);

    cout << "Feed de 1 con mas tweets: ";
    printFeed(twitter.getNewsFeed(1));

    return 0;
}
