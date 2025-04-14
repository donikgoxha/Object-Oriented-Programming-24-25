#include<iostream>
#include <cstring>
using namespace std;

class Book {
    string name;
    int pages;

public:
    Book(string name = "TEST_BOOK", int pages = 0) {
        this->name = name;
        this->pages = pages;
    }

    void readPages(int p) {
        if (p > 200) return;
        pages += p;
        if (pages > 200) pages = 200;
    }

    void print() {
        cout << name << " - " << pages << "/200" << " - ";
        if (pages < 100) cout << "IN PROGRESS" << endl;
        else if (pages < 200) cout << "ALMOST DONE" << endl;
        else cout << "FINISHED" << endl;
    }
};


int main() {
    string command;
    Book s;
    string name;
    int pagesRead;

    while (cin >> command) {
        if (command == "constructor1") {
            cin >> name >> pagesRead;
            s = Book(name, pagesRead);
        } else if (command == "constructor2") {
            cin >> name;
            s = Book(name);
        } else if (command == "readPages") {
            cin >> pagesRead;
            s.readPages(pagesRead);
        } else if (command == "print") {
            s.print();
        }
    }


    return 0;
}
