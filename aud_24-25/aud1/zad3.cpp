#include <iostream>
#include <cstring>
using namespace std;

struct Zitel {
    char ime[30];
    char prezime[30];
    char partija[10];
    bool dali_pres;
};

struct Grad {
    char ime[30];
    Zitel ziteli[100];
    int br_ziteli;
    bool glaven_grad;
};

struct Drzava {
    char ime[30];
    Grad gradovi[100];
    int br_gradovi;
};

int main() {
    Drzava niza[100];
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> niza[i].ime >> niza[i].br_gradovi;

        for (int j = 0; j < niza[i].br_gradovi; j++) {
            cin >> niza[i].gradovi[j].ime >> niza[i].gradovi[j].br_ziteli >> niza[i].gradovi[j].glaven_grad;

            for (int k = 0; k < niza[i].gradovi[j].br_ziteli; k++) {
                cin >> niza[i].gradovi[j].ziteli[k].ime
                        >> niza[i].gradovi[j].ziteli[k].prezime
                        >> niza[i].gradovi[j].ziteli[k].partija
                        >> niza[i].gradovi[j].ziteli[k].dali_pres;
            }
        }
    }

    return 0;
}
