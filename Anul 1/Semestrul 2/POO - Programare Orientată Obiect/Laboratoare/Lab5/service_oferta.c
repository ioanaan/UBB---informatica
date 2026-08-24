#include "service_oferta.h"
#include "validator.h"
#include <string.h>
#include "utilitare.h"

int lungime_lista(Lista oferte)
{
	return lungime(oferte);
}

int adauga_oferta(Lista* oferte, int id, char tip[], char destinatie[], char data[], double pret)
{
	for (int i = 0; i < oferte->lungime; i++) {
		if (get_id(oferte->elemente[i]) == id) {
			return 2;
		}
	}
	Oferta oferta;
	oferta = initializeaza(id, tip, destinatie, data, pret);
	if (valideaza_oferta(oferta) == 1)
	{
		adauga(oferte, oferta);
		return 1;}
	else
	{
		distruge_oferta(&oferta);
		return 0;
	}
}

int sterge_oferta(Lista* oferte, int id)
{
	return sterge(oferte, id);
}

Lista creeaza_lista_oferta()
{
	return creeaza_lista(2);
}

int actualizeaza_oferta(Lista* oferte, int id, char tip[], char destinatie[], char data[], double pret)
{
	Oferta oferta_actualizata = initializeaza(id, tip, destinatie, data, pret);
	if (valideaza_oferta(oferta_actualizata) == 1)
	{
		int rezultat_repo = actualizare(oferte, oferta_actualizata);

		// Daca ID-ul nu a fost gasit in repo, distrugem oferta creata pentru a nu pierde memorie
		if (rezultat_repo == 0) {
			distruge_oferta(&oferta_actualizata);
		}

		return rezultat_repo;}
	else
	{
		distruge_oferta(&oferta_actualizata);
		return 0;
	}
}

Lista sorteaza_dupa_pret_crescator(Lista* oferte)
{
	return sorteaza(oferte, cmp_pret_crescator);
}

Lista sorteaza_dupa_pret_descrescator(Lista* oferte) {
	return sorteaza(oferte, cmp_pret_descrescator);
}

Lista sorteaza_dupa_dest_crescator(Lista* oferte) {
	return sorteaza(oferte, cmp_dest_crescator);
}

Lista sorteaza_dupa_dest_descrescator(Lista* oferte) {
	return sorteaza(oferte, cmp_dest_descrescator);
}

Lista filtreaza_oferta(Lista* oferte, char destinatie_cautata[])
{
	return filtrare(oferte, destinatie_cautata);
}
