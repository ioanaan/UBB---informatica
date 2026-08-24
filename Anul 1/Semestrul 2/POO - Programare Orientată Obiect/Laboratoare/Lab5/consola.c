#include <stdio.h>
#include "consola.h"
#include <string.h>
#include "validator.h"


void afisare_meniu()
{
	printf("Alege o optiune din meniu: \n");
	printf("1. Adaugarea de noi oferte. \n");
	printf("2. Actualizare oferte. \n");
	printf("3. Stergere oferta. \n");
	printf("4. Vizualizare oferte ordonate dupa pret, destinatie (crescator/descrescator). \n");
	printf("5. Vizualizare oferte filtrate dupa destinatie. \n");
	printf("P. Afisare lista oferte.\n");
	printf("E. Exit\n");
	printf("Introduceti o comanda: ");
}

void adaugare_ui(Lista* oferte)
{
	int id;
	char tip[50], destinatie[50], data[50];
	double pret;
	int id_valid = 0;
	while (id_valid == 0) {
		printf("Introduceti id-ul: ");
		if (scanf_s("%d", &id) == 1) {
			id_valid = 1;
		}
		else {
			printf("Trebuie sa introduceti un numar intreg!\n");
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
		}
	}
	printf("Introduceti tipul: ");
	scanf_s(" %[^\n]", tip, 50);
	printf("Introduceti destinatia: ");
	scanf_s(" %[^\n]", destinatie, 50);
	printf("Introduceti data: ");
	scanf_s("%s", data, 50);
	int pret_valid = 0;
	while (pret_valid == 0) {
		printf("Introduceti pretul: ");
		if (scanf_s("%lf", &pret) == 1) {
			pret_valid = 1;
		}
		else {
			printf("Trebuie sa introduceti un numar valid pentru pret!\n");
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
		}
	}
	int rezultat = adauga_oferta(oferte, id, tip, destinatie, data, pret);
	if (rezultat == 1)
		printf("Oferta a fost adaugata!\n");
	else if (rezultat == 2)
		printf("Exista deja o oferta cu acest ID!\n");
	else
		printf("Au fost introduse date invalide.\n");
}

void sterge_ui(Lista* oferte)
{
	int id;
	int id_valid = 0;
	while (id_valid == 0) {
		printf("Introduceti id-ul: ");
		if (scanf_s("%d", &id) == 1) {
			id_valid = 1;
		}
		else {
			printf("Trebuie sa introduceti un numar intreg!\n");
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
		}
	}
	if (sterge_oferta(oferte, id) == 1)
		printf("Oferta cu id-ul %d a fost stearsa din lista.\n", id);
	else
		printf("Eroare la stergere.\n");
}

void afisare_ui(Lista* oferte)
{
	for (int i = 0; i < oferte->lungime; i++)
		printf("id: %d, tip: %s, destinatie: %s, data: %s, pret: %.2lf \n", get_id(oferte->elemente[i]), get_tip(oferte->elemente[i]), get_destinatie(oferte->elemente[i]), get_data_plecare(oferte->elemente[i]), get_pret(oferte->elemente[i]));
}

void actualizare_ui(Lista* oferte)
{
	int id;
	char tip[50], destinatie[50], data[50];
	double pret;
	int id_valid = 0;
	while (id_valid == 0) {
		printf("Introduceti id-ul ofertei pe care doriti sa o actualizati: ");
		if (scanf_s("%d", &id) == 1) {
			id_valid = 1;
		}
		else {
			printf("Trebuie sa introduceti un numar intreg!\n");
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
		}
	}
	printf("Introduceti nout tip: ");
	scanf_s("%s", tip, 50);
	printf("Introduceti noua destinatie: ");
	scanf_s("%s", destinatie, 50);
	printf("Introduceti noua data: ");
	scanf_s("%s", data, 50);
	int pret_valid = 0;
	while (pret_valid == 0) {
		printf("Introduceti noul pret: ");
		if (scanf_s("%lf", &pret) == 1) {
			pret_valid = 1;
		}
		else {
			printf("Trebuie sa introduceti un numar valid pentru pret!\n");
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
		}
	}
	if (actualizeaza_oferta(oferte, id, tip, destinatie, data, pret) == 1)
		printf("Oferta cu id-ul %d a fost actualizata.\n", id);
	else
		printf("Eroare la actualizare sau date invalide.\n");
}

