/*
Да се креира апстрактна класа Sensor која ги моделира сите сензори во една дистрибуирана средина.
Класата треба да содржи два виртуелни методи:
float calculateReadingWeight() - пресметка на важност на податокот
void print() - ги печати сите информации за сензорот
Податоци кои треба да се чуваат за сензорот:
име на сензор - string
основна важност на податокот од сензорот - float
ID на сензорот, кој ќе биде генериран автоматски за секој нов сензор
Потребно е да се изведат две класи: TemperatureSensor и MotionSensor
За класата TemperatureSensor потребно е да се додадат следниве информации:
точност на мерење - float (процент)
дали е калибриран - boolean
Пресметка на важност: Доколку сензорот има точност на мерење поголем од 90%, се додава 0.1.
Доколку е калибриран се додава 0.3. Доколку точноста е поголема од 90% и е калибриран се додава 0.5.
Формат на функцијата за печатење:
ID: [ID]
Name: [име на сензор]
Calculation: [пресметаната важност]
За класата MotionSensor потребно е да се додадат следниве информации:
опсег на детекција - float (метри)
низа од датуми на калибрација - динамички алоцирана низа од објекти од тип Date
(да се креира функција void addDate(Date date))
Пресметка на важност: Доколку сензорот има опсег на детекција помал од 10м, се додава 0.2.
Доколку сензорот бил редовно калибриран на помалку од 3 дена, тогаш се додава 0.5.
Формат на функцијата за печатење:
ID: [ID]
Name: [име на сензор]
Calculation: [пресметаната важност]
Last date of calibration: [последен датум на калибрација] - овој ред се печати само доколку има додадено датуми
Да се дефинира глобална функција која Sensor *highestReadingWeight(Sensor **sensors, int n) која ќе го врати сензорот
со највисока важност на податок.
 */

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Date {
private:
    int day;
    int month;
    int year;

    void copy(const Date &d) {
        this->day = d.day;
        this->month = d.month;
        this->year = d.year;
    }

public:
    Date(int day = 0, int month = 0, int year = 0) {
        this->day = day;
        this->month = month;
        this->year = year;
    }

    static int date_difference(Date d1, Date d2) {
        int d1_total_days = d1.year * 365 + d1.month * 30 + d1.day;
        int d2_total_days = d2.year * 365 + d2.month * 30 + d2.day;
        return abs(d1_total_days - d2_total_days);
    }

    Date(const Date &o) {
        copy(o);
    }

    Date &operator=(const Date &o) {
        if (this != &o) {
            copy(o);
        }
        return *this;
    }

    friend istream &operator>>(istream &in, Date &d) {
        char sep;
        in >> d.day;
        in >> sep;
        in >> d.month;
        in >> sep;
        in >> d.year;
        return in;
    }

    friend ostream &operator<<(ostream &out, const Date &d) {
        out << d.day << "/" << d.month << "/" << d.year;
        return out;
    }
};

class Sensor {
protected:
    string name;
    float baseReadingWeight;
    static int idCounter;
    int id;

public:
    Sensor(const string &name, float baseReadingWeight) {
        this->name = name;
        this->baseReadingWeight = baseReadingWeight;
        id = ++idCounter;
    }

    virtual ~Sensor() {
    }

    virtual float calculateReadingWeight() = 0;

    virtual void print() = 0;

    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }
};

int Sensor::idCounter = 0;

class TemperatureSensor : public Sensor {
private:
    float accuracy;
    bool isCalibrated;

public:
    TemperatureSensor(string name, float baseReadingWeight, float accuracy, bool isCalibrated)
        : Sensor(name, baseReadingWeight) {
        this->accuracy = accuracy;
        this->isCalibrated = isCalibrated;
    }

    float calculateReadingWeight() override {
        float weight = baseReadingWeight;

        if (accuracy > 90 && isCalibrated) {
            weight += 0.5;
        } else {
            if (accuracy > 90) {
                weight += 0.1;
            }
            if (isCalibrated) {
                weight += 0.3;
            }
        }

        return weight;
    }

    void print() override {
        cout << "ID: " << getId() << endl;
        cout << "Name: " << getName() << endl;
        cout << "Calculation: " << calculateReadingWeight() << endl;
    }
};

