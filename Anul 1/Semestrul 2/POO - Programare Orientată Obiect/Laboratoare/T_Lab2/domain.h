#pragma once

typedef struct
{
	char numar[10];
	char model[20];
	char categorie[20];
	/// suv, cabrio, sedan, hatchback, break
	int status; 
	/// 0 - disponibil, 1 - inchiriat

}Masina;

Masina creeaza_masina(const char* numar, const char* model, const char* categorie, int status);