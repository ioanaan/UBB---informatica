#pragma once

#include "domain.h"

typedef struct
{
	Masina masini[100];
	int nr_masini;

}ListaMasini;

void initializare_lista(ListaMasini* masini);
void adauga_masina(ListaMasini* lista_m, Masina m);
int cauta_masina(ListaMasini* masini, char* nr_cautat);
int actualizare_masina(ListaMasini* masini, Masina m);
int get_dimensiune(ListaMasini* masini);
Masina* get_all_masini(ListaMasini* masini);