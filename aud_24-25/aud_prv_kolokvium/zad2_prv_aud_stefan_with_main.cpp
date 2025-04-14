/*
Define the class Book, which represents a single book. The class holds the following attributes:
-title – a textual array of up to 30 characters
-id – serial number (integer)
-type – enumerated type representing the book type: academic or roman
-price – decimal number
The serial number is unique for each book. The initial value is 777550. Ensure sequential
generation of this number, so that the first book has serial number 777551, the second 777552,
the third 777553, etc. (5 points)
Provide the necessary constructors and set/get methods. (5 points)
Implement a method print() which prints the information in the following format:
[serial number] - [title] [type] [price] (5 points)
Implement a method increasePrice(float) that takes a real number representing the margin,
and adds it to the book's price. (5 points)

Then define the class BookStore, which stores information about:
-Name (textual array of up to 20 characters)
-List of books (regular array of up to 100 Book objects)
-Number of books (number of elements in the array, initially 0)
Define the necessary constructors, destructor (if needed), and set/get methods. (5 points)
Implement a method print() in the following format: [name] and then all books printed
individually (see format from the Book::print method). (5 points)
Implement a method addBook(const Book&) to add a new book to the store.
Books are managed based on their title, and adding a book with an already existing title
is not allowed. (10 points)
Define a method greaterThan(const BookStore&) to compare two stores by the number of books. (5 points)
Define a method void createMarketPrice() that generates selling prices for all books in the store.
The selling prices depend on the book type:
-For academic literature, 5% is added to the price
-For romans, 3% is added (10 points)
Define a global function best() that takes an array of BookStore objects and the number of stores,
and returns the store with the most books. If multiple stores have the same number of books,
the first one is returned. (5 points)
 */

#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

enum BOOK_TYPE { ACADEMIC, NOVEL };

class Book {
private:
    char title[30];
    int ID;
    BOOK_TYPE bookType;
    double price;
    static int COUNTER;

public:
    Book() {
        strcpy(this->title, "");
        this->bookType = ACADEMIC;
        this->ID = 0;
        this->price = 100;
    }

    Book(const char *title, int type, double price) {
        strcpy(this->title, title);
        this->bookType = (BOOK_TYPE) (type);
        this->price = price;
        this->ID = 777550 + COUNTER;
        ++COUNTER;
    }

    void print() {
        cout << ID << " - " << title << " ";
        if (bookType == NOVEL) {
            cout << "Roman";
        } else if (bookType == ACADEMIC) {
            cout << "Academic";
        }
        cout << " ";
        cout << price << endl;
    }

    float increasePrice(float amount) {
        this->price += amount;
    }

    char *getTitle() {
        return title;
    }

    BOOK_TYPE getBookType() {
        return bookType;
    }

    friend class BookStore;
};

class BookStore {
private:
    char name[20];
    Book books[100];
    int n;

public:
    BookStore(const char *name = "") {
        strcpy(this->name, name);
        n = 0;
    }

    void addBook(const Book &other) {
        if (n == 100) {
            return;
        }

        for (int i = 0; i < n; i++) {
            if (strcmp(books[i].title(), other.title()) == 0) {
                return;
            }
        }
        books[n++] = other;
    }

    void print() {
        cout << name << endl;
        for (int i = 0; i < n; i++) {
            books[i].print();
        }
    }

    bool greaterThan(const BookStore &other) {
        return this->n > other.n;
    }

    void createMarketPrice() {
        for (int i = 0; i < n; i++) {
            if (books[i].bookType == ACADEMIC) {
                books[i].increasePrice(books[i].price * 0.05);
            } else {
                books[i].increasePrice(books[i].price * 0.05);
            }
        }
    }

    void deleteElement(int idx) {
        for (int i = idx; i < n - 1; ++i) {
            books[i] = books[i + 1];
        }
        n--;
    }

    void deleteBook(char *title) {
        for (int i = 0; i < n; i++) {
            if (strcmp(books[i].title(), title) == 0) {
                deleteElement(i);
            }
        }
    }

    void deleteAcademicBooks() {
        for (int i = 0; i < n; i++) {
            if (books[i].bookType == ACADEMIC) {
                deleteElement(i);
            }
        }
    }

    int getNumberOfBooks() const {
        return n;
    }
};

BookStore best(BookStore stores[], int numStores) {
    if (numStores <= 0) {
        return BookStore("");
    }
    int bestIndex = 0;
    for (int i = 1; i < numStores; i++) {
        if (stores[i].getNumberOfBooks() > stores[bestIndex].getNumberOfBooks()) {
            bestIndex = i;
        }
    }
    return stores[bestIndex];
}

int Book::COUNTER = 1;

