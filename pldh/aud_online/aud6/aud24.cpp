// Links to the lessons
// https://finki-mk.github.io/OOP/html5/oop_av8.html

// https://bbb-lb.finki.ukim.mk/playback/presentation/2.3/740dc1184c44f2d100ce97a5038744c4cd34f22a-1651063530889
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

class Shape {
protected:
    double height;
    double base;

public:
    Shape(double height, double base) {
        this->height = height;
        this->base = base;
    }

    virtual void print() = 0;

    virtual double volume() = 0;

    double getHeight() {
        return height;
    }
};

class Cylinder : public Shape {
public:
    Cylinder(double height, double base) : Shape(height, base) {
    }

    double volume() {
        return 3.14 * base * base * height;
    }

    void print() {
        cout << "Cylinder with volume: " << volume() << endl;
    }
};

class Cone : public Shape {
public:
    Cone(double height, double base) : Shape(height, base) {
    }

    double volume() {
        return (1.0 / 3.0) * 3.14 * base * base * height;
    }

    void print() {
        cout << "Cone with volume: " << volume() << endl;
    }
};

class Cuboid : public Shape {
private:
    double width;

public:
    Cuboid(double height, double length, double width) : Shape(height, length) {
        this->width = width;
    }

    double volume() {
        return base * width * height;
    }

    void print() {
        cout << "Cuboid with volume: " << volume() << endl;
    }
};

void shapeWithLargestVolume(Shape **shapes, int n) {
    Shape *max = shapes[0];
    for (int i = 1; i < n; i++) {
        if (shapes[i]->volume() > max->volume()) {
            max = shapes[i];
        }
    }
    max->print();
}

int countShapesWithoutCircleBase(Shape **shapes, int n) {
    int counter = 0;
    for (int i = 0; i < n; i++) {
        Cuboid *castedCuboid = dynamic_cast<Cuboid *>(shapes[i]);
        if (castedCuboid->volume() == 0) {
            ++counter;
        }
    }
    return counter;
}


int main() {
    int n;
    cin >> n;
    Shape **shapes = new Shape *[n];

    for (int i = 0; i < n; i++) {
        int type; //1.cilindar, 2.konus ,3 kvadar

        double height, base, secondBase;
        cin >> type >> height >> base;
        if (type == 1) {
            //cilindar
            shapes[i] = new Cylinder(height, base);
        } else if (type == 2) {
            //kon
            shapes[i] = new Cone(height, base);
        } else {
            //kuboid
            cin >> secondBase;
            shapes[i] = new Cuboid(height, base, secondBase);
        }
        //shapes[i]->print(); //da se komentira posle
    }

    shapeWithLargestVolume(shapes, n);
    cout << endl << "Number of shapes without a circle base is: " << countShapesWithoutCircleBase(shapes, n);
}
