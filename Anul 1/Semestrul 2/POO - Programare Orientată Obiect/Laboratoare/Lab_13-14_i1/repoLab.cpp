#include "repoLab.h"

void RepoLab::adauga(const Carte& carte) {
    const_cast<RepoLab*>(this)->verificaProbabilitate();
    if (carti.find(carte.getTitlu()) != carti.end())
        throw DuplicateTitluException(carte.getTitlu());
    carti[carte.getTitlu()] = carte;
}

void RepoLab::sterge(const string& titlu) {
    const_cast<RepoLab*>(this)->verificaProbabilitate();
    auto it = carti.find(titlu);
    if (it == carti.end())
        throw CarteNotFoundException(titlu);
    carti.erase(it);
}

void RepoLab::modifica(const string& titlu, const Carte& carteNoua) {
    const_cast<RepoLab*>(this)->verificaProbabilitate();
    auto it = carti.find(titlu);
    if (it == carti.end())
        throw CarteNotFoundException(titlu);
    carti[titlu] = carteNoua;
}

const vector<Carte>& RepoLab::getAll() const {
    const_cast<RepoLab*>(this)->verificaProbabilitate();
    static vector<Carte> rezultat;
    rezultat.clear();
    for (const auto& pereche : carti)
        rezultat.push_back(pereche.second);
    return rezultat;
}

const Carte& RepoLab::cauta(const string& titlu) const {
    const_cast<RepoLab*>(this)->verificaProbabilitate();
    auto it = carti.find(titlu);
    if (it == carti.end())
        throw CarteNotFoundException(titlu);
    return it->second;
}

vector<Carte> RepoLab::filtreazaDupaTitlu(const string& titlu) const {
    const_cast<RepoLab*>(this)->verificaProbabilitate();
    vector<Carte> rezultat;
    for (const auto& pereche : carti)
        if (pereche.first.find(titlu) != string::npos)
            rezultat.push_back(pereche.second);
    return rezultat;
}

vector<Carte> RepoLab::filtreazaDupaAn(int an) const {
    const_cast<RepoLab*>(this)->verificaProbabilitate();
    vector<Carte> rezultat;
    for (const auto& pereche : carti)
        if (pereche.second.getAnAparitie() == an)
            rezultat.push_back(pereche.second);
    return rezultat;
}