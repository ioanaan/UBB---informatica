#pragma once

#include "domain.h"
#include "repo.h"

int adauga_masina_service(ListaMasini* masini, const char* numar, const char* model, const char* categorie, int status);
int actualizare_masina_service(ListaMasini* masini, const char* numar, const char* model, const char* categorie, int status);
int inchiriere_returnare_service(ListaMasini* masini, const char* numar, int status);
int get_dimensiune_service(ListaMasini* masini);
Masina* get_all_masini_service(ListaMasini* masini);
ListaMasini filtrare_dupa_categorie(ListaMasini* masini, const char* categorie);
ListaMasini filtrare_dupa_model(ListaMasini* masini, const char* model);
ListaMasini dupa_model_crescator(ListaMasini* masini);
ListaMasini dupa_model_descrescator(ListaMasini* masini);
ListaMasini dupa_categorie_crescator(ListaMasini* masini);
ListaMasini dupa_categorie_descrescator(ListaMasini* masini);