#define _CRT_SECURE_NO_WARNINGS

#include "domain.h"
#include <stdio.h>
#include <string.h>

Masina creeaza_masina(const char* numar, const char* model, const char* categorie, int status)
{
	/*
	 * Descriere: creeaza o masina pe baza datelor furnizate
	 * Parametri: numar (const char*) - numarul de inmatriculare, model (const char*) - modelul masinii,
	 * categorie (const char*) - categoria, status (int) - starea masinii (ex: 0 sau 1)
	 * Preconditii: numar, model, categorie sunt siruri de caractere valide (nevide)
	 * Postconditii: returneaza o masina cu atributele setate
	 */

	Masina m;
	strcpy(m.numar, numar);
	strcpy(m.model, model);
	strcpy(m.categorie, categorie);
	m.status = status;
	return m;
}