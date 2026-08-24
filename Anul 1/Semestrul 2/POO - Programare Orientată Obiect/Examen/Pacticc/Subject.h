#pragma once
#include "Observer.h"
#include <vector>

class Subject {
private:
    std::vector<Observer*> observers;

public:
    void addObserver(Observer* o) {
        observers.push_back(o);
    }

    /* notifica toti observerii */
    void notifyAll() {
        for (auto* o : observers)
            o->update();
    }

    virtual ~Subject() = default;
};
