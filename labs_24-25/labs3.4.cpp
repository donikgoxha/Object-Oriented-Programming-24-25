#include <iostream>
#include <string.h>
using namespace std;

class Tour {
private:
    char destination[100];
    int duration;
    double price;
    static int totalTours;
    int passengers;

public:
    Tour() {
        destination[0] = '\0';
        duration = 0;
        price = 0.0;
        passengers = 0;
    }

    Tour(const char *destination, int duration, double price, int passengers) {
        strcpy(this->destination, destination);
        this->duration = duration;
        this->price = price;
        this->passengers = passengers;
        totalTours++;
    }

    Tour(const Tour &t) {
        strcpy(this->destination, t.destination);
        this->duration = t.duration;
        this->price = t.price;
        this->passengers = t.passengers;
    }

    double profitByTour() {
        return price * passengers;
    }

    void display() {
        cout << "Destination: " << destination << ", Duration: " << duration << " days, Price: " << price <<
                ", Passengers: "
                << passengers << endl;
    }

    static int getNumTours() {
        return totalTours;
    }
};

int Tour::totalTours = 0;

class Agency {
private:
    char name[100];
    Tour tours[10];
    int numTours;

public:
    Agency(const char *name = "") {
        strcpy(this->name, name);
        numTours = 0;
    }

    void display() {
        cout << "Travel Agency: " << name << endl;
        for (int i = 0; i < numTours; i++) {
            tours[i].display();
        }
    }

    void setName(const char *n) {
        strcpy(name, n);
    }

    int getNumTours() const {
        return numTours;
    }

    void addTour(Tour t) {
        if (numTours < 10) {
            tours[numTours++] = t;
        }
    }

    friend void findBestAgency(Agency *agencies, int numAgencies);
};

void findBestAgency(Agency *agencies, int numAgencies) {
    double bestProfit = -1.0;
    int idx = 0;
    for (int i = 0; i < numAgencies; i++) {
        double profit = 0.0;
        for (int j = 0; j < agencies[i].numTours; j++) {
            profit += agencies[i].tours[j].profitByTour();
        }
        if (profit > bestProfit) {
            bestProfit = profit;
            idx = i;
        }
    }
    agencies[idx].display();
}

int main() {
    int test_case_n;

    char name[50];
    char dest[50];
    int dur;
    double pr;
    int pass;

    cin >> test_case_n;

    if (test_case_n == 0) {
        cout << "Testing Tour c-tors, display function:" << endl;
        cin >> dest >> dur >> pr >> pass;
        Tour t1 = Tour(dest, dur, pr, pass);
        Tour t2 = Tour(t1);
        t1.display();
        t2.display();
    } else if (test_case_n == 1) {
        cout << "Testing Tour profitByTour function:" << endl;
        cin >> dest >> dur >> pr >> pass;
        Tour t1 = Tour(dest, dur, pr, pass);
        cout << t1.profitByTour() << endl;
    } else if (test_case_n == 2) {
        cout << "Testing Agency c-tor, display function:" << endl;

        Agency agency;

        cin >> name;
        agency.setName(name);
        int numTours;
        cin >> numTours;
        for (int j = 0; j < numTours; ++j) {
            cin >> dest >> dur >> pr >> pass;
            agency.addTour(Tour(dest, dur, pr, pass));
        }

        agency.display();
    } else if (test_case_n == 3) {
        cout << "Testing static field in Tour:" << endl;

        Agency agency[10];
        int n;
        cin >> n;

        for (int i = 0; i < n; ++i) {
            cin >> name;
            agency[i].setName(name);
            int numTours;
            cin >> numTours;
            for (int j = 0; j < numTours; ++j) {
                cin >> dest >> dur >> pr >> pass;
                agency[i].addTour(Tour(dest, dur, pr, pass));
            }
        }

        cout << "Total number of tours: " << Tour::getNumTours() << endl;
    } else if (test_case_n == 4) {
        Agency agency[10];
        int n;
        cin >> n;

        for (int i = 0; i < n; ++i) {
            cin >> name;
            agency[i].setName(name);
            int numTours;
            cin >> numTours;
            for (int j = 0; j < numTours; ++j) {
                cin >> dest >> dur >> pr >> pass;
                agency[i].addTour(Tour(dest, dur, pr, pass));
            }
        }

        findBestAgency(agency, n);
    }


    return 0;
}
