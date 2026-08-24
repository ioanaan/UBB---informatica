#pragma once
#include "repo.h"
#include "exceptii.h"
#include <map>
#include <random>
using std::map;

class RepoLab : public Repo {
private:
    map<string, Carte> carti;
    double probabilitate;
    std::mt19937 generator;
    std::uniform_real_distribution<double> distributie;

    void verificaProbabilitate() {
        if (distributie(generator) < probabilitate)
            throw RepoLabException();
    }

public:
    explicit RepoLab(double probabilitate)
        : probabilitate{ probabilitate },
        generator{ std::random_device{}() },
        distributie{ 0.0, 1.0 } {
    }

    RepoLab(const RepoLab&) = delete;

    void adauga(const Carte& carte) override;
    void sterge(const string& titlu) override;
    void modifica(const string& titlu, const Carte& carteNoua) override;
    const vector<Carte>& getAll() const override;
    const Carte& cauta(const string& titlu) const override;
    vector<Carte> filtreazaDupaTitlu(const string& titlu) const override;
    vector<Carte> filtreazaDupaAn(int an) const override;
};