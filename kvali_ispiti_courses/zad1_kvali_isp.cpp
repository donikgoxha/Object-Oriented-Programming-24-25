#include<iostream>
#include <cstring>
using namespace std;

class Student {
    string index;
    int points;

public:
    Student(string index = "NO_ID", int points = 0) {
        this->index = index;
        this->points = points;
    }


    void addPoints(int p) {
        if (p > 100)
            return;
        points += p;
        if (points > 100)
            points = 100;
    }

    void print() {
        cout << index << " - " << points << " ";
        if (points < 50) {
            cout << "FAILED";
        } else if (points < 90) {
            cout << "PASSED";
        } else {
            cout << "BEST";
        }
        cout << endl;
    }
};


int main() {
    string command;
    Student s;
    string id;
    int points;

    while (cin >> command) {
        if (command == "constructor1") {
            cin >> id >> points;
            s = Student(id, points);
        } else if (command == "constructor2") {
            cin >> id;
            s = Student(id);
        } else if (command == "addPoints") {
            cin >> points;
            s.addPoints(points);
        } else if (command == "print") {
            s.print();
        }
    }
    return 0;
}
