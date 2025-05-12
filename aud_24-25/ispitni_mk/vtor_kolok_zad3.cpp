#include <iostream>
#include <cstring>
using namespace std;

class NoCourseException {
private:
    int indeks;
public:
    NoCourseException(int indeks) {
        this->indeks = indeks;
    }
    void message() {
        cout << "Demonstratorot so indeks " << indeks << " ne drzi laboratoriski vezbi" << endl;
    }
};

class Kurs {
private:
    char ime[20];
    int krediti;
public:
    Kurs() {
        strcpy(ime, "");
        krediti = 0;
    }
    Kurs(const char *ime, int krediti) {
        strcpy(this->ime, ime);
        this->krediti = krediti;
    }
    void setIme(const char *ime) {
        strcpy(this->ime, ime);
    }
    char *getIme() {
        return ime;
    }
    void setKrediti(int krediti) {
        this->krediti = krediti;
    }
    int getKrediti() {
        return krediti;
    }
};

class Student {
protected:
    int indeks;
    int *oceni;
    int brojOceni;
public:
    Student(int indeks = 0, int *oceni = nullptr, int brojOceni = 0) {
        this->indeks = indeks;
        this->brojOceni = brojOceni;
        if(brojOceni > 0) {
            this->oceni = new int[brojOceni];
            if(oceni != nullptr) {
                for(int i = 0; i < brojOceni; i++) {
                    this->oceni[i] = oceni[i];
                }
            }
        } else {
            this->oceni = nullptr;
        }
    }
    virtual ~Student() {
        delete [] oceni;
    }
    virtual int getBodovi() {
        if(brojOceni == 0 || oceni == nullptr) return 0;
        int brojPolozeni = 0;
        for(int i = 0; i < brojOceni; i++) {
            if(oceni[i] > 5) {
                brojPolozeni++;
            }
        }
        return (brojPolozeni * 100) / brojOceni;
    }
    virtual void pecati() {
        cout << indeks;
    }
    int getIndeks() {
        return indeks;
    }
};

class Predavach {
protected:
    char *ime;
    Kurs *kursevi;
    int brojKursevi;
public:
    Predavach(const char *ime = "", Kurs *kursevi = nullptr, int brojKursevi = 0) {
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
        this->brojKursevi = brojKursevi;
        if(brojKursevi > 0) {
            this->kursevi = new Kurs[brojKursevi];
            if(kursevi != nullptr) {
                for(int i = 0; i < brojKursevi; i++) {
                    this->kursevi[i] = kursevi[i];
                }
            }
        } else {
            this->kursevi = nullptr;
        }
    }
    ~Predavach() {
        delete [] ime;
        delete [] kursevi;
    }
    char *getIme() {
        return ime;
    }
    Kurs *getKursevi() {
        return kursevi;
    }
    int getBrojKursevi() {
        return brojKursevi;
    }
};

class Demonstrator : public Student, public Predavach {
private:
    int brojCasovi;
public:
    Demonstrator(int indeks = 0, int *oceni = nullptr, int brojOceni = 0,
                const char *ime = "", Kurs *kursevi = nullptr, int brojKursevi = 0,
                int brojCasovi = 0) : Student(indeks, oceni, brojOceni),
                                    Predavach(ime, kursevi, brojKursevi) {
        this->brojCasovi = brojCasovi;
    }
    int getBodovi() override {
        int bodovi = Student::getBodovi();
        if(brojKursevi == 0) {
            throw NoCourseException(indeks);
        }
        bodovi += (20 * brojCasovi) / brojKursevi;
        return bodovi;
    }
    void pecati() override {
        if(brojKursevi == 0) {
            cout << indeks;
        } else {
            cout << indeks << ": " << ime << " (";
            for(int i = 0; i < brojKursevi; i++) {
                cout << kursevi[i].getIme() << " " << kursevi[i].getKrediti() << "ECTS";
                if(i < brojKursevi - 1) {
                    cout << ", ";
                }
            }
            cout << ")";
        }
    }
    bool drziKurs(const char *kurs) {
        if(kursevi == nullptr) return false;
        for(int i = 0; i < brojKursevi; i++) {
            if(strcmp(kursevi[i].getIme(), kurs) == 0) {
                return true;
            }
        }
        return false;
    }
};

Student& vratiNajdobroRangiran(Student **studenti, int n) {
    int maxBodovi = -1;
    int maxIndex = 0;
    
    for(int i = 0; i < n; i++) {
        int bodovi = 0;
        try {
            bodovi = studenti[i]->getBodovi();
        } catch(NoCourseException &e) {
            bodovi = 0;
        }
        
        if(bodovi > maxBodovi) {
            maxBodovi = bodovi;
            maxIndex = i;
        }
    }
    
    return *studenti[maxIndex];
}

void pecatiDemonstratoriKurs(const char *kurs, Student **studenti, int n) {
    for(int i = 0; i < n; i++) {
        Demonstrator *d = dynamic_cast<Demonstrator*>(studenti[i]);
        if(d != nullptr && d->drziKurs(kurs)) {
            d->pecati();
        }
    }
}

int main() {
    int indeks, brojOcenki;
    cin >> indeks >> brojOcenki;
    
    int *ocenki = nullptr;
    if(brojOcenki > 0) {
        ocenki = new int[brojOcenki];
        for(int i = 0; i < brojOcenki; i++) {
            cin >> ocenki[i];
        }
    }
    
    char imeIPrezime[50] = "";
    int brojKursevi = 0;
    cin >> imeIPrezime >> brojKursevi;
    
    Kurs *kursevi = nullptr;
    if(brojKursevi > 0) {
        kursevi = new Kurs[brojKursevi];
        for(int i = 0; i < brojKursevi; i++) {
            char ime[20];
            int ocenka;
            cin >> ime >> ocenka;
            kursevi[i] = Kurs(ime, ocenka);
        }
    }
    
    Student *s = new Demonstrator(indeks, ocenki, brojOcenki, imeIPrezime, kursevi, brojKursevi, 0);
    s->pecati();
    cout << endl;
    try {
        cout << s->getBodovi() << endl;
    } catch(NoCourseException &e) {
        e.message();
    }
    
    delete s;
    delete [] ocenki;
    delete [] kursevi;
    
    
    return 0;
}
