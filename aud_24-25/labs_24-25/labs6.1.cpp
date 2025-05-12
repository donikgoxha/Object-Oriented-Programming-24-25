#include <iostream>
#include <cstring>
using namespace std;

class Kvadrat {
protected:
    double a;

public:
    Kvadrat(double a = 0.0) {
        this->a = a;
    }

    Kvadrat(const Kvadrat &other) {
        this->a = other.a;
    }

    virtual double perimetar() const {
        return 4 * a;
    }

    virtual double plostina() const {
        return a * a;
    }

    virtual void pecati() const {
        cout << "Kvadrat so dolzina a=" << a << " ima plostina P=" << plostina() << " i perimetar L=" << perimetar() <<
                endl;
    }

    double getA() {
        return a;
    }
};

class Pravoagolnik : public Kvadrat {
private:
    double x;
    double y;

public:
    Pravoagolnik(const Kvadrat &a = Kvadrat(), double x = 0.0, double y = 0.0) : Kvadrat(a) {
        this->x = x;
        this->y = y;
    }

    Pravoagolnik(const Pravoagolnik &other) : Kvadrat(other) {
        this->x = other.x;
        this->y = other.y;
    }

    double perimetar() const override {
        if (x == y) {
            return 4 * (a + x);
        }
        return 2 * (a + x) + 2 * (a + y);
    }

    double plostina() const override {
        if (x == y) {
            return (a + x) * (a + x);
        }
        return (a + x) * (a + y);
    }

    void pecati() const override {
        if (x == y) {
            double novaStrana = a + x;
            cout << "Kvadrat so dolzina a=" << novaStrana
                    << " ima plostina P=" << novaStrana * novaStrana
                    << " i perimetar L=" << 4 * novaStrana << endl;
        } else {
            cout << "Pravoagolnik so strani: " << a + x << " i " << a + y
                    << " ima plostina P=" << plostina()
                    << " i perimetar L=" << perimetar() << endl;
        }
    }
};

int main() {
    int n;
    double a, x, y;
    Kvadrat *kvadrati;
    Pravoagolnik *pravoagolnici;

    cin >> n;

    kvadrati = new Kvadrat [n];
    pravoagolnici = new Pravoagolnik [n];

    for (int i = 0; i < n; i++) {
        cin >> a;

        kvadrati[i] = Kvadrat(a);
    }

    for (int i = 0; i < n; i++) {
        cin >> x >> y;

        pravoagolnici[i] = Pravoagolnik(kvadrati[i], x, y);
    }

    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "===Testiranje na klasata Kvadrat===" << endl;
        for (int i = 0; i < n; i++)
            kvadrati[i].pecati();
    } else {
        cout << "===Testiranje na klasata Pravoagolnik===" << endl;
        for (int i = 0; i < n; i++)
            pravoagolnici[i].pecati();
    }
}
