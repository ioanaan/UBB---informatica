#pragma once
#include "repoMemorie.h"
#include <fstream>
#include <sstream>

class repoFisier : public RepoMemorie {
private:
    string numeFisier;

    void incarcaDinFisier();
    void salveazaInFisier() const;

public:
    explicit repoFisier(const string& numeFisier);

    void adauga(const Carte& carte) override;
    void sterge(const string& titlu) override;
    void modifica(const string& titlu, const Carte& carteNoua) override;
};