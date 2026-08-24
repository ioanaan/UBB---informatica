#include "ui.h"
#include <iostream>
#include <fstream>
using std::cout;
using std::cin;

void UI::alegeStorare() {
    cout << "\nAlegeti tipul de stocare:\n";
    cout << "1. In memorie\n";
    cout << "2. Fisier TXT\n";
    cout << "3. RepoLab (map + probabilitate exceptie)\n";
    cout << "Alege optiunea: ";

    int opt;
    while (!(cin >> opt) || (opt < 1 || opt > 3)) {
        cout << "Optiune invalida! Introduceti 1, 2 sau 3: ";
        cin.clear(); cin.ignore(1000, '\n');
    }

    if (opt == 1) {
        repo = std::make_unique<RepoMemorie>();
        cout << "\nStorare: memorie\n";
    }
    else if (opt == 2) {
        const string numeFisier = "carti.txt";
        std::ofstream(numeFisier, std::ios::app).close();
        repo = std::make_unique<repoFisier>(numeFisier);
        cout << "\nStorare: fisier \"carti.txt\"\n";
    }
    else {
        double prob;
        cout << "Introduceti probabilitatea de exceptie (0.0 - 1.0): ";
        while (!(cin >> prob) || prob < 0.0 || prob > 1.0) {
            cout << "Valoare invalida! Introduceti o valoare intre 0 si 1: ";
            cin.clear(); cin.ignore(1000, '\n');
        }
        repo = std::make_unique<RepoLab>(prob);
        cout << "\nStorare: RepoLab cu probabilitate " << prob << "\n";
    }

    service = std::make_unique<Service>(*repo);
    cos = std::make_unique<Cos>(*service);
}

void UI::afiseazaBiblioteca() const {
    const auto& carti = service->getCarti();
    if (carti.empty()) {
        cout << "\nBiblioteca este goala!\n";
        return;
    }
    cout << "\nBiblioteca:\n";
    for (const auto& c : carti)
        cout << "  " << c.getTitlu() << " | " << c.getAutor() << " | "
        << c.getGen() << " | " << c.getAnAparitie() << "\n";
    cout << "\n";
}

void UI::handleAdauga() {
    string titlu, autor, gen;
    int an;
    cout << "\nTitlu: "; getline(cin, titlu);
    cout << "Autor: "; getline(cin, autor);
    cout << "Gen (roman/nuvela/poezie/drama): "; getline(cin, gen);
    cout << "An: "; cin >> an;
    try {
        service->adaugaCarte(titlu, autor, gen, an);
        cout << "\nCarte adaugata!\n";
        afiseazaBiblioteca();
    }
    catch (const AppException& e) {
        cout << "\nEroare: " << e.what() << "\n";
    }
}

void UI::handleSterge() {
    afiseazaBiblioteca();
    string titlu;
    cout << "Titlul cartii de sters: "; getline(cin, titlu);
    try {
        service->stergeCarte(titlu);
        cout << "\nCarte stearsa!\n";
        afiseazaBiblioteca();
    }
    catch (const AppException& e) {
        cout << "\nEroare: " << e.what() << "\n";
    }
}

void UI::handleModifica() {
    afiseazaBiblioteca();
    string titluVechi, titlu, autor, gen;
    int an;
    cout << "Titlul cartii de modificat: "; getline(cin, titluVechi);
    cout << "Titlu nou: "; getline(cin, titlu);
    cout << "Autor nou: "; getline(cin, autor);
    cout << "Gen nou (roman/nuvela/poezie/drama): "; getline(cin, gen);
    cout << "An nou: "; cin >> an;
    try {
        service->modificaCarte(titluVechi, titlu, autor, gen, an);
        cout << "\nCarte modificata!\n";
        afiseazaBiblioteca();
    }
    catch (const AppException& e) {
        cout << "\nEroare: " << e.what() << "\n";
    }
}

