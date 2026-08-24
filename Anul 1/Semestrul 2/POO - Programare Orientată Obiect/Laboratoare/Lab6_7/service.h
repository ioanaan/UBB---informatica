#pragma once
#include "repo.h"
#include "validator.h"

class Service 
{
private:
    Repo& repo;
    Validator validator;

public:
    Service(Repo& repo) noexcept;

    void adaugaCarte(const string& titlu, const string& autor,
        const string& gen, int an);
    void stergeCarte(int index);
    void modificaCarte(int index, const string& titlu, const string& autor,
        const string& gen, int an);

    const MyVector<Carte>& getCarti() const noexcept;
    int cautaCarte(const string& titlu) const noexcept;

    MyVector<Carte> filtreazaDupaTitlu(const string& titlu) const;
    MyVector<Carte> filtreazaDupaAn(int an) const;

    MyVector<Carte> sorteazaDupaTitlu() const;
    MyVector<Carte> sorteazaDupaAutor() const;
    MyVector<Carte> sorteazaDupaAnSiGen() const;
};