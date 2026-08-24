#include "repo.h"
#include "domain.h"
#include "validator.h"
#include <stdio.h>
#include <string.h>

int adauga_masina_service(ListaMasini* masini, const char* numar, const char* model, const char* categorie, int status)
{
	/*
	 * Descriere: Evalueaza datele si salveaza o masina noua in aplicatie.
	 * Parametri: masini (ListaMasini*) - pointer catre lista, numar, model, categorie (const char*), status (int) - datele noii masini.
	 * Preconditii: masini reprezinta o lista valida.
	 * Postconditii: Returneaza 0 pentru inregistrare cu succes, 1 pentru date invalide, 2 pentru masina deja existenta.
	 */

	Masina m = creeaza_masina(numar, model, categorie, status);

	if (valideaza_masina(m) == 0)
		return 1;

	if (cauta_masina(masini, numar) != -1)
		return 2;

	adauga_masina(masini, m);

	return 0;
}

int actualizare_masina_service(ListaMasini* masini, const char* numar, const char* model, const char* categorie, int status)
{
	/*
	 * Descriere: Evalueaza datele si actualizeaza o masina existenta in aplicatie.
	 * Parametri: masini (ListaMasini*) - pointer catre lista, numar, model, categorie (const char*), status (int) - datele noi.
	 * Preconditii: masini reprezinta o lista valida.
	 * Postconditii: Returneaza 0 pentru succes, 1 pentru date invalide, 2 daca masina nu exista in sistem.
	 */

	Masina m = creeaza_masina(numar, model, categorie, status);

	if (valideaza_masina(m) == 0)
		return 1;

	if (actualizare_masina(masini, m) == 0)
		return 2;

	return 0;
}

int get_dimensiune_service(ListaMasini* masini)
{
	/*
	 * Descriere: Furnizeaza numarul de masini din aplicatie.
	 * Parametri: masini (ListaMasini*) - pointer catre lista.
	 * Preconditii: masini reprezinta o lista valida.
	 * Postconditii: Returneaza numarul curent de elemente inregistrate.
	 */

	return get_dimensiune(masini);
}

Masina* get_all_masini_service(ListaMasini* masini)
{
	/*
	 * Descriere: Furnizeaza masinile din aplicatie.
	 * Parametri: masini (ListaMasini*) - pointer catre lista.
	 * Preconditii: masini reprezinta o lista valida.
	 * Postconditii: Returneaza un pointer catre entitatile salvate.
	 */

	return get_all_masini(masini);
}

int inchiriere_returnare_service(ListaMasini* masini, const char* numar, int status)
{
	/*
	 * Descriere: Gestioneaza procesul de inchiriere sau returnare a unei masini.
	 * Parametri: masini (ListaMasini*) - pointer catre lista, numar (const char*) - numarul masinii, status (int) - 0 pentru returnare, 1 pentru inchiriere.
	 * Preconditii: masini reprezinta o lista valida.
	 * Postconditii: Returneaza 0 pentru succes, 1 pentru date invalide, 2 daca masina nu exista sau nu poate fi inchiriata/returnata.
	 */
	int poz = cauta_masina(masini, numar);
	if (poz == -1)
		return 2;
	Masina m = masini->masini[poz];
	if (status == 1 && m.status == 1)
		return 2; // masina deja inchiriata
	if (status == 0 && m.status == 0)
		return 2; // masina deja disponibila
	m.status = status;
	actualizare_masina(masini, m);
	return 0;
}

ListaMasini filtrare_dupa_categorie(ListaMasini* masini, const char* categorie)
{
	/*
	 * Descriere: Filtreaza masinile disponibile in functie de o categorie specifica.
	 * Parametri: masini (ListaMasini*) - pointer catre lista, categorie (const char*) - criteriul de filtrare.
	 * Preconditii: masini reprezinta o lista valida.
	 * Postconditii: Returneaza o lista noua formata exclusiv din masinile care corespund categoriei.
	 */

	ListaMasini lis;
	initializare_lista(&lis);
	for (int i = 0; i < masini->nr_masini; i++)
	{
		if (strcmp(masini->masini[i].categorie, categorie) == 0)
		{
			adauga_masina(&lis, masini->masini[i]);
		}
	}

	return lis;
}

