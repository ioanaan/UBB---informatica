#pragma once
#include "repo.h"
#include "validator.h"

class Service {
private:
    Repo& repo;

public:
    Service(Repo& repo) noexcept : repo{ repo } {}
    Service(const Service&) = delete;

    void adaugaCarte(const string& titlu, const string& autor,
        const string& gen, int an);
    void stergeCarte(const string& titlu);
    void modificaCarte(const string& titluVechi, const string& titlu,
        const string& autor, const string& gen, int an);

    const vector<Carte>& getCarti() const noexcept;
    const Carte& cautaCarte(const string& titlu) const;

    vector<Carte> filtreazaDupaTitlu(const string& titlu) const;
    vector<Carte> filtreazaDupaAn(int an) const;

    vector<Carte> sorteazaDupaTitlu() const;
    vector<Carte> sorteazaDupaAutor() const;
    vector<Carte> sorteazaDupaAnSiGen() const;

    void populeazaBiblioteca();
};