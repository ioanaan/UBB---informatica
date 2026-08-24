#pragma once

typedef void (*DestroyFunction)(void*);
typedef void* (*CopyFunction)(void*);

// Structura lista de obiecte generice 
typedef struct {
	void** elemente; // vector pointeri
	int lungime;
	int capacitate;
	DestroyFunction fn_destroy;  // distruge elem curent
	CopyFunction fn_copy;        // copieza elem curent
} Lista;

/*
* Creeaza o lista de obiecte generice de lungime=0;
* return: lista noua.
*/
Lista creeaza_lista(int capacitate_initiala, DestroyFunction dest_fn, CopyFunction copy_fn);

/*
* Distruge lista pentru a elibera memoria alocata dinamic. 
*/
void distruge_lista(Lista* oferte);

/*
* Adauga un element nou la lista.
* param: oferte=lista de oferte
* param: element=pointer catre elementul de adaugat
* retun: -
*/
void adauga(Lista* oferte, void* element);

/*
* Sterge elementul de pe pozitia precizata din lista.
* param: oferte=lista de elemente
* param: poz=pozitia de sters
*/
void sterge_pozitie(Lista* oferte, int poz);

/*
* Returneaza elementul de pe o pozitie data.
* param: oferte=lista de elemente
* param: poz=pozitia elementului
* return: un pointer catre elementul cautat
*/
void* get_element(Lista* oferte, int poz);

/*
* Returneaza lungimea unei liste transmise ca parametru.
* param: oferte=lista
* return: lungimea listei
*/
int lungime(Lista oferte);

/*
* Realizeaza o copie a listei transmisa ca parametru.
* param: lista_originala=lista pentru care se realizeaza o copie
* return: copia listei originale.
*/
Lista copiaza_lista(Lista* lista_originala);