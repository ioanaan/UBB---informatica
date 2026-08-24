#include "teste.h"
#include "service.h"
#include <cassert>

void testAdauga()
{
    Repo repo;
    Service service{ repo };

    service.adaugaCarte("Ion", "Rebreanu", "roman", 1920);
    assert(static_cast<int>(service.getCarti().size()) == 1);
    assert(service.getCarti()[0].getTitlu() == "Ion");
    assert(service.getCarti()[0].getAutor() == "Rebreanu");
    assert(service.getCarti()[0].getGen() == "roman");
    assert(service.getCarti()[0].getAnAparitie() == 1920);

    service.adaugaCarte("Baltagul", "Sadoveanu", "roman", 1930);
    assert(static_cast<int>(service.getCarti().size()) == 2);
}

void testAdauga2()
{
    Repo repo;
    Service service{ repo };

    service.adaugaCarte("Ion", "Rebreanu", "roman", 1920);
    assert(static_cast<int>(service.getCarti().size()) == 1);
    assert(repo.getSize() == 1);

    service.adaugaCarte("Baltagul", "Sadoveanu", "roman", 1930);
    assert(static_cast<int>(service.getCarti().size()) == 2);
    assert(repo.getSize() == 2);
}

void testSterge()
{
    Repo repo;
    Service service{ repo };

    service.adaugaCarte("Ion", "Rebreanu", "roman", 1920);
    service.adaugaCarte("Baltagul", "Sadoveanu", "roman", 1930);
    assert(static_cast<int>(service.getCarti().size()) == 2);

    service.stergeCarte(0);
    assert(static_cast<int>(service.getCarti().size()) == 1);
    assert(service.getCarti()[0].getTitlu() == "Baltagul");
}

void testModifica()
{
    Repo repo;
    Service service{ repo };

    service.adaugaCarte("Ion", "Rebreanu", "roman", 1920);
    service.modificaCarte(0, "Ion - editie noua", "Rebreanu", "roman", 2000);

    assert(service.getCarti()[0].getTitlu() == "Ion - editie noua");
    assert(service.getCarti()[0].getAnAparitie() == 2000);
}

void testCauta()
{
    Repo repo;
    Service service{ repo };

    service.adaugaCarte("Ion", "Rebreanu", "roman", 1920);
    service.adaugaCarte("Baltagul", "Sadoveanu", "roman", 1930);

    assert(service.cautaCarte("Ion") == 0);
    assert(service.cautaCarte("Morometii") == -1);
}

void testFiltreazaDupaTitlu()
{
    Repo repo;
    Service service{ repo };

    service.adaugaCarte("Ion", "Rebreanu", "roman", 1920);
    service.adaugaCarte("Baltagul", "Sadoveanu", "roman", 1930);
    service.adaugaCarte("Ionel", "Autor", "nuvela", 1950);

    assert(static_cast<int>(service.filtreazaDupaTitlu("Ion").size()) == 2);
    assert(static_cast<int>(service.filtreazaDupaTitlu("Morometii").size()) == 0);
}

void testFiltreazaDupaAn()
{
    Repo repo;
    Service service{ repo };

    service.adaugaCarte("Ion", "Rebreanu", "roman", 1920);
    service.adaugaCarte("Baltagul", "Sadoveanu", "roman", 1930);
    service.adaugaCarte("Mara", "Slavici", "roman", 1920);

    assert(static_cast<int>(service.filtreazaDupaAn(1920).size()) == 2);
    assert(static_cast<int>(service.filtreazaDupaAn(2000).size()) == 0);
}

void testSorteazaDupaTitlu()
{
    Repo repo;
    Service service{ repo };

    service.adaugaCarte("Baltagul", "Sadoveanu", "roman", 1930);
    service.adaugaCarte("Ion", "Rebreanu", "roman", 1920);
    service.adaugaCarte("Mara", "Slavici", "roman", 1906);

    MyVector<Carte> rezultat = service.sorteazaDupaTitlu();
    assert(rezultat[0].getTitlu() == "Baltagul");
    assert(rezultat[1].getTitlu() == "Ion");
    assert(rezultat[2].getTitlu() == "Mara");
}

void testSorteazaDupaAutor()
{
    Repo repo;
    Service service{ repo };

    service.adaugaCarte("Baltagul", "Sadoveanu", "roman", 1930);
    service.adaugaCarte("Ion", "Rebreanu", "roman", 1920);
    service.adaugaCarte("Mara", "Slavici", "roman", 1906);

    MyVector<Carte> rezultat = service.sorteazaDupaAutor();
    assert(rezultat[0].getAutor() == "Rebreanu");
    assert(rezultat[1].getAutor() == "Sadoveanu");
    assert(rezultat[2].getAutor() == "Slavici");
}