int main() {
    int testCase;
    cin >> testCase;
    if (testCase == 0) {
        cout << "TESTING BOOK CONSTRUCTOR" << endl;
        Book book1("Object-oriented programming", 0, 2300);
        Book book2("Discrete Mathematics", 0, 1800);
        Book book3("Crime and punishment", 1, 950);
        cout << "TEST PASSED" << endl;
    } else if (testCase == 1) {
        cout << "TESTING BOOK print()" << endl;
        Book book1("Object-oriented programming", 0, 2300);
        Book book2("Discrete Mathematics", 0, 1800);
        Book book3("Crime and punishment", 1, 950);
        book1.print();
        book2.print();
        book3.print();
        cout << "TEST PASSED" << endl;
    } else if (testCase == 2) {
        cout << "TESTING BOOK increasePrice" << endl;
        Book book1("Object-oriented programming", 0, 2300);
        Book book2("Discrete Mathematics", 0, 1800);
        Book book3("Crime and punishment", 1, 950);
        book1.print();
        book2.print();
        book3.print();
        book1.increasePrice(200);
        book2.increasePrice(300);
        book3.increasePrice(150);
        cout << "===== INCREASE =====" << endl;
        book1.print();
        book2.print();
        book3.print();
        cout << "TEST PASSED" << endl;
    } else if (testCase == 3) {
        cout << "TESTING BOOKSTORE CONSTRUCTOR" << endl;
        BookStore bookStore1("The Book Cellar");
        bookStore1.print();
        cout << "TEST PASSED" << endl;
    } else if (testCase == 4) {
        cout << "TESTING BOOKSTORE addBook() and print()" << endl;
        Book book1("Object-oriented programming", 0, 2300);
        Book book2("Discrete Mathematics", 0, 1800);
        Book book3("Crime and punishment", 1, 950);
        BookStore bookStore1("The Book Cellar");
        bookStore1.addBook(book1);
        bookStore1.addBook(book2);
        bookStore1.addBook(book3);
        bookStore1.print();
        cout << "TEST PASSED" << endl;
    } else if (testCase == 5) {
        cout << "TESTING BOOKSTORE OPERATOR addBook() and print()" << endl;
        Book book1("Object-oriented programming", 0, 2300);
        Book book2("Discrete Mathematics", 0, 1800);
        Book book3("Crime and punishment", 1, 950);
        Book book4("Object-oriented programming", 0, 2300);
        BookStore bookStore1("The Book Cellar");
        bookStore1.addBook(book1);
        bookStore1.addBook(book2);
        bookStore1.addBook(book3);
        bookStore1.addBook(book4);
        bookStore1.print();
        cout << "TEST PASSED" << endl;
    } else if (testCase == 6) {
        cout << "TESTING BOOKSTORE COPY-CONSTRUCTOR" << endl;
        Book book1("Object-oriented programming", 0, 2300);
        Book book2("Discrete Mathematics", 0, 1800);
        Book book3("Crime and punishment", 1, 950);
        Book book4("Anna Karenina", 1, 1200);
        Book book5("Calculus 1", 0, 1320);
        BookStore bookStore1("The Book Cellar");
        bookStore1.addBook(book1);
        bookStore1.addBook(book2);
        bookStore1.addBook(book3);
        BookStore bookStore2(bookStore1);

        bookStore1.print();
        bookStore2.print();
        cout << "TEST PASSED" << endl;
    } else if (testCase == 7) {
        cout << "TESTING BOOKSTORE greaterThan " << endl;
        Book book1("Object-oriented programming", 0, 2300);
        Book book2("Discrete Mathematics", 0, 1800);
        Book book3("Crime and punishment", 1, 950);
        Book book4("Anna Karenina", 1, 1200);
        Book book5("Calculus 1", 0, 1320);
        BookStore bookStore1("The Book Cellar");
        bookStore1.addBook(book1);
        bookStore1.addBook(book2);
        bookStore1.addBook(book3);
        BookStore bookStore3("Word Wizardry Books");
        bookStore3.addBook(book4);
        bookStore3.addBook(book5);
        if (bookStore1.greaterThan(bookStore3)) {
            cout << "TEST PASSED" << endl;
        } else {
            cout << "TEST FAILED" << endl;
        }
    } else if (testCase == 8) {
        cout << "TESTING METHOD createMarketPrice()" << endl;
        char name[30], name1[30];
        int type, numofBookStores, numberOfBooks;
        float price;
        cin >> numofBookStores;
        cin.ignore();
        BookStore bookStores[10];
        for (int i = 0; i < numofBookStores; i++) {
            cin.getline(name, 20);
            bookStores[i] = BookStore(name);
            cin >> numberOfBooks;
            cin.ignore();
            Book books[10]; //777561
            for (int j = 0; j < numberOfBooks; j++) {
                cin >> name1 >> type >> price;
                cin.ignore();
                books[j] = Book(name1, type, price);
                bookStores[i].addBook(books[j]);
            }
        }
        for (int i = 0; i < numofBookStores; i++) {
            bookStores[i].print();
            cout << "CREATED MARKET PRICES" << endl;
            bookStores[i].createMarketPrice();
            bookStores[i].print();
        }
    } else if (testCase == 9) {
        cout << "TESTING METHOD best()" << endl;
        char name[30], name1[30];
        int type, numofBookStores, numberOfBooks;
        float price;
        cin >> numofBookStores;
        cin.ignore();
        BookStore bookStores[10];
        for (int i = 0; i < numofBookStores; i++) {
            cin.getline(name, 20);
            bookStores[i] = BookStore(name);
            cin >> numberOfBooks;
            cin.ignore();
            Book books[10];
            for (int j = 0; j < numberOfBooks; j++) {
                cin >> name1 >> type >> price;
                cin.ignore();
                books[j] = Book(name1, type, price);
                bookStores[i].addBook(books[j]);
            }
        }
        //best(bookStores, numofBookStores).print();
    }
    return 0;
}
