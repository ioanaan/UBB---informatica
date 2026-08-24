#pragma once
#include "oferta.h"

/*
* Primeste o oferta ca parametru si se asigura ca valorile atributelor sunt valide.
* param: oferta pentru care se verifica
* return 1, daca toate atributele sunt valide sau 0 daca a fosta o valoare invalida
*/
int valideaza_oferta(Oferta oferta);

/*
* Primeste un criteriu si se asigura ca este fie "pret", fie "destinatie".
* param: criteriu=criteriul de verificat
* return: 1, daca criteriul este valid, 0 altfel
*/
int valideaza_criteriu(char criteriu[]);

/*
* Primeste un sir de caractere care reprezinta ordinea dupa care se doreste o sortare si verifica daca este fie "crescator", fie "descrescator".
* param: ordine=sirul de verificat
* return: 1, daca ordinea este una valida, 0 altfel.
*/
int valideaza_ordine(char ordine[]);