void sorteaza_ui(Lista* oferte)
{
	printf("Meniu Sortare:\n");
	printf("1. Sortare dupa pret (crescator)\n");
	printf("2. Sortare dupa pret (descrescator)\n");
	printf("3. Sortare dupa destinatie (crescator)\n");
	printf("4. Sortare dupa destinatie (descrescator)\n");
	printf("Alegeti o varianta: ");

	int optiune;
	if (scanf_s("%d", &optiune) != 1) {
		printf("Trebuie sa introduceti un numar!\n");
		int c;
		while ((c = getchar()) != '\n' && c != EOF);
		return;
	}

	Lista lista_sortata;

	if (optiune == 1) {
		lista_sortata = sorteaza_dupa_pret_crescator(oferte);
	}
	else if (optiune == 2) {
		lista_sortata = sorteaza_dupa_pret_descrescator(oferte);
	}
	else if (optiune == 3) {
		lista_sortata = sorteaza_dupa_dest_crescator(oferte);
	}
	else if (optiune == 4) {
		lista_sortata = sorteaza_dupa_dest_descrescator(oferte);
	}
	else {
		printf("Optiune invalida!\n");
		return; 
	}

	if (lungime_lista(lista_sortata) == 0) {
		printf("Nu exista elemente in lista.\n");
	}
	else {
		printf("Lista de oferte sortata este: \n");
		for (int i = 0; i < lungime_lista(lista_sortata); i++) {
			printf("Id: %d | Tip: %s | Destinatie: %s | Data: %s | Pret: %.2lf\n",
				get_id(lista_sortata.elemente[i]),
				get_tip(lista_sortata.elemente[i]),
				get_destinatie(lista_sortata.elemente[i]),
				get_data_plecare(lista_sortata.elemente[i]),
				get_pret(lista_sortata.elemente[i]));
		}
	}

	distruge_lista(&lista_sortata);
}

void filtrare_ui(Lista* oferte)
{
	char destinatie[50];
	printf("Introduceti destinatia cautata: ");
	scanf_s("%s", destinatie, 50);
	Lista oferte_gasite = filtreaza_oferta(oferte, destinatie);
	if (lungime_lista(oferte_gasite) == 0)
		printf("Nu exista oferte pentru destinatia %s.\n", destinatie);
	else
	{
		printf("Ofertele gasite pentru destinatia %s sunt: \n", destinatie);
		for (int i = 0; i < lungime_lista(oferte_gasite); i++)
		{
			printf("Id: %d | Tip: %s | Destinatie: %s | Data: %s | Pret: %.2lf\n",
				get_id(oferte_gasite.elemente[i]),
				get_tip(oferte_gasite.elemente[i]),
				get_destinatie(oferte_gasite.elemente[i]),
				get_data_plecare(oferte_gasite.elemente[i]),
				get_pret(oferte_gasite.elemente[i]));
		}
	}
	distruge_lista(&oferte_gasite);
}

void initializare_ui(Lista* oferte)
{
	adauga_oferta(oferte, 1, "munte", "Brasov", "20.10.2026", 1500);
	adauga_oferta(oferte, 2,  "munte", "Brasov", "30.11.2026", 1000);
	adauga_oferta(oferte, 3,  "mare", "Grecia", "02.08.2026", 3500);
	adauga_oferta(oferte, 4,  "citiy break", "Franta", "30.09.2026", 4500);
	adauga_oferta(oferte, 5,  "mare", "Constanta", "05.03.2027", 5000);
}

void run()
{
	Lista oferte=creeaza_lista_oferta();
	initializare_ui(&oferte);

	while (1)
	{
		afisare_meniu();
		char cmd[50];
		scanf_s("%s", cmd, 50);
		if (strcmp(cmd, "1")==0)
		{
			adaugare_ui(&oferte);
		}
		else if (strcmp(cmd, "2") == 0)
		{
			actualizare_ui(&oferte);
		}
		else if (strcmp(cmd, "3") == 0)
		{
			sterge_ui(&oferte);
		}
		else if (strcmp(cmd, "4") == 0)
		{
			sorteaza_ui(&oferte);
		}
		else if (strcmp(cmd, "5") == 0)
		{
			filtrare_ui(&oferte);
		}
		else if (strcmp(cmd, "p") == 0 || strcmp(cmd, "P") == 0)
		{
			printf("Lista contine urmatoarele oferte: \n");
			afisare_ui(&oferte);
		}
		else if (strcmp(cmd, "e") == 0 || strcmp(cmd, "E") == 0)
		{
			printf("Programul s-a terminat!\n");
			distruge_lista(&oferte);
			break;
		}
		else
		{
			printf("Comanda invalida!\n");
		}
	}
}