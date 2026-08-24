#include "teste.h"
#include <assert.h>
#include "service_oferta.h"
#include "oferta.h"
#include <string.h>

void test_adauga()
{
	Lista oferte = creeaza_lista_oferta();
	Lista undo_list = creeaza_lista_undo();
	assert(lungime_lista(oferte) == 0);

	assert(adauga_oferta(&oferte, &undo_list, 1, "munte", "Brasov", "20.04.2026", 1500) == 1);
	assert(lungime_lista(oferte) == 1);

	Oferta* of0 = (Oferta*)get_element(&oferte, 0);
	assert(strcmp(get_tip(*of0), "munte") == 0);
	assert(strcmp(get_destinatie(*of0), "Brasov") == 0);
	assert(strcmp(get_data_plecare(*of0), "20.04.2026") == 0);
	assert(get_pret(*of0) == 1500);

	// Acopera return 2 (ID Duplicat)
	assert(adauga_oferta(&oferte, &undo_list, 1, "mare", "Mamaia", "20.04.2026", 2000) == 2);
	// Acopera return 0 (Date Invalide)
	assert(adauga_oferta(&oferte, &undo_list, 2, "vacanta", "Brasov", "20.04.2026", 1500) == 0);

	distruge_lista(&oferte);
	distruge_lista(&undo_list);
}

void test_sterge()
{
	Lista oferte = creeaza_lista_oferta();
	Lista undo_list = creeaza_lista_undo();
	assert(lungime_lista(oferte) == 0);

	// Adaugam DOUA oferte ca sa fortam for-ul sa mearga mai departe de prima pozitie
	adauga_oferta(&oferte, &undo_list, 1, "munte", "Brasov", "20.04.2026", 1500);
	adauga_oferta(&oferte, &undo_list, 2, "mare", "Constanta", "10.05.2026", 2000);

	// Stergem a doua oferta. For-ul va atinge acolada rosie dupa ce verifica prima oferta!
	int sterse = sterge_oferta(&oferte, &undo_list, 2);
	assert(sterse == 1);

	// Stergere id inexistent
	sterse = sterge_oferta(&oferte, &undo_list, 99);
	assert(sterse == 0);

	distruge_lista(&oferte);
	distruge_lista(&undo_list);
}

void test_actualizeaza()
{
	Lista oferte = creeaza_lista_oferta();
	Lista undo_list = creeaza_lista_undo();
	adauga_oferta(&oferte, &undo_list, 1, "munte", "Brasov", "20.04.2026", 1500);

	// Actualizare cu succes
	assert(actualizeaza_oferta(&oferte, &undo_list, 1, "munte", "Brasov", "10.02.2027", 2000) == 1);

	// Acopera return 0 (ID Inexistent)
	assert(actualizeaza_oferta(&oferte, &undo_list, 99, "mare", "Grecia", "10.08.2026", 8000) == 0);
	// Acopera return 0 (Date invalide)
	assert(actualizeaza_oferta(&oferte, &undo_list, 1, "munte", "Brasov", "20.04.2026", -100) == 0);

	distruge_lista(&oferte);
	distruge_lista(&undo_list);
}

