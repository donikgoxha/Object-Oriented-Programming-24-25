/*
*link to the lesson: https://bbb-lb.finki.ukim.mk/playback/presentation/2.3/740dc1184c44f2d100ce97a5038744c4cd34f22a-1648644753777

Да се креира класа Deposit во која се чуваат податоци за банкарски депозит и тоа:
износ на депозитот,
вид (денари, евра, долари) - енумерациски тип
каматна стапка (реален број меѓу 0 и 1)
времетраење на депозитот во години (цел број).
За класата да се дефинираат потребните конструктори и други потребни методи за точно функционирање на програмата. (5 поени) За класата да се обезбедат следните методи:
totalValue() - метод за пресметка на вкупниот изност на депозитот по завршување на периодот на орочувањето. Се пресметува по формулата:
 каде k е каматната стапка, а n е бројот на години на кој е орочен депозитот (10 поени)
interestAmount() - Ја пресметува заработката од депозитот. Се пресметува како разлика меѓу вкупната сума која се добива и почетниот влог на депозитот. (5 поени)
print() - за печатење на информациите за еден депозит во формат: (5 поени)
[тип на депозит]
Total Principal:  [почетен влог]
Total Value: [вкупен износ по истекот на времетраењето]
Total Interest: [износ на каматата која се заработува]

Потоа да се креира класа Branch во која се чуваат податоци за депозитите издадени од вработените во филијалата:
адреса на филијалата (низа од максимум 100 знаци)
динамички алоцирана низа од објекти од класата Deposit, како и број на елементи во низата (цел број).
За класата да се обезбедат конструктори, деструктор, set и get методи потребни за точно функционирање на програмата. (5 поени) За класата да се обезбедат и следниве методи:
newDeposit(Deposit& d) - за додавање на нов кредит во низата. (5 поени)
depositAnalysis(int v) - за наоѓање и печатење на информациите за кредитот со највисок износ на камата за категоријата одредена од влезниот аргумент (1-денари, 2-евра, 3-долари). Ако се внесе вид на депозит што не е еден од наведените, треба да се испечати порака “Error!”. Доколку низата не содржи депозит од валутата проследена преку влезниот аргумент, се печати порака “Ne postoi aktiven deposit vo EUR/MKD/USD!” (10 поени)
print() - за печатење на податоците за филијалата како и информации за сите депозити што ги издала (5 поени)
  [Адреса на филијала]:
  1. [Кредит1]
  2. [Кредит2]
  3. [Кредит3]
  ...
За целосна функционалност на програмата (5 поени)
***Напомена: Можете да користите помошни функции од библиотеката cmath***
Get the main from down there
 */

#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

enum type { DENARS = 1, EUROS = 2, DOLLARS = 3 };

class Deposit {
private:
    double amount;
    type type;
    double interest;
    int duration;

public:
    Deposit(double amount = 0, enum type type = DENARS, double interest = 0.1, int duration = 1) {
        this->amount = amount;
        this->type = type;
        this->interest = interest;
        this->duration = duration;
    }

    Deposit(const Deposit &d) {
        this->amount = d.amount;
        this->type = d.type;
        this->interest = d.interest;
        this->duration = d.duration;
    }


    double totalValue() {
        return amount * pow((1 + interest), duration);
    }

    double interestAmount() {
        return totalValue() - amount;
    }

    void print() {
        switch (type) {
            case DENARS:
                cout << "Denarski depozit" << endl;
                break;
            case EUROS:
                cout << "Devizen depozit vo EUR" << endl;
                break;
            default:
                cout << "Devizen depozit vo USD" << endl;
                break;
        }
        cout << "Total Principal: " << amount << endl;
        cout << "Total Value: " << totalValue() << endl;
        cout << "Total Interest: " << interestAmount() << endl;
    }

    enum type getType() {
        return type;
    }
};

class Branch {
private:
    char address[100];
    Deposit *deposits;
    int count;

    void copy(const Branch &b) {
        strcpy(this->address, b.address);
        this->count = b.count;
        this->deposits = new Deposit[this->count];
        for (int i = 0; i < this->count; i++) {
            this->deposits[i] = b.deposits[i];
        }
    }

public:
    Branch(char *address = "") {
        strcpy(this->address, address);
        count = 0;
        deposits = new Deposit[count];
    }

    Branch(const Branch &b) {
        copy(b);
    }

    Branch &operator=(const Branch &b) {
        if (this != &b) {
            delete [] deposits;
            copy(b);
        }
        return *this;
    }

    ~Branch() {
        delete[] deposits;
    }

