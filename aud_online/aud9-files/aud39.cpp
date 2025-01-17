#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

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

class Book {
private:
    string title;
    string author;
    int year;

public:
    Book(string title = "", string author = "", int year = 1900) {
        this->title = title;
        this->author = author;
        this->year = year;
    }

    friend ostream &operator<<(ostream &out, const Book &book) {
        return out << book.title << " " << book.author << " " << book.year;
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
        Book *temp = new Book[n + 1];
        for (int i = 0; i < n; i++) {
            temp[i] = books[i];
        }
        temp[n++] = b;
        delete [] books;
        books = temp;
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Library &library) {
        out << library.name << endl;
        for (int i = 0; i < library.n; i++) {
            out << library.books[i] << endl;
        }
        return out;
    }
};

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

    string a;
    string t;
    int year;
    for (int i = 0; i < n; i++) {
        getline(ifs, t);
        getline(ifs, a);
        cin >> year;
        ifs.ignore();

        cout << t << " " << a << " " << year << endl;
    }


    //DO NOT MODIFY THE NEXT PART

    string author;
    getline(std::cin, author);

    //DO NOT MODIFY THE PART ABOVE, CONTINUE AFTER THIS COMMENT


    //YOUR CODE ENDS HERE
    rff1();
    cout << "Books written by " << author << " are: " << endl;
    rff2();

    return 0;
}
