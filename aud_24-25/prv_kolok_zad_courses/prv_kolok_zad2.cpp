#include <iostream>
using namespace std;

class List {
private:
    int *numbers;
    int n;

    void copy(const List &l) {
        n = l.n;
        numbers = new int[n];
        for (int i = 0; i < n; i++) {
            numbers[i] = l.numbers[i];
        }
    }

public:
    List(const int *numbers = nullptr, int n = 0) {
        this->n = n;
        this->numbers = new int[n];
        for (int i = 0; i < n; i++) {
            this->numbers[i] = numbers[i];
        }
    }

    List(const List &l) {
        copy(l);
    }

    List &operator=(const List &l) {
        if (this != &l) {
            delete [] numbers;
            copy(l);
        }
        return *this;
    }

    int sum() const {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += numbers[i];
        }
        return sum;
    }

    double average() const {
        if (sum() == 0)
            return 0;
        else
            return (double) sum() / n;
    }

    void print() const {
        cout << n << ": ";
        for (int i = 0; i < n; i++) {
            cout << numbers[i] << " ";
        }
        cout << "sum: " << sum() << " average: " << average() << endl;
    }
};

class ListContainer {
private:
    List *lists;
    int n;
    int attempts;

    void copy(const ListContainer &lc) {
        n = lc.n;
        attempts = lc.attempts;
        lists = new List[n];
        for (int i = 0; i < n; i++) {
            lists[i] = lc.lists[i];
        }
    }

public:
    ListContainer(List *lists = nullptr, int n = 0, int attempts = 0) {
        this->n = n;
        this->attempts = attempts;
        lists = new List[n];
        for (int i = 0; i < n; i++) {
            this->lists[i] = lists[i];
        }
    }

    ListContainer(const ListContainer &lc) {
        copy(lc);
    }

    ListContainer &operator=(const ListContainer &lc) {
        if (this != &lc) {
            delete [] lists;
            copy(lc);
        }
        return *this;
    }

    void print() const {
        if (n == 0) {
            cout << "The list is empty" << endl;
            return;
        }

        for (int i = 0; i < n; i++) {
            cout << "List number: " << i + 1 << " List info: ";
            lists[i].print();
        }

        cout << "Sum: " << sum() << " Average: " << average() << endl;
        cout << "Successful attempts: " << n << " Failed attempts: " << (attempts - n) << endl;
    }

    void addNewList(const List &l) {
        attempts++;

        for (int i = 0; i < n; i++) {
            if (lists[i].sum() == l.sum()) {
                return;
            }
        }

        List *temp = new List[n + 1];
        for (int i = 0; i < n; i++) {
            temp[i] = lists[i];
        }
        temp[n] = l;

        delete[] lists;
        lists = temp;
        n++;
    }

    int sum() const {
        int total = 0;
        for (int i = 0; i < n; i++) {
            total += lists[i].sum();
        }
        return total;
    }

    double average() const {
        int totalElements = 0;
        int totalSum = 0;
        for (int i = 0; i < n; i++) {
            totalSum += lists[i].sum();
            totalElements += lists[i].sum() / lists[i].average();
        }
        if (totalElements == 0) return 0;
        return (double) totalSum / totalElements;
    }

    ~ListContainer() {
        delete[] lists;
    }
};


int main() {
    ListContainer lc;
    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        int n;
        int niza[100];

        cin >> n;

        for (int j = 0; j < n; j++) {
            cin >> niza[j];
        }

        List l = List(niza, n);

        lc.addNewList(l);
    }


    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "Test case for operator =" << endl;
        ListContainer lc1;
        lc1.print();
        cout << lc1.sum() << " " << lc.sum() << endl;
        lc1 = lc;
        lc1.print();
        cout << lc1.sum() << " " << lc.sum() << endl;
        lc1.sum();
        lc1.average();
    } else {
        lc.print();
    }
}
