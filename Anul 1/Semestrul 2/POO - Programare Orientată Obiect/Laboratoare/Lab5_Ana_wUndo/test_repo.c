#include "repo_oferta.h"
#include "oferta.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void test_destroy(void* elem)
{
	Oferta* of = (Oferta*)elem;
	distruge_oferta(of);
	free(of);
}

void* test_copy(void* elem) 
{
	Oferta* of = (Oferta*)elem;
	Oferta* copie = (Oferta*)malloc(sizeof(Oferta));
	*copie = initializeaza(get_id(*of), get_tip(*of), get_destinatie(*of), get_data_plecare(*of), get_pret(*of));
	return copie;
}

void test_repo_adauga_si_lungime()
{
	Lista l = creeaza_lista(2, test_destroy, test_copy);
	assert(lungime(l) == 0);

	Oferta* of = (Oferta*)malloc(sizeof(Oferta));
	*of = initializeaza(1, "munte", "Sinaia", "12.12.2026", 1000);
	adauga(&l, of);

	assert(lungime(l) == 1);
	Oferta* of_scos = (Oferta*)get_element(&l, 0);
	assert(get_id(*of_scos) == 1);

	distruge_lista(&l);
}

void test_repo_sterge_pozitie() 
{
	Lista l = creeaza_lista(2, test_destroy, test_copy);

	Oferta* of1 = (Oferta*)malloc(sizeof(Oferta));
	*of1 = initializeaza(1, "munte", "Sinaia", "12.12.2026", 1000);
	Oferta* of2 = (Oferta*)malloc(sizeof(Oferta));
	*of2 = initializeaza(2, "mare", "Mamaia", "10.08.2026", 2000);

	adauga(&l, of1);
	adauga(&l, of2);
	assert(lungime(l) == 2);

	sterge_pozitie(&l, 0); // Stergem primul element
	assert(lungime(l) == 1);

	Oferta* ramas = (Oferta*)get_element(&l, 0);
	assert(get_id(*ramas) == 2); // A ramas doar a doua oferta

	distruge_lista(&l);
}

void test_repo_copiaza()
{
	Lista l = creeaza_lista(2, test_destroy, test_copy);
	Oferta* of = (Oferta*)malloc(sizeof(Oferta));
	*of = initializeaza(1, "munte", "Sinaia", "12.12.2026", 1000);
	adauga(&l, of);

	Lista copie = copiaza_lista(&l);
	assert(lungime(copie) == 1);

	Oferta* of_copie = (Oferta*)get_element(&copie, 0);
	assert(get_id(*of_copie) == 1);

	distruge_lista(&l);
	distruge_lista(&copie);
}

void test_repo_creare_esuata()
{
	Lista l = creeaza_lista(-1, test_destroy, test_copy);
	assert(l.capacitate == 0);
	assert(l.elemente == NULL);
	distruge_lista(&l);
}

void ruleaza_teste_repo() 
{
	test_repo_adauga_si_lungime();
	test_repo_sterge_pozitie();
	test_repo_copiaza();
	test_repo_creare_esuata();
}