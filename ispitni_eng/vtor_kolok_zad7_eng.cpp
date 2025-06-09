#include <iostream>
#include <string.h>
using namespace std;

class DonaciskiApel {
protected:
    char *name;
    char idNumber[10];
    int collectedFund;
    int neededFund;

    void copy(const DonaciskiApel &d) {
        this->name = new char[strlen(d.name) + 1];
        strcpy(this->name, d.name);
        strcpy(this->idNumber, d.idNumber);
        this->collectedFund = d.collectedFund;
        this->neededFund = d.neededFund;
    }

    void validateId(const char *id) {
        if (strlen(id) > 9) {
            throw "The id number has more than 9 characters";
        }
        for (int i = 0; i < strlen(id); i++) {
            if (!isdigit(id[i])) {
                throw "The id number has a non-digit character";
            }
        }
    }

public:
    DonaciskiApel(const char *name = "", const char *idNumber = "", int neededFund = 0, int collectedFund = 0) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->idNumber, idNumber);
        this->collectedFund = collectedFund;
        this->neededFund = neededFund;
        validateId(idNumber);
    }

    DonaciskiApel(const DonaciskiApel &d) {
        copy(d);
    }

    DonaciskiApel &operator=(const DonaciskiApel &d) {
        if (this != &d) {
            delete[] name;
            copy(d);
        }
        return *this;
    }

    DonaciskiApel &operator+=(int amount) {
        collectedFund += amount;
        return *this;
    }

    const char *getId() const { return idNumber; }
    int getNeeded() const { return neededFund; }
    int getCollected() const { return collectedFund; }

    bool operator<(const DonaciskiApel &other) const {
        int difference1 = neededFund - collectedFund;
        int difference2 = other.neededFund - other.collectedFund;
        if (difference1 == difference2) {
            return strcmp(idNumber, other.idNumber) < 0;
        }
        return difference1 < difference2;
    }

    friend ostream &operator<<(ostream &os, const DonaciskiApel &da) {
        os << da.idNumber << " " << da.name;
        if (da.collectedFund >= da.neededFund) {
            os << " collected";
        } else {
            os << " " << (da.neededFund - da.collectedFund) << " more denars are needed";
        }
        return os;
    }

    virtual ~DonaciskiApel() {
        delete[] name;
    }
};

class DonaciskoDurstvo {
private:
    char president[31];
    DonaciskiApel *apel;
    int donations;

public:
    DonaciskoDurstvo(const char *president = "") {
        strcpy(this->president, president);
        this->donations = 0;
        this->apel = nullptr;
    }

    bool primiiDonacija(char id[], int amount) {
        for (int i = 0; i < donations; i++) {
            if (strcmp(apel[i].getId(), id) == 0) {
                apel[i] += amount;
                return true;
            }
        }
        return false;
    }

    DonaciskoDurstvo &operator+=(const DonaciskiApel &newAction) {
        for (int i = 0; i < donations; i++) {
            if (strcmp(apel[i].getId(), newAction.getId()) == 0) {
                return *this;
            }
        }

        DonaciskiApel *temp = new DonaciskiApel[donations + 1];
        for (int i = 0; i < donations; i++) {
            temp[i] = apel[i];
        }
        temp[donations] = newAction;
        delete[] apel;
        apel = temp;
        donations++;
        return *this;
    }

    friend ostream &operator<<(ostream &os, const DonaciskoDurstvo &ds) {
        DonaciskiApel *sorted = new DonaciskiApel[ds.donations];
        for (int i = 0; i < ds.donations; i++) {
            sorted[i] = ds.apel[i];
        }

        for (int i = 0; i < ds.donations - 1; i++) {
            for (int j = i + 1; j < ds.donations; j++) {
                if (sorted[i] < sorted[j]) {
                    swap(sorted[i], sorted[j]);
                }
            }
        }

        for (int i = 0; i < ds.donations; i++) {
            os << sorted[i] << endl;
        }
        os << "President:" << ds.president;

        delete[] sorted;
        return os;
    }

    ~DonaciskoDurstvo() {
        delete[] apel;
    }
};

int main() {
    DonaciskoDurstvo donacii("Velko Velkovski");
    int n;
    char naziv[50], id[50];
    int potrebnasuma, doniranasuma;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin.get();
        cin.getline(naziv, 50);
        cin >> id >> potrebnasuma;

        try {
            DonaciskiApel edna(naziv, id, potrebnasuma);
            donacii += edna;
        } catch (const char *msg) {
            cout << msg << endl;
        }
    }

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> id >> doniranasuma;

        if (!donacii.primiiDonacija(id, doniranasuma))
            cout << "The donation is not taken. Wrong ID." << endl;
    }
    cout << "===============" << endl;
    cout << donacii;

    return 0;
}
