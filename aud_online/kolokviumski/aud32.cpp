// Links to the lessons
//https://bbb-lb.finki.ukim.mk/playback/presentation/2.3/740dc1184c44f2d100ce97a5038744c4cd34f22a-1652877940499
#include<iostream>
#include<cstring>
#include<string>
using namespace std;


// Да се напише апстрактна класа што репрезентира медија сегмент ( MediaSegment ).
// За секој медија сегмент се дефинира:
// Наслов (низа од најмногу. 100 знаци)
// Автор (низа од најмногу 100 знаци)
// Времетраење во секунди (позитивен цел број)
// Големина на записот во мегабајти (позитивен цел број).
// За класата да се имплементираат потребните методи/конструктори за
// правилно функционирање (според дадената функција main).
// Од класата за MediaSegment да се изведат класите за аудио и видео запис.
// Класата за аудио запис ( AudioRecording) репрезентира аудио снимка. За аудио записот се чува:
// Формат на аудио записот: може да има една од следните вредности: mp3, wav, ogg и flac.
// Број на канали - променлива од тип short.
// За класата AudioRecording да се имплементираат потребните методи/конструктори за
// правилно функционирање (според дадената функција main ).
// За класата да се обезбеди функција price што ja пресметува цената на аудио записот.
// Цената на аудио записот (изразена во евра) се добива на следниот начин:
// Се пресметува производ од времетраењето (во секунди) и бројот на канали.
// Ако форматот е flac тогаш пресметаниот производ во чекор 1 дополнително се зголемува за 50%
// Да се преоптовари операторот << за печатење на информациите за аудио сегментот во форматот:
// Наслов - Автор - Времетраeње - големина - цена
// Класата за видео запис (VideoRecording) репрезентира видео снимка. За секој видео запис се чува:
// Ширина на сликата на видео записот - позитивен цел број
// компресија на видео записот - може да има една од следните вредности: х264, Theora, AV1
// За класата VideoRecording да се обезбедат потребните методи/конструктори за
// правилно функционирање (според дадената функција main).
// За класата да се обезбеди и функција price што пресметува цена на видео записот.
// Цената на видео записот (изразена во евра) се пресметува на следниот начин:
// Ако ширината е помала или еднаква на 1920 тогаш видео записот чини 100 евра по секунда.
// Ако ширината е поголема од 1920 тогаш цената е 170 евра по секунда.
// Ако компресијата е x264 тогаш пресметаната цена во чекор 1 дополнително се зголемува за 50%.
// Ако компресијата е Theora, пресметаната цена во чекор 1 се намалува за 10%.
// Да се преоптовари операторот << за печатење на информациите за видео записот во формат:
// Наслов - Автор - Времетраeње - големина - димензии - цена
// Да се креира класа Музичко видео (MusicVideo) што истовремено наследува од
// класите AudioRecording и VideoRecording. Класата треба чува:
// Датум на публикација - низа од знаци во форматот ddmmgggg.
// Да се обезбеди метод price за пресметување на цената на музичкото видео.
// Таа се пресметува како сума од цената на аудио и на видео записот. Ако датумот на публикација е по 2010 година,
// цената дополнително се зголемува за 30%.
// Да се преоптовари операторот << за печатење на информациите за музичкото видео во форматот:
// Наслов - Автор - датум на публикација - Времетраeње - цена
// Да се имплементира глобална функција total_price што прима низа од покажувачи од тип MediaSegment и
// нивниот број и пресметува колку чинела продукцијата на сите тие записи.
// Да се имплементира глобална функција cheapest_music_video што прима низа од покажувачи од тип MediaSegment и
// нивниот број и го враќа најевтиното музичко видео во рамките сите записи.

enum AudioFormat { mp3, wav, ogg, flac };

enum VideoCompression { x264, Theora, AV1 };


class MediaSegment {
protected:
    char title[100];
    char author[100];
    int duration;
    int size;

public:
    MediaSegment(char *title = "", char *author = "", int duration = 0, int size = 0) {
        strcpy(this->title, title);
        strcpy(this->author, author);
        this->duration = duration;
        this->size = size;
    }

