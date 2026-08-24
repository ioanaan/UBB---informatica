#pragma once

typedef struct
{
	char* numar;
	char* model;
	char* categorie;
	/// suv, cabrio, sedan, hatchback, break
	int status; 
	/// 0 - disponibil, 1 - inchiriat

}Masina;

Masina creeaza_masina(const char* numar, const char* model, const char* categorie, int status);
void distruge_masina(Masina* m);
Masina copiaza_masina(Masina* m);