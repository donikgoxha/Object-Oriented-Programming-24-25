#include<iostream>
#include<cstdio>
#include <string.h>
using namespace std;
//zad6 ispitni/kolokviumski eng

class Camera {
protected:
    char manufacturer[30];
    char model[30];
    int year;
    float resolution;

public:
    Camera(const char *manufacturer = "", const char *model = "", int year = 0, float resolution = 0.0) {
        strcpy(this->manufacturer, manufacturer);
        strcpy(this->model, model);
        this->year = year;
        this->resolution = resolution;
    }

    virtual float price() const = 0;

    virtual float rentalPrice(int days) const = 0;

    virtual ~Camera() = default;

    const char *getModel() const {
        return model;
    }

    bool operator<(const Camera &other) const {
        return price() < other.price();
    }
};

class PhotoCamera : public Camera {
private:
    bool supportsRAW;
    //true - supports, false = doesnt support

public:
    PhotoCamera(const char *manufacturer = "", const char *model = "", int year = 0, float resolution = 0.0,
                bool supportsRAW = false): Camera(manufacturer, model, year, resolution) {
        this->supportsRAW = supportsRAW;
    }

    float price() const override {
        if (!supportsRAW) {
            return 100 + resolution * 20;
        }
        return 100 + (resolution * 20 + 50);
    }

    float rentalPrice(int days) const override {
        if (days > 7) {
            return (price() / 100) * days * 0.8;
        }
        return (price() / 100) * days;
    }
};

class VideoCamera : public Camera {
private:
    int seconds;

public:
    VideoCamera(const char *manufacturer = "", const char *model = "", int year = 0, float resolution = 0.0,
                int seconds = 0): Camera(manufacturer, model, year, resolution) {
        this->seconds = seconds;
    }

    float price() const override {
        if (seconds > 3600) {
            return resolution * 80 * 1.4;
        }
        return resolution * 80;
    }

    float rentalPrice(int days) const override {
        if (days > 7) {
            return (price() / 100) * days * 0.8;
        }
        return (price() / 100) * days;
    }
};

class FilmCamera : public Camera {
private:
    int fps;

public:
    FilmCamera(const char *manufacturer = "", const char *model = "", int year = 0, float resolution = 0.0,
               int fps = 0): Camera(manufacturer, model, year, resolution) {
        this->fps = fps;
    }

    float price() const override {
        if (fps > 30) {
            return 50000 + (5000 * (fps - 30));
        }
        return 50000;
    }

    float rentalPrice(int days) const override {
        if (fps > 60) {
            return 1000 * days;
        }
        return 500 * days;
    }
};

float production(Camera **cameras, int numCameras, int days) {
    float price = 0;
    for (int i = 0; i < numCameras; i++) {
        price += cameras[i]->rentalPrice(days);
    }
    return price;
}

const char *mostExpensiveCamera(Camera *cameras[], int numCameras) {
    if (numCameras == 0) {
        return nullptr;
    }


    int maxIndex = 0;
    for (int i = 0; i < numCameras; ++i) {
        if (cameras[i]->price() > cameras[maxIndex]->price()) {
            maxIndex = i;
        }
    }
    return cameras[maxIndex]->getModel();
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
