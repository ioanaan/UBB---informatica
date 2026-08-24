#include <stdio.h>
#include <string.h>
#include "consola.h"
#include "service_oferta.h"
#include "oferta.h" // Aici am rezolvat problema cu "Oferta is undefined"

void afisare_meniu() {
	printf("\n--- AGENTIE DE TURISM ---\n");
	printf("1. Adaugare oferta\n");
	printf("2. Actualizare oferta\n");
	printf("3. Stergere oferta\n");
	printf("4. Vizualizare oferte ordonate (Sortare)\n");
	printf("5. Filtrare oferte dupa destinatie\n");
	printf("6. Filtrare oferte dupa tip\n");     // Optiunea noua adaugata!
	printf("U. UNDO (anuleaza ultima operatie)\n");
	printf("P. Afisare lista oferte\n");
	printf("E. Exit\n");
	printf("Introduceti comanda: ");
}

void adaugare_ui(Lista* oferte, Lista* undo_list) {
	int id;
	char tip[50] = "", destinatie[50] = "", data[50] = "";
	double pret;

	printf("ID: "); scanf_s("%d", &id);
	printf("Tip: "); scanf_s(" %[^\n]", tip, 50);
	printf("Destinatie: "); scanf_s(" %[^\n]", destinatie, 50);
	printf("Data (DD.MM.YYYY): "); scanf_s("%s", data, 50);
	printf("Pret: "); scanf_s("%lf", &pret);

	int rezultat = adauga_oferta(oferte, undo_list, id, tip, destinatie, data, pret);
	if (rezultat == 1) printf("Adaugat cu succes!\n");
	else if (rezultat == 2) printf("Eroare: ID duplicat!\n");
	else printf("Eroare: Date invalide!\n");
}

void sterge_ui(Lista* oferte, Lista* undo_list) {
	int id;
	printf("ID-ul de sters: "); scanf_s("%d", &id);

	if (sterge_oferta(oferte, undo_list, id) == 1) printf("Sters cu succes!\n");
	else printf("Eroare la stergere (ID inexistent).\n");
}

void actualizare_ui(Lista* oferte, Lista* undo_list) {
	int id;
	char tip[50] = "", destinatie[50] = "", data[50] = "";
	double pret;

	printf("ID-ul de actualizat: "); scanf_s("%d", &id);
	printf("Tip nou: "); scanf_s(" %[^\n]", tip, 50);
	printf("Destinatie noua: "); scanf_s(" %[^\n]", destinatie, 50);
	printf("Data noua: "); scanf_s("%s", data, 50);
	printf("Pret nou: "); scanf_s("%lf", &pret);

	if (actualizeaza_oferta(oferte, undo_list, id, tip, destinatie, data, pret) == 1) printf("Actualizat cu succes!\n");
	else printf("Eroare la actualizare (Date invalide sau ID inexistent).\n");
}

void sorteaza_ui(Lista* oferte) {
	printf("1. Pret (crescator)\n");
	printf("2. Pret (descrescator)\n");
	printf("3. Destinatie (crescator)\n");
	printf("4. Destinatie (descrescator)\n");
	printf("5. Tip (crescator - alfabetic)\n");
	printf("Alegeti o optiune de sortare: ");

	int optiune;
	scanf_s("%d", &optiune);

	Lista lista_sortata;

	if (optiune == 1) { lista_sortata = sorteaza_dupa_pret_crescator(oferte); }
	else if (optiune == 2) { lista_sortata = sorteaza_dupa_pret_descrescator(oferte); }
	else if (optiune == 3) { lista_sortata = sorteaza_dupa_dest_crescator(oferte); }
	else if (optiune == 4) { lista_sortata = sorteaza_dupa_dest_descrescator(oferte); }
	else if (optiune == 5) { lista_sortata = sorteaza_dupa_tip_crescator(oferte); }
	else { printf("Optiune invalida!\n"); return; }

	for (int i = 0; i < lungime_lista(lista_sortata); i++) {
		Oferta* of = (Oferta*)get_element(&lista_sortata, i);
		printf("Id: %d | Tip: %s | Destinatie: %s | Pret: %.2lf\n", get_id(*of), get_tip(*of), get_destinatie(*of), get_pret(*of));
	}
	distruge_lista(&lista_sortata);
}