void test_sortari_specifice()
{
	Lista oferte = creeaza_lista_oferta();
	Lista undo_list = creeaza_lista_undo();
	adauga_oferta(&oferte, &undo_list, 1, "munte", "Brasov", "20.04.2026", 1500);
	adauga_oferta(&oferte, &undo_list, 2, "mare", "Grecia", "06.08.2026", 3000);
	adauga_oferta(&oferte, &undo_list, 3, "munte", "Sinaia", "02.01.2027", 4800);

	Lista sortata_pret_cresc = sorteaza_dupa_pret_crescator(&oferte);
	Oferta* s1_0 = (Oferta*)get_element(&sortata_pret_cresc, 0);
	assert(get_pret(*s1_0) == 1500);
	distruge_lista(&sortata_pret_cresc);

	Lista sortata_pret_desc = sorteaza_dupa_pret_descrescator(&oferte);
	Oferta* s2_0 = (Oferta*)get_element(&sortata_pret_desc, 0);
	assert(get_pret(*s2_0) == 4800);
	distruge_lista(&sortata_pret_desc);

	Lista sortata_dest_cresc = sorteaza_dupa_dest_crescator(&oferte);
	Oferta* s3_0 = (Oferta*)get_element(&sortata_dest_cresc, 0);
	assert(strcmp(get_destinatie(*s3_0), "Brasov") == 0);
	distruge_lista(&sortata_dest_cresc);

	Lista sortata_dest_desc = sorteaza_dupa_dest_descrescator(&oferte);
	Oferta* s4_0 = (Oferta*)get_element(&sortata_dest_desc, 0);
	assert(strcmp(get_destinatie(*s4_0), "Sinaia") == 0);
	distruge_lista(&sortata_dest_desc);

	Lista sortata_tip_cresc = sorteaza_dupa_tip_crescator(&oferte);
	Oferta* s5_0 = (Oferta*)get_element(&sortata_tip_cresc, 0);
	assert(strcmp(get_tip(*s5_0), "mare") == 0);
	distruge_lista(&sortata_tip_cresc);

	distruge_lista(&oferte);
	distruge_lista(&undo_list);
}

void test_filtreaza()
{
	Lista oferte = creeaza_lista_oferta();
	Lista undo_list = creeaza_lista_undo();
	adauga_oferta(&oferte, &undo_list, 1, "munte", "Brasov", "20.04.2026", 1500);
	adauga_oferta(&oferte, &undo_list, 2, "mare", "Grecia", "06.08.2026", 3000);
	adauga_oferta(&oferte, &undo_list, 3, "munte", "Brasov", "02.01.2027", 4800);

	// Filtrare dupa destinatie
	Lista lista_filtrata = filtreaza_oferta(&oferte, "Brasov");
	assert(lungime_lista(lista_filtrata) == 2);
	distruge_lista(&lista_filtrata);

	// Filtrare dupa destinatie (inexistent)
	Lista lista_vida = filtreaza_oferta(&oferte, "Paris");
	assert(lungime_lista(lista_vida) == 0);
	distruge_lista(&lista_vida);

	// Filtrare dupa tip (NOU)
	Lista lista_filtrata_tip = filtreaza_dupa_tip(&oferte, "mare");
	assert(lungime_lista(lista_filtrata_tip) == 1);
	distruge_lista(&lista_filtrata_tip);

	// Filtrare dupa tip (inexistent)
	Lista lista_vida_tip = filtreaza_dupa_tip(&oferte, "citybreak");
	assert(lungime_lista(lista_vida_tip) == 0);
	distruge_lista(&lista_vida_tip);

	distruge_lista(&oferte);
	distruge_lista(&undo_list);
}

void test_functionalitate_undo()
{
	Lista oferte = creeaza_lista_oferta();
	Lista undo_list = creeaza_lista_undo();

	// Acopera cazul in care lista de undo e goala
	assert(fa_undo(&oferte, &undo_list) == 0);

	adauga_oferta(&oferte, &undo_list, 1, "munte", "Brasov", "20.04.2026", 1500);
	assert(fa_undo(&oferte, &undo_list) == 1);

	distruge_lista(&oferte);
	distruge_lista(&undo_list);
}

// ASTA va inverzi cele 3 linii din prima poza!
void test_acoperire_suplimentara_dummy()
{
	void* rezultat = dummy_copy(NULL);
	assert(rezultat == NULL);
}

void ruleaza_teste_service()
{
	test_adauga();
	test_sterge();
	test_actualizeaza();
	test_sortari_specifice();
	test_filtreaza();
	test_functionalitate_undo();
	test_acoperire_suplimentara_dummy(); // Apelam functia de mai sus
}