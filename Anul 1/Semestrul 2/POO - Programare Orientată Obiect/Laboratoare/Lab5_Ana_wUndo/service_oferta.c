#include "service_oferta.h"
#include "validator.h"
#include "utilitare.h"
#include <string.h>
#include <stdlib.h>

void distruge_oferta_generica(void* element)
{
	Oferta* of = (Oferta*)element;
	distruge_oferta(of); free(of);
}

void* copiaza_oferta_generica(void* element)
{
	Oferta* of = (Oferta*)element;
	Oferta* copie = (Oferta*)malloc(sizeof(Oferta));
	*copie = initializeaza(get_id(*of), get_tip(*of), get_destinatie(*of), get_data_plecare(*of), get_pret(*of));
	return copie;
}

void distruge_lista_pentru_undo(void* element)
{
	Lista* l = (Lista*)element;
	distruge_lista(l); free(l);
}

void* dummy_copy(void* element)
{
	return NULL;
}

Lista creeaza_lista_oferta()
{
	return creeaza_lista(2, distruge_oferta_generica, copiaza_oferta_generica);
}

Lista creeaza_lista_undo()
{
	return creeaza_lista(2, distruge_lista_pentru_undo, dummy_copy);
}

int lungime_lista(Lista oferte)
{
	return lungime(oferte);
}

int adauga_oferta(Lista* oferte, Lista* undo_list, int id, char tip[], char destinatie[], char data[], double pret)
{
	for (int i = 0; i < lungime(*oferte); i++)
	{
		Oferta* of_curenta = (Oferta*)get_element(oferte, i);
		if (get_id(*of_curenta) == id) return 2;
	}

	Oferta* oferta_noua = (Oferta*)malloc(sizeof(Oferta));
	*oferta_noua = initializeaza(id, tip, destinatie, data, pret);

	if (valideaza_oferta(*oferta_noua) == 1)
	{
		Lista* copie_oferte = (Lista*)malloc(sizeof(Lista));
		*copie_oferte = copiaza_lista(oferte);
		adauga(undo_list, copie_oferte);

		adauga(oferte, oferta_noua);
		return 1;
	}

	distruge_oferta(oferta_noua); free(oferta_noua);
	return 0;
}

int sterge_oferta(Lista* oferte, Lista* undo_list, int id)
{
	for (int i = 0; i < lungime(*oferte); i++)
	{
		Oferta* of = (Oferta*)get_element(oferte, i);
		if (get_id(*of) == id)
		{
			Lista* copie_oferte = (Lista*)malloc(sizeof(Lista));
			*copie_oferte = copiaza_lista(oferte);
			adauga(undo_list, copie_oferte);

			sterge_pozitie(oferte, i);
			return 1;
		}
	}

	return 0;
}

int actualizeaza_oferta(Lista* oferte, Lista* undo_list, int id, char tip[], char destinatie[], char data[], double pret)
{
	Oferta* oferta_noua = (Oferta*)malloc(sizeof(Oferta));
	*oferta_noua = initializeaza(id, tip, destinatie, data, pret);

	if (valideaza_oferta(*oferta_noua) == 0)
	{
		distruge_oferta(oferta_noua); free(oferta_noua); return 0;
	}

	for (int i = 0; i < lungime(*oferte); i++)
	{
		Oferta* of_curenta = (Oferta*)get_element(oferte, i);
		if (get_id(*of_curenta) == id)
		{
			Lista* copie_oferte = (Lista*)malloc(sizeof(Lista));
			*copie_oferte = copiaza_lista(oferte);
			adauga(undo_list, copie_oferte);

			sterge_pozitie(oferte, i);
			adauga(oferte, oferta_noua);
			return 1;
		}
	}
	distruge_oferta(oferta_noua); free(oferta_noua);
	return 0;
}

int fa_undo(Lista* oferte, Lista* undo_list)
{
	if (lungime(*undo_list) == 0)
	{
		return 0;
	}
	distruge_lista(oferte);

	int ultima_poz = lungime(*undo_list) - 1;
	Lista* ultima_stare = (Lista*)get_element(undo_list, ultima_poz);

	*oferte = copiaza_lista(ultima_stare);

	sterge_pozitie(undo_list, ultima_poz);

	return 1;
}

Lista sorteaza_general(Lista* oferte, int (*functie_cmp)(Oferta, Oferta))
{
	Lista copie = copiaza_lista(oferte);
	for (int i = 0; i < lungime(copie) - 1; i++)
	{
		for (int j = i + 1; j < lungime(copie); j++)
		{
			Oferta* o1 = (Oferta*)get_element(&copie, i);
			Oferta* o2 = (Oferta*)get_element(&copie, j);
			if (functie_cmp(*o1, *o2) == 1)
			{
				void* aux = copie.elemente[i];
				copie.elemente[i] = copie.elemente[j];
				copie.elemente[j] = aux;
			}
		}
	}
	return copie;
}

Lista sorteaza_dupa_pret_crescator(Lista* oferte)
{
	return sorteaza_general(oferte, cmp_pret_crescator);
}

Lista sorteaza_dupa_pret_descrescator(Lista* oferte)
{
	return sorteaza_general(oferte, cmp_pret_descrescator);
}

Lista sorteaza_dupa_dest_crescator(Lista* oferte)
{
	return sorteaza_general(oferte, cmp_dest_crescator);
}

Lista sorteaza_dupa_dest_descrescator(Lista* oferte)
{
	return sorteaza_general(oferte, cmp_dest_descrescator);
}

Lista sorteaza_dupa_tip_crescator(Lista* oferte)
{
	return sorteaza_general(oferte, cmp_tip_crescator);
}

Lista filtreaza_oferta(Lista* oferte, char destinatie_cautata[])
{
	Lista lista_filtrata = creeaza_lista_oferta();
	for (int i = 0; i < lungime(*oferte); i++)
	{
		Oferta* of_curenta = (Oferta*)get_element(oferte, i);
		if (strcmp(get_destinatie(*of_curenta), destinatie_cautata) == 0)
		{
			Oferta* copie = copiaza_oferta_generica(of_curenta);
			adauga(&lista_filtrata, copie);
		}
	}
	return lista_filtrata;
}

Lista filtreaza_dupa_tip(Lista* oferte, char tip_cautat[])
{
	Lista lista_filtrata = creeaza_lista_oferta();
	for (int i = 0; i < lungime(*oferte); i++)
	{
		Oferta* of_curenta = (Oferta*)get_element(oferte, i);
		if (strcmp(get_tip(*of_curenta), tip_cautat) == 0)
		{
			Oferta* copie = copiaza_oferta_generica(of_curenta);
			adauga(&lista_filtrata, copie);
		}
	}
	return lista_filtrata;
}