void filtrare_destinatie_ui(Lista* oferte) {
	char destinatie[50] = "";
	printf("Destinatia cautata: "); scanf_s(" %[^\n]", destinatie, 50);

	Lista oferte_gasite = filtreaza_oferta(oferte, destinatie);

	if (lungime_lista(oferte_gasite) == 0) printf("Nu exista oferte pentru aceasta destinatie!\n");
	else {
		for (int i = 0; i < lungime_lista(oferte_gasite); i++) {
			Oferta* of = (Oferta*)get_element(&oferte_gasite, i);
			printf("Id: %d | Tip: %s | Destinatie: %s | Pret: %.2lf\n", get_id(*of), get_tip(*of), get_destinatie(*of), get_pret(*of));
		}
	}
	distruge_lista(&oferte_gasite);
}

// Functia de UI care se ocupa exclusiv de filtrarea dupa tip
void filtrare_tip_ui(Lista* oferte) {
	char tip[50] = "";
	printf("Tipul cautat (ex: munte, mare, city break): "); scanf_s(" %[^\n]", tip, 50);

	Lista oferte_gasite = filtreaza_dupa_tip(oferte, tip);

	if (lungime_lista(oferte_gasite) == 0) printf("Nu exista oferte pentru acest tip!\n");
	else {
		for (int i = 0; i < lungime_lista(oferte_gasite); i++) {
			Oferta* of = (Oferta*)get_element(&oferte_gasite, i);
			printf("Id: %d | Tip: %s | Destinatie: %s | Pret: %.2lf\n", get_id(*of), get_tip(*of), get_destinatie(*of), get_pret(*of));
		}
	}
	distruge_lista(&oferte_gasite);
}

void afisare_ui(Lista* oferte) {
	if (lungime_lista(*oferte) == 0) {
		printf("Lista de oferte este goala.\n");
		return;
	}

	for (int i = 0; i < lungime_lista(*oferte); i++) {
		Oferta* of = (Oferta*)get_element(oferte, i);
		printf("ID: %d | Tip: %s | Destinatie: %s | Data: %s | Pret: %.2lf \n",
			get_id(*of), get_tip(*of), get_destinatie(*of), get_data_plecare(*of), get_pret(*of));
	}
}

void run() {
	Lista oferte = creeaza_lista_oferta();
	Lista undo_list = creeaza_lista_undo();

	while (1) {
		afisare_meniu();
		char cmd[50] = "";
		scanf_s("%s", cmd, 50);

		if (strcmp(cmd, "1") == 0) adaugare_ui(&oferte, &undo_list);
		else if (strcmp(cmd, "2") == 0) actualizare_ui(&oferte, &undo_list);
		else if (strcmp(cmd, "3") == 0) sterge_ui(&oferte, &undo_list);
		else if (strcmp(cmd, "4") == 0) sorteaza_ui(&oferte);
		else if (strcmp(cmd, "5") == 0) filtrare_destinatie_ui(&oferte);
		else if (strcmp(cmd, "6") == 0) filtrare_tip_ui(&oferte); // Apelam functia noua cand apesi 6
		else if (strcmp(cmd, "u") == 0 || strcmp(cmd, "U") == 0) {
			if (fa_undo(&oferte, &undo_list) == 1)
				printf("UNDO realizat cu succes!\n");
			else
				printf("Nu se mai poate face undo!\n");
		}
		else if (strcmp(cmd, "p") == 0 || strcmp(cmd, "P") == 0) afisare_ui(&oferte);
		else if (strcmp(cmd, "e") == 0 || strcmp(cmd, "E") == 0) {
			distruge_lista(&oferte);
			distruge_lista(&undo_list);
			printf("La revedere!\n");
			break;
		}
		else {
			printf("Comanda invalida!\n");
		}
	}
}