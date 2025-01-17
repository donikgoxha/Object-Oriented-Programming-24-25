#include <iostream>
#include <cstring>
using namespace std;

void test(int k);

class TennisPlayer {
private:
    char name[20];
    char surname[20];
    int rank;
    int matchesPlayed;
    int matchesWon;

public:
    TennisPlayer() {
        strcpy(name, "");
        strcpy(surname, "");
        rank = 0;
        matchesPlayed = 0;
        matchesWon = 0;
    }

    ~TennisPlayer() {
    }

    int getRank() const {
        return rank;
    }

    void setRank(int rank) {
        this->rank = rank;
    }

    int getMatchesPlayed() const {
        return matchesPlayed;
    }

    void setMatchesPlayed(int matches_played) {
        matchesPlayed = matches_played;
    }

    int getMatchesWon() const {
        return matchesWon;
    }

    void setMatchesWon(int matches_won) {
        matchesWon = matches_won;
    }

    char *getName() const {
        return (char *) name;
    }

    void setName(const char *n) {
        strncpy(name, n, 19);
        name[19] = '\0';
    }

    char *getSurname() const {
        return (char *) surname;
    }

    void setSurname(const char *s) {
        strncpy(surname, s, 19);
        surname[19] = '\0';
    }

    int findPercentageWins() {
        if (matchesPlayed == 0) {
            return 0;
        }
        return (matchesWon * 100) / matchesPlayed;
    }
};

void printHighestRankedPlayerBelow50PercentWins(TennisPlayer *players, int n) {

    TennisPlayer *bestPlayer = nullptr;
    for (int i = 0; i < n; i++) {
        if (players[i].findPercentageWins() < 50) {
            bestPlayer = &players[i];
            break;
        }
    }

    for (int i = 0; i < n; i++) {
        if (players[i].findPercentageWins() < 50 &&
            (bestPlayer == nullptr || players[i].getRank() < bestPlayer->getRank())) {
            bestPlayer = &players[i];
        }
    }

    if (bestPlayer == nullptr) {
        cout << "No such tennis player." << endl;
    } else {
        cout << bestPlayer->getName() << " " << bestPlayer->getSurname() << endl;
    }
}


int main() {
    int testCase;
    cin >> testCase;

    if (testCase == 0 || testCase == 1) {
        test(testCase);
        return 0;
    }

    int n;
    cin >> n;

    TennisPlayer *players = new TennisPlayer[n];

    for (int i = 0; i < n; i++) {
        char name[20], surname[20];
        int rank, matchesPlayed, matchesWon;

        cin >> name >> surname >> rank >> matchesPlayed >> matchesWon;

        players[i].setName(name);
        players[i].setSurname(surname);
        players[i].setRank(rank);
        players[i].setMatchesPlayed(matchesPlayed);
        players[i].setMatchesWon(matchesWon);
    }

    printHighestRankedPlayerBelow50PercentWins(players, n);

    delete[] players;
    return 0;
}

void test(int k) {
    if (k == 0) {
        cout << "Testing default constructor and getters/setters" << endl;
        cout << "---" << endl;
        TennisPlayer player = TennisPlayer();
        player.setName(new char[5]{'J', 'o', 'h', 'n', '\0'});
        player.setSurname(new char[5]{'D', 'o', 'e', '\0'});
        player.setRank(55);
        player.setMatchesPlayed(100);
        player.setMatchesWon(50);
        cout << "Full name: " << player.getName() << " " << player.getSurname() << endl;
        cout << "Rank and won matches out of total: " << player.getRank() << " " << player.getMatchesWon() << "/"
                << player.getMatchesPlayed() << endl;
    } else if (k == 1) {
        cout << "Testing findPercentageWins function" << endl;
        cout << "---" << endl;
        TennisPlayer player = TennisPlayer();
        player.setName(new char[5]{'J', 'o', 'h', 'n', '\0'});
        player.setSurname(new char[5]{'D', 'o', 'e', '\0'});
        player.setRank(55);
        player.setMatchesPlayed(100);
        player.setMatchesWon(50);
        if (player.findPercentageWins() != 50) {
            cout << "Test case failed." << endl;
            cout << "Expected: " << 0.5 << "; Got: " << player.findPercentageWins() << endl;
            return;
        }
        player.setMatchesWon(90);
        if (player.findPercentageWins() != 90) {
            cout << "Test case failed." << endl;
            cout << "Expected: " << 0.9 << "; Got: " << player.findPercentageWins() << endl;
            return;
        }
        cout << "Passed." << endl;
    }
}
