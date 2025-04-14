/*
Define the class SMS, where information about the message date (an object of the Date class),
message content (an array of 150 characters), and two phone numbers (textual arrays of 10 digits
for the sender and the receiver) are stored.
The Date class should contain three integers for day, month, and year. (5 points)
Write a main function in which an integer N (max 500) is read, followed by information for
N messages. Reading a single message is in the following format:
-dd mm yyyy
-sender_number
-receiver_number
-content. (10 points)
Then, another date should be read, indicating the start of the time period from that date until today.
Example input:
18 03 2016
070211123
071300400
I'll call you back
.... messages
18 12 2017
070211123
071300400
hahah
11 11 2015
Print all messages shorter than 70 characters made after the entered date (excluding messages on
that exact date). Use a separate function that takes as arguments: an array of objects of the SMS
class, the size of the message array (an integer), and a date (an object of the Date class)
indicating the start of the time period. If there are no messages meeting the specified conditions,
print an appropriate message. (15 points)
The printing format should be seen from the test examples.
HINT: Include the library #include <iomanip> to print dates using the command
cout << setfill('0') << setw(2) << day << "/" << setfill('0') << setw(2) << month << "/" << year
 */


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
