#pragma once
#include "repo.h"

class RepoMemorie : public Repo {
protected:
    vector<Carte> carti;

public:
    RepoMemorie() = default;
    RepoMemorie(const RepoMemorie&) = delete;

    void adauga(const Carte& carte) override;
    void sterge(const string& titlu) override;
    void modifica(const string& titlu, const Carte& carteNoua) override;
    const vector<Carte>& getAll() const override;
    const Carte& cauta(const string& titlu) const override;
    vector<Carte> filtreazaDupaTitlu(const string& titlu) const override;
    vector<Carte> filtreazaDupaAn(int an) const override;
};