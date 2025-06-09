#include <iostream>
#include <cstring>
using namespace std;

// Your code here!!!
class MonthlyInvoice {
protected:
    char username[100];
    int userNumber;
    float initialPrice;
    int usedInternet;

    void copy(const MonthlyInvoice &m) {
        strcpy(this->username, m.username);
        this->userNumber = m.userNumber;
        this->initialPrice = m.initialPrice;
        this->usedInternet = m.usedInternet;
    }

public:
    MonthlyInvoice(const char *username = "", int userNumber = 0, float initialPrice = 0.0, int usedInternet = 0) {
        strcpy(this->username, username);
        this->userNumber = userNumber;
        this->initialPrice = initialPrice;
        this->usedInternet = usedInternet;
    }

    MonthlyInvoice(const MonthlyInvoice &m) {
        copy(m);
    }

    MonthlyInvoice &operator=(const MonthlyInvoice &m) {
        if (this != &m) {
            copy(m);
        }
        return *this;
    }

    virtual float total_price() const = 0;

    virtual ~MonthlyInvoice() {
    }

    friend bool operator>(const MonthlyInvoice &a, const MonthlyInvoice &b) {
        return a.total_price() > b.total_price();
    }

    virtual void print(ostream &out) const = 0;

    friend ostream &operator<<(ostream &out, const MonthlyInvoice &mi) {
        mi.print(out);
        return out;
    }
};

class BusinessInvoice : public MonthlyInvoice {
private:
    bool line; //true - optics; false - cable
    int quantity;

public:
    BusinessInvoice(const char *username = "", int userNumber = 0, float initialPrice = 0.0, int usedInternet = 0,
                    bool line = false, int quantity = 0): MonthlyInvoice(
        username, userNumber, initialPrice, usedInternet) {
        this->line = line;
        this->quantity = quantity;
    }

    float total_price() const override {
        float extra = (usedInternet > quantity) ? (usedInternet - quantity) * 100.0 : 0;
        float base = line ? initialPrice * 1.5f : initialPrice;
        return base + extra;
    }

    BusinessInvoice &operator++(int) {
        usedInternet++;
        return *this;
    }

    void print(ostream &out) const override {
        out << userNumber << " - " << username << ", " << initialPrice << endl;
        out << (line ? "optical link" : "cable link") << ", "
                << ((usedInternet > quantity) ? usedInternet - quantity : 0) << endl;
    }
};


class PrivateInvoice : public MonthlyInvoice {
private:
    char citizenId[14];
    int *movieSizes;
    int numMovies;

    void copyFrom(const PrivateInvoice &pi) {
        strcpy(this->citizenId, pi.citizenId);
        this->numMovies = pi.numMovies;
        this->movieSizes = new int[pi.numMovies];
        for (int i = 0; i < pi.numMovies; ++i) {
            this->movieSizes[i] = pi.movieSizes[i];
        }
    }

public:
    PrivateInvoice(const char *username = "", int userNumber = 0, float initialPrice = 0.0, int usedInternet = 0)
        : MonthlyInvoice(username, userNumber, initialPrice, usedInternet), numMovies(0) {
        strcpy(citizenId, "0000000000000");
        movieSizes = nullptr;
    }

    PrivateInvoice(const PrivateInvoice &pi) : MonthlyInvoice(pi) {
        copyFrom(pi);
    }

    PrivateInvoice &operator=(const PrivateInvoice &pi) {
        if (this != &pi) {
            delete[] movieSizes;
            MonthlyInvoice::operator=(pi);
            copyFrom(pi);
        }
        return *this;
    }

    ~PrivateInvoice() {
        delete[] movieSizes;
    }

    float total_price() const override {
        int movieTotal = 0;
        for (int i = 0; i < numMovies; ++i) {
            movieTotal += movieSizes[i];
        }
        return initialPrice + usedInternet * 50 + movieTotal * 10;
    }

    int operator[](int index) const {
        if (index < 0 || index >= numMovies) return -1;
        return movieSizes[index];
    }

    PrivateInvoice &operator+=(int size) {
        int *tmp = new int[numMovies + 1];
        for (int i = 0; i < numMovies; ++i)
            tmp[i] = movieSizes[i];
        tmp[numMovies++] = size;
        delete[] movieSizes;
        movieSizes = tmp;
        return *this;
    }

    PrivateInvoice &operator++(int) {
        usedInternet++;
        return *this;
    }

    int getMoviesNo() const {
        return numMovies;
    }

    void print(ostream &out) const override {
        int movieTotal = 0;
        for (int i = 0; i < numMovies; ++i)
            movieTotal += movieSizes[i];
        out << userNumber << " - " << username << ", " << initialPrice << endl;
        out << usedInternet << endl;
        out << numMovies << ", " << movieTotal << endl;
    }
};

MonthlyInvoice &biggestInvoice(MonthlyInvoice **arr, int n) {
    MonthlyInvoice *max = arr[0];
    for (int i = 1; i < n; ++i) {
        if (*arr[i] > *max) {
            max = arr[i];
        }
    }
    return *max;
}


