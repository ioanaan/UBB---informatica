#include "teste.h"
#include <assert.h>
#include "service_oferta.h"
#include "oferta.h"
#include <string.h>

void test_adauga()
{
	Lista oferte = creeaza_lista_oferta();
	assert(lungime_lista(oferte) == 0);

	// Adaugare cu succes
	assert(adauga_oferta(&oferte, 1, "munte", "Brasov", "20.04.2026", 1500) == 1);
	assert(lungime_lista(oferte) == 1);
	assert(strcmp(get_tip(oferte.elemente[0]), "munte") == 0);
	assert(strcmp(get_destinatie(oferte.elemente[0]), "Brasov") == 0);
	assert(strcmp(get_data_plecare(oferte.elemente[0]), "20.04.2026") == 0);
	assert(get_pret(oferte.elemente[0]) == 1500);

	// Testam ID duplicat (returneaza 2)
	assert(adauga_oferta(&oferte, 1, "mare", "Mamaia", "20.04.2026", 2000) == 2);

	// Testam date invalide (returneaza 0)
	assert(adauga_oferta(&oferte, 2, "vacanta", "Brasov", "20.04.2026", 1500) == 0);
	assert(adauga_oferta(&oferte, 3, "munte", "Paris", "10.10.2026", -500) == 0);

	distruge_lista(&oferte);
}

void test_sterge()
{
	Lista oferte = creeaza_lista_oferta();
	assert(lungime_lista(oferte) == 0);
	adauga_oferta(&oferte, 1, "munte", "Brasov", "20.04.2026", 1500);

	int sterse = sterge_oferta(&oferte, 1);
	assert(sterse == 1);
	sterse = sterge_oferta(&oferte, 2); // ID inexistent
	assert(sterse == 0);

	distruge_lista(&oferte);
}

void test_actualizeaza()
{
	Lista oferte = creeaza_lista_oferta();
	assert(lungime_lista(oferte) == 0);
	adauga_oferta(&oferte, 1, "munte", "Brasov", "20.04.2026", 1500);
	assert(lungime_lista(oferte) == 1);

	// Actualizare cu succes
	assert(actualizeaza_oferta(&oferte, 1, "munte", "Brasov", "10.02.2027", 2000) == 1);
	assert(strcmp(get_data_plecare(oferte.elemente[0]), "10.02.2027") == 0);
	assert(get_pret(oferte.elemente[0]) == 2000);

	// Actualizare esuata (ID inexistent)
	assert(actualizeaza_oferta(&oferte, 2, "mare", "Grecia", "10.08.2026", 8000) == 0);
	// Actualizare esuata (Pret invalid)
	assert(actualizeaza_oferta(&oferte, 1, "munte", "Brasov", "20.04.2026", -100) == 0);

	distruge_lista(&oferte);
}

/*void test_sorteaza()
{
	Lista oferte = creeaza_lista_oferta();
	adauga_oferta(&oferte, 1, "munte", "Brasov", "20.04.2026", 1500);
	adauga_oferta(&oferte, 2, "mare", "Grecia", "06.08.2026", 3000);
	adauga_oferta(&oferte, 3, "munte", "Sinaia", "02.01.2027", 4800);
	assert(lungime_lista(oferte) == 3);

	Lista lista_sortata = sorteaza_oferte(&oferte, "pret", "crescator");
	assert(get_pret(lista_sortata.elemente[0]) == 1500);
	assert(get_pret(lista_sortata.elemente[1]) == 3000);
	assert(get_pret(lista_sortata.elemente[2]) == 4800);
	distruge_lista(&lista_sortata);

	lista_sortata = sorteaza_oferte(&oferte, "pret", "descrescator");
	assert(get_pret(lista_sortata.elemente[0]) == 4800);
	assert(get_pret(lista_sortata.elemente[1]) == 3000);
	assert(get_pret(lista_sortata.elemente[2]) == 1500);
	distruge_lista(&lista_sortata);

	lista_sortata = sorteaza_oferte(&oferte, "destinatie", "crescator");
	assert(strcmp(get_destinatie(lista_sortata.elemente[0]), "Brasov") == 0);
	assert(strcmp(get_destinatie(lista_sortata.elemente[1]), "Grecia") == 0);
	assert(strcmp(get_destinatie(lista_sortata.elemente[2]), "Sinaia") == 0);
	distruge_lista(&lista_sortata);

	lista_sortata = sorteaza_oferte(&oferte, "destinatie", "descrescator");
	assert(strcmp(get_destinatie(lista_sortata.elemente[0]), "Sinaia") == 0);
	assert(strcmp(get_destinatie(lista_sortata.elemente[1]), "Grecia") == 0);
	assert(strcmp(get_destinatie(lista_sortata.elemente[2]), "Brasov") == 0);
	distruge_lista(&lista_sortata);

	// Cazuri de invalidare
	lista_sortata = sorteaza_oferte(&oferte, "data", "crescator");
	assert(lungime_lista(lista_sortata) == 0);
	distruge_lista(&lista_sortata);

	lista_sortata = sorteaza_oferte(&oferte, "pret", "aleatoriu");
	assert(lungime_lista(lista_sortata) == 0);
	distruge_lista(&lista_sortata);

	lista_sortata = sorteaza_oferte(&oferte, "nush", "nush");
	assert(lungime_lista(lista_sortata) == 0);
	distruge_lista(&lista_sortata);

	distruge_lista(&oferte);
}*/

