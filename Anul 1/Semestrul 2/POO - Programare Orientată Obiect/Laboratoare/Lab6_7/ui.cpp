#include "ui.h"

UI::UI(Service& service) noexcept : service{ service }
{
}

void UI::afiseazaMeniu() const 
{
    cout << "\n-Biblioteca-\n";
    cout << "1. Adauga carte\n";
    cout << "2. Sterge carte\n";
    cout << "3. Modifica carte\n";
    cout << "4. Afiseaza toate cartile\n";
    cout << "5. Cauta carte\n";
    cout << "6. Filtreaza carti\n";
    cout << "7. Sorteaza carti\n";
    cout << "0. Iesire\n";
    cout << "Alege optiunea: ";
}

void UI::afiseazaCarti(const MyVector<Carte>& carti) const 
{
    if (carti.size() == 0)
    {
        cout << "Nu exista carti.\n";
        return;
    }
    for (int i = 0; i < carti.size(); i++) {
        cout << i + 1 << ". "
            << carti[i].getTitlu() << " | "
            << carti[i].getAutor() << " | "
            << carti[i].getGen() << " | "
            << carti[i].getAnAparitie() << "\n";
    }
}

void UI::handleAdauga()
{
    string titlu, autor, gen;
    int an;
    cout << "Titlu: "; getline(cin, titlu);
    cout << "Autor: "; getline(cin, autor);
    cout << "Gen (roman / nuvela / poezie / drama): ";   getline(cin, gen);
    cout << "An: ";    cin >> an;
    try {
        service.adaugaCarte(titlu, autor, gen, an);
        cout << "Carte adaugata!\n";
    }
    catch (const ValidationException& e) {
        cout << "Eroare: " << e.getMesaj();
    }
}

void UI::handleSterge()
{
    afiseazaCarti(service.getCarti());
    int index;
    cout << "Numarul cartii de sters: "; cin >> index;
    try {
        service.stergeCarte(index - 1);
        cout << "Carte stearsa!\n";
    }
    catch (const ValidationException& e) {
        cout << "Eroare: " << e.getMesaj();
    }
}

void UI::handleModifica()
{
    afiseazaCarti(service.getCarti());
    int index;
    cout << "Numarul cartii de modificat: "; cin >> index;
    cin.ignore();
    string titlu, autor, gen;
    int an;
    cout << "Titlu nou: ";  getline(cin, titlu);
    cout << "Autor nou: ";  getline(cin, autor);
    cout << "Gen nou: ";    getline(cin, gen);
    cout << "An nou: ";     cin >> an;
    try {
        service.modificaCarte(index - 1, titlu, autor, gen, an);
        cout << "Carte modificata!\n";
    }
    catch (const ValidationException& e) {
        cout << "Eroare: " << e.getMesaj();
    }
}

void UI::handleCauta() 
{
    string titlu;
    cout << "Titlu de cautat: "; cin >> titlu;
    const int index = service.cautaCarte(titlu);
    if (index == -1) 
    {
        cout << "Cartea nu a fost gasita.\n";
        return;
    }
    const Carte& c = service.getCarti()[index];
    cout << "Gasita: " << c.getTitlu() << " | "
        << c.getAutor() << " | "
        << c.getGen() << " | "
        << c.getAnAparitie() << "\n";
}

void UI::handleFiltreaza() 
{
    cout << "1. Dupa titlu\n";
    cout << "2. Dupa an\n";
    cout << "Optiunea ta: ";
    int opt; cin >> opt;
    if (opt == 1) 
    {
        string titlu;
        cout << "Titlu: "; getline(cin, titlu);
        afiseazaCarti(service.filtreazaDupaTitlu(titlu));
    }
    else if (opt == 2) 
    {
        int an;
        cout << "An: "; cin >> an;
        afiseazaCarti(service.filtreazaDupaAn(an));
    }
}

void UI::handleSorteaza() 
{
    cout << "1. Dupa titlu\n";
    cout << "2. Dupa autor\n";
    cout << "3. Dupa an si gen\n";
    cout << "Optiunea ta: ";
    int opt; cin >> opt;
    if (opt == 1)
        afiseazaCarti(service.sorteazaDupaTitlu());
    else if (opt == 2)
        afiseazaCarti(service.sorteazaDupaAutor());
    else if (opt == 3)
        afiseazaCarti(service.sorteazaDupaAnSiGen());
}

void UI::run() 
{
    int optiune;
    do 
    {
        afiseazaMeniu();
        cin >> optiune;
        cin.ignore();

        if (optiune == 1) 
            handleAdauga();
        else if (optiune == 2) 
            handleSterge();
        else if (optiune == 3) 
            handleModifica();
        else if (optiune == 4) 
            afiseazaCarti(service.getCarti());
        else if (optiune == 5) 
            handleCauta();
        else if (optiune == 6) 
            handleFiltreaza();
        else if (optiune == 7) 
            handleSorteaza();
        else if (optiune != 0) 
            cout << "Optiune invalida!\n";
    } while (optiune != 0);
}