#include <iostream>
#include <cstring>
using namespace std;

class InvalidTimeException {
public:
    void message() {
        cout << "Invalid Time" << endl;
    }
};


class Race {
protected:
    char city[41];
    int year;
    int month;
    float bestTime;
    float length;

    void copy(const Race &r) {
        strcpy(this->city, r.city);
        this->year = r.year;
        this->month = r.month;
        this->bestTime = r.bestTime;
        this->length = r.length;
    }

public:
    Race(const char *city = "", int year = 0, int month = 01, float bestTime = 0.0, float length = 0.0) {
        strcpy(this->city, city);
        this->year = year;
        this->month = month;
        this->bestTime = bestTime;
        this->length = length;
    }

    Race(const Race &r) {
        copy(r);
    }

    Race &operator=(const Race &r) {
        if (this != &r) {
            copy(r);
        }
        return *this;
    }

    virtual float complexity() const {
        return bestTime / length;
    }

    friend ostream &operator<<(ostream &out, const Race &r) {
        out << r.city << " " << r.month << "." << r.year << " " << r.complexity() << endl;
    }
};

class MotoGPRace : public Race {
private:
    float *bestTimesPrep;
    int numBestTimes;
    int laps;
    static float K;

    void copy(const MotoGPRace &r) {
        this->numBestTimes = r.numBestTimes;
        this->bestTimesPrep = new float[r.numBestTimes];
        for (int i = 0; i < r.numBestTimes; i++) {
            this->bestTimesPrep[i] = r.bestTimesPrep[i];
        }
        this->laps = r.laps;
    }

public:
    MotoGPRace(const char *city = "", int year = 0, int month = 01, float bestTime = 0.0, float length = 0.0,
               float *bestTimesPrep = nullptr, int numBestTimes = 0, int laps = 0) : Race(
        city, year, month, bestTime, length) {
        this->numBestTimes = numBestTimes;
        this->laps = laps;
        this->bestTimesPrep = new float[numBestTimes];
        for (int i = 0; i < numBestTimes; i++) {
            this->bestTimesPrep[i] = bestTimesPrep[i];
        }
    }

    MotoGPRace(const MotoGPRace &r) : Race(r) {
        copy(r);
    }

    MotoGPRace &operator=(const MotoGPRace &r) {
        if (this != &r) {
            delete [] bestTimesPrep;
            Race::operator=(r);
            copy(r);
        }
        return *this;
    }

    ~MotoGPRace() {
        delete [] bestTimesPrep;
    }

    float complexity() const override {
        float base = Race::complexity();
        float average = 0.0;
        for (int i = 0; i < numBestTimes; i++) {
            average += this->bestTimesPrep[i];
        }
        if (numBestTimes > 0) {
            average /= numBestTimes;
        }
        base += average * K;
        if (laps > 22)
            base *= 1.2;
        return base;
    }

    MotoGPRace &operator+=(float newTime) {
        if (newTime < 9.5) {
            throw InvalidTimeException();
        }
        float *tmp = new float[numBestTimes + 1];
        for (int i = 0; i < numBestTimes; i++) {
            tmp[i] = bestTimesPrep[i];
        }
        tmp[numBestTimes++] = newTime;
        delete[] bestTimesPrep;
        bestTimesPrep = tmp;
        return *this;
    }

    MotoGPRace operator++(int) {
        MotoGPRace temp = *this;
        laps++;
        return temp;
    }

    int getNumberLaps() const {
        return laps;
    }

    void setNumberLaps(int l) {
        laps = l;
    }

    static void setK(float newK) {
        K = newK;
    }

    friend ostream &operator<<(ostream &out, const MotoGPRace &r) {
        out << r.city << " " << r.month << "." << r.year << " " << r.complexity() << endl;
        return out;
    }
};


float MotoGPRace::K = 0.4;
//your code here

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
        } catch (InvalidTimeException &e) {
            e.message();
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
                    try {
                        *pok += 1.4;
                    } catch (InvalidTimeException &e) {
                        e.message();
                    }
                }
            }
        }
        cout << "\nList of the races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
    }

    return 0;
}