void UI::handleCauta() {
    string titlu;
    cout << "\nTitlu de cautat: "; getline(cin, titlu);
    try {
        const Carte& c = service->cautaCarte(titlu);
        cout << "\nGasita: " << c.getTitlu() << " | " << c.getAutor()
            << " | " << c.getGen() << " | " << c.getAnAparitie() << "\n";
    }
    catch (const AppException& e) {
        cout << "\nEroare: " << e.what() << "\n";
    }
}

void UI::handleFiltreaza() {
    cout << "\n1. Dupa titlu\n";
    cout << "2. Dupa an\n";
    cout << "Alege optiunea: ";
    int opt; cin >> opt; cin.ignore();

    if (opt == 1) {
        string titlu;
        cout << "Titlu: "; getline(cin, titlu);
        const auto rez = service->filtreazaDupaTitlu(titlu);
        if (rez.empty()) { cout << "\nNu exista carti cu titlul dat.\n"; return; }
        cout << "\n";
        for (const auto& c : rez)
            cout << "  " << c.getTitlu() << " | " << c.getAutor() << " | "
            << c.getGen() << " | " << c.getAnAparitie() << "\n";
    }
    else if (opt == 2) {
        int an;
        cout << "An: "; cin >> an; cin.ignore();
        const auto rez = service->filtreazaDupaAn(an);
        if (rez.empty()) { cout << "\nNu exista carti din anul dat.\n"; return; }
        cout << "\n";
        for (const auto& c : rez)
            cout << "  " << c.getTitlu() << " | " << c.getAutor() << " | "
            << c.getGen() << " | " << c.getAnAparitie() << "\n";
    }
    else cout << "\nOptiune invalida!\n";
}

void UI::handleSorteaza() {
    cout << "\n1. Dupa titlu\n";
    cout << "2. Dupa autor\n";
    cout << "3. Dupa an si gen\n";
    cout << "Alege optiunea: ";
    int opt; cin >> opt; cin.ignore();

    vector<Carte> lista;
    if (opt == 1) lista = service->sorteazaDupaTitlu();
    else if (opt == 2) lista = service->sorteazaDupaAutor();
    else if (opt == 3) lista = service->sorteazaDupaAnSiGen();
    else { cout << "\nOptiune invalida!\n"; return; }

    cout << "\n";
    for (const auto& c : lista)
        cout << "  " << c.getTitlu() << " | " << c.getAutor() << " | "
        << c.getGen() << " | " << c.getAnAparitie() << "\n";
}

void UI::handlePopuleaza() {
    int n;
    cout << "\nNumarul de carti de adaugat: ";
    while (!(cin >> n) || n <= 0) {
        cout << "Numar invalid!\n";
        cin.clear(); cin.ignore(1000, '\n');
    }
    cin.ignore();
    try {
        service->populeazaBiblioteca(n);
        cout << "\nBiblioteca a fost populata cu " << n << " carti.\n";
        afiseazaBiblioteca();
    }
    catch (const AppException& e) {
        cout << "\nEroare: " << e.what() << "\n";
    }
}

void UI::handleUndo() {
    try {
        service->undo();
        cout << "\nUndo efectuat cu succes!\n";
        afiseazaBiblioteca();
    }
    catch (const AppException& e) {
        cout << "\nEroare: " << e.what() << "\n";
    }
}

void UI::afiseazaCos() const {
    const auto& carti = cos->getCarti();
    cout << "\nCos curent (" << cos->getNrCarti() << " carti):\n";
    if (carti.empty()) { cout << "  (cosul este gol)\n"; return; }
    for (const auto& c : carti)
        cout << "  " << c.getTitlu() << " | " << c.getAutor() << " | "
        << c.getGen() << " | " << c.getAnAparitie() << "\n";
    cout << "\n";
}

void UI::handleCosGoleste() {
    cos->goleste();
    cout << "\nCosul a fost golit.\n";
    afiseazaCos();
}

