#include <iostream>
using namespace std;

class Temperature {
    float temperature;

public:
    Temperature(float temperature = 0) {
        this->temperature = temperature;
    }

    void set(const float temperature) {
        this->temperature = temperature;
    }

    void changeTemp() {
        if (temperature < 0) {
            temperature++;
        } else {
            temperature--;
        }
    }

    void print() {
        cout << temperature << endl;
    }
};

int main() {
    Temperature obj;
    int n;
    cin >> n;
    int cmd;
    float k;
    for (int i = 0; i < n; i++) {
        cin >> cmd;
        switch (cmd) {
            case 1: {
                cin >> k;
                obj.set(k);
                obj.print();
                break;
            }
            case 2: {
                obj.changeTemp();
                obj.print();
                break;
            }
            case 3: {
                Temperature obj3;
                cin >> k;
                obj3.set(k);
                obj3.changeTemp();
                obj3.print();
                break;
            }
            default: {
                obj.print();
                break;
            }
        }
    }
}
