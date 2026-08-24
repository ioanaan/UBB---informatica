#include "repo_oferta.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Lista creeaza_lista(int capacitate_initiala)
{
	Lista lista_noua;
	lista_noua.lungime = 0;
	lista_noua.capacitate = capacitate_initiala;

	lista_noua.elemente = (Oferta*)malloc(sizeof(Oferta) * lista_noua.capacitate);

	if (lista_noua.elemente == NULL) 
	{
		lista_noua.capacitate = 0;
	}

	return lista_noua;
}

void distruge_lista(Lista* oferte)
{
	for (int i = 0; i < oferte->lungime; i++)
	{
		distruge_oferta(&oferte->elemente[i]);
	}

	free(oferte->elemente);

	oferte->elemente = NULL;
	oferte->lungime = 0;
	oferte->capacitate = 0;
}

//void adauga(Lista* oferte, Oferta oferta_noua)
//{
//	if (oferte->capacitate <= oferte->lungime)
//	{
//		Oferta* aux = malloc(sizeof(Oferta) * (oferte->capacitate + 5));
//		for (int i = 0; i < oferte->lungime; i++)
//		{
//			aux[i] = oferte->elemente[i];
//		}
//		free(oferte->elemente);
//		oferte->elemente = aux;
//		oferte->capacitate += 5;
//	}
//	oferte->elemente[oferte->lungime++] = oferta_noua;
//}

void adauga(Lista* oferte, Oferta oferta_noua)
{
	// Daca s-a umplut capacitatea, o marim
	if (oferte->lungime >= oferte->capacitate)
	{
		int noua_capacitate = oferte->capacitate + 5;

		// realloc incearca sa mareasca memoria pe loc. Daca nu are loc, 
		// aloca el altundeva si copiaza automat datele (mult mai rapid decat un 'for')
		Oferta* aux = (Oferta*)realloc(oferte->elemente, sizeof(Oferta) * noua_capacitate);

		// Verificam mereu daca am primit memorie inapoi!
		if (aux != NULL)
		{
			oferte->elemente = aux;
			oferte->capacitate = noua_capacitate;
		}
	}

	// Adaugam noua oferta pe ultima pozitie si crestem lungimea
	oferte->elemente[oferte->lungime] = oferta_noua;
	oferte->lungime++;
}

int sterge(Lista* oferte, int id)
{
	for (int i = 0; i < oferte->lungime; i++)
	{
		if (get_id(oferte->elemente[i]) == id)
		{
			distruge_oferta(&oferte->elemente[i]);
			for (int j = i; j < oferte->lungime - 1; j++)
			{
				oferte->elemente[j] = oferte->elemente[j + 1];
			}
			oferte->lungime--;
			return 1;
		}
	}
	return 0;
}

int actualizare(Lista* oferte, Oferta oferta_actualizata)
{
	for (int i = 0; i < oferte->lungime; i++)
	{
		if (get_id(oferte->elemente[i]) == get_id(oferta_actualizata))
		{
			distruge_oferta(&oferte->elemente[i]);
			oferte->elemente[i] = oferta_actualizata;
			return 1;
		}
	}
	return 0;
}

int lungime(Lista oferte)
{
	return oferte.lungime;
}

Lista copiaza_lista(Lista* lista_originala)
{
	Lista copie = creeaza_lista(lista_originala->capacitate);

	for (int i = 0; i < lista_originala->lungime; i++)
	{
		Oferta oferta_copiata = initializeaza(
			get_id(lista_originala->elemente[i]),
			get_tip(lista_originala->elemente[i]),
			get_destinatie(lista_originala->elemente[i]),
			get_data_plecare(lista_originala->elemente[i]),
			get_pret(lista_originala->elemente[i])
		);

		adauga(&copie, oferta_copiata);
	}
	return copie;
}

Lista sorteaza(Lista* oferte, int (*functie_cmp)(Oferta, Oferta))
{
	Lista copie = copiaza_lista(oferte);
	for (int i = 0; i < copie.lungime - 1; i++)
	{
		for (int j = i + 1; j < copie.lungime; j++)
		{
			if (functie_cmp(copie.elemente[i], copie.elemente[j]) == 1)
			{
				Oferta aux = copie.elemente[i];
				copie.elemente[i] = copie.elemente[j];
				copie.elemente[j] = aux;
			}
		}
	}
	return copie;
}

Lista filtrare(Lista* oferte, char criteriu[])
{
	Lista lista_filtrata = creeaza_lista(2);

	for (int i = 0; i < oferte->lungime; i++)
	{
		if (strcmp(get_destinatie(oferte->elemente[i]), criteriu) == 0)
		{
			Oferta oferta_filtrata = initializeaza(
				get_id(oferte->elemente[i]),
				get_tip(oferte->elemente[i]),
				get_destinatie(oferte->elemente[i]),
				get_data_plecare(oferte->elemente[i]),
				get_pret(oferte->elemente[i])
			);

			adauga(&lista_filtrata, oferta_filtrata);
		}
	}
	return lista_filtrata;
}