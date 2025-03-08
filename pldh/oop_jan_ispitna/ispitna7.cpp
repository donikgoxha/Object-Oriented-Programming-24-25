#include <iostream>
#include <cstring>
using namespace std;

//zad9 ispitni/kolokviumski

class Exception {
public:
    char *message() {
        return "Ne moze da se vnese dadeniot trud";
    }
};

class Trud {
private:
    char type;
    int year;

public:
    Trud(char type = 'C', int year = 2000) {
        this->type = type;
        this->year = year;
    }

    char getType() {
        return this->type;
    }

    int getYear() const {
        return this->year;
    }

    friend istream &operator>>(istream &is, Trud &t) {
        return is >> t.type >> t.year;
    }
};

class Student {
protected:
    char name[30];
    int indeks;
    int enrollmentYear;
    int *grades;
    int numGrades;

public:
    Student(const char *name = "", int indeks = 0, int enrollmentYear = 0, int *grades = nullptr, int numGrades = 0) {
        strcpy(this->name, name);
        this->indeks = indeks;
        this->enrollmentYear = enrollmentYear;
        this->numGrades = numGrades;
        this->grades = new int[this->numGrades];
        for (int i = 0; i < this->numGrades; i++) {
            this->grades[i] = grades[i];
        }
    }

    Student(const Student &s) {
        strcpy(this->name, s.name);
        this->indeks = s.indeks;
        this->enrollmentYear = s.enrollmentYear;
        this->numGrades = s.numGrades;
        this->grades = new int[this->numGrades];
        for (int i = 0; i < this->numGrades; i++) {
            this->grades[i] = s.grades[i];
        }
    }

    virtual ~Student() {
        delete[] grades;
    }

    virtual float rang() const {
        if (numGrades == 0) return 0;

        float sum = 0;
        for (int i = 0; i < numGrades; i++) {
            sum += grades[i];
        }
        return sum / numGrades;
    }

    friend ostream &operator<<(ostream &out, const Student &s) {
        return out << s.indeks << " " << s.name << " " << s.enrollmentYear << " " << s.rang() << endl;
    }

    int getIndex() const { return indeks; }
    int getEnrollmentYear() const { return enrollmentYear; }
};


class PhDStudent : public Student {
private:
    Trud *papers;
    int numPapers;
    static int confPoints;
    static int journalPoints;

public:
    PhDStudent(const char *n = "", int idx = 0, int year = 0, int *g = nullptr, int num = 0,
               Trud *p = nullptr, int np = 0) : Student(n, idx, year, g, num) {
        numPapers = np;
        papers = new Trud[numPapers];
        if (p != nullptr) {
            for (int i = 0; i < numPapers; i++) {
                if (p[i].getYear() < enrollmentYear) {
                    delete[] papers;
                    throw Exception();
                }
                papers[i] = p[i];
            }
        }
    }

    PhDStudent(const PhDStudent &phd) : Student(phd) {
        numPapers = phd.numPapers;
        papers = new Trud[numPapers];
        for (int i = 0; i < numPapers; i++) {
            papers[i] = phd.papers[i];
        }
    }

    float rang() const override {
        float baseRang = Student::rang();
        float paperPoints = 0;
        for (int i = 0; i < numPapers; i++) {
            if (papers[i].getType() == 'C' || papers[i].getType() == 'c') {
                paperPoints += confPoints;
            } else if (papers[i].getType() == 'J' || papers[i].getType() == 'j') {
                paperPoints += journalPoints;
            }
        }
        return baseRang + paperPoints;
    }

    PhDStudent &operator+=(const Trud &t) {
        if (t.getYear() < enrollmentYear) {
            throw Exception();
        }
        Trud *temp = new Trud[numPapers + 1];
        for (int i = 0; i < numPapers; i++) {
            temp[i] = papers[i];
        }
        temp[numPapers++] = t;
        delete[] papers;
        papers = temp;
        return *this;
    }

    static void setPoints(int conf, int journal) {
        confPoints = conf;
        journalPoints = journal;
    }

    virtual ~PhDStudent() {
        delete []papers;
    }
};

int PhDStudent::confPoints = 1;
int PhDStudent::journalPoints = 3;

int main() {
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++) {
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        bool found = false;
        try {
            for (int i = 0; i < m; i++) {
                PhDStudent *phd = dynamic_cast<PhDStudent *>(niza[i]);
                if (phd != nullptr && phd->getIndex() == indeks) {
                    *phd += t;
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Ne postoi PhD student so indeks " << indeks << endl;
            }
        } catch (Exception &e) {
            cout << e.message() << endl;
        }


        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        bool found = false;
        try {
            for (int i = 0; i < m; i++) {
                PhDStudent *phd = dynamic_cast<PhDStudent *>(niza[i]);
                if (phd != nullptr && phd->getIndex() == indeks) {
                    *phd += t;
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Ne postoi PhD student so indeks " << indeks << endl;
            }
        } catch (Exception &e) {
            cout << e.message() << endl;
        }


        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++) {
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        //PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        try {
            PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
            cout << phd;
        } catch (Exception &e) {
            cout << e.message() << endl;
        }
        //cout << phd;
    }
    if (testCase == 5) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        try {
            for (int i = 0; i < m; i++) {
                PhDStudent *phd = dynamic_cast<PhDStudent *>(niza[i]);
                if (phd != nullptr && phd->getIndex() == indeks) {
                    *phd += t;
                    break;
                }
            }
        } catch (Exception &e) {
            cout << e.message() << endl;
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6) {
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;

        //postavete gi soodvetnite vrednosti za statickite promenlivi
        PhDStudent::setPoints(conf, journal);


        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }

    return 0;
}
