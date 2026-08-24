#pragma once
#include "service.h"
#include "exceptii.h"
#include <vector>
#include <string>
using std::vector;
using std::string;

class Cos {
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