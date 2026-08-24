#pragma once
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

class Carte
{
private:
    string titlu, autor, gen;
    int an_aparitie;

public:
    Carte(const string& titlu, const string& autor,
        const string& gen, int an_aparitie);

    const string& getTitlu() const noexcept;
    const string& getAutor() const noexcept;
    const string& getGen() const noexcept;
    int getAnAparitie() const noexcept;

    void setTitlu(const string& newTitlu);
    void setAutor(const string& newAutor);
    void setGen(const string& newGen);
    void setAnAparitie(int an) noexcept;

    Carte(const Carte& other);
    Carte& operator=(const Carte& other) = default;
    Carte(Carte&& other) = default;
    Carte& operator=(Carte&& other) = default;
    ~Carte() = default;
    Carte() noexcept : titlu{ "" }, autor{ "" }, gen{ "" }, an_aparitie{ 0 } {}
};