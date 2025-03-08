#include <iostream>
#include <cstring>
#include <cctype>
#include <cmath>
using namespace std;

class Triagolnik {
private:
    int a, b, c;

public:
    Triagolnik() = default;

    Triagolnik(int aa, int bb, int cc) {
        a = aa;
        b = bb;
        c = cc;
    }

    int perimeter() {
        return a + b + c;
    }

    double area() {
        double s = perimeter() / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }

    ~Triagolnik() = default;
};

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    Triagolnik t(a, b, c);
    cout << t.perimeter() << endl;
    cout << t.area() << endl;
    return 0;
}
