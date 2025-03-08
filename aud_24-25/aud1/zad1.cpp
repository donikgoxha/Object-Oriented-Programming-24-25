#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

struct Date {
    int day;
    int month;
    int year;

    void print() {
        cout << day << "." << month << "." << year;
    }
};

void read(Date &d2) {
    cin >> d2.day >> d2.month >> d2.year;
}

int compare(Date d1, Date d2) {
    if (d1.year > d2.year) {
        return -1;
    } else if (d1.year < d2.year) {
        return 1;
    } else if (d1.month > d2.month) {
        return -1;
    } else if (d1.month < d2.month) {
        return 1;
    } else if (d1.day > d2.day) {
        return -1;
    } else if (d1.day < d2.day) {
        return 1;
    } else return 0;
}

int diff_days(Date d1, Date d2) {
    if (compare(d1, d2) == 1) {
        Date tmp = d1;
        d1 = d2;
        d2 = tmp;
    }
    return (d1.year - d2.year) * 365 + (d1.month - d2.month) * 30 + (d1.day - d2.day);
}

int main() {
    Date d1, d2;
    cin >> d1.day >> d1.month >> d1.year;
    d1.print();
    read(d2);
    d2.print();
    cout << diff_days(d1, d2) << endl;
    return 0;
}
