#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

class Book {
private:
    string title;
    string author;
    int year;

public:
    Book() = default;

    Book(const string &title, const string &author, const int year)
        : title(title),
          author(author),
          year(year) {
    }

    friend ostream &operator<<(ostream &out, const Book &book) {
        return out << book.title << " " << book.author << " " << book.year;
    }

    friend bool operator==(const Book &lhs, const Book &rhs) {
        return lhs.title == rhs.title
               && lhs.author == rhs.author
               && lhs.year == rhs.year;
    }

    friend bool operator!=(const Book &lhs, const Book &rhs) {
        return !(lhs == rhs);
    }

    string &getAuthor() {
        return author;
    }
};


class BookAlreadyExistsException {
private:
    Book b;

public:
    BookAlreadyExistsException(const Book &b) {
        this->b = b;
    }

    void message() {
        cout << "Book \"" << b << "\" already exists in the library" << endl;
    }
};

class Library {
private:
    string name;
    Book *books;
    int n;

public:
    Library(const string &name = "") {
        this->name = name;
        n = 0;
        books = new Book[n];
    }

    Library &operator+=(const Book &b) {
        for (int i = 0; i < n; i++) {
            if (books[i] == b) {
                throw BookAlreadyExistsException(b);
            }
        }
        Book *temp = new Book[n + 1];
        for (int i = 0; i < n; i++) {
            temp[i] = books[i];
        }
        temp[n] = b;
        n++;
        delete [] books;
        books = temp;
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Library &l) {
        out << l.name << endl;
        for (int i = 0; i < l.n; i++) {
            out << l.books[i] << endl;
        }
        return out;
    }

    Book *getBooksByAuthor(string &author, int &numberFound) {
        numberFound = 0;
        for (int i = 0; i < n; i++) {
            if (books[i].getAuthor() == author) {
                numberFound++;
            }
        }

        Book *result = new Book [numberFound];
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (books[i].getAuthor() == author) {
                result[j++] = books[i];
            }
        }
        if (numberFound == 0) {
            return nullptr;
        } else {
            return result;
        }
    }
};

void wtf() {
    ofstream fout("input.txt");

    string fname, lname;
    int points;
    string line;

    while (getline(std::cin, line)) {
        if (line == "----") {
            break;
        }
        fout << line << endl;
    }
}

void rff1() {
    ifstream fin("output1.txt");
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
}

void rff2() {
    ifstream fin("output2.txt");
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
}

int main() {
    wtf(); //ja kreira datotekata input.txt
    //YOUR CODE STARTS HERE

    ifstream ifs("input.txt");
    string libraryName;
    getline(ifs, libraryName);

    Library library(libraryName);

    int n;
    ifs >> n;
    ifs.ignore();

    string t, a;
    int year;
    for (int i = 0; i < n; i++) {
        getline(ifs, t);
        getline(ifs, a);
        ifs >> year;
        ifs.ignore();

        //cout << t << " " << a << " " << year << endl;

        Book b(t, a, year);
        try {
            library += b;
        } catch (BookAlreadyExistsException &e) {
            e.message();
        }
    }
    ifs.close();

    ofstream fout1("output1.txt");
    fout1 << library;
    fout1.close();


    //DO NOT MODIFY THE NEXT PART

    string author;
    getline(std::cin, author);

    //DO NOT MODIFY THE PART ABOVE, CONTINUE AFTER THIS COMMENT

    ofstream fout2("output2.txt");
    Book *result = library.getBooksByAuthor(author, n);
    if (result == nullptr) {
        fout2 << "None" << endl;
    } else {
        for (int i = 0; i < n; i++) {
            fout2 << result[i] << endl;
        }
    }
    fout2.close();

    //YOUR CODE ENDS HERE
    rff1();
    cout << "Books written by " << author << " are: " << endl;
    rff2();

    return 0;
}
