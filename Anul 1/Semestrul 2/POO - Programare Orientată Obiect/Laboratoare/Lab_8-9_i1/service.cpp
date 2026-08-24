#include "service.h"

void Service::adaugaCarte(const string& titlu, const string& autor,
    const string& gen, int an) {
    Validator::valideaza(titlu, autor, gen, an);
    Carte c{ titlu, autor, gen, an };
    repo.adauga(c);
}

void Service::stergeCarte(const string& titlu) {
    repo.sterge(titlu);
}

void Service::modificaCarte(const string& titluVechi, const string& titlu,
    const string& autor, const string& gen, int an) {
    Validator::valideaza(titlu, autor, gen, an);
    Carte c{ titlu, autor, gen, an };
    repo.modifica(titluVechi, c);
}

const vector<Carte>& Service::getCarti() const noexcept {
    return repo.getAll();
}

const Carte& Service::cautaCarte(const string& titlu) const {
    return repo.cauta(titlu);
}

vector<Carte> Service::filtreazaDupaTitlu(const string& titlu) const {
    return repo.filtreazaDupaTitlu(titlu);
}

vector<Carte> Service::filtreazaDupaAn(int an) const {
    return repo.filtreazaDupaAn(an);
}

vector<Carte> Service::sorteazaDupaTitlu() const {
    auto copie = repo.getAll();
    std::sort(copie.begin(), copie.end(), [](const Carte& a, const Carte& b) {
        return a.getTitlu() < b.getTitlu();
        });
    return copie;
}

vector<Carte> Service::sorteazaDupaAutor() const {
    auto copie = repo.getAll();
    std::sort(copie.begin(), copie.end(), [](const Carte& a, const Carte& b) {
        return a.getAutor() < b.getAutor();
        });
    return copie;
}

vector<Carte> Service::sorteazaDupaAnSiGen() const {
    auto copie = repo.getAll();
    std::sort(copie.begin(), copie.end(), [](const Carte& a, const Carte& b) {
        if (a.getAnAparitie() != b.getAnAparitie())
            return a.getAnAparitie() < b.getAnAparitie();
        return a.getGen() < b.getGen();
        });
    return copie;
}

void Service::populeazaBiblioteca() {
    adaugaCarte("Ion", "Rebreanu", "roman", 1920);
    adaugaCarte("Baltagul", "Sadoveanu", "roman", 1930);
    adaugaCarte("Mara", "Slavici", "roman", 1906);
    adaugaCarte("Luceafarul", "Eminescu", "poezie", 1883);
    adaugaCarte("Ultima noapte", "Camil Petrescu", "roman", 1930);
    adaugaCarte("Enigma Otiliei", "Calinescu", "roman", 1938);
    adaugaCarte("Morometii", "Preda", "roman", 1955);
    adaugaCarte("Harap-Alb", "Creanga", "drama", 1877);
    adaugaCarte("Floare Albastra", "Eminescu", "poezie", 1873);
    adaugaCarte("Padurea Spanzuratilor", "Rebreanu", "roman", 1922);
}