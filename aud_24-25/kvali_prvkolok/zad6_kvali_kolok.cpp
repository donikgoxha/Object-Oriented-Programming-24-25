#include <iostream>
using namespace std;

class Letter {
    char ch;

public:
    void set(char c) {
        ch = c;
    }
    Letter () {
        ch = 'a';
    }
    Letter (char c) {
        ch = c;
    }
    void lowerLetter() {
        if (isalpha(ch)) {
            ch = tolower(ch);
        } else {
            cout << "Character is not a letter" << endl;
        }
    }
    void print() {
        cout << ch << endl;
    }
};

int main() {
    Letter obj;
    int n;
    cin >> n;
    int cmd;
    char k;
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
                obj.lowerLetter();
                obj.print();
                break;
            }
            case 3: {
                cin >> k;
                Letter obj2;
                obj2.set(k);
                obj2.lowerLetter();
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
