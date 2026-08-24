#include "repo_oferta.h"
#include <assert.h>
#include <string.h>
#include "teste.h"
#include "utilitare.h"

void test_repo_adauga()
{
	Lista oferte = creeaza_lista(2);
	assert(lungime(oferte) == 0);

	Oferta oferta_noua = initializeaza(1, "mare", "Grecia", "30.07.2026", 3800);
	adauga(&oferte, oferta_noua);

	assert(lungime(oferte) == 1);
	assert(get_id(oferte.elemente[0]) == 1);
	assert(strcmp(get_tip(oferte.elemente[0]), "mare") == 0);
	assert(strcmp(get_destinatie(oferte.elemente[0]), "Grecia") == 0);
	assert(strcmp(get_data_plecare(oferte.elemente[0]), "30.07.2026") == 0);
	assert(get_pret(oferte.elemente[0]) == 3800);

	distruge_lista(&oferte);
}

void test_repo_sterge()
{
	Lista oferte = creeaza_lista(2);
	assert(lungime(oferte) == 0);

	Oferta oferta_mare = initializeaza(1, "mare", "Mamaia", "10.10.2026", 1000);
	Oferta oferta_munte = initializeaza(2, "munte", "Sinaia", "10.10.2026", 1000);
	Oferta oferta_city = initializeaza(3, "city break", "Roma", "10.10.2026", 1000);

	adauga(&oferte, oferta_mare);
	assert(lungime(oferte) == 1);

	int sterse = sterge(&oferte, 1); // Stergem dupa ID-ul 1 ("mare")
	assert(lungime(oferte) == 0);
	assert(sterse == 1);
	sterse = sterge(&oferte, 2); // ID inexistent momentan
	assert(sterse == 0);

	Oferta oferta_mare2 = initializeaza(1, "mare", "Mamaia", "10.10.2026", 1000);

	adauga(&oferte, oferta_munte);
	adauga(&oferte, oferta_mare2);
	adauga(&oferte, oferta_city);
	assert(lungime(oferte) == 3);

	sterse = sterge(&oferte, 1); // Stergem oferta "mare"
	assert(sterse == 1);
	assert(lungime(oferte) == 2);
	assert(strcmp(get_tip(oferte.elemente[0]), "munte") == 0);
	assert(strcmp(get_tip(oferte.elemente[1]), "city break") == 0);

	sterse = sterge(&oferte, 99); // ID inexistent
	assert(sterse == 0);
	assert(lungime(oferte) == 2);

	distruge_lista(&oferte); // Curatenie
}

void test_repo_actualizare()
{
	Lista oferte = creeaza_lista(2);

	Oferta oferta_noua = initializeaza(1, "mare", "Grecia", "30.07.2026", 3800);
	adauga(&oferte, oferta_noua);
	assert(lungime(oferte) == 1);

	Oferta oferta_actualizata = initializeaza(1, "mare", "Grecia", "07.08.2027", 3000);
	assert(actualizare(&oferte, oferta_actualizata) == 1);
	assert(strcmp(get_data_plecare(oferte.elemente[0]), "07.08.2027") == 0);
	assert(get_pret(oferte.elemente[0]) == 3000);

	// cazul cand actualizarea pica (ID-ul nu exista)
	Oferta oferta_invalida = initializeaza(99, "mare", "Grecia", "07.08.2027", 3000);
	assert(actualizare(&oferte, oferta_invalida) == 0);
	distruge_oferta(&oferta_invalida);

	distruge_lista(&oferte);
}

void test_repo_sorteaza()
{
	Lista oferte = creeaza_lista(2);
	adauga(&oferte, initializeaza(1, "mare", "Grecia", "30.07.2026", 3800));
	adauga(&oferte, initializeaza(2, "munte", "Brasov", "10.10.2026", 2600));
	adauga(&oferte, initializeaza(3, "munte", "Sinaia", "01.01.2027", 1500));
	assert(lungime(oferte) == 3);

	Lista copie = copiaza_lista(&oferte);

	Lista lista_sortata = sorteaza(&copie, cmp_pret_crescator);
	assert(get_pret(lista_sortata.elemente[0]) == 1500);
	assert(get_pret(lista_sortata.elemente[1]) == 2600);
	assert(get_pret(lista_sortata.elemente[2]) == 3800);
	distruge_lista(&lista_sortata);

	lista_sortata = sorteaza(&copie, cmp_pret_descrescator);
	assert(get_pret(lista_sortata.elemente[0]) == 3800);
	assert(get_pret(lista_sortata.elemente[1]) == 2600);
	assert(get_pret(lista_sortata.elemente[2]) == 1500);
	distruge_lista(&lista_sortata);

	lista_sortata = sorteaza(&copie, cmp_dest_crescator);
	assert(strcmp(get_destinatie(lista_sortata.elemente[0]), "Brasov") == 0);
	assert(strcmp(get_destinatie(lista_sortata.elemente[1]), "Grecia") == 0);
	assert(strcmp(get_destinatie(lista_sortata.elemente[2]), "Sinaia") == 0);
	distruge_lista(&lista_sortata);

	lista_sortata = sorteaza(&copie, cmp_dest_descrescator);
	assert(strcmp(get_destinatie(lista_sortata.elemente[0]), "Sinaia") == 0);
	assert(strcmp(get_destinatie(lista_sortata.elemente[1]), "Grecia") == 0);
	assert(strcmp(get_destinatie(lista_sortata.elemente[2]), "Brasov") == 0);
	distruge_lista(&lista_sortata);

	distruge_lista(&copie); // Curatam copia initiala
	distruge_lista(&oferte); // Curatam lista mare originala
}

void test_repo_filtrare()
{
	Lista oferte = creeaza_lista(2);
	adauga(&oferte, initializeaza(1, "mare", "Grecia", "30.07.2026", 3800));
	adauga(&oferte, initializeaza(2, "munte", "Brasov", "10.10.2026", 2600));
	adauga(&oferte, initializeaza(3, "munte", "Brasov", "01.01.2027", 1500));
	assert(lungime(oferte) == 3);

	Lista lista_filtrata = filtrare(&oferte, "Brasov");
	assert(strcmp(get_data_plecare(lista_filtrata.elemente[0]), "10.10.2026") == 0);
	assert(get_pret(lista_filtrata.elemente[0]) == 2600);
	assert(strcmp(get_data_plecare(lista_filtrata.elemente[1]), "01.01.2027") == 0);
	assert(get_pret(lista_filtrata.elemente[1]) == 1500);
	assert(lungime(lista_filtrata) == 2);

	distruge_lista(&lista_filtrata); // Curatam lista filtrata
	distruge_lista(&oferte); // Curatam lista mare
}

void test_repo_creare_esuata()
{
	Lista oferte_ok = creeaza_lista(2);
	assert(oferte_ok.capacitate == 2);
	distruge_lista(&oferte_ok);

	Lista oferte_picata = creeaza_lista(-1);
	assert(oferte_picata.capacitate == 0);
	assert(oferte_picata.elemente == NULL);

	distruge_lista(&oferte_picata);
}

void ruleaza_teste_repo()
{
	test_repo_adauga();
	test_repo_sterge();
	test_repo_actualizare();
	test_repo_sorteaza();
	test_repo_filtrare();
	test_repo_creare_esuata();
}