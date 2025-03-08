#include <iostream>
#include <cstring>
using namespace std;

// Links to the lessons
// https://finki-mk.github.io/OOP/html5/oop_av4.html
// https://bbb-lb.finki.ukim.mk/playback/presentation/2.3/740dc1184c44f2d100ce97a5038744c4cd34f22a-1647438467490

class Team {
private:
    char name[50];
    int foundingYear;
    char city[50];

public:
    Team(char *nname = "", int ffoundingYear = 1990, char *ccity = "") {
        strcpy(name, nname);
        foundingYear = ffoundingYear;
        strcpy(city, ccity);
    }

    Team(const Team &t) {
        //cout << "Copy constructor" << endl;
        strcpy(name, t.name);
        foundingYear = t.foundingYear;
        strcpy(city, t.city);
    }

    ~Team() {
    }

    bool isEqual(Team other) {
        return strcmp(name, other.name) == 0;
    }

    void print() {
        cout << name << endl;
    }

    void setName(const char *n) {
        strcpy(name, n);
    }
};

class Game {
private:
    Team homeTeam;
    Team awayTeam;
    int homeGoals;
    int awayGoals;

public:
    Game() {
        homeGoals = 0;
        awayGoals = 0;
    }

    Game(Team hhomeTeam, Team aawayTeam, int hhomeGoals, int aawayGoals) {
        homeTeam = hhomeTeam;
        awayTeam = aawayTeam;
        homeGoals = hhomeGoals;
        awayGoals = aawayGoals;
    }

    Game(const Game &g) {
        //cout << "Copy constructor" << endl;
        homeTeam = g.homeTeam;
        awayTeam = g.awayTeam;
        homeGoals = g.homeGoals;
        awayGoals = g.awayGoals;
    }

    ~Game() {
    }

    bool isRematch(Game other) {
        return homeTeam.isEqual(other.awayTeam) && awayTeam.isEqual(other.homeTeam);
    }

    friend Team duel(Game first, Game second);
};

Team duel(Game first, Game second) {
    if (first.isRematch(second)) {
        int goalsOFirstTeam = first.homeGoals + second.awayGoals;
        int goalsOfSecondTeam = second.homeGoals + first.awayGoals;

        if (goalsOFirstTeam > goalsOfSecondTeam) {
            return first.homeTeam;
        } else if (goalsOFirstTeam < goalsOfSecondTeam) {
            return second.homeTeam;
        } else {
            return nullptr;
        }
    } else {
        return nullptr;
    }
}

int main() {
    Team team1("Barca", 1899, "Barcelona");
    Team team2("Real Madrid", 1888, "Madrid");

    Team team3(team2);
    team3.setName("Chelsea");

    Game firstGame(team1, team2, 10, 5);
    Game secondGame(team2, team3, 4, 6);

    cout << firstGame.isRematch(secondGame) << endl;

    duel(firstGame, secondGame).print();
    return 0;
}
