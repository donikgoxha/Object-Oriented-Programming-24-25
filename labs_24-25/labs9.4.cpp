// Да се креира класа VehicleRegistration во кој се чува податоци за едно возило. Класата треба да ги содржи следните аргументи:
// string registration_number;
// string manufacture_date;
// int mileage;
// int engine_power;
// int vehicle_age;
// double emission_level;
// Потребно е да се имплементираат:
// Default конструктор
// Конструктор со параметри
// Copy конструктор
// Оператор =
// Оператор за читање istream>>
// Оператор за печатење ostream<< во следниот формат
// Vehicle Reg: <registration_number> <manufacture_date> | Mileage <mileage>km Power <engine_power>hp
// Age <vehicle_age>y Emission <emission_level>g/km
// Функцијата string VehicleCategory() која ги категоризира возилата во три категории: Restricted, Limited и Approved:
// Restricted - mileage > 250000 или vehicle_age > 20 или emission_level > 120.0 или engine_power < 60
// Limited - mileage > 150000 или vehicle_age > 15 или emission_level > 90.0 или engine_power < 80
// Approved - сите останати
// Да се напише глобалната функција FilterByVehicleCategory() која прима низа од VehicleRegistration,
// број на елементи и string категорија. Како резултат функцијата враќа нова динамички алоцирана низа
// која ги содржи само возилата од дадената категорија.
// Податоците се дадени во датотеката text.txt во форматот: прв ред - број на test case, втор ред - број на елементи,
// секој следен ред содржи податоци за едно возило (за читање на податоци за едно возило користете го
// istream операторот од класата).
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

class VehicleRegistration {
private:
    string registration_number;
    string manufacture_date;
    int mileage;
    int engine_power;
    int vehicle_age;
    double emission_level;

    void copy(const VehicleRegistration &other) {
        this->registration_number = other.registration_number;
        this->manufacture_date = other.manufacture_date;
        this->mileage = other.mileage;
        this->engine_power = other.engine_power;
        this->vehicle_age = other.vehicle_age;
        this->emission_level = other.emission_level;
    }

public:
    VehicleRegistration(const string &registration_number = "", const string &manufacture_date = "", int mileage = 0,
                        int engine_power = 0, int vehicle_age = 0, double emission_level = 0.0) {
        this->registration_number = registration_number;
        this->manufacture_date = manufacture_date;
        this->mileage = mileage;
        this->engine_power = engine_power;
        this->vehicle_age = vehicle_age;
        this->emission_level = emission_level;
    }

    VehicleRegistration(const VehicleRegistration &other) {
        copy(other);
    }

    VehicleRegistration &operator=(const VehicleRegistration &other) {
        if (this != &other) {
            copy(other);
        }
        return *this;
    }

    friend istream &operator>>(istream &in, VehicleRegistration &v) {
        in >> v.registration_number >> v.manufacture_date >> v.mileage >> v.engine_power >> v.vehicle_age >> v.
                emission_level;
        return in;
    }

    friend ostream &operator<<(ostream &out, const VehicleRegistration &v) {
        out << "Vehicle Reg: " << v.registration_number << " " << v.manufacture_date
                << " | Mileage " << v.mileage << "km Power " << v.engine_power << "hp Age "
                << v.vehicle_age << "y Emission " << v.emission_level << "g/km" << endl;
        return out;
    }

    string VehicleCategory() const {
        if (mileage > 250000 || vehicle_age > 20 || emission_level > 120.0 || engine_power < 60) {
            return "Restricted";
        } else if (mileage > 150000 || vehicle_age > 15 || emission_level > 90.0 || engine_power < 80) {
            return "Limited";
        }
        return "Approved";
    }
};

VehicleRegistration *FilterByVehicleCategory(VehicleRegistration *arr, int n, string category) {
    VehicleRegistration *filtered = new VehicleRegistration[n];
    int idx = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i].VehicleCategory() == category) {
            filtered[idx++] = arr[i];
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

    // TODO: Вчитајте податоци од датотека (број на тест примери (testCase), број на записи (n) и податоци)
    int testCase, n;
    fin >> testCase;
    fin >> n;

    // Остатокот од кодот останува непроменет

    VehicleRegistration *records = new VehicleRegistration[n];
    for (int i = 0; i < n; i++) {
        fin >> records[i];
    }

    if (testCase == 1) {
        cout << "===== Testing Constructor, Istream Operator & Ostream Operator =====" << endl;
        for (int i = 0; i < n; i++) {
            cout << records[i];
        }
    }

    if (testCase == 2) {
        cout << "===== Testing VehicleCategory Function =====" << endl;
        for (int i = 0; i < n; i++) {
            cout << records[i].VehicleCategory() << endl;
        }
    }

    if (testCase == 3) {
        cout << "===== Testing FilterByVehicleCategory Global Function =====" << endl;
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (records[i].VehicleCategory() == "Approved") {
                count++;
            }
        }
        VehicleRegistration *filtered = FilterByVehicleCategory(records, n, "Approved");
        cout << "Approved Vehicles:" << endl;
        for (int i = 0; i < count; i++) {
            cout << filtered[i];
        }
        delete[] filtered;
    }

    if (testCase == 4) {
        cout << "===== Testing FilterByVehicleCategory Global Function =====" << endl;
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (records[i].VehicleCategory() == "Limited") {
                count++;
            }
        }
        VehicleRegistration *filtered = FilterByVehicleCategory(records, n, "Limited");
        cout << "Limited Vehicles:" << endl;
        for (int i = 0; i < count; i++) {
            cout << filtered[i];
        }
        delete[] filtered;
    }

    if (testCase == 5) {
        cout << "===== Testing FilterByVehicleCategory Global Function =====" << endl;
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (records[i].VehicleCategory() == "Restricted") {
                count++;
            }
        }
        VehicleRegistration *filtered = FilterByVehicleCategory(records, n, "Restricted");
        cout << "Restricted Vehicles:" << endl;
        for (int i = 0; i < count; i++) {
            cout << filtered[i];
        }
        delete[] filtered;
    }

    delete[] records;
    return 0;
}
