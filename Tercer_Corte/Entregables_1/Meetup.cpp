#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class Weekday {
    Sunday = 0,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};

enum class Schedule {
    First,
    Second,
    Third,
    Fourth,
    Last,
    Teenth
};

struct Date {
    int year;
    int month;
    int day;
};

bool isLeapYear(int year) {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

int daysInMonth(int year, int month) {
    static const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month == 2) {
        return isLeapYear(year) ? 29 : 28;
    }
    return days[month - 1];
}

int weekdayOf(int year, int month, int day) {
    static const int offsets[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    if (month < 3) {
        year--;
    }
    return (year + year / 4 - year / 100 + year / 400 + offsets[month - 1] + day) % 7;
}

Date meetupDay(int year, int month, Weekday targetWeekday, Schedule schedule) {
    int target = static_cast<int>(targetWeekday);
    int lastDay = daysInMonth(year, month);

    if (schedule == Schedule::Teenth) {
        for (int day = 13; day <= 19; day++) {
            if (weekdayOf(year, month, day) == target) {
                return {year, month, day};
            }
        }
    }

    if (schedule == Schedule::Last) {
        for (int day = lastDay; day >= lastDay - 6 && day >= 1; day--) {
            if (weekdayOf(year, month, day) == target) {
                return {year, month, day};
            }
        }
    }

    int occurrence = 0;
    switch (schedule) {
        case Schedule::First:  occurrence = 1; break;
        case Schedule::Second: occurrence = 2; break;
        case Schedule::Third:  occurrence = 3; break;
        case Schedule::Fourth: occurrence = 4; break;
        default: break;
    }

    int seen = 0;
    for (int day = 1; day <= lastDay; day++) {
        if (weekdayOf(year, month, day) == target) {
            seen++;
            if (seen == occurrence) {
                return {year, month, day};
            }
        }
    }

    return {-1, -1, -1};
}

void printDate(const string& label, const Date& d) {
    cout << label << ": ";
    if (d.year == -1) {
        cout << "invalid\n";
        return;
    }
    cout << d.year << "-";
    if (d.month < 10) cout << "0";
    cout << d.month << "-";
    if (d.day < 10) cout << "0";
    cout << d.day << "\n";
}

int main() {
    printDate("First Monday of January 2018",
              meetupDay(2018, 1, Weekday::Monday, Schedule::First));

    printDate("Third Tuesday of August 2019",
              meetupDay(2019, 8, Weekday::Tuesday, Schedule::Third));ç

    printDate("Teenth Wednesday of May 2020",
              meetupDay(2020, 5, Weekday::Wednesday, Schedule::Teenth));

    printDate("Fourth Sunday of July 2021",
              meetupDay(2021, 7, Weekday::Sunday, Schedule::Fourth));

    printDate("Last Thursday of November 2022",
              meetupDay(2022, 11, Weekday::Thursday, Schedule::Last));

    printDate("Teenth Saturday of August 1953",
              meetupDay(1953, 8, Weekday::Saturday, Schedule::Teenth));

    return 0;
}
