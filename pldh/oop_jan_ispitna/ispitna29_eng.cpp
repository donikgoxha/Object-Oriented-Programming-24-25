#include <iostream>
#include <cstring>
using namespace std;

// your code here
class Parcel {
protected:
    int parcelID;
    static int processingPrice;

public:
    Parcel(int parcelID = 0) {
        this->parcelID = parcelID;
    }

    int getId() {
        return parcelID;
    }

    static int setProcessingPrice(int price) {
        processingPrice = price;
    }

    static int getProcessingPrice() {
        return processingPrice;
    }
};


class Envelope : public Parcel {
private:
    int width;
    int height;
    char receiver[50];

public:
    Envelope(int parcelID = 0, const char *receiver = "", int height = 0, int width = 0) : Parcel(parcelID) {
        this->width = width;
        this->height = height;
        strcpy(this->receiver, receiver);
    }

    const char *getReceiver() const {
        return receiver;
    }

    double price() const {
        return getProcessingPrice() + width * height * 0.3;
    }
};

class PostOffice {
private:
    Envelope *envelopes[100];
    int count;

public:
    PostOffice() : count(0) {
    }

    int sendEnvelope(int id, const char *receiver, int length, int width) {
        if (count >= 100) return 0;
        envelopes[count] = new Envelope(id, receiver, length, width);
        double price = envelopes[count]->price();
        count++;
        return price;
    }

    void printEnvelopsTo(const char *receiver) const {
        cout << "For " << receiver << " are envelops with ids: ";
        for (int i = 0; i < count; i++) {
            if (strcmp(envelopes[i]->getReceiver(), receiver) == 0) {
                cout << envelopes[i]->getId() << " ";
            }
        }
        cout << endl;
    }

    ~PostOffice() {
        for (int i = 0; i < count; i++) {
            delete envelopes[i];
        }
    }
};

int Parcel::processingPrice = 150;

int main() {
    int type;
    int n;
    int price;
    int id;
    int height, width;
    char receiver[50];

    PostOffice p;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> type;
        if (type == 1) {
            // send envelope
            cin >> id >> receiver >> width >> height;
            cout << "The price of sending envelope with id " << id << " is:" << p.sendEnvelope(
                id, receiver, width, height) << endl;
        } else if (type == 2) {
            // print envelops to
            cin >> receiver;
            p.printEnvelopsTo(receiver);
        } else if (type == 3) {
            // set processing price
            cin >> price;
            Parcel::setProcessingPrice(price);
        } else if (type == 4) {
            // Parcel
            cin >> id;
            Parcel p1(id);
            cout << "Parcel with id [" << p1.getId() << "] is created" << endl;
        } else {
            // Envelope
            cin >> id >> receiver >> width >> height;
            Envelope p2(id, receiver, width, height);
            cout << "Price of sending envelope with ID: " << p2.getId() << " To: " << p2.getReceiver() << " is: " << (int)p2.
                    price() << endl;
        }
    }
    return 0;
}
