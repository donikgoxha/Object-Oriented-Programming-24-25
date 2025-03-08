// Links to the lessons
// https://finki-mk.github.io/OOP/html5/oop_av9.html
// https://bbb-lb.finki.ukim.mk/playback/presentation/2.3/740dc1184c44f2d100ce97a5038744c4cd34f22a-1651668005815
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

class RoundPeg {
protected:
    float radius;

public:
    RoundPeg(float radius = 0) {
        this->radius = radius;
    }

    virtual float getRadius() const {
        return radius;
    }

    void setRadius(float radius) {
        this->radius = radius;
    }
};

class SquarePeg {
protected:
    float side;

public:
    SquarePeg(float side) {
        this->side = side;
    }

    float getSide() const {
        return side;
    }

    void setSide(float side) {
        this->side = side;
    }
};

class SquarePegAdapter : public RoundPeg {
private:
    float side;

public:
    SquarePegAdapter(float side) : RoundPeg(side * sqrt(2) / 2) {
        this->side = side;
    }

    float getSide() const {
        return side;
    }
};

class RoundHole {
protected:
    float radius;

public:
    RoundHole(float radius) {
        this->radius = radius;
    }

    float getRadius() const {
        return radius;
    }

    void setRadius(float radius) {
        this->radius = radius;
    }

    bool fits(RoundPeg *roundPeg) {
        return roundPeg->getRadius() <= this->radius;
    }
};


int main() {
    RoundHole hole(10);
    RoundPeg *peg1 = new RoundPeg(8);
    RoundPeg *peg2 = new RoundPeg(11);
    RoundPeg *peg3 = new SquarePegAdapter(25);

    cout << hole.fits(peg1) << endl;
    cout << hole.fits(peg2) << endl;
    cout << hole.fits(peg3) << endl;

    delete peg1;
    delete peg2;
    delete peg3;

    return 0;
}