// Testing the program!!!
int main() {
    int test_case;
    char username[101];
    int userNumber;
    float basic_price;
    int spent_gigabytes;
    bool optical;
    int free_gigabytes;
    int num_inc;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case Business Invoice - Constructor, operator <<
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        cin >> optical >> free_gigabytes;
        BusinessInvoice bi(username, userNumber, basic_price, spent_gigabytes, optical, free_gigabytes);
        cout << "BusinessInvoice Created:\n";
        cout << bi;
    } else if (test_case == 2) {
        // Test Case Business Invoice - Constructor, operators <<, ++
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        cin >> optical >> free_gigabytes;
        BusinessInvoice bi(username, userNumber, basic_price, spent_gigabytes, optical, free_gigabytes);
        cout << "BusinessInvoice:\n";
        cout << bi;
        cout << "testing operator++\n";

        // Additional spent gigabytes
        cin >> num_inc;
        for (int i = 0; i < num_inc; ++i) {
            bi++;
        }
        cout << bi;
    } else if (test_case == 3) {
        // Test Case Business Invoice - Constructor, total_price, operators <<, ++,
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        cin >> optical >> free_gigabytes;
        BusinessInvoice bi(username, userNumber, basic_price, spent_gigabytes, optical, free_gigabytes);
        cout << "Testing total_price()\n";
        cout << bi;
        cout << bi.total_price() << endl;
        bi++;
        cout << bi;
        cout << bi.total_price() << endl;
    } else if (test_case == 4) {
        // Test Case Private Invoice - Constructor, operator <<
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;

        PrivateInvoice pi(username, userNumber, basic_price, spent_gigabytes);
        cout << "Private Invoice Created:\n";
        cout << pi;
    } else if (test_case == 5) {
        // Test Case Private Invoice - Constructor, operators <<, ++
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber, basic_price, spent_gigabytes);
        cin >> num_inc;
        for (int i = 0; i < num_inc; ++i) {
            pi++;
        }
        cout << pi;
    } else if (test_case == 6) {
        // Test Case Private Invoice - Constructor, operators <<, +=
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber, basic_price, spent_gigabytes);
        cin >> num_inc;
        int film_length;
        for (int i = 0; i < num_inc; ++i) {
            cin >> film_length;
            pi += film_length;
        }
        cout << pi;
    } else if (test_case == 7) {
        // Test Case Private Invoice - Constructor, operators <<, +=, []
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber, basic_price, spent_gigabytes);
        cin >> num_inc;
        int film_length;
        for (int i = 0; i < num_inc; ++i) {
            cin >> film_length;
            pi += film_length;
        }
        cout << pi;
        cout << "Movie sizes: [";
        for (int i = 0; i < pi.getMoviesNo(); ++i) {
            cout << pi[i] << " ";
        }
        cout << "]" << endl;
    } else if (test_case == 8) {
        // Test Case Private Invoice - Constructor, total_price
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber, basic_price, spent_gigabytes);
        cout << pi;
        cout << pi.total_price() << endl;
        cin >> num_inc;
        int film_length;
        for (int i = 0; i < num_inc; ++i) {
            cin >> film_length;
            pi += film_length;
        }
        cin >> num_inc;
        for (int i = 0; i < num_inc; ++i) {
            pi++;
        }
        cout << pi;
        cout << pi.total_price() << endl;
    } else if (test_case == 9) {
        // Test Case

        int num_invoices;
        int invoice_type;

        cin >> num_invoices;
        MonthlyInvoice **mi = new MonthlyInvoice *[num_invoices];
        for (int j = 0; j < num_invoices; ++j) {
            cin >> invoice_type;
            if (invoice_type == 1) {
                cin >> username >> userNumber >> basic_price >> spent_gigabytes;
                cin >> optical >> free_gigabytes;
                BusinessInvoice *bip;
                bip = new BusinessInvoice(username, userNumber, basic_price, spent_gigabytes, optical, free_gigabytes);
                cin >> num_inc;
                for (int i = 0; i < num_inc; ++i) {
                    (*(bip))++;
                }
                cout << *(bip);
                cout << bip->total_price() << endl;

                mi[j] = bip;
            }
            if (invoice_type == 2) {
                cin >> username >> userNumber >> basic_price >> spent_gigabytes;
                PrivateInvoice *pip = new PrivateInvoice(username, userNumber, basic_price, spent_gigabytes);
                cin >> num_inc;
                int film_length;
                for (int i = 0; i < num_inc; ++i) {
                    cin >> film_length;
                    (*pip) += film_length;
                }
                cin >> num_inc;
                for (int i = 0; i < num_inc; ++i) {
                    (*pip)++;
                }
                cout << (*pip);
                cout << pip->total_price() << endl;
                mi[j] = pip;
            }
        }

        cout << "The biggest invoice is:\n";
        MonthlyInvoice &invoice = biggestInvoice(mi, num_invoices);

        MonthlyInvoice *m = &invoice;
        BusinessInvoice *bip;
        PrivateInvoice *pip;
        if (dynamic_cast<BusinessInvoice *>(m)) {
            bip = dynamic_cast<BusinessInvoice *>(m);
            cout << *bip << bip->total_price();
        }
        if (dynamic_cast<PrivateInvoice *>(m)) {
            pip = dynamic_cast<PrivateInvoice *>(m);
            cout << *pip << pip->total_price();
        }
    }
    return 0;
}
