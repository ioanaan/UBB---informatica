#include "repo.h"
#include "domain.h"
#include "sort.h"
#include "validator.h"
#include "service.h"
#include <stdio.h>
#include <string.h>

int cmpModelCrescator(Masina* m1, Masina* m2) 
{
	return strcmp(m1->model, m2->model);
}

int cmpModelDescrescator(Masina* m1, Masina* m2) 
{
	return strcmp(m2->model, m1->model);
}

int cmpCategorieCrescator(Masina* m1, Masina* m2) 
{
	return strcmp(m1->categorie, m2->categorie);
}

int cmpCategorieDescrescator(Masina* m1, Masina* m2) 
{
	return strcmp(m2->categorie, m1->categorie);
}

int adauga_masina_service(ListaMasini* masini, const char* numar, const char* model, const char* categorie, int status)
{
	Masina m = creeaza_masina(numar, model, categorie, status);

	if (valideaza_masina(m) == 0)
	{
		distruge_masina(&m);
		return 1;
	}
	if (cauta_masina(masini, numar) != -1)
	{
		distruge_masina(&m);
		return 2;
	}
	adauga_masina(masini, m);
	return 0;
}

int actualizare_masina_service(ListaMasini* masini, const char* numar, const char* model, const char* categorie, int status)
{
	Masina m = creeaza_masina(numar, model, categorie, status);

	if (valideaza_masina(m) == 0)
	{
		distruge_masina(&m);
		return 1;
	}
	if (actualizare_masina(masini, m) == 0)
	{
		distruge_masina(&m);
		return 2;
	}
	return 0;
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

	if (status == 1 && masini->masini[poz].status == 1)
		return 2; 
	if (status == 0 && masini->masini[poz].status == 0)
		return 2; 

	masini->masini[poz].status = status;

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
			adauga_masina(&lis, copiaza_masina(&masini->masini[i]));
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
			adauga_masina(&lis, copiaza_masina(&masini->masini[i]));
		}
	}

	return lis;
}

ListaMasini dupa_model_crescator(ListaMasini* masini)
{
	ListaMasini lis;
	initializare_lista(&lis);
	for (int i = 0; i < masini->nr_masini; i++)
	{
		adauga_masina(&lis, copiaza_masina(&masini->masini[i]));
	}

	sortare_generica(&lis, cmpModelCrescator);
	return lis;
}

ListaMasini dupa_model_descrescator(ListaMasini* masini)
{
	ListaMasini lis;
	initializare_lista(&lis);
	for (int i = 0; i < masini->nr_masini; i++)
	{
		adauga_masina(&lis, copiaza_masina(&masini->masini[i]));
	}

	sortare_generica(&lis, cmpModelDescrescator);
	return lis;
}

ListaMasini dupa_categorie_crescator(ListaMasini* masini)
{
	ListaMasini lis;
	initializare_lista(&lis);
	for (int i = 0; i < masini->nr_masini; i++)
	{
		adauga_masina(&lis, copiaza_masina(&masini->masini[i]));
	}

	sortare_generica(&lis, cmpCategorieCrescator);
	return lis;
}

ListaMasini dupa_categorie_descrescator(ListaMasini * masini)
{
	ListaMasini lis;
	initializare_lista(&lis);
	for (int i = 0; i < masini->nr_masini; i++)
	{
		adauga_masina(&lis, copiaza_masina(&masini->masini[i]));
	}

	sortare_generica(&lis, cmpCategorieDescrescator);
	return lis;
}

int get_dimensiune_service(ListaMasini* masini)
{
	return get_dimensiune(masini);
}