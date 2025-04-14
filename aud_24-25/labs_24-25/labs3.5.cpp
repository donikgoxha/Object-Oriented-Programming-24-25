#include <iostream>
#include <cstring>
using namespace std;


class UserProfile;

class Achievement {
private:
    char name[100];
    char description[100];
    static int totalUserAchievements;

public:
    Achievement(const char *name = "", const char *description = "") {
        strcpy(this->name, name);
        strcpy(this->description, description);
    }

    Achievement(const Achievement &a) {
        strcpy(this->name, a.name);
        strcpy(this->description, a.description);
    }

    void print() const {
        cout << name << endl << description << endl;
    }

    static void incrementTotalUserAchievements() {
        totalUserAchievements++;
    }

    friend class UserProfile;

    friend void showAchievementsProgress(UserProfile profiles[], int n, Achievement achievements[], int m);
};

int Achievement::totalUserAchievements = 0;

class UserProfile {
private:
    char name[100];
    Achievement achievements[50];
    int n;

public:
    UserProfile(const char *name = "") {
        strcpy(this->name, name);
        n = 0;
    }

    void print() const {
        cout << "User: " << name << endl;
        cout << "Achievements: " << endl;
        for (int i = 0; i < n; i++) {
            cout << achievements[i].name << endl << achievements[i].description << endl;
        }
    }

    void addAchievement(const Achievement &achievement) {
        if (n < 50) {
            achievements[n++] = achievement;
            Achievement::totalUserAchievements++;
        }
    }

    friend void showAchievementsProgress(UserProfile profiles[], int n, Achievement achievements[], int m);
};


void showAchievementsProgress(UserProfile profiles[], int n, Achievement achievements[], int m) {
    // For each achievement from the external array.
    for (int i = 0; i < m; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < profiles[j].n; k++) {
                if (strcmp(profiles[j].achievements[k].name, achievements[i].name) == 0) {
                    count++;
                    break;
                }
            }
        }
        double percentage = 0.0;
        if (n > 0) {
            percentage = count * 100.0 / n;
        } else {
            percentage = 0;
        }
        cout << achievements[i].name << endl;
        cout << achievements[i].description << endl;
        cout << "---Percentage of users who have this achievement: " << percentage << "%" << endl;
    }
    double avg;
    if (n * m > 0)
        avg = Achievement::totalUserAchievements * 100.0 / (n * m);
    else
        avg = 0;

    cout << "------Average completion rate of the game: " << avg << "%" << endl;
}

// Don't modify
int main() {
    char testcase[100];
    cin.getline(testcase, 100);

    int n;
    cin >> n;
    cin.ignore();

    char ignore[100];
    cin.getline(ignore, 100);
    UserProfile users[100];
    for (int i = 0; i < n; ++i) {
        char name[100];
        cin >> name;
        users[i] = UserProfile(name);
    }

    int m;
    cin >> m;
    cin.ignore();

    cin.getline(ignore, 100);
    Achievement achievements[100];
    for (int i = 0; i < m; ++i) {
        char name[100], description[100];
        cin.getline(name, 100);
        cin.getline(description, 100);
        achievements[i] = Achievement(name, description);
    }

    int k;
    cin >> k;
    cin.ignore();

    cin.getline(ignore, 100);
    for (int i = 0; i < k; ++i) {
        int numUser, numAchievement;
        cin >> numUser >> numAchievement;
        numUser -= 1;
        numAchievement -= 1;
        users[numUser].addAchievement(achievements[numAchievement]);
    }

    if (testcase[8] == 'A') {
        // Testing Achievement methods.
        for (int i = 0; i < m; ++i) {
            achievements[i].print();
        }
        Achievement::incrementTotalUserAchievements();
    } else if (testcase[8] == 'U') {
        // Testing UserProfile methods.
        for (int i = 0; i < n; ++i) {
            users[i].print();
        }
    } else {
        // Testing showAchievementsProgress function.
        showAchievementsProgress(users, n, achievements, m);
    }

    return 0;
}
