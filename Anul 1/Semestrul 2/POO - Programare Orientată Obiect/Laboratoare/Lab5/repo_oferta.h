#pragma once
#include "oferta.h"

/*
* Structura care reprezinta o lista de obiecte(oferte).
* campuri:
* -elemente=elementele din lista;
* -lungime=lungimea listei.
*/
typedef struct {
	Oferta* elemente;
	int lungime;
	int capacitate;
}Lista;

/*
* Creeaza o lista de obiecte de lungime=0;
* return: lista noua.
*/
Lista creeaza_lista(int capacitate_initiala);

void distruge_lista(Lista* oferte);

/*
* Adauga o oferta noua la lista de oferte.
* param: oferte=lista de oferte
* param: oferta_noua=oferta de adaugat
* retun: -
*/
void adauga(Lista* oferte, Oferta oferta_noua);

/*
* Sterge prima oferta de tipul precizat din lista de oferte.
* param: oferte=lista de oferte
* param: tip=tipul cautat
* return: 1, daca oferta a fost stearsa, 0 daca nu exista o oferta cu tipul respectiv.
*/
int sterge(Lista* oferte, int id);

/*
* Actualizeaza data plecarii si pretul pentru oferta cu tipul si destinatia specificata.
* param: oferte=lista de oferte
* param: oferta_actualizata=oferta cu datele actualizate.
* return: 1, daca oferta a fost actualizata, 0 daca nu exista oferta cu tipul si destinatia specificata.
*/
int actualizare(Lista* oferte, Oferta oferta_actualizata);

/*
* Returneaza lungimea unei liste transmise ca parametru.
* param: oferte=lista de oferte
* return: lungimea listei
*/
int lungime(Lista oferte);

/*
* Realizeaza o copie a listei transmisa ca parametru.
* param: lista_originala=lista pesntru care se realizeaza o copie
* return: copia listei originale.
*/
Lista copiaza_lista(Lista* lista_originala);

/*
* Sorteaza copia unei liste transmisa ca parametru, trimitand un pointer spre o functie de comparare care decide ordinea sortarii.
* param: oferte=lista de oferte de sortat\
* param: (*functie_cmp)=un pointer care arata spre adresa de inceput a functiei de comparare
* param: (Oferta, Oferta)=parametrii pe care ii poate primii functia de comparare.
* return: copia listei sortata corespunzator.
*/
Lista sorteaza(Lista* oferte, int (*functie_cmp)(Oferta, Oferta));

/*
* Filtreaza o lista de obiecte, dupa un criteriu dat (aici criteriul este destinatia).
* param: oferte=lista de obiecte(oferte) in care se filtreaza;
* param: criteriu=criteriul dupa care se realizeaza filtrare.
* return: lista filtrata.
*/
Lista filtrare(Lista* oferte, char criteriu[]);