void testSorteazaDupaAnSiGen()
{
    Repo repo;
    Service service{ repo };

    service.adaugaCarte("Mara", "Slavici", "roman", 1906);
    service.adaugaCarte("Baltagul", "Sadoveanu", "roman", 1930);
    service.adaugaCarte("Ion", "Rebreanu", "nuvela", 1906);

    MyVector<Carte> rezultat = service.sorteazaDupaAnSiGen();
    assert(rezultat[0].getGen() == "nuvela");
    assert(rezultat[1].getGen() == "roman");
    assert(rezultat[2].getAnAparitie() == 1930);
}

void testSetteri()
{
    Carte c{ "Ion", "Rebreanu", "roman", 1920 };

    c.setTitlu("Baltagul");
    assert(c.getTitlu() == "Baltagul");

    c.setAutor("Sadoveanu");
    assert(c.getAutor() == "Sadoveanu");

    c.setGen("nuvela");
    assert(c.getGen() == "nuvela");

    c.setAnAparitie(1930);
    assert(c.getAnAparitie() == 1930);
}

void testCopyConstructor()
{
    Carte c1{ "Ion", "Rebreanu", "roman", 1920 };
    Carte c2{ c1 };

    assert(c2.getTitlu() == "Ion");
    assert(c2.getAutor() == "Rebreanu");
    assert(c2.getGen() == "roman");
    assert(c2.getAnAparitie() == 1920);
}

void testValidare()
{
    Repo repo;
    Service service{ repo };

    // titlu gol
    try {
        service.adaugaCarte("", "Rebreanu", "roman", 1920);
        assert(false);
    }
    catch (const ValidationException&) { assert(true); }

    // autor gol
    try {
        service.adaugaCarte("Ion", "", "roman", 1920);
        assert(false);
    }
    catch (const ValidationException&) { assert(true); }

    // gen invalid
    try {
        service.adaugaCarte("Ion", "Rebreanu", "invalid", 1920);
        assert(false);
    }
    catch (const ValidationException&) { assert(true); }

    // an invalid
    try {
        service.adaugaCarte("Ion", "Rebreanu", "roman", -1);
        assert(false);
    }
    catch (const ValidationException&) { assert(true); }

    // duplicat
    service.adaugaCarte("Ion", "Rebreanu", "roman", 1920);
    try {
        service.adaugaCarte("Ion", "Rebreanu", "roman", 1920);
        assert(false);
    }
    catch (const ValidationException&) { assert(true); }

    // index invalid la stergere
    try {
        service.stergeCarte(-1);
        assert(false);
    }
    catch (const ValidationException&) { assert(true); }

    // index invalid la modificare
    try {
        service.modificaCarte(-1, "Ion", "Rebreanu", "roman", 1920);
        assert(false);
    }
    catch (const ValidationException&) { assert(true); }
}

void testValidationException()
{
    ValidationException e{ "test eroare" };
    assert(e.getMesaj() == "test eroare");
}

void testSorteazaMyVector()
{
    Repo repo;
    Service service{ repo };
    service.adaugaCarte("Mara", "Slavici", "roman", 1906);
    service.adaugaCarte("Baltagul", "Sadoveanu", "roman", 1930);
    MyVector<Carte> rezultat = service.sorteazaDupaTitlu();
    assert(rezultat[0].getTitlu() == "Baltagul");
    assert(rezultat[1].getTitlu() == "Mara");
}

void testMyVector()
{
    // testeaza redimensionarea
    MyVector<int> v;
    for (int i = 0; i < 15; i++)
        v.add(i);
    assert(v.size() == 15);
    assert(v[0] == 0);
    assert(v[14] == 14);

    // testeaza operator=
    MyVector<int> v2;
    v2 = v;
    assert(v2.size() == 15);

    // testeaza copy constructor
    MyVector<int> v3{ v };
    assert(v3.size() == 15);

    // testeaza remove
    v.remove(0);
    assert(v.size() == 14);
}

void testMyVectorSelfAssign()
{
    MyVector<int> v;
    v.add(1);
    v.add(2);
    v = v;  // self assignment - testeaza return *this
    assert(v.size() == 2);
    assert(v[0] == 1);
}

void testAll()
{
    testAdauga();
    testAdauga2();
    testSterge();
    testModifica();
    testCauta();
    testFiltreazaDupaTitlu();
    testFiltreazaDupaAn();
    testSorteazaDupaTitlu();
    testSorteazaDupaAutor();
    testSorteazaDupaAnSiGen();
    testSetteri();
    testCopyConstructor();
    testValidare();
    testValidationException();
    testSorteazaMyVector();
    testMyVector();
    testMyVectorSelfAssign();

    cout << "Toate testele au trecut!\n";
}