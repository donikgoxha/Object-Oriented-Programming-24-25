/*
Да се дефинира класа Flight во која што ќе се чуваат податоци за лет:
име на лет (низа од максимум 100 карактери)
полетување од (низа од максимум 50 карактери)
пристигнување во (низа од максимум 50 карактери)
цена на лет (цел број)
За класата да се дефинира copy конструктор, default конструктор и конструктор со аргументи.
Доколку е потребно да се креираат и get методи.
Потоа да се креира класа Airport во која што се чуваат следните податоци:
име на аеродром (низа од максимум 50 карактери)
број на летови на аеродромот(цел број)
низа од летови на аеродромот(низа од објекти од Flight класата, max 100)
Да се креира конструктор со аргументи за класата.
Доколку е потребно да се креира и get методи.
Во класата да се креира функција cheapestFlight што ќе го врати најевтиниот лет на аеродромот.

ДА НЕ СЕ МЕНУВА MAIN ФУНКЦИЈАТА.
*/

#include <iostream>
#include <cstring>
using namespace std;

class Flight {
    char flightName[100];
    char departure[50];
    char arrival[50];
    int flightPrice;

    void copy(const Flight &other) {
        strcpy(flightName, other.flightName);
        strcpy(departure, other.departure);
        strcpy(arrival, other.arrival);
        flightPrice = other.flightPrice;
    }

public:
    Flight(const char *flightName = "", const char *departure = "", const char *arrival = "", int flightPrice = 0) {
        strcpy(this->flightName, flightName);
        strcpy(this->departure, departure);
        strcpy(this->arrival, arrival);
        this->flightPrice = flightPrice;
    }

    Flight(const Flight &f) {
        copy(f);
    }

    ~Flight() = default;

    int getFlightPrice() const { return flightPrice; }

    //void setFlightPrice(const int flight_price) { flightPrice = flight_price; }

    const char *getFlightName() const { return flightName; }

    //void setFlightName(const char *flight_name) { strcpy(this->flightName, flight_name); }

    const char *getDeparture() const { return departure; }

    //void setDeparture(const char *departure) { strcpy(this->departure, departure); }

    const char *getArrival() const { return arrival; }

    //void setArrival(const char *arrival) { strcpy(this->arrival, arrival); }
};

class Airport {
    char name[50];
    int numFlights;
    Flight flights[100];

public:
    Airport(const char *name = "", int numFlights = 0, Flight flights[100] = nullptr) {
        strcpy(this->name, name);
        this->numFlights = numFlights;
        for (int i = 0; i < numFlights; i++) {
            this->flights[i] = flights[i];
        }
    }

    Flight cheapestFlight() {
        int index = -1;
        int cheapest = INT_MAX;
        for (int i = 0; i < numFlights; i++) {
            if (cheapest > flights[i].getFlightPrice()) {
                cheapest = flights[i].getFlightPrice();
                index = i;
            }
        }
        return flights[index];
    }
};

int main() {
    //GIVEN MAIN
    return 0;
}