class MotionSensor : public Sensor {
private:
    float detectionRange;
    Date *calibrationDates;
    int numDates;

public:
    MotionSensor(string name, float baseReadingWeight, float detectionRange, Date *dates, int numDates)
        : Sensor(name, baseReadingWeight), detectionRange(detectionRange), numDates(numDates) {
        if (numDates > 0 && dates != nullptr) {
            calibrationDates = new Date[numDates];
            for (int i = 0; i < numDates; i++) {
                calibrationDates[i] = dates[i];
            }
        } else {
            calibrationDates = nullptr;
            this->numDates = 0;
        }
    }

    ~MotionSensor() {
        delete[] calibrationDates;
    }

    void addDate(Date date) {
        Date *temp = new Date[numDates + 1];
        for (int i = 0; i < numDates; i++) {
            temp[i] = calibrationDates[i];
        }
        temp[numDates] = date;

        delete[] calibrationDates;
        calibrationDates = temp;
        numDates++;
    }

    float calculateReadingWeight() override {
        float weight = baseReadingWeight;

        if (detectionRange < 10) {
            weight += 0.2;
        }

        if (numDates >= 2) {
            bool regularlyCalibrated = true;
            for (int i = 1; i < numDates; i++) {
                if (Date::date_difference(calibrationDates[i], calibrationDates[i - 1]) >= 3) {
                    regularlyCalibrated = false;
                    break;
                }
            }

            if (regularlyCalibrated) {
                weight += 0.5;
            }
        }

        return weight;
    }

    void print() override {
        cout << "ID: " << getId() << endl;
        cout << "Name: " << getName() << endl;
        cout << "Calculation: " << calculateReadingWeight() << endl;
        if (numDates > 0) {
            cout << "Last date of calibration: " << calibrationDates[numDates - 1] << endl;
        }
    }
};

Sensor *highestReadingWeight(Sensor **sensors, int n) {
    if (n <= 0 || sensors == nullptr) {
        return nullptr;
    }

    Sensor *highest = sensors[0];
    float maxWeight = highest->calculateReadingWeight();

    for (int i = 1; i < n; i++) {
        float weight = sensors[i]->calculateReadingWeight();
        if (weight > maxWeight) {
            maxWeight = weight;
            highest = sensors[i];
        }
    }

    return highest;
}

int main() {
    int tc;
    cin >> tc;

    if (tc == 1) {
        cout << "Testing TemperatureSensor " << endl;
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            string name;
            float baseReadingWeight;
            int accuracy;
            bool isCalibrated;
            cin >> name >> baseReadingWeight >> accuracy >> isCalibrated;

            TemperatureSensor *ts = new TemperatureSensor(name, baseReadingWeight, accuracy, isCalibrated);
            ts->print();
            delete ts;
        }
    } else if (tc == 2) {
        cout << "Testing MotionSensor " << endl;
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            string name;
            float baseReadingWeight;
            int range;
            int m;
            cin >> name >> baseReadingWeight >> range >> m;

            Sensor *ms = new MotionSensor(name, baseReadingWeight, range, nullptr, 0);

            if (m > 0) {
                for (int j = 0; j < m; j++) {
                    Date date;
                    cin >> date;
                    ((MotionSensor *) ms)->addDate(date);
                }
            }

            ms->print();
            delete ms;
        }
    } else if (tc == 3) {
        cout << "Testing Dynamic Allocation" << endl;
        int n;
        cin >> n;
        Sensor **sensors = new Sensor *[n];

        for (int i = 0; i < n; i++) {
            string name;
            float baseReadingWeight;
            int range;
            int m;
            cin >> name >> baseReadingWeight >> range >> m;

            sensors[i] = new MotionSensor(name, baseReadingWeight, range, nullptr, 0);

            if (m > 0) {
                for (int j = 0; j < m; j++) {
                    Date date;
                    cin >> date;
                    ((MotionSensor *) sensors[i])->addDate(date);
                }
            }
        }

        Sensor *highest = highestReadingWeight(sensors, n);
        if (highest != nullptr) {
            cout << "Sensor with highest reading weight:" << endl;
            highest->print();
        }

        // Cleanup
        for (int i = 0; i < n; i++) {
            delete sensors[i];
        }
        delete[] sensors;
    }

    return 0;
}
