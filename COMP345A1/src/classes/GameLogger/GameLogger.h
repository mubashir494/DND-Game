#ifndef COMP345A1_GAMELOGGER_H
#define COMP345A1_GAMELOGGER_H

#include <string>
#include <iostream>

using namespace std;

// Observer Interface
class IObserver {
public:
    virtual void update(const string& message) = 0;
    virtual ~IObserver() = default;
};

class IObservable {
public:
    virtual void attach(IObserver* observer) = 0;
    virtual void detach(IObserver* observer) = 0;
    bool loggingEnabled = true;

    void setLogging(bool enabled) {
        loggingEnabled = enabled;
    }

    virtual void notify(const std::string& message) = 0;

    virtual ~IObservable() = default;
};



class GameLogger : public IObserver {
public:
    void update(const string& message) override {
        cout << message << endl;
    }
};


#endif //COMP345A1_GAMELOGGER_H
