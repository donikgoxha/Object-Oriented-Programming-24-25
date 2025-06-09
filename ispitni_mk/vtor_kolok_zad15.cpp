#include <iostream>
#include <cstring>
using namespace std;

constexpr int MINOCENKA = 6;

class BadInputException {
public:
    static void cleanString(char *str) {
        char temp[100];
        int j = 0;
        for (int i = 0; str[i] != '\0'; i++) {
            if (isalpha(str[i])) {
                temp[j++] = str[i];
            }
        }
        temp[j] = '\0';
        strcpy(str, temp);
    }
};

class StudentKurs {
protected:
    char ime[30];
    int grade;
    bool daliUsno;
    static int MAX;
    static const int MINOCENKA = 6;

public:
    StudentKurs(char *ime, int finalenIspit) {
        strcpy(this->ime, ime);
        this->grade = finalenIspit;
        this->daliUsno = false;
    }

    static void setMAX(int max) {
        MAX = max;
    }

    virtual int ocenka() {
        return grade;
    }

    bool getDaliUsno() {
        return daliUsno;
    }

    char *getIme() {
        return ime;
    }

    friend ostream &operator<<(ostream &os, StudentKurs &sk) {
        os << sk.ime << " --- " << sk.ocenka();
        return os;
    }
};


int StudentKurs::MAX = 10;

class StudentKursUsno : public StudentKurs {
private:
    char *opisnaOcenka;

public:
    StudentKursUsno(char *ime, int finalenIspit) : StudentKurs(ime, finalenIspit) {
        daliUsno = true;
        opisnaOcenka = new char[10];
        strcpy(opisnaOcenka, "");
    }

    StudentKursUsno(const StudentKursUsno &other) : StudentKurs(other) {
        opisnaOcenka = new char[10];
        strcpy(opisnaOcenka, other.opisnaOcenka);
    }

    ~StudentKursUsno() {
        delete[] opisnaOcenka;
    }

    int ocenka() override {
        int finalOcenka = StudentKurs::ocenka();
        if (strcmp(opisnaOcenka, "odlicen") == 0) {
            finalOcenka = min(finalOcenka + 2, MAX);
        } else if (strcmp(opisnaOcenka, "dobro") == 0) {
            finalOcenka = min(finalOcenka + 1, MAX);
        } else if (strcmp(opisnaOcenka, "losho") == 0) {
            finalOcenka = max(finalOcenka - 1, 1);
        }
        return finalOcenka;
    }

    StudentKursUsno &operator+=(char *opis) {
        for (int i = 0; opis[i] != '\0'; i++) {
            if (!isalpha(opis[i])) {
                throw BadInputException();
            }
        }
        strcpy(opisnaOcenka, opis);
        return *this;
    }
};

class KursFakultet {
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;

public:
    KursFakultet(char *naziv, StudentKurs **studenti, int broj) {
        strcpy(this->naziv, naziv);
        for (int i = 0; i < broj; i++) {
            if (studenti[i]->getDaliUsno()) {
                this->studenti[i] = new StudentKursUsno(*dynamic_cast<StudentKursUsno *>(studenti[i]));
            } else {
                this->studenti[i] = new StudentKurs(*studenti[i]);
            }
        }
        this->broj = broj;
    }

    ~KursFakultet() {
        for (int i = 0; i < broj; i++) {
            delete studenti[i];
        }
    }

    void pecatiStudenti() {
        cout << "Kursot " << naziv << " go polozile:" << endl;
        for (int i = 0; i < broj; i++) {
            if (studenti[i]->ocenka() >= MINOCENKA) {
                cout << *studenti[i] << endl;
            }
        }
    }

    void postaviOpisnaOcenka(char *ime, char *opisnaOcenka) {
        for (int i = 0; i < broj; i++) {
            if (strcmp(studenti[i]->getIme(), ime) == 0 && studenti[i]->getDaliUsno()) {
                try {
                    (*dynamic_cast<StudentKursUsno *>(studenti[i])) += opisnaOcenka;
                } catch (BadInputException) {
                    cout << "Greshna opisna ocenka" << endl;
                    BadInputException::cleanString(opisnaOcenka);
                    (*dynamic_cast<StudentKursUsno *>(studenti[i])) += opisnaOcenka;
                }
                break;
            }
        }
    }
};

int main() {
    StudentKurs **niza;
    int n, m, ocenka;
    char ime[30], opisna[10];
    bool daliUsno;
    cin >> n;
    niza = new StudentKurs *[n];
    for (int i = 0; i < n; i++) {
        cin >> ime;
        cin >> ocenka;
        cin >> daliUsno;
        if (!daliUsno)
            niza[i] = new StudentKurs(ime, ocenka);
        else
            niza[i] = new StudentKursUsno(ime, ocenka);
    }

    KursFakultet programiranje("OOP", niza, n);
    for (int i = 0; i < n; i++) delete niza[i];
    delete [] niza;
    cin >> m;

    for (int i = 0; i < m; i++) {
        cin >> ime >> opisna;
        programiranje.postaviOpisnaOcenka(ime, opisna);
    }

    StudentKurs::setMAX(9);
    programiranje.pecatiStudenti();
}
