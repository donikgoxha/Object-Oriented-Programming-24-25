#include <iostream>
#include <cstring>
#include <cctype>
#include <iomanip>
using namespace std;

class Date {
private:
    int d, m, y;

public:
    Date(int d = 1, int m = 1, int y = 2025) {
        this->d = d;
        this->m = m;
        this->y = y;
    }

    ~Date() = default;

    void print() {
        cout << setfill('0') << setw(2) << d << "/" << setfill('0') << setw(2) << m << "/" << y;
    }

    bool ifAfter(Date &other) {
        if (this->y > other.y) {
            return true;
        } else if (this->y < other.y) {
            return false;
        } else {
            //this->y == other.y
            if (this->m > other.m) {
                return true;
            } else if (this->m < other.m) {
                return false;
            } else {
                //this->m == other.m
                return this->d > other.d;
            }
        }
    }
};

class SMS {
private:
    Date d;
    char content[151];
    char sender[10];
    char receiver[10];

public:
    SMS(const Date &d = Date(), const char *content = "", const char *sender = "", const char *receiver = "") {
        this->d = d;
        strcpy(this->content, content);
        strcpy(this->sender, sender);
        strcpy(this->receiver, receiver);
    }

    ~SMS() = default;

    void print() {
        d.print();
        cout << " " << sender << " " << receiver << " " << content << endl;
    }

    char *getContent() {
        return content;
    }

    int getContentLength() {
        return strlen(content);
    }

    friend void filter(SMS *messages, int n, Date &start);
};

void filter(SMS *messages, int n, Date &start) {
    for (int i = 0; i < n; i++) {
        if (messages[i].getContentLength() < 70 && messages[i].d.ifAfter(start)) {
            messages[i].print();
        }
    }
}


int main() {
    int n;
    cin >> n;

    SMS messages[20];
    int d, m, y;
    char content[151];
    char sender[10];
    char receiver[10];

    for (int i = 0; i < n; i++) {
        cin >> d >> m >> y >> sender >> receiver;
        cin.ignore();
        cin.getline(content, 151);
        messages[i] = SMS(Date(d, m, y), content, sender, receiver);
        messages[i].print();
    }

    cin >> d >> m >> y;
    Date start(d, m, y);

    filter(messages, n, start);


    return 0;
}
