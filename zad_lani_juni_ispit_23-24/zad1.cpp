#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class Song {
private:
    string title;
    string author;
    string performer;
    int duration;

public:
    Song(const string &title = "", const string &author = "", const string &performer = "", int duration = 0) {
        this->title = title;
        this->author = author;
        this->performer = performer;
        this->duration = duration;
    }

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getPerformer() const { return performer; }
    int getDuration() const { return duration; }

    string setTitle(const string &t) { this->title = t; }
    string setAuthor(const string &a) { this->author = a; }
    string setPerformer(const string &p) { this->performer = p; }
    string setDuration(int d) { this->duration = d; }

    friend istream &operator>>(istream &in, Song &s) {
        in >> ws;
        getline(in, s.title);
        getline(in, s.author);
        getline(in, s.performer);
        in >> s.duration;
        in.ignore();
        return in;
    }

    void print(ofstream &out) {
        //Song title: Usni na usni, Author: Grigor Koprov, Interpreted by: Toshe Proeski, 215 sek.
        out << "Song title: " << title << ", Author: " << author
                << ", Interpreted by: " << performer << ", " << duration << " sek." << endl;
    }

    bool operator==(const Song &other) const {
        return title == other.title &&
               author == other.author &&
               performer == other.performer &&
               duration == other.duration;
    }


    friend class Festival;
};

class Festival {
private:
    string festivalName;
    string city;
    string date; //dd/mm/yyyy
    Song *songs;
    int n;

    void copy(const Festival &f) {
        festivalName = f.festivalName;
        city = f.city;
        date = f.date;
        n = f.n;
        songs = new Song[f.n];
        for (int i = 0; i < f.n; i++) {
            songs[i] = f.songs[i];
        }
    }

public:
    Festival() {
        this->festivalName = "";
        this->city = "";
        this->date = "";
        this->n = 0;
        songs = nullptr;
    }

    Festival(const Festival &f) {
        copy(f);
    }

    Festival &operator=(const Festival &f) {
        if (this != &f) {
            delete [] songs;
            copy(f);
        }
        return *this;
    }

    ~Festival() {
        delete [] songs;
    }

    Festival &operator-=(const Song &s) {
        if (n == 0) {
            cout << "Trying to delete from an empty list!" << endl;
            return *this;
        }
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (!(songs[i] == s)) count++;
        }
        Song *temp = new Song[count];
        int idx = 0;
        for (int i = 0; i < n; i++) {
            if (!(songs[i] == s)) {
                temp[idx++] = songs[i];
            }
        }
        delete[] songs;
        songs = temp;
        n = count;
        return *this;
    }

    void addSong(const Song &s) {
        Song *temp = new Song[n + 1];
        for (int i = 0; i < n; i++) {
            temp[i] = songs[i];
        }
        temp[n++] = s;
        delete[] songs;
        songs = temp;
    }

    void print(ofstream &out) const {
        out << "Festival: " << festivalName << " - " << city << ", " << date << endl;
        for (int i = 0; i < n; i++) {
            songs[i].print(out);
        }
    }

    friend istream &operator>>(istream &in, Festival &f) {
        getline(in, f.festivalName);
        getline(in, f.city);
        getline(in, f.date);
        in >> f.n;
        in.ignore();
        f.songs = new Song[f.n];
        for (int i = 0; i < f.n; i++) {
            in >> f.songs[i];
        }
        return in;
    }

    Festival notFromAuthor(const string &author) const {
        Festival result;
        result.festivalName = festivalName;
        result.city = city;
        result.date = date;
        for (int i = 0; i < n; i++) {
            if (songs[i].getAuthor() != author) {
                result.addSong(songs[i]);
            }
        }
        return result;
    }
};


void wtf() {
    ofstream fout("vlezna.txt");
    string line;
    while (getline(std::cin, line)) {
        if (line == "----") {
            break;
        }
        fout << line << endl;
    }
}

void rff(string path) {
    ifstream fin(path);
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
}


int main() {
    wtf();

    Festival festival;
    //TO DO your code here
    //TO DO Read the data from the file and store them in `festival`
    ifstream fin("vlezna.txt");
    if (!fin) {
        cerr << "Could not open input file!" << endl;
        return 1;
    }

    fin >> festival;
    fin.close();

    festival -= Song();


    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE NEXT COMMENT
    string author;
    getline(cin, author);
    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE PREVIOUS COMMENT

    //TO DO Save the results in the files izlezna1.txt and izlezna2.txt after this line
    ofstream out1("izlezna1.txt");
    festival.print(out1);
    out1.close();

    Festival filtered = festival.notFromAuthor(author);
    ofstream out2("izlezna2.txt");
    filtered.print(out2);

    out2.close();

    //DO NOT MODIFY THE CODE BELLOW

    cout << "All the data for the festival:" << endl;
    rff("izlezna1.txt");
    cout << "Songs NOT from the author " << author << ": " << endl;
    rff("izlezna2.txt");


    return 0;
}
