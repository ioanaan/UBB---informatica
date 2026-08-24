#include "repo_oferta.h"
#include <stdlib.h>

Lista creeaza_lista(int capacitate_initiala, DestroyFunction dest_fn, CopyFunction copy_fn)
{
	Lista lista_noua;
	lista_noua.lungime = 0;
	lista_noua.capacitate = capacitate_initiala;
	lista_noua.fn_destroy = dest_fn;
	lista_noua.fn_copy = copy_fn;

	lista_noua.elemente = (void**)malloc(sizeof(void*) * lista_noua.capacitate);

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
		oferte->fn_destroy(oferte->elemente[i]);
	}
	free(oferte->elemente);
	oferte->elemente = NULL;
	oferte->lungime = 0;
	oferte->capacitate = 0;
}

void adauga(Lista* oferte, void* element)
{
	if (oferte->lungime >= oferte->capacitate)
	{
		int noua_capacitate = oferte->capacitate + 5;
		void** aux = (void**)realloc(oferte->elemente, sizeof(void*) * noua_capacitate);
		if (aux != NULL) 
		{
			oferte->elemente = aux;
			oferte->capacitate = noua_capacitate;
		}
	}
	oferte->elemente[oferte->lungime] = element;
	oferte->lungime++;
}

void sterge_pozitie(Lista* oferte, int poz)
{
	if (poz < 0 || poz >= oferte->lungime) return;

	oferte->fn_destroy(oferte->elemente[poz]);

	for (int i = poz; i < oferte->lungime - 1; i++) 
	{
		oferte->elemente[i] = oferte->elemente[i + 1];
	}
	oferte->lungime--;
}

void* get_element(Lista* oferte, int poz)
{
	return oferte->elemente[poz];
}

int lungime(Lista oferte)
{
	return oferte.lungime;
}

Lista copiaza_lista(Lista* lista_originala)
{
	Lista copie = creeaza_lista(lista_originala->capacitate, lista_originala->fn_destroy, lista_originala->fn_copy);
	for (int i = 0; i < lista_originala->lungime; i++) 
	{
		void* element_copiat = lista_originala->fn_copy(lista_originala->elemente[i]);
		adauga(&copie, element_copiat);
	}
	return copie;
}