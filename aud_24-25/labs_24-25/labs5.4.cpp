#include <iostream>
#include <cstring>
using namespace std;

class Atom {
private:
    char symbol[3];
    float weight;

public:
    Atom(const char *symbol = "", float weight = 0) {
        strcpy(this->symbol, symbol);
        this->weight = weight;
    }

    Atom(const Atom &other) {
        strcpy(this->symbol, other.symbol);
        this->weight = other.weight;
    }

    Atom &operator=(const Atom &other) {
        if (this != &other) {
            strcpy(this->symbol, other.symbol);
            this->weight = other.weight;
        }
        return *this;
    }

    friend bool operator==(const Atom &lhs, const Atom &rhs) {
        return strcmp(lhs.symbol, rhs.symbol) == 0;
    }

    const char *getSymbol() const {
        return symbol;
    }

    float getWeight() const {
        return weight;
    }
};

class Molecule {
private:
    Atom *atoms;
    int n;

public:
    Molecule(Atom *atoms = nullptr, int n = 0) {
        this->n = n;
        if (n > 0) {
            this->atoms = new Atom[n];
            for (int i = 0; i < n; ++i) {
                this->atoms[i] = atoms[i];
            }
        } else {
            this->atoms = nullptr;
        }
    }

    Molecule(const Molecule &other) {
        n = other.n;
        if (n > 0) {
            atoms = new Atom[n];
            for (int i = 0; i < n; ++i) {
                atoms[i] = other.atoms[i];
            }
        } else {
            atoms = nullptr;
        }
    }

    Molecule &operator=(const Molecule &other) {
        if (this != &other) {
            delete[] atoms;
            n = other.n;
            if (n > 0) {
                atoms = new Atom[n];
                for (int i = 0; i < n; ++i) {
                    atoms[i] = other.atoms[i];
                }
            } else {
                atoms = nullptr;
            }
        }
        return *this;
    }

    ~Molecule() {
        delete[] atoms;
    }

    float getMolecularWeight() const {
        float tWeight = 0;
        for (int i = 0; i < n; ++i) {
            tWeight += atoms[i].getWeight();
        }
        return tWeight;
    }

    Atom *getAtoms() const {
        return atoms;
    }

    int getN() const {
        return n;
    }

    friend ostream &operator<<(ostream &os, const Molecule &m) {
        for (int i = 0; i < m.n;) {
            int count = 1;
            while (i + count < m.n && strcmp(m.atoms[i].getSymbol(), m.atoms[i + count].getSymbol()) == 0) {
                ++count;
            }
            os << m.atoms[i].getSymbol();
            if (count > 1) os << count;
            i += count;
        }
        os << " --- " << m.getMolecularWeight();
        return os;
    }
};


Molecule operator+(const Molecule &m1, const Molecule &m2) {
    int totalAtoms = m1.getN() + m2.getN();
    Atom *combinedAtoms = new Atom[totalAtoms];
    for (int i = 0; i < m1.getN(); ++i) {
        combinedAtoms[i] = m1.getAtoms()[i];
    }
    for (int i = 0; i < m2.getN(); ++i) {
        combinedAtoms[m1.getN() + i] = m2.getAtoms()[i];
    }
    Molecule result(combinedAtoms, totalAtoms);
    delete[] combinedAtoms;
    return result;
}


Molecule operator+(const Atom &a1, const Atom &a2) {
    Atom atoms[2]{a1, a2};
    return Molecule(atoms, 2);
}

Molecule operator+(const Atom &a1, const Molecule &m2) {
    int n = m2.getN();
    Atom *atoms = new Atom[n + 1];
    atoms[0] = a1;
    for (int i = 0; i < n; ++i) {
        atoms[i + 1] = m2.getAtoms()[i];
    }
    return Molecule(atoms, n + 1);
}

Molecule operator+(const Molecule &m1, const Atom &a2) {
    int n = m1.getN();
    Atom *atoms = new Atom[n + 1];
    for (int i = 0; i < n; ++i) {
        atoms[i] = m1.getAtoms()[i];
    }
    atoms[n] = a2;
    return Molecule(atoms, n + 1);
}

