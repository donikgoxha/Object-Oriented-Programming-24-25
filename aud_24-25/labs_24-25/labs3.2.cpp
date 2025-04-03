/*
Да се дефинира класа Tour за која се чуваат слецните податоци:

destination - char[]
duration - int
price - double
totalTours - static варијабла која брои колку вкупно тури се креирани,
бројот да се инкрементира во конструкторот со аргумрнти
passengers - int
За класата да се дефинира default конструктор, конструктор со аргументи и copy конструктор.

За класата да се дефинира метод double profitByTour() со која се пресметува остварениот профит
од дадената тура. (бројот на патници * цената на турата)

Да се креира и display метода во следниот формат:

Destination: [destination], Duration: [duration] days, Price: [price], Passengers: [passengers]

Потоа да се дефинира класа Agency за која се чува:
name - char[]
tours - низа од Tour која нема да има повеќе од 10 елементи
numTours - int
За класата да се дефинира default конструктор, конструктор со аргументи.
Да се креира и display метода во следниот формат:
Travel Agency: [name]
[tour1 display]
[tour2 display]
...

Исто така да се дефинира метода void addTour(Tour tour) со која ќе се додаваат тури во агенцијата.

Надвор од класата да се дефинира метод void findBestAgency(Agency *agencies, int numAgencies)
кој прима низа од агении и ја печати онаа агенција која остварила најмногу профит од сите тури.
Овој метод мора да пристапува до самите приватни полиња од класите.
 */


#include <iostream>
#include <cstring>
using namespace std;

class Tour {
private:
    char destination[100];
    int duration;
    double price;
    static int totalTours;
    int passengers;

    void copy(const Tour &t){
      strcpy(destination, t.destination);
      duration = t.duration;
      price = t.price;
      passengers = t.passengers;
      totalTours = t.totalTours;
    }

public:
    Tour() {}

    Tour(const char destination[], int duration, double price, int passengers) {
        strcpy(this->destination, destination);
        this->duration = duration;
        this->price = price;
        this->passengers = passengers;
        totalTours++;
    }

    Tour(const Tour &t){
      copy(t);
    }

    double profitByTour() {
        return passengers * price;
    }

    void display() {
        cout << "Destination: " << destination << ", Duration: " << duration << " days, Price: " << price << ", Passengers: " << passengers << endl;
    }

    static int getNumTours() {  // ✅ Fixed static function
        return totalTours;
    }

    ~Tour() {}
    friend class Agency;
};

int Tour::totalTours = 0;

class Agency {
private:
    char name[30];
    Tour tours[10];
    int numTours;

public:
    Agency() { numTours = 0; }

    Agency(char name[], Tour tours[10], int numTours) {
        strcpy(this->name, name);
        for (int i = 0; i < numTours; i++) {
            this->tours[i] = tours[i];
        }
        this->numTours = numTours;
    }

    void setName(char n[30]) {
        strcpy(name, n);
    }

    void display() {
        cout << name << endl;
        for (int i = 0; i < numTours; i++) {
            tours[i].display();
        }
    }

    void addTour(Tour tour) {
        if (numTours < 10) {
            tours[numTours++] = tour;
        }
    }

    int getNumTours() {
        return numTours;
    }

    char* getName() { return name; }
    Tour* getTours() { return tours; }

    ~Agency() {}
};

void findBestAgency(Agency *agencies, int numAgencies) {
    int bestIndex = 0;
    double maxProfit = -1;

    for (int i = 0; i < numAgencies; i++) {
        double totalProfit = 0;

        for (int j = 0; j < agencies[i].getNumTours(); j++) {
            totalProfit += agencies[i].getTours()[j].profitByTour();
        }

        if (totalProfit > maxProfit) {
            maxProfit = totalProfit;
            bestIndex = i;
        }
    }

    cout << "Best agency: " << agencies[bestIndex].getName() << " with profit: " << maxProfit << endl;
}

int main() {
    int test_case_n;
    char name[50], dest[50];
    int dur, pass;
    double pr;

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
