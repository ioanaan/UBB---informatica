#pragma once

#include "domain.h"

typedef struct
{
	Masina* masini;
	int nr_masini;
	int capacitate;

}ListaMasini;

void initializare_lista(ListaMasini* masini);
void adauga_masina(ListaMasini* lista_m, Masina m);
int cauta_masina(ListaMasini* masini, const char* nr_cautat);
int actualizare_masina(ListaMasini* masini, Masina m);
int get_dimensiune(ListaMasini* masini);
Masina* get_all_masini(ListaMasini* masini);
void distruge_lista(ListaMasini* lista_m);