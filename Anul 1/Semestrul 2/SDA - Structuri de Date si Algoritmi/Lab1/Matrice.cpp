#include "Matrice.h"

#include <exception>

using namespace std;


Matrice::Matrice(int m, int n) // Complexitate: theta(n)
{
	/* de adaugat */
	if (m <= 0 || n <= 0) 
	{
		throw std::exception();
	}

	nrL = m;
	nrC = n;
	capacitate = 10;
	nrElemente = 0;

	valoare = new TElem[capacitate];
	linie = new int[capacitate];
	coloana = new int[nrC + 1];

	for (int i = 0; i <= nrC; i++)
		coloana[i] = 0;

}

int Matrice::nrLinii() const // Complexitate: theta(1)
{
	/* de adaugat */
	return nrL;
}


int Matrice::nrColoane() const // Complexitate: theta(1)
{
	/* de adaugat */
	return nrC;
}


/*
* Caz favorabil: O(1) - cand col j nu are elem
* Caz defavorabil: O(n)
*/
TElem Matrice::element(int i, int j) const
{
	/* de adaugat */
	if (i < 0 || i >= nrL || j < 0 || j >= nrC) 
	{
		throw std::exception();
	}

	for(int k = coloana[j]; k < coloana[j+1]; k++)
	{
		if (linie[k] == i)
		{
			return valoare[k];
		}
	}

	return NULL_TELEMENT;
}
/*
* -> daca e exista:
*    Complexitate: theta(n)
* 
* -> daca elem vechi trebuie șters:
*	 Complexitate: theta(n)
* 
* -> daca e trebuie adaugat:
*	 Complexitate: theta(n)
*/
TElem Matrice::modifica(int i, int j, TElem e) 
{
	/* de adaugat */
	if (i < 0 || i >= nrL || j < 0 || j >= nrC)
	{
		throw std::exception();
	}

	for (int k = coloana[j]; k < coloana[j + 1]; k++)
	{
		if (linie[k] == i)
		{
			TElem vechi = valoare[k];

			//daca e exista
			if (e != NULL_TELEMENT)
			{
				valoare[k] = e;
			}
			else //daca elem vechi trebuie șters
			{
				for (int l = k; l < nrElemente - 1; l++)
				{
					linie[l] = linie[l + 1];
					valoare[l] = valoare[l + 1];
				}

				nrElemente--;
				for (int d = j + 1; d <= nrC; d++)
				{
					coloana[d]--;
				}

			}
			return vechi;
		}
	}

	if (e == NULL_TELEMENT) 
	{
		return NULL_TELEMENT;
	}

	//daca e trebuie adaugat
	int pos = coloana[j];

	while (pos < coloana[j + 1] && linie[pos] < i)
	{
		pos++;
	}

	if (nrElemente == capacitate)
	{
		redimensionare(); 
	}

	for (int k = nrElemente - 1; k >= pos; k--)
	{
		linie[k + 1] = linie[k];
		valoare[k + 1] = valoare[k];
	}

	valoare[pos] = e;
	linie[pos] = i;
	nrElemente++;

	for (int c = j + 1; c <= nrC; c++)
	{
		coloana[c]++;
	}

	return NULL_TELEMENT;
}

Matrice::~Matrice() 
{
	//destructor
	delete[] valoare;
	delete[] linie;
	delete[] coloana;
}

void Matrice::redimensionare() // Complexitate: theta(n)
{
	capacitate *= 2;

	TElem* nouValoare = new TElem[capacitate];
	int* nouLinie = new int[capacitate];

	for (int i = 0; i < nrElemente; i++)
	{
		nouValoare[i] = valoare[i];
		nouLinie[i] = linie[i];
	}

	delete[] valoare;
	delete[] linie;

	valoare = nouValoare;
	linie = nouLinie;
}

void Matrice::redimensioneaza(int numarNouLinii, int numarNouColoane)
{
	int numElem = 0;

	if (numarNouColoane < nrC && numarNouLinii < nrL)
	{
		for (int i = coloana[0]; i < coloana[numarNouColoane]; i++)
		{
			numElem++;
		}

		TElem* valoareN = new TElem[capacitate];
		int* linieN = new int[capacitate];

		for (int i = 0; i < numElem; i++)
		{
			valoareN[i] = valoare[i];
			linieN[i] = linie[i];
		}

		delete[] valoare;
		delete[] linie;

		valoare = valoareN;
		linie = linieN;
	}
	else if (numarNouColoane < nrC && numarNouLinii > nrL)
	{
		redimensionare();
		for (int i = coloana[0]; i < coloana[numarNouColoane]; i++)
		{
			numElem++;
		}

		TElem* valoareN = new TElem[capacitate];
		int* linieN = new int[capacitate];

		for (int i = 0; i < numElem; i++)
		{
			valoareN[i] = valoare[i];
			linieN[i] = linie[i];
		}

		for (int i = nrL; i < numarNouLinii; i++)
		{
			valoareN[i] = NULL_TELEMENT;
			linieN[i] = NULL_TELEMENT;
		}

		delete[] valoare;
		delete[] linie;

		valoare = valoareN;
		linie = linieN;
	}
	else if (numarNouColoane > nrC && numarNouLinii < nrL)
	{
		numElem = nrElemente;
		redimensionare();
		for (int k = coloana[nrC]; k < coloana[numarNouColoane]; k++)
		{
			numElem++;
			coloana[k] = NULL_TELEMENT;
		}

		TElem* valoareN = new TElem[capacitate];
		int* linieN = new int[capacitate];

		for (int k = nrElemente; k < numElem; k++)
		{
			valoareN[k] = NULL_TELEMENT;
			linieN[k] = NULL_TELEMENT;
		}

		delete[] valoare;
		delete[] linie;

		valoare = valoareN;
		linie = linieN;

	}
	else if (numarNouColoane > nrC && numarNouLinii > nrL)
	{
		numElem = nrElemente;
		redimensionare();
		for (int k = coloana[nrC]; k < coloana[numarNouColoane]; k++)
		{
			numElem++;
			coloana[k] = NULL_TELEMENT;
		}

		TElem* valoareN = new TElem[capacitate];
		int* linieN = new int[capacitate];

		for (int k = nrElemente; k < numElem; k++)
		{
			valoareN[k] = NULL_TELEMENT;
			linieN[k] = NULL_TELEMENT;
		}

		for (int i = nrL; i < numarNouLinii; i++)
		{
			valoareN[i] = NULL_TELEMENT;
			linieN[i] = NULL_TELEMENT;
		}

		delete[] valoare;
		delete[] linie;

		valoare = valoareN;
		linie = linieN;
	}
}