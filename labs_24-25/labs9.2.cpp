// Да се креира класа WeatherData во која се чуваат податоци за временските услови за различни локации.
// Класата треба да ги содржи следните атрибути:
// string location_id; - Единствен идентификатор за локацијата
// string timestamp; - Кога се снимени временските податоци
// double temperature; - Температура во Целзиусови степени
// int humidity; - Процент на влажност
// double wind_speed; - Брзина на ветер во км/ч
// int precipitation; - Врнежи во милиметри
// Потребно е да се имплементираат:
// Default конструктор
// Конструктор со параметри
// Copy конструктор
// Оператор за доделување (=)
// Оператор за читање од влезен поток (>>)
// Оператор за печатење (<<) во следниот формат:
// Weather at location: <location_id>
// <timestamp> | Temp: <temperature>°C Humidity: <humidity>% Wind: <wind_speed> km/h Precip: <precipitation> mm
// Функцијата string WeatherAlert() која ги категоризира временските услови во три категории:
// Severe - temperature > 35.0 или temperature < -10.0 или humidity > 90 или wind_speed > 30.0 или precipitation > 50
// Warning - temperature > 30.0 или temperature < 0.0 или humidity > 80 или wind_speed > 20.0 или precipitation > 30
// Normal - сите останати услови
// Да се напише глобалната функција FilterByAlertLevel() која прима низа од WeatherData објекти,
// број на елементи и string параметар за нивото на алармирање. Како резултат функцијата враќа нова динамички
// алоцирана низа која ги содржи само временските податоци со специфицираното ниво на алармирање.
// Податоците се дадени во датотеката text.txt во форматот: прв ред - број на test case, втор ред - број на елементи,
// секој следен ред содржи податоци за една временска станица (за читање на податоци за една станица
// користете го istream операторот од класата).
// На почетокот во main() каде што има TO DO да се вчитаат потребните податоци од датотека.
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
using namespace std;


void writeToFile() {
    ofstream file("text.txt");
    char c;
    while ((c = cin.get()) != '#') {
        file.put(c);
    }
    file.close();
}

class WeatherData {
private:
    string location_id;
    string timestamp;
    double temperature;
    int humidity;
    double wind_speed;
    int precipitation;

    void copy(const WeatherData &other) {
        this->location_id = other.location_id;
        this->timestamp = other.timestamp;
        this->temperature = other.temperature;
        this->humidity = other.humidity;
        this->wind_speed = other.wind_speed;
        this->precipitation = other.precipitation;
    }

public:
    WeatherData(const string &location_id = "", const string &timestamp = "", double temperature = 0.0,
                int humidity = 0, double wind_speed = 0.0, int precipitation = 0) {
        this->location_id = location_id;
        this->timestamp = timestamp;
        this->temperature = temperature;
        this->humidity = humidity;
        this->wind_speed = wind_speed;
        this->precipitation = precipitation;
    }

    WeatherData(const WeatherData &other) {
        copy(other);
    }

    WeatherData &operator=(const WeatherData &other) {
        if (this != &other) {
            copy(other);
        }
        return *this;
    }

    friend istream &operator>>(istream &in, WeatherData &w) {
        in >> w.location_id >> w.timestamp >> w.temperature >> w.humidity >> w.wind_speed >> w.precipitation;
        return in;
    }

    friend ostream &operator<<(ostream &out, const WeatherData &w) {
        out << "Weather at location: " << w.location_id << endl;
        out << w.timestamp << " | Temp: " << w.temperature << "°C Humidity: " << w.humidity
                << "% Wind: " << w.wind_speed << " km/h Precip: " << w.precipitation << " mm" << endl;
        return out;
    }

    string WeatherAlert() const {
        if (temperature > 35.0 || temperature < -10.0 || humidity > 90 ||
            wind_speed > 30.0 || precipitation > 50) {
            return "Severe";
        } else if (temperature > 30.0 || temperature < 0.0 || humidity > 80 ||
                   wind_speed > 20.0 || precipitation > 30) {
            return "Warning";
        }
        return "Normal";
    }
};

WeatherData *FilterByAlertLevel(WeatherData *data, int n, string level) {
    WeatherData *filtered = new WeatherData[n];
    int idx = 0;
    for (int i = 0; i < n; ++i) {
        if (data[i].WeatherAlert() == level) {
            filtered[idx++] = data[i];
        }
    }
    return filtered;
}


int main() {
    writeToFile();
    ifstream fin("text.txt");
    if (!fin) {
        std::cerr << "Cannot open file\n";
        return 1;
    }

    // TO DO: Вчитајте податоци од датотека (број на тест примери (testCase), број на WeatherData записи (n) и податоци за WeatherData)
    int testCase, n;

    fin >> testCase;
    fin >> n;

    WeatherData *records = new WeatherData[n];
    for (int i = 0; i < n; ++i) {
        fin >> records[i];
    }

    // Остатокот од кодот останува непроменет

    if (testCase == 1) {
        cout << "===== Testing Constructor, Istream Operator & OstreamOperator =====" << endl;
        for (int i = 0; i < n; i++) {
            cout << records[i];
        }
    }

    if (testCase == 2) {
        cout << "===== Testing WeatherAlert Function =====" << endl;
        for (int i = 0; i < n; i++) {
            cout << records[i].WeatherAlert() << endl;
        }
    }
    if (testCase == 3) {
        cout << "===== Testing FilterByAlertLevel Global Function =====" << endl;
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (records[i].WeatherAlert() == "Normal") {
                count++;
            }
        }
        WeatherData *filtered = FilterByAlertLevel(records, n, "Normal");
        cout << "Normal Weather Conditions:" << endl;
        for (int i = 0; i < count; i++) {
            cout << filtered[i];
        }
        delete[] filtered;
    }

    if (testCase == 4) {
        cout << "===== Testing FilterByAlertLevel Global Function =====" << endl;
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (records[i].WeatherAlert() == "Warning") {
                count++;
            }
        }
        WeatherData *filtered = FilterByAlertLevel(records, n, "Warning");
        cout << "Warning Weather Conditions:" << endl;
        for (int i = 0; i < count; i++) {
            cout << filtered[i];
        }
        delete[] filtered;
    }

    if (testCase == 5) {
        cout << "===== Testing FilterByAlertLevel Global Function =====" << endl;
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (records[i].WeatherAlert() == "Severe") {
                count++;
            }
        }
        WeatherData *filtered = FilterByAlertLevel(records, n, "Severe");
        cout << "Severe Weather Conditions:" << endl;
        for (int i = 0; i < count; i++) {
            cout << filtered[i];
        }
        delete[] filtered;
    }

    delete[] records;
    return 0;
}
