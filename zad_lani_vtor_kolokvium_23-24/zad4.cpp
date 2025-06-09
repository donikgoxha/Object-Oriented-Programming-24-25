#include <iostream>
#include <cstring>

using namespace std;

//Your code here
class Museum {
protected:
    string name;
    string city;
    float basePrice;
    int workingHoursWeekly;

public:
    Museum(const string &name = "", const string &city = "", float basePrice = 0.0, int workingHoursWeekly = 0) {
        this->name = name;
        this->city = city;
        this->basePrice = basePrice;
        this->workingHoursWeekly = workingHoursWeekly;
    }

    virtual double calculateTicketCost() const = 0;

    virtual void printDetail() const = 0;

    int getWorkingHoursWeekly() const {
        return workingHoursWeekly;
    }
};

class ScientificMuseum : public Museum {
private:
    bool interactiveExibits;
    int numPresentations;

public:
    ScientificMuseum(const string &name = "", const string &city = "", float basePrice = 0.0,
                     int workingHoursWeekly = 0, bool interactiveExibits = false, int numPresentations = 0): Museum(
        name, city, basePrice, workingHoursWeekly) {
        this->interactiveExibits = interactiveExibits;
        this->numPresentations = numPresentations;
    }

    double calculateTicketCost() const {
        double fee = basePrice;
        if (interactiveExibits) fee *= 1.12;
        fee += numPresentations * 6;
        return fee;
    }

    void printDetail() const {
        cout << name << " - (Scientific) " << city << " " << numPresentations << " " << calculateTicketCost() << endl;
    }
};


class ArtMuseum : public Museum {
private:
    bool amateurExhibitions;
    int nonRestoredArt;

public:
    ArtMuseum(const string &name = "", const string &city = "", float basePrice = 0.0,
              int workingHoursWeekly = 0, bool amateurExhibitions = false, int nonRestoredArt = 0): Museum(
        name, city, basePrice, workingHoursWeekly) {
        this->amateurExhibitions = amateurExhibitions;
        this->nonRestoredArt = nonRestoredArt;
    }

    double calculateTicketCost() const {
        double fee = basePrice;
        if (amateurExhibitions) fee *= 0.82;
        fee += nonRestoredArt * 3;
        return fee;
    }

    void printDetail() const {
        cout << name << " - (Art) " << city << " " << amateurExhibitions << " " << calculateTicketCost() << endl;
    }
};

int findCheapestScientificMuseum(Museum **m, int n) {
    int index = -1;
    double minCost = -1;
    int maxHours = -1;

    for (int i = 0; i < n; i++) {
        ScientificMuseum *sci = dynamic_cast<ScientificMuseum *>(m[i]);
        if (sci != nullptr) {
            double cost = sci->calculateTicketCost();
            int hours = sci->getWorkingHoursWeekly();

            if (index == -1 || cost < minCost || (cost == minCost && hours > maxHours)) {
                index = i;
                minCost = cost;
                maxHours = hours;
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
