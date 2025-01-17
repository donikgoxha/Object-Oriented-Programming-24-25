#include <iostream>
#include <cmath>
using namespace std;

//links to the lessons
//https://finki-mk.github.io/OOP/html5/oop_av3.html
//https://bbb-lb.finki.ukim.mk/playback/presentation/2.3/9111e1b452b190f16e6faecde632b78dd975ea9c-1615368406409?meetingId=9111e1b452b190f16e6faecde632b78dd975ea9c-1615368406409
//https://bbb-lb.finki.ukim.mk/playback/presentation/2.3/9111e1b452b190f16e6faecde632b78dd975ea9c-1615371630474?meetingId=9111e1b452b190f16e6faecde632b78dd975ea9c-1615371630474


//zadaca1
class Triangle {
private:
    int a, b, c;

public:
    //constructor 2in1
    Triangle(int aa = 5, int bb = 4, int cc = 3) {
        cout << "Triangle constructor" << endl;
        a = aa;
        b = bb;
        c = cc;
    }

    ~Triangle() {
        cout << "Triangle destructor" << endl;
    }

    int perimeter() {
        return a + b + c;
    }

    double area() {
        float s = (a + b + c) / 2.0;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }

    void print() {
        cout << "Triangle with sides: " << a << " " << b << " " << c << endl;
        cout << "Perimeter: " << perimeter() << endl;
        cout << "Area: " << area() << endl;
    }
};

int main() {
    Triangle t;
    t.print();
    Triangle t1(6, 6, 6);
    t1.print();
    Triangle t2(15, 9, 12);
    t2.print();
    return 0;
}