    MediaSegment(const MediaSegment &s) {
        strcpy(this->title, s.title);
        strcpy(this->author, s.author);
        this->duration = s.duration;
        this->size = s.size;
    }

    virtual double price() const = 0;

    virtual ~MediaSegment() {
    }
};


class AudioRecording : virtual public MediaSegment {
protected:
    AudioFormat format;;
    short channels;

public:
    AudioRecording(char *title = "", char *author = "", int duration = 0, int size = 0, int format = 0,
                   short channels = 0) : MediaSegment(title, author, duration, size) {
        this->format = (AudioFormat) format;
        this->channels = channels;
    }

    double price() const override {
        double product = duration * channels;
        if (format == flac) {
            product *= 1.5;
        }
        return product;
    }

    friend ostream &operator<<(ostream &out, const AudioRecording &ar) {
        return out << ar.title << " - " << ar.author << " - " << ar.duration << " - " << ar.size << " - " << ar.price();
    }

    virtual ~AudioRecording() {
    }
};

class VideoRecording : virtual public MediaSegment {
protected:
    int width;
    VideoCompression compression;

public:
    VideoRecording(char *title = "", char *author = "", int duration = 0, int size = 0, int width = 0,
                   int compression = 0) : MediaSegment(title, author, duration, size) {
        this->width = width;
        this->compression = (VideoCompression) compression;
    }

    double price() const override {
        double price;
        if (width <= 1920) {
            price = 100 * duration;
        } else {
            price = 170 * duration;
        }
        if (compression == x264) {
            price *= 1.5;
        } else if (compression == Theora) {
            price *= 0.9;
        }

        return price;
    }

    friend ostream &operator<<(ostream &out, const VideoRecording &vr) {
        return out << vr.title << " - " << vr.author << " - " << vr.duration << " - " << vr.size << " - " << vr.width
               << " - " << vr.price();
    }

    virtual ~VideoRecording() {
    }
};

class MusicVideo : public AudioRecording, public VideoRecording {
protected:
    char date[9]; //ddmmgggg

public:
    MusicVideo(char *title = "", char *author = "", int duration = 0, int size = 0, int format = 0, int channels = 0,
               int width = 0, int compression = 0, char *date = "07082004")
        : MediaSegment(title, author, duration, size) {
        this->format = (AudioFormat) format;
        this->channels = channels;
        this->width = width;
        this->compression = (VideoCompression) compression;
        strcpy(this->date, date);
    }

    double price() const override {
        double result = AudioRecording::price() + VideoRecording::price();
        if (strcmp(date + 4, "2010") > 0) {
            result += 1.3;
        }
        return result;
    }

    friend ostream &operator<<(ostream &out, const MusicVideo &mv) {
        return out << mv.title << " - " << mv.author << " - " << mv.duration << " - " << mv.size << " - " << mv.width <<
               mv.price();
    }

    virtual ~MusicVideo() {
    }
};

double total_price(MediaSegment **segments, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        //sum += (*segments)[i].price();
        sum += segments[i]->price();
    }
    return sum;
}

MusicVideo cheapest_music_video(MediaSegment **segments, int n) {
    MusicVideo *min;
    for (int i = 0; i < n; i++) {
        MusicVideo *casted = dynamic_cast<MusicVideo *>(segments[i]);
        if (casted) {
            if (min == nullptr) {
                min = casted;
            } else if (casted->price() < min->price()) {
                min = casted;
            }
        }
        return *min;
    }
}


