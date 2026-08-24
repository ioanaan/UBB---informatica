#include "repo.h"
#include "domain.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void initializare_lista(ListaMasini* lista_m)
{
	/*
	 * Descriere: Initializeaza o lista de masini setand dimensiunea la 0.
	 * Parametri: lista_m (ListaMasini*) - pointer catre lista ce trebuie initializata.
	 * Preconditii: lista_m este un pointer alocat valid.
	 * Postconditii: lista_m->nr_masini devine 0.
	 */

	lista_m->capacitate = 2;
	lista_m->nr_masini = 0;
	lista_m->masini = (Masina*)malloc(lista_m->capacitate * sizeof(Masina));
}

void adauga_masina(ListaMasini* lista_m, Masina m)
{
	if (lista_m->nr_masini == lista_m->capacitate)
	{
		lista_m->capacitate = lista_m->capacitate * 2;
		Masina* aux = (Masina*)realloc(lista_m->masini, lista_m->capacitate * sizeof(Masina));

		if (aux != NULL)
		{
			lista_m->masini = aux;
		}
	}

	lista_m->masini[lista_m->nr_masini] = m;
	lista_m->nr_masini++;
}

int cauta_masina(ListaMasini* masini, const char* nr_cautat)
{
	/*
	 * Descriere: verifica existenta unei masini pe baza numarului de inmatriculare.
	 * Parametri: masini (ListaMasini*) - pointer catre lista, nr_cautat (const char*) - numarul cautat.
	 * Preconditii: masini reprezinta o lista valida.
	 * Postconditii: returneaza pozitia masinii in lista daca aceasta exista, sau -1 in caz contrar.
	 */

	for (int i = 0; i < masini->nr_masini; i++)
		if (strcmp(masini->masini[i].numar, nr_cautat) == 0)
			return i;
	return -1;
}

int actualizare_masina(ListaMasini* masini, Masina m)
{
	/*
	 * Descriere: Modifica datele unei masini existente in lista.
	 * Parametri: masini (ListaMasini*) - pointer catre lista, m (Masina) - masina cu noile date.
	 * Preconditii: masini reprezinta o lista valida.
	 * Postconditii: Datele masinii sunt actualizate si se returneaza 1, sau se returneaza 0 daca masina nu a fost gasita.
	 */	

	int poz = cauta_masina(masini, m.numar);
	if (poz == -1)
		return 0;

	distruge_masina(&masini->masini[poz]);

	masini->masini[poz] = m;
	return 1;
}

int get_dimensiune(ListaMasini* masini)
{
	/*
	 * Descriere: Furnizeaza numarul de elemente stocate in lista.
	 * Parametri: masini (ListaMasini*) - pointer catre lista.
	 * Preconditii: masini reprezinta o lista valida.
	 * Postconditii: Returneaza un numar intreg reprezentand dimensiunea listei.
	 */

	return masini->nr_masini;
}

Masina* get_all_masini(ListaMasini* masini)
{
	/*
	 * Descriere: Furnizeaza acces la elementele stocate in lista.
	 * Parametri: masini (ListaMasini*) - pointer catre lista.
	 * Preconditii: masini reprezinta o lista valida.
	 * Postconditii: Returneaza un pointer catre elementele din lista.
	 */

	return masini->masini;
}

void distruge_lista(ListaMasini* lista_m)
{
	if (lista_m->masini != NULL)
	{
		for (int i = 0; i < lista_m->nr_masini; i++)
		{
			distruge_masina(&lista_m->masini[i]);
		}

		free(lista_m->masini);
		lista_m->masini = NULL;
	}
	lista_m->nr_masini = 0;
	lista_m->capacitate = 0;
}