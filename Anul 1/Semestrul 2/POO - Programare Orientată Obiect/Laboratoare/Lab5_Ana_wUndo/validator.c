#include "oferta.h"
#include <string.h>

int valideaza_oferta(Oferta oferta)
{
	if (get_id(oferta) < 0)
		return 0;
	if (get_pret(oferta) < 0)
		return 0;
	if (!((strcmp(get_tip(oferta), "munte") == 0) || (strcmp(get_tip(oferta), "mare") == 0) || (strcmp(get_tip(oferta), "citiy break") == 0)))
		return 0;
	char data[50];
	strcpy_s(data, 50, get_data_plecare(oferta));
	if (strlen(data) < 10)
		return 0;
	if (data[2] != '.' && data[5] != '.')
		return 0;
	int zi = (data[0] - '0') * 10 + (data[1] - '0');
	int luna = (data[3] - '0') * 10 + (data[4] - '0');
	int an = (data[6] - '0') * 1000 + (data[7] - '0') * 100 + (data[8] - '0') * 10 + (data[9] - '0');
	if ((zi <= 0 || zi > 31) || (luna <= 0 || luna > 12) || an < 0)
		return 0;
	return 1;
}

int valideaza_criteriu(char criteriu[])
{
	if (!(strcmp(criteriu, "pret") == 0 || strcmp(criteriu, "destinatie") == 0))
		return 0;
	return 1;
}

int valideaza_ordine(char ordine[])
{
	if (!(strcmp(ordine, "crescator") == 0 || strcmp(ordine, "descrescator") == 0))
		return 0;
	return 1;
}
