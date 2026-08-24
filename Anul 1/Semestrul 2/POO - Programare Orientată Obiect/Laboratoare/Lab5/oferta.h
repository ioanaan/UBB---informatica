#pragma once 

/*
* Structura care reprezinta o oferta dintr-o agentie de turism.
* campuri:
* -tip=tipul ofertei(munte, mare, city break)
* -destinatie=destinatia ofertei
* -data_plecare=data plecarii
* -pret=pretul aferent ofertei
*/
typedef struct {
	int id;
	char* tip;
	char* destinatie;
	char* data_plecare;
	double pret;
}Oferta;

/*
* Returneaza id-ul unei oferte.
* param: oferta=oferta careia i se returneaza id-ul;
* return: id-ul ofertei
*/
int get_id(Oferta oferta);

/*
* Returneaza tipul unei oferte.
* param: oferta=oferta careia i se returneaza tipul;
* return: tipul ofertei
*/
char* get_tip(Oferta oferta);

/*
*Returneaza destinatia unei oferte.
* param: oferta=oferta careia i se returneaza destinatia;
* return: destinatia ofertei
*/
char* get_destinatie(Oferta oferta);

/*
*Returneaza data plecarii unei oferte.
* param: oferta=oferta careia i se returneaza data;
* return: data plecarii ofertei
*/
char* get_data_plecare(Oferta oferta);

/*
* Returneaza pretul unei oferte.
* param: oferta=oferta careia i se returneaza pretul;
* return: pretul ofertei
*/
double get_pret(Oferta oferta);

/*
* Initializeaza o oferta cu datele transmise ca parametrii.
* param: tip=tipul ofertei
* param: destinatie=destinatia ofertei
* param: data=data plecarii ofertei
* param: pret=pretul ofertei
* return: oferta cu datele initializate.
*/
Oferta initializeaza(int id, char* tip, char* destinatie, char* data, double pret);


/*
* Distruge oferta pentru a elibera memoria alocata dinamic.
* param: oferta care se distruge.
*/
void distruge_oferta(Oferta* oferta);
