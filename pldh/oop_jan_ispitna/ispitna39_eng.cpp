#include <iostream>
#include <cstring>
using namespace std;

//Your code here
class Museum {
protected:
    string name;
    string city;
    float basePrice;
    int working_hours;

public:
    Museum(const string &name, const string &city, const float base_price, const int working_hours)
        : name(name),
          city(city),
          basePrice(base_price),
          working_hours(working_hours) {
    }

    virtual ~Museum() = default;

    virtual void printDetail() const = 0;

    virtual double calculateTicketCost() const = 0;

    int getWorkingHours() const {
        return working_hours;
    }
};

class ScientificMuseum : public Museum {
    bool interactive;
    int multimediaPresentations;

public:
    ScientificMuseum(const string &name, const string &city, const float base_price, const int number_of_working_days,
                     const bool interactive, const int multimedia_presentations)
        : Museum(name, city, base_price, number_of_working_days),
          interactive(interactive),
          multimediaPresentations(multimedia_presentations) {
    }

    double calculateTicketCost() const override {
        float cost = basePrice;
        if (interactive) {
            cost *= 1.12;
        }
        cost += multimediaPresentations * 6;
        return cost;
    }

    void printDetail() const override {
        cout << name << " - (Scientific) " << city << " " << multimediaPresentations << " "
                << calculateTicketCost() << endl;
    }
};


class ArtMuseum : public Museum {
    bool amateur;
    int nonRestored;

public:
    ArtMuseum(const string &name, const string &city, float base_price, int number_of_working_days, bool amateur,
              int non_restored)
        : Museum(name, city, base_price, number_of_working_days),
          amateur(amateur),
          nonRestored(non_restored) {
    }

    double calculateTicketCost() const override {
        float cost = basePrice;
        if (amateur) {
            cost *= 0.82;
        }
        cost += nonRestored * 3;
        return cost;
    }

    void printDetail() const override {
        cout << name << " - (Art) " << city << " " << amateur << " "
                << calculateTicketCost() << endl;
    }
};

int findCheapestScientificMuseum(Museum **m, int n) {
    int index = -1;
    double min_cost = 9999;
    int maxWorkingHours = 0;

    for (int i = 0; i < n; ++i) {
        ScientificMuseum *sci_museum = dynamic_cast<ScientificMuseum *>(m[i]);
        if (sci_museum) {
            double cost = sci_museum->calculateTicketCost();
            if (cost < min_cost || (cost == min_cost && sci_museum->getWorkingHours() > maxWorkingHours)) {
                min_cost = cost;
                maxWorkingHours = sci_museum->getWorkingHours();
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

    Museum **m = new Museum *[n];

    for (int i = 0; i < n; ++i) {
        string name;
        string city;
        float base_price;
        int working_hours;

        cin >> type;
        cin.ignore();
        getline(cin, name);
        getline(cin, city);
        cin >> base_price;
        cin.ignore();
        cin >> working_hours;
        cin.ignore();

        if (type == 1) {
            bool interactive_shows;
            int multimedia_pres;

            cin >> interactive_shows >> multimedia_pres;
            cin.ignore();

            m[i] = new ScientificMuseum(name, city, base_price, working_hours, interactive_shows, multimedia_pres);
        } else {
            bool amateur_shows;
            int original_artwork;

            cin >> amateur_shows >> original_artwork;
            cin.ignore();

            m[i] = new ArtMuseum(name, city, base_price, working_hours, amateur_shows, original_artwork);
        }
    }

    if (testCase == 1) {
        cout << "Abstract and child classes OK" << endl;
    } else if (testCase == 2) {
        for (int i = 0; i < n; i++) {
            cout << m[i]->calculateTicketCost() << endl;
        }
        cout << "calculateTicketCost method OK" << endl;
    } else if (testCase == 3) {
        for (int i = 0; i < n; i++) {
            m[i]->printDetail();
        }
        cout << "printDetail method OK" << endl;
    } else if (testCase == 4) {
        int cheapest_sci_museum_index = findCheapestScientificMuseum(m, n);
        if (cheapest_sci_museum_index >= 0) {
            m[cheapest_sci_museum_index]->printDetail();
        } else {
            cout << "Scientific Museum not found in the array!" << endl;
        }
        cout << "findCheapestOnlineOrder method OK" << endl;
    }


    for (int i = 0; i < n; ++i) {
        delete m[i];
    }

    delete[] m;

    return 0;
}
