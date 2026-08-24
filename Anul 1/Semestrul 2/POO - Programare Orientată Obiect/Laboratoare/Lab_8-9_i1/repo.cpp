#include "repo.h"

void Repo::adauga(const Carte& carte) {
    auto it = std::find_if(carti.begin(), carti.end(), [&carte](const Carte& c) noexcept {
        return c.getTitlu() == carte.getTitlu();
        });
    if (it != carti.end())
        throw DuplicateTitluException(carte.getTitlu());
    carti.push_back(carte);
}

void Repo::sterge(const string& titlu) {
    auto it = std::find_if(carti.begin(), carti.end(), [&titlu](const Carte& c) noexcept {
        return c.getTitlu() == titlu;
        });
    if (it == carti.end())
        throw CarteNotFoundException(titlu);
    carti.erase(it);
}

void Repo::modifica(const string& titlu, const Carte& carteNoua) {
    auto it = std::find_if(carti.begin(), carti.end(), [&titlu](const Carte& c) noexcept {
        return c.getTitlu() == titlu;
        });
    if (it == carti.end())
        throw CarteNotFoundException(titlu);
    *it = carteNoua;
}

const vector<Carte>& Repo::getAll() const noexcept {
    return carti;
}

const Carte& Repo::cauta(const string& titlu) const {
    auto it = std::find_if(carti.begin(), carti.end(), [&titlu](const Carte& c) noexcept {
        return c.getTitlu() == titlu;
        });
    if (it == carti.end())
        throw CarteNotFoundException(titlu);
    return *it;
}

vector<Carte> Repo::filtreazaDupaTitlu(const string& titlu) const {
    vector<Carte> rezultat;
    std::copy_if(carti.begin(), carti.end(), std::back_inserter(rezultat),
        [&titlu](const Carte& c) noexcept {
            return c.getTitlu().find(titlu) != string::npos;
        });
    return rezultat;
}

vector<Carte> Repo::filtreazaDupaAn(int an) const {
    vector<Carte> rezultat;
    std::copy_if(carti.begin(), carti.end(), std::back_inserter(rezultat),
        [an](const Carte& c) noexcept {
            return c.getAnAparitie() == an;
        });
    return rezultat;
}