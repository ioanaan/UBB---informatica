#pragma once
#include "service_oferta.h" 

/*
* Afiseaza meniul.
*/
void afisare_meniu();

/*
* Adauga o oferta la lista de oferte.
* param: oferte=lista de oferte la care se adauga.
*/
void adaugare_ui(Lista* oferte);

/*
* Sterge o oferta din lista de oferte.
* param: oferte=lista din care se sterge
*/
void sterge_ui(Lista* oferte);

/*
* Actualizeaza datele unei oferte din lista.
* param: oferte=lista pentru care se actualizeaza
*/
void actualizare_ui(Lista* oferte);

/*
* Sorteaza o lista de oferte.
* param: oferte=lista de sortat
*/
void sorteaza_ui(Lista* oferte);

/*
* Filtreaza dintr-o lista de oferte.
* param: oferte=lista din care se filtreaza
*/
void filtrare_ui(Lista* oferte);

/*
* Functia care ruleaza aplicatia.
*/
void run();