#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

struct Student {
    char ime[30];
    char prezime[30];
    int indeks;
    int poeni;

    void print() {
        cout << prezime << " " << ime << " " << indeks << " " << poeni << endl;
    }
};

int main() {
    int n;
    cin >> n;
    Student students[100];
    for (int i = 0; i < n; i++) {
        cin >> students[i].ime >> students[i].prezime >> students[i].indeks >> students[i].poeni;
        if (students[i].ime[0] >= 'a' && students[i].ime[0] <= 'z') {
            students[i].ime[0] -= ('a' - 'A');
        }
        if (students[i].prezime[0] >= 'a' && students[i].prezime[0] <= 'z') {
            students[i].prezime[0] -= ('a' - 'A');
        }
        int poen;
        students[i].poeni = 0;
        for (int j = 0; j < 4; j++) {
            cin >> poen;
            students[i].poeni += poen;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (students[j].poeni < students[j + 1].poeni) {
                swap(students[j], students[j + 1]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        students[i].print();
    }
    return 0;
}
