#pragma once
#include "carte.h"
#include "exceptii.h"
#include <vector>
#include <algorithm>
using std::vector;

class Repo {
public:
    virtual ~Repo() = default;

    virtual void adauga(const Carte& carte) = 0;
    virtual void sterge(const string& titlu) = 0;
    virtual void modifica(const string& titlu, const Carte& carteNoua) = 0;
    virtual const vector<Carte>& getAll() const = 0;
    virtual const Carte& cauta(const string& titlu) const = 0;
    virtual vector<Carte> filtreazaDupaTitlu(const string& titlu) const = 0;
    virtual vector<Carte> filtreazaDupaAn(int an) const = 0;
};