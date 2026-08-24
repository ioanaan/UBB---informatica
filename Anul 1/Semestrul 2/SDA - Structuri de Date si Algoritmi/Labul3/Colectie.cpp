#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include <iostream>

using namespace std;


Colectie::Colectie()
{
	/* de adaugat */
	//complexitate : theta(1)
	prim = nullptr;
	lungime = 0;
}


void Colectie::adauga(TElem elem)
{
	/* de adaugat */
	//complexitate : O(n)

	// cauta daca elementul exista in lista
	Nod* curent = prim;
	while (curent != nullptr)
	{
		if (curent->element == elem)
		{
			// daca exista element -> creste frecventa
			curent->frecventa++;
			lungime++;
			return;
		}
		curent = curent->urmator;
	}
	// elementul nu exista -> creaza un nod nou si il pune la inceputul listei
	Nod* nou = new Nod;
	nou->element = elem;
	nou->frecventa = 1;
	nou->urmator = prim;
	prim = nou;
	lungime++;
}


bool Colectie::sterge(TElem elem)
{
	/* de adaugat */
	////complexitate : O(n)

	Nod* curent = prim;
	Nod* anterior = nullptr;

	while (curent != nullptr)
	{
		if (curent->element == elem)
		{
			curent->frecventa--;
			lungime--;
			if (curent->frecventa == 0)
			{
				// elimin nodul din lista
				if (anterior == nullptr)
				{
					prim = curent->urmator;
				}
				else 
				{
					anterior->urmator = curent->urmator;
				}
				delete curent;
			}
			return true;
		}
		anterior = curent;
		curent = curent->urmator;
	}

	// elementul nu exista
	return false;
}


bool Colectie::cauta(TElem elem) const
{
	/* de adaugat */
	//complexitate : O(n)

	Nod* curent = prim;
	while (curent != nullptr)
	{
		if (curent->element == elem)
		{
			return true;
		}
		curent = curent->urmator;
	}

	//element nu exista
	return false;
}

int Colectie::nrAparitii(TElem elem) const
{
	/* de adaugat */
	//complexitate : O(n)

	Nod* curent = prim;
	while (curent != nullptr)
	{
		if (curent->element == elem)
		{
			return curent->frecventa;
		}
		curent = curent->urmator;
	}

	//element nu exista
	return 0;
}


int Colectie::dim() const
{
	/* de adaugat */
	////complexitate : theta(1)

	return lungime;
}


bool Colectie::vida() const
{
	/* de adaugat */
	//complexitate : theta(1)

	return prim == nullptr;
}

IteratorColectie Colectie::iterator() const
{
	return  IteratorColectie(*this);
}


Colectie::~Colectie()
{
	/* de adaugat */
	//complexitate : theta(n)

	// Stergem toate nodurile din lista
	Nod* curent = prim;
	while (curent != nullptr)
	{
		Nod* urmator = curent->urmator;
		delete curent;
		curent = urmator;
	}
	prim = nullptr;
}


