#include<iostream>
#include<cstring>

using namespace std;

enum Extension { pdf, txt, exe };

class File {
private:
    char *name;
    Extension extension;
    char *owner;
    int size;

    void copy(const File &f) {
        this->name = new char [strlen(f.name) + 1];
        strcpy(this->name, f.name);
        this->extension = f.extension;
        this->owner = new char [strlen(f.owner) + 1];
        strcpy(this->owner, f.owner);
        this->size = f.size;
    }

public:
    File(const char *name = "", const char *owner = "", int size = 0, Extension extension = txt) {
        this->name = new char [strlen(name) + 1];
        strcpy(this->name, name);
        this->extension = extension;
        this->owner = new char [strlen(owner) + 1];
        strcpy(this->owner, owner);
        this->size = size;
    }

    File(const File &f) {
        copy(f);
    }

    File &operator=(const File &f) {
        if (this != &f) {
            delete [] name;
            delete [] owner;
            copy(f);
        }
        return *this;
    }

    ~File() {
        delete [] name;
        delete [] owner;
    }

    void print() const {
        cout << "File name: " << name << ".";
        if (extension == txt) cout << "txt" << endl;
        else if (extension == pdf) cout << "pdf" << endl;
        else if (extension == exe) cout << "exe" << endl;
        cout << "File owner: " << owner << endl;
        cout << "File size: " << size << endl;
    }

    bool equals(const File &that) const {
        return strcmp(name, that.name) == 0 && extension == that.extension && strcmp(owner, that.owner) == 0;
    }

    bool equalsType(const File &that) const {
        return strcmp(name, that.name) == 0 && extension == that.extension;
    }
};


class Folder {
private:
    char *folderName;
    int fileCount;
    File *files;

    void copy(const Folder &f) {
        this->folderName = new char[strlen(f.folderName) + 1];
        strcpy(this->folderName, f.folderName);
        this->fileCount = f.fileCount;
        this->files = new File[fileCount];
        for (int i = 0; i < fileCount; i++) {
            this->files[i] = f.files[i];
        }
    }

public:
    Folder(const char *folderName = "") {
        this->folderName = new char [strlen(folderName) + 1];
        strcpy(this->folderName, folderName);
        this->fileCount = 0;
        this->files = nullptr;
    }

    Folder(const Folder &f) {
        copy(f);
    }

    Folder &operator=(const Folder &f) {
        if (this != &f) {
            delete[] folderName;
            delete[] files;
            copy(f);
        }
        return *this;
    }

    ~Folder() {
        delete [] folderName;
        delete [] files;
    }

    void print() const {
        cout << "Folder name: " << folderName << endl;
        for (int i = 0; i < fileCount; i++) {
            files[i].print();
        }
    }

    void add(const File &f) {
        File *tmp = new File[fileCount + 1];
        for (int i = 0; i < fileCount; i++) {
            tmp[i] = files[i];
        }
        tmp[fileCount++] = f;
        delete [] files;
        files = tmp;
    }

    void remove(const File &file) {
        for (int i = 0; i < fileCount; i++) {
            if (files[i].equals(file)) {
                File *tmp = new File[fileCount - 1];
                for (int j = 0, k = 0; j < fileCount; j++) {
                    if (j != i) tmp[k++] = files[j];
                }
                delete[] files;
                files = tmp;
                fileCount--;
                break;
            }
        }
    }
};

int main() {
    char fileName[20];
    char fileOwner[20];
    int ext;
    int fileSize;

    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File created = File(fileName, fileOwner, fileSize, (Extension) ext);
        File copied = File(created);
        File assigned = created;

        cout << "======= CREATED =======" << endl;
        created.print();
        cout << endl;
        cout << "======= COPIED =======" << endl;
        copied.print();
        cout << endl;
        cout << "======= ASSIGNED =======" << endl;
        assigned.print();
    } else if (testCase == 2) {
        cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File first(fileName, fileOwner, fileSize, (Extension) ext);
        first.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File second(fileName, fileOwner, fileSize, (Extension) ext);
        second.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File third(fileName, fileOwner, fileSize, (Extension) ext);
        third.print();

        bool equals = first.equals(second);
        cout << "FIRST EQUALS SECOND: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equals = first.equals(third);
        cout << "FIRST EQUALS THIRD: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        bool equalsType = first.equalsType(second);
        cout << "FIRST EQUALS TYPE SECOND: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equalsType = second.equals(third);
        cout << "SECOND EQUALS TYPE THIRD: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;
    } else if (testCase == 3) {
        cout << "======= FOLDER CONSTRUCTOR =======" << endl;
        cin >> fileName;
        Folder folder(fileName);
        folder.print();
    } else if (testCase == 4) {
        cout << "======= ADD FILE IN FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        folder.print();
    } else {
        cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File file(fileName, fileOwner, fileSize, (Extension) ext);
        folder.remove(file);
        folder.print();
    }
    return 0;
}
