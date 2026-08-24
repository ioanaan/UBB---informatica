#include "repo.h"

void Repo::adaugaCarte(const Carte& carte)
{
    carti.add(carte);
}

void Repo::stergeCarte(int index) noexcept
{
    carti.remove(index);
}

void Repo::modificaCarte(int index, const Carte& carteNoua)
{
    carti.get(index) = carteNoua;
}

const MyVector<Carte>& Repo::getCarti() const noexcept
{
    return carti;
}

int Repo::getSize() const noexcept
{
    return static_cast<int>(carti.size());
}