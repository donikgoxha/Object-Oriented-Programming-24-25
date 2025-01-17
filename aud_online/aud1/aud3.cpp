#include <iostream>
#include <string.h>
using namespace std;

//links to the lessons
//https://finki-mk.github.io/OOP/html5/oop_av3.html
//https://bbb-lb.finki.ukim.mk/playback/presentation/2.3/9111e1b452b190f16e6faecde632b78dd975ea9c-1615368406409?meetingId=9111e1b452b190f16e6faecde632b78dd975ea9c-1615368406409
//https://bbb-lb.finki.ukim.mk/playback/presentation/2.3/9111e1b452b190f16e6faecde632b78dd975ea9c-1615371630474?meetingId=9111e1b452b190f16e6faecde632b78dd975ea9c-1615371630474


//zadaca 3
class EmailMessage {
private:
    char sender[50];
    char receiver[50];
    char subject[50];
    char text[300];

public:
    EmailMessage(char *ssender = "info@finki.ukim.mk",
                 char *rreceiver = "donik@finki.ukim.mk",
                 char *ssubject = "Hello",
                 char *ttext = "okokok") {
        strcpy(sender, ssender);
        strcpy(receiver, rreceiver);
        strcpy(subject, ssubject);
        strcpy(text, ttext);
    }

    ~EmailMessage() {
    }

    void show() {
        cout << "From:      \t" << sender << endl;
        cout << "To:        \t" << receiver << endl;
        cout << "-----------------------------------------------------------" << endl;
        cout << "Subject:   \t" << subject << endl;
        cout << "-----------------------------------------------------------" << endl;
        cout << "Text: " << endl;
        cout << text << endl;
    }
};

bool valid(char mailAddress[50]) {
    //short way and more efficient
    char *ptr = strstr(mailAddress, "@");
    if (ptr == nullptr) {
        return false;
    }
    return strstr(ptr, ".") != nullptr;

    //long way and more annoying
    // int index = -1;
    // for (int i = 0; i < strlen(mailAddress); i++) {
    //     if (mailAddress[i] == '@') {
    //         index = i;
    //         break;
    //     }
    // }
    // if (index == -1) {
    //     //we haven't found @
    //     return false;
    // } else {
    //     for (int i = index; i < strlen(mailAddress); i++) {
    //         if (mailAddress[i] == '.') {
    //             return true;
    //         }
    //     }
    //     return false;
    // }
}

int main() {
    char sender[50];
    char receiver[50];
    char subject[50];
    char text[300];
    cin >> sender >> receiver;
    if (!valid(sender) || !valid(receiver)) {
        cout << "Sender or Receiver has an invalid address" << endl;
        return 0;
    }
    cin >> subject;
    //cin.getline(subject, 50);
    cin.getline(text, 300);
    EmailMessage em(sender, receiver, subject, text);
    em.show();
    return 0;
}
