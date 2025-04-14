/*
Define a class Temperature that holds a float variable temp. Implement for the class:
Necessary constructors
changeTemp method, which if the temp's value is positive (including 0 number) will increment it by one;
if negative it will be decrement by one getter for temp.
Do not change the main function.
*/

#include <iostream>
using namespace std;

class Temperature {
private:
    double temp;

public:
    Temperature(double temp = 0.0) {
        this->temp = temp;
    }

    void changeTemp() {
        if (temp >= 0) temp++;
        else temp--;
    }

    double get() {
        return temp;
    }
};


int main() {
    Temperature obj1;
    int n;
    cin >> n;
    int cmd;
    float k;
    for (int i = 0; i < n; i++) {
        cin >> cmd;
        switch (cmd) {
            case 1: {
                cin >> k;
                Temperature obj2(k);
                cout << obj2.get() << endl;
                break;
            }
            case 2: {
                obj1.changeTemp();
                cout << obj1.get() << endl;
                break;
            }
            case 3: {
                cin >> k;
                Temperature obj3(k);
                obj3.changeTemp();
                cout << obj3.get() << endl;
                break;
            }
            default: {
                cout << obj1.get() << endl;
                break;
            }
        }
    }
}
