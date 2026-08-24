#include "domain.h"
#include "repo.h"
#include "service.h"
#include "validator.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

void test_creeaza_masina()
{
	Masina m = creeaza_masina("BC11NGD", "Astra", "break", 0);

	assert(strcmp(m.numar, "BC11NGD") == 0);
	assert(strcmp(m.model, "Astra") == 0);
	assert(strcmp(m.categorie, "break") == 0);
	assert(m.status == 0);

	distruge_masina(&m);
}

void test_adauga_masina()
{
	ListaMasini l;
	initializare_lista(&l);

	Masina m = creeaza_masina("BC11NGD", "Astra", "break", 0);
	adauga_masina(&l, m);

	assert(l.nr_masini == 1);
	assert(strcmp(l.masini[0].numar, "BC11NGD") == 0);

	distruge_lista(&l);
}

void test_cautare_masina()
{
	ListaMasini l;
	initializare_lista(&l);

	Masina m1 = creeaza_masina("BC11NGD", "Astra", "break", 0);
	Masina m2 = creeaza_masina("CJ96AFI", "CLS", "sedan", 0);
	adauga_masina(&l, m1);
	adauga_masina(&l, m2);

	assert(l.nr_masini == 2);
	assert(cauta_masina(&l, "BC11NGD") == 0);
	assert(cauta_masina(&l, "CJ96AFI") == 1);
	assert(cauta_masina(&l, "ZZD07RT") == -1);

	distruge_lista(&l);
}

void test_actualizare_masina()
{
	ListaMasini l;
	initializare_lista(&l);

	Masina m1 = creeaza_masina("BC11NGD", "Astra", "break", 0);
	adauga_masina(&l, m1);

	Masina m2 = creeaza_masina("BC11NGD", "Astra", "sedan", 0);
	assert(actualizare_masina(&l, m2) == 1);
	assert(strcmp(l.masini[0].categorie, "sedan") == 0);

	Masina m3 = creeaza_masina("ZZD07RT", "Astra", "break", 0);
	assert(actualizare_masina(&l, m3) == 0);
	distruge_masina(&m3); // Curatam memoria manual!

	distruge_lista(&l);
}

void test_get_dimensiune_si_elemente()
{
	ListaMasini l;
	initializare_lista(&l);

	assert(get_dimensiune(&l) == 0);

	Masina m1 = creeaza_masina("BC11AAA", "Astra", "break", 0);
	Masina m2 = creeaza_masina("CJ96AFI", "CLS", "sedan", 0);
	adauga_masina(&l, m1);
	adauga_masina(&l, m2);

	assert(get_dimensiune(&l) == 2);

	Masina* vector = get_all_masini(&l);
	assert(strcmp(vector[0].numar, "BC11AAA") == 0);
	assert(strcmp(vector[1].numar, "CJ96AFI") == 0);
	assert(strcmp(vector[0].model, "Astra") == 0);

	distruge_lista(&l);
}

void test_validator()
{
	Masina m_valid_1 = creeaza_masina("BC69AXN", "Golf", "hatchback", 0);
	assert(valideaza_masina(m_valid_1) == 1);
	distruge_masina(&m_valid_1);

	Masina m_valid_2 = creeaza_masina("B01ZZZ", "X5", "suv", 1);
	assert(valideaza_masina(m_valid_2) == 1);
	distruge_masina(&m_valid_2);

	Masina m_valid_3 = creeaza_masina("CJ111FFF", "A4", "break", 0);
	assert(valideaza_masina(m_valid_3) == 1);
	distruge_masina(&m_valid_3);

	Masina m_fara_nr = creeaza_masina("", "Golf", "sedan", 0);
	assert(valideaza_masina(m_fara_nr) == 0);
	distruge_masina(&m_fara_nr);

	Masina m_fara_model = creeaza_masina("BC69AXN", "", "sedan", 0);
	assert(valideaza_masina(m_fara_model) == 0);
	distruge_masina(&m_fara_model);

	Masina m_fara_cat = creeaza_masina("BC69AXN", "Golf", "", 0);
	assert(valideaza_masina(m_fara_cat) == 0);
	distruge_masina(&m_fara_cat);

	Masina m_status_inv = creeaza_masina("BC69AXN", "Golf", "sedan", 4);
	assert(valideaza_masina(m_status_inv) == 0);
	distruge_masina(&m_status_inv);

	Masina m_cat_inv = creeaza_masina("BC69AXN", "Golf", "tractor", 0);
	assert(valideaza_masina(m_cat_inv) == 0);
	distruge_masina(&m_cat_inv); // Aici era o greseala in codul tau!

	Masina m_nr_scurt = creeaza_masina("B1AAA", "Golf", "sedan", 0);
	assert(valideaza_masina(m_nr_scurt) == 0);
	distruge_masina(&m_nr_scurt);

	Masina m_nr_lung = creeaza_masina("BCC111AAA", "Golf", "sedan", 0);
	assert(valideaza_masina(m_nr_lung) == 0);
	distruge_masina(&m_nr_lung);

	Masina m_nr_final_inv = creeaza_masina("BC11AA1", "Golf", "sedan", 0);
	assert(valideaza_masina(m_nr_final_inv) == 0);
	distruge_masina(&m_nr_final_inv);

	Masina m_nr_start_inv = creeaza_masina("1C11AAA", "Golf", "sedan", 0);
	assert(valideaza_masina(m_nr_start_inv) == 0);
	distruge_masina(&m_nr_start_inv);

	Masina m_nr_litere_mid = creeaza_masina("BC1XAAA", "Golf", "sedan", 0);
	assert(valideaza_masina(m_nr_litere_mid) == 0);
	distruge_masina(&m_nr_litere_mid);

	Masina m_nr_cifre_putine = creeaza_masina("BC1AAA", "Golf", "sedan", 0);
	assert(valideaza_masina(m_nr_cifre_putine) == 0);
	distruge_masina(&m_nr_cifre_putine);
}