void UI::handleCosAdauga() {
    afiseazaBiblioteca();
    string titlu;
    cout << "Titlul cartii de adaugat in cos: "; getline(cin, titlu);
    try {
        cos->adauga(titlu);
        afiseazaCos();
    }
    catch (const AppException& e) {
        cout << "\nEroare: " << e.what() << "\n";
        cout << "Total carti in cos: " << cos->getNrCarti() << "\n";
    }
}

void UI::handleCosGenereaza() {
    int n;
    cout << "\nNumarul de carti pentru cos aleator: ";
    while (!(cin >> n)) {
        cout << "Numar invalid!\n";
        cin.clear(); cin.ignore(1000, '\n');
    }
    cin.ignore();
    try {
        cos->genereaza(static_cast<size_t>(n));
        afiseazaCos();
    }
    catch (const AppException& e) {
        cout << "\nEroare: " << e.what() << "\n";
        cout << "Total carti in cos: " << cos->getNrCarti() << "\n";
    }
}
void UI::handleCosExport() {
    cout << "\nFormat export:\n";
    cout << "1. HTML\n";
    cout << "Alege optiunea: ";
    int tip; cin >> tip; cin.ignore();

    string numeFisier;
    cout << "Numele fisierului (fara extensie): ";
    getline(cin, numeFisier);

    try {
        if (tip == 1) {
            cos->exportHTML(numeFisier);
            cout << "\nCosul exportat in " << numeFisier << ".html\n";
        }
        else cout << "\nOptiune invalida!\n";
    }
    catch (const AppException& e) {
        cout << "\nEroare la export: " << e.what() << "\n";
    }
    cout << "Total carti in cos: " << cos->getNrCarti() << "\n";
}

void UI::handleCos() {
    int cmd;
    do {
        cout << "\n--- MENIU COS ---\n\n";
        cout << "1. Afiseaza cos\n";
        cout << "2. Goleste cos\n";
        cout << "3. Adauga carte in cos (dupa titlu)\n";
        cout << "4. Genereaza cos aleator\n";
        cout << "5. Export cos (HTML)\n";
        cout << "0. Inapoi la meniul principal\n\n";
        cout << "Alege optiunea: ";
        cin >> cmd; cin.ignore();

        if (cmd == 1) afiseazaCos();
        else if (cmd == 2) handleCosGoleste();
        else if (cmd == 3) handleCosAdauga();
        else if (cmd == 4) handleCosGenereaza();
        else if (cmd == 5) handleCosExport();
        else if (cmd != 0) cout << "\nOptiune invalida!\n";
    } while (cmd != 0);
}

void UI::afiseazaMeniu() const {
    cout << "\n=== BIBLIOTECA ===\n\n";
    cout << "1. Afiseaza biblioteca\n";
    cout << "2. Populeaza biblioteca\n";
    cout << "3. Adauga carte\n";
    cout << "4. Sterge carte\n";
    cout << "5. Modifica carte\n";
    cout << "6. Cauta carte\n";
    cout << "7. Filtreaza carti\n";
    cout << "8. Sorteaza carti\n";
    cout << "9. Gestionare cos\n";
    cout << "10. Undo\n";
    cout << "0. Iesire\n\n";
    cout << "Alege optiunea: ";
}

void UI::run() {
    alegeStorare();

    int optiune;
    do {
        afiseazaMeniu();
        cin >> optiune;
        cin.ignore();

        if (optiune == 1) afiseazaBiblioteca();
        else if (optiune == 2) handlePopuleaza();
        else if (optiune == 3) handleAdauga();
        else if (optiune == 4) handleSterge();
        else if (optiune == 5) handleModifica();
        else if (optiune == 6) handleCauta();
        else if (optiune == 7) handleFiltreaza();
        else if (optiune == 8) handleSorteaza();
        else if (optiune == 9) handleCos();
        else if (optiune == 10) handleUndo();
        else if (optiune != 0) cout << "\nOptiune invalida!\n";
    } while (optiune != 0);

    cout << "\nLa revedere!\n";
}