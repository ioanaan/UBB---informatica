#include <assert.h>
#include "oferta.h"
#include <string.h>
#include "teste.h"
#include "validator.h"

void test_oferta()
{
	Oferta oferta = initializeaza(1, "citiy break", "Italia", "10.08.2026", 2500);

	assert(get_id(oferta) == 1);
	assert(strcmp(get_tip(oferta), "citiy break") == 0);
	assert(strcmp(get_destinatie(oferta), "Italia") == 0);
	assert(strcmp(get_data_plecare(oferta), "10.08.2026") == 0);
	assert(get_pret(oferta) == 2500);

	distruge_oferta(&oferta);
}

void test_validator()
{
	Oferta oferta1 = initializeaza(1, "munte", "Brasov", "10.10.2026", 1000);
	assert(valideaza_oferta(oferta1) == 1);
	distruge_oferta(&oferta1);

	Oferta oferta2 = initializeaza(2, "vacanta", "Brasov", "10.10.2026", 1000);
	assert(valideaza_oferta(oferta2) == 0);
	distruge_oferta(&oferta2);

	Oferta oferta3 = initializeaza(3, "munte", "Brasov", "10", 1000);
	assert(valideaza_oferta(oferta3) == 0);
	distruge_oferta(&oferta3);

	Oferta oferta4 = initializeaza(4, "munte", "Brasov", "10.10.2026", -1);
	assert(valideaza_oferta(oferta4) == 0);
	distruge_oferta(&oferta4);

	Oferta oferta5 = initializeaza(5, "munte", "Brasov", "40.10.2026", 1000);
	assert(valideaza_oferta(oferta5) == 0);
	distruge_oferta(&oferta5);

	Oferta oferta6 = initializeaza(6, "munte", "Brasov", "10.50.2026", 1000);
	assert(valideaza_oferta(oferta6) == 0);
	distruge_oferta(&oferta6);

	Oferta oferta7 = initializeaza(7, "munte", "Brasov", "10.10.-1", 1000);
	assert(valideaza_oferta(oferta7) == 0);
	distruge_oferta(&oferta7);

	Oferta oferta8 = initializeaza(-1, "munte", "Brasov", "10.10.2026", 1000);
	assert(valideaza_oferta(oferta8) == 0);
	distruge_oferta(&oferta8);

	Oferta oferta_format = initializeaza(9, "munte", "Brasov", "10-10-2026", 1000);
	assert(valideaza_oferta(oferta_format) == 0);
	distruge_oferta(&oferta_format);

	char criteriu[50];
	strcpy_s(criteriu, 50, "pret");
	assert(valideaza_criteriu(criteriu) == 1);
	strcpy_s(criteriu, 50, "destinatie");
	assert(valideaza_criteriu(criteriu) == 1);
	strcpy_s(criteriu, 50, "data");
	assert(valideaza_criteriu(criteriu) == 0);

	char ordine[50];
	strcpy_s(ordine, 50, "crescator");
	assert(valideaza_ordine(ordine) == 1);
	strcpy_s(ordine, 50, "descrescator");
	assert(valideaza_ordine(ordine) == 1);
	strcpy_s(ordine, 50, "altceva");
	assert(valideaza_ordine(ordine) == 0);
}

void ruleaza_teste_domain()
{
	test_oferta();
	test_validator();
}