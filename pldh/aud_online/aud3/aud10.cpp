// Links to the lessons
// https://finki-mk.github.io/OOP/html5/oop_av5.html
// https://bbb-lb.finki.ukim.mk/playback/presentation/2.3/740dc1184c44f2d100ce97a5038744c4cd34f22a-1648042101186

#include <iostream>
#include <string.h>
using namespace std;

class WebPage {
private:
    char url[100];
    char *content;

    void copy(const WebPage &wp) {
        strcpy(url, wp.url);
        this->content = new char[strlen(wp.content + 1)];
        strcpy(this->content, wp.content);
    }

public:
    WebPage(char *url = "https://finki.mk", char *content = "Website na finki") {
        strcpy(this->url, url);
        this->content = new char[strlen(content + 1)];
        strcpy(this->content, content);
    }

    WebPage(const WebPage &wp) {
        copy(wp);
    }

    WebPage &operator=(const WebPage &wp) {
        if (this != &wp) {
            delete [] content;
            copy(wp);
        }
        return *this;
    }

    ~WebPage() {
        delete [] content;
    }

    void print() {
        cout << url << " " << endl << content << endl;
    }

    bool equal(const WebPage &wp) {
        return strcmp(this->url, wp.url) == 0;
    }
};


class WebServer {
private:
    char name[30];
    WebPage *webpages;
    int size;

    void copy(const WebServer &ws) {
        strcpy(this->name, ws.name);
        this->size = ws.size;
        webpages = new WebPage [this->size];
        for (int i = 0; i < this->size; i++) {
            this->webpages[i] = ws.webpages[i];
        }
    }

public:
    WebServer(char *name = "Finki Server") {
        this->size = 0;
        strcpy(this->name, name);
        this->webpages = new WebPage [size];
    }

    WebServer(const WebServer &ws) {
        copy(ws);
    }

    WebServer &operator=(const WebServer &ws) {
        if (this != &ws) {
            delete [] webpages;
            copy(ws);
        }
        return *this;
    }

    ~WebServer() {
        delete [] webpages;
    }

    void addPage(const WebPage &wp) {
        if (hasPage(wp))
            return;

        WebPage *tmp = new WebPage[size + 1];
        for (int i = 0; i < size; i++) {
            tmp[i] = webpages[i];
        }
        tmp[size++] = wp;
        delete [] webpages;
        webpages = tmp;
    }

    void print() {
        cout << name << endl;
        for (int i = 0; i < size; i++) {
            webpages[i].print();
        }
    }

    bool hasPage(const WebPage &wp) {
        bool found = false;
        for (int i = 0; i < size; i++) {
            if (webpages[i].equal(wp)) {
                found = true;
                break;
            }
        }
        return found;
    }

    void deletePage(const WebPage &wp) {
        if (hasPage(wp)) {
            WebPage *tmp = new WebPage [size - 1];
            int j = 0;
            for (int i = 0; i < size; i++) {
                if (!webpages[i].equal(wp)) {
                    tmp[j++] = webpages[i];
                }
            }
            size--;
            delete [] webpages;
            webpages = tmp;
        }
    }
};

int main() {
    WebPage wp;

    WebPage copy(wp);
    WebPage testAssignment;
    testAssignment = wp;

    //    wp.print(); //default constructor
    //    copy.print(); //copy constructor
    //    testAssignment.print(); //operator =

    //    cout << wp.equal(copy);

    WebServer ws("FINKI");
    ws.addPage(wp);

    WebPage courses("courses.finki.ukim.mk", "Moodle za potrebite na FINKI");
    ws.addPage(copy);
    ws.addPage(testAssignment);
    ws.addPage(courses);
    ws.print();
    cout << "------" << endl;
    ws.deletePage(copy);
    ws.print();
    return 0;
}
