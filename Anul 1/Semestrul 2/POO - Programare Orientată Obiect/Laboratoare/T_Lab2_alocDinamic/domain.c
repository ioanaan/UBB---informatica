#define _CRT_SECURE_NO_WARNINGS
#include "domain.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Masina creeaza_masina(const char* numar, const char* model, const char* categorie, int status)
{
	Masina m;
	m.status = status;

	m.numar = (char*)malloc(strlen(numar) + 1);
	if (m.numar != NULL) {
		strcpy(m.numar, numar);
	}

	m.model = (char*)malloc(strlen(model) + 1);
	if (m.model != NULL) {
		strcpy(m.model, model);
	}

	m.categorie = (char*)malloc(strlen(categorie) + 1);
	if (m.categorie != NULL) {
		strcpy(m.categorie, categorie);
	}

	return m;
}

void distruge_masina(Masina* m)
{
	free(m->numar);
	free(m->model);
	free(m->categorie);

	m->numar = NULL;
	m->model = NULL;
	m->categorie = NULL;
}

Masina copiaza_masina(Masina* m)
{
	return creeaza_masina(m->numar, m->model, m->categorie, m->status);
}