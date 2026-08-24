#define _CRT_SECURE_NO_WARNINGS
#include "Ui.h"
#pragma warning(disable: 6031)

void meniu_principal()
{
	printf("\n~~~Meniu principal~~~\n");
	printf("1. Adauga masina\n");
	printf("2. Actualizeaza masina\n");
	printf("3. Inchiriere/Returnare masina\n");
	printf("4. Vizualizeaza masinile\n");
	printf("5. Sortarea masinior\n");
	printf("0. Exit\n");
	printf("Alege o optiune: ");
}

void meniu_vizualizare()
{
	printf("\n~~~Meniu vizualizare~~~\n");
	printf("1. Vizualizare integrala masini\n");
	printf("2. Vizualizare dupa model\n");
	printf("3. Vizualizare dupa categorie\n");
	printf("0. Back\n");
	printf("Alege o optiune: ");
}

void meniu_sortare()
{
	printf("\n~~~Meniu sortare~~~\n");
	printf("1. Sortare dupa model crescator\n");
	printf("2. Sortare dupa model descrescator\n");
	printf("3. Sortare dupa categorie crescator\n");
	printf("4. Sortare dupa categorie descrescator\n");
	printf("0. Back\n");
	printf("Alege o optiune: ");
}

void afisare_masini(ListaMasini l) 
{
	/*
	 * Descriere: Afiseaza formatat datele dintr-o lista de masini.
	 * Parametri: l (ListaMasini) - lista de masini ce trebuie afisata.
	 * Preconditii: l reprezinta o lista initializata.
	 * Postconditii: Datele sunt tiparite in consola.
	 */

	if (l.nr_masini == 0)
	{
		printf("nu sunt masini\n");
		return;
	}

	for (int i = 0; i < l.nr_masini; i++) 
	{
		printf("Numar: %s | Model: %s | Categorie: %s | Status: %d\n",
			l.masini[i].numar, l.masini[i].model, l.masini[i].categorie, l.masini[i].status);
	}
	printf("\n");
}

void ui_adauga(ListaMasini* lis)
{
	/*
	 * Descriere: Preia datele de la utilizator si gestioneaza procesul de adaugare a unei masini.
	 * Parametri: lis (ListaMasini*) - pointer catre lista principala.
	 * Preconditii: lis reprezinta o lista valida.
	 * Postconditii: Operatiunea este trimisa catre executie si se afiseaza starea ei (succes/eroare).
	 */

	char numar[20], model[20], categorie[20];
	int status;

	printf("Numar: ");
	scanf("%s", numar);
	printf("Model: ");
	scanf("%s", model);
	printf("Categorie (suv, cabrio, sedan, hatchback, break): ");
	scanf("%s", categorie);
	printf("Status (0 sau 1): ");
	scanf("%d", &status);

	int rezultat = adauga_masina_service(lis, numar, model, categorie, status);
	if (rezultat == 0)
		printf("masina adaugata\n");
	else if (rezultat == 1)
		printf("date invalide\n");
	else if (rezultat == 2)
		printf("masina exista\n");
}

void ui_actualizare(ListaMasini* lis)
{
	/*
	 * Descriere: Preia datele de la utilizator si gestioneaza procesul de actualizare a unei masini.
	 * Parametri: lis (ListaMasini*) - pointer catre lista principala.
	 * Preconditii: lis reprezinta o lista valida.
	 * Postconditii: Operatiunea este trimisa catre executie si se afiseaza starea ei (succes/eroare).
	 */

	char numar[20], model[20], categorie[20];
	int status;

	printf("Numar: ");
	scanf("%s", numar);
	printf("Model: ");
	scanf("%s", model);
	printf("Categorie (suv, cabrio, sedan, hatchback, break): ");
	scanf("%s", categorie);
	printf("Status (0 sau 1): ");
	scanf("%d", &status);

	int rezultat = actualizare_masina_service(lis, numar, model, categorie, status);
	if (rezultat == 0)
		printf("masina actualizata\n");
	else if (rezultat == 1)
		printf("date invalide\n");
	else if (rezultat == 2)
		printf("masina nu exista\n");
}

void ui_inchiriere_returnare(ListaMasini* lis)
{
	/*
	 * Descriere: Preia datele de la utilizator si gestioneaza procesul de inchiriere sau returnare a unei masini.
	 * Parametri: lis (ListaMasini*) - pointer catre lista principala.
	 * Preconditii: lis reprezinta o lista valida.
	 * Postconditii: Operatiunea este trimisa catre executie si se afiseaza starea ei (succes/eroare).
	 */
	char numar[20];
	int status;
	printf("Numar: ");
	scanf("%s", numar);
	printf("Status (0 pentru returnare, 1 pentru inchiriere): ");
	scanf("%d", &status);
	int rezultat = inchiriere_returnare_service(lis, numar, status);
	if (rezultat == 0)
	{
		if (status == 1)
			printf("masina inchiriata\n");
		else
			printf("masina returnata\n");
	}
	else if (rezultat == 1)
		printf("date invalide\n");
	else if (rezultat == 2)
		printf("masina nu exista\n");
}

