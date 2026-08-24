#include "repoFisier.h"

repoFisier::repoFisier(const string& numeFisier)
    : numeFisier{ numeFisier } {
    incarcaDinFisier();
}

void repoFisier::incarcaDinFisier() {
    carti.clear();
    std::ifstream f(numeFisier);
    if (!f.is_open())
        return;

    string linie;
    while (std::getline(f, linie)) {
        if (linie.empty()) continue;
        std::istringstream ss(linie);
        string titlu, autor, gen, tok_an;
        if (!std::getline(ss, titlu, ',')) continue;
        if (!std::getline(ss, autor, ',')) continue;
        if (!std::getline(ss, gen, ',')) continue;
        if (!std::getline(ss, tok_an, ',')) continue;
        try {
            int an = std::stoi(tok_an);
            carti.emplace_back(titlu, autor, gen, an);
        }
        catch (...) {}
    }
}

void repoFisier::salveazaInFisier() const {
    std::ofstream f(numeFisier, std::ios::trunc);
    if (!f.is_open())
        throw AppException("Nu s-a putut deschide fisierul: " + numeFisier);
    for (const auto& c : carti)
        f << c.getTitlu() << "," << c.getAutor() << ","
        << c.getGen() << "," << c.getAnAparitie() << "\n";
}

void repoFisier::adauga(const Carte& carte) {
    RepoMemorie::adauga(carte);
    salveazaInFisier();
}

void repoFisier::sterge(const string& titlu) {
    RepoMemorie::sterge(titlu);
    salveazaInFisier();
}

void repoFisier::modifica(const string& titlu, const Carte& carteNoua) {
    RepoMemorie::modifica(titlu, carteNoua);
    salveazaInFisier();
}