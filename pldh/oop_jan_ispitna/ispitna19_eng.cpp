#include<iostream>
#include<string.h>
#include<string>
using namespace std;
//zad2 ispitni/kolokviumski eng

// Your code here

class ExistingBill : public exception {
public:
    const char *what() const noexcept override {
        return "The bill already exists";
    }
};

class Bill {
protected:
    char *billNumber;
    int expense;
    char date[10]; //MM.YYYY
    bool status;

    void copy(const Bill &bill) {
        this->billNumber = new char [strlen(bill.billNumber) + 1];
        strcpy(this->billNumber, bill.billNumber);
        this->expense = bill.expense;
        strcpy(this->date, bill.date);
        this->status = bill.status;
    }

public:
    //Bill() = default;

    Bill(const char *billNumber = "", int expense = 0, const char *date = "", bool status = false) {
        this->billNumber = new char [strlen(billNumber) + 1];
        strcpy(this->billNumber, billNumber);
        this->expense = expense;
        strcpy(this->date, date);
        this->status = status;
    }

    Bill(const Bill &bill) {
        copy(bill);
    }

    Bill &operator=(const Bill &bill) {
        if (this != &bill) {
            delete [] billNumber;
            copy(bill);
        }
        return *this;
    }

    ~Bill() {
        delete []billNumber;
    }

    bool operator==(const Bill &other) const {
        if (other.billNumber == nullptr || billNumber == nullptr) {
            return false;
        }
        return strcmp(other.billNumber, billNumber) == 0;
    }

    friend ostream &operator<<(ostream &out, const Bill &b) {
        //254118445(04.2016) - 2000
        return out << b.billNumber << "(" << b.date << ")" << " - " << b.expense;
    }

    const char *getMonthYear() const { return date; }
    bool getStatus() const { return status; }
    int getExpense() const { return expense; }
};

class UserProfile {
private:
    char username[30];
    Bill billsArray[30];
    int numBills;

public:
    //UserProfile() = default;

    UserProfile(const char *username = "", int numBills = 0) {
        strcpy(this->username, username);
        this->numBills = numBills;
    }

    UserProfile &operator+=(const Bill &bill) {
        for (int i = 0; i < numBills; i++) {
            if (billsArray[i] == bill) {
                throw ExistingBill();
            }
        }
        if (numBills < 30) {
            billsArray[numBills++] = bill;
        }
        return *this;
    }

    friend ostream &operator<<(ostream &out, const UserProfile &profile) {
        out << "Unpaid bills of user " << profile.username << " are:" << endl;
        for (int i = 0; i < profile.numBills; i++) {
            if (!profile.billsArray[i].getStatus()) {
                out << profile.billsArray[i] << endl;
            }
        }
        return out;
    }

    int totalDue(int month, int year) {
        int total = 0;
        char target[8];
        snprintf(target, sizeof(target), "%02d.%04d", month, year);
        for (int i = 0; i < numBills; ++i) {
            if (strcmp(billsArray[i].getMonthYear(), target) == 0) {
                total += billsArray[i].getExpense();
            }
        }
        return total;
    }
};


int main() {
    char number[50], month[8], name[50];
    int price, n;
    bool status;


    int type;
    cin >> type;

    if (type == 1) {
        cout << "-----Test Bill & operator <<-----" << endl;
        cin >> number >> price >> month >> status;
        Bill b(number, price, month, status);
        cout << b;
    } else if (type == 2) {
        cout << "-----Test Bill & operator == -----" << endl;
        cin >> number >> price >> month >> status;
        Bill b1(number, price, month, status);
        cin >> number >> price >> month >> status;
        Bill b2(number, price, month, status);
        if (b1 == b2) cout << "Equal" << endl;
        else cout << "Not equal" << endl;
    } else if (type == 3) {
        cout << "-----Test UserProfile & operator += & << -----" << endl;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            Bill s(number, price, month, status);
            up += s;
        }
        cout << up;
    } else if (type == 4) {
        cout << "-----Test UserProfile & operator += & totalDue -----" << endl;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            Bill s(number, price, month, status);

            try {
                up += s;
            } catch (ExistingBill &e) {
                cout << e.what() << endl;
            }
        }
        int m, y;
        cin >> m >> y;
        cout << "Total due for month " << m << " and year " << y << " is:";
        cout << up.totalDue(m, y) << endl;
    } else if (type == 5) {
        cout << "-----Test all -----" << endl;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            Bill s(number, price, month, status);
            try {
                up += s;
            } catch (const ExistingBill &e) {
                cout << e.what() << endl;
            }
        }
        cout << up;
        int m, y;
        cin >> m >> y;
        cout << "Total due for month " << m << " and year " << y << " is:";
        cout << up.totalDue(m, y) << endl;
    }

    return 0;
}