void ui_vizualizare_masini(ListaMasini* lis)
{
	/*
	 * Descriere: Afiseaza toate masinile din lista.
	 * Parametri: lis (ListaMasini*) - pointer catre lista principala.
	 * Preconditii: lis reprezinta o lista valida.
	 * Postconditii: Toate masinile sunt afisate pe ecran.
	 */
	printf("\nVizualizare masini:\n");
	afisare_masini(*lis);
}

void ui_filtrare_model(ListaMasini* lis)
{
	/*
	 * Descriere: Gestioneaza filtrarea masinilor dupa model si afisarea rezultatelor.
	 * Parametri: lis (ListaMasini*) - pointer catre lista principala.
	 * Preconditii: lis reprezinta o lista valida.
	 * Postconditii: Rezultatele operatiunii sunt afisate pe ecran.
	 */

	char model[20];

	printf("Model: ");
	scanf("%s", model);

	printf("\nFiltrare dupa model:\n");
	ListaMasini filtrate = filtrare_dupa_model(lis, model);
	afisare_masini(filtrate);

	distruge_lista(&filtrate);
}


void ui_filtrare_categorie(ListaMasini* lis)
{
	/*
	 * Descriere: Gestioneaza filtrarea masinilor dupa categorie si afisarea rezultatelor.
	 * Parametri: lis (ListaMasini*) - pointer catre lista principala.
	 * Preconditii: lis reprezinta o lista valida.
	 * Postconditii: Rezultatele operatiunii sunt afisate pe ecran.
	 */

	char categorie[20];

	printf("Categorie (suv, cabrio, sedan, hatchback, break): ");
	scanf("%s", categorie);

	printf("\nFiltrare dupa categorie:\n");
	ListaMasini filtrate = filtrare_dupa_categorie(lis, categorie);
	afisare_masini(filtrate);

	distruge_lista(&filtrate);
}

void ui_sortare_model_crescator(ListaMasini* lis)
{
	/*
	 * Descriere: Gestioneaza ordonarea masinilor (dupa model/categorie crescator/descrescator) si afisarea lor.
	 * Parametri: lis (ListaMasini*) - pointer catre lista principala.
	 * Preconditii: lis reprezinta o lista valida.
	 * Postconditii: Lista ordonata este afisata pe ecran.
	 */

	printf("\nSortare dupa model crescator...\n");
	ListaMasini sortate = dupa_model_crescator(lis);
	afisare_masini(sortate);

	distruge_lista(&sortate);
}

void ui_sortare_model_descrescator(ListaMasini* lis)
{
	// ----//----
	printf("\nSortare dupa model descrescator...\n");
	ListaMasini sortate = dupa_model_descrescator(lis);
	afisare_masini(sortate);

	distruge_lista(&sortate);
}

void ui_sortare_categorie_crescator(ListaMasini* lis)
{
	// ----//----
	printf("\nSortare dupa categorie crescator...\n");
	ListaMasini sortate = dupa_categorie_crescator(lis);
	afisare_masini(sortate);

	distruge_lista(&sortate);
}

void ui_sortare_categorie_descrescator(ListaMasini* lis)
{
	// ----//----
	printf("\nSortare dupa categorie descrescator...\n");
	ListaMasini sortate = dupa_categorie_descrescator(lis);
	afisare_masini(sortate);

	distruge_lista(&sortate);
}

void start()
{
	/*
	 * Descriere: Porneste si mentine in executie aplicatia consola.
	 * Parametri: Nu are.
	 * Preconditii: Aplicatia este configurata corect.
	 * Postconditii: Programul interactioneaza cu utilizatorul pana la comanda de oprire.
	 */

	ListaMasini lis;
	initializare_lista(&lis);

	while (1)
	{
		meniu_principal();

		int optiune;
		scanf("%d", &optiune);

		if (optiune == 0)
			break;

		switch (optiune)
		{
		case 1:
		{
			ui_adauga(&lis);
			break;
		}
		case 2:
		{
			ui_actualizare(&lis);
			break;
		}
		case 3:
		{
			ui_inchiriere_returnare(&lis);
			break;
		}
		case 4:
		{
			meniu_vizualizare();
			int opt_v;
			scanf("%d", &opt_v);
			if (opt_v == 1) 
			{
				ui_vizualizare_masini(&lis);
			}
			else if (opt_v == 2) 
			{
				ui_filtrare_model(&lis);
			}
			else if (opt_v == 3) 
			{
				ui_filtrare_categorie(&lis);
			}
			break;
		}
		case 5:
		{
			meniu_sortare();
			int opt_s;
			scanf("%d", &opt_s);
			if (opt_s == 1) 
			{
				ui_sortare_model_crescator(&lis);

			}
			else if (opt_s == 2) 
			{
				ui_sortare_model_descrescator(&lis);
				
			}
			else if (opt_s == 3) 
			{
				ui_sortare_categorie_crescator(&lis);
				
			}
			else if (opt_s == 4) 
			{
				ui_sortare_categorie_descrescator(&lis);
				
			}
			break;
		}
		default:
			printf("optiune invalida\n");
		}
	}
	distruge_lista(&lis);
}