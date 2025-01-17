#include <iostream>
#include <cstring>
using namespace std;

// Links to the lessons
// https://finki-mk.github.io/OOP/html5/oop_av5.html
// https://bbb-lb.finki.ukim.mk/playback/presentation/2.3/740dc1184c44f2d100ce97a5038744c4cd34f22a-1648042101186

class Team {
private:
    char *name;
    char *stadium;
    char *city;

    void copy(const Team &t) {
        this->name = new char[strlen(t.name) + 1];
        strcpy(this->name, t.name);
        this->stadium = new char[strlen(t.stadium) + 1];
        strcpy(this->stadium, t.stadium);
        this->city = new char[strlen(t.city) + 1];
        strcpy(this->city, t.city);
    }

    void freeMemory() {
        delete[] name;
        delete[] stadium;
        delete[] city;
    }

public:
    //constructor with args and default
    Team(char *name = "", char *stadium = "", char *city = "") {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->stadium = new char[strlen(stadium) + 1];
        strcpy(this->stadium, stadium);
        this->city = new char[strlen(city) + 1];
        strcpy(this->city, city);
    }

    //copy constructor
    Team(const Team &t) {
        copy(t);
    }

    //operator ednakvo (=)
    Team &operator=(const Team &t) {
        if (this != &t) {
            freeMemory();
            copy(t);
        }
        return *this;
    }

    //destructor
    ~Team() {
        freeMemory();
    }

    void print() {
        cout << "Team name: " << name << " which plays on stadium: " << stadium << " in the city: " << city << endl;
    }
};


int main() {
    int n;
    cin >> n;
    Team *teams = new Team[n];

    char name[101];
    char stadium[101];
    char city[101];

    for (int i = 0; i < n; i++) {
        cin >> name >> stadium >> city;
        teams[i] = Team(name, stadium, city);
    }

    for (int i = 0; i < n; i++) {
        teams[i].print();
    }
    return 0;
}
