#include <iostream>
#include <cstring>
using namespace std;

class State;

class County {
private:
    char name[100];
    int gdp;

public:
    County(const char *name = "", int gdp = 0) {
        strcpy(this->name, name);
        this->gdp = gdp;
    }

    County(const County &other) {
        strcpy(this->name, other.name);
        this->gdp = other.gdp;
    }

    const char *getName() {
        return name;
    }

    const int getGDP() {
        return gdp;
    }

    friend void printStatesInGDPOrderByStateType(State states[], int numStates, bool redStates);

    friend class State;
};

class State {
private:
    County counties[100];
    char name[100];
    int numCounties;
    static float federalTax;
    bool redState;

public:
    State(County *counties = nullptr, const char *name = "", int numCounties = 0, bool redState = false) {
        if (counties != nullptr) {
            for (int i = 0; i < numCounties; i++) {
                this->counties[i] = counties[i];
            }
        }
        this->numCounties = numCounties;
        strcpy(this->name, name);
        this->redState = redState;
    }

    const char *getName() {
        return name;
    }

    static float getFederalTax() {
        return federalTax;
    }

    static void setFederalTax(float tax) {
        federalTax = tax;
    }

    static void increaseFederalTax(float i) {
        federalTax += i;
    }

    double getFullGDP() {
        float total = 0;
        for (int i = 0; i < numCounties; i++) {
            total += counties[i].getGDP();
        }
        return total - (total * (federalTax / 100.0));
    }

    void print() {
        cout << "State of " << name << endl;
        for (int i = 0; i < numCounties; i++) {
            cout << counties[i].getName() << endl;
        }
    }

    friend void printStatesInGDPOrderByStateType(State states[], int numStates, bool redStates);

    friend class County;
};

void printStatesInGDPOrderByStateType(State states[], int numStates, bool redStates) {
    int a[100];
    int counter = 0;

    for (int i = 0; i < numStates; i++) {
        if (states[i].redState == redStates) {
            a[counter++] = i;
        }
    }

    for (int i = 0; i < counter - 1; i++) {
        for (int j = 0; j < counter - i - 1; j++) {
            if (states[a[j]].getFullGDP() < states[a[j + 1]].getFullGDP()) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < counter; i++) {
        int index = a[i];
        cout << states[index].name << endl;
    }
}


//main should remain unchanged!
float State::federalTax = 15.5;

int main() {
    int n;
    cin >> n;
    char name[30] = "Richmond";
    County counties[3];
    counties[0] = County(name, 20);
    strcpy(name, "Bronx");
    counties[1] = County(name, 57);
    strcpy(name, "New York");
    counties[2] = County(name, 32);
    State state(counties, name, 3, false);
    switch (n) {
        case 1: {
            cout << "---Testing constructors, getters, setters---" << endl;
            float fed;
            cin >> fed;
            State::setFederalTax(fed);
            if (State::getFederalTax() == 15.5) {
                cout << "State federal tax setter not OK!";
                break;
            }
            cout << counties[2].getName() << " Federal tax: " << State::getFederalTax() << " Full GDP: "
                    << state.getFullGDP();
            break;
        }
        case 2: {
            cout << "---Testing print method---" << endl;
            char name2[50];
            cin >> name2;
            County counties2[4];
            for (int i = 0; i < 3; ++i) {
                counties2[i] = counties[i];
            }
            counties2[3] = County(name2, 27);
            State state2(counties2, name, 4, false);
            state2.print();
            break;
        }
        case 3: {
            cout << "---Testing increaseFederalTax static method---" << endl;
            float increase;
            cin >> increase;
            cout << State::getFederalTax() << endl;
            State::increaseFederalTax(increase);
            cout << State::getFederalTax() << endl;
            cout << state.getFullGDP();
            break;
        }
        default:
            cout << "---Testing printStatesInGDPOrderByStateType---" << endl;
            County counties2[4];
            for (int i = 0; i < 3; ++i) {
                counties2[i] = counties[i];
            }
            strcpy(name, "Wayme");
            counties2[3] = County(name, 27);
            strcpy(name, "Ohio");
            State state2(counties2, name, 4, false);
            int numStates;
            cin >> numStates;
            numStates = numStates + 2;
            State states[numStates];
            states[0] = state;
            states[1] = state2;
            bool redStateSType;
            for (int i = 2; i < numStates; ++i) {
                char stateName[30];
                int numCounties;
                cin >> stateName >> numCounties >> redStateSType;
                County county[numCounties];
                for (int j = 0; j < numCounties; ++j) {
                    char ime[30];
                    int GDP;
                    cin >> ime >> GDP;
                    county[j] = County(ime, GDP);
                }
                states[i] = State(county, stateName, numCounties, redStateSType);
            }
            cout << "Red states: " << endl;
            printStatesInGDPOrderByStateType(states, numStates, true);
            cout << "Blue states: " << endl;
            printStatesInGDPOrderByStateType(states, numStates, false);
    }
    return 0;
}
