#pragma once
#include "repo_oferta.h"

/*
* Returneaza lungimea unei liste transmisa ca parametru.
* param: oferte=lista de obiecte careia i se returneaza lungimea.
* return: lungimea listei
*/
int lungime_lista(Lista oferte);

/*
* Adauga o oferta noua in lista de oferte.
* param: oferte=lista de oferte
* param: tip=tipul ofertei care se adauga
* param: destinatie=destinatia ofertei care se aduga
* param: data=data ofertei care se adauga
* param: pret=pretul ofertei care se adauga
* return: -
*/
int adauga_oferta(Lista* oferte, int id, char tip[], char destinatie[], char data[], double pret);

/*
* Creeaza o lista de obiecte de lungime=0;
* return: lista noua.
*/
Lista creeaza_lista_oferta();

/*
* Sterge prima oferta de un anumit tip din lista de oferte.
* param: oferte=lista de oferte
* pram: tip=tipul cautat
* return: 1, daca oferta a fost stearsa, 0 daca nu exista oferta cu tipul specificat.
*/
int sterge_oferta(Lista* oferte, int id);

/*
* Actualizeaza data plecarii si pretul pentru oferta cu tipul si destinatia specificata.
* param: oferte=lista de oferte
* param: tip=tipul cautat
* param: destinatie=destinatia cautata
* param: data=noua data de plecare
* param: pret=noul pret
* return: 1, daca oferta a fost actualizata, 0 daca nu exista oferta cu tipul si destinatia specificata.
*/
int actualizeaza_oferta(Lista* oferte, int id, char tip[], char destinatie[], char data[], double pret);

/*
* Sorteaza copia unei liste transmisa ca parametru, dupa un criteriu si intr-o ordine data.
* param: oferte=lista de oferte de sortat
* param: criteriu=criteriul dupa care se sorteaza(pret sau destinatie)
* param: ordine=ordinea de sortare(crescator sau descrescator)
* return: copia listei sortata corespunzator.
*/
//Lista sorteaza_oferte(Lista* oferte, char criteriu[], char ordine[]);

/*
* Filtreaza o lista de obiecte, dupa un criteriu dat (aici criteriul este destinatia).
* param: oferte=lista de obiecte(oferte) in care se filtreaza;
* param: destinatie_cautata=criteriul dupa care se realizeaza filtrare.
* return: lista filtrata.
*/
Lista filtreaza_oferta(Lista* oferte, char destinatie_cautata[]);

Lista sorteaza_dupa_pret_crescator(Lista* oferte);

Lista sorteaza_dupa_pret_descrescator(Lista* oferte);

Lista sorteaza_dupa_dest_crescator(Lista* oferte);

Lista sorteaza_dupa_dest_descrescator(Lista* oferte);