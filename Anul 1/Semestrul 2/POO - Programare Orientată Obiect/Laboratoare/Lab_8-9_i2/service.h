#pragma once
#include "repoMemorie.h"
#include "validator.h"
#include "ActiuneUndo.h"
#include <memory>
#include <vector>
using std::unique_ptr;

class Service {
private:
    Repo& repo;
    vector<unique_ptr<ActiuneUndo>> istoricUndo;

public:
    Service(Repo& repo) noexcept : repo{ repo } {}
    Service(const Service&) = delete;

    void adaugaCarte(const string& titlu, const string& autor,
        const string& gen, int an);
    void stergeCarte(const string& titlu);
    void modificaCarte(const string& titluVechi, const string& titlu,
        const string& autor, const string& gen, int an);

    const vector<Carte>& getCarti() const;
    const Carte& cautaCarte(const string& titlu) const;

    vector<Carte> filtreazaDupaTitlu(const string& titlu) const;
    vector<Carte> filtreazaDupaAn(int an) const;

    vector<Carte> sorteazaDupaTitlu() const;
    vector<Carte> sorteazaDupaAutor() const;
    vector<Carte> sorteazaDupaAnSiGen() const;

    void populeazaBiblioteca(int n = 10);
    void undo();
};