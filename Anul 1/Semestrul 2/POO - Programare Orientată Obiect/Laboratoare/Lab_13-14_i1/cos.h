#pragma once
#include "service.h"
#include "exceptii.h"
#include <vector>
#include <string>
#include <algorithm>
using std::vector;
using std::string;

class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};

class Observable {
private:
    std::vector<Observer*> observers;
public:
    void addObserver(Observer* obs);
    void removeObserver(Observer* obs);
protected:
    void notify();
};


class Cos : public Observable {
private:
    vector<Carte> carti;
    Service& service;

public:
    Cos(Service& service) noexcept : service{ service } {}

    void goleste() noexcept;
    void adauga(const string& titlu);
    void genereaza(size_t n);
    const vector<Carte>& getCarti() const noexcept;
    size_t getNrCarti() const noexcept;
    void exportHTML(const string& numeFisier) const;
};