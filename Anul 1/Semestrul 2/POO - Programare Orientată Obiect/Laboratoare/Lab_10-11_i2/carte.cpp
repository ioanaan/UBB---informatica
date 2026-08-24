#include "carte.h"

Carte::Carte(const string& titlu, const string& autor,
    const string& gen, int an_aparitie)
    : titlu{ titlu }, autor{ autor }, gen{ gen }, an_aparitie{ an_aparitie } {
}

const string& Carte::getTitlu() const noexcept { return titlu; }
const string& Carte::getAutor() const noexcept { return autor; }
const string& Carte::getGen() const noexcept { return gen; }
int Carte::getAnAparitie() const noexcept { return an_aparitie; }

void Carte::setTitlu(const string& newTitlu) { titlu = newTitlu; }
void Carte::setAutor(const string& newAutor) { autor = newAutor; }
void Carte::setGen(const string& newGen) { gen = newGen; }
void Carte::setAnAparitie(int an) noexcept{ an_aparitie = an; }

Carte::Carte(const Carte& other) 
    : titlu{ other.titlu }, autor{ other.autor },
    gen{ other.gen }, an_aparitie{ other.an_aparitie } 
{
    cout << "[Copy] Se creeaza o copie pentru cartea: " << titlu << "\n";
}