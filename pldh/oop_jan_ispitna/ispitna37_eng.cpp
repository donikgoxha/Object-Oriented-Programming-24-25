#include <iostream>

using namespace std;

//Your code here

class Library {
protected:
    string name;
    string city;
    float membership;
    bool weekends;

public:
    Library(const string &name, const string &city, const float membership, const bool weekends)
        : name(name),
          city(city),
          membership(membership),
          weekends(weekends) {
    }

    ~Library() {
    }

    virtual void printDetail() const = 0;

    virtual double calculateMembershipCardCost() const = 0;

    bool isOperating() const {
        return weekends;
    }
};

class AcademicLibrary : public Library {
private:
    bool research;
    int specializedJournals;

public:
    AcademicLibrary(const string &name, const string &city, const float membership, const bool weekends,
                    const bool research, const int specialized_journals)
        : Library(name, city, membership, weekends),
          research(research),
          specializedJournals(specialized_journals) {
    }

    double calculateMembershipCardCost() const override {
        float cost = membership;
        if (research) {
            cost *= 1.24;
        }
        cost += specializedJournals * 6;
        return cost;
    }

    void printDetail() const override {
        cout << name << " - (Academic) " << city << " " << specializedJournals << " "
                << calculateMembershipCardCost() << endl;
    }
};


class NationalLibrary : public Library {
private:
    bool educational;
    int originalManuscripts;

public:
    NationalLibrary(const string &name, const string &city, const float membership, const bool weekends,
                    const bool educational, const int original_manuscripts)
        : Library(name, city, membership, weekends),
          educational(educational),
          originalManuscripts(original_manuscripts) {
    }

    double calculateMembershipCardCost() const override {
        float cost = membership;
        if (educational) {
            cost *= 0.93;
        }
        cost += originalManuscripts * 15;
        return cost;
    }

    void printDetail() const override {
        cout << name << " - (National) " << city << " " << originalManuscripts << " "
                << calculateMembershipCardCost() << endl;
    }
};

int findMostExpensiveNationalLibrary(Library **l, int n) {
    int maxIndex = -1;
    double maxValue = -1.0;
    for (int i = 0; i < n; i++) {
        NationalLibrary *nl = dynamic_cast<NationalLibrary *>(l[i]);
        if (nl) {
            double fee = nl->calculateMembershipCardCost();
            if (fee > maxValue || (fee == maxValue && nl->isOperating())) {
                maxValue = fee;
                maxIndex = i;
            }
        }
    }
    return maxIndex;
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