// Don't modify
int main() {
    int testcase;
    cin >> testcase;
    switch (testcase) {
        case 0: {
            cout << "Testing Atom constructors and operators ==, =" << endl;
            Atom a1("H", 1.001);
            Atom a2("O", 15.997);
            Atom a3(a1);
            cout << (a1 == a3) << endl << (a2 == a3) << endl;
            a3 = a2;
            cout << (a1 == a3) << endl << (a2 == a3) << endl;
            break;
        }
        case 1: {
            cout << "Testing Molecule constructors, methods and operator =" << endl;
            Atom atoms[5];
            Atom c("C", 12.0096);
            Atom h("H", 1.001);
            atoms[0] = c;
            for (int i = 0; i < 4; ++i) {
                atoms[i + 1] = h;
            }

            Molecule m1(atoms, 5);
            Molecule m2(atoms, 3);
            Molecule m3(m1);

            cout << m1.getMolecularWeight() << endl << m2.getMolecularWeight() << endl;
            cout << m3.getMolecularWeight() << endl;

            m3 = m2;
            cout << m3.getMolecularWeight() << endl;
            break;
        }
        case 2: {
            cout << "Testing operator << on Molecule" << endl;

            Atom c("C", 12.0096);
            Atom h("H", 1.001);
            Atom o("O", 15.997);
            Atom cl("Cl", 35.45);

            Atom atoms0[3];
            atoms0[0] = h;
            atoms0[1] = h;
            atoms0[2] = o;
            cout << Molecule(atoms0, 3) << endl; // H20

            atoms0[0] = h;
            atoms0[1] = o;
            atoms0[2] = h;
            cout << Molecule(atoms0, 3) << endl; // HOH

            Atom atoms[5];
            atoms[0] = c;
            for (int i = 0; i < 4; ++i) atoms[i + 1] = h;

            cout << Molecule(atoms, 5) << endl; // CH4

            Atom atoms1[10];

            for (int i = 0; i < 10; ++i) {
                if (i < 3) atoms1[i] = c;
                else if (i < 8) atoms1[i] = h;
                else if (i == 8) atoms1[i] = cl;
                else atoms1[i] = o;
            }

            cout << Molecule(atoms1, 10) << endl; // C3H5ClO

            cout << endl << "[Formatting help: Print the atoms" << endl << "in the order of the atoms array." << endl;
            cout << "Consecutive atoms that are" << endl << "the same should be counted." << endl <<
                    "Then print the molecule weight.]" << endl;
            break;
        }
        case 3: {
            cout << "Testing operator + on class Molecule." << endl;
            Molecule m1, m2;
            Atom c("C", 12.0096);
            Atom h("H", 1.001);
            Atom o("O", 15.997);
            Atom cl("Cl", 35.45);
            Atom n("N", 14.006);

            m1 = c + h;
            m2 = cl + n + o;
            cout << (m1 + m2) << endl;
            break;
        }
        case 4: {
            cout << "Complete/Full test." << endl;
            Molecule m, m1, m2;
            Atom c("C", 12.0096);
            Atom h("H", 1.001);
            Atom o("O", 15.997);
            Atom cl("Cl", 35.45);
            Atom n("N", 14.006);

            char input[10];
            int i = 1;
            while (true) {
                i = i == 0 ? 1 : 0;
                cin >> input;
                if (input[0] == 'E') return 0;
                while (input[0] != '.' && input[0] != '+') {
                    switch (input[0]) {
                        case 'H':
                            m = m + h;
                            break;
                        case 'O':
                            m = m + o;
                            break;
                        case 'N':
                            m = m + n;
                            break;
                        case 'C':
                            if (input[1] == 'l') m = m + cl;
                            else m = m + c;
                            break;
                    }
                    cin >> input;
                }
                if (i == 0) {
                    m1 = m;
                    m = Molecule();
                } else {
                    m2 = m;
                    cout << (m1 + m2) << endl;
                    m = Molecule();
                }
            }
        }
    }
}