    void newDeposit(const Deposit &newOne) {
        Deposit *tmp = new Deposit[count + 1];
        for (int i = 0; i < count; i++) {
            tmp[i] = deposits[i];
        }
        tmp[count++] = newOne;
        delete[] deposits;
        deposits = tmp;
    }

    void depositAnalysis(int v) {
        if (v < 0 || v > 3) {
            cout << "Error!" << endl;
            return;
        }
        bool found = false;
        Deposit max;
        for (int i = 0; i < count; i++) {
            if (deposits[i].getType() == (type) v) {
                if (!found) {
                    max = deposits[i];
                    found = true;
                } else {
                    if (deposits[i].interestAmount() > max.interestAmount()) {
                        max = deposits[i];
                    }
                }
            }
        }

        if (found) {
            max.print();
        } else {
            cout << "Ne postoi aktiven depozit vo ";
            switch (v) {
                case 1:
                    cout << "MKD!" << endl;
                    break;
                case 2:
                    cout << "EUR!" << endl;
                    break;
                default:
                    cout << "USD!" << endl;
                    break;
            }
        }
    }

    void print() {
        cout << address << endl;
        for (int i = 0; i < count; i++) {
            cout << i + 1 << ". ";
            deposits[i].print();
        }
    }

    int countAllFromType(type type) {
        int counter = 0;
        for (int i = 0; i < count; i++) {
            if (deposits[i].getType() == type) {
                counter++;
            }
        }
    }

    void removeAllDepositsFromType(type type) {
        Deposit *tmp = new Deposit[count - countAllFromType(type)];
        int j = 0;
        for (int i = 0; i < count; i++) {
            if (deposits[i].getType() != type) {
                tmp[j++] = deposits[i];
            }
        }
        count = j;
        delete[] deposits;
        deposits = tmp;
    }
};


int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, tip, godini;
    double iznos, kamata;
    char adresa[100];

    if (testCase == 1) {
        cout << "===== Testiranje na klasata Deposit ======" << endl;
        cin >> iznos >> kamata >> godini;
        cin >> tip; // 1-MKD, 2-EUR, 3-USD
        Deposit l(iznos, (type) tip, kamata, godini);
        cout << "Deposit constructor OK" << endl;
    } else if (testCase == 2) {
        cout << "===== Testiranje na klasata Deposit so dopolnitelni metodi ======" << endl;
        cin >> iznos >> kamata >> godini;
        cin >> tip; // 1-MKD, 2-EUR, 3-USD
        Deposit l(iznos, (type) tip, kamata, godini);
        l.print();
    } else if (testCase == 3) {
        cout << "===== Testiranje na klasata Branch so metodot print() ======" << endl;
        Branch b("Strumica");
        b.print();
    } else if (testCase == 4) {
        cout << "===== Testiranje na klasata Branch so metodot newDeposit() ======" << endl;
        Branch b("Strumica");
        cin >> n;
        for (int i = 0; i < n; i++) {
            //cin.get();
            cin >> iznos >> kamata >> godini;
            cin >> tip; // 1-MKD, 2-EUR, 3-USD
            Deposit l(iznos, (type) tip, kamata, godini);
            b.newDeposit(l);
        }
        b.print();
    } else if (testCase == 5) {
        cout << "===== Testiranje na metodot depositAnalysis() od klasata Branch ======" << endl;
        Branch b("Gevgelija");
        cin >> n;
        for (int i = 0; i < n; i++) {
            //cin.get();
            cin >> iznos >> kamata >> godini;
            cin >> tip; // 1-MKD, 2-EUR, 3-USD
            Deposit l(iznos, (type) tip, kamata, godini);
            b.newDeposit(l);
        }
        b.depositAnalysis(1);
        b.depositAnalysis(2);
        b.removeAllDepositsFromType((type) 2);
        b.depositAnalysis(2);
        b.depositAnalysis(3);
        b.depositAnalysis(4);
    } else if (testCase == 6) {
        cout << "===== Testiranje kompletna funkcionalnost ======" << endl;
        Branch b("Kavadarci");
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin.get();
            cin >> iznos >> kamata >> godini;
            cin >> tip; // 1-MKD, 2-EUR, 3-USD
            Deposit l(iznos, (type) tip, kamata, godini);
            b.newDeposit(l);
        }
        b.depositAnalysis(3);
        Branch b_new = b;
        b.print();
        b_new.print();

        //cin.get();
        cin >> iznos >> kamata >> godini;
        cin >> tip; // 1-MKD, 2-EUR, 3-USD
        Deposit l(iznos, (type) tip, kamata, godini);
        b.newDeposit(l);

        b.depositAnalysis(3);

        b.print();
        b_new.print();
    }
    return 0;
}
