#include <string.h>
#include "oferta.h"
#include <stdlib.h>

int get_id(Oferta oferta)
{
	return oferta.id;
}

char* get_tip(Oferta oferta)
{
	return oferta.tip;
}

char* get_destinatie(Oferta oferta)
{
	return oferta.destinatie;
}

char* get_data_plecare(Oferta oferta)
{
	return oferta.data_plecare;
}

double get_pret(Oferta oferta)
{
	return oferta.pret;
}

Oferta initializeaza(int id, char* tip, char* destinatie, char* data, double pret)
{
	Oferta oferta;
	oferta.id = id;
	oferta.pret = pret;

	oferta.tip = (char*)malloc(sizeof(char) * (strlen(tip) + 1));
	if (oferta.tip != NULL) {
		strcpy_s(oferta.tip, strlen(tip) + 1, tip);
	}

	oferta.destinatie = (char*)malloc(sizeof(char) * (strlen(destinatie) + 1));
	if (oferta.destinatie != NULL) {
		strcpy_s(oferta.destinatie, strlen(destinatie) + 1, destinatie);
	}

	oferta.data_plecare = (char*)malloc(sizeof(char) * (strlen(data) + 1));
	if (oferta.data_plecare != NULL) {
		strcpy_s(oferta.data_plecare, strlen(data) + 1, data);
	}

	return oferta;
}
void distruge_oferta(Oferta* oferta)
{
	free(oferta->tip);
	free(oferta->destinatie);
	free(oferta->data_plecare);

	// Ca masura de siguranta, setam pointerii la NULL dupa stergere
	oferta->tip = NULL;
	oferta->destinatie = NULL;
	oferta->data_plecare = NULL;
}