#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

class Student {
protected:
    string id;
    double average;

public:
    Student(const string &id, double average) {
        this->id = id;
        this->average = average;
    }

    void print() {
        cout << "ID: " << id << " " << average << endl;
    }
};

class LabStaff : public Student {
protected:
    int slotsWeekly;
    int courses;

public:
    LabStaff(const string &id, double average, int SlotsWeekly, int courses) : Student(id, average) {
        this->slotsWeekly = slotsWeekly;
        this->courses = courses;
    }

    void print() {

    }
};

int main() {
    return 0;
}
