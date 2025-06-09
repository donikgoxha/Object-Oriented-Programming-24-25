// Да се дефинира класа Book која ќе претставува една книга. Треба да ги содржи следните полиња:
// title, насловот на книгата (string)
// author, авторот на книгата (string)
// За класата треба да се дефинира параметризиран конструктор и метод print().
// Да се дефинира класа DigitalCopy, која ќе ги претставува дигиталните параметри на книгата.
// Таа треба да ги содржи следните полиња:
// fileSize, големината на датотеката во MB (double)
// formats, низа од 3 стрингови кои ги претставуваат поддржаните формати (на пример: "PDF", "EPUB", "MOBI")
// За класата треба да се дефинира параметризиран конструктор и метод print(). Во конструкторот треба да се провери:
// fileSize да е поголем од 0 и помал од 1000 MB – во спротивно, да се фрли исклучок од тип InvalidFileSizeException.
// Секој формат да биде "PDF", "EPUB" или "MOBI" – во спротивно, да се фрли исклучок од тип InvalidFormatException.
// Исклучоците треба да се фатат во main() функцијата, каде ќе се читаат податоци за n дигитални книги.
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class InvalidFileSizeException {
public:
    void print() const {
        cout << "Invalid File Size" << endl;
    }
};

class InvalidFormatException {
public:
    void print() const {
        cout << "Invalid Format" << endl;
    }
};

class Book {
protected:
    string title;
    string author;

public:
    Book(const string &title = "", const string &author = "") {
        this->title = title;
        this->author = author;
    }

    virtual void print() const {
        cout << title << " " << author << endl;
    }
};

class DigitalCopy {
protected:
    double fileSize;
    string formats[3];

public:
    DigitalCopy(double fileSize = 0.0, const string *formats = nullptr) {
        if (fileSize <= 0 || fileSize >= 1000) {
            throw InvalidFileSizeException();
        }
        this->fileSize = fileSize;

        for (int i = 0; i < 3; i++) {
            if (formats[i] != "PDF" && formats[i] != "EPUB" && formats[i] != "MOBI") {
                throw InvalidFormatException();
            }
            this->formats[i] = formats[i];
        }
    }

    void print() const {
        cout << "File size: " << fileSize << "MB" << endl;
        cout << "Formats: ";
        for (int i = 0; i < 3; ++i) {
            cout << formats[i];
            if (i < 2) cout << ", ";
        }
        cout << endl;
    }
};

class EBook : public Book, public DigitalCopy {
public:
    EBook(string title, string author, double fileSize, string formats[3])
        : Book(title, author), DigitalCopy(fileSize, formats) {
    }

    void print() const override {
        cout << "EBook:" << endl;
        Book::print();
        DigitalCopy::print();
    }
};

class AudioBook : public Book, public DigitalCopy {
public:
    AudioBook(string title, string author, double fileSize, string formats[3])
        : Book(title, author), DigitalCopy(fileSize, formats) {
    }

    void print() const override {
        cout << "AudioBook:" << endl;
        Book::print();
        DigitalCopy::print();
    }
};

int main() {
    int n;
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; ++i) {
        string title, author;
        double fileSize;
        string formats[3];

        getline(cin, title);
        getline(cin, author);
        cin >> fileSize;

        for (int j = 0; j < 3; ++j) {
            cin >> formats[j];
        }
        cin.ignore();

        try {
            if (i % 2 == 0) {
                EBook eb(title, author, fileSize, formats);
                eb.print();
            } else {
                AudioBook ab(title, author, fileSize, formats);
                ab.print();
            }
        } catch (InvalidFileSizeException &e) {
            e.print();
        }
        catch (InvalidFormatException &e) {
            e.print();
        }
    }

    return 0;
}
