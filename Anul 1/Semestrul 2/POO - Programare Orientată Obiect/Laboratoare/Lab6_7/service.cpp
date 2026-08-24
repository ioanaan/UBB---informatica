#include "service.h"

Service::Service(Repo& repo) noexcept : repo{ repo } {
}

void Service::adaugaCarte(const string& titlu, const string& autor,
    const string& gen, int an)
{
    validator.valideazaCarte(titlu, autor, gen, an);
    if (cautaCarte(titlu) != -1)
        throw ValidationException("Cartea exista deja!\n");
    Carte c{ titlu, autor, gen, an };
    repo.adaugaCarte(c);
}

void Service::stergeCarte(int index)
{
    validator.valideazaIndex(index, repo.getSize());
    repo.stergeCarte(index);
}

void Service::modificaCarte(int index, const string& titlu, const string& autor,
    const string& gen, int an)
{
    validator.valideazaIndex(index, repo.getSize());
    validator.valideazaCarte(titlu, autor, gen, an);
    Carte c{ titlu, autor, gen, an };
    repo.modificaCarte(index, c);
}

const MyVector<Carte>& Service::getCarti() const noexcept
{
    return repo.getCarti();
}

int Service::cautaCarte(const string& titlu) const noexcept
{
    const MyVector<Carte>& carti = repo.getCarti();
    for (int i = 0; i < static_cast<int>(carti.size()); i++)
        if (carti.get(i).getTitlu() == titlu)
            return i;
    return -1;
}

MyVector<Carte> Service::filtreazaDupaTitlu(const string& titlu) const
{
    MyVector<Carte> rezultat;
    for (int i = 0; i < repo.getCarti().size(); i++)
        if (repo.getCarti().get(i).getTitlu().find(titlu) != string::npos)
            rezultat.add(repo.getCarti().get(i));
    return rezultat;
}

MyVector<Carte> Service::filtreazaDupaAn(int an) const
{
    MyVector<Carte> rezultat;
    for (int i = 0; i < repo.getCarti().size(); i++)
        if (repo.getCarti().get(i).getAnAparitie() == an)
            rezultat.add(repo.getCarti().get(i));
    return rezultat;
}

MyVector<Carte> Service::sorteazaDupaTitlu() const
{
    MyVector<Carte> rezultat = repo.getCarti();
    for (int i = 0; i < rezultat.size() - 1; i++)
        for (int j = i + 1; j < rezultat.size(); j++)
            if (rezultat.get(i).getTitlu() > rezultat.get(j).getTitlu())
            {
                Carte aux = rezultat.get(i);
                rezultat.get(i) = rezultat.get(j);
                rezultat.get(j) = aux;
            }
    return rezultat;
}

MyVector<Carte> Service::sorteazaDupaAutor() const
{
    MyVector<Carte> rezultat = repo.getCarti();
    for (int i = 0; i < rezultat.size() - 1; i++)
        for (int j = i + 1; j < rezultat.size(); j++)
            if (rezultat.get(i).getAutor() > rezultat.get(j).getAutor())
            {
                Carte aux = rezultat.get(i);
                rezultat.get(i) = rezultat.get(j);
                rezultat.get(j) = aux;
            }
    return rezultat;
}

MyVector<Carte> Service::sorteazaDupaAnSiGen() const
{
    MyVector<Carte> rezultat = repo.getCarti();
    for (int i = 0; i < rezultat.size() - 1; i++)
        for (int j = i + 1; j < rezultat.size(); j++)
        {
            bool trebuieSchimbat = false;
            if (rezultat.get(i).getAnAparitie() != rezultat.get(j).getAnAparitie())
                trebuieSchimbat = rezultat.get(i).getAnAparitie() > rezultat.get(j).getAnAparitie();
            else
                trebuieSchimbat = rezultat.get(i).getGen() > rezultat.get(j).getGen();

            if (trebuieSchimbat)
            {
                Carte aux = rezultat.get(i);
                rezultat.get(i) = rezultat.get(j);
                rezultat.get(j) = aux;
            }
        }
    return rezultat;
}