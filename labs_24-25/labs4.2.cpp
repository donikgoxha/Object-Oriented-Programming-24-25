/*
Да се дефинира класа TableTennisPlayer која ќе чува информации за:
name (име на игра, низа од 50 знаци)
country (држава на играчот, низа од 50 знаци)

За класата да се обезбедат потребните конструктори, како и соодветни get,set методи
Да се имплементира метод print() што печати инфо. во следниот формат:
[име на играч] ([држава])

Да се дефинира класа TableTennisMatch која ќе чува информации за:
player1 (објект од класата TableTennisPlayer за првиот играч)
player2 (објект од класата TableTennisPlayer за вториот играч)
pointsPlayer1 (број на поени од првиот играч, цел број)
pointsPlayer2 (број на поени од вториот играч, цел број)
matchDate (датум на натпреварот, низа од 10 знаци во формат dd.mm.yyyy)

За класата да се обезбедат потребните конструктори, како и соодветни get,set методи
Да се имплементира метод print() што печати инфо. во следниот формат:
Match Date: [датум на натпреварот]
Match Details:
[име на првиот играч] ([држава]) - Points: [поени на првиот играч]
[име на вториот играч] ([држава]) - Points: [поени на вториот играч]

Во рамките на main функцијата да се чита цел број n (max 100), а потоа и информации за тие n
натпревари. Читањето на еден натпревар е во следниот формат:
datum
ime_na_prv_igrach
drzhava_na_prv_igrach
poeni_na_prv_igrach
ime_na_vtor_igrach
drzhava_na_vtor_igrach
poeni_na_vtor_igrach
 */

#include <iostream>
#include <cstring>
using namespace std;


class TableTennisPlayer {
private:
    char name[50]{};
    char country[50]{};

public:
    explicit TableTennisPlayer(const char *name = "", const char *country = "") {
        strcpy(this->name, name);
        strcpy(this->country, country);
    }

    const char *getName() { return name; }

    const char *getCountry() { return country; }

    void setName(const char *name) { strcpy(this->name, name); }

    void setCountry(const char *country) { strcpy(this->country, country); }

    void print() { cout << name << " (" << country << ")" << endl; }
};

class TableTennisMatch {
private:
    TableTennisPlayer p1;
    TableTennisPlayer p2;
    int pts1;
    int pts2;
    char date[11]{};

public:
    TableTennisMatch(const char *name1 = "", const char *country1 = "", const char *name2 = "",
                     const char *country2 = "",
                     int pts1 = 0, int pts2 = 0,
                     const char *date = "") {
        this->p1 = TableTennisPlayer(name1, country1);
        this->p2 = TableTennisPlayer(name2, country2);
        this->p1 = p1;
        this->p2 = p2;
        this->pts1 = pts1;
        this->pts2 = pts2;
        strcpy(this->date, date);
    }

    void setPlayer1(const TableTennisPlayer &p) { p1 = p; }
    void setPlayer2(const TableTennisPlayer &p) { p2 = p; }
    void setPointsPlayer1(int pts) { pts1 = pts; }
    void setPointsPlayer2(int pts) { pts2 = pts; }
    void setMatchDate(const char *date) { strcpy(this->date, date); }

    void print() {
        cout << "Match date: " << this->date << endl;
        //[име на првиот играч] ([држава]) - Points: [поени на првиот играч]
        cout << p1.getName() << " (" << p1.getCountry() << ")" << " - Points: " << pts1 << endl;
        cout << p2.getName() << " (" << p2.getCountry() << ")" << " - Points: " << pts2 << endl;
    }
};


int main() {
    int n;
    cin >> n;
    cin.ignore();

    TableTennisMatch matches[100];
    for (int i = 0; i < n; i++) {
        char name1[50]{};
        char country1[50]{};
        char name2[50]{};
        char country2[50]{};
        char date[11]{};
        int pts1, pts2;

        cin.getline(date, 11);
        cin.ignore();
        cin.getline(name1, 50);
        cin.getline(country1, 50);
        cin >> pts1;
        cin.ignore();
        cin.getline(name2, 50);
        cin.getline(country2, 50);
        cin >> pts2;
        cin.ignore();


        TableTennisPlayer p1(name1, country1);
        TableTennisPlayer p2(name2, country2);

        matches[i] = TableTennisMatch(name1, country1, name2, country2, pts1, pts2);
    }

    for (int i = 0; i < n; i++) {
        matches[i].print();
        cout << endl;
    }
    return 0;
}
