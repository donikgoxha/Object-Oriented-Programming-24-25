#include <iostream>
#include <cstring>
#include <cctype>
#include <cmath>
using namespace std;

struct Vraboten {
    char ime[30];
    char embg[13];
    char oddel[30];
    int plata;

    void pechati() {
        cout << ime << " " << embg << " " << oddel << " " << plata << endl;
    }
};

struct Companija {
    char ime[30];
    Vraboten vraboteni[100];
    int n;

    void pechati() {
        cout << ime << endl;
        for (int i = 0; i < n; i++) {
            cout << vraboteni[i].ime;
        }
    }
};

void printEmployeesBelowAverageSalary(Companija *comp, int numCompanies) {
    for (int i = 0; i < numCompanies; i++) {
        int suma = 0;
        for (int j = 0; j < comp[i].n; j++) {
            suma += comp[i].vraboteni[j].plata;
        }
        float prosek = (suma * 1.0) / comp[i].n;
        for (int j = 0; j < comp[i].n; j++) {
            if (comp[i].vraboteni[j].plata <= prosek) {
                comp[i].vraboteni[j].pechati();
            }
        }
    }
}

void printHighestSalaryEmployee(Companija *comp, int numCompanies, char *department) {
    for (int i = 0; i < numCompanies; i++) {
        int max = 0;
        int max_j = 0;
        bool flag = 0;
        for (int j = 0; j < comp[i].n; j++) {
            if (strcmp(comp[i].vraboteni[j].oddel, department) == 0 && comp[i].vraboteni[j].plata > max) {
                max = comp[i].vraboteni[j].plata;
                max_j = j;
                flag = 1;
            }
        }
        if (flag == 1) {
            comp[i].vraboteni[max_j].pechati();
        }
    }
}


int main() {
    int n;
    cin >> n;
    Companija niza[100];

    for (int i = 0; i < n; i++) {
        cin >> niza[i].ime >> niza[i].n;
        for (int j = 0; j < niza[i].n; j++) {
            cin >> niza[i].vraboteni[j].ime >> niza[i].vraboteni[j].embg >> niza[i].vraboteni[j].oddel >> niza[i].
                    vraboteni[j].plata;
        }
    }

    cout << "Employees with salaries below the average: " << endl;
    printEmployeesBelowAverageSalary(niza, n);
    char oddel[30];
    cin >> oddel;
    cout << "Employees with highest salaries for given department: " << endl;
    printHighestSalaryEmployee(niza, n, oddel);
    return 0;
}