void test_adaugare_service()
{
	ListaMasini l;
	initializare_lista(&l);

	assert(adauga_masina_service(&l, "BC11NGD", "Astra", "break", 0) == 0);
	assert(adauga_masina_service(&l, "CJ96AFI", "CLS", "sedan", 0) == 0);
	assert(adauga_masina_service(&l, "BC69AXN", "Golf", "hatchback", 0) == 0);

	assert(adauga_masina_service(&l, "BC1sNG2", "23456", "breack", 4) == 1);
	assert(adauga_masina_service(&l, "BC11NGD", "Astra", "break", 0) == 2);

	distruge_lista(&l);
}

void test_actualizare_masina_service()
{
	ListaMasini l;
	initializare_lista(&l);

	adauga_masina_service(&l, "BC11AAA", "Astra", "break", 0);

	assert(actualizare_masina_service(&l, "BC11AAA", "Astra", "tractor", 0) == 1);
	assert(actualizare_masina_service(&l, "CJ99ZZZ", "Golf", "hatchback", 0) == 2);
	assert(actualizare_masina_service(&l, "BC11AAA", "Vectra", "sedan", 0) == 0);

	assert(strcmp(l.masini[0].model, "Vectra") == 0);
	assert(strcmp(l.masini[0].categorie, "sedan") == 0);

	distruge_lista(&l);
}

void test_inchiriere_returnare_service()
{
	ListaMasini l;
	initializare_lista(&l);

	adauga_masina_service(&l, "BC11AAA", "Astra", "break", 0);

	assert(inchiriere_returnare_service(&l, "CJ99ZZZ", 1) == 2);
	assert(inchiriere_returnare_service(&l, "BC11AAA", 1) == 0);

	int poz = cauta_masina(&l, "BC11AAA");
	assert(l.masini[poz].status == 1);

	assert(inchiriere_returnare_service(&l, "BC11AAA", 1) == 2);
	assert(inchiriere_returnare_service(&l, "BC11AAA", 0) == 0);
	assert(l.masini[poz].status == 0);

	assert(inchiriere_returnare_service(&l, "BC11AAA", 0) == 2);

	distruge_lista(&l);
}

void test_functionalitati_service()
{
	ListaMasini l;
	initializare_lista(&l);

	adauga_masina_service(&l, "BC01AAA", "Volvo", "sedan", 0);
	adauga_masina_service(&l, "BC02BBB", "Audi", "sedan", 0);
	adauga_masina_service(&l, "BC03CCC", "Audi", "break", 0);

	ListaMasini filtrate = filtrare_dupa_model(&l, "Audi");
	assert(filtrate.nr_masini == 2);
	assert(strcmp(filtrate.masini[0].model, "Audi") == 0);

	ListaMasini sortate = dupa_model_crescator(&l);
	assert(sortate.nr_masini == 3);
	assert(strcmp(sortate.masini[0].model, "Audi") == 0);
	assert(strcmp(sortate.masini[2].model, "Volvo") == 0);

	distruge_lista(&filtrate);
	distruge_lista(&sortate);
	distruge_lista(&l);
}

