#include <iostream>
#include <utility>
using namespace std;

class InvalidSerialNumberException : public exception {
    string serialNumber;

public:
    explicit InvalidSerialNumberException(string serialNumber) : serialNumber(std::move(serialNumber)) {
    }

    void showMessage() const {
        cout << "The serial number " << serialNumber << " is invalid machine serial number format." << endl;
    }
};

class Machine {
protected:
    string model;
    int powerConsumption;
    float basePrice;
    string serialNumber;

public:
    Machine(const string &model = "", int powerConsumption = 0, const string &serialNumber = "") {
        if (serialNumber.length() != 12 || serialNumber.find(' ') != string::npos) {
            throw InvalidSerialNumberException(serialNumber);
        }
        this->serialNumber = serialNumber;
        this->model = model;
        this->powerConsumption = powerConsumption;
    }

    virtual ~Machine() = default;

    virtual float calculateCost() = 0;

    virtual void showDetails() = 0;
};


class WashingMachine : public Machine {
private:
    int loadCapacity;

public:
    WashingMachine(const string &model = "", int powerConsumption = 0, const string &serialNumber = "",
                   int loadCapacity = 0)
        : Machine(model, powerConsumption, serialNumber), loadCapacity(loadCapacity) {
    }

    float calculateCost() override {
        basePrice = (loadCapacity > 8) ? 500 * 1.12 : 500;
        basePrice += (powerConsumption / 100) * 20;
        return basePrice;
    }


    void showDetails() override {
        cout << "Washing Machine " << model << " cost: " << calculateCost() << "$" << endl;
    }
};


class DryingMachine : public Machine {
private:
    bool hasSensor;

public:
    DryingMachine(const string &model = "", int powerConsumption = 0, const string &serialNumber = "",
                  bool hasSensor = false) : Machine(
        model, powerConsumption, serialNumber) {
        this->hasSensor = hasSensor;
    }

    float calculateCost() override {
        basePrice = (hasSensor) ? 600 * 1.15 : 600;
        basePrice += (powerConsumption / 100) * 25;
        return basePrice;
    }

    void showDetails() override {
        cout << "Drying Machine " << model << " cost: " << calculateCost() << "$" << endl;
    }
};

Machine **createMachines(int n) {
    Machine **machines = new Machine *[n];
    for (int i = 0; i < n; i++) {
        int type;
        string model, serialNumber;
        int powerConsumption;
        cin >> type >> model >> powerConsumption >> serialNumber;

        try {
            if (type == 1) {
                int loadCapacity;
                cin >> loadCapacity;
                machines[i] = new WashingMachine(model, powerConsumption, serialNumber, loadCapacity);
            } else if (type == 2) {
                bool hasSensor;
                cin >> hasSensor;
                machines[i] = new DryingMachine(model, powerConsumption, serialNumber, hasSensor);
            }
        } catch (InvalidSerialNumberException &e) {
            e.showMessage();
            i--;
        }
    }
    return machines;
}

void calculatePercentageOfCost(Machine **machines, int n) {
    float totalCost = 0.0, washingMachinesCost = 0.0, dryingMachinesCost = 0.0;
    for (int i = 0; i < n; i++) {
        totalCost += machines[i]->calculateCost();
        (dynamic_cast<WashingMachine *>(machines[i])) != nullptr
            ? washingMachinesCost += machines[i]->calculateCost()
            : dryingMachinesCost += machines[i]->calculateCost();
    }
    cout << "The total cost of washing machines is " << washingMachinesCost << "$, which is " << (
        (washingMachinesCost / totalCost) * 100) << "% of the total cost of machines." << endl;
    cout << "The total cost of drying machines is " << dryingMachinesCost << "$, which is " << (
        (dryingMachinesCost / totalCost) * 100) << "% of the total cost of machines." << endl;
}

void cleanUp(Machine **machines, int n) {
    for (int i = 0; i < n; i++) {
        delete machines[i];
    }
    delete[]machines;
}

int main() {
    int testCase, n;
    cin >> testCase;


    switch (testCase) {
        case 1: {
            cout << "TESTING ABSTRACT CLASS AND CHILD CLASSES"
                    << endl;
            cin >> n;
            Machine **machines = createMachines(n);

            for (int i = 0; i < n; i++) {
                machines[i]->showDetails();
            }
            cleanUp(machines, n);
            cout << "ABSTRACT CLASS AND CHILD CLASSES OK" <<
                    endl;
            break;
        }
        case 2: {
            cout << "TEST EXCEPTION HANDLING" << endl;
            cin >> n;
            Machine **machines = createMachines(n);
            for (int i = 0; i < n; i++) {
                machines[i]->showDetails();
            }
            cleanUp(machines, n);
            cout << "EXCEPTION HANDLING OK" << endl;
            break;
        }
        default: {
            cout << "INTEGRATION TEST AND TESTING GLOBAL FUNCTION" << endl;
            cin >> n;
            Machine **machines = createMachines(n);
            for (int i = 0; i < n; i++) {
                machines[i]->showDetails();
            }
            calculatePercentageOfCost(machines, n);
            cleanUp(machines, n);
            cout << "INTEGRATION TEST AND TESTING GLOBAL FUNCTION OK " << endl;
            break;
        }
    }
}
