// Links to the lessons
// https://finki-mk.github.io/OOP/html5/oop_av7.html

// https://bbb-lb.finki.ukim.mk/playback/presentation/2.3/740dc1184c44f2d100ce97a5038744c4cd34f22a-1650458798901

#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;


class TennisPlayer {
protected:
    char name[50];
    bool playsInLeague;

public:
    TennisPlayer(char *name = "", bool playsInLeague = false) {
        strcpy(this->name, name);
        this->playsInLeague = playsInLeague;
    }

    TennisPlayer(const TennisPlayer &p) {
        strcpy(this->name, p.name);
        this->playsInLeague = p.playsInLeague;
    }

    friend ostream &operator <<(ostream &out, const TennisPlayer &tp) {
        return out << "Tennis player " << tp.name << " "
               << (tp.playsInLeague ? "plays in league" : "doesn't play in league");
    }
};

class RankedTennisPlayer : public TennisPlayer {
private:
    int rank;

public:
    RankedTennisPlayer(char *name = "", bool playsInLeague = false, int rank = 100)
        : TennisPlayer(name, playsInLeague) {
        this->rank = rank;
    }

    RankedTennisPlayer(const TennisPlayer &tp, int rank) : TennisPlayer(tp) {
        this->rank = rank;
    }

    RankedTennisPlayer(const RankedTennisPlayer &other) : TennisPlayer(other) {
        this->rank = other.rank;
    }

    friend ostream &operator <<(ostream &out, const RankedTennisPlayer &rtp) {
        out << "Ranked ";
        TennisPlayer tmp(rtp);
        out << tmp << ", is ranked " << rtp.rank;
        return out;
    }

    ~RankedTennisPlayer() {
    }
};

int main() {
    //    TennisPlayer tp("Novak Djokovic", true);
    //    cout << tp << endl;
    //    RankedTennisPlayer rtp (tp, 1);
    //    cout << rtp << endl;

    RankedTennisPlayer rtp("Novak Djokovic", true, 1);
    cout << rtp << endl;

    TennisPlayer tp = rtp;
    //cout << tp;
    return 0;
}