ListaMasini filtrare_dupa_model(ListaMasini* masini, const char* model)
{
	/*
	 * Descriere: Filtreaza masinile disponibile in functie de un model specific.
	 * Parametri: masini (ListaMasini*) - pointer catre lista, model (const char*) - criteriul de filtrare.
	 * Preconditii: masini reprezinta o lista valida.
	 * Postconditii: Returneaza o lista noua formata exclusiv din masinile care corespund modelului.
	 */

	ListaMasini lis;
	initializare_lista(&lis);
	for (int i = 0; i < masini->nr_masini; i++)
	{
		if (strcmp(masini->masini[i].model, model) == 0)
		{
			adauga_masina(&lis, masini->masini[i]);
		}
	}

	return lis;
}

ListaMasini dupa_model_crescator(ListaMasini* masini)
{
	/*
	 * Descriere: Ordoneaza masinile alfabetic crescator in functie de model.
	 * Parametri: masini (ListaMasini*) - pointer catre lista.
	 * Preconditii: masini reprezinta o lista valida.
	 * Postconditii: Returneaza o lista noua cu elementele ordonate.
	 */

	ListaMasini lis;
	initializare_lista(&lis);

	for (int i = 0; i < masini->nr_masini; i++)
	{
		adauga_masina(&lis, masini->masini[i]);
	}

	int ok = 0;

	while (!ok)
	{ 
		ok = 1;
		for (int i = 0; i < lis.nr_masini - 1; i++)
			if (strcmp(lis.masini[i].model, lis.masini[i+1].model) > 0)
			{
				ok = 0;

				Masina aux = lis.masini[i];
				lis.masini[i] = lis.masini[i+1];
				lis.masini[i+1] = aux;
			}
	}
	return lis;
}

ListaMasini dupa_model_descrescator(ListaMasini* masini)
{
	/*
	 * Descriere: Ordoneaza masinile alfabetic descrescator in functie de model.
	 * Parametri: masini (ListaMasini*) - pointer catre lista.
	 * Preconditii: masini reprezinta o lista valida.
	 * Postconditii: Returneaza o lista noua cu elementele ordonate.
	 */

	ListaMasini lis;
	initializare_lista(&lis);

	for (int i = 0; i < masini->nr_masini; i++)
	{
		adauga_masina(&lis, masini->masini[i]);
	}

	int ok = 0;

	while (!ok)
	{
		ok = 1;
		for (int i = 0; i < lis.nr_masini - 1; i++)
			if (strcmp(lis.masini[i].model, lis.masini[i + 1].model) < 0)
			{
				ok = 0;

				Masina aux = lis.masini[i];
				lis.masini[i] = lis.masini[i + 1];
				lis.masini[i + 1] = aux;
			}
	}
	return lis;
}

ListaMasini dupa_categorie_crescator(ListaMasini* masini)
{
	/*
	 * Descriere: Ordoneaza masinile alfabetic crescator in functie de categorie.
	 * Parametri: masini (ListaMasini*) - pointer catre lista.
	 * Preconditii: masini reprezinta o lista valida.
	 * Postconditii: Returneaza o lista noua cu elementele ordonate.
	 */

	ListaMasini lis;
	initializare_lista(&lis);

	for (int i = 0; i < masini->nr_masini; i++)
	{
		adauga_masina(&lis, masini->masini[i]);
	}

	int ok = 0;

	while (!ok)
	{
		ok = 1;
		for (int i = 0; i < lis.nr_masini - 1; i++)
			if (strcmp(lis.masini[i].categorie, lis.masini[i + 1].categorie) > 0)
			{
				ok = 0;

				Masina aux = lis.masini[i];
				lis.masini[i] = lis.masini[i + 1];
				lis.masini[i + 1] = aux;
			}
	}
	return lis;
}

ListaMasini dupa_categorie_descrescator(ListaMasini* masini)
{
	/*
	 * Descriere: Ordoneaza masinile alfabetic descrescator in functie de categorie.
	 * Parametri: masini (ListaMasini*) - pointer catre lista.
	 * Preconditii: masini reprezinta o lista valida.
	 * Postconditii: Returneaza o lista noua cu elementele ordonate.
	 */

	ListaMasini lis;
	initializare_lista(&lis);

	for (int i = 0; i < masini->nr_masini; i++)
	{
		adauga_masina(&lis, masini->masini[i]);
	}

	int ok = 0;

	while (!ok)
	{
		ok = 1;
		for (int i = 0; i < lis.nr_masini - 1; i++)
			if (strcmp(lis.masini[i].categorie, lis.masini[i + 1].categorie) < 0)
			{
				ok = 0;

				Masina aux = lis.masini[i];
				lis.masini[i] = lis.masini[i + 1];
				lis.masini[i + 1] = aux;
			}
	}
	return lis;
}