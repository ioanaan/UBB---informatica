#pragma once
#include "carte.h"
#include "MyVector.h"

class Repo 
{
private:
    MyVector<Carte> carti;

public:
    void adaugaCarte(const Carte& carte);
    void stergeCarte(int index) noexcept;
    void modificaCarte(int index, const Carte& carteNoua);
    const MyVector<Carte>& getCarti() const noexcept;
    int getSize() const noexcept;
};