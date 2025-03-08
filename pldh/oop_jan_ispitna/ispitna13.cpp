#include <iostream>
#include <cstring>
using namespace std;
//zad14 ispitni/kolokviumski

class SMS {
protected:
    char phoneNumber[15];
    float basePrice;
    const static float TAX;

public:
    SMS(const char *phone, float price) {
        strncpy(phoneNumber, phone, 15);
        basePrice = price;
    }

    virtual float SMS_cena() = 0;

    friend ostream &operator<<(ostream &out, SMS &s) {
        return out << "Tel: " << s.phoneNumber << " - cena: " << s.SMS_cena() << "den." << endl;
    }

    virtual ~SMS() {
    }
};

class RegularSMS : public SMS {
private:
    char *message;
    bool roaming;
    static float rPercent;

public:
    RegularSMS(const char *phone, float price, const char *msg, bool isRoaming)
        : SMS(phone, price) {
        message = new char[strlen(msg) + 1];
        strcpy(message, msg);
        roaming = isRoaming;
    }

    static void set_rProcent(int p) {
        rPercent = p / 100.0f;
    }

    float SMS_cena() override {
        int numMessages = (strlen(message) - 1) / 160 + 1;
        float price = basePrice * numMessages;

        if (roaming) {
            price *= (1 + rPercent);
        } else {
            price *= (1 + TAX);
        }

        return price;
    }

    ~RegularSMS() {
        delete[] message;
    }
};

class SpecialSMS : public SMS {
private:
    bool humanitarian;
    static float sPercent;

public:
    SpecialSMS(const char *phone, float price, bool isHumanitarian)
        : SMS(phone, price) {
        humanitarian = isHumanitarian;
    }

    static void set_sProcent(int p) {
        sPercent = p / 100.0f;
    }

    float SMS_cena() override {
        float price = basePrice;

        if (!humanitarian) {
            price *= (1 + sPercent);
            price *= (1 + TAX);
        }

        return price / (TAX);
    }
};


void vkupno_SMS(SMS **poraka, int n) {
    int regularCount = 0;
    float regularTotal = 0;
    int specialCount = 0;
    float specialTotal = 0;

    for (int i = 0; i < n; i++) {
        RegularSMS *regular = dynamic_cast<RegularSMS *>(poraka[i]);
        if (regular) {
            regularCount++;
            regularTotal += regular->SMS_cena();
        } else {
            specialCount++;
            specialTotal += poraka[i]->SMS_cena();
        }
    }

    cout << "Vkupno ima " << regularCount << " regularni SMS poraki i nivnata cena e: " << regularTotal << endl;
    cout << "Vkupno ima " << specialCount << " specijalni SMS poraki i nivnata cena e: " << specialTotal << endl;
}

const float SMS::TAX = 0.18f;
float RegularSMS::rPercent = 3.0f;
float SpecialSMS::sPercent = 1.5f;

int main() {
    char tel[20], msg[1000];
    float cena;
    float price;
    int p;
    bool roam, hum;
    SMS **sms;
    int n;
    int tip;

    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "====== Testing RegularSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++) {
            cin >> tel;
            cin >> cena;
            cin.get();
            cin.getline(msg, 1000);
            cin >> roam;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new RegularSMS(tel, cena, msg, roam);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i < n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 2) {
        cout << "====== Testing SpecialSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++) {
            cin >> tel;
            cin >> cena;
            cin >> hum;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new SpecialSMS(tel, cena, hum);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i < n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 3) {
        cout << "====== Testing method vkupno_SMS() ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++) {
            cin >> tip;
            cin >> tel;
            cin >> cena;
            if (tip == 1) {
                cin.get();
                cin.getline(msg, 1000);
                cin >> roam;

                sms[i] = new RegularSMS(tel, cena, msg, roam);
            } else {
                cin >> hum;

                sms[i] = new SpecialSMS(tel, cena, hum);
            }
        }

        vkupno_SMS(sms, n);
        for (int i = 0; i < n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 4) {
        cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        sms1 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        cin >> p;
        RegularSMS::set_rProcent(p);
        sms2 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms2;

        delete sms1, sms2;
    }
    if (testCase == 5) {
        cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin >> hum;
        sms1 = new SpecialSMS(tel, cena, hum);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin >> hum;
        cin >> p;
        SpecialSMS::set_sProcent(p);
        sms2 = new SpecialSMS(tel, cena, hum);
        cout << *sms2;

        delete sms1, sms2;
    }

    return 0;
}
