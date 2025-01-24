#include <fstream>
#include <cstring>
#include <iostream>
using namespace std;

class Date {
private:
    int d, m, y;

public:
    Date() {
    }

    Date(int dd, int mm, int yy) {
        d = dd;
        m = mm;
        y = mm;
    }

    ~Date() {
    }

    bool compare(Date &date) {
        return y == date.y && m == date.m && d == date.d;
    }

    friend ostream &operator<<(ostream &out, Date &f) {
        out << f.d << "/" << f.m << "/" << f.y;
        return out;
    }

    friend istream &operator>>(istream &in, Date &f) {
        in >> f.d;
        in >> f.m;
        in >> f.y;
        return in;
    }

    void read(ifstream &in) {
        in >> d >> m >> y;
        in.ignore();
    }
};


class Call {
protected:
    string telephoneNumber;
    int duration;
    Date date;

public:
    Call() = default;

    Call(const string &telephone_number, int duration, const Date &date)
        : telephoneNumber(telephone_number),
          duration(duration),
          date(date) {
    }

    ~Call() = default;

    string getTelephoneNumber() const {
        return telephoneNumber;
    }

    void setTelephoneNumber(const string &telephone_number) {
        telephoneNumber = telephone_number;
    }

    int getDuration() const {
        return duration;
    }

    void setDuration(const int duration) {
        this->duration = duration;
    }

    Date getDate() const {
        return date;
    }

    void setDate(const Date &date) {
        this->date = date;
    }

    void read(ifstream &in) {
        date.read(in);
        getline(in, telephoneNumber);
        in >> duration;
        in.ignore();
    }

    friend ostream &operator<<(ostream &out, Call &c) {
        return out << "Dialed Number: " << c.telephoneNumber << " " << c.duration << " sec, " << c.date << endl;
    }
};

class Log {
private:
    Call *calls;
    int n;

public:
    Log(const Call *c = nullptr, int n = 0) {
        this->n = n;
        this->calls = new Call[n];
        for (int i = 0; i < n; i++) {
            calls[i] = c[i];
        }
    }

    Log(const Log &l) {
        this->n = l.n;
        this->calls = new Call[n];
        for (int i = 0; i < n; i++) {
            calls[i] = l.calls[i];
        }
    }

    ~Log() {
        delete[]calls;
    }

    void read(ifstream &in) {
        in >> n;
        in.ignore();
        calls = new Call[n];
        for (int i = 0; i < n; i++) {
            calls[i].read(in);
        }
    }

    friend ostream &operator<<(ostream &out, Log &l) {
        for (int i = 0; i < l.n; i++) {
            out << l.calls[i];
        }
        return out;
    }

    Log daily(Date d) {
        int counter = 0;
        Call *temp = new Call [n];
        for (int i = 0; i < n; i++) {
            if (calls[i].getDate().compare(d)) {
                temp[counter++] = calls[i];
            }
        }
        Log log(temp, counter);
        return log;
    }
};


void wtf() {
    ofstream fout("prva.txt");
    string line;
    while (getline(std::cin, line)) {
        if (line == "----") {
            break;
        }
        fout << line << endl;
    }
}

void rff(string path) {
    ifstream fin(path);
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
}

int main() {
    wtf();

    Log log;
    ifstream in("prva.txt");
    ofstream fout("vtora.txt");
    ofstream fout2("treta.txt");

    log.read(in);
    in.close();

    fout << log;
    fout.close();


    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE NEXT COMMENT
    Date d;
    cin >> d;
    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE PREVIOUS COMMENT

    Log log1 = log.daily(d);
    fout2<<log1;
    fout2.close();


    //DO NOT MODIFY THE CODE BELLOW
    cout << "All the data for the log:" << endl;
    rff("vtora.txt");
    cout << "Calls on date " << d << endl;
    rff("treta.txt");
    return 0;
}
