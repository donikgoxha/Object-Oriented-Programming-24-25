#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

class Boy {
    char fullName[50];
    int age;

public:
    Boy(const char *_fullName = "No name", int _age = 18) {
        strcpy(fullName, _fullName);
        age = _age;
    }

    ~Boy() {
    }

    void print() {
        cout << "Boy: " << fullName << " Age: " << age << endl;
    }

    int getAge() const {
        return age;
    }
};

class Girl {
    char fullName[50];
    int age;

public:
    Girl(const char *_fullName = "No name", int _age = 18) {
        strcpy(fullName, _fullName);
        age = _age;
    }

    ~Girl() {
    }

    void print() {
        cout << "Girl: " << fullName << " Age: " << age << endl;
    }

    int getAge() const {
        return age;
    }
};

class Date {
private:
    Boy boy;
    Girl girl;
    int counter;

public:
    Date(const Boy &boy = Boy(), const Girl &girl = Girl(), int counter = 1)
        : boy(boy),
          girl(girl),
          counter(counter) {
    }

    void print() {
        cout << "Date between: " << endl;
        boy.print();
        cout << "&" << endl;
        girl.print();
        cout << "Count of date: " << counter << endl;
        if (isMatch()) {
            cout << "Good match! :)" << endl;
        } else {
            cout << "Not a match! :(" << endl;
        }
    }

    bool isMatch() {
        int difference = abs(boy.getAge() - girl.getAge());
        return difference <= 5 || counter >= 3;
    }
};

int main() {
    Boy boy;
    //boy.print();

    Boy boy2("Donik", 20);
    //boy2.print();

    Girl girl;
    //girl.print();

    Girl girl2("Ana", 23);
    //girl2.print();

    // Date date;
    // date.print();

    Date date2(boy2, girl2, 5);
    date2.print();

    return 0;
}
