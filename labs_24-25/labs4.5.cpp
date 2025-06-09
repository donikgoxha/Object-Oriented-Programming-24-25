#include<iostream>
#include<cstring>
using namespace std;

enum Type { EMPLOYER, WORKER, SCIENTIST };

class Robot {
private:
    char name[50];
    int battery;
    Type type;

public:
    Robot(const char *name = "", int battery = 0, Type type = EMPLOYER) {
        strcpy(this->name, name);
        this->battery = battery;
        this->type = type;
    }

    void addBattery(int increase) {
        battery += increase;
        if (battery > 100) {
            battery = 100;
        }
    }

    const char *getName() const {
        return name;
    }

    Type getCategory() const {
        return type;
    }

    void print() const {
        cout << "Name: " << name << endl;
        cout << "Battery: " << battery << endl;
        cout << "Category: ";
        if (type == EMPLOYER) cout << "EMPLOYER";
        else if (type == WORKER) cout << "WORKER";
        else cout << "SCIENTIST";
        cout << endl;
    }

    friend class Colony;
};

class Colony {
private:
    char name[50];
    Robot robots[10];
    int n;

public:
    Colony(const char *name = "", Robot *robots = nullptr, int n = 0) {
        strcpy(this->name, name);
        this->n = 0;
        if (robots != nullptr) {
            for (int i = 0; i < n; i++) {
                this->robots[i] = robots[i];
            }
        }
    }

    void addRobot(const Robot &r) {
        for (int i = 0; i < n; i++) {
            if (strcmp(robots[i].getName(), r.getName()) == 0 &&
                robots[i].getCategory() == r.getCategory()) {
                cout << "This robot can't be added!" << endl;
                return;
            }
        }
        if (n < 10) {
            robots[n++] = r;
        }
    }

    void print() const {
        cout << "Colony: " << name << endl;
        for (int i = 0; i < n; i++) {
            robots[i].print();
        }
    }

    friend void addBatteryForOthersCategory(Colony *c, int n, Type notfromthisCategory, int amount);

    int getRobotCount() const { return n; }
};

void addBatteryForOthersCategory(Colony *colonies, int numColonies, Type notfromthisCategory, int amount) {
    for (int i = 0; i < numColonies; i++) {
        for (int j = 0; j < colonies[i].getRobotCount(); j++) {
            if (colonies[i].robots[j].getCategory() != notfromthisCategory) {
                colonies[i].robots[j].addBattery(amount); // Add battery to robots that are not in the excluded category
            }
        }
    }
}


int main() {
    //main given by the quiz
    return 0;
}
