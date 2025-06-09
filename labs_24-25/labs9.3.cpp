//Да се дефинира класа AIModel која ќе претставува еден AI модел. Треба да ги содржи следните полиња:
//brand - компанија-производител на моделот,
//name - име на моделот и
//version - верзија на моделот.
//За класата треба да се дефинира параметризиран конструктор и print() метод.
//Да се дефинира класа AIConfiguration, која ќе ги претставува конфигурациите на AI модел.
//Таа треба да ги содржи следните полиња:
//parameters - број на влезни параметри на моделот,
//epochs - број на епохи на кои е трениран моделот,
//type - податок од тип AIModelType (GPT, VISION, CLASSIFIER, EMBEDDING)
//За класата треба да се дефинира параметризиран конструктор и print() метод. Во параметризираниот конструктор треба
//да се провери валидноста на бројот на параметри и типот, и доколку се наиде на невалиден податок да се фрли
//соодветен исклучок (треба да ги креирате класите InvalidNumberOfParametersException и InvalidModelTypeException, соодветно).
//За бројот на параметри велиме дека е невалиден доколку е број помал од 0. За типот на моделот велиме дека
//е невалиден доколку не е дефиниран во енумерацијата.
//Напомена: прво се проверува бројот на параметри, па потоа типот на модел. Исклучоците треба да се фатат
//на означеното место во main функцијата.*/

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

enum AIModelType {
    GPT,
    VISION,
    CLASSIFIER,
    EMBEDDING
};

class InvalidNumberOfParametersException {
public:
    void print() const {
        cout << "Exception: Invalid number of parameters" << endl;
    }
};

class InvalidModelTypeException {
public:
    void print() const {
        cout << "Exception: Invalid model type" << endl;
    }
};


/**
 
Converts a string representation of an AI model type to its corresponding AIModelType enum value.,
If the input string does not match any known type, the function returns an invalid value (-1 cast to AIModelType).*,
@param typeStr A string representing the AI model type.,
@return AIModelType The corresponding enum value if found, or static_cast<AIModelType>(-1) if the input is invalid.**/
AIModelType getStringMapping(string typeStr) {
    unordered_map<string, AIModelType> mapping = {
        {"GPT", GPT},
        {"VISION", VISION},
        {"CLASSIFIER", CLASSIFIER},
        {"EMBEDDING", EMBEDDING}
    };

    if (mapping.find(typeStr) != mapping.end()) {
        return mapping[typeStr];
    } else {
        return static_cast<AIModelType>(-1); // Invalid type
    }
}

class AIModel {
private:
    string brand;
    string name;
    string version;

public:
    AIModel(string brand, string name, string version) {
        this->brand = brand;
        this->name = name;
        this->version = version;
    }

    void print() const {
        cout << "AI Model: " << brand << " " << name << " (Version: " << version << ")" << endl;
    }
};

class AIConfiguration {
private:
    int parameters;
    int epochs;
    AIModelType type;

public:
    AIConfiguration(int parameters, int epochs, AIModelType type) {
        if (parameters < 0) {
            throw InvalidNumberOfParametersException();
        }
        if (type < GPT || type > EMBEDDING) {
            throw InvalidModelTypeException();
        }

        this->parameters = parameters;
        this->epochs = epochs;
        this->type = type;
    }

    void print() const {
        cout << "AI Configuration: Parameters = " << parameters << ", Epochs = " << epochs << ", Type = ";
        switch (type) {
            case GPT:
                cout << "GPT";
                break;
            case VISION:
                cout << "VISION";
                break;
            case CLASSIFIER:
                cout << "CLASSIFIER";
                break;
            case EMBEDDING:
                cout << "EMBEDDING";
                break;
        }
        cout << endl;
    }
};

// COMPLETE TODOs
int main() {
    int tc;
    cin >> tc;
    if (tc == 1) {
        string brand, name, version;
        cout << "Testing AI Model Creation:";
        cin >> brand >> name >> version;
        AIModel model(brand, name, version);
        cout << " PASSED" << endl;
    }
    if (tc == 2) {
        AIModel model("OpenAI", "GPT-3", "v1.0");
        cout << "Testing Print Method for AI Model:" << endl;
        model.print();
    }
    if (tc == 3) {
        cout << "Testing AI Configuration Creation:";
        int parameters, epochs;
        string typeStr;
        cin >> parameters >> epochs >> typeStr;
        AIModelType type = getStringMapping(typeStr);
        AIConfiguration config(parameters, epochs, type);
        cout << " PASSED" << endl;
    }
    if (tc == 4) {
        cout << "Testing Print Method for AI Configuration:" << endl;
        int parameters = 10, epochs = 5;
        string typeStr = "GPT";
        AIModelType type = getStringMapping(typeStr);
        AIConfiguration config(parameters, epochs, type);
        config.print();
    }
    if (tc == 5) {
        cout << "Testing Invalid Number of Parameters Exception:" << endl;
        int parameters, epochs;
        string typeStr = "GPT";
        cin >> parameters >> epochs;
        AIModelType type = getStringMapping(typeStr);
        try {
            AIConfiguration config(parameters, epochs, type);
            config.print();
        } catch (InvalidNumberOfParametersException &e) {
            e.print();
        }
    }
    if (tc == 6) {
        cout << "Testing Invalid Model Type Exception:" << endl;
        int parameters = 10, epochs = 5;
        string typeStr;
        cin >> typeStr;
        AIModelType type = getStringMapping(typeStr);
        try {
            AIConfiguration config(parameters, epochs, type);
            config.print();
        } catch (InvalidModelTypeException &e) {
            e.print();
        }
    }
    return 0;
}
