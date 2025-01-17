#include <iostream>
#include <cstring>
using namespace std;

//links to the lessons
//https://finki-mk.github.io/OOP/html5/oop_av4.html
//https://bbb-lb.finki.ukim.mk/playback/presentation/2.3/740dc1184c44f2d100ce97a5038744c4cd34f22a-1647438467490

class Boy {
private:
    char name[50];
    int age;

public:
    //default constructor
    Boy() {
        strcpy(name, "YYYYY");
        age = 18;
    }

    //constructor with args
    Boy(char *nname, int aage) {
        strcpy(name, nname);
        age = aage;
    }

    //copy constructor
    Boy(const Boy &b) {
        strcpy(name, b.name);
        age = b.age;
    }

    ~Boy() {
    }

    void print() {
        cout << "Boy: " << name;
        cout << " Age: " << age << endl;
    }
};

class Girl {
private:
    char name[50];
    int age;

public:
    //default constructor
    Girl() {
        strcpy(name, "XXXXX");
        age = 18;
    }

    //constructor with args
    Girl(char *nname, int aage) {
        strcpy(name, nname);
        age = aage;
    }

    //copy constructor
    Girl(const Girl &g) {
        strcpy(name, g.name);
        age = g.age;
    }

    ~Girl() {
    }

    void print() {
        cout << "Girl: " << name;
        cout << " Age: " << age << endl;
    }
};

class Date {
private:
    Boy boy;
    Girl girl;

public:
    //default constructor
    Date() {
    }

    //constructor with args
    Date(Boy bboy, Girl ggirl) {
        boy = bboy;
        girl = ggirl;
    }

    //copy constructor
    Date(const Date &d) {
        boy = d.boy;
        girl = d.girl;
    }

    //destructor
    ~Date() {
    }

    void print() {
        cout << "Date between: ";
        boy.print();
        cout << " and ";
        girl.print();
    }
};

int main() {
    Boy b;
    //b.print();
    Girl g;
    //g.print();

    Date date(b, g);
    date.print();

    //usage of default constructor in arrays
    // Boy boys[100];
    // for (int i = 0; i < 100; i++) {
    //     boys[i].print();
    // }
    // Girl girls[100];
    // for (int i = 0; i < 100; i++) {
    //     girls[i].print();
    // }

    return 0;
}
