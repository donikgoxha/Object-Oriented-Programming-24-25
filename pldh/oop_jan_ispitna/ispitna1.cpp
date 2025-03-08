#include <iostream>
#include <cstring>
using namespace std;
//zad1 ispitni/kolokviumski
class Book {
protected:
    char ISBN[21];
    char title[51];
    char author[31];
    float basePrice;

public:
    Book(const char *ISBN, const char *title, const char *author, float basePrice) {
        strncpy(this->ISBN, ISBN, 20);
        this->ISBN[20] = '\0';
        strncpy(this->title, title, 50);
        this->title[50] = '\0';
        strncpy(this->author, author, 30);
        this->author[30] = '\0';
        this->basePrice = basePrice;
    }

    virtual ~Book() {
    }

    virtual float bookPrice() const = 0;

    virtual void print(ostream &out) const {
        out << ISBN << ": " << title << ", " << author;
    }

    bool operator>(const Book &other) const {
        return this->bookPrice() > other.bookPrice();
    }

    friend ostream &operator<<(ostream &out, const Book &book) {
        book.print(out);
        return out;
    }
};

class OnlineBook : public Book {
private:
    char *url;
    int sizeMB;

public:
    OnlineBook(const char *ISBN, const char *title, const char *author, float basePrice, const char *url, int sizeMB)
        : Book(ISBN, title, author, basePrice) {
        this->url = new char[strlen(url) + 1];
        strcpy(this->url, url);
        this->sizeMB = sizeMB;
    }

    OnlineBook(const OnlineBook &other) : Book(other.ISBN, other.title, other.author, other.basePrice) {
        this->url = new char[strlen(other.url) + 1];
        strcpy(this->url, other.url);
        this->sizeMB = other.sizeMB;
    }

    OnlineBook &operator=(const OnlineBook &other) {
        if (this != &other) {
            delete[] url;
            strncpy(this->ISBN, other.ISBN, 20);
            strncpy(this->title, other.title, 50);
            strncpy(this->author, other.author, 30);
            this->basePrice = other.basePrice;
            this->url = new char[strlen(other.url) + 1];
            strcpy(this->url, other.url);
            this->sizeMB = other.sizeMB;
        }
        return *this;
    }

    ~OnlineBook() {
        delete[] url;
    }

    void setISBN(const char *ISBN) {
        strncpy(this->ISBN, ISBN, 20);
        this->ISBN[20] = '\0';
    }

    float bookPrice() const override {
        if (sizeMB > 20) {
            return basePrice * 1.20f;
        }
        return basePrice;
    }

    void print(ostream &out) const override {
        Book::print(out);
        out << " " << bookPrice() << endl;
    }
};

class PrintBook : public Book {
private:
    float weight;
    bool inStock;

public:
    PrintBook(const char *ISBN, const char *title, const char *author, float basePrice, float weight, bool inStock)
        : Book(ISBN, title, author, basePrice), weight(weight), inStock(inStock) {
    }

    float bookPrice() const override {
        if (weight > 0.7f) {
            return basePrice * 1.15f;
        }
        return basePrice;
    }

    void print(ostream &out) const override {
        Book::print(out);
        out << " " << bookPrice() << endl;
    }
};

void mostExpensiveBook(Book **books, int n) {
    int onlineCount = 0, printCount = 0;
    Book *mostExpensive = books[0];

    for (int i = 0; i < n; i++) {
        OnlineBook *ob = dynamic_cast<OnlineBook *>(books[i]);
        if (ob) {
            onlineCount++;
        } else {
            printCount++;
        }

        if (*books[i] > *mostExpensive) {
            mostExpensive = books[i];
        }
    }

    cout << "FINKI-Education" << endl;
    cout << "Total number of online books: " << onlineCount << endl;
    cout << "Total number of print books: " << printCount << endl;
    cout << "The most expensive book is: " << endl;
    cout << *mostExpensive;
}


int main() {
    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++) {
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2) {
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3) {
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++) {
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4) {
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++) {
            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {
                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);
            } else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i < n; i++) delete books[i];
    delete[] books;
    return 0;
}
