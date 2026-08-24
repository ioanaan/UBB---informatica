#include "service.h"
#include <random>
#include <string>

void Service::adaugaCarte(const string& titlu, const string& autor,
    const string& gen, int an) {
    Validator::valideaza(titlu, autor, gen, an);
    Carte c{ titlu, autor, gen, an };
    repo.adauga(c);
    istoricUndo.push_back(std::make_unique<UndoAdauga>(repo, c));
}

void Service::stergeCarte(const string& titlu) {
    istoricUndo.push_back(std::make_unique<UndoSterge>(repo, repo.cauta(titlu)));
    repo.sterge(titlu);
}

void Service::modificaCarte(const string& titluVechi, const string& titlu,
    const string& autor, const string& gen, int an) {
    Validator::valideaza(titlu, autor, gen, an);
    istoricUndo.push_back(std::make_unique<UndoModifica>(repo, repo.cauta(titluVechi), titlu));
    Carte c{ titlu, autor, gen, an };
    repo.modifica(titluVechi, c);
}

const vector<Carte>& Service::getCarti() const {
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

void Service::populeazaBiblioteca(int n) {
    const vector<string> titluri = {
        "Ion", "Baltagul", "Mara", "Luceafarul", "Ultima noapte",
        "Enigma Otiliei", "Morometii", "Harap-Alb", "Floare Albastra",
        "Padurea Spanzuratilor", "Rascoala", "Ciuleandra", "Padurea",
        "Iona", "Acasa", "Noaptea", "Dimineata", "Seara", "Toamna", "Iarna"
    };
    const vector<string> autori = {
        "Rebreanu", "Sadoveanu", "Slavici", "Eminescu", "Camil Petrescu",
        "Calinescu", "Preda", "Creanga", "Caragiale", "Blaga"
    };
    const vector<string> genuri = { "roman", "nuvela", "poezie", "drama" };

    std::random_device rd;
    std::mt19937 g(rd());

    for (int i = 0; i < n; i++) {
        string titlu = titluri[g() % titluri.size()] + "_" + std::to_string(i);
        string autor = autori[g() % autori.size()];
        string gen = genuri[g() % genuri.size()];
        int anAparitie = 1800 + static_cast<int>(g() % 200);
        try {
            adaugaCarte(titlu, autor, gen, anAparitie);
        }
        catch (const AppException&) {}
    }
}

void Service::undo() {
    if (istoricUndo.empty())
        throw AppException("Nu exista operatii de undo!");
    istoricUndo.back()->doUndo();
    istoricUndo.pop_back();
}