void test_filtrare_dupa_categorie_full()
{
	ListaMasini l;
	initializare_lista(&l);

	adauga_masina_service(&l, "BC11AAA", "Astra", "sedan", 0);
	adauga_masina_service(&l, "BC22BBB", "Golf", "suv", 0);
	adauga_masina_service(&l, "BC33CCC", "Passat", "sedan", 0);

	ListaMasini filtrate_sedan = filtrare_dupa_categorie(&l, "sedan");
	assert(filtrate_sedan.nr_masini == 2);
	assert(strcmp(filtrate_sedan.masini[0].numar, "BC11AAA") == 0);
	assert(strcmp(filtrate_sedan.masini[1].numar, "BC33CCC") == 0);

	ListaMasini filtrate_suv = filtrare_dupa_categorie(&l, "suv");
	assert(filtrate_suv.nr_masini == 1);
	assert(strcmp(filtrate_suv.masini[0].model, "Golf") == 0);

	ListaMasini filtrate_cabrio = filtrare_dupa_categorie(&l, "cabrio");
	assert(filtrate_cabrio.nr_masini == 0);

	distruge_lista(&filtrate_sedan);
	distruge_lista(&filtrate_suv);
	distruge_lista(&filtrate_cabrio);
	distruge_lista(&l);
}

void test_dupa_model_descrescator()
{
	ListaMasini l;
	initializare_lista(&l);

	adauga_masina_service(&l, "BC01AAA", "Audi", "sedan", 0);
	adauga_masina_service(&l, "BC02BBB", "Volvo", "break", 0);
	adauga_masina_service(&l, "BC03CCC", "BMW", "suv", 0);

	ListaMasini sortate = dupa_model_descrescator(&l);

	assert(sortate.nr_masini == 3);
	assert(strcmp(sortate.masini[0].model, "Volvo") == 0);
	assert(strcmp(sortate.masini[1].model, "BMW") == 0);
	assert(strcmp(sortate.masini[2].model, "Audi") == 0);

	distruge_lista(&sortate);
	distruge_lista(&l);
}

void test_dupa_categorie_crescator()
{
	ListaMasini l;
	initializare_lista(&l);

	adauga_masina_service(&l, "BC01AAA", "Astra", "suv", 0);
	adauga_masina_service(&l, "BC02BBB", "Golf", "break", 0);
	adauga_masina_service(&l, "BC03CCC", "CLS", "sedan", 0);

	ListaMasini sortate = dupa_categorie_crescator(&l);

	assert(sortate.nr_masini == 3);
	assert(strcmp(sortate.masini[0].categorie, "break") == 0);
	assert(strcmp(sortate.masini[1].categorie, "sedan") == 0);
	assert(strcmp(sortate.masini[2].categorie, "suv") == 0);

	distruge_lista(&sortate);
	distruge_lista(&l);
}

void test_dupa_categorie_descrescator()
{
	ListaMasini l;
	initializare_lista(&l);

	adauga_masina_service(&l, "BC01AAA", "Astra", "break", 0);
	adauga_masina_service(&l, "BC02BBB", "Golf", "suv", 0);
	adauga_masina_service(&l, "BC03CCC", "CLS", "sedan", 0);

	ListaMasini sortate = dupa_categorie_descrescator(&l);

	assert(sortate.nr_masini == 3);
	assert(strcmp(sortate.masini[0].categorie, "suv") == 0);
	assert(strcmp(sortate.masini[1].categorie, "sedan") == 0);
	assert(strcmp(sortate.masini[2].categorie, "break") == 0);

	distruge_lista(&sortate);
	distruge_lista(&l);
}

void test_getters_service()
{
	ListaMasini l;
	initializare_lista(&l);

	assert(get_dimensiune_service(&l) == 0);

	adauga_masina_service(&l, "BC11AAA", "Astra", "break", 0);

	assert(get_dimensiune_service(&l) == 1);

	Masina* masini = get_all_masini_service(&l);
	assert(strcmp(masini[0].numar, "BC11AAA") == 0);
	assert(strcmp(masini[0].model, "Astra") == 0);

	distruge_lista(&l);
}

void ruleaza_toate_testele()
{
	test_creeaza_masina();
	test_adauga_masina();
	test_cautare_masina();
	test_actualizare_masina();
	test_get_dimensiune_si_elemente();
	test_validator();
	test_adaugare_service();
	test_actualizare_masina_service();
	test_inchiriere_returnare_service();
	test_functionalitati_service();
	test_filtrare_dupa_categorie_full();
	test_dupa_model_descrescator();
	test_dupa_categorie_crescator();
	test_dupa_categorie_descrescator();
	test_getters_service();

	printf("testele au trecut\n");
}