// Links to the lessons
// https://finki-mk.github.io/OOP/html5/oop_av9.html
//pt.1: https://finkiukim-my.sharepoint.com/personal/stefan_andonov_finki_ukim_mk/_layouts/15/stream.aspx?id=%2Fpersonal%2Fstefan%5Fandonov%5Ffinki%5Fukim%5Fmk%2FDocuments%2FRecordings%2FOOP%20grupa%203%20AV11%202022%20snimki%2FOOP%20GR3%20AV11%2D20220511%5F150723%2DMeeting%20Recording%2Emp4&referrer=StreamWebApp%2EWeb&referrerScenario=AddressBarCopied%2Eview%2Ed5942334%2D5364%2D45b2%2D82f7%2Dcfe723fb3c79
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

class NotValidUsernameException {
private:
    char notValidUsername[80];

public:
    NotValidUsernameException(char *email = "test@test.com") {
        strcpy(notValidUsername, email);
    }

    void showMessage() {
        cout << notValidUsername << " is not valid! You must enter a valid username. " << endl;
    }
};


class User {
protected:
    int id;
    char username[50];
    static int ID_TRACKER;

public:
    User(char *username = "test") {
        bool atSignFound = false;
        bool dotSignFound = false;
        for (int i = 0; i < strlen(username); i++) {
            if (username[i] == '@') {
                atSignFound = true;
            }
            if (atSignFound) {
                if (username[i] == '.') {
                    dotSignFound = true;
                }
            }
        }
        if (!atSignFound || !dotSignFound) {
            throw NotValidUsernameException(username);
        }

        strcpy(this->username, username);
        this->id = ID_TRACKER++;
    }

    void print() {
        cout << id << " " << username << endl;
    }
};

int User::ID_TRACKER = 1;


int main() {
    try {
        User u1("stefan@finki.com"); // ID = 1
        u1.print();
        User u2("trajce@finki.com"); // ID = 2
        u2.print();
        User u3("petko"); // ID = 3
        u3.print();
    } catch (NotValidUsernameException e) {
        e.showMessage();
    }

    return 0;
}
