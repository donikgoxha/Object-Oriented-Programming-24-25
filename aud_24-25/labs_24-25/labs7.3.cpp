// Да се дефинира класа Scientist за која ќе се чуваат:
//
// динамички алоцирана низа од карактери за името на научникот
//
// низа од максимум 50 карактери за институцијата каде што работи
//
// вкупен број објавени трудови (int)
//
// вкупен број цитати од тие трудови (int)
//
// вкупен број години истражувачка работа (int)
//
// За потребите на класата да се дефинираат:
//
// default конструктор и конструктор со аргументи
//
// copy constructor и оператор =
//
// деструктор
//
// метод impact() кој го враќа научниот импакт според формулата: (цитати * 0.5 + трудови * 0.3 + години * 0.2)
//
// метод print() кој печати:
//
// Name: <име> - Institution: <институција>
// Publications: <трудови>
// Citations: <цитати>
// Experience: <години>
// Impact Score: <импакт>
//
// Input	Result
// 1
// 2
// Alice ResearchLab 10 100 5
// Bob InstituteA 20 200 10
// SCIENTISTS:
// =====================================
// Alice - ResearchLab
// Publications: 10
// Citations: 100
// Experience (Years): 5
// Impact Score: 54
// -------------------------
// Bob - InstituteA
// Publications: 20
// Citations: 200
// Experience (Years): 10
// Impact Score: 108
// -------------------------
// Testing Copy Constructor:
// Alice - ResearchLab
// Publications: 10
// Citations: 100
// Experience (Years): 5
// Impact Score: 54
// Testing Assignment Operator:
// Bob - InstituteA
// Publications: 20
// Citations: 200
// Experience (Years): 10
// Impact Score: 108

#include <iostream>
#include <cstring>
using namespace std;

class Scientist {
private:
    char *name;
    char institution[50];
    int publications;
    int citations;
    int year;

    void copy(const Scientist &s) {
        this->name = new char [strlen(s.name) + 1];
        strcpy(this->name, s.name);
        strcpy(this->institution, s.institution);
        this->publications = s.publications;
        this->citations = s.citations;
        this->year = s.year;
    }

public:
    Scientist(const char *name = "", const char *institution = "", int publications = 0, int citations = 0,
              int year = 0) {
        this->name = new char [strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->institution, institution);
        this->publications = publications;
        this->citations = citations;
        this->year = year;
    }

    Scientist(const Scientist &s) {
        copy(s);
    }

    Scientist &operator=(const Scientist &s) {
        if (this != &s) {
            delete [] name;
            copy(s);
        }
        return *this;
    }

    virtual ~Scientist() {
        delete [] name;
    }

    virtual double impact() const {
        return ((citations * 0.5) + (publications * 0.3) + (year * 0.2));
    }

    virtual void print() const {
        cout << name << " - Institution: " << institution << endl;
        cout << "Publications: " << publications << endl;
        cout << "Citations: " << citations << endl;
        cout << "Experience: " << year << endl;
        cout << "Impact: " << impact() << endl;
    }
};

class ResearchScientist : public Scientist {
private:
    int Q1Publications;
    int EUProjects;
    double funding;

public:
    ResearchScientist(const char *name = "", const char *institution = "", int publications = 0,
                      int citations = 0, int year = 0, int Q1Publications = 0,
                      int EUProjects = 0, double funding = 0.0)
        : Scientist(name, institution, publications, citations, year) {
        this->Q1Publications = Q1Publications;
        this->EUProjects = EUProjects;
        this->funding = funding;
    }

    ResearchScientist(const ResearchScientist &rs)
        : Scientist(rs) {
        this->Q1Publications = rs.Q1Publications;
        this->EUProjects = rs.EUProjects;
        this->funding = rs.funding;
    }

    ResearchScientist &operator=(const ResearchScientist &rs) {
        if (this != &rs) {
            Scientist::operator=(rs);
            this->Q1Publications = rs.Q1Publications;
            this->EUProjects = rs.EUProjects;
            this->funding = rs.funding;
        }
        return *this;
    }

    double impact() const override {
        return Scientist::impact() + (Q1Publications * 0.4 + EUProjects * 0.3 + funding * 0.01);
    }

    void print() const override {
        Scientist::print();
        cout << "Q1 Publications: " << Q1Publications << endl;
        cout << "EU Projects: " << EUProjects << endl;
        cout << "Funding: " << funding << endl;
        cout << "Impact Score: " << impact() << endl;
    }
};

void printHighestImpact(Scientist *scientists, int n) {
    int maxIndex = 0;
    for (int i = 1; i < n; i++) {
        if (scientists[i].impact() > scientists[maxIndex].impact()) {
            maxIndex = i;
        }
    }

    cout << "HIGHEST IMPACT SCIENTIST:" << endl;
    cout << "=====================================" << endl;
    scientists[maxIndex].print();
}


int main() {
    int n;
    cin >> n;

    if (n == 1) {
        // Test Scientist (Basic)
        int numScientists;
        cin >> numScientists;

        Scientist *scientists = new Scientist[numScientists];

        for (int i = 0; i < numScientists; ++i) {
            char name[100], institutiontitution[50];
            int publications, citons, years;
            cin >> name >> institutiontitution >> publications >> citons >> years;

            scientists[i] = Scientist(name, institutiontitution, publications, citons, years);
        }

        cout << "SCIENTISTS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < numScientists; ++i) {
            scientists[i].print();
            cout << "-------------------------" << endl;
        }

        // Copy Constructor Test
        cout << "Testing Copy Constructor:" << endl;
        Scientist copiedScientist = scientists[0];
        copiedScientist.print();

        // Assignment Operator Test
        cout << "Testing Assignment Operator:" << endl;
        Scientist assignedScientist;
        assignedScientist = scientists[1];
        assignedScientist.print();

        delete[] scientists;
    } else if (n == 2) {
        // Test ResearchScientist
        int numScientists;
        cin >> numScientists;

        ResearchScientist *scientists = new ResearchScientist[numScientists];

        for (int i = 0; i < numScientists; ++i) {
            char name[100], institutiontitution[50];
            int publications, citons, years, Q1publications, EUprojects;
            double funding;

            cin >> name >> institutiontitution >> publications >> citons >> years;
            cin >> Q1publications >> EUprojects >> funding;

            scientists[i] = ResearchScientist(name, institutiontitution, publications, citons, years, Q1publications,
                                              EUprojects, funding);
        }

        cout << "RESEARCH SCIENTISTS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < numScientists; ++i) {
            scientists[i].print();
            cout << "-------------------------" << endl;
        }

        // Copy Constructor Test
        cout << "Testing Copy Constructor:" << endl;
        ResearchScientist copiedResearchScientist = scientists[0];
        copiedResearchScientist.print();

        // Assignment Operator Test
        cout << "Testing Assignment Operator:" << endl;
        ResearchScientist assignedResearchScientist;
        assignedResearchScientist = scientists[1];
        assignedResearchScientist.print();

        delete[] scientists;
    } else if (n == 3) {
        // Test printing scientist with highest impact
        int numScientists;
        cin >> numScientists;

        Scientist *scientists = new Scientist[numScientists];

        for (int i = 0; i < numScientists; ++i) {
            char name[100], institutiontitution[50];
            int publications, citons, years;
            cin >> name >> institutiontitution >> publications >> citons >> years;

            scientists[i] = Scientist(name, institutiontitution, publications, citons, years);
        }

        printHighestImpact(scientists, numScientists);
        delete[] scientists;
    }

    return 0;
}