int main() {
    int test_case_num;
    cin >> test_case_num;


    // for MediaSegment
    char title[100];
    char author[1000];
    unsigned int size;
    unsigned int duration;


    // for AudioRecording
    //-------------------
    unsigned short channels;

    // AudioFormat:
    // 0 - mp3
    // 1 - wav
    // 2 - ogg
    // 3 - flac
    unsigned short format;


    // for VideoRecording
    //-------------------
    unsigned short width;

    // VideoCompression:
    // 0 - x264
    // 1 - Theora
    // 2 - AV1
    int compression;


    // for MusicVideo
    //-------------------
    char publication_date[9];


    if (test_case_num == 1) {
        cout << "Testing class AudioRecording and operator<<" << std::endl;
        cin.get();
        cin.getline(title, 100);
        cin.getline(author, 100);
        //cin.get();
        cin >> duration >> size;
        cin >> format >> channels;

        AudioRecording a(title, author, duration, size, format, channels);

        cout << a;
    } else if (test_case_num == 2) {
        cout << "Testing class VideoRecording and operator<<" << std::endl;
        cin.get();
        cin.getline(title, 100);
        cin.getline(author, 100);
        //cin.get();
        cin >> duration >> size;
        cin >> width >> compression;

        VideoRecording v(title, author, duration, size, width, compression);

        cout << v;
    } else if (test_case_num == 3) {
        cout << "Testing class MusicVideo and operator<<" << std::endl;

        cin.get();
        cin.getline(title, 100);
        cin.getline(author, 100);
        //cin.get();
        cin >> duration >> size;

        cin >> format >> channels;
        cin >> width >> compression;

        cin.get();
        cin.getline(publication_date, 9);
        MusicVideo mv(title, author, duration, size, format, channels, width, compression, publication_date);

        cout << mv;
    } else if (test_case_num == 4) {
        cout << "Testing function: total_price " << std::endl;

        MediaSegment **m;

        int num_media_segments;
        cin >> num_media_segments;

        // 1 - AudioRecording
        // 2 - VideoRecording
        // 3 - MusicVideo
        short media_type;

        m = new MediaSegment *[num_media_segments];

        for (int i = 0; i < num_media_segments; i++) {
            cin >> media_type;

            cin.get();
            cin.getline(title, 100);
            cin.getline(author, 100);
            //cin.get();
            cin >> duration >> size;

            switch (media_type) {
                case 1:
                    cin >> format >> channels;
                    m[i] = new AudioRecording(title, author, duration, size, format, channels);
                    break;
                case 2:
                    cin >> width >> compression;
                    m[i] = new VideoRecording(title, author, duration, size, width, compression);
                    break;
                case 3:
                    cin >> format >> channels;
                    cin >> width >> compression;
                    cin.get();
                    cin.getline(publication_date, 9);
                    m[i] = new MusicVideo(title, author, duration, size, format, channels, width, compression,
                                          publication_date);
                    break;
            }
        }

        //for (int i=0;i<num_media_segments; i++){
        //    cout << *m[i];
        //}

        cout << "Total price is: " << total_price(m, num_media_segments);

        delete[] m;
    } else if (test_case_num == 5) {
        cout << "Testing function: cheapest_music_video " << std::endl;

        MediaSegment **m;

        int num_media_segments;
        cin >> num_media_segments;

        // 1 - AudioRecording
        // 2 - VideoRecording
        // 3 - MusicVideo
        short media_type;

        m = new MediaSegment *[num_media_segments];

        for (int i = 0; i < num_media_segments; i++) {
            cin >> media_type;

            cin.get();
            cin.getline(title, 100);
            cin.getline(author, 100);
            //cin.get();
            cin >> duration >> size;

            switch (media_type) {
                case 1:
                    cin >> format >> channels;
                    m[i] = new AudioRecording(title, author, duration, size, format, channels);
                    break;
                case 2:
                    cin >> width >> compression;
                    m[i] = new VideoRecording(title, author, duration, size, width, compression);
                    break;
                case 3:
                    cin >> format >> channels;
                    cin >> width >> compression;
                    cin.get();
                    cin.getline(publication_date, 9);
                    m[i] = new MusicVideo(title, author, duration, size, format, channels, width, compression,
                                          publication_date);
                    break;
            }
        }

        cout << cheapest_music_video(m, num_media_segments);

        delete[] m;
    }

    return 0;
}
