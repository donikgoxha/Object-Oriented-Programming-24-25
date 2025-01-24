#include<iostream>
#include<string.h>
using namespace std;

//your code here
class InvalidTimeException {
public:
    InvalidTimeException() = default;
};

class Race {
protected:
    char cityName[40];
    int year;
    int month;
    float bestTime;
    float length;

    void copy(const Race &r) {
        strcpy(this->cityName, r.cityName);
        this->year = r.year;
        this->month = r.month;
        this->bestTime = r.bestTime;
        this->length = r.length;
    }

public:
    Race(const char *cityName = "", int year = 0, int month = 0, float bestTime = 0.0, float length = 0.0) {
        strcpy(this->cityName, cityName);
        this->year = year;
        this->month = month;
        this->bestTime = bestTime;
        this->length = length;
    }

    Race(const Race &other) {
        copy(other);
    }

    Race &operator=(const Race &other) {
        if (this != &other) {
            copy(other);
        }
        return *this;
    }

    virtual float complexity() const {
        return bestTime / length;
    }

    friend ostream &operator<<(ostream &out, const Race &r) {
        out << r.cityName << " " << r.month << "." << r.year << " " << r.complexity() << endl;
        return out;
    }
};

class MotoGPRace : public Race {
private:
    float *bestTimes;
    int numTimes;
    int laps;
    static float coefficient;

public:
    MotoGPRace(const char *cityName = "", int year = 0, int month = 0, float bestTime = 0.0, float length = 0.0,
               float *bestTimes = nullptr, int numTimes = 0, int laps = 0) : Race(
        cityName, year, month, bestTime, length) {
        this->bestTimes = new float[numTimes];
        this->numTimes = numTimes;
        this->laps = laps;

        if (bestTimes) {
            for (int i = 0; i < numTimes; i++) {
                this->bestTimes[i] = bestTimes[i];
            }
        }
    }

    MotoGPRace(const MotoGPRace &other) : Race(other) {
        numTimes = other.numTimes;
        laps = other.laps;
        bestTimes = new float[numTimes];
        for (int i = 0; i < numTimes; i++) {
            bestTimes[i] = other.bestTimes[i];
        }
    }

    float complexity() const override {
        return (bestTime / length) * coefficient;
    }

    MotoGPRace &operator+=(float newTime) {
        if (newTime < 9.5) {
            throw InvalidTimeException();
        }

        float *tmp = new float[numTimes + 1];
        for (int i = 0; i < numTimes; i++) {
            tmp[i] = bestTimes[i];
        }
        tmp[numTimes] = newTime;
        delete[] bestTimes;
        bestTimes = tmp;
        numTimes++;
        return *this;
    }

    MotoGPRace &operator=(const MotoGPRace &other) {
        if (this != &other) {
            Race::operator=(other);
            delete[] bestTimes;
            numTimes = other.numTimes;
            laps = other.laps;
            bestTimes = new float[numTimes];
            for (int i = 0; i < numTimes; i++) {
                bestTimes[i] = other.bestTimes[i];
            }
        }
        return *this;
    }

    MotoGPRace operator++(int) {
        MotoGPRace temp(*this);
        laps++;
        return temp;
    }

    static void setK(float k) {
        coefficient = k;
    }

    int getNumberLaps() const {
        return laps;
    }

    void setNumberLaps(int numLaps) {
        laps = numLaps;
    }

    ~MotoGPRace() {
        delete[] bestTimes;
    }
};

float MotoGPRace::coefficient = 0.4;

int main() {
    int testCase;
    cin >> testCase;
    char city[50];
    int year;
    int month;
    float bestTime;
    float length;
    float bestTimes[50];
    int n;
    int m;
    int choice;
    int numberLaps;

    if (testCase == 1) {
        cout << "===== Testing - classes ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin >> length;
        Race t(city, year, month, bestTime, length);
        cout << t;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin >> length;
        cin >> numberLaps;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> bestTimes[j];
        MotoGPRace mgt(city, year, month, bestTime, length, bestTimes, n, numberLaps);
        cout << mgt;
        MotoGPRace mgt2;
    }
    if (testCase == 2) {
        cout << "===== Testing - operatorot += ======" << endl;
        Race **rArray;
        cin >> m;
        rArray = new Race *[m];
        for (int i = 0; i < m; i++) {
            cin >> choice;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >> length;
            if (choice == 1) {
                rArray[i] = new Race(city, year, month, bestTime, length);
            } else {
                cin >> numberLaps;
                cin >> n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                rArray[i] = new MotoGPRace(city, year, month, bestTime, length, bestTimes, n, numberLaps);
            }
        }
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];

        // add a new best time
        float best;
        cin >> best;
        int flag = 1;
        for (int i = 0; i < m; i++) {
            MotoGPRace *nn = dynamic_cast<MotoGPRace *>(rArray[i]);
            if (nn != 0) {
                flag = 0;
                (*nn) += best;
                break;
            }
        }

        // print the races
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
    }
    if (testCase == 3) {
        cout << "===== Testing - exceptions ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin >> length;
        cin >> numberLaps;
        MotoGPRace mgt(city, year, month, bestTime, length);
        mgt.setNumberLaps(numberLaps);
        float time1, time2;
        cin >> time1 >> time2;

        try {
            mgt += time1;
            mgt += time2;
        } catch (const InvalidTimeException &e) {
            cout << "Invalid Time" << endl;
        }

        cout << mgt;
    }
    if (testCase == 4) {
        cout << "===== Testing - operator++ ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin >> length;
        cin >> numberLaps;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> bestTimes[j];

        MotoGPRace mgt(city, year, month, bestTime, length, bestTimes, n, numberLaps);
        float v, koef2;
        cout << (mgt++).getNumberLaps() << endl;
        cout << mgt;
        mgt++;
        cout << mgt;
    }
    if (testCase == 5) {
        cout << "===== Testing - coefficient ======" << endl;
        Race **rArray;
        cin >> m;
        rArray = new Race *[m];
        for (int i = 0; i < m; i++) {
            cin >> choice;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >> length;
            if (choice == 1) {
                rArray[i] = new Race(city, year, month, bestTime, length);
            } else {
                cin >> numberLaps;
                cin >> n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                rArray[i] = new MotoGPRace(city, year, month, bestTime, length, bestTimes, n, numberLaps);
            }
        }
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];

        MotoGPRace::setK(0.7);
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
    }

    if (testCase == 6) {
        cout << "===== Testing - full functionality ======" << endl;
        Race **rArray;
        cin >> m;
        rArray = new Race *[m];
        for (int i = 0; i < m; i++) {
            cin >> choice;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >> length;
            if (choice == 1) {
                rArray[i] = new Race(city, year, month, bestTime, length);
            } else {
                cin >> numberLaps;
                cin >> n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                rArray[i] = new MotoGPRace(city, year, month, bestTime, length, bestTimes, n, numberLaps);
            }
        }
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
        float newCoef;
        cin >> newCoef;
        MotoGPRace::setK(newCoef);
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
        // print the races
        float newBest;
        cin >> newBest;
        int flag = 1;
        for (int i = 0; i < m; i++) {
            MotoGPRace *pok = dynamic_cast<MotoGPRace *>(rArray[i]);
            if (pok != 0) {
                (*pok)++;
                (*pok) += newBest;
                if (flag == 1) {
                    flag = 0;
                    *pok += 1.4;
                }
            }
        }
        cout << "\nList of the races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
    }

    return 0;
}
