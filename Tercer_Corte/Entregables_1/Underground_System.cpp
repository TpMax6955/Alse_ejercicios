#include <iostream>
#include <unordered_map>
#include <string>
#include <iomanip>

using namespace std;

class UndergroundSystem {
private:
    struct CheckInInfo {
        string stationName;
        int time;
    };

    struct RouteStats {
        long long totalTime = 0;
        int tripCount = 0;
    };

    unordered_map<int, CheckInInfo> checkins;
    unordered_map<string, RouteStats> stats;

    string makeRouteKey(const string& start, const string& end) {
        return start + "->" + end;
    }

public:
    UndergroundSystem() {}

    void checkIn(int id, string stationName, int t) {
        checkins[id] = {stationName, t};
    }

    void checkOut(int id, string stationName, int t) {
        CheckInInfo info = checkins[id];
        checkins.erase(id);

        string routeKey = makeRouteKey(info.stationName, stationName);
        int tripTime = t - info.time;

        stats[routeKey].totalTime += tripTime;
        stats[routeKey].tripCount += 1;
    }

    double getAverageTime(string startStation, string endStation) {
        string routeKey = makeRouteKey(startStation, endStation);
        const RouteStats& route = stats[routeKey];
        return static_cast<double>(route.totalTime) / route.tripCount;
    }
};

int main() {
    cout << fixed << setprecision(5);

    UndergroundSystem undergroundSystem;

    undergroundSystem.checkIn(45, "Leyton", 3);
    undergroundSystem.checkIn(32, "Paradise", 8);
    undergroundSystem.checkIn(27, "Leyton", 10);

    undergroundSystem.checkOut(45, "Waterloo", 15);
    undergroundSystem.checkOut(27, "Waterloo", 20);
    undergroundSystem.checkOut(32, "Cambridge", 22);

    cout << "Promedio Paradise -> Cambridge: "
         << undergroundSystem.getAverageTime("Paradise", "Cambridge") << endl;

    cout << "Promedio Leyton -> Waterloo: "
         << undergroundSystem.getAverageTime("Leyton", "Waterloo") << endl;

    undergroundSystem.checkIn(10, "Leyton", 24);

    cout << "Promedio Leyton -> Waterloo (antes del checkout de id=10): "
         << undergroundSystem.getAverageTime("Leyton", "Waterloo") << endl;

    undergroundSystem.checkOut(10, "Waterloo", 38);

    cout << "Promedio Leyton -> Waterloo (final): "
         << undergroundSystem.getAverageTime("Leyton", "Waterloo") << endl;

    return 0;
}