void test_sortari_specifice()
{
	Lista oferte = creeaza_lista_oferta();
	adauga_oferta(&oferte, 1, "munte", "Brasov", "20.04.2026", 1500);
	adauga_oferta(&oferte, 2, "mare", "Grecia", "06.08.2026", 3000);
	adauga_oferta(&oferte, 3, "munte", "Sinaia", "02.01.2027", 4800);
	assert(lungime_lista(oferte) == 3);

	Lista sortata_pret_cresc = sorteaza_dupa_pret_crescator(&oferte);
	assert(get_pret(sortata_pret_cresc.elemente[0]) == 1500);
	assert(get_pret(sortata_pret_cresc.elemente[1]) == 3000);
	assert(get_pret(sortata_pret_cresc.elemente[2]) == 4800);
	distruge_lista(&sortata_pret_cresc);

	Lista sortata_pret_desc = sorteaza_dupa_pret_descrescator(&oferte);
	assert(get_pret(sortata_pret_desc.elemente[0]) == 4800);
	assert(get_pret(sortata_pret_desc.elemente[1]) == 3000);
	assert(get_pret(sortata_pret_desc.elemente[2]) == 1500);
	distruge_lista(&sortata_pret_desc);

	Lista sortata_dest_cresc = sorteaza_dupa_dest_crescator(&oferte);
	assert(strcmp(get_destinatie(sortata_dest_cresc.elemente[0]), "Brasov") == 0);
	assert(strcmp(get_destinatie(sortata_dest_cresc.elemente[1]), "Grecia") == 0);
	assert(strcmp(get_destinatie(sortata_dest_cresc.elemente[2]), "Sinaia") == 0);
	distruge_lista(&sortata_dest_cresc);

	Lista sortata_dest_desc = sorteaza_dupa_dest_descrescator(&oferte);
	assert(strcmp(get_destinatie(sortata_dest_desc.elemente[0]), "Sinaia") == 0);
	assert(strcmp(get_destinatie(sortata_dest_desc.elemente[1]), "Grecia") == 0);
	assert(strcmp(get_destinatie(sortata_dest_desc.elemente[2]), "Brasov") == 0);
	distruge_lista(&sortata_dest_desc);

	distruge_lista(&oferte);
}

void test_filtreaza()
{
	Lista oferte = creeaza_lista_oferta();
	adauga_oferta(&oferte, 1, "munte", "Brasov", "20.04.2026", 1500);
	adauga_oferta(&oferte, 2, "mare", "Grecia", "06.08.2026", 3000);
	adauga_oferta(&oferte, 3, "munte", "Brasov", "02.01.2027", 4800);
	assert(lungime_lista(oferte) == 3);

	Lista lista_filtrata = filtreaza_oferta(&oferte, "Brasov");
	assert(strcmp(get_data_plecare(lista_filtrata.elemente[0]), "20.04.2026") == 0);
	assert(get_pret(lista_filtrata.elemente[0]) == 1500);
	assert(strcmp(get_data_plecare(lista_filtrata.elemente[1]), "02.01.2027") == 0);
	assert(get_pret(lista_filtrata.elemente[1]) == 4800);
	assert(lungime_lista(lista_filtrata) == 2);

	distruge_lista(&lista_filtrata);
	distruge_lista(&oferte);
}

void ruleaza_teste_service()
{
	test_adauga();
	test_sterge();
	test_actualizeaza();
	//test_sorteaza();
	test_sortari_specifice();
	test_filtreaza();
}