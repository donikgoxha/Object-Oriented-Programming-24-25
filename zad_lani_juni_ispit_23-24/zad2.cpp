#include <iostream>
#include <cstring>
#include <iomanip>
#include <stdexcept>

using namespace std;

class InvalidCodeFormatException {
private:
    string code;

public:
    InvalidCodeFormatException(const string &code = "") {
        this->code = code;
    }

    void print() const {
        cout << "The code " << code
                << " is invalid doctor code format. THE CODE MUST BE 8 CHARACTERS LONG AND CANNOT CONTAIN COMMA." <<
                endl;
    }
};

class Doctor {
protected:
    string name;
    string lastName;
    string code;

    void validateCode(const string &code) {
        if (code.length() != 8 || code.find(',') != string::npos) {
            throw InvalidCodeFormatException(code);
        }
    }

    void copy(const Doctor &doctor) {
        this->name = doctor.name;
        this->lastName = doctor.lastName;
        this->code = doctor.code;
    }

public:
    Doctor(const string &name = "", const string &lastName = "", const string &code = "") {
        this->name = name;
        this->lastName = lastName;
        validateCode(code);
        this->code = code;
    }

    Doctor(const Doctor &doctor) {
        copy(doctor);
    }

    Doctor &operator=(const Doctor &doctor) {
        if (this != &doctor) {
            copy(doctor);
        }
        return *this;
    }

    virtual ~Doctor() {
    }

    virtual float calculateSalary() const = 0;

    virtual void print() const = 0;
};

class GeneralDoctor : public Doctor {
private:
    int numPatients;

public:
    GeneralDoctor(const string &name = "", const string &lastName = "", const string &code = "",
                  int numPatients = 0): Doctor(name, lastName, code) {
        this->numPatients = numPatients;
    }

    float calculateSalary() const override {
        float base = 45000;
        int bonusBlocks = numPatients / 10;
        float bonus = bonusBlocks * 3000;
        float gross = base + bonus;
        return gross * 0.93;
    }

    void print() const override {
        cout << "General Doctor: " << name << " " << lastName << " CODE:" << code << " Salary: " << calculateSalary()
                << endl;
    }
};

class Specialist : public Doctor {
private:
    string specialty;
    int interventions;
    int years;

public:
    Specialist(const string &name = "", const string &lastName = "", const string &code = "",
               const string &specialty = "", int interventions = 0, int years = 0): Doctor(name, lastName, code) {
        this->specialty = specialty;
        this->interventions = interventions;
        this->years = years;
    }

    float calculateSalary() const override {
        float base = 55000;
        float interventionBonus = interventions * 85;
        float experienceBonus = base * 0.05f * years;
        float gross = base + interventionBonus + experienceBonus;
        return gross * 0.93f; // 7% tax
    }

    void print() const override {
        cout << "Specialist: " << name << " " << lastName << " CODE:" << code << " " << specialty <<
                " Salary: " << calculateSalary() << endl;
    }
};

void findDoctorsPercentage(Doctor **doctors, int n) {
    int specialists = 0;
    int generals = 0;
    for (int i = 0; i < n; i++) {
        if (dynamic_cast<Specialist *>(doctors[i]))
            specialists++;
        else if (dynamic_cast<GeneralDoctor *>(doctors[i]))
            generals++;
    }
    float total = n;

    cout << (specialists / total) * 100 << "%" << " of the doctors are specialists and " << (generals / total) * 100 <<
            "%" << " are general doctors." << endl;
}


int main() {
    int testCase, n;
    string name, surname, specialty, code;
    int numberOfPatients, yearsOfExperience, numberOfInterventions;
    cin >> testCase;

    if (testCase == 1) {
        cout << "TESTING GENERAL DOCTOR CLASS" << endl;
        Doctor *d = new GeneralDoctor("John", "Smith", "236XY@2B", 120);
        Doctor *d1 = new GeneralDoctor("Marco", "Brown", "345X!Y2B", 120);
        Doctor *d2 = new GeneralDoctor("Emily", "Johnson", "ABCD123@", 230);
        d->print();
        d1->print();
        d2->print();

        cout << "GENERAL DOCTOR CLASS OK!" << endl;
    } else if (testCase == 2) {
        cout << "TESTING SPECIALIST DOCTOR CLASS" << endl;
        Doctor *d = new Specialist("Beth", "Davis", "96Tr$$33", "Cardiologist", 45, 5);
        Doctor *d1 = new Specialist("William", "Wilson", "785#Qy2B", "Pulmonologist", 50, 7);
        Doctor *d2 = new Specialist("Micheal", "Rosen", "7896YZ$s", "Radiologist", 41, 10);
        d->print();
        d1->print();
        d2->print();
        cout << "SPECIALIST DOCTOR CLASS OK!" << endl;
    } else if (testCase == 3) {
        cout << "TESTING EXCEPTION HANDLING" << endl;
        try {
            Doctor *d = new GeneralDoctor("John", "Smith", "23Y@2B", 120);
            d->print();
        } catch (InvalidCodeFormatException &e) {
            e.print();
        }

        cout << "EXCEPTION HANDLING OK!" << endl;
    } else if (testCase == 4) {
        cout << "TESTING EXCEPTION HANDLING" << endl;
        try {
            Doctor *d = new Specialist("Beth", "Davis", "9,R$$334", "Cardiologist", 45, 5);
            d->print();
        } catch (InvalidCodeFormatException &e) {
            e.print();
        }
        cout << "EXCEPTION HANDLING OK!" << endl;
    } else if (testCase == 5) {
        cout << "TESTING EXCEPTION HANDLING" << endl;
        try {
            Doctor *d = new Specialist("Beth", "Davis", "9,R$$334", "Cardiologist", 45, 5);
            d->print();
        } catch (InvalidCodeFormatException &e) {
            e.print();
        }

        Doctor *d1 = new Specialist("William", "Wilson", "785#Qy2B", "Pulmonologist", 50, 7);
        d1->print();

        try {
            Doctor *d2 = new Specialist("Beth", "Davis", "96Tr,", "Cardiologist", 45, 5);
            d2->print();
        } catch (InvalidCodeFormatException &e) {
            e.print();
        }

        cout << "EXCEPTION HANDLING OK!" << endl;
    } else {
        cout << "INTEGRATION TEST AND TESTING GLOBAL FUNCTION!" << endl;
        cin >> n;
        Doctor **doctors = new Doctor *[n];
        int validCount = 0;
        for (int i = 0; i < n; i++) {
            int t;
            cin >> t;
            cin >> name >> surname;
            cin >> code;
            try {
                if (t == 1) // General doctor
                {
                    cin >> numberOfPatients;

                    doctors[validCount++] = new GeneralDoctor(name, surname, code, numberOfPatients);
                } else // Specialist
                {
                    cin >> specialty;
                    cin >> numberOfInterventions >> yearsOfExperience;

                    doctors[validCount++] = new Specialist(name, surname, code, specialty, numberOfInterventions,
                                                           yearsOfExperience);
                }
            } catch (InvalidCodeFormatException &e) {
                e.print();
            }
        }
        cout << "LIST OF ALL DOCTORS: " << endl;
        for (int i = 0; i < validCount; i++) {
            doctors[i]->print();
        }
        findDoctorsPercentage(doctors, validCount);
        for (int i = 0; i < validCount; i++) {
            delete doctors[i];
        }
        delete[] doctors;
    }
    return 0;
}
