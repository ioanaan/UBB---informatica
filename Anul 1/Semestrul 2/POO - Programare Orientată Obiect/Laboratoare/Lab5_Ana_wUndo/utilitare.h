#pragma once
#include "oferta.h"

/*
* Compara doua obiecte de tip oferta si decide daca trebuie sau nu interschimbate atunci cand sortam crescator dupa pret.
* param: o1, o2=cele doua oferte care se compara.
* return: 1, daca trebuie sa interschimbam, 0 altfel.
*/
int cmp_pret_crescator(Oferta o1, Oferta o2);

/*
* Compara doua obiecte de tip oferta si decide daca trebuie sau nu interschimbate atunci cand sortam descrescator dupa pret.
* param: o1, o2=cele doua oferte care se compara.
* return: 1, daca trebuie sa interschimbam, 0 altfel.
*/
int cmp_pret_descrescator(Oferta o1, Oferta o2);

/*
* Compara doua obiecte de tip oferta si decide daca trebuie sau nu interschimbate atunci cand sortam crescator dupa destinatie.
* param: o1, o2=cele doua oferte care se compara.
* return: 1, daca trebuie sa interschimbam, 0 altfel.
*/
int cmp_dest_crescator(Oferta o1, Oferta o2);

/*
* Compara doua obiecte de tip oferta si decide daca trebuie sau nu interschimbate atunci cand sortam descrescator dupa destinatie.
* param: o1, o2=cele doua oferte care se compara.
* return: 1, daca trebuie sa interschimbam, 0 altfel.
*/
int cmp_dest_descrescator(Oferta o1, Oferta o2);

//---
int cmp_tip_crescator(Oferta o1, Oferta o2);