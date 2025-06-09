#include <iostream>

using namespace std;
//Your code here

class Library {
protected:
    string name;
    string city;
    float monthlyMembershipFee;
    bool weekends;

public:
    Library(const string &name = "", const string &city = "", float monthlyMembershipFee = 0.0, bool weekends = false) {
        this->name = name;
        this->city = city;
        this->monthlyMembershipFee = monthlyMembershipFee;
        this->weekends = weekends;
    }

    virtual void printDetail() const = 0;

    virtual double calculateMembershipCardCost() const = 0;

    bool operatesOnWeekends() const { return weekends; }
};

class AcademicLibrary : public Library {
private:
    bool research;
    int specializedJournals;

public:
    AcademicLibrary(const string &name = "", const string &city = "", float monthlyMembershipFee = 0.0,
                    bool weekends = false, bool research = false, int specializedJournals = 0) : Library(
        name, city, monthlyMembershipFee, weekends) {
        this->research = research;
        this->specializedJournals = specializedJournals;
    }

    double calculateMembershipCardCost() const {
        double fee = monthlyMembershipFee;
        if (research) fee *= 1.24;
        fee += specializedJournals * 6;
        return fee;
    }

    void printDetail() const {
        cout << name << " - (Academic) " << city << " " << specializedJournals << " " << calculateMembershipCardCost()
                << endl;
    }
};


class NationalLibrary : public Library {
private:
    bool educationalPrograms;
    int ogManuscripts;

public:
    NationalLibrary(const string &name = "", const string &city = "", float monthlyMembershipFee = 0.0,
                    bool weekends = false, bool educationalPrograms = false, int ogManuscripts = 0): Library(
        name, city, monthlyMembershipFee, weekends) {
        this->educationalPrograms = educationalPrograms;
        this->ogManuscripts = ogManuscripts;
    }

    double calculateMembershipCardCost() const {
        double fee = monthlyMembershipFee;
        if (educationalPrograms) fee *= 0.93;
        fee += ogManuscripts * 15;
        return fee;
    }

    void printDetail() const {
        cout << name << " - (National) " << city << " " << ogManuscripts << " " << calculateMembershipCardCost() <<
                endl;
    }
};

int findMostExpensiveNationalLibrary(Library **l, int n) {
    int index = -1;
    double maxCost = -1;

    for (int i = 0; i < n; ++i) {
        NationalLibrary *natLib = dynamic_cast<NationalLibrary *>(l[i]);
        if (natLib != nullptr) {
            double cost = natLib->calculateMembershipCardCost();
            if (cost > maxCost || (cost == maxCost && natLib->operatesOnWeekends())) {
                maxCost = cost;
                index = i;
            }
        }
    }
    return index;
}

int main() {
    int n, testCase, type;
    cin >> testCase >> n;
    cin.ignore();

    Library **m = new Library *[n];

    for (int i = 0; i < n; ++i) {
        string name;
        string city;
        float base_price;
        bool weekend_working;

        cin >> type;
        cin.ignore();
        getline(cin, name);
        getline(cin, city);
        cin >> base_price;
        cin.ignore();
        cin >> weekend_working;
        cin.ignore();

        if (type == 1) {
            bool open_cooperation;
            int specialized_articles;

            cin >> open_cooperation >> specialized_articles;
            cin.ignore();

            m[i] = new AcademicLibrary(name, city, base_price, weekend_working, open_cooperation, specialized_articles);
        } else {
            bool cultural_program;
            int national_articles;

            cin >> cultural_program >> national_articles;
            cin.ignore();

            m[i] = new NationalLibrary(name, city, base_price, weekend_working, cultural_program, national_articles);
        }
    }

    if (testCase == 1) {
        cout << "Abstract and child classes OK" << endl;
    } else if (testCase == 2) {
        for (int i = 0; i < n; i++) {
            cout << m[i]->calculateMembershipCardCost() << endl;
        }
        cout << "calculateMembershipCardCost method OK" << endl;
    } else if (testCase == 3) {
        for (int i = 0; i < n; i++) {
            m[i]->printDetail();
        }
        cout << "printDetail method OK" << endl;
    } else if (testCase == 4) {
        int most_expensive_nat_lib_index = findMostExpensiveNationalLibrary(m, n);
        if (most_expensive_nat_lib_index >= 0) {
            m[most_expensive_nat_lib_index]->printDetail();
        } else {
            cout << "National Library not found in the array!" << endl;
        }
        cout << "findMostExpensiveNationalLibrary method OK" << endl;
    }


    for (int i = 0; i < n; ++i) {
        delete m[i];
    }

    delete[] m;

    return 0;
}
