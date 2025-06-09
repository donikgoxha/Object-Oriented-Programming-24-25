#include <iostream>
#include <cstring>
using namespace std;

struct Player {
    char korisnickoIme[15];
    int nivo;
    int poeni;
};

struct ComputerGame {
    char ime[20];
    Player lista[30];
    int n; // number of players
};

void bestPlayer(ComputerGame *array, int n) {
    int maxPlayers = -1;
    int indexPopularGame = -1;

    // Step 1: Find the most popular game (greatest number of players)
    for (int i = 0; i < n; i++) {
        if (array[i].n > maxPlayers) {
            maxPlayers = array[i].n;
            indexPopularGame = i;
        }
    }

    // Step 2: In that game, find the player with the most points
    Player best = array[indexPopularGame].lista[0];
    for (int i = 1; i < array[indexPopularGame].n; i++) {
        Player current = array[indexPopularGame].lista[i];
        if (current.poeni > best.poeni) {
            best = current;
        } else if (current.poeni == best.poeni && current.nivo > best.nivo) {
            best = current;
        }
    }

    // Step 3: Print the result
    cout << "Najdobar igrac e igracot so korisnicko ime " << best.korisnickoIme
            << " koj ja igra igrata " << array[indexPopularGame].ime << endl;
}

int main() {
    int n, m;
    char ime[20];
    cin >> n;
    //create an array of max 100 computer games;
    ComputerGame poleigri[100];
    for (int i = 0; i < n; i++) {
        ComputerGame nova;
        cin >> nova.ime >> nova.n;
        Player pole[30];
        for (int j = 0; j < nova.n; j++) {
            Player nov;
            cin >> nov.korisnickoIme >> nov.nivo >> nov.poeni;
            nova.lista[j] = nov;
        }
        poleigri[i] = nova;
    }

    bestPlayer(poleigri, n);
    return 0;
}
