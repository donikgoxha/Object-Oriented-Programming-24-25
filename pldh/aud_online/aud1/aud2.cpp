#include <iostream>
#include <cstring>
using namespace std;

//links to the lessons (makedonski)
//https://finki-mk.github.io/OOP/html5/oop_av3.html
//https://bbb-lb.finki.ukim.mk/playback/presentation/2.3/9111e1b452b190f16e6faecde632b78dd975ea9c-1615368406409?meetingId=9111e1b452b190f16e6faecde632b78dd975ea9c-1615368406409
//https://bbb-lb.finki.ukim.mk/playback/presentation/2.3/9111e1b452b190f16e6faecde632b78dd975ea9c-1615371630474?meetingId=9111e1b452b190f16e6faecde632b78dd975ea9c-1615371630474

//zadaca 2
enum Type {
    employee, //0
    manager, //1
    owner //2
};

class Employee {
private:
    char name[50];
    Type type;
    int salary;

public:
    Employee(char *nname = "Donik", int ssalary = 50000, Type ttype = employee) {
        strcpy(name, nname);
        salary = ssalary;
        type = ttype;
    }

    ~Employee() {
    }

    void print() {
        cout << "Employee name: " << name << endl;
        cout << "Salary: " << salary << endl;
        switch (type) {
            case employee:
                cout << "Basic" << endl;
                break;
            case manager:
                cout << "Manager" << endl;
                break;
            default:
                cout << "Owner" << endl;
        }
    }

    void setName(char *nname) {
        strcpy(name, nname);
    }

    void setSalary(int ssalary) {
        salary = ssalary;
    }

    void setType(Type ttype) {
        type = ttype;
    }

    int compareTo(Employee other) {
        if (salary < other.salary) {
            return -1;
        } else if (salary > other.salary) {
            return 1;
        } else {
            return 0;
        }
    }

    int getSalary() {
        return salary;
    }
};

int main() {
    int n;
    cin >> n;
    Employee employee[50];
    char name[50];
    int salary;
    int type;
    for (int i = 0; i < n; i++) {
        cin >> name >> salary >> type; //Donik 15000 0
        //employee[i] = Employee(name, salary, (Type) type);
        employee[i].setName(name);
        employee[i].setSalary(salary);
        employee[i].setType((Type) type);
    }
    //to do sorting employees by salary
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            //employee[j].getSalary() < employee[j + 1].getSalary()
            if (employee[j].compareTo(employee[j + 1]) == -1) {
                swap(employee[j], employee[j + 1]);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        employee[i].print();
    }
    return 0;
}
