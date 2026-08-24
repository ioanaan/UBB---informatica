#pragma once
#include "carte.h"
#include "exceptii.h"
#include <vector>
#include <algorithm>
using std::vector;

class Repo {
private:
    vector<Carte> carti;

public:
    Repo() = default;
    Repo(const Repo&) = delete;

    void adauga(const Carte& carte);
    void sterge(const string& titlu);
    void modifica(const string& titlu, const Carte& carteNoua);
    const vector<Carte>& getAll() const noexcept;
    const Carte& cauta(const string& titlu) const;
    vector<Carte> filtreazaDupaTitlu(const string& titlu) const;
    vector<Carte> filtreazaDupaAn(int an) const;
};