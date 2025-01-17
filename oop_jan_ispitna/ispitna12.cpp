#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

//zad13 ispitni/kolokviumski

class Image {
protected:
    char *ime;
    char sopstvenik[51];
    int sirina, visina;

public:
    Image(const char *ime = "untitled", const char *sopstvenik = "unknown", int sirina = 800, int visina = 800) {
        this->ime = new char[strlen(ime)];
        strcpy(this->ime, ime);
        strcpy(this->sopstvenik, sopstvenik);
        this->sirina = sirina;
        this->visina = visina;
    }

    Image(const Image &i) {
        ime = new char[strlen(i.ime) + 1];
        strcpy(ime, i.ime);
        strcpy(sopstvenik, i.sopstvenik);
        sirina = i.sirina;
        visina = i.visina;
    }

    virtual ~Image() {
        delete[] ime;
    }

    virtual int fileSize() {
        return visina * sirina * 3;
    };

    friend ostream &operator<<(ostream &os, Image &i) {
        os << i.ime << " " << i.sopstvenik << " " << i.fileSize() << endl;
        return os;
    }

    bool operator>(Image &i) {
        return fileSize() > i.fileSize();
    }
};

class TransparentImage : public Image {
protected:
    bool hasTransparency;

public:
    TransparentImage(const char *ime = "untitled", const char *sopstvenik = "unknown",
                     int sirina = 800, int visina = 800, bool hasTransparency = false)
        : Image(ime, sopstvenik, sirina, visina) {
        this->hasTransparency = hasTransparency;
    }

    int fileSize() {
        if (hasTransparency) {
            return 4 * visina * sirina;
        } else
            return visina * sirina + (visina * sirina) / 8;
    }
};

class Folder {
protected:
    char ime[256];
    char sopstvenik[51];
    Image *sliki[100];
    int brojSliki;

public:
    Folder(const char *ime = "", const char *sopstvenik = "unknown") {
        strcpy(this->ime, ime);
        strcpy(this->sopstvenik, sopstvenik);
        brojSliki = 0;
    }

    int folderSize() const {
        int size = 0;
        for (int i = 0; i < brojSliki; i++) {
            size += sliki[i]->fileSize();
        }
        return size;
    }

    Image *getMaxFile() {
        if (brojSliki == 0) return nullptr;
        Image *max = sliki[0];
        for (int i = 1; i < brojSliki; i++) {
            if (sliki[i]->fileSize() > max->fileSize()) {
                max = sliki[i];
            }
        }
        return max;
    }

    Folder &operator+=(Image &i) {
        if (brojSliki < 100) {
            sliki[brojSliki++] = &i;
        }
        return *this;
    }

    Image *operator[](int index) {
        if (index >= 0 && index < brojSliki)
            return sliki[index];
        return nullptr;
    }

    friend ostream &operator<<(ostream &out, const Folder &f) {
        out << f.ime << " " << f.sopstvenik << endl << "--" << endl;
        for (int i = 0; i < f.brojSliki; i++)
            out << *f.sliki[i];
        out << "--" << endl << "Folder size: " << f.folderSize() << endl;
        return out;
    }
};

Folder max_folder_size(Folder *folders, int n) {
    Folder max = folders[0];
    for (int i = 1; i < n; i++)
        if (folders[i].folderSize() > max.folderSize())
            max = folders[i];
    return max;
}

int main() {
    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc == 1) {
        // Testing constructor(s) & operator << for class File

        cin >> name;
        cin >> user_name;
        cin >> w;
        cin >> h;


        Image f1;

        cout << f1;

        Image f2(name);
        cout << f2;

        Image f3(name, user_name);
        cout << f3;

        Image f4(name, user_name, w, h);
        cout << f4;
    } else if (tc == 2) {
        // Testing constructor(s) & operator << for class TextFile
        cin >> name;
        cin >> user_name;
        cin >> w >> h;
        cin >> tl;

        TransparentImage tf1;
        cout << tf1;

        TransparentImage tf4(name, user_name, w, h, tl);
        cout << tf4;
    } else if (tc == 3) {
        // Testing constructor(s) & operator << for class Folder
        cin >> name;
        cin >> user_name;

        Folder f3(name, user_name);
        cout << f3;
    } else if (tc == 4) {
        // Adding files to folder
        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image *f;
        TransparentImage *tf;

        int sub, fileType;

        while (1) {
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >> fileType;
            if (fileType == 1) {
                // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name, user_name, w, h);
                dir += *f;
            } else if (fileType == 2) {
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name, user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout << dir;
    } else if (tc == 5) {
        // Testing getMaxFile for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image *f;
        TransparentImage *tf;

        int sub, fileType;

        while (1) {
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >> fileType;
            if (fileType == 1) {
                // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name, user_name, w, h);
                dir += *f;
            } else if (fileType == 2) {
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name, user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout << *(dir.getMaxFile());
    } else if (tc == 6) {
        // Testing operator [] for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image *f;
        TransparentImage *tf;

        int sub, fileType;

        while (1) {
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >> fileType;
            if (fileType == 1) {
                // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name, user_name, w, h);
                dir += *f;
            } else if (fileType == 2) {
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name, user_name, w, h, tl);
                dir += *tf;
            }
        }

        cin >> sub; // Reading index of specific file
        cout << *dir[sub];
    } else if (tc == 7) {
        // Testing function max_folder_size
        int folders_num;

        Folder dir_list[10];

        Folder dir;
        cin >> folders_num;

        for (int i = 0; i < folders_num; ++i) {
            cin >> name;
            cin >> user_name;
            dir = Folder(name, user_name);


            Image *f;
            TransparentImage *tf;

            int sub, fileType;

            while (1) {
                cin >> sub; // Should we add subfiles to this folder
                if (!sub) break;

                cin >> fileType;
                if (fileType == 1) {
                    // Reading File
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    f = new Image(name, user_name, w, h);
                    dir += *f;
                } else if (fileType == 2) {
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    cin >> tl;
                    tf = new TransparentImage(name, user_name, w, h, tl);
                    dir += *tf;
                }
            }
            dir_list[i] = dir;
        }
        cout << max_folder_size(dir_list, folders_num);
    }
    return 0;
};
