#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

enum pozicija { vraboten, direktor, shef };

class Vraboten {
private:
    char ime[30];
    int plata;
    pozicija p;

public:
    Vraboten() = default;

    Vraboten(const char *imee, int plataa, int poz1) {
        strcpy(ime, imee);
        plata = plataa;
        p = (pozicija) poz1;
    }

    void pechatenje() {
        cout << ime << " " << plata << " " << endl;
        if (p == 0) {
            cout << "Vraboten" << endl;
        } else if (p == 1) {
            cout << "Direktor" << endl;
        } else {
            cout << "Shef" << endl;
        }
    }

    void set_ime(char *imee) {
        strcpy(imee, ime);
    }

    void set_plataa(int plataa) {
        plata = plataa;
    }

    void set_pozicija(int poz) {
        p = (pozicija) poz;
    }

    void set_all(char *imee, int plataa, int poz) {
        strcpy(imee, ime);
        plata = plataa;
        p = (pozicija) poz;
    }

    int get_plata() {
        return plata;
    }

    ~Vraboten() = default;
};

int main() {
    int n;
    cin >> n;
    Vraboten v[100];
    char ime[30];
    int plata, poz;
    //chitanje na niza na objektite
    for (int i = 0; i < n; i++) {
        cin >> ime >> plata >> poz;
        //prv nachin
        v[i].set_all(ime, plata, poz);
        //vtor nachin
        // v[i].set_ime(ime);
        // v[i].set_plataa(plata);
        // v[i].set_pozicija(poz);
        //tret nachin
        // Vraboten tmp(ime, plata, poz);
        // v[i] = tmp;
    }
    //sortiranje
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (v[j].get_plata() < v[j + 1].get_plata()) {
                //swap(v[j], v[j + 1]);
                Vraboten tmp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = tmp;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        v[i].pechatenje();
    }

    return 0;
}
