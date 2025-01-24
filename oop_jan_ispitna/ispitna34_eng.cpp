#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

// Your code here!!!
class MonthlyInvoice {
protected:
    char name[100];
    int userNumber;
    float initialPrice;
    int usedInternetGB;

public:
    MonthlyInvoice(const char *name = "", int userNumber = 0, float initialPrice = 0.0, int usedInternetGB = 0) {
        strcpy(this->name, name);
        this->userNumber = userNumber;
        this->initialPrice = initialPrice;
        this->usedInternetGB = usedInternetGB;
    }

    MonthlyInvoice(const MonthlyInvoice &other) {
        strcpy(this->name, other.name);
        this->userNumber = other.userNumber;
        this->initialPrice = other.initialPrice;
        this->usedInternetGB = other.usedInternetGB;
    }

    virtual ~MonthlyInvoice() {
    }

    virtual float total_price() const = 0;

    friend ostream &operator<<(ostream &out, const MonthlyInvoice &invoice) {
        out << invoice.userNumber << " - " << invoice.name << ", " << invoice.initialPrice << endl;
        return out;
    }

    virtual void print(ostream &out) const = 0;

    friend bool operator<(const MonthlyInvoice &a, const MonthlyInvoice &b) {
        return a.total_price() < b.total_price();
    }
};

class BusinessInvoice : public MonthlyInvoice {
private:
    bool optical;
    int freeGB;

public:
    BusinessInvoice(const char *name = "", int userNumber = 0, float initialPrice = 0.0, int usedInternetGB = 0,
                    bool optical = false, int freeGB = 0)
        : MonthlyInvoice(name, userNumber, initialPrice, usedInternetGB), optical(optical), freeGB(freeGB) {
    }

    float total_price() const override {
        float extraCost = 0;
        if (usedInternetGB > freeGB)
            extraCost = (usedInternetGB - freeGB) * 100;

        float price = initialPrice + extraCost;
        if (optical) {
            price *= 1.5;
        }
        return price;
    }

    void operator++(int) {
        usedInternetGB++;
    }

    void print(ostream &out) const override {
        out << (optical ? "optical link" : "cable link") << ", " << max(0, usedInternetGB - freeGB) << endl;
    }

    friend ostream &operator<<(ostream &out, const BusinessInvoice &bi) {
        out << static_cast<const MonthlyInvoice &>(bi);
        bi.print(out);
        return out;
    }
};

class PrivateInvoice : public MonthlyInvoice {
private:
    char numID[13];
    int *movies;
    int numMovies;

public:
    PrivateInvoice(const char *name = "", int userNumber = 0, float initialPrice = 0.0, int usedInternetGB = 0,
                   const char *numID = "", int *movies = nullptr, int numMovies = 0)
        : MonthlyInvoice(name, userNumber, initialPrice, usedInternetGB), numMovies(numMovies) {
        strcpy(this->numID, numID);
        this->movies = new int[numMovies];
        for (int i = 0; i < numMovies; ++i) {
            this->movies[i] = movies[i];
        }
    }

    PrivateInvoice(const PrivateInvoice &other) : MonthlyInvoice(other), numMovies(other.numMovies) {
        strcpy(this->numID, other.numID);
        movies = new int[numMovies];
        for (int i = 0; i < numMovies; ++i) {
            movies[i] = other.movies[i];
        }
    }

    ~PrivateInvoice() override {
        delete[] movies;
    }

    float total_price() const override {
        int totalMoviesGB = 0;
        for (int i = 0; i < numMovies; i++) {
            totalMoviesGB += movies[i];
        }
        return initialPrice + usedInternetGB * 50 + totalMoviesGB * 10;
    }

    void operator++(int) {
        usedInternetGB++;
    }

    void operator+=(int movieSize) {
        int *newMovies = new int[numMovies + 1];
        for (int i = 0; i < numMovies; i++) {
            newMovies[i] = movies[i];
        }
        newMovies[numMovies++] = movieSize;
        delete[] movies;
        movies = newMovies;
    }

    int operator[](int index) const {
        if (index < 0 || index >= numMovies) {
            return -1;
        }
        return movies[index];
    }

    int getMoviesNo() const {
        return numMovies;
    }

    void print(ostream &out) const override {
        int totalMovieGB = 0;
        for (int i = 0; i < numMovies; ++i) {
            totalMovieGB += movies[i];
        }
        out << usedInternetGB << endl << numMovies << ", " << totalMovieGB << endl;
    }

    friend ostream &operator<<(ostream &out, const PrivateInvoice &pi) {
        out << static_cast<const MonthlyInvoice &>(pi);
        pi.print(out);
        return out;
    }
};

MonthlyInvoice &biggestInvoice(MonthlyInvoice **invoices, int size) {
    return **max_element(invoices, invoices + size, [](MonthlyInvoice *a, MonthlyInvoice *b) {
        return *a < *b;
    });
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
