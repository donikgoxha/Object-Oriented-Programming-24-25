#include<iostream>
#include<cstdio>
#include <string.h>
using namespace std;
// Your code here

class Camera {
protected:
    char manufacturer[21];
    char model[21];
    int year;
    float resolution;

    void copy(const Camera &c) {
        strcpy(this->manufacturer, c.manufacturer);
        strcpy(this->model, c.model);
        this->year = c.year;
        this->resolution = c.resolution;
    }

public:
    Camera(const char *manufacturer = "", const char *model = "", int year = 0, float resolution = 0.0) {
        strcpy(this->manufacturer, manufacturer);
        strcpy(this->model, model);
        this->year = year;
        this->resolution = resolution;
    }

    Camera(const Camera &c) {
        copy(c);
    }

    Camera &operator=(const Camera &c) {
        if (this != &c) {
            copy(c);
        }
        return *this;
    }

    virtual ~Camera() {
    }

    virtual float price() const = 0;

    virtual float rentalPrice(int days) const = 0;

    const char *getModel() const {
        return model;
    }

    bool operator<(const Camera &c) const {
        return price() < c.price();
    }
};

class PhotoCamera : public Camera {
private:
    bool RAW;

public:
    PhotoCamera(const char *manufacturer = "", const char *model = "", int year = 0, float resolution = 0.0,
                bool RAW = false)
        : Camera(manufacturer, model, year, resolution) {
        this->RAW = RAW;
    }

    float price() const {
        return 100 + resolution * 20 + (RAW ? 50 : 0);
    }

    float rentalPrice(int days) const {
        float base = price() / 100 * days;
        if (days > 7) base *= 0.8;
        return base;
    }
};

class VideoCamera : public Camera {
private:
    int seconds;

public:
    VideoCamera(const char *manufacturer = "", const char *model = "", int year = 0, float resolution = 0.0,
                int seconds = 0)
        : Camera(manufacturer, model, year, resolution) {
        this->seconds = seconds;
    }

    float price() const {
        float price = resolution * 80;
        if (seconds > 3600) {
            price *= 1.4;
        }
        return price;
    }

    float rentalPrice(int days) const {
        float base = price() / 100 * days;
        if (days > 7) base *= 0.8;
        return base;
    }
};

class FilmCamera : public Camera {
private:
    int maxFPS;

public:
    FilmCamera(const char *manufacturer = "", const char *model = "", int year = 0, float resolution = 0.0,
               int maxFPS = 0)
        : Camera(manufacturer, model, year, resolution) {
        this->maxFPS = maxFPS;
    }

    float price() const {
        if (maxFPS <= 30) {
            return 50000;
        }
        return 50000 + (maxFPS - 30) * 5000;
    }

    float rentalPrice(int days) const {
        float base = 500 * days;
        if (maxFPS > 60) base *= 2;
        return base;
    }
};

float production(Camera **a, int n, int d) {
    float total = 0;
    for (int i = 0; i < n; ++i) {
        total += a[i]->rentalPrice(d);
    }
    return total;
}

const char *mostExpensiveCamera(Camera **arr, int n) {
    int maxIdx = 0;
    for (int i = 1; i < n; ++i) {
        if (*arr[maxIdx] < *arr[i]) {
            maxIdx = i;
        }
    }
    return arr[maxIdx]->getModel();
}

int main(int argc, char *argv[]) {
    // Variables for reading input
    char model[20], producer[20];
    int year, length, fps, n;
    float resolution;
    bool raw;

    int t;

    // Array of cameras
    Camera *c[10];

    // Read number of cameras
    cin >> n;

    for (int i = 0; i < n; ++i) {
        // Camera type: 1 - Photo, 2 - Video, 3 - Film
        cin >> t;

        if (t == 1) {
            cin >> producer >> model >> year >> resolution;
            cin >> raw;
            c[i] = new PhotoCamera(producer, model, year, resolution, raw);
        } else if (t == 2) {
            cin >> producer >> model >> year >> resolution;
            cin >> length;
            c[i] = new VideoCamera(producer, model, year, resolution, length);
        } else if (t == 3) {
            cin >> producer >> model >> year >> resolution;
            cin >> fps;
            c[i] = new FilmCamera(producer, model, year, resolution, fps);
        }
    }


    // Production days
    int days;
    cin >> days;


    cout << "Price of production is: " << production(c, n, days) << endl;
    cout << "Most expensive camera used in production is: " << mostExpensiveCamera(c, n);


    return 0;
}
