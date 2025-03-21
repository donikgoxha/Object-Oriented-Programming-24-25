#include <iostream>
using namespace std;

class Number {
    int number;

public:
    Number() {
        number = 0;
    }

    void decreaseNumber(int value) {
        if (number - value < 0) {
            number = 0;
            cout << "Difference is less than 0" << endl;
        } else {
            number -= value;
        }
    }

    void print() const {
        cout << number << endl;
    }

    void set(int n) {
        number = n;
    }
};


int main() {
    Number obj;
    int n;
    cin >> n;
    int cmd;
    int k;
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
                cin >> k;
                obj.decreaseNumber(k);
                obj.print();
                break;
            }
            case 3: {
                Number obj2;
                cin >> k;
                obj2.set(k);
                cin >> k;
                obj2.decreaseNumber(k);
                obj2.print();
                break;
            }
            default: {
                obj.print();
                break;
            }
        }
    }
}
