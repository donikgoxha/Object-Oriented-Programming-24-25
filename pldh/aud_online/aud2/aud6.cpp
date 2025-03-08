#include<iostream>
#include <cstring>
using namespace std;

// Links to the lessons
// https://finki-mk.github.io/OOP/html5/oop_av4.html
// https://bbb-lb.finki.ukim.mk/playback/presentation/2.3/740dc1184c44f2d100ce97a5038744c4cd34f22a-1647438467490

class Date {
    int day;
    int month;
    int year;

public:
    //2in1 default, with arguments
    Date(int _day = 1, int _month = 1, int _year = 2000) {
        day = _day;
        month = _month;
        year = _year;
    }

    Date(const Date &d) {
        day = d.day;
        month = d.month;
        year = d.year;
    }

    ~Date() {
    }

    void print() {
        cout << day << "." << month << "." << year << endl;
    }

    int compare(Date &date) {
        if (year > date.year) {
            return 1;
        } else if (year < date.year) {
            return -1;
        } else {
            if (month > date.month) {
                return 1;
            } else if (month < date.month) {
                return -1;
            } else {
                if (day > date.day) {
                    return 1;
                } else if (day < date.day) {
                    return -1;
                } else {
                    return 0;
                }
            }
        }
    }
};

class Employee {
    char name[50];
    int salary;
    Date dateOfBirth;

public:
    Employee() {
        strcpy(name, "");
        salary = 0;
    }

    Employee(char *_name, int _salary, Date _DOB) {
        strcpy(name, _name);
        salary = _salary;
        dateOfBirth = _DOB;
    }

    Employee(const Employee &e) {
        strcpy(name, e.name);
        salary = e.salary;
        dateOfBirth = e.dateOfBirth;
    }

    ~Employee() {
    }

    void print() {
        cout << name << " " << salary << " ";
        dateOfBirth.print();
    }

    friend Employee highestPaidEmployee(Employee *employees, int n);

    friend Employee youngestEmployee(Employee *employees, int n);
};

Employee highestPaidEmployee(Employee *employees, int n) {
    Employee max = employees[0];
    for (int i = 1; i < n; i++) {
        if (employees[i].salary > max.salary) {
            max = employees[i];
        }
    }
    return max;
}


Employee youngestEmployee(Employee *employees, int n) {
    Employee max = employees[0];
    for (int i = 0; i < n; i++) {
        if (employees[i].dateOfBirth.compare(max.dateOfBirth) > 0) {
            max = employees[i];
        }
    }
    return max;
}

int main() {
    //10 pati se povikuva default konstruktorot
    Employee employees[10];

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        char name[50];
        int salary;
        int day, month, year;
        cin >> name >> salary >> day >> month >> year;
        Date dob(day, month, year);
        employees[i] = Employee(name, salary, dob);
    }

    highestPaidEmployee(employees, n).print();

    youngestEmployee(employees, n).print();

    return 0;
}
