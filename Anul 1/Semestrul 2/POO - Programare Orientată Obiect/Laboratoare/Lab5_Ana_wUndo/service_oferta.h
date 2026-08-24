#pragma once
#include "repo_oferta.h"

/*
* Creeaza o lista generica pregatita pentru a stoca oferte.
* return: lista noua.
*/
Lista creeaza_lista_oferta();

/*
* Creeaza o lista generica pregatita pentru a stoca istoricul (alte liste) pentru Undo.
* return: lista noua de undo.
*/
Lista creeaza_lista_undo();

/*
* Returneaza lungimea unei liste transmise ca parametru.
* param: oferte=lista careia i se returneaza lungimea.
* return: lungimea listei
*/
int lungime_lista(Lista oferte);

/*
* Adauga o oferta noua in lista de oferte si salveaza starea pentru undo.
* param: oferte=lista de oferte
* param: undo_list=lista in care se salveaza istoricul (copia listei inainte de adaugare)
* param: id=id-ul ofertei
* param: tip=tipul ofertei
* param: destinatie=destinatia ofertei
* param: data=data plecarii
* param: pret=pretul ofertei
* return: 1 daca a fost adaugata cu succes, 2 daca ID-ul exista deja, 0 daca datele sunt invalide.
*/
int adauga_oferta(Lista* oferte, Lista* undo_list, int id, char tip[], char destinatie[], char data[], double pret);

/*
* Sterge oferta cu id-ul specificat din lista si salveaza starea pentru undo.
* param: oferte=lista de oferte
* param: undo_list=lista in care se salveaza istoricul
* param: id=id-ul ofertei cautate pentru stergere
* return: 1, daca oferta a fost stearsa, 0 daca nu exista oferta cu ID-ul specificat.
*/
int sterge_oferta(Lista* oferte, Lista* undo_list, int id);

/*
*Actualizeaza o oferta cu id-ul specificat si salveaza starea pentru undo.
* param: oferte=lista de oferte
* param: undo_list=lista in care se salveaza istoricul
* param: id=id-ul ofertei care trebuie actualizata
* param: tip=noul tip
* param: destinatie=noua destinatie
* param: data=noua data de plecare
* param: pret=noul pret
* return: 1, daca oferta a fost actualizata, 0 daca datele sunt invalide sau ID-ul nu exista.
*/
int actualizeaza_oferta(Lista* oferte, Lista* undo_list, int id, char tip[], char destinatie[], char data[], double pret);

/*
* Reface ultima operatie care a modificat lista de oferte (Adaugare, Stergere, Actualizare).
* param: oferte=lista curenta de oferte
* param: undo_list=istoricul cu starile anterioare ale listei
* return: 1 daca undo-ul a fost realizat cu succes, 0 daca nu se mai poate face undo.
*/
int fa_undo(Lista* oferte, Lista* undo_list);

/*
* Returneaza o copie a listei, sortata crescator dupa pret.
* param: oferte=lista de oferte de sortat
* return: copia listei sortata.
*/
Lista sorteaza_dupa_pret_crescator(Lista* oferte);

/*
* Returneaza o copie a listei, sortata descrescator dupa pret.
* param: oferte=lista de oferte de sortat
* return: copia listei sortata.
*/
Lista sorteaza_dupa_pret_descrescator(Lista* oferte);

/*
* Returneaza o copie a listei, sortata crescator (alfabetic) dupa destinatie.
* param: oferte=lista de oferte de sortat
* return: copia listei sortata.
*/
Lista sorteaza_dupa_dest_crescator(Lista* oferte);

/*
* Returneaza o copie a listei, sortata descrescator (invers alfabetic) dupa destinatie.
* param: oferte=lista de oferte de sortat
* return: copia listei sortata.
*/
Lista sorteaza_dupa_dest_descrescator(Lista* oferte);

/*
* Returneaza o copie a listei, sortata crescator (alfabetic) dupa tip.
* param: oferte=lista de oferte de sortat
* return: copia listei sortata.
*/
Lista sorteaza_dupa_tip_crescator(Lista* oferte);

/*
* Filtreaza o lista de oferte, returnand doar ofertele care au destinatia specificata.
* param: oferte=lista in care se filtreaza;
* param: destinatie_cautata=destinatia dorita
* return: o noua lista ce contine doar ofertele filtrate.
*/
Lista filtreaza_oferta(Lista* oferte, char destinatie_cautata[]);

Lista filtreaza_dupa_tip(Lista* oferte, char tip_cautat[]);