#include <iostream>
#include <cstring>
using namespace std;
// Your code here

class ExistingBill {
public:
    void message() {
        cout << "The bill already exists" << endl;
    }
};

class Bill {
protected:
    char *billNumber;
    int expense;
    char issueDate[8];
    bool status;

    void copy(const Bill &b) {
        this->billNumber = new char[strlen(b.billNumber) + 1];
        strcpy(this->billNumber, b.billNumber);
        this->expense = b.expense;
        strcpy(this->issueDate, b.issueDate);
        this->status = b.status;
    }

public:
    Bill(const char *billNumber = "", int expense = 0, const char *issueDate = "", bool status = false) {
        this->billNumber = new char [strlen(billNumber) + 1];
        strcpy(this->billNumber, billNumber);
        this->expense = expense;
        strcpy(this->issueDate, issueDate);
        this->status = status;
    }

    ~Bill() {
        delete[] billNumber;
    }

    Bill(const Bill &b) {
        copy(b);
    }

    Bill &operator=(const Bill &b) {
        if (this != &b) {
            delete [] billNumber;
            copy(b);
        }
        return *this;
    }

    bool operator==(const Bill &b) const {
        return strcmp(billNumber, b.billNumber) == 0;
    }

    friend ostream &operator<<(ostream &out, const Bill &b) {
        out << b.billNumber << " (" << b.issueDate << ") " << " - " << b.expense << endl;
    }

    bool isPaid() const {
        return status;
    }

    int getExpense() const {
        return expense;
    }

    const char *getIssueDate() const {
        return issueDate;
    }
};

class UserProfile {
private:
    char username[30];
    Bill billsArray[30];
    int n;

public:
    UserProfile(const char *username = "") {
        strcpy(this->username, username);
        this->n = 0;
    }

    UserProfile &operator+=(const Bill &b) {
        for (int i = 0; i < n; i++) {
            if (billsArray[i] == b) {
                ExistingBill e;
                e.message();
                return *this;
            }
        }
        billsArray[n++] = b;
        return *this;
    }

    friend ostream &operator<<(ostream &out, const UserProfile &up) {
        out << "Unpaid bills of user " << up.username << " are:" << endl;
        for (int i = 0; i < up.n; i++) {
            if (!up.billsArray[i].isPaid()) {
                out << up.billsArray[i];
            }
        }
        return out;
    }

    int totalDue(int month, int year) const {
        char formatted[8];
        sprintf(formatted, "%02d.%d", month, year);
        int total = 0;
        for (int i = 0; i < n; i++) {
            if (billsArray[i].isPaid() && strcmp(billsArray[i].getIssueDate(), formatted) == 0) {
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
            up += s;
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
            up += s;
        }
        cout << up;
        int m, y;
        cin >> m >> y;
        cout << "Total due for month " << m << " and year " << y << " is:";
        cout << up.totalDue(m, y) << endl;
    }

    return 0;
}
