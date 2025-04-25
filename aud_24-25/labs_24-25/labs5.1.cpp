/*
Write a class Automobile to store information about the Brand of the automobile (dynamically allocated character array),
Registration (dynamically allocated array of 5 integers), and Maximum Speed (an integer). For the class, provide
appropriate set and get methods and overload the following operators:

(1) Operator == for comparing two automobiles by their registration and

(2) Operator << for printing the automobile details in the format Marka:brand Registracija:[x y z k l].

Write a class RentACar for a vehicle rental agency that stores the Agency name (a character array of 100 characters),
Array of automobiles (dynamically allocated array of Automobile objects), and Number of automobiles (an integer).
The RentACar class should include a constructor with one argument to initialize the agency name. For every new
automobile added, the dynamically allocated array should increase its capacity by 1 element.
Overload the following operators:
(1) Operator += for adding a new automobile to the agency and
(2) Operator -= for removing an automobile from the agency (the one with the same registration).
In the main function, instantiate an object of the RentACar class. Automobiles should be added to the agency by
reading information from the keyboard using the += operator. If a new automobile is attempted to be added but its
registration already exists, remove the previously added automobile with the same registration
and add the new one instead.

Print the agency's name and the list of automobiles that the agency rents out, filtered by those with a maximum
speed greater than 150. Use the function pecatiNadBrzina(int max) defined in the RentACar class to achieve this.

Input

3
Opel 4 5 6 7 4 200
Toyota 2 3 4 1 2 120
Audi 1 2 1 1 1 130
Suzuki 1 2 1 1 1 100

Result

FINKI-Car
Marka	Opel	Registracija[ 4 5 6 7 4 ]
 */
#include <iostream>
#include <cstring>
using namespace std;

class Automobile {
private:
    char *brand;
    int *registration;
    int maxSpeed;

public:
    Automobile(const char *brand = "", int *registration = nullptr, int maxSpeed = 0) {
        this->brand = new char[strlen(brand) + 1];
        strcpy(this->brand, brand);

        this->registration = new int[5];
        if (registration) {
            for (int i = 0; i < 5; i++) {
                this->registration[i] = registration[i];
            }
        }

        this->maxSpeed = maxSpeed;
    }

    Automobile(const Automobile &other) {
        brand = new char[strlen(other.brand) + 1];
        strcpy(brand, other.brand);

        registration = new int[5];
        for (int i = 0; i < 5; i++) {
            registration[i] = other.registration[i];
        }

        maxSpeed = other.maxSpeed;
    }

    Automobile &operator=(const Automobile &other) {
        if (this != &other) {
            delete[] brand;
            delete[] registration;

            brand = new char[strlen(other.brand) + 1];
            strcpy(brand, other.brand);

            registration = new int[5];
            for (int i = 0; i < 5; i++) {
                registration[i] = other.registration[i];
            }

            maxSpeed = other.maxSpeed;
        }
        return *this;
    }

    ~Automobile() {
        delete[] brand;
        delete[] registration;
    }

    int getMaxSpeed() const {
        return maxSpeed;
    }

    bool operator==(const Automobile &other) const {
        for (int i = 0; i < 5; i++) {
            if (registration[i] != other.registration[i])
                return false;
        }
        return true;
    }

    friend ostream &operator<<(ostream &os, const Automobile &a) {
        os << "Marka\t" << a.brand << "\tRegistracija[ ";
        for (int i = 0; i < 5; i++) {
            os << a.registration[i] << " ";
        }
        os << "]";
        return os;
    }
};

class RentACar {
private:
    char name[100];
    Automobile *autos;
    int numAutos;

public:
    RentACar(const char *name) {
        strcpy(this->name, name);
        autos = nullptr;
        numAutos = 0;
    }

    ~RentACar() {
        delete[] autos;
    }

    RentACar &operator+=(const Automobile &newAuto) {
        for (int i = 0; i < numAutos; i++) {
            if (autos[i] == newAuto) {
                autos[i] = newAuto;
                return *this;
            }
        }

        Automobile *temp = new Automobile[numAutos + 1];
        for (int i = 0; i < numAutos; i++) {
            temp[i] = autos[i];
        }
        temp[numAutos++] = newAuto;
        delete[] autos;
        autos = temp;
        return *this;
    }

    RentACar &operator-=(const Automobile &toRemove) {
        for (int i = 0; i < numAutos; i++) {
            if (autos[i] == toRemove) {
                Automobile *temp = new Automobile[numAutos - 1];
                for (int j = 0, k = 0; j < numAutos; j++) {
                    if (j != i) temp[k++] = autos[j];
                }
                delete[] autos;
                autos = temp;
                numAutos--;
                break;
            }
        }
        return *this;
    }

    void pecatiNadBrzina(int max) const {
        cout << name << endl;
        for (int i = 0; i < numAutos; i++) {
            if (autos[i].getMaxSpeed() > max) {
                cout << autos[i] << endl;
            }
        }
    }
};


int main() {
    RentACar agencija("FINKI-Car");
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        char marka[100];
        int regisracija[5];
        int maximumBrzina;

        cin >> marka;

        for (int i = 0; i < 5; i++)
            cin >> regisracija[i];

        cin >> maximumBrzina;

        Automobile nov = Automobile(marka, regisracija, maximumBrzina);

        //dodavanje na avtomobil
        agencija += nov;
    }
    //se cita grehsniot avtmobil, za koj shto avtmobilot so ista registracija treba da se izbrishe
    char marka[100];
    int regisracija[5];
    int maximumBrzina;
    cin >> marka;
    for (int i = 0; i < 5; i++)
        cin >> regisracija[i];
    cin >> maximumBrzina;

    Automobile greshka = Automobile(marka, regisracija, maximumBrzina);

    //brishenje na avtomobil
    agencija -= greshka;

    agencija.pecatiNadBrzina(150);

    return 0;
}
